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
#include <sys/utsname.h>

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
#if TARGET_OS_MACCATALYST
	return Platform::OSX;
#else
    if (@available(iOS 14.0, *)) {
        if ([NSProcessInfo processInfo].isiOSAppOnMac) {
            return Platform::OSX;
        }
    }
	
	return Platform::iOS;
#endif
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
    case UIUserInterfaceIdiomMac:
        return true;
    }
}

static NSString* getDeviceIdentifier()
{
    struct utsname systemInfo;
    uname(&systemInfo);
    NSString *deviceIdentifier = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    return deviceIdentifier;
}

static bool hasNotchByDeviceIdentifier(NSString *deviceIdentifier)
{
    // iPhone X and later (except iPhone SE models)
    NSArray *notchedDevices = @[
        // iPhone X series
        @"iPhone10,3", @"iPhone10,6",  // iPhone X
        @"iPhone11,2", @"iPhone11,4", @"iPhone11,6", @"iPhone11,8",  // iPhone XS, XS Max, XR
        // iPhone 11 series
        @"iPhone12,1", @"iPhone12,3", @"iPhone12,5",  // iPhone 11, 11 Pro, 11 Pro Max
        // iPhone 12 series
        @"iPhone13,1", @"iPhone13,2", @"iPhone13,3", @"iPhone13,4",  // iPhone 12 mini, 12, 12 Pro, 12 Pro Max
        // iPhone 13 series
        @"iPhone14,2", @"iPhone14,3", @"iPhone14,4", @"iPhone14,5",  // iPhone 13, 13 Pro, 13 mini, 13 Pro Max
        // iPhone 14 series
        @"iPhone14,6", @"iPhone14,7", @"iPhone14,8",  // iPhone 14, 14 Plus, 14 Pro
        @"iPhone15,2", @"iPhone15,3", @"iPhone15,4", @"iPhone15,5",  // iPhone 14 Pro Max, 15, 15 Plus, 15 Pro
        @"iPhone16,1", @"iPhone16,2",  // iPhone 15 Pro Max, 16
        // iPhone 16 series (future devices)
        @"iPhone17,1", @"iPhone17,2", @"iPhone17,3", @"iPhone17,4"   // iPhone 16 Plus, 16 Pro, 16 Pro Max
    ];
    
    return [notchedDevices containsObject:deviceIdentifier];
}

const bool hasNotch()
{
    if (@available(iOS 11.0, *)) {
        UIWindowScene *windowScene = nil;
        for (UIWindowScene *scene in [UIApplication sharedApplication].connectedScenes) {
            if (scene.activationState == UISceneActivationStateForegroundActive) {
                windowScene = scene;
                break;
            }
        }
        
        // Primary method: Use safe area insets (most reliable)
        if (windowScene) {
            UIWindow *window = windowScene.windows.firstObject;
            if (window) {
                // Devices with notch have a top safe area inset > 20 points
                CGFloat topInset = window.safeAreaInsets.top;
                return topInset > 20.0;
            }
        }
        
        // Fallback method: Use device identifier for precise detection
        NSString *deviceIdentifier = getDeviceIdentifier();
        if (deviceIdentifier) {
            return hasNotchByDeviceIdentifier(deviceIdentifier);
        }
    }
    
    return false;
}

const bool hasDynamicIsland()
{
    if (@available(iOS 16.0, *)) {
        UIWindowScene *windowScene = nil;
        for (UIWindowScene *scene in [UIApplication sharedApplication].connectedScenes) {
            if (scene.activationState == UISceneActivationStateForegroundActive) {
                windowScene = scene;
                break;
            }
        }
        
        if (windowScene) {
            UIWindow *window = windowScene.windows.firstObject;
            if (window) {
                // Devices with Dynamic Island have a top safe area inset around 59 points
                CGFloat topInset = window.safeAreaInsets.top;
                return topInset >= 59.0;
            }
        }
    }
    
    return false;
}

}; // namespace Device
}; // namespace MK
