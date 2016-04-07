//
//  IAPKit.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef IAPKit_hpp
#define IAPKit_hpp

#include <functional>
#include <string>
#include <vector>

namespace MK {

/**
 *  `IAPKit` namespace features methods to handle in-app purchases.
 */
namespace IAPKit {

/// Enumeration defining available in-app purchases. Must be declared in your
/// game.
/// @example enum class ProductID: unsigned long long { COINS = 0 };
enum class ProductID : unsigned long long;

/**
 *  Inits In-App Purchase system, calling given callback on end.
 *
 *  @param products List of products whose information will be downloaded.
 *  @param callback Callback to be called.
 */
void init( const std::vector<ProductID> &products,
           std::function<void( void )> callback = nullptr );

/**
 *  Returns string identifier (global ID) of given in-app purchase.
 *
 *  @note Your game should implement this method.
 *
 *  @param localID LocalID (enum class item) of in-app purchase.
 *
 *  @return String identifier (global ID) of given in-app purchase.
 */
const std::string productGlobalIDForProductLocalID( const ProductID localID );

/**
 *  Returns enum class item (local ID) of in-app purchase with given string
 *  identifier (global ID).
 *
 *  @note Your game should implement this method.
 *
 *  @param globalID Global ID (string) of in-app purchase.
 *
 *  @return Enum class item (local ID) of given in-app purchase.
 */
const ProductID productLocalIDForProductGlobalID( const std::string &globalID );

/**
 *  Unlocks content locked by product with given identifier.
 *
 *  @note Your game should implement this method.
 *
 *  @example unlockProduct(LE::IAP::ProductID::BAG_OF_COINS); // Gives user 20k
 *
 *  @param productIdentifier Identifier of product to unlock.
 */
void unlockProduct( const ProductID productIdentifier );

/**
 *  Tries to buy given item, calling callback on finished.
 *
 *  @param productIdentifier Identifier of product to buy.
 *  @param callback          Callback to be called. First argument will be true
 *                           if user finished the purchase,
 */
void buyIfPossible( const ProductID productIdentifier, std::function<void( bool )> callback );

/**
 *  Returns title of buy button for product with given identifier.
 *  Title may include currency in user's expected format.
 *
 *  @param productIdentifier Identifier of product whose buy button title will
 *                           be returned.
 *
 *  @return Title to show in buy button for product with given identifier.
 */
const std::string buyButtonTitleForProduct( const ProductID productIdentifier );

/**
 *  Returns whether given product has been found on store and can be bought
 *  or not.
 *
 *  @note This method does not check whether user already bought the product or
 *        not.
 *
 *  @native
 *
 *  @param productIdentifier Identifier of product to check.
 *
 *  @return `true` if product has been retrieved from store and can be bought.
 */
const bool productMetadataHasBeenRetrievedFromStore( const ProductID productIdentifier );

/**
 *  Restores any previously purchased item, calling given callback on end.
 *
 *  @param callback Callback to be called after restoring purchases. First
 *                  parameter will be `true` on success.
 */
void restorePurchases( std::function<void( bool )> callback = nullptr );

/**
 *  Returns whether IAPKit is enabled or not.
 *
 *  @return `true` if IAPKit is enabled.
 */
const bool enabled();

}; // namespace IAPKit
}; // namespace MK

#endif /* IAPKit_hpp */
