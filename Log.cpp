//
//  Log.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#include "Log.hpp"
#include "_Log.hpp"
#include "cocos2d.h"

#include <cassert>
#include <cstdarg>
#include <cstdio>

namespace MK {
namespace Log {

void warning( const char *format, ... )
{
	va_list args;
	va_start( args, format );
	char * final    = new char[cocos2d::MAX_LOG_LENGTH];
	char *realFinal = new char[cocos2d::MAX_LOG_LENGTH];
	sprintf( final, "⚠️  [WARN] ⚠️ %s", format );
	vsprintf( realFinal, final, args );
	cocos2d::log( "%s", realFinal );
	va_end( args );
	delete[] final;
	delete[] realFinal;
}

void debug( const char *format, ... )
{
#ifdef COCOS2D_DEBUG
	va_list args;
	va_start( args, format );
	char * final    = new char[cocos2d::MAX_LOG_LENGTH];
	char *realFinal = new char[cocos2d::MAX_LOG_LENGTH];
	sprintf( final, "🐞 [DEBUG] 🐞 %s", format );
	vsprintf( realFinal, final, args );
	cocos2d::log( "%s", realFinal );
	va_end( args );
	delete[] final;
	delete[] realFinal;
#endif
}

void verbose( const char *format, ... )
{
#ifdef COCOS2D_DEBUG
	va_list args;
	va_start( args, format );
	char * final    = new char[cocos2d::MAX_LOG_LENGTH];
	char *realFinal = new char[cocos2d::MAX_LOG_LENGTH];
	sprintf( final, "💭 [VBOSE] 💭 %s", format );
	vsprintf( realFinal, final, args );
	cocos2d::log( "%s", realFinal );
	va_end( args );
	delete[] final;
	delete[] realFinal;
#endif
}

void nonCriticalCrash( const char *format, ... )
{
	// TODO: Add Fabric support
	va_list args;
	va_start( args, format );
	char * final    = new char[cocos2d::MAX_LOG_LENGTH];
	char *realFinal = new char[cocos2d::MAX_LOG_LENGTH];
	sprintf( final, "❌ [ERROR] ❌ %s", format );
	vsprintf( realFinal, final, args );
	cocos2d::log( "%s", realFinal );
	toFabric( format, args );
	va_end( args );
	delete[] final;
	delete[] realFinal;

#ifdef COCOS2D_DEBUG
	assert( false );
#endif
}

}; // namespace Log
}; // namespace MK
