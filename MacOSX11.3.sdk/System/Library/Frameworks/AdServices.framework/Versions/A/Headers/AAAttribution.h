//
//  AAAttribution.h
//  AdServices
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum AAAttributionErrorCode
 *
 * @const AAAttributionErrorCodeNetworkNotAvailable
 * A token could not be provided because a network error occured.
 *
 * @const AAAttributionErrorCodeInternalError
 * A token could not be provided because an internal error occurred.
 *
 * @discussion
 * Error codes for NSErrors returned from the attributionTokenWithError: method.
 */
extern NSErrorDomain const AAAttributionErrorDomain API_AVAILABLE(ios(14.3), macosx(11.1), tvos(14.3));
                                                                  
typedef NS_ERROR_ENUM(AAAttributionErrorDomain, AAAttributionErrorCode)
{
    AAAttributionErrorCodeNetworkError = 1,
    AAAttributionErrorCodeInternalError = 2,
    AAAttributionErrorCodePlatformNotSupported = 3
} API_AVAILABLE(ios(14.3), macosx(11.1), tvos(14.3));

/*!
 * @class AAAttribution
 *
 * @discussion
 * This class contains a method that generates a token used to obtain the app's attribution from Apple’s Attribution Server.
 */
API_AVAILABLE(ios(14.3), macosx(11.1), tvos(14.3))
@interface AAAttribution : NSObject

/*!
 * @method attributionTokenWithError:
 *
 * @param error
 * If the error parameter is not nil it will contain any errors encountered during the call. The code property on the error object will be a member of the enum AAAttributionErrorCode.
 *
 * @return NSString
 * The value returned will be a token string. If there are any errors the return value will be nil and error parameter populated.
 *
 * @discussion
 * This method is used to generate an attribution token. The token is used in conjunction with Ad Platforms Attribution REST API to obtain the app's attribution information from Apple’s Attribution Server.
 * This method requires that the network is available otherwise it will return an error.
 * The token string can be used directly with the REST API.
 * If an error occurs, the return value of the method will be nil and the error parameter, if provided, will contain a reference to an NSError object describing the error that occurred.
 */
+ (nullable NSString *)attributionTokenWithError:(NSError * __autoreleasing _Nullable * _Nullable)error;

@end
              
NS_ASSUME_NONNULL_END
