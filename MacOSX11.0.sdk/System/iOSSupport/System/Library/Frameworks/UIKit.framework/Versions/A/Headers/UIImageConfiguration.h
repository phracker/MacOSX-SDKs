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

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface UIImageConfiguration : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

#if __has_include(<UIKit/UITraitCollection.h>)
@property (nonatomic, nullable, readonly) UITraitCollection *traitCollection;

// inserts/applies the traitCollection to this configuration
- (instancetype)configurationWithTraitCollection:(nullable UITraitCollection *)traitCollection;
#endif

// Applies the other configuration over this configuration
// Any specified values in the other configuration will overwrite the values in this one.
// Values that are unspecified in the other configuration will leave the current configuration
// as is.
- (instancetype)configurationByApplyingConfiguration:(nullable UIImageConfiguration *)otherConfiguration;

@end



NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIImageConfiguration.h>
#endif
