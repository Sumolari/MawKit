//
//  Facebook.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 18/02/16.
//
//

#ifndef Facebook_hpp
#define Facebook_hpp

#include <string>

namespace MK {

/**
 *  `Facebook` namespace features constants and methods used to interact
 *  with Facebook API.
 */
namespace Facebook {

/**
 *  Shows Facebook invite modal view controller with given link and thumbnail
 *  URL. If no parameter is given default invitation will be sent.
 *
 *  @ios
 *  @native
 *
 *  @param linkURL      URL to be opened after app is installed.
 *  @param thumbnailURL URL of thumbnail to be attached.
 */
void sendInvitation( const std::string &linkURL, const std::string &thumbnailURL );

/**
 *  Returns whether Facebook integration is enabled or not.
 *
 *  @return `true` is Facebook integration is enabled.
 */
const bool enabled();

}; // namespace Facebook
}; // namespace LE

#endif /* Facebook_hpp */
