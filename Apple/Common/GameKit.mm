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

std::vector<std::string> leaderboards;
std::vector<std::string> achievements;

LoginState currentLoginState = LoginState::Pending;

void _init()
{
	cocos2d::ValueMap ids = cocos2d::FileUtils::getInstance()->getValueMapFromFile(
	( MK::Device::isiOS() ) ? "ios_ids.plist" : "mac_ids.plist" );

	cocos2d::ValueVector aIDs = ids.at( "Achievements" ).asValueVector();
	cocos2d::ValueVector lIDs = ids.at( "Leaderboards" ).asValueVector();

	for ( auto value : aIDs ) {
		achievements.push_back( value.asString() );
	}

	for ( auto value : lIDs ) {
		leaderboards.push_back( value.asString() );
	}

	// Show the "Sign In" window.
	_signInPlayer();
}

void _requestScore( const int lID, VoidLongLongBoolCB callback )
{
	if ( leaderboards.size() > lID ) {
		if ( !isAvailable() ) {
			Log::debug(
			"Can't retrieve score from Leaderboard %d as player didn't log in.", lID );
		}
		else {
			GKLeaderboard *leaderboardRequest = [[GKLeaderboard alloc] init];
			leaderboardRequest.identifier = to_nsstring( leaderboards[lID] );
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
		"Trying to retrieve score from leaderbord %d out of %d", lID, leaderboards.size() );
	}
}

void _requestFriendsScores(
const int lID, std::function<void( std::map<std::string, unsigned long long>, bool )> callback )
{
	if ( leaderboards.size() > lID ) {
		if ( !isAvailable() ) {
			Log::debug(
			"Can't retrieve score from Leaderboard %d as player didn't log in.", lID );
		}
		else {
			GKLeaderboard *leaderboardRequest = [[GKLeaderboard alloc] init];
			leaderboardRequest.playerScope = GKLeaderboardPlayerScopeFriendsOnly;
			leaderboardRequest.timeScope   = GKLeaderboardTimeScopeAllTime;
			leaderboardRequest.identifier  = to_nsstring( leaderboards[lID] );
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
		"Trying to retrieve score from leaderbord %d out of %d", lID, leaderboards.size() );
	}
}

void _submitScore( const long long score, const int lID )
{
	if ( leaderboards.size() > lID ) {
		if ( !isAvailable() ) {
			Log::debug(
			"Can't submit score to Leaderboard %d as player didn't log in.", lID );
		}
		else {
			GKScore *scoreReporter = [[GKScore alloc]
			initWithLeaderboardIdentifier:to_nsstring( leaderboards[lID] )];

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
		"Trying to submit score (%lld) to leaderbord %d out of %d", score, lID,
		leaderboards.size() );
	}
}

void _reportAchievementProgress( const int aID, const float progress )
{
	if ( achievements.size() > aID ) {
		if ( !isAvailable() ) {
			Log::debug( "Can't report achievement progress for achievement %d "
			            "as player didn't log in.",
			            aID );
		}
		else {
			GKAchievement *achievement = [[GKAchievement alloc]
			initWithIdentifier:to_nsstring( achievements[aID] )];
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
		progress * 100, aID, achievements.size() );
	}
}

void _requestAchievement( const int aID, std::function<void( float, bool )> callback )
{
	if ( achievements.size() > aID ) {

		if ( !isAvailable() ) {
			Log::debug(
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

				  NSString *achievementID = to_nsstring( achievements[aID] );

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
		achievements.size() );
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
