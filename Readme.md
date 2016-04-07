# MawKit

**MawKit** is a library built on top of Cocos2d-x offering useful cross-platform utilities to implement platform-specific features like *leaderboards*, *achievements*, or *in-app purchases* quickly.

## Main features

- **Leaderboards and achievements:** Game Center (iOS, OS X) / Google Play Games (Android).
- **In-app purchases:** App Store (iOS, OS X), Google Play (Android).
- **Ads:** AdMob (iOS, Android, not supported on OS X).
- **Analytics:** Fabric (iOS, Android, OS X) and MixPanel (iOS, Android).
- **Mathematical utilities:** ranges, random number generator.

## Installation

### Requirements

- **CocoaPods** (iOS).

### iOS / OS X

1. Run `pod init` in `proj.ios_mac` folder to create a `Podfile`.
1. Add the following dependencies for **iOS**:
  - `pod 'SecureNSUserDefaults'`
  - `pod 'Fabric'                # Fabric`
  - `pod 'Crashlytics'           # Fabric`
  - `pod 'FBSDKCoreKit'          # Facebook`
  - `pod 'FBSDKShareKit'         # Facebook`
  - `pod 'FBSDKShareKit'         # Facebook`
  - `pod 'Bolts'                 # Facebook`
  - `pod 'Google-Mobile-Ads-SDK' # AdMob`
  - `pod 'Mixpanel'              # MixPanel `
1. Add the following dependencies for **OS X**:
  - `pod 'SecureNSUserDefaults'`
  - `pod 'Fabric'                # Fabric`
  - `pod 'Crashlytics'           # Fabric`
1. Set up and fix **Fabric** for iOS and OS X. This is required as `Fabric.framework` is different for iOS and OS X and Fabric's app does not support multiplatform targets by default. Fix is as easy as getting both versions and storing them at different paths. This can be done with the two following steps:
  1. Follow **Fabric** instructions to set up Fabric for **iOS** target. When finished you'll have a `Fabric.framework` folder inside `proj.ios_mac`. You'll have to move it to `proj.ios_mac/iOS` subfolder and update Xcode project to reflect the change.
  1. Follow **Fabric** instructions again to set up Fabric for **OS X** target. When finished you'll have a `Fabric.framework` folder inside `proj.ios_mac`. You'll have to move it to `proj.ios_mac/osx` subfolder and update Xcode project to reflect the change. 
1. Set up **MixPanel** for iOS (MixPanel is not supported on OS X):
  1. Open `proj.ios_mac/ios/AppDelegate.mm` and add in the header `#import "Mixpanel.h"` to import MixPanel.
  1. Open `proj.ios_mac/ios/AppDelegate.mm` and add in the header `#define MIXPANEL_TOKEN @"YOUR_MIXPANEL_TOKEN_HERE"` to set up MixPanel's token.
  1. Open `proj.ios_mac/ios/AppDelegate.mm` and add this line to `- (BOOL)application:didFinishLaunchingWithOptions:` method:  `[Mixpanel sharedInstanceWithToken:MIXPANEL_TOKEN];` to init MixPanel analytics on startup.
1. To support **Game Center** on **iOS**, convert `_window` ivar into a property in `proj.ios_mac/ios/AppDelegate.h`: `@property ( nonatomic, strong ) UIWindow *window;` (nothing is required on OS X).

## Usage

Everything defined and implemented by **MawKit** can be found on `MK` namespace.

### GameKit

### in-App purchases

### KVDatabase
