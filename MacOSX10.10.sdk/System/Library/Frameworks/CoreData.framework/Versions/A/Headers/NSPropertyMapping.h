/*
    NSPropertyMapping.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSDictionary.h>

@class NSArray;
@class NSExpression;

NS_CLASS_AVAILABLE(10_5,3_0)
@interface NSPropertyMapping : NSObject {
    @private
    void *_reserved;
    NSArray *_transformValidations;
    NSArray *_propertyTransforms;
    NSString *_name;
    NSExpression *_valueExpression;
    NSDictionary *_userInfo;
    struct __propertyMappingFlags {
        unsigned int _isInUse:1;
        unsigned int _reservedPropertyMapping:31;
    } _propertyMappingFlags;
}

/* Returns/sets the name of the property in the destination entity for the mapping.  
*/
@property (copy) NSString *name;

/* Returns/sets the value expression for the property mapping.  The expression is used to create the value for the destination property.
*/
@property (strong) NSExpression *valueExpression;

/* Returns/sets the user info for the property mapping.
*/
@property (strong) NSDictionary *userInfo;

@end
