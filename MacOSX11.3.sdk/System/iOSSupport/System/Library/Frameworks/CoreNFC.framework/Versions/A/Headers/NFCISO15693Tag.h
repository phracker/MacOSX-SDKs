//
//  NFCISO15693Tag.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCISO15693Tag_h
#define NFCISO15693Tag_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCTagCommandConfiguration;
@protocol NFCTag, NFCNDEFTag;

typedef NS_OPTIONS(uint8_t, NFCISO15693RequestFlag) {
    NFCISO15693RequestFlagDualSubCarriers API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)     = (1 << 0),
    NFCISO15693RequestFlagHighDataRate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)        = (1 << 1),
    NFCISO15693RequestFlagProtocolExtension API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)   = (1 << 3),
    NFCISO15693RequestFlagSelect API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)              = (1 << 4),
    NFCISO15693RequestFlagAddress API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)             = (1 << 5),
    NFCISO15693RequestFlagOption API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)              = (1 << 6),
    NFCISO15693RequestFlagCommandSpecificBit8 API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos) = (1 << 7),
    
    RequestFlagDualSubCarriers API_DEPRECATED_WITH_REPLACEMENT("NFCISO15693RequestFlagDualSubCarriers", ios(11.0, 14.0))    = NFCISO15693RequestFlagDualSubCarriers,
    RequestFlagHighDataRate API_DEPRECATED_WITH_REPLACEMENT("NFCISO15693RequestFlagHighDataRate", ios(11.0,14.0))           = NFCISO15693RequestFlagHighDataRate,
    RequestFlagProtocolExtension API_DEPRECATED_WITH_REPLACEMENT("NFCISO15693RequestFlagProtocolExtension", ios(11.0,14.0)) = NFCISO15693RequestFlagProtocolExtension,
    RequestFlagSelect API_DEPRECATED_WITH_REPLACEMENT("NFCISO15693RequestFlagSelect", ios(11.0,14.0))                       = NFCISO15693RequestFlagSelect,
    RequestFlagAddress API_DEPRECATED_WITH_REPLACEMENT("NFCISO15693RequestFlagAddress", ios(11.0,14.0))                     = NFCISO15693RequestFlagAddress,
    RequestFlagOption API_DEPRECATED_WITH_REPLACEMENT("NFCISO15693RequestFlagOption", ios(11.0,14.0))                       = NFCISO15693RequestFlagOption

} API_AVAILABLE(ios(14.0));

typedef NFCISO15693RequestFlag RequestFlag API_AVAILABLE(ios(11.0)) API_DEPRECATED_WITH_REPLACEMENT("NFCISO15693RequestFlag", ios(11.0, 14.0));

typedef NS_OPTIONS(uint8_t, NFCISO15693ResponseFlag) {
    NFCISO15693ResponseFlagError API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos)                     = (1 << 0),
    NFCISO15693ResponseFlagResponseBufferValid API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos)       = (1 << 1),
    NFCISO15693ResponseFlagFinalResponse API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos)             = (1 << 2),
    NFCISO15693ResponseFlagProtocolExtension API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos)         = (1 << 3),
    NFCISO15693ResponseFlagBlockSecurityStatusBit5 API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos)   = (1 << 4),
    NFCISO15693ResponseFlagBlockSecurityStatusBit6 API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos)   = (1 << 5),
    NFCISO15693ResponseFlagWaitTimeExtension API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos)         = (1 << 6),
} API_AVAILABLE(ios(14.0));

/*!
 * @class       NFCISO15693CustomCommandConfiguration
 *
 * @discussion  Configuration options for the Manufacturer Custom command.
 */

NS_EXTENSION_UNAVAILABLE("Not available to extensions") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO15693CustomCommandConfiguration : NFCTagCommandConfiguration

/*!
 * @discussion  Manufacturer code. Valid range is 0x00 to 0xFF.
 */
@property (nonatomic, assign) NSUInteger manufacturerCode API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion  Manufacturer Custom Command Index.  Valid range is 0xA0 to 0xDF.
 */
@property (nonatomic, assign) NSUInteger customCommandCode API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion  Custom request data.
 */
