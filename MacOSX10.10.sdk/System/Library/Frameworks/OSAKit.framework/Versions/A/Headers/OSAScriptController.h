/*	
    OSAScriptController.h
    Copyright (C) 2005-2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/


#import <Cocoa/Cocoa.h>

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
@property (strong) OSAScriptView *scriptView;
@property (strong) NSTextView *resultView;
@property (copy) OSAScript *script;
@property (strong) OSALanguage *language;
@property (readonly) OSAScriptState scriptState;
@property (getter=isCompiling, readonly) BOOL compiling;

// Actions
- (IBAction)compileScript:(id)sender;
- (IBAction)recordScript:(id)sender;
- (IBAction)runScript:(id)sender;
- (IBAction)stopScript:(id)sender;

@end
