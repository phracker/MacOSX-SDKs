//
//  AVBConstants.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2015 Apple Inc. All rights reserved.
//

#ifndef AudioVideoBridging_AVBConstants_h
#define AudioVideoBridging_AVBConstants_h

#include <Foundation/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

#if !defined(_LP64)

#define AVB_LEGACY_OBJC_RUNTIME	1
#define AVB_MODERN_OBJC_RUNTIME	0

#else

#define AVB_LEGACY_OBJC_RUNTIME	0
#define AVB_MODERN_OBJC_RUNTIME	1

#endif


#define AVBMACAddressSize												6

#pragma mark Entity Capability Flags

//Entity Capabilities

typedef NS_ENUM(uint32_t, AVB17221ADPEntityCapabilities)
{
	/*!
		@constant	AVB17221ADPEntityCapabilitiesDFUMode
		@abstract	The IEEE Std 1722.1™-2013 entity supports firmware upgrade mode.
	 */
	AVB17221ADPEntityCapabilitiesDFUMode NS_ENUM_DEPRECATED(10_8, 10_9, NA, NA)				= 0x00000001,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesEFUMode
		@abstract	The IEEE Std 1722.1™-2013 entity supports firmware upgrade mode.
	 */
	AVB17221ADPEntityCapabilitiesEFUMode NS_ENUM_AVAILABLE(10_9, NA)						= 0x00000001,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesAddressAccessSupported
		@abstract	The IEEE Std 1722.1™-2013 entity supports using address access commands and responses.
	 */
	AVB17221ADPEntityCapabilitiesAddressAccessSupported										= 0x00000002,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesGatewayEntity
		@abstract	The IEEE Std 1722.1™-2013 entity functions as a gateway between AVB and another transport.
	 */
	AVB17221ADPEntityCapabilitiesGatewayEntity												= 0x00000004,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesAEMSupported
		@abstract	The IEEE Std 1722.1™-2013 entity uses IEEE Std 1722.1™-2013 AVDECC Entity Model for enumeration and control."
	 */
	AVB17221ADPEntityCapabilitiesAEMSupported												= 0x00000008,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesLegacyAVC
		@abstract	The IEEE Std 1722.1™-2013 entity supports using IEEE 1394 AV/C for enumeration and control."
	 */
	AVB17221ADPEntityCapabilitiesLegacyAVC													= 0x00000010,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesAssociationIDSupported
		@abstract	The IEEE Std 1722.1™-2013 entity supports using the Association ID field.
	 */
	AVB17221ADPEntityCapabilitiesAssociationIDSupported										= 0x00000020,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesAssociationIDValid
		@abstract	The IEEE Std 1722.1™-2013 entity has a valid value in the Association ID field.
	 */
	AVB17221ADPEntityCapabilitiesAssociationIDValid											= 0x00000040,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesVendorUniqueSupported
		@abstract	The IEEE Std 1722.1™-2013 entity supports vendor unique commands and responses.
	 */
	AVB17221ADPEntityCapabilitiesVendorUniqueSupported										= 0x00000080,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesClassASupported
		@abstract	The IEEE Std 1722.1™-2013 entity supports class A streaming.
	 */
	AVB17221ADPEntityCapabilitiesClassASupported											= 0x00000100,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesClassBSupported
		@abstract	The IEEE Std 1722.1™-2013 entity supports class B streaming.
	 */
	AVB17221ADPEntityCapabilitiesClassBSupported											= 0x00000200,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesASSupported
		@abstract	The IEEE Std 1722.1™-2013 entity supports IEEE Std 802.1AS-2011.
	 */
	AVB17221ADPEntityCapabilitiesASSupported NS_ENUM_DEPRECATED(10_8, 10_9, NA, NA)			= 0x00000400,
	/*!
		@constant	AVB17221ADPEntityCapabilitiesGPTPSupported
		@abstract	The IEEE Std 1722.1™-2013 entity supports IEEE Std 802.1AS-2011.
	 */
	AVB17221ADPEntityCapabilitiesGPTPSupported NS_ENUM_AVAILABLE(10_9, NA)					= 0x00000400,
	/*!
		 @constant	AVB17221ADPEntityCapabilitiesAEMAuthenticationSupported
		 @abstract	The IEEE Std 1722.1™-2013 entity supports using AEM authentication.
	 */
	AVB17221ADPEntityCapabilitiesAEMAuthenticationSupported NS_ENUM_AVAILABLE(10_9, NA)		= 0x00000800,
	/*!
		 @constant	AVB17221ADPEntityCapabilitiesAEMAuthenticationRequired
		 @abstract	The IEEE Std 1722.1™-2013 entity requires a controller to authenticate.
	 */
	AVB17221ADPEntityCapabilitiesAEMAuthenticationRequired NS_ENUM_AVAILABLE(10_9, NA)		= 0x00001000,
	/*!
		 @constant	AVB17221ADPEntityCapabilitiesAEMPersistentAcquireSupported
		 @abstract	The IEEE Std 1722.1™-2013 entity supports being persistentlty aquired.
	 */
	AVB17221ADPEntityCapabilitiesAEMPersistentAcquireSupported NS_ENUM_AVAILABLE(10_9, NA)	= 0x00002000,
	/*!
		 @constant	AVB17221ADPEntityCapabilitiesAEMIdenitifyControlIndexValid
		 @abstract	The IEEE Std 1722.1™-2013 entity has an idenitfy control and the identify_control_index field contains a valid index.
	 */
	AVB17221ADPEntityCapabilitiesAEMIdenitifyControlIndexValid NS_ENUM_AVAILABLE(10_9, NA)	= 0x00004000,
	/*!
		 @constant	AVB17221ADPEntityCapabilitiesAEMInterfaceIndexValid
		 @abstract	The IEEE Std 1722.1™-2013 entity has the interface_index field set to a valid index.
	 */
	AVB17221ADPEntityCapabilitiesAEMInterfaceIndexValid NS_ENUM_AVAILABLE(10_9, NA)			= 0x00008000,
	/*!
		 @constant	AVB17221ADPEntityCapabilitiesGeneralControllerIgnore
		 @abstract	The IEEE Std 1722.1™-2013 entity should be ignored by general controllers.
	 */
	AVB17221ADPEntityCapabilitiesGeneralControllerIgnore NS_ENUM_AVAILABLE(10_9, NA)		= 0x00010000,
	/*!
		 @constant	AVB17221ADPEntityCapabilitiesEntityNotReady
		 @abstract	The IEEE Std 1722.1™-2013 entity is not ready to be enumerated or connected by a controller.
	 */
	AVB17221ADPEntityCapabilitiesEntityNotReady NS_ENUM_AVAILABLE(10_9, NA)					= 0x00020000,
} NS_ENUM_AVAILABLE(10_8, NA);

