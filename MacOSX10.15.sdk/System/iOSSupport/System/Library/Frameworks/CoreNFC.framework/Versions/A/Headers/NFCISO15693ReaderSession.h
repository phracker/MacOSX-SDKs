//
//  NFCISO15693ReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//
#ifndef NFCISO15693ReaderSession_h
#define NFCISO15693ReaderSession_h

#import <Foundation/Foundation.h>

@protocol NFCReaderSessionDelegate;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - ISO15693 reader session

/*!
 * @class NFCISO15693ReaderSession
 *
 * @discussion Reader session for processing ISO15693 tags.  @link [NFCReaderSessionDelegate readerSession:didDetectTags:] @link/ will return tag objects that
 *             are conformed to the NFCISO15693Tag protocol.  This session requires the "com.apple.developer.nfc.readersession.formats" entitlement in your process.
 *
 * NOTE:
 * Only one NFCReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 * The NFCISO15693 tag object returned by this session will only respond to the legacy APIs that are introducted in iOS11.  
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCISO15693ReaderSession : NFCReaderSession

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithQueue:
 *
 * @param delegate  The session will hold a weak ARC reference to this @link NFCReaderSessionDelegate @link/ object.
 * @param queue     A dispatch queue where NFCReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                  cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 *
 * @return          A new NFCISO15693ReaderSession instance.
 */
- (instancetype)initWithDelegate:(id<NFCReaderSessionDelegate>)delegate queue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER NS_EXTENSION_UNAVAILABLE("Not available to extensions");

/*!
 * @method restartPolling
 *
 * @discussion Restart the polling sequence in this session to discover new tags.  Tags that are returned previously by @link [NFCReaderSessionDelegate readerSession:didDetectTags:]
 *             @link/ will become invalid, and all references to these tags shall be removed to properly release the resources.  Calling this method on an invalidated session
 *             will have no effect; a new reader session is required to restart the reader.
 */
- (void)restartPolling;

@end

NS_ASSUME_NONNULL_END

#endif
