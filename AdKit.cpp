//
//  AdKit.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "AdKit.hpp"
#include "_AdKit.hpp"

#include "cocos2d.h"

#include "Device.hpp"
#include "Features.hpp"
#include "KVDatabase.hpp"
#include "Range.hpp"

namespace MK {
namespace AdKit {

void init( std::string interstitialUnitID,
           std::string videoRewardUnitID,
           std::string adColonyAppID,
           std::string adColonyZoneID,
           std::string adColonyCustomID,
           std::vector<std::string>
           testingDevices )
{
	if ( !enabled() ) return;

	_init( interstitialUnitID, videoRewardUnitID, adColonyAppID, adColonyZoneID,
	       adColonyCustomID, testingDevices );
}

void sessionStart()
{
	if ( !enabled() ) return;

	_sessionStart();
}

void sessionEnd()
{
	if ( !enabled() ) return;

	_sessionEnd();
}

void preloadAd( const AdType &type )
{
	if ( !enabled() ) return;

	switch ( type ) {
	case AdType::Interstitial:
		if ( Interstitial::DISABLE ) return;
		break;
	case AdType::TopBanner:
		if ( TopBanner::DISABLE ) return;
		break;
	case AdType::BottomBanner:
		if ( BottomBanner::DISABLE ) return;
		break;
	case AdType::VideoReward:
		if ( !videoRewardsAvailable() ) return;
		break;
	}

	_preloadAd( type );
}

void showInterstitial( std::string adUnitID )
{
	if ( !enabled() ) return;

	_showInterstitial( adUnitID );
}

void showTopBanner( std::string adUnitID )
{
	if ( !enabled() ) return;

	_showTopBanner( adUnitID );
}

void showBottomBanner( std::string adUnitID )
{
	if ( !enabled() ) return;

	_showBottomBanner( adUnitID );
}

void showVideoReward( std::string adUnitID, std::function<void( bool )> callback )
{
	if ( !videoRewardsAvailable() ) {
		callback( false );
		return;
	}

	_showVideoReward( adUnitID, callback );
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
