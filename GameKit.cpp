//
//  GameKit.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#include "GameKit.hpp"
#include "_GameKit.hpp"

#include <algorithm>
#include <functional>

#include "Features.hpp"
#include "KVDatabase.hpp"

namespace MK {
namespace GameKit {

void init( std::function<void( void )> callback )
{
	if ( MK::Features::GameKitLeaderboards || MK::Features::GameKitAchievements ) {
		_init();
		if ( callback != nullptr ) {
			callback();
		}
	}
}

void requestScore( const LeaderboardIndex &leaderboardID, VoidLongLongBoolCB callback )
{
	if ( !MK::Features::GameKitLeaderboards ) return;

	_requestScore( int( leaderboardID ), callback );
}

void requestFriendsScores( const LeaderboardIndex &leaderboardID,
                           std::function<void( std::map<std::string, unsigned long long>, bool )> callback )
{
	if ( !MK::Features::GameKitLeaderboards ) return;

	_requestFriendsScores( int( leaderboardID ), callback );
}

void submitScore( const long long score, const LeaderboardIndex &leaderboardID )
{
	if ( !MK::Features::GameKitLeaderboards ) return;

	_submitScore( score, int( leaderboardID ) );
}

void showLeaderboard( const LeaderboardIndex &leaderbaordID )
{
	if ( !MK::Features::GameKitLeaderboards ) return;

	_showLeaderboard( int( leaderbaordID ) );
}

void showLeaderboards()
{
	if ( !MK::Features::GameKitLeaderboards ) return;

	_showLeaderboards();
}

void reportAchievementProgress( const AchievementIndex &achievementID, const float progress )
{
	if ( !MK::Features::GameKitAchievements ) return;

	_reportAchievementProgress( int( achievementID ),
	                            std::min( 1.0, static_cast<double>( progress ) ) );
}

void requestAchievement( const AchievementIndex &achievementID,
                         std::function<void( float, bool )> callback )
{
	if ( !MK::Features::GameKitAchievements ) return;

	_requestAchievement( int( achievementID ), callback );
}

}; // namespace GameKit
}; // namespace MK
