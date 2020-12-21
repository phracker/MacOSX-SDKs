//
//  IOUSBHostObject.h
//  IOUSBHost
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IOUSBHost/IOUSBHostDefinitions.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 * @class   IOUSBHostObject
 * @brief   The Abstract class IOUSBHostDevice and IOUSBHostInterface derive from.
 * @details Defines common methods that are shared between IOUSBHostDevice and IOUSBHostInterface including instance
 *          management.
 */
@interface IOUSBHostObject : NSObject

    typedef void (^ IOUSBHostInterestHandler)(IOUSBHostObject* hostObject, uint32_t messageType, void* _Nullable messageArgument);

#pragma mark session management and creation

- (instancetype)init __attribute__((unavailable("Please use initWithIOService:queue:error:interestHandler.")));

/*!
 * @brief      Initializes IOUSBHostObject object along with user client
 * @discussion If the io_service_t is not found nil will be returned. If an IOUSBHostDevice or
 *             IOUSBHostInterface user client is already created, nil will be returned.
 *             Upon creation, exclusive ownership of the IOService will be established. When done
 *             using the object destroy must be called on the object.
 * @param      ioService io_service_t of the IOUSBHostDevice or IOUSBHostInterface
 *             the user client is for. The IOUSBHostObject will keep a reference to the io_service_t
 *             and release it after the IOUSBHostObject has been released.
 * @param      options IOUSBHostObjectInitOptions. Default value is IOUSBHostObjectInitOptionsNone
 * @param      queue A serial queue that all asynchronous io will be serviced. By
 *             default a serial queue will be created on behalf of the client. Setting
 *             a queue will create a dispatch source event handler for the target queue to service
 *             all underlying io.
 * @param      interestHandler IOUSBHostInterestHandler a generalInterest IOService handler. This is
 *             to handle underlying service state changes such as termination. See
 *             IOServiceAddInterestNotification in IOKitLib for more details. All notifications will be serviced
 *             on an internal serial queue separate from the IO queue.
 * @return     An IOUSBHostDevice or IOUSBHostInterface. The object is to be released by the caller.
 *             An IOReturn error code will be reported on failure.
 */
- (nullable instancetype)initWithIOService:(io_service_t)ioService
                                   options:(IOUSBHostObjectInitOptions)options
                                     queue:(nullable dispatch_queue_t)queue
                                     error:(NSError* _Nullable*)error
                           interestHandler:(nullable IOUSBHostInterestHandler)interestHandler NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
 * @brief      Initializes IOUSBHostObject object along with user client
 * @discussion This method should be called from either IOUSBHostDevice or IOUSBHostInterface.
 *             If the io_service_t is not found nil will be returned. If an IOUSBHostDevice or
 *             IOUSBHostInterface user client is already created, nil will be returned.
 *             Upon creation, exclusive ownership of the IOService will be established. When done
 *             using the object destroy must be called on the object.
 * @param      ioService io_service_t of the IOUSBHostDevice or IOUSBHostInterface
 *             the user client is for. The IOUSBHostObject will keep a reference to the io_service_t
 *             and release it after the IOUSBHostObject has been released.
 * @param      queue A serial queue that all asynchronous io will be serviced. By
 *             default a serial queue will be created on behalf of the client. Setting
 *             a queue will create a dispatch source event handler for the target queue to service
 *             all underlying io.
 * @param      interestHandler IOUSBHostInterestHandler a generalInterest IOService handler. This is
 *             to handle underlying service state changes such as termination. See
 *             IOServiceAddInterestNotification in IOKitLib for more details. All notifications will be serviced
 *             on an internal serial queue separate from the IO queue.
 * @return     An IOUSBHostDevice or IOUSBHostInterface. The object is to be released by the caller.
 *             An IOReturn error code will be reported on failure.
 */
- (nullable instancetype)initWithIOService:(io_service_t)ioService
                                     queue:(nullable dispatch_queue_t)queue
                                     error:(NSError* _Nullable*)error
                           interestHandler:(nullable IOUSBHostInterestHandler)interestHandler NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");
