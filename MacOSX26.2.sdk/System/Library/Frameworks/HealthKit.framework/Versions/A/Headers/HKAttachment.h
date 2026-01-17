//
//  HKAttachment.h
//  HealthKit
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <UniformTypeIdentifiers/UTType.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKAttachment
 @discussion    An HKAttachment represents a file attachment stored in the HealthKit database.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKAttachment : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      identifier
 @abstract      A unique identifier of the receiver in the HealthKit database.
 */
@property (copy, readonly) NSUUID *identifier;

/*!
 @property      name
 @abstract      Represents the name of the file.
 */
@property (copy, readonly) NSString *name;

/*!
 @property      contentType
 @abstract      The Uniform Type of the file.
 */
@property (copy, readonly) UTType *contentType;

/*!
 @property      size
 @abstract      The size in bytes of the file.
 */
@property (assign, readonly) NSInteger size;

/*!
 @property      creationDate
 @abstract      The date the receiver was created.
 */
@property (copy, readonly) NSDate *creationDate;

/*!
 @property      metadata
 @abstract      Extra information describing the attachment.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, or NSDate.
 */
@property (copy, readonly, nullable) NSDictionary<NSString *, id> *metadata;

/*!
 @method        init
 @abstract      The init method is unavailable. To create an attachment, use HKAttachmentStore.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        new
 @abstract      The new method is unavailable. To create an attachment, use HKAttachmentStore.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
