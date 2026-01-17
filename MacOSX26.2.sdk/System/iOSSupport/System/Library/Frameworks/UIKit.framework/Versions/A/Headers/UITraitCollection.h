#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITraitCollection.h>)
//
//  UITraitCollection.h
//  UIKit
//
//  Copyright (c) 2013-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UITrait.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UITouch.h>
#import <UIKit/UIContentSizeCategory.h>
#import <UIKit/UISceneDefinitions.h>
#import <UIKit/UITraitListEnvironment.h>
#import <UIKit/UITabAccessory.h>
#import <UIKit/UISplitViewControllerLayoutEnvironment.h>

/*! A trait collection encapsulates the system traits of an interface's environment. */
NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos) NS_SWIFT_SENDABLE
@interface UITraitCollection : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// This deprecated method considers system traits only.
- (BOOL)containsTraitsInCollection:(nullable UITraitCollection *)trait API_DEPRECATED("Compare values for specific traits in the trait collections instead", ios(8.0, 17.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

// This deprecated method merges system traits only. The value of custom traits in the returned trait collection will be equal to the value of those custom traits in the first trait collection in the array.
#if __swift__
+ (UITraitCollection *)traitCollectionWithTraitsFromCollections:(NSArray<UITraitCollection *> *)traitCollections API_DEPRECATED("Use UITraitCollection.init(mutations:) and UITraitCollection.modifyingTraits(_:) to create and modify trait collections", ios(8.0, 17.0), visionos(1.0, 1.0));
#else
+ (UITraitCollection *)traitCollectionWithTraitsFromCollections:(NSArray<UITraitCollection *> *)traitCollections API_DEPRECATED("Use +[UITraitCollection traitCollectionWithTraits:] and -[UITraitCollection traitCollectionByModifyingTraits:] to create and modify trait collections", ios(8.0, 17.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
#endif

+ (UITraitCollection *)traitCollectionWithUserInterfaceIdiom:(UIUserInterfaceIdiom)idiom;
@property (nonatomic, readonly) UIUserInterfaceIdiom userInterfaceIdiom; // unspecified: UIUserInterfaceIdiomUnspecified

+ (UITraitCollection *)traitCollectionWithUserInterfaceStyle:(UIUserInterfaceStyle)userInterfaceStyle API_AVAILABLE(tvos(10.0)) API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIUserInterfaceStyle userInterfaceStyle API_AVAILABLE(tvos(10.0)) API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos); // unspecified: UIUserInterfaceStyleUnspecified

+ (UITraitCollection *)traitCollectionWithLayoutDirection:(UITraitEnvironmentLayoutDirection)layoutDirection API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UITraitEnvironmentLayoutDirection layoutDirection API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos); // unspecified: UITraitEnvironmentLayoutDirectionUnspecified

+ (UITraitCollection *)traitCollectionWithDisplayScale:(CGFloat)scale;
@property (nonatomic, readonly) CGFloat displayScale; // unspecified: 0.0

+ (UITraitCollection *)traitCollectionWithHorizontalSizeClass:(UIUserInterfaceSizeClass)horizontalSizeClass;
@property (nonatomic, readonly) UIUserInterfaceSizeClass horizontalSizeClass; // unspecified: UIUserInterfaceSizeClassUnspecified

+ (UITraitCollection *)traitCollectionWithVerticalSizeClass:(UIUserInterfaceSizeClass)verticalSizeClass;
@property (nonatomic, readonly) UIUserInterfaceSizeClass verticalSizeClass; // unspecified: UIUserInterfaceSizeClassUnspecified

+ (UITraitCollection *)traitCollectionWithForceTouchCapability:(UIForceTouchCapability)capability API_AVAILABLE(ios(9.0));
@property (nonatomic, readonly) UIForceTouchCapability forceTouchCapability API_AVAILABLE(ios(9.0)); // unspecified: UIForceTouchCapabilityUnknown

+ (UITraitCollection *)traitCollectionWithPreferredContentSizeCategory:(UIContentSizeCategory)preferredContentSizeCategory API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, copy, readonly) UIContentSizeCategory preferredContentSizeCategory API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos); // unspecified: UIContentSizeCategoryUnspecified

