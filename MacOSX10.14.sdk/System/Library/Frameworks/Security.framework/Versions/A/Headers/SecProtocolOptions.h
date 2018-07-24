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

#ifndef SecProtocolOptions_h
#define SecProtocolOptions_h

#include <Security/SecProtocolObject.h>
#include <Security/SecBase.h>
#include <Security/SecureTransport.h>
#include <Security/SecTrust.h>
#include <Security/SecCertificate.h>
#include <Security/SecIdentity.h>
#include <Security/SecProtocolMetadata.h>

#include <dispatch/dispatch.h>
#include <os/object.h>

/*!
 * The following diagram shows how clients interact with sec_protocol_options
 * and sec_protocol_metadata when configuring and using network security protocols.
 *
 *                    +--------+
 *                    | Client |
 *                    +-+---/ \+
 *                      |    |
 *        +-------------+    +-------------+
 *        | (1) set             (2) get    |
 *        | options             metadata   |
 * +-----\ /---------------+  +------------+----------+
 * | sec_protocol_options  |  | sec_protocol_metadata |
 * +-----------------------+  +-----------------------+
 *
 * Clients configure security protocols with `sec_protocol_options` instances.
 * And they inspect protocol instances using `sec_protocol_metadata` instances.
 */

#ifndef SEC_OBJECT_IMPL
/*!
 * A `sec_protocol_options` instance is a container of options for security protocol instances,
 * such as TLS. Protocol options are used to configure security protocols in the network stack.
 * For example, clients may set the maximum and minimum allowed TLS versions through protocol
 * options.
 */
SEC_OBJECT_DECL(sec_protocol_options);
#endif // !SEC_OBJECT_IMPL

__BEGIN_DECLS

SEC_ASSUME_NONNULL_BEGIN

/*!
 * @function sec_protocol_options_set_local_identity
 *
 * @abstract
 *      Set the local identity to be used for this protocol instance.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param identity
 *      A `sec_identity_t` instance carrying the private key and certificate.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_local_identity(sec_protocol_options_t options, sec_identity_t identity);

/*!
 * @function sec_protocol_options_add_tls_ciphersuite
 *
 * @abstract
 *      Add a TLS ciphersuite to the set of enabled ciphersuites.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param ciphersuite
 *      A SSLCipherSuite value.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_add_tls_ciphersuite(sec_protocol_options_t options, SSLCipherSuite ciphersuite);

/*!
 * @function sec_protocol_options_add_tls_ciphersuite_group
 *
 * @abstract
 *      Add a TLS ciphersuite group to the set of enabled ciphersuites.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param group
 *      A SSLCipherSuiteGroup value.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_add_tls_ciphersuite_group(sec_protocol_options_t options, SSLCiphersuiteGroup group);

/*!
 * @function sec_protocol_options_set_tls_min_version
 *
 * @abstract
 *      Set the minimum support TLS version.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param version
 *      A SSLProtocol enum value.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_min_version(sec_protocol_options_t options, SSLProtocol version);

/*!
 * @function sec_protocol_options_set_tls_max_version
 *
 * @abstract
 *      Set the maximum support TLS version.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param version
 *      A SSLProtocol enum value.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_max_version(sec_protocol_options_t options, SSLProtocol version);

/*!
 * @function sec_protocol_options_add_tls_application_protocol
 *
 * @abstract
 *      Add an application protocol supported by clients of this protocol instance.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param application_protocol
 *      A NULL-terminated string defining the application protocol.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_add_tls_application_protocol(sec_protocol_options_t options, const char *application_protocol);

/*!
 * @function sec_protocol_options_set_tls_server_name
 *
 * @abstract
 *      Set the server (domain) name to be used in the TLS SNI. This will override
 *      the server name obtained from the endpoint.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param server_name
 *      A NULL-terminated string carrying the server (domain) name.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_server_name(sec_protocol_options_t options, const char *server_name);

/*!
 * @function sec_protocol_options_set_tls_diffie_hellman_parameters
 *
 * @abstract
 *      Set the supported Diffie-Hellman parameters.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param params
 *      A dispatch_data_t containing legacy Diffie-Hellman parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_diffie_hellman_parameters(sec_protocol_options_t options, dispatch_data_t params);

/*!
 * @function sec_protocol_options_add_pre_shared_key
 *
 * @abstract
 *      Add a pre-shared key (PSK) and its identity to the options.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param psk
 *      A dispatch_data_t containing a PSK blob.
 *
 * @param psk_identity
 *      A dispatch_data_t containing a PSK identity blob.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_add_pre_shared_key(sec_protocol_options_t options, dispatch_data_t psk, dispatch_data_t psk_identity);

/*!
 * @function sec_protocol_options_set_tls_tickets_enabled
 *
 * @abstract
 *      Enable or disable TLS session ticket support.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param tickets_enabled
 *      Flag to enable or disable TLS session ticket support.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_tickets_enabled(sec_protocol_options_t options, bool tickets_enabled);

/*!
 * @function sec_protocol_options_set_tls_is_fallback_attempt
 *
 * @abstract
 *      Signal if this is a TLS fallback attempt.
 *
 *      A fallback attempt is one following a previously failed TLS connection
 *      due to version or parameter incompatibility, e.g., when speaking to a server
 *      that does not support a client-offered ciphersuite.
 *
 *      Clients MUST NOT enable fallback for fresh connections.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param is_fallback_attempt
 *      Set a flag indicating that this is a TLS fallback attempt.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_is_fallback_attempt(sec_protocol_options_t options, bool is_fallback_attempt);

/*!
 * @function sec_protocol_options_set_tls_resumption_enabled
 *
 * @abstract
 *      Enable or disable TLS session resumption.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param resumption_enabled
 *      Flag to enable or disable TLS session resumption.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_resumption_enabled(sec_protocol_options_t options, bool resumption_enabled);

/*!
 * @function sec_protocol_options_set_tls_false_start_enabled
 *
 * @abstract
 *      Enable or disable TLS False Start.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param false_start_enabled
 *      Flag to enable or disable TLS False Start.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_false_start_enabled(sec_protocol_options_t options, bool false_start_enabled);

/*!
 * @function nw_protocol_options_set_tls_ocsp_enabled
 *
 * @abstract
 *      Enable or disable OCSP support.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param ocsp_enabled
 *      Flag to enable or disable OCSP support.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_ocsp_enabled(sec_protocol_options_t options, bool ocsp_enabled);

/*!
 * @function sec_protocol_options_set_tls_sct_enabled
 *
 * @abstract
 *      Enable or disable SCT (signed certificate timestamp) support.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param sct_enabled
 *      Flag to enable or disable SCT support.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_sct_enabled(sec_protocol_options_t options, bool sct_enabled);

/*!
 * @function sec_protocol_options_set_tls_renegotiation_enabled
 *
 * @abstract
 *      Enable or disable TLS (1.2 and prior) session renegotiation. This defaults to `true`.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param renegotiation_enabled
 *      Flag to enable or disable TLS (1.2 and prior) session renegotiation.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_tls_renegotiation_enabled(sec_protocol_options_t options, bool renegotiation_enabled);

/*!
 * @function sec_protocol_options_set_peer_authentication_required
 *
 * @abstract
 *      Enable or disable peer authentication. Clients default to true, whereas servers default to false.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param peer_authentication_required
 *      Flag to enable or disable mandatory peer authentication.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_peer_authentication_required(sec_protocol_options_t options, bool peer_authentication_required);

#ifdef __BLOCKS__

/*!
 * @block sec_protocol_key_update_complete_t
 *
 * @abstract
 *      Block to be invoked when a key update event is handled.
 */
