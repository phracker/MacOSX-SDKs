/*	NSEnumerator.h
	Copyright 1995-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray;

/****************	Abstract Enumerator	****************/

@interface NSEnumerator : NSObject

- (id)nextObject;

@end

@interface NSEnumerator (NSExtendedEnumerator)

- (NSArray *)allObjects;

@end

