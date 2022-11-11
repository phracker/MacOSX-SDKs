//
//  WCSession.h
//  WatchConnectivity
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WCSessionFile, WCSessionFileTransfer, WCSessionUserInfoTransfer;
@protocol WCSessionDelegate;

typedef NS_ENUM(NSInteger, WCSessionActivationState) {
	WCSessionActivationStateNotActivated  = 0,
	WCSessionActivationStateInactive      = 1,
	WCSessionActivationStateActivated     = 2,
} __IOS_AVAILABLE(9.3) __WATCHOS_AVAILABLE(2.2);

/** -------------------------------- WCSession --------------------------------
 *  The default session is used to communicate between two counterpart apps
 *  (i.e. iOS app and its native WatchKit extension). The session provides
 *  methods for sending, receiving, and tracking state.
 *
 *  On start up an app should set a delegate on the default session and call
 *  activate. This will allow the system to populate the state properties and
 *  deliver any outstanding background transfers.
 */
API_AVAILABLE(ios(9.0), macCatalyst(13.0), watchos(2.0)) API_UNAVAILABLE(macos, tvos)
@interface WCSession : NSObject

/** Check if session is supported on this iOS device. Session is always available on WatchOS */
+ (BOOL)isSupported;

/** Use the default session for all transferring of content and state monitoring. */
@property (class, readonly) WCSession *defaultSession;

/** Use the default session instead. */
- (instancetype)init NS_UNAVAILABLE;

/** A delegate must exist before the session will allow sends. */
@property (nonatomic, weak, nullable) id <WCSessionDelegate> delegate;

/** The default session must be activated on startup before the session's properties contain correct values and will begin receiving delegate callbacks. Calling activate without a delegate set is undefined. If the WCSessionDelegate session:activationDidCompleteWithState:error: is implemented this method becomes an asynchronous call. */
- (void)activateSession;

/** The state of the current session */
@property (nonatomic, readonly) WCSessionActivationState activationState __IOS_AVAILABLE(9.3) __WATCHOS_AVAILABLE(2.2);

/** Whether or not there is more content for the session to deliver */
@property (nonatomic, readonly) BOOL hasContentPending __IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0);

/** ------------------------- iOS App State For Watch ---------------------------
 *  State information that applies to Watch and is only available to the iOS app.
 *  This information includes device state, counterpart app state, and iOS app
 *  information specific to Watch.
 */

/** Check if iOS device is paired to a watch */
@property (nonatomic, readonly, getter=isPaired) BOOL paired __WATCHOS_UNAVAILABLE;

/** Check if the user has the Watch app installed */
@property (nonatomic, readonly, getter=isWatchAppInstalled) BOOL watchAppInstalled __WATCHOS_UNAVAILABLE;

/** Check if the user has the Watch app's complication enabled */
@property (nonatomic, readonly, getter=isComplicationEnabled) BOOL complicationEnabled __WATCHOS_UNAVAILABLE;

/** The number of calls remaining to transferCurrentComplicationUserInfo: before the system starts transferring the complicationUserInfo as regular userInfos. If this is 0, the complicationUserInfo will be transferred as regular userInfos. Count will be 0 whenever the complication is not enabled */
@property (nonatomic, readonly) NSUInteger remainingComplicationUserInfoTransfers __IOS_AVAILABLE(10.0) __WATCHOS_UNAVAILABLE;

/** Use this directory to persist any data specific to the selected Watch. The location of the URL will change when the selected Watch changes. This directory will be deleted upon next launch if the watch app is uninstalled for the selected Watch, or that Watch is unpaired. If the watch app is not installed for the selected Watch the value will be nil. */
@property (nonatomic, readonly, nullable) NSURL *watchDirectoryURL __WATCHOS_UNAVAILABLE;

/** ------------------------- Watch App State ---------------------------
 *  State specific to the Watch app.
 */

/** Check if the companion app is installed on the paired iPhone. This only applies to Watch apps that can run independently. */
@property (nonatomic, readonly, getter=isCompanionAppInstalled) BOOL companionAppInstalled __IOS_UNAVAILABLE __WATCHOS_AVAILABLE(6.0);

/** -------------------------- Interactive Messaging ---------------------------
 *  Interactive messages can only be sent between two actively running apps.
 *  They require the counterpart app to be reachable.
 */

/** The counterpart app must be reachable for a send message to succeed. */
@property (nonatomic, readonly, getter=isReachable) BOOL reachable;

