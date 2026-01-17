//
//  XGAuthenticator.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class XGAuthenticatorInternal;

/*!
	@header XGAuthenticator.h
 
	This header file describes the abstract interface of a generic authenticator.
	This interface is intended to be used by concrete authenticator subclasses.
*/

/*!
	@enum XGAuthenticatorState
 
	@discussion The XGAuthenticatorState enum defines constants that are used by
	the authenticator to specify which state it is in.
 
	@constant XGAuthenticatorStateUnauthenticated The initial state of the
	authenticator.
 
	@constant XGAuthenticatorStateAuthenticating The authenticator enters this
	state immediately following reception of the -startAuthenticating message.
 
	@constant XGAuthenticatorStateAuthenticated The authenticator enters this
	state immediately following the successful authentication of the connection.
 
	@constant XGAuthenticatorStateFailed The authenticator enters this state
	immediately following an unsucessful authentication of the connection.
*/
typedef enum {
	XGAuthenticatorStateUnauthenticated = 0,
	XGAuthenticatorStateAuthenticating,
	XGAuthenticatorStateAuthenticated,
	XGAuthenticatorStateFailed
} XGAuthenticatorState;

/*!
	@class XGAuthenticator
 
	@abstract An XGAuthenticator class is used by the XGConnection class to perform
	authentication of the connection.
 
	@discussion The XGAuthenticator class is created by an Xgrid client using the
	users credentials and then set on an XGConnection object. The authenticator
	starts in the Unauthenticated state, and then enters the Authenticating state
	when the connection is ready to be authenticated.  If the authentication is
	successful the authenticator enters the Authenticated state.  If the
	authentication is unsucessful the authenticator enters the Failed state.
 
	This is an abstract class.  Subclasses must override the specifed methods.
*/
@interface XGAuthenticator : NSObject
{
	@private
	XGAuthenticatorInternal *_internal;
}

/*!
	@method profileURI
	@abstract Returns the profileURI of the authentication channel.
	@result The profileURI.
*/
+ (NSString *)profileURI;

/*!
	@method setDelegate:
	@abstract Sets the delegate of the receiver.
	@discussion The delegate is not retained.  If the delegate implements any of
	the methods in the XGAuthenticatorDelegate protocol then it will receive
	callbacks when connection events occur, prior to the notification of key-value
	observers.
*/
- (void)setDelegate:(id)delegate;

/*!
	@method delegate
	@abstract Returns the delegate of the receiver.
	@result The delegate of the receiver.
*/
- (id)delegate;

/*!
	@method error
	@abstract Returns the error of the receiver.
	@result The error of the receiver.
	@discussion The error is set if the authenticator enters the Failed state.
*/
- (NSError *)error;

/*!
	@method state
	@abstract Returns the state of the receiver.
	@result The state of the receiver.
*/
- (XGAuthenticatorState)state;

/*
	Overrides -- the following methods must be implemented by subclasses.
*/
#pragma mark @interface XGAuthenticator (Overrides)

/*!
	@method piggyback
	@abstract Returns the piggyback message to be sent when opening the
	authentication channel.
	@result The piggyback to be sent.
*/
- (NSString *)piggyback;

/*!
	@method beginAuthentication:
	@abstract Called once the authentication channel has been opened and the reply
	to the piggyback has been received.
	@param piggybackReply The reply to the piggyback.
*/
- (void)beginAuthentication:(NSString *)piggybackReply;

/*!
	@method receiveData:
	@abstract Called everytime data arrives on the authentication channel.
	@param data The received data.
*/
- (void)receiveData:(NSData *)data;

/*
	Protected -- the following methods must only be called by subclasses.
*/
#pragma mark @interface XGAuthenticator (Protected)

/*!
	@method finishAuthentication
	@abstract Called once the authentication has completed sucessfully.
*/
- (void)finishAuthentication;

/*!
	@method sendData:
	@abstract Sends the data on the authentication channel.
	@param data The data to send.
*/
- (void)sendData:(NSData *)data; // only to be called by subclasses

/*!
	@method failWithError:
	@abstract Causes the authenticator to fail and sets the error.
	@param error The error that caused the failure.
*/
- (void)failWithError:(NSError *)error; // only to be called by subclasses

@end

/*!
	@protocol XGAuthenticatorDelegate
	@discussion The XGAuthenticatorDelegate delegate is used to report the status
	of the authenticator.
*/
@interface NSObject (XGAuthenticatorDelegate)

/*!
	@method authenticatorDidAuthenticate:
	@abstract This method is called as soon as the connection enters the
	Authenticated state.
	@param authenticator The authenticator that authenticated.
*/
- (void)authenticatorDidAuthenticate:(XGAuthenticator *)authenticator;

/*!
	@method authenticatorDidNotAuthenticate:
	@abstract This method is called as soon as the connection enters the
	Failed state.
	@param authenticator The authenticator that didn't authenticate.
*/
- (void)authenticatorDidNotAuthenticate:(XGAuthenticator *)authenticator;

@end
