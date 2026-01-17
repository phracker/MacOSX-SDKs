#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIImageConfiguration.h>)
//
//  UIImageConfiguration.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

#if __has_include(<UIKit/UITraitCollection.h>)
@class UITraitCollection;
#endif

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_SENDABLE
@interface UIImageConfiguration : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

#if __has_include(<UIKit/UITraitCollection.h>)
// The configuration's trait collection.
@property (nonatomic, nullable, readonly) UITraitCollection *traitCollection API_UNAVAILABLE(watchos);

// inserts/applies the traitCollection to this configuration
- (instancetype)configurationWithTraitCollection:(nullable UITraitCollection *)traitCollection API_UNAVAILABLE(watchos);

// Creates a new configuration object with the specified trait collection.
+ (instancetype)configurationWithTraitCollection:(nullable UITraitCollection *)traitCollection API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
#endif

// The configuration's locale. If nil/unspecified, the image will be looked up using the current locale.
@property (nonatomic, nullable, readonly) NSLocale *locale API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));

// inserts/applies the locale to this configuration
- (instancetype)configurationWithLocale:(nullable NSLocale *)locale API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));

// Creates a new configuration object with the specified locale.
+ (instancetype)configurationWithLocale:(nullable NSLocale *)locale API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0));

// Applies the other configuration over this configuration
// Any specified values in the other configuration will overwrite the values in this one.
// Values that are unspecified in the other configuration will leave the current configuration
// as is.
- (instancetype)configurationByApplyingConfiguration:(nullable UIImageConfiguration *)otherConfiguration;

@end



NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIImageConfiguration.h>
#endif
