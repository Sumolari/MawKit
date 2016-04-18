![MawKit](https://cloud.githubusercontent.com/assets/779767/14524930/472cc86c-023b-11e6-8794-f28ab8bc8966.png "MawKit")

**MawKit** is a library built on top of Cocos2d-x offering useful cross-platform utilities to implement platform-specific features like *leaderboards*, *achievements*, or *in-app purchases* quickly.

## Main features

- **Leaderboards and achievements:** Game Center (iOS, OS X) / Google Play Games (Android).
- **In-app purchases:** App Store (iOS, OS X), Google Play (Android).
- **Ads:** AdMob and AdColony (iOS, Android, not supported on OS X).
- **Analytics:** Fabric (iOS, Android, OS X) and MixPanel (iOS).
- **Mathematical utilities:** ranges, random number generator.

## Installation

### Requirements

- **CocoaPods** (iOS).

### Android

To do...

### iOS / OS X

1. Run `pod init` in `proj.ios_mac` folder to create a `Podfile`. [[Gif]](https://cloud.githubusercontent.com/assets/779767/14518514/9823d7c4-0218-11e6-9015-7370af4ca264.gif)

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
1. Open Xcode project and locate `Build Settings` tab of **iOS** target: [[Gif]](https://cloud.githubusercontent.com/assets/779767/14518515/98274c06-0218-11e6-924d-1bb153b7522a.gif)
  1. Look for `GCC_PREPROCESSOR_DEFINITIONS` and prepend `$(inherited)` for release and debug build.
  1. Look for `LIBRARY_SEARCH_PATHS`, prepend `$(inherited)` and append `$(PROJECT_DIR)/../Classes/MawKit/Apple/iOS` for release and debug build.
  1. Look for `OTHER_LDFLAGS` and prepend `$(inherited)` for release and debug build.
1. Open Xcode project and locate `Build Settings` tab of **OS X** target:
  1. Look for `GCC_PREPROCESSOR_DEFINITIONS` and prepend `$(inherited)` for release and debug build.
  1. Look for `LIBRARY_SEARCH_PATHS` and prepend `$(inherited)` for release and debug build.
  1. Look for `OTHER_LDFLAGS` and prepend `$(inherited)` for release and debug build.
1. Run `pod install` to install pods.
1. Add `Game Center` and `In-App Purchase` capabilities on both iOS and OS X. [[Gif]](https://cloud.githubusercontent.com/assets/779767/14518513/9822364e-0218-11e6-9256-38197db48101.gif)
1. Import `MawKit` folder in Xcode.
1. Remove `MawKit/Android` and `MawKit/Example` folders from Xcode project. [[Gif]](https://cloud.githubusercontent.com/assets/779767/14518512/9821d3f2-0218-11e6-8839-fc8ade992f80.gif)
1. Check files `.mm` and `.a` files in `MawKit/Apple/iOS` so they are only build on iOS target.
1. Check files `.mm` files in `MawKit/Apple/OS X` so they are only build on OS X target.
1. Add `Examples/ios_ids.plist` and `Examples/mac_ids.plist` to `Resources` folder. Don't forget to add it in Xcode so it gets bundled. [[Gif]](https://cloud.githubusercontent.com/assets/779767/14518517/982cc0aa-0218-11e6-9d26-00ae65c6bd1a.gif)
1. Add `Examples/MKConstants.h` and `Examples/MKUtils.cpp` to project. `MKUtils.cpp` should be added to iOS and OS X targets. [[Gif]](https://cloud.githubusercontent.com/assets/779767/14518516/982c80e0-0218-11e6-86c2-31be493e9ad5.gif)
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

To do...

### in-App purchases

To do...

### KVDatabase

To do...

### Mathematical utilities

#### Random

![first-use](https://cloud.githubusercontent.com/assets/779767/14518510/97e3b766-0218-11e6-8013-732ee304a835.gif)

[[Random loop Gif]](https://cloud.githubusercontent.com/assets/779767/14518511/980ee828-0218-11e6-8b55-fef2da3ff5ac.gif)

#### Ranges

```
auto range = MK::Range<int>(10, 20);
MK::Log::debug(
	"Random number in [%d, %d] range: %d",
	range.first(),
	range.last(), 
	range.randomInteger()
);
```
