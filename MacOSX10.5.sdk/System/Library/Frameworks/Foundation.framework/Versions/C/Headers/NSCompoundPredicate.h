/*	NSCompoundPredicate.h
	Copyright (c) 2004-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPredicate.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@class NSArray;

// Compound predicates are predicates which act on the results of evaluating other operators. We provide the basic boolean operators: AND, OR, and NOT.

enum {
    NSNotPredicateType = 0, 
    NSAndPredicateType,
    NSOrPredicateType,
};
typedef NSUInteger NSCompoundPredicateType;

@interface NSCompoundPredicate : NSPredicate {
    @private
    void *_reserved2;
    NSUInteger _type;
    NSArray *_subpredicates;
}

- (id)initWithType:(NSCompoundPredicateType)type subpredicates:(NSArray *)subpredicates;

- (NSCompoundPredicateType)compoundPredicateType;
- (NSArray *)subpredicates;

/*** Convenience Methods ***/
+ (NSPredicate *)andPredicateWithSubpredicates:(NSArray *)subpredicates;
+ (NSPredicate *)orPredicateWithSubpredicates:(NSArray *)subpredicates;
+ (NSPredicate *)notPredicateWithSubpredicate:(NSPredicate *)predicate;
@end

#endif
