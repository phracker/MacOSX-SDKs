//
//  IOUSBHostDefinitions.h
//  IOUSBHost
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IOKit/IOKitLib.h>
#import <IOKit/IOMessage.h>
#import <IOKit/usb/AppleUSBDefinitions.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark Completion Handlers

typedef void (^ IOUSBHostCompletionHandler)(IOReturn status, NSUInteger bytesTransferred);

/*!
 * @brief AbsoluteTime represented as a uint64_t.
 */
typedef uint64_t IOUSBHostTime;

/*!
 * @struct      IOUSBHostIsochronousFrame
 * @discussion  Structure representing a single frame in an isochronous transfer. Use of this
 *              structure is discouraged, use @link IOUSBHostIsochronousTransaction @/link instead.
 * @field       status Completion status for this individual frame. IOUSBHostFamily will initialize
 *              this to kIOReturnInvalid and will update the field with a valid status code upon
 *              completion of the frame.
 * @field       requestCount The number of bytes requested to transfer for this frame.
 *              This field must be initialized by the caller before the structure is submitted.
 * @field       completeCount The number of bytes actually transferred for this frame.
 *              IOUSBHostFamily will update this field upon completion of the frame.
 * @field       reserved Reserved for future use.
 * @field       timeStamp The observed IOUSBHostTime for this frame's completion.  Note that
 *              interrupt latency and system load may result in more than one frame completing with
 *              the same timestamp.
 */
typedef struct IOUSBHostIsochronousFrame
{
    IOReturn      status;
    uint32_t      requestCount;
    uint32_t      completeCount;
    uint32_t      reserved;
    IOUSBHostTime timeStamp;
} __attribute__((packed)) IOUSBHostIsochronousFrame __OSX_DEPRECATED(10.15, API_TO_BE_DEPRECATED, "Use IOUSBHostIsochronousTransaction instead");

/*!
 * @enum        IOUSBHostIsochronousTransferOptions
 * @brief       Options for <code>sendIORequestWithData:transactionList:transactionListCount:firstFrameNumber:options:error</code>
 *              and <code>sendIORequestWithData:transactionList:transactionListCount:firstFrameNumber:options:error:completionHandler</code>
 * @constant    kIsochronousTransferOptionsNone No options are selected for this transfer
 */
typedef NS_OPTIONS (UInt32, IOUSBHostIsochronousTransferOptions)
{
    IOUSBHostIsochronousTransferOptionsNone = 0,
};

/*!
 * @enum        IOUSBHostIsochronousTransactionOptions
 * @brief       Options for <code>sendIORequestWithData:transactionList:transactionListCount:firstFrameNumber:error</code>
 *              and <code>sendIORequestWithData:transactionList:transactionListCount:firstFrameNumber:error:completionHandler</code>
 * @constant    kIsochronousTransactionOptionsNone No options are selected for this transaction
 * @constant    kIsochronousTransactionOptionsWrap This transaction's data reaches the end of the memory descriptor and continues at the descriptor's start.  If this option is selected, the transaction's offset + requestCount should exceed the memory descriptor's length. This option is not supported on UHCI or UserHCI controllers.
 */
typedef NS_OPTIONS (UInt32, IOUSBHostIsochronousTransactionOptions)
{
    IOUSBHostIsochronousTransactionOptionsNone = 0,
    IOUSBHostIsochronousTransactionOptionsWrap = (1 << 0),
};

/*!
 * @struct      IOUSBHostIsochronousTransaction
 * @discussion  Structure representing a single frame or microframe in an isochronous transfer.
 * @field       status Completion status for this individual transaction. IOUSBHostFamily will
 *              initialize this to kIOReturnInvalid and will update the field with a valid status
 *              code upon completion of the transaction.
 * @field       requestCount The number of bytes requested to transfer for this transaction.
 *              This field must be initialized by the caller before the structure is submitted.
 * @field       offset The number of bytes between the start of the memory descriptor in which this
 *              transaction resides and the start of the transaction.  The offset cannot exceed 4GB.
 * @field       completeCount The number of bytes actually transferred for this transaction.
 *              IOUSBHostFamily will update this field upon completion of the transaction.
 * @field       timeStamp The observed IOUSBHostTime for this transaction's completion.  Note that
 *              interrupt latency and system load may result in more than one transaction completing
 *              with the same timestamp.
 * @field       options Flags that specify additional transaction behavior.  See @link IOUSBHostIsochronousTransactionOptions @/link for more details.
 */
typedef struct IOUSBHostIsochronousTransaction
{
    IOReturn                               status;
    uint32_t                               requestCount;
    uint32_t                               offset;
    uint32_t                               completeCount;
    IOUSBHostTime                          timeStamp;
    IOUSBHostIsochronousTransactionOptions options;
} __attribute__((packed)) IOUSBHostIsochronousTransaction;

/*!
 * @brief      Isochronous IO completion handler.
 * @param      status IOReturn result code for isochronous transfer.
 * @param      frameList Frame list for isochronous transfer.
 */
