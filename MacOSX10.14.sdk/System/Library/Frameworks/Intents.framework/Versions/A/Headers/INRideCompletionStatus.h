//
//  INRideCompletionStatus.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INRideFeedbackTypeOptions.h>


NS_ASSUME_NONNULL_BEGIN

@class INCurrencyAmount;

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INRideCompletionStatus: NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

// The ride completed.
+ (instancetype)completed;

// The ride completed. The fare in the provided amount was successfully paid; this amount may be displayed to the user.
+ (instancetype)completedWithSettledPaymentAmount:(INCurrencyAmount *)settledPaymentAmount NS_SWIFT_NAME(completed(settled:));

// The ride completed but there is a payment outstanding that the user needs to settle in the application.
// The .completionUserActivity should be set, and will be continued in your application to perform payment tasks.
+ (instancetype)completedWithOutstandingPaymentAmount:(INCurrencyAmount *)outstandingPaymentAmount NS_SWIFT_NAME(completed(outstanding:));

// The ride completed but there is feedback outstanding that the user may provide to the system. See INSendRideFeedbackIntent.
// If feedbackType includes INRideFeedbackTypeOptionTip, the .defaultTippingOptions should be set.
+ (instancetype)completedWithOutstandingFeedbackType:(INRideFeedbackTypeOptions)feedbackType API_AVAILABLE(ios(11.0), watchos(4.0)) NS_SWIFT_NAME(completed(feedbackType:));

// The ride was canceled by the service (e.g. because the driver asked to cancel)
+ (instancetype)canceledByService;

// The ride was canceled by the user (e.g. by doing so through your application)
+ (instancetype)canceledByUser;

// The ride was canceled by the service because the passenger was not present for pickup and the vehicle maximum wait time elapsed.
+ (instancetype)canceledMissedPickup;

// If this property is set, UI may be shown to the user to complete post-ride tasks (e.g. for settling outstanding payment). Acting on that UI will continue this activity in your application.
@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *completionUserActivity;

// YES if the ride was completed.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isCompleted) BOOL completed;

// YES if the ride was canceled.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isCanceled) BOOL canceled;

// YES if the user missed the pickup. This is only YES if .canceled is YES.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isMissedPickup) BOOL missedPickup;

// The payment amount, if any.
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *paymentAmount;

// The type of feedback requested, if any.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INRideFeedbackTypeOptions feedbackType API_AVAILABLE(ios(11.0), watchos(4.0));

// Whether the payment is outstanding (YES) or settled (NO).
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isOutstanding) BOOL outstanding;

// Default options the user can choose from when adding a tip.
@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSSet<INCurrencyAmount *> *defaultTippingOptions API_AVAILABLE(ios(11.0), watchos(4.0));
                                                                                                           
@end

NS_ASSUME_NONNULL_END
