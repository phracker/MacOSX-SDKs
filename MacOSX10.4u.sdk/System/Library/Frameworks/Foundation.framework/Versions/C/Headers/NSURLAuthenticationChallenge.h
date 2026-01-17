/*	
    NSURLAuthenticationChallenge.h
    Copyright (C) 2003-2005, Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if defined(MAC_OS_X_VERSION_10_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2)

#import <Foundation/NSObject.h>

@class NSURLAuthenticationChallenge;
@class NSURLCredential;
@class NSURLProtectionSpace;
@class NSURLResponse;
@class NSError;

/*!  
    @protocol NSURLAuthenticationChallengeSender 
    @discussion This protocol represents the sender of an
    authentication challenge. It has methods to provide a credential,
    to continue without any credential, getting whatever failure
    result would happen in that case, or to cancel.
*/

@protocol NSURLAuthenticationChallengeSender <NSObject>

/*!
    @method useCredential:forAuthenticationChallenge:
*/
- (void)useCredential:(NSURLCredential *)credential forAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
    @method continueWithoutCredentialForAuthenticationChallenge:
*/
- (void)continueWithoutCredentialForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
    @method cancelAuthenticationChallenge:
*/
- (void)cancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

@end

@class NSURLAuthenticationChallengeInternal;

/*!
    @class NSURLAuthenticationChallenge
    @discussion This class represents an authentication challenge. It
    provides all the information about the challenge, and has a method
    to indicate when it's done.
*/

@interface NSURLAuthenticationChallenge : NSObject
{
@private
    NSURLAuthenticationChallengeInternal *_internal;
}

/*!
    @method initWithProtectionSpace:proposedCredential:previousFailureCount:failureResponse:error:
    @abstract Initialize an authentication challenge 
    @param space The NSURLProtectionSpace to use
    @param credential The proposed NSURLCredential for this challenge, or nil
    @param previousFailureCount A count of previous failures attempting access.
    @param response The NSURLResponse for the authentication failure, if applicable, else nil
    @param error The NSError for the authentication failure, if applicable, else nil
    @result An authentication challenge initialized with the specified parameters
*/
- (id)initWithProtectionSpace:(NSURLProtectionSpace *)space proposedCredential:(NSURLCredential *)credential previousFailureCount:(int)previousFailureCount failureResponse:(NSURLResponse *)response error:(NSError *)error sender:(id<NSURLAuthenticationChallengeSender>)sender;

/*!
    @method initWithAuthenticationChallenge:
    @abstract Initialize an authentication challenge copying all parameters from another one.
    @param challenge
    @result A new challenge initialized with the parameters from the passed in challenge
    @discussion This initializer may be useful to subclassers that want to proxy
    one type of authentication challenge to look like another type.
*/
- (id)initWithAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge sender:(id<NSURLAuthenticationChallengeSender>)sender;

/*!
    @method protectionSpace
    @abstract Get a description of the protection space that requires authentication
    @result The protection space that needs authentication
*/
- (NSURLProtectionSpace *)protectionSpace;

/*!
    @method proposedCredential
    @abstract Get the proposed credential for this challenge
    @result The proposed credential
    @discussion proposedCredential may be nil, if there is no default
    credential to use for this challenge (either stored or in the
    URL). If the credential is not nil and returns YES for
    hasPassword, this means the NSURLConnection thinks the credential
    is ready to use as-is. If it returns NO for hasPassword, then the
    credential is not ready to use as-is, but provides a default
    username the client could use when prompting.
*/
- (NSURLCredential *)proposedCredential;

/*!
    @method previousFailureCount
    @abstract Get count of previous failed authentication attempts
    @result The count of previous failures
*/
- (int)previousFailureCount;

/*!
    @method failureResponse
    @abstract Get the response representing authentication failure.
    @result The failure response or nil
    @discussion If there was a previous authentication failure, and
    this protocol uses responses to indicate authentication failure,
    then this method will return the response. Otherwise it will
    return nil.
*/
- (NSURLResponse *)failureResponse;

/*!
    @method error
    @abstract Get the error representing authentication failure.
    @discussion If there was a previous authentication failure, and
    this protocol uses errors to indicate authentication failure,
    then this method will return the error. Otherwise it will
    return nil.
*/
- (NSError *)error;

/*!
    @method sender
    @abstract Get the sender of this challenge
    @result The sender of the challenge
    @discussion The sender is the object you should reply to when done processing the challenge.
*/
- (id<NSURLAuthenticationChallengeSender>)sender;

@end

#endif
