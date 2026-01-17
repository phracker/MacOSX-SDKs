/*	
    NSURLError.h
    Copyright (c) 2003-2015, Apple Inc. All rights reserved.
    
    Public header file.
*/
#if TARGET_OS_IPHONE
#if __has_include(<CFNetwork/CFNetwork.h>)
#import <CFNetwork/CFNetwork.h>
#endif
#elif TARGET_OS_WIN32
#import <CFNetwork/CFNetwork.h>
#else
#import <CoreServices/CoreServices.h>
#endif

#import <Foundation/NSObjCRuntime.h>

@class NSString;

NS_ASSUME_NONNULL_BEGIN

/*
    @discussion Constants used by NSError to differentiate between "domains" of error codes, serving as a discriminator for error codes that originate from different subsystems or sources.
    @constant NSURLErrorDomain Indicates an NSURL error.
*/
FOUNDATION_EXPORT NSString * const NSURLErrorDomain;

/*!
    @const NSURLErrorFailingURLErrorKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the URL which caused a load to fail.
*/
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLErrorKey NS_AVAILABLE(10_6, 4_0);

/*!
    @const NSURLErrorFailingURLStringErrorKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the NSString object for the URL which caused a load to fail.
    @discussion This constant supersedes NSErrorFailingURLStringKey, which was deprecated in Mac OS X 10.6.  Both constants refer to the same value for backward-compatibility, but this symbol name has a better prefix.
*/
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLStringErrorKey NS_AVAILABLE(10_6, 4_0);

/*!
    @const NSErrorFailingURLStringKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the NSString object for the URL which caused a load to fail.
    @discussion This constant is deprecated in Mac OS X 10.6, and is superseded by NSURLErrorFailingURLStringErrorKey.  Both constants refer to the same value for backward-compatibility, but the new symbol name has a better prefix.
*/
FOUNDATION_EXPORT NSString * const NSErrorFailingURLStringKey NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);

/*!
    @const NSURLErrorFailingURLPeerTrustErrorKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the SecTrustRef object representing the state of a failed SSL handshake.
 */
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLPeerTrustErrorKey NS_AVAILABLE(10_6, 4_0);

/*!
    @const NSURLErrorBackgroundTaskCancelledReasonKey
    @abstract The NSError userInfo dictionary key used to store and retrieve the NSNumber corresponding to the reason why a background
	NSURLSessionTask was cancelled
 */
FOUNDATION_EXPORT NSString * const NSURLErrorBackgroundTaskCancelledReasonKey NS_AVAILABLE(10_10, 8_0);

/*!
    @enum Codes associated with NSURLErrorBackgroundTaskCancelledReasonKey
    @abstract Constants used by NSError to indicate why a background NSURLSessionTask was cancelled.
 */

NS_ENUM(NSInteger)
{
    NSURLErrorCancelledReasonUserForceQuitApplication =    0,
    NSURLErrorCancelledReasonBackgroundUpdatesDisabled =   1,
    NSURLErrorCancelledReasonInsufficientSystemResources NS_ENUM_AVAILABLE(10_10, 8_0) = 2,
    
} NS_ENUM_AVAILABLE(10_10, 7_0);

/*!
    @enum NSURL-related Error Codes
    @abstract Constants used by NSError to indicate errors in the NSURL domain
*/
NS_ENUM(NSInteger)
{
    NSURLErrorUnknown = 			-1,
    NSURLErrorCancelled = 			-999,
    NSURLErrorBadURL = 				-1000,
    NSURLErrorTimedOut = 			-1001,
    NSURLErrorUnsupportedURL = 			-1002,
    NSURLErrorCannotFindHost = 			-1003,
    NSURLErrorCannotConnectToHost = 		-1004,
    NSURLErrorNetworkConnectionLost = 		-1005,
    NSURLErrorDNSLookupFailed = 		-1006,
    NSURLErrorHTTPTooManyRedirects = 		-1007,
    NSURLErrorResourceUnavailable = 		-1008,
    NSURLErrorNotConnectedToInternet = 		-1009,
    NSURLErrorRedirectToNonExistentLocation = 	-1010,
    NSURLErrorBadServerResponse = 		-1011,
    NSURLErrorUserCancelledAuthentication = 	-1012,
    NSURLErrorUserAuthenticationRequired = 	-1013,
    NSURLErrorZeroByteResource = 		-1014,
    NSURLErrorCannotDecodeRawData =             -1015,
    NSURLErrorCannotDecodeContentData =         -1016,
    NSURLErrorCannotParseResponse =             -1017,
    NSURLErrorAppTransportSecurityRequiresSecureConnection NS_ENUM_AVAILABLE(10_11, 9_0) = -1022,
    NSURLErrorFileDoesNotExist = 		-1100,
    NSURLErrorFileIsDirectory = 		-1101,
    NSURLErrorNoPermissionsToReadFile = 	-1102,
    NSURLErrorDataLengthExceedsMaximum NS_ENUM_AVAILABLE(10_5, 2_0) =	-1103,
    
    // SSL errors
    NSURLErrorSecureConnectionFailed = 		-1200,
    NSURLErrorServerCertificateHasBadDate = 	-1201,
    NSURLErrorServerCertificateUntrusted = 	-1202,
    NSURLErrorServerCertificateHasUnknownRoot = -1203,
    NSURLErrorServerCertificateNotYetValid = 	-1204,
    NSURLErrorClientCertificateRejected = 	-1205,
    NSURLErrorClientCertificateRequired =	-1206,
    NSURLErrorCannotLoadFromNetwork = 		-2000,
    
    // Download and file I/O errors
    NSURLErrorCannotCreateFile = 		-3000,
    NSURLErrorCannotOpenFile = 			-3001,
    NSURLErrorCannotCloseFile = 		-3002,
    NSURLErrorCannotWriteToFile = 		-3003,
    NSURLErrorCannotRemoveFile = 		-3004,
    NSURLErrorCannotMoveFile = 			-3005,
    NSURLErrorDownloadDecodingFailedMidStream = -3006,
    NSURLErrorDownloadDecodingFailedToComplete =-3007,

    NSURLErrorInternationalRoamingOff NS_ENUM_AVAILABLE(10_7, 3_0) =         -1018,
    NSURLErrorCallIsActive NS_ENUM_AVAILABLE(10_7, 3_0) =                    -1019,
    NSURLErrorDataNotAllowed NS_ENUM_AVAILABLE(10_7, 3_0) =                  -1020,
    NSURLErrorRequestBodyStreamExhausted NS_ENUM_AVAILABLE(10_7, 3_0) =      -1021,
    
    NSURLErrorBackgroundSessionRequiresSharedContainer NS_ENUM_AVAILABLE(10_10, 8_0) = -995,
    NSURLErrorBackgroundSessionInUseByAnotherProcess NS_ENUM_AVAILABLE(10_10, 8_0) = -996,
    NSURLErrorBackgroundSessionWasDisconnected NS_ENUM_AVAILABLE(10_10, 8_0)= -997,
};

NS_ASSUME_NONNULL_END

