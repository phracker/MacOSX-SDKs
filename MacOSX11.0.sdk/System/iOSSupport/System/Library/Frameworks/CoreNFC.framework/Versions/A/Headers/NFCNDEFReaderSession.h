//
//  NFCNDEFReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCNDEFReaderSession_h
#define NFCNDEFReaderSession_h

#import <Foundation/Foundation.h>

@class NFCReaderSession;
@class NFCNDEFReaderSession;
@class NFCNDEFMessage;
@protocol NFCNDEFTag;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @protocol NFCNDEFReaderSessionDelegate
 *
 * @discussion NDEF reader session callbacks.  Presence of the -readerSession:didDetectTags: optional method will change the session behaviour
 *             into a read-write session where @link NFCNDEFTag @link/ objects are returned.
 *
 * @note       A read-write session does not trigger the -readerSession:didDetectNDEFs: method.
 * @note       A read-write session does not get invalidate automatically after a successful tag detection.  Invalidation occurs when
 *             the invalidation method is called explicitly or the 60 seconds session time limit is reached.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCNDEFReaderSessionDelegate <NSObject>

@required

/*!
 * @method readerSession:didInvalidateWithError:
 *
 * @param session   The session object that is invalidated.
 * @param error     The error indicates the invalidation reason.
 *
 * @discussion      Gets called when a session becomes invalid.  At this point the client is expected to discard
 *                  the returned session object.
 */
- (void)readerSession:(NFCNDEFReaderSession *)session didInvalidateWithError:(NSError *)error API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readerSession:didDetectNDEFs:
 *
 * @param session   The session object used for tag detection.
 * @param messages  Array of @link NFCNDEFMessage @link/ objects.
 *
 * @discussion      Gets called when the reader detects NFC tag(s) with NDEF messages in the polling sequence.  Polling
 *                  is automatically restarted once the detected tag is removed from the reader's read range.  This method
 *                  is only get call if the optional -readerSession:didDetectTags: method is not
 *                  implemented.
 */
- (void)readerSession:(NFCNDEFReaderSession *)session didDetectNDEFs:(NSArray<NFCNDEFMessage *> *)messages API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos);

@optional

/*!
 * @method readerSession:didDetectTags:
 *
 * @param session   The session object used for NDEF tag detection.
 * @param tags      Array of @link NFCNDEFTag @link/ objects.
 *
 * @discussion      Gets called when the reader detects NDEF tag(s) in the RF field.  Presence of this method overrides -readerSession:didDetectNDEFs: and enables
 *                  read-write capability for the session.
 */
- (void)readerSession:(NFCNDEFReaderSession *)session didDetectTags:(NSArray<__kindof id<NFCNDEFTag>> *)tags API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readerSessionDidBecomeActive:
 *
 * @param session   The session object in the active state.
 *
 * @discussion      Gets called when the NFC reader session has become active. RF is enabled and reader is scanning for tags.
 */
- (void)readerSessionDidBecomeActive:(NFCNDEFReaderSession *)session API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end


#pragma mark - NDEF reader session

