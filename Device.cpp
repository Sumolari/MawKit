//
//  Device.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "Device.hpp"

namespace MK {
namespace Device {

const bool isAndroid()
{
	return currentPlatform() == Platform::Android;
}

const bool isiOS()
{
	return currentPlatform() == Platform::iOS;
}

const bool isOSX()
{
	return currentPlatform() == Platform::OSX;
}

}; // namespace Device
}; // namespace MK
