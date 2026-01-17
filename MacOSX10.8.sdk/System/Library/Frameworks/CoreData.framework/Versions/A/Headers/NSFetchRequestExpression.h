/*
    NSFetchRequestExpression.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

enum {
    NSFetchRequestExpressionType = 50
};

NS_CLASS_AVAILABLE(10_5,3_0)
@interface NSFetchRequestExpression : NSExpression {
@private
    void* _reserved1;
    void* _reserved2;
    void* _reserved3;
    void* _reserved4;
    NSExpression* _fetchRequest;
    NSExpression* _managedObjectContext;
    struct _fetchExpressionFlags {
        unsigned int isCountOnly:1;
        unsigned int _RESERVED:31;
    } _flags;
}

/* Returns an expression which will evaluate to the result of executing a fetch request on a context.  The first argument must be an expression which evaluates to an NSFetchRequest *, and the second must be an expression which evaluates to an NSManagedObjectContext *.  If the desired result is simply the count for the request, the "countOnly" argument should be YES.
*/
+ (NSExpression*)expressionForFetch:(NSExpression*)fetch context:(NSExpression*)context countOnly:(BOOL)countFlag;


/* Returns the expression for the fetch request:  evaluating it must return an NSFetchRequest *.
*/
- (NSExpression *)requestExpression;


/* Returns the expression for the managed object context:  evaluating it must return an NSManagedObjectContext *.
*/
- (NSExpression *)contextExpression; 


/* Boolean indicating if the request will return object values or merely the count.  If the value returns NO, the managed object context (from the contextExpression) will perform executeFetchRequest:error: with the requestExpression;  if the value returns YES, the managed object context will perform countForFetchRequest:error with the requestExpression.
*/
- (BOOL)isCountOnlyRequest;

@end
