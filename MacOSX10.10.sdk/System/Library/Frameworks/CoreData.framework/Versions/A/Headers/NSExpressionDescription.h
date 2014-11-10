/*
 NSExpressionDescription.h
 Core Data
 Copyright (c) 2004-2012 Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <CoreData/NSPropertyDescription.h>
#import <CoreData/NSAttributeDescription.h>

@class NSExpression;

/* Special property description type intended for use with the NSFetchRequest -propertiesToFetch method.
   An NSExpressionDescription describes a column to be returned from a fetch that may not appear 
   directly as an attribute or relationship on an entity. Examples would be: upper(attribute) or
   max(attribute). NSExpressionDescriptions cannot be set as properties on NSEntityDescription. */
NS_CLASS_AVAILABLE(10_6,3_0)
@interface NSExpressionDescription : NSPropertyDescription {
	@private
	id _reservedtype1_1;
	id _reservedtype1_2;
    NSAttributeType _reservedtype1_3;
    id _reservedtype1_4;
    NSUInteger _reservedtype1_5;
    id _reservedtype1_6;
	void *_reservedtype2_1;
	void *_reservedtype2_2;
	void *_reservedtype2_3;
	NSExpression *_expression;
	NSAttributeType _expressionResultType;
}

@property (strong) NSExpression *expression;

@property () NSAttributeType expressionResultType;

@end

