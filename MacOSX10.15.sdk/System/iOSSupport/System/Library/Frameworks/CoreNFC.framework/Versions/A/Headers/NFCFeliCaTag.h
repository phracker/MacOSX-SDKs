//
//  NFCFeliCaTag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCFeliCaTag_h
#define NFCFeliCaTag_h

#import <Foundation/Foundation.h>
#import <CoreNFC/NFCNDEFTag.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NFCTag, NFCNDEFTag;

/*!
 * @protocol NFCFeliCaTag
 *
 * @discussion  A @link NFCTagReaderSession @link/ reader session returns an instance conforming to this protocol
 *              when a FeliCa tag is detected.  Unless it is specified all block completion handlers are dispatched on the
 *              session work queue that is associated with the tag.  Your process requires to include the
 *              "com.apple.developer.nfc.readersession.formats" entitlement and the "com.apple.developer.nfc.readersession.felica.systemcodes"
 *              key in the application's Info.plist to receive this tag object from the @link NFCTagReaderSessionDelegate @link/ delegate.
 *              @link NFCReaderErrorSecurityViolation @link/ will be returned from the @link NFCTagReaderSessionDelegate @link/ invalidation
 *              method if the required entitlement is missing or "com.apple.developer.nfc.readersession.felica.systemcodes" does not contain
 *              at least one valid entry.
 *              When the reader discovers a FeliCa tag it automatically performs a Polling command using the system code values provided in the
 *              "com.apple.developer.nfc.readersession.felica.systemcodes" in the specified array order. System code
 *              specified in the array must not contain a wildcard value (0xFF) in the upper or the lower byte, i.e. full
 *              matching value is required.  The tag is returned from the [NFCTagReaderSessionDelegate readerSession:didDetectTags:] call
 *              on the first successful Polling command matching one of the system codes.  Tag will not be returned
 *              to the NFCTagReaderSessionDelegate if no matching system is found based on entries listed in the Info.plist.
 *              Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCFeliCaTag <NFCTag, NFCNDEFTag>

/*!
 * @discussion Request code parameter for the polling command
 */
typedef NS_ENUM(NSInteger, PollingRequestCode) {
    PollingRequestCodeNoRequest = 0,
    PollingRequestCodeSystemCode = 1,
    PollingRequestCodeCommunicationPerformance = 2,
};

/*!
 * @discussion Time slot parameter for the polling command
 */
typedef NS_ENUM(NSInteger, PollingTimeSlot) {
    PollingTimeSlotMax1 = 0,
    PollingTimeSlotMax2 = 1,
    PollingTimeSlotMax4 = 3,
    PollingTimeSlotMax8 = 7,
    PollingTimeSlotMax16 = 15,
};

/*!
 * @discussion Encryption Identifier parameter in response of Request Service V2
 */
typedef NS_ENUM(NSInteger, EncryptionId) {
    EncryptionIdAES = 0x4F,
    EncryptionIdAES_DES = 0x41,
};

@required

/*!
 * @property currentSystemCode  The system code most recently selected by the reader using the Polling command.
 *                              This will match one of the entries in the "com.apple.developer.nfc.readersession.felica.systemcodes"
 *                              in the Info.plist.
 */
@property (nonatomic, retain, readonly) NSData *currentSystemCode API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property currentIDm         Manufacturer ID of the currently selected system.  Value is updated on each Polling command execution.
 *                              It will be empty if system selection fails.
 */
@property (nonatomic, retain, readonly) NSData *currentIDm API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

#pragma mark - Helper functions

/*
 *  The following commands are defined in FeliCa Card User's Manual Excerpted Edition Version 2.02 (No. M617-E02-02) which
 *  is publicly available from Sony Corporations.
 */

/*!
 * @method pollingWithSystemCode:requestCode:timeSlot:completionHandler:
 *
 * @param systemCode        Designation of System Code.  Wildcard value (0xFF) in the upper or the lower byte is not supported.
 * @param requestCode       Designation of Requset Data output.
 * @param timeSlot          Maximum number of slots possible to respond.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation
 *                          succeeds, else all other return values shall be ignored.  Non-zero length requestData is return when
 *                          requestCode is a non-zero parameter and feature is supported by the tag.  The @link currentIDM @link/ property will be updated
 *                          on each execution, except when an invalid systemCode is provided and the existing selected system will stay selected.
 *
 * @discussion              Polling command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 *                          System code must be one of the provided values in the "com.apple.developer.nfc.readersession.felica.systemcodes"
 *                          in the Info.plist; @link NFCReaderErrorSecurityViolation @link/ will be returned when an invalid system code is used.
 *                          Polling with wildcard value in the upper or lower byte is not supported.
 */
