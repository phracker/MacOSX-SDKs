//
//  CSSearchableItemAttributeSet_General.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

@interface CSSearchableItemAttributeSet (CSGeneral)

//A localized string to be displayed in the UI for this item.
@property(nullable, copy) NSString *displayName;

//An array of localized strings of alternate display names for this item.
@property(nullable, copy) NSArray<NSString*> *alternateNames;

//This is the complete path to the item.
@property(nullable, copy) NSString *path;

//Optional file URL representing the content to be indexed
//Applications that are also 'Documents & Data' clients can set this property to allow Spotlight to deduplicate
//their searchable items against the iCloud Drive's items. When this property is set, Spotlight will not display
//the iCloud Drive's searchable items that have the same contentURL property.
@property(nullable, strong) NSURL *contentURL;

//Optional file URL pointing to a thumbnail image for this item
@property(nullable, strong) NSURL *thumbnailURL;

//Optional image data for thumbnail for this item
@property(nullable, copy) NSData *thumbnailData;

//For activities, this is the unique identifier for the item this activity is related to. If the item doesn't exist in the index, the activity will not get stored. When the item is deleted, the activity will also be deleted.
@property(nullable, copy) NSString *relatedUniqueIdentifier;

//For activities, this is the unique identifier for an item this activity is related to. Unlike relatedUniqueIdentifier, this attribute does not link the life time of the items.
@property(nullable, copy) NSString *weakRelatedUniqueIdentifier CS_AVAILABLE(10_13, 10_0) CS_TVOS_UNAVAILABLE;


//This is the date that the last metadata attribute was changed.
@property(nullable, strong) NSDate *metadataModificationDate;

//UTI Type pedigree for an item.  Common types can be found in UTCoreTypes.h
@property(nullable, copy) NSString *contentType;

@property(nullable, copy) NSArray<NSString*> *contentTypeTree;

//Represents keywords associated with this particular item.
//Example Keywords might be Birthday,Important etc.
@property(nullable, copy) NSArray<NSString*> *keywords;

//The title of this particular item.
//Title of the document, or it could be the title of this mp3 or a subject of a mail message.
@property(nullable, copy) NSString *title;

//A version specifier for this item.
@property(nullable, copy) NSString *version;

//This property is used to indicate if the indexed item was created by the user
//It is used to distinguish pushed app content from content that required explicit user interaction
//Example content that may set this field: user created notes, documents
@property(nullable, strong, getter=isUserCreated) NSNumber *userCreated CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

//This property is used to indicate if the indexed item has been purchased or otherwise acquired by the user
//Example content are songs bought by a user and made searchable
@property(nullable, strong, getter=isUserOwned) NSNumber *userOwned CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

//This property is used to indicate if the indexed item was selected by the user
//It is used to distinguish pushed app content from content that a user has chosen to add to a collection
//Example content that may set this field: downloaded media content, bookmarked websites/news articles
@property(nullable, strong, getter=isUserCurated) NSNumber *userCurated CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

//This property allows content donors to provide a ranking signal to each indexed item
//It will inform the ranker, allowing it to distinguish more easily between otherwise similar items
//This is query-independent and should be used to indicate the relative importance of an item w.r.t. all other items for the same application
//Expected value ∈ [0-100]; preferably integral values
//Monotonically increasing with larger values being considered better results
@property(nullable, strong) NSNumber *rankingHint CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

// This property has the same semantics as -[CSSearchableItem domainIdentifier].
// It can be set on the contentAttributeSet property of a NSUserActivity instance and then used to delete the user activity
// by calling [[CSSearchableIndex defaultSearchableIndex] deleteSearchableItemsWithDomainIdentifiers:].
@property(nullable, copy) NSString *domainIdentifier CS_AVAILABLE(10_13, 10_0) CS_TVOS_UNAVAILABLE;

@end

@interface CSSearchableItemAttributeSet (CSActionExtras)
// If supportsPhoneCall is 1 and the item has the phoneNumbers property, then the phone number may be used to initiate phone calls. This should be used to indicate that using the phone number is appropriate, and a primary action for the user. For example, supportsPhoneCall would be set on a business, but not an academic paper that happens to have phone numbers for the authors or the institution.
@property(nullable, strong) NSNumber *supportsPhoneCall;

// If supportsNavigation is set to 1, and the item has the latitude and longitude properties set, then the latitude and longitude may be used for navigation. For example, supportsNavigation would be set on a restaurant review, but not on a photo.
@property(nullable, strong) NSNumber *supportsNavigation;
@end

@interface CSSearchableItemAttributeSet(CSContainment)
@property(nullable, copy) NSString *containerTitle;
@property(nullable, copy) NSString *containerDisplayName;
@property(nullable, copy) NSString *containerIdentifier;
@property(nullable, strong) NSNumber *containerOrder;
@end

@interface CSSearchableItemAttributeSet (CSItemProvider)
// The string value of type identifer can only be used by one providerTypeIdentifier array.

// An array of types identifiers that owner can provided a NSData representation.
@property(nullable, copy) NSArray<NSString *> *providerDataTypeIdentifiers CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

// An array of types identifiers that owner can provided a NSURL to file representation.
@property(nullable, copy) NSArray<NSString *> *providerFileTypeIdentifiers CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

// An array of types identifiers that owner can provided a NSURL to inplace file representation.
@property(nullable, copy) NSArray<NSString *> *providerInPlaceFileTypeIdentifiers CS_AVAILABLE(10_13, 11_0) CS_TVOS_UNAVAILABLE;

@end

