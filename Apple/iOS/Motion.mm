//
//  Motion.mm
//  MawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 14/04/16.
//
//

#import <CoreMotion/CoreMotion.h>
#import <Foundation/Foundation.h>

#include "../../Log.hpp"
#include "../../Motion.hpp"
#include "../Common/CPPUtils.h"


NSMutableDictionary<NSString *, CMMotionManager *> *gyroscopeManagerForKey;
NSMutableDictionary<NSString *, CMMotionManager *> *accelerometerManagerForKey;

namespace MK {
namespace Motion {

const cocos2d::Vec3 getCurrentAcceleration()
{
	CMMotionManager *manager = [[CMMotionManager alloc] init];

	[manager startAccelerometerUpdates];

	CMAccelerometerData *accelerometerData = nil;
	while ( accelerometerData == nil ) {
		accelerometerData = manager.accelerometerData;
	}

	[manager stopAccelerometerUpdates];

	return cocos2d::Vec3( accelerometerData.acceleration.x,
	                      accelerometerData.acceleration.y,
	                      accelerometerData.acceleration.z );
}

void getCurrentAcceleration( std::function<void( cocos2d::Vec3 )> callback )
{
	CMMotionManager *manager = [[CMMotionManager alloc] init];

	[manager
	startAccelerometerUpdatesToQueue:[NSOperationQueue mainQueue]
	                     withHandler:^( CMAccelerometerData *_Nullable accelerometerData,
	                                    NSError *_Nullable error ) {
		                   if ( accelerometerData != nil && error == nil ) {
			                   callback(
			                   cocos2d::Vec3( accelerometerData.acceleration.x,
			                                  accelerometerData.acceleration.y,
			                                  accelerometerData.acceleration.z ) );
			                   [manager stopGyroUpdates];
		                   }
		                   else if ( error != nil ) {
			                   MK::Log::warning(
			                   "Could not get accelerometer data, error:" );
			                   MK::Log::warning( "%s", [error localizedDescription] );
		                   }
		                   else {
			                   MK::Log::warning( "Could not get accelerometer "
			                                     "data, due to an unknown "
			                                     "error" );
		                   }
		                 }];
}

void startGettingAccelerationMeasurements( std::function<void( cocos2d::Vec3 )> callback,
                                           const std::string &key )
{
	if ( accelerometerManagerForKey == nil ) {
		accelerometerManagerForKey = [NSMutableDictionary dictionary];
	}

	CMMotionManager *manager = [[CMMotionManager alloc] init];

	NSString *ns_key = to_nsstring( key );

	// Remove previously enqueued callbacks.
	if ( accelerometerManagerForKey[ns_key] != nil ) {
		MK::Motion::stopGettingAccelerationMeasurements( key );
	}
	accelerometerManagerForKey[ns_key] = manager;

	[manager
	startAccelerometerUpdatesToQueue:[NSOperationQueue mainQueue]
	                     withHandler:^( CMAccelerometerData *_Nullable accelerometerData,
	                                    NSError *_Nullable error ) {
		                   if ( accelerometerData != nil && error == nil ) {
			                   callback(
			                   cocos2d::Vec3( accelerometerData.acceleration.x,
			                                  accelerometerData.acceleration.y,
			                                  accelerometerData.acceleration.z ) );
		                   }
		                 }];
}


void stopGettingAccelerationMeasurements( const std::string &key )
{
	NSString *ns_key = to_nsstring( key );
	if ( accelerometerManagerForKey[ns_key] == nil ) {
		return; // If not registered do nothing.
	}

	[accelerometerManagerForKey[ns_key] stopAccelerometerUpdates];
	accelerometerManagerForKey[ns_key] = nil;
}


const cocos2d::Vec3 getCurrentRotationRate()
{
	CMMotionManager *manager = [[CMMotionManager alloc] init];

	[manager startGyroUpdates];

	CMGyroData *gyroData = nil;
	while ( gyroData == nil ) {
		gyroData = manager.gyroData;
	}

	[manager stopGyroUpdates];

	return cocos2d::Vec3( gyroData.rotationRate.x, gyroData.rotationRate.y,
	                      gyroData.rotationRate.z );
};

void getCurrentRotationRate( std::function<void( cocos2d::Vec3 )> callback )
{
	CMMotionManager *manager = [[CMMotionManager alloc] init];

	[manager
	startGyroUpdatesToQueue:[NSOperationQueue mainQueue]
	            withHandler:^( CMGyroData *_Nullable gyroData, NSError *_Nullable error ) {
		          if ( gyroData != nil && error == nil ) {
			          callback( cocos2d::Vec3( gyroData.rotationRate.x, gyroData.rotationRate.y,
			                                   gyroData.rotationRate.z ) );
			          [manager stopGyroUpdates];
		          }
		          else if ( error != nil ) {
			          MK::Log::warning(
			          "Could not get gyroscope data, error:" );
			          MK::Log::warning( "%s", [error localizedDescription] );
		          }
		          else {
			          MK::Log::warning(
			          "Could not get gyroscope data, due to an unknown error" );
		          }
		        }];
}

void startGettingRotationRateMeasurements( std::function<void( cocos2d::Vec3 )> callback,
                                           const std::string &key )
{
	if ( gyroscopeManagerForKey == nil ) {
		gyroscopeManagerForKey = [NSMutableDictionary dictionary];
	}

	CMMotionManager *manager = [[CMMotionManager alloc] init];

	NSString *ns_key = to_nsstring( key );

	// Remove previously enqueued callbacks.
	if ( gyroscopeManagerForKey[ns_key] != nil ) {
		MK::Motion::stopGettingRotationRateMeasurements( key );
	}
	gyroscopeManagerForKey[ns_key] = manager;

	[manager
	startGyroUpdatesToQueue:[NSOperationQueue mainQueue]
	            withHandler:^( CMGyroData *_Nullable gyroData, NSError *_Nullable error ) {
		          if ( gyroData != nil && error == nil ) {
			          callback( cocos2d::Vec3( gyroData.rotationRate.x, gyroData.rotationRate.y,
			                                   gyroData.rotationRate.z ) );
		          }
		        }];
}

void stopGettingRotationRateMeasurements( const std::string &key )
{
	NSString *ns_key = to_nsstring( key );
	if ( gyroscopeManagerForKey[ns_key] == nil ) {
		return; // If not registered do nothing.
	}

	[gyroscopeManagerForKey[ns_key] stopGyroUpdates];
	gyroscopeManagerForKey[ns_key] = nil;
}

}; // namespace Motion
}; // namespace MK
