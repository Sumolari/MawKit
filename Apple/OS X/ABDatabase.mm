//
//  ABDatabase.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 25/02/16.
//
//

#include "../../ABDatabase.hpp"

namespace MK {
namespace ABDatabase {

void init( const std::function<void( void )> callback )
{
	callback();
}

const std::string getStringValueForKey( const std::string &, const std::string &_default )
{
	return _default;
}

const long long getLongValueForKey( const std::string &, const long long _default )
{
	return _default;
}

const bool getBoolValueForKey( const std::string &, const bool _default )
{
	return _default;
}

const float getFloatValueForKey( const std::string &, const float _default )
{
	return _default;
}

}; // namespace ABDatabase
}; // namespace MK
