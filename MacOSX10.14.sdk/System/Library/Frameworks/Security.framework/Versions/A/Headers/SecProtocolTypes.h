/*
 * Copyright (c) 2018 Apple Inc. All Rights Reserved.
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

#ifndef SecProtocolTypes_h
#define SecProtocolTypes_h

#include <Security/SecProtocolObject.h>
#include <Security/SecTrust.h>
#include <Security/SecCertificate.h>
#include <Security/SecIdentity.h>

#ifndef SEC_OBJECT_IMPL
/*!
 * These are os_object compatible and ARC-able wrappers around existing CoreFoundation
 * Security types, including: SecTrustRef, SecIdentityRef, and SecCertificateRef. They allow
 * clients to use these types in os_object-type APIs and data structures. The underlying
 * CoreFoundation types may be extracted and used by clients as needed.
 */
SEC_OBJECT_DECL(sec_trust);
SEC_OBJECT_DECL(sec_identity);
SEC_OBJECT_DECL(sec_certificate);
#endif // !SEC_OBJECT_IMPL

SEC_ASSUME_NONNULL_BEGIN

/*!
 * @function sec_trust_create
 *
 * @abstract
 *      Create an ARC-able `sec_trust_t` instance from a `SecTrustRef`.
 *
 * @param trust
 *      A `SecTrustRef` instance.
 *
 * @return a `sec_trust_t` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable sec_trust_t
sec_trust_create(SecTrustRef __nonnull trust);

/*!
 * @function sec_trust_copy_ref
 *
 * @abstract
 *      Copy a retained reference to the underlying `SecTrustRef` instance.
 *
 * @param trust
 *      A `sec_trust_t` instance.
 *
 * @return The underlying `SecTrustRef` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SecTrustRef
sec_trust_copy_ref(sec_trust_t __nonnull trust);

/*!
 * @function sec_identity_create
 *
 * @abstract
 *      Create an ARC-able `sec_identity_t` instance from a `SecIdentityRef`.
 *
 * @param identity
 *      A `SecIdentityRef` instance.
 *
 * @return a `sec_identity_t` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable sec_identity_t
sec_identity_create(SecIdentityRef __nonnull identity);

/*!
 * @function sec_identity_create_with_certificates
 *
 * @abstract
 *      Create an ARC-able `sec_identity_t` instance from a `SecIdentityRef` and
 *      array of SecCertificateRef instances.
 *
 * @param identity
 *      A `SecIdentityRef` instance.
 *
 * @param certificates
 *      An array of `SecCertificateRef` instances.
 *
 * @return a `sec_identity_t` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable sec_identity_t
sec_identity_create_with_certificates(SecIdentityRef __nonnull identity, CFArrayRef __nonnull certificates);

/*!
 * @function sec_identity_copy_ref
 *
 * @abstract
 *      Copy a retained reference to the underlying `SecIdentityRef` instance.
 *
 * @param identity
 *      A `sec_identity_t` instance.
 *
 * @return The underlying `SecIdentityRef` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SecIdentityRef
sec_identity_copy_ref(sec_identity_t __nonnull identity);

/*!
 * @function sec_identity_copy_certificates_ref
 *
 * @abstract
 *      Copy a retained reference to the underlying `CFArrayRef` container of `SecCertificateRef` types.
 *
 * @param identity
 *      A `sec_identity_t` instance.
 *
 * @return The underlying `CFArrayRef` container with `SecCertificateRef` instances.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
CFArrayRef
sec_identity_copy_certificates_ref(sec_identity_t __nonnull identity);

/*!
 * @function sec_certificate_create
 *
 * @abstract
 *      Create an ARC-able `sec_certificate_t` instance from a `SecCertificateRef`.
 *
 * @param certificate
 *      A `SecCertificateRef` instance.
 *
 * @return a `sec_certificate_t` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SEC_RETURNS_RETAINED _Nullable sec_certificate_t
sec_certificate_create(SecCertificateRef __nonnull certificate);

/*!
 * @function sec_certificate_copy_ref
 *
 * @abstract
 *      Copy a retained reference to the underlying `SecCertificateRef` instance.
 *
 * @param certificate
 *      A `sec_certificate_t` instance.
 *
 * @return The underlying `SecCertificateRef` instance.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
SecCertificateRef
sec_certificate_copy_ref(sec_certificate_t __nonnull certificate);

SEC_ASSUME_NONNULL_END

#endif // SecProtocolTypes_h
