//
//  GameKit.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#include "../Common/GameKit.h"

#include <UIKit/UIKit.h>

#include "../../Log.hpp"
#include "../Common/CPPUtils.h"

@interface GCDelegate : NSObject <GKGameCenterControllerDelegate>

@end

@implementation GCDelegate

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController
{
	[gameCenterViewController dismissViewControllerAnimated:true
	                                             completion:nil];
}

@end

GCDelegate *gameCenterDelegate = [[GCDelegate alloc] init];

namespace MK {
namespace GameKit {

void _showLeaderboard( const int lID )
{
	if ( leaderboards.count > lID ) {
		if ( !isAvailable() ) {
			Log::debug( "Can't open Leaderboard %d as player didn't log in.", lID );
		}
		else {

			GKGameCenterViewController *gkController =
			[[GKGameCenterViewController alloc] init];

			if ( gkController != nil ) {
				gkController.gameCenterDelegate = gameCenterDelegate;
				gkController.viewState = GKGameCenterViewControllerStateLeaderboards;
				gkController.leaderboardTimeScope = GKLeaderboardTimeScopeToday; // GKLeaderboardTimeScopeAllTime;
				gkController.leaderboardIdentifier = leaderboards[lID];

				[[[UIApplication sharedApplication].delegate window]
				 .rootViewController presentViewController:gkController
				                                  animated:YES
				                                completion:nil];
			}
		}
	}
	else {
		Log::nonCriticalCrash( "Trying to show leaderbord %d out of %d", lID,
		                       leaderboards.count );
	}
}

void showAchievementsList()
{
	if ( !isAvailable() ) {
		Log::debug( "Can't open Achievements UI as player didn't log in." );
	}
	else {

		GKGameCenterViewController *gkController =
		[[GKGameCenterViewController alloc] init];

		if ( gkController != nil ) {
			gkController.gameCenterDelegate = gameCenterDelegate;
			[[[UIApplication sharedApplication].delegate window]
			 .rootViewController presentViewController:gkController
			                                  animated:YES
			                                completion:nil];
		}
	}
}

const bool _signInPlayer()
{
	GKLocalPlayer *player                     = [GKLocalPlayer localPlayer];
	static bool alreadySetAuthenticateHandler = false;
	if ( !alreadySetAuthenticateHandler ) {
		player.authenticateHandler = ^( UIViewController *, NSError *error ) {
		  if ( error ) {
			  MK::Log::debug(
			  "Error trying to sign in Game Center local player: %s",
			  [error localizedDescription].UTF8String );
			  currentLoginState = LoginState::NotLoggedIn;
		  }
		  else {
			  if ( [GKLocalPlayer localPlayer].isAuthenticated ) {
				  currentLoginState = LoginState::LoggedIn;
			  }
			  else {
				  currentLoginState = LoginState::NotLoggedIn;
			  }
		  }
		};
		alreadySetAuthenticateHandler = true;
	}
	return player.isAuthenticated;
}


}; // namespace GameKit
}; // namespace MK
