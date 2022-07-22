//
//  AdKit.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "AdKit.hpp"

#include "cocos2d.h"

#include "Device.hpp"
#include "Features.hpp"
#include "KVDatabase.hpp"
#include "Range.hpp"

namespace MK {
namespace AdKit {

void init( __attribute__((unused)) std::string interstitialUnitID,
           __attribute__((unused)) std::string bottomBannerUnitID,
           __attribute__((unused)) BannerSize bottomBannerSize,
           __attribute__((unused)) std::string topBannerUnitID,
           __attribute__((unused)) BannerSize topBannerSize,
           __attribute__((unused)) std::string videoRewardUnitID,
           __attribute__((unused)) std::string adColonyAppID,
           __attribute__((unused)) std::string adColonyZoneID,
           __attribute__((unused)) std::string adColonyCustomID,
           __attribute__((unused)) std::vector<std::string> testingDevices )
{
	if ( !enabled() ) return;

}

void showInterstitial( __attribute__((unused)) std::string adUnitID )
{
	if ( !enabled() ) return;
}

void showTopBanner( __attribute__((unused)) std::string adUnitID )
{
	if ( !enabled() ) return;
}

void showBottomBanner( __attribute__((unused)) std::string adUnitID )
{
	if ( !enabled() ) return;
}

void showVideoReward( __attribute__((unused)) std::string adUnitID,
                      __attribute__((unused)) std::function<void( bool )> callback )
{
}

bool enabled()
{
	if ( MK::Device::isOSX() ) return false;  // Not enabled on OS X.
	if ( !MK::Features::AdKit ) return false; // Not enabled if AdKit disabled.

	// Not enabled if database tells so.
	return MK::KVDatabase::getLongValueForKey( MK::KVDatabase::Key::ADS_DISABLED ) ==
	       MK::KVDatabase::Default::LONG;
}

}; // namespace AdKit
}; // namespace MK
