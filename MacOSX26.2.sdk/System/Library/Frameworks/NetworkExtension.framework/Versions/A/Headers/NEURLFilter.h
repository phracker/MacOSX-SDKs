/*
 * NEURLFilter.h
 *
 * Copyright (c) 2025 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/// This file declares the NEURLFilter API.  For Applications that are not using any of the Apple Networking frameworks
/// (WebKit, CFNetwork and Network frameworks), use the NEURLFilter API to voluntarily validate URLs before potentially
/// connecting to any restricted or malicious Internet site.  This API checks the specified URL and returns a Allow or Deny
/// verdict.  Applications should not connect to any URLs with the Deny result.
/// This API is part of NetworkExtension.framework.

#if defined(__cplusplus)
#define NEURLFILTER_EXPORT extern "C"
#else
#define NEURLFILTER_EXPORT extern
#endif

/// URL Filter Verdicts
typedef NS_ENUM(NSInteger, NEURLFilterVerdict) {
	/*! @const NEURLFilterVerdictUnknown The validation failed */
	NEURLFilterVerdictUnknown = 1,
	/*! @const NEURLFilterVerdictAllow URL should be allowed */
	NEURLFilterVerdictAllow = 2,
	/*! @const NEURLFilterVerdictDeny URL should be denied. */
	NEURLFilterVerdictDeny = 3,
} NS_SWIFT_NAME(NEURLFilter.Verdict) API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos);

API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos);
@interface NEURLFilter : NSObject
/// This method determines if the specified URL should be allowed or denied.  The returned Allow or Deny verdict should be honored to prevent
/// communication with restricted or malicious Internet sites.
/// - Parameters:
///   - url: url to be validated
///   - completionHandler: A block that will be called when validation is completed. A NEURLFilterVerdict verdict will be returned to indicate
///   whether the specified URL should be allowed or denied.  If verdict is Deny, caller should fail the URL request.
+ (void)verdictForURL:(NSURL *)url
	completionHandler:(void (^)(NEURLFilterVerdict result))completionHandler API_AVAILABLE(macos(26.0), ios(26.0)) API_UNAVAILABLE(watchos, tvos, visionos);

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
