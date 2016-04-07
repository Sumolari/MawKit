//
//  AdKit.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../AdKit.hpp"
#include "../../_AdKit.hpp"

#include <GoogleMobileAds/GoogleMobileAds.h>
#include <UIKit/UIKit.h>

#include "../../Analytics.hpp"
#include "../../Device.hpp"
#include "../../Log.hpp"
#include "../Common/CPPUtils.h"
#include "GADMAdapterAdColonyExtras.h"
#include "GADMAdapterAdColonyInitializer.h"

//------------------------------------------------------------------------------
// Storage of active delegates and ads.
//------------------------------------------------------------------------------

NSMutableDictionary<NSString *, id> *delegates;
NSMutableDictionary<NSString *, GADInterstitial *> *interstitials;
NSMutableDictionary<NSString *, GADBannerView *> *banners;

//------------------------------------------------------------------------------
#pragma mark - Banner view
//------------------------------------------------------------------------------

@interface BannerViewDelegate : NSObject <GADBannerViewDelegate>

@property ( nonatomic, strong ) NSString *adUnitId;

@property ( nonatomic, strong ) NSArray *testDevices;

@property ( nonatomic ) MK::AdKit::BannerSize size;

- (id)initWithAdUnitID:(NSString *)adID
               forSize:(MK::AdKit::BannerSize)size
        andTestDevices:(NSArray *)devices;

+ (GADAdSize)GADAdSizeForMKBannerSize:(MK::AdKit::BannerSize)size;

@end

@implementation BannerViewDelegate

- (id)initWithAdUnitID:(NSString *)adID
               forSize:(MK::AdKit::BannerSize)size
        andTestDevices:(NSArray *)devices
{
	self = [super init];
	if ( self ) {
		self.adUnitId    = adID;
		self.size        = size;
		self.testDevices = devices;
	}
	return self;
}

- (void)requestNewBanner
{
	banners[self.adUnitId] = [[GADBannerView alloc]
	initWithAdSize:[self.class GADAdSizeForMKBannerSize:self.size]];
	banners[self.adUnitId].adUnitID = self.adUnitId;
	banners[self.adUnitId].delegate = self;
	banners[self.adUnitId].rootViewController =
	[UIApplication sharedApplication].keyWindow.rootViewController;

	GADRequest *request = [GADRequest request];
	request.testDevices = self.testDevices;
	[banners[self.adUnitId] loadRequest:request];
}

- (void)adViewWillDismissScreen:(GADBannerView *)bannerView
{
	[self requestNewBanner];
}

+ (GADAdSize)GADAdSizeForMKBannerSize:(MK::AdKit::BannerSize)size
{
	switch ( size ) {
	case MK::AdKit::BannerSize::StandardBanner:
		return kGADAdSizeBanner;
	case MK::AdKit::BannerSize::LargeBanner:
		return kGADAdSizeLargeBanner;
	case MK::AdKit::BannerSize::IABMediumRectangle:
		return kGADAdSizeMediumRectangle;
	case MK::AdKit::BannerSize::IABFullSizeBanner:
		return kGADAdSizeFullBanner;
	case MK::AdKit::BannerSize::IABLeaderboard:
		return kGADAdSizeLeaderboard;
	case MK::AdKit::BannerSize::SmartBannerPortrait:
		return kGADAdSizeSmartBannerPortrait;
	case MK::AdKit::BannerSize::SmartBannerLandscape:
		return kGADAdSizeSmartBannerLandscape;
	}
}

@end

//------------------------------------------------------------------------------
#pragma mark - Interstitial
//------------------------------------------------------------------------------

@interface InterstitialDelegate : NSObject <GADInterstitialDelegate>

@property ( nonatomic, strong ) NSString *adUnitId;

@property ( nonatomic, strong ) NSArray *testDevices;

- (id)initWithAdUnitID:(NSString *)adID andTestDevices:(NSArray *)devices;

- (void)requestNewInterstitial;

@end

@implementation InterstitialDelegate

- (id)initWithAdUnitID:(NSString *)adID andTestDevices:(NSArray *)devices;
{
	self = [super init];
	if ( self ) {
		self.adUnitId    = adID;
		self.testDevices = devices;
	}
	return self;
}

