//
//  NFCTagReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCTagReaderSession_h
#define NFCTagReaderSession_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NFCTag;
@class NFCTagReaderSession;

/*!
 * @protocol NFCTagReaderSessionDelegate
 *
 * @discussion Tag reader session delegate
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCTagReaderSessionDelegate <NSObject>
@required

/*!
 * @method tagReaderSession:didInvalidateWithError:
 *
 * @param session   The session object that is invalidated.
 * @param error     The error indicates the invalidation reason.
 *
 * @discussion      Gets called when a session becomes invalid.  At this point the client is expected to discard
 *                  the returned session object.
 */
- (void)tagReaderSession:(NFCTagReaderSession *)session didInvalidateWithError:(NSError *)error API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@optional

/*!
 * @method tagReaderSessionDidBecomeActive:
 *
 * @param session   The session object in the active state.
 *
 * @discussion      Gets called when the NFC reader session has become active. RF is enabled and reader is scanning for tags.
 *                  The @link readerSession:didDetectTags: @link/ will be called when a tag is detected.
 */
- (void)tagReaderSessionDidBecomeActive:(NFCTagReaderSession *)session API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method tagReaderSession:didDetectTags:
 *
 * @param session   The session object used for tag detection.
 * @param tags      Array of @link NFCTag @link/ objects.
 *
 * @discussion      Gets called when the reader detects NFC tag(s) in the polling sequence.
 */
- (void)tagReaderSession:(NFCTagReaderSession *)session didDetectTags:(NSArray<__kindof id<NFCTag>> *)tags API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end


#pragma mark - Raw tag reader session

/*!
 * @class NFCTagReaderSession
 *
 * @discussion  Reader session for processing NFC tags supporting one of the @link NFCTagType @link/ types.  @link [NFCTagReaderSessionDelegate readerSession:didDetectTags:] @link/
 *              will return tag objects matching the requested type for the session.  This session requires the "com.apple.developer.nfc.readersession.formats" entitlement
 *              in your process.  In addition your application's Info.plist must contain a non-empty usage description string. @link NFCReaderErrorSecurityViolation @link/ will be
 *              returned from @link [NFCTagReaderSessionDelegate tagReaderSession:didInvalidateWithError:] @link/ if the required entitlement is missing when session is started.
 *
 * NOTE:
 * - Only one NFCReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 * - If the session is configured with @link NFCPollingISO14443 @link/ and an ISO7816 compliant MiFare tag that contains one of the applications listed in the
 *   "com.apple.developer.nfc.readersession.iso7816.select-identifiers" array in Info.plist is found, then @link [NFCTagReaderSessionDelegate readerSession:didDetectTags:] @link/
 *   will return a tag instance conform to the @link NFCISO7816Tag @link/ protocol.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCTagReaderSession : NFCReaderSession

/*!
 *  @property connectedTag  Current connected tag object; nil if no tag is connected in the session.
 */
@property (nonatomic, readonly, retain, nullable) id<NFCTag> connectedTag API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @enum NFCPollingOption
 *
 * @constant NFCPollingISO14443     Support both Type A & B modulation.  NFCTagTypeISO7816Compatible and NFCTagTypeMiFare tags will be discovered.
 * @constant NFCPollingISO15693     NFCTagTypeISO15693 tag will be discovered.
 * @constant NFCPollingISO18092     NFCTagTypeFeliCa tag will be discovered.
 */
typedef NS_OPTIONS(NSInteger, NFCPollingOption) {
    NFCPollingISO14443 API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)     = 0x1,
    NFCPollingISO15693 API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)     = 0x2,
    NFCPollingISO18092 API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)     = 0x4,
};

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithPollingOption:delegate:queue:
 *
 * @param pollingOption Configures the RF polling of the reader session; multiple options can be OR'ed together.  This option affects the possible NFC tag type discover.
 * @param delegate      The session will hold a weak ARC reference to this @link NFCTagReaderSessionDelegate @link/ object.
 * @param queue         A dispatch queue where NFCTagReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                      cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 *
 * @return              A new NFCTagReaderSession instance.
 */
- (instancetype)initWithPollingOption:(NFCPollingOption)pollingOption
                             delegate:(id<NFCTagReaderSessionDelegate>)delegate
                                queue:(nullable dispatch_queue_t)queue API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) NS_EXTENSION_UNAVAILABLE("Not available to extensions") ;

/*!
 * @method restartPolling
 *
 * @discussion Restart the polling sequence in this session to discover new tags.  New tags discovered from polling will return in the subsequent @link [NFCTagReaderSessionDelegate tagReaderSession:didDetectTags:]
 *             @link/ call. Tags that are returned previously by @link [NFCTagReaderSessionDelegate tagReaderSession:didDetectTags:] @link/ will become invalid, 
 *             and all references to these tags shall be removed to properly release the resources.  Calling this method on an invalidated session
 *             will have no effect; a new reader session is required to restart the reader.
 */
- (void)restartPolling API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method connectToTag:completionHandler:
 *
 * @param tag   A NFCTag protocol compliant tag object that will be connected to.
 *
 * @param completionHandler Completion handler called when the operation is completed.  error is nil if operation succeeds.
 *                          A @link NFCErrorDomain @link/ error is returned when there is a communication issue with the tag.
 *
 * @discussion  This method establishes a tag connection and activates the tag.  Connecting to the same tag that is currently opened has no effect.
 *              Connecting to a different tag will automatically terminate the previous tag connection and put it into the halt state.  Tag stays in the
 *              connected state until another tag is connected or the polling is restarted.
 */
- (void)connectToTag:(id<NFCTag>)tag completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
@end

NS_ASSUME_NONNULL_END

#endif /* NFCTagReaderSession_h */
