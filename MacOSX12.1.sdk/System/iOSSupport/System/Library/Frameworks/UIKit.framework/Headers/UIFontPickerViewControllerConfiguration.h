#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFontPickerViewControllerConfiguration.h>)
//
//  UIFontPickerViewControllerConfiguration.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIFontDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIFontPickerViewControllerConfiguration : NSObject <NSCopying>

// Indicates if individual faces can be selected instead of just families.
@property (nonatomic) BOOL includeFaces;

@property (nonatomic) BOOL displayUsingSystemFont; // Indicates if all fonts should be shown in the system font instead of themselves.

// Filter to fonts with just the specified traits.
@property (nonatomic) UIFontDescriptorSymbolicTraits filteredTraits;

// Filter fonts based on languages supported using a predicate. The predicate is evaluated against an array of string language identifiers (conforming to UTS #35) supported by the font.
@property (nullable, copy, nonatomic) NSPredicate *filteredLanguagesPredicate;

// Generate a filter predicate to filter to fonts that support one of the specified language identifiers (conforming to UTS #35).
+ (nullable NSPredicate *)filterPredicateForFilteredLanguages:(NSArray<NSString *> *)filteredLanguages;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIFontPickerViewControllerConfiguration.h>
#endif
