/*	
    OSALanguage.h
    Copyright (C) 2005 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>
#include <Carbon/Carbon.h>

@class OSAScript;
@class OSALanguagePrivate;

// Language Options
// ================

typedef enum 
{
  OSASupportsCompiling		= 0x0002,
  OSASupportsGetSource		= 0x0004,
  OSASupportsAECoercion		= 0x0008,
  OSASupportsAESending		= 0x0010,
  OSASupportsRecording		= 0x0020,
  OSASupportsConvenience	= 0x0040,
  OSASupportsDialects		= 0x0080,
  OSASupportsEventHandling  = 0x0100
} OSALanguageFeatures;


// OSALanguage
// ===========

@interface OSALanguage : NSObject
{
@private
	OSALanguagePrivate *_private;
}

// Class Methods
+ (NSArray *)availableLanguages;
+ (OSALanguage *)languageForName:(NSString *)name;
+ (OSALanguage *)defaultLanguage;
+ (void)setDefaultLanguage:(OSALanguage *)defaultLanguage;

// Construction
- (id)initWithComponent:(Component)component;

// Accessors
- (ComponentInstance)componentInstance;
- (NSString *)name;
- (NSString *)info;
- (NSString *)version;
- (OSType)type;
- (OSType)subType;
- (OSType)manufacturer;
- (OSALanguageFeatures)features;

@end