//Talker Specific Capabilities
typedef NS_OPTIONS(uint16_t, AVB17221ADPTalkerCapabilities)
{
	/*!
		@constant	AVB17221ADPTalkerCapabilitiesImplemented
		@abstract	The IEEE Std 1722.1™-2013 entity has talker capabilities.
	 */
	AVB17221ADPTalkerCapabilitiesImplemented							= 0x0001,
	/*!
		@constant	AVB17221ADPTalkerCapabilitiesHasOtherSource
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sources which are not control, media clock, SMPTE, MIDI, audio or video.
	 */
	AVB17221ADPTalkerCapabilitiesHasOtherSource							= 0x0200,
	/*!
		@constant	AVB17221ADPTalkerCapabilitiesHasControlSource
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sources which source a control stream.
	 */
	AVB17221ADPTalkerCapabilitiesHasControlSource						= 0x0400,
	/*!
		@constant	AVB17221ADPTalkerCapabilitiesHasMediaClockSource
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sources which source a media clock stream.
	 */
	AVB17221ADPTalkerCapabilitiesHasMediaClockSource					= 0x0800,
	/*!
		@constant	AVB17221ADPTalkerCapabilitiesHasSMPTESource
		@abstract	The IEEE Std 1722.1™-2013 entity has stream source which source a SMPTE stream.
	 */
	AVB17221ADPTalkerCapabilitiesHasSMPTESource							= 0x1000,
	/*!
		@constant	AVB17221ADPTalkerCapabilitiesHasMIDISource
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sources which source a stream carrying MIDI data.
	 */
	AVB17221ADPTalkerCapabilitiesHasMIDISource							= 0x2000,
	/*!
		@constant	AVB17221ADPTalkerCapabilitiesHasAudioSource
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sources which source a stream with audio data (not embedded in a video stream).
	 */
	AVB17221ADPTalkerCapabilitiesHasAudioSource							= 0x4000,
	/*!
		@constant	AVB17221ADPTalkerCapabilitiesHasVideoSource
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sources which source a stream with video data (and optionally embedded audio data).
	 */
	AVB17221ADPTalkerCapabilitiesHasVideoSource							= 0x8000,
} NS_ENUM_AVAILABLE(10_8, NA);

//Listener Specific Capabilities
typedef NS_OPTIONS(uint16_t, AVB17221ADPListenerCapabilities)
{
	/*!
		@constant	AVB17221ADPListenerCapabilitiesImplemented
		@abstract	The IEEE Std 1722.1™-2013 entity has listener capabilities.
	 */
	AVB17221ADPListenerCapabilitiesImplemented							= 0x0001,
	/*!
		@constant	AVB17221ADPListenerCapabilitiesHasOtherSink
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sinks which are not control, media clock, SMPTE, MIDI, audio or video.
	 */
	AVB17221ADPListenerCapabilitiesHasOtherSink							= 0x0200,
	/*!
		@constant	AVB17221ADPListenerCapabilitiesHasControlSink
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sinks which sink a control stream.
	 */
	AVB17221ADPListenerCapabilitiesHasControlSink						= 0x0400,
	/*!
		@constant	AVB17221ADPListenerCapabilitiesHasMediaClockSink
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sinks which sink a media clock stream.
	 */
	AVB17221ADPListenerCapabilitiesHasMediaClockSink					= 0x0800,
	/*!
		@constant	AVB17221ADPListenerCapabilitiesHasSMPTESink
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sinks which sink a SMPTE stream.
	 */
	AVB17221ADPListenerCapabilitiesHasSMPTESink							= 0x1000,
	/*!
		@constant	AVB17221ADPListenerCapabilitiesHasMIDISink
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sinks which can sink a stream carrying MIDI data.
	 */
	AVB17221ADPListenerCapabilitiesHasMIDISink							= 0x2000,
	/*!
		@constant	AVB17221ADPListenerCapabilitiesHasAudioSink
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sinks which sink a stream with audio data (not embedded in a video stream).
	 */
	AVB17221ADPListenerCapabilitiesHasAudioSink							= 0x4000,
	/*!
		@constant	AVB17221ADPListenerCapabilitiesHasVideoSink
		@abstract	The IEEE Std 1722.1™-2013 entity has stream sinks which sink a stream with video data (and optionally embedded audio data).
	 */
	AVB17221ADPListenerCapabilitiesHasVideoSink							= 0x8000,
} NS_ENUM_AVAILABLE(10_8, NA);

//Controller Specific Capabilities
typedef NS_OPTIONS(uint32_t, AVB17221ADPControllerCapabilities)
{
	/*!
		@constant	AVB17221ADPControllerCapabilitiesImplemented
		@abstract	The IEEE Std 1722.1™-2013 entity has controller capabilities.
	 */
	AVB17221ADPControllerCapabilitiesImplemented						= 0x00000001,
	/*!
		@constant	AVB17221ADPControllerCapabilitiesHasLayer3Proxy
		@abstract	The IEEE Std 1722.1™-2013 entity has a layer 3 to layer 2 proxy implementation.
	 */
	AVB17221ADPControllerCapabilitiesHasLayer3Proxy						= 0x00000002,
} NS_ENUM_AVAILABLE(10_8, NA);

