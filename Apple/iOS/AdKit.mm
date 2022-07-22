//
//  AdKit.mm
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "../../AdKit.hpp"

#include <UIKit/UIKit.h>

#include "../../Analytics.hpp"
#include "../../Device.hpp"
#include "../../Log.hpp"
#include "../Common/CPPUtils.h"

//------------------------------------------------------------------------------
// Storage of active delegates and ads.
//------------------------------------------------------------------------------

NSMutableDictionary<NSString *, id> *delegates;

//------------------------------------------------------------------------------
#pragma mark - MawKit
//------------------------------------------------------------------------------

namespace MK {
namespace AdKit {

bool videoRewardsAvailable()
{
    return false;
}

}; // namespace AdKit
}; // namespace MK
