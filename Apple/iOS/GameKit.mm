//
//  GameKit.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#include "../Common/GameKit.h"

#include <AVFoundation/AVFoundation.h>
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

@interface RPPVCDelegate : NSObject <RPPreviewViewControllerDelegate>

@property ( nonatomic, strong ) RPPreviewViewController *lastRecordingPreviewVC;

@end

@implementation RPPVCDelegate

- (void)previewControllerDidFinish:(RPPreviewViewController *)previewController
{
	[[NSOperationQueue mainQueue] addOperationWithBlock:^{
	  [previewController dismissViewControllerAnimated:YES completion:nil];
	}];
}

@end

RPPVCDelegate *previewVCDelegate = [[RPPVCDelegate alloc] init];

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

namespace ReplayKit {

const bool isAvailable()
{
	return [RPScreenRecorder sharedRecorder].available;
}

void startRecording( bool microphoneEnabled, std::function<void( bool )> callback )
{
	if ( !isAvailable() ) {
		return;
	}

	MK::Log::debug( "Starting new screen recording..." );

	[[RPScreenRecorder sharedRecorder]
	startRecordingWithMicrophoneEnabled:microphoneEnabled
	                            handler:^( NSError *error ) {

		                          /*
		                        [[AVAudioSession sharedInstance]
		                        setCategory:AVAudioSessionCategorySoloAmbient
		                              error:nil];
		                          */

		                          if ( error != nil ) {
			                          MK::Log::warning(
			                          "Error when starting screen recorder:" );
			                          MK::Log::warning( "%s", [error localizedDescription].UTF8String );
		                          }
		                          if ( callback != nullptr ) {
			                          callback( error == nil );
		                          }
		                        }];
}

void stopRecording( std::function<void( bool )> callback )
{
	if ( !isAvailable() ) {
		return;
	}

	MK::Log::debug( "Stopping current screen recording..." );

	[[RPScreenRecorder sharedRecorder]
	stopRecordingWithHandler:^( RPPreviewViewController *_Nullable previewViewController,
	                            NSError *_Nullable error ) {
	  if ( error != nil ) {
		  MK::Log::warning( "Error when stopping screen recorder:" );
		  MK::Log::warning( "%s", [error localizedDescription].UTF8String );
	  }
	  if ( previewViewController != nil ) {
		  previewViewController.previewControllerDelegate = previewVCDelegate;
		  previewVCDelegate.lastRecordingPreviewVC = previewViewController;
	  }
	  if ( callback != nullptr ) {
		  callback( error == nil && previewViewController != nil );
	  }
	}];
}

void discardRecording( std::function<void( void )> callback )
{
	if ( !isAvailable() ) {
		return;
	}

	MK::Log::debug( "Discarting current screen recording..." );

	previewVCDelegate.lastRecordingPreviewVC = nil;

	[[RPScreenRecorder sharedRecorder] discardRecordingWithHandler:^{
	  if ( callback != nullptr ) {
		  callback();
	  }
	}];
}

void showLastRecordedReplayEditor()
{
	if ( hasRecordedReplay() ) {
		[[[UIApplication sharedApplication].delegate window]
		 .rootViewController presentViewController:previewVCDelegate.lastRecordingPreviewVC
		                                  animated:YES
		                                completion:nil];
	}
}

bool hasRecordedReplay()
{
	return previewVCDelegate.lastRecordingPreviewVC != nil;
}

}; // namespace ReplayKit

}; // namespace GameKit
}; // namespace MK
