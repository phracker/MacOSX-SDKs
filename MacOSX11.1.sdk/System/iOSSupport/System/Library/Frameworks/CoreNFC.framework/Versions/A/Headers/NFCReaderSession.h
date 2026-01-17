//
//  NFCReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCReaderSession_h
#define NFCReaderSession_h

#import <Foundation/Foundation.h>
#import <dispatch/dispatch.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCReaderSession;
@protocol NFCTag;

#pragma mark - NFCReaderSession, protocol of a reader session

/*!
 * @protocol NFCReaderSession
 *
 * @discussion General reader session functions
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCReaderSession <NSObject>

/*!
 * @property ready
 *
 * @return <i>YES</i> if the reader session is started and ready to use.
 *
 * @discussion The RF discovery polling begins immediately when a reader session is activated successfully.
 *             The @link readerSession:didDetectTags: @link/ will be called when a tag is detected.
 */
@property (nonatomic, getter=isReady, readonly) BOOL ready API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property alertMessage
 *
 * @discussion Descriptive text message that is displayed on the alert action sheet once tag scanning has started.  The string can be update
 *             dynamically in any thread context as long as the session is valid.  This should be set prior to calling @link beginSession @link/ to display
 *             the correct message.  Use this string to provide additional context about the NFC reader mode operation.
 */
@property (nonatomic, copy) NSString *alertMessage API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);


/*!
 * @method beginSession:
 *
 * @discussion      Starts the session.  The @link [NFCReaderSessionDelegate readerSessionDidBecomeActive:] @link/ will be called when the reader session
 *                  is activated successfully.  @link [NFCReaderSessionDelegate readerSession:didDetectTags:] @link/ will return tag objects that are
 *                  conformed to the @link NFCTag @link/ protocol.  @link [NFCReaderSessionDelegate readerSession:didInvalidateWithError:] will return
 *                  errors related to the session start.
 */
- (void)beginSession API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method invalidateSession
 *
 * @discussion Closes the reader session.  The session cannot be re-used.
 */
- (void)invalidateSession API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method invalidateSessionWithErrorMessage:
 *
 * @discussion Closes the reader session.  The session cannot be re-used.  The specified error message and an error symbol will be displayed momentarily
 *             on the action sheet before it is automatically dismissed.
 */
- (void)invalidateSessionWithErrorMessage:(NSString *)errorMessage API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

#pragma mark - NFCReaderSessionDelegate, Reader session callback delegate

/*!
 * @protocol NFCReaderSession
 *
 * @discussion General reader session callbacks
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCReaderSessionDelegate <NSObject>
@required

/*!
 * @method readerSessionDidBecomeActive:
 *
 * @param session   The session object in the active state.
 *
 * @discussion      Gets called when the NFC reader session has become active. RF is enabled and reader is scanning for tags.
 *                  The @link readerSession:didDetectTags: @link/ will be called when a tag is detected.
 */
- (void)readerSessionDidBecomeActive:(NFCReaderSession *)session API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readerSession:didInvalidateWithError:
 *
 * @param session   The session object that is invalidated.
 * @param error     The error indicates the invalidation reason.
 *
 * @discussion      Gets called when a session becomes invalid.  At this point the client is expected to discard
 *                  the returned session object.
 */
- (void)readerSession:(NFCReaderSession *)session didInvalidateWithError:(NSError *)error API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

@optional
/*!
 * @method readerSession:didDetectTags:
 *
 * @param session   The session object used for tag detection.
 * @param tags      Array of @link NFCTag @link/ objects.
 *
 * @discussion      Gets called when the reader detects NFC tag(s) in the polling sequence.
 */
- (void)readerSession:(NFCReaderSession *)session didDetectTags:(NSArray<__kindof id<NFCTag>> *)tags API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

#pragma mark - NFCReaderSession, Reader session base class

/*!
 * @class NFCReaderSession
 *
 * @discussion      This represents a NFC reader session for processing tags; this base class cannot be instantiate. Only one NFCReaderSession 
 *                  can be active at any time in the system.  Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCReaderSession : NSObject<NFCReaderSession>

@property (nonatomic, weak, readonly) id delegate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property readingAvailable
 *
 * @discussion YES if device supports NFC tag reading.
 */
@property (class, nonatomic, readonly) BOOL readingAvailable API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property sessionQueue
 *
 * @discussion  The NFCReaderSessionDelegate delegate callbacks and the completion block handlers for tag operation will be dispatched on this queue.
 */
@property (nonatomic, readonly) dispatch_queue_t sessionQueue API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

- (instancetype)init NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END

#endif /* NFCReaderSession_h */
