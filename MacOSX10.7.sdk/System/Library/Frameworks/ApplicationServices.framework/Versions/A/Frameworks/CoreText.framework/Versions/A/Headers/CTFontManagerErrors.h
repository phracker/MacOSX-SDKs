/*
 *  CTFontManagerErrors.h
 *  CoreText
 *
 *  Copyright (c) 2008-2011 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTFONTMANAGERERRORS__
#define __CTFONTMANAGERERRORS__

#include <CoreText/CTDefines.h>
#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @const      kCTFontManagerErrorDomain
    @abstract   CFError domain for CTFontManager errors
    @discussion CFErrors with this domain will have error codes corresponding to one of the CTFontManagerErrors above.
*/
extern const CFStringRef kCTFontManagerErrorDomain CT_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_3_2);

/*!
    @constant   kCTFontManagerErrorFontURLsKey
    @abstract   User info key to be used with CFError references returned from registration functions.
    @discussion The value associated with this key in the user info dictionary of a CFError is a CFArray of font URLs that failed with given error.
*/
extern const CFStringRef kCTFontManagerErrorFontURLsKey CT_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_3_2);

/*!
    @enum
    @abstract   Font registration errors
    @discussion Errors that would prevent registration of fonts for a specified font file URL.
    @constant   kCTFontManagerErrorFileNotFound
                The file does not exist at the specified URL.
    @constant   kCTFontManagerErrorInsufficientPermissions
                Cannot access the file due to insufficient permissions.
    @constant   kCTFontManagerErrorUnrecognizedFileFormat
                The file is not a recognized or supported font file format.
    @constant   kCTFontManagerErrorInvalidFontData
                The file contains invalid font data that could cause system problems.
    @constant   kCTFontManagerErrorAlreadyRegistered
                The file has already been registered in the specified scope.
*/
enum {
    kCTFontManagerErrorFileNotFound             = 101,
    kCTFontManagerErrorInsufficientPermissions  = 102,
    kCTFontManagerErrorUnrecognizedFormat       = 103,
    kCTFontManagerErrorInvalidFontData          = 104,
    kCTFontManagerErrorAlreadyRegistered        = 105,
};

/*!
    @enum
    @abstract   Font un-registration errors
    @discussion Errors that would prevent un-registration of fonts for a specified font file URL.
    @constant   kCTFontManagerErrorNotRegistered
                The file is not registered in the specified scope.
    @constant   kCTFontManagerErrorInUse
                The font file is actively in use and cannot be unregistered.
    @constant   kCTFontManagerErrorSystemRequired
                The file is required by the system and cannot be unregistered.
*/
enum {
    kCTFontManagerErrorNotRegistered            = 201,
    kCTFontManagerErrorInUse                    = 202,
    kCTFontManagerErrorSystemRequired           = 202,
};

typedef CFIndex CTFontManagerError;

#if defined(__cplusplus)
}
#endif

#endif
