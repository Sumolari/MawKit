//
//  Device.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../Device.hpp"

#include <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import <IOKit/IOKitLib.h>

#include "../../Log.hpp"
#include "../Common/CPPUtils.h"

// Returns a NSData object, containing the computer's GUID.
NSData *copy_mac_address( void );

NSData *copy_mac_address( void )
{
	kern_return_t kernResult;
	mach_port_t master_port;
	CFMutableDictionaryRef matchingDict;
	io_iterator_t iterator;
	io_object_t service;
	CFDataRef macAddress = nil;

	kernResult = IOMasterPort( MACH_PORT_NULL, &master_port );
	if ( kernResult != KERN_SUCCESS ) {
		MK::Log::warning( "IOMasterPort returned %d", kernResult );
		return nil;
	}

	matchingDict = IOBSDNameMatching( master_port, 0, "en0" );
	if ( !matchingDict ) {
		MK::Log::warning( "IOBSDNameMatching returned empty dictionary" );
		return nil;
	}

	kernResult = IOServiceGetMatchingServices( master_port, matchingDict, &iterator );
	if ( kernResult != KERN_SUCCESS ) {
		MK::Log::warning( "IOServiceGetMatchingServices returned %d", kernResult );
		return nil;
	}

	while ( ( service = IOIteratorNext( iterator ) ) != 0 ) {
		io_object_t parentService;

		kernResult =
		IORegistryEntryGetParentEntry( service, kIOServicePlane, &parentService );
		if ( kernResult == KERN_SUCCESS ) {
			if ( macAddress ) CFRelease( macAddress );

			macAddress =
			(CFDataRef)IORegistryEntryCreateCFProperty( parentService, CFSTR( "IOMACAddress" ),
			                                            kCFAllocatorDefault, 0 );
			IOObjectRelease( parentService );
		}
		else {
			MK::Log::warning( "IORegistryEntryGetParentEntry returned %d", kernResult );
		}

		IOObjectRelease( service );
	}
	IOObjectRelease( iterator );

	return [NSData dataWithData:(__bridge NSData *)macAddress];
}


namespace MK {
namespace Device {

const std::string UUID()
{
	return std::string( NSDataToHex( copy_mac_address() ).UTF8String );
}

const Platform currentPlatform()
{
	return Platform::OSX;
}

const cocos2d::Size screenSize()
{
	CGSize size = [NSScreen mainScreen].frame.size;
	return cocos2d::Size( size.width, size.height );
}

const cocos2d::Size pxScreenSize()
{
	return screenSize() * [[NSScreen mainScreen] backingScaleFactor];
}

const bool hasPowerfulHardware()
{
	return true;
}

const bool hasNotch()
{
    // Check if the current Mac has a notch (MacBook Pro 14" and 16" from 2021 onwards)
    NSScreen *mainScreen = [NSScreen mainScreen];
    if (!mainScreen) {
        return false;
    }
    
    NSRect frame = mainScreen.frame;
    NSRect visibleFrame = mainScreen.visibleFrame;
    
    // The notch creates a difference between the full frame and visible frame at the top
    // If there's a significant difference in the top area, it likely indicates a notch
    CGFloat topInset = frame.origin.y + frame.size.height - (visibleFrame.origin.y + visibleFrame.size.height);
    
    // A notch typically creates a top inset of around 10-20 points
    return topInset > 8.0;
}

const bool hasDynamicIsland()
{
    return false;
}

}; // namespace Device
}; // namespace MK
