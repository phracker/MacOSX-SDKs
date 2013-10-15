/*
    NSMappingModel.h
    Core Data
    Copyright (c) 2004-2007 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class NSManagedObjectModel;

@interface NSMappingModel: NSObject {
    @private
    void *_reserved;
    void *_reserved1;
    void *_reserved2;
    NSMutableArray *_entityMappings;
    NSMutableDictionary *_entityMappingsByName;
    struct __modelMappingFlags {
        unsigned int _isInUse:1;
        unsigned int _reservedModelMapping:31;
    } _modelMappingFlags;

}


/* Returns the mapping model to translate data from the source to the destination model.  This method is a companion to the mergedModelFromBundles: methods;  in this case, the framework uses the version information from the models to locate the appropriate mapping model in the available bundles.  If the mapping model for the models cannot be found, this method returns nil. 
*/
+ (NSMappingModel *)mappingModelFromBundles:(NSArray *)bundles forSourceModel:(NSManagedObjectModel *)sourceModel destinationModel:(NSManagedObjectModel *)destinationModel;

/* Loads the mapping model from the specified URL.
*/
- (id)initWithContentsOfURL:(NSURL *)url;


/* Returns/sets the collection of entity mappings for the model.  The order of the mappings dictates the order in which they will be processed during migration.
*/
- (NSArray *)entityMappings;
- (void)setEntityMappings:(NSArray *)mappings;


/* Returns a dictionary of the entity mappings for the model, keyed by their respective name.  (This API is provided for quick access to a mapping by name, rather than iterating the ordered entityMapping array.)
*/
- (NSDictionary *)entityMappingsByName;

@end

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

