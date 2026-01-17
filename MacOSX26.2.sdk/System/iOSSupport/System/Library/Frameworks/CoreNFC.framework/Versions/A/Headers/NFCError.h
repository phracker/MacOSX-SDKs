//
//  NFCError.h
//  CoreNFC
//
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef NFCError_h
#define NFCError_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)
extern NSErrorDomain const NFCErrorDomain;

/*!
 * @enum NFCReaderError
 *
 * @discussion  Possible errors returned by CoreNFC framework reader session.
 * @constant    NFCReaderErrorUnsupportedFeature                                Core NFC is not supported on the current platform.
 * @constant    NFCReaderErrorSecurityViolation                                 Missing required entitlement and/or privacy settings from the client app.
 * @constant    NFCReaderErrorInvalidParameter                                  Input parameter is invalid.
 * @constant    NFCReaderErrorInvalidParameterLength                            Length of input parameter is invalid, i.e. size of data container.
 * @constant    NFCReaderErrorParameterOutOfBound                               Parameter value is outside of the acceptable boundary / range.
 * @constant    NFCReaderErrorRadioDisabled                                     NFC Radio is disabled.
 * @constant    NFCReaderErrorIneligible                                        The current system setting or hardware configuation isn’t eligible to use the requested reader service.
 * @constant    NFCReaderErrorAccessNotAccepted                                 The person using the app hasn’t yet accepted or declined your app’s request to use the selected service.
 * @constant    NFCReaderTransceiveErrorTagConnectionLost                       Connection to the tag is lost.
 * @constant    NFCReaderTransceiveErrorRetryExceeded                           Maximum data transmission retry has reached.
 * @constant    NFCReaderTransceiveErrorTagResponseError                        Tag response is invalid or tag does not provide a response.  Additional error information may be contain in the underlying user info dictionary.
 * @constant    NFCReaderTransceiveErrorSessionInvalidated                      Session has been previously invalidated.
 * @constant    NFCReaderTransceiveErrorPacketTooLong                           Packet length has exceeded the limit.
 * @constant    NFCReaderTransceiveErrorTagNotConnected                         Tag is not in the connected state.
 * @constant    NFCReaderSessionInvalidationErrorUserCanceled                   Session is invalidated by the user.
 * @constant    NFCReaderSessionInvalidationErrorSessionTimeout                 Session is timed out.
 * @constant    NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly  Session is terminated unexpectedly.
 * @constant    NFCReaderSessionInvalidationErrorSystemIsBusy                   Core NFC is temporary unavailable due to system resource constraints.
 * @constant    NFCReaderSessionInvalidationErrorFirstNDEFTagRead               Session is terminated after the 1st NDEF tag is read.
 * @constant    NFCTagCommandConfigurationErrorInvalidParameters
 * @constant    NFCNdefReaderSessionErrorTagNotWritable                         NDEF tag is not writable.
 * @constant    NFCNdefReaderSessionErrorTagUpdateFailure                       NDEF tag write fails.
 * @constant    NFCNdefReaderSessionErrorTagSizeTooSmall                        NDEF tag memory size is too small to store the desired data.
 * @constant    NFCNdefReaderSessionErrorZeroLengthMessage                      NDEF tag does not contain any NDEF message.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
typedef NS_ERROR_ENUM(NFCErrorDomain, NFCReaderError) {
    NFCReaderErrorUnsupportedFeature API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)                             = 1,
    NFCReaderErrorSecurityViolation API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderErrorInvalidParameter API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderErrorInvalidParameterLength API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderErrorParameterOutOfBound API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderErrorRadioDisabled API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderErrorIneligible API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderErrorAccessNotAccepted API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    
    NFCReaderTransceiveErrorTagConnectionLost API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)                    = 100,
    NFCReaderTransceiveErrorRetryExceeded API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderTransceiveErrorTagResponseError API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderTransceiveErrorSessionInvalidated API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderTransceiveErrorTagNotConnected API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderTransceiveErrorPacketTooLong API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),

    NFCReaderSessionInvalidationErrorUserCanceled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)                = 200,
    NFCReaderSessionInvalidationErrorSessionTimeout API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderSessionInvalidationErrorSystemIsBusy API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCReaderSessionInvalidationErrorFirstNDEFTagRead API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),

    NFCTagCommandConfigurationErrorInvalidParameters API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)             = 300,

    NFCNdefReaderSessionErrorTagNotWritable API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)                      = 400 ,
    NFCNdefReaderSessionErrorTagUpdateFailure API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCNdefReaderSessionErrorTagSizeTooSmall API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
    NFCNdefReaderSessionErrorZeroLengthMessage API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos),
};

#pragma mark - ISO15693 specific command response error code

/*!
 *  Key in NSError userInfo dictionary.  The corresponding value is the NSUInteger error code from tag's response.
 *  Refer to ISO15693 specification for the error code values.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)
extern NSString * const NFCISO15693TagResponseErrorKey;

/*!
 *  Key in NSError userInfo dictionary.  Presence of this key indicates the received response packet length is invalid.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos)
extern NSString * const NFCTagResponseUnexpectedLengthErrorKey;

NS_ASSUME_NONNULL_END

#endif /* CNFCError_h */
