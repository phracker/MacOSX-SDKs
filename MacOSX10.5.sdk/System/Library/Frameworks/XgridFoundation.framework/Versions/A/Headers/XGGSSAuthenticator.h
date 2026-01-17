//
//  XGGSSAuthenticator.h
//  GridFoundation
//
//  Copyright 2004 Apple Computer, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "XGAuthenticator.h"

@class XGGSSAuthenticatorInternal;

/*!
@header XGGSSAuthenticator.h
 
 This header file describes the interface of the authenticator that handles
 the Xgrid GSS authentication protocol.
 */

/*!
@class XGGSSAuthenticator

@abstract An XGGSSAuthenticator is used by the XGConnection object
to perform GSSAPI authentication.  It is a concrete subclass of the
abstract XGAuthenticator class.
*/

@interface XGGSSAuthenticator : XGAuthenticator
{
	@private
	XGGSSAuthenticatorInternal *_internal1;
}

/*!
	@method setServicePrincipal:
	@abstract Sets the service principal of the controller with which to authenticate.
	@param servicePrincipal The service principal. Must not be nil.
*/
- (void)setServicePrincipal:(NSString *)servicePrincipal;

/*!
	@method servicePrincipal
	@abstract Returns the service principal associated with the receiver.
	@result The service principal.
*/
- (NSString *)servicePrincipal;

@end
