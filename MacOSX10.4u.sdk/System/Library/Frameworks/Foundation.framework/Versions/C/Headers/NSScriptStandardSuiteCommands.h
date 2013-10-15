/*
	NSScriptStandardSuiteCommands.h
	Copyright (c) 1997-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSScriptCommand.h>

@class NSDictionary;
@class NSScriptObjectSpecifier;
@class NSScriptClassDescription;


typedef enum {
    NSSaveOptionsYes = 0,
    NSSaveOptionsNo,
    NSSaveOptionsAsk
} NSSaveOptions;


@interface NSCloneCommand : NSScriptCommand {
    @private
    NSScriptObjectSpecifier *_keySpecifier;
}

- (void)setReceiversSpecifier:(NSScriptObjectSpecifier *)receiversRef;
    // Splits off the inner-most child specifier.  The rest is the receiver specifier while the child is the key specifier.

- (NSScriptObjectSpecifier *)keySpecifier;

@end


@interface NSCloseCommand : NSScriptCommand {}

- (NSSaveOptions)saveOptions;
    // This converts the "SaveOptions" argument into a constant that can be easily tested.  You should use this instead of accessing the SaveOptions argument directly.

@end


@interface NSCountCommand : NSScriptCommand {}

@end


@interface NSCreateCommand : NSScriptCommand {
    @private
    id _privateVars;
}

- (NSScriptClassDescription *)createClassDescription;
    // Returns the class description for the class that is to be created (using the "ObjectClass" argument to figure it out).

- (NSDictionary *)resolvedKeyDictionary;
    // The actual "KeyDictionary" argument has appleEventCodes as keys.  This method returns a version that has those codes resolved to actual key names (using the -createClassDescription to resolve the keys).

@end


@interface NSDeleteCommand : NSScriptCommand {
    @private
    NSScriptObjectSpecifier *_keySpecifier;
}

- (void)setReceiversSpecifier:(NSScriptObjectSpecifier *)receiversRef;
    // Splits off the inner-most child specifier.  The rest is the receiver specifier while the child is the key specifier.

- (NSScriptObjectSpecifier *)keySpecifier;

@end


@interface NSExistsCommand : NSScriptCommand {}

@end


@interface NSGetCommand : NSScriptCommand {}

@end


@interface NSMoveCommand : NSScriptCommand {
    @private
    NSScriptObjectSpecifier *_keySpecifier;
}

- (void)setReceiversSpecifier:(NSScriptObjectSpecifier *)receiversRef;
    // Splits off the inner-most child specifier.  The rest is the receiver specifier while the child is the key specifier.

- (NSScriptObjectSpecifier *)keySpecifier;

@end


@interface NSQuitCommand : NSScriptCommand {}

- (NSSaveOptions)saveOptions;
    // This converts the "SaveOptions" argument into a constant that can be easily tested.  You should use this instead of accessing the SaveOptions argument directly.

@end


@interface NSSetCommand : NSScriptCommand {
    @private
    NSScriptObjectSpecifier *_keySpecifier;
}

- (void)setReceiversSpecifier:(NSScriptObjectSpecifier *)receiversRef;
    // Splits off the inner-most child specifier.  The rest is the receiver specifier while the child is the key specifier.

- (NSScriptObjectSpecifier *)keySpecifier;

@end
