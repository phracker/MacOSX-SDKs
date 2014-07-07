/*	NSScriptCommand.h
	Copyright 1997-2002, Apple, Inc. All rights reserved.
*/

// An NSScriptCommand is what an AppleScript AppleEvent turns into when it enters the Foundation Framework's scripting system.  A command can be executed.  Executing a command means invoking the selector on the receivers with the arguments.  The arguments may be NSScriptObjectSpecifiers, in which case they are evaluated and the resulting object[s] are used as the argument.
// The NSScriptCommand is in charge of making sure of the sanity of the receivers, the selector, and the arguments.  NSScriptClassDescription is consulted for this sanity checking.

#import <Foundation/NSObject.h>

@class NSDictionary;
@class NSMutableDictionary;
@class NSScriptObjectSpecifier;
@class NSScriptCommandDescription;
@class NSString;

// Error codes for general command execution problems (not typedef'd to allow subclasses to define their own values)
enum {
    NSNoScriptError = 0,
    NSReceiverEvaluationScriptError,  // Problem evaluating receiver specifier
    NSKeySpecifierEvaluationScriptError,  // Problem evaluating key specifier (for commands that have them)
    NSArgumentEvaluationScriptError,  // Problem evaluating an argument specifier
    NSReceiversCantHandleCommandScriptError,  // The receivers dont support the command
    NSRequiredArgumentsMissingScriptError,  // One or more required arguments are missing
    NSArgumentsWrongScriptError,  // One or more arguments are of wrong type or are otherwise invalid
    NSUnknownKeyScriptError,  // Other miscellaneous internal error
    NSInternalScriptError,  // Other miscellaneous internal error
    NSOperationNotSupportedForKeyScriptError,
    NSCannotCreateScriptCommandError
};

@interface NSScriptCommand : NSObject <NSCoding> {

    // All instance variables are private.
    @private
    NSScriptCommandDescription *_commandDescription;
    id _directParameterOrReceiversSpecifier;
    id _evaluatedReceivers;
    NSMutableDictionary *_arguments;
    NSMutableDictionary *_evaluatedArguments;
    int _isWellFormed;
    BOOL _hasEvaluatedReceivers;
    BOOL _hasEvaluatedArguments;
    int _errorNumber;
    NSString *_errorString;

}

- (id)initWithCommandDescription:(NSScriptCommandDescription *)commandDef;

- (NSScriptCommandDescription *)commandDescription;
    // The command description is immutable once the command is created.

- (void)setDirectParameter:(id)directParameter;
- (id)directParameter;
    // Accessors for the object that corresponds to the keyDirectObject parameter of the Apple event from which this command derives.

- (void)setReceiversSpecifier:(NSScriptObjectSpecifier *)receiversRef;
- (NSScriptObjectSpecifier *)receiversSpecifier;
    // Accessors for the specifier of the object(s) that will be given a chance to handle the command, if the direct parameter of the original event was an object specifier.  For backwards compatibility, -[NSScriptCommand setDirectParameter:] sends a [self setReceiversSpecifier:] message if the direct parameter is an object specifier.
    // Some types of commands may treat this somewhat specially.  For instance, the Set command backs off the innermost component of this specifier and uses the innermost component as the key to be set within that specifiers container specifier.

- (id)evaluatedReceivers;
    // If the direct parameter of the original event was an object specifier, and that object specifier can be (or already has been) evaluated successfully, return the specified object(s).  Return nil otherwise.

- (void)setArguments:(NSDictionary *)args;
- (NSDictionary *)arguments;
- (NSDictionary *)evaluatedArguments;
    // Arguments can be either normal objects or object specifiers.  If they are object specifiers they will be evaluated before being used.

- (BOOL)isWellFormed;
    // This checks the command against the command's description.  It makes sure there is a defined command and that the number of arguments and the types of non-specifier arguments is well formed with respect to the command description.

- (id)performDefaultImplementation;
    // Do not call this.  executeCommand calls this method if the receivers don't want to handle the command themselves.  Subclasses should override this.  It is only necessary to provide a subclass for a command if it is going to provide a default implementation by overriding this method.

- (id)executeCommand;
    // This actually evaluates all the object specifiers involved in the command and then validates that the receivers can actually handle the command and that the types of any arguments that were specifiers are valid.
    // If the command is valid, it then is executed and the result, if any, is returned.  If the receivers want to handle it themselves, this calls them.  If not, this calls performDefaultImplementation on self.  You shouldn't have to override this method.

- (void)setScriptErrorNumber:(int)num;
- (int)scriptErrorNumber;
- (void)setScriptErrorString:(NSString *)str;
- (NSString *)scriptErrorString;

@end
