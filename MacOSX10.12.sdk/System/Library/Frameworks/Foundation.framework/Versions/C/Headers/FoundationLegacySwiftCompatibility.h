#import <Foundation/NSObjCRuntime.h>

#pragma mark Swift epochs before 8

#if FOUNDATION_SWIFT_SDK_EPOCH_LESS_THAN(8)

#import <Foundation/NSBundle.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSBundle (NSLegacySwiftCompatibility)
+ (NSBundle *)mainBundle;
+ (NSArray<NSBundle *> *)allBundles;
+ (NSArray<NSBundle *> *)allFrameworks;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSCalendar.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSCalendar (NSLegacySwiftCompatibility)
+ (NSCalendar *)currentCalendar;
+ (NSCalendar *)autoupdatingCurrentCalendar NS_AVAILABLE(10_5, 2_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSCharacterSet.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSCharacterSet (NSLegacySwiftCompatibility)
+ (NSCharacterSet *)controlCharacterSet;
+ (NSCharacterSet *)whitespaceCharacterSet;
+ (NSCharacterSet *)whitespaceAndNewlineCharacterSet;
+ (NSCharacterSet *)decimalDigitCharacterSet;
+ (NSCharacterSet *)letterCharacterSet;
+ (NSCharacterSet *)lowercaseLetterCharacterSet;
+ (NSCharacterSet *)uppercaseLetterCharacterSet;
+ (NSCharacterSet *)nonBaseCharacterSet;
+ (NSCharacterSet *)alphanumericCharacterSet;
+ (NSCharacterSet *)decomposableCharacterSet;
+ (NSCharacterSet *)illegalCharacterSet;
+ (NSCharacterSet *)punctuationCharacterSet;
+ (NSCharacterSet *)capitalizedLetterCharacterSet;
+ (NSCharacterSet *)symbolCharacterSet;
+ (NSCharacterSet *)newlineCharacterSet NS_AVAILABLE(10_5, 2_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSDate (NSLegacySwiftCompatibility)
+ (NSTimeInterval)timeIntervalSinceReferenceDate;
+ (NSDate *)distantFuture;
+ (NSDate *)distantPast;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSDateFormatter.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSDateFormatter (NSLegacySwiftCompatibility)
+ (NSDateFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSDateFormatterBehavior)behavior;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSDecimalNumber.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSDecimalNumber (NSLegacySwiftCompatibility)
+ (NSDecimalNumber *)zero;
+ (NSDecimalNumber *)one;
+ (NSDecimalNumber *)minimumDecimalNumber;
+ (NSDecimalNumber *)maximumDecimalNumber;
+ (NSDecimalNumber *)notANumber;
+ (id <NSDecimalNumberBehaviors>)defaultBehavior;
+ (void)setDefaultBehavior:(id <NSDecimalNumberBehaviors>)behavior;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSException.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSAssertionHandler (NSLegacySwiftCompatibility)
+ (NSAssertionHandler *)currentHandler;
@end
NS_ASSUME_NONNULL_END

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <Foundation/NSFileCoordinator.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSFileCoordinator (NSLegacySwiftCompatibility)
+ (NSArray<id<NSFilePresenter>> *)filePresenters;
@end
NS_ASSUME_NONNULL_END
#endif

#import <Foundation/NSFileHandle.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSFileHandle (NSLegacySwiftCompatibility)
+ (NSFileHandle *)fileHandleWithStandardInput;
+ (NSFileHandle *)fileHandleWithStandardOutput;
+ (NSFileHandle *)fileHandleWithStandardError;
+ (NSFileHandle *)fileHandleWithNullDevice;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSFileManager.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSFileManager (NSLegacySwiftCompatibility)
+ (NSFileManager *)defaultManager;

@property (nullable, readonly, copy) NSDictionary<NSString *, id> *fileAttributes;
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *directoryAttributes;

- (BOOL)setAttributes:(NSDictionary<NSString *, id> *)attributes ofItemAtPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);
- (nullable NSDictionary<NSString *, id> *)attributesOfItemAtPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);
- (nullable NSDictionary<NSString *, id> *)attributesOfFileSystemForPath:(NSString *)path error:(NSError **)error NS_AVAILABLE(10_5, 2_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSHTTPCookieStorage.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSHTTPCookieStorage (NSLegacySwiftCompatibility)
+ (NSHTTPCookieStorage *)sharedHTTPCookieStorage;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSKeyValueCoding.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSObject(NSKeyValueCodingLegacySwiftCompatibility)
+ (BOOL)accessInstanceVariablesDirectly;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSLocale.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSLocale (NSLegacySwiftCompatibility)
+ (NSLocale *)autoupdatingCurrentLocale NS_AVAILABLE(10_5, 2_0);
+ (NSLocale *)currentLocale;
+ (NSLocale *)systemLocale;
+ (NSArray<NSString *> *)availableLocaleIdentifiers;
+ (NSArray<NSString *> *)ISOLanguageCodes;
+ (NSArray<NSString *> *)ISOCountryCodes;
+ (NSArray<NSString *> *)ISOCurrencyCodes;
+ (NSArray<NSString *> *)commonISOCurrencyCodes NS_AVAILABLE(10_5, 2_0);
+ (NSArray<NSString *> *)preferredLanguages NS_AVAILABLE(10_5, 2_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSNotification.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSNotificationCenter (NSLegacySwiftCompatibility)
+ (NSNotificationCenter *)defaultCenter;
- (void)addObserver:(id)observer selector:(SEL)aSelector name:(nullable NSString *)aName object:(nullable id)anObject;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSNotificationQueue.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSNotificationQueue (NSLegacySwiftCompatibility)
+ (NSNotificationQueue *)defaultQueue;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSOperation.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSOperationQueue (NSLegacySwiftCompatibility)
+ (nullable NSOperationQueue *)currentQueue NS_AVAILABLE(10_6, 4_0);
+ (NSOperationQueue *)mainQueue;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSProcessInfo.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSProcessInfo (NSLegacySwiftCompatibility)
+ (NSProcessInfo *)processInfo;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSRunLoop.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSRunLoop (NSLegacySwiftCompatibility)
+ (NSRunLoop *)currentRunLoop;
+ (NSRunLoop *)mainRunLoop NS_AVAILABLE(10_5, 2_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSStream.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSStream (NSLegacySwiftCompatibility)
- (nullable id)propertyForKey:(NSString *)key;
- (BOOL)setProperty:(nullable id)property forKey:(NSString *)key;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSString.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSString (NSLegacySwiftCompatibility)
+ (const NSStringEncoding *)availableStringEncodings;
+ (NSStringEncoding)defaultCStringEncoding;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSTextCheckingResult.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSTextCheckingResult (NSLegacySwiftCompatibility)
@property (nullable, readonly, copy) NSArray<NSString *> *grammarDetails;
+ (NSTextCheckingResult *)grammarCheckingResultWithRange:(NSRange)range details:(NSArray<NSString *> *)details;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSThread.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSThread (NSLegacySwiftCompatibility)
+ (NSThread *)currentThread;
+ (NSArray<NSNumber *> *)callStackReturnAddresses;
+ (NSArray<NSString *> *)callStackSymbols;
+ (BOOL)isMainThread NS_AVAILABLE(10_5, 2_0);
+ (NSThread *)mainThread NS_AVAILABLE(10_5, 2_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSTimeZone.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSTimeZone (NSLegacySwiftCompatibility)
+ (NSTimeZone *)systemTimeZone;
+ (NSTimeZone *)defaultTimeZone;
+ (void)setDefaultTimeZone:(NSTimeZone *)timeZone;
+ (NSTimeZone *)localTimeZone;
+ (NSArray<NSString *> *)knownTimeZoneNames;
+ (void)setAbbreviationDictionary:(NSDictionary<NSString *, NSString *> *)dictionary NS_AVAILABLE(10_6, 4_0);
+ (NSDictionary<NSString *, NSString *> *)abbreviationDictionary;
+ (NSString *)timeZoneDataVersion NS_AVAILABLE(10_6, 4_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSURL.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSCharacterSet (NSLegacySwiftCompatibility)
+ (NSCharacterSet *)URLUserAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);
+ (NSCharacterSet *)URLPasswordAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);
+ (NSCharacterSet *)URLHostAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);
+ (NSCharacterSet *)URLPathAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);
+ (NSCharacterSet *)URLQueryAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);
+ (NSCharacterSet *)URLFragmentAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSURLCache.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSURLCache (NSLegacySwiftCompatibility)
+ (NSURLCache *)sharedURLCache;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSURLCredentialStorage.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSURLCredentialStorage (NSLegacySwiftCompatibility)
+ (NSURLCredentialStorage *)sharedCredentialStorage;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSURLRequest.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSURLRequest (NSLegacySwiftCompatibility)
+ (BOOL)supportsSecureCoding;
@end
NS_ASSUME_NONNULL_END

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <Foundation/NSURLSession.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSURLSession (NSLegacySwiftCompatibility)
+ (NSURLSession *)sharedSession;
@end
NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN
@interface NSURLSessionConfiguration (NSLegacySwiftCompatibility)
+ (NSURLSessionConfiguration *)defaultSessionConfiguration;
+ (NSURLSessionConfiguration *)ephemeralSessionConfiguration;
@end
NS_ASSUME_NONNULL_END
#endif

