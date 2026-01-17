//
//  CNContactRelation.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a related contact.
 *
 * @discussion CNContactRelation is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactRelation : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)contactRelationWithName:(NSString *)name;
- (instancetype)initWithName:(NSString *)name;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;

@end


// Contact relation labels
CONTACTS_EXTERN NSString * const CNLabelContactRelationFather             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMother             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationParent             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrother            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSister             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSon                NS_AVAILABLE(10_13, 11_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationDaughter           NS_AVAILABLE(10_13, 11_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationChild              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFriend             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSpouse             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationPartner            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAssistant          NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationManager            NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
