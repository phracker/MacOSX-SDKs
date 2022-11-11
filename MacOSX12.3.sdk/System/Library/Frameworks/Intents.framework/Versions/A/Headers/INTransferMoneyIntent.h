//
//  INTransferMoneyIntent.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INPaymentAccount;
@class INPaymentAccountResolutionResult;
@class INPaymentAmount;
@class INPaymentAmountResolutionResult;
@class INStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INTransferMoneyIntent is deprecated. There is no replacement.", ios(11.0, 15.0), watchos(4.0, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INTransferMoneyIntent : INIntent

- (instancetype)initWithFromAccount:(nullable INPaymentAccount *)fromAccount
                          toAccount:(nullable INPaymentAccount *)toAccount
                  transactionAmount:(nullable INPaymentAmount *)transactionAmount
           transactionScheduledDate:(nullable INDateComponentsRange *)transactionScheduledDate
                    transactionNote:(nullable NSString *)transactionNote NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *fromAccount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *toAccount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAmount *transactionAmount;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *transactionScheduledDate;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *transactionNote;

@end

@class INTransferMoneyIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INTransferMoneyIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_DEPRECATED("INTransferMoneyIntentHandling is deprecated. There is no replacement.", ios(11.0, 15.0), watchos(4.0, 8.0))
API_UNAVAILABLE(macos, tvos)
@protocol INTransferMoneyIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INTransferMoneyIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INTransferMoneyIntentResponse containing the details of the result of having executed the intent

 @see  INTransferMoneyIntentResponse
 */

- (void)handleTransferMoney:(INTransferMoneyIntent *)intent
                 completion:(void (^)(INTransferMoneyIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INTransferMoneyIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INTransferMoneyIntentResponse
 */

- (void)confirmTransferMoney:(INTransferMoneyIntent *)intent
                  completion:(void (^)(INTransferMoneyIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveFromAccountForTransferMoney:(INTransferMoneyIntent *)intent
                            withCompletion:(void (^)(INPaymentAccountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveFromAccount(for:with:));

- (void)resolveToAccountForTransferMoney:(INTransferMoneyIntent *)intent
                          withCompletion:(void (^)(INPaymentAccountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveToAccount(for:with:));

- (void)resolveTransactionAmountForTransferMoney:(INTransferMoneyIntent *)intent
                                  withCompletion:(void (^)(INPaymentAmountResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionAmount(for:with:));

- (void)resolveTransactionScheduledDateForTransferMoney:(INTransferMoneyIntent *)intent
                                         withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionScheduledDate(for:with:));

- (void)resolveTransactionNoteForTransferMoney:(INTransferMoneyIntent *)intent
                                withCompletion:(void (^)(INStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTransactionNote(for:with:));

@end

NS_ASSUME_NONNULL_END
