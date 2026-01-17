/*	NSUbiquitousKeyValueStore.h
	Copyright (c) 2011-2016, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>

@class NSArray, NSDictionary<KeyType, ObjectType>, NSData, NSString;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSUbiquitousKeyValueStore : NSObject {
@private
    id _private1;
    id _private2;
    id _private3;
    void *_private4;
    void *_reserved[3];
    int _daemonWakeToken;
#if DEPLOYMENT_TARGET_MACOSX
    BOOL _disabledSuddenTermination;
#endif
}

+ (NSUbiquitousKeyValueStore *)defaultStore;

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

FOUNDATION_EXPORT NSNotificationName const NSUbiquitousKeyValueStoreDidChangeExternallyNotification NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreChangeReasonKey NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreChangedKeysKey NS_AVAILABLE(10_7, 5_0);

NS_ENUM(NSInteger) {
    NSUbiquitousKeyValueStoreServerChange NS_ENUM_AVAILABLE(10_7, 5_0),
    NSUbiquitousKeyValueStoreInitialSyncChange NS_ENUM_AVAILABLE(10_7, 5_0),
    NSUbiquitousKeyValueStoreQuotaViolationChange NS_ENUM_AVAILABLE(10_7, 5_0),
    NSUbiquitousKeyValueStoreAccountChange NS_ENUM_AVAILABLE(10_8, 6_0)
};

NS_ASSUME_NONNULL_END
