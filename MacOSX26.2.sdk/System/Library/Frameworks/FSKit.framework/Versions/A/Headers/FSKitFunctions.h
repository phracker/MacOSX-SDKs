//
//  Copyright (c) 2023 Apple Inc.  All rights reserved.
//
//  FSKitFunctions.h
//  FSKit
//

#ifndef FSKitFunctions_h
#define FSKitFunctions_h

// C code in this header is meant to be bridged to our Swift module
#import <Foundation/Foundation.h>
#import <os/log.h>

#import <FSKit/FSKitDefines.h>

/// Creates an error object for the given POSIX error code.
FOUNDATION_EXPORT NSError * _Nonnull fs_errorForPOSIXError(int) FSKIT_API_AVAILABILITY_V1;
/// Creates an error object for the given Mach error code.
FOUNDATION_EXPORT NSError * _Nonnull fs_errorForMachError(int errorCode) FSKIT_API_AVAILABILITY_V1;
/// Creates an error object for the given Cocoa error code.
FOUNDATION_EXPORT NSError * _Nonnull fs_errorForCocoaError(int errorCode) FSKIT_API_AVAILABILITY_V1;

#endif /* FSKitFunctions_h */