@property (nonatomic, copy) NSData *requestParameters API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method initWithManufacturerCode:customCommandCode:requestParameters:
 *
 * @param manufacturerCode      8 bits manufacturer code.
 * @param customCommandCode     8 bits custom command code.  Valid range is 0xA0 to 0xDF.
 * @param requestParameters     Optional custom request parameters.
 *
 * @discussion  Initialize with default zero maximum retry and zero retry interval.
 */
- (instancetype)initWithManufacturerCode:(NSUInteger)manufacturerCode
                       customCommandCode:(NSUInteger)customCommandCode
                       requestParameters:(nullable NSData *)requestParameters API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method initWithManufacturerCode:customCommandCode:requestParameters:maximumRetries:retryInterval:
 *
 * @param manufacturerCode      8 bits manufacturer code.
 * @param customCommandCode     8 bits custom command code.  Valid range is 0xA0 to 0xDF.
 * @param requestParameters     Optional custom request parameters.
 * @param maximumRetries        Maximum number of retry attempt when tag response is not recevied.
 * @param retryInterval         Time interval wait between each retry attempt.
 */
- (instancetype)initWithManufacturerCode:(NSUInteger)manufacturerCode
                       customCommandCode:(NSUInteger)customCommandCode
                       requestParameters:(nullable NSData *)requestParameters
                          maximumRetries:(NSUInteger)maximumRetries
                           retryInterval:(NSTimeInterval)retryInterval API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

/*!
 * @class       NFCISO15693ReadMultipleBlocksConfiguration
 *
 * @discussion  Configuration options for the Read Multiple Blocks command.
 */
NS_EXTENSION_UNAVAILABLE("Not available to extensions")  API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO15693ReadMultipleBlocksConfiguration : NFCTagCommandConfiguration

/*!
 * @discussion  Range to read in blocks.  Valid start index range is 0x00 to 0xFF.  Length shall not be 0.
 */
@property (nonatomic, assign) NSRange range API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion  Number of blocks to read per Read Multiple Blocks command. This may be limited by the tag hardware.
 */
@property (nonatomic, assign) NSUInteger chunkSize API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion  Initialize with default zero maximum retry and zero retry interval.
 */
- (instancetype)initWithRange:(NSRange)range
                    chunkSize:(NSUInteger)chunkSize API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);
/*!
 * @method initWithRange:chunkSize:maximumRetries:retryInterval:
 *
 * @param range             Read range specify by the starting block index and the total number of blocks.
 * @param chunkSize         Specify number of blocks parameter for the Read multiple blocks command.
 * @param maximumRetries    Maximum number of retry attempt when tag response is not recevied.
 * @param retryInterval     Time interval wait between each retry attempt.
 */
- (instancetype)initWithRange:(NSRange)range
                    chunkSize:(NSUInteger)chunkSize
               maximumRetries:(NSUInteger)maximumRetries
                retryInterval:(NSTimeInterval)retryInterval API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

/*!
 * @protocol NFCISO15693Tag
 *
 * @discussion  A @link NFCISO15693ReaderSession @link/ or @link NFCTagReaderSession @link/ reader session returns an instance conforming
 *              to this protocol when an ISO15693 tag is detected.  Unless it is specified all block completion handlers are dispatched on the
 *              reader session work queue that is associated with the tag.  Your process requires to include the "com.apple.developer.nfc.readersession.formats"
 *              entitlement to receive this tag object from the @link NFCReaderSessionDelegate @link/ delegate.
 *              @link NFCReaderErrorSecurityViolation @link/ will be returned from the @link NFCTagReaderSessionDelegate @link/ invalidation method if the required
 *              entitlement is missing when session is started.
 *              Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.  Each data frame send out by the reader may not
 *              exceed 256 bytes total.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCISO15693Tag <NFCTag, NFCNDEFTag>

@required

/*!
 * @discussion The 64 bit hardware UID of the tag. Data is in Big Endian byte order.
 */
@property (nonatomic, readonly, copy) NSData *identifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion  The IC manufacturer code (bits 56 – 49) in UID according to ISO/IEC 7816-6:2004.
 */
@property (nonatomic, readonly) NSUInteger icManufacturerCode API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @discussion  The IC serial number (bits 48 – 1) in UID assigned by the manufacturer.  Data is in Big Endian byte order.
 */
@property (nonatomic, readonly, copy) NSData *icSerialNumber API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);


#pragma mark - Legacy APIs

