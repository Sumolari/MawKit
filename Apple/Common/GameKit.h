//
//  GameKit.h
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#ifndef GameKit_h
#define GameKit_h

#include "../../GameKit.hpp"
#include "../../_GameKit.hpp"

#include <Foundation/Foundation.h>
#include <GameKit/GameKit.h>
#include <string>
#include <vector>

namespace MK {
namespace GameKit {

extern NSArray<NSString *> *leaderboards; ///< List of leaderboards.
extern NSArray<NSString *> *achievements; ///< List of achievements.

/// `LoginState` represents possible states in a login process.
enum class LoginState {
	Pending     = 0, ///< User has not finished log in process yet.
	LoggedIn    = 1, ///< User has logged in.
	NotLoggedIn = 2  ///< User has decided not to log in.
};

extern LoginState currentLoginState; ///< Current login state.

}; // namespace GameKit
}; // namespace MK

#endif /* GameKit_h */
