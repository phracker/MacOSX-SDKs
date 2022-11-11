//
//  CNContactStore.h
//  Contacts
//
//  Copyright (c) 2015–2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>
#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN

@class CNContact;
@class CNGroup;
@class CNContainer;
@class CNChangeHistoryEvent;
@class CNContactFetchRequest;
@class CNChangeHistoryFetchRequest;
@class CNFetchResult<ValueType>;
@class CNSaveRequest;

/*!
 * @abstract The entities the user can grant access to.
 */
typedef NS_ENUM(NSInteger, CNEntityType)
{
    /*! The user's contacts. */
    CNEntityTypeContacts
}  NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 * @abstract The authorization the user has given the application to access an entity type.
 */
typedef NS_ENUM(NSInteger, CNAuthorizationStatus)
{
    /*! The user has not yet made a choice regarding whether the application may access contact data. */
    CNAuthorizationStatusNotDetermined = 0,
    /*! The application is not authorized to access contact data.
     *  The user cannot change this application’s status, possibly due to active restrictions such as parental controls being in place. */
    CNAuthorizationStatusRestricted,
    /*! The user explicitly denied access to contact data for the application. */
    CNAuthorizationStatusDenied,
    /*! The application is authorized to access contact data. */
    CNAuthorizationStatusAuthorized
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*!
 * @abstract Provides methods to fetch and save contacts.
 *
 * @discussion The CNContactStore is a thread safe class that can fetch and save contacts, fetch and save groups, and fetch containers.
 *
 * @note Some good practices are:
 * 1) Only fetch contact properties that will be used.
 * 2) When fetching all contacts and caching the results, first fetch all contact identifiers only. Then fetch batches of detailed contacts by identifiers as you need them.
 * 3) To aggregate several contact fetches collect a set of unique contact identifiers from the fetches. Then fetch batches of detailed contacts by identifiers.
 * 4) When CNContactStoreDidChangeNotification is posted, if you cache any fetched contacts/groups/containers then they must be refetched and the old cached objects released.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactStore : NSObject

#pragma mark - Privacy Access

/*!
 * @abstract Indicates the current authorization status to access contact data.
 *
 * @discussion Based upon the access, the application could display or hide its UI elements that would access any Contacts API. This method is thread safe.
 *
 * @return Returns the authorization status for the given entityType.
 */
+ (CNAuthorizationStatus)authorizationStatusForEntityType:(CNEntityType)entityType;

/*!
 * @abstract Request access to the user's contacts.
 *
 * @discussion Users are able to grant or deny access to contact data on a per-application basis. To request access to contact data, call requestAccessForEntityType:completionHandler:. This will not block the application while the user is being asked to grant or deny access. The user will only be prompted the first time access is requested; any subsequent CNContactStore calls will use the existing permissions. The completion handler is called on an arbitrary queue.
 *
 * @note Recommended to use CNContactStore instance methods in this completion handler instead of the UI main thread. This method is optional when CNContactStore is used on a background thread. If it is not used in that case, CNContactStore will block if the user is asked to grant or deny access.
 *
 * @param entityType Set to CNEntityTypeContacts.
 * @param completionHandler This block is called upon completion. If the user grants access then granted is YES and error is nil. Otherwise granted is NO with an error. 
 */
- (void)requestAccessForEntityType:(CNEntityType)entityType completionHandler:(void (^)(BOOL granted, NSError *__nullable error))completionHandler;


#pragma mark - Unified Contacts Helpers

/*!
 * @abstract Fetch all unified contacts matching a given predicate.
 *
 * @discussion Use only predicates from CNContact+Predicates.h. Compound predicates are not supported. Due to unification the returned contacts may have a different identifier. 
 *
 * @note To fetch all contacts use enumerateContactsWithFetchRequest:error:usingBlock:.
 *
 * @param predicate The predicate to match against.
 * @param keys The properties to fetch into the returned CNContact objects. Should only fetch the properties that will be used. Can combine contact keys and contact key descriptors.
 * @param error If an error occurs, contains error information.
 * @return An array of CNContact objects matching the predicate. If no matches are found, an empty array is returned. If an error occurs, nil is returned.
 */
- (nullable NSArray<CNContact*> *)unifiedContactsMatchingPredicate:(NSPredicate *)predicate keysToFetch:(NSArray<id<CNKeyDescriptor>> *)keys error:(NSError **)error;

/*!
 * @abstract Fetch a unified contact with a given identifier.
 *
 * @discussion Due to unification the returned contact may have a different identifier. To fetch a batch of contacts by identifiers use [CNContact predicateForContactsWithIdentifiers:].
 *
 * @param identifier The identifier of the contact to fetch.
 * @param keys The properties to fetch into the returned CNContact object. Should only fetch the properties that will be used. Can combine contact keys and contact key descriptors.
 * @param error If an error occurs, contains error information.
 * @return The unified contact matching or linked to the identifier. If no contact with the given identifier is found, nil is returned and error is set to CNErrorCodeRecordDoesNotExist.
 */
- (nullable CNContact *)unifiedContactWithIdentifier:(NSString *)identifier keysToFetch:(NSArray<id<CNKeyDescriptor>> *)keys error:(NSError **)error;

