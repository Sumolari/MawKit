//
//  Analytics.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef Analytics_hpp
#define Analytics_hpp

#include <map>
#include <string>

namespace MK {

/**
 *  `Analytics` namespace wraps Twitter's Fabric and MixPanel methods in a set
 *  of cross-compatible functions.
 */
namespace Analytics {

/**
 *  `Fabric::PerformanceIntensiveLogging` namespace features constants that
 *  allow enabling or disabling logging performance in an intensive way, as well
 *  as fine-tuning intensive performance logging intervals.
 */
namespace PerformanceIntensiveLogging {

/**
 *  Period of intensive performance logging in seconds, that is, seconds to
 *  wait between two consecutive performance events.
 */
constexpr double PERIOD = 2.0;

/**
 *  Probability (up to 1) of an invocation to
 *  `Fabric::maybeScheduleIntensivePerformanceLogging` to schedule an intensive
 *  performance logging.
 */
constexpr double PROBABILITY = 0.01;

/**
 *  Identifier of callback that logs FPS periodically.
 */
constexpr const char *CALLBACK_ID = "logFPS";

}; // namespace PerformanceIntensiveLogging

/**
 *  Logs given event without additional attributes.
 *
 *  @native
 *
 *  @param event Name of the event to log.
 */
void logEvent( const std::string &event );

/**
 *  Logs given event with given additional attributes.
 *
 *  @native
 *
 *  @param event Name of the event to log.
 *  @param attr  Additional attributes.
 */
void logEvent( const std::string &event, const std::map<std::string, std::string> &attr );

/**
 *  Logs given event with given additional attributes.
 *
 *  @native
 *
 *  @param event Name of the event to log.
 *  @param attr  Additional attributes.
 */
void logEvent( const std::string &event, const std::map<std::string, double> &attr );

/**
 *  Logs start of level with given name/identifier.
 *
 *  @param levelName Name of the started level to log.
 */
void logLevelStart( const std::string &levelName );

/**
 *  Logs start of level with given name/identifier and given optional additional
 *  attributes.
 *
 *  @native
 *
 *  @param levelName  Name of the started level to log.
 *  @param attributes Additional attributes to log in this event.
 */
void logLevelStart( const std::string &levelName,
                    const std::map<std::string, std::string> &attributes );

/**
 *  Logs start of level with given name/identifier and given optional additional
 *  attributes.
 *
 *  @native
 *
 *  @param levelName  Name of the started level to log.
 *  @param attributes Additional attributes to log in this event.
 */
void logLevelStart( const std::string &levelName,
                    const std::map<std::string, double> &attributes );

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
void logLevelEnd( const std::string &levelName,
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
void logLevelEnd( const std::string &levelName,
                  const long long score,
                  const bool succeeded,
                  const std::map<std::string, double> &attr = {} );

/**
 *  Logs that app tried to display a video reward ad that was not ready yet.
 */
void logNonReadyVideoRewardDisplay();

/**
 *  Returns whether Analytics logging in enbled or not.
 *
 *  @return `true` if events should be logged in Fabric's Answers platform and
 *          MixPanel.
 */
const bool enabled();

}; // namespace Analytics
}; // namespace MK

#endif /* Fabric_hpp */
