//
//  NFCVASReaderSession.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCVASReaderSession_h
#define NFCVASReaderSession_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NFCReaderSession;
@class NFCVASReaderSession;

/*!
 * @enum NFCVASMode
 *
 * @constant NFCVASModeURLOnly     Reserved.
 * @constant NFCVASModeNormal      Full VAS protocol.
 */
typedef NS_ENUM(NSInteger, NFCVASMode) {
    NFCVASModeURLOnly API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)    = 0,
    NFCVASModeNormal API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)     = 1,
    
    VASModeURLOnly API_DEPRECATED_WITH_REPLACEMENT("NFCVASModeURLOnly", ios(13.0, 14.0))    = NFCVASModeURLOnly,
    VASModeNormal API_DEPRECATED_WITH_REPLACEMENT("NFCVASModeNormal", ios(13.0, 14.0))      = NFCVASModeNormal,
} API_AVAILABLE(ios(13.0));

typedef NFCVASMode VASMode API_DEPRECATED_WITH_REPLACEMENT("NFCVASMode", ios(13.0, 14.0));

/*!
 * @class NFCVASCommandConfiguration
 *
 * @discussion Configuration for one GET VAS DATA command.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCVASCommandConfiguration : NSObject<NSCopying>

/*!
 * @property mode
 * @discussion  VAS protocol mode.
 */
@property (nonatomic, assign) NFCVASMode mode API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property passTypeIdentifier
 * @discussion  Wallet Pass Type Identifier of the Wallet Pass.  The string value will be used to calculate the
 *              Merchant ID value for the GET VAS DATA command.
 */
@property (nonatomic, retain) NSString *passTypeIdentifier API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property url
 * @discussion  Merchant URL object.  Maximum length of the URL is 64 characters, including the schema.
 *              Set to nil to disable the merchant URL.
 */
@property (nonatomic, retain, nullable) NSURL *url API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method initWithVASMode:passTypeIdentifier:url:
 *
 * @param mode                  VAS operation mode
 * @param passTypeIdentifier    Pass type identifier of the Wallet pass.
 * @param url                   URL for VAR URL Only mode.  Set to <i>nil</i> for VAS normal mode.
 */
- (instancetype)initWithVASMode:(NFCVASMode)mode passTypeIdentifier:(NSString *)passTypeIdentifier url:(NSURL * _Nullable)url NS_DESIGNATED_INITIALIZER;
@end

/*!
 * @enum NFCVASErrorCode
 *
 * @discussion Response APDU status word.
 */
typedef NS_ENUM(NSInteger, NFCVASErrorCode) {
    NFCVASErrorCodeSuccess API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)                        = 0x9000,
    NFCVASErrorCodeDataNotFound API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)                   = 0x6A83,
    NFCVASErrorCodeDataNotActivated API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)               = 0x6287,
    NFCVASErrorCodeWrongParameters API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)                = 0x6B00,
    NFCVASErrorCodeWrongLCField API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)                   = 0x6700,
    NFCVASErrorCodeUserIntervention API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)               = 0x6984,
    NFCVASErrorCodeIncorrectData API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)                  = 0x6A80,
    NFCVASErrorCodeUnsupportedApplicationVersion API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)  = 0x6340,
    
    VASErrorCodeSuccess API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCodeSuccess", ios(13.0, 14.0))                                              = NFCVASErrorCodeSuccess,
    VASErrorCodeDataNotFound API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCodeDataNotFound", ios(13.0, 14.0))                                    = NFCVASErrorCodeDataNotFound,
    VASErrorCodeDataNotActivated API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCodeDataNotActivated", ios(13.0, 14.0))                            = NFCVASErrorCodeDataNotActivated,
    VASErrorCodeWrongParameters API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCodeWrongParameters", ios(13.0, 14.0))                              = NFCVASErrorCodeWrongParameters,
    VASErrorCodeWrongLCField API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCodeWrongLCField", ios(13.0, 14.0))                                    = NFCVASErrorCodeWrongLCField,
    VASErrorCodeUserIntervention API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCodeUserIntervention", ios(13.0, 14.0))                            = NFCVASErrorCodeUserIntervention,
    VASErrorCodeIncorrectData API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCodeIncorrectData", ios(13.0, 14.0))                                  = NFCVASErrorCodeIncorrectData,
    VASErrorCodeUnsupportedApplicationVersion API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCodeUnsupportedApplicationVersion", ios(13.0, 14.0))  = NFCVASErrorCodeUnsupportedApplicationVersion,
} API_AVAILABLE(ios(13.0));

