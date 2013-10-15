/*
	NSUserScriptTask.h
	Copyright (c) 2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSAppleEventDescriptor, NSArray, NSDictionary, NSError, NSFileHandle, NSURL, NSXPCConnection;


/*
    These classes are intended to execute user-supplied scripts, and will execute them outside of the application's sandbox, if any.  (They are *not* intended to execute scripts built into an application; for that, use NSTask, NSAppleScript, or AMWorkflow.)  If the application is sandboxed, then the script must be in the "application scripts" folder, which you can get using +[NSFileManager URLForDirectory:NSApplicationScriptsDirectory ...].  A sandboxed application may read from, but not write to, this folder.

    If you simply need to execute scripts without regard to input or output, use NSUserScriptTask, which can execute any of the specific types.  If you need specific control over the input to or output from the script, use one of the sub-classes, which have more detailed "execute" methods.
*/

/* NSUserScriptTask: An abstract "user script".
*/
NS_CLASS_AVAILABLE(10_8, NA)
@interface NSUserScriptTask : NSObject {
    @protected
    NSURL *_scriptURL;
    NSXPCConnection *_connection;
    BOOL _hasExeced;
    BOOL _hasTerminated;
    NSFileHandle *_stdin;
    NSFileHandle *_stdout;
    NSFileHandle *_stderr;
}

// Initialize given a URL for a script file.  The returned object will be of one of the specific sub-classes below, or nil if the file does not appear to match any of the known types.  (If used from a sub-class, the result will be of that class, or nil.)
- (id)initWithURL:(NSURL *)url error:(NSError **)error;
- (NSURL *)scriptURL;

// Execute the script with no input and ignoring any result.  This and the other "execute" methods below may be called at most once on any given instance.  If the script completed normally, the completion handler's "error" parameter will be nil.
typedef void (^NSUserScriptTaskCompletionHandler)(NSError *error);
- (void)executeWithCompletionHandler:(NSUserScriptTaskCompletionHandler)handler;

@end


/* NSUserUnixTask: a Unix executable file, typically a shell script.
*/
NS_CLASS_AVAILABLE(10_8, NA)
@interface NSUserUnixTask : NSUserScriptTask

// Standard I/O streams.  Setting them to nil (the default) will bind them to /dev/null.
@property (retain) NSFileHandle *standardInput;
@property (retain) NSFileHandle *standardOutput;
@property (retain) NSFileHandle *standardError;

// Execute the file with the given arguments.  "arguments" is an array of NSStrings.  The arguments do not undergo shell expansion, so you do not need to do special quoting, and shell variables are not resolved.
typedef void (^NSUserUnixTaskCompletionHandler)(NSError *error);
- (void)executeWithArguments:(NSArray *)arguments completionHandler:(NSUserUnixTaskCompletionHandler)handler;

@end


/* NSUserAppleScriptTask: an AppleScript script.
*/
NS_CLASS_AVAILABLE(10_8, NA)
@interface NSUserAppleScriptTask : NSUserScriptTask {
    @private
    BOOL _isParentDefaultTarget;
}

// Execute the AppleScript script by sending it the given Apple event.  Pass nil to execute the script's default "run" handler.
typedef void (^NSUserAppleScriptTaskCompletionHandler)(NSAppleEventDescriptor *result, NSError *error);
- (void)executeWithAppleEvent:(NSAppleEventDescriptor *)event completionHandler:(NSUserAppleScriptTaskCompletionHandler)handler;

@end


/* NSUserAutomatorTask: an Automator workflow.
*/
NS_CLASS_AVAILABLE(10_8, NA)
@interface NSUserAutomatorTask : NSUserScriptTask {
    @private
    NSDictionary *_variables;
}

// Workflow variables.
@property (copy) NSDictionary *variables;

// Execute the Automator workflow, passing it the given input.
typedef void (^NSUserAutomatorTaskCompletionHandler)(id result, NSError *error);
- (void)executeWithInput:(id <NSSecureCoding>)input completionHandler:(NSUserAutomatorTaskCompletionHandler)handler;

@end
