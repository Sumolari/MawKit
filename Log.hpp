//
//  Log.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#ifndef Log_hpp
#define Log_hpp

namespace MK {

/**
 *  `Log` namespace offers methods to easily log warning, error, debug-only and
 *  information messages.
 *
 *  Each method will log message to a different subset of output files:
 *  - `warning`: debug, release
 *  - `debug`: debug
 *  - `critical`: debug, release, Fabric (as critical)
 *  - `nonCriticalCrash`: debug, release, Fabric (as non-critical)
 *
 */
namespace Log {

/**
 *  `Log::ErrorMessageFormat` namespace wraps constants defining well-known
 *  errors.
 */
namespace ErrorMessageFormat {

/**
 *  Message logged when a iOS/OS X only method is called on Android.
 */
constexpr const char *METHOD_NOT_AVAILABLE_ON_ANDROID =
"iOS/OS X only method %s called on Android";

/**
 *  Message logged when a method not available on OS X is called on OS X.
 */
constexpr const char *METHOD_NOT_AVAILABLE_ON_OSX =
"called method %s but it is not available on OS X";

}; // namespace ErrorMessageFormat

/**
 *  Logs a warning message that will appear also in release builds.
 *
 *  @param format Format.
 *  @param ...    Additional parameters.
 */
void warning( const char *format, ... );

/**
 *  Logs a debug message that will **not** appear also in release builds.
 *
 *  @param format Format.
 *  @param ...    Additional parameters.
 */
void debug( const char *format, ... );

/**
 *  Logs a critical message that will appear also in release builds and will
 *  also be logged to Fabric.
 *
 *  @param format Format.
 *  @param ...    Additional parameters.
 */
void critical( const char *format, ... );

/**
 *  Logs a non critical message that will appear also in release builds and will
 *  also be logged to Fabric.
 *
 *  @param format Format.
 *  @param ...    Additional parameters.
 */
void nonCriticalCrash( const char *format, ... );

}; // namespace Log
}; // namespace MK

#endif /* Log_hpp */
