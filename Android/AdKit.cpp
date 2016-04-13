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
#include <vector>

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

std::vector<std::function<void( bool )>> rewardCallbacks;

void _init( std::string interstitialUnitID,
            std::string bottomBannerUnitID,
            BannerSize bottomBannerSize,
            std::string topBannerUnitID,
            BannerSize topBannerSize,
            std::string videoRewardUnitID,
            std::string adColonyAppID,
            std::string adColonyZoneID,
            std::string adColonyCustomID,
            std::vector<std::string> testingDevices )
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

void _showInterstitial( std::string adUnitID )
{
	cocos2d::log( "Called AdKit showInterstitial() for Android" );
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "showInterstitial",
	                                              "()V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}
}

void _showTopBanner( std::string adUnitID )
{
	cocos2d::log( "Called Adkit showTopBanner() for Android" );
}

void _showBottomBanner( std::string adUnitID )
{
	cocos2d::log( "Called Adkit showBottomBanner() for Android" );
}

void _showVideoReward( std::string adUnitID, std::function<void( bool )> callback )
{
	cocos2d::log( "Called Adkit showVideoReward() for Android" );
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY,
	                                              "showRewarded", "()V" ) ) {
		rewardCallbacks.push_back( callback );

		t.env->CallStaticVoidMethod( t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}
}

bool videoRewardsAvailable()
{
	cocos2d::log( "Called Adkit videoRewardsAvailable() for Android" );
	if ( !MK::AdKit::enabled() ) return false;

	bool isAvailable = false;

	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "rewardedAvailable",
	                                              "()Z" ) ) {
		isAvailable = t.env->CallStaticBooleanMethod( t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}

	return isAvailable;
}

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppRewardCallback(
JNIEnv *env, jobject thiz, jboolean success );
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppRewardCallback(
JNIEnv *env, jobject thiz, jboolean success )
{
	if ( rewardCallbacks.size() > 0 ) {
		rewardCallbacks[0]( success );
		rewardCallbacks.erase( rewardCallbacks.begin() );
	}
}

}; // namespace AdKit
}; // namespace MK

#endif
