//
//  AAAttribution.h
//  AdServices
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The framework attribution error domain.
extern NSErrorDomain const AAAttributionErrorDomain API_AVAILABLE(ios(14.3), macosx(11.1), tvos(14.3));
        
/// The error codes that may be returned by AAAttribution.
typedef NS_ERROR_ENUM(AAAttributionErrorDomain, AAAttributionErrorCode)
{
    /// attributionTokenWithError: is unable to provide a token because the internet isn’t available.
    ///
    /// To receive an attribution token, you must have unimpeded internet access. Make sure
    /// you’re not using a simulator when generating a token.
    AAAttributionErrorCodeNetworkError = 1,
    /// attributionTokenWithError: is unable to provide a token because of an internal error.
    AAAttributionErrorCodeInternalError = 2,
    /// attributionTokenWithError: is unable to provide a token because of an unsupported operating system.
    AAAttributionErrorCodePlatformNotSupported = 3
} API_AVAILABLE(ios(14.3), macosx(11.1), tvos(14.3));

/// The parent class that the framework uses to request a token.
API_AVAILABLE(ios(14.3), macosx(11.1), tvos(14.3))
@interface AAAttribution : NSObject

/// Generates a token.
+ (nullable NSString *)attributionTokenWithError:(NSError * __autoreleasing _Nullable * _Nullable)error;

@end
              
NS_ASSUME_NONNULL_END