- (void)requestNewInterstitial
{
	interstitials[self.adUnitId] = [[GADInterstitial alloc] initWithAdUnitID:self.adUnitId];
	interstitials[self.adUnitId].delegate =
	(id<GADInterstitialDelegate>)delegates[self.adUnitId];
	GADRequest *request = [GADRequest request];
	request.testDevices = self.testDevices;
	[interstitials[self.adUnitId] loadRequest:request];
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)interstitial
{
#pragma unused( interstitial )
	[self requestNewInterstitial];
}

@end

//------------------------------------------------------------------------------
#pragma mark - Video reward
//------------------------------------------------------------------------------

@interface RewardVideoDelegate : NSObject <GADRewardBasedVideoAdDelegate>

@property ( nonatomic, strong ) NSString *adUnitId;

@property ( nonatomic, copy ) void ( ^callback )( BOOL );

- (id)initWithAdUnitID:(NSString *)adID andCallback:(void ( ^)( BOOL ))callback;

- (void)requestNewRewardVideo;

@end

@implementation RewardVideoDelegate

- (id)initWithAdUnitID:(NSString *)adID andCallback:(void ( ^)( BOOL ))callback
{
	self = [super init];
	if ( self ) {
		self.adUnitId = adID;
		self.callback = callback;
		[self requestNewRewardVideo];
	}
	return self;
}

- (void)requestNewRewardVideo
{
	GADRequest *request                             = [GADRequest request];
	[GADRewardBasedVideoAd sharedInstance].delegate = self;
	[[GADRewardBasedVideoAd sharedInstance] loadRequest:request
	                                       withAdUnitID:self.adUnitId];
}

- (void)rewardBasedVideoAd:(GADRewardBasedVideoAd *)rewardBasedVideoAd
   didRewardUserWithReward:(GADAdReward *)reward
{
#pragma unused( rewardBasedVideoAd )
#pragma unused( reward )
	self.callback( true );
}

- (void)rewardBasedVideoAdDidClose:(GADRewardBasedVideoAd *)rewardBasedVideoAd
{
#pragma unused( rewardBasedVideoAd )
	[self requestNewRewardVideo];
}

- (void)rewardBasedVideoAd:(GADRewardBasedVideoAd *)rewardBasedVideoAd
    didFailToLoadWithError:(NSError *)error
{
#pragma unused( rewardBasedVideoAd )
#pragma unused( error )
	[self requestNewRewardVideo];
}

@end

//------------------------------------------------------------------------------
#pragma mark - MawKit
//------------------------------------------------------------------------------

