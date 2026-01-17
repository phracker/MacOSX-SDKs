//
//  IOUSBHostPipe.h
//  IOUSBHost
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IOUSBHost/IOUSBHostIOSource.h>

@class IOUSBHostStream;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class       IOUSBHostPipe
 * @brief       The IOUSBHostIOSource representing a USB endpoint
 * @discussion  This class provides functionality to transfer data across USB.
 */
@interface IOUSBHostPipe : IOUSBHostIOSource

#pragma mark Descriptors

/*!
 * @brief       Retrieve the Original descriptor used when creating the pipe.
 * @return      IOUSBHostIOSourceDescriptors pointer
 */
@property(readonly) const IOUSBHostIOSourceDescriptors* originalDescriptors;

/*!
 * @brief       Retrieve the current descriptor controlling the endpoint.
 * @return      IOUSBHostIOSourceDescriptors pointer
 */
@property(readonly) const IOUSBHostIOSourceDescriptors* descriptors;

#pragma mark Bus Policies
/*!
 * @brief       Adjust behavior of periodic endpoints to consume a different amount of bus bandwidth
 * @discussion  Periodic (interrupt and isochronous) endpoints reserve bus bandwidth when they are
 *              created, which takes into account max packet size, burst size, and the endpoint
 *              service interval.  If a function driver knows the endpoint will not use all of the
 *              allocated bandwidth, the <code>adjustPolicy</code> method may be used to reduce the
 *              bandwidth reserved for the endpoint.  The original endpoint descriptors should be
 *              copied and modified to adjust max packet size, mult, burst, and interval, and then
 *              passed to <code>adjustPolicy</code>.  The altered descriptors must pass
 *              <code>validateEndpointDescriptor(...)</code> from the kernel for policy changes to be
 *              processed.
 * @param       descriptors Reference to an IOUSBHostIOSourceDescriptors describing the
 *              new endpoint policy
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
-(BOOL)adjustPipeWithDescriptors:(const IOUSBHostIOSourceDescriptors*)descriptors
                           error:(NSError* _Nullable*)error;

/*!
 * @brief       Retrieve the current idle suspend timeout.
 *              See @link setIdleTimeout @/link
 * @return      The amount of time after all pipes are idle to wait before
 *              suspending the device,
 */
@property(readonly) NSTimeInterval idleTimeout;

/*!
 * @brief       Sets the desired idle suspend timeout for the interface
 * @discussion  Once the interface is considered idle, it will defer electrical suspend of the
 *              device for the specified duration.
 * @param       idleTimeout The amount of time after all pipes are idle to
 *              wait before suspending the device.
 * @return      YES on success. An IOReturn error code will be reported on failure.
 */
- (BOOL)setIdleTimeout:(NSTimeInterval)idleTimeout
                 error:(NSError* _Nullable*)error;

