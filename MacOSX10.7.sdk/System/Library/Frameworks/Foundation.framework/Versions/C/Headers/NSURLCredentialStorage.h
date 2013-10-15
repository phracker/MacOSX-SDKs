/*	
    NSURLCredentialStorage.h
    Copyright (c) 2003-2011, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSDictionary;
@class NSString;
@class NSURLCredential;
@class NSURLProtectionSpace;

@class NSURLCredentialStorageInternal;

/*!
    @class NSURLCredentialStorage
    @discussion NSURLCredentialStorage implements a singleton object (shared instance) which manages the shared credentials cache. Note: Whereas in Mac OS X any application can access any credential with a persistence of NSURLCredentialPersistencePermanent provided the user gives permission, in iPhone OS an application can access only its own credentials.
*/

@interface NSURLCredentialStorage : NSObject
{
    @private
    NSURLCredentialStorageInternal *_internal;
}

/*!
    @method sharedCredentialStorage
    @abstract Get the shared singleton authentication storage
    @result the shared authentication storage
*/
+ (NSURLCredentialStorage *)sharedCredentialStorage;

/*!
    @method credentialsForProtectionSpace:
    @abstract Get a dictionary mapping usernames to credentials for the specified protection space.
    @param protectionSpace An NSURLProtectionSpace indicating the protection space for which to get credentials
    @result A dictionary where the keys are usernames and the values are the corresponding NSURLCredentials.
*/
- (NSDictionary *)credentialsForProtectionSpace:(NSURLProtectionSpace *)space;

/*!
    @method allCredentials
    @abstract Get a dictionary mapping NSURLProtectionSpaces to dictionaries which map usernames to NSURLCredentials
    @result an NSDictionary where the keys are NSURLProtectionSpaces
    and the values are dictionaries, in which the keys are usernames
    and the values are NSURLCredentials
*/
- (NSDictionary *)allCredentials;

/*!
    @method setCredential:forProtectionSpace:
    @abstract Add a new credential to the set for the specified protection space or replace an existing one.
    @param credential The credential to set.
    @param space The protection space for which to add it. 
    @discussion Multiple credentials may be set for a given protection space, but each must have
    a distinct user. If a credential with the same user is already set for the protection space,
    the new one will replace it.
*/
- (void)setCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

/*!
    @method removeCredential:forProtectionSpace:
    @abstract Remove the a credential from the set for the specified protection space.
    @param credential The credential to remove.
    @param space The protection space for which a credential should be removed
    @discussion The credential is removed from both persistent and temporary storage.
*/
- (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

/*!
    @method defaultCredentialForProtectionSpace:
    @abstract Get the default credential for the specified protection space.
    @param space The protection space for which to get the default credential.
*/
- (NSURLCredential *)defaultCredentialForProtectionSpace:(NSURLProtectionSpace *)space;

/*!
    @method setDefaultCredential:forProtectionSpace:
    @abstract Set the default credential for the specified protection space.
    @param credential The credential to set as default.
    @param space The protection space for which the credential should be set as default.
    @discussion If the credential is not yet in the set for the protection space, it will be added to it.
*/
- (void)setDefaultCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

@end

/*!
    @const NSURLCredentialStorageChangedNotification
    @abstract This notification is sent on the main thread whenever
    the set of stored credentials changes.
*/
FOUNDATION_EXPORT NSString *const NSURLCredentialStorageChangedNotification;