+ (UITraitCollection *)traitCollectionWithDisplayGamut:(UIDisplayGamut)displayGamut API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIDisplayGamut displayGamut API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos); // unspecified: UIDisplayGamutUnspecified

+ (UITraitCollection *)traitCollectionWithAccessibilityContrast:(UIAccessibilityContrast)accessibilityContrast API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIAccessibilityContrast accessibilityContrast API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);// unspecified: UIAccessibilityContrastUnspecified

+ (UITraitCollection *)traitCollectionWithUserInterfaceLevel:(UIUserInterfaceLevel)userInterfaceLevel API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIUserInterfaceLevel userInterfaceLevel API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos); // unspecified: UIUserInterfaceLevelUnspecified

+ (UITraitCollection *)traitCollectionWithLegibilityWeight:(UILegibilityWeight)legibilityWeight API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UILegibilityWeight legibilityWeight API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos); // unspecified: UILegibilityWeightUnspecified

/* This trait indicates whether the UI should have an 'active' appearance.
 * On macOS, this varies based on window activation state.
 * On other platforms, this is always .active.
 */
+ (UITraitCollection *)traitCollectionWithActiveAppearance:(UIUserInterfaceActiveAppearance)userInterfaceActiveAppearance API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UIUserInterfaceActiveAppearance activeAppearance API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);  // unspecified: UIUserInterfaceActiveAppearanceUnspecified

