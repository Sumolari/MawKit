//
//  CryptoKit.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#include "CryptoKit.hpp"
#include "Device.hpp"

namespace MK {

namespace CryptoKit {

const std::string symmetricEncrypt( const std::string &content )
{
	std::string encrypted = std::string( content );
	// Encryption key should be at least as long as message to be encrypted.
	std::string key = MK::Device::UUID();
	while ( key.size() < encrypted.size() ) {
		key += MK::Device::UUID();
	}

	for ( int i = 0; i < encrypted.size(); i++ ) {
		encrypted[i] ^= key[i];
	}

	return encrypted;
}

const std::string symmetricDecrypt( const std::string &content )
{
	return symmetricEncrypt( content );
}

}; // namespace CryptoKit

}; // namespace MK