/** Reachability in the Watch app requires the paired iOS device to have been unlocked at least once after reboot. This property can be used to determine if the iOS device needs to be unlocked. If the reachable property is set to NO it may be because the iOS device has rebooted and needs to be unlocked. If this is the case, the Watch can show a prompt to the user suggesting they unlock their paired iOS device. */
@property (nonatomic, readonly) BOOL iOSDeviceNeedsUnlockAfterRebootForReachability __IOS_UNAVAILABLE __WATCHOS_AVAILABLE(2.0);

/** Clients can use this method to send messages to the counterpart app. Clients wishing to receive a reply to a particular message should pass in a replyHandler block. If the message cannot be sent or if the reply could not be received, the errorHandler block will be invoked with an error. If both a replyHandler and an errorHandler are specified, then exactly one of them will be invoked. Messages can only be sent while the sending app is running. If the sending app exits before the message is dispatched the send will fail. If the counterpart app is not running the counterpart app will be launched upon receiving the message (iOS counterpart app only). The message dictionary can only accept the property list types. */
- (void)sendMessage:(NSDictionary<NSString *, id> *)message replyHandler:(nullable void (^)(NSDictionary<NSString *, id> *replyMessage))replyHandler errorHandler:(nullable void (^)(NSError *error))errorHandler;

/** Clients can use this method to send message data. All the policies of send message apply to send message data. Send message data is meant for clients that have an existing transfer format and do not need the convenience of the send message dictionary. */
- (void)sendMessageData:(NSData *)data replyHandler:(nullable void (^)(NSData *replyMessageData))replyHandler errorHandler:(nullable void (^)(NSError *error))errorHandler;



/** --------------------------- Background Transfers ---------------------------
 *  Background transfers continue transferring when the sending app exits. The
 *  counterpart app (other side) is not required to be running for background
 *  transfers to continue. The system will transfer content at opportune times.
 */

/** Setting the applicationContext is a way to transfer the latest state of an app. After updating the applicationContext, the system initiates the data transfer at an appropriate time, which can occur after the app exits. The counterpart app will receive a delegate callback on next launch if the applicationContext has successfully arrived. If there is no app context, it should be updated with an empty dictionary. The applicationContext dictionary can only accept the property list types. */
@property (nonatomic, readonly, copy) NSDictionary<NSString *, id> *applicationContext;
- (BOOL)updateApplicationContext:(NSDictionary<NSString *, id> *)applicationContext error:(NSError **)error;

/** Stores the most recently received applicationContext from the counterpart app. */
@property (nonatomic, readonly, copy) NSDictionary<NSString *, id> *receivedApplicationContext;


/** The system will enqueue the user info dictionary and transfer it to the counterpart app at an opportune time. The transfer of user info will continue after the sending app has exited. The counterpart app will receive a delegate callback on next launch if the file has successfully arrived. The userInfo dictionary can only accept the property list types.
 */
- (WCSessionUserInfoTransfer *)transferUserInfo:(NSDictionary<NSString *, id> *)userInfo;

/** Enqueues a user info dictionary containing the most current information for an enabled complication. If the app's complication is enabled the system will try to transfer this user info immediately. Once a current complication user info is received the system will launch the Watch App Extension in the background and allow it to update the complication content. If the current user info cannot be transferred (i.e. devices disconnected, out of background launch budget, etc.) it will wait in the outstandingUserInfoTransfers queue until next opportune time. There can only be one current complication user info in the outstandingUserInfoTransfers queue. If a current complication user info is outstanding (waiting to transfer) and -transferCurrentComplicationUserInfo: is called again with new user info, the new user info will be tagged as current and the previously current user info will be untagged. The previous user info will however stay in the queue of outstanding transfers. */
- (WCSessionUserInfoTransfer *)transferCurrentComplicationUserInfo:(NSDictionary<NSString *, id> *)userInfo __WATCHOS_UNAVAILABLE;

/** Returns an array of user info transfers that are still transferring (i.e. have not been cancelled, failed, or been received by the counterpart app).*/
@property (nonatomic, readonly, copy) NSArray<WCSessionUserInfoTransfer *> *outstandingUserInfoTransfers;


/** The system will enqueue the file and transfer it to the counterpart app at an opportune time. The transfer of a file will continue after the sending app has exited. The counterpart app will receive a delegate callback on next launch if the file has successfully arrived. The metadata dictionary can only accept the property list types. */
- (WCSessionFileTransfer *)transferFile:(NSURL *)file metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/** Returns an array of file transfers that are still transferring (i.e. have not been cancelled, failed, or been received by the counterpart app). */
@property (nonatomic, readonly, copy) NSArray<WCSessionFileTransfer *> *outstandingFileTransfers;

