/*
	File:		OBEXSession.h
	Contains:	OBEX session object.
    Copyright:	й 2002 by Apple Computer, Inc. All rights reserved.
*/

#import <IOKit/IOKitLib.h>

#import <IOBluetooth/OBEX.h>


#pragma mark еее Types еее

typedef struct OpaquePrivOBEXSessionData* PrivOBEXSessionDataRef;


//---------------------------------------------------------------------------------------------------------------------------
/*!	@class			OBEXSession
	@abstract		Object representing an OBEX connection to a remote target.
	@discussion		You will have no need for a obtaining/using a raw OBEXSession, since it requires an underlying
					transport to do anything useful. However, once you have an object that is a subclass of this
					class, you can use the functions herein to manipulate that OBEXSession. First off, you will want
					to use OBEXConnect (if you are a client session) to actually cause the transport to open a
					connection to a remote target and establish an OBEX connection over it. From there you can issue
					more commands based on the responses from a server.
					
					If you are a server session, the first thing you should receive is an OBEXConnect command packet,
					and you will want to issue an OBEXConnectResponse packet, with your reesponse to that command
					(success, denied, bad request, etc.).
					
					You can use the session accessors to access certain information, such as the negotiated max
					packet length.
					
					If you wish to implement your own OBEXSession over a transport such as ethernet, you will need to
					see the end of the file to determine which functions to override, and what to pass to those
					functions.
					
					No timeout mechanism has been implemented so far for an OBEXSessions. If you need timeouts, you
					will need to implement them yourself. This is being explored for a future revision. However, be aware
					that the OBEX Specification does not explicitly require timeouts, so be sure you allow ample time
					for commands to complete, as some devices may be slow when sending large amounts of data.
*/

#pragma mark -
#pragma mark еее OBEXSession Interface еее

@interface OBEXSession : NSObject
{	
	/* All instance variables are private */
	
	BOOL							mHasOBEXConnection;					// Has the OBEX connection been established over the transport?
	BOOL							mIsServer;							// Is this session an OBEX client (we initiated the connection) or server?
	OBEXMaxPacketLength				mMaxPacketLength;					// Negotiated maximum packet size.
	uint8_t*						mReceivePacketBuffer;				// Desgmentation buffer.
	size_t							mResponsePacketDataLengthExpected;	// Desgmentation buffer support.
	size_t							mResponsePacketDataLengthSoFar;		// Desgmentation buffer support.
	OBEXOpCode						mIncompletePacketResponseCode;		// Desgmentation buffer support.
	PrivOBEXSessionDataRef			mPrivateOBEXSessionData;			// Truly-private session state data.
	OBEXMaxPacketLength				mTheirMaxPacketLength;				// Negotiated maximum packet size.
	OBEXMaxPacketLength				mOurMaxPacketLength;				// Negotiated maximum packet size we can handle.
}