/*!
 * @brief      Removes underlying allocations of the IOUSBHostObject object along with user client
 * @discussion When the IOUSBHostObject is no longer needed, destroy must be called. This will destroy
 *             the connection with the user client and de-register interest on the service. If the object
 *             is free'd destroy will be called automatically. Calling destroy multiple times has no effect.
 */
- (void)destroy;

/*!
 * @brief   Retrieve the IOUSBHostObject's io_service_t.
 */
@property(readonly) io_service_t ioService;

/*!
 * @brief      The dispatch queue that all asynchronous io will be serviced.
 */
@property(readonly) dispatch_queue_t queue;

#pragma mark Device Requests

/*!
 * @brief      Send a request on the default control endpoint
 * @discussion This method will send a synchronous request on the default control endpoint, and
 *             will not return until the request is complete.
 * @param      request IOUSBDeviceRequest structure.
 * @param      data An NSMutableData* defining the memory to use for the request's data phase.
 * @param      bytesTransferred Optional NSUInteger reference which will be updated with the byte
 *             count of the completed data phase.
 * @param      completionTimeout Timeout of the request. If 0, the request will never timeout. By
 *             default this value is IOUSBHostDefaultControlCompletionTimeout.
 * @return     YES on success, an IOReturn error code will be reported on failure.
 */
- (BOOL)sendDeviceRequest:(IOUSBDeviceRequest)request
                     data:(nullable NSMutableData*)data
         bytesTransferred:(nullable NSUInteger*)bytesTransferred
        completionTimeout:(NSTimeInterval)completionTimeout
                    error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief      Send a request on the default control endpoint
 * @discussion This method will send a synchronous request on the default control endpoint, and
 *             will not return until the request is complete.
 * @param      request IOUSBDeviceRequest structure.
 * @param      data An NSMutableData* defining the memory to use for the request's data phase.
 * @param      bytesTransferred Optional NSUInteger reference which will be updated with the byte
 *             count of the completed data phase.
 * @return     YES on success, an IOReturn error code will be reported on failure.
 */
- (BOOL)sendDeviceRequest:(IOUSBDeviceRequest)request
                     data:(nullable NSMutableData*)data
         bytesTransferred:(nullable NSUInteger*)bytesTransferred
                    error:(NSError* _Nullable*)error  NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief      Send a request on the default control endpoint
 * @discussion This method will send a synchronous request on the default control endpoint, and
 *             will not return until the request is complete.
 * @param      request IOUSBDeviceRequest structure.
 * @return     YES on success, an IOReturn error code will be reported on failure.
 */
- (BOOL)sendDeviceRequest:(IOUSBDeviceRequest)request
                    error:(NSError* _Nullable*)error  NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief      Enqueue a request on the default control endpoint
 * @discussion This method will enqueue an asynchronous request on the default control endpoint.
 *             If successful, the provided completionHandler will be called to report the status
 *             of the completed IO.
 * @param      data An NSMutableData* defining the memory to use for the request's data phase.
 * @param      completionTimeout Timeout of the request. If 0, the request will never timeout. By
 *             default this value is IOUSBHostDefaultControlCompletionTimeout
 * @param      completionHandler an IOUSBHostCompletionHandler
 * @return     YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueDeviceRequest:(IOUSBDeviceRequest)request
                        data:(nullable NSMutableData*)data
           completionTimeout:(NSTimeInterval)completionTimeout
                       error:(NSError* _Nullable*)error
           completionHandler:(nullable IOUSBHostCompletionHandler)completionHandler NS_REFINED_FOR_SWIFT;

