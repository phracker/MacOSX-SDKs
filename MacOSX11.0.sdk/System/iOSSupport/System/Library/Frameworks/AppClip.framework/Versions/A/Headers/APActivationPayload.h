// Copyright © 2020 Apple Inc. All rights reserved.

#import <AppClip/APBase.h>
#import <Foundation/Foundation.h>

@class CLRegion;

NS_ASSUME_NONNULL_BEGIN

AP_EXTERN API_AVAILABLE(ios(14.0))
NSErrorDomain const APActivationPayloadErrorDomain;

/*! @enum APActivationPayloadErrorCode
 @abstract Error code of the NSError object passed in completionHandler for location confirmation.
 @constant APActivationPayloadErrorCodeDisallowed The location confirmation request is disalllowed by user or system; or the code is not acquired by QR/NFC scanning.
 @constant APActivationPayloadErrorCodeDoesNotMatch The payload passed in by the application doesn't match the payload it was launched with.
 */
typedef NS_ERROR_ENUM(APActivationPayloadErrorDomain, APActivationPayloadErrorCode) {
    APActivationPayloadErrorCodeDisallowed = 1,
    APActivationPayloadErrorCodeDoesNotMatch = 2,
} API_AVAILABLE(ios(14.0));

/*!
@class APActivationPayload
 An APActivationPayload object is an object passed to application within NSUserActity when it is launched by a physical code scan. Upon receiving
 the payload, application can inspect its content. Application can also check whether the payload was acquired at an expected location.
*/
AP_EXTERN API_AVAILABLE(ios(14.0))
@interface APActivationPayload : NSObject <NSSecureCoding, NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, strong, readonly, nullable) NSURL *URL;

/*! @abstract checks if the payload was acquired at an expected region.
 @param region the region this paylaod is expected to be acquired.
 @param completionHandler the completion handler which is called when the system confirms weather the payload was acquired in expected region.
 @discussion For the system to accept this request, application needs to specify sub-key NSAppClipRequestLocationConfirmation to true in NSAppClip section in Info.plist.
*/
- (void)confirmAcquiredInRegion:(CLRegion *)region completionHandler:(void (^)(BOOL inRegion, NSError *_Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
