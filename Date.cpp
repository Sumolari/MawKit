//
//  Date.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 29/02/16.
//
//

#include "Date.hpp"

namespace MK {

typedef Date Self;

const Self Self::Today()
{
	std::time_t rawtime;
	std::time( &rawtime );
	return Self( rawtime );
}

const Self Self::EasterStart()
{
	auto end = Self::EasterEnd();

	unsigned short day = end.getDay();
	auto month         = end.getMonth();

	if ( day < 15 ) {
		month = static_cast<Self::Month>( static_cast<int>( month ) - 1 );
		day   = 31 - 15 + day;
	}
	else {
		day -= 15;
	}

	return Date( day, month, end.getYear() );
}

const Self Self::EasterEnd()
{
	auto today = Self::Today();

	int A = today.getYear() % 19;
	int B = int( today.getYear() / 100 );
	int C = today.getYear() % 100;
	int D = B / 4;
	int E = B % 4;
	int F = ( B + 8 ) / 25;
	int G = ( B - F + 1 ) / 3;
	int H = ( 19 * A + B - D - G + 15 ) % 30;
	int I = C / 4;
	int K = C % 4;
	int L = ( 32 + 2 * E + 2 * I - H - K ) % 7;
	int M = ( A + 11 * H + 22 * L ) / 451;
	int N = H + L - 7 * M + 114;

	int month = N / 31;
	int day   = 1 + ( N % 31 );

	return Date( day, static_cast<Self::Month>( month ), today.getYear() );
}

const Self Self::ChristmasStart()
{
	return Date( 10, Self::Month::December, Self::Today().getYear() );
}

const Self Self::ChristmasEnd()
{
	return Date( 31, Self::Month::December, Self::Today().getYear() );
}

Self::Date( std::time_t timestamp )
{
	this->unixTimestamp = timestamp;
}

Self::Date( unsigned short day, Month month, unsigned long long year )
{
	std::tm lDate;

	lDate.tm_sec  = 0;
	lDate.tm_min  = 0;
	lDate.tm_hour = 0;
	lDate.tm_mday = day;
	lDate.tm_mon  = static_cast<int>( month );
	lDate.tm_year = static_cast<int>( year ) - 1900;

	std::time_t lTimeEpoch = std::mktime( &lDate );

	this->unixTimestamp = lTimeEpoch;
}

const unsigned short Self::getDay() const
{
	auto lDate = std::gmtime( &( this->unixTimestamp ) );
	return lDate->tm_mday;
}

const Self::Month Self::getMonth() const
{
	auto lDate = std::gmtime( &( this->unixTimestamp ) );
	return static_cast<Self::Month>( lDate->tm_mon );
}

const unsigned long long Self::getYear() const
{
	auto lDate = std::gmtime( &( this->unixTimestamp ) );
	return 1900 + lDate->tm_year;
}

bool Self::operator<( const Self &rhs ) const
{
	return this->getTimestamp() < rhs.getTimestamp();
}

bool Self::operator==( const Self &rhs ) const
{
	return this->getTimestamp() == rhs.getTimestamp();
}

std::time_t Self::getTimestamp() const
{
	return this->unixTimestamp;
}

}; // namespace MK
