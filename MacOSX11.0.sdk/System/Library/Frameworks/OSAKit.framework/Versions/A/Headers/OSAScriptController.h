/*	
    OSAScriptController.h
    Copyright (C) 2005-2015 Apple Inc. All rights reserved.    
    
    Public header file.
*/


#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@class OSAScriptView;
@class OSAScript;
@class OSALanguage;
@class OSAScriptControllerPrivate;

typedef NS_ENUM(NSInteger, OSAScriptState)
{
	OSAScriptStopped,
	OSAScriptRunning,
	OSAScriptRecording
};

// OSAScriptController
// =====================

@interface OSAScriptController : NSController 
{
@public
	IBOutlet OSAScriptView *scriptView;
	IBOutlet NSTextView *resultView;
	
@private
	OSAScriptControllerPrivate *_private;
}

// Accessors
@property (nullable, strong) OSAScriptView *scriptView;
@property (nullable, strong) NSTextView *resultView;
@property (nullable, copy) OSAScript *script;
@property (nullable, strong) OSALanguage *language;
@property (readonly) OSAScriptState scriptState;
@property (getter=isCompiling, readonly) BOOL compiling;

// Actions
- (IBAction)compileScript:(nullable id)sender;
- (IBAction)recordScript:(nullable id)sender;
- (IBAction)runScript:(nullable id)sender;
- (IBAction)stopScript:(nullable id)sender;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
