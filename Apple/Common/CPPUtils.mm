//
//  CPPUtils.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#include "CPPUtils.h"

#include <Foundation/Foundation.h>
#include <iostream>

NSString *to_nsstring( const std::string &string )
{
	return [NSString stringWithUTF8String:string.c_str()];
}

NSDictionary<NSString *, NSString *> *
to_nsdictionary( const std::map<std::string, std::string> &map )
{
	NSMutableDictionary *dict = [NSMutableDictionary dictionary];
	for ( auto it = map.begin(); it != map.end(); it++ ) {
		[dict setObject:[NSString stringWithUTF8String:it->second.c_str()]
		         forKey:[NSString stringWithUTF8String:it->first.c_str()]];
	}
	return dict;
}

NSDictionary<NSString *, NSNumber *> *
to_nsdictionary( const std::map<std::string, double> &map )
{
	NSMutableDictionary *dict = [NSMutableDictionary dictionary];
	for ( auto it = map.begin(); it != map.end(); it++ ) {
		[dict setObject:@( it->second )
		         forKey:[NSString stringWithUTF8String:it->first.c_str()]];
	}
	return dict;
}

NSDictionary<NSString *, NSNumber *> *
to_nsdictionary( const std::map<std::string, long long> &map )
{
	NSMutableDictionary *dict = [NSMutableDictionary dictionary];
	for ( auto it = map.begin(); it != map.end(); it++ ) {
		[dict setObject:@( it->second )
		         forKey:[NSString stringWithUTF8String:it->first.c_str()]];
	}
	return dict;
}

NSDictionary<NSString *, NSNumber *> *
to_nsdictionary( const std::map<std::string, bool> &map )
{
	NSMutableDictionary *dict = [NSMutableDictionary dictionary];
	for ( auto it = map.begin(); it != map.end(); it++ ) {
		[dict setObject:@( it->second )
		         forKey:[NSString stringWithUTF8String:it->first.c_str()]];
	}
	return dict;
}

NSArray<NSString *> *to_nsarray( const std::vector<std::string> &vec )
{
	NSMutableArray *arr = [NSMutableArray arrayWithCapacity:vec.size()];
	for ( auto item : vec ) {
		[arr addObject:to_nsstring( item )];
	}
	return arr;
}

static inline char itoh( int i )
{
	if ( i > 9 ) return 'A' + ( i - 10 );
	return '0' + i;
}

NSString *NSDataToHex( NSData *data )
{
	NSUInteger i, len;
	unsigned char *buf, *bytes;

	len   = data.length;
	bytes = (unsigned char *)data.bytes;
	buf   = static_cast<unsigned char *>( malloc( len * 2 ) );

	for ( i = 0; i < len; i++ ) {
		buf[i * 2]     = itoh( ( bytes[i] >> 4 ) & 0xF );
		buf[i * 2 + 1] = itoh( bytes[i] & 0xF );
	}

	return [[NSString alloc] initWithBytesNoCopy:buf
	                                      length:len * 2
	                                    encoding:NSASCIIStringEncoding
	                                freeWhenDone:YES];
}

NSData *HexToNSData( NSString *string )
{
	NSMutableData *data = [[NSMutableData alloc] init];
	unsigned char whole_byte;
	char byte_chars[3] = {'\0', '\0', '\0'};
	int i;
	for ( i = 0; i < [string length] / 2; i++ ) {
		byte_chars[0] = [string characterAtIndex:i * 2];
		byte_chars[1] = [string characterAtIndex:i * 2 + 1];
		whole_byte    = strtol( byte_chars, NULL, 16 );
		[data appendBytes:&whole_byte length:1];
	}
	return data;
}
