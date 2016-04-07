//
//  Math.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef Math_hpp
#define Math_hpp

#include <type_traits>

namespace MK {

/**
 *  `Math` namespace wraps common mathematical utilities.
 */
namespace Math {

/**
 *  Returns value clamped so it is bigger or equal to given minimum and lower
 *  or equal to given maximum.
 *
 *  @param min   Minimum value possible.
 *  @param value Value to clamp.
 *  @param max   Maximum value possible.
 *
 *  @return Value clamped to given range.
 */
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
const T clamp( const T min, const T value, const T max )
{
	return std::max( min, std::min( max, value ) );
};

}; // namespace Math

}; // namespace MK

#endif /* Math_hpp */