+ (UITraitCollection *)traitCollectionWithToolbarItemPresentationSize:(UINSToolbarItemPresentationSize)toolbarItemPresentationSize API_AVAILABLE(macCatalyst(16.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) UINSToolbarItemPresentationSize toolbarItemPresentationSize API_AVAILABLE(macCatalyst(16.0)) API_UNAVAILABLE(watchos);

/// Construct a new trait collection with the given image content dynamic range.
+ (UITraitCollection *)traitCollectionWithImageDynamicRange:(UIImageDynamicRange)imageDynamicRange API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// The imageDynamicRange determines how HDR images will render in the given trait environment. SDR images are unaffected.
@property (nonatomic, readonly) UIImageDynamicRange imageDynamicRange API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

+ (UITraitCollection *)traitCollectionWithTypesettingLanguage:(NSString *)language API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@property (nonatomic, readonly) NSString *typesettingLanguage API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Construct a new trait collection with the given scene capture state.
+ (UITraitCollection *)traitCollectionWithSceneCaptureState:(UISceneCaptureState)sceneCaptureState API_AVAILABLE(ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Scene capture state represents whether a scene is currently being mirrored or recorded.
@property (nonatomic, readonly) UISceneCaptureState sceneCaptureState API_AVAILABLE(ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Construct a new trait collection with the given `listEnvironment`.
+ (UITraitCollection *)traitCollectionWithListEnvironment:(UIListEnvironment)listEnvironment API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// The list environment represents whether a given trait collection is from a view in a UITableView or a UICollectionView list section.
@property (nonatomic, readonly) UIListEnvironment listEnvironment API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// Constructs a new trait collection with the given `tabAccessoryEnvironment`.
+ (UITraitCollection *)traitCollectionWithTabAccessoryEnvironment:(UITabAccessoryEnvironment)tabAccessoryEnvironment API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, tvos, watchos);

/// The tab accessory environment represents whether a given trait collection is from a view in a `UITabAccessory` content view.
@property (nonatomic, readonly) UITabAccessoryEnvironment tabAccessoryEnvironment API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, tvos, watchos);

/// The split view controller layout environment represents whether an ancestor split view controller is expanded or collapsed.
@property (nonatomic, readonly) UISplitViewControllerLayoutEnvironment splitViewControllerLayoutEnvironment API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// If HDR headroom should be used for the current UI configuration. Headroom usage is disabled in certain UI configurations, such as when all an application's windows are in the background.
@property (nonatomic, readonly) UIHDRHeadroomUsageLimit hdrHeadroomUsageLimit API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
+ (UITraitCollection *)traitCollectionWithHDRHeadroomUsageLimit:(UIHDRHeadroomUsageLimit)hdrHeadroomUsageLimit API_AVAILABLE(ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

+ (UITraitCollection *)traitCollectionWithResolvesNaturalAlignmentWithBaseWritingDirection:(BOOL)resolvesNaturalAlignmentWithBaseWritingDirection API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Specifies the behavior for resolving ``NSTextAlignment.natural`` to the visual alignment.
///
/// When set to ``true``, the resolved visual alignment is determined by the resolved base writing direction; otherwise, it is using the user’s preferred language.
@property (nonatomic, readonly) BOOL resolvesNaturalAlignmentWithBaseWritingDirection API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

@end


API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIMutableTraits <NSObject>

- (void)setCGFloatValue:(CGFloat)value forTrait:(UICGFloatTrait)trait;
- (CGFloat)valueForCGFloatTrait:(UICGFloatTrait)trait;

- (void)setNSIntegerValue:(NSInteger)value forTrait:(UINSIntegerTrait)trait;
- (NSInteger)valueForNSIntegerTrait:(UINSIntegerTrait)trait;

- (void)setObject:(nullable id<NSObject>)object forTrait:(UIObjectTrait)trait;
- (nullable __kindof id<NSObject>)objectForTrait:(UIObjectTrait)trait;

@property (nonatomic) UIUserInterfaceIdiom userInterfaceIdiom;
@property (nonatomic) UIUserInterfaceStyle userInterfaceStyle;
@property (nonatomic) UITraitEnvironmentLayoutDirection layoutDirection;
@property (nonatomic) CGFloat displayScale;
@property (nonatomic) UIUserInterfaceSizeClass horizontalSizeClass;
@property (nonatomic) UIUserInterfaceSizeClass verticalSizeClass;
@property (nonatomic) UIForceTouchCapability forceTouchCapability;
@property (nonatomic, copy) UIContentSizeCategory preferredContentSizeCategory;
@property (nonatomic) UIDisplayGamut displayGamut;
@property (nonatomic) UIAccessibilityContrast accessibilityContrast API_UNAVAILABLE(watchos);
@property (nonatomic) UIUserInterfaceLevel userInterfaceLevel API_UNAVAILABLE(tvos, watchos);
@property (nonatomic) UILegibilityWeight legibilityWeight;
@property (nonatomic) UIUserInterfaceActiveAppearance activeAppearance;
@property (nonatomic) UINSToolbarItemPresentationSize toolbarItemPresentationSize API_AVAILABLE(macCatalyst(17.0));
@property (nonatomic) UIImageDynamicRange imageDynamicRange API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);
@property (nonatomic) UISceneCaptureState sceneCaptureState API_AVAILABLE(ios(17.0), tvos(17.0), visionos(1.0));
@property (nonatomic, copy) NSString *typesettingLanguage;
@property (nonatomic) UIListEnvironment listEnvironment API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);
@property (nonatomic) UITabAccessoryEnvironment tabAccessoryEnvironment API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, tvos, watchos);
@property (nonatomic) UISplitViewControllerLayoutEnvironment splitViewControllerLayoutEnvironment API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);
@property (nonatomic) BOOL resolvesNaturalAlignmentWithBaseWritingDirection API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);
@end

typedef void (^UITraitMutations)(id<UIMutableTraits> mutableTraits) API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface UITraitCollection ()

+ (UITraitCollection *)traitCollectionWithTraits:(NS_NOESCAPE UITraitMutations)mutations API_UNAVAILABLE(watchos);
- (UITraitCollection *)traitCollectionByModifyingTraits:(NS_NOESCAPE UITraitMutations)mutations API_UNAVAILABLE(watchos);

