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

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import "Mixpanel.h"
#endif

#include <Crashlytics/Answers.h>

#include "CPPUtils.h"

namespace MK {
namespace Analytics {

void _logEvent( const std::string &event )
{
	[Answers logCustomEventWithName:to_nsstring( event ) customAttributes:nil];

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	[[Mixpanel sharedInstance] track:to_nsstring( event ) properties:nil];
#endif
}

void _logEvent( const std::string &event, const std::map<std::string, std::string> &attr )
{
	[Answers logCustomEventWithName:to_nsstring( event )
	               customAttributes:to_nsdictionary( attr )];

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	[[Mixpanel sharedInstance] track:to_nsstring( event )
	                      properties:to_nsdictionary( attr )];
#endif
}

void _logEvent( const std::string &event, const std::map<std::string, double> &attr )
{
	[Answers logCustomEventWithName:to_nsstring( event )
	               customAttributes:to_nsdictionary( attr )];

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	[[Mixpanel sharedInstance] track:to_nsstring( event )
	                      properties:to_nsdictionary( attr )];
#endif
}

void _logLevelStart( const std::string &levelName,
                     const std::map<std::string, std::string> &attributes )
{
	[Answers logLevelStart:to_nsstring( levelName )
	      customAttributes:to_nsdictionary( attributes )];

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	NSMutableDictionary *dict =
	[NSMutableDictionary dictionaryWithDictionary:to_nsdictionary( attributes )];
	dict[@"level_name"] = to_nsstring( levelName );
	[[Mixpanel sharedInstance] track:@"Level Start" properties:dict];
#endif
}

void _logLevelStart( const std::string &levelName,
                     const std::map<std::string, double> &attributes )
{
	[Answers logLevelStart:to_nsstring( levelName )
	      customAttributes:to_nsdictionary( attributes )];

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	NSMutableDictionary *dict =
	[NSMutableDictionary dictionaryWithDictionary:to_nsdictionary( attributes )];
	dict[@"level_name"] = to_nsstring( levelName );
	[[Mixpanel sharedInstance] track:@"Level Start" properties:dict];
#endif
}

void _logLevelEnd( const std::string &levelName,
                   const long long score,
                   const bool succeeded,
                   const std::map<std::string, std::string> &attr )
{
	[Answers logLevelEnd:to_nsstring( levelName )
	               score:@( score )
	             success:@( succeeded )
	    customAttributes:to_nsdictionary( attr )];

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	NSMutableDictionary *dict =
	[NSMutableDictionary dictionaryWithDictionary:to_nsdictionary( attr )];
	dict[@"level_name"] = to_nsstring( levelName );
	dict[@"score"]      = @( score );
	dict[@"duration"]   = dict[@"time"];
	[dict removeObjectForKey:@"time"];
	[[Mixpanel sharedInstance] track:@"Level End" properties:dict];
#endif
}

void _logLevelEnd( const std::string &levelName,
                   const long long score,
                   const bool succeeded,
                   const std::map<std::string, double> &attr )
{
	[Answers logLevelEnd:to_nsstring( levelName )
	               score:@( score )
	             success:@( succeeded )
	    customAttributes:to_nsdictionary( attr )];

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	NSMutableDictionary *dict =
	[NSMutableDictionary dictionaryWithDictionary:to_nsdictionary( attr )];
	dict[@"level_name"] = to_nsstring( levelName );
	dict[@"score"]      = @( score );
	dict[@"duration"]   = dict[@"time"];
	[dict removeObjectForKey:@"time"];
	[[Mixpanel sharedInstance] track:@"Level End" properties:dict];
#endif
}

}; // namespace Analytics
}; // namespace MK
