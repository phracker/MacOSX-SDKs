//
//  PKPushRegistry.h
//  PushKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushKit/PKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// A push type for Voice-over-IP (VoIP) call invitations.
///
/// Use this type of notification to initiate live voice calls over the network.
/// Apps receiving VoIP push notifications must report the call quickly to
/// CallKit, so it can alert the user to the presence of the incoming call. For
/// apps linked against the iOS 13 SDK or later, the system terminates your app
/// if you fail to report these notifications to CallKit. If your app repeatedly
/// fails to report VoIP notifications to CallKit, the system stops launching
/// your app for VoIP push notifications.
///
/// Don't use this type of notification for anything other than initiating VoIP
/// calls. If you don't want to post the CallKit call interface, handle
/// notifications with the
/// <doc://com.apple.documentation/documentation/usernotifications> framework
/// instead of ``PushKit``. When sending encrypted content, use a Notification
/// Service Extension to decrypt that content before displaying it to the user.
/// You can also use a Notification Content Extension to display a custom
/// interface for your app's notifications. For more information, see
/// <doc://com.apple.documentation/documentation/usernotifications/modifying_content_in_newly_delivered_notifications>
/// and
/// <doc://com.apple.documentation/documentation/usernotificationsui/customizing_the_appearance_of_notifications>.
PK_EXPORT PKPushType const PKPushTypeVoIP API_AVAILABLE(ios(9.0), macCatalyst(14.0), watchos(9.0), visionos(1.0)) API_UNAVAILABLE(macos, tvos);
/// A push type for watchOS complications.
///
/// Use this type of notification to deliver updated data related for your
/// watchOS app’s complication. The watchOS app’s complication must be active on
/// the user’s current clock face. If it is not, the system does not deliver
/// pushes of this type. For watchOS 6 and later, send the push notification
/// directly to Apple Watch. For watchOS 5 and earlier, you must send it to the
/// iOS companion instead.
///
/// The time your watchOS app spends processing these push notifications counts
/// against the budget allotted to your complication for updating itself. Don't
/// start any long-running tasks when processing the notification payload. In
/// fact, it is recommended that you include all needed data in the payload so
/// that your app can process that data quickly.
///
/// The system limits you to 50 push notifications per day. If you exceed the
/// limit, subsequent pushes are not delivered.
PK_EXPORT PKPushType const PKPushTypeComplication API_AVAILABLE(watchos(6.0)) API_DEPRECATED("Complication pushes are supported directly on watchOS now, so this should no longer be used on iOS.", ios(9.0, 13.0), macCatalyst(9.0, 13.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, tvos);
/// A push type for file provider updates.
///
/// Use file provider notifications to update your File Provider extension's content
/// from your server. For more information, see <doc://com.apple.documentation/documentation/fileprovider/nonreplicated_file_provider_extension/content_and_change_tracking/tracking_your_file_provider_s_changes>.
/// 
PK_EXPORT PKPushType const PKPushTypeFileProvider API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(13.0), visionos(1.0)) API_UNAVAILABLE(watchos, tvos);


@protocol PKPushRegistryDelegate;
@class PKPushCredentials, PKPushPayload;