#import <Foundation/NSUserDefaults.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSUserDefaults (NSLegacySwiftCompatibility)
+ (NSUserDefaults *)standardUserDefaults;
@end
NS_ASSUME_NONNULL_END

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <Foundation/NSUserNotification.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSUserNotificationCenter (NSLegacySwiftCompatibility)
+ (NSUserNotificationCenter *)defaultUserNotificationCenter;
@end
NS_ASSUME_NONNULL_END
#endif

#endif // FOUNDATION_SWIFT_SDK_EPOCH_LESS_THAN(8)

#pragma mark Swift epochs before 7

#if FOUNDATION_SWIFT_SDK_EPOCH_LESS_THAN(7)

#import <Foundation/NSError.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSError (NSLegacySwiftCompatibility)
+ (void)setUserInfoValueProviderForDomain:(NSErrorDomain)errorDomain provider:(id _Nullable (^ _Nullable)(NSError *err, NSErrorUserInfoKey userInfoKey))provider NS_AVAILABLE(10_11, 9_0);
+ (id _Nullable (^ _Nullable)(NSError *err, NSErrorUserInfoKey userInfoKey))userInfoValueProviderForDomain:(NSErrorDomain)errorDomain NS_AVAILABLE(10_11, 9_0);
@end
NS_ASSUME_NONNULL_END