/*!
 * @abstract Fetch the unified contact that is the "me" card.
 *
 * @discussion Fetches the contact that is represented in the user interface as "My Card".
 *
 * @param keys The properties to fetch into the returned CNContact object. Should only fetch the properties that will be used. Can combine contact keys and contact key descriptors.
 * @param error If an error occurs, contains error information.
 * @return The unified contact that is the "me" card. If no "me" card is set, nil is returned.
 */
- (nullable CNContact *)unifiedMeContactWithKeysToFetch:(NSArray<id<CNKeyDescriptor>> *)keys error:(NSError **)error NS_AVAILABLE(10_11, NA) __WATCHOS_PROHIBITED;


#pragma mark - Fetch and Save

/*!
 * @abstract    Enumerate a contact fetch request.
 *
 * @discussion  Executes the given fetch request and returns an enumerator for the results.
 *              This may prevent all records from being loaded into memory at once.
 *
 *              An exception may be thrown if an error occurs during enumeration.
 *
 * @param       request
 *              A description of the records to fetch.
 *
 * @param       error
 *              If the fetch fails, contains an @c NSError object with more information.
 *
 * @return      An enumerator of the records matching the result, or @c nil if there was an error.
 */
- (nullable CNFetchResult<NSEnumerator<CNContact *> *> *)enumeratorForContactFetchRequest:(CNContactFetchRequest *)request error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0)) NS_SWIFT_UNAVAILABLE("");

/*!
 * @abstract    Enumerate a change history fetch request.
 *
 * @discussion  Executes the given fetch request and returns an enumerator for the results.
 *              This may prevent all events from being loaded into memory at once.
 *
 *              An exception may be thrown if an error occurs during enumeration.
 *
 * @param       request
 *              A description of the events to fetch.
 *
 * @param       error
 *              If the fetch fails, contains an @c NSError object with more information.
 *
 * @return      An enumerator of the events matching the result, or @c nil if there was an error.
 */
- (nullable CNFetchResult<NSEnumerator<CNChangeHistoryEvent *> *> *)enumeratorForChangeHistoryFetchRequest:(CNChangeHistoryFetchRequest *)request error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0)) NS_SWIFT_UNAVAILABLE("");


/*!
 * @abstract Enumerates all contacts matching a contact fetch request.
 *
 * @discussion This method will wait until the enumeration is finished. If there are no results, the block is not called and YES is returned.
 *
 * @param fetchRequest The contact fetch request that specifies the search criteria.
 * @param error If an error occurs, contains error information.
 * @param block Called for each matching contact. Set *stop to YES to stop the enumeration.
 * @return YES if successful, otherwise NO.
 */
- (BOOL)enumerateContactsWithFetchRequest:(CNContactFetchRequest *)fetchRequest error:(NSError **)error usingBlock:(void (^)(CNContact *contact, BOOL *stop))block;

/*!
 * @abstract Fetch all groups matching a given predicate.
 *
 * @discussion Use only predicates from CNGroup+Predicates.h. Compound predicates are not supported.
 *
 * @param predicate The predicate to match against. Set to nil to match all groups.
 * @param error If an error occurs, contains error information.
 * @return An array of CNGroup objects matching the predicate. If no matches are found, an empty array is returned. If an error occurs, nil is returned.
 */
- (nullable NSArray<CNGroup*> *)groupsMatchingPredicate:(nullable NSPredicate *)predicate error:(NSError **)error;

/*!
 * @abstract Fetch all containers matching a given predicate.
 *
 * @discussion Use only predicates from CNContainer+Predicates.h. Compound predicates are not supported.
 *
 * @param predicate The predicate to match against. Set to nil to match all containers.
 * @param error If an error occurs, contains error information.
 * @return An array of CNContainer objects matching the predicate. If no matches are found, an empty array is returned. If an error occurs, nil is returned.
 */
- (nullable NSArray<CNContainer*> *)containersMatchingPredicate:(nullable NSPredicate *)predicate error:(NSError **)error;

/*!
 * @abstract Executes a save request.
 *
 * @discussion Do not access objects when save request is executing. A save request with contacts may modify the contacts while executing. A save request only applies the changes to the objects. If there are overlapping changes with multiple, concurrent CNSaveRequests then the last saved change wins.
 *
 * @param saveRequest Save request to execute.
 * @param error If an error occurs, contains error information.
 * @return YES if successful, otherwise NO.
 */
- (BOOL)executeSaveRequest:(CNSaveRequest *)saveRequest error:(NSError **)error __WATCHOS_PROHIBITED;


#pragma mark - Miscellaneous

/*!
 *  @abstract The current history token.
 *
 *  @discussion Retrieve the current history token. If you are fetching contacts or change history events, you should use the token on the @c CNFetchResult instead.
 */
@property (nonatomic, readonly, copy, nullable) NSData * currentHistoryToken API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0));

/*!
 *  @abstract The identifier of the default container.
 *
 *  @discussion This identifier can be used to fetch the default container.
 *
 *  @return The identifier of the default container. If the caller lacks Contacts authorization or an error occurs, nil is returned.
 */
- (nullable NSString *)defaultContainerIdentifier;

@end


#pragma mark - Constants

/*!
 * @abstract Notification posted when changes occur in another CNContactStore.
 */
CONTACTS_EXTERN NSString * const CNContactStoreDidChangeNotification NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
