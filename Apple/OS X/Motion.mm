//
//  Motion.mm
//  MawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 14/04/16.
//
//

#import <Foundation/Foundation.h>

#include "../../Motion.hpp"

namespace MK {
namespace Motion {

const cocos2d::Vec3 getCurrentAcceleration()
{
	return cocos2d::Vec3::ZERO;
}

void getCurrentAcceleration( std::function<void( cocos2d::Vec3 )> )
{
}

void startGettingAccelerationMeasurements( std::function<void( cocos2d::Vec3 )>,
                                           const std::string & )
{
}


void stopGettingAccelerationMeasurements( const std::string & )
{
}


const cocos2d::Vec3 getCurrentRotationRate()
{
	return cocos2d::Vec3::ZERO;
};

void getCurrentRotationRate( std::function<void( cocos2d::Vec3 )> )
{
}

void startGettingRotationRateMeasurements( std::function<void( cocos2d::Vec3 )>,
                                           const std::string & )
{
}

void stopGettingRotationRateMeasurements( const std::string & )
{
}

}; // namespace Motion
}; // namespace MK
