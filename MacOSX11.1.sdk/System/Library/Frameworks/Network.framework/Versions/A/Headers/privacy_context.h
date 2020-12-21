//
//  privacy_context.h
//  Network
//
//  Copyright (c) 2020 Apple Inc. All rights reserved.
//

#ifndef __NW_PRIVACY_CONTEXT_H__
#define __NW_PRIVACY_CONTEXT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <Network/resolver_config.h>

#include <stdbool.h>
#include <stdint.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_privacy_context_t
 * @abstract
 *		A Network Privacy Context can contain various connections and listeners
 *		that share various privacy settings and protocol caches. Any in-process
 *		cached state, such as TLS sessions, will only be shared within privacy
 *		contexts and will not cross privacy context boundaries.
 *
 *		Besides defining caching boundaries, privacy contexts also allow restricting
 *		the behavior of connections within a context to improve their privacy stance
 *		with regards to the system and the local network. For example, a privacy context
 *		can disable logging to ensure that sensitive connections do not contribute to the
 *		system logs. A privacy context can also require that DNS resolutions are encrypted
 *		so that names are not transmitted in the clear on the network during resolution.
 *
 *		Some settings, such as DNS settings, can also be applied to the default privacy
 *		context for the process using NW_DEFAULT_PRIVACY_CONTEXT. Such settings
 *		will be inherited by other resolutions in the same process. Any privacy context
 *		set directly on an nw_parameters_t will take precedence over the default context
 *		settings.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PRIVACY_CONTEXT_IMPL
NW_OBJECT_DECL(nw_privacy_context);
#endif // NW_PRIVACY_CONTEXT_IMPL

/*!
 * @function nw_privacy_context_create
 *
 * @abstract
 * 		Create a new privacy context. This object can be added to connections and listeners
 * 		by setting the privacy context on the nw_parameters_t. Each privacy context can have
 * 		unique settings for logging and resolution, and implicitly has an isolated cache for
 * 		items like TLS sessions.
 *
 * @param description
 * 		A string description used for logging.
 *
 * @result
 *		Returns an allocated nw_privacy_context_t object on success.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED nw_privacy_context_t
nw_privacy_context_create(const char *description);

#define NW_PRIVACY_CONTEXT_TYPE_DECL(name) \
	extern const nw_privacy_context_t _nw_privacy_context_##name

/*!
 * @const NW_DEFAULT_PRIVACY_CONTEXT
 * @discussion The default privacy context represents the default privacy settings used
 * 		throughout the currently running process. Logging may not be disabled on the
 * 		default privacy context.
 *
 * 		Flushing the cache on the default privacy context will not affect other privacy contexts.
 *
 * 		Changing name resolution settings will only affect privacy contexts that did not already
 * 		explicitly configure name resolution requirements.
 */
#define NW_DEFAULT_PRIVACY_CONTEXT (_nw_privacy_context_default_context)
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_PRIVACY_CONTEXT_TYPE_DECL(default_context);

/*!
 * @function nw_privacy_context_flush_cache
 *
 * @abstract
 * 		Flush any cached state stored in this privacy context. The act of flushing the
 * 		cache may be asynchronous, which means that it will take effect shortly after the
 * 		function is invoked.
 *
 * @param privacy_context
 * 		A privacy context to flush.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_privacy_context_flush_cache(nw_privacy_context_t privacy_context);

/*!
 * @function nw_privacy_context_disable_logging
 *
 * @abstract
 * 		Disable logging for connections and listeners associated with this context. Logging
 * 		may not be disabled on the default privacy context.
 *
 * @param privacy_context
 * 		A privacy context on which to disable logging.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_privacy_context_disable_logging(nw_privacy_context_t privacy_context);

/*!
 * @function nw_privacy_context_require_encrypted_name_resolution
 *
 * @abstract
 * 		Require that any DNS name resolution occurring for connections
 * 		associated with this context use encrypted transports, such as TLS or HTTPS.
 * 		Any unencrypted queries will be blocked if require_encrypted_name_resolution
 * 		is set to true. Optionally, a fallback resolver config can be provided to use
 * 		instead of blocking queries when require_encrypted_name_resolution is set to
 * 		true.
 *
 * @param privacy_context
 * 		A privacy context to modify. This can include the default privacy context.
 *
 * @param require_encrypted_name_resolution
 * 		If true, require that any name resolution using DNS is performed
 * 		with encryption. If false, allow cleartext resolution. Defaults to false.
 *
 * @param fallback_resolver_config
 * 		An optional resolver configuration to use if no other encrypted DNS resolver
 * 		is already configured for the query. This will only take effect if
 * 		require_encrypted_name_resolution is set to true. If this configuration is
 * 		NULL and require_encrypted_name_resolution is set to true, all cleartext
 * 		name resolution will be blocked.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_privacy_context_require_encrypted_name_resolution(nw_privacy_context_t privacy_context,
													 bool require_encrypted_name_resolution,
													 _Nullable nw_resolver_config_t fallback_resolver_config);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_PRIVACY_CONTEXT_H__
