//
//  NFCISO7816Tag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCISO7816Tag_h
#define NFCISO7816Tag_h

#import <Foundation/Foundation.h>
#import <CoreNFC/NFCNDEFTag.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class NFCISO7816APDU
 *
 * @discussion ISO7816 Application Data Unit (APDU).
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO7816APDU : NSObject<NSCopying>
/*!
 * @property instructionClass   Class (CLA) byte.
 */
@property (nonatomic, readonly, assign) uint8_t instructionClass;

/*!
 * @property instructionCode    Instruction (INS) byte.
 */
@property (nonatomic, readonly, assign) uint8_t instructionCode;

/*!
 * @property p1Parameter     P1 parameter.
 */
@property (nonatomic, readonly, assign) uint8_t p1Parameter;

/*!
 * @property p2Parameter     P2 parameter.
 */
@property (nonatomic, readonly, assign) uint8_t p2Parameter;

/*!
 * @property data   Data field; nil if data field is absent
 */
@property (nonatomic, readonly, copy, nullable) NSData *data;

/*!
 * @property expectedResponseLength     Expected response length (Le).  -1 means no response data field is expected.
 */
@property (readonly, assign, nonatomic) NSInteger expectedResponseLength;

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithInstructionClass:instructionCode:p1Parameter:p2Parameter:data:expectedResponseLength:
 *
 * @param instructionClass  Instruction class (CLA) byte
 * @param instructionCode   Instruction code (INS) byte
 * @param p1Parameter       P1 parameter byte
 * @param p2Parameter       P2 parameter byte
 * @param data              Data to transmit.  Value of Lc field is set according to the data size.
 * @param expectedResponseLength Response data length (Le) in bytes. Valid range is from 1 to 65536 inclusively;
 *                               -1 means no response data field is expected.  Use 256 if you want to send '00' as the short Le field
 *                               assuming the data field is less than 256 bytes.  Use 65536 if you want to send '0000' as the extended
 *                               Le field.
 *
 * @discussion  Generates an ISO7816 APDU object.  The Lc value is generated base on the size of the data object; possible value ranges from
 *              1 to 65535 inclusively.  Use @link -initWithData: @link/ in cases where a finer control on the APDU format is required.
 */
- (instancetype)initWithInstructionClass:(uint8_t)instructionClass
                         instructionCode:(uint8_t)instructionCode
                             p1Parameter:(uint8_t)p1Parameter
                             p2Parameter:(uint8_t)p2Parameter
                                    data:(NSData *)data
                  expectedResponseLength:(NSInteger)expectedResponseLength;

/*!
 * @method initWithData:
 *
 * @param data  Data buffer containing the full APDU.
 *
 * @return nil if input data does not contain a valid APDU.
 */
- (_Nullable instancetype)initWithData:(NSData *)data;

@end

@protocol NFCTag, NFCNDEFTag;
/*!
 * @protocol NFCISO7816Tag
 *
 * @discussion  A @link NFCTagReaderSession @link/ reader session returns an instance conforming to this protocol
 *              when an ISO7816 compatible tag is detected.  Unless it is specified all block completion handlers are dispatched on the
 *              session work queue that is associated with the tag.  Your process requires to include the
 *              "com.apple.developer.nfc.readersession.formats" entitlement and the "com.apple.developer.nfc.readersession.iso7816.select-identifiers"
 *              key in the application's Info.plist to receive this tag object from the @link NFCTagReaderSessionDelegate @link/ delegate.
 *              @link NFCReaderErrorSecurityViolation @link/ will be returned from the @link NFCTagReaderSessionDelegate @link/ invalidation
 *              method if the required entitlement is missing or "com.apple.developer.nfc.readersession.iso7816.select-identifiers" does not contain
 *              at least one valid entry.
 *              When the reader discovered a compatible ISO7816 tag it automatically performs a SELECT command (by DF name) using the values provided in
 *              "com.apple.developer.nfc.readersession.iso7816.select-identifiers" in the specified array order.  The tag is
 *              returned from the [NFCTagReaderSessionDelegate readerSession:didDetectTags:] call on the first successful SELECT command.
 *              The initialSelectedAID property returns the application identifier of the selected application.  Tag will not be returned
 *              to the NFCTagReaderSessionDelegate if no application described in "com.apple.developer.nfc.readersession.iso7816.select-identifiers"
 *              is found.  Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.
 *
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCISO7816Tag <NFCTag, NFCNDEFTag>

/*!
 * @property initialSelectedAID The Hex string of the application identifier (DF name) selected by the reader when the tag is discovered.
 *                              This will match one of the entries in the "com.apple.developer.nfc.readersession.iso7816.select-identifiers"
 *                              in the Info.plist.
 */
@property (nonatomic, retain, readonly) NSString *initialSelectedAID API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion The hardware UID of the tag.
 */
@property (nonatomic, readonly, copy) NSData *identifier;

/*!
 * @discussion The optional historical bytes extracted from the Type A Answer To Select response.
 */
@property (nonatomic, readonly, copy, nullable) NSData *historicalBytes;

/*!
 * @discussion The optional Application Data bytes extracted from the Type B Answer To Request response.
 */
@property (nonatomic, readonly, copy, nullable) NSData *applicationData;

/*!
 * @discussion Indicates if @link applicationData @link/ follows proprietary data coding.  If false, the format of the application data is
 *             defined in the ISO14443-3 specification.
 */
@property (nonatomic, readonly) BOOL proprietaryApplicationDataCoding;

/*!
 * @method sendCommandAPDU:completionHandler:
 *
 * @param apdu              The command APDU object
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.  responseData may be
 *                          empty.  Command processing status bytes (SW1-SW2) are always valid.
 *
 * @discussion  Send a command APDU to the tag and receives a response APDU.  Note that a SELECT command with a P1 value of 0x04 (seelction by DF name)
 *              will be checked against the values listed in the "com.apple.developer.nfc.readersession.iso7816.select-identifiers" in the Info.plist.
 *              Selecting an application outside of the permissible list will result in a NFCReaderErrorSecurityViolation error.
 */
- (void)sendCommandAPDU:(NFCISO7816APDU *)apdu
      completionHandler:(void(^)(NSData *responseData, uint8_t sw1, uint8_t sw2, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCISO7816Tag_h */
