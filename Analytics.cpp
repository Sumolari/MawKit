//
//  Fabric.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "Analytics.hpp"
#include "_Analytics.hpp"

#include "cocos2d.h"

#include "Features.hpp"
#include "Random.hpp"

namespace MK {
namespace Analytics {

/**
 *  Logs frames per second.
 *
 *  @param isIntensive Whether this log is due to intensive performance
 *                     information report or a regular performance information
 *                     report. Defaults to false.
 */
void logPerformance( const bool isIntensive );

void logEvent( const std::string &event )
{
	if ( !enabled() ) return;

	_logEvent( event );
}

void logEvent( const std::string &event, const std::map<std::string, std::string> &attr )
{
	if ( !enabled() ) return;

	_logEvent( event, attr );
}

void logEvent( const std::string &event, const std::map<std::string, double> &attr )
{
	if ( !enabled() ) return;

	_logEvent( event, attr );
}

void logLevelStart( const std::string &levelName )
{
	std::map<std::string, double> emptyMap;
	logLevelStart( levelName, emptyMap );
}

void logLevelStart( const std::string &levelName,
                    const std::map<std::string, std::string> &attributes )
{
	if ( !enabled() ) return;

	_logLevelStart( levelName, attributes );
}

void logLevelStart( const std::string &levelName, const std::map<std::string, double> &attributes )
{
	if ( !enabled() ) return;

	_logLevelStart( levelName, attributes );
}

void logLevelEnd( const std::string &levelName,
                  const long long score,
                  const bool succeeded,
                  const std::map<std::string, std::string> &attr )
{
	if ( !enabled() ) return;

	_logLevelEnd( levelName, score, succeeded, attr );
}

void logLevelEnd( const std::string &levelName,
                  const long long score,
                  const bool succeeded,
                  const std::map<std::string, double> &attr )
{
	if ( !enabled() ) return;

	_logLevelEnd( levelName, score, succeeded, attr );
}

void logNonReadyVideoRewardDisplay()
{
	logEvent( "Non ready video reward shown" );
}

const bool enabled()
{
	return Features::Analytics;
}

}; // namespace Analytics
}; // namespace MK
