//
//  PKPushRegistry.h
//  PushKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushKit/PKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/* PKPushType constants can be used to register for a PKPushType-specific push token or to identify received push
   notifications.
 */
PK_EXPORT PKPushType const PKPushTypeVoIP API_AVAILABLE(ios(9.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, watchos, tvos);
PK_EXPORT PKPushType const PKPushTypeComplication API_AVAILABLE(watchos(6.0)) API_DEPRECATED("Complication pushes are supported directly on watchOS now, so this should no longer be used on iOS.", ios(9.0, 13.0), macCatalyst(9.0, 13.0))  API_UNAVAILABLE(macos, tvos);
PK_EXPORT PKPushType const PKPushTypeFileProvider API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos, tvos);

@protocol PKPushRegistryDelegate;
@class PKPushCredentials, PKPushPayload;

/*!
 @class         PKPushRegistry
 @abstract      An instance of this class can be used to register for 3rd party notifications. The supported push
                notification types are listed above as PKPushType constants.
 */
API_AVAILABLE(macos(10.15), macCatalyst(13.0), ios(8.0), watchos(6.0), tvos(13.0))
@interface PKPushRegistry : NSObject

/*!
 @property      delegate
 @abstract      Setting a delegate is required to receive device push tokens and incoming pushes.
 */
@property (readwrite,weak,nullable) id<PKPushRegistryDelegate> delegate;

/*!
 @property      desiredPushTypes
 @abstract      An app requests registration for various types of pushes by setting this NSSet to the desired
                PKPushType constants. Push tokens and notifications will be delivered via delegate callback.
 */
@property (readwrite,copy,nullable) NSSet<PKPushType> *desiredPushTypes;

/*!
 @method        pushTokenForType:
 @abstract      Access the locally cached push token for a specified PKPushType.
 @discussion    A push token returned here has previously been given to the delegate via handlePushTokenUpdate:forType:
                callback.
 @param         type
                This is a PKPushType constant that is already in desiredPushTypes.
 @result        Returns the push token that can be used to send pushes to the device for the specified PKPushType.
                Returns nil if no push token is available for this PKPushType at the time of invocation.
 */
- (nullable NSData *)pushTokenForType:(PKPushType)type;

/*!
 @method        initWithQueue:
 @abstract      Instantiates a PKPushRegistry with a delegate callback dispatch queue.
 @param         queue
                All delegate callbacks are performed asynchronously by PKPushRegistry on this queue.
 @result        A PKPushRegistry instance that can be used to register for push tokens and notifications for supported
                push types.
 */
- (instancetype)initWithQueue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

/*!
 @method        init
 @abstract      Unavailable, use -initWithQueue: instead.
 */
- (instancetype)init NS_UNAVAILABLE;

@end


@protocol PKPushRegistryDelegate <NSObject>

@required

/*!
 @method        pushRegistry:didUpdatePushCredentials:forType:
 @abstract      This method is invoked when new credentials (including push token) have been received for the specified
                PKPushType.
 @param         registry
                The PKPushRegistry instance responsible for the delegate callback.
 @param         pushCredentials
                The push credentials that can be used to send pushes to the device for the specified PKPushType.
 @param         type
                This is a PKPushType constant which is present in [registry desiredPushTypes].
 */
- (void)pushRegistry:(PKPushRegistry *)registry didUpdatePushCredentials:(PKPushCredentials *)pushCredentials forType:(PKPushType)type;


@optional

/*!
 @method        pushRegistry:didReceiveIncomingPushWithPayload:forType:
 @abstract      This method is invoked when a push notification has been received for the specified PKPushType.
 @param         registry
                The PKPushRegistry instance responsible for the delegate callback.
 @param         payload
                The push payload sent by a developer via APNS server API.
 @param         type
                This is a PKPushType constant which is present in [registry desiredPushTypes].
 */
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type API_DEPRECATED_WITH_REPLACEMENT("-pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void(^)(void))completion", ios(8.0, 11.0), macCatalyst(8.0, 11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 @method        pushRegistry:didReceiveIncomingPushWithPayload:forType:withCompletionHandler:
 @abstract      This method is invoked when a push notification has been received for the specified PKPushType.
 @param         registry
                The PKPushRegistry instance responsible for the delegate callback.
 @param         payload
                The push payload sent by a developer via APNS server API.
 @param         type
                This is a PKPushType constant which is present in [registry desiredPushTypes].
 @param         completion
                This completion handler should be called to signify the completion of payload processing.
 */
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void(^)(void))completion API_AVAILABLE(macos(10.15), macCatalyst(13.0), ios(11.0), watchos(6.0), tvos(13.0));

/*!
 @method        pushRegistry:didInvalidatePushTokenForType:
 @abstract      This method is invoked if a previously provided push token is no longer valid for use. No action is
                necessary to rerequest registration. This feedback can be used to update an app's server to no longer
                send push notifications of the specified type to this device.
 @param         registry
                The PKPushRegistry instance responsible for the delegate callback.
 @param         type
                This is a PKPushType constant which is present in [registry desiredPushTypes].
 */
- (void)pushRegistry:(PKPushRegistry *)registry didInvalidatePushTokenForType:(PKPushType)type;

@end

NS_ASSUME_NONNULL_END