typedef void (^sec_protocol_key_update_complete_t)(void);

/*!
 * @block sec_protocol_key_update_t
 *
 * @abstract
 *      Block to be invoked when the protocol key MUST be updated.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param complete
 *      A `sec_protocol_key_update_complete_t` to be invoked when the key update is complete.
 */
typedef void (^sec_protocol_key_update_t)(sec_protocol_metadata_t metadata, sec_protocol_key_update_complete_t complete);

/*!
 * @block sec_protocol_challenge_complete_t
 *
 * @abstract
 *      Block to be invoked when an identity (authentication) challenge is complete.
 *
 * @param identity
 *      A `sec_identity_t` containing the identity to use for this challenge.
 */
typedef void (^sec_protocol_challenge_complete_t)(sec_identity_t identity);

/*!
 * @block sec_protocol_challenge_t
 *
 * @abstract
 *      Block to be invoked when the protocol instance is issued a challenge (e.g., a TLS certificate request).
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param complete
 *      A `sec_protocol_challenge_complete_t` to be invoked when the challenge is complete.
 */
typedef void (^sec_protocol_challenge_t)(sec_protocol_metadata_t metadata, sec_protocol_challenge_complete_t complete);

/*!
 * @block sec_protocol_verify_complete_t
 *
 * @abstract
 *      Block to be invoked when verification is complete.
 *
 * @param result
 *      A `bool` indicating if verification succeeded or failed.
 */
typedef void (^sec_protocol_verify_complete_t)(bool result);

/*!
 * @block sec_protocol_verify_t
 *
 * @abstract
 *      Block to be invoked when the protocol instance must verify the peer.
 *
 *      NOTE: this may be called one or more times for a given connection.
 *
 * @param metadata
 *      A `sec_protocol_metadata_t` instance.
 *
 * @param trust_ref
 *      A `sec_trust_t` instance.
 *
 * @param complete
 *      A `sec_protocol_verify_finish_t` to be invoked when verification is complete.
 */
typedef void (^sec_protocol_verify_t)(sec_protocol_metadata_t metadata, sec_trust_t trust_ref, sec_protocol_verify_complete_t complete);

/*!
 * @function sec_protocol_options_set_key_update_block
 *
 * @abstract
 *      Set the key update block.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @param key_update_block
 *      A `sec_protocol_key_update_t` block.
 *
 * @params key_update_queue
 *      A `dispatch_queue_t` on which the key update block should be called.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_key_update_block(sec_protocol_options_t options, sec_protocol_key_update_t key_update_block, dispatch_queue_t key_update_queue);

/*!
 * @function sec_protocol_options_set_challenge_block
 *
 * @abstract
 *      Set the challenge block.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @params challenge_block
 *      A `sec_protocol_challenge_t` block.
 *
 * @params challenge_queue
 *      A `dispatch_queue_t` on which the challenge block should be called.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_challenge_block(sec_protocol_options_t options, sec_protocol_challenge_t challenge_block, dispatch_queue_t challenge_queue);

/*!
 * @function sec_protocol_options_set_verify_block
 *
 * @abstract
 *      Set the verify block.
 *
 * @param options
 *      A `sec_protocol_options_t` instance.
 *
 * @params verify_block
 *      A `sec_protocol_verify_t` block.
 *
 * @params verify_block_queue
 *      A `dispatch_queue_t` on which the verify block should be called.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
sec_protocol_options_set_verify_block(sec_protocol_options_t options, sec_protocol_verify_t verify_block, dispatch_queue_t verify_block_queue);

#endif // __BLOCKS__

SEC_ASSUME_NONNULL_END

__END_DECLS

#endif // SecProtocolOptions_h
