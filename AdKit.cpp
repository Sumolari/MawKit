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
           testingDevices )
{
	if ( !enabled() ) return;

}

void showInterstitial( std::string adUnitID )
{
	if ( !enabled() ) return;
}

void showTopBanner( std::string adUnitID )
{
	if ( !enabled() ) return;
}

void showBottomBanner( std::string adUnitID )
{
	if ( !enabled() ) return;
}

void showVideoReward( std::string adUnitID, std::function<void( bool )> callback )
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
