#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/error.h>)
//
//  error.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef error_h
#define error_h

#import <ARKit/object.h>

#import <CoreFoundation/CFBase.h>
#import <CoreFoundation/CFError.h>
#import <os/availability.h>

AR_ASSUME_NONNULL_BEGIN

#pragma mark - Error

AR_OBJECT_DECL(ar_error)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0));

API_AVAILABLE(visionos(1.0), macos(26.0)) AR_EXTERN const CFStringRef ar_error_domain AR_REFINED_FOR_SWIFT;
API_AVAILABLE(visionos(1.0), macos(26.0)) typedef intptr_t ar_error_code_t AR_REFINED_FOR_SWIFT;

/**
 Get the error code associated with an error.

 @param error The `ar_error_t` instance.

 @return The error code.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN ar_error_code_t ar_error_get_error_code(ar_error_t error) AR_REFINED_FOR_SWIFT;

/**
 Copy out a `CFErrorRef` that represents an `ar_error_t`.

 @param error The `ar_error_t` instance.

 @return The `CFErrorRef`. The caller is responsible for calling `CFRelease` on the returned pointer.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN CF_RETURNS_RETAINED CFErrorRef ar_error_copy_cf_error(ar_error_t error) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // error_h
#else
#import <ARKitCore/error.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/error.h>)