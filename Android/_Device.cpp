//
//  _Device.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#if CC_PLATFORM == CC_PLATFORM_ANDROID

#include "../Device.hpp"
#include "Constants.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

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
	return cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
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

const std::string language()
{
	cocos2d::JniMethodInfo t;
	std::string lang = "en";
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "getLanguage",
	                                              "()Ljava/lang/String;" ) ) {
		jstring returnString =
		(jstring)t.env->CallStaticObjectMethod( t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );

		lang = t.env->GetStringUTFChars( returnString, NULL );
		if ( lang.length() > 2 ) {
			lang = lang.substr( 0, 2 );
		}
	}

	return lang;
}

}; // namespace Device;
}; // namespace MK

#endif
