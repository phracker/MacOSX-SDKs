/*	NSClassDescription.h
	Copyright (c) 1995-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSException.h>

@class NSString, NSArray, NSDictionary;

@interface NSClassDescription : NSObject

+ (void)registerClassDescription:(NSClassDescription *)description forClass:(Class)aClass;
+ (void)invalidateClassDescriptionCache;
+ (NSClassDescription *)classDescriptionForClass:(Class)aClass;

- (NSArray *)attributeKeys;
- (NSArray *)toOneRelationshipKeys;
- (NSArray *)toManyRelationshipKeys;
- (NSString *)inverseForRelationshipKey:(NSString *)relationshipKey;

@end

@interface NSObject (NSClassDescriptionPrimitives)

- (NSClassDescription *)classDescription;
- (NSArray *)attributeKeys;
- (NSArray *)toOneRelationshipKeys;
- (NSArray *)toManyRelationshipKeys;
- (NSString *)inverseForRelationshipKey:(NSString *)relationshipKey;

@end

FOUNDATION_EXPORT NSString *NSClassDescriptionNeededForClassNotification;

