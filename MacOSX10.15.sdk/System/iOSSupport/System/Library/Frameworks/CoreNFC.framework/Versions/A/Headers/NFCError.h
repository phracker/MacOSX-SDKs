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

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
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
 * @constant    NFCReaderTransceiveErrorTagConnectionLost                       Connection to the tag is lost.
 * @constant    NFCReaderTransceiveErrorRetryExceeded                           Maximum data transmission retry has reached.
 * @constant    NFCReaderTransceiveErrorTagResponseError                        Tag response is invalid.  Additional error information may be contain in the underlying user info dictionary.
 * @constant    NFCReaderTransceiveErrorSessionInvalidated                      Session has been previously invalidated.
 * @constant    NFCReaderTransceiveErrorTagNotConnected                         Tag is not in the connected state.
 * @constant    NFCReaderSessionInvalidationErrorUserCanceled                   Session is invalidated by the user.
 * @constant    NFCReaderSessionInvalidationErrorSessionTimeout                 Session is timed out.
 * @constant    NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly  Session is terminated unexpectly.
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
    NFCReaderErrorUnsupportedFeature = 1,
    NFCReaderErrorSecurityViolation,
    NFCReaderErrorInvalidParameter API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCReaderErrorInvalidParameterLength API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCReaderErrorParameterOutOfBound API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),

    NFCReaderTransceiveErrorTagConnectionLost = 100,
    NFCReaderTransceiveErrorRetryExceeded,
    NFCReaderTransceiveErrorTagResponseError,
    NFCReaderTransceiveErrorSessionInvalidated API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCReaderTransceiveErrorTagNotConnected API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),

    NFCReaderSessionInvalidationErrorUserCanceled = 200,
    NFCReaderSessionInvalidationErrorSessionTimeout,
    NFCReaderSessionInvalidationErrorSessionTerminatedUnexpectedly,
    NFCReaderSessionInvalidationErrorSystemIsBusy,
    NFCReaderSessionInvalidationErrorFirstNDEFTagRead,

    NFCTagCommandConfigurationErrorInvalidParameters = 300,

    NFCNdefReaderSessionErrorTagNotWritable API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos) = 400 ,
    NFCNdefReaderSessionErrorTagUpdateFailure API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCNdefReaderSessionErrorTagSizeTooSmall API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
    NFCNdefReaderSessionErrorZeroLengthMessage API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos),
};

#pragma mark - ISO15693 specific command response error code

/*!
 *  Key in NSError userInfo dictionary.  The corresponding value is the NSUInteger error code from tag's response.
 *  Refer to ISO15693 specification for the error code values.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
extern NSString * const NFCISO15693TagResponseErrorKey;

/*!
 *  Key in NSError userInfo dictionary.  Presence of this key indicates the received response packet length is invalid.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos)
extern NSString * const NFCTagResponseUnexpectedLengthErrorKey;

NS_ASSUME_NONNULL_END

#endif /* CNFCError_h */