/*!
 * @brief       Clear the halt condition of the pipe.
 * @discussion  When a bulk or interrupt USB endpoint encounters any IO error other than a timeout,
 *              it transitions to a Halted state which must be cleared to perform additional IO on
 *              the endpoint.  This method will clear the halted condition for the endpoint,
 *              including sending a CLEAR_TT_BUFFER control request  (USB 2.0 11.24.2.3) to an
 *              intermediate hub if required.  All pending IO on the endpoint will be aborted, and
 *              the data toggle for the endpoint will also be reset. ClearStall is not required for
 *              control endpoints.
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
-(BOOL)clearStallWithError:(NSError* _Nullable*)error;

#pragma mark Control requests

/*!
 * @brief       Send a request on a control endpoint
 * @discussion  This method will send a synchronous request on a control endpoint, and will not
 *              return until the request is complete.
 * @param       request IOUSBDeviceRequest structure.
 * @param       data An NSMutableData* defining the memory to use for the request's data phase.
 * @param       bytesTransferred An NSUInteger reference which will be updated with the byte count
 *              of the completed data phase.
 * @param       completionTimeout Timeout of the request.  If 0, the request will never timeout.
 *              The default value is IOUSBHostDefaultControlCompletionTimeout.
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)sendControlRequest:(IOUSBDeviceRequest)request
                      data:(nullable NSMutableData*)data
          bytesTransferred:(nullable NSUInteger*)bytesTransferred
         completionTimeout:(NSTimeInterval)completionTimeout
                     error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Send a request on a control endpoint
 * @discussion  This method will send a synchronous request on a control endpoint, and will not
 *              return until the request is complete.
 * @param       request IOUSBDeviceRequest structure.
 * @param       data An NSMutableData* defining the memory to use for the request's data phase.
 * @param       bytesTransferred An NSUInteger reference which will be updated with the byte count
 *              of the completed data phase.
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)sendControlRequest:(IOUSBDeviceRequest)request
                      data:(nullable NSMutableData*)data
          bytesTransferred:(nullable NSUInteger*)bytesTransferred
                     error:(NSError* _Nullable*)error NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief       Send a request on a control endpoint
 * @discussion  This method will send a synchronous request on a control endpoint, and will not
 *              return until the request is complete.
 * @param       request IOUSBDeviceRequest structure.
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)sendControlRequest:(IOUSBDeviceRequest)request
                     error:(NSError* _Nullable*)error NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief       Enqueue a request on a control endpoint
 * @discussion  This method will enqueue an asynchronous request on a control endpoint.
 *              If successful, the provided completion routine will be called to report the status
 *              of the completed IO. Completions will be serviced in the
 *              IOUSBHostCompletionHandler on the IOUSBHostInterface's dispatch queue.
 * @param       request Reference IOUSBDeviceRequest structure.
 * @param       data An NSMutableData* defining the memory to use for the request's data phase.
 * @param       completionTimeout Timeout of the request.  If 0, the request will
 *              never timeout. The default value is IOUSBHostDefaultControlCompletionTimeout.
 * @param       completionHandler an IOUSBHostCompletionHandler
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueControlRequest:(IOUSBDeviceRequest)request
                         data:(nullable NSMutableData*)data
            completionTimeout:(NSTimeInterval)completionTimeout
                        error:(NSError* _Nullable*)error
            completionHandler:(nullable IOUSBHostCompletionHandler)completionHandler NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Enqueue a request on a control endpoint
 * @discussion  This method will enqueue an asynchronous request on a control endpoint.
 *              If successful, the provided completion routine will be called to report the status
 *              of the completed IO. Completions will be serviced in the
 *              IOUSBHostCompletionHandler on the IOUSBHostInterface's dispatch queue.
 * @param       request Reference IOUSBDeviceRequest structure.
 * @param       data An NSMutableData* defining the memory to use for the request's data phase.
 * @param       completionHandler an IOUSBHostCompletionHandler
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueControlRequest:(IOUSBDeviceRequest)request
                         data:(nullable NSMutableData*)data
                        error:(NSError* _Nullable*)error
            completionHandler:(nullable IOUSBHostCompletionHandler)completionHandler NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief       Enqueue a request on a control endpoint
 * @discussion  This method will enqueue an asynchronous request on a control endpoint.
 *              If successful, the provided completion routine will be called to report the status
 *              of the completed IO. Completions will be serviced in the
 *              IOUSBHostCompletionHandler on the IOUSBHostInterface's dispatch queue.
 * @param       request Reference IOUSBDeviceRequest structure.
 * @param       completionHandler an IOUSBHostCompletionHandler
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueControlRequest:(IOUSBDeviceRequest)request
                        error:(NSError* _Nullable*)error
            completionHandler:(nullable IOUSBHostCompletionHandler)completionHandler NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

#pragma mark IO
/*!
 * @brief       Abort pending I/O requests.
 * @discussion  This method will abort all pending I/O requests.  If <code>option</code> includes
 *              <code>IOUSBHostAbortOptionSynchronous</code>, this method will block any new IO
 *              requests unless they are submitted from an aborted IO's completion routine.
 * @param       option IOUSBHostAbortOption by default IOUSBHostAbortOptionSynchronous is used
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
-(BOOL)abortWithOption:(IOUSBHostAbortOption)option
                 error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Abort pending I/O requests.
 * @discussion  This method will abort all pending I/O requests.  If <code>option</code> includes
 *              <code>IOUSBHostAbortOptionSynchronous</code>, this method will block any new IO
 *              requests unless they are submitted from an aborted IO's completion routine.
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
-(BOOL)abortWithError:(NSError* _Nullable*)error NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

/*!
 * @brief       Send an IO request on the source
 * @discussion  This method will send a synchronous request on the IO source, and will not return
 *              until the request is complete.
 * @param       data An NSMutableData* containing the buffer to use for the transfer. nil will send a zero length packet.
 * @param       bytesTransferred NSUInteger pointer which will be updated with the bytes transferred
 *              during the request
 * @param       completionTimeout Timeout of the request.  If 0, the request will never timeout.
 *              Must be 0 for interrupt pipes and streams.
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)sendIORequestWithData:(nullable NSMutableData*)data
             bytesTransferred:(nullable NSUInteger*)bytesTransferred
            completionTimeout:(NSTimeInterval)completionTimeout
                        error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Enqueue an IO request on the source
 * @discussion  This method is used to issue an asynchronous I/O request on a bulk or interrupt
 *              pipe.
 * @param       data An NSMutableData* containing the buffer to use for the transfer. nil will send a zero length packet.
 * @param       completionTimeout Timeout of the request.  If 0, the request will never timeout.
 *              Must be 0 for interrupt pipes and streams.
 * @param       completionHandler an IOUSBHostCompletionHandler
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueIORequestWithData:(nullable NSMutableData*)data
               completionTimeout:(NSTimeInterval)completionTimeout
                           error:(NSError* _Nullable*)error
               completionHandler:(nullable IOUSBHostCompletionHandler)completionHandler;

/*!
 * @brief       Send a request on an isochronous endpoint
 * @discussion  This method is used to issue isochronous requests.  The caller allocates and
 *              initializes  an array of IOUSBHostIsochronousFrame structures, which is used to
 *              describe the frames that will be transferred.  See
 *              @link IOUSBHostIsochronousFrame @/link for information regarding structure
 *              initialization requirements and usage.
 * @param       data An NSMutableData* to be used as the backing store for the I/O. nil will send a zero length packet.
 * @param       frameList Pointer first element in an IOUSBHostIsochronousFrame array.  The array
 *              must contain at least frameListCount elements.
 * @param       frameListCount Number of elements in <code>frameList</code>.
 * @param       firstFrameNumber Frame number which this request should begin on.  The current frame
 *              number can be queried via <code>[IOUSBHostObject getFrameNumber]</code>
 *              If 0, the transfer will start on the next available frame (XHCI only).
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)sendIORequestWithData:(NSMutableData*)data
                    frameList:(IOUSBHostIsochronousFrame*)frameList
               frameListCount:(NSUInteger)frameListCount
             firstFrameNumber:(uint64_t)firstFrameNumber
                        error:(NSError* _Nullable*)error;

/*!
 * @brief       Send a request on an isochronous endpoint
 * @discussion  This method is used to issue isochronous requests.  The caller allocates and
 *              initializes an array of IOUSBHostIsochronousFrame structures, which is used to
 *              describe the frames that will be transferred.  See
 *              @link IOUSBHostIsochronousFrame @/link for information regarding structure
 *              initialization requirements and usage.
 * @param       data An NSMutableData* to be used as the backing store for the I/O. nil will send a zero length packet.
 * @param       frameList Pointer first element in an IOUSBHostIsochronousFrame array.  The array
 *              must contain at least frameListCount elements.
 * @param       frameListCount Number of elements in <code>frameList</code>.
 * @param       firstFrameNumber Frame number which this request should begin on.  The current frame
 *              number can be queried via <code>[IOUSBHostObject frameNumberWithTime]</code>
 *              If 0, the transfer will start on the next available frame (XHCI only).
 * @param       completionHandler an IOUSBHostIsochronousCompletionHandler
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueIORequestWithData:(NSMutableData*)data
                       frameList:(IOUSBHostIsochronousFrame*)frameList
                  frameListCount:(NSUInteger)frameListCount
                firstFrameNumber:(uint64_t)firstFrameNumber
                           error:(NSError* _Nullable*)error
               completionHandler:(nullable IOUSBHostIsochronousCompletionHandler)completionHandler;

#pragma mark Streams
/*!
 * @brief       Enable streams for the IOUSBHostPipe
 * @discussion  This method changes the operational mode of the IOUSBHostPipe to allow streaming
 *              endpoint transfers, and must be called before copyStream will return any
 *              IOUSBHostStream objects.
 * @return      YES on success, an An IOReturn error will be returned if the pipe, device, or
 *              underlying host controller does not support streams.
 */
