//
//  ADClient.h
//
//  Copyright 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @const ADClientErrorDomain
 *
 * @discussion
 * Error domain for NSErrors passed to the completionHandler as a
 * result of calling:
 *
 *   • -[[ADClient SharedClient] requestAttributionDetailsWithBlock]
 *
 */
extern NSString * const ADClientErrorDomain NS_DEPRECATED(10_14, 12_0, 7_1, 15_0);

/*!
 * @enum ADClientError
 *
 * @const ADClientErrorUnknown
 * This is not used and should never be returned.
 *
 * @const ADClientErrorTrackingRestrictedOrDenied
 * The user is restricted or has denied tracking for the calling application.
 *
 * @const ADClientErrorLimitAdTracking
 * This is deprecated, please use ADClientErrorTrackingRestrictedOrDenied.
 *
 * @const ADClientErrorMissingData
 * The downloaded app received a payload lacking enough data to perform an attribution check.
 *
 * @const ADClientErrorCorruptResponse
 * The response received from the Attribution Server was corrupt.
 *
 * @const ADClientErrorRequestClientError
 * The response received from the Attribution Server had an HTTP 4xx status code.
 *
 * @const ADClientErrorRequestServerError
 * The response received from the Attribution Server had an HTTP 5xx status code.
 *
 * @const ADClientErrorRequestNetworkError
 * The communication with the  Attribution Server had a network error. The underlying error will be provided in the user info dictionary if available.
 *
 * @const ADClientErrorUnsupportedPlatform
 * The attribution API was called on an unsupported platform. Only iOS and iPadOS are supported.
 *
 * @discussion
 * Error codes for NSErrors passed to the completionHandler block when calling the requestAttributionDetailsWithBlock: method.
 */
typedef NS_ENUM(NSInteger, ADClientError) {
    ADClientErrorUnknown __deprecated_enum_msg("ADClientErrorUnknown is not used and never returned.") = 0,
    ADClientErrorTrackingRestrictedOrDenied = 1,
    ADClientErrorLimitAdTracking __deprecated_enum_msg("ADClientErrorLimitAdTracking has been deprecated use ADClientErrorTrackingRestrictedOrDenied.") = ADClientErrorTrackingRestrictedOrDenied,
    ADClientErrorMissingData = 2,
    ADClientErrorCorruptResponse = 3,
    ADClientErrorRequestClientError = 4,
    ADClientErrorRequestServerError = 5,
    ADClientErrorRequestNetworkError = 6,
    ADClientErrorUnsupportedPlatform = 7
} NS_ENUM_DEPRECATED(10_14, 12_0, 7_1, 15_0);

NS_DEPRECATED(10_14, 11_3, 7_1, 14_5, "This has been replaced by functionality in AdServices.framework's AAAttribution class.")
@interface ADClient : NSObject

/*!
 * @method sharedClient
 *
 * @return
 * An instance of ADClient.
 *
 * @discussion
 * This is no longer a singleton and returns a new instance for every call.
 */
+ (ADClient *)sharedClient NS_DEPRECATED(10_14, 11_3, 7_1, 14_5, "This has been replaced by functionality in AdServices.framework's AAAttribution class.");

/*!
 * @method requestAttributionDetailsWithBlock:
 *
 * @param completionHandler
 * A block which will be called with details related to the attribution status of the app.
 * The attributionDetails dictionary will contain purchase and impression dates
 * as well as other specific campaign related information. If the attributionDetails
 * dictionary is nil, an NSError is passed with an ADClientError enum.
 *
 * The handler will be called on an arbitrary queue.
 *
 * @discussion
 * Provides a way for an app to determine when an an was shown to the user
 * which resulted in the user's purchase of the app.
 */
- (void)requestAttributionDetailsWithBlock:(void (^)(NSDictionary<NSString *, NSObject *> * _Nullable attributionDetails, NSError * _Nullable error))completionHandler NS_DEPRECATED(10_14, 11_3, 9_0, 14_5, "This has been replaced by functionality in AdServices.framework's AAAttribution class.");

/*!
 * @method addClientToSegments:replaceExisting:
 *
 * @param segmentIdentifiers
 * This parameter is unused.
 *
 * @param replaceExisting
 * This parameter is unused.
 *
 * @discussion
 * This method does nothing and immediately returns.
 */
- (void)addClientToSegments:(NSArray<NSString *> *)segmentIdentifiers replaceExisting:(BOOL)replaceExisting NS_DEPRECATED(10_14, 10_14, 8_0, 13_0);

@end

NS_ASSUME_NONNULL_END
