//
//  Range.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef Range_hpp
#define Range_hpp

#include <type_traits>

#include "cocos2d.h"

#include "CompilerEnhancements.hpp"
#include "Math.hpp"
#include "Random.hpp"

namespace MK {

/**
 *  A `range` defines a mathematical closed range starting at a value `a`
 *  and ending at a value `b`, both of them included in the range,
 *  mathematically expressed as \f$\left [a,b\right ]\f$. Any value
 *  \f$a\leq  x\leq b\f$ is considered to be included in the range.
 *
 */
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Range {
	template <bool isInteger> class Discrim;

	/**
	 *  Type of first and last values of this range.
	 */
	typedef T ValueType;

	public:
	/**
	 *  Creates a new range starting a `start` and ending at `end`, with both
	 *  values included. Mathematically the new range is expressed as
	 *  \f$\left [\mbox{start},\mbox{end}\right ]\f$
	 */
	Range( const ValueType start, const ValueType end )
	: firstElement( start ), lastElement( end ){};

	/**
	 *  Creates a new range starting at `x` value and ending at `y` value of
	 *  given `cocos2d::Vec2`. Mathematically the new range is expressed as
	 *  \f$\left [\mbox{vector.x},\mbox{vector.y}\right ]\f$
	 */
	Range( const cocos2d::Vec2 &vector )
	: firstElement( vector.x ), lastElement( vector.y ){};

	/**
	 *  Returns a new `Range` of `double` values starting and ending at the
	 *  same values as this `Range`. Useful to get floating point values from an
	 *  integer `Range`.
	 *
	 *  @return New `Range` of `double` values starting and ending at the same
	 *          values as this range.
	 */
	const Range<double> doubleRange() const
	{
		return Range<double>( static_cast<double>( this->firstElement ),
		                      static_cast<double>( this->lastElement ) );
	}

	/**
	 *  Returns a new `Range` of `long long` values. First value will be the
	 *  result of rounding this range's first value as well as last value will
	 *  be the one resulting of rounding this range's last value.
	 *
	 *  @return New `Range` of `long long` values starting and ending values
	 *          near this range`s ones.
	 */
	const Range<long long> longRange() const
	{
		return Range<long long>( static_cast<long long>( std::round( this->firstElement ) ),
		                         static_cast<long long>( std::round( this->lastElement ) ) );
	}

	/**
	 *  Returns a new range starting at `start` and containing `elements`
	 *  integer elements, that is, ending at `start + elements - 1`.
	 *
	 *  Mathematically the new range is expressed as
	 *  \f$\left [\mbox{start},\mbox{start}+\mbox{elements} - 1\right ]\f$.
	 *
	 *  @param start    First element contained in the range.
	 *  @param elements Amount of integer elements contained in new range.
	 *
	 *  @return New range \f$\left [\mbox{start},\mbox{start}+
	 *          \mbox{elements}-1\right]\f$.
	 */
	static const Range RangeFromStartWithLength( const ValueType start, const size_t elements )
	{
		return Range<ValueType>( start, start + elements - 1 );
	}

	/**
	 *  Returns a new range ending containing `elements` integer elements and
	 *  ending at `end`, that is, starting at `end - elements + 1`.
	 *
	 *  Mathematically the new range is expressed as
	 *  \f$\left [\mbox{end}-\mbox{elements}+1,\mbox{end}\right ]\f$.
	 *
	 *  @param elements Last element contained in the range.
	 *  @param end      Amount of integer elements contained in new range.
	 *
	 *  @return New range \f$\left [\mbox{end}-\mbox{elements}+1,\mbox{end}
	 *          \right]\f$.
	 */
	static const Range RangeWithLengthUpToEnd( const size_t elements, const ValueType end )
	{
		return Range<ValueType>( end - elements + 1, end );
	}

	/**
	 *  Returns whether given value is contained in this range or not,
	 *  mathematically speaking returns whether \f$\mbox{start}\leq \mbox{value}
	 *  \leq \mbox{end}\f$ holds or not.
	 *
	 *  @param value Value to check if it is contained in this range or not.
	 *
	 *  @return `true` if given value is contained in this range or not.
	 */
	const bool contains( ValueType value ) const
	{
		return value >= this->firstElement && value <= this->lastElement;
	}

	/**
	 *  Returns given value clamped to this range.
	 *
	 *  @param value Value to be clamped.
	 *
	 *  @return Clamped value so it is contained in this range and the
	 *          difference to original value is minimum.
	 */
	const ValueType clamp( ValueType value ) const
	{
		return Clamp( this->firstElement, value, this->lastElement );
	}

	/**
	 *  Returns whether this range's first value is lower than given range's
	 *  first value.
	 *
	 *  @param rhs Right hand side operand.
	 *
	 *  @return `true` if this range's first value is lower than given range's
	 *          first value.
	 */
	const bool operator<( MK::Range<T> rhs ) const
	{
		if ( this->first() < rhs.first() ) {
			return true;
		}
		else if ( this->first() == rhs.first() ) {
			return this->last() < rhs.last();
		}
		return false;
	}

	/**
	 *  Returns whether this range's last value is grater than given range's
	 *  last value.
	 *
	 *  @param rhs Right hand side operand.
	 *
	 *  @return `true` if this range's last value is greater than given range's
	 *          last value.
	 */
	const bool operator>( MK::Range<T> rhs ) const
	{
		if ( this->first() > rhs.first() ) {
			return true;
		}
		else if ( this->first() == rhs.first() ) {
			return this->last() > rhs.last();
		}
		return false;
	}

	/**
	 *  Returns whether this range is equal to given range.
	 *
	 *  @param rhs Right hand side operand.
	 *
	 *  @return `true` if both ranges start and end in the same values.
	 */
	const bool operator==( MK::Range<T> rhs ) const
	{
		return this->first() == rhs.last();
	}

	/**
	 *  Returns whether given value is contained in this range or not,
	 *  mathematically speaking returns whether \f$\mbox{start}\leq \mbox{value}
	 *  \leq \mbox{end}\f$ holds or not.
	 *
	 *  @param value Value to check if it is contained in this range or not.
	 *
	 *  @return `true` if given value is contained in this range or not.
	 */
	const bool operator[]( ValueType value ) const
	{
		return this->contains( value );
	}

	/**
	 *  Returns a random integer value contained in this range, that is, a
	 *  random value such that \f$\mbox{start}\leq \mbox{value}\leq
	 *  \mbox{end}\f$ holds.
	 *
	 *  @return Random integer value contained in this range.
	 */
	const ValueType randomInteger() const
	{
		if ( this->firstElement >= 0 ) {
			return Random::IntegerNumberInRange(
			static_cast<unsigned long long>( std::ceil( this->firstElement ) ),
			static_cast<unsigned long long>( std::floor( this->lastElement ) ) );
		}
		else {
			return Random::IntegerNumberInRange(
			static_cast<long long>( std::ceil( this->firstElement ) ),
			static_cast<long long>( std::floor( this->lastElement ) ) );
		}
	}

	/**
	 *  Returns a random value contained in this range, that is, a random value
	 *  such that \f$\mbox{start}\leq \mbox{value}< \mbox{end}\f$ holds.
	 *
	 *  @return Random value contained in this range.
	 */
	const ValueType randomFloatingPoint() const
	{
		return Random::FloatingPointNumberInRange( this->firstElement, this->lastElement );
	}

	/**
	 *  Returns the length of this range, that is, the amount of integer values
	 *  such that \f$\mbox{start}\leq \mbox{value}\leq \mbox{end}\f$ holds.
	 *
	 *  @return Amount of integer values contained in this range.
	 */
	const size_t length() const
	{
		return static_cast<size_t>( std::ceil( lastElement - firstElement ) );
	}

	/**
	 *  Returns first value contained in this range.
	 *
	 *  @return First value contained in this range.
	 */
	const ValueType first() const
	{
		return this->firstElement;
	}

	/**
	 *  Returns last value contained in this range.
	 *
	 *  @return Last value contained in this range.
	 */
	const ValueType last() const
	{
		return this->lastElement;
	}

	protected:
	/**
	 *  First element of this range.
	 */
	const ValueType firstElement;

	/**
	 *  Last element of this range.
	 */
	const ValueType lastElement;
};

/**
 *  Range of `short` values.
 */
typedef Range<short> SRange;

/**
 *  Range of `long long` values.
 */
typedef Range<long long> LLRange;

/**
 *  Range of `double` values.
 */
typedef Range<double> DRange;

}; // namespace MK

#endif /* Range_hpp */
