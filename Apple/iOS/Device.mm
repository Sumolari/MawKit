//
//  Device.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../Device.hpp"

#include <Foundation/Foundation.h>
#include <OpenGLES/EAGL.h>
#include <UIKit/UIKit.h>

#include "../Common/CPPUtils.h"

namespace MK {
namespace Device {

const std::string UUID()
{
	UIDevice *device   = [UIDevice currentDevice];
	NSUUID *identifier = [device identifierForVendor];
	uuid_t uuid;
	[identifier getUUIDBytes:uuid];
	NSData *guidData = [NSData dataWithBytes:(const void *)uuid length:16];

	return std::string( NSDataToHex( guidData ).UTF8String );
}

const Platform currentPlatform()
{
	return Platform::iOS;
}

const cocos2d::Size screenSize()
{
	CGSize size = [UIScreen mainScreen].bounds.size;
	return cocos2d::Size( size.width, size.height );
}

const cocos2d::Size pxScreenSize()
{
	return screenSize() * [UIScreen mainScreen].scale;
}

const bool hasPowerfulHardware()
{
	// iPhones with metal are powerful.
	// iPads with retina display are powerful.
	switch ( [UIDevice currentDevice].userInterfaceIdiom ) {
	case UIUserInterfaceIdiomPhone:
		int max;
		glGetIntegerv( GL_MAX_TEXTURE_SIZE, &max );
		return ( max >= 4096 ); // Apple Ax GPU.
	case UIUserInterfaceIdiomPad:
		return ( [[UIScreen mainScreen] respondsToSelector:@selector( scale )] == YES &&
		         [[UIScreen mainScreen] scale] >= 2 );
	case UIUserInterfaceIdiomTV:
	case UIUserInterfaceIdiomUnspecified:
    case UIUserInterfaceIdiomCarPlay:
		return false;
	}
}


}; // namespace Device
}; // namespace MK