typedef NS_ENUM(uint8_t, AVB17221AECPMessageType)
{
	/*!
		@constant	AVB17221AECPMessageTypeAEMCommand
		@abstract	The IEEE Std 1722.1™-2013 AECP AVDECC Entity Model command message.
	 */
	AVB17221AECPMessageTypeAEMCommand									= 0x0,
	/*!
		@constant	AVB17221AECPMessageTypeAEMResponse
		@abstract	The IEEE Std 1722.1™-2013 AECP AVDECC Entity Model response message.
	 */
	AVB17221AECPMessageTypeAEMResponse									= 0x1,
	/*!
		@constant	AVB17221AECPMessageTypeAddressAccessCommand
		@abstract	The IEEE Std 1722.1™-2013 AECP address access command message.
	 */
	AVB17221AECPMessageTypeAddressAccessCommand							= 0x2,
	/*!
		@constant	AVB17221AECPMessageTypeAddressAccessResponse
		@abstract	The IEEE Std 1722.1™-2013 AECP address access response message.
	 */
	AVB17221AECPMessageTypeAddressAccessResponse						= 0x3,
	/*!
		@constant	AVB17221AECPMessageTypeLegacyAVCCommand
		@abstract	The IEEE Std 1722.1™-2013 AECP AV/C command message.
	 */
	AVB17221AECPMessageTypeLegacyAVCCommand								= 0x4,
	/*!
		@constant	AVB17221AECPMessageTypeLegacyAVCResponse
		@abstract	The IEEE Std 1722.1™-2013 AECP AV/C response message.
	 */
	AVB17221AECPMessageTypeLegacyAVCResponse							= 0x5,
	/*!
		@constant	AVB17221AECPMessageTypeVendorUniqueCommand
		@abstract	The IEEE Std 1722.1™-2013 AECP vendor unique command message.
	 */
	AVB17221AECPMessageTypeVendorUniqueCommand							= 0x6,
	/*!
		@constant	AVB17221AECPMessageTypeVendorUniqueResponse
		@abstract	The IEEE Std 1722.1™-2013 AECP vendor unique response message.
	 */
	AVB17221AECPMessageTypeVendorUniqueResponse							= 0x7,
} NS_ENUM_AVAILABLE(10_8, NA);

typedef NS_ENUM(uint8_t, AVB17221AECPStatusCode)
{
	/*!
		@constant	AVB17221AECPStatusSuccess
		@abstract	The IEEE Std 1722.1™-2013 AECP SUCCESS status code.
	 */
	AVB17221AECPStatusSuccess											= 0x00,
	/*!
		@constant	AVB17221AECPStatusNotImplemented
		@abstract	The IEEE Std 1722.1™-2013 AECP NOT_IMPLEMENTED status code.
	 */
	AVB17221AECPStatusNotImplemented									= 0x01,
	
	/*!
		@constant	AVB17221AECPStatusNoSuchDescriptor
		@abstract	The IEEE Std 1722.1™-2013 AECP AEM NO_SUCH_DESCRIPTOR status code.
	 */
	AVB17221AECPStatusNoSuchDescriptor									= 0x02,
	/*!
		@constant	AVB17221AECPStatusEntityLocked
		@abstract	The IEEE Std 1722.1™-2013 AECP AEM ENTITY_LOCKED status code.
	 */
	AVB17221AECPStatusEntityLocked										= 0x03,
	/*!
		@constant	AVB17221AECPStatusEntityAcquired
		@abstract	The IEEE Std 1722.1™-2013 AECP AEM ENTITY_ACQUIRED status code.
	 */
	AVB17221AECPStatusEntityAcquired									= 0x04,
	/*!
		@constant	AVB17221AECPStatusNotAuthorized
		@abstract	The IEEE Std 1722.1™-2013 AECP AEM NOT_AUTHORIZED status code.
	 */
	AVB17221AECPStatusNotAuthorized										= 0x05,
	/*!
		@constant	AVB17221AECPStatusInsufficientPrivileges
		@abstract	The IEEE Std 1722.1™-2013 AECP AEM INSUFFICIENT_PRIVILEGES status code.
	 */
	AVB17221AECPStatusInsufficientPrivileges							= 0x06,
	/*!
		@constant	AVB17221AECPStatusBadArguments
		@abstract	The IEEE Std 1722.1™-2013 AECP AEM BAD_ARGUMENTS status code.
	 */
	AVB17221AECPStatusBadArguments										= 0x07,
	/*!
		@constant	AVB17221AECPStatusNoResources
		@abstract	The IEEE Std 1722.1™-2013 AECP AEM NO_RESOURCES status code.
	 */
	AVB17221AECPStatusNoResources										= 0x08,
	/*!
		@constant	AVB17221AECPStatusInProgress
		@abstract	The IEEE Std 1722.1™-2013 AECP AEM IN_PROGRESS status code.
	 */
	AVB17221AECPStatusInProgress										= 0x09,
	/*!
	 @constant	AVB17221AECPStatusEntityMisbehaving
	 @abstract	The IEEE Std 1722.1™-2013 AECP AEM ENTITY_MISBEHAVING status code.
	 */
	AVB17221AECPStatusEntityMisbehaving									= 0x0a,
	/*!
	 @constant	AVB17221AECPStatusNotSupported
	 @abstract	The IEEE Std 1722.1™-2013 AECP AEM NOT_SUPPORTED status code.
	 */
	AVB17221AECPStatusNotSupported										= 0x0b,
	/*!
	 @constant	AVB17221AECPStatusStreamIsRunning
	 @abstract	The IEEE Std 1722.1™-2013 AECP AEM STREAM_IS_RUNNING status code.
	 */
	AVB17221AECPStatusStreamIsRunning									= 0x0c,

	/*!
		@constant	AVB17221AECPStatusAddressAccessAddressTooLow
		@abstract	The IEEE Std 1722.1™-2013 AECP ADDRESS_ACCESS_ADDRESS_TOO_LOW status code.
	 */
	AVB17221AECPStatusAddressAccessAddressTooLow						= 0x02,
	/*!
		@constant	AVB17221AECPStatusAddressAccessAddressTooHigh
		@abstract	The IEEE Std 1722.1™-2013 AECP ADDRESS_ACCESS_ADDRESS_TOO_HIGH status code.
	 */
	AVB17221AECPStatusAddressAccessAddressTooHigh						= 0x03,
	/*!
		@constant	AVB17221AECPStatusAddressAccessAddressInvalid
		@abstract	The IEEE Std 1722.1™-2013 AECP ADDRESS_ACCESS_ADDRESS_INVALID status code.
	 */
	AVB17221AECPStatusAddressAccessAddressInvalid						= 0x04,
	/*!
		@constant	AVB17221AECPStatusAddressAccessTLVInvalid
		@abstract	The IEEE Std 1722.1™-2013 AECP ADDRESS_ACCESS_TLV_INVALID status code.
	 */
	AVB17221AECPStatusAddressAccessTLVInvalid							= 0x05,
	/*!
		@constant	AVB17221AECPStatusAddressAccessDataInvalid
		@abstract	The IEEE Std 1722.1™-2013 AECP ADDRESS_ACCESS_DATA_INVALID status code.
	 */
	AVB17221AECPStatusAddressAccessDataInvalid							= 0x06,
	/*!
		@constant	AVB17221AECPStatusAddressAccessUnsupported
		@abstract	The IEEE Std 1722.1™-2013 AECP ADDRESS_ACCESS_UNSUPPORTED status code.
	 */
	AVB17221AECPStatusAddressAccessUnsupported							= 0x07,

	/*!
		@constant	AVB17221AECPStatusAVCFailure
		@abstract	The IEEE Std 1722.1™-2013 AECP AVC FAILURE status code.
	 */
	AVB17221AECPStatusAVCFailure										= 0x02,
} NS_ENUM_AVAILABLE(10_8, NA);

