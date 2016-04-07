//
//  CPPUtils.h
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#ifndef CPPUtils_h
#define CPPUtils_h

#include <Foundation/Foundation.h>
#include <string>

/**
 *  Returns a NSString equivalent to given std::string.
 *
 *  @param string String to convert.
 *
 *  @return Equivalent NSString.
 */
NSString *to_nsstring( const std::string &string );

/**
 *  Returns a NSDictionary equivalent to given std::map of strings.
 *
 *  @param map Map to convert.
 *
 *  @return Equivalent NSDictionary.
 */
NSDictionary<NSString *, NSString *> *
to_nsdictionary( const std::map<std::string, std::string> &map );

/**
 *  Returns a NSDictionary equivalent to given std::map of key strings and
 *  double values.
 *
 *  @param map Map to convert.
 *
 *  @return Equivalent NSDictionary.
 */
NSDictionary<NSString *, NSNumber *> *
to_nsdictionary( const std::map<std::string, double> &map );

/**
 *  Returns a NSDictionary equivalent to given std::map of key strings and
 *  long long values.
 *
 *  @param map Map to convert.
 *
 *  @return Equivalent NSDictionary.
 */
NSDictionary<NSString *, NSNumber *> *
to_nsdictionary( const std::map<std::string, long long> &map );

/**
 *  Returns a NSDictionary equivalent to given std::map of key strings and
 *  bool values.
 *
 *  @param map Map to convert.
 *
 *  @return Equivalent NSDictionary.
 */
NSDictionary<NSString *, NSNumber *> *
to_nsdictionary( const std::map<std::string, bool> &map );

/**
 *  Returns a NSArray equivalent to given std::vector of strings.
 *
 *  @param vec Vector to convert.
 *
 *  @return Equivalent NSArray.
 */
NSArray<NSString *> *to_nsarray( const std::vector<std::string> &vec );

/**
 *  Returns hexadecimal representation of given integer.
 *
 *  @param i Integer whose hexadecimal representation will be returned.
 *
 *  @return Hexadecimal representation of given integer.
 */
static inline char itoh( int i );

/**
 *  Returns NSString with hexadecimal representation of given NSData.
 *
 *  @param data Data to be represented in hexadecimal.
 *
 *  @return Hexadecimal representation of given data.
 */
NSString *NSDataToHex( NSData *data );

/**
 *  Returns NSData with bytes represented by given hexadecimal NSString.
 *
 *  @param string Hexadecimal string containing data.
 *
 *  @return Data represented by given hexadecimal string.
 */
NSData *HexToNSData( NSString *string );

#endif /* CPPUtils_h */
