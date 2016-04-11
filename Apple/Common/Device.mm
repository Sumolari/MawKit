//
//  Device.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../Device.hpp"

#import <Foundation/Foundation.h>
#import <Reachability/Reachability.h>

namespace MK {

namespace Device {

const bool isInternetAvailable()
{
	return [[Reachability reachabilityForInternetConnection] isReachable];
}

const bool isUsingWifi()
{
	return [[Reachability reachabilityForInternetConnection] isReachableViaWiFi];
}

const bool isUsingCellularData()
{
	return [[Reachability reachabilityForInternetConnection] isReachableViaWWAN];
}

const std::string language()
{
	return std::string(
	[[NSLocale preferredLanguages][0] substringToIndex:2].lowercaseString.UTF8String );
}

}; // namespace Device

}; // namespace MK
