//
//  KVDatabase.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#include "KVDatabase.hpp"

#include <iostream>
#include <map>
#include <string>

#include "Log.hpp"

namespace MK {
namespace KVDatabase {

/**
 *  Sets given key in database to the result of applying given binary operation
 *  to previous value (default value if no previous value available) and given
 *  value.
 *
 *  Will return previousy stored value for given key or given default value if
 *  there was not such a key.
 *
 *  @param key   Key to set.
 *  @param value Value to pass to binary operator as second argument.
 *  @param op    Binary operation to perform to previous and new value.
 *
 *  @return Previous value in database for given key.
 */
const long long storeApplyingBinaryOperationAndReturningPreviousValue(
const std::string &key,
const long long value,
const std::function<const long long( const long long, const long long )> &op );

//------------------------------------------------------------------------------
// MARK: - Internal
//------------------------------------------------------------------------------

void init( const std::function<void( void )> callback )
{
	static bool alreadySetup = false;
	if ( !alreadySetup ) {
		if ( callback != nullptr ) {
			callback();
		}
		alreadySetup = true;
	}
}

const long long storeApplyingBinaryOperationAndReturningPreviousValue(
const std::string &key,
const long long value,
const std::function<const long long( const long long, const long long )> &op )
{
	auto prev = getLongValueForKey( key );
	setLongValueForKey( key, op( prev, value ) );
	return prev;
}

//------------------------------------------------------------------------------
// MARK: - Long
//------------------------------------------------------------------------------

const long long increaseLongValueForKey( const std::string &key, const long long amount )
{
	return storeApplyingBinaryOperationAndReturningPreviousValue(
	key, amount,
	[]( const long long prev, const long long value ) { return prev + value; } );
}

const long long decreaseLongValueForKey( const std::string &key, const long long amount )
{
	return increaseLongValueForKey( key, -amount );
}

const long long keepMaxLongValueForKey( const std::string &key, const long long proposedValue )
{
	return storeApplyingBinaryOperationAndReturningPreviousValue(
	key, proposedValue, []( const long long prev, const long long value ) {
		return MAX( prev, value );
	} );
}

const long long keepMinLongValueForKey( const std::string &key, const long long proposedValue )
{
	return storeApplyingBinaryOperationAndReturningPreviousValue(
	key, proposedValue, []( const long long prev, const long long value ) {
		return MIN( prev, value );
	} );
}

}; // namespace KVDatabase

}; // namespace MK
