//
//  PKPushCredentials.h
//  PushKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushKit/PKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that encapsulates the device token you use to deliver push notifications
/// to your app.
///
/// When registering your app's push types, PushKit creates a ``PushKit/PKPushCredentials``
/// object for each type your app supports and delivers it to your delegate's ``PushKit/PKPushRegistryDelegate/pushRegistry:didUpdatePushCredentials:forType:``
/// method. Don't create ``PushKit/PKPushCredentials`` objects yourself.
/// 
API_AVAILABLE(macos(10.15), macCatalyst(13.0), ios(8.0), watchos(6.0), tvos(13.0), visionos(1.0))
@interface PKPushCredentials : NSObject

/// The push type constant associated with the token.
///
/// For possible values, see ``PushKit/PKPushType``.
@property (readonly,copy) PKPushType type;
/// A unique device token to use when sending push notifications to the current device.
///
/// Forward this token to the server you use to generate push notifications. When preparing
/// to deliver a push notification to the current device, include the token in the HTTP
/// request you send to Apple Push Notification service (APNs).
///
@property (readonly,copy) NSData *token;

@end

NS_ASSUME_NONNULL_END
