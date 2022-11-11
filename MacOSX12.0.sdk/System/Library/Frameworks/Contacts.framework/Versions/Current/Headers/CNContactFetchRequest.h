//
//  CNContactFetchRequest.h
//  Contacts
//
//  Copyright (c) 2015–2019 Apple Inc. All rights reserved.
//

#import <Contacts/CNContact.h>
#import <Contacts/CNFetchRequest.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract Specifies the search criteria to fetch contacts.
 *
 * @discussion Used with [CNContactStore enumerateContactsWithFetchRequest:error:usingBlock:]. Can combine any of these options to create a contact fetch request.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactFetchRequest : CNFetchRequest <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;

/*!
 *  @param      keysToFetch
 *              The properties to fetch for the returned contacts.
 *
 *  @discussion Only fetch the properties that will be used.
 */
- (instancetype)initWithKeysToFetch:(NSArray <id<CNKeyDescriptor>>*)keysToFetch NS_DESIGNATED_INITIALIZER;

/*!
 * @abstract The predicate to match contacts against.
 *
 * @discussion Use only predicates from CNContact+Predicates.h. Compound predicates are not supported. Set to nil to match all contacts.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSPredicate *predicate;

/*!
 * @abstract The properties to fetch in the returned contacts.
 *
 * @discussion Should only fetch the properties that will be used. Can combine contact keys and contact key descriptors.
 */
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<id<CNKeyDescriptor>> *keysToFetch;

/*!
 * @abstract To return mutable contacts.
 *
 * @discussion If YES returns CNMutableContact objects, otherwise returns CNContact objects. Default is NO.
 */
@property (NS_NONATOMIC_IOSONLY) BOOL mutableObjects NS_AVAILABLE(10_12, 10_0);

/*!
 * @abstract To return linked contacts as unified contacts.
 *
 * @discussion If YES returns unified contacts, otherwise returns individual contacts. Default is YES.
 *
 * @note A unified contact is the aggregation of properties from a set of linked individual contacts. If an individual contact is not linked then the unified contact is simply that individual contact.
 */
@property (NS_NONATOMIC_IOSONLY) BOOL unifyResults;

/*!
 * @abstract To return contacts in a specific sort order.
 *
 * @discussion Default is CNContactSortOrderNone.
 */
@property (NS_NONATOMIC_IOSONLY) CNContactSortOrder sortOrder;

@end

NS_ASSUME_NONNULL_END
