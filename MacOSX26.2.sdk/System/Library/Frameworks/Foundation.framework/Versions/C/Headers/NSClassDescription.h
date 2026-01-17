/*	NSClassDescription.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSException.h>
#import <Foundation/NSNotification.h>

@class NSString, NSArray<ObjectType>, NSDictionary;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@interface NSClassDescription : NSObject

+ (void)registerClassDescription:(NSClassDescription *)description forClass:(Class)aClass;
+ (void)invalidateClassDescriptionCache;
+ (nullable NSClassDescription *)classDescriptionForClass:(Class)aClass;

@property (readonly, copy) NSArray<NSString *> *attributeKeys;
@property (readonly, copy) NSArray<NSString *> *toOneRelationshipKeys;
@property (readonly, copy) NSArray<NSString *> *toManyRelationshipKeys;
- (nullable NSString *)inverseForRelationshipKey:(NSString *)relationshipKey;

@end

@interface NSObject (NSClassDescriptionPrimitives)

@property (readonly, copy) NSClassDescription *classDescription;
@property (readonly, copy) NSArray<NSString *> *attributeKeys;
@property (readonly, copy) NSArray<NSString *> *toOneRelationshipKeys;
@property (readonly, copy) NSArray<NSString *> *toManyRelationshipKeys;
- (nullable NSString *)inverseForRelationshipKey:(NSString *)relationshipKey;

@end

FOUNDATION_EXPORT NSNotificationName const NSClassDescriptionNeededForClassNotification;

NS_HEADER_AUDIT_END(nullability, sendability)
