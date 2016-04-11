//
//  MKUtils.cpp
//  DemoMawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 11/04/16.
//
//

#include "MawKit/Device.hpp"
#include "MawKit/Features.hpp"
#include "MawKit/KVDatabase.hpp"
#include "MawKit/Log.hpp"

#include "MKConstants.h"

#include "cocos2d.h"

namespace MK {
namespace IAPKit {

const std::string productGlobalIDForProductLocalID(const ProductID localID) {
  static std::vector<std::string> identifiers;
  CCASSERT(false, "Method not implemented yet");
}

const ProductID productLocalIDForProductGlobalID(const std::string &globalID) {
  CCASSERT(false, "Method not implemented yet");
}

void unlockProduct(const ProductID productIdentifier) {
  CCASSERT(false, "Method not implemented yet");
}

}; // namespace IAPKit
}; // namespace MK