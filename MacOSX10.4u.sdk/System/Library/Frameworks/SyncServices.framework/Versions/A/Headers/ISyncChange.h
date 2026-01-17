/*
 * SyncServices -- ISyncChange.h
 * Copyright (c) 2003, Apple Computer, Inc.  All rights reserved.
 */

#import <SyncServices/ISyncCommon.h>

@class ISyncClient;


typedef int ISyncChangeType;
enum __ISyncChangeType {
    ISyncChangeTypeAdd = 1,
    ISyncChangeTypeModify,
    ISyncChangeTypeDelete
};


@interface ISyncChange : NSObject

+ (id)changeWithType:(ISyncChangeType)type recordIdentifier:(NSString *)recordIdentifier changes:(NSArray /* NSDictionary */ *)changes;
- (id)initWithChangeType:(ISyncChangeType)type recordIdentifier:(NSString *)recordIdentifier changes:(NSArray /* NSDictionary */ *)changes;

- (ISyncChangeType)type;
- (NSString *)recordIdentifier;

/* Returns a dictionary containing a complete copy of this record.  When applying changes to the
   engine, this will likely be nil.  When getting changes from the engine, this will contain a
   copy of the record as it appears in the Truth.  Only those keys supported by the client will be
   included in this record.  The changes array contains only the modified properties in this record. */
- (NSDictionary *)record;

/* Returns an array of dictionaries, one dictionary for each change to this record.  The
   dictionary contains the following keys:

      action (ISyncChangePropertyActionKey) - either "set" (ISyncChangePropertySet) or "clear" (ISyncChangePropertyClear).

      name (ISyncChangePropertyNameKey) - the name of the attribute or relationship being changed.

      value (ISyncChangePropertyValueKey) - the new attribute value if the attribute is being set, otherwise absent if the attribute is being cleared. */
- (NSArray /* NSDictionary */ *)changes;
@end


SYNCSERVICES_EXPORT NSString * const ISyncChangePropertyActionKey;
SYNCSERVICES_EXPORT NSString * const     ISyncChangePropertySet;
SYNCSERVICES_EXPORT NSString * const     ISyncChangePropertyClear;
SYNCSERVICES_EXPORT NSString * const ISyncChangePropertyNameKey;
SYNCSERVICES_EXPORT NSString * const ISyncChangePropertyValueKey;
