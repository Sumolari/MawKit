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

/**
 *  `AdKit::Interstitial` namespace features constants used to decide when to
 *  show an interstitial ad.
 */
namespace Interstitial {

/**
 *  Whether insterstitial ads are disabled (`true`) or not.
 */
constexpr bool DISABLE = false;

}; // namespace Interstitial

/**
 *  `AdKit::TopBanner` namespace features constants used to decide when to show
 *  a top banner ad.
 */
namespace TopBanner {

/**
 *  Whether top banner is disabled (`true`) or not.
 */
constexpr bool DISABLE = true;

}; // namespace TopBanner

/**
 *  `AdKit::BottomBanner` namespace features constants used to decide when to
 *  show a bottom banner ad.
 */
namespace BottomBanner {

/**
 *  Whether top banner is disabled (`true`) or not.
 */
constexpr bool DISABLE = true;

}; // namespace BottomBanner

/// Type of ads that can be displayed in the game.
enum class AdType {
	/**
     *  Interstitial, blocking, modal, ads. Include video ads.
     */
	Interstitial = 0,
	/**
     *  Banner displayed on the top of the screen.
     */
	TopBanner = 1,
	/**
     *  Banner displayed on the bottom of the screen.
     */
	BottomBanner = 2,
	/**
     *  Video reward.
     */
	VideoReward = 3
};

/**
 *  Performs any initialization required by the ads adapter.
 *
 *  @param interstitialUnitID ID of interstitial Ad unit to be queried.
 *  @param videoRewardUnitID  ID of video reward Ad unit to be queried.
 *  @param adColonyAppID      ID of AdColony app to be queried.
 *  @param adColonyZoneID     ID of AdColony zone.
 *  @param adColonyCustomID   AdColony custom param.
 *  @param testingDevices     List of testing devices.
 */
void init( std::string interstitialUnitID,
           std::string videoRewardUnitID,
           std::string adColonyAppID,
           std::string adColonyZoneID,
           std::string adColonyCustomID,
           std::vector<std::string>
           testingDevices );

/**
 *  Method called when application beings being in foreground.
 */
void sessionStart();

/**
 *  Method called when application begins being in background.
 */
void sessionEnd();

/**
 *  Preloads ads of given type but shows no ad.
 *
 *  @param type Type of add to preload.
 */
void preloadAd( const AdType &type );

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
