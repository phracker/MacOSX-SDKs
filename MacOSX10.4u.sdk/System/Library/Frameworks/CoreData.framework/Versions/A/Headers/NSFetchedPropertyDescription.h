/*
    NSFetchedPropertyDescription.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <CoreData/NSPropertyDescription.h>

@class NSFetchRequest;

// Fetched properties allow to specify related objects through a "weakly" resolved property, so there is no actual join necessary.
@interface NSFetchedPropertyDescription : NSPropertyDescription {
@private
	void *_reserved5;
	void *_reserved6;
    NSFetchRequest *_fetchRequest;
    NSString *_lazyFetchRequestEntityName;
}

// As part of the predicate for a fetched property, you can use the two variables $FETCH_SOURCE (which is the managed object fetching the property) and $FETCHED_PROPERTY (which is the NSFetchedPropertyDescription instance).
- (NSFetchRequest *)fetchRequest;
- (void)setFetchRequest:(NSFetchRequest *)fetchRequest;

@end

#endif
