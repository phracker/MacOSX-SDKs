//
//  CXProvider.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXAction;
@class CXCallAction;
@class CXCallUpdate;
@class CXProvider;
@class CXProviderConfiguration;
@class CXTransaction;
@class CXAction;
@class CXCallAction;
@class CXStartCallAction;
@class CXAnswerCallAction;
@class CXEndCallAction;
@class CXSetHeldCallAction;
@class CXSetMutedCallAction;
@class CXSetGroupCallAction;
@class CXPlayDTMFCallAction;

@class AVAudioSession;

typedef NS_ENUM(NSInteger, CXCallEndedReason) {
    CXCallEndedReasonFailed = 1, // An error occurred while trying to service the call
    CXCallEndedReasonRemoteEnded = 2, // The remote party explicitly ended the call
    CXCallEndedReasonUnanswered = 3, // The call never started connecting and was never explicitly ended (e.g. outgoing/incoming call timeout)
    CXCallEndedReasonAnsweredElsewhere = 4, // The call was answered on another device
    CXCallEndedReasonDeclinedElsewhere = 5, // The call was declined on another device
} API_AVAILABLE(ios(10.0), macCatalyst(13.0), macos(11.0))  API_UNAVAILABLE(watchos, tvos);

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), macos(11.0))  API_UNAVAILABLE(watchos, tvos)
@protocol CXProviderDelegate <NSObject>

/// Called when the provider has been reset. Delegates must respond to this callback by cleaning up all internal call state (disconnecting communication channels, releasing network resources, etc.). This callback can be treated as a request to end all calls without the need to respond to any actions
- (void)providerDidReset:(CXProvider *)provider;

@optional

/// Called when the provider has been fully created and is ready to send actions and receive updates
- (void)providerDidBegin:(CXProvider *)provider;

/// Called whenever a new transaction should be executed. Return whether or not the transaction was handled:
///
/// - NO: the transaction was not handled indicating that the perform*CallAction methods should be called sequentially for each action in the transaction
/// - YES: the transaction was handled and the perform*CallAction methods should not be called sequentially
///
/// If the method is not implemented, NO is assumed.
- (BOOL)provider:(CXProvider *)provider executeTransaction:(CXTransaction *)transaction;

// If provider:executeTransaction:error: returned NO, each perform*CallAction method is called sequentially for each action in the transaction
- (void)provider:(CXProvider *)provider performStartCallAction:(CXStartCallAction *)action;
- (void)provider:(CXProvider *)provider performAnswerCallAction:(CXAnswerCallAction *)action;
- (void)provider:(CXProvider *)provider performEndCallAction:(CXEndCallAction *)action;
- (void)provider:(CXProvider *)provider performSetHeldCallAction:(CXSetHeldCallAction *)action;
- (void)provider:(CXProvider *)provider performSetMutedCallAction:(CXSetMutedCallAction *)action;
- (void)provider:(CXProvider *)provider performSetGroupCallAction:(CXSetGroupCallAction *)action;
- (void)provider:(CXProvider *)provider performPlayDTMFCallAction:(CXPlayDTMFCallAction *)action;

/// Called when an action was not performed in time and has been inherently failed. Depending on the action, this timeout may also force the call to end. An action that has already timed out should not be fulfilled or failed by the provider delegate
- (void)provider:(CXProvider *)provider timedOutPerformingAction:(CXAction *)action;

/// Called when the provider's audio session activation state changes.
- (void)provider:(CXProvider *)provider didActivateAudioSession:(AVAudioSession *)audioSession;
- (void)provider:(CXProvider *)provider didDeactivateAudioSession:(AVAudioSession *)audioSession;

@end

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0), macos(11.0))  API_UNAVAILABLE(watchos, tvos)
@interface CXProvider : NSObject

/// Initialize a new provider instance with the supplied configuration
- (instancetype)initWithConfiguration:(CXProviderConfiguration *)configuration NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/// Set delegate and optional queue for delegate callbacks to be performed on.
/// A nil queue implies that delegate callbacks should happen on the main queue. The delegate is stored weakly
- (void)setDelegate:(nullable id<CXProviderDelegate>)delegate queue:(nullable dispatch_queue_t)queue;

/// Report a new incoming call to the system.
///
/// If completion is invoked with a non-nil `error`, the incoming call has been disallowed by the system and will not be displayed, so the provider should not proceed with the call.
///
/// Completion block will be called on delegate queue, if specified, otherwise on a private serial queue.
- (void)reportNewIncomingCallWithUUID:(NSUUID *)UUID update:(CXCallUpdate *)update completion:(void (^)(NSError *_Nullable error))completion;

/// Report an update to call information.
- (void)reportCallWithUUID:(NSUUID *)UUID updated:(CXCallUpdate *)update;

/// Report that a call ended. A nil value for `dateEnded` results in the ended date being set to now.
- (void)reportCallWithUUID:(NSUUID *)UUID endedAtDate:(nullable NSDate *)dateEnded reason:(CXCallEndedReason)endedReason;

/// Report that an outgoing call started connecting. A nil value for `dateStartedConnecting` results in the started connecting date being set to now.
- (void)reportOutgoingCallWithUUID:(NSUUID *)UUID startedConnectingAtDate:(nullable NSDate *)dateStartedConnecting;

/// Report that an outgoing call connected. A nil value for `dateConnected` results in the connected date being set to now.
- (void)reportOutgoingCallWithUUID:(NSUUID *)UUID connectedAtDate:(nullable NSDate *)dateConnected;

/// From within a Notification Service Extension, request the containing application be launched to handle an incoming VoIP call. The application's PKPushRegistryDelegate must handle the push upon launch.
+ (void)reportNewIncomingVoIPPushPayload:(NSDictionary *)dictionaryPayload completion:(nullable void (^)(NSError *_Nullable))completion API_UNAVAILABLE( tvos, watchos, macos) API_AVAILABLE(ios(14.5), macCatalyst(14.5));

/// The receiver's current configuration.
@property (nonatomic, readwrite, copy) CXProviderConfiguration *configuration;

/// Invalidate the receiver. All existing calls will be marked as ended in failure. The provider must be invalidated before it is deallocated.
- (void)invalidate;

/// List of all transactions that are incomplete.
@property (nonatomic, readonly, copy) NSArray<CXTransaction *> *pendingTransactions;

/// Returns subset of call actions contained in any transaction in -pendingTransactions of the specified class and with the specified call UUID.
- (NSArray<__kindof CXCallAction *> *)pendingCallActionsOfClass:(Class)callActionClass withCallUUID:(NSUUID *)callUUID;

@end

NS_ASSUME_NONNULL_END