typedef NFCVASErrorCode VASErrorCode API_DEPRECATED_WITH_REPLACEMENT("NFCVASErrorCode", ios(13.0, 14.0));

/*!
 * @class NFCVASResponse
 *
 * @discussion Response from one GET VAS DATA command.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCVASResponse : NSObject<NSCopying>

/*!
 * @property status
 *
 * @discussion Response APDU status.
 */
@property (nonatomic, assign, readonly) NFCVASErrorCode status API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property vasData
 *
 * @discussion VAS data.
 */
@property (nonatomic, retain, readonly) NSData *vasData API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @property mobileToken
 *
 * @discussion Mobile token value.
 */
@property (nonatomic, retain, readonly) NSData *mobileToken API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

/*!
 * @protocol    NFCVASReaderSessionDelegate
 *
 * @discussion  Value Added Service (VAS) reader session callbacks.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@protocol NFCVASReaderSessionDelegate <NSObject>
@optional

/*!
 * @method readerSessionDidBecomeActive:
 *
 * @param session   The session object in the active state.
 *
 * @discussion      Gets called when the NFC reader session has become active. RF is enabled and reader is scanning for VAS tags.
 *                  The @link readerSession:didReceiveVASResponses: @link/ will be called when a VAS transaction is completed.
 */
- (void)readerSessionDidBecomeActive:(NFCVASReaderSession *)session API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

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
- (void)readerSession:(NFCVASReaderSession *)session didInvalidateWithError:(NSError *)error API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method readerSession:didReceiveVASResponses:
 *
 * @param session   The session object used for tag detection.
 * @param responses Array of @link NFCVASResponse @link/ objects.  The order of the response objects follows the
 *                  sequence of GET VAS DATA sent by the reader session.
 *
 * @discussion      Gets called when the reader completes the requested VAS transaction.  Polling
 *                  is automatically restarted once the detected tag is removed from the reader's read range.
 */
- (void)readerSession:(NFCVASReaderSession *)session didReceiveVASResponses:(NSArray<NFCVASResponse *> *)responses API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end

/*!
 * @class NFCVASReaderSession
 *
 * @discussion Reader session for processing Value Added Service (VAS) tags.  This session requires the "com.apple.developer.nfc.readersession.formats"
 *             entitlement in your process.  In addition your application's Info.plist must contain a non-empty usage description string.
 *             @link NFCReaderErrorSecurityViolation @link/ will be returned from @link [NFCVASReaderSessionDelegate readerSession:didInvalidateWithError:] @link/
 *             if the required entitlement is missing when session is started.
 *
 * NOTE:
 * Only one NFCReaderSession can be active at any time in the system. Subsequent opened sessions will get queued up and processed by the system in FIFO order.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCVASReaderSession : NFCReaderSession

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithVASCommandConfigurations:delegate:queue:invalidateAfterFirstRead:
 *
 * @param commandConfigurations     NSArray of NFCVASCommandConfiguration objects.  Each NFCVASCommandConfiguration defines one GET VAS DATA command send to
 *                                  a compatible tag when discovered.  The order of elements in the array defines the order of the command execution.
 * @param delegate  The session will hold a weak ARC reference to this @link NFCVASReaderSessionDelegate @link/ object.
 * @param queue     A dispatch queue where NFCVASReaderSessionDelegate delegate callbacks will be dispatched to.  A <i>nil</i> value will
 *                  cause the creation of a serial dispatch queue internally for the session.  The session object will retain the provided dispatch queue.
 *
 * @return          A new NFCVASReaderSession instance.
 *
 * @discussion      A VAS reader session will automatically scan and detect tag that is compatible with the VAS protocol.  The session will advertise as a
 *                  VAS App Only terminal.  A modal system UI will present once -beginSession is called to inform the start of the session; the UI sheet
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
 */
- (instancetype)initWithVASCommandConfigurations:(NSArray<NFCVASCommandConfiguration *> *)commandConfigurations
                                        delegate:(id<NFCVASReaderSessionDelegate>)delegate
                                           queue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) NS_EXTENSION_UNAVAILABLE("Not available to extensions");
@end

NS_ASSUME_NONNULL_END

#endif /* NFCVASReaderSession_h */