typedef NS_ENUM(uint8_t, AVB17221ACMPMessageType)
{
	/*!
		@constant	AVB17221ACMPMessageTypeConnectTXCommand
		@abstract	The IEEE Std 1722.1™-2013 ACMP CONNECT_TX_COMMAND message type.
	 */
	AVB17221ACMPMessageTypeConnectTXCommand								= 0x0,
	/*!
		@constant	AVB17221ACMPMessageTypeConnectTXResponse
		@abstract	The IEEE Std 1722.1™-2013 ACMP CONNECT_TX_RESPONSE message type.
	 */
	AVB17221ACMPMessageTypeConnectTXResponse							= 0x1,
	/*!
		@constant	AVB17221ACMPMessageTypeDisconnectTXCommand
		@abstract	The IEEE Std 1722.1™-2013 ACMP DISCONNECT_TX_COMMAND message type.
	 */
	AVB17221ACMPMessageTypeDisconnectTXCommand							= 0x2,
	/*!
		@constant	AVB17221ACMPMessageTypeDisconnectTXResponse
		@abstract	The IEEE Std 1722.1™-2013 ACMP DISCONNECT_TX_RESPONSE message type.
	 */
	AVB17221ACMPMessageTypeDisconnectTXResponse							= 0x3,
	/*!
		@constant	AVB17221ACMPMessageTypeGetTXStateCommand
		@abstract	The IEEE Std 1722.1™-2013 ACMP GET_TX_STATE_COMMAND message type.
	 */
	AVB17221ACMPMessageTypeGetTXStateCommand							= 0x4,
	/*!
		@constant	AVB17221ACMPMessageTypeGetTXStateResponse
		@abstract	The IEEE Std 1722.1™-2013 ACMP GET_TX_STATE_RESPONSE message type.
	 */
	AVB17221ACMPMessageTypeGetTXStateResponse							= 0x5,
	/*!
		@constant	AVB17221ACMPMessageTypeConnectRXCommand
		@abstract	The IEEE Std 1722.1™-2013 ACMP CONNECT_RX_COMMAND message type.
	 */
	AVB17221ACMPMessageTypeConnectRXCommand								= 0x6,
	/*!
		@constant	AVB17221ACMPMessageTypeConnectRXResponse
		@abstract	The IEEE Std 1722.1™-2013 ACMP CONNECT_RX_RESPONSE message type.
	 */
	AVB17221ACMPMessageTypeConnectRXResponse							= 0x7,
	/*!
		@constant	AVB17221ACMPMessageTypeDisconnectRXCommand
		@abstract	The IEEE Std 1722.1™-2013 ACMP DISCONNECT_RX_COMMAND message type.
	 */
	AVB17221ACMPMessageTypeDisconnectRXCommand							= 0x8,
	/*!
		@constant	AVB17221ACMPMessageTypeDisconnectRXResponse
		@abstract	The IEEE Std 1722.1™-2013 ACMP DISCONNECT_RX_RESPONSE message type.
	 */
	AVB17221ACMPMessageTypeDisconnectRXResponse							= 0x9,
	/*!
		@constant	AVB17221ACMPMessageTypeGetRXStateCommand
		@abstract	The IEEE Std 1722.1™-2013 ACMP GET_RX_STATE_COMMAND message type.
	 */
	AVB17221ACMPMessageTypeGetRXStateCommand							= 0xA,
	/*!
		@constant	AVB17221ACMPMessageTypeGetRXStateResponse
		@abstract	The IEEE Std 1722.1™-2013 ACMP GET_RX_STATE_RESPONSE message type.
	 */
	AVB17221ACMPMessageTypeGetRXStateResponse							= 0xB,
	/*!
		@constant	AVB17221ACMPMessageTypeGetTXConnectionCommand
		@abstract	The IEEE Std 1722.1™-2013 ACMP GET_TX_CONNECTION_COMMAND message type.
	 */
	AVB17221ACMPMessageTypeGetTXConnectionCommand						= 0xC,
	/*!
		@constant	AVB17221ACMPMessageTypeGetTXConnectionResponse
		@abstract	The IEEE Std 1722.1™-2013 ACMP GET_TX_CONNECTION_RESPONSE message type.
	 */
	AVB17221ACMPMessageTypeGetTXConnectionResponse						= 0xD,
} NS_ENUM_AVAILABLE(10_8, NA);

