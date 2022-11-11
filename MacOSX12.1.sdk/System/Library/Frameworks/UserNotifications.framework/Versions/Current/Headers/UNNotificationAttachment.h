//
//  UNNotificationAttachment.h
//  UserNotification
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos)
@interface UNNotificationAttachment : NSObject <NSCopying, NSSecureCoding>

// The identifier of this attachment
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *identifier;

// The URL to the attachment's data. If you have obtained this attachment from UNUserNotificationCenter then the URL will be security-scoped.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSURL *URL;

// The UTI of the attachment.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *type;

// Creates an attachment for the data at URL with an optional options dictionary. URL must be a file URL. Returns nil if the data at URL is not supported.
+ (nullable instancetype)attachmentWithIdentifier:(NSString *)identifier URL:(NSURL *)URL options:(nullable NSDictionary *)options error:(NSError *__nullable *__nullable)error;

- (instancetype)init NS_UNAVAILABLE;

@end

// Key to manually provide a type hint for the attachment. If not set the type hint will be guessed from the attachment's file extension. Value must be an NSString.
extern NSString * const UNNotificationAttachmentOptionsTypeHintKey API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos);

// Key to specify if the thumbnail for this attachment is hidden. Defaults to NO. Value must be a boolean NSNumber.
extern NSString * const UNNotificationAttachmentOptionsThumbnailHiddenKey API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos);

// Key to specify a normalized clipping rectangle to use for the attachment thumbnail. Value must be a CGRect encoded using CGRectCreateDictionaryRepresentation.
extern NSString * const UNNotificationAttachmentOptionsThumbnailClippingRectKey API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos);

// Key to specify the animated image frame number or the movie time to use as the thumbnail.
// An animated image frame number must be an NSNumber. A movie time must either be an NSNumber with the time in seconds or a CMTime encoded using CMTimeCopyAsDictionary.
extern NSString * const UNNotificationAttachmentOptionsThumbnailTimeKey API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END
