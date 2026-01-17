/*	
    OSAScriptController.h
    Copyright (C) 2005 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/


#import <Cocoa/Cocoa.h>

@class OSAScriptView;
@class OSAScript;
@class OSALanguage;
@class OSAScriptControllerPrivate;

typedef enum
{
	OSAScriptStopped,
	OSAScriptRunning,
	OSAScriptRecording
} OSAScriptState;

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
- (OSAScriptView *)scriptView;
- (void)setScriptView:(OSAScriptView *)newScriptView;
- (NSTextView *)resultView;
- (void)setResultView:(NSTextView *)newResultView;
- (OSAScript *)script;
- (void)setScript:(OSAScript *)newScript;
- (OSALanguage *)language;
- (void)setLanguage:(OSALanguage *)newLanguage;
- (OSAScriptState)scriptState;
- (BOOL)isCompiling;

// Actions
- (IBAction)compileScript:(id)sender;
- (IBAction)recordScript:(id)sender;
- (IBAction)runScript:(id)sender;
- (IBAction)stopScript:(id)sender;

@end
