//
//  Fabric.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "../Analytics.hpp"
#include "Constants.h"

#include <map>
#include <string>

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

namespace MK {
namespace Analytics {

void _logEvent( const std::string &event )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "logEvent",
	                                              "(Ljava/lang/String;)V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID,
		                             t.env->NewStringUTF( event.c_str() ) );
		t.env->DeleteLocalRef( t.classID );
	}
}

void _logEvent( const std::string &event, const std::map<std::string, std::string> &attr )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo(
	     t, MK::Android::APP_ACTIVITY, "logEvent",
	     "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)V" ) ) {
		jobjectArray keysArray =
		t.env->NewObjectArray( attr.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		jobjectArray valuesArray =
		t.env->NewObjectArray( attr.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		int i = 0;
		for ( auto it = attr.begin(); it != attr.end(); ++it, ++i ) {
			t.env->SetObjectArrayElement( keysArray, i,
			                              t.env->NewStringUTF( it->first.c_str() ) );
			t.env->SetObjectArrayElement( valuesArray, i,
			                              t.env->NewStringUTF( it->second.c_str() ) );
		}

		t.env->CallStaticVoidMethod( t.classID, t.methodID,
		                             t.env->NewStringUTF( event.c_str() ),
		                             keysArray, valuesArray );
		t.env->DeleteLocalRef( t.classID );
	}
}

void _logEvent( const std::string &event, const std::map<std::string, double> &attr )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo(
	     t, MK::Android::APP_ACTIVITY, "logEvent",
	     "(Ljava/lang/String;[Ljava/lang/String;[D)V" ) ) {
		jobjectArray keysArray =
		t.env->NewObjectArray( attr.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		jdoubleArray valuesArray = t.env->NewDoubleArray( attr.size() );

		int i = 0;
		for ( auto it = attr.begin(); it != attr.end(); ++it, ++i ) {
			t.env->SetObjectArrayElement( keysArray, i,
			                              t.env->NewStringUTF( it->first.c_str() ) );
			t.env->SetDoubleArrayRegion( valuesArray, i, 1, &( it->second ) );
		}

		t.env->CallStaticVoidMethod( t.classID, t.methodID,
		                             t.env->NewStringUTF( event.c_str() ),
		                             keysArray, valuesArray );
		t.env->DeleteLocalRef( t.classID );
	}
}

void _logLevelStart( const std::string &levelName,
                     const std::map<std::string, std::string> &attributes )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo(
	     t, MK::Android::APP_ACTIVITY, "logLevelStart",
	     "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)V" ) ) {
		jobjectArray keysArray =
		t.env->NewObjectArray( attributes.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		jobjectArray valuesArray =
		t.env->NewObjectArray( attributes.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		int i = 0;
		for ( auto it = attributes.begin(); it != attributes.end(); ++it, ++i ) {
			t.env->SetObjectArrayElement( keysArray, i,
			                              t.env->NewStringUTF( it->first.c_str() ) );
			t.env->SetObjectArrayElement( valuesArray, i,
			                              t.env->NewStringUTF( it->second.c_str() ) );
		}

		t.env->CallStaticVoidMethod( t.classID, t.methodID,
		                             t.env->NewStringUTF( levelName.c_str() ),
		                             keysArray, valuesArray );
		t.env->DeleteLocalRef( t.classID );
	}
}

void _logLevelStart( const std::string &levelName,
                     const std::map<std::string, double> &attributes )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo(
	     t, MK::Android::APP_ACTIVITY, "logLevelStart",
	     "(Ljava/lang/String;[Ljava/lang/String;[D)V" ) ) {
		jobjectArray keysArray =
		t.env->NewObjectArray( attributes.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		jdoubleArray valuesArray = t.env->NewDoubleArray( attributes.size() );

		int i = 0;
		for ( auto it = attributes.begin(); it != attributes.end(); ++it, ++i ) {
			t.env->SetObjectArrayElement( keysArray, i,
			                              t.env->NewStringUTF( it->first.c_str() ) );
			t.env->SetDoubleArrayRegion( valuesArray, i, 1, &( it->second ) );
		}

		t.env->CallStaticVoidMethod( t.classID, t.methodID,
		                             t.env->NewStringUTF( levelName.c_str() ),
		                             keysArray, valuesArray );
		t.env->DeleteLocalRef( t.classID );
	}
}

void _logLevelEnd( const std::string &levelName,
                   const long long score,
                   const bool succeeded,
                   const std::map<std::string, std::string> &attr )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo(
	     t, MK::Android::APP_ACTIVITY, "logLevelEnd",
	     "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;JZ)V" ) ) {
		jobjectArray keysArray =
		t.env->NewObjectArray( attr.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		jobjectArray valuesArray =
		t.env->NewObjectArray( attr.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		int i = 0;
		for ( auto it = attr.begin(); it != attr.end(); ++it, ++i ) {
			t.env->SetObjectArrayElement( keysArray, i,
			                              t.env->NewStringUTF( it->first.c_str() ) );
			t.env->SetObjectArrayElement( valuesArray, i,
			                              t.env->NewStringUTF( it->second.c_str() ) );
		}

		t.env->CallStaticVoidMethod( t.classID, t.methodID,
		                             t.env->NewStringUTF( levelName.c_str() ),
		                             keysArray, valuesArray, score, succeeded );
		t.env->DeleteLocalRef( t.classID );
	}
}

void _logLevelEnd( const std::string &levelName,
                   const long long score,
                   const bool succeeded,
                   const std::map<std::string, double> &attr )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo(
	     t, MK::Android::APP_ACTIVITY, "logLevelEnd",
	     "(Ljava/lang/String;[Ljava/lang/String;[DJZ)V" ) ) {
		jobjectArray keysArray =
		t.env->NewObjectArray( attr.size(),
		                       t.env->FindClass( "java/lang/String" ),
		                       t.env->NewStringUTF( "" ) );

		jdoubleArray valuesArray = t.env->NewDoubleArray( attr.size() );

		int i = 0;
		for ( auto it = attr.begin(); it != attr.end(); ++it, ++i ) {
			t.env->SetObjectArrayElement( keysArray, i,
			                              t.env->NewStringUTF( it->first.c_str() ) );
			t.env->SetDoubleArrayRegion( valuesArray, i, 1, &( it->second ) );
		}

		t.env->CallStaticVoidMethod( t.classID, t.methodID,
		                             t.env->NewStringUTF( levelName.c_str() ),
		                             keysArray, valuesArray, score, succeeded );
		t.env->DeleteLocalRef( t.classID );
	}
}

}; // namespace Analytics
}; // namespace MK

#endif
