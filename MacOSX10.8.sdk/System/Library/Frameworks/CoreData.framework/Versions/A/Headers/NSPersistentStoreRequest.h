/*
 NSPersistentStoreRequest.h
 Core Data
 Copyright (c) 2004-2012 Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSArray.h>

enum {
    NSFetchRequestType = 1,
    NSSaveRequestType, 
};

typedef NSUInteger NSPersistentStoreRequestType;

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSPersistentStoreRequest : NSObject <NSCopying> {
	@private
	NSArray *_affectedStores;
}

// Stores this request should be sent to.
- (NSArray*)affectedStores;
- (void)setAffectedStores:(NSArray*)stores;

// The type of the request.
- (NSPersistentStoreRequestType)requestType;

@end

