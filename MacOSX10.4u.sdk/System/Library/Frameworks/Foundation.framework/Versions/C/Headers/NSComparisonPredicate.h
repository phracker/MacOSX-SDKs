/*	NSComparisonPredicate.h
	Copyright (c) 2004-2005, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSPredicate.h>

// Flags(s) that can be passed to the factory to indicate that a operator operating on strings should do so in a case insensitive fashion.
enum {
    NSCaseInsensitivePredicateOption = 0x01,
    NSDiacriticInsensitivePredicateOption = 0x02,
};

// Describes how the operator is modified: can be direct, ALL, or ANY
typedef enum {
    NSDirectPredicateModifier = 0, // Do a direct comparison
    NSAllPredicateModifier, // ALL toMany.x = y
    NSAnyPredicateModifier // ANY toMany.x = y
} NSComparisonPredicateModifier;

// Type basic set of operators defined. Most are obvious; NSCustomSelectorPredicateOperatorType allows a developer to create an operator which uses the custom selector specified in the constructor to do the evaluation.
typedef enum {
    NSLessThanPredicateOperatorType = 0, // compare: returns NSOrderedAscending
    NSLessThanOrEqualToPredicateOperatorType, // compare: returns NSOrderedAscending || NSOrderedSame
    NSGreaterThanPredicateOperatorType, // compare: returns NSOrderedDescending
    NSGreaterThanOrEqualToPredicateOperatorType, // compare: returns NSOrderedDescending || NSOrderedSame
    NSEqualToPredicateOperatorType, // isEqual: returns true
    NSNotEqualToPredicateOperatorType, // isEqual: returns false
    NSMatchesPredicateOperatorType,
    NSLikePredicateOperatorType,
    NSBeginsWithPredicateOperatorType,
    NSEndsWithPredicateOperatorType,
    NSInPredicateOperatorType, // rhs contains lhs returns true
    NSCustomSelectorPredicateOperatorType
} NSPredicateOperatorType;

@class NSPredicateOperator;
@class NSExpression;

// Comparison predicates are predicates which do some form of comparison between the results of two expressions and return a BOOL. They take an operator, a left expression, and a right expression, and return the result of invoking the operator with the results of evaluating the expressions.

@interface NSComparisonPredicate : NSPredicate {
    @private
    void *_reserved2;
    NSPredicateOperator *_predicateOperator;
    NSExpression *_lhs;
    NSExpression *_rhs;
}

+ (NSPredicate *)predicateWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs modifier:(NSComparisonPredicateModifier)modifier type:(NSPredicateOperatorType)type options:(unsigned)options;
+ (NSPredicate *)predicateWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs customSelector:(SEL)selector;

- (id)initWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs modifier:(NSComparisonPredicateModifier)modifier type:(NSPredicateOperatorType)type options:(unsigned)options;
- (id)initWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs customSelector:(SEL)selector;

- (NSPredicateOperatorType)predicateOperatorType;
- (NSComparisonPredicateModifier)comparisonPredicateModifier;
- (NSExpression *)leftExpression;
- (NSExpression *)rightExpression;
- (SEL)customSelector;
- (unsigned)options;

@end

#endif
