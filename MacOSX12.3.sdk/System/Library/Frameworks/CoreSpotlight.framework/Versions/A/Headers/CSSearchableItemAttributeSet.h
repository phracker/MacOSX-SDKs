//
//  CSSearchableItemAttributeSet.h
//  CoreSpotlight
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreSpotlight/CSBase.h>
#import <CoreSpotlight/CSPerson.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

NS_ASSUME_NONNULL_BEGIN

CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
// CSSearchableItemAttribute encapsulates a set of properties of an CSSearchableItem.
// CSSearchableItemAttribute set should only be mutated from one thread at a time. Concurrent access to properties has undefined behavior.
@interface CSSearchableItemAttributeSet : NSObject <NSCopying,NSSecureCoding>

//Creates an attribute set for the given content type.
- (instancetype)initWithItemContentType:(nonnull NSString *)itemContentType API_DEPRECATED("Use initWithContentType instead", macos(10.13, API_TO_BE_DEPRECATED), ios(9.0, API_TO_BE_DEPRECATED)) CS_TVOS_UNAVAILABLE;
- (instancetype)initWithContentType:(nonnull UTType *)contentType NS_AVAILABLE(11_0, 14_0) CS_TVOS_UNAVAILABLE;

@end

//CSLocalizedString can be used in place of NSString to support localization
CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSLocalizedString : NSString

//Takes a dictionary of preferred codes to the localized string for that language
- (instancetype)initWithLocalizedStrings:(NSDictionary *)localizedStrings;

//Returns the localized string for the current language
- (NSString *)localizedString;

@end

//CSCustomAttributeKey allows you to specify a custom attribute as well as various other properties of that attribute.
CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSCustomAttributeKey : NSObject <NSCopying,NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

//Key names should be ASCII only, with no punctuation other than '_'.
//It is recommended keys be of the form "com_mycompany_myapp_keyname"
//Keys starting with 'kMD' are reserved.
- (nullable instancetype)initWithKeyName:(NSString *)keyName;
- (nullable instancetype)initWithKeyName:(NSString *)keyName
                              searchable:(BOOL)searchable
                     searchableByDefault:(BOOL)searchableByDefault
                                  unique:(BOOL)unique
                             multiValued:(BOOL)multiValued NS_DESIGNATED_INITIALIZER;

@property (readonly) NSString *keyName;

//Can this attribute be searched on? By default, YES
@property (readonly,getter=isSearchable) BOOL searchable;

//Is this property searchable by default? By default, NO
@property (readonly, getter=isSearchableByDefault) BOOL searchableByDefault;

//Should values be uniqued to save storage? By default, NO. Set this to YES when there is a small set of known values, or values are likely to be frequently repeating for other reasons.
@property (readonly, getter=isUnique) BOOL unique;

//Is this attribute expecting multiple values to be associated with it, i.e. are values arrays?  By default, NO
@property (readonly, getter=isMultiValued) BOOL multiValued;

@end

//Use these methods to set custom attributes on an attribute set
//Values must be common plist types (NSString,NSNumber,NSNull,NSData,NSDate) or CSPerson, or arrays (NSArray) of these types.
CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE
@interface CSSearchableItemAttributeSet (CSCustomAttributes)

- (void)setValue:(nullable id<NSSecureCoding>)value forCustomKey:(CSCustomAttributeKey *)key;
- (nullable id<NSSecureCoding>)valueForCustomKey:(CSCustomAttributeKey *)key;

@end

#if __OBJC2__

//Attributes to be indexed for a given NSUserActivity
CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE
@interface NSUserActivity (CSSearchableItemAttributeSet)

@property (nullable, copy) CSSearchableItemAttributeSet *contentAttributeSet;

@end

#endif

NS_ASSUME_NONNULL_END

#ifndef CoreSpotlightAPIVersion
#import <CoreSpotlight/CSSearchableItemAttributeSet_Categories.h>
#endif


