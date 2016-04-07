//
//  Facebook.cpp
//  LatinExplorer
//
//  Created by Victor Grau Moreso on 25/02/16.
//
//

#if CC_PLATFORM == CC_PLATFORM_ANDROID

#include "../KVDatabase.hpp"
#include "cocos2d.h"

namespace MK {
namespace KVDatabase {

const std::string setStringValueForKey( const std::string &key, const std::string &value )
{
	// cocos2d::log("Called KVDatabase setStringValueForKey() for Android");
	std::string prevValue =
	cocos2d::UserDefault::getInstance()->getStringForKey( key.c_str(), "" );

	cocos2d::UserDefault::getInstance()->setStringForKey( key.c_str(), value );
	cocos2d::UserDefault::getInstance()->flush();

	return prevValue;
}

// WARNING precision loss
const long long setLongValueForKey( const std::string &key, const long long value )
{
	// cocos2d::log("Called KVDatabase setLongValueForKey() for Android");
	long long prevValue =
	cocos2d::UserDefault::getInstance()->getIntegerForKey( key.c_str(), 0 );

	cocos2d::UserDefault::getInstance()->setIntegerForKey( key.c_str(), value );
	cocos2d::UserDefault::getInstance()->flush();

	return prevValue;
}

const std::string getStringValueForKey( const std::string &key )
{
	// cocos2d::log("Called KVDatabase getStringValueForKey() for Android");
	return cocos2d::UserDefault::getInstance()->getStringForKey( key.c_str(), "" );
}

// WARNING precision loss
const long long getLongValueForKey( const std::string &key )
{
	// cocos2d::log("Called KVDatabase getLongValueForKey() for Android");
	return cocos2d::UserDefault::getInstance()->getIntegerForKey( key.c_str(), 0 );
}

const std::vector<std::string> storedKeys()
{
	// cocos2d::log("Called KVDatabase storedKeys() for Android");
	return std::vector<std::string>();
}

}; // namespace KVDatabase
}; // namespace MK

#endif
