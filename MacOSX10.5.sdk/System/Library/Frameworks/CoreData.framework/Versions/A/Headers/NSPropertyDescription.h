/*
    NSPropertyDescription.h
    Core Data
    Copyright (c) 2004-2007 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@class NSArray;
@class NSDictionary;
@class NSEntityDescription;
@class NSMutableArray;
@class NSMutableDictionary;
@class NSString;

// Properties describe values within a managed object. There are different types of properties, each of them represented by a subclass which encapsulates the specific property behavior.
@interface NSPropertyDescription : NSObject <NSCoding, NSCopying> {
@private
	void *_reserved;
	NSString *_versionHashModifier;
	NSData *_versionHash;
    __weak NSEntityDescription *_entity;
    NSString *_name;
    NSArray *_validationPredicates;
    NSArray *_validationWarnings;
    struct __propertyDescriptionFlags {
        unsigned int _isReadOnly:1;
        unsigned int _isTransient:1;
        unsigned int _isOptional:1;
        unsigned int _isIndexed:1;
        unsigned int _skipValidation:1;
        unsigned int _reservedPropertyDescription:27;
    } _propertyDescriptionFlags;    
    NSMutableDictionary *_mappings;
    NSMutableDictionary *_userInfo;
	long _entitysReferenceIDForProperty;
}

- (NSEntityDescription *)entity;

- (NSString *)name;
- (void)setName:(NSString *)name;

// The optional flag specifies whether a property's value can be nil or not (before an object can be persisted).
- (BOOL)isOptional;
- (void)setOptional:(BOOL)flag;

// The transient flag specifies whether a property's value is persisted or ignored when an object is persisted - transient properties are still managed for undo/redo, validation, etc.
- (BOOL)isTransient;
- (void)setTransient:(BOOL)flag;

// Instead of individual methods to set/get parameters like length, min and max values, formats, etc., there is a list of predicates evaluated against the managed objects and corresponding error messages (which can be localized).
- (NSArray *)validationPredicates;
- (NSArray *)validationWarnings;
- (void)setValidationPredicates:(NSArray *)validationPredicates withValidationWarnings:(NSArray *)validationWarnings;

- (NSDictionary *)userInfo;
- (void)setUserInfo:(NSDictionary *)dictionary;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Returns a boolean value indicating if the property is important for searching.  NSPersistentStores can optionally utilize this information upon store creation for operations like defining indexes.
*/
- (BOOL)isIndexed;
- (void)setIndexed:(BOOL)flag;

/* Returns the version hash for the property.  The version hash is used to uniquely identify a property based on its configuration.  The version hash uses only values which affect the persistence of data and the user-defined versionHashModifier value.  (The values which affect persistence are the name of the property, the flags for isOptional, isTransient, and isReadOnly).  This value is stored as part of the version information in the metadata for stores, as well as a definition of a property involved in an NSPropertyMapping.
*/
- (NSData *)versionHash;

/* Returns/sets the version hash modifier for the property.  This value is included in the version hash for the property, allowing developers to mark/denote a property as being a different "version" than another, even if all of the values which affects persistence are equal.  (Such a difference is important in cases where the design of a property is unchanged, but the format or content of data has changed.)
*/
- (NSString *)versionHashModifier;
- (void)setVersionHashModifier:(NSString *)modifierString;

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

@end

#endif
