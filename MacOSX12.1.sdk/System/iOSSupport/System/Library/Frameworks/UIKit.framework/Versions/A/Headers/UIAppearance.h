#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAppearance.h>)
//
//  UIAppearance.h
//  UIKit
//
//  Copyright 2011-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class UITraitCollection;

/* To participate in the appearance proxy API, tag your appearance property selectors in your header with UI_APPEARANCE_SELECTOR.
 
 Appearance property selectors must be of the form:
 - (void)setProperty:(PropertyType)property forAxis1:(IntegerType)axis1 axis2:(IntegerType)axis2 axisN:(IntegerType)axisN;
 - (PropertyType)propertyForAxis1:(IntegerType)axis1 axis2:(IntegerType)axis2 axisN:(IntegerType)axisN;
 You may have no axes or as many as you like for any property. PropertyType may be any standard iOS type: id, NSInteger, NSUInteger, CGFloat, CGPoint, CGSize, CGRect, UIEdgeInsets or UIOffset. IntegerType must be either NSInteger or NSUInteger; we will throw an exception if other types are used in the axes.
 */
#define UI_APPEARANCE_SELECTOR __attribute__((annotate("ui_appearance_selector")))

NS_SWIFT_UI_ACTOR
@protocol UIAppearanceContainer <NSObject> @end

NS_SWIFT_UI_ACTOR
@protocol UIAppearance <NSObject>
/* To customize the appearance of all instances of a class, send the relevant appearance modification messages to the appearance proxy for the class. For example, to modify the bar tint color for all UINavigationBar instances:
    [[UINavigationBar appearance] setBarTintColor:myColor];
 
    Note for iOS7: On iOS7 the tintColor property has moved to UIView, and now has special inherited behavior described in UIView.h.
    This inherited behavior can conflict with the appearance proxy, and therefore tintColor is now disallowed with the appearance proxy.
  */
+ (instancetype)appearance;

/* To customize the appearances for instances of a class contained within an instance of a container class, or instances in a hierarchy, use +appearanceWhenContainedInInstancesOfClasses: for the appropriate appearance proxy. For example:
 
 [[UINavigationBar appearanceWhenContainedInInstancesOfClasses:@[[UISplitViewController class]]] setBarTintColor:myColor];
 [[UINavigationBar appearanceWhenContainedInInstancesOfClasses:@[[UITabBarController class], [UISplitViewController class]]] setBarTintColor:myTabbedNavBarColor];
 
 In any given view hierarchy the outermost appearance proxy wins. Specificity (depth of the chain) is the tie-breaker.
 
 In other words, the containment statement is treated as a partial ordering. Given a concrete ordering (actual subview hierarchy), we select the partial ordering that is the first unique match when reading the actual hierarchy from the window down.
*/
+ (instancetype)appearanceWhenContainedIn:(nullable Class <UIAppearanceContainer>)ContainerClass, ... NS_REQUIRES_NIL_TERMINATION API_DEPRECATED_WITH_REPLACEMENT("appearanceWhenContainedInInstancesOfClasses:", ios(5.0, 9.0)) API_UNAVAILABLE(tvos);
+ (instancetype)appearanceWhenContainedInInstancesOfClasses:(NSArray<Class <UIAppearanceContainer>> *)containerTypes API_AVAILABLE(ios(9.0));

+ (instancetype)appearanceForTraitCollection:(UITraitCollection *)trait API_AVAILABLE(ios(8.0));
+ (instancetype)appearanceForTraitCollection:(UITraitCollection *)trait whenContainedIn:(nullable Class <UIAppearanceContainer>)ContainerClass, ... NS_REQUIRES_NIL_TERMINATION API_DEPRECATED_WITH_REPLACEMENT("appearanceForTraitCollection:whenContainedInInstancesOfClasses:", ios(8.0, 9.0)) API_UNAVAILABLE(tvos);
+ (instancetype)appearanceForTraitCollection:(UITraitCollection *)trait whenContainedInInstancesOfClasses:(NSArray<Class <UIAppearanceContainer>> *)containerTypes  API_AVAILABLE(ios(9.0));

@end
NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIAppearance.h>
#endif
