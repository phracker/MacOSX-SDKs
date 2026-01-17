//
//  SNError.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SoundAnalysis/SNDefines.h>

SN_EXPORT NSString * const SNErrorDomain API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
typedef NS_ERROR_ENUM(SNErrorDomain, SNErrorCode)
{
    SNErrorCodeUnknownError = 1,
    SNErrorCodeOperationFailed,
    SNErrorCodeInvalidFormat,
    SNErrorCodeInvalidModel,
    SNErrorCodeInvalidFile
};
