//
//  Date.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 29/02/16.
//
//

#ifndef Date_hpp
#define Date_hpp

#include <ctime>

namespace MK {

/// `Date` class is a wrapper for day-precision dates.
class Date {

	public:
	/// Enumeration holding months.
	enum class Month {
		January   = 0,  ///< January
		February  = 1,  ///< February
		March     = 2,  ///< March
		April     = 3,  ///< April
		May       = 4,  ///< May
		June      = 5,  ///< June
		July      = 6,  ///< July
		August    = 7,  ///< August
		September = 8,  ///< September
		October   = 9,  ///< October
		November  = 10, ///< November
		December  = 11  ///< December
	};

	/**
	 *  Returns today's date.
	 *
	 *  @return Date representing today.
	 */
	static const Date Today();

	/**
	 *  Returns the first day of Easter of this year.
	 *
	 *  @return First day of Easter.
	 */
	static const Date EasterStart();

	/**
	 *  Returns the last day of Easter of this year.
	 *
	 *  @return Last day of Easter.
	 */
	static const Date EasterEnd();

	/**
	 *  Returns the first day of Christmas of this year.
	 *
	 *  @return First day of Christmas.
	 */
	static const Date ChristmasStart();

	/**
	 *  Returns the last day of Christmas of this year.
	 *
	 *  @return Last day of Christmas.
	 */
	static const Date ChristmasEnd();

	/**
	 *  Returns a new date object given its UNIX timestamp.
	 *
	 *  @param timestamp UNIX timestamp.
	 */
	Date( std::time_t timestamp );

	/**
	 *  Returns a new date object for given day, month and year.
	 *
	 *  @param day   Day.
	 *  @param month Month.
	 *  @param year  Year.
	 */
	Date( unsigned short day, Month month, unsigned long long year );

	/**
	 *  Returns day component of this date.
	 *
	 *  @return Day component of this date.
	 */
	const unsigned short getDay() const;

	/**
	 *  Returns month component of this date.
	 *
	 *  @return Month component of this date.
	 */
	const Month getMonth() const;

	/**
	 *  Returns year component of this date.
	 *
	 *  @return Year component of this date.
	 */
	const unsigned long long getYear() const;

	/**
	 *  Returns whether left hand side happened before right hand side.
	 *
	 *  @param rhs Right hand side.
	 *
	 *  @return `true` if left hand side happened before right hand side.
	 */
	inline bool operator<( const Date &rhs ) const;

	/**
	 *  Returns whether given dates are equal or not.
	 *
	 *  @param rhs Right hand side.
	 *
	 *  @return `true` if both dates are equal.
	 */
	inline bool operator==( const Date &rhs ) const;

	/**
	 *  Returns UNIX timestamp for given date.
	 *
	 *  @return UNIX timestamp for given date.
	 */
	std::time_t getTimestamp() const;

	protected:
	/**
	 *  Timestamp of this date.
	 */
	std::time_t unixTimestamp;
};

}; // namespace MK

#endif /* Date_hpp */
