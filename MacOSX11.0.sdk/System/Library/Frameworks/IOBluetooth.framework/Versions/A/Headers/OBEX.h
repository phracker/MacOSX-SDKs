/*
	File:		OBEX.h
	Contains:	Technology interfaces for OBEX.
	Copyright:	(c) 2010 by Apple, Inc. All rights reserved.
*/

#pragma once

#import <stdio.h>
#import <stdint.h>

#import <CoreServices/CoreServices.h>
#import <IOBluetooth/IOBluetoothUserLib.h>

//---------------------------------------------------------------------------------------------------------------------------
/*!	@header		OBEX
	@abstract	Public OBEX technology interfaces.	
	@discussion	Contains generic OBEX constants, structs, and C API used for all OBEX communication over any transport.
				For specific transport API, see that transport's C API. For example, if you wanted to know more about the
				Bluetooth OBEX implementation, see OBEXBluetooth.h.
				
				The file also contains API that will assist in the construction and deconstruction of OBEX headers to
				and from raw bytes, as well as the creation of vCards and vEvents.
*/

#if 0
#pragma mark ======= OBEX.h =======
#endif


#ifdef	__cplusplus
	extern "C" {
#endif


//===========================================================================================================================
//	OBEXErrorCodes
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark ======= OBEXErrorCodes =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXErrorCodes
	@abstract	Codes for OBEX errors. If the return value was not in the following range, then it is most likely resulting
				from kernel code/IOKit, and you should consult IOReturn.h for those codes.
	@constant	kOBEXErrorRangeMin				Minimum value in OBEX error range.
	@constant	kOBEXErrorRangeMax				Maximum value in OBEX error range.
	
*/

typedef int32_t	OBEXError;
enum OBEXErrorCodes
{
	kOBEXErrorRangeMin					= -21850,
	kOBEXErrorRangeMax					= -21899,
	
	kOBEXSuccess						= 0,			// Success at whatever you were attempting.
	kOBEXGeneralError					= -21850,		// Catch all for misc. errors.
	kOBEXNoResourcesError				= -21851,		// An allocation failed, etc.
	kOBEXUnsupportedError				= -21852,		// operation or item is not supported.
	kOBEXInternalError					= -21853,		// A problem has occurred in our internal code.
	kOBEXBadArgumentError				= -21854,		// A bad argument was passed to an OBEX function.
	kOBEXTimeoutError					= -21855,		// timeout error
	kOBEXBadRequestError				= -21856,		// bad request error
	kOBEXCancelledError					= -21857,
	kOBEXForbiddenError					= -21858,		// operation was not allowed on remote device (wrong permissions, etc.).
	
	kOBEXUnauthorizedError				= -21859,		// Unauthorized
	kOBEXNotAcceptableError				= -21860,		// Not Acceptable
	kOBEXConflictError					= -21861,		// Conflict
	kOBEXMethodNotAllowedError			= -21862,		// Method not allowed
	kOBEXNotFoundError					= -21863,		// File/Folder not found
	kOBEXNotImplementedError			= -21864,		// Not Implemented
	kOBEXPreconditionFailedError		= -21865,		// Precondition failed
		
	kOBEXSessionBusyError				= -21875,		// Session is busy with a command already.
	kOBEXSessionNotConnectedError		= -21876,		// Session does not have an open connection.
	kOBEXSessionBadRequestError			= -21877,		// Whatever you are trying to do is invalid (trying to send more data than the max packet size supports, e.g.).
	kOBEXSessionBadResponseError		= -21878,		// The OBEX Server/client you are talking to has sent us a bad response (e.g. when a Connect Command was sent, we got back "0xA0", which is not correct).
	kOBEXSessionNoTransportError		= -21879,		// The underlying transport (Bluetooth, etc.) is not open/available.
	kOBEXSessionTransportDiedError		= -21880,		// The underlying transport connection (Bluetooth, etc.) died.
	kOBEXSessionTimeoutError			= -21881,		// Timeout occurred performing an operation.
	kOBEXSessionAlreadyConnectedError	= -21882		// Connection over OBEX already established (returned from OBEXConnect).
};

//===========================================================================================================================
//	OBEXMacros
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark ======= OBEXMacros =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*! @defineblock OBEX Convenience Macros
 *	Convenience Macros for OBEX Header Identifiers. The API should shield you from using these, they are included here to completeness.
 */

#define 	GET_HEADER_ID_IS_NULL_TERMINATED_UNICODE_TEXT( HEADER_ID )		( (HEADER_ID & 0xC0) == 0x00 )
#define 	GET_HEADER_ID_IS_BYTE_SEQUENCE( HEADER_ID )						( (HEADER_ID & 0xC0) == 0x40 )
#define 	GET_HEADER_ID_IS_1_BYTE_QUANTITY( HEADER_ID )					( (HEADER_ID & 0xC0) == 0x80 )
#define 	GET_HEADER_ID_IS_4_BYTE_QUANTITY( HEADER_ID )					( (HEADER_ID & 0xC0) == 0xC0 )
#define 	SET_HEADER_ID_IS_NULL_TERMINATED_UNICODE_TEXT( HEADER_ID )		( (HEADER_ID & 0x3F) )
#define 	SET_HEADER_ID_IS_BYTE_SEQUENCE( HEADER_ID )						( (HEADER_ID & 0x3F) | 0x40 )
#define 	SET_HEADER_ID_IS_1_BYTE_QUANTITY( HEADER_ID )					( (HEADER_ID & 0x3F) | 0x80 )
#define 	SET_HEADER_ID_IS_4_BYTE_QUANTITY( HEADER_ID )					( (HEADER_ID & 0x3F) | 0xC0 )
#define 	IS_RESPONSE_CODE_FINAL_BIT_SET( RESPONSE_CODE )					( RESPONSE_CODE >> 7L )
#define 	STRIP_RESPONSE_CODE_FINAL_BIT( RESPONSE_CODE )					( RESPONSE_CODE & 0x7F )
		
/*! @/defineblock */
		
//===========================================================================================================================
//	OBEXHeaderIdentifiers
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark ======= OBEXHeaderIdentifiers =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXHeaderIdentifiers
	@abstract	Identifiers for OBEX Headers.
	@constant	kOBEXHeaderIDName						Name of the object.  Null terminated unicode text.
	@constant	kOBEXHeaderIDDescription				Text description of the object. Null terminated unicode text.
	@constant	kOBEXHeaderIDReservedRangeStart			Range includes all combos of the upper 2 bits. Reserved.
	@constant	kOBEXHeaderIDReservedRangeEnd			Range includes all combos of the upper 2 bits. Reserved.
	@constant	kOBEXHeaderIDUserDefinedRangeStart		Range includes all combos of the upper 2 bits. User defined.
	@constant	kOBEXHeaderIDUserDefinedRangeEnd		Range includes all combos of the upper 2 bits. User defined.
	@constant	kOBEXHeaderIDType						Type of object - e.g. text, html, binary, etc. Null terminated ASCII text.
	@constant	kOBEXHeaderIDTimeISO					Date/time stamp - ISO8601 version of time. (YYYYMMDDTHHMMSSZ)
	@constant	kOBEXHeaderIDTarget						Name of service that operation is destined for.
	@constant	kOBEXHeaderIDHTTP						An HTTP 1.x header.
	@constant	kOBEXHeaderIDBody						A Chunk of the object body.
	@constant	kOBEXHeaderIDEndOfBody					The last checking of the object body.
	@constant	kOBEXHeaderIDWho						Identifies the OBEX applications, used to tell if talking to a peer.
	@constant	kOBEXHeaderIDAppParameters				Extended application request and resposnse info.
	@constant	kOBEXHeaderIDAuthorizationChallenge		Authentication digest-challenge.
	@constant	kOBEXHeaderIDAuthorizationResponse		Authentication digest-reponse.
	@constant	kOBEXHeaderIDObjectClass				OBEX Object - class of object.
	@constant	kOBEXHeaderIDCount						Number of objects (used in Connect command).
	@constant	kOBEXHeaderIDLength						The length of the object in bytes. 4 byte unsigned integer value.
	@constant	kOBEXHeaderIDTime4Byte					Date/time stamp - 4 byte version for compat. only. Seconds since Jan 1, 1970.
	@constant	kOBEXHeaderIDConnectionID				An identifier used for OBEX connection multiplexing.
	@constant	kOBEXHeaderIDOBEX13WANUUID					Used to provide state information when layering OBEX over stateless networks. 16byte UUID.
	@constant	kOBEXHeaderIDOBEX13ObjectClass				Used to reference the object class and properties. Byte Sequence.
	@constant	kOBEXHeaderIDOBEX13SessionParameters		Byte sequence required for CreateSession, CloseSession and other OBEX commands.
	@constant	kOBEXHeaderIDOBEX13SessionSequenceNumber	1-byte quantitied containing the current sequence number.
	@constant	kOBEXHeaderIDOBEX13CreatorID				4-byte unsigned integer that identifies the creator of the object.
*/

enum OBEXHeaderIdentifiers
{
	kOBEXHeaderIDName							= 0x01,
	kOBEXHeaderIDDescription					= 0x05,
	kOBEXHeaderIDReservedRangeStart				= 0x10,
	kOBEXHeaderIDReservedRangeEnd				= 0x2F,
	
	kOBEXHeaderIDUserDefinedRangeStart			= 0x30,
	kOBEXHeaderIDUserDefinedRangeEnd			= 0x3F,
	
	kOBEXHeaderIDType							= 0x42,
	kOBEXHeaderIDTimeISO						= 0x44,
	kOBEXHeaderIDTarget							= 0x46,
	kOBEXHeaderIDHTTP							= 0x47,
	kOBEXHeaderIDBody							= 0x48,
	kOBEXHeaderIDEndOfBody						= 0x49,
	kOBEXHeaderIDWho							= 0x4A,
	kOBEXHeaderIDAppParameters					= 0x4C,
	kOBEXHeaderIDAuthorizationChallenge			= 0x4D,
	kOBEXHeaderIDAuthorizationResponse			= 0x4E,
	kOBEXHeaderIDObjectClass					= 0x4F, /* OBEX 1.2 and prior specification only; note that there is another Object Class defined below; this is removed in the 1.3 specification */

	kOBEXHeaderIDCount							= 0xC0,
	kOBEXHeaderIDLength							= 0xC3,
	kOBEXHeaderIDTime4Byte						= 0xC4,
	kOBEXHeaderIDConnectionID					= 0xCB,

	/* OBEX 1.3 and later specification */
	
	kOBEXHeaderIDOBEX13WANUUID					= 0x50, 
	kOBEXHeaderIDOBEX13ObjectClass				= 0x51,
	kOBEXHeaderIDOBEX13SessionParameters		= 0x52,
	kOBEXHeaderIDOBEX13SessionSequenceNumber	= 0x93,
	kOBEXHeaderIDOBEX13CreatorID				= 0xCF,
	
	/* End OBEX 1.3 and later specification */
	
};

//===========================================================================================================================
//	OBEXOpCodeResponseValues
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXOpCodeCommandResponseValues =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXOpCodeResponseValues
	@abstract	Response opCode values.
*/

enum OBEXOpCodeResponseValues
{
	kOBEXResponseCodeReservedRangeStart						= 0x00,
	kOBEXResponseCodeReservedRangeEnd						= 0x0F,
	
	kOBEXResponseCodeContinue								= 0x10,
	kOBEXResponseCodeContinueWithFinalBit					= 0x90,
	kOBEXResponseCodeSuccess								= 0x20,
	kOBEXResponseCodeSuccessWithFinalBit					= 0xA0,
	kOBEXResponseCodeCreated								= 0x21,
	kOBEXResponseCodeCreatedWithFinalBit					= 0xA1,
	kOBEXResponseCodeAccepted								= 0x22,
	kOBEXResponseCodeAcceptedWithFinalBit					= 0xA2,
	kOBEXResponseCodeNonAuthoritativeInfo					= 0x23,
	kOBEXResponseCodeNonAuthoritativeInfoWithFinalBit		= 0xA3,
	kOBEXResponseCodeNoContent								= 0x24,
	kOBEXResponseCodeNoContentWithFinalBit					= 0xA4,
	kOBEXResponseCodeResetContent							= 0x25,
	kOBEXResponseCodeResetContentWithFinalBit				= 0xA5,
	kOBEXResponseCodePartialContent							= 0x26,
	kOBEXResponseCodePartialContentWithFinalBit				= 0xA6,
	
	kOBEXResponseCodeMultipleChoices						= 0x30,
	kOBEXResponseCodeMultipleChoicesWithFinalBit			= 0xB0,
	kOBEXResponseCodeMovedPermanently						= 0x31,
	kOBEXResponseCodeMovedPermanentlyWithFinalBit			= 0xB1,
	kOBEXResponseCodeMovedTemporarily						= 0x32,
	kOBEXResponseCodeMovedTemporarilyWithFinalBit			= 0xB2,
	kOBEXResponseCodeSeeOther								= 0x33,
	kOBEXResponseCodeSeeOtherWithFinalBit					= 0xB3,
	kOBEXResponseCodeNotModified							= 0x34,
	kOBEXResponseCodeNotModifiedWithFinalBit				= 0xB4,
	kOBEXResponseCodeUseProxy								= 0x35,
	kOBEXResponseCodeUseProxyWithFinalBit					= 0xB5,
	
	kOBEXResponseCodeBadRequest								= 0x40,
	kOBEXResponseCodeBadRequestWithFinalBit					= 0xC0,
	kOBEXResponseCodeUnauthorized							= 0x41,
	kOBEXResponseCodeUnauthorizedWithFinalBit				= 0xC1,
	kOBEXResponseCodePaymentRequired						= 0x42,
	kOBEXResponseCodePaymentRequiredWithFinalBit			= 0xC2,
	kOBEXResponseCodeForbidden								= 0x43,
	kOBEXResponseCodeForbiddenWithFinalBit					= 0xC3,
	kOBEXResponseCodeNotFound								= 0x44,
	kOBEXResponseCodeNotFoundWithFinalBit					= 0xC4,
	kOBEXResponseCodeMethodNotAllowed						= 0x45,
	kOBEXResponseCodeMethodNotAllowedWithFinalBit			= 0xC5,
	kOBEXResponseCodeNotAcceptable							= 0x46,
	kOBEXResponseCodeNotAcceptableWithFinalBit				= 0xC6,
	kOBEXResponseCodeProxyAuthenticationRequired			= 0x47,
	kOBEXResponseCodeProxyAuthenticationRequiredWithFinalBit= 0xC7,
	kOBEXResponseCodeRequestTimeOut							= 0x48,
	kOBEXResponseCodeRequestTimeOutWithFinalBit				= 0xC8,
	kOBEXResponseCodeConflict								= 0x49,
	kOBEXResponseCodeConflictWithFinalBit					= 0xC9,
	kOBEXResponseCodeGone									= 0x4A,
	kOBEXResponseCodeGoneWithFinalBit						= 0xCA,
	kOBEXResponseCodeLengthRequired							= 0x4B,
	kOBEXResponseCodeLengthRequiredFinalBit					= 0xCB,
	kOBEXResponseCodePreconditionFailed						= 0x4C,
	kOBEXResponseCodePreconditionFailedWithFinalBit			= 0xCC,
	kOBEXResponseCodeRequestedEntityTooLarge				= 0x4D,
	kOBEXResponseCodeRequestedEntityTooLargeWithFinalBit	= 0xCD,
	kOBEXResponseCodeRequestURLTooLarge						= 0x4E,
	kOBEXResponseCodeRequestURLTooLargeWithFinalBit			= 0xCE,
	kOBEXResponseCodeUnsupportedMediaType					= 0x4F,
	kOBEXResponseCodeUnsupportedMediaTypeWithFinalBit		= 0xCF,
	
	kOBEXResponseCodeInternalServerError					= 0x50,
	kOBEXResponseCodeInternalServerErrorWithFinalBit		= 0xD0,
	kOBEXResponseCodeNotImplemented							= 0x51,
	kOBEXResponseCodeNotImplementedWithFinalBit				= 0xD1,
	kOBEXResponseCodeBadGateway								= 0x52,
	kOBEXResponseCodeBadGatewayWithFinalBit					= 0xD2,
	kOBEXResponseCodeServiceUnavailable						= 0x53,
	kOBEXResponseCodeServiceUnavailableWithFinalBit			= 0xD3,
	kOBEXResponseCodeGatewayTimeout							= 0x54,
	kOBEXResponseCodeGatewayTimeoutWithFinalBit				= 0xD4,
	kOBEXResponseCodeHTTPVersionNotSupported				= 0x55,
	kOBEXResponseCodeHTTPVersionNotSupportedWithFinalBit	= 0xD5,
	
	kOBEXResponseCodeDatabaseFull							= 0x60,
	kOBEXResponseCodeDatabaseFullWithFinalBit				= 0xE0,
	kOBEXResponseCodeDatabaseLocked							= 0x61,
	kOBEXResponseCodeDatabaseLockedWithFinalBit				= 0xE1,
};

//===========================================================================================================================
//	OBEXOpCodeCommandValues
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXOpCodeCommandValues =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXOpCodeCommandValues
	@abstract	Operation OpCode values for commands.
*/

enum OBEXOpCodeCommandValues
{
	kOBEXOpCodeReserved					= 0x04,

	kOBEXOpCodeConnect					= 0x80,		// High bit always set.
	kOBEXOpCodeDisconnect				= 0x81,		// High bit always set.
	
	kOBEXOpCodePut						= 0x02,
	kOBEXOpCodePutWithHighBitSet		= 0x82,
	kOBEXOpCodeGet						= 0x03,
	kOBEXOpCodeGetWithHighBitSet		= 0x83,
	
	kOBEXOpCodeReservedWithHighBitSet	= 0x84,
	kOBEXOpCodeSetPath					= 0x85,		// High bit always set.

	kOBEXOpCodeAbort					= 0xFF,		// High bit always set.
	kOBEXOpCodeReservedRangeStart		= 0x06,
	kOBEXOpCodeReservedRangeEnd			= 0x0F,
	kOBEXOpCodeUserDefinedStart			= 0x10,
	kOBEXOpCodeUserDefinedEnd			= 0x1F,
};

//===========================================================================================================================
//	OBEXConnectFlags
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXConnectFlags =======
#endif


//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXConnectFlags
	@abstract	Flags for Connect command.
*/

enum OBEXConnectFlagValues
{
	kOBEXConnectFlagNone							= (0 << 0L),
	
	kOBEXConnectFlagSupportMultipleItLMPConnections	= (1 << 0L),
	kOBEXConnectFlag1Reserved						= (1 << 1L),
	kOBEXConnectFlag2Reserved						= (1 << 2L),
	kOBEXConnectFlag3Reserved						= (1 << 3L),
	kOBEXConnectFlag4Reserved						= (1 << 4L),
	kOBEXConnectFlag5Reserved						= (1 << 5L),
	kOBEXConnectFlag6Reserved						= (1 << 6L),
	kOBEXConnectFlag7Reserved						= (1 << 7L),
};

//===========================================================================================================================
//	OBEXPutFlags
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXSetPathFlags =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXSetPathFlags
	@abstract	Flags for SetPath command. Not that these are called "PutFlags". That is a mistake, they are not used
				with a Put command. We are not changing the names to maintain backwards compatibility.
*/

enum OBEXPutFlagValues
{
	kOBEXPutFlagNone								= (0 << 0L),
	
	kOBEXPutFlagGoToParentDirFirst					= (1 << 0L),
	kOBEXPutFlagDontCreateDirectory					= (1 << 1L),
	kOBEXPutFlag2Reserved							= (1 << 2L),
	kOBEXPutFlag3Reserved							= (1 << 3L),
	kOBEXPutFlag4Reserved							= (1 << 4L),
	kOBEXPutFlag5Reserved							= (1 << 5L),
	kOBEXPutFlag6Reserved							= (1 << 6L),
	kOBEXPutFlag7Reserved							= (1 << 7L),

};

//===========================================================================================================================
//	OBEXNonceFlags
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXNonceFlags =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXNonceFlags
	@abstract	Flags for Nonce command during digest challenge.
*/

enum OBEXNonceFlagValues
{
	kOBEXNonceFlagNone								= (0 << 0L),
	
	kOBEXNonceFlagSendUserIDInResponse				= (1 << 0L),
	kOBEXNonceFlagAccessModeReadOnly				= (1 << 1L),
	kOBEXNonceFlag2Reserved							= (1 << 2L),
	kOBEXNonceFlag3Reserved							= (1 << 3L),
	kOBEXNonceFlag4Reserved							= (1 << 4L),
	kOBEXNonceFlag5Reserved							= (1 << 5L),
	kOBEXNonceFlag6Reserved							= (1 << 6L),
	kOBEXNonceFlag7Reserved							= (1 << 7L),

};


//===========================================================================================================================
//	OBEXRealmValues
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXRealmValues =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXRealmValues
	@abstract	Values for Realm during digest response.
*/

enum OBEXRealmValues
{
	kOBEXRealmASCII									= 0x00,
	kOBEXRealmISO88591								= 0x01,
	kOBEXRealmISO88592								= 0x02,
	kOBEXRealmISO88593								= 0x03,
	kOBEXRealmISO88594								= 0x04,
	kOBEXRealmISO88595								= 0x05,
	kOBEXRealmISO88596								= 0x06,
	kOBEXRealmISO88597								= 0x07,
	kOBEXRealmISO88598								= 0x08,
	kOBEXRealmISO88599								= 0x09,
	kOBEXRealmUNICODE								= 0xFF,
};

//===========================================================================================================================
//	OBEXOpCodeSessionValues
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXOpCodeSessionValues =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXOpCodeSessionValues
	@abstract	Operation OpCode values for sessions. From the OBEX 1.3 specification.
*/

enum OBEXOpCodeSessionValues
{
	kOBEXOpCodeCreateSession			= 0x00,
	kOBEXOpCodeCloseSession				= 0x01,
	kOBEXOpCodeSuspendSession			= 0x02,
	kOBEXOpCodeResumeSession			= 0x03,
	kOBEXOpCodeSetTimeout				= 0x04
	
	/* 0x05-0xFF are reserved */
};

//===========================================================================================================================
//	OBEXPutTags
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXSessionTags =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXSessionParameterTags
	@abstract	Tags for SessionParameters.
*/

enum OBEXSessionParameterTags
{
	kOBEXSessionParameterTagDeviceAddress					= 0x00,
	kOBEXSessionParameterTagNonce							= 0x01,
	kOBEXSessionParameterTagSessionID						= 0x02,
	kOBEXSessionParameterTagNextSequenceNumber				= 0x03,
	kOBEXSessionParameterTagTimeout							= 0x04,
	kOBEXSessionParameterTagSessionOpcode					= 0x05

};

//===========================================================================================================================
//	OBEXVersions
//===========================================================================================================================

#if 0
#pragma mark ======= OBEXVersions =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXVersions
	@abstract	The available/supported OBEX versions.
*/

enum OBEXVersions
{
	kOBEXVersion10									= 0x10,
};

//===========================================================================================================================
//	OBEX Types
//===========================================================================================================================

#if 0
#pragma mark ======= OBEX Types =======
#endif


typedef	uint8_t		OBEXHeaderIdentifier;			
typedef	uint8_t		OBEXVersion;			
typedef	uint8_t		OBEXFlags;			
typedef	uint8_t		OBEXOpCode;			
typedef	uint8_t		OBEXConstants;			
typedef	uint16_t	OBEXMaxPacketLength;			

typedef	struct OpaqueOBEXSessionRef *	OBEXSessionRef;


//===========================================================================================================================
//	OBEX Session Types
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark ======= Client Session Types =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXConnectCommandResponseData
	@discussion	Part of the OBEXSessionEvent structure. Is readable when the event is of type
				kOBEXSessionEventTypeConnectCommandResponseReceived (see OBEXSessionEventTypes).
*/

typedef struct	OBEXConnectCommandResponseData			OBEXConnectCommandResponseData;
struct OBEXConnectCommandResponseData
{
	OBEXOpCode			serverResponseOpCode;
	void* 				headerDataPtr;
	size_t 				headerDataLength;
	OBEXMaxPacketLength	maxPacketSize;
	OBEXVersion			version;
	OBEXFlags			flags;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXDisconnectCommandResponseData	Part of the OBEXSessionEvent structure. Is readable when the event is
													of type kOBEXSessionEventTypeDisconnectCommandResponseReceived (see
													OBEXSessionEventTypes).
*/

typedef struct	OBEXDisconnectCommandResponseData		OBEXDisconnectCommandResponseData;
struct OBEXDisconnectCommandResponseData
{
	OBEXOpCode			serverResponseOpCode;
	void* 				headerDataPtr;
	size_t 				headerDataLength;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXPutCommandResponseData	Part of the OBEXSessionEvent structure. Is readable when the event is
											of type kOBEXSessionEventTypePutCommandResponseReceived (see OBEXSessionEventTypes).
*/

typedef struct	OBEXPutCommandResponseData				OBEXPutCommandResponseData;
struct OBEXPutCommandResponseData
{
	OBEXOpCode			serverResponseOpCode;
	void* 				headerDataPtr;
	size_t 				headerDataLength;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXGetCommandResponseData	Part of the OBEXSessionEvent structure. Is readable when the event is
											of type kOBEXSessionEventTypeGetCommandResponseReceived (see OBEXSessionEventTypes).
*/

typedef struct	OBEXGetCommandResponseData				OBEXGetCommandResponseData;
struct OBEXGetCommandResponseData
{
	OBEXOpCode			serverResponseOpCode;
	void* 				headerDataPtr;
	size_t 				headerDataLength;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXSetPathCommandResponseData	Part of the OBEXSessionEvent structure. Is readable when the event is
												of type kOBEXSessionEventTypeSetPathCommandResponseReceived (see
												OBEXSessionEventTypes).
*/

typedef struct	OBEXSetPathCommandResponseData			OBEXSetPathCommandResponseData;
struct OBEXSetPathCommandResponseData
{
	OBEXOpCode			serverResponseOpCode;
	void* 				headerDataPtr;
	size_t 				headerDataLength;
	OBEXFlags			flags;
	OBEXConstants		constants;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXAbortCommandResponseData	Part of the OBEXSessionEvent structure. Is readable when the event is
												of type kOBEXSessionEventTypeAbortCommandResponseReceived (see
												OBEXSessionEventTypes).
*/

typedef struct	OBEXAbortCommandResponseData			OBEXAbortCommandResponseData;
struct OBEXAbortCommandResponseData
{
	OBEXOpCode			serverResponseOpCode;
	void* 				headerDataPtr;
	size_t 				headerDataLength;
};


//===========================================================================================================================
//	Server Session Types
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark ======= Server Session Types =======
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXConnectCommandData	Part of the OBEXSessionEvent structure. Is readable when the event is
										of type kOBEXSessionEventTypeConnectCommandReceived (see
										OBEXSessionEventTypes).
*/

typedef struct	OBEXConnectCommandData			OBEXConnectCommandData;
struct OBEXConnectCommandData
{
	void* 				headerDataPtr;
	size_t 				headerDataLength;
	OBEXMaxPacketLength	maxPacketSize;
	OBEXVersion			version;
	OBEXFlags			flags;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXDisconnectCommandData	Part of the OBEXSessionEvent structure. Is readable when the event is
											of type kOBEXSessionEventTypeDisconnectCommandReceived (see OBEXSessionEventTypes).
*/

typedef struct	OBEXDisconnectCommandData		OBEXDisconnectCommandData;
struct OBEXDisconnectCommandData
{
	void* 				headerDataPtr;
	size_t 				headerDataLength;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXPutCommandData			Part of the OBEXSessionEvent structure. Is readable when the event is
											of type kOBEXSessionEventTypePutCommandReceived (see OBEXSessionEventTypes).
*/

typedef struct	OBEXPutCommandData				OBEXPutCommandData;
struct OBEXPutCommandData
{
	void* 				headerDataPtr;
	size_t 				headerDataLength;
	size_t				bodyDataLeftToSend;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXGetCommandData			Part of the OBEXSessionEvent structure. Is readable when the event is
											of type kOBEXSessionEventTypeGetCommandReceived (see OBEXSessionEventTypes).
*/

typedef struct	OBEXGetCommandData				OBEXGetCommandData;
struct OBEXGetCommandData
{
	void* 				headerDataPtr;
	size_t 				headerDataLength;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXSetPathCommandData		Part of the OBEXSessionEvent structure. Is readable when the event is
											of type kOBEXSessionEventTypeSetPathCommandReceived (see OBEXSessionEventTypes).
*/

typedef struct	OBEXSetPathCommandData			OBEXSetPathCommandData;
struct OBEXSetPathCommandData
{
	void* 				headerDataPtr;
	size_t 				headerDataLength;
	OBEXFlags			flags;
	OBEXConstants		constants;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXAbortCommandData		Part of the OBEXSessionEvent structure. Is readable when the event is
											of type kOBEXSessionEventTypeAbortCommandReceived (see OBEXSessionEventTypes).
*/

typedef struct	OBEXAbortCommandData			OBEXAbortCommandData;
struct OBEXAbortCommandData
{
	void* 				headerDataPtr;
	size_t 				headerDataLength;
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXErrorData		Part of the OBEXSessionEvent structure. Is readable when the event is
									of type kOBEXSessionEventTypeError (see OBEXSessionEventTypes).
*/

typedef struct	OBEXErrorData		OBEXErrorData;
struct OBEXErrorData
{
	OBEXError			error;
	void*				dataPtr;			// If data was associated with the error, it will be included here if possible.
	size_t				dataLength;			// Check the size to see if there is data to be examined.
};


#if 0
#pragma mark -
#pragma mark ======= OBEXSessionEventTypes =======
#endif


//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXSessionEventTypes
	@abstract	When a new session event occurs, your selector (or C callback) will be given an OBEXSessionEvent pointer,
				and in it will be a 'type' field with one of the following types in it. Based on that type, you can then
				read the corresponding field in the union to get out interesting data for that event type. For example,
				if the type of an event is a 'kOBEXSessionEventTypeConnectCommandResponseReceived', you should look in
				the 'OBEXConnectCommandResponseData' part of the structure's union to find more information pased to you
				in the event. Note that some you will never see, depending on the type of session you are using - a client
				or server. If you are a client (most likely case), you will never see the "Command" events, but instead
				you will only receive the "CommandResponse" events since you will be the issuer oft he commands, not the
				receiver of them. Both types of sessions will receive error type events.
*/

enum OBEXSessionEventTypes
{
	// Client event types.

	kOBEXSessionEventTypeConnectCommandResponseReceived		= 'OCEC',
	kOBEXSessionEventTypeDisconnectCommandResponseReceived 	= 'OCED',
	kOBEXSessionEventTypePutCommandResponseReceived			= 'OCEP',
	kOBEXSessionEventTypeGetCommandResponseReceived			= 'OCEG',
	kOBEXSessionEventTypeSetPathCommandResponseReceived		= 'OCES',
	kOBEXSessionEventTypeAbortCommandResponseReceived		= 'OCEA',
	
	// Server event types.
	
	kOBEXSessionEventTypeConnectCommandReceived				= 'OSEC',
	kOBEXSessionEventTypeDisconnectCommandReceived 			= 'OSED',
	kOBEXSessionEventTypePutCommandReceived					= 'OSEP',
	kOBEXSessionEventTypeGetCommandReceived					= 'OSEG',
	kOBEXSessionEventTypeSetPathCommandReceived				= 'OSES',
	kOBEXSessionEventTypeAbortCommandReceived				= 'OSEA',
	
	// Shared (Server/client) event types.
	
	kOBEXSessionEventTypeError								= 'OGEE',
};

typedef uint32_t	OBEXSessionEventType;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXSessionEvent
	@abstract	When a new session event occurs, your selector (or C callback) will be given an OBEXSessionEvent pointer,
				and in it will be information you might find interesting so that you can then reply back appropriately.
				For example, of you receive a kOBEXSessionEventTypeConnectCommandResponseReceived event, you can then
				parse out the information related to that event, and if all looks well to you, you could them send a
				"Get" command to get a file off of the OBEX server you just connected to.
*/

typedef struct OBEXSessionEvent				OBEXSessionEvent;
struct OBEXSessionEvent
{
	OBEXSessionEventType	type;
	OBEXSessionRef			session;
	void*					refCon;
	Boolean					isEndOfEventData;
	void*					reserved1;
	void*					reserved2;
	union
	{
		// Client session events.
		
		OBEXConnectCommandResponseData			connectCommandResponseData;
		OBEXDisconnectCommandResponseData		disconnectCommandResponseData;
		OBEXPutCommandResponseData				putCommandResponseData;
		OBEXGetCommandResponseData				getCommandResponseData;
		OBEXSetPathCommandResponseData			setPathCommandResponseData;
		OBEXAbortCommandResponseData			abortCommandResponseData;
		
		// Server session events.
		
		OBEXConnectCommandData					connectCommandData;
		OBEXDisconnectCommandData				disconnectCommandData;
		OBEXPutCommandData						putCommandData;
		OBEXGetCommandData						getCommandData;
		OBEXSetPathCommandData					setPathCommandData;
		OBEXAbortCommandData					abortCommandData;
		
		// Client & Server Session events.
		
		OBEXErrorData							errorData;
	} u;
};

// C API OBEXSessionEvent callback.

API_UNAVAILABLE(ios, watchos, tvos)
typedef	void	(*OBEXSessionEventCallback)	( const OBEXSessionEvent * inEvent );

// vCard charsets

#define		kCharsetStringISO88591			"CHARSET=ISO-8859-1"
#define		kCharsetStringUTF8				"UTF-8"

// vEvent encodings

#define		kEncodingStringQuotedPrintable	"QUOTED-PRINTABLE"
#define		kEncodingStringBase64			"BASE-64"
#define		kEncodingString8Bit				"8BIT"

#pragma mark -
#pragma mark ======= Header Contruction Kit =======

/*
	Header Contruction Kit
	
	You can use the following functions to ease the burden of creating your properly formatted OBEX headers.
	Generally, the strategy is either you will have a ptr to some data full of headers, and you
	can use OBEXGetHeaders to get you a easily-accessed CFDictionary (or NSDictionary) full of headers and
	use the keys below to obtain the actual header values. Conversely, you can create a CFDictionary full
	of headers using the OBEXAddXXXXXHeader(void) functions, and then pass this to an OBEX command using the
	OBEXHeadersToBytes( headerDictionary ) function to get the raw bytes.
*/

//---------------------------------------------------------------------------------------------------------------------------
/*
	These are defined keys to assist in locating headers in the dictionary of headers returned from the OBEXGetHeaders(void)
	function, described below.
*/

extern CFStringRef	kOBEXHeaderIDKeyName;
extern CFStringRef	kOBEXHeaderIDKeyType;
extern CFStringRef	kOBEXHeaderIDKeyDescription;
extern CFStringRef	kOBEXHeaderIDKeyTimeISO;
extern CFStringRef	kOBEXHeaderIDKeyTime4Byte;
extern CFStringRef	kOBEXHeaderIDKeyTarget;
extern CFStringRef	kOBEXHeaderIDKeyHTTP;
extern CFStringRef	kOBEXHeaderIDKeyBody;
extern CFStringRef	kOBEXHeaderIDKeyEndOfBody;
extern CFStringRef	kOBEXHeaderIDKeyWho;
extern CFStringRef	kOBEXHeaderIDKeyAppParameters;
extern CFStringRef	kOBEXHeaderIDKeyAuthorizationChallenge;
extern CFStringRef	kOBEXHeaderIDKeyAuthorizationResponse;
extern CFStringRef	kOBEXHeaderIDKeyObjectClass;
extern CFStringRef	kOBEXHeaderIDKeyCount;
extern CFStringRef	kOBEXHeaderIDKeyLength;
extern CFStringRef	kOBEXHeaderIDKeyConnectionID;
extern CFStringRef	kOBEXHeaderIDKeyByteSequence;
extern CFStringRef	kOBEXHeaderIDKeyUnknownUnicodeText;
extern CFStringRef	kOBEXHeaderIDKeyUnknownByteSequence;
extern CFStringRef	kOBEXHeaderIDKeyUnknown1ByteQuantity;
extern CFStringRef	kOBEXHeaderIDKeyUnknown4ByteQuantity;
extern CFStringRef	kOBEXHeaderIDKeyUserDefined;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXGetHeaders
	@abstract		Take a data blob and looks for OBEX headers.
	@param			inData			The data chunk with the headers you are interested in.
	@param			inDataSize		The size of the buffer you are passing in.
	@result			A CFDictionary with the headers found in the data blob inside it.
	@discussion
	You should use this when your callback for PUTs, GETs, etc. give you a data chunk
	and a size. Pass these params to this function and you will receive a dictionary
	back full of the parse headers. You can use the CFDictionary calls to get objects
	out of it, based on the header keys defined above. You are responsible for releasing
	the CFDictionary returned to you.
	Example usage:
	<pre>
	CFDictionaryRef   dictionary = OBEXGetHeaders( data, dataLength );
	if( dictionary )
	{
		if( CFDictionaryGetCountOfKey( dictionary, kOBEXHeaderIDKeyName ) > 0 )
		{			
			CFStringRef theStringRef;
			
			theStringRef = (CFStringRef) CFDictionaryGetValue( dictionary, kOBEXHeaderIDKeyName );
			if( theStringRef )
			{				
				// Display it, use it as a filename, whatever.
			}
		}
		
		if( CFDictionaryGetCountOfKey( dictionary, kOBEXHeaderIDKeyConnectionID ) > 0 )
		{
			CFDataRef theDataRef;
			
			theDataRef = (CFDataRef) CFDictionaryGetValue( dictionary, kOBEXHeaderIDKeyConnectionID );
			if( theDataRef )
			{
				// now we have data representing the connection ID.
			}
		}
		
		CFRelease( dictionary );
	}
	</pre>
*/

API_UNAVAILABLE(ios, watchos, tvos)
CFDictionaryRef OBEXGetHeaders( const void* inData, size_t inDataSize ) CF_RETURNS_RETAINED;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXHeadersToBytes
	@abstract		Converts a dictionary of headers to a data pointer, from which you can extract as bytes and pass to
					the OBEX command/response functions.
	@param			dictionaryOfHeaders		dictionary that you have added headers to with the above OBEXAddXXXHeader functions.		
	@result			Mutable data ref containing the bytes of all headers.
	@discussion		Returns a CFMutableDataRef containing all the header data found in the dictionary, formatted according to
					the OBEX/IrMC spec. YOU MUST RELEASE IT when you are finished with it (ie. when the OBEX request is complete).
					All OBEX-specification defined headers are supported and should be returned to the dictionary. Use the
					keys defined above to get headers from dictionary. Example usage:
	<pre>
	Example usage:

	CFMutableDictionaryRef	dictionary;
	CFMutableDataRef		mGetHeadersDataRef;
	uint8_t* 				headerDataPtr;
	uint32_t 				headerDataLength;
	
	dictionary = CFDictionaryCreateMutable( kCFAllocatorDefault, 0, &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
	
	// Package up desired headers.

	OBEXAddTypeHeader( CFSTR( "text/x-vCard" ), dictionary ); 

	mGetHeadersDataRef = OBEXHeadersToBytes( dictionary );

	headerDataPtr = CFDataGetBytePtr( mGetHeadersDataRef );
	headerDataLength = CFDataGetLength( mGetHeadersDataRef );
	
	// From here I can pass it to any OBEX command, such as OBEXPut...
	</pre>
					
*/

API_UNAVAILABLE(ios, watchos, tvos)
CFMutableDataRef OBEXHeadersToBytes( CFDictionaryRef dictionaryOfHeaders );

#pragma mark -

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddNameHeader
	@abstract		Add a CFStringRef to a dictionary of OBEXheaders.
	@param			name		name you want to add to the OBEX header dictionary.			
	@param			dictRef		dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Name header - OBEX Spec, 2.2.2: (2-byte) Null terminated unicode string.
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddNameHeader(	CFStringRef				name,
								CFMutableDictionaryRef	dictRef );
							
//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddDescriptionHeader
	@abstract		Add a CFStringRef to a dictionary of OBEXheaders.
	@param			description		Description you want to add to the OBEX header dictionary.			
	@param			dictRef			dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Description header - OBEX Spec, 2.2.6: (2-byte) Null terminated unicode string.
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddDescriptionHeader(	CFStringRef				description,
									CFMutableDictionaryRef	dictRef );
									
//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddCountHeader
	@abstract		Add a CFStringRef to a dictionary of OBEXheaders.
	@param			count		Count value you want to add to the OBEX header dictionary.			
	@param			dictRef		dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Count header - OBEX Spec, 2.2.1: 4 byte unsigned integer
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddCountHeader(	uint32_t				count,
								CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddTime4ByteHeader
	@abstract		Add a CFStringRef to a dictionary of OBEXheaders.
	@param			time4Byte		4-byte time value you want to add to the OBEX header dictionary.			
	@param			dictRef			dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Time4Byte headers - OBEX Spec, 2.2.5: 4 Bytes
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddTime4ByteHeader(	uint32_t				time4Byte,
									CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddLengthHeader
	@abstract		Add a CFStringRef to a dictionary of OBEXheaders.
	@param			length			Value of Length header you want to add to the OBEX header dictionary.			
	@param			dictRef			dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Length header - OBEX Spec, 2.2.4: 4 byte unsigned integer
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddLengthHeader(	uint32_t				length,
								CFMutableDictionaryRef	dictRef );
								
//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddTypeHeader
	@abstract		Add a CFStringRef to a dictionary of OBEXheaders.
	@param			type			String containing the type of header to add.
 	@param			dictRef			dictionary you have allocated to hold the headers. Make sure it's mutable.
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Type header - OBEX Spec, 2.2.3: 1-byte Null terminated ascii string.
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddTypeHeader(	CFStringRef				type,
								CFMutableDictionaryRef	dictRef );
							
//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddTimeISOHeader
	@abstract		Add bytes to a dictionary of OBEXheaders.
	@param			inHeaderData		Time ISO 8601 header data, local times in format YYYYMMDDTHHMMSS and UTC in the format YYYYMMDDTHHMMSSZ.
	@param			inHeaderDataLength	Length of header data.
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		TimeISO header - OBEX Spec, 2.2.5: Byte Sequence
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddTimeISOHeader(	const void*				inHeaderData,
								uint32_t				inHeaderDataLength,
								CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddTargetHeader
	@abstract		Add bytes of data to a dictionary of OBEXheaders.
	@param			inHeaderData		Target header data.			
	@param			inHeaderDataLength	Length of Target header data.
	@param			dictRef				dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Target header - OBEX Spec, 2.2.7: Byte Sequence
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddTargetHeader(	const void*				inHeaderData,
								uint32_t				inHeaderDataLength,
								CFMutableDictionaryRef	dictRef );
								
//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddHTTPHeader
	@abstract		Add bytes of data to a dictionary of OBEXheaders.
	@param			inHeaderData		HTTP header data.			
	@param			inHeaderDataLength	Length of HTTP header data.
	@param			dictRef				dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		HTTP header - OBEX Spec, 2.2.8: Byte Sequence
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddHTTPHeader(	const void*				inHeaderData,
								uint32_t				inHeaderDataLength,
								CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddBodyHeader
	@abstract		Add bytes of data to a dictionary of OBEXheaders.
	@param			inHeaderData		Body header data.			
	@param			inHeaderDataLength	Length of Body header data.
	@param			isEndOfBody			Set this flag if you want an end of body header instead of a body header.
	@param			dictRef				dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Body,EndOfBody headers - OBEX Spec, 2.2.9: Byte Sequence
*/
			
API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddBodyHeader(	const void*				inHeaderData,
								uint32_t				inHeaderDataLength,
								Boolean					isEndOfBody,
								CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddWhoHeader
	@abstract		Add bytes of data to a dictionary of OBEXheaders.
	@param			inHeaderData		Who header data.			
	@param			inHeaderDataLength	Length of Who header data.	
	@param			dictRef				dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Who headers - OBEX Spec, 2.2.10: Byte Sequence
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddWhoHeader(	const void*				inHeaderData,
							uint32_t				inHeaderDataLength,
							CFMutableDictionaryRef	dictRef );
							
//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddConnectionIDHeader
	@abstract		Add bytes representing a connection ID to a dictionary of OBEX headers.
	@param			inHeaderData		Connection ID data. Should be 4 bytes in length only.
	@param			inHeaderDataLength	Length of Connection ID data. This should ONLY be set to equal 4.		
	@param			dictRef				dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		ConnectionID headers - OBEX Spec, 2.2.10: Byte Sequence
					
					*** IMPORTANT NOTE: In bluetooth 1.0, using this function will allow you to pass in any value.
										You should not pass more than 4 bytes ever. In later releases, if the length
										passed is not 4, a kOBEXBadArgumentError error will be returned. ***
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddConnectionIDHeader(	const void*				inHeaderData,
										uint32_t				inHeaderDataLength,
										CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddApplicationParameterHeader
	@abstract		Add bytes representing an application parameter to a dictionary of OBEX headers.
	@param			inHeaderData		Application parameter data - should be tag/length/value triplets.
	@param			inHeaderDataLength	Length of application parameter data.		
	@param			dictRef				dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Application Request/Response Parameter headers - OBEX Spec, 2.2.11: Byte Sequence
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddApplicationParameterHeader(	const void*				inHeaderData,
												uint32_t				inHeaderDataLength,
												CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddByteSequenceHeader
	@abstract		Add a byte sequence header to a dictionary of OBEXheaders.
	@param			inHeaderData		bytes you want to put in the byte sequence header.			
	@param			inHeaderDataLength	length of the bytes you want to put in the byte sequence header.			
	@param			dictRef				dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Byte Sequence header - OBEX Spec, 2.2.5: Byte sequence. One thing of important note here - since we
					don't know what Header Identifier and length you intend to use here, you MUST include your own
					identifier and length in the data you pass. Thus, your data must be in this format:
						<1:HI><2:LENGTH><n:(<TAG><LENGTH><VALUE>)>
					Also, note that LENGTH = (3 + n), (1 for HI, 2 for the 2 bytes of length information, plus your n bytes of custom data).
					Be careful here to not mess up these values, as it could adversely affect the ability of the remote-device's headers parser.
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddByteSequenceHeader(	const void*				inHeaderData,
										uint32_t				inHeaderDataLength,
										CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddObjectClassHeader
	@abstract		Add an object class header to a dictionary of OBEXheaders.
	@param			inHeaderData		bytes you want to put in the object class header.			
	@param			inHeaderDataLength	length of the bytes you want to put in the object class header.			
	@param			dictRef				dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Object Class header - OBEX Spec, 2.2.15: Byte sequence.
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddObjectClassHeader(	const void*				inHeaderData,
									uint32_t				inHeaderDataLength,
									CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddAuthorizationChallengeHeader
	@abstract		Add an authorization challenge header to a dictionary of OBEXheaders.
	@param			inHeaderData		bytes you want to put in the authorization challenge header.			
	@param			inHeaderDataLength	length of the bytes you want to put in authorization challenge header.			
	@param			dictRef			dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Authorization Challenge header - OBEX Spec, 2.2.13: Authorization Challenge.
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddAuthorizationChallengeHeader(	const void*				inHeaderData,
												uint32_t				inHeaderDataLength,
												CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddAuthorizationResponseHeader
	@abstract		Add an authorization Response header to a dictionary of OBEXheaders.
	@param			inHeaderData		bytes you want to put in the authorization Response header.			
	@param			inHeaderDataLength	length of the bytes you want to put in authorization Response header.			
	@param			dictRef			dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		Authorization Response header - OBEX Spec, 2.2.14: Authorization Response.
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddAuthorizationResponseHeader(	const void*				inHeaderData,
												uint32_t				inHeaderDataLength,
												CFMutableDictionaryRef	dictRef );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function		OBEXAddUserDefinedHeader
	@abstract		Add a user-defined custom header to a dictionary of OBEXheaders.
	@param			inHeaderData		bytes you want to put in the user-defined header.			
	@param			inHeaderDataLength	length of the bytes you want to put in user-defined header.			
	@param			dictRef			dictionary you have allocated to hold the headers. Make sure it's mutable.		
	@result			Error code, kOBEXSuccess (0) if success.
	@discussion		User Defined header - OBEX Spec, 2.2.20: User Defined Headers.
*/

API_UNAVAILABLE(ios, watchos, tvos)
OBEXError OBEXAddUserDefinedHeader(	const void*				inHeaderData,
									uint32_t				inHeaderDataLength,
									CFMutableDictionaryRef	dictRef );

#ifdef	__cplusplus
	}
#endif

