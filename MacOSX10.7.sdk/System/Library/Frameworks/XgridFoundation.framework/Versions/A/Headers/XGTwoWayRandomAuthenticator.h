//
//  XGTwoWayRandomAuthenticator.h
//  GridFoundation
//
//  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "XGAuthenticator.h"

@class XGTwoWayRandomAuthenticatorInternal;

/*!
	@header XGTwoWayRandomAuthenticator.h
 
	This header file describes the interface of the authenticator that handles
	the two-way-random mutal authentication protocol.
*/

/*!
	@class XGTwoWayRandomAuthenticator
 
	@abstract An XGTwoWayRandomAuthenticator is used by the XGConnection object
	to perform two-way-random authentication.  It is a concrete subclass of the
	abstract XGAuthenticator superclass.
*/
@interface XGTwoWayRandomAuthenticator : XGAuthenticator
{
	@private
	XGTwoWayRandomAuthenticatorInternal *_internal1;
}

/*!
	@method setUsername:
	@abstract Sets the username with which to authenticate.
	@param username The username. Must not be nil.
*/
- (void)setUsername:(NSString *)username NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method username
	@abstract Returns the username of the receiver.
	@result The username.
*/
- (NSString *)username NS_DEPRECATED_MAC(10_4, 10_7);

/*!
	@method setPassword
	@abstract Sets the password with which to authenticate.
	@param password The password. Must not be nil.
*/
- (void)setPassword:(NSString *)password NS_DEPRECATED_MAC(10_4, 10_7);

@end
