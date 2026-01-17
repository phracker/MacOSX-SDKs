#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneGeometry.h>)
//
//  UIWindowSceneGeometry.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIWindowSceneResizingRestrictions) {
    /// App has no preference on user resize
    UIWindowSceneResizingRestrictionsUnspecified = 0,

    /// The user cannot resize the scene
    UIWindowSceneResizingRestrictionsNone,

    /// User resizes are restricted to the current aspect ratio
    UIWindowSceneResizingRestrictionsUniform,
    
    /// User resizes are only restricted by the system and other restrictions put in place
    UIWindowSceneResizingRestrictionsFreeform
} API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, macos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos)
@interface UIWindowSceneGeometry : NSObject <NSCopying>

/// Geometry objects are readonly and should only be created by the framework. To set a window scene's geometry, see UIWindowSceneGeometryPreferences and -[UIWindowScene requestGeometryUpdateWithPreferences:].
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) CGRect systemFrame API_AVAILABLE(macCatalyst(16.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/// The coordinate space of the scene
@property (nonatomic, readonly) id<UICoordinateSpace> coordinateSpace API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// The interface orientation of the scene
@property (nonatomic, readonly) UIInterfaceOrientation interfaceOrientation API_UNAVAILABLE(tvos);

/// If the scene's interface orientation is locked and preventing changes. To express a preference for this value, override  `UIViewController`'s `prefersInterfaceOrientationLocked`.
@property (nonatomic, getter=isInterfaceOrientationLocked, readonly) BOOL interfaceOrientationLocked API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos);

/// The current app specified minimumSize. A value of 0,0 is returned if a minimum is not set by the application
@property (nonatomic, readonly) CGSize minimumSize API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, macos, watchos);

/// The current app specified maximumSize. A value of CGFLOAT_MAX,CGFLOAT_MAX is returned if a maximum is not set by the application
@property (nonatomic, readonly) CGSize maximumSize API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, macos, watchos);

/// The current app specified resizingRestriction. Default value UIWindowSceneResizingRestrictionsUnspecified
@property (nonatomic, readonly) UIWindowSceneResizingRestrictions resizingRestrictions API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, macos, watchos);

/// Returns true when the scene is being resized interactively, otherwise false.
@property (nonatomic, readonly, getter=isInteractivelyResizing) BOOL interactivelyResizing API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneGeometry.h>
#endif
