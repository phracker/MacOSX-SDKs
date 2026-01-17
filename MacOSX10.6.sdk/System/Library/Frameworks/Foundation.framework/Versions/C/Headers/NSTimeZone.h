/*	NSTimeZone.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSString, NSArray, NSDictionary, NSDate, NSData, NSLocale;

@interface NSTimeZone : NSObject <NSCopying, NSCoding>

- (NSString *)name;
- (NSData *)data;

- (NSInteger)secondsFromGMTForDate:(NSDate *)aDate;
- (NSString *)abbreviationForDate:(NSDate *)aDate;
- (BOOL)isDaylightSavingTimeForDate:(NSDate *)aDate;
- (NSTimeInterval)daylightSavingTimeOffsetForDate:(NSDate *)aDate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSDate *)nextDaylightSavingTimeTransitionAfterDate:(NSDate *)aDate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

@interface NSTimeZone (NSExtendedTimeZone)

+ (NSTimeZone *)systemTimeZone;
+ (void)resetSystemTimeZone;

+ (NSTimeZone *)defaultTimeZone;
+ (void)setDefaultTimeZone:(NSTimeZone *)aTimeZone;

+ (NSTimeZone *)localTimeZone;

+ (NSArray *)knownTimeZoneNames;

+ (NSDictionary *)abbreviationDictionary;
+ (void)setAbbreviationDictionary:(NSDictionary *)dict AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

+ (NSString *)timeZoneDataVersion AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSInteger)secondsFromGMT;
- (NSString *)abbreviation;
- (BOOL)isDaylightSavingTime;
- (NSTimeInterval)daylightSavingTimeOffset AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // for current instant
- (NSDate *)nextDaylightSavingTimeTransition AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // after current instant

- (NSString *)description;

- (BOOL)isEqualToTimeZone:(NSTimeZone *)aTimeZone;

enum {
	NSTimeZoneNameStyleStandard,		// Central Standard Time
	NSTimeZoneNameStyleShortStandard,	// CST
	NSTimeZoneNameStyleDaylightSaving,	// Central Daylight Time
	NSTimeZoneNameStyleShortDaylightSaving,	// CDT
	NSTimeZoneNameStyleGeneric,		// Central Time
	NSTimeZoneNameStyleShortGeneric		// CT
};
typedef NSInteger NSTimeZoneNameStyle;

- (NSString *)localizedName:(NSTimeZoneNameStyle)style locale:(NSLocale *)locale AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

@interface NSTimeZone (NSTimeZoneCreation)

// Primary creation method is +timeZoneWithName:; the
// data-taking variants should rarely be used directly

+ (id)timeZoneWithName:(NSString *)tzName;
+ (id)timeZoneWithName:(NSString *)tzName data:(NSData *)aData;

- (id)initWithName:(NSString *)tzName;
- (id)initWithName:(NSString *)tzName data:(NSData *)aData;

// Time zones created with this never have daylight savings and the
// offset is constant no matter the date; the name and abbreviation
// do NOT follow the POSIX convention (of minutes-west).
+ (id)timeZoneForSecondsFromGMT:(NSInteger)seconds;

+ (id)timeZoneWithAbbreviation:(NSString *)abbreviation;

@end

FOUNDATION_EXPORT NSString * const NSSystemTimeZoneDidChangeNotification AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

