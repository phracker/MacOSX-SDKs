/*	
    OSALanguageInstance.h
    Copyright (C) 2009-2015 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

@class OSALanguage;
@class OSALanguageInstancePrivate;

NS_ASSUME_NONNULL_BEGIN

// OSALanguageInstance
// ===================

@interface OSALanguageInstance : NSObject
{
@private
	OSALanguageInstancePrivate *_private;
}

// Construction
+ (instancetype)languageInstanceWithLanguage:(OSALanguage *)language;
- (instancetype)initWithLanguage:(OSALanguage *)language;

// Accessors
@property (readonly, strong) OSALanguage *language;
@property (readonly) ComponentInstance componentInstance; // If this is the shared instance for the language, this is the same as the language's component instance.
@property (nullable, strong) NSAppleEventDescriptor *defaultTarget NS_AVAILABLE_MAC(10_10); // The default target application for Apple event sending. It also establishes the default target from which terminologies come. It is effectively like having an AppleScript "tell" statement around the entire program. When nil, the default target is the current application.

// Operations
- (nullable NSAttributedString *)richTextFromDescriptor:(NSAppleEventDescriptor *)descriptor NS_AVAILABLE_MAC(10_10); // Get source text for a descriptor using the language instance for context.

@end

NS_ASSUME_NONNULL_END

#endif
