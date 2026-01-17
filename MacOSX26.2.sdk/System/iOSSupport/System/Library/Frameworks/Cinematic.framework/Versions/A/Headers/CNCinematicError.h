//
//  CNCinematicError.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cinematic/Cinematic.h>

NS_ASSUME_NONNULL_BEGIN

CN_CINEMATIC_EXTERN NSErrorDomain const CNCinematicErrorDomain API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

typedef NS_ERROR_ENUM(CNCinematicErrorDomain, CNCinematicErrorCode)
{
    // failed for unknown reasons (check for underlying error)
    CNCinematicErrorCodeUnknown         = 1,

    // not readable
    CNCinematicErrorCodeUnreadable      = 2,

    // missing needed information (e.g. not cinematic)
    CNCinematicErrorCodeIncomplete      = 3,

    // data or content is corrupted
    CNCinematicErrorCodeMalformed       = 4,

    // version or feature not supported
    CNCinematicErrorCodeUnsupported     = 5,

    // not compatible in current context
    CNCinematicErrorCodeIncompatible    = 6,

    // operation was cancelled
    CNCinematicErrorCodeCancelled       = 7,
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_END
