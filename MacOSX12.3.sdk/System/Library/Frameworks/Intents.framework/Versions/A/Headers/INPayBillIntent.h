//
//  INPayBillIntent.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INBillType.h>

@class INBillPayee;
@class INBillPayeeResolutionResult;
@class INBillTypeResolutionResult;
@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPaymentAccount;
@class INPaymentAccountResolutionResult;
@class INPaymentAmount;
@class INPaymentAmountResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INPayBillIntent is deprecated. There is no replacement.", ios(10.3, 15.0), watchos(3.2, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INPayBillIntent : INIntent

- (instancetype)initWithBillPayee:(nullable INBillPayee *)billPayee
                      fromAccount:(nullable INPaymentAccount *)fromAccount
                transactionAmount:(nullable INPaymentAmount *)transactionAmount
         transactionScheduledDate:(nullable INDateComponentsRange *)transactionScheduledDate
                  transactionNote:(nullable NSString *)transactionNote
                         billType:(INBillType)billType
                          dueDate:(nullable INDateComponentsRange *)dueDate NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INBillPayee *billPayee;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *fromAccount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAmount *transactionAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *transactionScheduledDate;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *transactionNote;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INBillType billType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dueDate;

@end

@class INPayBillIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INPayBillIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_DEPRECATED("INPayBillIntentHandling is deprecated. There is no replacement.", ios(10.3, 15.0), watchos(3.2, 8.0))
API_UNAVAILABLE(macos, tvos)
@protocol INPayBillIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INPayBillIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INPayBillIntentResponse containing the details of the result of having executed the intent

 @see  INPayBillIntentResponse
 */

- (void)handlePayBill:(INPayBillIntent *)intent
           completion:(void (^)(INPayBillIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INPayBillIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INPayBillIntentResponse
 */

- (void)confirmPayBill:(INPayBillIntent *)intent
            completion:(void (^)(INPayBillIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveBillPayeeForPayBill:(INPayBillIntent *)intent
                    withCompletion:(void (^)(INBillPayeeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveBillPayee(for:with:));

- (void)resolveFromAccountForPayBill:(INPayBillIntent *)intent
                      withCompletion:(void (^)(INPaymentAccountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFromAccount(for:with:));

- (void)resolveTransactionAmountForPayBill:(INPayBillIntent *)intent
                            withCompletion:(void (^)(INPaymentAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionAmount(for:with:));

- (void)resolveTransactionScheduledDateForPayBill:(INPayBillIntent *)intent
                                   withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionScheduledDate(for:with:));

- (void)resolveTransactionNoteForPayBill:(INPayBillIntent *)intent
                          withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionNote(for:with:));

- (void)resolveBillTypeForPayBill:(INPayBillIntent *)intent
                   withCompletion:(void (^)(INBillTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveBillType(for:with:));

- (void)resolveDueDateForPayBill:(INPayBillIntent *)intent
                  withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDueDate(for:with:));

@end

NS_ASSUME_NONNULL_END