namespace MK {
namespace AdKit {

void _init( std::string interstitialUnitID,
            std::string bottomBannerUnitID,
            BannerSize bottomBannerSize,
            std::string topBannerUnitID,
            BannerSize topBannerSize,
            std::string videoRewardUnitID,
            std::string adColonyAppID,
            std::string adColonyZoneID,
            std::string adColonyCustomID,
            std::vector<std::string>
            testingDevices )
{
	interstitials = [NSMutableDictionary dictionary];
	banners       = [NSMutableDictionary dictionary];
	delegates     = [NSMutableDictionary dictionary];

	NSArray *ns_testingDevices = to_nsarray( testingDevices );

	if ( interstitialUnitID.size() > 0 ) {
		NSString *interstitialID = to_nsstring( interstitialUnitID );

		interstitials[interstitialID] =
		[[GADInterstitial alloc] initWithAdUnitID:interstitialID];

		delegates[interstitialID] =
		[[InterstitialDelegate alloc] initWithAdUnitID:interstitialID
		                                andTestDevices:ns_testingDevices];

		GADRequest *request = [GADRequest request];
		request.testDevices = ns_testingDevices;
		[interstitials[interstitialID] loadRequest:request];

		interstitials[interstitialID].delegate =
		(id<GADInterstitialDelegate>)delegates[interstitialID];

		[((InterstitialDelegate *)delegates[interstitialID])requestNewInterstitial];
	}

	if ( bottomBannerUnitID.size() > 0 ) {
		NSString *bottomID = to_nsstring( bottomBannerUnitID );

		banners[bottomID] = [[GADBannerView alloc]
		initWithAdSize:[BannerViewDelegate GADAdSizeForMKBannerSize:bottomBannerSize]];

		delegates[bottomID] =
		[[BannerViewDelegate alloc] initWithAdUnitID:bottomID
		                                     forSize:bottomBannerSize
		                              andTestDevices:ns_testingDevices];

		banners[bottomID].delegate = (id<GADBannerViewDelegate>)delegates[bottomID];
		banners[bottomID].rootViewController =
		[UIApplication sharedApplication].keyWindow.rootViewController;
	}

	if ( topBannerUnitID.size() > 0 ) {
		NSString *topID = to_nsstring( topBannerUnitID );

		banners[topID] = [[GADBannerView alloc]
		initWithAdSize:[BannerViewDelegate GADAdSizeForMKBannerSize:topBannerSize]];

		delegates[topID] = [[BannerViewDelegate alloc] initWithAdUnitID:topID
		                                                        forSize:topBannerSize
		                                                 andTestDevices:ns_testingDevices];

		banners[topID].delegate = (id<GADBannerViewDelegate>)delegates[topID];
		banners[topID].rootViewController =
		[UIApplication sharedApplication].keyWindow.rootViewController;
	}

	if ( videoRewardUnitID.size() > 0 ) {

		NSString *videoRewardID = to_nsstring( videoRewardUnitID );


		delegates[videoRewardID] = [[RewardVideoDelegate alloc] initWithAdUnitID:videoRewardID
		                                                             andCallback:nil];

		[GADMAdapterAdColonyInitializer
		startWithAppID:to_nsstring( adColonyAppID )
		      andZones:@[to_nsstring( adColonyZoneID )]
		   andCustomID:to_nsstring( adColonyCustomID )];
	}
}

void _showInterstitial( std::string adUnitID )
{
	auto interstitial = interstitials[to_nsstring( adUnitID )];
	if ( [interstitial isReady] ) {
		[interstitial
		presentFromRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
	}
}

void _showVideoReward( std::string adUnitID, std::function<void( bool )> callback )
{
	if ( [GADRewardBasedVideoAd sharedInstance].isReady ) {
		( (RewardVideoDelegate *)delegates[to_nsstring( adUnitID )] ).callback =
		^( BOOL success ) {
		  callback( success );
		};
		[[GADRewardBasedVideoAd sharedInstance]
		presentFromRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
	}
	else {
		Analytics::logNonReadyVideoRewardDisplay();
		callback( false );
	}
}

bool videoRewardsAvailable()
{
	return enabled() && MK::Device::isUsingWifi() &&
	       [GADRewardBasedVideoAd sharedInstance].isReady;
}

void _showTopBanner( std::string adUnitID )
{
	auto view = [UIApplication sharedApplication].keyWindow.rootViewController.view;

	for ( UIView *subview in view.subviews ) {
		if ( [subview isKindOfClass:GADBannerView.class] ) {
			MK::Log::warning(
			"Trying to show a top banner view when a banner view "
			"is already visible. Call ignored." );
			return;
		}
	}


	[((BannerViewDelegate *)delegates[to_nsstring( adUnitID )])requestNewBanner];

	auto banner = banners[to_nsstring( adUnitID )];
	[view addSubview:banner];
}

void _showBottomBanner( std::string adUnitID )
{
	MK::Log::nonCriticalCrash( "Method _showBottomBanner not implemented yet" );

	/*
	auto view = [UIApplication
	sharedApplication].keyWindow.rootViewController.view;

	for ( UIView *subview in view.subviews ) {
	    if ( [subview isKindOfClass:GADBannerView.class] ) {
	        MK::Log::warning(
	        "Trying to show a top banner view when a banner view "
	        "is already visible. Call ignored." );
	        return;
	    }
	}

	[((BannerViewDelegate *)delegates[to_nsstring( adUnitID
	)])requestNewBanner];

	auto banner = banners[to_nsstring( adUnitID )];

	CGFloat screen_height = view.bounds.size.height;
	CGFloat banner_height = banner.bounds.size.height;

	banner.bounds = CGRectMake( banner.bounds.origin.x, screen_height -
	banner_height,
	                            banner.bounds.size.width, banner_height );

	[view addSubview:banner];
	 */
}

}; // namespace AdKit
}; // namespace MK
