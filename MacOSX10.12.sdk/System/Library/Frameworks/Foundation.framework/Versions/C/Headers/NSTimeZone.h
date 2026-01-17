/*	NSTimeZone.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>

@class NSString, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSDate, NSData, NSLocale;

NS_ASSUME_NONNULL_BEGIN

@interface NSTimeZone : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy) NSString *name;
@property (readonly, copy) NSData *data;

- (NSInteger)secondsFromGMTForDate:(NSDate *)aDate;
- (nullable NSString *)abbreviationForDate:(NSDate *)aDate;
- (BOOL)isDaylightSavingTimeForDate:(NSDate *)aDate;
- (NSTimeInterval)daylightSavingTimeOffsetForDate:(NSDate *)aDate NS_AVAILABLE(10_5, 2_0);
- (nullable NSDate *)nextDaylightSavingTimeTransitionAfterDate:(NSDate *)aDate NS_AVAILABLE(10_5, 2_0);

@end

@interface NSTimeZone (NSExtendedTimeZone)

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
@property (class, readonly, copy) NSTimeZone *systemTimeZone;
#endif
+ (void)resetSystemTimeZone;

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
@property (class, copy) NSTimeZone *defaultTimeZone;

@property (class, readonly, copy) NSTimeZone *localTimeZone;

@property (class, readonly, copy) NSArray<NSString *> *knownTimeZoneNames;

@property (class, copy) NSDictionary<NSString *, NSString *> *abbreviationDictionary NS_AVAILABLE(10_6, 4_0);

+ (NSDictionary<NSString *, NSString *> *)abbreviationDictionary;

@property (class, readonly, copy) NSString *timeZoneDataVersion NS_AVAILABLE(10_6, 4_0);
#endif

@property (readonly) NSInteger secondsFromGMT;
@property (nullable, readonly, copy) NSString *abbreviation;
@property (readonly, getter=isDaylightSavingTime) BOOL daylightSavingTime;
@property (readonly) NSTimeInterval daylightSavingTimeOffset NS_AVAILABLE(10_5, 2_0); // for current instant
@property (nullable, readonly, copy) NSDate *nextDaylightSavingTimeTransition NS_AVAILABLE(10_5, 2_0); // after current instant

@property (readonly, copy) NSString *description;

- (BOOL)isEqualToTimeZone:(NSTimeZone *)aTimeZone;

typedef NS_ENUM(NSInteger, NSTimeZoneNameStyle) {
	NSTimeZoneNameStyleStandard,		// Central Standard Time
	NSTimeZoneNameStyleShortStandard,	// CST
	NSTimeZoneNameStyleDaylightSaving,	// Central Daylight Time
	NSTimeZoneNameStyleShortDaylightSaving,	// CDT
	NSTimeZoneNameStyleGeneric,		// Central Time
	NSTimeZoneNameStyleShortGeneric		// CT
};

- (nullable NSString *)localizedName:(NSTimeZoneNameStyle)style locale:(nullable NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

@end

@interface NSTimeZone (NSTimeZoneCreation)

// Primary creation method is +timeZoneWithName:; the
// data-taking variants should rarely be used directly

+ (nullable instancetype)timeZoneWithName:(NSString *)tzName;
+ (nullable instancetype)timeZoneWithName:(NSString *)tzName data:(nullable NSData *)aData;

- (nullable instancetype)initWithName:(NSString *)tzName;
- (nullable instancetype)initWithName:(NSString *)tzName data:(nullable NSData *)aData;

// Time zones created with this never have daylight savings and the
// offset is constant no matter the date; the name and abbreviation
// do NOT follow the POSIX convention (of minutes-west).
+ (instancetype)timeZoneForSecondsFromGMT:(NSInteger)seconds;

+ (nullable instancetype)timeZoneWithAbbreviation:(NSString *)abbreviation;

@end

FOUNDATION_EXPORT NSNotificationName const NSSystemTimeZoneDidChangeNotification NS_AVAILABLE(10_5, 2_0);

NS_ASSUME_NONNULL_END
