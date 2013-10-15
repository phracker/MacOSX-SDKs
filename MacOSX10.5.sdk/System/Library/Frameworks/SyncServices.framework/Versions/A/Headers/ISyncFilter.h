/*
 * SyncServices -- ISyncFilter.h
 * Copyright (c) 2003, Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>


/* The protocol for filtering records. */
@protocol ISyncFiltering <NSCoding>

/* Each filter must provide an implementation of isEqual:.  When setting a filter, the engine compares
   it to the previous version (if there was one).  If the filter has changed, the engine must re-filter
   all records that have been pushed to a client. */
- (BOOL)isEqual:(id)anotherFilter;

/* The entities the filter applies to.  Must not be nil or empty. */
- (NSArray /* NSString */ *)supportedEntityNames;

/* The filter method.  If NO, the record will not be applied to the client.  If the client already has
   the record, this will result in a delete being sent to the client. */
- (BOOL)shouldApplyRecord:(NSDictionary *)record withRecordIdentifier:(NSString *)recordId;

@end




@interface ISyncFilter : NSObject
+ (id <ISyncFiltering>)filterMatchingAllFilters:(NSArray /* id <ISyncFiltering> */ *)filters; // logical AND
+ (id <ISyncFiltering>)filterMatchingAtLeastOneFilter:(NSArray /* id <ISyncFiltering> */ *)filters; // logical OR
@end
