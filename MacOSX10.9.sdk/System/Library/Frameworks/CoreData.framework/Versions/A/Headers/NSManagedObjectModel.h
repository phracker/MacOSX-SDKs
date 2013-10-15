/*
    NSManagedObjectModel.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>

@class NSEntityDescription;
@class NSFetchRequest;
@class NSSet;
@class NSData;

// Models describe object graphs to be managed. Models (and their entities/properties/fetch request templates) are editable until they are used by a persistent store coordinator, allowing developers to create/modify them dynamically. However, once a model is being used, it MUST NOT be changed. When the persistent store coordinator first fetches data using a model, it will become uneditable. Any attempt to mutate a model or any of its subobjects after that point will cause an exception to be thrown. If you need to modify a model that is in use, create a copy, modify the copy, and then discard the objects with the old model.
NS_CLASS_AVAILABLE(10_4,3_0)
@interface NSManagedObjectModel : NSObject <NSCoding, NSCopying, NSFastEnumeration> {
@private
	id _dataForOptimization;
	id *_optimizationHints; 
    id _localizationPolicy;
    NSMutableDictionary *_entities;
    NSMutableDictionary *_configurations;
    NSMutableDictionary *_fetchRequestTemplates;
	NSSet *_versionIdentifiers;
    struct __managedObjectModelFlags {
        unsigned int _isInUse:1;
        unsigned int _isImmutable:1;
		unsigned int _isOptimizedForEncoding:1;
        unsigned int _reservedEntityDescription:29;
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

/* Returns the managed object model used to create the store for the specified metadata.  This method is a companion to the mergedModelFromBundles: method;  in this case, the framework uses the version information stored in the metadata for a store to locate the models/entities used to create the store in the available bundles, and return the model.  If the model for the store cannot be found, this method will return nil.
*/
+ (NSManagedObjectModel *)mergedModelFromBundles:(NSArray *)bundles forStoreMetadata:(NSDictionary *)metadata NS_AVAILABLE(10_5,3_0);


/* Returns a merged model from the specified array for the version information in the provided metadata.  (This is the companion method to mergedModelFromBundles:forStoreMetadata:)  If a model cannot be created to match the version information in the specified metadata, this method will return nil.  
*/
+ (NSManagedObjectModel *)modelByMergingModels:(NSArray *)models forStoreMetadata:(NSDictionary *)metadata NS_AVAILABLE(10_5,3_0);


/* Returns the dictionary of fetch request templates, keyed by name, for the model.  If the template contains a predicate with substitution variables, you should instead use fetchRequestFromTemplateWithName:substitutionVariables: to create a new fetch request.
*/
- (NSDictionary *)fetchRequestTemplatesByName NS_AVAILABLE(10_5,3_0);

/* Returns the collection of developer-defined version identifiers for the model.  For models created in Xcode, this value is set by the developer in the model inspector. Merged models return the combined  collection of identifiers. This value is meant to be used as a debugging hint to help developers determine the models that were combined to create a merged model. The framework does not give models a default identifier, nor does it depend this value at runtime.
*/
- (NSSet *)versionIdentifiers NS_AVAILABLE(10_5,3_0);
- (void)setVersionIdentifiers:(NSSet *)identifiers NS_AVAILABLE(10_5,3_0);


/* Compares the version information in the store metadata with the entity version of a given configuration. Returns NO if there are differences between the version information.  (For information on specific differences, developers should utilize the entityVersionHashesByName method, and perform a comparison.)
*/
- (BOOL)isConfiguration:(NSString *)configuration compatibleWithStoreMetadata:(NSDictionary *)metadata NS_AVAILABLE(10_5,3_0);


/* Returns a dictionary of the version hashes for the entities in the model, keyed by entity name.  (The dictionary of version hash information is used by Core Data to determine schema compatibility.)
*/
- (NSDictionary *)entityVersionHashesByName NS_AVAILABLE(10_5,3_0);

@end
