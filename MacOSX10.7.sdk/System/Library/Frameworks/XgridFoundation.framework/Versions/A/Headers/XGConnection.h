//
//  XGConnection.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class XGAuthenticator;
@class XGConnectionInternal;

/*!
	@header XGConnection.h
 
	This header file describes the interface to an object which represents
	the connection between an Xgrid client and an Xgrid controller.  The
	XGConnection class is created by an Xgrid client using the name or address
	of a controller.  The connection can be in one of four states, and a collection
	of constants is declared which are used describe which state a connection is
	in.  An authenticator can be set on the connector, which allows the connection
	to be authenticated.  A delegate may be set on the connection, and will
	receive callbacks when connection events occur, prior to the notification of
	key-value observers.
*/

/*!
	@enum XGConnectionState
 
	@discussion The XGConnectionState enum defines constants that are used by the
	connection to specify which state it is in.  A connection begins in the Closed
	state.  After receiving the -open message the connection enters the Opening
	state.  If the connection succeeds at opening then the state becomes Open.  If
	the connection fails to open while in the Opening state, or if the connection
	encounters an error while it is Open, or if the connection receives the -close
	message, then the state will become Closing, and then Closed.
 
	@constant XGConnectionStateClosed The initial state of the connection.
 
	@constant XGConnectionStateOpening The connection enters this state immediately
	following reception of the -open message.
 
	@constant XGConnectionStateOpen In this state the connection is open and can
	be used by XGResource objects to retreive information and perform actions.
 
	@constant XGConnectionStateClosing The connection enters this state immediately
	following the reception of the -close message, as well as when it encounters an
	error.
*/
typedef enum {
	XGConnectionStateClosed,
	XGConnectionStateOpening,
	XGConnectionStateOpen,
	XGConnectionStateClosing
} XGConnectionState NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@const XGConnectionKeyIsOpened
	@abstract The key for the "isOpened" property of XGConnection.
 */
extern NSString * const XGConnectionKeyIsOpened NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@const XGConnectionKeyIsClosed
	@abstract The key for the "isClosed" property of XGConnection.
*/
extern NSString * const XGConnectionKeyIsClosed NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@const XGConnectionKeyState
	@abstract The key for the "state" property of XGConnection.
*/
extern NSString * const XGConnectionKeyState NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@class XGConnection
 
	@abstract An XGConnection object represents the connection between an Xgrid
	client and an Xgrid controller.
 
	@discussion The XGConnection class is created by an Xgrid client using the name
	or address of a controller.  The connection can be in one of four states, and a
	collection of constants is declared which are used describe which state a
	connection is in.  An authenticator can be set on the connector, which allows
	the connection to be authenticated.  A delegate may be set on the connection,
	and will receive callbacks when connection events occur, prior to the
	notification of key-value observers.
*/
@interface XGConnection : NSObject
{
	@private
	XGConnectionInternal *_internal;
}

/*!
	@method initWithNetService:
	@abstract Initializes a XGConnection object with a NSNetService.
	@param netService The net service to connect to. Must not be nil.
	@result An initialized XGConnection object.
*/
- (id)initWithNetService:(NSNetService *)netService NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method initWithHostname:portnumber:
	@abstract Initializes a XGConnection object with a hostname and portnumber.
	@param hostname The hostname to connect to. May be a name or address. Must
	not be nil.
	@param portnumber The portnumber to connect to. If portnumber is 0 then the
	default portnumber will be used.
*/
- (id)initWithHostname:(NSString *)hostname portnumber:(UInt32)portnumber NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method netService
	@abstract Returns the NSNetService the receiver was initialized with, or
	nil if the receiver wasn't initialized with an NSNetService.
	@result The NSNetService the receiver connects to.
*/
- (NSNetService *)netService NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method hostname
	@abstract Returns the hostname the receiver was initialized with, or nil
	if the receiver wasn't initialized with a hostname.
	@result The hostname the receiver connects to.
*/
- (NSString *)hostname NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method portnumber
	@abstract Returns the portnumber the receiver was initialized with, or
	the default portnumber if the receiver was initialized with a 0 portnumber,
	or 0 if the receiver wasn't initialized with a portnumber.
	@result The portnumber the receiver connects to.
*/
- (UInt32)portnumber NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method name
	@abstract Returns the name of the connection.  This may be the name of the
	netService or the hostname, depending on which the receiver was initialized
	with.
	@result The name of the receiver.
*/
- (NSString *)name NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method setDelegate:
	@abstract Sets the delegate of the receiver.
	@param delegate The delegate.
	@discussion The delegate is not retained.  If the delegate implements any of
	the methods in the XGConnectionDelegate protocol then it will receive callbacks
	when connection events occur, prior to the notification of key-value observers.
*/
- (void)setDelegate:(id)delegate NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method delegate
	@abstract Returns the delegate of the receiver.
	@result The delegate of the receiver.
*/
- (id)delegate NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method setAuthenticator:
	@abstract Sets the authenticator of the receiver.
	@discussion The authenticator is retained.  The authenticator will be used by
	the connection if the client or controller requires the connection to be
	authenticated.
*/
- (void)setAuthenticator:(XGAuthenticator *)authenticator NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method authenticator
	@abstract Returns the authenticator of the receiver.
	@result The authenticator of the receiver.
*/
- (XGAuthenticator *)authenticator NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method error
	@abstract Returns the error of the receiver.
	@result The error of the receiver.
	@discussion The error is nil during the Opening and Closing states.  The error
	represents success if the connection is in the Open state.  If the connection
	closes due to an error, then this will be set to that error.  If the connection
	closes due to a -close message, then this will be a success error.
*/
- (NSError *)error NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method state
	@abstract Returns the state of the receiver.
	@result The state of the receiver.
*/
- (XGConnectionState)state NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method isOpened
	@abstract Returns YES iff the connection state is Open.
*/
- (BOOL)isOpened NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method isClosed
	@abstract Returns YES iff the connection state is Closed.
*/
- (BOOL)isClosed NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method open
	@abstract Starts opening the connection from the client to the controller.
	@discussion This method may only be called when the connection is in the Closed
	state.
*/
- (void)open NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method close
	@abstract Starts closing the connection from the client to the controller.
	@discussion This method may only be called when the connection is in the Opening
	or Open states.
*/
- (void)close NS_DEPRECATED_MAC(10_4, 10_7);

- (NSString *)servicePrincipal NS_DEPRECATED_MAC(10_4, 10_7);

@end

/*!
	@protocol
	@discussion The XGConnectionDelegate delegate is used to report the status
	of the connection and any errors that are encountered.
*/
@interface NSObject (XGConnectionDelegate)

/*!
	@method connectionDidOpen:
	@abstract This method is called as soon as the connection enters the Open state.
	@param connection The connection that just opened.
*/
- (void)connectionDidOpen:(XGConnection *)connection NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method connectionDidNotOpen:withError:
	@abstract This method is called as soon as the connection enters the Closed
	state from the Opening state.
	@param connection The connection that didn't open.
	@param error The error that was encountered.
*/
- (void)connectionDidNotOpen:(XGConnection *)connection withError:(NSError *)error NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method connectionDidClose:
	@abstract This method is called as soon as the connection enters the Closed
	state from the Open state.
	@param connection The connection that closed.
*/
- (void)connectionDidClose:(XGConnection *)connection NS_DEPRECATED_MAC(10_4, 10_7);

@end

