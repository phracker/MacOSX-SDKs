/*	
    OSALanguageInstance.h
    Copyright (C) 2009 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

@class OSALanguage;
@class OSALanguageInstancePrivate;

// OSALanguageInstance
// ===================

@interface OSALanguageInstance : NSObject
{
@private
	OSALanguageInstancePrivate *_private;
}

// Construction
+ (id)languageInstanceWithLanguage:(OSALanguage *)language;
- (id)initWithLanguage:(OSALanguage *)language;

// Accessors
- (OSALanguage *)language;
- (ComponentInstance)componentInstance; // If this is the shared instance for the language, this is the same as the language's component instance.

@end

#endif
