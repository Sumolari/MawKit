//
//  _Log.hpp
//  LatinExplorer
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 01/03/16.
//
//

#ifndef _Log_hpp
#define _Log_hpp

#include <cstdarg>

namespace MK {
namespace Log {

/**
 *  Logs message with given format and additional data to Fabric's
 *  Crashlytics service.
 *
 *  @param format Message to be logged's format.
 *  @param list   Additional data.
 */
void toFabric( const char *format, va_list list );

}; // namespace Log
}; // namespace MK

#endif /* _Log_hpp */
