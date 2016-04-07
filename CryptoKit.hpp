//
//  CryptoKit.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef CryptoKit_hpp
#define CryptoKit_hpp

#include <string>

namespace MK {

/**
 *  `CryptoKit` namespace offers methods to encrypt and descrypt data.
 */
namespace CryptoKit {

/**
 *  Returns given content encrypted.
 *
 *  @note Credits to: http://www.cplusplus.com/forum/windows/128374/
 *
 *  @param content Content to encrypt.
 *
 *  @return Encrypted content.
 */
const std::string symmetricEncrypt( const std::string &content );

/**
 *  Returns given encrypted content decrypted.
 *
 *  @note Credits to: http://www.cplusplus.com/forum/windows/128374/
 *
 *  @param content Encrypted content.
 *
 *  @return Decrypted content.
 */
const std::string symmetricDecrypt( const std::string &content );

}; // namespace CryptoKit

}; // namespace MK

#endif /* CryptoKit_hpp */
