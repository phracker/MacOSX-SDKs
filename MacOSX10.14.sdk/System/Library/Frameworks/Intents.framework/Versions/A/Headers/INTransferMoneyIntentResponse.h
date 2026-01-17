//
//  INTransferMoneyIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

@class INCurrencyAmount;
@class INDateComponentsRange;
@class INPaymentAccount;
@class INPaymentAmount;

typedef NS_ENUM(NSInteger, INTransferMoneyIntentResponseCode) {
    INTransferMoneyIntentResponseCodeUnspecified = 0,
    INTransferMoneyIntentResponseCodeReady,
    INTransferMoneyIntentResponseCodeInProgress,
    INTransferMoneyIntentResponseCodeSuccess,
    INTransferMoneyIntentResponseCodeFailure,
    INTransferMoneyIntentResponseCodeFailureRequiringAppLaunch,
    INTransferMoneyIntentResponseCodeFailureCredentialsUnverified,
    INTransferMoneyIntentResponseCodeFailureInsufficientFunds,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTransferMoneyIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INTransferMoneyIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INTransferMoneyIntentResponseCode code;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *fromAccount;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAccount *toAccount;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPaymentAmount *transactionAmount;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *transactionScheduledDate;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *transactionNote;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *transferFee;

@end

NS_ASSUME_NONNULL_END
