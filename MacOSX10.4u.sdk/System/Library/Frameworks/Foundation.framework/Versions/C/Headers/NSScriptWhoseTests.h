/*	NSScriptWhoseTests.h
	Copyright (c) 1997-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray;
@class NSScriptObjectSpecifier;
@class NSString;


typedef enum {
    NSEqualToComparison = 0,
    NSLessThanOrEqualToComparison,
    NSLessThanComparison,
    NSGreaterThanOrEqualToComparison,
    NSGreaterThanComparison,
    NSBeginsWithComparison,
    NSEndsWithComparison,
    NSContainsComparison
} NSTestComparisonOperation;


@interface NSScriptWhoseTest : NSObject <NSCoding> {}

- (BOOL)isTrue;

@end


@interface NSLogicalTest : NSScriptWhoseTest {
    @private
    int _operator;
    id _subTests;
}

- (id)initAndTestWithTests:(NSArray *)subTests;
- (id)initOrTestWithTests:(NSArray *)subTests;
- (id)initNotTestWithTest:(NSScriptWhoseTest *)subTest;

@end


// Given a comparison operator selector and an object specifier and either another object specifier or an actual value object this class can perform the test.
// The specifiers are evaluated normally (using the top-level container stack) before the comparison operator is evaluated.  If _object1 or _object2 is nil, the objectBeingTested is used.

@interface NSSpecifierTest : NSScriptWhoseTest {
    @private
    NSTestComparisonOperation _comparisonOperator;
    NSScriptObjectSpecifier *_object1;
    id _object2;
}

- (id)initWithObjectSpecifier:(NSScriptObjectSpecifier *)obj1 comparisonOperator:(NSTestComparisonOperation)compOp testObject:(id)obj2;

@end


@interface NSObject (NSComparisonMethods)
- (BOOL)isEqualTo:(id)object;
    // Implemented using isEqual:. Returns NO if receiver is nil.
- (BOOL)isLessThanOrEqualTo:(id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)isLessThan:(id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)isGreaterThanOrEqualTo:(id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)isGreaterThan:(id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)isNotEqualTo:(id)object;
    // Implemented using compare. Returns NO if receiver is nil.
- (BOOL)doesContain:(id)object;
    // Returns nil if receiver is not an NSArray or if array doesn't contain object.
    // This operator is not working against the database.
- (BOOL)isLike:(NSString *)object;
    // argument should be a string using simple shell wildcards (* and ?).
    // (e.g. "Stev*" or "N?XT").
    // Returns NO if receiver is not an NSString.
- (BOOL)isCaseInsensitiveLike:(NSString *)object;
@end


@interface NSObject (NSScriptingComparisonMethods)

//  Often the correct way to compare two objects for scripting is different from the correct way to compare objects programmatically.  This category defines a set of methods that can be implemented to perform the comparison appropriate for scripting that is independant of other existing methods for doing comparisons, like those defined in EOQualifier.h

// If the object1 implements the appropriate one of these methods for the comparison operation, these methods will be used.  If object1 does not implement the appropriate one of these, and object2 the inverted version, and the comparison operator is one of the first five, then the comparison operator is inverted (ie scriptingIsGreaterThan: -> scriptingIsLessThanOrEqualTo:).
// If neither object1 or object2 implement the appropriate one of these selectors, we will fall back on trying to use standard EOQualifier-type methods like isEqualto:, isGreaterThan:, etc... for the first five.

- (BOOL)scriptingIsEqualTo:(id)object;
- (BOOL)scriptingIsLessThanOrEqualTo:(id)object;
- (BOOL)scriptingIsLessThan:(id)object;
- (BOOL)scriptingIsGreaterThanOrEqualTo:(id)object;
- (BOOL)scriptingIsGreaterThan:(id)object;

- (BOOL)scriptingBeginsWith:(id)object;
- (BOOL)scriptingEndsWith:(id)object;
- (BOOL)scriptingContains:(id)object;

@end