#if 0
#pragma mark -
#pragma mark еее Client Commands еее
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXConnect
	@abstract	Initiate an OBEX connection to a device. Causes underlying transport (Bluetooth, et al) to attempt to connect
				to a remote device. After success, an OBEX connect packet is sent to establish the OBEX Connection.
	@param		inFlags					OBEX connect flags. See OBEX.h for possibilities.
	@param		inMaxPacketLength		Maximum packet size you want to support. May be negotiated down, depending on
										target device.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use the
										provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXConnectHandler:(const OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				transport. You will receive a response to your command on your selector. If you have already established an OBEX
				connection and you call this again you will get an 'kOBEXSessionAlreadyConnectedError' as a result.
*/

-(OBEXError)OBEXConnect:(OBEXFlags)inFlags
				maxPacketLength:(OBEXMaxPacketLength)inMaxPacketLength
				optionalHeaders:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXDisconnect
	@abstract	Send an OBEX Disconnect command to the session's target. THIS DOES NOT necessarily close the underlying transport
				connection. Deleting the session will ensure that closure.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXDisconnectHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				transport. You will receive a response to your command on your selector.
				Be careful not to exceed the max packet length in your optional headers, or your command will be rejected.
				It is recommended that you call getMaxPacketLength on your session before issuing this command so
				you know how much data the session's target will accept in a single transaction.
*/

-(OBEXError)OBEXDisconnect:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;
				
//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXPut
	@abstract	Send an OBEX Put command to the session's target.
	@param		isFinalChunk			Specify if this request is complete in one shot - that all the headers you are
										supplying will fit in the negotiated max packet length.
	@param		inHeadersData			Can be NULL. Ptr to some data you want to send as your headers, such as Length,
										Name, etc. Use the provided header contruction kit in OBEX.h and OBEXHeadersToBytes()
										for convenience.
	@param		inHeadersDataLength		Length of data in ptr passed in above.
	@param		inBodyData				Can be NULL. Ptr to some data you want to send as your BODY header. Do not construct a
										real OBEX header here, it will be done for you - just pass a pointer to your
										data, we'll do the rest. HOWEVER, be aware that some overhead (3 bytes) will be added
										to the data in constructing the BODY header for you.
	@param		inBodyDataLength		Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXPutHandler:(const  OBEXSessionEvent*)inSessionEvent;


	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion	A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				transport. You will receive a response to your command on your selector. 
*/

-(OBEXError)OBEXPut:(Boolean)isFinalChunk
				headersData:(void*)inHeadersData
				headersDataLength:(size_t)inHeadersDataLength
				bodyData:(void*)inBodyData
				bodyDataLength:(size_t)inBodyDataLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXGet
	@abstract	Send an OBEX Get command to the session's target.
	@param		isFinalChunk			Specify if this request is complete in one shot - that all the headers you are
										supplying will fit in the negotiated max packet length.
	@param		inHeadersData			Can be NULL. Ptr to some data you want to send as your headers, such as Length,
										Name, etc. Use the provided header contruction kit in OBEX.h and OBEXHeadersToBytes()
										for your convenience.
	@param		inHeadersDataLength		Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXGetHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion	A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				transport. You will receive a response to your command on your selector. 
*/

-(OBEXError)OBEXGet:(Boolean)isFinalChunk
				headers:(void*)inHeaders
				headersLength:(size_t)inHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXAbort
	@abstract	Send an OBEX Abort command to the session's target.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXAbortHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion	A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				transport. You will receive a response to your command on your selector. 
*/
			 		
-(OBEXError)OBEXAbort:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXSetPath
	@abstract	Send an OBEX SetPath command to the session's target.
	@param		inFlags					OBEX setpath flags. See OBEX.h for possibilities.
	@param		inConstants				OBEX setpath constants. See OBEX.h for possibilities.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXSetPathHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				transport. You will receive a response to your command on your selector.
*/

-(OBEXError)OBEXSetPath:(OBEXFlags)inFlags
				constants:(OBEXConstants)inConstants
				optionalHeaders:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

#if 0
#pragma mark -
#pragma mark еее Server Command Responses еее
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXConnectResponse
	@abstract	Send a connect response to a session's target.
	@param		inFlags					OBEX connect flags. See OBEX.h for possibilities.
	@param		inConstants				OBEX connect constants. See OBEX.h for possibilities.
	@param		inMaxPacketLength		Maximum packet size you want your OBEX session to communicate with. This MUST be
										lower than the max packet size the client has reported to you in the connect command
										you received from it.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXConnectResponseHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				underlying OBEX transport. You will receive any responses to your command response on your selector.
*/

-(OBEXError)OBEXConnectResponse:(OBEXOpCode)inResponseOpCode
				flags:(OBEXFlags)inFlags
				maxPacketLength:(OBEXMaxPacketLength)inMaxPacketLength
				optionalHeaders:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXDisconnectResponse
	@abstract	Send a disconnect response to a session's target.
	@param		inMaxPacketLength		Maximum packet size you want your OBEX session to communicate with. This MUST be
										lower than the max packet size the client has reported to you in the connect command
										you received from it.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXDisconnectResponseHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				underlying OBEX transport. You will receive any responses to your command response on your selector.
*/

-(OBEXError)OBEXDisconnectResponse:(OBEXOpCode)inResponseOpCode
				optionalHeaders:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXPutResponse
	@abstract	Send a put response to a session's target.
	@param		inMaxPacketLength		Maximum packet size you want your OBEX session to communicate with. This MUST be
										lower than the max packet size the client has reported to you in the connect command
										you received from it.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXPutResponseHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				underlying OBEX transport. You will receive any responses to your command response on your selector.
*/

-(OBEXError)OBEXPutResponse:(OBEXOpCode)inResponseOpCode
				optionalHeaders:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXGetResponse
	@abstract	Send a get response to a session's target.
	@param		inMaxPacketLength		Maximum packet size you want your OBEX session to communicate with. This MUST be
										lower than the max packet size the client has reported to you in the connect command
										you received from it.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXGetResponseHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				underlying OBEX transport. You will receive any responses to your command response on your selector.
*/

-(OBEXError)OBEXGetResponse:(OBEXOpCode)inResponseOpCode
				optionalHeaders:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXAbortResponse
	@abstract	Send a abort response to a session's target.
	@param		inMaxPacketLength		Maximum packet size you want your OBEX session to communicate with. This MUST be
										lower than the max packet size the client has reported to you in the connect command
										you received from it.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXAbortResponseHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				underlying OBEX transport. You will receive any responses to your command response on your selector.
*/

-(OBEXError)OBEXAbortResponse:(OBEXOpCode)inResponseOpCode
				optionalHeaders:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		OBEXSetPathResponse
	@abstract	Send a set path response to a session's target.
	@param		inMaxPacketLength		Maximum packet size you want your OBEX session to communicate with. This MUST be
										lower than the max packet size the client has reported to you in the connect command
										you received from it.
	@param		inOptionalHeaders		Can be NULL. Ptr to some data you want to send as your optional headers. Use
										the provided header contruction kit in OBEX.h and OBEXHeadersToBytes() for convenience.
	@param		inOptionalHeadersLength	Length of data in ptr passed in above.
	@param		inSelector				A VALID selector to be called when something interesting happens due to this call.
										Selector in your target object MUST have the following signature, or it
										will not be called properly (look for error messages in Console.app):

										- (void)OBEXSetPathResponseHandler:(const  OBEXSessionEvent*)inSessionEvent;

	@param		inTarget				A VALID target object for the selector.
	@param		inUserRefCon			Whatever you want to pass here. It will be passed back to you in the refCon portion of the
										OBEXSessionEvent struct. nil is, of course, OK here.
	@result		An error code value on failure (see OBEX.h and IOReturn.h for possible return values). 0 (kOBEXSuccess) if successful.
	@discussion A NULL selector or target will result in an error. After return, the data passed in will have been sent over the
				underlying OBEX transport. You will receive any responses to your command response on your selector.
*/

-(OBEXError)OBEXSetPathResponse:(OBEXOpCode)inResponseOpCode
				optionalHeaders:(void*)inOptionalHeaders
				optionalHeadersLength:(size_t)inOptionalHeadersLength
				eventSelector:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;

#if 0
#pragma mark -
#pragma mark еее Session Accessors еее
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		getAvailableCommandPayloadLength
	@abstract	Determine the maximum amount of data you can send in a particular command as an OBEX client session.
	@param		inOpCode		The opcode you are interested in sending (as a client).
	@result		The maximum amount of data a particular packet can handle, after accounting for the command/ overhead.
	@discussion	You should call this only if you are a server and are responding to a client's command.
				Each OBEX Command has a certain amount of overhead. Since the negotiated max packet length does
				not indicate what the maximum data amount you can send in a particular command's packet, you can
				use this function to determine how much data to provide in optional headers or body data headers.
*/

-(OBEXMaxPacketLength)getAvailableCommandPayloadLength:(OBEXOpCode)inOpCode;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		getAvailableCommandResponsePayloadLength
	@abstract	Determine the maximum amount of data you can send in a particular command response as an OBEX server session.
	@param		inOpCode		The opcode you are interested in responding to (as a server).
	@param		inIsResponse	Whether or not you the opcode will be sent as a command (client) or as a command response (server).
	@result		The maximum amount of data a particular packet can handle, after accounting for the command response overhead.
	@discussion	You should call this only if you are a server and are responding to a client's command.
				Each OBEX Command response has a certain amount of overhead. Since the negotiated max packet length does
				not indicate what the maximum data amount you can send in a particular response's packet, you can
				use this function to determine how much data to provide in optional headers or body data headers.
*/

-(OBEXMaxPacketLength)getAvailableCommandResponsePayloadLength:(OBEXOpCode)inOpCode;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		getMaxPacketLength
	@abstract	Gets current max packet length.
	@result		Max packet length.
	@discussion	This value *could* change before and after a connect command has been sent or a connect
				command response has been received, since the recipient could negotiate a lower max packet size.
*/

-(OBEXMaxPacketLength)getMaxPacketLength;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		hasOpenOBEXConnection
	@abstract	Has a successful connect packet been sent and received? This API tells you so.
	@result		True or false, we are OBEX-connected to another OBEX entity.
	@discussion	A "transport" connection may exist (such as a Bluetooth baseband connection), but the OBEX connection
				may not be established over that transport. If it has been, this function returns true.
*/

-(BOOL)hasOpenOBEXConnection;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setEventCallback
	@abstract	Sets the C-API callback used when the session recieves data.
	@param		inEventCallback		Function to callback. Should be non-NULL, unless you are attempting to clear the
									callback, but doing that doesn't make much sense.
	@discussion	This is really not intended for client sessions. Only subclasses would really be interested in using this. They
				should set these when their subclass object is created, because otherwise they will have no way of receiving
				the initial command data packet. This is a partner to setEventRefCon, described below.
*/

-(void)setEventCallback:(OBEXSessionEventCallback)inEventCallback;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setEventRefCon
	@abstract	Sets the C-API callback refCon used when the session recieves data.
	@param		inRefCon		User's refCon that will get passed when their event callback is invoked.
	@discussion	This is really not intended for client sessions. Only subclasses would really be interested in using this. They
				should set these when their subclass object is created, because otherwise they will have no context in their
				callback.
*/

-(void)setEventRefCon:(void*)inRefCon;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setEventSelector
	@abstract	Allow you to set a selector to be called when events occur on the OBEX session.
	@param		inEventSelector				Selector to call on the target.
	@param		inEventSelectorTarget		Target to be called with the selector.
	@param		inUserRefCon				User's refCon that will get passed when their event callback is invoked.
	@discussion	Really not needed to be used, since the event selector will get set when an OBEX command is sent out.
*/

-(void)setEventSelector:(SEL)inEventSelector
			target:(id)inEventSelectorTarget
			refCon:(id)inUserRefCon;
	
#if 0
#pragma mark -
#pragma mark еее Transport Subclassing еее
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!	@enum		OBEXTransportEventTypes
	@discussion	Pass these types in the OBEXTransportEvent, and then pass the struct on to the session object once you
				have filled it out. This is how you can communicate with the session when events happen - if data is
				received, the type will be 'kOBEXTransportEventTypeDataReceived'. if an error has occurred on your transport,
				like the remote target died, you can send a status event with a non-zero value. Since session objects will
				receive this status code on their event handlers, you should try to pass a useful status/error code, such as
				an IOReturn value.
*/

typedef uint32_t	OBEXTransportEventType;
enum OBEXTransportEventTypes
{
	kOBEXTransportEventTypeDataReceived		= 'DatA',
	kOBEXTransportEventTypeStatus			= 'StaT'
};

//---------------------------------------------------------------------------------------------------------------------------
/*!	@struct		OBEXTransportEvent
	@discussion	You will need to construcy these when data is received, and then pass a pointer to it to one of the
				incoming data methods defined below. Pass 0 as your status if data was received OK. Otherwise, you can
				put your own error code in there. For the transport type, be sure to use one of the defined types above.
*/

typedef struct OBEXTransportEvent	OBEXTransportEvent;
struct OBEXTransportEvent
{	
	OBEXTransportEventType	type;
	OBEXError				status;	
	void *					dataPtr;
	size_t					dataLength;
};
	

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		serverHandleIncomingData
	@abstract	Tranport subclasses need to invoke this from their own data-receive handlers. For example, when data is
				received over a Bluetooth RFCOMM channel in the IOBluetoothOBEXSession, it in turn calls this to dispatch
				the data. If you do not handle this case, your server session will not work, guaranteed.
	@param		event			New event received from the transport.
	@discussion	Tranport subclasses must call this for OBEX server sessions to work!
*/

-(void) serverHandleIncomingData:(OBEXTransportEvent*)event;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		clientHandleIncomingData
	@abstract	Tranport subclasses need to invoke this from their own data-receive handlers. For example, when data is
				received over a Bluetooth RFCOMM channel in the IOBluetoothOBEXSession, it in turn calls this to dispatch
				the data. If you do not handle this case, your server session will not work, guaranteed.
	@param		event			New event received from the transport.
	@discussion	Tranport subclasses must call this for OBEX client sessions to work!
*/


-(void) clientHandleIncomingData:(OBEXTransportEvent*)event;


//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		sendDataToTransport
	@abstract	You must override this to send data over your transport. This does nothing by default, it will
				return a kOBEXUnsupportedError.
	@param		inDataToSend		Data to shove over the transport to a remote OBEX session.
	@param		inDataLength		Length of data passed in.
	@result		Return whether or not the transport could send the  data or not. If you are successful, return kOBEXSuccess,
				otherwise an interesting error code.
	@discussion	Tranport subclasses must override this! When called you should send the data over the transport to
				the remote session.
*/

-(OBEXError)sendDataToTransport:(void *)inDataToSend
			dataLength:(size_t)inDataLength;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		openTransportConnection
	@abstract	Opens a transport connection to a device. A Bluetooth connection is one example of a transport.
	@param		inSelector			Selector to call for success, failure or timeout.
	@param		inTarget			Target on which to call the selector.
	@param		inUserRefCon		Caller's reference constant.
	@result		Should return kOBEXSuccess ( 0 ) on success, otherwise an error code.
	@discussion	Tranport subclasses must override this! when called you should attempt to open your transport
				connection, and if you are successful, return kOBEXSuccess, otherwise an interesting error code.
*/

-(OBEXError)openTransportConnection:(SEL)inSelector
				selectorTarget:(id)inTarget
				refCon:(void *)inUserRefCon;
				
//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		hasOpenTransportConnection
	@abstract	You must override this - it will be called periodically to determine if a transport connection is open or not.
	@result		Return whether or not the transport connection is still open.
	@discussion	Tranport subclasses must override this! When called you simply return if the transport connection is still
				open or not.
*/

-(Boolean)hasOpenTransportConnection;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		closeTransportConnection
	@abstract	You must override this - it will be called when the transport connection should be shutdown.
	@result		Return whether or not the transport connection was closed successfully or not. Return OBEXSuccess ( 0 ) on
				success, otherwise an error code.
	@discussion	Tranport subclasses must override this! When called you should take whatever steps are necessary to
				actually close down the transport connection.
*/

-(OBEXError)closeTransportConnection;

@end
