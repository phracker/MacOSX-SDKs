/*
 * Copyright (c) 2024 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
#ifndef timingsafe_h
#define timingsafe_h
#include <Availability.h>
#include <os/base.h>
#include <stdint.h>

/**
 Token used to track state from enable() to disable().
 */
typedef uint64_t timingsafe_token_t;

__BEGIN_DECLS

/**
 @function timingsafe_enable_if_supported
 @abstract Unconditionally enable all supported timingsafe features.
 If timingsafe features aren't supported, they are ignored. If no features are
 supported, this is a no-op.

 @return The opaque token to use in timingsafe_restore_if_supported().
 */
__API_AVAILABLE(macos(15.2), ios(18.2), tvos(18.2), watchos(11.2), visionos(2.2))
OS_EXPORT OS_WARN_RESULT
OS_SWIFT_UNAVAILABLE_FROM_ASYNC("Not supported for async.")
timingsafe_token_t timingsafe_enable_if_supported(void);

/**
 @function timingsafe_restore_if_supported
 @abstract Restore timingsafe features to the state they were in before calling
 timingsafe_enable_if_supported and given the provided token.

 @param token
 The token returned by timingsafe_enable_if_supported.
 */
__API_AVAILABLE(macos(15.2), ios(18.2), tvos(18.2), watchos(11.2), visionos(2.2))
OS_EXPORT
OS_SWIFT_UNAVAILABLE_FROM_ASYNC("Not supported for async.")
void timingsafe_restore_if_supported(timingsafe_token_t token);

__END_DECLS

#endif /* timingsafe_h */
