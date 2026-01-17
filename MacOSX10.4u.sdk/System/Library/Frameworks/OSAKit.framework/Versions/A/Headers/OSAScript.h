/*	
    OSAScript.h
    Copyright (C) 2005 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>
#import <OSAKit/OSALanguage.h>

@class OSAScriptPrivate;

// Error Info Keys
// ===============

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

typedef enum
{
	OSANull					= 0x00000000,
	OSAPreventGetSource		= 0x00000001,
	OSACompileIntoContext   = 0x00000002,
	OSAStayOpenApplet		= 0x10000000,
	OSAShowStartupScreen	= 0x20000000,
} OSAStorageOptions;


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

// Construction
- (id)initWithSource:(NSString *)source;
- (id)initWithSource:(NSString *)source language:(OSALanguage *)language;
- (id)initWithContentsOfURL:(NSURL *)url error:(NSDictionary **)errorInfo;
- (id)initWithContentsOfURL:(NSURL *)url language:(OSALanguage *)language error:(NSDictionary **)errorInfo;
- (id)initWithCompiledData:(NSData *)data error:(NSDictionary **)errorInfo;

// Accessors
- (NSString *)source;
- (NSURL *)url;
- (OSALanguage *)language;
- (void)setLanguage:(OSALanguage *)language;
- (BOOL)isCompiled;

// Operations
- (BOOL)compileAndReturnError:(NSDictionary **)errorInfo;
- (NSAppleEventDescriptor *)executeAndReturnError:(NSDictionary **)errorInfo;
- (NSAppleEventDescriptor *)executeAppleEvent:(NSAppleEventDescriptor *)event error:(NSDictionary **)errorInfo;
- (NSAppleEventDescriptor *)executeAndReturnDisplayValue:(NSAttributedString **)displayValue error:(NSDictionary **)errorInfo;
- (NSAppleEventDescriptor *)executeHandlerWithName:(NSString *)name arguments:(NSArray *)arguments error:(NSDictionary **)errorInfo;
- (NSAttributedString *)richTextSource;
- (NSAttributedString *)richTextFromDescriptor:(NSAppleEventDescriptor *)descriptor;
- (BOOL)writeToURL:(NSURL *)url ofType:(NSString *)type error:(NSDictionary **)errorInfo;
- (BOOL)writeToURL:(NSURL *)url ofType:(NSString *)type usingStorageOptions:(OSAStorageOptions)storageOptions error:(NSDictionary **)errorInfo;
- (NSData *)compiledDataForType:(NSString *)type usingStorageOptions:(OSAStorageOptions)storageOptions error:(NSDictionary **)errorInfo;

@end
