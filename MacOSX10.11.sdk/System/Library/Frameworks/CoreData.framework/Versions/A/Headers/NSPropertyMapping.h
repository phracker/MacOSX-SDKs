/*
    NSPropertyMapping.h
    Core Data
    Copyright (c) 2004-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>


NS_ASSUME_NONNULL_BEGIN

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
@property (nullable, copy) NSString *name;

/* Returns/sets the value expression for the property mapping.  The expression is used to create the value for the destination property.
*/
@property (nullable, strong) NSExpression *valueExpression;

/* Returns/sets the user info for the property mapping.
*/
@property (nullable, strong) NSDictionary *userInfo;

@end

NS_ASSUME_NONNULL_END
