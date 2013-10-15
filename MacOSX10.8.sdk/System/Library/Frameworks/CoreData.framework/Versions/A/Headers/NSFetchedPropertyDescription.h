/*
    NSFetchedPropertyDescription.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreData/NSPropertyDescription.h>

@class NSFetchRequest;

// Fetched properties allow to specify related objects through a "weakly" resolved property, so there is no actual join necessary.
NS_CLASS_AVAILABLE(10_4,3_0)
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
