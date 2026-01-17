/*	
    NSURLError.h
    Copyright (c) 2003-2012, Apple Inc. All rights reserved.    
    
    Public header file.
*/

// Retrieve kCFURLError* values used in the NSURLError* assignments
#if TARGET_OS_EMBEDDED || TARGET_OS_IPHONE || TARGET_OS_WIN32
#import <CFNetwork/CFNetwork.h>
#else
#import <CoreServices/CoreServices.h>
#endif
#import <Foundation/NSObjCRuntime.h>

@class NSString;

/*
    @discussion Constants used by NSError to differentiate between "domains" of error codes, serving as a discriminator for error codes that originate from different subsystems or sources.
    @constant WebFoundationErrorDomain Indicates a WebFoundation error.
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
    @enum NSURL-related Error Codes
    @abstract Constants used by NSError to indicate errors in the WebFoundation domain
    @discussion Documentation on each constant forthcoming.
*/
enum
{
    NSURLErrorUnknown = 			-1,
    NSURLErrorCancelled = 			kCFURLErrorCancelled,
    NSURLErrorBadURL = 				kCFURLErrorBadURL,
    NSURLErrorTimedOut = 			kCFURLErrorTimedOut,
    NSURLErrorUnsupportedURL = 			kCFURLErrorUnsupportedURL,
    NSURLErrorCannotFindHost = 			kCFURLErrorCannotFindHost,
    NSURLErrorCannotConnectToHost = 		kCFURLErrorCannotConnectToHost,
    NSURLErrorNetworkConnectionLost = 		kCFURLErrorNetworkConnectionLost,
    NSURLErrorDNSLookupFailed = 		kCFURLErrorDNSLookupFailed,
    NSURLErrorHTTPTooManyRedirects = 		kCFURLErrorHTTPTooManyRedirects,
    NSURLErrorResourceUnavailable = 		kCFURLErrorResourceUnavailable,
    NSURLErrorNotConnectedToInternet = 		kCFURLErrorNotConnectedToInternet,
    NSURLErrorRedirectToNonExistentLocation = 	kCFURLErrorRedirectToNonExistentLocation,
    NSURLErrorBadServerResponse = 		kCFURLErrorBadServerResponse,
    NSURLErrorUserCancelledAuthentication = 	kCFURLErrorUserCancelledAuthentication,
    NSURLErrorUserAuthenticationRequired = 	kCFURLErrorUserAuthenticationRequired,
    NSURLErrorZeroByteResource = 		kCFURLErrorZeroByteResource,
    NSURLErrorCannotDecodeRawData =             kCFURLErrorCannotDecodeRawData,
    NSURLErrorCannotDecodeContentData =         kCFURLErrorCannotDecodeContentData,
    NSURLErrorCannotParseResponse =             kCFURLErrorCannotParseResponse,
    NSURLErrorFileDoesNotExist = 		kCFURLErrorFileDoesNotExist,
    NSURLErrorFileIsDirectory = 		kCFURLErrorFileIsDirectory,
    NSURLErrorNoPermissionsToReadFile = 	kCFURLErrorNoPermissionsToReadFile,
    NSURLErrorDataLengthExceedsMaximum NS_ENUM_AVAILABLE(10_5, 2_0) =	kCFURLErrorDataLengthExceedsMaximum,
    
    // SSL errors
    NSURLErrorSecureConnectionFailed = 		kCFURLErrorSecureConnectionFailed,
    NSURLErrorServerCertificateHasBadDate = 	kCFURLErrorServerCertificateHasBadDate,
    NSURLErrorServerCertificateUntrusted = 	kCFURLErrorServerCertificateUntrusted,
    NSURLErrorServerCertificateHasUnknownRoot = kCFURLErrorServerCertificateHasUnknownRoot,
    NSURLErrorServerCertificateNotYetValid = 	kCFURLErrorServerCertificateNotYetValid,
    NSURLErrorClientCertificateRejected = 	kCFURLErrorClientCertificateRejected,
    NSURLErrorClientCertificateRequired =	kCFURLErrorClientCertificateRequired,
    NSURLErrorCannotLoadFromNetwork = 		kCFURLErrorCannotLoadFromNetwork,
    
    // Download and file I/O errors
    NSURLErrorCannotCreateFile = 		kCFURLErrorCannotCreateFile,
    NSURLErrorCannotOpenFile = 			kCFURLErrorCannotOpenFile,
    NSURLErrorCannotCloseFile = 		kCFURLErrorCannotCloseFile,
    NSURLErrorCannotWriteToFile = 		kCFURLErrorCannotWriteToFile,
    NSURLErrorCannotRemoveFile = 		kCFURLErrorCannotRemoveFile,
    NSURLErrorCannotMoveFile = 			kCFURLErrorCannotMoveFile,
    NSURLErrorDownloadDecodingFailedMidStream = kCFURLErrorDownloadDecodingFailedMidStream,
    NSURLErrorDownloadDecodingFailedToComplete =kCFURLErrorDownloadDecodingFailedToComplete,

    NSURLErrorInternationalRoamingOff NS_ENUM_AVAILABLE(10_7, 3_0) =         kCFURLErrorInternationalRoamingOff,
    NSURLErrorCallIsActive NS_ENUM_AVAILABLE(10_7, 3_0) =                    kCFURLErrorCallIsActive,
    NSURLErrorDataNotAllowed NS_ENUM_AVAILABLE(10_7, 3_0) =                  kCFURLErrorDataNotAllowed,
    NSURLErrorRequestBodyStreamExhausted NS_ENUM_AVAILABLE(10_7, 3_0) =      kCFURLErrorRequestBodyStreamExhausted,
};

