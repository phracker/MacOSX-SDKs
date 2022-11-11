//
//  CSSearchableItem.h
//  CoreSpotlight
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <CoreSpotlight/CSBase.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

NS_ASSUME_NONNULL_BEGIN

// When opening a document from Spotlight, the application's application:willContinueUserActivityWithType:
// method will get called with CSSearchableItemActionType, followed by  application:continueUserActivity:restorationHandler:
// with an NSUserActivity where the userInfo dictionary has a key value pair where CSSearchableItemActivityIdentifier is the key
// and the value is the uniqueIdentifier used when creating the item.
CORESPOTLIGHT_EXPORT NSString * const CSSearchableItemActionType CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE;
CORESPOTLIGHT_EXPORT NSString * const CSSearchableItemActivityIdentifier CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE;

// For custom actions on iOS, the userInfo dictionary also has another key value pair where CSActionIdentifier is the key
// and the value is the action tapped in the UI based on what was indexed by the app.
CORESPOTLIGHT_EXPORT NSString * const CSActionIdentifier API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos);

// When continuing a query from Spotlight, the application's -application:willContinueUserActivityWithType:
// method will get called with CSQueryContinuationActionType, followed by -application:continueUserActivity:restorationHandler:
// with an NSUserActivity where the userInfo dictionary has a key value pair with CSSearchQueryString as the key
// and the value is the string the application should use when performing its query.
// The application should declare that it supports the query continuation by adding the CoreSpotlightContinuation key to its Info.plist:
//
//    <key>CoreSpotlightContinuation</key>
//    <true/>
//
CORESPOTLIGHT_EXPORT NSString * const CSQueryContinuationActionType CS_AVAILABLE(10_13, 10_0) CS_TVOS_UNAVAILABLE;
CORESPOTLIGHT_EXPORT NSString * const CSSearchQueryString CS_AVAILABLE(10_13, 10_0) CS_TVOS_UNAVAILABLE;


CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSSearchableItem : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithUniqueIdentifier:(nullable NSString *)uniqueIdentifier //Can be null, one will be generated
                        domainIdentifier:(nullable NSString *)domainIdentifier
                            attributeSet:(CSSearchableItemAttributeSet *)attributeSet;

// Should be unique to your application group.
// REQUIRED since this is the way you will refer to the item to update the index / delete it from the index
// Starts with an UUID for ease of use, but you can replace it with an UID of your own before the item is first indexed if you wish.
@property (copy) NSString *uniqueIdentifier;

// An optional identifier that represents the "domain" or owner of this item.
// This might be an identifier for a mailbox in an account whose indexed data you may want to remove when the account is deleted.
// In that case the domainIdentifier should be of the form <account-id>.<mailbox-id> where <account-id> and <mailbox-id> should not contains periods.
// Calling deleteSearchableItemsWithDomainIdentifiers with <account-id>.<mailbox-id> will delete all items with that domain identifier.
// Calling deleteSearchableItemsWithDomainIdentifiers with <account-id> will delete all items with <account-id> and any <mailbox-id>.
@property (copy, nullable) NSString *domainIdentifier;

// Searchable items have an expiration date or time to live.  By default it's set to 1 month.
@property (copy, null_resettable) NSDate * expirationDate;

// Set of attributes containing meta data for the item
@property (strong) CSSearchableItemAttributeSet *attributeSet;

@end

NS_ASSUME_NONNULL_END
