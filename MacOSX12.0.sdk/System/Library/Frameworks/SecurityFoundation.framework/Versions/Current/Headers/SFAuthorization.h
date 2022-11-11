/*
	SFAuthorization.h
	SecurityFoundation
	Copyright (c) 2000-2005, Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFAUTHORIZATION_H_
#define _SFAUTHORIZATION_H_

#import <Foundation/Foundation.h>
#import <Security/Authorization.h>

/*!
	@class SFAuthorization 
    @abstract SFAuthorization APIs are used for implementing access control in applications and daemons. It has NSCoder support for proxied objects SFAuthorization is a wrapper for using the Authorization API.
*/
@interface SFAuthorization : NSObject <NSSecureCoding>
{
@private
	AuthorizationRef _authorization;
    id _reserved;
}

/*!
	@method authorization
	@abstract Returns an authorization object initialized with a default environment, flags and rights.
*/
+ (id)authorization API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method authorizationRef
	@abstract Returns the AuthorizationRef for this SFAuthorization.
*/
- (AuthorizationRef)authorizationRef API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method authorizationWithFlags:rights:environment:
	@abstract Returns an authorization object initialized with the specified flags, rights and environment.
	@param flags Authorization flags.
    @param rights (input/optional) An AuthorizationItemSet containing rights for which authorization is being requested.  If none are specified the resulting AuthorizationRef will authorize nothing at all.
    @param environment (input/optional) An AuthorizationItemSet containing enviroment state used when making the autorization decision.  See the AuthorizationEnvironment type for details.
*/
+ (id)authorizationWithFlags:(AuthorizationFlags)flags rights:(const AuthorizationRights *)rights environment:(const AuthorizationEnvironment *)environment API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method initWithFlags:rights:environment:
	@abstract Initializes an authorization object specified flags, rights and environment.
	@param flags Authorization flags.
    @param rights (input/optional) An AuthorizationItemSet containing rights for which authorization is being requested.  If none are specified the resulting AuthorizationRef will authorize nothing at all.
    @param environment (input/optional) An AuthorizationItemSet containing enviroment state used when making the autorization decision.  See the AuthorizationEnvironment type for details.
*/
- (id)initWithFlags:(AuthorizationFlags)flags rights:(const AuthorizationRights *)rights environment:(const AuthorizationEnvironment *)environment API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method init
	@abstract Initializes an authorization object initialized with a default environment, flags and rights.
*/
-(id)init API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method invalidateCredentials
	@abstract Calling this will prevent any rights that were obtained by this object to be preserved. It effectively locks down all potentially shared authorizations.
*/
- (void)invalidateCredentials API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
 @method obtainWithRight:flags:
 @abstract Call obtainWithRight to gain a right to have access to a privilege operation. On success, YES is returned.
 @param rightName The name of an authorization right.
 @param flags Authorization flags.
 @param error Resulting error.
 */
- (BOOL)obtainWithRight:(AuthorizationString)rightName flags:(AuthorizationFlags)flags error:(NSError**)error API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method obtainWithRights:flags:environment:authorizedRights:error:
	@abstract Call obtainWithRights to gain the rights to have access to privileged operations. On success, YES is returned.
	@param flags Authorization flags.
    @param rights (input) A rights set (see AuthorizationCreate).
    @param environment (input/optional) An AuthorizationItemSet containing enviroment state used when making the autorization decision.  See the AuthorizationEnvironment type for details.
    @param authorizedRights (output/optional) A pointer to a newly allocated AuthorizationInfoSet in which the authorized subset of rights are returned (authorizedRights should be deallocated by calling AuthorizationFreeInfoSet() when it is no longer needed).  If NULL the only information returned is the status.  Note that if the kAuthorizationFlagPreAuthorize flag was specified rights that could not be preauthorized are returned in authorizedRights, but their flags contains the kAuthorizationFlagCanNotPreAuthorize bit.
	@param error Resulting error.
*/
- (BOOL)obtainWithRights:(const AuthorizationRights *)rights flags:(AuthorizationFlags)flags environment:(const AuthorizationEnvironment *)environment authorizedRights:(AuthorizationRights **)authorizedRights error:(NSError**)error API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

@interface SFAuthorization (SFAuthorizationDeprecated)

/*!
    DEPRECATED: Use obtainWithRights:flags:environment:authorizedRights:error:
    @method permitWithRights:flags:environment:authorizedRights:
	@abstract Call permitWithRights to gain the rights to have access to privileged operations and to obtain the result.
	@param flags Authorization flags.
    @param rights (input) A rights set (see AuthorizationCreate).
    @param environment (input/optional) An AuthorizationItemSet containing enviroment state used when making the autorization decision.  See the AuthorizationEnvironment type for details.
    @param authorizedRights (output/optional) A pointer to a newly allocated AuthorizationInfoSet in which the authorized subset of rights are returned (authorizedRights should be deallocated by calling AuthorizationFreeInfoSet() when it is no longer needed).  If NULL the only information returned is the status.  Note that if the kAuthorizationFlagPreAuthorize flag was specified rights that could not be preauthorized are returned in authorizedRights, but their flags contains the kAuthorizationFlagCanNotPreAuthorize bit.
*/
- (OSStatus)permitWithRights:(const AuthorizationRights *)rights flags:(AuthorizationFlags)flags environment:(const AuthorizationEnvironment *)environment authorizedRights:(AuthorizationRights *)authorizedRights DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    DEPRECATED: Use obtainWithRight:flags:error:
	@method permitWithRight:flags:
	@abstract Call permitWithRight to gain a right to have access to a privilege operation.
	@param rightName The name of an authorization right.
	@param flags Authorization flags.
*/
- (OSStatus)permitWithRight:(AuthorizationString)rightName flags:(AuthorizationFlags)flags DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

#endif /* !_SFAUTHORIZATION_H_ */

