/*
    NSManagedObject.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>
#import <Foundation/NSKeyValueObserving.h>

@class NSDictionary;
@class NSEntityDescription;
@class NSError;
@class NSManagedObjectContext;
@class NSManagedObjectID;
@class NSString;

@interface NSManagedObject : NSObject {
@private
    NSManagedObjectID *_cd_objectID;
    id _cd_faultHandler;
    NSManagedObjectContext *_cd_managedObjectContext;
    id _cd_rawData;
    NSDictionary *_cd_originalSnapshot;
    NSDictionary *_cd_lastSnapshot;
    u_int32_t _cd_stateFlags;
    u_int32_t _cd_rc;
    void *_cd_observationInfo;
    u_int32_t _cd_lockingInfo;
    void *_cd_reserved1;
}

- (id)initWithEntity:(NSEntityDescription *)entity insertIntoManagedObjectContext:(NSManagedObjectContext *)context;    // designated initializer

// identity
- (NSManagedObjectContext *)managedObjectContext;
- (NSEntityDescription *)entity;
- (NSManagedObjectID *)objectID;

// state - methods can be used through KVC, for example for enabling/disabling widgets based on the state of the object
- (BOOL)isInserted;
- (BOOL)isUpdated;
- (BOOL)isDeleted;
- (BOOL)isFault;    // this information is useful in many situations when computations are optional - this can be used to avoid growing the object graph unnecessarily (which allows to control performance as it can avoid time consuming fetches from databases)

// lifecycle/change management (includes key-value observing methods)
- (void)willAccessValueForKey:(NSString *)key;    // read notification
- (void)didAccessValueForKey:(NSString *)key;    // read notification (together with willAccessValueForKey used to maintain inverse relationships, to fire faults, etc.) - each read access has to be wrapped in this method pair (in the same way as each write access has to be wrapped in the KVO method pair)
- (void)willChangeValueForKey:(NSString *)key;    // KVO - change notification
- (void)didChangeValueForKey:(NSString *)key;    // KVO - change notification
- (void)willChangeValueForKey:(NSString *)inKey withSetMutation:(NSKeyValueSetMutationKind)inMutationKind usingObjects:(NSSet *)inObjects;    // KVO - change notification
- (void)didChangeValueForKey:(NSString *)inKey withSetMutation:(NSKeyValueSetMutationKind)inMutationKind usingObjects:(NSSet *)inObjects;    // KVO - change notification
- (void)setObservationInfo:(void *)inObservationInfo; // KVO optimization
- (void *)observationInfo;    

- (void)awakeFromFetch;    // invoked after a fetch or after unfaulting (commonly used for computing derived values from the persisted properties)
- (void)awakeFromInsert;    // invoked after an insert (commonly used for initializing special default/initial settings)
- (void)willSave;    // commonly used to compute persisted values from other transient/scratchpad values, to set timestamps, etc. - this method can have "side effects" on the persisted values
- (void)didSave;    // commonly used to notify other objects after a save
- (void)didTurnIntoFault;    // commonly used to clear out additional transient values or caches

// value access (includes key-value coding methods)
- (id)valueForKey:(NSString *)key;    // KVC - overridden to access generic dictionary storage unless subclasses explicitly provide accessors
- (void)setValue:(id)value forKey:(NSString *)key;    // KVC - overridden to access generic dictionary storage unless subclasses explicitly provide accessors
- (id)primitiveValueForKey:(NSString *)key;    // primitive methods give access to the generic dictionary storage from subclasses that implement explicit accessors like -setName/-name to add custom document logic
- (void)setPrimitiveValue:(id)value forKey:(NSString *)key;

- (NSDictionary *)committedValuesForKeys:(NSArray *)keys;    // returns a dictionary of the last fetched or saved keys and values of this object
- (NSDictionary *)changedValues;    // returns a dictionary with the keys and (new) values that have been changed since last fetching or saving the object (this is implemented efficiently without firing relationship faults)

// validation - in addition to KVC validation managed objects have hooks to validate their lifecycle state; validation is a critical piece of functionality and the following methods are likely the most commonly overridden methods in custom subclasses
- (BOOL)validateValue:(id *)value forKey:(NSString *)key error:(NSError **)error;    // KVC
- (BOOL)validateForDelete:(NSError **)error;
- (BOOL)validateForInsert:(NSError **)error;
- (BOOL)validateForUpdate:(NSError **)error;

@end

#endif
