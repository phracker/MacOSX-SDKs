#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIImageSymbolConfiguration.h>)
//
//  UIImageSymbolConfiguration.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIFont.h>
#import <UIKit/UIFontDescriptor.h>
#import <UIKit/UIImage.h>
#import <UIKit/UIImageConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

// -- symbol images size
typedef NS_ENUM(NSInteger, UIImageSymbolScale) {
    UIImageSymbolScaleDefault = -1,      // use the system default size
    UIImageSymbolScaleUnspecified = 0,   // allow the system to pick a size based on the context
    UIImageSymbolScaleSmall = 1,
    UIImageSymbolScaleMedium,
    UIImageSymbolScaleLarge,
} API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

// -- symbol image weights
// only regular is supported by now, but you can specify any weight
// you need for future implementation.
typedef NS_ENUM(NSInteger, UIImageSymbolWeight) {
    UIImageSymbolWeightUnspecified = 0,
    UIImageSymbolWeightUltraLight = 1,
    UIImageSymbolWeightThin,
    UIImageSymbolWeightLight,
    UIImageSymbolWeightRegular,
    UIImageSymbolWeightMedium,
    UIImageSymbolWeightSemibold,
    UIImageSymbolWeightBold,
    UIImageSymbolWeightHeavy,
    UIImageSymbolWeightBlack
} API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));

UIKIT_EXTERN UIFontWeight UIFontWeightForImageSymbolWeight(UIImageSymbolWeight symbolWeight) API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));
UIKIT_EXTERN UIImageSymbolWeight UIImageSymbolWeightForFontWeight(UIFontWeight fontWeight) API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0));


UIKIT_EXTERN API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0)) 
@interface UIImageSymbolConfiguration : UIImageConfiguration

// everything is "unspecified". This is essentially the same as nil but's more explicit.
@property (class, nonatomic, readonly) UIImageSymbolConfiguration *unspecifiedConfiguration;

// just change the scale on the configuration
+ (instancetype)configurationWithScale:(UIImageSymbolScale)scale;

// Fixed point size configurations
+ (instancetype)configurationWithPointSize:(CGFloat)pointSize;
+ (instancetype)configurationWithWeight:(UIImageSymbolWeight)weight;
+ (instancetype)configurationWithPointSize:(CGFloat)pointSize weight:(UIImageSymbolWeight)weight;
+ (instancetype)configurationWithPointSize:(CGFloat)pointSize weight:(UIImageSymbolWeight)weight scale:(UIImageSymbolScale)scale;

// Dynamic type size configurations
+ (instancetype)configurationWithTextStyle:(UIFontTextStyle)textStyle;
+ (instancetype)configurationWithTextStyle:(UIFontTextStyle)textStyle scale:(UIImageSymbolScale)scale;

// Derive a configuration from a font
+ (instancetype)configurationWithFont:(UIFont *)font; // Adjusts for Dynamic Type. Use UIFontMetrics to get automatic adjustment with a custom font.
+ (instancetype)configurationWithFont:(UIFont *)font scale:(UIImageSymbolScale)scale; // Adjusts for Dynamic Type. Use UIFontMetrics to get automatic adjustment with a custom font.

// Removes attributes from the configuration if they are set
- (instancetype)configurationWithoutTextStyle;
- (instancetype)configurationWithoutScale;
- (instancetype)configurationWithoutWeight;
- (instancetype)configurationWithoutPointSizeAndWeight;

// checks if the other configuration is equal to this one.
// the values have to match exactly. If you only want to check "specified"
// values, use `isEquivalentToConfiguration:`.
- (BOOL)isEqualToConfiguration:(nullable UIImageSymbolConfiguration *)otherConfiguration;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIImageSymbolConfiguration.h>
#endif
