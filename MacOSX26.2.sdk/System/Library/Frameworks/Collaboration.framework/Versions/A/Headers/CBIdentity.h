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

    
    /// A `CBIdentity` object is used for accessing the attributes of an
    /// identity stored in an identity authority. You can use an identity object
    /// for finding identities, and storing them in an access control list
    /// (ACL). If you need to edit these attributes, take advantage of the
    /// `CSIdentity` class in Core Services.
    ///
    /// You can obtain a `CBIdentity` object from one of the following class
    /// factory methods: ``CBIdentity/identityWithName:authority:``,
    /// ``CBIdentity/identityWithUUIDString:authority:``,
    /// ``CBIdentity/identityWithPersistentReference:``, or
    /// ``CBIdentity/identityWithCSIdentity:``.
    ///
    /// A `CBIdentity` object has methods to support for interoperability with
    /// the Core Services Identity API. Send ``CBIdentity/CSIdentity`` to your
    /// `CBIdentity` object to return an opaque object for use in the Core
    /// Services Identity API. Similarly, call
    /// ``CBIdentity/identityWithCSIdentity:`` to use an Core Services Identity
    /// opaque object in the Collaboration framework.
    ///
    /// There are two subclasses of `CBIdentity`: `CBGroupIdentity` and
    /// `CBUserIdentity`. If you are working specifically with a group identity,
    /// use `CBGroupIdentity`. Similarly, if you are working with a user
    /// identity, use `CBUserIdentity`.
NS_CLASS_AVAILABLE(10_5, NA)
@interface CBIdentity : NSObject <NSCoding, NSCopying> {
    @protected
        id _reserved[4];
}



/* Finding Identities */

/* Return the identity with the given name, from the specified authority, nil if not found. */
/* The name is compared against all valid identity names, including full names, posix names, email addresses, and aliases. */

/// Returns the identity object with the given name from the specified identity
/// authority.
///
/// The name is compared against all valid identity names, including full names,
/// short names, email addresses, and aliases.
///
/// - Parameters:
///   - name: The name of the identity.
///
///   - authority: The identity authority to search.
///
/// - Returns: The identity object, or `nil` if no identity is found with the
/// specified name.
+ (nullable CBIdentity *)identityWithName:(NSString *)name authority:(CBIdentityAuthority *)authority;


/* Return the identity with the given UUID, from the specified authority, nil if not found. */
+ (nullable CBIdentity *)identityWithUniqueIdentifier:(NSUUID *)uuid authority:(CBIdentityAuthority *)authority NS_AVAILABLE(10_11, NA);

/* Return the identity with the given UUID, from the specified authority, nil if not found. */

/// Returns the identity object with the given UUID from the specified identity
/// authority.
///
/// - Parameters:
///   - uuid: The UUID of the identity you are searching for.
///
///   - authority: The identity authority to search.
///
/// - Returns: The identity object, or `nil` if no identity is found with the
/// matching criteria.
+ (nullable CBIdentity *)identityWithUUIDString:(NSString *)uuid authority:(CBIdentityAuthority *)authority NS_DEPRECATED(10_5, 10_11, NA, NA, "Use +identityWithUniqueIdentifier:authority: instead.");

/* Return the identity specified in the given persistent reference data, nil if not found. 
   A persistent reference is an opaque blob suitable for persistent storage. */

/// Returns the identity object matching the persistent reference data.
///
/// A persistent reference is an opaque data object suitable for persistent
/// storage.
///
/// - Parameters:
///   - data: The persistent data object that refers to an identity.
///
/// - Returns: The identity object matching the persistent data object, or `nil`
/// if the identity is not found.
+ (nullable CBIdentity *)identityWithPersistentReference:(NSData *)data;

/* Return the identity with the given CSIdentityRef, for interoperability with CoreServices/CSIdentity API */

/// Returns an identity object created from the specified Core Services Identity
/// opaque object.
///
/// This method is used for interoperability with the Core Services Identity
/// API.
///
/// - Parameters:
///   - csIdentity: The Core Services Identity opaque object.
///
/// - Returns: The identity object for use with the Collaboration framework.
+ (CBIdentity *)identityWithCSIdentity:(CSIdentityRef)csIdentity NS_SWIFT_UNAVAILABLE("CSIdentity is not available in Swift.");




/* Identity Attributes */

/* The identity's authority */

/// Returns the identity authority where the identity is stored.
///
/// - Returns: The identity authority where the identity is stored.
@property (readonly, nonatomic) CBIdentityAuthority *authority;

