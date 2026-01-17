/*	NSExpression.h
	Copyright (c) 2004-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;
@class NSArray;
@class NSMutableDictionary;
@class NSPredicate;

// Expressions are the core of the predicate implementation. When expressionValueWithObject: is called, the expression is evaluated, and a value returned which can then be handled by an operator. Expressions can be anything from constants to method invocations. Scalars should be wrapped in appropriate NSValue classes.

typedef NS_ENUM(NSUInteger, NSExpressionType) {
    NSConstantValueExpressionType = 0, // Expression that always returns the same value
    NSEvaluatedObjectExpressionType, // Expression that always returns the parameter object itself
    NSVariableExpressionType, // Expression that always returns whatever is stored at 'variable' in the bindings dictionary
    NSKeyPathExpressionType, // Expression that returns something that can be used as a key path
    NSFunctionExpressionType, // Expression that returns the result of evaluating a symbol
    NSUnionSetExpressionType NS_ENUM_AVAILABLE(10_5, 3_0), // Expression that returns the result of doing a unionSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSIntersectSetExpressionType NS_ENUM_AVAILABLE(10_5, 3_0), // Expression that returns the result of doing an intersectSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSMinusSetExpressionType NS_ENUM_AVAILABLE(10_5, 3_0), // Expression that returns the result of doing a minusSet: on two expressions that evaluate to flat collections (arrays or sets)
    NSSubqueryExpressionType NS_ENUM_AVAILABLE(10_5, 3_0) = 13,
    NSAggregateExpressionType NS_ENUM_AVAILABLE(10_5, 3_0)
#if NS_BLOCKS_AVAILABLE
    ,
    NSBlockExpressionType = 19
#endif /* NS_BLOCKS_AVAILABLE */
};

NS_CLASS_AVAILABLE(10_4, 3_0)
@interface NSExpression : NSObject <NSCoding, NSCopying> {
    @private
    void *_reserved;
    NSExpressionType _expressionType;
}

+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat argumentArray:(NSArray *)arguments NS_AVAILABLE(10_6,4_0);
+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat, ...  NS_AVAILABLE(10_6,4_0);
+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat arguments:(va_list)argList NS_AVAILABLE(10_6,4_0);

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

+ (NSExpression *)expressionForAggregate:(NSArray *)subexpressions NS_AVAILABLE(10_5, 3_0); // Expression that returns a collection containing the results of other expressions
+ (NSExpression *)expressionForUnionSet:(NSExpression *)left with:(NSExpression *)right NS_AVAILABLE(10_5, 3_0); // return an expression that will return the union of the collections expressed by left and right
+ (NSExpression *)expressionForIntersectSet:(NSExpression *)left with:(NSExpression *)right NS_AVAILABLE(10_5, 3_0); // return an expression that will return the intersection of the collections expressed by left and right
+ (NSExpression *)expressionForMinusSet:(NSExpression *)left with:(NSExpression *)right NS_AVAILABLE(10_5, 3_0); // return an expression that will return the disjunction of the collections expressed by left and right
+ (NSExpression *)expressionForSubquery:(NSExpression *)expression usingIteratorVariable:(NSString *)variable predicate:(id)predicate NS_AVAILABLE(10_5, 3_0); // Expression that filters a collection by storing elements in the collection in the variable variable and keeping the elements for which qualifer returns true; variable is used as a local variable, and will shadow any instances of variable in the bindings dictionary, the variable is removed or the old value replaced once evaluation completes
+ (NSExpression *)expressionForFunction:(NSExpression *)target selectorName:(NSString *)name arguments:(NSArray *)parameters NS_AVAILABLE(10_5, 3_0);    // Expression that invokes the selector on target with parameters. Will throw at runtime if target does not implement selector or if parameters are wrong.

#if NS_BLOCKS_AVAILABLE
+ (NSExpression *)expressionForBlock:(id (^)(id evaluatedObject, NSArray *expressions, NSMutableDictionary *context))block arguments:(NSArray *)arguments NS_AVAILABLE(10_6, 4_0); // Expression that invokes the block with the parameters; note that block expressions are not encodable or representable as parseable strings.
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

- (id)collection NS_AVAILABLE(10_5, 3_0);
- (NSPredicate *)predicate NS_AVAILABLE(10_5, 3_0);
- (NSExpression *)leftExpression NS_AVAILABLE(10_5, 3_0); // expression which represents the left side of a set expression
- (NSExpression *)rightExpression NS_AVAILABLE(10_5, 3_0); // expression which represents the right side of a set expression

#if NS_BLOCKS_AVAILABLE
- (id (^)(id, NSArray *, NSMutableDictionary *))expressionBlock NS_AVAILABLE(10_6, 4_0);
#endif /* NS_BLOCKS_AVAILABLE */

// evaluate the expression using the object and bindings- note that context is mutable here and can be used by expressions to store temporary state for one predicate evaluation
- (id)expressionValueWithObject:(id)object context:(NSMutableDictionary *)context;
@end

