//
//  AdKit.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef AdKit_hpp
#define AdKit_hpp

#include <functional>
#include <string>
#include <vector>

namespace MK {

/**
 *  `AdKit` namespace features methods to preload and display ads. This methods
 *  automatically take into account whether Ads are enabled for this user or
 *  not.
 */
namespace AdKit {

/// Size of banner view ad.
enum class BannerSize {
	/**
     *  300x50, phones and tablets. `kGADAdSizeBanner`.
     */
	StandardBanner = 0,
	/**
     *  320x100, phones and tablets. `kGADAdSizeLargeBanner`.
     */
	LargeBanner = 1,
	/**
     *  300x250, phones and tablets. `kGADAdSizeMediumRectangle`.
     */
	IABMediumRectangle = 2,
	/**
     *  468x60, phones and tablets. `kGADAdSizeFullBanner`.
     */
	IABFullSizeBanner = 3,
	/**
     *  728x60, phones and tablets. `kGADAdSizeLeaderboard`.
     */
	IABLeaderboard = 4,
	/**
     *  screen width x 32|50|90, phones and tablets.
     *  `kGADAdSizeSmartBannerPortrait`.
     */
	SmartBannerPortrait = 5,
	/**
     *  screen width x 32|50|90, phones and tablets.
     *  `kGADAdSizeSmartBannerLandscape`.
     */
	SmartBannerLandscape = 6
};

/**
 *  Performs any initialization required by the ads adapter.
 *
 *  @param interstitialUnitID ID of interstitial Ad unit to be queried.
 *  @param bottomBannerUnitID ID of bottom banner view Ad unit to be queried.
 *  @param bottomBannerSize   Size of bottom banner view Ad.
 *  @param topBannerUnitID    ID of top banner view Ad unit to be queried.
 *  @param topBannerSize      Size of top banner view Ad.
 *  @param videoRewardUnitID  ID of video reward Ad unit to be queried.
 *  @param adColonyAppID      ID of AdColony app to be queried.
 *  @param adColonyZoneID     ID of AdColony zone.
 *  @param adColonyCustomID   AdColony custom param.
 *  @param testingDevices     List of testing devices.
 */
void init( std::string interstitialUnitID,
           std::string bottomBannerUnitID,
           BannerSize bottomBannerSize,
           std::string topBannerUnitID,
           BannerSize topBannerSize,
           std::string videoRewardUnitID,
           std::string adColonyAppID,
           std::string adColonyZoneID,
           std::string adColonyCustomID,
           std::vector<std::string>
           testingDevices );

/**
 *  Shows an interstitial ad.
 */
void showInterstitial( std::string adUnitID );

/**
 *  Shows a top banner ad.
 *
 *  @param adUnitID ID of Ad unit to be queried.
 */
void showTopBanner( std::string adUnitID );

/**
 *  Shows a bottom banner ad.
 *
 *  @param adUnitID ID of Ad unit to be queried.
 */
void showBottomBanner( std::string adUnitID );

/**
 *  Shows video reward ad.
 *
 *  @param adUnitID ID of Ad unit to be queried.
 *  @param callback Callback to be called on video reward end. First parameter
 *                  will be true if user should be rewarded.
 */
void showVideoReward( std::string adUnitID, std::function<void( bool )> callback );

/**
 *  Returns whether this user has video rewards available or not.
 *
 *  @native
 *
 *  @return Whether this user has video rewards available or not.
 */
bool videoRewardsAvailable();

/**
 *  Returns whether ads are enabled for this user or not.
 *
 *  @return `true` if this user should see ads.
 */
bool enabled();

}; // namespace ads

}; // namespace LE

#endif /* AdKit_hpp */
