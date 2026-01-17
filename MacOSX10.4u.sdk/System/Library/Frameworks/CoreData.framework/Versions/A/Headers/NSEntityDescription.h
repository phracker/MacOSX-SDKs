/*
    NSEntityDescription.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSArray;
@class NSDictionary;
@class NSManagedObjectModel;
@class NSMutableDictionary;
@class NSString;
@class NSManagedObjectContext;
@class NSManagedObject;

// Entities describe the "types" of objects available.
@interface NSEntityDescription : NSObject <NSCoding, NSCopying> {
@private
	void *_reserved;
	void *_reserved2;
	void *_reserved3;
	void *_reserved4;
    NSManagedObjectModel *_model;
    NSString *_classNameForEntity;
    Class _instanceClass;
    NSString *_name;
    NSEntityDescription *_rootentity;
    NSEntityDescription *_superentity;
    NSMutableDictionary *_subentities;
    NSMutableDictionary *_properties;
    id _propertyMapping;
    NSRange *_propertyRanges;
    struct __entityDescriptionFlags {
        unsigned int _isAbstract:1;
        unsigned int _shouldValidateOnSave:1;
        unsigned int _isImmutable:1;
        unsigned int _reservedEntityDescription:29;
    } _entityDescriptionFlags;
    NSMutableDictionary *_mappings;
    NSMutableDictionary *_userInfo;
    id _flattenedSubentities;
    id* _propertyGetters;
    id* _propertySetters;
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

@end

#endif
