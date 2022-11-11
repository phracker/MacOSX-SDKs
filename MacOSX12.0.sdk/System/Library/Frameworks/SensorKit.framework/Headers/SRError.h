#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

SR_EXTERN NSErrorDomain SRErrorDomain API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);

typedef NS_ERROR_ENUM(SRErrorDomain, SRErrorCode) {
    /// No valid entitlement found
    SRErrorInvalidEntitlement,

    /// Insufficient authorization to perform the action.
    SRErrorNoAuthorization,

    /// Data is not accessible at this time
    SRErrorDataInaccessible,

    /// Fetch request contained invalid values
    SRErrorFetchRequestInvalid,

    /// Authorization request not completed
    SRErrorPromptDeclined,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END
