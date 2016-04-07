//
//  _GameKit.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#ifndef _GameKit_hpp
#define _GameKit_hpp

#include "GameKit.hpp"

namespace MK {

namespace GameKit {

/**
 *  Inits native components of Game Kit.
 *
 *  @native
 */
void _init();

/**
 *  Requests current score from given leaderboard and calls given callback once
 *  value is available.
 *
 *  Callback's first parameter will be the score if the request succeeded and an
 *  invalid value if it didn't.
 *
 *  Callback's second parameter will be `true` if the request succeeded and
 *  `false` otherwise.
 *
 *  @native
 *
 *  @param leaderboardID Leaderboard which current player's current score will
 *                       be retrieved.
 *  @param callback      Callback to be called on success or failure.
 */
void _requestScore( const int leaderboardID, VoidLongLongBoolCB callback = nullptr );

/**
 *  Requests current scores of current player's friends in given leaderboard and
 *  calls given callback once values are available.
 *
 *  Callback's first parameter will be a map of [player's name -> score] if the
 *  request succeeded and an invalid value if it didn't.
 *
 *  Callback's second parameter will be `true` if the request succeeded and
 *  `false` otherwise.
 *
 *  @native
 *
 *  @param leaderboardID Leaderboard which current player's current score will
 *                       be retrieved.
 *  @param callback      Callback to be called on success or failure.
 */
void _requestFriendsScores(
const int leaderboardID,
std::function<void( std::map<std::string, unsigned long long>, bool )> callback = nullptr );

/**
 *  Submits given score to given leaderboard.
 *
 *  @native
 *
 *  @param score         Score to submit.
 *  @param leaderboardID Leaderboard that will receive score.
 */
void _submitScore( const long long score, const int leaderboardID );

/**
 *  Opens leaderboards UI for given leaderboard.
 *
 *  @native
 *
 *  @param leaderbaordID Leaderboard to display.
 */
void _showLeaderboard( const int leaderbaordID );

/**
 *  Reports given progress in achievement with given identifier, unlocking it if
 *  progress is \f$\geq\f$.
 *
 *  @native
 *
 *  @param achievementID Achievement to unlock.
 *  @param progress      Progress of achievement to unlock, from 0 to 1.
 */
void _reportAchievementProgress( const int achievementID, const float progress = 1 );

/**
 *  Requests player's current progress on given achievement and calls given
 *  callback.
 *
 *  Callback's first parameter will be player's current progress on given
 *  achievement if the request succeeded and an invalid value if it didn't.
 *
 *  Callback's second parameter will be `true` if the request succeeded and
 *  `false` otherwise.
 *
 *  @native
 *
 *  @param achievementID Achievement to be retrieved.
 *  @param callback      Callback to be called on success or failure.
 */
void _requestAchievement( const int achievementID,
                          std::function<void( float, bool )> callback = nullptr );

/**
 *  Signs in player in Game Center.
 *
 *  @ios
 *  @osx
 *  @native
 */
const bool _signInPlayer();

}; // namespace GameKit

}; // namespace MK

#endif /* _GameKit_hpp */
