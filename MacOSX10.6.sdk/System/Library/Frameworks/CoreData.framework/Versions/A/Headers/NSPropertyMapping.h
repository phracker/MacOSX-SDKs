/*
    NSPropertyMapping.h
    Core Data
    Copyright (c) 2004-2009 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
@class NSExpression;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@interface NSPropertyMapping : NSObject {
    @private
    void *_reserved;
    void *_reserved1;
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
- (NSString *)name;
- (void)setName:(NSString *)name;


/* Returns/sets the value expression for the property mapping.  The expression is used to create the value for the destination property.
*/
- (NSExpression *)valueExpression;
- (void)setValueExpression:(NSExpression *)expression;


/* Returns/sets the user info for the property mapping.
*/
- (NSDictionary *)userInfo;
- (void)setUserInfo:(NSDictionary *)userInfo;

@end

#endif
