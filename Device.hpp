//
//  Device.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef Device_hpp
#define Device_hpp

#include <string>

#include "cocos2d.h"

namespace MK {

/**
 *  `Device` namespace features method to get information about this device's
 * hardware.
 */
namespace Device {

/// `Platform::Supported` enum represents possible platforms where a MawKit
/// game runs.
enum class Platform { Android = 0, iOS = 1, OSX = 2 };

/**
 *  Returns current platform.
 *
 *  @return Platform currently running this game.
 */
const Platform currentPlatform();

/**
 *  Returns whether this device is running Android or not.
 *
 *  @return `true` is this device is running Android.
 */
const bool isAndroid();

/**
 *  Returns whether this device is running iOS or not.
 *
 *  @return `true` is this device is running iOS.
 */
const bool isiOS();

/**
 *  Returns whether this device is running OS X or not.
 *
 *  @return `true` is this device is running OS X.
 */
const bool isOSX();

/**
 *  Returns whether this device has powerful hardware or not.
 *
 *  @return `true` if this device's hardware can run Hop Raider at 60 fps.
 */
const bool hasPowerfulHardware();

/**
 *  Returns UUID of this device.
 *
 *  @note Current implementation of this method returns a fixed string.
 *
 *  @native
 *
 *  @return UUID of this device.
 */
const std::string UUID();

/**
 *  Retuns this device's screen size, in points.
 *
 *  @native
 *
 *  @return Size of this device's screen in points.
 */
const cocos2d::Size screenSize();

/**
 *  Retuns this device's screen size, in pixel.
 *
 *  @native
 *
 *  @return Size of this device's screen in pixels.
 */
const cocos2d::Size pxScreenSize();

/**
 *  Returns whether internet is currently available or not.
 *
 *  @return `true` if internet is currently reachable.
 */
const bool isInternetAvailable();

/**
 *  Returns whether internet is currently reachable via Wifi or not.
 *
 *  @return `true` if this device is connected to the internet through Wifi.
 */
const bool isUsingWifi();

/**
 *  Returns whether internet is currently reachable via cellular data or not.
 *
 *  @return `true` if this device is connected to the internet through cellular
 *          data.
 */
const bool isUsingCellularData();

}; // namespace Device

}; // namespace MK

#endif /* Device_hpp */
