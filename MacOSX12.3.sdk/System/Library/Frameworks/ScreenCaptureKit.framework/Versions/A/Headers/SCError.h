//
//  SCError.h
//  ScreenCaptureKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
extern NSString *const __nonnull SCStreamErrorDomain;

NS_ASSUME_NONNULL_BEGIN
typedef NS_ERROR_ENUM (SCStreamErrorDomain, SCStreamErrorCode) {
    SCStreamErrorUserDeclined = -3801,                           // The user chose not to authorize capture
    SCStreamErrorFailedToStart = -3802,                          // The stream failed to start
    SCStreamErrorMissingEntitlements = -3803,                    // The stream failed due to missing entitlements
    SCStreamErrorFailedApplicationConnectionInvalid = -3804,     // Failed during recording application connection invalid
    SCStreamErrorFailedApplicationConnectionInterrupted = -3805, // Failed during recording appliation connection interrupted
    SCStreamErrorFailedNoMatchingApplicationContext = -3806,     // Failed during recording context id does not match application
    SCStreamErrorAttemptToStartStreamState = -3807,              // Failed due to attempting to start a stream thats already in a recording state
    SCStreamErrorAttemptToStopStreamState = -3808,               // Failed due to attempting to stop a stream thats already in a recording state
    SCStreamErrorAttemptToUpdateFilterState = -3809,             // Failed due to attempting to update the filter on a stream
    SCStreamErrorAttemptToConfigState = -3810,                   // Failed due to attempting to update stream config on a stream
    SCStreamErrorInternalError = -3811,                          // Failed to start due to video/audio capture failure
    SCStreamErrorInvalidParameter = -3812,                       // Failed due to invalid parameter
    SCStreamErrorNoWindowList = -3813,                           // Failed due to no window list
    SCStreamErrorNoDisplayList = -3814,                          // Failed due to no display list
    SCStreamErrorNoCaptureSource = -3815,                        // Failed due to no display or window list to capture
    SCStreamErrorRemovingStream = -3816                          // Failed to remove stream
};

NS_ASSUME_NONNULL_END
