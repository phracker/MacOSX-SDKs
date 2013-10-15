/*	NSPredicate.h
	Copyright (c) 2004-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

// Predicates wrap some combination of expressions and operators and when evaluated return a BOOL.

@interface NSPredicate : NSObject <NSCoding, NSCopying> {
    void *_reserved;
}

// Parse predicateFormat and return an appropriate predicate
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat argumentArray:(NSArray *)arguments;
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat, ...;
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat arguments:(va_list)argList;

+ (NSPredicate *)predicateWithValue:(BOOL)value;    // return predicates that always evaluate to true/false

- (NSString *)predicateFormat;    // returns the format string of the predicate

- (NSPredicate *)predicateWithSubstitutionVariables:(NSDictionary *)variables;    // substitute constant values for variables

- (BOOL)evaluateWithObject:(id)object;    // evaluate a predicate against a single object

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (BOOL)evaluateWithObject:(id)object substitutionVariables:(NSDictionary *)bindings; // single pass evaluation substituting variables from the bindings dictionary for any variable expressions encountered
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

@end

@interface NSArray (NSPredicateSupport)
- (NSArray *)filteredArrayUsingPredicate:(NSPredicate *)predicate;    // evaluate a predicate against an array of objects and return a filtered array
@end

@interface NSMutableArray (NSPredicateSupport)
- (void)filterUsingPredicate:(NSPredicate *)predicate;    // evaluate a predicate against an array of objects and filter the mutable array directly
@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
@interface NSSet (NSPredicateSupport)
- (NSSet *)filteredSetUsingPredicate:(NSPredicate *)predicate;    // evaluate a predicate against a set of objects and return a filtered set
@end

@interface NSMutableSet (NSPredicateSupport)
- (void)filterUsingPredicate:(NSPredicate *)predicate;    // evaluate a predicate against a set of objects and filter the mutable set directly
@end
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */


#endif
