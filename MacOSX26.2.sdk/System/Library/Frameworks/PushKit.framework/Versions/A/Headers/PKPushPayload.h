//
//  PKPushPayload.h
//  PushKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushKit/PKDefines.h>

NS_ASSUME_NONNULL_BEGIN
/// An object that contains information about a received PushKit notification.
///
/// ## Topics
///
/// ### Payload Data
///
/// - ``PushKit/PKPushPayload/dictionaryPayload``
/// - ``PushKit/PKPushPayload/type``
///
API_AVAILABLE(macos(10.15), macCatalyst(13.0), ios(8.0), watchos(6.0), tvos(13.0), visionos(1.0))
@interface PKPushPayload : NSObject

/// The type value indicating how to interpret the payload.
///
/// For possible values, see ``PushKit/PKPushType``.
@property (readonly,copy) PKPushType type;
/// The contents of the received payload.
///
/// For VoIP pushes, the sender is free to specify any fields for the contained data
/// as long as it is provided in a text-encodable JSON format.
@property (readonly,copy) NSDictionary *dictionaryPayload;

@end

NS_ASSUME_NONNULL_END
