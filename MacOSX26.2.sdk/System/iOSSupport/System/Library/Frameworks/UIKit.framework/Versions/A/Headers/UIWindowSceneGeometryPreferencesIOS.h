#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneGeometryPreferencesIOS.h>)
//
//  UIWindowSceneGeometryPreferencesIOS.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UIWindowSceneGeometryPreferences.h>
#import <UIKit/UIApplication.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Use this class to express iOS-specific geometry preferences when calling `-[UIWindowScene requestGeometryUpdateWithPreferences:errorHandler:]`
UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos)
@interface UIWindowSceneGeometryPreferencesIOS : UIWindowSceneGeometryPreferences

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithInterfaceOrientations:(UIInterfaceOrientationMask)interfaceOrientations;

/// The preferred interface orientations. The system will choose the best orientation from the intersection of these
/// orientations and the current supported orientations. Defaults to an empty mask to indicate no preference.
@property (nonatomic, assign) UIInterfaceOrientationMask interfaceOrientations NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneGeometryPreferencesIOS.h>
#endif
