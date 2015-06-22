/*
	NSFontCollection.h
	Application Kit
	Copyright (c) 2010-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>
#import <Foundation/NSLocale.h>
#import <Foundation/NSString.h>
#import <AppKit/AppKitDefines.h>


NS_ASSUME_NONNULL_BEGIN

@class NSFontDescriptor;

/*
 Named collection visibility
 */
typedef NS_OPTIONS(NSUInteger, NSFontCollectionVisibility) {
    // Visible within this process, not persistent
    NSFontCollectionVisibilityProcess = (1UL << 0),
    
    // Visible to all processes, stored persistently
    NSFontCollectionVisibilityUser = (1UL << 1),
    
    // Visible to all users, stored persistently
    NSFontCollectionVisibilityComputer = (1UL << 2)
};


/*
 NSFontCollection - immutable font list
 */
NS_CLASS_AVAILABLE(10_7, NA)
@interface NSFontCollection : NSObject <NSCopying, NSMutableCopying, NSCoding>

/*
 Creating collections
 */
// Return a font collection matching the given descriptors
+ (NSFontCollection *)fontCollectionWithDescriptors:(NSArray<NSFontDescriptor *> *)queryDescriptors;

// Return a font collection matching all registered fonts
+ (NSFontCollection *)fontCollectionWithAllAvailableDescriptors;

// Return a collection with fonts for the specified locale.
+ (nullable NSFontCollection *)fontCollectionWithLocale:(NSLocale *)locale;

/* 
 Naming collections
 
 These methods allow you to associate a name with a collection. Named collections are shown by user interfaces such as NSFontPanel.
 
 Set the visibility to NSFontCollectionVisibilityProcess if you wish to make the collection visible to the current process, but not to other processes. NSFontCollectionVisibilityUser will archive the collection to persistent storage and make it visible to other processes. NSFontCollectionVisibilityComputer is like NSFontCollectionVisibilityUser but makes the collection visible to all users of the computer.
 
 There is no association between the the NSFontCollection instance and the name from which it was created. When you change the collection, you must show it again to see the changes reflected on disk or in font UI.
 
 Errors returned from these methods are NSFileManager errors.
 */

// Make the font collection visible by giving it a name
+ (BOOL)showFontCollection:(NSFontCollection *)collection withName:(NSString *)name visibility:(NSFontCollectionVisibility)visibility error:(NSError **)error;

// Remove font collection from view (for a persistent collection, deletes the named font collection from disk)
+ (BOOL)hideFontCollectionWithName:(NSString *)name visibility:(NSFontCollectionVisibility)visibility error:(NSError **)error;

// Rename named collection
+ (BOOL)renameFontCollectionWithName:(NSString *)name visibility:(NSFontCollectionVisibility)visibility toName:(NSString *)name error:(NSError **)error;

// Named collections visible to this process (array of NSString)
+ (NSArray<NSString *> *)allFontCollectionNames;

// Return the specified named collection
+ (nullable NSFontCollection *)fontCollectionWithName:(NSString *)name;

// Return the specified named collection with specified visibility
+ (nullable NSFontCollection *)fontCollectionWithName:(NSString *)name visibility:(NSFontCollectionVisibility)visibility;

/*
 Descriptor matching
 */

// The list of NSFontDescriptors to match. The matching descriptors are produced by matching this list of descriptors.
@property (nullable, readonly, copy) NSArray<NSFontDescriptor *> *queryDescriptors;

// A separate list of query descriptors. The matching results from this list are excluded from matchingDescriptors.
@property (nullable, readonly, copy) NSArray<NSFontDescriptor *> *exclusionDescriptors;

// Returns a list of descriptors matching the logical descriptors.
// These are determined at runtime as (matching queryDescriptors - matching exclusionDescriptors).
// options may be nil or a dictionary containing any combination of {NSFontCollectionIncludeDisabledFontsOption, NSFontCollectionRemoveDuplicatesOption, NSFontCollectionDisallowAutoActivationOption}.
@property (nullable, readonly, copy) NSArray<NSFontDescriptor *> *matchingDescriptors;
- (nullable NSArray<NSFontDescriptor *> *)matchingDescriptorsWithOptions:(nullable NSDictionary<NSString *, NSNumber *> *)options;

// Return a list of matching descriptors for a particular family
- (nullable NSArray<NSFontDescriptor *> *)matchingDescriptorsForFamily:(NSString *)family;
- (nullable NSArray<NSFontDescriptor *> *)matchingDescriptorsForFamily:(NSString *)family options:(nullable NSDictionary<NSString *, NSNumber *> *)options;

