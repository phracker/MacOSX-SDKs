//
//  ILMessageFilterError.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

IL_EXTERN NSErrorDomain const ILMessageFilterErrorDomain API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

typedef NS_ERROR_ENUM(ILMessageFilterErrorDomain, ILMessageFilterError) {
    /// An unspecified system error occurred.
    ILMessageFilterErrorSystem = 1,

    /// The network request URL included in the extension's Info.plist was either missing or invalid. See documentation for network request URL requirements.
    ILMessageFilterErrorInvalidNetworkURL = 2,

    /// Extension's containing app is not authorized to allow extension to defer network requests to the host specified in the URL of the extension's Info.plist.
    ILMessageFilterErrorNetworkURLUnauthorized = 3,

    /// Network request was attempted but failed. See `NSUnderlyingErrorKey` in `userInfo` dictionary for details.
    ILMessageFilterErrorNetworkRequestFailed = 4,

    /// Extension requested to defer a request to its network service more than once. Requests may be deferred to the network at most once.
    ILMessageFilterErrorRedundantNetworkDeferral = 5,
} API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_END
