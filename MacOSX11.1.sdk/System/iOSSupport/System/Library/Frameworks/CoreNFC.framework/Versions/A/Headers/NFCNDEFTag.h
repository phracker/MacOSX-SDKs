//
//  NFCNDEFTag.h
//  CoreNFC
//
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef NFCNDEFTag_h
#define NFCNDEFTag_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCNDEFMessage;

/*!
 * @enum NFCNDEFStatus
 *
 * @constant NFCNDEFStatusNotSupport    Tag is not NDEF formatted; NDEF read and write are disallowed.
 * @constant NFCNDEFStatusReadWrite     Tag is NDEF read and writable.
 * @constant NFCNDEFStatusReadOnly      Tag is NDEF read-only; NDEF writing is disallowed.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
typedef NS_ENUM(NSUInteger, NFCNDEFStatus) {
    NFCNDEFStatusNotSupported API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)  = 1,
    NFCNDEFStatusReadWrite API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)     = 2,
    NFCNDEFStatusReadOnly API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)      = 3,
};

/*!
 * @protocol NFCNDEFTag
 *
 * @discussion Operations on a NDEF formatted tag.  Unless it is specified all block completion handlers are dispatched on the session work queue that is associated with the tag.
 *
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCNDEFTag <NSObject, NSSecureCoding, NSCopying>

/*!
 * @property available:
 *
 * @return      <i>YES</i> if NDEF tag is available in the current reader session.  A tag remove from the RF field will become
 *              unavailable.  Tag in disconnected state will return NO.
 *
 * @discussion  Check whether a detected NDEF tag is available.
 */
@property (nonatomic, getter=isAvailable, readonly) BOOL available API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method queryNDEFStatusWithCompletionHandler:
 *
 * @param completionHandler Return the NFCNDEFStatus of the tag.  capacity indicates the maximum NDEF message size in bytes that can be store on the tag.
 *                          error returns a valid NSError object when query fails.
 *
 * @discussion Query the NDEF support status of the tag.
 */
- (void)queryNDEFStatusWithCompletionHandler:(void(^)(NFCNDEFStatus status, NSUInteger capacity, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readNDEFWithCompletionHandler:
 *
 * @param completionHandler Returns the NDEF message from read operation.  Successful read would return a valid NFCNDEFMessage object with NSError object set to nil;
 *                          read failure returns a nil NFCNDEFMessage and a valid NSError object.
 *
 * @discussion Reads NDEF message from the tag.
 */
- (void)readNDEFWithCompletionHandler:(void(^)(NFCNDEFMessage * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeNDEF:completionHandler:
 *
 * @param completionHandler  Returns operation status.  A nil NSError object indicates a successful write operation.
 *
 * @discussion Writes a NDEF message to the tag.
 */
- (void)writeNDEF:(NFCNDEFMessage *)ndefMessage completionHandler:(void(^)(NSError * _Nullable))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeLockWithCompletionHandler:
 *
 * @param completionHandler Returns operation status. A nil NSError object indicates a successful lock operation.
 *
 * @discussion Locks the NDEF tag to read-only state; tag can no longer be written afterward.  This is a permanent operation.  A successful lock operaiton via this method
 *             will change the NFCNDEFStatus value of the tag to @link NFCNDEFStatusReadOnly @link/.
 */
- (void)writeLockWithCompletionHandler:(void(^)(NSError * _Nullable))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif
