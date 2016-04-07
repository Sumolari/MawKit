//
//  _Analytics.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef _Analytics_hpp
#define _Analytics_hpp

#include "Analytics.hpp"

namespace MK {
namespace Analytics {

/**
 *  Logs given event without additional attributes.
 *
 *  @native
 *
 *  @param event Name of the event to log.
 */
void _logEvent( const std::string &event );

/**
 *  Logs given event with given additional attributes.
 *
 *  @native
 *
 *  @param event Name of the event to log.
 *  @param attr  Additional attributes.
 */
void _logEvent( const std::string &event, const std::map<std::string, std::string> &attr );

/**
 *  Logs given event with given additional attributes.
 *
 *  @native
 *
 *  @param event Name of the event to log.
 *  @param attr  Additional attributes.
 */
void _logEvent( const std::string &event, const std::map<std::string, double> &attr );

/**
 *  Logs start of level with given name/identifier and given optional additional
 *  attributes.
 *
 *  @native
 *
 *  @param levelName Name of the started level to log.
 *  @param attr      Additional attributes to log in this event.
 */
void _logLevelStart( const std::string &levelName,
                     const std::map<std::string, std::string> &attr = {} );

/**
 *  Logs start of level with given name/identifier and given optional additional
 *  attributes.
 *
 *  @native
 *
 *  @param levelName Name of the started level to log.
 *  @param attr      Additional attributes to log in this event.
 */
void _logLevelStart( const std::string &levelName,
                     const std::map<std::string, double> &attr = {} );

/**
 *  Logs end of level with given name/identifier, given score, whether user
 *  succeeded or not in the level and given optional additional attributes.
 *
 *  @native
 *
 *  @param levelName Name of the finished level to log.
 *  @param score     Score use achieved in this level.
 *  @param succeeded Whether used suceeded in this level (`true) or not.
 *  @param attr      Additional attributes to log in this event.
 */
void _logLevelEnd( const std::string &levelName,
                   const long long score,
                   const bool succeeded,
                   const std::map<std::string, std::string> &attr = {} );

/**
 *  Logs end of level with given name/identifier, given score, whether user
 *  succeeded or not in the level and given optional additional attributes.
 *
 *  @native
 *
 *  @param levelName Name of the finished level to log.
 *  @param score     Score use achieved in this level.
 *  @param succeeded Whether used suceeded in this level (`true) or not.
 *  @param attr      Additional attributes to log in this event.
 */
void _logLevelEnd( const std::string &levelName,
                   const long long score,
                   const bool succeeded,
                   const std::map<std::string, double> &attr = {} );

/**
 *  Logs frames per second.
 *
 *  @param isIntensive Whether this log is due to intensive performance
 *                     information report or a regular performance information
 *                     report. Defaults to false.
 */
void _logPerformance( const bool isIntensive = false );

}; // namespace Analytics
}; // namespace MK

#endif /* _Fabric_hpp */
