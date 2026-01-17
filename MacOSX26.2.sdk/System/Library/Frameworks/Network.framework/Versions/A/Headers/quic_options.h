//
//  quic_options.h
//  Network
//
//  Copyright (c) 2020-2021 Apple Inc. All rights reserved.
//

#ifndef __NW_QUIC_OPTIONS_H__
#define __NW_QUIC_OPTIONS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>

#include <Security/Security.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

#pragma mark - QUIC

/*!
 * @function nw_protocol_copy_quic_definition
 *
 * @abstract
 *		Access the definition of the default system protocol implementation
 *		of QUIC. This protocol can be used as part of a
 *		connection's protocol stack as a transport protocol.
 *
 * @result
 *		Returns a retained protocol definition object.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NW_RETURNS_RETAINED nw_protocol_definition_t
nw_protocol_copy_quic_definition(void);

/*!
 * @function nw_quic_create_options
 *
 * @abstract
 *		Create an instance of QUIC protocol options. This object can be added
 *		to an nw_protocol_stack_t to be used in an nw_connection_t or
 *		an nw_listener_t.
 *
 * @result
 *		Returns a retained protocol options object.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NW_RETURNS_RETAINED nw_protocol_options_t
nw_quic_create_options(void);

/*!
 * @function nw_protocol_options_is_quic
 *
 * @abstract
 *		Checks whether the given protocol options define a QUIC protocol.
 *
 * @result
 *		Returns true if the protocol options are for QUIC, false otherwise.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
bool
nw_protocol_options_is_quic(nw_protocol_options_t options);

/*!
 * @function nw_quic_add_tls_application_protocol
 *
 * @abstract
 *		Adds an Application-Layer Protocol Negotiation (ALPN) value to present in the TLS handshake.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_add_tls_application_protocol(nw_protocol_options_t options, const char *application_protocol);

/*!
 * @function nw_quic_copy_sec_protocol_options
 *
 * @abstract
 *		Access the sec_protocol_options_t for a given QUIC
 *		options instance. See <Security/SecProtocolOptions.h> for functions
 *		to further configure security options.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		Returns a retained sec_protocol_options_t object.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NW_RETURNS_RETAINED sec_protocol_options_t
nw_quic_copy_sec_protocol_options(nw_protocol_options_t options);

#pragma mark - QUIC Options

/*!
 * @function nw_quic_get_stream_is_unidirectional
 *
 * @abstract
 *		Returns whether or not a QUIC stream is unidirectional.
 *
 * @param options
 *		An nw_protocol_options_t for a QUIC stream.
 *
 * @result
 *		True if the stream is unidirectional, false otherwise.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
bool
nw_quic_get_stream_is_unidirectional(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_stream_is_unidirectional
 *
 * @abstract
 *		Set whether or not a QUIC stream should be unidirectional.
 *
 * @param options
 *		An nw_protocol_options_t for a QUIC stream.
 *
 * @param is_unidirectional
 *		True if the stream is unidirectional, false otherwise.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_stream_is_unidirectional(nw_protocol_options_t options,
									 bool is_unidirectional);

/*!
 * @function nw_quic_get_stream_is_datagram
 *
 * @abstract
 *		Get whether or not the QUIC stream is a QUIC datagram flow.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result is_datagram
 *		True if the QUIC stream is a QUIC datagram flow.
 */
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
bool
nw_quic_get_stream_is_datagram(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_stream_is_datagram
 *
 * @abstract
 *		Set whether or not the QUIC stream should be a QUIC datagram flow.
 *		Only one QUIC datagram flow can be created per connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param is_datagram
 *		A boolean to indicate whether or not the QUIC stream should be a QUIC datagram flow.
 */
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
void
nw_quic_set_stream_is_datagram(nw_protocol_options_t options,
							   bool is_datagram);

/*!
 * @function nw_quic_get_initial_max_data
 *
 * @abstract
 *		Get the initial_max_data transport parameter on a QUIC
 *		connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		The initial_max_data that a client
 *		is willing to receive on a connection.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_initial_max_data(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_initial_max_data
 *
 * @abstract
 *		Set the initial_max_data transport parameter on a QUIC
 *		connection. Setting this option requires
 *		initial_max_stream_data_bidirectional_local,
 *		initial_max_stream_data_bidirectional_remote and
 *		initial_max_stream_data_unidirectional also to be set.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param initial_max_data
 *		The initial_max_data controls how much data, in bytes, a client
 *		is willing to receive on a connection.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_initial_max_data(nw_protocol_options_t options,
							 uint64_t initial_max_data);

/*!
 * @function nw_quic_get_max_udp_payload_size
 *
 * @abstract
 *		Get the maximum length of a QUIC packet (UDP payload)
 *		that the client is willing to receive on a connection, in bytes.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		The max_udp_payload_size value, in bytes.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint16_t
nw_quic_get_max_udp_payload_size(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_max_udp_payload_size
 *
 * @abstract
 *		Define the maximum length of a QUIC packet (UDP payload)
 *		that the client is willing to receive on a connection, in bytes.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param max_udp_payload_size
 *		The max_udp_payload_size value, in bytes.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_max_udp_payload_size(nw_protocol_options_t options,
								 uint16_t max_udp_payload_size);

/*!
 * @function nw_quic_get_idle_timeout
 *
 * @abstract
 *		Get the idle timeout value for the QUIC connection. If no packets are sent or received
 *		within this timeout, the QUIC connection will be closed.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		The idle_timeout value, in milliseconds.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint32_t
nw_quic_get_idle_timeout(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_idle_timeout
 *
 * @abstract
 *		Define an idle timeout value for the QUIC connection. If no packets are sent or received
 *		within this timeout, the QUIC connection will be closed.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param idle_timeout
 *		The idle_timeout value, in milliseconds.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_idle_timeout(nw_protocol_options_t options,
						 uint32_t idle_timeout);

/*!
 * @function nw_quic_get_initial_max_streams_bidirectional
 *
 * @abstract
 *		Get the initial value of maximum bidirectional streams
 *		that the peer can initiate on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		The initial value for the maximum concurrent bidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_initial_max_streams_bidirectional(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_initial_max_streams_bidirectional
 *
 * @abstract
 *		Set the initial value of maximum bidirectional streams
 *		that the peer can initiate on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param initial_max_streams_bidirectional
 *		The initial value for the maximum concurrent bidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_initial_max_streams_bidirectional(nw_protocol_options_t options,
											  uint64_t initial_max_streams_bidirectional);

/*!
 * @function nw_quic_get_initial_max_streams_unidirectional
 *
 * @abstract
 *		Get the initial value of maximum unidirectional streams
 *		that the peer can initiate on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		The initial value for the maximum concurrent unidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_initial_max_streams_unidirectional(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_initial_max_streams_unidirectional
 *
 * @abstract
 *		Set the initial value of maximum unidirectional streams
 *		that the peer can initiate on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param initial_max_streams_unidirectional
 *		The initial value for the maximum concurrent unidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_initial_max_streams_unidirectional(nw_protocol_options_t options,
											   uint64_t initial_max_streams_unidirectional);

/*!
 * @function nw_quic_get_initial_max_stream_data_bidirectional_local
 *
 * @abstract
 *		Get the initial_max_stream_data_bidi_local transport parameter
 *		on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		How much data the client is willing to receive on a locally initiated stream.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_initial_max_stream_data_bidirectional_local(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_initial_max_stream_data_bidirectional_local
 *
 * @abstract
 *		Set the initial_max_stream_data_bidi_local transport parameter
 *		on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param initial_max_stream_data_bidirectional_local
 *		The initial_max_stream_data_bidi_local controls how much data
 *		the client is willing to receive on a locally initiated stream.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_initial_max_stream_data_bidirectional_local(nw_protocol_options_t options,
														uint64_t initial_max_stream_data_bidirectional_local);

/*!
 * @function nw_quic_get_initial_max_stream_data_bidirectional_remote
 *
 * @abstract
 *		Get the initial_max_stream_data_bidi_remote transport parameter
 *		on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		How much data the client is willing to receive on a remotely initiated stream.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_initial_max_stream_data_bidirectional_remote(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_initial_max_stream_data_bidirectional_remote
 *
 * @abstract
 *		Set the initial_max_stream_data_bidi_remote transport parameter
 *		on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param initial_max_stream_data_bidirectional_remote
 *		The initial_max_stream_data_bidi_remote controls how much data
 *		the client is willing to receive on a remotely initiated stream.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_initial_max_stream_data_bidirectional_remote(nw_protocol_options_t options,
														 uint64_t initial_max_stream_data_bidirectional_remote);

/*!
 * @function nw_quic_get_initial_max_stream_data_unidirectional
 *
 * @abstract
 *		Get the initial_max_stream_data_uni transport parameter
 *		on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 *		How much data the client is willing to receive on a unidirectional stream.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_initial_max_stream_data_unidirectional(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_initial_max_stream_data_unidirectional
 *
 * @abstract
 *		Set the initial_max_stream_data_uni transport parameter
 *		on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param initial_max_stream_data_unidirectional
 *		The initial_max_stream_data_uni controls how much data
 *		the client is willing to receive on a unidirectional stream.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_initial_max_stream_data_unidirectional(nw_protocol_options_t options,
												   uint64_t initial_max_stream_data_unidirectional);

/*!
 * @function nw_quic_get_max_datagram_frame_size
 *
 * @abstract
 *		Get the max_datagram_frame_size transport parameter
 *		on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @result
 * 		If greater than zero, the max_datagram_frame_size value indicates that
 * 		DATAGRAM frames are supported, and describes the maximum number
 * 		of bytes that a single DATAGRAM frame can contain.
 */
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
uint16_t
nw_quic_get_max_datagram_frame_size(nw_protocol_options_t options);

/*!
 * @function nw_quic_set_max_datagram_frame_size
 *
 * @abstract
 *		Set the max_datagram_frame_size transport parameter
 *		on a QUIC connection.
 *
 * @param options
 *		An nw_protocol_options_t for QUIC.
 *
 * @param max_datagram_frame_size
 * 		If greater than zero, the max_datagram_frame_size value indicates that
 * 		DATAGRAM frames are supported, and describes the maximum number
 * 		of bytes that a single DATAGRAM frame can contain.
 */
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
void
nw_quic_set_max_datagram_frame_size(nw_protocol_options_t options,
									uint16_t max_datagram_frame_size);

#pragma mark - QUIC Metadata

/**
 * @typedef nw_quic_stream_type_t
 * @abstract
 *    Represents the type of a QUIC stream.
 */
typedef enum {
	/*! @const nw_quic_stream_type_unknown 		A QUIC stream whose direction can not be determined. */
	nw_quic_stream_type_unknown = 0,
	/*! @const nw_quic_stream_type_bidirectional	A bidirectional QUIC stream. */
	nw_quic_stream_type_bidirectional = 1,
	/*! @const nw_quic_stream_type_unidirectional 	An unidirectional QUIC stream. */
	nw_quic_stream_type_unidirectional = 2,
	/*! @const nw_quic_stream_type_datagram 		A QUIC datagram stream. */
	nw_quic_stream_type_datagram = 3,
} nw_quic_stream_type_t;

/*!
 * @function nw_protocol_metadata_is_quic
 *
 * @abstract
 *		Checks if a protocol metadata object is compatible with the
 *		accessors defined in this file for the default system
 *		implementation of QUIC.
 *
 * @result
 *		Returns true if the metadata is for the default system QUIC,
 *		false otherwise.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
bool
nw_protocol_metadata_is_quic(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_copy_sec_protocol_metadata
 *
 * @abstract
 *		Access the sec_protocol_metadata_t for a given QUIC connection
 *		metadata instance. See <Security/SecProtocolOptions.h> for functions
 *		to further configure security options.
 *
 *		Will be filled out on connected instances of QUIC for metadata
 *		returned by nw_connection_copy_protocol_metadata.
 *
 * @param metadata
 *		An nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns a retained sec_protocol_metadata_t object.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
NW_RETURNS_RETAINED sec_protocol_metadata_t
nw_quic_copy_sec_protocol_metadata(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_get_stream_id
 *
 * @abstract
 *		Get the QUIC stream ID.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for a QUIC stream.
 *
 * @result
 *		Returns the QUIC stream id.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_stream_id(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_stream_get_type
 *
 * @abstract
 *        Describes the type of the QUIC stream.
 *
 * @param stream_metadata
 *        A nw_protocol_metadata_t for a QUIC stream.
 *
 * @result
 *        Returns the type of the QUIC stream, stored in nw_quic_stream_type_t.
 *        If the type can not be determined, returns nw_quic_stream_type_unknown.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint8_t
nw_quic_get_stream_type(nw_protocol_metadata_t stream_metadata);

/*!
 * @function nw_quic_get_stream_application_error
 *
 * @abstract
 *		Access the Application Error value received from the peer in a stream close
 *		message.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for a QUIC stream.
 *
 * @result
 *		Returns the Application Error code value received from by the peer,
 *		or UINT64_MAX if no error has been received.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_stream_application_error(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_set_stream_application_error
 *
 * @abstract
 *		Set an Application Error value to send to the peer when the stream
 *		is closed.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for a QUIC stream.
 *
 * @param application_error
 *		An application-specific error code value.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_stream_application_error(nw_protocol_metadata_t metadata,
									 uint64_t application_error);

/*!
 * @function nw_quic_get_local_max_streams_bidirectional
 *
 * @abstract
 *      Get the most recent value of the maximum number of bidirectional streams that the peer can create.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns the most recent value of the peer's max number of bidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_local_max_streams_bidirectional(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_set_local_max_streams_bidirectional
 *
 * @abstract
 *		Sets the maximum number of bidirectional streams that the peer can create.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @param max_streams_bidirectional
 *		The new number of maximum bidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_local_max_streams_bidirectional(nw_protocol_metadata_t metadata,
											uint64_t max_streams_bidirectional);

/*!
 * @function nw_quic_get_local_max_streams_unidirectional
 *
 * @abstract
 *      Get the most recent value of the maximum number of unidirectional streams that the peer can create.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns the most recent value of the peer's max number of unidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_local_max_streams_unidirectional(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_set_local_max_streams_unidirectional
 *
 * @abstract
 *		Sets the maximum number of unidirectional streams that the peer can create.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @param max_streams_unidirectional
 *		The new number of maximum unidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_local_max_streams_unidirectional(nw_protocol_metadata_t metadata,
											 uint64_t max_streams_unidirectional);

/*!
 * @function nw_quic_get_remote_max_streams_bidirectional
 *
 * @abstract
 * 	    Get the maximum number of bidirectional streams advertised by peer that an application
 *  	is allowed to create.
 *
 *  	Note that while attempts to create streams above this limit will
 *  	be blocked until the server increases the limit, these blocked
 *  	attempts will cause a STREAMS_BLOCKED frame to be sent to the
 *  	server. This informs the server that the client has more streams
 *  	it would like to create. As a result, the caller should attempt to
 *  	create streams over this limit if it desires more streams.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns the most recent value of the peer's advertised max number of bidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_remote_max_streams_bidirectional(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_get_remote_max_streams_unidirectional
 *
 * @abstract
 * 	    Get the maximum number of unidirectional streams advertised by peer that an application
 *  	is allowed to create.
 *
 *  	Note that while attempts to create streams above this limit will
 *  	be blocked until the server increases the limit, these blocked
 *  	attempts will cause a STREAMS_BLOCKED frame to be sent to the
 *  	server. This informs the server that the client has more streams
 *  	it would like to create. As a result, the caller should attempt to
 *  	create streams over this limit if it desires more streams.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns the most recent value of the peer's advertised max number of unidirectional streams.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_remote_max_streams_unidirectional(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_get_stream_usable_datagram_frame_size
 *
 * @abstract
 *		Get the usable size of a datagram frame from a QUIC datagram flow.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns the usable datagram frame size.
 */
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
uint16_t
nw_quic_get_stream_usable_datagram_frame_size(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_get_application_error
 *
 * @abstract
 *		Access the Application Error value received from the peer in a connection close
 *		message.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns the Application Error code value received from by the peer,
 *		or UINT64_MAX if no	error has been received.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_application_error(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_get_application_error_reason
 *
 * @abstract
 *		Access the Application Error reason string received from the peer in a connection
 *		close message.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns the Application Error reason received from by the peer,
 *		or NULL if no error reason has been received.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
const char * _Nullable
nw_quic_get_application_error_reason(nw_protocol_metadata_t metadata);

/*!
 * @function nw_quic_set_application_error
 *
 * @abstract
 *		Set the Application Error value to send to the peer in a connection close
 *		message.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @param application_error
 *		Sets the Application Error code value.
 *
 * @param reason
 *		An optional reason string to associate with the error.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_application_error(nw_protocol_metadata_t metadata,
							  uint64_t application_error,
							  const char * _Nullable reason);

/*!
 * @function nw_quic_get_keepalive_interval
 *
 * @abstract
 *		Retrieves the keep-alive interval set on a QUIC connection.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns value of the keep-alive interval, in seconds,
 *		or 0 if the keep-alive timer is disabled.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint16_t
nw_quic_get_keepalive_interval(nw_protocol_metadata_t metadata);

/*!
 * @define NW_QUIC_CONNECTION_DEFAULT_KEEPALIVE
 * @discussion A sentinel value passed to `nw_quic_set_keepalive_interval` to configure
 * 		the default keepalive value. The current default behavior is to send a keepalive
 * 		every 20 seconds, although this is subject to change.
 */
#define NW_QUIC_CONNECTION_DEFAULT_KEEPALIVE	UINT16_MAX

/*!
 * @function nw_quic_set_keepalive_interval
 *
 * @abstract
 *		Changes the keep-alive interval for QUIC.
 *
 * @discussion
 * 		QUIC connections are encrypted and operate over the UDP protocol
 * 		which makes it hard for Network Address	Translators and firewalls
 * 		to track their state. For this reason, these middleboxes may
 * 		use short timeouts for QUIC flows. By sending keep-alive packets
 * 		(QUIC PING frames), the endpoint can maintain
 * 		state of the flow across the network.
 * 		Keep-alives should only be enabled while there is an outstanding
 * 		exchange of information with the remote endpoint that has not yet
 * 		completed, it is not recommended to enable keep-alive packets on an
 * 		idle connection that is not expecting to send or receive data in
 * 		the near future.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @param keepalive_interval
 * 		The keep-alive interval for QUIC, in seconds,
 * 		or 0 if the keep-alive timer is disabled.
 * 		Pass `NW_QUIC_CONNECTION_DEFAULT_KEEPALIVE` to use the default
 * 		keep-alive interval.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
void
nw_quic_set_keepalive_interval(nw_protocol_metadata_t metadata,
							   uint16_t keepalive_interval);

#pragma mark - QUIC Metadata Get Only

/*!
 * @function nw_quic_get_remote_idle_timeout
 *
 * @abstract
 *		Access the idle_timeout value in milliseconds received from the peer
 *		in the transport parameters.
 *
 * @param metadata
 *		A nw_protocol_metadata_t for QUIC.
 *
 * @result
 *		Returns the idle_timeout value in milliseconds received from the peer.
 */
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
uint64_t
nw_quic_get_remote_idle_timeout(nw_protocol_metadata_t metadata);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif // __NW_QUIC_OPTIONS_H__
