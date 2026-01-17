/*
    CBIdentityAuthority.h
    Collaboration.framework
  
    Copyright (c) 2006-2012 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString;

/* CBIdentityAuthority - A wrapper for CSIdentityAuthorityRef */

    
    /// An identity authority is a database that stores information about
    /// identities. The `CBIdentityAuthority` class defines one or more identity
    /// authorities. This database can be searched for identities in conjunction
    /// with the `CBIdentity` class factory methods.
NS_CLASS_AVAILABLE(10_5, NA)
@interface CBIdentityAuthority : NSObject {
    @private
    id _reserved[2];
}

/* Standard Identity Authorities */

/* The local authority contains identities defined in the local system's database */

/// Returns the identity authority on the local system.
///
/// Any identities stored on the local system are contained within this identity
/// authority.
///
/// - Returns: The identity authority on the local system.
+ (CBIdentityAuthority *)localIdentityAuthority;


/* The managed authority contains identities define in bound network directory servers */

/// Returns the identity authority that contains all the identities in bound
/// network directory servers.
///
/// If you are bound to a network directory server (such as an LDAP server) that
/// has an identity authority, use this method to search those authorities.
///
/// - Returns: The identity authorities in bound network directory servers.
+ (CBIdentityAuthority *)managedIdentityAuthority;


/* The default authority is the union of the local and managed authorities */

/// Returns an identity authority that contains the identities in both the local
/// and the network-bound authorities.
///
/// The default identity authority is the logical union of the identities in the
/// local and managed authorities.
///
/// - Returns: The local and network-bound identity authorities.
+ (CBIdentityAuthority *)defaultIdentityAuthority;


/* For conversion from a CSIdentityAuthorityRef */

/// Returns an identity authority specified by a given Core Services Identity
/// authority object.
///
/// This method, along with ``CBIdentityAuthority/CSIdentityAuthority``, is used
/// for interoperability with the Core Services Identity API.
///
/// - Parameters:
///   - CSIdentityAuthority: The Core Services Identity opaque object.
///
/// - Returns: The identity authority object for use with the Collaboration
/// framework.
+ (CBIdentityAuthority *)identityAuthorityWithCSIdentityAuthority:(CSIdentityAuthorityRef)CSIdentityAuthority NS_SWIFT_UNAVAILABLE("CSIdentityAuthority is not available in Swift.");


/* For conversion to a CSIdentityAuthorityRef */

/// Returns an identity authority for use with the Core Services Identity API.
///
/// This method, along with
/// ``CBIdentityAuthority/identityAuthorityWithCSIdentityAuthority:``, is used
/// for interoperability with the Core Services Identity API.
///
/// - Returns: The opaque authority object for use with the Core Services
/// Identity API.
@property (readonly) CSIdentityAuthorityRef CSIdentityAuthority NS_SWIFT_UNAVAILABLE("CSIdentityAuthority is not available in Swift.");

/* The identity authority's localized name */

/// Returns the localized name of the identity authority.
///
/// - Returns: The computer’s name if the authority is local, or Managed Network
/// Directory if the authority is managed.
@property (readonly, nonatomic) NSString *localizedName;
@end

NS_ASSUME_NONNULL_END
