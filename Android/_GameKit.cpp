//
//  _GameKit.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#if CC_PLATFORM == CC_PLATFORM_ANDROID

#include "../_GameKit.hpp"
#include "Constants.h"

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#include <functional>

#include "../Log.hpp"

namespace MK {

namespace GameKit {

std::map<int, std::vector<VoidLongLongBoolCB>> scoreCallbacks;
std::map<int, std::vector<std::function<void( float, bool )>>> achievementCallbacks;

void _init()
{
}

void _requestScore( int leaderboardID, VoidLongLongBoolCB callback )
{
	if ( isAvailable() ) {
		cocos2d::JniMethodInfo t;
		if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "requestScoreFromLeaderboard",
		                                              "(I)V" ) ) {
			t.env->CallStaticVoidMethod( t.classID, t.methodID, leaderboardID );

			scoreCallbacks[leaderboardID].push_back( callback );
		}
		else {
			callback( 0, false );
		}
	}
	else {
		callback( 0, false );
	}
}

void _submitScore( long long score, int leaderboardID )
{
	if ( isAvailable() ) {
		cocos2d::JniMethodInfo t;
		if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "submitScoreToLeaderboard",
		                                              "(II)V" ) ) {
			t.env->CallStaticVoidMethod( t.classID, t.methodID, score, leaderboardID );
		}
	}
}

void _showLeaderboard( const int leaderbaordID )
{
	if ( isAvailable() ) {
		cocos2d::JniMethodInfo t;
		if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "openLeaderboardUI",
		                                              "(I)V" ) ) {
			t.env->CallStaticVoidMethod( t.classID, t.methodID, leaderbaordID );
		}
	}
	else {
		// cocos2d::log( "Log in before opening leaderboard" );
		// Attempt GPG login
		cocos2d::JniMethodInfo t;
		if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "attemptGPGLogin",
		                                              "()V" ) ) {
			t.env->CallStaticVoidMethod( t.classID, t.methodID );
		}
	}
}

void _requestAchievement( const int achievementID, std::function<void( float, bool )> callback )
{
	if ( isAvailable() ) {
		cocos2d::JniMethodInfo t;
		if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "requestAchievement",
		                                              "(I)V" ) ) {
			t.env->CallStaticVoidMethod( t.classID, t.methodID, achievementID );

			achievementCallbacks[achievementID].push_back( callback );
		}
		else {
			callback( 0.0f, false );
		}
	}
	else {
		callback( 0.0f, false );
	}
}

void _reportAchievementProgress( int aID, float progress )
{
	if ( isAvailable() ) {
		cocos2d::JniMethodInfo t;
		if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "updateAchievement",
		                                              "(II)V" ) ) {
			t.env->CallStaticVoidMethod( t.classID, t.methodID, aID,
			                             static_cast<int>( progress * 100 ) );
		}
	}
}

void showAchievementsList()
{
	if ( isAvailable() ) {
		cocos2d::JniMethodInfo t;
		if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "showAchievements",
		                                              "()V" ) ) {
			t.env->CallStaticVoidMethod( t.classID, t.methodID );
		}
	}
	else {
		// cocos2d::log( "Log in before opening achievements" );
		// Attempt GPG login
		cocos2d::JniMethodInfo t;
		if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "attemptGPGLogin",
		                                              "()V" ) ) {
			t.env->CallStaticVoidMethod( t.classID, t.methodID );
		}
	}
}

const bool _signInPlayer()
{
	MK::Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_ANDROID,
	                           "MK::GameKit::_signInPlayer()" );
	return false;
}

void exitGame()
{
	cocos2d::JniMethodInfo t;
	// TODO fix this aberration
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY,
	                                              "exitGame", "()V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID );
	}

	// Director::getInstance()->end();
}

const bool isAvailable()
{
	bool tmp = false;

	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY,
	                                              "isGPGSupported", "()Z" ) ) {
		tmp = t.env->CallStaticBooleanMethod( t.classID, t.methodID );
	}

	return tmp;
}

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppScoreCallback(
JNIEnv *env, jobject thiz, jint id, jint score, jboolean success );
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppScoreCallback(
JNIEnv *env, jobject thiz, jint id, jint score, jboolean success )
{
	int newScore = score;
	MK::Log::debug( "Retrieved score from leaderboard %d: %d", id, newScore );

	for ( auto callback : scoreCallbacks[id] ) {
		callback( newScore, success );
	}

	scoreCallbacks[id].clear();
}

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppAchievementCallback(
JNIEnv *env, jobject thiz, jint id, jfloat progress, jboolean success );
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppAchievementCallback(
JNIEnv *env, jobject thiz, jint id, jfloat progress, jboolean success )
{
	bool isUnlocked = ( progress == 1.0f );
	MK::Log::debug( "Achievement %d unlocked? %s", id, isUnlocked ? "true" : false );

	for ( auto callback : achievementCallbacks[id] ) {
		callback( progress, success );
	}

	achievementCallbacks[id].clear();
}

}; // namespace GameKit

}; // namespace MK

#endif

/* ORIGINAL CODE OF GAME SHARING LEFT AS REFERENCE */

/*
#include <map>

#include "GameSharing.h"

USING_NS_CC;

bool GameSharing::bIsGPGAvailable       = true;
bool GameSharing::wasGPGAvailableCalled = false;
std::function<void()> GameSharing::errorHandler;
bool GameSharing::requestIsBeingProcessed = false;

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
std::map<unsigned long long, std::function<void( int )>> callbacks;
unsigned long long lastRequestID = 0;
#endif

void GameSharing::RequestCurrentScoreFromLeaderboard( int leaderboardID,
std::function<void( int )> callback )
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM ==
CC_PLATFORM_MAC )
    GameSharing::startScoreRequest( leaderboardID, callback );
    requestIsBeingProcessed = true;
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    lastRequestID++;
    // TODO: Pass last request ID to Java.
    cocos2d::JniMethodInfo t;
    if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY,
                                        "requestScoreFromLeaderboard",
                                        "()V" ) ) {
        t.env->CallStaticVoidMethod( t.classID, t.methodID );
    }
    std::function<void( int )> runCallbackAndRemove = [&, callback,
lastRequestID]( int score ) {
        callback( score );
        callbacks.erase( lastRequestID );
    } callbacks[lastRequestID] = runCallbackAndRemove;
    requestIsBeingProcessed    = true;
#endif
}

void GameSharing::SetErrorHandler( std::function<void()> handler )
{
    errorHandler = handler;
}

*/