- (void)pollingWithSystemCode:(NSData *)systemCode
                  requestCode:(PollingRequestCode)requestCode
                     timeSlot:(PollingTimeSlot)timeSlot
            completionHandler:(void(^)(NSData *pmm, NSData *requestData, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestServiceWithNodeCodeList:completionHandler:
 *
 * @param nodeCodeList      Node Code list represented in a NSArray of NSData objects.  Number of nodes specified should be between 1 to 32 inclusive.
 *                          Each node code should be 2 bytes stored in Little Endian format.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  Node key version list is return as NSArray of NSData objects,
 *                          and each data object is stored in Little Endian format per FeliCa specification.
 *
 * @discussion              Request Service command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)requestServiceWithNodeCodeList:(NSArray<NSData *> *)nodeCodeList
                     completionHandler:(void(^)(NSArray<NSData *> *nodeKeyVersionList, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestResponseWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  Valid mode value ranges from 0 to 3 inclusively.
 *
 * @discussion              Request Response command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)requestResponseWithCompletionHandler:(void(^)(NSInteger mode, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);


/*!
 * @method readWithoutEncryptionWithServiceCodeList:blockList:completionHandler:
 *
 * @param serviceCodeList   Service Code list represented in a NSArray of NSData objects.  Number of nodes specified should be between 1 to 16 inclusive.
 *                          Each service code should be 2 bytes stored in Little Endian format.
 * @param blockList         Block List represent in a NSArray of NSData objects.  2-Byte or 3-Byte block list element is supported.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  Valid read data blocks (block length of 16 bytes)
 *                          are returned in NSArray of NSData objects when Status Flag 1 equals zero.
 *
 * @discussion              Read Without Encrypton command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)readWithoutEncryptionWithServiceCodeList:(NSArray<NSData *> *)serviceCodeList
                                       blockList:(NSArray<NSData *> *)blockList
                               completionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, NSArray<NSData*> *blockData, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeWithoutEncryptionWithServiceCodeList:blockList:blockData:completionHandler:
 *
 * @param serviceCodeList   Service Code list represented in a NSArray of NSData objects.  Number of nodes specified should be between 1 to 16 inclusive.
 *                          Each service code should be 2 bytes stored in Little Endian format.
 * @param blockList         Block List represent in a NSArray of NSData objects.  Total blockList items and blockData items should match.
 *                          2-Byte or 3-Byte block list element is supported.
 * @param blockData         Block data represent in a NSArray of NSData objects.  Total blockList items and blockData items should match.
 *                          Data block should be 16 bytes in length.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.
 *
 * @discussion              Write Without Encrypton command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)writeWithoutEncryptionWithServiceCodeList:(NSArray<NSData *> *)serviceCodeList
                                        blockList:(NSArray<NSData *> *)blockList
                                        blockData:(NSArray<NSData *> *)blockData
                                completionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestSystemCodeWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  Each system code is 2 bytes stored in Little Endian format.
 *
 * @discussion              Request System Code command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)requestSystemCodeWithCompletionHandler:(void(^)(NSArray<NSData *> *systemCodeList, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestServiceV2WithNodeCodeList:completionHandler:
 *
 * @param nodeCodeList      Node Code list represent in a NSArray of NSData.  Number of nodes specified should be between 1 to 32 inclusive.
 *                          Each node code should be 2 bytes stored in Little Endian format.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  encryptionIdentifier value shall be ignored if Status Flag 1 value indicates an error.
 *                          nodeKeyVerionListAES and nodeKeyVersionListDES may be empty depending on the Status Flag 1 value and the Encryption Identifier value.
 *                          The 2 bytes node key version (AES and DES) is in Little Endian format.
 *
 * @discussion              Request Service V2 command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)requestServiceV2WithNodeCodeList:(NSArray<NSData *> *)nodeCodeList
                       completionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, EncryptionId encryptionIdentifier, NSArray<NSData *> *nodeKeyVersionListAES, NSArray<NSData *> *nodeKeyVersionListDES, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method requestSpecificationVersionWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.  basicVersion and optionVersion may be empty depending on the Status Flag 1 value
 *                          and if the tag supports AES/DES.
 *
 * @discussion              Request Specification Verison command defined by FeliCa card specification.  This command supports response format version `00`h.
 *                          Refer to the FeliCa specification for details.
 */
- (void)requestSpecificationVersionWithCompletionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, NSData *basicVersion, NSData *optionVersion, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method resetModeWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if the contactless transceive operation succeeds,
 *                          else all other return values shall be ignored.
 *
 * @discussion              Reset Mode command defined by FeliCa card specification.  Refer to the FeliCa specification for details.
 */
- (void)resetModeWithCompletionHandler:(void(^)(NSInteger statusFlag1, NSInteger statusFlag2, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);


#pragma mark - Sending additional FeliCa commands

/*!
 * @method sendFeliCaCommandPacket:completionHandler:
 *
 * @param commandPacket     Command packet send to the FeliCa card.  Maximum packet length is 254.  Data length (LEN) byte and CRC bytes are calculated and inserted
 *                          automatically to the provided packet data frame.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *
 * @discussion              Transmission of FeliCa Command Packet Data at the applicaiton layer.  Refer to the FeliCa specification for details.
 *                          Manufacturer ID (IDm) of the currently selected system can be read from the currentIDm property.
 */
- (void)sendFeliCaCommandPacket:(NSData *)commandPacket
              completionHandler:(void(^)(NSData *responsePacket, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif /* NFCFeliCaTag_h */
