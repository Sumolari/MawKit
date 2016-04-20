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
std::map<int, std::vector<std::function<void( std::map<std::string, unsigned long long>, bool )>>> friendScoreCallbacks;

void _init()
{
}

void _requestScore( int leaderboardID, VoidLongLongBoolCB callback )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY,
	                                              "requestScoreFromLeaderboard", "(I)V" ) ) {
		scoreCallbacks[leaderboardID].push_back( callback );

		t.env->CallStaticVoidMethod( t.classID, t.methodID, leaderboardID );
	}
	else {
		callback( 0, false );
	}
}

void _requestFriendsScores( int leaderboardID,
                            std::function<void( std::map<std::string, unsigned long long>, bool )> callback )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "requestFriendScoresFromLeaderboard",
	                                              "(I)V" ) ) {
		friendScoreCallbacks[leaderboardID].push_back( callback );

		t.env->CallStaticVoidMethod( t.classID, t.methodID, leaderboardID );
	}
	else {
		callback( std::map<std::string, unsigned long long>(), false );
	}
}

void _submitScore( long long score, int leaderboardID )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY,
	                                              "submitScoreToLeaderboard", "(JI)V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID, score, leaderboardID );
	}
}

void _showLeaderboard( const int leaderboardID )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "openLeaderboardUI",
	                                              "(I)V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID, leaderboardID );
	}
}

void _showLeaderboards()
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "openLeaderboardsUI",
	                                              "()V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID );
	}
}

void _requestAchievement( const int achievementID, std::function<void( float, bool )> callback )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "requestAchievement",
	                                              "(I)V" ) ) {
		achievementCallbacks[achievementID].push_back( callback );

		t.env->CallStaticVoidMethod( t.classID, t.methodID, achievementID );
	}
	else {
		callback( 0.0f, false );
	}
}

void _reportAchievementProgress( int aID, float progress )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "updateAchievement",
	                                              "(II)V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID, aID,
		                             static_cast<int>( progress * 100 ) );
	}
}

void showAchievementsList()
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "showAchievements",
	                                              "()V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID );
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
	cocos2d::Director::getInstance()->end();
}

const bool isAvailable()
{
	bool tmp = false;

	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY,
	                                              "isSignedIn", "()Z" ) ) {
		tmp = t.env->CallStaticBooleanMethod( t.classID, t.methodID );
	}

	return tmp;
}

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppScoreCallback(
JNIEnv *env, jobject thiz, jint id, jlong score, jboolean success );
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppScoreCallback(
JNIEnv *env, jobject thiz, jint id, jlong score, jboolean success )
{
	long long newScore = score;
	MK::Log::debug( "Retrieved score from leaderboard %d: %d", id, newScore );

	for ( auto callback : scoreCallbacks[id] ) {
		callback( newScore, success );
	}

	scoreCallbacks[id].clear();
}

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppFriendScoreCallback(
JNIEnv *env, jobject thiz, jint id, jobjectArray names, jlongArray scores, jboolean success );
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppFriendScoreCallback(
JNIEnv *env, jobject thiz, jint id, jobjectArray names, jlongArray scores, jboolean success )
{
	std::map<std::string, unsigned long long> friendScores;
	int namesCount   = env->GetArrayLength( names );
	long long *score = env->GetLongArrayElements( scores, NULL );

	for ( int i = 0; i < namesCount; i++ ) {
		jstring jname    = (jstring)env->GetObjectArrayElement( names, i );
		std::string name = env->GetStringUTFChars( jname, NULL );

		friendScores[name] = static_cast<unsigned long long>( score[i] );
	}

	for ( auto callback : friendScoreCallbacks[id] ) {
		callback( friendScores, success );
	}

	friendScoreCallbacks.clear();
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

namespace ReplayKit {

const bool isAvailable()
{
	return false;
}

void startRecording( bool, std::function<void( bool )> callback )
{
	if ( callback != nullptr ) {
		callback( false );
	}
}

void stopRecording( std::function<void( bool )> callback )
{
	if ( callback != nullptr ) {
		callback( false );
	}
}

void discardRecording( std::function<void( void )> callback )
{
	if ( callback != nullptr ) {
		callback();
	}
}

void showLastRecordedReplayEditor()
{
}

bool hasRecordedReplay()
{
	return false;
}

}; // namespace ReplayKit

}; // namespace GameKit

}; // namespace MK

#endif
