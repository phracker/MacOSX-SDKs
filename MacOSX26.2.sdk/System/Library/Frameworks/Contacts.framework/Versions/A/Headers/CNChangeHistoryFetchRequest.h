//
//  CNChangeHistoryFetchRequest.h
//  Contacts
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Contacts/CNFetchRequest.h>

@protocol CNKeyDescriptor;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract    Specifies the criteria to fetch change history.
 *
 * @discussion  Changes to contacts are always returned.
 *              All changes are coalesced to remove redundant adds, updates and deletes.
 *              This request is used with [CNContactStore enumeratorForChangeHistoryFetchRequest:error:].
 */
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryFetchRequest : CNFetchRequest <NSSecureCoding>

/*!
 * @abstract    Request changes made after a certain point.
 *
 * @discussion  If non-nil, only changes made after this point in history will be returned.
 *
 *              If nil, a @c CNChangeHistoryDropEverythingEvent will be returned, followed by an add event
 *              for every contact and group currently in the contacts database.
 */
@property (copy, nullable, nonatomic) NSData * startingToken;

/*!
 * @abstract    Additional keys to include in the fetched contacts.
 *
 * @discussion  By default, only @c CNContactIdentifierKey will be fetched. If you
 *              would like to include additional key descriptors to process the contacts,
 *              include the key descriptors you need.
 *
 *              @c CNContactIdentifierKey will always be fetched, whether you
 *              request it or not.
 */
@property (copy, nullable, nonatomic) NSArray<id<CNKeyDescriptor>> * additionalContactKeyDescriptors;

/*!
 * @abstract    Returns contact changes as unified contacts.
 *
 * @discussion  If @c YES, returns unified contact history. Otherwise returns individual contact history. Default is @c YES.
 *
 * @note        A unified contact is the aggregation of properties from a set of linked individual contacts.
 *              If an individual contact is not linked then the unified contact is simply that individual contact.
 */
@property (nonatomic) BOOL shouldUnifyResults;

/*!
 * @abstract    To return mutable contacts and groups.
 *
 * @discussion  If @c YES returns mutable contacts and groups. Default is @c NO.
 */
@property (nonatomic) BOOL mutableObjects;

/*!
 * @abstract    Set to @c YES to also fetch group changes. Default is @c NO.
 */
@property (nonatomic) BOOL includeGroupChanges;

/*!
 * @abstract    Exclude changes made by certain authors.
 *
 * @discussion  If set, transactions made by the specified authors will be excluded
 *              from the results. Use this, in conjunction with @c CNSaveRequest.transactionAuthor,
 *              to suppress processing of changes you already know about.
 */
@property (copy, nullable, nonatomic) NSArray<NSString *> * excludedTransactionAuthors;

@end

NS_ASSUME_NONNULL_END
