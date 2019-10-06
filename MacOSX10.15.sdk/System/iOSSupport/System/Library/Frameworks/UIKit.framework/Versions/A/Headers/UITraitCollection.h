#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITraitCollection.h>)
//
//  UITraitCollection.h
//  UIKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UITouch.h>
#import <UIKit/UIContentSizeCategory.h>

/*! A trait collection encapsulates the system traits of an interface's environment. */
NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) @interface UITraitCollection : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (BOOL)containsTraitsInCollection:(nullable UITraitCollection *)trait;

/*! Returns a trait collection by merging the traits in `traitCollections`. The last trait along any given
 axis (e.g. interface usage) will supersede any others. */
+ (UITraitCollection *)traitCollectionWithTraitsFromCollections:(NSArray<UITraitCollection *> *)traitCollections;


+ (UITraitCollection *)traitCollectionWithUserInterfaceIdiom:(UIUserInterfaceIdiom)idiom;
@property (nonatomic, readonly) UIUserInterfaceIdiom userInterfaceIdiom; // unspecified: UIUserInterfaceIdiomUnspecified

+ (UITraitCollection *)traitCollectionWithUserInterfaceStyle:(UIUserInterfaceStyle)userInterfaceStyle API_AVAILABLE(tvos(10.0)) API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIUserInterfaceStyle userInterfaceStyle API_AVAILABLE(tvos(10.0)) API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos); // unspecified: UIUserInterfaceStyleUnspecified

+ (UITraitCollection *)traitCollectionWithLayoutDirection:(UITraitEnvironmentLayoutDirection)layoutDirection API_AVAILABLE(ios(10.0));
@property (nonatomic, readonly) UITraitEnvironmentLayoutDirection layoutDirection API_AVAILABLE(ios(10.0)); // unspecified: UITraitEnvironmentLayoutDirectionUnspecified

+ (UITraitCollection *)traitCollectionWithDisplayScale:(CGFloat)scale;
@property (nonatomic, readonly) CGFloat displayScale; // unspecified: 0.0

+ (UITraitCollection *)traitCollectionWithHorizontalSizeClass:(UIUserInterfaceSizeClass)horizontalSizeClass;
@property (nonatomic, readonly) UIUserInterfaceSizeClass horizontalSizeClass; // unspecified: UIUserInterfaceSizeClassUnspecified

+ (UITraitCollection *)traitCollectionWithVerticalSizeClass:(UIUserInterfaceSizeClass)verticalSizeClass;
@property (nonatomic, readonly) UIUserInterfaceSizeClass verticalSizeClass; // unspecified: UIUserInterfaceSizeClassUnspecified

+ (UITraitCollection *)traitCollectionWithForceTouchCapability:(UIForceTouchCapability)capability API_AVAILABLE(ios(9.0));
@property (nonatomic, readonly) UIForceTouchCapability forceTouchCapability API_AVAILABLE(ios(9.0)); // unspecified: UIForceTouchCapabilityUnknown

+ (UITraitCollection *)traitCollectionWithPreferredContentSizeCategory:(UIContentSizeCategory)preferredContentSizeCategory API_AVAILABLE(ios(10.0));
@property (nonatomic, copy, readonly) UIContentSizeCategory preferredContentSizeCategory API_AVAILABLE(ios(10.0)); // unspecified: UIContentSizeCategoryUnspecified

+ (UITraitCollection *)traitCollectionWithDisplayGamut:(UIDisplayGamut)displayGamut API_AVAILABLE(ios(10.0));
@property (nonatomic, readonly) UIDisplayGamut displayGamut API_AVAILABLE(ios(10.0)); // unspecified: UIDisplayGamutUnspecified

+ (UITraitCollection *)traitCollectionWithAccessibilityContrast:(UIAccessibilityContrast)accessibilityContrast API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIAccessibilityContrast accessibilityContrast API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos); // unspecified: UIAccessibilityContrastUnspecified

+ (UITraitCollection *)traitCollectionWithUserInterfaceLevel:(UIUserInterfaceLevel)userInterfaceLevel API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIUserInterfaceLevel userInterfaceLevel API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos); // unspecified: UIUserInterfaceLevelUnspecified

+ (UITraitCollection *)traitCollectionWithLegibilityWeight:(UILegibilityWeight)legibilityWeight API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0));
@property (nonatomic, readonly) UILegibilityWeight legibilityWeight API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)); // unspecified: UILegibilityWeightUnspecified

@end

/*! Trait environments expose a trait collection that describes their environment. */
@protocol UITraitEnvironment <NSObject>
@property (nonatomic, readonly) UITraitCollection *traitCollection API_AVAILABLE(ios(8.0));

/*! To be overridden as needed to provide custom behavior when the environment's traits change. */
- (void)traitCollectionDidChange:(nullable UITraitCollection *)previousTraitCollection API_AVAILABLE(ios(8.0));
@end


@interface UITraitCollection (CurrentTraitCollection)

/* The current trait collection, used when resolving the appearance of dynamic UIColors and similar objects.
 * This is a thread-local property, so it may be changed on non-main threads without affecting the main thread.
 */
@property (class, nonatomic, strong) UITraitCollection *currentTraitCollection API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/* Sets `UITraitCollection.currentTraitCollection` to this trait collection, performs the given actions,
 * then restores `UITraitCollection.currentTraitCollection` to its original value.
 * Just like `currentTraitCollection`, this only affects the current thread, and may be used on non-main threads
 * without affecting the main thread.
 */
- (void)performAsCurrentTraitCollection:(void (NS_NOESCAPE ^)(void))actions API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

@end


@interface UITraitCollection (DynamicAppearance)

/* Return whether this trait collection, compared to a different trait collection, could show a different appearance
 * for dynamic colors that are provided by UIKit or are in an asset catalog.
 * If you need to be aware of when dynamic colors might change, override `traitCollectionDidChange` in your view or view controller,
 * and use this method to compare `self.traitCollection` with `previousTraitCollection`.
 *
 * Currently, a change in any of these traits could affect dynamic colors:
 *    userInterfaceIdiom, userInterfaceStyle, displayGamut, accessibilityContrast, userInterfaceLevel
 * and more could be added in the future.
 */
- (BOOL)hasDifferentColorAppearanceComparedToTraitCollection:(nullable UITraitCollection *)traitCollection API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

@end


@class UIImageConfiguration;

@interface UITraitCollection (ImageConfiguration)

/*
 * Returns an image configuration compatible with this trait collection.
 */
@property (nonatomic, strong, readonly) UIImageConfiguration *imageConfiguration API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0));

@end


NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITraitCollection.h>
#endif
