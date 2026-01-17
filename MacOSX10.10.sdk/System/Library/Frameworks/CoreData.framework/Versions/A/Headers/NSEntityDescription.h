/*
    NSEntityDescription.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSRange.h>

@class NSManagedObjectModel;
@class NSManagedObjectContext;
@class NSManagedObject;
@class NSData;

// Entities describe the "types" of objects available.
NS_CLASS_AVAILABLE(10_4,3_0)
@interface NSEntityDescription : NSObject <NSCoding, NSCopying, NSFastEnumeration> {
@private
	int32_t  _cd_rc;
	id _snapshotClass;
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
        unsigned int _rangesAreInDataBlob:1; 
		unsigned int _hasAttributesWithExternalDataReferences:1;
        unsigned int _hasNonstandardPrimitiveProperties:2;
        unsigned int _reservedEntityDescription:21;
    } _entityDescriptionFlags;
    __strong void *_extraIvars;
    NSMutableDictionary *_userInfo;
    id _flattenedSubentities;
    id** _kvcPropertyAccessors;
    long _modelsReferenceIDForEntity;
}

+ (NSEntityDescription *)entityForName:(NSString *)entityName inManagedObjectContext:(NSManagedObjectContext *)context;
+ (id)insertNewObjectForEntityForName:(NSString *)entityName inManagedObjectContext:(NSManagedObjectContext *)context;

@property (readonly, assign) NSManagedObjectModel *managedObjectModel;
@property (copy) NSString *managedObjectClassName;

@property (copy) NSString *name;

@property (getter=isAbstract) BOOL abstract;
@property (readonly, copy) NSDictionary *subentitiesByName;
@property (strong) NSArray *subentities;
@property (readonly, assign) NSEntityDescription *superentity;

@property (readonly, copy) NSDictionary *propertiesByName;
@property (strong) NSArray *properties;

@property (nonatomic, strong) NSDictionary *userInfo;

// convenience methods to get the most common (and most relevant) types of properties for an entity
@property (readonly, copy) NSDictionary *attributesByName;
@property (readonly, copy) NSDictionary *relationshipsByName;
- (NSArray *)relationshipsWithDestinationEntity:(NSEntityDescription *)entity;

/* Returns a boolean indicating if the receiver is a subentity of the specified entity.  (This method is the Core Data entity inheritance equivalent of -isKindOfClass:)
*/
- (BOOL)isKindOfEntity:(NSEntityDescription *)entity NS_AVAILABLE(10_5,3_0);

/* Returns the version hash for the entity.  The version hash is used to uniquely identify an entity based on the collection and configuration of properties for the entity.  The version hash uses only values which affect the persistence of data and the user-defined versionHashModifier value.  (The values which affect persistence are the name of the entity, the version hash of the superentity (if present), if the entity is abstract, and all of the version hashes for the properties.)  This value is stored as part of the version information in the metadata for stores which use this entity, as well as a definition of an entity involved in an NSEntityMapping.
*/
@property (readonly, copy) NSData *versionHash NS_AVAILABLE(10_5,3_0);

/* Returns/sets the version hash modifier for the entity.  This value is included in the version hash for the entity, allowing developers to mark/denote an entity as being a different "version" than another, even if all of the values which affect persistence are equal.  (Such a difference is important in cases where the structure of an entity is unchanged, but the format or content of data has changed.)
*/
@property (copy) NSString *versionHashModifier NS_AVAILABLE(10_5,3_0);

@property (copy) NSString *renamingIdentifier NS_AVAILABLE(10_6,3_0);

/* Returns/sets the set of compound indices for the entity. Returns/takes an array of arrays, each of which contains one or more NSPropertyDescription or NSString instances (strings must be the names of properties of the entity on which the index is created).
    This value does not form part of the entity's version hash, and may be ignored by stores which do not natively support compound
    indexes.
 */
@property (strong) NSArray *compoundIndexes NS_AVAILABLE(10_7,5_0);

@end
