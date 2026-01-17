#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneGeometryPreferencesVision.h>)
//
//  UIWindowSceneGeometryPreferencesVision.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIWindowSceneGeometryPreferences.h>
#import <UIKit/UIWindowSceneGeometry.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Used as the value for a dimension of a size related preference when wanting to leave it unchanged.
UIKIT_EXTERN const CGFloat UIProposedSceneSizeNoPreference API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, macos, watchos);

UIKIT_EXTERN API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, macos, watchos)
@interface UIWindowSceneGeometryPreferencesVision : UIWindowSceneGeometryPreferences

/// Creates a geometry preference with no changes. Update the properties who's preference should change
- (instancetype)init NS_REFINED_FOR_SWIFT;

/// Creates a geometry preference with a specific size (specifying UIProposedSceneSizeNoPreference for any dimension of size, will specify no preference, keeping that dimension the same if possible)
- (instancetype)initWithSize:(CGSize)size NS_REFINED_FOR_SWIFT;

/// The preferred system size. Use UIProposedSceneSizeNoPreference to use existing value
@property (nonatomic, assign) CGSize size NS_REFINED_FOR_SWIFT;

/// The preferred minimum size of the scene. Use `UIProposedSceneSizeNoPreference` on a dimension of the size to indicate that axis should be returned to the system default.
/// By default, the value is left unchanged
@property (nonatomic, assign) CGSize minimumSize NS_REFINED_FOR_SWIFT;

/// The preferred maximum size of the scene. Use `UIProposedSceneSizeNoPreference` on a dimension of the size to indicate that axis should be returned to the system default.
/// By default, the value is left unchanged
@property (nonatomic, assign) CGSize maximumSize NS_REFINED_FOR_SWIFT;

/// The user resizable restrictions on the window scene
/// By default, the value is left unchanged
@property (nonatomic, assign) UIWindowSceneResizingRestrictions resizingRestrictions NS_REFINED_FOR_SWIFT;
@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIWindowSceneGeometryPreferencesVision.h>
#endif
