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
@property (nonatomic, assign) NSUInteger manufacturerCode;

/*!
 * @discussion  Manufacturer Custom Command Index.  Valid range is 0xA0 to 0xDF.
 */
@property (nonatomic, assign) NSUInteger customCommandCode;

/*!
 * @discussion  Custom request data.
 */
@property (nonatomic, copy) NSData *requestParameters;

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
                       requestParameters:(nullable NSData *)requestParameters;

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
                           retryInterval:(NSTimeInterval)retryInterval;
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
@property (nonatomic, assign) NSRange range;

/*!
 * @discussion  Number of blocks to read per Read Multiple Blocks command. This may be limited by the tag hardware.
 */
@property (nonatomic, assign) NSUInteger chunkSize;

/*!
 * @discussion  Initialize with default zero maximum retry and zero retry interval.
 */
- (instancetype)initWithRange:(NSRange)range
                    chunkSize:(NSUInteger)chunkSize;
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
                retryInterval:(NSTimeInterval)retryInterval;

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
 *              Tag must be in the connected state for NFCNDEFTag protocol properties and methods to work correctly.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCISO15693Tag <NFCTag, NFCNDEFTag>

typedef NS_OPTIONS(uint8_t, RequestFlag) {
    RequestFlagDualSubCarriers      = (1 << 0),
    RequestFlagHighDataRate         = (1 << 1),
    RequestFlagProtocolExtension    = (1 << 3),
    RequestFlagSelect               = (1 << 4),
    RequestFlagAddress              = (1 << 5),
    RequestFlagOption               = (1 << 6),
};


@required

/*!
 * @discussion The 64 bit hardware UID of the tag. Data is in Big Endian byte order.
 */
@property (nonatomic, readonly, copy) NSData *identifier;

/*!
 * @discussion  The IC manufacturer code (bits 56 – 49) in UID according to ISO/IEC 7816-6:2004.
 */
@property (nonatomic, readonly) NSUInteger icManufacturerCode;

/*!
 * @discussion  The IC serial number (bits 48 – 1) in UID assigned by the manufacturer.  Data is in Big Endian byte order.
 */
@property (nonatomic, readonly, copy) NSData *icSerialNumber;


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
- (void)readSingleBlockWithRequestFlags:(RequestFlag)flags
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
- (void)writeSingleBlockWithRequestFlags:(RequestFlag)flags
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
- (void)lockBlockWithRequestFlags:(RequestFlag)flags
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
- (void)readMultipleBlocksWithRequestFlags:(RequestFlag)flags
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
- (void)writeMultipleBlocksWithRequestFlags:(RequestFlag)flags
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
- (void)selectWithRequestFlags:(RequestFlag)flags
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
- (void)resetToReadyWithRequestFlags:(RequestFlag)flags
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
- (void)writeAFIWithRequestFlag:(RequestFlag)flags
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
- (void)lockAFIWithRequestFlag:(RequestFlag)flags
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
- (void)writeDSFIDWithRequestFlag:(RequestFlag)flags
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
 * @discussion              Lock DSFID command (0x2A command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)lockDFSIDWithRequestFlag:(RequestFlag)flags
               completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method getSystemInfoWithRequestFlag:completionHandler:
 *
 * @param flags             Request flags.
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *                          A @link NFCISO15693TagResponseErrorKey @link/ in NSError userInfo dictionary is returned when the tag
 *                          responded to the command with an error, and the error code value is defined in ISO15693-3 specification.
 *                          Value of -1 will be returned from dsfid, afi, blockSize, blockNumber, or icReference if tag response does not contain the information.
 *                          blockSize returns the actual block size in bytes ranged from 1 to 32.  blockCount returns the actual number of blocks
 *                          ranged from 1 to 256 blocks.
 *
 * @discussion              Get system information command (0x2B command code) as defined in ISO15693-3 specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)getSystemInfoWithRequestFlag:(RequestFlag)flags
                   completionHandler:(void(^)(NSInteger dsfid, NSInteger afi, NSInteger blockSize, NSInteger blockCount, NSInteger icReference, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

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
- (void)getMultipleBlockSecurityStatusWithRequestFlag:(RequestFlag)flags
                                           blockRange:(NSRange)blockRange
                                    completionHandler:(void(^)(NSArray<NSNumber *> *securityStatus, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);


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
- (void)customCommandWithRequestFlag:(RequestFlag)flags
                   customCommandCode:(NSInteger)customCommandCode
             customRequestParameters:(NSData *)customRequestParameters
                   completionHandler:(void(^)(NSData *customResponseParameters, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*
 * The following is defined by the NFC Forum Type 5 tag specification
 */

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
 * @discussion              Extended read single block command (0x30 command code) as defined in NFC Forum Type 5 tag specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedReadSingleBlockWithRequestFlags:(RequestFlag)flags
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
 * @discussion              Extended write single block command (0x31 command code) as defined in NFC Forum Type 5 tag specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedWriteSingleBlockWithRequestFlags:(RequestFlag)flags
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
 * @discussion              Extende lock single block command (0x32 command code) as defined in NFC Forum Type 5 tag specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedLockBlockWithRequestFlags:(RequestFlag)flags
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
 * @discussion              Extended read multiple block command (0x33 command code) as defined in NFC Forum Type 5 tag specification.  Address flag is automatically
 *                          enforced by default and the tag's UID is sent with the command; setting RequestFlagSelect to flags will disable the Address flag.
 */
- (void)extendedReadMultipleBlocksWithRequestFlags:(RequestFlag)flags
                                        blockRange:(NSRange)blockRange
                                 completionHandler:(void(^)(NSArray<NSData *> *dataBlocks, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCISO15693Tag_h */