typedef NS_ENUM(uint8_t, AVB17221ACMPStatusCode)
{
	/*!
		@constant	AVB17221ACMPStatusSuccess
		@abstract	The IEEE Std 1722.1™-2013 ACMP SUCCESS status code.
	 */
	AVB17221ACMPStatusSuccess											= 0x00,
	/*!
		@constant	AVB17221ACMPStatusListenerUnknownID
		@abstract	The IEEE Std 1722.1™-2013 ACMP LISTENER_UNKNOWN_ID status code.
	 */
	AVB17221ACMPStatusListenerUnknownID									= 0x01,
	/*!
		@constant	AVB17221ACMPStatusTalkerUnknownID
		@abstract	The IEEE Std 1722.1™-2013 ACMP TALKER_UNKNOWN_ID status code.
	 */
	AVB17221ACMPStatusTalkerUnknownID									= 0x02,
	/*!
		@constant	AVB17221ACMPStatusTalkerDestMACFail
		@abstract	The IEEE Std 1722.1™-2013 ACMP TALKER_DEST_MAC_FAIL status code.
	 */
	AVB17221ACMPStatusTalkerDestMACFail									= 0x03,
	/*!
		@constant	AVB17221ACMPStatusTalkerNoStreamIndex
		@abstract	The IEEE Std 1722.1™-2013 ACMP TALKER_NO_STREAM_INDEX status code.
	 */
	AVB17221ACMPStatusTalkerNoStreamIndex								= 0x04,
	/*!
		@constant	AVB17221ACMPStatusTalkerNoBandwidth
		@abstract	The IEEE Std 1722.1™-2013 ACMP TALKER_NO_BANDWIDTH status code.
	 */
	AVB17221ACMPStatusTalkerNoBandwidth									= 0x05,
	/*!
		@constant	AVB17221ACMPStatusTalkerExclusive
		@abstract	The IEEE Std 1722.1™-2013 ACMP TALKER_EXCLUSIVE status code.
	 */
	AVB17221ACMPStatusTalkerExclusive									= 0x06,
	/*!
		@constant	AVB17221ACMPStatusListenerTalkerTimeout
		@abstract	The IEEE Std 1722.1™-2013 ACMP LISTENER_TALKER_TIMEOUT status code.
	 */
	AVB17221ACMPStatusListenerTalkerTimeout								= 0x07,
	/*!
		@constant	AVB17221ACMPStatusListenerExclusive
		@abstract	The IEEE Std 1722.1™-2013 ACMP LISTENER_EXCLUSIVE status code.
	 */
	AVB17221ACMPStatusListenerExclusive									= 0x08,
	/*!
		@constant	AVB17221ACMPStatusStateUnavailable
		@abstract	The IEEE Std 1722.1™-2013 ACMP STATE_UNAVAILABLE status code.
	 */
	AVB17221ACMPStatusStateUnavailable									= 0x09,
	/*!
		@constant	AVB17221ACMPStatusNotConnected
		@abstract	The IEEE Std 1722.1™-2013 ACMP NOT_CONNECTED status code.
	 */
	AVB17221ACMPStatusNotConnected										= 0x0a,
	/*!
		@constant	AVB17221ACMPStatusNoSuchConnection
		@abstract	The IEEE Std 1722.1™-2013 ACMP NO_SUCH_CONNECTION status code.
	 */
	AVB17221ACMPStatusNoSuchConnection									= 0x0b,
	/*!
		@constant	AVB17221ACMPStatusUnableToSendMessage
		@abstract	The IEEE Std 1722.1™-2013 ACMP COULD_NOT_SEND_MESSAGE status code.
	 */
	AVB17221ACMPStatusUnableToSendMessage								= 0x0c,
	/*!
		@constant	AVB17221ACMPStatusTalkerMisbehaving
		@abstract	The IEEE Std 1722.1™-2013 ACMP TALKER_MISBEHAVING status code.
	 */
	AVB17221ACMPStatusTalkerMisbehaving									= 0x0d,
	/*!
		@constant	AVB17221ACMPStatusListenerMisbehaving
		@abstract	The IEEE Std 1722.1™-2013 ACMP LISTENER_MISBEHAVING status code.
	 */
	AVB17221ACMPStatusListenerMisbehaving								= 0x0e,
	/*!
		@constant	AVB17221ACMPStatusSRPFace
		@abstract	The IEEE Std 1722.1™-2013 ACMP SRP_FACE status code.
	 */
	AVB17221ACMPStatusSRPFace											= 0x0f,
	/*!
		@constant	AVB17221ACMPStatusControllerNotAuthorized
		@abstract	The IEEE Std 1722.1™-2013 ACMP CONTROLLER_NOT_AUTHORIZED status code.
	 */
	AVB17221ACMPStatusControllerNotAuthorized							= 0x10,
	/*!
		@constant	AVB17221ACMPStatusIncompatibleRequest
		@abstract	The IEEE Std 1722.1™-2013 ACMP INCOMPATIBLE_REQUEST status code.
	 */
	AVB17221ACMPStatusIncompatibleRequest								= 0x11,
	/*!
		@constant	AVB17221ACMPStatusNotSupported
		@abstract	The IEEE Std 1722.1™-2013 ACMP NOT_SUPPORTED status code.
	 */
	AVB17221ACMPStatusNotSupported										= 0x1f,
} NS_ENUM_AVAILABLE(10_8, NA);

