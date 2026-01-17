#ifndef __TRANSFORM_DIGEST__
#define __TRANSFORM_DIGEST__


/*
 * Copyright (c) 2010-2011 Apple Inc. All Rights Reserved.
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

#include <Security/SecTransform.h>

#ifdef __cplusplus
extern "C" {
#endif

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@abstract
		Specifies an MD2 digest
*/
extern const CFStringRef kSecDigestMD2
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@abstract
		Specifies an MD4 digest
 */
extern const CFStringRef kSecDigestMD4
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@abstract
		Specifies an MD5 digest
 */
extern const CFStringRef kSecDigestMD5
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@abstract
		Specifies a SHA1 digest
 */
extern const CFStringRef kSecDigestSHA1
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@abstract
		Specifies a SHA2 digest.
 */
extern const CFStringRef kSecDigestSHA2
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@abstract
		Specifies an HMAC using the MD5 digest algorithm.
 */
extern const CFStringRef kSecDigestHMACMD5
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@abstract
		Specifies an HMAC using the SHA1 digest algorithm.
 */
extern const CFStringRef kSecDigestHMACSHA1
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@abstract
		Specifies an HMAC using one of the SHA2 digest algorithms.
 */
extern const CFStringRef kSecDigestHMACSHA2
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);


/*!
	@constant kSecDigestTypeAttribute
		Used with SecTransformGetAttribute to query the attribute type.
		Returns one of the strings defined in the previous section.
 */
extern const CFStringRef kSecDigestTypeAttribute
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@constant kSecDigestLengthAttribute
		Used with SecTransformGetAttribute to query the length attribute.
		Returns a CFNumberRef that contains the length in bytes.
 */
extern const CFStringRef kSecDigestLengthAttribute
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@constant kSecDigestHMACKeyAttribute
		When set and used with one of the HMAC digest types, sets the key
		for the HMAC operation.  The data type for this attribute must be
		a CFDataRef.  If this value is not set, the transform will assume
		a zero length key.
*/
extern const CFStringRef kSecDigestHMACKeyAttribute
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@function SecDigestTransformCreate
	@abstract			Creates a digest computation object.
	@param digestType	The type of digest to compute.  You may pass NULL
						for this parameter, in which case an appropriate
						algorithm will be chosen for you.
	@param digestLength	The desired digest length.  Note that certain
						algorithms may only support certain sizes. You may
						pass 0 for this parameter, in which case an
						appropriate length will be chosen for you.
	@param error		A pointer to a CFErrorRef.  This pointer will be set
						if an error occurred.  This value may be NULL if you
						do not want an error returned.
	@result				A pointer to a SecTransformRef object.  This object must
						be released with CFRelease when you are done with
						it.  This function will return NULL if an error
						occurred.
	@discussion			This function creates a transform which computes a
						cryptographic digest.
*/

SecTransformRef SecDigestTransformCreate(CFTypeRef __nullable digestType,
										 CFIndex digestLength,
										 CFErrorRef* error
										 )
API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);


/*!
	@function SecDigestTransformGetTypeID
	@abstract			Return the CFTypeID of a SecDigestTransform
	@result			The CFTypeID
*/

    CFTypeID SecDigestTransformGetTypeID(void)
    API_DEPRECATED("SecTransform is no longer supported", macos(10.7, 13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

#ifdef __cplusplus
};
#endif


#endif
