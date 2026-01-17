//
//  SNRequest.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SoundAnalysis/SNDefines.h>

/*!
 @brief The base protocol to which analysis requests conform
 @discussion An analysis request is a configuration that defines the analysis the client wishes to perform on the audio stream. Each request has a corresponding result type, which contains information describing the analysis results. This protocol is designed for all requests provided by the framework to conform to, and shouldn't be conformed to by client objects.
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@protocol SNRequest <NSObject>
@end
