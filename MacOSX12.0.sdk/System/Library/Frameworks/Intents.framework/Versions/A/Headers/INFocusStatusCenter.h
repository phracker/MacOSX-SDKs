//
//  INFocusStatusCenter.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INFocusStatus.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INFocusStatusAuthorizationStatus) {
    INFocusStatusAuthorizationStatusNotDetermined = 0,
    INFocusStatusAuthorizationStatusRestricted,
    INFocusStatusAuthorizationStatusDenied,
    INFocusStatusAuthorizationStatusAuthorized
} API_AVAILABLE(ios(15.0), macos(12.0), watchos(8.0)) API_UNAVAILABLE(tvos);

API_AVAILABLE(ios(15.0), macos(12.0), watchos(8.0))
API_UNAVAILABLE(tvos)
@interface INFocusStatusCenter : NSObject

@property (nonatomic, strong, readonly, class) INFocusStatusCenter *defaultCenter;
@property (nonatomic, readonly) INFocusStatus *focusStatus;
@property (nonatomic, readonly) INFocusStatusAuthorizationStatus authorizationStatus;

- (void)requestAuthorizationWithCompletionHandler:(void (^ _Nullable)(INFocusStatusAuthorizationStatus status))completionHandler;

@end

NS_ASSUME_NONNULL_END