typedef void (^ IOUSBHostIsochronousCompletionHandler)(IOReturn                  status,
                                                       IOUSBHostIsochronousFrame frameList[_Nonnull]);

/*!
 * @brief      Isochronous IO completion handler.
 * @param      status IOReturn result code for isochronous transfer.
 * @param      transactionList Transaction list for isochronous transfer.
 */
typedef void (^ IOUSBHostIsochronousTransactionCompletionHandler)(IOReturn                        status,
                                                                  IOUSBHostIsochronousTransaction transactionList[_Nonnull]);
#pragma mark General enumerations

/*!
 * @brief       NSErrorDomain for IOUSBHostFamily. Error codes are IOKit IOReturn codes.
 * @constant    IOUSBHostErrorDomain domain for IOUSBHostFamily errors
 */
extern NSErrorDomain const IOUSBHostErrorDomain;

/*!
 * @enum        IOUSBHostAbortOption
 * @brief       Options for <code>abort</code>
 * @constant    IOUSBHostAbortOptionAsynchronous abort should return immediately without
 *              waiting for the aborted IO to complete
 * @constant    IOUSBHostAbortOptionSynchronous abort should not return until the aborted
 *              IO has completed
 * @discussion  To be used with @link abortDeviceRequestsWithOption:error: @/link
 *              @link abortWithOption:error: @/link
 */
typedef NS_ENUM (NSUInteger, IOUSBHostAbortOption)
{
    IOUSBHostAbortOptionAsynchronous = 0,
    IOUSBHostAbortOptionSynchronous
};

/*!
 * @enum        IOUSBHostObjectInitOptions
 * @brief       Options for <code>initWithIOService:options:queue:error:interestHandler</code>
 * @constant    IOUSBHostObjectInitOptionsDeviceCapture Callers must have the "com.apple.vm.device-access" entitlement
 *              and the IOUSBHostDevice IOService object needs to have successfully been authorized by IOServiceAuthorize().
 *              If the caller has root privelages the entitlement and authorization is not needed. Using this option
 *              will terminate all clients and drivers of the IOUSBHostDevice and associated IOUSBHostInterface clients
 *              besides the caller.
 *              Upon <code>destroy</code> of the IOUSBHostDevice, the device will be reset and drivers will be re-registered
 *              for matching. This option is only valid for macOS
 */
typedef NS_OPTIONS (NSUInteger, IOUSBHostObjectInitOptions)
{
    IOUSBHostObjectInitOptionsNone          = 0,
    IOUSBHostObjectInitOptionsDeviceCapture = (1 << 0)
};

/*!
 * @brief Helper method for creating the <code>bmRequestType</code> field of a device request.
 * @param direction The direction of the request.
 * @param type the type of device request.
 * @param recipient the recipient of the device request.
 * @return uint8_t bmRequestType
 */
NS_INLINE uint8_t IOUSBHostDeviceRequestType(tIOUSBDeviceRequestDirectionValue direction,
                                             tIOUSBDeviceRequestTypeValue      type,
                                             tIOUSBDeviceRequestRecipientValue recipient)
{
    return ((direction << kIOUSBDeviceRequestDirectionPhase) & kIOUSBDeviceRequestDirectionMask)
           | ((type << kIOUSBDeviceRequestTypePhase) & kIOUSBDeviceRequestTypeMask)
           | ((recipient << kIOUSBDeviceRequestRecipientPhase) & kIOUSBDeviceRequestRecipientMask);
}

#pragma mark Registry property names

typedef NSString* IOUSBHostMatchingPropertyKey NS_STRING_ENUM;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyVendorID;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyProductID;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyProductIDMask;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyProductIDArray;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyInterfaceNumber;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyConfigurationValue;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyDeviceReleaseNumber;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyInterfaceClass;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyInterfaceSubClass;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyInterfaceProtocol;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyProductIDMask;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyDeviceClass;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyDeviceSubClass;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeyDeviceProtocol;
extern IOUSBHostMatchingPropertyKey IOUSBHostMatchingPropertyKeySpeed;

typedef NSString* IOUSBHostPropertyKey;
extern IOUSBHostPropertyKey IOUSBHostPropertyKeyLocationID;

typedef NSString* IOUSBHostDevicePropertyKey NS_STRING_ENUM;
extern IOUSBHostDevicePropertyKey IOUSBHostDevicePropertyKeyVendorString;
extern IOUSBHostDevicePropertyKey IOUSBHostDevicePropertyKeySerialNumberString;
extern IOUSBHostDevicePropertyKey IOUSBHostDevicePropertyKeyContainerID;
extern IOUSBHostDevicePropertyKey IOUSBHostDevicePropertyKeyCurrentConfiguration;

typedef NSString* IOUSBHostInterfacePropertyKey NS_STRING_ENUM;
extern IOUSBHostInterfacePropertyKey IOUSBHostInterfacePropertyKeyAlternateSetting;

#pragma mark Miscellaneous

extern NSTimeInterval const IOUSBHostDefaultControlCompletionTimeout;

NS_ASSUME_NONNULL_END
