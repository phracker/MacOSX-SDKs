/*
    NSManagedObject.h
    Core Data
    Copyright (c) 2004-2007 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSKeyValueObserving.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@class NSDictionary;
@class NSEntityDescription;
@class NSError;
@class NSManagedObjectContext;
@class NSManagedObjectID;
@class NSString;

@interface NSManagedObject : NSObject {
@private
    int32_t             _cd_rc;
    uintptr_t           _cd_stateFlags;
    id                  _cd_rawData;
    id                  _cd_entity;
    __weak NSManagedObjectContext* _cd_managedObjectContext;
    NSManagedObjectID*  _cd_objectID;
    id                  _cd_faultHandler;
    id                  _cd_observationInfo;
    id*                 _cd_snapshots;
    uintptr_t           _cd_lockingInfo;
    id                  _cd_queueReference;
}

// The designated initializer.
- (id)initWithEntity:(NSEntityDescription *)entity insertIntoManagedObjectContext:(NSManagedObjectContext *)context;    

// identity
- (NSManagedObjectContext *)managedObjectContext;
- (NSEntityDescription *)entity;
- (NSManagedObjectID *)objectID;

// state - methods can be used through KVC, for example for enabling/disabling widgets based on the state of the object
- (BOOL)isInserted;
- (BOOL)isUpdated;
- (BOOL)isDeleted;

// this information is useful in many situations when computations are optional - this can be used to avoid growing the object graph unnecessarily (which allows to control performance as it can avoid time consuming fetches from databases)
- (BOOL)isFault;    

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
// returns a Boolean indicating if the relationship for the specified key is a fault.  If a value of NO is returned, the resulting relationship is a realized object;  otherwise the relationship is a fault.  If the specified relationship is a fault, calling this method does not result in the fault firing.
- (BOOL) hasFaultForRelationshipNamed:(NSString *)key; 
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */


// lifecycle/change management (includes key-value observing methods)
- (void)willAccessValueForKey:(NSString *)key;      // read notification
- (void)didAccessValueForKey:(NSString *)key;       // read notification (together with willAccessValueForKey used to maintain inverse relationships, to fire faults, etc.) - each read access has to be wrapped in this method pair (in the same way as each write access has to be wrapped in the KVO method pair)

// KVO change notification
- (void)willChangeValueForKey:(NSString *)key;
- (void)didChangeValueForKey:(NSString *)key;
- (void)willChangeValueForKey:(NSString *)inKey withSetMutation:(NSKeyValueSetMutationKind)inMutationKind usingObjects:(NSSet *)inObjects;
- (void)didChangeValueForKey:(NSString *)inKey withSetMutation:(NSKeyValueSetMutationKind)inMutationKind usingObjects:(NSSet *)inObjects;

// KVO optimization
- (void)setObservationInfo:(void *)inObservationInfo; 
- (void *)observationInfo;    

// invoked after a fetch or after unfaulting (commonly used for computing derived values from the persisted properties)
- (void)awakeFromFetch;    

// invoked after an insert (commonly used for initializing special default/initial settings)
- (void)awakeFromInsert;    

// commonly used to compute persisted values from other transient/scratchpad values, to set timestamps, etc. - this method can have "side effects" on the persisted values
- (void)willSave;    

// commonly used to notify other objects after a save
- (void)didSave;    

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
// invoked automatically by the Core Data framework before receiver is converted (back) to a fault.  This method is the companion of the -didTurnIntoFault method, and may be used to (re)set state which requires access to property values (for example, observers across keypaths.)  The default implementation does nothing.  
- (void) willTurnIntoFault;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

// commonly used to clear out additional transient values or caches
- (void)didTurnIntoFault;    


// value access (includes key-value coding methods)

// KVC - overridden to access generic dictionary storage unless subclasses explicitly provide accessors
- (id)valueForKey:(NSString *)key;    

// KVC - overridden to access generic dictionary storage unless subclasses explicitly provide accessors
- (void)setValue:(id)value forKey:(NSString *)key;    

// primitive methods give access to the generic dictionary storage from subclasses that implement explicit accessors like -setName/-name to add custom document logic
- (id)primitiveValueForKey:(NSString *)key;    
- (void)setPrimitiveValue:(id)value forKey:(NSString *)key;

// returns a dictionary of the last fetched or saved keys and values of this object
- (NSDictionary *)committedValuesForKeys:(NSArray *)keys;    

// returns a dictionary with the keys and (new) values that have been changed since last fetching or saving the object (this is implemented efficiently without firing relationship faults)
- (NSDictionary *)changedValues;    


// validation - in addition to KVC validation managed objects have hooks to validate their lifecycle state; validation is a critical piece of functionality and the following methods are likely the most commonly overridden methods in custom subclasses
- (BOOL)validateValue:(id *)value forKey:(NSString *)key error:(NSError **)error;    // KVC
- (BOOL)validateForDelete:(NSError **)error;
- (BOOL)validateForInsert:(NSError **)error;
- (BOOL)validateForUpdate:(NSError **)error;

@end

#endif
