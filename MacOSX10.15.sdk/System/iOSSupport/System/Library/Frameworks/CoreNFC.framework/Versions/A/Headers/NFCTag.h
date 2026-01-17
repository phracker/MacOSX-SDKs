//
//  NFCTag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCTag_h
#define NFCTag_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum NFCTagType
 *
 * @constant NFCTagTypeISO15693             ISO15693 tag.
 * @constant NFCTagTypeFeliCa               FeliCa tag.
 * @constant NFCTagTypeISO7816Compatible    ISO14443-4 type A / B tag with ISO7816 communication.
 * @constant NFCTagTypeMiFare               MiFare technology tag (MIFARE Plus, UltraLight, DESFire) base on ISO14443.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
typedef NS_ENUM(NSUInteger, NFCTagType) {
    NFCTagTypeISO15693 = 1,
    NFCTagTypeFeliCa API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) = 2,
    NFCTagTypeISO7816Compatible API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) = 3,
    NFCTagTypeMiFare API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) = 4,
};

@protocol NFCReaderSession;
@protocol NFCNDEFTag;
@protocol NFCISO15693Tag;
@protocol NFCISO7816Tag;
@protocol NFCMiFareTag;
@protocol NFCFeliCaTag;

/*!
 * @protocol NFCTag
 *
 * @discussion A NFC / RFID tag object conforms to this protocol.  The NFCReaderSession returns an instance of this type when a tag is detected.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCTag <NSObject, NSSecureCoding, NSCopying>

@required

/*!
 * @property type
 * 
 * @discussion See @link CNFCTagType @link/
 */
@property (nonatomic, readonly, assign) NFCTagType type;

/*!
 * @property    session
 *
 * @discussion  Session that provides this tag.
 */
@property (nonatomic, weak, readonly) id<NFCReaderSession> session;

/*!
 * @property available:
 *
 * @return      <i>YES</i> if tag is available in the current reader session.  A tag remove from the RF field will become
 *              unavailable.  Tag in disconnected state will return NO.
 *
 * @discussion  Check whether a detected tag is available.
 */
@property (nonatomic, getter=isAvailable, readonly) BOOL available;

/*!
 * @method asNFCISO15693Tag
 *
 * @return      Returns self if it conforms to the NFCISO15693Tag protocol; else returns nil.
 */
- (nullable id<NFCISO15693Tag>)asNFCISO15693Tag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method asNFCISO7816Tag
 *
 * @return      Returns self if it conforms to the NFCISO7816Tag protocol; else returns nil.
 */
- (nullable id<NFCISO7816Tag>)asNFCISO7816Tag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property asNFCFeliCaTag
 *
 * @discussion Returns nil if tag does not conform to NFCFeliCaTag.
 */
- (nullable id<NFCFeliCaTag>)asNFCFeliCaTag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property asNFCMiFareTag
 *
 * @discussion Returns nil if tag does not conform to NFCMiFareTag.
 */
- (nullable id<NFCMiFareTag>)asNFCMiFareTag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

#pragma mark - Tag command configuration

/*!
 * @interface   NFCTagCommandConfiguration
 *
 * @discussion  Define configuration parameters for tag commands.
 */
NS_EXTENSION_UNAVAILABLE("Not available to extensions") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCTagCommandConfiguration : NSObject<NSCopying>

/*!
 * @discussion  Maximum number of retries.  Valid value is 0 to 256.  Default is 0.
 */
@property (nonatomic, assign) NSUInteger maximumRetries;

/*!
 * @discussion  Delay in seconds before retry occurs.  Default is 0.
 */
@property (nonatomic, assign) NSTimeInterval retryInterval;

@end

NS_ASSUME_NONNULL_END

#endif /* NFCTag_h */
