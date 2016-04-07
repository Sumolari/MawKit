//
//  IAPKit.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "IAPKit.hpp"
#include "_IAPKit.hpp"

#include "Features.hpp"
#include "KVDatabase.hpp"

#include "../Constants/features.h"

#include "AppDelegate.h"

#include <functional>

namespace MK {
namespace IAPKit {

void init( const std::vector<ProductID> &products, std::function<void( void )> callback )
{
	if ( !enabled() ) return;

	_init( products, callback );
}

void buyIfPossible( const ProductID productIdentifier, std::function<void( bool )> callback )
{
	if ( !enabled() ) {
		callback( false );
		return;
	}

	_buyIfPossible( productIdentifier, callback );
}

const std::string buyButtonTitleForProduct( const ProductID productIdentifier )
{
	if ( !enabled() ) return "";

	return _buyButtonTitleForProduct( productIdentifier );
}

void restorePurchases( std::function<void( bool )> callback )
{
	if ( !enabled() ) {
		callback( false );
		return;
	}

	_restorePurchases( callback );
}

const bool enabled()
{
	return MK::Features::IAPKit;
}

}; // namespace IAPKit
}; // namespace MK