#endif // FOUNDATION_SWIFT_SDK_EPOCH_LESS_THAN(7)

#pragma mark Swift epochs before 6

#if FOUNDATION_SWIFT_SDK_EPOCH_LESS_THAN(6)

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <Foundation/NSExpression.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSExpression (NSLegacySwiftCompatibility)
@property (readonly, retain) id constantValue;

- (id)expressionValueWithObject:(nullable id)object context:(nullable NSMutableDictionary *)context;
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSPredicate.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSPredicate (NSLegacySwiftCompatibility)
+ (NSPredicate*)predicateWithBlock:(BOOL (^)(id evaluatedObject, NSDictionary<NSString *, id> * _Nullable bindings))block NS_AVAILABLE(10_6, 4_0);
@end
NS_ASSUME_NONNULL_END
#endif

#import <Foundation/NSURL.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSURL (NSLegacySwiftCompatibility)
@property (readonly, copy) NSString *absoluteString;
@property (nullable, readonly, copy) NSString *relativeString; // The relative portion of a URL.  If baseURL is nil, or if the receiver is itself absolute, this is the same as absoluteString
@property (nullable, readonly, copy) NSURL *baseURL; // may be nil.
@property (readonly, copy) NSURL *absoluteURL; // if the receiver is itself absolute, this will return self.

/* Any URL is composed of these two basic pieces.  The full URL would be the concatenation of [myURL scheme], ':', [myURL resourceSpecifier]
 */
@property (readonly, copy) NSString *scheme;
@property (readonly, copy) NSString *resourceSpecifier;

- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent isDirectory:(BOOL)isDirectory NS_AVAILABLE(10_7, 5_0);
@property (nullable, readonly, copy) NSURL *URLByDeletingLastPathComponent NS_AVAILABLE(10_6, 4_0);
- (NSURL *)URLByAppendingPathExtension:(NSString *)pathExtension NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSURL *URLByDeletingPathExtension NS_AVAILABLE(10_6, 4_0);
@end
NS_ASSUME_NONNULL_END

#import <Foundation/NSPathUtilities.h>

NS_ASSUME_NONNULL_BEGIN
@interface NSString (NSStringPathExtensionsLegacySwiftCompatibility)
- (NSUInteger)completePathIntoString:(NSString * _Nonnull * _Nullable)outputName caseSensitive:(BOOL)flag matchesIntoArray:(NSArray<NSString *> * _Nonnull * _Nullable)outputArray filterTypes:(nullable NSArray<NSString *> *)filterTypes;
@end
NS_ASSUME_NONNULL_END

#endif
