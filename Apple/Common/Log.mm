//
//  Log.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 01/03/16.
//
//

#include "../../_Log.hpp"

namespace MK {
namespace Log {

void toFabric( const char *format, va_list list )
{
	NSLogv( [NSString stringWithUTF8String:format], list );
}

}; // namespace Log
}; // namespace MK
