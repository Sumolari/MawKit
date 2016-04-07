//
//  IAPKit.mm
//  MawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 13/03/16.
//
//

#include "../../IAPKit.hpp"
#include "../../_IAPKit.hpp"

#include <StoreKit/StoreKit.h>
#include <iostream>
#include <vector>

#include "../../Device.hpp"
#include "../../Log.hpp"
#include "../Common/CPPUtils.h"
#include "ReceiptValidator.h"
#include "cocos2d.h"

@class StoreManager;

typedef void ( ^voidManagerLambda )( StoreManager * );
typedef void ( ^voidManagerBoolLambda )( StoreManager *, bool );

@interface StoreManager : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>

/**
 *  Request managed by this manager.
 */
@property ( nonatomic, strong ) SKProductsRequest *request;

/**
 *  Callbacks to be called when request finishes.
 */
@property ( nonatomic, strong ) NSMutableArray<voidManagerLambda> *pendingCallbacks;

/**
 *  Callback to be called after a purchase.
 */
@property ( nonatomic, copy ) voidManagerBoolLambda onBuyCallback;

/**
 *  List of available products, indexed by ID.
 */
@property ( nonatomic, strong ) NSMutableDictionary<NSString *, SKProduct *> *products;

/**
 *  Whether this store manager is ready (remote request finished) or not.
 */
@property ( nonatomic, getter=isReady ) BOOL ready;

/**
 *  Whether this store manager has a pending purchase or not.
 */
@property ( nonatomic, getter=hasPendingPurchase ) BOOL purchasePending;

/**
 *  Adds given callback to the list of callbacks to be called when this manager
 *  is ready. If the manager is ready calls it immediately.
 *
 *  @param callback Callback to call.
 */
- (void)addCallback:(voidManagerLambda)callback;

/**
 *  Returns product with given identifier.
 *
 *  @param identifier Identifier of product to return.
 *
 *  @return Product with given identifier.
 */
- (SKProduct *)productWithIdentifier:(MK::IAPKit::ProductID)identifier;

/**
 *  Tries to restore purchased items calling given callback on end.
 *
 *  @param callback   Callback to be called on end.
 *                    Second parameter will be `true` if item was restored.
 */
- (void)restorePurchasesCallingOnEnd:(voidManagerBoolLambda)callback;

/**
 *  Tries to buy product with given identifier, calling given callback on end.
 *
 *  @param identifier Global identifier of product to buy.
 *  @param callback   Callback to be called on end.
 *                    Second parameter will be `true` if item was purchased.
 */
- (void)buyProductWithIdentifier:(MK::IAPKit::ProductID)identifier
                    callingOnEnd:(voidManagerBoolLambda)callback;

@end

StoreManager *storeManager;

//------------------------------------------------------------------------------
#pragma mark - StoreManager implementation
//------------------------------------------------------------------------------

@implementation StoreManager

//------------------------------------------------------------------------------
#pragma mark - Constructor
//------------------------------------------------------------------------------

- (id)init
{
	self = [super init];
	if ( self ) {
		self.request          = nil;
		self.pendingCallbacks = [NSMutableArray array];
		self.products         = [NSMutableDictionary dictionary];
		self.ready            = NO;
		self.purchasePending  = NO;
		self.onBuyCallback    = ^( id manager, bool success ) {
#pragma unused( manager )
#pragma unused( success )
		  assert( "Called onBuyCallback with no callback set" );
		};
	}
	return self;
}

//------------------------------------------------------------------------------
#pragma mark - SKProductRequestDelegate
//------------------------------------------------------------------------------

- (void)productsRequest:(SKProductsRequest *)request
     didReceiveResponse:(SKProductsResponse *)response
{
#pragma unused( request )
#pragma unused( response )
	for ( SKProduct *product in response.products ) {
		self.products[product.productIdentifier] = product;
	}

	self.ready = YES;

	while ( self.pendingCallbacks.count > 0 ) {
		voidManagerLambda lambda = self.pendingCallbacks.lastObject;
		lambda( self );
		[self.pendingCallbacks removeLastObject];
	}
}

//------------------------------------------------------------------------------
#pragma mark - SKPaymentTransactionObserver
//------------------------------------------------------------------------------

- (void)paymentQueue:(SKPaymentQueue *)queue
 updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions
{
	for ( SKPaymentTransaction *transaction in transactions ) {
		switch ( transaction.transactionState ) {
		// Call the appropriate custom method for the transaction state.
		case SKPaymentTransactionStatePurchasing:
			// [self showTransactionAsInProgress:transaction deferred:NO];
			break;
		case SKPaymentTransactionStateDeferred:
			// [self showTransactionAsInProgress:transaction deferred:YES];
			break;
		case SKPaymentTransactionStateFailed: {
			// [self failedTransaction:transaction];
			dispatch_async( dispatch_get_main_queue(), ^{
			  self.purchasePending = NO;
			  self.onBuyCallback( self, false );
			} );
			[queue finishTransaction:transaction];
			break;
		}
		case SKPaymentTransactionStatePurchased: {
			// [self completeTransaction:transaction];
			dispatch_async( dispatch_get_main_queue(), ^{
			  self.purchasePending = NO;
			  if ( [ReceiptValidator appReceiptIsValidForBundleID:nil
				                                       andVersion:nil] ) {
				  self.onBuyCallback( self, true );
			  }
			  else {
				  MK::Log::debug( "Receipt was not valid" );
			  }
			} );
			[queue finishTransaction:transaction];
			break;
		}
		case SKPaymentTransactionStateRestored: {
			// [self restoreTransaction:transaction];
			dispatch_async( dispatch_get_main_queue(), ^{
			  MK::IAPKit::unlockProduct( MK::IAPKit::productLocalIDForProductGlobalID(
			  [transaction.payment.productIdentifier UTF8String] ) );
			  self.purchasePending = NO;
			  if ( [ReceiptValidator appReceiptIsValidForBundleID:nil
				                                       andVersion:nil] ) {
				  self.onBuyCallback( self, true );
			  }
			  else {
				  MK::Log::debug( "Receipt was not valid" );
			  }
			} );
			[queue finishTransaction:transaction];
			break;
		}
		default:
			// For debugging
			NSLog( @"Unexpected transaction state %@", @( transaction.transactionState ) );
			break;
		}
	}
}

