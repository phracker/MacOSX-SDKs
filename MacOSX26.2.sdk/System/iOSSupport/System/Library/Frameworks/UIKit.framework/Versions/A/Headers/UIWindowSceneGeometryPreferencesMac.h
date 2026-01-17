#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneGeometryPreferencesMac.h>)
//
//  UIWindowSceneGeometryPreferencesMac.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CGGeometry.h>
#import <UIKit/UIWindowSceneGeometryPreferences.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Use this class to express macOS-specific geometry preferences when calling `-[UIWindowScene requestGeometryUpdateWithPreferences:errorHandler:]`
UIKIT_EXTERN API_AVAILABLE(macCatalyst(16.0)) API_UNAVAILABLE(watchos)
@interface UIWindowSceneGeometryPreferencesMac : UIWindowSceneGeometryPreferences

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithSystemFrame:(CGRect)systemFrame;

/// The preferred system frame in the system scale where an origin of (0, 0) corresponds to the top-left
/// corner of the main display. Defaults to CGRectNull to indicate no preference.
@property (nonatomic, assign) CGRect systemFrame NS_REFINED_FOR_SWIFT; 

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneGeometryPreferencesMac.h>
#endif
