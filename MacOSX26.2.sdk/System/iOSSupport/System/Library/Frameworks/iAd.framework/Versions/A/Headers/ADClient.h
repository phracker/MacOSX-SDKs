//
//  ADClient.h
//
//  Copyright 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define ADCLIENT_DEPRECATED_MACOS_1014_113_OBSOLETED_180 __attribute__((availability(macos, introduced=10.14, deprecated=11.3, obsoleted=18.0, \
    message="This has been replaced by functionality in AdServices.framework's AAAttribution class.")))

#define ADCLIENT_DEPRECATED_MACOS_1014_120_OBSOLETED_180 __attribute__((availability(macos, introduced=10.14, deprecated=12.0, obsoleted=18.0, \
    message="This has been replaced by functionality in AdServices.framework's AAAttribution class.")))

#define ADCLIENT_DEPRECATED_IOS_71_145_OBSOLETED_180 __attribute__((availability(ios, introduced=7.1, deprecated=14.5, obsoleted=18.0, \
    message="This has been replaced by functionality in AdServices.framework's AAAttribution class.")))

#define ADCLIENT_DEPRECATED_IOS_71_150_OBSOLETED_180 __attribute__((availability(ios, introduced=7.1, deprecated=15.0, obsoleted=18.0, \
    message="This has been replaced by functionality in AdServices.framework's AAAttribution class.")))

#define ADCLIENT_DEPRECATED_IOS_90_145_OBSOLETED_180 __attribute__((availability(ios, introduced=9.0, deprecated=14.5, obsoleted=18.0, \
    message="This has been replaced by functionality in AdServices.framework's AAAttribution class.")))

#define ADCLIENT_DEPRECATED_TVOS_71_145_OBSOLETED_180 __attribute__((availability(tvos, introduced=7.1, deprecated=14.5, obsoleted=18.0, \
    message="This has been replaced by functionality in AdServices.framework's AAAttribution class.")))

#define ADCLIENT_DEPRECATED_TVOS_71_150_OBSOLETED_180 __attribute__((availability(tvos, introduced=7.1, deprecated=15.0, obsoleted=18.0, \
    message="This has been replaced by functionality in AdServices.framework's AAAttribution class.")))

#define ADCLIENT_DEPRECATED_TVOS_90_145_OBSOLETED_180 __attribute__((availability(tvos, introduced=9.0, deprecated=14.5, obsoleted=18.0, \
    message="This has been replaced by functionality in AdServices.framework's AAAttribution class.")))

extern NSString * const ADClientErrorDomain ADCLIENT_DEPRECATED_MACOS_1014_120_OBSOLETED_180 ADCLIENT_DEPRECATED_IOS_71_150_OBSOLETED_180 ADCLIENT_DEPRECATED_TVOS_71_150_OBSOLETED_180;

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
} ADCLIENT_DEPRECATED_MACOS_1014_120_OBSOLETED_180 ADCLIENT_DEPRECATED_IOS_71_150_OBSOLETED_180 ADCLIENT_DEPRECATED_TVOS_71_150_OBSOLETED_180;

ADCLIENT_DEPRECATED_MACOS_1014_113_OBSOLETED_180 ADCLIENT_DEPRECATED_IOS_71_145_OBSOLETED_180 ADCLIENT_DEPRECATED_TVOS_71_145_OBSOLETED_180
@interface ADClient : NSObject

+ (ADClient *)sharedClient ADCLIENT_DEPRECATED_MACOS_1014_113_OBSOLETED_180 ADCLIENT_DEPRECATED_IOS_71_145_OBSOLETED_180 ADCLIENT_DEPRECATED_TVOS_71_145_OBSOLETED_180;

- (void)requestAttributionDetailsWithBlock:(void (^)(NSDictionary<NSString *, NSObject *> * _Nullable attributionDetails, NSError * _Nullable error))completionHandler ADCLIENT_DEPRECATED_MACOS_1014_113_OBSOLETED_180 ADCLIENT_DEPRECATED_IOS_90_145_OBSOLETED_180 ADCLIENT_DEPRECATED_TVOS_71_145_OBSOLETED_180;

@end

NS_ASSUME_NONNULL_END