- (void)paymentQueue:(SKPaymentQueue *)queue
restoreCompletedTransactionsFailedWithError:(NSError *)error
{
#pragma unused( queue )
	MK::Log::nonCriticalCrash( "Failed to restore IAP: %s",
	                           [error localizedDescription].UTF8String );
	self.onBuyCallback( self, false );
}

//------------------------------------------------------------------------------
#pragma mark - Public methods
//------------------------------------------------------------------------------

- (void)addCallback:(voidManagerLambda)callback
{
	if ( self.isReady ) {
		callback( self );
	}
	else {
		[self.pendingCallbacks addObject:callback];
	}
}

- (SKProduct *)productWithIdentifier:(MK::IAPKit::ProductID)identifier
{
	return self.products[to_nsstring( MK::IAPKit::productGlobalIDForProductLocalID( identifier ) )];
}

- (void)restorePurchasesCallingOnEnd:(voidManagerBoolLambda)callback
{
	if ( self.hasPendingPurchase ) {
		return;
	}

	self.purchasePending = YES;
	self.onBuyCallback   = callback;

	[[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)buyProductWithIdentifier:(MK::IAPKit::ProductID)identifier
                    callingOnEnd:(voidManagerBoolLambda)callback
{
	if ( self.hasPendingPurchase ) {
		MK::Log::debug(
		"Not buying product %d because there is a pending purchase", identifier );
		return;
	}

	self.purchasePending = YES;
	self.onBuyCallback   = callback;

	SKProduct *product        = [self productWithIdentifier:identifier];
	SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:product];
	[[SKPaymentQueue defaultQueue] addPayment:payment];
}

@end

//------------------------------------------------------------------------------
#pragma mark - LE::IAP namespace
//------------------------------------------------------------------------------

namespace MK {
namespace IAPKit {

void _init( const std::vector<ProductID> &products, std::function<void( void )> callback )
{
	if ( storeManager == nil ) {
		storeManager = [[StoreManager alloc] init];

		[[SKPaymentQueue defaultQueue] addTransactionObserver:storeManager];

		NSMutableSet *set = [NSMutableSet set];

		for ( auto product : products ) {
			[set addObject:to_nsstring( MK::IAPKit::productGlobalIDForProductLocalID( product ) )];
		}

		storeManager.request = [[SKProductsRequest alloc] initWithProductIdentifiers:set];

		storeManager.request.delegate = storeManager;
		[storeManager.request start];
	}

	[storeManager addCallback:^( StoreManager *manager ) {
#pragma unused( manager )
	  if ( callback != nullptr ) {
		  callback();
	  }
	}];
}

void _restorePurchases( std::function<void( bool )> callback )
{
	[storeManager restorePurchasesCallingOnEnd:^( StoreManager *manager, bool success ) {
#pragma unused( manager )
	  if ( callback != nullptr ) {
		  callback( success );
	  }
	}];
}

void _buyIfPossible( const ProductID productIdentifier, std::function<void( bool )> callback )
{
	MK::Log::debug( "Going to buy product %d", productIdentifier );
	[storeManager
	buyProductWithIdentifier:productIdentifier
	            callingOnEnd:^( StoreManager *manager, bool success ) {
#pragma unused( manager )
		          if ( success ) {
			          MK::Log::debug( "Going to unlock product %d", productIdentifier );
			          unlockProduct( productIdentifier );
		          }
		          else {
			          MK::Log::debug( "Not unlocking product %d because "
			                          "purchase did not succeed",
			                          productIdentifier );
		          }
		          if ( callback != nullptr ) {
			          callback( success );
		          }
		        }];
}

const std::string _buyButtonTitleForProduct( const ProductID productIdentifier )
{
	if ( storeManager.isReady ) {
		SKProduct *product = [storeManager productWithIdentifier:productIdentifier];

		NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
		[numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
		[numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
		[numberFormatter setLocale:product.priceLocale];
		return std::string( [numberFormatter stringFromNumber:product.price].UTF8String );
	}
	else {
		return "";
	}
}

const bool productMetadataHasBeenRetrievedFromStore( const ProductID productIdentifier )
{
	return storeManager.isReady &&
	       storeManager.products[to_nsstring( MK::IAPKit::productGlobalIDForProductLocalID( productIdentifier ) )] !=
	       nil;
}

}; // namespace IAPKit
}; // namespace MK
