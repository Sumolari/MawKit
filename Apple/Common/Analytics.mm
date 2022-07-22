//
//  Fabric.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../Analytics.hpp"
#include "../../_Analytics.hpp"

#include "cocos2d.h"

#include "CPPUtils.h"

namespace MK {
namespace Analytics {

void _logEvent( __attribute__((unused)) const std::string &event )
{
	
}

void _logEvent( __attribute__((unused)) const std::string &event,
                __attribute__((unused)) const std::map<std::string, std::string> &attr )
{
	
}

void _logEvent( __attribute__((unused)) const std::string &event,
                __attribute__((unused)) const std::map<std::string, double> &attr )
{
	
}

void _logLevelStart( __attribute__((unused)) const std::string &levelName,
                     __attribute__((unused)) const std::map<std::string, std::string> &attributes )
{

}

void _logLevelStart( __attribute__((unused)) const std::string &levelName,
                     __attribute__((unused)) const std::map<std::string, double> &attributes )
{
}

void _logLevelEnd( __attribute__((unused)) const std::string &levelName,
                   __attribute__((unused)) const long long score,
                   __attribute__((unused)) const bool succeeded,
                   __attribute__((unused)) const std::map<std::string, std::string> &attr )
{

}

void _logLevelEnd( __attribute__((unused)) const std::string &levelName,
                   __attribute__((unused)) const long long score,
                   __attribute__((unused)) const bool succeeded,
                   __attribute__((unused)) const std::map<std::string, double> &attr )
{

}

}; // namespace Analytics
}; // namespace MK
