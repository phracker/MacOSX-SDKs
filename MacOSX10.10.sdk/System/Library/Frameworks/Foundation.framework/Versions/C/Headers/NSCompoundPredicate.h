/*	NSCompoundPredicate.h
	Copyright (c) 2004-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPredicate.h>

@class NSArray;

// Compound predicates are predicates which act on the results of evaluating other operators. We provide the basic boolean operators: AND, OR, and NOT.

typedef NS_ENUM(NSUInteger, NSCompoundPredicateType) {
    NSNotPredicateType = 0, 
    NSAndPredicateType,
    NSOrPredicateType,
};

NS_CLASS_AVAILABLE(10_4, 3_0)
@interface NSCompoundPredicate : NSPredicate {
    @private
    void *_reserved2;
    NSUInteger _type;
    NSArray *_subpredicates;
}

- (instancetype)initWithType:(NSCompoundPredicateType)type subpredicates:(NSArray *)subpredicates;

@property (readonly) NSCompoundPredicateType compoundPredicateType;
@property (readonly, copy) NSArray *subpredicates;

/*** Convenience Methods ***/
+ (NSCompoundPredicate *)andPredicateWithSubpredicates:(NSArray *)subpredicates;
+ (NSCompoundPredicate *)orPredicateWithSubpredicates:(NSArray *)subpredicates;
+ (NSCompoundPredicate *)notPredicateWithSubpredicate:(NSPredicate *)predicate;
@end

