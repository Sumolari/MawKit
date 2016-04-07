//
//  KVDatabase.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#ifndef KVDatabase_hpp
#define KVDatabase_hpp

#include <functional>
#include <string>
#include <vector>

namespace MK {

/**
 *  `KVDatabase` namespace offers a key-value secure storage system stores
 *  content with a symmetric encryption in a way that users cannot decrypt data
 *  easily.
 *
 *  It is not meant to store privacy-critical information but data that you
 *  don't want users to easily see or modify.
 */
namespace KVDatabase {

/**
 *  Well known KVDatabase keys.
 *
 *  @note Implementation details: this is wrapped in a namespace and not in an
 *        `enum class` because we need a mapping from each key to a string as
 *        native implementation of these methods use string keys and not numeric
 *        keys. Although any number could be converted to a string it makes it
 *        easier to debug if the string values of keys are actual string
 *        representations of he literals used in the code. As for the moment
 *        we are supporting C++11 and it does not allow setting a `std::string`
 *        nor `char *` associated values for `enum class`, we will stick to
 *        a set of constant values, wrapped in a namespace so they look more
 *        similar to an enumeration.
 */
namespace Key {

/**
 *  Key used to store whether ads are disabled or not.
 */
constexpr const char *ADS_DISABLED = "ads_disabled";

}; // namespace Key

/**
 *  Default values returned by KVDatabase.
 */
namespace Default {

/**
 *  Default value returned when string does not exist.
 */
constexpr const char *STRING = "";

/**
 *  Default value returned when long does not exist.
 */
const long long LONG = 0;

}; // namespace Default

/**
 *  Initializes key-value database and calls given callback if this is the first
 *  time database has been initialized since the game started.
 *
 *  @param callback Callback to be run after initialising database for the first
 *                  time.
 */
void init( const std::function<void( void )> callback = nullptr );

//------------------------------------------------------------------------------
// MARK: - String value setters
//------------------------------------------------------------------------------

/**
 *  Sets string value for given key.
 *
 *  @native
 *
 *  @param key   Key to set.
 *  @param value Value to set.
 *
 *  @return Previous string value for given key or
 *          `MK::KVDatabase::Default::STRING`.
 */
const std::string setStringValueForKey( const std::string &key, const std::string &value );

//------------------------------------------------------------------------------
// MARK: - Long value setters
//------------------------------------------------------------------------------

/**
 *  Sets long value for given key.
 *
 *  @native
 *
 *  @param key   Key to set.
 *  @param value Value to set.
 *
 *  @return Previous long value for given key or
 *          `MK::KVDatabase::Default::LONG`.
 */
const long long setLongValueForKey( const std::string &key, const long long value );

/**
 *  Increases long value for given key by given amount.
 *
 *  @note If there was no long value for given key this method is equivalent to
 *        `setLongValueForKey`.
 *
 *  @param key    Key to increase.
 *  @param amount Amount to increase. Defaults to 1.
 *
 *  @return Previous long value for given key or
 *          `MK::KVDatabase::Default::LONG`.
 */
const long long increaseLongValueForKey( const std::string &key, const long long amount = 1 );

/**
 *  Decreases long value for given key by given amount.
 *
 *  @note If there was no long value for given key this method is equivalent to
 *        `setLongValueForKey`.
 *
 *  @param key    Key to decrease.
 *  @param amount Amount to decrease. Defaults to 1.
 *
 *  @return Previous long value for given key or
 *          `MK::KVDatabase::Default::LONG`.
 */
const long long decreaseLongValueForKey( const std::string &key, const long long amount = 1 );

/**
 *  Keeps maximum long value between current long value and given value.
 *
 *  @note If there was no long value for given key
 *        `MK::KVDatabase::Default::LONG` is used as previous value.
 *
 *  @param key           Key to set.
 *  @param proposedValue Proposed value.
 *
 *  @return Previous long value for given key or
 *          `MK::KVDatabase::Default::LONG`.
 */
const long long keepMaxLongValueForKey( const std::string &key, const long long proposedValue );

/**
 *  Keeps minimum long value between current long value and given value.
 *
 *  @note If there was no long value for given key
 *        `MK::KVDatabase::Default::LONG` is used as previous value.
 *
 *  @param key           Key to set.
 *  @param proposedValue Proposed value.
 *
 *  @return Previous long value for given key or
 *          `MK::KVDatabase::Default::LONG`.
 */
const long long keepMinLongValueForKey( const std::string &key, const long long proposedValue );

//------------------------------------------------------------------------------
// MARK: - Getters
//------------------------------------------------------------------------------

/**
 *  Returns string value associated with given key.
 *
 *  @native
 *
 *  @param key Key to retrieve.
 *
 *  @return String value associated with given key or
 *          `MK::KVDatabase::Default::STRING`.
 */
const std::string getStringValueForKey( const std::string &key );

/**
 *  Returns long value associated with given key.
 *
 *  @native
 *
 *  @param key Key to retrieve.
 *
 *  @return Long value associated with given key or
 *          `MK::KVDatabase::Default::LONG`.
 */
const long long getLongValueForKey( const std::string &key );

//------------------------------------------------------------------------------
// MARK: - Forced sync
//------------------------------------------------------------------------------

/**
 *  Forces writing KVDatabase changes to disk.
 *
 *  @native
 */
void forcedWriteDisk();

}; // namespace KVDatabase

}; // namespace MK

#endif /* KVDatabase_hpp */
