//
//  _Device.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#if CC_PLATFORM == CC_PLATFORM_ANDROID

#include "../Device.hpp"
#include "cocos2d.h"

#include <cassert>
#include <string>

namespace MK {
namespace Device {

constexpr float HD = 720 * 1280;

const Platform currentPlatform()
{
	return Platform::Android;
}

const std::string UUID()
{
	return "randomUUID";
}

const cocos2d::Size screenSize()
{
	// Shouldn't be called on Android
	assert( false );
	return cocos2d::Size( 1080, 1920 /*size.width, size.height*/ );
}

const cocos2d::Size pxScreenSize()
{
	return screenSize();
}

const bool hasPowerfulHardware()
{
	// Assume device is powerful if resolution is HD or higher
	cocos2d::Size res = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
	return ( res.width * res.height ) >= HD;
}

}; // namespace Device;
}; // namespace MK

#endif