@end


/** ----------------------------- WCSessionDelegate -----------------------------
 *  The session calls the delegate methods when content is received and session
 *  state changes. All delegate methods will be called on the same queue. The
 *  delegate queue is a non-main serial queue. It is the client's responsibility
 *  to dispatch to another queue if neccessary.
 */
@protocol WCSessionDelegate <NSObject>

/** Called when the session has completed activation. If session state is WCSessionActivationStateNotActivated there will be an error with more details. */
- (void)session:(WCSession *)session activationDidCompleteWithState:(WCSessionActivationState)activationState error:(nullable NSError *)error __IOS_AVAILABLE(9.3) __WATCHOS_AVAILABLE(2.2);

/** ------------------------- iOS App State For Watch ------------------------ */

/** Called when the session can no longer be used to modify or add any new transfers and, all interactive messages will be cancelled, but delegate callbacks for background transfers can still occur. This will happen when the selected watch is being changed. */
- (void)sessionDidBecomeInactive:(WCSession *)session __IOS_AVAILABLE(9.3) __WATCHOS_UNAVAILABLE;

/** Called when all delegate callbacks for the previously selected watch has occurred. The session can be re-activated for the now selected watch using activateSession. */
- (void)sessionDidDeactivate:(WCSession *)session __IOS_AVAILABLE(9.3) __WATCHOS_UNAVAILABLE;

@optional

/** Called when any of the Watch state properties change. */
- (void)sessionWatchStateDidChange:(WCSession *)session __WATCHOS_UNAVAILABLE;

/** Called when the installed state of the Companion app changes. */
- (void)sessionCompanionAppInstalledDidChange:(WCSession *)session __IOS_UNAVAILABLE __WATCHOS_AVAILABLE(6.0);

/** ------------------------- Interactive Messaging ------------------------- */

/** Called when the reachable state of the counterpart app changes. The receiver should check the reachable property on receiving this delegate callback. */
- (void)sessionReachabilityDidChange:(WCSession *)session;

/** Called on the delegate of the receiver. Will be called on startup if the incoming message caused the receiver to launch. */
- (void)session:(WCSession *)session didReceiveMessage:(NSDictionary<NSString *, id> *)message;

/** Called on the delegate of the receiver when the sender sends a message that expects a reply. Will be called on startup if the incoming message caused the receiver to launch. */
- (void)session:(WCSession *)session didReceiveMessage:(NSDictionary<NSString *, id> *)message replyHandler:(void(^)(NSDictionary<NSString *, id> *replyMessage))replyHandler;

/** Called on the delegate of the receiver. Will be called on startup if the incoming message data caused the receiver to launch. */
- (void)session:(WCSession *)session didReceiveMessageData:(NSData *)messageData;

/** Called on the delegate of the receiver when the sender sends message data that expects a reply. Will be called on startup if the incoming message data caused the receiver to launch. */
- (void)session:(WCSession *)session didReceiveMessageData:(NSData *)messageData replyHandler:(void(^)(NSData *replyMessageData))replyHandler;


/** -------------------------- Background Transfers ------------------------- */

/** Called on the delegate of the receiver. Will be called on startup if an applicationContext is available. */
- (void)session:(WCSession *)session didReceiveApplicationContext:(NSDictionary<NSString *, id> *)applicationContext;

/** Called on the sending side after the user info transfer has successfully completed or failed with an error. Will be called on next launch if the sender was not running when the user info finished. */
- (void)session:(WCSession * __nonnull)session didFinishUserInfoTransfer:(WCSessionUserInfoTransfer *)userInfoTransfer error:(nullable NSError *)error;

/** Called on the delegate of the receiver. Will be called on startup if the user info finished transferring when the receiver was not running. */
- (void)session:(WCSession *)session didReceiveUserInfo:(NSDictionary<NSString *, id> *)userInfo;

/** Called on the sending side after the file transfer has successfully completed or failed with an error. Will be called on next launch if the sender was not running when the transfer finished. */
- (void)session:(WCSession *)session didFinishFileTransfer:(WCSessionFileTransfer *)fileTransfer error:(nullable NSError *)error;

/** Called on the delegate of the receiver. Will be called on startup if the file finished transferring when the receiver was not running. The incoming file will be located in the Documents/Inbox/ folder when being delivered. The receiver must take ownership of the file by moving it to another location. The system will remove any content that has not been moved when this delegate method returns. */
- (void)session:(WCSession *)session didReceiveFile:(WCSessionFile *)file;


@end

NS_ASSUME_NONNULL_END
