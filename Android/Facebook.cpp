//
//  Facebook.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#if CC_PLATFORM == CC_PLATFORM_ANDROID

#include "../Facebook.hpp"
#include "cocos2d.h"

namespace MK {
namespace Facebook {

void sendInvitation( const std::string &linkURL, const std::string &thumbnailURL )
{
	cocos2d::log( "Called Facebook sendInvitation() for Android" );
}

}; // namespace Facebook
}; // namespace MK

#endif
