//
//  CNContactProperty.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CNContact;


/*!
 * @abstract Contains related information for a specific contact property.
 *
 * @discussion CNContactProperty is used by the CNContactPicker to return the user's selected property.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactProperty : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CNContact *contact;

/*!
 * @abstract The key of the contact property, as defined in CNContact.h.
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *key;

/*!
 * @abstract The value of the property.
 */
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) id value;

/*!
 * @abstract The identifier of the labeled value if the property is an array of labeled values, otherwise is nil.
 */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

/*!
 * @abstract The label of the labeled value if the property is an array of labeled values, otherwise is nil.
 */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *label;

@end

NS_ASSUME_NONNULL_END
