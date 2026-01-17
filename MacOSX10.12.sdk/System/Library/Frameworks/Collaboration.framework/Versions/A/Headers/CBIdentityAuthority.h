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

NS_CLASS_AVAILABLE(10_5, NA)
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
+ (CBIdentityAuthority *)identityAuthorityWithCSIdentityAuthority:(CSIdentityAuthorityRef)CSIdentityAuthority NS_SWIFT_UNAVAILABLE("CSIdentityAuthority is not available in Swift.");

/* For conversion to a CSIdentityAuthorityRef */
@property (readonly) CSIdentityAuthorityRef CSIdentityAuthority NS_SWIFT_UNAVAILABLE("CSIdentityAuthority is not available in Swift.");

/* The identity authority's localized name */
@property (readonly, nonatomic) NSString *localizedName;
@end

NS_ASSUME_NONNULL_END
