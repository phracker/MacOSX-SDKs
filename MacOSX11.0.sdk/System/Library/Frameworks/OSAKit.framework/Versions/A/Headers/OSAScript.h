/*	
    OSAScript.h
    Copyright (C) 2005-2015 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>
#if TARGET_OS_OSX
#import <Carbon/Carbon.h>
#endif
#import <OSAKit/OSALanguage.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@class OSAScriptPrivate;

// Error Info Keys
// ===============

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

// The NSError codes are OSStatus values, so the domain is NSOSStatusErrorDomain, but there are also several OSAKit-specific user info keys.

extern NSString * const OSAScriptErrorMessageKey;			// NSString containing entire error message; may or may not be the same value as NSLocalizedDescriptionKey
extern NSString * const OSAScriptErrorBriefMessageKey;		// NSString containing just the failure; may or may not be the same value as NSLocalizedFailureReasonErrorKey
extern NSString * const OSAScriptErrorNumberKey;			// NSNumber containing an OSAError; may or may not be the same value as the NSError code
extern NSString * const OSAScriptErrorPartialResultKey;		// NSAppleEventDescriptor
extern NSString * const OSAScriptErrorOffendingObjectKey;	// NSAppleEventDescriptor
extern NSString * const OSAScriptErrorExpectedTypeKey;		// NSAppleEventDescriptor
extern NSString * const OSAScriptErrorAppAddressKey;		// NSAppleEventDescriptor containing the target application address
extern NSString * const OSAScriptErrorAppNameKey;			// NSString containing the target application name
extern NSString * const OSAScriptErrorRangeKey;				// NSValue containing an NSRange indicating the range of source characters where the error occurred

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 */

// Keys used by methods that return a bare error info NSDictionary. These have the same values as the corresonding keys above, so the old and new names may be used with error dictionaries and NSError user info dictionaries for compatibility with existing code.

extern NSString * const OSAScriptErrorMessage; 
extern NSString * const OSAScriptErrorNumber;
extern NSString * const OSAScriptErrorAppName; 
extern NSString * const OSAScriptErrorBriefMessage;
extern NSString * const OSAScriptErrorRange;

// Storage Types
// =============

extern NSString * const OSAStorageScriptType;
extern NSString * const OSAStorageScriptBundleType;
extern NSString * const OSAStorageApplicationType;
extern NSString * const OSAStorageApplicationBundleType;
extern NSString * const OSAStorageTextType;

// Storage Options
// ===============

typedef NS_OPTIONS(NSUInteger, OSAStorageOptions)
{
	OSANull						= 0x00000000,
	OSAPreventGetSource			= 0x00000001,	// May be used when initing with a compiled script, writing or getting compiled data
	OSACompileIntoContext		= 0x00000002,	// May be used when getting compiled data
	OSADontSetScriptLocation	= 0x01000000,	// May be used when initing with a URL or fromURL
	OSAStayOpenApplet			= 0x10000000,	// May be used when writing
	OSAShowStartupScreen		= 0x20000000,	// May be used when writing
};


// OSAScript
// =========

@interface OSAScript : NSObject<NSCopying>
{
@private
	OSAScriptPrivate *_private;
	
    void *_reserved1;
    void *_reserved2;
    void *_reserved3;
    void *_reserved4;
    void *_reserved5;
    void *_reserved6;
}

// Class methods

// Given a URL that locates a compiled script, script application, or script source, create and return an autoreleased script data descriptor with its contents. You may use the descriptor to create a script with -[OSAScript initWithScriptDataDescriptor:...]. This enables you to create a script with a specific OSALanguageInstance. You may use +[OSALanguage languageForScriptDataDescriptor:] to get the language for the script data, which may then be used to create or select an appropriate language instance for an OSAScript. Script source data may be compiled by -[OSAScript initWithScriptDataDescriptor:...], or you can coerce the descriptor to a string (using NSAppleEventDescriptor methods) and explicitly create an OSAScript with the source.
+ (nullable NSAppleEventDescriptor *)scriptDataDescriptorWithContentsOfURL:(NSURL *)url AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// Construction

// fromURL: arguments are optional and may be nil. URL arguments may be used to indicate the origin of scripts. In AppleScript, for example, this URL may be used for the value of "path to me", unless you use the OSADontSetScriptLocation storage option.
// languageInstance: parameters are optional and may be nil, in which case the shared instance of the current default language will be used.
- (instancetype)initWithSource:(NSString *)source;
- (instancetype)initWithSource:(NSString *)source language:(nullable OSALanguage *)language;
- (instancetype)initWithSource:(NSString *)source fromURL:(nullable NSURL *)url languageInstance:(nullable OSALanguageInstance *)instance usingStorageOptions:(OSAStorageOptions)storageOptions AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;
- (id)initWithContentsOfURL:(NSURL *)url language:(OSALanguage *)language error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url languageInstance:(nullable OSALanguageInstance *)instance usingStorageOptions:(OSAStorageOptions)storageOptions error:(NSError **)errorInfo AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (id)initWithCompiledData:(NSData *)data error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
- (nullable instancetype)initWithCompiledData:(NSData *)data fromURL:(nullable NSURL *)url usingStorageOptions:(OSAStorageOptions)storageOptions error:(NSError **)errorInfo AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (nullable instancetype)initWithScriptDataDescriptor:(NSAppleEventDescriptor *)data fromURL:(nullable NSURL *)url languageInstance:(nullable OSALanguageInstance *)instance usingStorageOptions:(OSAStorageOptions)storageOptions error:(NSError **)errorInfo AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// Accessors
@property (readonly, copy) NSString *source;
@property (nullable, readonly, copy) NSURL *url;
@property (strong) OSALanguage *language;
@property (strong) OSALanguageInstance *languageInstance AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
@property (getter=isCompiled, readonly) BOOL compiled;

// Operations
- (BOOL)compileAndReturnError:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;
- (nullable NSAppleEventDescriptor *)executeAndReturnError:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;
- (nullable NSAppleEventDescriptor *)executeAppleEvent:(NSAppleEventDescriptor *)event error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;
- (nullable NSAppleEventDescriptor *)executeAndReturnDisplayValue:(NSAttributedString * __nullable * __nonnull)displayValue error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;
- (nullable NSAppleEventDescriptor *)executeHandlerWithName:(NSString *)name arguments:(NSArray *)arguments error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;
@property (nullable, readonly, copy) NSAttributedString *richTextSource;
- (nullable NSAttributedString *)richTextFromDescriptor:(NSAppleEventDescriptor *)descriptor;
- (BOOL)writeToURL:(NSURL *)url ofType:(NSString *)type error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;
- (BOOL)writeToURL:(NSURL *)url ofType:(NSString *)type usingStorageOptions:(OSAStorageOptions)storageOptions error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;
- (nullable NSData *)compiledDataForType:(NSString *)type usingStorageOptions:(OSAStorageOptions)storageOptions error:(NSDictionary<NSString *, id> * __nullable * __nullable)errorInfo;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
