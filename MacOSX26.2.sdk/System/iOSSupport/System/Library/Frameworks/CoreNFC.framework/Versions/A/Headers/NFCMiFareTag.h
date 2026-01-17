//
//  NFCMiFareTag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCMiFareTag_h
#define NFCMiFareTag_h

#import <Foundation/Foundation.h>
#import <CoreNFC/NFCNDEFTag.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NFCTag, NFCNDEFTag;
@class NFCISO7816APDU;

/*!
 * @enum NFCMiFareFamily
 *
 * @constant NFCMiFareUnknown       MiFare compatible ISO14443 Type A tag.
 * @constant NFCMiFareUltralight    MiFare Ultralight series.
 * @constant NFCMiFarePlus          MiFare Plus series.
 * @constant NFCMiFareDESFire       MiFare DESFire series.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)
typedef NS_ENUM(NSUInteger, NFCMiFareFamily) {
    NFCMiFareUnknown API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)       = 1,
    NFCMiFareUltralight API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)    = 2,
    NFCMiFarePlus API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)          = 3,
    NFCMiFareDESFire API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)       = 4,
};


/*!
 * @protocol NFCMiFareTag
 *
 * @discussion  A @link NFCTagReaderSession @link/ reader session returns an instance conforming to this protocol when a MiFare tag is detected.  Unless it is specified
 *              all block completion handlers are dispatched on the session work queue that is associated with the tag.  Your process requires to include the
 *              "com.apple.developer.nfc.readersession.formats" entitlement to receive this tag object from the @link NFCTagReaderSessionDelegate @link/ delegate.
 *              Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.
 *              @link NFCReaderErrorSecurityViolation @link/ will be returned from the @link NFCTagReaderSessionDelegate @link/ invalidation method if the required entitlement
 *              is missing when session is started.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)
@protocol NFCMiFareTag <NFCTag, NFCNDEFTag>

/*!
 * @property mifareFamily   MiFare product type identifier.
 */
@property (nonatomic, readonly, assign) NFCMiFareFamily mifareFamily API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos);

/*!
 * @discussion The hardware UID of the tag.
 */
@property (nonatomic, readonly, copy) NSData *identifier API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos);

/*!
 * @discussion The optional historical bytes extracted from the Answer To Select response.
 */
@property (nonatomic, readonly, copy, nullable) NSData *historicalBytes API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos);

/*!
 * @method sendMiFareCommand:completionHandler:
 *
 * @param command           The complete MiFare command.  CRC bytes are calculated and inserted automatically to the provided packet data frame.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds. A @link NFCErrorDomain @link/ error
 *                          is returned when there is a communication issue with the tag. Successfully read data blocks will be returned from the NSData object.
 *
 * @discussion              Send native MIFARE command to a tag.  Support MIFARE UltraLight, Plus, and DESFire products.
 *                          Crypto1 protocol is not supported.  Command chaining is handled internally by the method and the full response composed of the
 *                          individual fragment is returned in the completion handler.
 */
- (void)sendMiFareCommand:(NSData *)command
        completionHandler:(void(^)(NSData *response, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos);

/*!
 * @method sendMiFareISO7816Command:completionHandler:
 *
 * @param apdu              The ISO7816-4 command APDU object.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag or tag does not support ISO7816-4 commands,
 *                          and all other parameters should be ignore.
 *
 * @discussion  Send a ISO7816 command APDU to the tag and receives a response APDU.  Only available when @link mifareFamily @link/ returns NFCMiFarePlus, NFCMiFareDESFire.
 */
- (void)sendMiFareISO7816Command:(NFCISO7816APDU *)apdu
      completionHandler:(void(^)(NSData *responseData, uint8_t sw1, uint8_t sw2, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCMiFareTag_h */
