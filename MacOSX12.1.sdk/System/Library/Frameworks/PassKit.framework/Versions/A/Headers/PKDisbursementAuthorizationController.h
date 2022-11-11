//
//  PKDisbursementAuthorizationController.h
//
//  Copyright © 2019 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PKDisbursementRequest;
@class PKDisbursementVoucher;
@class PKDisbursementAuthorizationController;

@protocol PKDisbursementAuthorizationControllerDelegate <NSObject>

@required

// Sent to the delegate when disbursement controller has authorized the disbursement request.
- (void)disbursementAuthorizationController:(PKDisbursementAuthorizationController *)controller
        didAuthorizeWithDisbursementVoucher:(PKDisbursementVoucher *)disbursementVoucher API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);


// Sent to the delegate when disbursement controller is finished. This may occur when
// the user cancels the request or after the disbursement has been authorized.
- (void)disbursementAuthorizationControllerDidFinish:(PKDisbursementAuthorizationController *)controller API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

@end

@interface PKDisbursementAuthorizationController : NSObject

// Initializes and returns a newly created controller for the supplied disbursement request.
- (nullable instancetype)initWithDisbursementRequest:(PKDisbursementRequest *)disbursementRequest
                                            delegate:(id<PKDisbursementAuthorizationControllerDelegate>)delegate API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

// The controller's delegate.
@property (nonatomic, weak, readonly) id<PKDisbursementAuthorizationControllerDelegate> delegate API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

// This presents the Apple Pay sheet. If the sheet is presented successfully, success is YES. Otherwise, an error will be returned.
- (void)authorizeDisbursementWithCompletion:(void(^)(BOOL success, NSError * _Nullable error))completion API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

// Determine whether this user's account supports disbursements.
+ (BOOL)supportsDisbursements API_AVAILABLE(ios(12.2)) API_UNAVAILABLE(tvos, watchos, macos);

@end

NS_ASSUME_NONNULL_END
