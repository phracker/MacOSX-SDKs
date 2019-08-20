/*
    CBIdentity.h
    Collaboration.framework
  
    Copyright (c) 2006-2012 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>

NS_ASSUME_NONNULL_BEGIN

@class CBUserIdentity;
@class CBGroupIdentity;
@class CBIdentityAuthority;
@class NSArray;
@class NSData;
@class NSImage;
@class NSString;


/* CBIdentity - A wrapper for CSIdentityRef */

NS_CLASS_AVAILABLE(10_5, NA)
@interface CBIdentity : NSObject <NSCoding, NSCopying> {
    @protected
        id _reserved[4];
}



/* Finding Identities */

/* Return the identity with the given name, from the specified authority, nil if not found. */
/* The name is compared against all valid identity names, including full names, posix names, email addresses, and aliases. */
+ (nullable CBIdentity *)identityWithName:(NSString *)name authority:(CBIdentityAuthority *)authority;

/* Return the identity with the given UUID, from the specified authority, nil if not found. */
+ (nullable CBIdentity *)identityWithUniqueIdentifier:(NSUUID *)uuid authority:(CBIdentityAuthority *)authority NS_AVAILABLE(10_11, NA);

/* Return the identity with the given UUID, from the specified authority, nil if not found. */
+ (nullable CBIdentity *)identityWithUUIDString:(NSString *)uuid authority:(CBIdentityAuthority *)authority NS_DEPRECATED(10_5, 10_11, NA, NA, "Use +identityWithUniqueIdentifier:authority: instead.");

/* Return the identity specified in the given persistent reference data, nil if not found. 
   A persistent reference is an opaque blob suitable for persistent storage. */
+ (nullable CBIdentity *)identityWithPersistentReference:(NSData *)data;

/* Return the identity with the given CSIdentityRef, for interoperability with CoreServices/CSIdentity API */
+ (CBIdentity *)identityWithCSIdentity:(CSIdentityRef)csIdentity NS_SWIFT_UNAVAILABLE("CSIdentity is not available in Swift.");



/* Identity Attributes */

/* The identity's authority */
@property (readonly, nonatomic) CBIdentityAuthority *authority;

/* The identity's UUID */
@property (readonly, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE(10_11, NA);

/* The identity's UUID in string form */
@property (readonly, nonatomic) NSString *UUIDString NS_DEPRECATED(10_5, 10_11, NA, NA, "Use the uniqueIdentifier property instead.");

/* The identity's full name */
@property (readonly, nonatomic) NSString *fullName;

/* The identity's POSIX ("short") name */
@property (readonly, nonatomic) NSString *posixName;

/* Return an array of the identity's aliases (alternate names) */
@property (readonly, nonatomic) NSArray<NSString *> *aliases;

/* The identity's primary email address, or nil */
@property (nullable, readonly, nonatomic) NSString *emailAddress;

/* The identity's image */
@property (nullable, readonly, nonatomic) NSImage *image;

/* Return a presistent reference data blob for use in an ACL or other storage */
@property (nullable, readonly, nonatomic) NSData *persistentReference;

/* Hidden identities include "system" users and groups such as root, www, wheel */
@property (readonly, nonatomic, getter=isHidden) BOOL hidden;

/* Return YES if the identity is a member of the specified group */
- (BOOL)isMemberOfGroup:(CBGroupIdentity *)group;

/* Return the corresponding CSIdentityRef (for interoperability with Identity Services API) */
@property (readonly) CSIdentityRef CSIdentity NS_SWIFT_UNAVAILABLE("CSIdentity is not available in Swift.");

@end




/* CBUserIdentity - an identity with password and/or certificate credentials */

NS_CLASS_AVAILABLE(10_5, NA)
@interface CBUserIdentity : CBIdentity <NSCoding, NSCopying>

/* Return the user identity with the given Posix UID from the specified authority, nil if not found */
+ (nullable CBUserIdentity *)userIdentityWithPosixUID:(uid_t)uid authority:(CBIdentityAuthority *)authority;

/* Return the Posix UID of the user identity */
@property (readonly, nonatomic) uid_t posixUID;

/* The user's authentication certificate; nil if no cert */
@property (nullable, readonly, nonatomic) SecCertificateRef certificate;

/* Return YES if the user can authenticate, NO if authentication is not allowed  */
@property (readonly, nonatomic, getter=isEnabled) BOOL enabled;

/* Return YES if the given password is correct for this user. */
- (BOOL)authenticateWithPassword:(NSString *)password;

@end




/* CBGroupIdentity - an identity with membership */

NS_CLASS_AVAILABLE(10_5, NA)
@interface CBGroupIdentity : CBIdentity

/* Return the group identity with the given Posix GID from the specified authority, nil if not found */
+ (nullable CBGroupIdentity *)groupIdentityWithPosixGID:(gid_t)gid authority:(CBIdentityAuthority *)authority;

/* Return the Posix GID of the group identity */
@property (readonly, nonatomic) gid_t posixGID;

/* The group's members, as an array of CSIdentityRef values */
@property (nullable, readonly, nonatomic) NSArray *members NS_DEPRECATED(10_5, 10_11, NA, NA, "Use the memberIdentities property instead.") NS_SWIFT_UNAVAILABLE("Use the memberIdentities property instead. CSIdentity is not available in Swift.");

/* The group's members, as an array of CBIdentity objects */
@property (readonly, nonatomic) NSArray<CBIdentity *> *memberIdentities NS_AVAILABLE(10_11, NA);
@end

NS_ASSUME_NONNULL_END
