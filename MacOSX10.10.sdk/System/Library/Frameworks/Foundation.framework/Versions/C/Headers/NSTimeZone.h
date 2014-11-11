/*	NSTimeZone.h
	Copyright (c) 1994-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSString, NSArray, NSDictionary, NSDate, NSData, NSLocale;

@interface NSTimeZone : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy) NSString *name;
@property (readonly, copy) NSData *data;

- (NSInteger)secondsFromGMTForDate:(NSDate *)aDate;
- (NSString *)abbreviationForDate:(NSDate *)aDate;
- (BOOL)isDaylightSavingTimeForDate:(NSDate *)aDate;
- (NSTimeInterval)daylightSavingTimeOffsetForDate:(NSDate *)aDate NS_AVAILABLE(10_5, 2_0);
- (NSDate *)nextDaylightSavingTimeTransitionAfterDate:(NSDate *)aDate NS_AVAILABLE(10_5, 2_0);

@end

@interface NSTimeZone (NSExtendedTimeZone)

+ (NSTimeZone *)systemTimeZone;
+ (void)resetSystemTimeZone;

+ (NSTimeZone *)defaultTimeZone;
+ (void)setDefaultTimeZone:(NSTimeZone *)aTimeZone;

+ (NSTimeZone *)localTimeZone;

+ (NSArray *)knownTimeZoneNames;

+ (NSDictionary *)abbreviationDictionary;
+ (void)setAbbreviationDictionary:(NSDictionary *)dict NS_AVAILABLE(10_6, 4_0);

+ (NSString *)timeZoneDataVersion NS_AVAILABLE(10_6, 4_0);

@property (readonly) NSInteger secondsFromGMT;
@property (readonly, copy) NSString *abbreviation;
@property (readonly, getter=isDaylightSavingTime) BOOL daylightSavingTime;
@property (readonly) NSTimeInterval daylightSavingTimeOffset NS_AVAILABLE(10_5, 2_0); // for current instant
@property (readonly, copy) NSDate *nextDaylightSavingTimeTransition NS_AVAILABLE(10_5, 2_0); // after current instant

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

- (NSString *)localizedName:(NSTimeZoneNameStyle)style locale:(NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

@end

@interface NSTimeZone (NSTimeZoneCreation)

// Primary creation method is +timeZoneWithName:; the
// data-taking variants should rarely be used directly

+ (instancetype)timeZoneWithName:(NSString *)tzName;
+ (instancetype)timeZoneWithName:(NSString *)tzName data:(NSData *)aData;

- (instancetype)initWithName:(NSString *)tzName;
- (instancetype)initWithName:(NSString *)tzName data:(NSData *)aData;

// Time zones created with this never have daylight savings and the
// offset is constant no matter the date; the name and abbreviation
// do NOT follow the POSIX convention (of minutes-west).
+ (instancetype)timeZoneForSecondsFromGMT:(NSInteger)seconds;

+ (instancetype)timeZoneWithAbbreviation:(NSString *)abbreviation;

@end

FOUNDATION_EXPORT NSString * const NSSystemTimeZoneDidChangeNotification NS_AVAILABLE(10_5, 2_0);

