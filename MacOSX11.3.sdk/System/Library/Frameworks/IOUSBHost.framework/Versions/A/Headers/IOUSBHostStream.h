//
//  IOUSBHostStream.h
//  IOUSBHost
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IOUSBHost/IOUSBHostIOSource.h>

@class IOUSBHostPipe;

NS_ASSUME_NONNULL_BEGIN

@interface IOUSBHostStream : IOUSBHostIOSource

/*!
 * @brief   Returns the IOUSBHostPipe this stream was created from
 * @return  IOUSBHostPipe pointer
 */
@property(readonly) IOUSBHostPipe* hostPipe;

/*!
 * @brief   Returns streamID associated with this IOUSBHostStream.
 * @return  streamID
 */
@property(readonly) NSUInteger streamID;

/*!
 * @brief       Abort pending I/O requests.
 * @discussion  A stream context must be set as non-active on the device via an out-of-band
 *              (class-defined) mechanism before this method is called (USB 3.1 8.12.1.4).
 *              A non-active stream will not be selected by the device to become the current
 *              stream on the endpoint.
 * @param       option IOUSBHostAbortOption by default IOUSBHostAbortOptionSynchronous is used
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
-(BOOL)abortWithOption:(IOUSBHostAbortOption)option
                 error:(NSError* _Nullable*)error;

/*!
 * @brief       Abort pending I/O requests.
 * @discussion  A stream context must be set as non-active on the device via an out-of-band
 *              (class-defined) mechanism before this method is called (USB 3.1 8.12.1.4).
 *              A non-active stream will not be selected by the device to become the current
 *              stream on the endpoint.
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
-(BOOL)abortWithError:(NSError* _Nullable*)error;

#pragma mark IO

/*!
 * @brief       Send an IO request on the source
 * @discussion  This method will send a synchronous request on the IO source, and will not return
 *              until the request is complete. CompletionTimeouts are not applicable to streams.
 * @param       data NSData* pointer containing the buffer to use for the transfer
 * @param       bytesTransferred NSUInteger reference which will be updated with the bytes
 *              transferred during the request
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)sendIORequestWithData:(nullable NSMutableData*)data
             bytesTransferred:(nullable NSUInteger*)bytesTransferred
                        error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Enqueue an IO request on the source
 * @discussion  This method is used to issue an asynchronous I/O request on the IO source.
 *              CompletionTimeouts are not applicable to streams.
 * @param       data pointer containing the buffer to use for the transfer
 * @return      YES on success, an IOReturn error code will be reported on failure
 */
- (BOOL)enqueueIORequestWithData:(nullable NSMutableData*)data
                           error:(NSError* _Nullable*)error
               completionHandler:(nullable IOUSBHostCompletionHandler)completionHandler;

@end

NS_ASSUME_NONNULL_END
