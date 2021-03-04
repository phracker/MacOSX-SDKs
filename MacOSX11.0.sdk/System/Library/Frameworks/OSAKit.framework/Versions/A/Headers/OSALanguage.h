/*	
    OSALanguage.h
    Copyright (C) 2005-2015 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>
#if TARGET_OS_OSX
#import <Carbon/Carbon.h>
#endif

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@class OSAScript;
@class OSALanguageInstance;
@class OSALanguagePrivate;

// Language Options
// ================

typedef NS_OPTIONS(NSUInteger, OSALanguageFeatures) 
{
  OSASupportsCompiling		= 0x0002,
  OSASupportsGetSource		= 0x0004,
  OSASupportsAECoercion		= 0x0008,
  OSASupportsAESending		= 0x0010,
  OSASupportsRecording		= 0x0020,
  OSASupportsConvenience	= 0x0040,
  OSASupportsDialects		= 0x0080,
  OSASupportsEventHandling  = 0x0100
};


// OSALanguage
// ===========

@interface OSALanguage : NSObject
{
@private
	OSALanguagePrivate *_private;
}

// Class Methods
+ (NSArray<OSALanguage *> *)availableLanguages;
+ (nullable OSALanguage *)languageForName:(NSString *)name;
+ (nullable OSALanguage *)languageForScriptDataDescriptor:(NSAppleEventDescriptor *)descriptor AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (nullable OSALanguage *)defaultLanguage;
+ (void)setDefaultLanguage:(OSALanguage *)defaultLanguage;

// Construction
- (instancetype)initWithComponent:(Component)component;

// Accessors
- (OSALanguageInstance *)sharedLanguageInstance AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
@property (readonly) ComponentInstance componentInstance;
@property (nullable, readonly, copy) NSString *name;
@property (nullable, readonly, copy) NSString *info;
@property (nullable, readonly, copy) NSString *version;
@property (readonly) OSType type;
@property (readonly) OSType subType;
@property (readonly) OSType manufacturer;
@property (readonly) OSALanguageFeatures features;
@property (getter=isThreadSafe, readonly) BOOL threadSafe AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
