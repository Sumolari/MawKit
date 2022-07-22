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

void sendInvitation( __attribute__((unused)) const std::string &linkURL,
                     __attribute__((unused)) const std::string &thumbnailURL )
{
}

const bool enabled()
{
	return Features::Facebook;
}

}; // namespace Facebook
}; // namespace MK
