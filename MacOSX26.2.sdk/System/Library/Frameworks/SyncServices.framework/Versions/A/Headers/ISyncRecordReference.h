/*
 * SyncServices -- ISyncRecordReference.h
 * Copyright (c) 2006, Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <SyncServices/ISyncRecordSnapshot.h>

/* An ISyncRecordReference serves as a persistent reference to a record, which 
   can be used to get that record's record identifier in the scope of any
   ISyncRecordSnapshot. An ISyncRecordReference can be encoded and saved,
   and later reconstituted to be used in another process.

   If the original record the ISyncRecordReference refers to is no longer present,
   if there is another record in the truth store that has the same identity
   fields as the original object, that record's record identifier will be
   returned. */
@interface ISyncRecordReference : NSObject <NSCoding>
{
}
@end