/* The identity's UUID */
@property (readonly, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE(10_11, NA);

/* The identity's UUID in string form */

/// Returns the UUID of the identity as a string.
///
/// The UUID string is generated so it is unique across all identity
/// authorities. When storing ACLs, one method is to store the UUID of each
/// identity. However, it is recommended that you use a persistent data object
/// instead (see ``CBIdentity/persistentReference``).
///
/// - Returns: The UUID string of the identity.
@property (readonly, nonatomic) NSString *UUIDString NS_DEPRECATED(10_5, 10_11, NA, NA, "Use the uniqueIdentifier property instead.");

/* The identity's full name */

/// Returns the full name of the identity.
///
/// - Returns: The full name for the identity.
@property (readonly, nonatomic) NSString *fullName;

/* The identity's POSIX ("short") name */

/// Returns the POSIX name of the identity.
///
/// The POSIX name is also referred to as the “short name” for an identity. It
/// can only contain the characters A-Z, a-z, 0-9, -, _, ., and @.
///
/// - Returns: The POSIX name of the identity.
@property (readonly, nonatomic) NSString *posixName;

/* Return an array of the identity's aliases (alternate names) */

/// Returns an array of aliases (alternate names) for the identity.
///
/// An identity can have zero or more aliases. Like the full and short names,
/// two identities cannot share an alias.
///
/// - Returns: An array of `NSString` objects containing the alternate names for
/// the identity.
@property (readonly, nonatomic) NSArray<NSString *> *aliases;

/* The identity's primary email address, or nil */

/// Returns the email address of an identity.
///
/// - Returns: The email address of an identity or `nil` if none exists.
@property (nullable, readonly, nonatomic) NSString *emailAddress;

/* The identity's image */

/// Returns the image associated with an identity.
///
/// - Returns: The image associated with an identity, or `nil` if none exists.
@property (nullable, readonly, nonatomic) NSImage *image;

/* Return a presistent reference data blob for use in an ACL or other storage */

/// Returns a persistent reference to store a reference to an identity.
///
/// A persistent reference data object is an object generated from an identity.
/// Persistent data objects can be written to and read from a file, making them
/// extremely useful for storing identities in an ACL.
///
/// - Returns: A data object that uniquely references an identity.
@property (nullable, readonly, nonatomic) NSData *persistentReference;

/* Hidden identities include "system" users and groups such as root, www, wheel */


/// Returns a Boolean value indicating the state of the identity’s hidden property.
///
/// A hidden identity does not show up in the Identity Picker. A hidden identity refers
/// to system identities such as `root`, `www`, and `wheel`.
///
/// - Returns: <doc://com.apple.documentation/documentation/objectivec/yes> if the identity is hidden;
/// <doc://com.apple.documentation/documentation/objectivec/no> if it is not.
@property (readonly, nonatomic, getter=isHidden) BOOL hidden;

/* Return YES if the identity is a member of the specified group */

/// Returns a Boolean value indicating whether the identity is a member of the
/// specified group.
///
/// - Parameters:
///   - group: The group to check for membership.
///
/// - Returns: <doc://com.apple.documentation/documentation/objectivec/yes> if
/// the identity is a member of the group;
/// <doc://com.apple.documentation/documentation/objectivec/no> if it is not.
- (BOOL)isMemberOfGroup:(CBGroupIdentity *)group;

/* Return the corresponding CSIdentityRef (for interoperability with Identity Services API) */

/// Returns an opaque object for use with the Core Services Identity API.
///
/// This method, along with ``CBIdentity/identityWithCSIdentity:``, is used for
/// interoperability with the Core Services Identity API.
///
/// - Returns: The opaque object for use with the Core Services Identity API.
@property (readonly) CSIdentityRef CSIdentity NS_SWIFT_UNAVAILABLE("CSIdentity is not available in Swift.");

@end




/* CBUserIdentity - an identity with password and/or certificate credentials */


/// An object of the `CBUserIdentity` class represents a user identity and is
/// used for accessing the attributes of a user identity from an identity
/// authority. The principal attributes of `CBUserIdentity` are a POSIX user
/// identifier (UID), password, and certificate.
NS_CLASS_AVAILABLE(10_5, NA)
@interface CBUserIdentity : CBIdentity <NSCoding, NSCopying>

/* Return the user identity with the given Posix UID from the specified authority, nil if not found */

/// Returns the user identity with the given POSIX UID in the specified identity
/// authority.
///
/// - Parameters:
///   - uid: The UID of the identity you are searching for.
///
///   - authority: The identity authority to search.
///
/// - Returns: The user identity with the given UID in the specified identity
/// authority, or `nil` if no identity exists with the specified UID.
+ (nullable CBUserIdentity *)userIdentityWithPosixUID:(uid_t)uid authority:(CBIdentityAuthority *)authority;


/* Return the Posix UID of the user identity */

/// Returns the POSIX UID of the identity.
///
/// The POSIX UID is a integer that can identify a user within an identity
/// authority. UIDs are not guaranteed to be unique within an identity
/// authority.
///
/// - Returns: The POSIX UID of the identity.
@property (readonly, nonatomic) uid_t posixUID;

/* The user's authentication certificate; nil if no cert */

/// Returns the public authentication certificate associated with a user
/// identity.
///
/// The Collaboration framework supports certificate-based authentication in
/// addition to passwords. If a certificate is stored for a user identity, it
/// will be the default method of authentication.
///
/// When a .Mac account is associated with a user identity, the authentication
/// certificate is automatically downloaded from the .Mac servers.
///
/// - Returns: The public authentication certificate, or `nil` if none exists.
@property (nullable, readonly, nonatomic) SecCertificateRef certificate;

/* Return YES if the user can authenticate, NO if authentication is not allowed  */

/// Returns a Boolean value indicating whether the identity is allowed to authenticate.
///
/// If the identity does not have authentication credentials (a password or certificate),
/// it is not able to log in. However, an identity with authentication credentials does
/// not ensure that it is enabled. Any identity can be disabled.
///
/// - Returns: `TRUE` if the identity can authenticate; otherwise, `FALSE`.
@property (readonly, nonatomic, getter=isEnabled) BOOL enabled;

/* Return YES if the given password is correct for this user. */

/// Returns a Boolean value indicating whether the given password is correct for
/// the identity.
///
/// - Parameters:
///   - password: The password to test for the identity.
///
/// - Returns: `TRUE` if the password is correct; otherwise, `FALSE`.
- (BOOL)authenticateWithPassword:(NSString *)password;

@end




/* CBGroupIdentity - an identity with membership */


/// An object of the `CBGroupIdentity` class represents a group identity and is
/// used for viewing the attributes of group identities from an identity
/// authority. The principal attributes of a `CBGroupIdentity` object are a
/// POSIX group identifier (GID) and a list of members.
NS_CLASS_AVAILABLE(10_5, NA)
@interface CBGroupIdentity : CBIdentity

/// Returns the group identity with the given POSIX GID in the specified
/// identity authority.
///
/// - Parameters:
///   - gid: The GID of the group identity you are searching for.
///   - authority: An identity authority in which to search for the group identity.
/// - Returns: The group identity object with the given GID in the specified
/// identity authority, or `nil` if no identity exists with the specified GID.
///
/// ## See Also
///
/// - [Identity Services Programming Guide](https://developer.apple.com/library/archive/documentation/Networking/Conceptual/IdentityServices_ProgGuide/Introduction/Introduction.html#//apple_ref/doc/uid/TP40004490)
+ (nullable CBGroupIdentity *)groupIdentityWithPosixGID:(gid_t)gid authority:(CBIdentityAuthority *)authority;


/* Return the Posix GID of the group identity */

/// Returns the POSIX GID of the identity.
///
/// The POSIX GID is an integer that can identify a group within an identity
/// authority. GIDs are not guaranteed to be unique within an identity
/// authority.
///
/// - Returns: The POSIX GID of the group identity.
@property (readonly, nonatomic) gid_t posixGID;

/* The group's members, as an array of CSIdentityRef values */

/// Returns the members of the group.
///
/// This method only returns direct members of a group, it does not return
/// members of members. Both user and group identities can be members of a
/// group, but a group cannot be a member of itself. You also cannot have
/// “circular” membership, i.e. a group be a member of another group that is a
/// member of the first group.
///
/// - Returns: An array of `CBIdentity` objects each representing a member of
/// the group identity.
@property (nullable, readonly, nonatomic) NSArray *members NS_DEPRECATED(10_5, 10_11, NA, NA, "Use the memberIdentities property instead.") NS_SWIFT_UNAVAILABLE("Use the memberIdentities property instead. CSIdentity is not available in Swift.");

/* The group's members, as an array of CBIdentity objects */
@property (readonly, nonatomic) NSArray<CBIdentity *> *memberIdentities NS_AVAILABLE(10_11, NA);
@end

NS_ASSUME_NONNULL_END
