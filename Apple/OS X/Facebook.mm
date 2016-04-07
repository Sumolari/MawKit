//
//  Facebook.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../Facebook.hpp"

#include "../../Log.hpp"

namespace MK {
namespace Facebook {

void sendInvitation( const std::string &, const std::string & )
{
	Log::nonCriticalCrash( MK::Log::ErrorMessageFormat::METHOD_NOT_AVAILABLE_ON_OSX,
	                       "MK::Facebook::sendInvitation()" );
}

}; // namespace Facebook
}; // namespace MK