/// An object that requests the delivery and handles the receipt of PushKit notifications.
///
/// A `PKPushRegistry` object manages only certain types of notifications,
/// such as high-priority notifications needed by a VoIP app. PushKit wakes up your app
/// as needed to deliver incoming notifications and delivers the notifications directly
/// to the push registry object that requested them.
///
/// Every time your app launches, whether in the foreground or in the background, create
/// a push registry object and configure it. Typically, you keep the push registry object
/// running for the duration of your app. Each push registry object delivers incoming
/// notifications to its ``PushKit/PKPushRegistry/delegate`` object, which also handles
/// the responses for registration requests. The listing below shows how to create
/// a push registry object and request VoIP notifications. Always assign an appropriate
/// delegate object before modifying the ``PushKit/PKPushRegistry/desiredPushTypes``
/// property.
///
/// ```objc
/// - (void) registerForVoIPPushes {
///    self.voipRegistry = [[PKPushRegistry alloc] initWithQueue:nil];
///    self.voipRegistry.delegate = self;
///
///    // Initiate registration.
///    self.voipRegistry.desiredPushTypes = [NSSet setWithObject:PKPushTypeVoIP];
/// }
/// ```
///
/// Assigning a new value to the ``PushKit/PKPushRegistry/desiredPushTypes`` property
/// registers the push registry object with the PushKit servers. The server reports the
/// success or failure of your registration attempts asynchronously to the push registry,
/// which then reports those results to its delegate object. The push registry also delivers
/// all received notifications to the delegate object. For more information about the
/// delegate methods, see ``PushKit/PKPushRegistryDelegate``.
///
/// ## Topics
///
/// ### Initializing a Push Registry
///
/// - ``PushKit/PKPushRegistry/initWithQueue:``
///
/// ### Receiving the Notification Data
///
/// - ``PushKit/PKPushRegistry/delegate``
/// - ``PushKit/PKPushRegistryDelegate``
///
/// ### Managing the Push Registry
///
/// - ``PushKit/PKPushRegistry/desiredPushTypes``
/// - ``PushKit/PKPushRegistry/pushTokenForType:``
///
API_AVAILABLE(macos(10.15), macCatalyst(13.0), ios(8.0), watchos(6.0), tvos(13.0))
@interface PKPushRegistry : NSObject

/// The delegate object that receives notifications coming from the push registry object.
///
/// You must assign a valid object to this property before modifying the ``PushKit/PKPushRegistry/desiredPushTypes``
/// property. A valid delegate object is required to receive push tokens and payload
/// data from incoming pushes.
///
/// For more information about the methods of the `PKPushRegistryDelegate`
/// protocol, see ``PushKit/PKPushRegistryDelegate``.
/// 
@property (readwrite,weak,nullable) id<PKPushRegistryDelegate> delegate;

/// Registers the push types for this push registry object.
///
/// When you assign a value to this property, the push registry object makes a registration
/// request with the PushKit server. This request is asynchronous, and the success or
/// failure of the request is reported to your registery's delegate object. For a successful
/// registration, PushKit delivers a push token to the delegate. Use that token to generate
/// push requests from your server.
///
/// For a list of push types that you may include in the set, see ``PushKit/PKPushType``.
///
@property (readwrite,copy,nullable) NSSet<PKPushType> *desiredPushTypes;

/// Retrieves the locally cached push token for the specified push type.
///
/// If registration for a specific push type is successful, the push registry delivers
/// the corresponding push token to its delegate and adds a copy of the token to its
/// local cache. Use this method to retrieve the token at a later time.
///
/// - Parameters:
///   - type: A push type requested by this push registry object. For a list of possible types,
/// see ``PushKit/PKPushType``.
///
/// - Returns: The push token used to send pushes to the device or `nil` if no token is available
/// for the specified type.
/// 
- (nullable NSData *)pushTokenForType:(PKPushType)type;

/// Creates a push registry with the specified dispatch queue.
///
/// - Parameters:
///   - queue: The dispatch queue on which to execute the delegate methods. It is recommended that
/// you specify a serial queue for this parameter. Specify `nil` to execute the delegate
/// methods on the app’s main queue.
///
/// - Returns: A `PKPushRegistry` object that you can use to register for push tokens and use to
/// receive notifications.
/// 
- (instancetype)initWithQueue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