/*
 * The following legacy methods require the "com.apple.developer.nfc.readersession.iso15693.tag-identifiers" entitlement in your process.
 * New replacement APIs has been made available for the general use without this entitlement.  Calling these APIs from a tag return by the
 * NFCTagReaderSession session will result in a NFCReaderErrorUnsupportedFeature error.
 */

/*!
 * @method sendCustomCommandWithConfiguration:completionHandler:
 *
 * @param commandConfiguration  Configuration for the Manufacturer Custom Command.
 * @param completionHandler     Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                              A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                              responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion Send a manufacturer dependent custom command using command code range from 0xA0 to 0xDF.  Refer to ISO15693-3
 *             specification for details.
 */
- (void)sendCustomCommandWithConfiguration:(NFCISO15693CustomCommandConfiguration *)commandConfiguration
                         completionHandler:(void(^)(NSData *customResponseParameters, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readMultipleBlocksWithConfiguration:completionHandler:
 *
 * @param readConfiguration Configuration For the Read Multiple Blocks command.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully read data blocks will be returned from NSData object.  All blocks are concatenated into the NSData object.
 *
 * @discussion  Performs read operation using Read Multiple Blocks command (0x23 command code) as defined in ISO15693-3 specification.
 *              Multiple Read Multiple Blocks commands will be sent if necessary to complete the operation.
 */
- (void)readMultipleBlocksWithConfiguration:(NFCISO15693ReadMultipleBlocksConfiguration *)readConfiguration
                          completionHandler:(void(^)(NSData *data, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);


#pragma mark - Public APIs

@required
/*!
 * @method stayQuietWithCompletionHandler:
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Stay quiet command (0x02 command code) as defined in ISO15693-3 specification.
 */
- (void)stayQuietWithCompletionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readSingleBlockWithRequestFlags:blockNumber:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       Block number. Blocks are numbered from 0 to 255 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully read data blocks will be returned from NSData object. If Option flag in the request flags is set,
 *                          then first byte of data block will contain the associated block security status.
 *
 * @discussion              Read single block command (0x20 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)readSingleBlockWithRequestFlags:(NFCISO15693RequestFlag)flags
                            blockNumber:(uint8_t)blockNumber
                      completionHandler:(void(^)(NSData *data, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeSingleBlockWithRequestFlags:blockNumber:dataBlock:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       Block number. Blocks are numbered from 0 to 255 inclusively.
 * @param dataBlock         A single block of data.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Write single block command (0x21 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)writeSingleBlockWithRequestFlags:(NFCISO15693RequestFlag)flags
                             blockNumber:(uint8_t)blockNumber
                               dataBlock:(NSData *)dataBlock
                       completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
* @method lockBlockWithRequestFlags:blockNumber:completionHandler:
*
* @param flags             Request flags.
* @param blockNumber       Block number. Blocks are numbered from 0 to 255 inclusively.
* @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
*                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
*                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
*                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
*                          Successfully read data blocks will be returned from NSData object.
*
* @discussion              Lock block command (0x22 command code) as defined in ISO15693-3 specification.  Address flag is automatically
*                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
*/
- (void)lockBlockWithRequestFlags:(NFCISO15693RequestFlag)flags
                      blockNumber:(uint8_t)blockNumber
                completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readMultipleBlocksWithRequestFlags:blockRange:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 255 inclusively.  Valid length is 1 to 256 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully read data blocks will be returned from NSArray of NSData object. If Option flag in the request flags is set,
 *                          then first byte of each returned data block will contain the associated block security status.  Each data block element
 *                          would have identical size.
 *
 * @discussion              Read multiple blocks command (0x23 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)readMultipleBlocksWithRequestFlags:(NFCISO15693RequestFlag)flags
                                blockRange:(NSRange)blockRange
                         completionHandler:(void(^)(NSArray<NSData *> *dataBlocks, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeMultipleBlocksWithRequestFlags:blockRange:dataBlocks:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 255 inclusively.  Valid length is 1 to 256 inclusively.
 * @param dataBlocks        Blocks of data represent in NSArray of NSData.  The number of blocks shall match the length value of the blockRange parameter.
 *                          Each block element should have identical size and should match the physical block size of the tag.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Write multiple blocks command (0x24 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)writeMultipleBlocksWithRequestFlags:(NFCISO15693RequestFlag)flags
                                 blockRange:(NSRange)blockRange
                                 dataBlocks:(NSArray<NSData *> *)dataBlocks
                          completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method selectWithRequestFlags:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Select command (0x25 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)selectWithRequestFlags:(NFCISO15693RequestFlag)flags
             completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method resetToReadyWithRequestFlags:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Reset To Ready command (0x26 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)resetToReadyWithRequestFlags:(NFCISO15693RequestFlag)flags
                   completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeAFIWithRequestFlag:afi:completionHandler:
 *
 * @param flags             Request flags.
 * @param afi               Application Family Identifier.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Write AFI command (0x27 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)writeAFIWithRequestFlag:(NFCISO15693RequestFlag)flags
                            afi:(uint8_t)afi
              completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method lockAFIWithRequestFlag:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Lock AFI command (0x28 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)lockAFIWithRequestFlag:(NFCISO15693RequestFlag)flags
             completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method writeDSFIDWithRequestFlag:dsfid:completionHandler:
 *
 * @param flags             Request flags.
 * @param dsfid             Data Storage Format Identifier.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Write DSFID command (0x29 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)writeDSFIDWithRequestFlag:(NFCISO15693RequestFlag)flags
                            dsfid:(uint8_t)dsfid
                completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method lockDFSIDWithRequestFlag:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Use the replacement -lockDSFIDWithRequestFlag:completionHandler:.
 */
- (void)lockDFSIDWithRequestFlag:(NFCISO15693RequestFlag)flags
               completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("lockDSFIDWithRequestFlag:completionHandler:", ios(13.0, 14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method lockDSFIDWithRequestFlag:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Lock DSFID command (0x2A command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)lockDSFIDWithRequestFlag:(NFCISO15693RequestFlag)flags
               completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method getSystemInfoWithRequestFlag:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Value of -1 will be returned from dsfid, afi, blockSize, blockCount, or icReference if tag response does not contain the information.
 *                          blockSize returns the actual block size in bytes ranged from 1 to 32.  blockCount returns the actual number of blocks
 *                          ranged from 1 to 256 blocks.
 *
 * @discussion              Use the replacement -getSystemInfoAndUIDWithRequestFlag:completionHandler:.
 */
- (void)getSystemInfoWithRequestFlag:(NFCISO15693RequestFlag)flags
                   completionHandler:(void(^)(NSInteger dsfid, NSInteger afi, NSInteger blockSize, NSInteger blockCount, NSInteger icReference, NSError * _Nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("getSystemInfoAndUIDWithRequestFlag:completionHandler:", ios(13.0, 14.0))  API_UNAVAILABLE(watchos, macos, tvos);

/*!
* @method getSystemInfoAndUIDWithRequestFlag:completionHandler:
*
* @param flags             Request flags.
* @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
*                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
*                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
*                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
*                          Value of -1 will be returned from dsfid, afi, blockSize, blockCount, or icReference, and a nil UID value if tag response does not contain the information.
*                          blockSize returns the actual block size in bytes ranged from 1 to 32.  blockCount returns the actual number of blocks
*                          ranged from 1 to 256 blocks.  64bits UID value in little endian byte order from the response packet is returned.
*
* @discussion              Get system information command (0x2B command code) as defined in ISO15693-3 specification.  Address flag is automatically
*                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
*/
- (void)getSystemInfoAndUIDWithRequestFlag:(NFCISO15693RequestFlag)flags
                         completionHandler:(void(^)(NSData * _Nullable uid,
                                                    NSInteger dsfid,
                                                    NSInteger afi,
                                                    NSInteger blockSize,
                                                    NSInteger blockCount,
                                                    NSInteger icReference,
                                                    NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method getMultipleBlockSecurityStatusWithRequestFlag:blockRange:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 255 inclusively.  Valid length is 1 to 256 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          The 8 bits security status of the requested blocks are returned in NSArray; the array will be empty when error occurs.
 *
 * @discussion              Get multiple block security status command (0x2C command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)getMultipleBlockSecurityStatusWithRequestFlag:(NFCISO15693RequestFlag)flags
                                           blockRange:(NSRange)blockRange
                                    completionHandler:(void(^)(NSArray<NSNumber *> *securityStatus, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method fastReadMultipleBlocksWithRequestFlag:blockRange:completionHandler:
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 255 inclusively.  Valid length is 1 to 256 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *
 * @discussion              Fast read multiple blocks command (0x2D command code) as defined in ISO15693-3 specification.
 */
- (void)fastReadMultipleBlocksWithRequestFlag:(NFCISO15693RequestFlag)flags
                                   blockRange:(NSRange)blockRange
                            completionHandler:(void(^)(NSArray<NSData *> * dataBlocks, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method customCommandWithRequestFlag:customCommandCode:customRequestParameters:completionHandler:
 *
 * @param flags                     Request flags.
 * @param customCommandCode         Custom command code defined by the IC manufacturer.  Valid range is 0xA0 to 0xDF inclusively.
 * @param customRequestParameters   Custom request parameters defined by the command.
 * @param completionHandler         Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                                  A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                                  A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                                  responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                                  The custom reponse parameters are returned on success.
 *
 * @discussion                      Custom command (0xA0 to 0xDF command code) as defined in ISO15693-3 specification.  IC manufacturer code from the tag is
 *                                  automatically inserted after the command byte before appending the custom request parameters in forming the packet.
 */
- (void)customCommandWithRequestFlag:(NFCISO15693RequestFlag)flags
                   customCommandCode:(NSInteger)customCommandCode
             customRequestParameters:(NSData *)customRequestParameters
                   completionHandler:(void(^)(NSData *customResponseParameters, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedReadSingleBlockWithRequestFlags:blockNumber:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       2 bytes block number, valid range from 0 to 65535 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          If Option flag in the request flags is set, then first byte of the returned data block will contain the associated block security status.
 *
 * @discussion              Extended read single block command (0x30 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedReadSingleBlockWithRequestFlags:(NFCISO15693RequestFlag)flags
                                    blockNumber:(NSInteger)blockNumber
                              completionHandler:(void(^)(NSData *data, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedWriteSingleBlockWithRequestFlags:blockNumber:dataBlock:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       2 bytes block number, valid range from 0 to 65535 inclusively.
 * @param dataBlock         A single block of data.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Extended write single block command (0x31 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedWriteSingleBlockWithRequestFlags:(NFCISO15693RequestFlag)flags
                                     blockNumber:(NSInteger)blockNumber
                                       dataBlock:(NSData *)dataBlock
                               completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedLockBlockWithRequestFlags:blockNumber:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockNumber       2 bytes block number, valid range from 0 to 65535 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Extende lock single block command (0x32 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedLockBlockWithRequestFlags:(NFCISO15693RequestFlag)flags
                              blockNumber:(NSInteger)blockNumber
                        completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedReadMultipleBlocksWithRequestFlags:blockRange:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 65535 inclusively.  Valid length is 1 to 65536 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully read data blocks will be returned from NSData object.  If Option flag in the request flags is set,
 *                          then first byte of each returned data blocks will contain the associated block security status.
 *
 * @discussion              Extended read multiple block command (0x33 command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedReadMultipleBlocksWithRequestFlags:(NFCISO15693RequestFlag)flags
                                        blockRange:(NSRange)blockRange
                                 completionHandler:(void(^)(NSArray<NSData *> *dataBlocks, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedWriteMultipleBlocksWithRequestFlags:blockRange:dataBlocks:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 65535 inclusively.  Valid length is 1 to 65536 inclusively.
 * @param dataBlocks        Blocks of data represented in NSArray of NSData.  The number of blocks shall match the length value of the blockRange parameter.
 *                          Each block element should have identical size and should match the physical block size of the tag.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion              Extended write multiple block command (0x34 command code) as defined in ISO15693-3 specification. Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedWriteMultipleBlocksWithRequestFlags:(NFCISO15693RequestFlag)flags
                                         blockRange:(NSRange)blockRange
                                         dataBlocks:(NSArray<NSData *> *)dataBlocks
                                  completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method authenticateWithRequestFlags:cryptoSuiteIdentifier:message:completionHandler:
 *
 * @param flags                 Request flags.
 * @param cryptoSuiteIdentifier 8 bits Crypto Suite Indicator as defined in ISO/IEC 29167 specification.
 * @param message               Content of the Authenticate command as dictated by the Crypto Suite Indicator.
 * @param completionHandler     Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                              A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                              A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                              responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                              Successfully command response will be return as NSData object excluding the 8 bits response flag.
 *
 * @discussion                  Authenticate command (0x35 command code) as defined in ISO15693-3 specification.  Please note that in-process reply is returned to the caller without any processing.
 */
- (void)authenticateWithRequestFlags:(NFCISO15693RequestFlag)flags
               cryptoSuiteIdentifier:(NSInteger)cryptoSuiteIdentifier
                             message:(NSData *)message
                   completionHandler:(void(^)(NFCISO15693ResponseFlag responseFlag, NSData * response, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method keyUpdateWithRequestFlags:message:completionHandler:
 *
 * @param flags             Request flags.
 * @param keyIdentifier     8 bits key identifier
 * @param message           Content of the Key Update command as dictated by the Crypto Suite Indicator used in Authenticate.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully command response will be return as NSData object excluding the 8 bits response flag.
 *
 * @discussion              Key update command (0x36 command code) as defined in ISO15693-3 specification.  Please note that in-process reply is returned to the caller without any processing.
 */
- (void)keyUpdateWithRequestFlags:(NFCISO15693RequestFlag)flags
                    keyIdentifier:(NSInteger)keyIdentifier
                          message:(NSData *)message
                completionHandler:(void(^)(NFCISO15693ResponseFlag responseFlag, NSData * response, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method challengeWithRequestFlags:message:completionHandler:
 *
 * @param flags                 Request flags.
 * @param cryptoSuiteIdentifier 8 bits Crypto Suite Indicator as defined in ISO/IEC 29167 specification.
 * @param message               Content of the Key Update command as dictated by the Crypto Suite Indicator used in Authenticate.
 * @param completionHandler     Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                              A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                              A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                              responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *
 * @discussion                  Challenge command (0x39 command code) as defined in ISO15693-3 specification.
 */
- (void)challengeWithRequestFlags:(NFCISO15693RequestFlag)flags
            cryptoSuiteIdentifier:(NSInteger)cryptoSuiteIdentifier
                          message:(NSData *)message
                completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readBufferWithRequestFlags:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Successfully command response will be return as NSData object excluding the 8 bits response flag.
 *
 * @discussion              Read buffer command (0x3A command code) as defined in ISO15693-3 specification.
 */
- (void)readBufferWithRequestFlags:(NFCISO15693RequestFlag)flags
                 completionHandler:(void(^)(NFCISO15693ResponseFlag responseFlag, NSData * data, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method extendedGetMultipleBlockSecurityStatusWithRequestFlag:blockRange:completionHandler:
 *
 * @param flags             Request flags.
 * @param blockRange        The range of blocks.  Valid start index range is 0 to 255 inclusively.  Valid length is 1 to 256 inclusively.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          The 8 bits security status of the requested blocks are returned in NSArray; the array will be empty when error occurs.
 *
 * @discussion              Get multiple block security status command (0x3C command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedGetMultipleBlockSecurityStatusWithRequestFlag:(NFCISO15693RequestFlag)flags
                                                   blockRange:(NSRange)blockRange
                                            completionHandler:(void(^)(NSArray<NSNumber *> *securityStatus, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);


/*!
 * @method extendedFastReadMultipleBlocksWithRequestFlag:blockRange:completionHandler:
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *
 * @discussion              Fast read multiple blocks command (0x3D command code) as defined in ISO15693-3 specification.
 */
- (void)extendedFastReadMultipleBlocksWithRequestFlag:(NFCISO15693RequestFlag)flags
                                           blockRange:(NSRange)blockRange
                                    completionHandler:(void(^)(NSArray<NSData *> * dataBlocks, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method sendRequestWithFlag:commandCode:parameters:data:completionHandler:
 * @param flags             Request flags.
 * @param commandCode       8 bits command code.
 * @param data              Data follows after the command code.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *
 * @discussion              Send a command according to the ISO15693-3 specification.  The request data frame is concatenation of 8 bits request flag, 8 bits command code, and optional data.
 *                          Total length of the data frame cannot exceed 256 bytes.  The 8 bits response flag and the data are returned in the completion handler.
 */
- (void)sendRequestWithFlag:(NSInteger)flags
                commandCode:(NSInteger)commandCode
                       data:(NSData * _Nullable)data
          completionHandler:(void(^)(NFCISO15693ResponseFlag responseFlag, NSData * _Nullable data, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCISO15693Tag_h */