/*!
 * @brief      Enqueue a request on the default control endpoint
 * @discussion This method will enqueue an asynchronous request on the default control endpoint.
 *             If successful, the provided completionHandler will be called to report the status
 *             of the completed IO.
 * @param      data An NSMutableData* defining the memory to use for the request's data phase.
 * @param      completionHandler an IOUSBHostCompletionHandler
 * @return     YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueDeviceRequest:(IOUSBDeviceRequest)request
                        data:(nullable NSMutableData*)data
                       error:(NSError* _Nullable*)error
           completionHandler:(nullable IOUSBHostCompletionHandler)completionHandler  NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief      Enqueue a request on the default control endpoint
 * @discussion This method will enqueue an asynchronous request on the default control endpoint.
 *             If successful, the provided completionHandler will be called to report the status
 *             of the completed IO.
 *             default this value is IOUSBHostDefaultControlCompletionTimeout
 * @param      completionHandler an IOUSBHostCompletionHandler
 * @return     YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueDeviceRequest:(IOUSBDeviceRequest)request
                       error:(NSError* _Nullable*)error
           completionHandler:(nullable IOUSBHostCompletionHandler)completionHandler  NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief      Abort device requests
 * @discussion This method will abort any requests made via the @link sendDeviceRequest @/link and
 *             @link enqueueDeviceRequest @/link methods.
 * @param      option IOUSBHostAbortOption by default IOUSBHostAbortOptionSynchronous is used
 * @return     YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)abortDeviceRequestsWithOption:(IOUSBHostAbortOption)option
                                error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief      Abort device requests
 * @discussion This method will abort any requests made via the @link sendDeviceRequest @/link and
 *             @link enqueueDeviceRequest @/link methods.
 * @return     YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)abortDeviceRequestsWithError:(NSError* _Nullable*)error  NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

#pragma mark Descriptors
/*!
 * @brief       Retrieve a descriptor from the cache or the device
 * @discussion  This method will search the descriptor cache for the descriptor that matches the
 *              input arguments.  If the descriptor is not in the cache, a GET_DESCRIPTOR control
 *              request (USB 2.0 9.4.3) will be issued to retrieve the descriptor from the device.
 *              If the device request is successful, the retrieved descriptor will be added to the
 *              cache.
 * @param       type <code>bDescriptorType</code> of the descriptor to find.
 * @param       length Reference to a NSUInteger which will be updated with the length of the
 *              descriptor. As input, used as <code>wLength</code> when fetching variable-length
 *              configuration or BOS descriptors, or when fetching nonstandard descriptor types.
 * @param       index Descriptor index value.  Low byte of <code>wValue</code> of the SET_DESCRIPTOR
 *              control request (USB 2.0 9.4.8). By default the value is 0
 * @param       languageID Descriptor language ID.  <code>wIndex</code> of the SET_DESCRIPTOR
 *              control request (USB 2.0 9.4.8).  By default the value is 0
 * @param       requestType tDeviceRequestType to be used for a GET_DESCRIPTOR control request.
 *              By default the value is IOUSBRequestTypeStandard
 * @param       requestRecipient tDeviceRequestRecipient to be used for a GET_DESCRIPTOR control
 *              request. By default the value is IOUSBRequestRecipientDevice
 * @return      Pointer to the cached descriptor if found, otherwise nil. An IOReturn error code
 *              will be reported on failure.
 */
- (nullable const IOUSBDescriptor*)descriptorWithType:(tIOUSBDescriptorType)type
                                               length:(NSUInteger*)length
                                                index:(NSUInteger)index
                                           languageID:(NSUInteger)languageID
                                          requestType:(tIOUSBDeviceRequestTypeValue)requestType
                                     requestRecipient:(tIOUSBDeviceRequestRecipientValue)requestRecipient
                                                error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Retrieve a descriptor from the cache or the device
 * @discussion  This method will search the descriptor cache for the descriptor that matches the
 *              input arguments.  If the descriptor is not in the cache, a GET_DESCRIPTOR control
 *              request (USB 2.0 9.4.3) will be issued to retrieve the descriptor from the device.
 *              If the device request is successful, the retrieved descriptor will be added to the
 *              cache.
 * @param       type <code>bDescriptorType</code> of the descriptor to find.
 * @param       length Reference to a NSUInteger which will be updated with the length of the
 *              descriptor. As input, used as <code>wLength</code> when fetching variable-length
 *              configuration or BOS descriptors, or when fetching nonstandard descriptor types.
 * @param       index Descriptor index value.  Low byte of <code>wValue</code> of the SET_DESCRIPTOR
 *              control request (USB 2.0 9.4.8). By default the value is 0
 * @param       languageID Descriptor language ID.  <code>wIndex</code> of the SET_DESCRIPTOR
 *              control request (USB 2.0 9.4.8).  By default the value is 0
 * @return      Pointer to the cached descriptor if found, otherwise nil. An IOReturn error code
 *              will be reported on failure.
 */
