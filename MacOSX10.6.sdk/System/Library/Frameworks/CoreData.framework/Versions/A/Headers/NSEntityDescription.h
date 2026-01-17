/*
    NSEntityDescription.h
    Core Data
    Copyright (c) 2004-2009 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@class NSArray;
@class NSDictionary;
@class NSManagedObjectModel;
@class NSMutableDictionary;
@class NSString;
@class NSManagedObjectContext;
@class NSManagedObject;

// Entities describe the "types" of objects available.
@interface NSEntityDescription : NSObject <NSCoding, NSCopying, NSFastEnumeration> {
@private
	int32_t  _cd_rc;
	id _reserved1;
	NSString *_versionHashModifier;
	NSData *_versionHash;
    __weak NSManagedObjectModel *_model;
    NSString *_classNameForEntity;
    Class _instanceClass;
    NSString *_name;
    __weak NSEntityDescription *_rootentity;
    __weak NSEntityDescription *_superentity;
    NSMutableDictionary *_subentities;
    NSMutableDictionary *_properties;
    id _propertyMapping;
    __strong NSRange *_propertyRanges;
    struct __entityDescriptionFlags {
        unsigned int _isAbstract:1;
        unsigned int _shouldValidateOnSave:1;
        unsigned int _isImmutable:1;
        unsigned int _isFlattened:1;
        unsigned int _skipValidation:1;
        unsigned int _hasPropertiesIndexedBySpotlight:1;
        unsigned int _hasPropertiesStoredInTruthFile:1;
        unsigned int _reservedEntityDescription:25;
    } _entityDescriptionFlags;
    __strong void *_extraIvars;
    NSMutableDictionary *_userInfo;
    id _flattenedSubentities;
    id** _kvcPropertyAccessors;
    long _modelsReferenceIDForEntity;
}

+ (NSEntityDescription *)entityForName:(NSString *)entityName inManagedObjectContext:(NSManagedObjectContext *)context;
+ (id)insertNewObjectForEntityForName:(NSString *)entityName inManagedObjectContext:(NSManagedObjectContext *)context;

- (NSManagedObjectModel *)managedObjectModel;
- (NSString *)managedObjectClassName;
- (void)setManagedObjectClassName:(NSString *)name;

- (NSString *)name;
- (void)setName:(NSString *)name;

- (BOOL)isAbstract;
- (void)setAbstract:(BOOL)flag;
- (NSDictionary *)subentitiesByName;
- (NSArray *)subentities;
- (void)setSubentities:(NSArray *)array;
- (NSEntityDescription *)superentity;

- (NSDictionary *)propertiesByName;
- (NSArray *)properties;
- (void)setProperties:(NSArray *)properties;

- (NSDictionary *)userInfo;
- (void)setUserInfo:(NSDictionary *)dictionary;

// convenience methods to get the most common (and most relevant) types of properties for an entity
- (NSDictionary *)attributesByName;
- (NSDictionary *)relationshipsByName;
- (NSArray *)relationshipsWithDestinationEntity:(NSEntityDescription *)entity;

/* Returns a boolean indicating if the receiver is a subentity of the specified entity.  (This method is the Core Data entity inheritance equivalent of -isKindOfClass:)
*/
- (BOOL)isKindOfEntity:(NSEntityDescription *)entity AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Returns the version hash for the entity.  The version hash is used to uniquely identify an entity based on the collection and configuration of properties for the entity.  The version hash uses only values which affect the persistence of data and the user-defined versionHashModifier value.  (The values which affect persistence are the name of the entity, the version hash of the superentity (if present), if the entity is abstract, and all of the version hashes for the properties.)  This value is stored as part of the version information in the metadata for stores which use this entity, as well as a definition of an entity involved in an NSEntityMapping.
*/
- (NSData *)versionHash AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Returns/sets the version hash modifier for the entity.  This value is included in the version hash for the entity, allowing developers to mark/denote an entity as being a different "version" than another, even if all of the values which affect persistence are equal.  (Such a difference is important in cases where the structure of an entity is unchanged, but the format or content of data has changed.)
*/
- (NSString *)versionHashModifier AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setVersionHashModifier:(NSString *)modifierString AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSString *)renamingIdentifier AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setRenamingIdentifier:(NSString *)value AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#endif
