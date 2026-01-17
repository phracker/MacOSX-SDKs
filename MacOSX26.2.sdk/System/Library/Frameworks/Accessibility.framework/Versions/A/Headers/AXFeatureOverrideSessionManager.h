//
//  AXFeatureOverrideSessionManager.h
//  Accessibility
//
//  Created by Drew Haas on 9/30/24.
//  Copyright © 2024 Apple. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_IOS && !TARGET_OS_VISION && !TARGET_OS_MACCATALYST

#import <Accessibility/AXFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Options indicating which Accessibility features will be turned on or off when an override session is held by your app.
API_AVAILABLE(ios(18.2))
typedef NS_OPTIONS(NSUInteger, AXFeatureOverrideSessionOptions) {
    AXFeatureOverrideSessionOptionsGrayscale = 1 << 0,
    AXFeatureOverrideSessionOptionsInvertColors = 1 << 1,
    AXFeatureOverrideSessionOptionsVoiceControl = 1 << 2,
    AXFeatureOverrideSessionOptionsVoiceOver = 1 << 3,
    AXFeatureOverrideSessionOptionsZoom = 1 << 4
} NS_SWIFT_NAME(AXFeatureOverrideSession.Options);

AX_EXTERN API_AVAILABLE(ios(18.2))
NSErrorDomain const AXFeatureOverrideSessionErrorDomain;
API_AVAILABLE(ios(18.2))
typedef NS_ERROR_ENUM(AXFeatureOverrideSessionErrorDomain, AXFeatureOverrideSessionError) {
    AXFeatureOverrideSessionErrorUndefined = 0,
    AXFeatureOverrideSessionErrorAppNotEntitled,
    AXFeatureOverrideSessionErrorOverrideIsAlreadyActive,
    AXFeatureOverrideSessionErrorOverrideNotFoundForUUID,
};

/// A token object that represents an override session held by your app.
AX_EXTERN API_AVAILABLE(ios(18.2))
@interface AXFeatureOverrideSession : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
@end

/// A manager class to begin and end accessibility feature override sessions. Multiple override sessions are reconciled by combining the requests, preferring feature enablement. Ending all sessions restores the prior state of Accessibility feature enablement. Your app must be entitled with com.apple.developer.accessibility.merchant-api-control.
AX_EXTERN API_AVAILABLE(ios(18.2))
@interface AXFeatureOverrideSessionManager : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (class, readonly) AXFeatureOverrideSessionManager *sharedInstance;

- (nullable AXFeatureOverrideSession *)beginOverrideSessionEnablingOptions:(AXFeatureOverrideSessionOptions)enableOptions disablingOptions:(AXFeatureOverrideSessionOptions)disableOptions error:(NSError * _Nullable *)error NS_SWIFT_NAME(beginOverrideSession(enabling:disabling:));
- (BOOL)endOverrideSession:(AXFeatureOverrideSession *)session error:(NSError * _Nullable *)error;
@end

NS_ASSUME_NONNULL_END

#endif
