#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/data.h>)
//
//  data.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef data_h
#define data_h

#import <ARKit/object.h>

#import <os/availability.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL(ar_data)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

#pragma mark - Data

/**
 Get a pointer to the data's bytes.

 @return A pointer to the data's bytes.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN const void *ar_data_get_bytes(ar_data_t data) AR_REFINED_FOR_SWIFT;

/**
 Get the length of the data, in bytes.

 @return The length of the data, in bytes.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_data_get_length(ar_data_t data) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // data_h
#else
#import <ARKitCore/data.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/data.h>)