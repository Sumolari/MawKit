//
//  Facebook.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../Facebook.hpp"

#include "../../Features.hpp"
#include "../Common/CPPUtils.h"

#include "AppController.h"
#include "RootViewController.h"

namespace MK {
namespace Facebook {

void sendInvitation( const std::string &linkURL, const std::string &thumbnailURL )
{
}

const bool enabled()
{
	return Features::Facebook;
}

}; // namespace Facebook
}; // namespace MK
