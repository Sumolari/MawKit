//
//  ABDatabase.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 25/02/16.
//
//

#include "../../ABDatabase.hpp"

#include <Mixpanel/MPTweakInline.h>

#include "../Common/CPPUtils.h"

namespace MK {
namespace ABDatabase {

void init( const std::function<void( void )> callback )
{
	callback();
}

const std::string getStringValueForKey( const std::string &key, const std::string &_default )
{
	return _default;
	return MPTweakValue( to_nsstring( key ), to_nsstring( _default ) );
}

const long long getLongValueForKey( const std::string &key, const long long _default )
{
	return _default;
	return to_nsstring( MPTweakValue( to_nsstring( key ), @( _default ) ) ).longLongValue;
}

const bool getBoolValueForKey( const std::string &key, const bool _default )
{
	return _default;
	return to_nsstring( MPTweakValue( to_nsstring( key ), @( _default ) ) ).boolValue;
}

const float getFloatValueForKey( const std::string &key, const float _default )
{
	return _default;
	return to_nsstring( MPTweakValue( to_nsstring( key ), @( _default ) ) ).floatValue;
}

}; // namespace ABDatabase
}; // namespace MK
