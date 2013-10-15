/*
	NSSpeechRecognizer.h
	Application Kit
	Copyright (c) 2003-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>

@class NSArray, NSString;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@interface NSSpeechRecognizer : NSObject {
@private // All instance variables are private
    id	_privateNSSpeechRecognizerVars;
}

- (id)init;

- (void)startListening;
- (void)stopListening;

- (id)delegate;
- (void)setDelegate:(id)anObject;

- (NSArray *)commands;
- (void)setCommands:(NSArray *)commands;

- (NSString *)displayedCommandsTitle;
- (void)setDisplayedCommandsTitle:(NSString *)title;

- (BOOL)listensInForegroundOnly;
- (void)setListensInForegroundOnly:(BOOL)flag;

- (BOOL)blocksOtherRecognizers;
- (void)setBlocksOtherRecognizers:(BOOL)flag;

@end

@interface NSObject (NSSpeechRecognizerDelegate)

- (void)speechRecognizer:(NSSpeechRecognizer *)sender didRecognizeCommand:(id)command;

@end

#endif
