//
//  GameKit.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#include "GameKit.h"

#include "../../Device.hpp"
#include "../../Log.hpp"
#include "CPPUtils.h"

namespace MK {
namespace GameKit {

NSArray<NSString *> *leaderboards;
NSArray<NSString *> *achievements;

LoginState currentLoginState = LoginState::Pending;

void _init()
{
	cocos2d::ValueMap ids = cocos2d::FileUtils::getInstance()->getValueMapFromFile(
	( MK::Device::isiOS() ) ? "ios_ids.plist" : "mac_ids.plist" );

	cocos2d::ValueVector aIDs = ids.at( "Achievements" ).asValueVector();
	cocos2d::ValueVector lIDs = ids.at( "Leaderboards" ).asValueVector();

	NSMutableArray<NSString *> *mutableAchievements =
	[NSMutableArray arrayWithCapacity:aIDs.size()];
	NSMutableArray<NSString *> *mutableLeaderboards =
	[NSMutableArray arrayWithCapacity:lIDs.size()];

	for ( auto value : aIDs ) {
		[mutableAchievements addObject:to_nsstring( value.asString() )];
	}

	for ( auto value : lIDs ) {
		[mutableLeaderboards addObject:to_nsstring( value.asString() )];
	}

	achievements = mutableAchievements;
	leaderboards = mutableLeaderboards;

	// Show the "Sign In" window.
	_signInPlayer();
}

void _requestScore( const int lID, VoidLongLongBoolCB callback )
{
	if ( leaderboards.count > lID ) {
		if ( !isAvailable() ) {
			Log::verbose(
			"Can't retrieve score from Leaderboard %d as player didn't log in.", lID );
		}
		else {
			GKLeaderboard *leaderboardRequest = [[GKLeaderboard alloc] init];
			leaderboardRequest.identifier     = leaderboards[lID];
			if ( leaderboardRequest != nil ) {
				[leaderboardRequest
				loadScoresWithCompletionHandler:^( NSArray *scores, NSError *error ) {
#pragma unused( scores )
				  if ( error != nil ) {
					  MK::Log::debug(
					  "Error retrieving score from leaderboard %d: %s", lID,
					  [error localizedDescription].UTF8String );
					  callback( 0, false );
				  }
				  else {
					  callback( leaderboardRequest.localPlayerScore.value, true );
				  }
				}];
			}
		}
	}
	else {
		Log::nonCriticalCrash(
		"Trying to retrieve score from leaderbord %d out of %d", lID, leaderboards.count );
	}
}

void _requestFriendsScores(
const int lID, std::function<void( std::map<std::string, unsigned long long>, bool )> callback )
{
	if ( leaderboards.count > lID ) {
		if ( !isAvailable() ) {
			Log::verbose(
			"Can't retrieve score from Leaderboard %d as player didn't log in.", lID );
		}
		else {
			GKLeaderboard *leaderboardRequest = [[GKLeaderboard alloc] init];
			leaderboardRequest.playerScope = GKLeaderboardPlayerScopeFriendsOnly;
			leaderboardRequest.timeScope   = GKLeaderboardTimeScopeAllTime;
			leaderboardRequest.identifier  = leaderboards[lID];
			if ( leaderboardRequest != nil ) {
				[leaderboardRequest
				loadScoresWithCompletionHandler:^( NSArray *scores, NSError *error ) {
#pragma unused( scores )
				  if ( error != nil ) {
					  MK::Log::debug(
					  "Error retrieving score from leaderboard %d: %s", lID,
					  [error localizedDescription].UTF8String );
					  callback( {}, false );
				  }
				  else {
					  std::map<std::string, unsigned long long> friendsScores;

					  for ( GKScore *s in scores ) {
						  if ( [s.player.playerID
							   isEqualToString:leaderboardRequest.localPlayerScore.player.playerID] ) {
							  continue;
						  }
						  friendsScores[std::string( s.player.alias.UTF8String )] =
						  static_cast<unsigned long long>( s.value );
					  }

					  callback( friendsScores, true );
				  }
				}];
			}
		}
	}
	else {
		Log::nonCriticalCrash(
		"Trying to retrieve score from leaderbord %d out of %d", lID, leaderboards.count );
	}
}

void _submitScore( const long long score, const int lID )
{
	if ( leaderboards.count > lID ) {
		if ( !isAvailable() ) {
			Log::verbose(
			"Can't submit score to Leaderboard %d as player didn't log in.", lID );
		}
		else {
			GKScore *scoreReporter =
			[[GKScore alloc] initWithLeaderboardIdentifier:leaderboards[lID]];

			scoreReporter.value   = score;
			scoreReporter.context = 0;

			[GKScore reportScores:@[scoreReporter]
			withCompletionHandler:^( NSError *error ) {
			  if ( error != nil ) {
				  MK::Log::debug(
				  "Error submitting score (%ll) to leaderboard %d: %s", score,
				  lID, [error localizedDescription].UTF8String );
			  }
			}];
		}
	}
	else {
		Log::nonCriticalCrash(
		"Trying to submit score (%lld) to leaderboard %d out of %d", score, lID,
		leaderboards.count );
	}
}

void _reportAchievementProgress( const int aID, const float progress )
{
	if ( achievements.count > aID ) {
		if ( !isAvailable() ) {
			Log::verbose(
			"Can't report achievement progress for achievement %d "
			"as player didn't log in.",
			aID );
		}
		else {
			GKAchievement *achievement =
			[[GKAchievement alloc] initWithIdentifier:achievements[aID]];
			if ( achievement ) {
				achievement.percentComplete       = progress * 100;
				achievement.showsCompletionBanner = true;
				[GKAchievement
				   reportAchievements:@[achievement]
				withCompletionHandler:^( NSError *error ) {
				  if ( error != nil ) {
					  Log::debug(
					  "Error submitting progress (%.2f) for achievement %d: %s",
					  achievement.percentComplete, aID,
					  [error localizedDescription].UTF8String );
				  }
				}];
			}
		}
	}
	else {
		Log::nonCriticalCrash(
		"Trying to submit progress (%.2f) for unknown achievement %d out of %d",
		progress * 100, aID, achievements.count );
	}
}

void _requestAchievement( const int aID, std::function<void( float, bool )> callback )
{
	if ( achievements.count > aID ) {

		if ( !isAvailable() ) {
			Log::verbose(
			"Can't request achievement %d progress as player didn't log in.", aID );
		}
		else {

			[GKAchievement
			loadAchievementsWithCompletionHandler:^( NSArray<GKAchievement *> *returnedAchievements,
			                                         NSError *error ) {

			  if ( error != nil ) {
				  Log::debug( "Error getting progress for achievement %d: %s",
					          aID, [error localizedDescription].UTF8String );
			  }

			  if ( returnedAchievements != nil ) {

				  NSString *achievementID = achievements[aID];

				  for ( GKAchievement *achievement in returnedAchievements ) {
					  if ( [achievement.identifier isEqualToString:achievementID] ) {
						  callback( achievement.percentComplete / 100.0, true );
						  return;
					  }
				  }

				  Log::debug( "Achievement with identifier %s (%d) was not "
					          "returned by Game Center",
					          achievementID.UTF8String, aID );
				  callback( 0, false );
			  }
			  else {
				  callback( 0, false );
			  }
			}];
		}
	}
	else {
		Log::nonCriticalCrash(
		"Trying to request progress for unknown achievement %d out of %d", aID,
		achievements.count );
	}
}

void exitGame()
{
	cocos2d::Director::getInstance()->end();
}

const bool isAvailable()
{
	switch ( currentLoginState ) {
	case LoginState::Pending:
		return false;
	case LoginState::LoggedIn:
		return true;
	case LoginState::NotLoggedIn:
		return false;
	}
}

}; // namespace GameKit
}; // namespace MK