- (BOOL)enableStreamsWithError:(NSError* _Nullable*)error;

/*!
 * @brief       Disable streams for the IOUSBHostPipe
 * @discussion  This method changes the operational mode of the IOUSBHostPipe to disable streaming
 *              endpoint transfers.  Calling this method will synchronously abort any outstanding
 *              calls on existing IOUSBHostStream objects, and therefore all stream contexts should
 *              first be set as non-active on the device via an out-of-band (class-defined)
 *              mechanism (USB 3.1 8.12.1.4).
 * @return      YES on success,  An IOReturn error will be returned if streams were not enabled for
 *              this IOUSBHostPipe.
 */
- (BOOL)disableStreamsWithError:(NSError* _Nullable*)error;

/*!
 * @brief       Return the stream associated with <code>streamID</code>
 * @discussion  This method will return the stream associated with <code>streamID</code>.
 *              The caller must release the IOUSBHostStream when finished using it.
 *              <code>[IOUSBHostPipe enableStreams]</code> must be called before this
 *              method will return a stream object.
 * @param       streamID Stream ID in the range of 1 to <code>max</code>, where <code>max</code>
 *              can be retrieved by calling <code>getEndpointMaxStreams</code> with
 *              the endpoint descriptors.
 * @return      Pointer to an IOUSBHostStream object or nil. nil may be returned if either the
 *              device or the underlying host controller do not support that stream ID.
 */
- (nullable IOUSBHostStream*)copyStreamWithStreamID:(NSUInteger)streamID
                                              error:(NSError* _Nullable*)error;

@end

NS_ASSUME_NONNULL_END
