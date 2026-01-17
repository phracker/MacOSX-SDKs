//
//  VNError.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


extern NSString* const VNErrorDomain API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


typedef NS_ENUM(NSInteger, VNErrorCode)
{
    VNErrorTuriCoreErrorCode = -1,
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
    VNErrorInvalidModel,
    VNErrorUnsupportedRevision API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0)),
    VNErrorDataUnavailable  API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)),
    VNErrorTimeStampNotFound  API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)),
    VNErrorUnsupportedRequest  API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)),
    VNErrorTimeout  API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)),
    VNErrorUnsupportedComputeStage API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)),
    VNErrorUnsupportedComputeDevice API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)),
};
