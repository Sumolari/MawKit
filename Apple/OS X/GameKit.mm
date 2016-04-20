//
//  GameKit.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#include "../Common/GameKit.h"

#include "../../Log.hpp"
#include "../Common/CPPUtils.h"

@interface GCDelegate : NSObject <GKGameCenterControllerDelegate>

@end

@implementation GCDelegate

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController
{
#pragma unused( gameCenterViewController )
	GKDialogController *sdc = [GKDialogController sharedDialogController];
	[sdc dismiss:self];
}

@end

GCDelegate *gameCenterDelegate = [[GCDelegate alloc] init];

namespace MK {
namespace GameKit {

void _showLeaderboard( int lID )
{
	if ( leaderboards.count > lID ) {
		if ( !isAvailable() ) {
			Log::verbose( "Can't open Leaderboard %d as player didn't log in.", lID );
		}
		else {

			GKGameCenterViewController *gkController =
			[[GKGameCenterViewController alloc] init];

			if ( gkController != nil ) {
				gkController.gameCenterDelegate = gameCenterDelegate;
				gkController.viewState = GKGameCenterViewControllerStateLeaderboards;
				gkController.leaderboardTimeScope = GKLeaderboardTimeScopeToday; // GKLeaderboardTimeScopeAllTime;
				gkController.leaderboardIdentifier = leaderboards[lID];

				GKDialogController *sdc = [GKDialogController sharedDialogController];
				sdc.parentWindow = [NSApplication sharedApplication].mainWindow;
				[sdc presentViewController:gkController];
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
		Log::verbose( "Can't open Achievements UI as player didn't log in." );
	}
	else {
		GKGameCenterViewController *gkController =
		[[GKGameCenterViewController alloc] init];

		if ( gkController != nil ) {
			gkController.gameCenterDelegate = gameCenterDelegate;
			[[NSApplication sharedApplication]
			 .mainWindow.contentViewController presentViewControllerAsModalWindow:gkController];
		}
	}
}


const bool _signInPlayer()
{
	GKLocalPlayer *player                     = [GKLocalPlayer localPlayer];
	static bool alreadySetAuthenticateHandler = false;
	if ( !alreadySetAuthenticateHandler ) {
		player.authenticateHandler = ^( NSViewController *viewController, NSError *error ) {
#pragma unused( viewController )
		  if ( error ) {
			  Log::debug(
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

namespace ReplayKit {

const bool isAvailable()
{
	return false;
}

void startRecording( bool, std::function<void( bool )> callback )
{
	if ( callback != nullptr ) {
		callback( false );
	}
}

void stopRecording( std::function<void( bool )> callback )
{
	if ( callback != nullptr ) {
		callback( false );
	}
}

void discardRecording( std::function<void( void )> callback )
{
	if ( callback != nullptr ) {
		callback();
	}
}

void showLastRecordedReplayEditor()
{
}

bool hasRecordedReplay()
{
	return false;
}

}; // namespace ReplayKit

}; // namespace GameKit
}; // namespace MK
