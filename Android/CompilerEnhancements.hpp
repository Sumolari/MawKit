//
//  CompilerEnhancements.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#ifndef Android_CompilerEnhancements_hpp
#define Android_CompilerEnhancements_hpp

#include <sstream>
#include <string>
#include <type_traits>


namespace std {
template <typename T> string to_string( const T &t )
{
	std::ostringstream os;
	os << t;
	return os.str();
}

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
long long round( const T &t )
{
	if ( static_cast<double>( t ) - std::floor( t ) < 0.5 ) {
		return static_cast<long long>( t );
	}

	return static_cast<long long>( t ) + 1;
}
}; // namespace std

#endif /* CompilerEnhancements_hpp */

#endif