/*!
 * @class NFCNDEFReaderSession
 *
 * @discussion NFC reader session for processing NFC Data Exchange Format (NDEF) tags.  This session requires the "com.apple.developer.nfc.readersession.formats"
 *             entitlement in your process.  In addition your application's Info.plist must contain a non-empty usage description string.
 *             @link NFCReaderErrorSecurityViolation @link/ will be returned from @link [NFCNDEFReaderSessionDelegate readerSession:didInvalidateWithError:] @link/
 *             if the required entitlement is missing when session is started.
 *
 * @note       Only one NFCNDEFReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 * @note       If the delegate object implements the optional -readerSession:didDetectTags: method the NFCNDEFReaderSession will become a read-write session; see @link
 *             NFCNDEFReaderSessionDelegate @link/ for detail description.
 * @note       The error symbol will not be drawn on the action sheet if -invalidateSessionWithError: method is called on a session that is not a read-write session;
 *             -invalidateSession: method should be used in a read-only session.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFReaderSession : NFCReaderSession

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithDelegate:queue:invalidateAfterFirstRead:
 *
 * @param delegate  The session will hold a weak ARC reference to this @link NFCNDEFReaderSessionDelegate @link/ object.
 * @param queue     A dispatch queue where NFCNDEFReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                  cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 * @param invalidateAfterFirstRead  Session will automatically invalidate after the first NDEF tag is read successfully when this is set to YES, and
 *                                  -readerSession:didInvalidateWithError: will return NFCReaderSessionInvalidationErrorFirstNDEFTagRead in this case.
 *                                  Set to NO if the delegate object implements the -readerSession:didDetectTags: optional method.
 *
 * @return          A new NFCNDEFReaderSession instance.
 *
 * @discussion      A NDEF reader session will scan and detect NFC Forum tags that contain a valid NDEF message.  NFC Forum Tag type 1 to 5 that
 *                  is NDEF formatted are supported.  A modal system UI will present once -beginSession is called to inform the start of the session; the UI sheet
 *                  is automatically dismissed when the session is invalidated either by the user or by calling -invalidateSession.  The alertMessage property shall be set
 *                  prior to -beginSession to display a message on the action sheet UI for the tag scanning operation.
 *
 *                  The reader session has the following properties:
 *                  + An opened session has a 60 seconds time limit restriction after -beginSession is called; -readerSession:didInvalidateWithError: will return
 *                  NFCReaderSessionInvalidationErrorSessionTimeout error when the time limit is reached.
 *                  + Only 1 active reader session is allowed in the system; -readerSession:didInvalidateWithError: will return NFCReaderSessionInvalidationErrorSystemIsBusy
 *                  when a new reader session is initiated by -beginSession when there is an active reader session.  
 *                  + -readerSession:didInvalidateWithError: will return NFCReaderSessionInvalidationErrorUserCanceled when user clicks on the done button on the UI.
 *                  + -readerSession:didInvalidateWithError: will return NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly when the client application enters
 *                  the background state.
 *                  + -readerSession:didInvalidateWithError: will return NFCReaderErrorUnsupportedFeature when 1) reader mode feature is not available on the hardware,
 *                  2) client application does not have the required entitlement.
 *
 *                  The session's mode of operation is determined by the implementation of the delegate object.  The -readerSession:didDetectTags: optional method will
 *                  enable the read-write capability and suppress the -readerSession:didDetectNDEFs: callback for the session.
 */
- (instancetype)initWithDelegate:(id<NFCNDEFReaderSessionDelegate>)delegate
                           queue:(nullable dispatch_queue_t)queue
        invalidateAfterFirstRead:(BOOL)invalidateAfterFirstRead NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos) NS_EXTENSION_UNAVAILABLE("Not available to extensions");

/*!
 * @method restartPolling
 *
 * @discussion Restart the polling sequence in this session to discover new NDEF tags.  New tags discovered from polling will return in the subsequent @link [NFCNDEFReaderSessionDelegate readerSession:didDetectTags:]
 *             @link/ call.  Tags that are returned previously by @link [NFCNDEFReaderSessionDelegate -readerSession:didDetectTags:] @link/ will become invalid,
 *             and all references to these tags shall be removed to properly release the resources.  Calling this method on an invalidated session
 *             will have no effect; a new reader session is required to restart the reader. Calling this method on an instance initiated with a delegate object that does not implement
 *             the optional -readerSession:didDetectTags: method has no effect as RF polling restart is done automatically.
 */
- (void)restartPolling API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method connectToTag:completionHandler:
 *
 * @param tag   A NFCTag protocol compliant tag object that will be connect to.
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *
 * @discussion  This method establishes a tag connection and activates the tag.  Connecting to the same tag that is currently opened has no effect.
 *              Connecting to a different tag will automatically terminate the previous tag connection and put it into the halt state.  Tag stays in the
 *              connected state until another tag is connected or the polling is restarted.
 */
- (void)connectToTag:(id<NFCNDEFTag>)tag completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif
