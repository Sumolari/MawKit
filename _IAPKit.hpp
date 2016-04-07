//
//  _IAPKit.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 19/02/16.
//
//

#ifndef _IAPKit_hpp
#define _IAPKit_hpp

#include "IAPKit.hpp"

#include <functional>
#include <vector>

namespace MK {
namespace IAPKit {

/**
 *  Inits In-App Purchase system, calling given callback on end.
 *
 *  @native
 *
 *  @param products List of products whose information will be downloaded.
 *  @param callback Callback to be called.
 */
void _init( const std::vector<ProductID> &products,
            std::function<void( void )> callback = nullptr );

/**
 *  Tries to buy given item, calling callback on finished.
 *
 *  @native
 *
 *  @param productIdentifier Identifier of product to buy.
 *  @param callback          Callback to be called. First argument will be true
 *                           if user finished the purchase,
 */
void _buyIfPossible( const ProductID productIdentifier, std::function<void( bool )> callback );

/**
 *  Returns title of buy button for product with given identifier.
 *  Title may include currency in user's expected format.
 *
 *  @native
 *
 *  @param productIdentifier Identifier of product whose buy button title will
 *                           be returned.
 *
 *  @return Title to show in buy button for product with given identifier.
 */
const std::string _buyButtonTitleForProduct( const ProductID productIdentifier );

/**
 *  Restores any previously purchased item, calling given callback on end.
 *
 *  @native
 *
 *  @param callback Callback to be called after restoring purchases. First
 *                  parameter will be `true` on success.
 */
void _restorePurchases( std::function<void( bool )> callback = nullptr );

}; // namespace IAPKit
}; // namespace MK

#endif /* _IAPKit_hpp */
