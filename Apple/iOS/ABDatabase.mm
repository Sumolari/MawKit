//
//  ABDatabase.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 25/02/16.
//
//

#include "../../ABDatabase.hpp"

#include "../Common/CPPUtils.h"

namespace MK {
namespace ABDatabase {

void init( const std::function<void( void )> callback )
{
	callback();
}

const std::string getStringValueForKey( __attribute__((unused)) const std::string &key,
                                        __attribute__((unused)) const std::string &_default )
{
	return _default;

}

const long long getLongValueForKey( __attribute__((unused)) const std::string &key,
                                    __attribute__((unused)) const long long _default )
{
	return _default;
	
}

const bool getBoolValueForKey( __attribute__((unused)) const std::string &key,
                               __attribute__((unused)) const bool _default )
{
	return _default;
	
}

const float getFloatValueForKey( __attribute__((unused)) const std::string &key,
                                 __attribute__((unused)) const float _default )
{
	return _default;
	
}

}; // namespace ABDatabase
}; // namespace MK
