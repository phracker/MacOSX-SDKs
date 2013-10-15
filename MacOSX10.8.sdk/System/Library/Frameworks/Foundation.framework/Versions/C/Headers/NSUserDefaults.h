/*	NSUserDefaults.h
	Copyright (c) 1994-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSData, NSDictionary, NSMutableDictionary, NSString, NSURL;

FOUNDATION_EXPORT NSString * const NSGlobalDomain;
FOUNDATION_EXPORT NSString * const NSArgumentDomain;
FOUNDATION_EXPORT NSString * const NSRegistrationDomain;

@interface NSUserDefaults : NSObject {
@private
    NSInteger _unused;
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
- (NSURL *)URLForKey:(NSString *)defaultName NS_AVAILABLE(10_6, 4_0);

- (void)setInteger:(NSInteger)value forKey:(NSString *)defaultName;
- (void)setFloat:(float)value forKey:(NSString *)defaultName;
- (void)setDouble:(double)value forKey:(NSString *)defaultName;
- (void)setBool:(BOOL)value forKey:(NSString *)defaultName;
- (void)setURL:(NSURL *)url forKey:(NSString *)defaultName NS_AVAILABLE(10_6, 4_0);

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

- (BOOL)objectIsForcedForKey:(NSString *)key;
- (BOOL)objectIsForcedForKey:(NSString *)key inDomain:(NSString *)domain;


@end

FOUNDATION_EXPORT NSString * const NSUserDefaultsDidChangeNotification;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
/* The following keys and their values are deprecated in Mac OS X 10.5 "Leopard". Developers should use NSLocale, NSDateFormatter and NSNumberFormatter to retrieve the values formerly returned by these keys.
 */
FOUNDATION_EXPORT NSString * const NSWeekDayNameArray NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSShortWeekDayNameArray NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSMonthNameArray NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSShortMonthNameArray NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSTimeFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSDateFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSTimeDateFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSShortTimeDateFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSCurrencySymbol NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSDecimalSeparator NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSThousandsSeparator NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSDecimalDigits NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSAMPMDesignation NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSHourNameDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSYearMonthWeekDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSEarlierTimeDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSLaterTimeDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSThisDayDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSNextDayDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSNextNextDayDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSPriorDayDesignations NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSDateTimeOrdering NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSInternationalCurrencyString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSShortDateFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSPositiveCurrencyFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
FOUNDATION_EXPORT NSString * const NSNegativeCurrencyFormatString NS_DEPRECATED(10_0, 10_5, NA, NA);
#endif

