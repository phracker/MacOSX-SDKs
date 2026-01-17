//
//  INInteraction.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INIntent;
@class INIntentResponse;

typedef NS_ENUM(NSInteger, INIntentHandlingStatus) {
    INIntentHandlingStatusUnspecified = 0,
    INIntentHandlingStatusReady,
    INIntentHandlingStatusInProgress,
    INIntentHandlingStatusSuccess,
    INIntentHandlingStatusFailure,
    INIntentHandlingStatusDeferredToApplication,
} API_AVAILABLE(macosx(10.12), ios(10.0));

typedef NS_ENUM(NSInteger, INInteractionDirection) {
    INInteractionDirectionUnspecified = 0,
    INInteractionDirectionOutgoing,
    INInteractionDirectionIncoming,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

/*
 An app can use an INInteraction to donate an action (represented as an intent) and its state to the system.

 The system may also launch the app with an NSUserActivity containing an INInteraction such that the app can perform the action if it chooses.
*/

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INInteraction : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithIntent:(INIntent *)intent response:(nullable INIntentResponse *)response NS_DESIGNATED_INITIALIZER;

// donate this interaction to the system
- (void)donateInteractionWithCompletion:(void(^_Nullable)(NSError * _Nullable error))completion NS_SWIFT_NAME(donate(completion:));

// delete all the interactions ever donated by the calling app
+ (void)deleteAllInteractionsWithCompletion:(void (^_Nullable)(NSError * _Nullable error))completion NS_SWIFT_NAME(deleteAll(completion:));

// delete the interactions with the specified identifiers that were donated by this app
+ (void)deleteInteractionsWithIdentifiers:(nonnull NSArray<NSString *> *)identifiers completion:(void(^_Nullable)(NSError * _Nullable error))completion NS_SWIFT_NAME(delete(with:completion:));

// delete this app's interactions with the specified group identifier
+ (void)deleteInteractionsWithGroupIdentifier:(nonnull NSString *)groupIdentifier completion:(void(^_Nullable)(NSError * _Nullable error))completion NS_SWIFT_NAME(delete(with:completion:));

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INIntent *intent;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INIntentResponse *intentResponse;

// Indicates the state of execution of the intent
// This is consistent with the response state of the intentResponse, if specified
@property (readonly, NS_NONATOMIC_IOSONLY) INIntentHandlingStatus intentHandlingStatus;

// Indicates the direction of the interaction
@property (assign, NS_NONATOMIC_IOSONLY) INInteractionDirection direction;

// The time the interaction started/occurred and its duration. The app can override with their own timestamp but it defaults to the time of creation of this interaction object
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateInterval *dateInterval;

// A unique identifier for the interaction. It defaults to a globally unique identifier.
// The app can override with their own identifier that is unique in the app's domain
@property (copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

// A user-defined identifier for the interaction group, this is handy during deletion time
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *groupIdentifier;

@end

NS_ASSUME_NONNULL_END
