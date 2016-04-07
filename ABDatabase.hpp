//
//  ABDatabase.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 25/02/16.
//
//

#ifndef ABDatabase_hpp
#define ABDatabase_hpp

#include <functional>
#include <string>

namespace MK {

/**
 *  `ABDatabase` namespace offers a read-only key-value storage system backed by
 *  MixPanel's AB test utilities so values can be changed at any moment.
 */
namespace ABDatabase {

/**
 *  Well known ABDatabase keys.
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

}; // namespace Key

/**
 *  Initializes A/B database and calls given callback if this is the first
 *  time database has been initialized since the game started.
 *
 *  @native
 *
 *  @param callback Callback to be run after initialising database for the first
 *                  time.
 */
void init( const std::function<void( void )> callback = nullptr );

//------------------------------------------------------------------------------
// MARK: - Getters
//------------------------------------------------------------------------------

/**
 *  Returns string value associated with given key.
 *
 *  @native
 *
 *  @param key      Key to retrieve.
 *  @param _default Value to return by default.
 *
 *  @return String value associated with given key or default value.
 */
const std::string getStringValueForKey( const std::string &key, const std::string &_default );

/**
 *  Returns long value associated with given key.
 *
 *  @native
 *
 *  @param key      Key to retrieve.
 *  @param _default Value to return by default.
 *
 *  @return Long value associated with given key or default value.
 */
const long long getLongValueForKey( const std::string &key, const long long _default );

/**
 *  Returns bool value associated with given key.
 *
 *  @native
 *
 *  @param key      Key to retrieve.
 *  @param _default Value to return by default.
 *
 *  @return Long value associated with given key or default value.
 */
const bool getBoolValueForKey( const std::string &key, const bool _default );

/**
 *  Returns float value associated with given key.
 *
 *  @native
 *
 *  @param key      Key to retrieve.
 *  @param _default Value to return by default.
 *
 *  @return Long value associated with given key or default value.
 */
const float getFloatValueForKey( const std::string &key, const float _default );


}; // namespace ABDatabase

}; // namespace MK

#endif /* ABDatabase_hpp */