typedef NS_OPTIONS(uint16_t, AVB17221ACMPFlags)
{
	/*!
		@constant	AVB17221ACMPFlagsNone
		@abstract	The IEEE Std 1722.1™-2013 ACMP no flags.
	 */
	AVB17221ACMPFlagsNone												= 0x0000,
	/*!
		@constant	AVB17221ACMPFlagsClassB
		@abstract	The IEEE Std 1722.1™-2013 ACMP CLASS_B flag.
	 */
	AVB17221ACMPFlagsClassB												= 0x0001,
	/*!
		@constant	AVB17221ACMPFlagsFastConnect
		@abstract	The IEEE Std 1722.1™-2013 ACMP FAST_CONNECT flag.
	 */
	AVB17221ACMPFlagsFastConnect										= 0x0002,
	/*!
		@constant	AVB17221ACMPFlagsSavedState
		@abstract	The IEEE Std 1722.1™-2013 ACMP SAVED_STATE flag.
	 */
	AVB17221ACMPFlagsSavedState											= 0x0004,
	/*!
		@constant	AVB17221ACMPFlagsStreamingWait
		@abstract	The IEEE Std 1722.1™-2013 ACMP STREAMING_WAIT flag.
	 */
	AVB17221ACMPFlagsStreamingWait										= 0x0008,
	/*!
	 @constant	AVB17221ACMPFlagsSupportsEncrypted
	 @abstract	The IEEE Std 1722.1™-2013 ACMP SUPPORTS_ENCRYPTED flag.
	 */
	AVB17221ACMPFlagsSupportsEncrypted									= 0x0010,
	/*!
	 @constant	AVB17221ACMPFlagsEncryptedPDU
	 @abstract	The IEEE Std 1722.1™-2013 ACMP ENCRYPTED_PDU flag.
	 */
	AVB17221ACMPFlagsEncryptedPDU										= 0x0020,
	/*!
	 @constant	AVB17221ACMPFlagsStreamingTalkerFailed
	 @abstract	The IEEE Std 1722.1™-2013 ACMP TALKER_FAILED flag.
	 */
	AVB17221ACMPFlagsStreamingTalkerFailed								= 0x0040,
} NS_ENUM_AVAILABLE(10_8, NA);

