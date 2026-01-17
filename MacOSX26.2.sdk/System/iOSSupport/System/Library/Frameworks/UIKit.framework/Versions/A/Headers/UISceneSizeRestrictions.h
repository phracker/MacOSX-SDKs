#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneSizeRestrictions.h>)
//
//  UISceneSizeRestrictions.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Sizing preferences for the scene. Clients do not create `UISceneSizeRestrictions` directly. An instance is returned from `UIWindowScene.sizeRestrictions`
/// if the platform supports scene resizing.
/// - Note: The system imposes limits on each preference that may result in it not being honored.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UISceneSizeRestrictions : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The preferred minimum size of the scene
@property (nonatomic, assign) CGSize minimumSize;

/// The preferred maximum size of the scene
@property (nonatomic, assign) CGSize maximumSize;

/// Whether the scene supports full screen or not
/// - Note: Currently only honored on Mac Catalyst
@property (nonatomic) BOOL allowsFullScreen API_AVAILABLE(macCatalyst(16.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneSizeRestrictions.h>
#endif
