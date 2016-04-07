//
//  _IAPKit.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "../_IAPKit.hpp"
#include "Constants.h"
#include <functional>
#include <vector>

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppPurchasesCallback(
JNIEnv *env, jobject thiz, jobjectArray stringArray );
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCppPurchasesCallback(
JNIEnv *env, jobject thiz, jobjectArray stringArray )
{
	int stringCount = env->GetArrayLength( stringArray );

	for ( int i = 0; i < stringCount; i++ ) {
		jstring string = (jstring)env->GetObjectArrayElement( stringArray, i );
		std::string androidProdID = env->GetStringUTFChars( string, NULL );
		std::transform( androidProdID.begin(), androidProdID.end(),
		                androidProdID.begin(), ::toupper );

		MK::IAPKit::unlockProduct( MK::IAPKit::productLocalIDForProductGlobalID( androidProdID ) );
		// Don't forget to call `ReleaseStringUTFChars` when you're done.
		// env->ReleaseStringUTFChars( string, androidProdID );
	}
}

void MK::IAPKit::_init( const std::vector<MK::IAPKit::ProductID> &products,
                        std::function<void( void )> callback )
{
	cocos2d::log( "Called IAPKit init() for Android" );
}

void MK::IAPKit::_buyIfPossible( const MK::IAPKit::ProductID &productIdentifier,
                                 std::function<void( bool )> callback )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "makePurchase",
	                                              "(Ljava/lang/String;)V" ) ) {

		std::string androidProdID =
		MK::IAPKit::productGlobalIDForProductLocalID( productIdentifier );
		std::transform( androidProdID.begin(), androidProdID.end(),
		                androidProdID.begin(), ::tolower );

		t.env->CallStaticVoidMethod( t.classID, t.methodID,
		                             t.env->NewStringUTF( androidProdID.c_str() ) );
		t.env->DeleteLocalRef( t.classID );
	}

	// Resolved in another callback because java
	callback( false );
}

const std::string MK::IAPKit::_buyButtonTitleForProduct( const MK::IAPKit::ProductID &productIdentifier )
{
	std::string s = "";
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo(
	     t, MK::Android::APP_ACTIVITY, "checkPurchase",
	     "(Ljava/lang/String;)Ljava/lang/String;" ) ) {

		std::string androidProdID =
		MK::IAPKit::productGlobalIDForProductLocalID( productIdentifier );
		std::transform( androidProdID.begin(), androidProdID.end(),
		                androidProdID.begin(), ::tolower );

		jstring returnString = (jstring)t.env->CallStaticObjectMethod(
		t.classID, t.methodID, t.env->NewStringUTF( androidProdID.c_str() ) );
		t.env->DeleteLocalRef( t.classID );

		s = t.env->GetStringUTFChars( returnString, NULL );
	}

	return s;
}

void MK::IAPKit::_restorePurchases( std::function<void( bool )> callback )
{
	cocos2d::JniMethodInfo t;
	if ( cocos2d::JniHelper::getStaticMethodInfo( t, MK::Android::APP_ACTIVITY, "restorePurchases",
	                                              "()V" ) ) {
		t.env->CallStaticVoidMethod( t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}

	// Resolved in another callback because java
	callback( false );
}


#endif