typedef NS_ENUM(uint16_t, AVB17221AEMCommandType)
{
	/*!
		@constant	AVB17221AEMCommandTypeAcquireEntity
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM ACQUIRE_ENTITY command.
	 */
	AVB17221AEMCommandTypeAcquireEntity									= 0x0000,
	/*!
		 @constant	AVB17221AEMCommandTypeLockEntity
		 @abstract	The command code for the IEEE Std 1722.1™-2013 AEM LOCK_ENTITY command.
	 */
	AVB17221AEMCommandTypeLockEntity									= 0x0001,
	/*!
		@constant	AVB17221AEMCommandTypeEntityAvailable
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM ENTITY_AVAILABLE command.
	 */
	AVB17221AEMCommandTypeEntityAvailable								= 0x0002,
	/*!
		@constant	AVB17221AEMCommandTypeControllerAvailable
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM CONTROLLER_AVAILABLE command.
	 */
	AVB17221AEMCommandTypeControllerAvailable							= 0x0003,
	/*!
		@constant	AVB17221AEMCommandTypeReadDescriptor
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM READ_DESCRIPTOR command.
	 */
	AVB17221AEMCommandTypeReadDescriptor								= 0x0004,
	/*!
		@constant	AVB17221AEMCommandTypeWriteDescriptor
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM WRITE_DESCRIPTOR command.
	 */
	AVB17221AEMCommandTypeWriteDescriptor								= 0x0005,
	/*!
		@constant	AVB17221AEMCommandTypeSetConfiguration
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_CONFIGURATION command.
	 */
	AVB17221AEMCommandTypeSetConfiguration								= 0x0006,
	/*!
		@constant	AVB17221AEMCommandTypeGetConfiguration
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_CONFIGURATION command.
	 */
	AVB17221AEMCommandTypeGetConfiguration								= 0x0007,
	/*!
		@constant	AVB17221AEMCommandTypeSetStreamFormat
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_STREAM_FORMAT command.
	 */
	AVB17221AEMCommandTypeSetStreamFormat								= 0x0008,
	/*!
		@constant	AVB17221AEMCommandTypeGetStreamFormat
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_STREAM_FORMAT command.
	 */
	AVB17221AEMCommandTypeGetStreamFormat								= 0x0009,
	/*!
		@constant	AVB17221AEMCommandTypeSetVideoFormat
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_VIDEO_FORMAT command.
	 */
	AVB17221AEMCommandTypeSetVideoFormat								= 0x000a,
	/*!
		@constant	AVB17221AEMCommandTypeGetVideoFormat
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_VIDEO_FORMAT command.
	 */
	AVB17221AEMCommandTypeGetVideoFormat								= 0x000b,
	/*!
		@constant	AVB17221AEMCommandTypeSetSensorFormat
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_SENSOR_FORMAT command.
	 */
	AVB17221AEMCommandTypeSetSensorFormat								= 0x000c,
	/*!
		@constant	AVB17221AEMCommandTypeGetSensorFormat
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_SENSOR_FORMAT command.
	 */
	AVB17221AEMCommandTypeGetSensorFormat								= 0x000d,
	/*!
		@constant	AVB17221AEMCommandTypeSetStreamInfo
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_STREAM_INFO command.
	 */
	AVB17221AEMCommandTypeSetStreamInfo									= 0x000e,
	/*!
		@constant	AVB17221AEMCommandTypeGetStreamInfo
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_STREAM_INFO command.
	 */
	AVB17221AEMCommandTypeGetStreamInfo									= 0x000f,
	/*!
		@constant	AVB17221AEMCommandTypeSetName
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_NAME command.
	 */
	AVB17221AEMCommandTypeSetName										= 0x0010,
	/*!
		@constant	AVB17221AEMCommandTypeGetName
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_NAME command.
	 */
	AVB17221AEMCommandTypeGetName										= 0x0011,
	/*!
		@constant	AVB17221AEMCommandTypeSetAssociationID
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_ASSOCIATION_ID command.
	 */
	AVB17221AEMCommandTypeSetAssociationID								= 0x0012,
	/*!
		@constant	AVB17221AEMCommandTypeGetAssociationID
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_ASSOCIATION_ID command.
	 */
	AVB17221AEMCommandTypeGetAssociationID								= 0x0013,
	/*!
		@constant	AVB17221AEMCommandTypeSetSamplingRate
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_SAMPLING_RATE command.
	 */
	AVB17221AEMCommandTypeSetSamplingRate								= 0x0014,
	/*!
		@constant	AVB17221AEMCommandTypeGetSamplingRate
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_SAMPLING_RATE command.
	 */
	AVB17221AEMCommandTypeGetSamplingRate								= 0x0015,
	/*!
		@constant	AVB17221AEMCommandTypeSetClockSource
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_CLOCK_SOURCE command.
	 */
	AVB17221AEMCommandTypeSetClockSource								= 0x0016,
	/*!
		@constant	AVB17221AEMCommandTypeGetClockSource
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_CLOCK_SOURCE command.
	 */
	AVB17221AEMCommandTypeGetClockSource								= 0x0017,
	/*!
		@constant	AVB17221AEMCommandTypeSetControl
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_CONTROL command.
	 */
	AVB17221AEMCommandTypeSetControl									= 0x0018,
	/*!
		@constant	AVB17221AEMCommandTypeGetControl
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_CONTROL command.
	 */
	AVB17221AEMCommandTypeGetControl									= 0x0019,
	/*!
		@constant	AVB17221AEMCommandTypeIncrementControlValue
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM INCREMENT_CONTROL_VALUE command.
	 */
	AVB17221AEMCommandTypeIncrementControl								= 0x001a,
	/*!
		@constant	AVB17221AEMCommandTypeDecrementControlValue
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM DECREMENT_CONTROL_VALIE command.
	 */
	AVB17221AEMCommandTypeDecrementControl								= 0x001b,
	/*!
		@constant	AVB17221AEMCommandTypeSetSignalSelector
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_SIGNAL_SELECTOR command.
	 */
	AVB17221AEMCommandTypeSetSignalSelector								= 0x001c,
	/*!
		@constant	AVB17221AEMCommandTypeGetSignalSelector
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_SIGNAL_SELECTOR command.
	 */
	AVB17221AEMCommandTypeGetSignalSelector								= 0x001d,
	/*!
		@constant	AVB17221AEMCommandTypeSetMixer
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_MIXER command.
	 */
	AVB17221AEMCommandTypeSetMixer										= 0x001e,
	/*!
		@constant	AVB17221AEMCommandTypeGetMixer
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_MIXER command.
	 */
	AVB17221AEMCommandTypeGetMixer										= 0x001f,
	/*!
		@constant	AVB17221AEMCommandTypeSetMatrix
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_MATRIX command.
	 */
	AVB17221AEMCommandTypeSetMatrix										= 0x0020,
	/*!
		@constant	AVB17221AEMCommandTypeGetMatrix
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_MATRIX command.
	 */
	AVB17221AEMCommandTypeGetMatrix										= 0x0021,
	/*!
		@constant	AVB17221AEMCommandTypeStartStreaming
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM START_STREAMING command.
	 */
	AVB17221AEMCommandTypeStartStreaming								= 0x0022,
	/*!
		@constant	AVB17221AEMCommandTypeStopStreaming
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM STOP_STREAMING command.
	 */
	AVB17221AEMCommandTypeStopStreaming									= 0x0023,
	/*!
		@constant	AVB17221AEMCommandTypeRegisterUnsolicitedNotification
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM REGISTER_UNSOLICITED_NOTIFICATION command.
	 */
	AVB17221AEMCommandTypeRegisterUnsolicitedNotification				= 0x0024,
	/*!
		@constant	AVB17221AEMCommandTypeDeregisterUnsolicitedNotification
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM DEREGISTER_UNSOLICITED_NOTIFICATION command.
	 */
	AVB17221AEMCommandTypeDeregisterUnsolicitedNotification				= 0x0025,
	/*!
		@constant	AVB17221AEMCommandTypeIdentifyNotification
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM IDENTIFY_NOTIFICATION command.
	 */
	AVB17221AEMCommandTypeIdentifyNotification							= 0x0026,
	/*!
		@constant	AVB17221AEMCommandTypeGetAVBInfo
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_AVB_INFO command.
	 */
	AVB17221AEMCommandTypeGetAVBInfo									= 0x0027,
	/*!
		@constant	AVB17221AEMCommandTypeGetASPath
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_AS_PATH command.
	 */
	AVB17221AEMCommandTypeGetASPath										= 0x0028,
	/*!
		@constant	AVB17221AEMCommandTypeGetCounters
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_COUNTERS command.
	 */
	AVB17221AEMCommandTypeGetCounters									= 0x0029,
	/*!
		@constant	AVB17221AEMCommandTypeReboot
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM REBOOT command.
	 */
	AVB17221AEMCommandTypeReboot										= 0x002a,
	/*!
		@constant	AVB17221AEMCommandTypeGetAudioMap
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_AUDIO_MAP command.
	 */
	AVB17221AEMCommandTypeGetAudioMap									= 0x002b,
	/*!
		@constant	AVB17221AEMCommandTypeAddAudioMapping
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM ADD_AUDIO_MAPPING command.
	 */
	AVB17221AEMCommandTypeAddAudioMapping								= 0x002c,
	/*!
		@constant	AVB17221AEMCommandTypeRemoveAudioMapping
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM REMOVE_AUDIO_MAPPING command.
	 */
	AVB17221AEMCommandTypeRemoveAudioMapping							= 0x002d,
	/*!
		@constant	AVB17221AEMCommandTypeGetVideoMap
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_VIDEO_MAP command.
	 */
	AVB17221AEMCommandTypeGetVideoMap									= 0x002e,
	/*!
		@constant	AVB17221AEMCommandTypeAddVideoMapping
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM ADD_VIDEO_MAPPING command.
	 */
	AVB17221AEMCommandTypeAddVideoMapping								= 0x002f,
	/*!
		@constant	AVB17221AEMCommandTypeRemoveVideoMapping
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM REMOVE_VIDEO_MAPPING command.
	 */
	AVB17221AEMCommandTypeRemoveVideoMapping							= 0x0030,
	/*!
		@constant	AVB17221AEMCommandTypeGetSensorMap
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_SENSOR_MAP command.
	 */
	AVB17221AEMCommandTypeGetSensorMap									= 0x0031,
	/*!
		@constant	AVB17221AEMCommandTypeAddSensorMapping
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM ADD_SENSOR_MAPPING command.
	 */
	AVB17221AEMCommandTypeAddSensorMapping								= 0x0032,
	/*!
		@constant	AVB17221AEMCommandTypeRemoveSensorMapping
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM REMOVE_SENSOR_MAPPING command.
	 */
	AVB17221AEMCommandTypeRemoveSensorMapping							= 0x0033,
	/*!
		@constant	AVB17221AEMCommandTypeStartOperation
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM START_OPERATION command.
	 */
	AVB17221AEMCommandTypeStartOperation								= 0x0034,
	/*!
		@constant	AVB17221AEMCommandTypeAbortOperation
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM ABORT_OPERATION command.
	 */
	AVB17221AEMCommandTypeAbortOperation								= 0x0035,
	/*!
		@constant	AVB17221AEMCommandTypeOperationStatus
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM OPERATION_STATUS command.
	 */
	AVB17221AEMCommandTypeOperationStatus								= 0x0036,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateAddKey
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_ADD_KEY command.
	 */
	AVB17221AEMCommandTypeAuthenticateAddKey							= 0x0037,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateDeleteKey
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_DELETE_KEY command.
	 */
	AVB17221AEMCommandTypeAuthenticateDeleteKey							= 0x0038,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateGetKeyList
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_GET_KEY_LIST command.
	 */
	AVB17221AEMCommandTypeAuthenticateGetKeyList						= 0x0039,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateGetKey
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_GET_KEY command.
	 */
	AVB17221AEMCommandTypeAuthenticateGetKey							= 0x003a,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateAddKeyToChain
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_ADD_KEY_TO_CHAIN command.
	 */
	AVB17221AEMCommandTypeAuthenticateAddKeyToChain						= 0x003b,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateDeleteKeyFromChain
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_DELETE_KEY_FROM_CHAIN command.
	 */
	AVB17221AEMCommandTypeAuthenticateDeleteKeyFromChain				= 0x003c,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateGetKeychainList
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_GET_KEYCHAIN_LIST command.
	 */
	AVB17221AEMCommandTypeAuthenticateGetKeychainList					= 0x003d,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateGetIdentity
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_GET_IDENTITY command.
	 */
	AVB17221AEMCommandTypeAuthenticateGetIdentity						= 0x003e,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateAddToken
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_ADD_TOKEN command.
	 */
	AVB17221AEMCommandTypeAuthenticateAddToken							= 0x003f,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticateDeleteToken
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTH_DELETE_TOKEN command.
	 */
	AVB17221AEMCommandTypeAuthenticateDeleteToken						= 0x0040,
	/*!
		@constant	AVB17221AEMCommandTypeAuthenticate
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM AUTHENTICATE command.
	 */
	AVB17221AEMCommandTypeAuthenticate									= 0x0041,
	/*!
		@constant	AVB17221AEMCommandTypeDeauthenticate
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM DEAUTHENTICATE command.
	 */
	AVB17221AEMCommandTypeDeauthenticate								= 0x0042,
	/*!
		@constant	AVB17221AEMCommandTypeEnableTransportSecurity
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM ENABLE_TRANSPORT_SECURITY command.
	 */
	AVB17221AEMCommandTypeEnableTransportSecurity						= 0x0043,
	/*!
		@constant	AVB17221AEMCommandTypeDisableTransportSecurity
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM DISABLE_TRANSPORT_SECURITY command.
	 */
	AVB17221AEMCommandTypeDisableTransportSecurity						= 0x0044,
	/*!
		@constant	AVB17221AEMCommandTypeEnableStreamEncryption
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM ENABLE_STREAM_ENCRYPTION command.
	 */
	AVB17221AEMCommandTypeEnableStreamEncryption						= 0x0045,
	/*!
		@constant	AVB17221AEMCommandTypeDisableStreamEncryption
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM DISABLE_STREAM_ENCRYPTION command.
	 */
	AVB17221AEMCommandTypeDisableStreamEncryption						= 0x0046,
	/*!
		@constant	AVB17221AEMCommandTypeSetMemoryObjectLength
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_MEMORY_OBJECT_LENGTH command.
	 */
	AVB17221AEMCommandTypeSetMemoryObjectLength							= 0x0047,
	/*!
		@constant	AVB17221AEMCommandTypeGetMemoryObjectLength
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_MEMORY_OBJECT_LENGTH command.
	 */
	AVB17221AEMCommandTypeGetMemoryObjectLength							= 0x0048,
	/*!
		@constant	AVB17221AEMCommandTypeSetStreamBackup
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM SET_STREAM_BACKUP command.
	 */
	AVB17221AEMCommandTypeSetStreamBackup								= 0x0049,
	/*!
		@constant	AVB17221AEMCommandTypeGetStreamBackup
		@abstract	The command code for the IEEE Std 1722.1™-2013 AEM GET_STREAM_BACKUP command.
	 */
	AVB17221AEMCommandTypeGetStreamBackup								= 0x004a,
} NS_ENUM_AVAILABLE(10_8, NA);


typedef NS_ENUM(uint8_t, AVB17221AECPAddressAccessTLVMode)
{
	/*!
	 @constant	AVB17221AECPAddressAccessTLVModeRead
	 @abstract	The IEEE Std 1722.1™-2013 ACMP SUCCESS status code.
	 */
	AVB17221AECPAddressAccessTLVModeRead								= 0x00,
	/*!
	 @constant	AVB17221AECPAddressAccessTLVModeWrite
	 @abstract	The IEEE Std 1722.1™-2013 ACMP LISTENER_UNKNOWN_ID status code.
	 */
	AVB17221AECPAddressAccessTLVModeWrite								= 0x01,
	/*!
	 @constant	AVB17221AECPAddressAccessTLVModeExecute
	 @abstract	The IEEE Std 1722.1™-2013 ACMP TALKER_UNKNOWN_ID status code.
	 */
	AVB17221AECPAddressAccessTLVModeExecute									= 0x02,
} NS_ENUM_AVAILABLE(10_9, NA);

/*!
	@constant	AVBErrorDomain
	@abstract	The string defining the error domain for AudioVideoBridging errors.
 */
FOUNDATION_EXPORT NSString * const AVBErrorDomain;

NS_ASSUME_NONNULL_END

#endif