/*!
 @method        init
 @abstract      Unavailable, use -initWithQueue: instead.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

/// The methods that you use to handle incoming PushKit notifications and registration
/// events.
///
/// Implement the methods of this protocol in an object of your app and assign that object
/// to the ``PushKit/PKPushRegistry/delegate`` property of your `PKPushRegistry`
/// object. Use the methods of this protocol to process incoming notifications and to
/// react to token registration and invalidation.
///
/// ## Topics
///
/// ### Responding to Registration Events
///
/// - ``PushKit/PKPushRegistryDelegate/pushRegistry:didUpdatePushCredentials:forType:``
/// - ``PushKit/PKPushRegistryDelegate/pushRegistry:didInvalidatePushTokenForType:``
///
/// ### Handling an Incoming Notification
///
/// - ``PushKit/PKPushRegistryDelegate/pushRegistry:didReceiveIncomingPushWithPayload:forType:withCompletionHandler:``
///
/// ### Deprecated Methods
///
/// - ``PushKit/PKPushRegistryDelegate/pushRegistry:didReceiveIncomingPushWithPayload:forType:``
///
///
@protocol PKPushRegistryDelegate <NSObject>

@required

/// Tells the delegate that the system updated the credentials for the specified type
/// of push notification.
///
/// The system calls this method when it receives new credentials (including a push token)
/// for the specified push type.
///
/// - Parameters:
///   - registry: The ``PushKit/PKPushRegistry`` instance responsible for the delegate callback.
///   - credentials: The push credentials that can be used to send pushes to the device for the specified push type.
///   - type: One of the requested notification types. This type is present in the ``PushKit/PKPushRegistry/desiredPushTypes`` property of the push registry.
/// 
- (void)pushRegistry:(PKPushRegistry *)registry didUpdatePushCredentials:(PKPushCredentials *)pushCredentials forType:(PKPushType)type;


@optional

/// Notifies the delegate that a remote push has been received.
///
/// This method is invoked when a push notification has been received for the
/// specified push type.
///
/// - Parameters:
///   - registry: The ``PKPushRegistry`` instance responsible for the delegate callback.
///   - payload: The push payload sent by a developer via APNS server API.
///   - type: This is a ``PushKit/PKPushType`` constant, which is present in `[registry desiredPushTypes]`.
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type API_DEPRECATED_WITH_REPLACEMENT("-pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void(^)(void))completion", ios(8.0, 11.0), macCatalyst(8.0, 11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/// Tells the delegate that a remote push notification arrived.
///
/// The system calls this method when it receives a push notification for the specified
/// push type. Use this method to extract data from the notification's payload and to
/// perform the relevant task for that data. For example, use this method to update the
/// complication data of your watchOS app. When you finish the task, execute the provided
/// `completion` handler block to let PushKit know you are finished.
///
/// When linking against the iOS 13 SDK or later, your implementation of this method
/// must report notifications of type ``PushKit/PKPushTypeVoIP`` to the <doc://com.apple.documentation/documentation/callkit>
/// framework by calling the <doc://com.apple.documentation/documentation/callkit/cxprovider/1930694-reportnewincomingcallwithuuid>
/// method of your app's <doc://com.apple.documentation/documentation/callkit/cxprovider>
/// object. When you call that method, the system displays the standard incoming call
/// interface to the user unless an error occurs. For example, the system reports an
/// error if the user enabled Do Not Disturb. You may establish a connection to your
/// VoIP server in tandem with notify CallKit.
///
/// > Important: On iOS 13.0 and later, if you fail to report a call to CallKit, the
/// system will terminate your app. Repeatedly failing to report calls may cause the
/// system to stop delivering any more VoIP push notifications to your app. If you want
/// to initiate a VoIP call without using CallKit,
/// register for push notifications using the User Notifications
/// framework instead of PushKit. For more information, see <doc://com.apple.documentation/documentation/usernotifications>.
///
/// - Parameters:
///   - registry: The ``PushKit/PKPushRegistry`` instance responsible for the delegate callback.
///   - payload: The push payload sent by a developer via APNs server API.
///   - type: This is a ``PushKit/PKPushType`` constant, which is present in `[registry desiredPushTypes]`.
///   - completion: The notification's completion handler. Execute this block when you finish processing the notification.
/// 
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void(^)(void))completion API_AVAILABLE(macos(10.15), macCatalyst(13.0), ios(11.0), watchos(6.0), tvos(13.0));

/// Tells the delegate that the system invalidated the push token for the specified type.
///
/// The system calls this method when a previously provided push token is no longer valid
/// for use. No action is necessary on your part to reregister the push type. Instead,
/// use this method to notify your server not to send push notifications using the matching
/// push token.
///
/// - Parameters:
///   - registry: The ``PushKit/PKPushRegistry`` instance responsible for the delegate callback.
///   - type: This is a ``PushKit/PKPushType`` constant, which is present in `[registry desiredPushTypes]`.
///
/// 
- (void)pushRegistry:(PKPushRegistry *)registry didInvalidatePushTokenForType:(PKPushType)type;

@end

NS_ASSUME_NONNULL_END
