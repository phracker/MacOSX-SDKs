//
//  NFCPaymentTagReaderSession.h
//  CoreNFC
//
//  Copyright © 2025 Apple. All rights reserved.
//

#ifndef NFCPaymentTagReaderSession_h
#define NFCPaymentTagReaderSession_h

#import <Foundation/Foundation.h>
#import <CoreNFC/NFCTagReaderSession.h>


NS_ASSUME_NONNULL_BEGIN

#pragma mark - Payment tag reader session

/*!
 * @class NFCPaymentTagReaderSession
 *
 * @discussion  Reader session for processing NFC payment tags supporting the @link NFCTagTypeISO7816Compatible @link/ type.
 *              @link [NFCTagReaderSessionDelegate readerSession:didDetectTags:] @link/ will return a @link NFCISO7816Tag @link /. object.
 *              This session requires the "com.apple.developer.nfc.readersession.formats" entitlement in your process.
 *              In addition your application's Info.plist must contain a non-empty usage description string.  @link NFCReaderErrorSecurityViolation @link/ will be
 *              returned from @link [NFCTagReaderSessionDelegate tagReaderSession:didInvalidateWithError:] @link/ if the required entitlement is missing when session is started.
 *
 *              When the reader discovers a compatible ISO7816 tag it automatically performs a SELECT command (by DF name) using the values provided in
 *              "com.apple.developer.nfc.readersession.iso7816.select-identifiers" in the specified array order.  The tag is
 *              returned from the [NFCTagReaderSessionDelegate readerSession:didDetectTags:] call on the first successful SELECT command.
 *              The initialSelectedAID property returns the application identifier of the selected application.  Tag will not be returned
 *              to the NFCTagReaderSessionDelegate if no application described in "com.apple.developer.nfc.readersession.iso7816.select-identifiers"
 *              is found.
 *
 * NOTE:
 * - Only one NFCReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 */
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)
@interface NFCPaymentTagReaderSession : NFCTagReaderSession
/*!
 * @method initWithDelegate:queue:
 *
 * @param delegate      The session will hold a weak ARC reference to this @link NFCTagReaderSessionDelegate @link/ object.
 * @param queue         A dispatch queue where NFCTagReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                      cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 *
 * @return              A new NFCPaymentTagReaderSession instance.
 *
 * NOTE:
 * The super class `-initWithPollingOption:delegate:queue:` initializer would only accept NFCPollingOption.NFCPollingISO14443; all other options will be ignored.
 */
- (instancetype)initWithDelegate:(id<NFCTagReaderSessionDelegate>)delegate
                           queue:(nullable dispatch_queue_t)queue API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos) NS_EXTENSION_UNAVAILABLE("Not available to extensions");
@end

NS_ASSUME_NONNULL_END

#endif /* NFCPaymentTagReaderSession_h */
