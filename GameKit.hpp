//
//  GameKit.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#ifndef GameKit_hpp
#define GameKit_hpp

#include <functional>
#include <map>
#include <string>

namespace MK {

/**
 *  `GameKit` namespace offers a secure wrapper for achievements and
 *  leaderboards backed by Game Center on Apple devices and Google Play Services
 *  on Android.
 */
namespace GameKit {

/// Enumeration defining available leaderboards. Must be declared in your game.
/// @example enum class LeaderboardIndex: unsigned long long { SCORE = 0 };
enum class LeaderboardIndex : unsigned long long;

/// Enumeration defining available achievements. Must be declared in your game.
/// @example enum class AchievementIndex: unsigned long long { DIED = 0 };
enum class AchievementIndex : unsigned long long;

/**
 *  Type of callbacks called after finishing an asynchronous request.
 *
 *  Receives as **first argument** value retrieved and as **second argument**
 *  whether value was successfully retrieved (`true`) or not. Value
 *  unsuccessfully retrieved has no meaning and should not be used.
 */
typedef std::function<void( long long, bool )> VoidLongLongBoolCB;

/**
 *  Initializes internal data structures, local player and so on.
 *
 *  @param callback Callback to be called after initialization.
 */
void init( std::function<void( void )> callback = nullptr );

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
 *  @param leaderboardID Leaderboard which current player's current score will
 *                       be retrieved.
 *  @param callback      Callback to be called on success or failure.
 */
void requestScore( const LeaderboardIndex &leaderboardID,
                   VoidLongLongBoolCB callback = nullptr );

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
 *  @param leaderboardID Leaderboard which current player's current score will
 *                       be retrieved.
 *  @param callback      Callback to be called on success or failure.
 */
void requestFriendsScores(
const LeaderboardIndex &leaderboardID,
std::function<void( std::map<std::string, unsigned long long>, bool )> callback = nullptr );

/**
 *  Submits given score to given leaderboard.
 *
 *  @param score         Score to submit.
 *  @param leaderboardID Leaderboard that will receive score.
 */
void submitScore( const long long score, const LeaderboardIndex &leaderboardID );

/**
 *  Opens leaderboards UI for given leaderboard.
 *
 *  @param leaderbaordID Leaderboard to display.
 */
void showLeaderboard( const LeaderboardIndex &leaderbaordID );

/**
 *  Opens all leaderboards UI.
 */
void showLeaderboards();

/**
 *  Reports achievement with given identifier and progress, unlocking it if
 *  progress is \f$\geq\f$.
 *
 *  @param achievementID Achievement to unlock.
 *  @param progress      Progress of achievement to unlock, from 0 to 1.
 */
void reportAchievementProgress( const AchievementIndex &achievementID,
                                const float progress = 1 );

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
 *  @param achievementID Achievement to be retrieved.
 *  @param callback      Callback to be called on success or failure.
 */
void requestAchievement( const AchievementIndex &achievementID,
                         std::function<void( float, bool )> callback = nullptr );

/**
 *  Shows achievements list screen.
 *
 *  @native
 */
void showAchievementsList();

/**
 *  Closes the game.
 *
 *  @note Do **NOT** use `cocos2d::Director::end()` with MK::GameKit.
 */
void exitGame();

/**
 *  On Android returns whether Google Play Games is available (`true`) or not.
 *
 *  On iOS and OS X returns whether Game Center is available and user has logged
 *  in (`true`) or not.
 *
 *  @return `true` if Google Play Games is available on Android or Game Center
 *          is available and user has logged in on iOS and OS X
 */
const bool isAvailable();

}; // namespace GameKit

}; // namespace MK


#endif /* GameKit_hpp */
