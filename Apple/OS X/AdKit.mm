//
//  AdKit.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//


#include "../../AdKit.hpp"
#include "../../_AdKit.hpp"

#include "../../Log.hpp"

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
#pragma unused( interstitialUnitID )
#pragma unused( videoRewardUnitID )
#pragma unused( adColonyAppID )
#pragma unused( adColonyZoneID )
#pragma unused( adColonyCustomID )
#pragma unused( testingDevices )
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::AdKit::_init()" );
}

void _sessionStart()
{
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::AdKit::_sessionStart()" );
}

void _sessionEnd()
{
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::AdKit::_sessionEnd()" );
}

void _preloadAd( const AdType & )
{
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::AdKit::_preloadAd()" );
}

void _showInterstitial( std::string adUnitID )
{
#pragma unused( adUnitID )
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::AdKit::_showInterstitial()" );
}

void _showTopBanner( std::string adUnitID )
{
#pragma unused( adUnitID )
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::AdKit::_showTopBanner()" );
}

void _showBottomBanner( std::string adUnitID )
{
#pragma unused( adUnitID )
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::AdKit::_showBottomBanner()" );
}

void _showVideoReward( std::string adUnitID, std::function<void( bool )> callback )
{
#pragma unused( adUnitID )
#pragma unused( callback )
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::AdKit::_showVideoReward()" );
}

bool videoRewardsAvailable()
{
	return false;
}

}; // namespace AdKit
}; // namespace MK