- (nullable const IOUSBDescriptor*)descriptorWithType:(tIOUSBDescriptorType)type
                                               length:(NSUInteger*)length
                                                index:(NSUInteger)index
                                           languageID:(NSUInteger)languageID
                                                error:(NSError* _Nullable*)error  NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief       Retrieve a descriptor from the cache or the device
 * @discussion  This method will search the descriptor cache for the descriptor that matches the
 *              input arguments.  If the descriptor is not in the cache, a GET_DESCRIPTOR control
 *              request (USB 2.0 9.4.3) will be issued to retrieve the descriptor from the device.
 *              If the device request is successful, the retrieved descriptor will be added to the
 *              cache.
 * @param       type <code>bDescriptorType</code> of the descriptor to find.
 * @param       length Reference to a NSUInteger which will be updated with the length of the
 *              descriptor. As input, used as <code>wLength</code> when fetching variable-length
 *              configuration or BOS descriptors, or when fetching nonstandard descriptor types.
 *              By default the value is 0
 * @return      Pointer to the cached descriptor if found, otherwise nil. An IOReturn error code
 *              will be reported on failure.
 */
- (nullable const IOUSBDescriptor*)descriptorWithType:(tIOUSBDescriptorType)type
                                               length:(NSUInteger*)length
                                                error:(NSError* _Nullable*)error  NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief       Returns the string from a string descriptor
 * @discussion  This method uses descriptorWithType to retrieve the string descriptor.
 * @param       index Descriptor index value.  Low byte of <code>wValue</code> of the
 *              SET_DESCRIPTOR control request (USB 2.0 9.4.8).
 * @param       languageID Descriptor language ID.  <code>wIndex</code> of the SET_DESCRIPTOR
 *              control request (USB 2.0 9.4.8). By default this value is kLanguageIDEnglishUS
 * @return      NSString reference to string from descriptor, an IOReturn error code will be reported on
 *              failure.
 */
- (nullable const NSString*)stringWithIndex:(NSUInteger)index
                                 languageID:(NSUInteger)languageID
                                      error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Returns the string from a string descriptor
 * @discussion  This method uses descriptorWithType to retrieve the string descriptor.
 * @param       index Descriptor index value.  Low byte of <code>wValue</code> of the
 *              SET_DESCRIPTOR control request (USB 2.0 9.4.8).
 * @return      NSString reference to string from descriptor, an IOReturn error code will be reported on
 *              failure.
 */
- (nullable const NSString*)stringWithIndex:(NSUInteger)index
                                      error:(NSError* _Nullable*)error  NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

#pragma mark Miscellaneous

/*!
 * @brief   Retrieve the current address of the device.
 */
@property(readonly) NSUInteger deviceAddress;

/*!
 * @brief       Return the current frame number of the USB controller
 * @discussion  This method will return the current frame number of the USB controller,
 *              omitting micro frame.  This is most useful for scheduling future isochronous
 *              requests.
 * @param       time If not nil, this will be updated with the current system time
 * @return      The current frame number
 */
- (uint64_t)frameNumberWithTime:(nullable IOUSBHostTime*)time NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Allocate a buffer to be used for I/O
 * @discussion  This method will allocate and map an IOBufferMemoryDescriptor optimized for use
 *              by the underlying controller hardware. A buffer allocated by this method will not
 *              be bounced to perform DMA operations.
 *              Because the NSMutableData is backed by kernel memory, the length and capacity are
 *              not mutable. Any changes to the length or capacity will cause an exception to be
 *              thrown.
 * @param       capacity Size of the buffer to allocate
 * @return      NSMutableData of memory mapped to user space of an IOBufferMemoryDescriptor if successful,
 *              otherwise nil. An IOReturn error code will be reported on failure. The result is
 *              to be released by the caller
 */
- (nullable NSMutableData*)ioDataWithCapacity:(NSUInteger)capacity
                                        error:(NSError* _Nullable*)error;

@end

NS_ASSUME_NONNULL_END
