//
//  VNError.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

extern NSString* const VNErrorDomain API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


typedef NS_ENUM(NSInteger, VNErrorCode)
{
    VNErrorOK = 0,
    VNErrorRequestCancelled,
    VNErrorInvalidFormat,
    VNErrorOperationFailed,
    VNErrorOutOfBoundsError,
    VNErrorInvalidOption,
    VNErrorIOError,
    VNErrorMissingOption,
    VNErrorNotImplemented,
    VNErrorInternalError,
    VNErrorOutOfMemory,
    VNErrorUnknownError,
    VNErrorInvalidOperation,
    VNErrorInvalidImage,
    VNErrorInvalidArgument,
    VNErrorInvalidModel
};

