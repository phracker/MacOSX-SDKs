/*	NSUbiquitousKeyValueStore.h
	Copyright (c) 2011-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>

@class NSArray, NSDictionary<KeyType, ObjectType>, NSData, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(10.7), ios(5.0), watchos(9.0), tvos(9.0))
@interface NSUbiquitousKeyValueStore : NSObject

@property (class, readonly, strong) NSUbiquitousKeyValueStore *defaultStore;

- (nullable id)objectForKey:(NSString *)aKey;
- (void)setObject:(nullable id)anObject forKey:(NSString *)aKey;
- (void)removeObjectForKey:(NSString *)aKey;

- (nullable NSString *)stringForKey:(NSString *)aKey;
- (nullable NSArray *)arrayForKey:(NSString *)aKey;
- (nullable NSDictionary<NSString *, id> *)dictionaryForKey:(NSString *)aKey;
- (nullable NSData *)dataForKey:(NSString *)aKey;
- (long long)longLongForKey:(NSString *)aKey;
- (double)doubleForKey:(NSString *)aKey;
- (BOOL)boolForKey:(NSString *)aKey;

- (void)setString:(nullable NSString *)aString forKey:(NSString *)aKey;
- (void)setData:(nullable NSData *)aData forKey:(NSString *)aKey;
- (void)setArray:(nullable NSArray *)anArray forKey:(NSString *)aKey;
- (void)setDictionary:(nullable NSDictionary<NSString *, id> *)aDictionary forKey:(NSString *)aKey;
- (void)setLongLong:(long long)value forKey:(NSString *)aKey;
- (void)setDouble:(double)value forKey:(NSString *)aKey;
- (void)setBool:(BOOL)value forKey:(NSString *)aKey;

@property (readonly, copy) NSDictionary<NSString *, id> *dictionaryRepresentation;

- (BOOL)synchronize;

@end

FOUNDATION_EXPORT NSNotificationName const NSUbiquitousKeyValueStoreDidChangeExternallyNotification API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreChangeReasonKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreChangedKeysKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

NS_ENUM(NSInteger) {
    NSUbiquitousKeyValueStoreServerChange API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)),
    NSUbiquitousKeyValueStoreInitialSyncChange API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)),
    NSUbiquitousKeyValueStoreQuotaViolationChange API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)),
    NSUbiquitousKeyValueStoreAccountChange API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
};

NS_HEADER_AUDIT_END(nullability, sendability)
