//
//  AdKit.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../AdKit.hpp"

#include <UIKit/UIKit.h>

#include "../../Analytics.hpp"
#include "../../Device.hpp"
#include "../../Log.hpp"
#include "../Common/CPPUtils.h"

//------------------------------------------------------------------------------
// Storage of active delegates and ads.
//------------------------------------------------------------------------------

NSMutableDictionary<NSString *, id> *delegates;

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
	
}

void _showInterstitial( std::string adUnitID )
{
	
}

void _showVideoReward( std::string adUnitID, std::function<void( bool )> callback )
{
	
}

bool videoRewardsAvailable()
{
    return false;
}

void _showTopBanner( std::string adUnitID )
{
	
}

void _showBottomBanner( std::string adUnitID )
{
}

}; // namespace AdKit
}; // namespace MK
