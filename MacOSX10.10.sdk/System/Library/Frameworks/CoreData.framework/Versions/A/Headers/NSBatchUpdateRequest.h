/*
 NSBatchUpdateRequest.h
 Core Data
 Copyright (c) 2004-2014 Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSPredicate.h>
#import <Foundation/NSDictionary.h>

#import <CoreData/NSPersistentStoreRequest.h>
#import <CoreData/NSPersistentStoreResult.h>

@class NSEntityDescription;

//  Used to request that Core Data do a batch update of data in a persistent store without
//  loading any data into memory. May not be supported by all store types.
//  WARNING:
//  It is up to the developer creating the request to ensure that changes made by the request to
//  the underlying store do not violate any validation rules specified in the model.
NS_CLASS_AVAILABLE(10_10,8_0)
@interface NSBatchUpdateRequest : NSPersistentStoreRequest {
    @private
    id _entity;
    NSPredicate *_predicate;
    struct _requestFlags {
        unsigned int includesSubentities:1;
        unsigned int resultType:2;
        unsigned int entityIsName:1;
        unsigned int _RESERVED:28;
    } _flags;
    NSDictionary *_columnsToUpdate;
}

+ (instancetype)batchUpdateRequestWithEntityName:(NSString*)entityName;

- (instancetype)initWithEntityName:(NSString *)entityName;
- (instancetype)initWithEntity:(NSEntityDescription *)entity;

@property (copy, readonly) NSString* entityName;
@property (strong, readonly) NSEntityDescription *entity;
@property (strong) NSPredicate *predicate;

// Should the update include subentities? Defaults to YES.
@property BOOL includesSubentities;

// The type of result that should be returned from this request. Defaults to NSStatusOnlyResultType
@property NSBatchUpdateRequestResultType resultType;

// Dictionary of NSPropertyDescription|property name string -> constantValue/NSExpression pairs describing the desired updates.
// The expressions can be any NSExpression that evaluates to a scalar value.
@property (copy) NSDictionary *propertiesToUpdate;

@end
