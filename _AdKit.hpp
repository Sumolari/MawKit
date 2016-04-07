//
//  _AdKit.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef _AdKit_hpp
#define _AdKit_hpp

namespace MK {
namespace AdKit {

/**
 *  Performs any initialization required by the ads adapter.
 *
 *  @native
 *
 *  @note Does not take into account whether ads are enabled or not,
 *  @note Do not call this method directly.
 *
 *  @param interstitialUnitID ID of interstitial Ad unit to be queried.
 *  @param videoRewardUnitID  ID of video reward Ad unit to be queried.
 *  @param adColonyAppID      ID of AdColony app to be queried.
 *  @param adColonyZoneID     ID of AdColony zone.
 *  @param adColonyCustomID   AdColony custom param.
 *  @param testingDevices     List of testing devices.
 */
void _init( std::string interstitialUnitID,
            std::string videoRewardUnitID,
            std::string adColonyAppID,
            std::string adColonyZoneID,
            std::string adColonyCustomID,
            std::vector<std::string>
            testingDevices );

/**
 *  Method called when application beings being in foreground.
 *
 *  @native
 *
 *  @note Does not take into account whether ads are enabled or not,
 *  @note Do not call this method directly.
 */
void _sessionStart();

/**
 *  Method called when application begins being in background.
 *
 *  @native
 *
 *  @note Does not take into account whether ads are enabled or not,
 *  @note Do not call this method directly.
 */
void _sessionEnd();

/**
 *  Preloads ads of given type but shows no ad.
 *
 *  @native
 *
 *  @note Does not take into account whether ads are enabled or not,
 *  @note Do not call this method directly.
 *
 *  @param type Type of add to preload.
 */
void _preloadAd( const AdType &type );

/**
 *  Shows an interstitial ad.
 *
 *  @native
 *
 *  @note Does not take into account whether ads are enabled or not,
 *  @note Do not call this method directly.
 *
 *  @param adUnitID ID of Ad unit to be queried.
 */
void _showInterstitial( std::string adUnitID );

/**
 *  Shows a top banner ad.
 *
 *  @native
 *
 *  @note Does not take into account whether ads are enabled or not,
 *  @note Do not call this method directly.
 *
 *  @param adUnitID ID of Ad unit to be queried.
 */
void _showTopBanner( std::string adUnitID );

/**
 *  Shows a bottom banner ad.
 *
 *  @native
 *
 *  @note Does not take into account whether ads are enabled or not,
 *  @note Do not call this method directly.
 *
 *  @param adUnitID ID of Ad unit to be queried.
 */
void _showBottomBanner( std::string adUnitID );

/**
 *  Shows a video reward ad.
 *
 *  @native
 *
 *  @note Does not take into account whether ads are enabled or not,
 *  @note Do not call this method directly.
 *
 *  @param adUnitID ID of Ad unit to be queried.
 *  @param callback Callback to be called on video reward end. First parameter
 *                  will be true if user should be rewarded.
 */
void _showVideoReward( std::string adUnitID, std::function<void( bool )> callback );

}; // namespace AdKit
}; // namespace MK


#endif /* _AdKit_hpp */
