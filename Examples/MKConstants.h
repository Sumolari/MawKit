//
//  MKConstants.h
//  DemoMawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 11/04/16.
//
//

#ifndef MKConstants_h
#define MKConstants_h

namespace MK {

namespace GameKit {

/// Available leaderboards indexes
enum class LeaderboardIndex : unsigned long long {};

/// Available achievements indexes.
enum class AchievementIndex : unsigned long long {};

}; // namespace GameKit

namespace IAPKit {

/// Available in app purchase indexes.
enum class ProductID : unsigned long long {};

}; // namespace IAPKit
}; // namespace MK

#endif /* MKConstants_h */
