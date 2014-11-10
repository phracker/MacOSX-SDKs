/*	NSClassDescription.h
	Copyright (c) 1995-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSException.h>

@class NSString, NSArray, NSDictionary;

@interface NSClassDescription : NSObject

+ (void)registerClassDescription:(NSClassDescription *)description forClass:(Class)aClass;
+ (void)invalidateClassDescriptionCache;
+ (NSClassDescription *)classDescriptionForClass:(Class)aClass;

@property (readonly, copy) NSArray *attributeKeys;
@property (readonly, copy) NSArray *toOneRelationshipKeys;
@property (readonly, copy) NSArray *toManyRelationshipKeys;
- (NSString *)inverseForRelationshipKey:(NSString *)relationshipKey;

@end

@interface NSObject (NSClassDescriptionPrimitives)

@property (readonly, copy) NSClassDescription *classDescription;
@property (readonly, copy) NSArray *attributeKeys;
@property (readonly, copy) NSArray *toOneRelationshipKeys;
@property (readonly, copy) NSArray *toManyRelationshipKeys;
- (NSString *)inverseForRelationshipKey:(NSString *)relationshipKey;

@end

FOUNDATION_EXPORT NSString *NSClassDescriptionNeededForClassNotification;

