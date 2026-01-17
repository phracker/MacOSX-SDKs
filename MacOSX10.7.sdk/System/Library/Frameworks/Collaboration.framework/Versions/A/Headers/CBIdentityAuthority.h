/*
    CBIdentityAuthority.h
    Collaboration.framework
  
    Copyright 2006 Apple Computer. All rights reserved.
*/


#import <Foundation/NSObject.h>
#import <CoreServices/CoreServices.h>


@class NSString;

/* CBIdentityAuthority - A wrapper for CSIdentityAuthorityRef */

@interface CBIdentityAuthority : NSObject {
    @private
    id _reserved[2];
}

/* Standard Identity Authorities */

/* The local authority contains identities defined in the local system's database */
+ (CBIdentityAuthority *)localIdentityAuthority;

/* The managed authority contains identities define in bound network directory servers */
+ (CBIdentityAuthority *)managedIdentityAuthority;

/* The default authority is the union of the local and managed authorities */
+ (CBIdentityAuthority *)defaultIdentityAuthority;

/* For conversion from a CSIdentityAuthorityRef */
+ (CBIdentityAuthority *)identityAuthorityWithCSIdentityAuthority:(CSIdentityAuthorityRef)CSIdentityAuthority;

/* For conversion to a CSIdentityAuthorityRef */
- (CSIdentityAuthorityRef)CSIdentityAuthority;

/* The identity authority's localized name */
- (NSString *)localizedName;

@end
