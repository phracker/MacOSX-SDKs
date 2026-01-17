/*
    NSManagedObjectModel.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>

@class NSArray;
@class NSDictionary;
@class NSEntityDescription;
@class NSFetchRequest;
@class NSMutableDictionary;
@class NSString;
@class NSURL;

// Models describe object graphs to be managed. Models (and their entities/properties/fetch request templates) are editable until they are used by a persistent store coordinator, allowing developers to create/modify them dynamically. However, once a model is being used, it MUST NOT be changed. When the persistent store coordinator first fetches data using a model, it will become uneditable. Any attempt to mutate a model or any of it's subobjects after that point will cause an exception to be thrown. If you need to modify a model that is in use, create a copy, modify the copy, and then discard the objects with the old model.
@interface NSManagedObjectModel : NSObject <NSCoding, NSCopying> {
@private
	void *_reserved;
	void *_reserved2;
	void *_reserved3;
    id _localizationPolicy;
    NSMutableDictionary *_entities;
    NSMutableDictionary *_configurations;
    NSMutableDictionary *_fetchRequestTemplates;
    struct __managedObjectModelFlags {
        unsigned int _isInUse:1;
        unsigned int _reservedEntityDescription:31;
    } _managedObjectModelFlags;
}

+ (NSManagedObjectModel *)mergedModelFromBundles:(NSArray *)bundles;    // looks up all models in the specified bundles and merges them; if nil is specified as argument, uses the main bundle

+ (NSManagedObjectModel *)modelByMergingModels:(NSArray *)models;    // combines multiple models (typically from different frameworks) into one

- (id)init;    // designated initializer
- (id)initWithContentsOfURL:(NSURL *)url;

- (NSDictionary *)entitiesByName;
- (NSArray *)entities;
- (void)setEntities:(NSArray *)entities;

- (NSArray *)configurations;    // returns all available configuration names
- (NSArray *)entitiesForConfiguration:(NSString *)configuration;
- (void)setEntities:(NSArray *)entities forConfiguration:(NSString *)configuration;

// fetch request templates allow to pre-define queries and their parameters in the model (with the tool) - typically they contain variables that need to be substituted at runtime.
- (void)setFetchRequestTemplate:(NSFetchRequest *)fetchRequestTemplate forName:(NSString *)name;
- (NSFetchRequest *)fetchRequestTemplateForName:(NSString *)name;
- (NSFetchRequest *)fetchRequestFromTemplateWithName:(NSString *)name substitutionVariables:(NSDictionary *)variables;    // returns a copy of the fetch request template with the variable bindings substituted - this is the usual way to bind an "abstractly" defined fetch request template to a concrete fetch

/*
 NSDictionary containing localized string values for entities, properties, and error strings related to this model. The key and value pattern follows:
 key = "Entity/NonLocalizedEntityName"
 value = "LocalizedEntityName"
 
 // for properties of the same non-localized name in differenct entities, which should have different localized names
 key = "Property/NonLocalizedPropertyName/Entity/EntityName" 
 value = "LocalizedPropertyName"
 
 key = "Property/NonLocalizedPropertyName"
 value = "LocalizedPropertyName"
 
 key = "ErrorString/NonLocalizedErrorString"
 value = "LocalizedErrorString"
 */
- (NSDictionary *)localizationDictionary;
- (void)setLocalizationDictionary:(NSDictionary *)localizationDictionary;

@end

#endif
