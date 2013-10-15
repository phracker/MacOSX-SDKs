/*	NSExpression.h
	Copyright (c) 2004-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class NSString;
@class NSArray;
@class NSMutableDictionary;
@class NSPredicate;

// Expressions are the core of the predicate implementation. When expressionValueWithObject: is called, the expression is evaluated, and a value returned which can then be handled by an operator. Expressions can be anything from constants to method invocations. Scalars should be wrapped in appropriate NSValue classes.

enum {
    NSConstantValueExpressionType = 0, // Expression that always returns the same value
    NSEvaluatedObjectExpressionType, // Expression that always returns the parameter object itself
    NSVariableExpressionType, // Expression that always returns whatever is stored at 'variable' in the bindings dictionary
    NSKeyPathExpressionType, // Expression that returns something that can be used as a key path
    NSFunctionExpressionType // Expression that returns the result of evaluating a symbol
#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
    ,
    NSUnionSetExpressionType, // Expression that returns the result of doing a unionSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSIntersectSetExpressionType, // Expression that returns the result of doing an intersectSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSMinusSetExpressionType, // Expression that returns the result of doing a minusSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSSubqueryExpressionType = 13,
    NSAggregateExpressionType
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */
#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
    ,
    NSBlockExpressionType = 19
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 */
};
typedef NSUInteger NSExpressionType;

@interface NSExpression : NSObject <NSCoding, NSCopying> {
    @private
    void *_reserved;
    NSExpressionType _expressionType;
}

+ (NSExpression *)expressionForConstantValue:(id)obj;    // Expression that returns a constant value
+ (NSExpression *)expressionForEvaluatedObject;    // Expression that returns the object being evaluated
+ (NSExpression *)expressionForVariable:(NSString *)string;    // Expression that pulls a value from the variable bindings dictionary
+ (NSExpression *)expressionForKeyPath:(NSString *)keyPath;    // Expression that invokes valueForKeyPath with keyPath
+ (NSExpression *)expressionForFunction:(NSString *)name arguments:(NSArray *)parameters;    // Expression that invokes one of the predefined functions. Will throw immediately if the selector is bad; will throw at runtime if the parameters are incorrect.
    // Predefined functions are:
    // name              parameter array contents				returns
	//-------------------------------------------------------------------------------------------------------------------------------------
    // sum:              NSExpression instances representing numbers		NSNumber 
    // count:            NSExpression instances representing numbers		NSNumber 
    // min:              NSExpression instances representing numbers		NSNumber  
    // max:              NSExpression instances representing numbers		NSNumber
    // average:          NSExpression instances representing numbers		NSNumber
    // median:           NSExpression instances representing numbers		NSNumber
    // mode:             NSExpression instances representing numbers		NSArray	    (returned array will contain all occurrences of the mode)
    // stddev:           NSExpression instances representing numbers		NSNumber
    // add:to:           NSExpression instances representing numbers		NSNumber
    // from:subtract:    two NSExpression instances representing numbers	NSNumber
    // multiply:by:      two NSExpression instances representing numbers	NSNumber
    // divide:by:        two NSExpression instances representing numbers	NSNumber
    // modulus:by:       two NSExpression instances representing numbers	NSNumber
    // sqrt:             one NSExpression instance representing numbers		NSNumber
    // log:              one NSExpression instance representing a number	NSNumber
    // ln:               one NSExpression instance representing a number	NSNumber
    // raise:toPower:    one NSExpression instance representing a number	NSNumber
    // exp:              one NSExpression instance representing a number	NSNumber
    // floor:            one NSExpression instance representing a number	NSNumber
    // ceiling:          one NSExpression instance representing a number	NSNumber
    // abs:              one NSExpression instance representing a number	NSNumber
    // trunc:            one NSExpression instance representing a number	NSNumber
    // uppercase:	 one NSExpression instance representing a string	NSString
    // lowercase:	 one NSExpression instance representing a string	NSString
    // random            none							NSNumber (integer) 
    // random:           one NSExpression instance representing a number	NSNumber (integer) such that 0 <= rand < param
    // now               none							[NSDate now]
    // bitwiseAnd:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // bitwiseOr:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // bitwiseXor:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // leftshift:by:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // rightshift:by:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // onesComplement:	 one NSExpression instance representing a numbers	NSNumber    (numbers will be treated as NSInteger)
    // noindex:		 an NSExpression					parameter   (used by CoreData to indicate that an index should be dropped)

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (NSExpression *)expressionForAggregate:(NSArray *)subexpressions; // Expression that returns a collection containing the results of other expressions
+ (NSExpression *)expressionForUnionSet:(NSExpression *)left with:(NSExpression *)right; // return an expression that will return the union of the collections expressed by left and right
+ (NSExpression *)expressionForIntersectSet:(NSExpression *)left with:(NSExpression *)right; // return an expression that will return the intersection of the collections expressed by left and right
+ (NSExpression *)expressionForMinusSet:(NSExpression *)left with:(NSExpression *)right; // return an expression that will return the disjunction of the collections expressed by left and right
+ (NSExpression *)expressionForSubquery:(NSExpression *)expression usingIteratorVariable:(NSString *)variable predicate:(id)predicate; // Expression that filters a collection by storing elements in the collection in the variable variable and keeping the elements for which qualifer returns true; variable is used as a local variable, and will shadow any instances of variable in the bindings dictionary, the variable is removed or the old value replaced once evaluation completes
+ (NSExpression *)expressionForFunction:(NSExpression *)target selectorName:(NSString *)name arguments:(NSArray *)parameters;    // Expression that invokes the selector on target with parameters. Will throw at runtime if target does not implement selector or if parameters are wrong.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

#if NS_BLOCKS_AVAILABLE
+ (NSExpression *)expressionForBlock:(id (^)(id evaluatedObject, NSArray *expressions, NSMutableDictionary *context))block arguments:(NSArray *)arguments AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; // Expression that invokes the block with the parameters; note that block expressions are not encodable or representable as parseable strings.
#endif

- (id)initWithExpressionType:(NSExpressionType)type;    // designated initializer

// accessors for individual parameters - raise if not applicable
- (NSExpressionType)expressionType;
- (id)constantValue;
- (NSString *)keyPath;
- (NSString *)function;
- (NSString *)variable;
- (NSExpression *)operand;    // the object on which the selector will be invoked (the result of evaluating a key path or one of the defined functions)
- (NSArray *)arguments;    // array of expressions which will be passed as parameters during invocation of the selector on the operand of a function expression

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (id)collection;
- (NSPredicate *)predicate;
- (NSExpression *)leftExpression; // expression which represents the left side of a set expression
- (NSExpression *)rightExpression; // expression which represents the right side of a set expression
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

#if NS_BLOCKS_AVAILABLE
- (id (^)(id, NSArray *, NSMutableDictionary *))expressionBlock;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 */

// evaluate the expression using the object and bindings- note that context is mutable here and can be used by expressions to store temporary state for one predicate evaluation
- (id)expressionValueWithObject:(id)object context:(NSMutableDictionary *)context;
@end

#endif
