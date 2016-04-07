//
//  KVDatabase.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../KVDatabase.hpp"

#include <SecureNSUserDefaults/NSUserDefaults+SecureAdditions.h>

#include "../../Device.hpp"
#include "CPPUtils.h"

/// Key used to cypher database.
#define SECRET_KEY "a75nv"

namespace MK {
namespace KVDatabase {

/**
 *  Return whether given key is in database or not.
 *
 *  @param key Key to check.
 *
 *  @return True if key is in database.
 */
const bool hasKey( NSString *key );

NSUserDefaults *db = [NSUserDefaults standardUserDefaults];

const bool hasKey( NSString *key )
{
	[db setSecret:@SECRET_KEY];
	return [db objectForKey:key] != nil;
}

//------------------------------------------------------------------------------
#pragma mark - Implementation of namespace methods
//------------------------------------------------------------------------------

const std::string setStringValueForKey( const std::string &key, const std::string &value )
{
	[db setSecret:@SECRET_KEY];

	NSString *ns_key      = to_nsstring( key );
	std::string prevValue = Default::STRING;

	if ( hasKey( ns_key ) ) {
		id dbVal = [db secretObjectForKey:ns_key];
		if ( [dbVal isKindOfClass:NSString.class] ) {
			prevValue = std::string( [dbVal UTF8String] );
		}
	}

	[db setSecretObject:to_nsstring( value ) forKey:ns_key];

	return prevValue;
}

const long long setLongValueForKey( const std::string &key, const long long value )
{
	[db setSecret:@SECRET_KEY];

	NSString *ns_key = to_nsstring( key );
	auto prevValue   = Default::LONG;

	if ( hasKey( ns_key ) ) {
		id dbVal = [db secretObjectForKey:ns_key];
		if ( [dbVal isKindOfClass:NSNumber.class] ) {
			prevValue = [[db secretObjectForKey:ns_key] longLongValue];
		}
	}

	[db setSecretObject:@( value ) forKey:ns_key];

	return prevValue;
}

const std::string getStringValueForKey( const std::string &key )
{
	[db setSecret:@SECRET_KEY];

	NSString *ns_key = to_nsstring( key );

	id dbVal = [db secretObjectForKey:ns_key];

	if ( hasKey( ns_key ) && [dbVal isKindOfClass:NSString.class] ) {
		return std::string( [dbVal UTF8String] );
	}
	else {
		return Default::STRING;
	}
}

const long long getLongValueForKey( const std::string &key )
{
	[db setSecret:@SECRET_KEY];

	NSString *ns_key = to_nsstring( key );

	id dbVal = [db secretObjectForKey:ns_key];

	if ( hasKey( ns_key ) && [dbVal isKindOfClass:NSNumber.class] ) {
		return [dbVal longLongValue];
	}
	else {
		return Default::LONG;
	}
}

//------------------------------------------------------------------------------
#pragma mark - Forced sync
//------------------------------------------------------------------------------

void forcedWriteDisk()
{
	[db synchronize];
}

}; // namespace KVDatabase
}; // namespace MK
