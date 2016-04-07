//
//  Facebook.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../Facebook.hpp"

#include <FBSDKCoreKit/FBSDKCoreKit.h>
#include <FBSDKShareKit/FBSDKShareKit.h>

#include "../../Features.hpp"
#include "../Common/CPPUtils.h"

#include "AppController.h"
#include "RootViewController.h"

namespace MK {
namespace Facebook {

void sendInvitation( const std::string &linkURL, const std::string &thumbnailURL )
{
	AppController *appController =
	(AppController *)[UIApplication sharedApplication].delegate;

	FBSDKAppInviteContent *content = [[FBSDKAppInviteContent alloc] init];

	content.appLinkURL = [NSURL URLWithString:to_nsstring( linkURL )];

	content.appInvitePreviewImageURL = [NSURL URLWithString:to_nsstring( thumbnailURL )];

	[FBSDKAppInviteDialog showFromViewController:appController.viewController
	                                 withContent:content
	                                    delegate:appController];
}

const bool enabled()
{
	return Features::Facebook;
}

}; // namespace Facebook
}; // namespace MK
