/*	NSUserDefaults.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSData, NSDictionary, NSMutableDictionary, NSString, NSURL;

FOUNDATION_EXPORT NSString * const NSGlobalDomain;
FOUNDATION_EXPORT NSString * const NSArgumentDomain;
FOUNDATION_EXPORT NSString * const NSRegistrationDomain;

@interface NSUserDefaults : NSObject {
@private
    id _private;
    void *_reserved[4];
}

+ (NSUserDefaults *)standardUserDefaults;
+ (void)resetStandardUserDefaults;

- (id)init;
- (id)initWithUser:(NSString *)username;

- (id)objectForKey:(NSString *)defaultName;
- (void)setObject:(id)value forKey:(NSString *)defaultName;
- (void)removeObjectForKey:(NSString *)defaultName;

- (NSString *)stringForKey:(NSString *)defaultName;
- (NSArray *)arrayForKey:(NSString *)defaultName;
- (NSDictionary *)dictionaryForKey:(NSString *)defaultName;
- (NSData *)dataForKey:(NSString *)defaultName;
- (NSArray *)stringArrayForKey:(NSString *)defaultName;
- (NSInteger)integerForKey:(NSString *)defaultName;
- (float)floatForKey:(NSString *)defaultName;
- (double)doubleForKey:(NSString *)defaultName;
- (BOOL)boolForKey:(NSString *)defaultName;
- (NSURL *)URLForKey:(NSString *)defaultName AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (void)setInteger:(NSInteger)value forKey:(NSString *)defaultName;
- (void)setFloat:(float)value forKey:(NSString *)defaultName;
- (void)setDouble:(double)value forKey:(NSString *)defaultName;
- (void)setBool:(BOOL)value forKey:(NSString *)defaultName;
- (void)setURL:(NSURL *)url forKey:(NSString *)defaultName AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (void)registerDefaults:(NSDictionary *)registrationDictionary;

- (void)addSuiteNamed:(NSString *)suiteName;
- (void)removeSuiteNamed:(NSString *)suiteName;

- (NSDictionary *)dictionaryRepresentation;

- (NSArray *)volatileDomainNames;
- (NSDictionary *)volatileDomainForName:(NSString *)domainName;
- (void)setVolatileDomain:(NSDictionary *)domain forName:(NSString *)domainName;
- (void)removeVolatileDomainForName:(NSString *)domainName;

- (NSArray *)persistentDomainNames;
- (NSDictionary *)persistentDomainForName:(NSString *)domainName;
- (void)setPersistentDomain:(NSDictionary *)domain forName:(NSString *)domainName;
- (void)removePersistentDomainForName:(NSString *)domainName;

- (BOOL)synchronize;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)objectIsForcedForKey:(NSString *)key;
- (BOOL)objectIsForcedForKey:(NSString *)key inDomain:(NSString *)domain;
#endif


@end

FOUNDATION_EXPORT NSString * const NSUserDefaultsDidChangeNotification;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
/* The following keys and their values are deprecated in Mac OS X 10.5 "Leopard". Developers should use NSLocale, NSDateFormatter and NSNumberFormatter to retrieve the values formerly returned by these keys.
 */
FOUNDATION_EXPORT NSString * const NSWeekDayNameArray DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSShortWeekDayNameArray DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSMonthNameArray DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSShortMonthNameArray DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSTimeFormatString DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSDateFormatString DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSTimeDateFormatString DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSShortTimeDateFormatString DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSCurrencySymbol DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSDecimalSeparator DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSThousandsSeparator DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSDecimalDigits DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSAMPMDesignation DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSHourNameDesignations DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSYearMonthWeekDesignations DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSEarlierTimeDesignations DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSLaterTimeDesignations DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSThisDayDesignations DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSNextDayDesignations DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSNextNextDayDesignations DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSPriorDayDesignations DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSDateTimeOrdering DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSInternationalCurrencyString DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSShortDateFormatString DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSPositiveCurrencyFormatString DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT NSString * const NSNegativeCurrencyFormatString DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
#endif

