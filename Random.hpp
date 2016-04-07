//
//  Random.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef Random_hpp
#define Random_hpp

#include <iterator>
#include <random>
#include <type_traits>
#include <vector>

namespace MK {

/**
 *  `Random` namespace features utilities to get random numbers.
 */
namespace Random {

/**
 *  Returns a random iterator between given `start` and `end` iterators,
 *  using given generator `g` to compute randomness.
 *
 *  @param start First iterator that can be selected.
 *  @param end   Last iterator, it cannot be selected.
 *  @param g     Generator of randomness.
 *
 *  @return Random iterator between given `start` and `end` iterators.
 */
template <typename Iter, typename RandomGenerator>
Iter Choose( Iter start, Iter end, RandomGenerator &g )
{
	std::uniform_int_distribution<> dis( 0, static_cast<int>(
	                                        std::distance( start, end ) - 1 ) );
	std::advance( start, dis( g ) );
	return start;
}

/**
 *  Returns a random iterator between given `start` and `end` iterators,
 *  using uniform probability.
 *
 *  @param start First iterator that can be selected.
 *  @param end   Last iterator, it cannot be selected.
 *
 *  @return Random iterator between given `start` and `end` iterators.
 */
template <typename Iter> Iter Choose( Iter start, Iter end )
{
	static std::random_device rd;
	static std::mt19937 gen( rd() );
	return Choose( start, end, gen );
}

/**
 *  Returns a random value in given vector.
 *
 *  @param vector Vector containing value to be returned.
 *
 *  @return Random value in given vector.
 */
template <class VectorValue>
VectorValue Choose( const std::vector<VectorValue> &vector )
{
	return *Choose( vector.begin(), vector.end() );
}

/**
 *  Returns a floating point number in range \f$\left[\mbox{min},\mbox{max}
 *  \right)\f$.
 *
 *  @param min Minimum value (included) in the range.
 *  @param max Maximum value (**not included**) in the range.
 *
 *  @return Floating point number in range \f$\left[\mbox{min},\mbox{max}
 *          \right)\f$.
 */
template <typename Number, typename = typename std::enable_if<std::is_arithmetic<Number>::value, Number>::type>
const double FloatingPointNumberInRange( const Number min, const Number max )
{
	return static_cast<double>( std::rand() ) / RAND_MAX * ( max - min ) + min;
}

/**
 *  Returns an integer number in closed range \f$\left[\mbox{min},\mbox{max}
 *  \right]\f$.
 *
 *  @param min Minimum value (included) in the range.
 *  @param max Maximum value (included) in the range.
 *
 *  @return Integer number in closed range \f$\left[\mbox{min},\mbox{max}
 *          \right]\f$.
 */
template <typename IntegerNumber,
          typename = typename std::enable_if<std::is_integral<IntegerNumber>::value, IntegerNumber>::type>
const IntegerNumber IntegerNumberInRange( const IntegerNumber min, const IntegerNumber max )
{
	return static_cast<IntegerNumber>(
	static_cast<double>( std::rand() ) / RAND_MAX * ( max - min + 1 ) + min );
}

/**
 *  Given a probability (floating point number between zero and one, both
 *  included) returns a random boolean value which will be `true`
 *  \f$\mbox{number}\times100\%\f$ of times this method is called and `false`
 *  the other \f$\left(1-\mbox{number}\right)\times100\%\f$.
 *
 *  @param number Probability of returning `true`.
 *
 *  @return Randomly `true` or `false` taking into account given `true`
 *          probability.
 */
template <typename FPNumberBetweenZeroAndOne,
          typename = typename std::enable_if<std::is_arithmetic<FPNumberBetweenZeroAndOne>::value, FPNumberBetweenZeroAndOne>::type>
const bool TakeChance( const FPNumberBetweenZeroAndOne number )
{
	return FloatingPointNumberInRange( 0, 1 ) <= number;
}

}; // namespace Random
}; // namespace MK

#endif /* Random_hpp */
