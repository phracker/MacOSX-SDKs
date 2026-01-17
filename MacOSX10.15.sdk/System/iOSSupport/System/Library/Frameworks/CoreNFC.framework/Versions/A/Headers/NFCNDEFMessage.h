//
//  NFCNDEFMessage.h
//  CoreNFC
//
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef NFCNDEFMessage_h
#define NFCNDEFMessage_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCNDEFPayload;
/*!
 * @class NFCNDEFMessage
 *
 * @discussion A NDEF message consists of payload records.  The maximum size of the NDEF message is limited to 128KB.
 */
NS_EXTENSION_UNAVAILABLE("Not available to extensions") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFMessage : NSObject<NSSecureCoding>

/*!
 * @property records
 *
 * @discussion Array of NFCNDEFPayload records contained in this message.
 */
@property (nonatomic, copy) NSArray<NFCNDEFPayload *> *records API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property length
 *
 * @discussion Length of the resulting NDEF message in bytes as it would be stored on a NFC tag.
 */
@property (nonatomic, readonly) NSUInteger length API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithNDEFRecords:
 *
 * @param records  NSArray of NFCNDEFPayload object.  An empty array will create an empty NDEF message.
 */
- (instancetype)initWithNDEFRecords:(NSArray<NFCNDEFPayload *> *)records API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method ndefMessageWithData:
 *
 * @param data  NSData storing raw bytes of a complete NDEF message.  The data content will be validated; all NDEF payloads must
 *              be valid according to the NFC Forum NDEF RTD specification and it shall only contain a single NDEF message.
 *
 */
+ (_Nullable instancetype)ndefMessageWithData:(NSData *)data API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCNDEFMessage_h */
