/*	NSPersonNameComponents.h
	Copyright (c) 2015, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NSPersonNameComponents : NSObject <NSCopying, NSSecureCoding>{
@private
    id _private;
}

/* Name bestowed upon an individual by one's parents, e.g. Johann */
@property (copy) NSString *givenName;

/* Inherited name shared with members of one's immediate family, e.g. Bach  */
@property (copy) NSString *familyName;

/* Secondary given name chosen to differentiate those with the same first name, e.g. Sebastian  */
@property (copy) NSString *middleName;

/* Pre-nominal letters denoting title, salutation, or honorific, e.g. Dr., Mrs. */
@property (copy) NSString *namePrefix;

/* Post-nominal letters denoting degree, accreditation, or other honor, e.g. Jr., Ph.D. */
@property (copy) NSString *nameSuffix;

/* Name substituted for full proper name for the purposes of familiarity, e.g. "A-Rod" for "Alex Rodriguez" */
@property (copy) NSString *nickname;

/* Each element of the phoneticRepresentation corresponds to an element of the original PersonNameComponents.
   The phoneticRepresentation of the phoneticRepresentation object will be ignored */
@property (copy, nullable) NSPersonNameComponents *phoneticRepresentation;

@end

NS_ASSUME_NONNULL_END
