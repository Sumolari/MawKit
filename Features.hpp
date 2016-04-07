//
//  Features.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 17/02/16.
//
//

#ifndef Features_hpp
#define Features_hpp

namespace MK {

/**
 *  `Features` namespace holds constants defining which features are enabled and
 *  disabled.
 */
namespace Features {

/**
 *  Whether in-app purchases are enabled (`true`) or not.
 */
constexpr bool IAPKit = true;

/**
 *  Whether GameKit's leaderboards are enabled (`true`) or not.
 */
constexpr bool GameKitLeaderboards = true;

/**
 *  Whether GameKit's achievements are enabled (`true`) or not.
 */
constexpr bool GameKitAchievements = true;

/**
 *  Whether Ads are enabled (`true`) or not.
 */
constexpr bool AdKit = true;

/**
 *  Whether Analytics is enabled (`true`) or not.
 */
constexpr bool Analytics = true;

/**
 *  Whether Facebook integration is enabled (`true`) or not.
 */
constexpr bool Facebook = true;

}; // Features

}; // namespace MK


#endif /* Features_hpp */
