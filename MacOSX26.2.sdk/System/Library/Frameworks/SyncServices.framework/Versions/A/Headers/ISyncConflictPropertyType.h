/*
 * SyncServices -- ISDPropertyConflictInformation.h
 * Copyright (c) 2009, Apple, Inc.  All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

//This protocol is to provide access to a subset of properyt information possibly useful
//to automatic conflict resolvers.  
@protocol ISyncConflictPropertyType
- (NSString *)name NS_DEPRECATED_MAC(10_4, 10_7);
- (NSString *)type NS_DEPRECATED_MAC(10_4, 10_7);
- (NSString *)subtype NS_DEPRECATED_MAC(10_4, 10_7);
- (NSArray *)enumValues NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL) isRelationship NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL) isToMany NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL) isRequired NS_DEPRECATED_MAC(10_4, 10_7);
@end
