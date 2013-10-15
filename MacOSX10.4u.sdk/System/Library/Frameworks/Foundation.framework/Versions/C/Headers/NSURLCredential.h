/*	
    NSURLCredential.h
    Copyright (C) 2003-2005, Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if defined(MAC_OS_X_VERSION_10_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2)

#import <Foundation/NSObject.h>

@class NSString;

/*!
    @enum NSURLCredentialPersistence
    @abstract Constants defining how long a credential will be kept around
    @constant NSURLCredentialPersistenceNone This credential won't be saved.
    @constant NSURLCredentialPersistenceForSession This credential will only be stored for this session.
    @constant NSURLCredentialPersistencePermanent This credential will be stored permanently and shared with other applications.
*/

typedef enum {
    NSURLCredentialPersistenceNone,
    NSURLCredentialPersistenceForSession,
    NSURLCredentialPersistencePermanent
} NSURLCredentialPersistence;

@class NSURLCredentialInternal;

/*!
    @class NSURLCredential
    @discussion This class is an immutable object representing an
    authentication credential - a user and a password.
*/

@interface NSURLCredential : NSObject <NSCopying>
{
    @private
    NSURLCredentialInternal *_internal;
}

/*!
    @method initWithUser:password:persistence:
    @abstract Initialize a NSURLCredential with a user and password
    @param user the username
    @param password the password
    @param persistence enum that says to store per session, permanently or not at all
    @result The initialized NSURLCredential
*/
- (id)initWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;

/*!
    @method credentialWithUser:password:persistence:
    @abstract Create a new NSURLCredential with a user and password
    @param user the username
    @param password the password
    @param persistence enum that says to store per session, permanently or not at all
    @result The new autoreleased NSURLCredential
*/
+ (NSURLCredential *)credentialWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;

/*!
    @method user
    @abstract Get the username
    @result The user string
*/
- (NSString *)user;

/*!
    @method password
    @abstract Get the password
    @result The password string
    @discussion This method might actually attempt to retrieve the
    password from an external store, possible resulting in prompting,
    so do not call it unless needed.
*/
- (NSString *)password;

/*!
    @method hasPassword
    @abstract Find out if this credential has a password, without trying to get it
    @result YES if this credential has a password, otherwise NO
    @discussion If this credential's password is actually kept in an
    external store, the password method may return nil even if this
    method returns YES, since getting the password may fail, or the
    user may refuse access.
*/
- (BOOL)hasPassword;

/*!
    @method persistence
    @abstract Determine whether this credential is or should be stored persistently
    @result A value indicating whether this credential is stored permanently, per session or not at all.
*/
- (NSURLCredentialPersistence)persistence;

@end

#endif
