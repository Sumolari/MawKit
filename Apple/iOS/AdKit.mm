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
#include "../Common/CPPUtils.h"
#include "GADMAdapterAdColonyExtras.h"
#include "GADMAdapterAdColonyInitializer.h"

NSMutableDictionary<NSString *, id> *delegates;
NSMutableDictionary<NSString *, GADInterstitial *> *interstitials;

@interface InterstitialDelegate : NSObject <GADInterstitialDelegate>

@property ( nonatomic, strong ) NSString *adUnitId;

@property ( nonatomic, strong ) NSArray *testDevices;

- (id)initWithAdUnitID:(NSString *)adID andTestDevices:(NSArray *)devices;

- (void)requestNewDeathInterstitial;

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

- (void)requestNewDeathInterstitial
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
	[self requestNewDeathInterstitial];
}

@end

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

namespace MK {
namespace AdKit {

void _init( std::string interstitialUnitID,
            std::string videoRewardUnitID,
            std::string adColonyAppID,
            std::string adColonyZoneID,
            std::string adColonyCustomID,
            std::vector<std::string>
            testingDevices )
{
	NSString *interstitialID = to_nsstring( interstitialUnitID );
	NSString *videoRewardID  = to_nsstring( videoRewardUnitID );

	interstitials[interstitialID] =
	[[GADInterstitial alloc] initWithAdUnitID:interstitialID];

	interstitials = [@{
		interstitialID: [[GADInterstitial alloc] initWithAdUnitID:interstitialID]
	} mutableCopy];

	delegates = [@{
		videoRewardID: [[RewardVideoDelegate alloc] initWithAdUnitID:videoRewardID
		                                                 andCallback:nil],
		interstitialID:
		[[InterstitialDelegate alloc] initWithAdUnitID:interstitialID
		                                andTestDevices:to_nsarray( testingDevices )],
	} mutableCopy];

	GADRequest *request = [GADRequest request];
	request.testDevices = to_nsarray( testingDevices );
	[interstitials[interstitialID] loadRequest:request];

	interstitials[interstitialID].delegate =
	(id<GADInterstitialDelegate>)delegates[interstitialID];

	[GADMAdapterAdColonyInitializer
	startWithAppID:to_nsstring( adColonyAppID )
	      andZones:@[to_nsstring( adColonyZoneID )]
	   andCustomID:to_nsstring( adColonyCustomID )];

	[((InterstitialDelegate *)delegates[interstitialID])requestNewDeathInterstitial];
}

void _sessionStart()
{
}

void _sessionEnd()
{
}

void _preloadAd( const AdType & )
{
	// Nothing to do here as Admob handles everything via delegate calls and
	// init method.
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
#pragma unused( adUnitID )
	assert( "Not implemented yet" );
}

void _showBottomBanner( std::string adUnitID )
{
#pragma unused( adUnitID )
	assert( "Not implemented yet" );
}

}; // namespace AdKit
}; // namespace MK
