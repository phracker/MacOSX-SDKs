#if !__has_include(<PassKitCore/PKIdentityAuthorizationController.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIdentityAuthorizationController.h
//    PassKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PKIdentityDocument;
@class PKIdentityRequest;
@protocol PKIdentityDocumentDescriptor;

NS_ASSUME_NONNULL_BEGIN

/// Used to request information from an identity document stored as a Wallet pass.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface PKIdentityAuthorizationController: NSObject

/// Determines if a document can be requested, taking into account the entitlement of the
/// calling process as well as the state of this device.
- (void)checkCanRequestDocument:(id<PKIdentityDocumentDescriptor>)descriptor
                     completion:(void(^)(BOOL canRequest))completion NS_SWIFT_ASYNC_NAME(canRequestDocument(_:));

/// Requests identity document information from the user. The user will be prompted to approve
/// the request before any data is released.
/// If the user approves, the document will be returned through the completion handler.
/// If the user does not approve, PKIdentityErrorUserCancelled will be returned through
/// the completion handler.
/// If the request is cancelled by the calling app through cancelRequest, PKIdentityErrorAppCancelled
/// will be returned.
/// Only one request can be in progress at a time, otherwise PKIdentityErrorRequestAlreadyInProgress
/// will be returned.
- (void)requestDocument:(PKIdentityRequest *)request
             completion:(void(^)(PKIdentityDocument * _Nullable document, NSError * _Nullable error))completion;

/// If there is a request in progress through requestDocument, this will cancel that request
/// if possible. If the request is cancelled, PKIdentityErrorAppCancelled will be returned in the
/// requestDocument:completion: completion handler. Cancellation is not guaranteed; even if
/// this method is called, it is possible that requestDocument:completion: will return a document
/// response if a response was already in flight.
- (void)cancelRequest;

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKIdentityAuthorizationController.h>
#endif