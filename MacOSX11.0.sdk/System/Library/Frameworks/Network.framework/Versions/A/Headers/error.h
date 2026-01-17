//
//  error.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_ERROR_H__
#define __NW_ERROR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <dns_sd.h>

#include <CoreFoundation/CoreFoundation.h>

__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_error_t
 * @abstract
 *		A network error object with a domain and error code.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_ERROR_IMPL
NW_OBJECT_DECL(nw_error);
#endif // NW_ERROR_IMPL


/*!
 * @typedef nw_error_domain_t
 * @abstract
 *		The enumeration of network error domains.
 */
typedef enum {
	/*! @const nw_error_domain_invalid */
	nw_error_domain_invalid = 0,
	/*! @const nw_error_domain_posix The error code will be a POSIX error as defined in <sys/errno.h> */
	nw_error_domain_posix = 1,
	/*! @const nw_error_domain_dns The error code will be a DNSServiceErrorType error as defined in <dns_sd.h> */
	nw_error_domain_dns = 2,
	/*! @const nw_error_domain_tls The error code will be a TLS error as defined in <Security/SecureTransport.h> */
	nw_error_domain_tls = 3
} nw_error_domain_t;

/*!
 * @function nw_error_get_error_domain
 *
 * @abstract
 *		Given a reference to a nw_error, returns the error domain.
 *
 * @param error
 *		A reference to the nw_error.
 *
 * @returns
 *		The error domain.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_error_domain_t
nw_error_get_error_domain(nw_error_t error);

/*!
 * @function nw_error_get_error_code
 *
 * @abstract
 *		Given a reference to a nw_error, returns the error code.
 *
 * @param error
 *		A reference to the nw_error.
 *
 * @returns
 *		The error code.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
int
nw_error_get_error_code(nw_error_t error);

/*!
 * @const kNWErrorDomainPOSIX
 * @abstract CFErrorRef domain corresponding to nw_error_domain_posix.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
extern const CFStringRef kNWErrorDomainPOSIX; // Values will be POSIX errors

/*!
 * @const kNWErrorDomainDNS
 * @abstract CFErrorRef domain corresponding to nw_error_domain_posix.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
extern const CFStringRef kNWErrorDomainDNS; // Values will be DNSServiceErrorType errors

/*!
 * @const kNWErrorDomainTLS
 * @abstract CFErrorRef domain corresponding to nw_error_domain_tls.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
extern const CFStringRef kNWErrorDomainTLS; // Values will be errSSL* errors

/*!
 * @function nw_error_copy_cf_error
 *
 * @abstract
 *		Given a reference to nw_error, returns a CFErrorRef representing the same error.
 *
 * @param error
 *		A reference to the nw_error.
 *
 * @returns
 *		The CFErrorRef. The caller is responsible for calling CFRelease on the returned value.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
CFErrorRef
nw_error_copy_cf_error(nw_error_t error);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_ERROR_H__ */
