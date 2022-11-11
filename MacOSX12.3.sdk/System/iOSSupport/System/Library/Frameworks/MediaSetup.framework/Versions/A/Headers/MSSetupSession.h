//
//  MSSetupSession.h
//  MediaSetup
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class MSServiceAccount;

typedef UIWindow * MSPresentationAnchor;

@protocol MSAuthenticationPresentationContext <NSObject>

/// The anchor to present the interface in
- (_Nullable MSPresentationAnchor) presentationAnchor;

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macosx, watchos, tvos)
@interface MSSetupSession : NSObject

- (instancetype _Null_unspecified)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Initialize a new setup session with the service account to add
- (instancetype)initWithServiceAccount:(MSServiceAccount *)serviceAccount;

/// Presents user with options to add service to home. Returns true if presented successfully, false otherwise
- (BOOL) startWithError:(NSError * _Nullable * _Nullable)error;

/// A context to provide the session with anchor for presentation. See MSAuthenticationPresentationContext protocol
@property (nonatomic, weak) _Nullable id<MSAuthenticationPresentationContext> presentationContext;

/// The account used to initialize the session
@property (nonatomic, strong, readonly) MSServiceAccount * account;

@end

NS_ASSUME_NONNULL_END