+ (UITraitCollection *)traitCollectionWithCGFloatValue:(CGFloat)value forTrait:(UICGFloatTrait)trait API_UNAVAILABLE(watchos);
- (UITraitCollection *)traitCollectionByReplacingCGFloatValue:(CGFloat)value forTrait:(UICGFloatTrait)trait API_UNAVAILABLE(watchos);
- (CGFloat)valueForCGFloatTrait:(UICGFloatTrait)trait API_UNAVAILABLE(watchos);

+ (UITraitCollection *)traitCollectionWithNSIntegerValue:(NSInteger)value forTrait:(UINSIntegerTrait)trait API_UNAVAILABLE(watchos);
- (UITraitCollection *)traitCollectionByReplacingNSIntegerValue:(NSInteger)value forTrait:(UINSIntegerTrait)trait API_UNAVAILABLE(watchos);
- (NSInteger)valueForNSIntegerTrait:(UINSIntegerTrait)trait API_UNAVAILABLE(watchos);

+ (UITraitCollection *)traitCollectionWithObject:(nullable id<NSObject>)object forTrait:(UIObjectTrait)trait API_UNAVAILABLE(watchos);
- (UITraitCollection *)traitCollectionByReplacingObject:(nullable id<NSObject>)object forTrait:(UIObjectTrait)trait API_UNAVAILABLE(watchos);
- (nullable __kindof id<NSObject>)objectForTrait:(UIObjectTrait)trait API_UNAVAILABLE(watchos);

- (NSSet<UITrait> *)changedTraitsFromTraitCollection:(nullable UITraitCollection *)traitCollection API_UNAVAILABLE(watchos);

@property (nonatomic, readonly, class) NSArray<UITrait> *systemTraitsAffectingColorAppearance API_UNAVAILABLE(watchos);
@property (nonatomic, readonly, class) NSArray<UITrait> *systemTraitsAffectingImageLookup API_UNAVAILABLE(watchos);

@end


/*! Trait environments expose a trait collection that describes their environment. */
API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITraitEnvironment <NSObject>
@property (nonatomic, readonly) UITraitCollection *traitCollection API_AVAILABLE(ios(8.0));

/*! To be overridden as needed to provide custom behavior when the environment's traits change. */
- (void)traitCollectionDidChange:(nullable UITraitCollection *)previousTraitCollection API_DEPRECATED("Use the trait change registration APIs declared in the UITraitChangeObservable protocol", ios(8.0, 17.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
@end


API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITraitChangeRegistration <NSObject, NSCopying>
@end

typedef void (^UITraitChangeHandler)(__kindof id<UITraitEnvironment> traitEnvironment, UITraitCollection *previousCollection) API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);


API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITraitOverrides <UIMutableTraits>

- (BOOL)containsTrait:(UITrait)trait;
- (void)removeTrait:(UITrait)trait;

@end


API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITraitChangeObservable

- (id<UITraitChangeRegistration>)registerForTraitChanges:(NSArray<UITrait> *)traits withHandler:(UITraitChangeHandler)handler;

// The action method you use with the following registration APIs may have zero, one, or two parameters.
// If the method accepts at least one parameter, the first parameter will be the trait environment whose traits are changing.
// If the method accepts two parameters, the second parameter will be the trait environment's previous trait collection before the change.
- (id<UITraitChangeRegistration>)registerForTraitChanges:(NSArray<UITrait> *)traits withTarget:(id)target action:(SEL)action;
// Convenience method where the target is self.
- (id<UITraitChangeRegistration>)registerForTraitChanges:(NSArray<UITrait> *)traits withAction:(SEL)action;

- (void)unregisterForTraitChanges:(id<UITraitChangeRegistration>)registration;

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
@property (nonatomic, strong, readonly) UIImageConfiguration *imageConfiguration API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

@end


NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITraitCollection.h>
#endif