@end

/*
 NSMutableFontCollection - mutable font list
 */
NS_CLASS_AVAILABLE(10_7, NA)
@interface NSMutableFontCollection : NSFontCollection

// Return a font collection matching the given descriptors
+ (NSMutableFontCollection *)fontCollectionWithDescriptors:(NSArray<NSFontDescriptor *> *)queryDescriptors;

// Return a font collection matching all registered fonts
+ (NSMutableFontCollection *)fontCollectionWithAllAvailableDescriptors;

// Return a collection with fonts for the specified locale.
+ (NSMutableFontCollection *)fontCollectionWithLocale:(NSLocale *)locale;

// Return the specified named collection
+ (nullable NSMutableFontCollection *)fontCollectionWithName:(NSString *)name;

// Return the specified named collection with specified visibility
+ (nullable NSMutableFontCollection *)fontCollectionWithName:(NSString *)name visibility:(NSFontCollectionVisibility)visibility;

@property (nullable, copy) NSArray<NSFontDescriptor *> *queryDescriptors;

@property (nullable, copy) NSArray<NSFontDescriptor *> *exclusionDescriptors;

// Edit the query and exclusion arrays to ensure that the results of querying the given descriptors are included in the matching descriptors.
- (void)addQueryForDescriptors:(NSArray<NSFontDescriptor *> *)descriptors;

// Edit the query and exclusion arrays to ensure that the results of querying the given descriptors are excluded from the matching descriptors.
- (void)removeQueryForDescriptors:(NSArray<NSFontDescriptor *> *)descriptors;

@end

/*
 Matching options
 */
// NSNumber BOOL specifying whether disabled fonts should be included in the list of matching descriptors (YES) or not (NO). When unspecified, CoreText assumes NO. This option is intended only for font management applications. This option will make descriptor matching slower.
APPKIT_EXTERN NSString * const NSFontCollectionIncludeDisabledFontsOption NS_AVAILABLE_MAC(10_7);

// NSNumber BOOL controlling whether more than one copy of a font with the same PostScript name should be included in the list of matching descriptors
APPKIT_EXTERN NSString * const NSFontCollectionRemoveDuplicatesOption NS_AVAILABLE_MAC(10_7);

// NSNumber BOOL specifying that auto-activation should not be used to find missing fonts
APPKIT_EXTERN NSString * const NSFontCollectionDisallowAutoActivationOption NS_AVAILABLE_MAC(10_7);

/*
 NSFontCollectionDidChangeNotification
 
 This notification is sent to the local notification center when a named, persistent collection is modified.
 User info key NSFontCollectionNotificationAction describes the nature of the change.
 */
APPKIT_EXTERN NSString * const NSFontCollectionDidChangeNotification NS_AVAILABLE_MAC(10_7);

// Notification user info dictionary keys
APPKIT_EXTERN NSString * const NSFontCollectionActionKey NS_AVAILABLE_MAC(10_7);			// NSString: action taken
APPKIT_EXTERN NSString * const NSFontCollectionNameKey NS_AVAILABLE_MAC(10_7);			// NSString: current name of affected collection
APPKIT_EXTERN NSString * const NSFontCollectionOldNameKey NS_AVAILABLE_MAC(10_7);		// NSString: for NSFontCollectionWasRenamed, previous name of affected collection
APPKIT_EXTERN NSString * const NSFontCollectionVisibilityKey NS_AVAILABLE_MAC(10_7);		// NSNumber: visibility of affected collection

// Values for NSFontCollectionAction
APPKIT_EXTERN NSString * const NSFontCollectionWasShown NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSFontCollectionWasHidden NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSFontCollectionWasRenamed NS_AVAILABLE_MAC(10_7);

/*
 Standard named collections
 
 Standard mutable collection names -- these names are included in the list of allFontCollectionNames -- they have special meaning to the
 Cocoa font system and should not be hidden or renamed.
 */
APPKIT_EXTERN NSString * const NSFontCollectionAllFonts NS_AVAILABLE_MAC(10_7);		// All fonts in the system
APPKIT_EXTERN NSString * const NSFontCollectionUser NS_AVAILABLE_MAC(10_7);			// Per-user unmodifiable collection
APPKIT_EXTERN NSString * const NSFontCollectionFavorites NS_AVAILABLE_MAC(10_7);		// Collection of the user's preferred font descriptors
APPKIT_EXTERN NSString * const NSFontCollectionRecentlyUsed NS_AVAILABLE_MAC(10_7);	// Collection automatically maintained by NSFontManager

NS_ASSUME_NONNULL_END

