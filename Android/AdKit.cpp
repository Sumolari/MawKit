//
//  AdKit.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "../AdKit.hpp"
#include "Constants.h"

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

/**
 *  ID of Admob's interstitial to show on death.
 */
#define ADMOB_DEATH_INTERSTITIAL_ID "ca-app-pub-3923006847000739/3531587460"

#ifdef COCOS2D_DEBUG

/**
 *  Test devices where ads will be test ads.
 */
#define ADMOB_TEST_DEVICES ""

#else

/**
 *  Test devices where ads will be test ads.
 */
#define ADMOB_TEST_DEVICES ""

#endif

namespace MK {
namespace AdKit {

void _init()
{
	cocos2d::log( "Initialized AdKit for Android." );
}

void _sessionStart()
{
	cocos2d::log( "Called AdKit sessionStart() for Android" );
}

void _sessionEnd()
{
	cocos2d::log( "Called Adkit sessionEnd() for Android" );
}

void _preloadAd( const AdType &type )
{
	cocos2d::log( "Called Adkit preloadAd() for Android" );
}

void _showInterstitial()
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "showInterstitial",
	                                              "()V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}
}

void _showTopBanner()
{
	cocos2d::log( "Called Adkit showTopBanner() for Android" );
}

void _showBottomBanner()
{
	cocos2d::log( "Called Adkit showBottomBanner() for Android" );
}

}; // namespace AdKit
}; // namespace MK

#endif
