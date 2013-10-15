/*	NSExpression.h
	Copyright (c) 2004-2005, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>

@class NSString;
@class NSArray;
@class NSMutableDictionary;
@class NSPredicate;

// Expressions are the core of the predicate implementation. When expressionValueWithObject: is called, the expression is evaluated, and a value returned which can then be handled by an operator. Expressions can be anything from constants to method invocations. Scalars should be wrapped in appropriate NSValue classes.

typedef enum {
    NSConstantValueExpressionType = 0, // Expression that always returns the same value
    NSEvaluatedObjectExpressionType, // Expression that always returns the parameter object itself
    NSVariableExpressionType, // Expression that always returns whatever is stored at 'variable' in the bindings dictionary
    NSKeyPathExpressionType, // Expression that returns something that can be used as a key path
    NSFunctionExpressionType // Expression that returns the result of evaluating a symbol
} NSExpressionType;


@interface NSExpression : NSObject <NSCoding, NSCopying> {
    @private
    void *_reserved;
    NSExpressionType _expressionType;
}

+ (NSExpression *)expressionForConstantValue:(id)obj;    // Expression that returns a constant value
+ (NSExpression *)expressionForEvaluatedObject;    // Expression that returns the object being evaluated
+ (NSExpression *)expressionForVariable:(NSString *)string;    // Expression that pulls a value from the variable bindings dictionary
+ (NSExpression *)expressionForKeyPath:(NSString *)keyPath;    // Expression that invokes valueForKeyPath with keyPath
+ (NSExpression *)expressionForFunction:(NSString *)name arguments:(NSArray *)parameters;    // Expression that invokes one of the following predefined functions. Will throw immediately if the selector is bad; will throw at runtime if the parameters are incorrect

	/*
	 Symbol	Parameter					Returns
	 avg	NSArray of n NSExpressions	NSNumber
	 count	NSArray of n NSExpressions	NSNumber
	 max	NSArray of n NSExpressions	NSNumber
	 min	NSArray of n NSExpressions	NSNumber
	 sum	NSArray of n NSExpressions	NSNumber
	 */

- (id)initWithExpressionType:(NSExpressionType)type;    // designated initializer

// accessors for individual parameters - raise if not applicable
- (NSExpressionType)expressionType;
- (id)constantValue;
- (NSString *)keyPath;
- (NSString *)function;
- (NSString *)variable;
- (NSExpression *)operand;    // the object on which the selector will be invoked (the result of evaluating a key path or one of the defined functions)
- (NSArray *)arguments;    // array of expressions which will be passed as parameters during invocation of the selector on the operand of a function expression

// evaluate the expression using the object and bindings- note that context is mutable here which can be used by expressions to store temporary state for one predicate evaluation
- (id)expressionValueWithObject:(id)object context:(NSMutableDictionary *)context;
@end

#endif
