//
//  Motion.hpp
//  MawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 14/04/16.
//
//

#ifndef Motion_hpp
#define Motion_hpp

#include "cocos2d.h"

#include <functional>
#include <string>

namespace MK {

/**
 *  `Motion` namespace features methods to query device's accelerometer and
 *  build in motion sensors.
 */
namespace Motion {

/**
 *  Returns current acceleration, provided by built in accelerometer if
 *  available.
 *
 *  If no acceleroemter is available `cocos2d::Vec3::ZERO` will be returned.
 *
 *  @note Will busy-wait for the measurement if not ready yet.
 *
 *  @native
 *
 *  @return Current rotation rate or `cocos2d::Vec3::ZERO`.
 */
const cocos2d::Vec3 getCurrentAcceleration();

/**
 *  Starts acceleroemter and calls given callback as soon as a measurement is
 *  ready.
 *
 *
 *  @native
 *
 *  @param callback Callback to be called when measurement is ready.
 *                  Will receive measurement as first parameter.
 */
void getCurrentAcceleration( std::function<void( cocos2d::Vec3 )> callback );

/**
 *  Starts accelerometer and calls given callback each time a new measurement is
 *  ready.
 *
 *  @note Will remove any previously enqueude callback that uses the same key.
 *
 *  @native
 *
 *
 *  @param callback Callback to be called when measurement is ready.
 *                  Will receive measurement as first parameter.
 *  @param key      Key to be associated with given callback.
 *                  Should be used layer to stop getting new measurements.
 */
void startGettingAccelerationMeasurements( std::function<void( cocos2d::Vec3 )> callback,
                                           const std::string &key = "" );

/**
 *  Stops calling callback associated with given key when new accelerometer
 *  measurements are available. If there is no additional callback enqueued to
 *  accelerometer's updates, it will stop the gyroscope.
 *
 *  Calling this with a not-registered key will do nothing.
 *
 *  @native
 *
 *
 *  @param key Key of callback to be removed from accelerometer updates queue.
 */
void stopGettingAccelerationMeasurements( const std::string &key = "" );

/**
 *  Returns current rotation rate, provided by built in gyroscope if available.
 *
 *  If no gyroscope is available `cocos2d::Vec3::ZERO` will be returned.
 *
 *  @note Will busy-wait for the measurement if not ready yet.
 *
 *  @native
 *
 *
 *  @return Current rotation rate or `cocos2d::Vec3::ZERO`.
 */
const cocos2d::Vec3 getCurrentRotationRate();

/**
 *  Starts gyroscope and calls given callback as soon as a measurement is ready.
 *
 *  @native
 *
 *
 *  @param callback Callback to be called when measurement is ready.
 *                  Will receive measurement as first parameter.
 */
void getCurrentRotationRate( std::function<void( cocos2d::Vec3 )> callback );

/**
 *  Starts gyroscope and calls given callback each time a new measurement is
 *  ready.
 *
 *  @note Will remove any previously enqueude callback that uses the same key.
 *
 *  @native
 *
 *
 *  @param callback Callback to be called when measurement is ready.
 *                  Will receive measurement as first parameter.
 *  @param key      Key to be associated with given callback.
 *                  Should be used layer to stop getting new measurements.
 */
void startGettingRotationRateMeasurements( std::function<void( cocos2d::Vec3 )> callback,
                                           const std::string &key = "" );

/**
 *  Stops calling callback associated with given key when new gyroscope
 *  measurements are available. If there is no additional callback enqueued to
 *  gyroscope's updates, it will stop the gyroscope.
 *
 *  Calling this with a not-registered key will do nothing.
 *
 *  @native
 *
 *
 *  @param key Key of callback to be removed from gyroscope updates queue.
 */
void stopGettingRotationRateMeasurements( const std::string &key = "" );

}; // namespace Motion

}; // namespace MK

#endif /* Motion_hpp */
