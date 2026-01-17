/*
    CBIdentity.h
    Collaboration.framework
  
    Copyright 2006 Apple Computer. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreServices/CoreServices.h>


@class CBUserIdentity;
@class CBGroupIdentity;
@class CBIdentityAuthority;
@class NSArray;
@class NSData;
@class NSImage;
@class NSString;


/* CBIdentity - A wrapper for CSIdentityRef */

@interface CBIdentity : NSObject <NSCoding, NSCopying> {
    @protected
        id _reserved[4];
}



/* Finding Identities */

/* Return the identity with the given name, from the specified authority, nil if not found. */
/* The name is compared against all valid identity names, including full names, posix names, email addresses, and aliases. */
+ (CBIdentity *)identityWithName:(NSString *)name authority:(CBIdentityAuthority *)authority;

/* Return the identity with the given UUID, from the specified authority, nil if not found. */
+ (CBIdentity *)identityWithUUIDString:(NSString *)uuid authority:(CBIdentityAuthority *)authority;

/* Return the identity specified in the given persistent reference data, nil if not found. 
   A persistent reference is an opaque blob suitable for persistent storage. */
+ (CBIdentity *)identityWithPersistentReference:(NSData *)data;

/* Return the identity with the given CSIdentityRef, for interoperability with CoreServices/CSIdentity API */
+ (CBIdentity *)identityWithCSIdentity:(CSIdentityRef)csIdentity;



/* Identity Attributes */

/* The identity's authority */
- (CBIdentityAuthority *)authority;

/* The identity's UUID in string form */
- (NSString *)UUIDString;

/* The identity's full name */
- (NSString *)fullName;

/* The identity's POSIX ("short") name */
- (NSString *)posixName;

/* Return an array of the identity's aliases (alternate names) */
- (NSArray *)aliases;

/* The identity's primary email address, or nil */
- (NSString *)emailAddress;

/* The identity's image */
- (NSImage *)image;

/* Return a presistent reference data blob for use in an ACL or other storage */
- (NSData *)persistentReference;

/* Hidden identities include "system" users and groups such as root, www, wheel */
- (BOOL)isHidden;

/* Return TRUE if the identity is a member of the specified group */
- (BOOL)isMemberOfGroup:(CBGroupIdentity *)group;

/* Return the corresponding CSIdentityRef (for interoperability with Identity Services API) */
- (CSIdentityRef)CSIdentity;

@end




/* CBUserIdentity - an identity with password and/or certificate credentials */

@interface CBUserIdentity : CBIdentity <NSCoding, NSCopying>

/* Return the user identity with the given Posix UID from the specified authority, nil if not found */
+ (CBUserIdentity *)userIdentityWithPosixUID:(uid_t)uid authority:(CBIdentityAuthority *)authority;

/* Return the Posix UID of the user identity */
- (uid_t)posixUID;

/* The user's authentication certificate; nil if no cert */
- (SecCertificateRef)certificate;

/* Return TRUE if the user can authenticate, FALSE if authentication is not allowed  */
- (BOOL)isEnabled;

/* Return TRUE if the given password is correct for this user. */
- (BOOL)authenticateWithPassword:(NSString *)password;

@end




/* CBGroupIdentity - an identity with membership */

@interface CBGroupIdentity : CBIdentity

/* Return the group identity with the given Posix GID from the specified authority, nil if not found */
+ (CBGroupIdentity *)groupIdentityWithPosixGID:(gid_t)gid authority:(CBIdentityAuthority *)authority;

/* Return the Posix GID of the group identity */
- (gid_t)posixGID;

/* The group's members, as an array of CBIdentity objects */
- (NSArray *)members;

@end
