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

void _logEvent( const std::string &event )
{
	
}

void _logEvent( const std::string &event, const std::map<std::string, std::string> &attr )
{
	
}

void _logEvent( const std::string &event, const std::map<std::string, double> &attr )
{
	
}

void _logLevelStart( const std::string &levelName,
                     const std::map<std::string, std::string> &attributes )
{

}

void _logLevelStart( const std::string &levelName,
                     const std::map<std::string, double> &attributes )
{
}

void _logLevelEnd( const std::string &levelName,
                   const long long score,
                   const bool succeeded,
                   const std::map<std::string, std::string> &attr )
{

}

void _logLevelEnd( const std::string &levelName,
                   const long long score,
                   const bool succeeded,
                   const std::map<std::string, double> &attr )
{

}

}; // namespace Analytics
}; // namespace MK
