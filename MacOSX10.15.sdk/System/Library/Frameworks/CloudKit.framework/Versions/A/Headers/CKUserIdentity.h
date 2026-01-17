//
//  CKUserIdentity.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKRecordID, CKUserIdentityLookupInfo;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKUserIdentity : NSObject <NSSecureCoding, NSCopying>
/*! Use `CKDiscoverUserIdentitiesOperation` or `CKFetchShareParticipantsOperation` to create a `CKUserIdentity` */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*! This is the `lookupInfo` you passed in to `CKDiscoverUserIdentitiesOperation` or `CKFetchShareParticipantsOperation` */
@property (nonatomic, readonly, copy, nullable) CKUserIdentityLookupInfo *lookupInfo;

@property (nonatomic, readonly, copy, nullable) NSPersonNameComponents *nameComponents;
@property (nonatomic, readonly, copy, nullable) CKRecordID *userRecordID;

/*! @abstract Link to the Contacts database.
 *
 *  @discussion Identities discovered via `CKDiscoverAllUserIdentitiesOperation` correspond to entries in the local Contacts database.  These identities will have `contactIdentifiers` filled out, which your app may use to get additional information about the contacts that were discovered.  Multiple `contactIdentifiers` may exist for a single discovered user, as multiple contacts may contain the same email addresses or phone numbers.
 *
 *  @return individual, non-unified contacts.
 *
 *  @discussion To transform these identifiers into an array of unified contact identifiers, pass a `CNContact.predicateForContacts(withIdentifiers:)` predicate into `CNContactStore.unifiedContacts(matching:keysToFetch:)`
 *
 *  @see Contacts.framework and CNContact.identifier
 */
@property (nonatomic, readonly, copy) NSArray<NSString *> *contactIdentifiers API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0)) API_UNAVAILABLE(tvos);


@property (nonatomic, readonly, assign) BOOL hasiCloudAccount;

@end

NS_ASSUME_NONNULL_END
