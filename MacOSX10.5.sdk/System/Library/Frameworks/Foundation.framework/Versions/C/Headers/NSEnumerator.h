/*	NSEnumerator.h
	Copyright (c) 1995-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray;

/*
 * The fast enumeration protocol NSFastEnumeration is adopted and
 * implemented by objects wishing to make use of a fast and safe
 * enumeration style.  The language "foreach" construct then can
 * be used with such objects.
 *
 * The abstract class NSEnumerator itself is taught how to do this
 * for convenience by using -nextObject to return items one at a time.
 */

typedef struct {
    unsigned long state;
    id *itemsPtr;
    unsigned long *mutationsPtr;
    unsigned long extra[5];
} NSFastEnumerationState;

@protocol NSFastEnumeration

- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id *)stackbuf count:(NSUInteger)len;

@end

@interface NSEnumerator : NSObject <NSFastEnumeration>

- (id)nextObject;

@end

@interface NSEnumerator (NSExtendedEnumerator)

- (NSArray *)allObjects;

@end

