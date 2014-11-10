/*
	NSSpeechRecognizer.h
	Application Kit
	Copyright (c) 2003-2014, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>

@class NSArray, NSString;
@protocol NSSpeechRecognizerDelegate;


@interface NSSpeechRecognizer : NSObject {
@private // All instance variables are private
    id	_privateNSSpeechRecognizerVars;
}

- (instancetype)init;

- (void)startListening;
- (void)stopListening;

@property (assign) id<NSSpeechRecognizerDelegate> delegate;

@property (copy) NSArray *commands;

@property (copy) NSString *displayedCommandsTitle;

@property BOOL listensInForegroundOnly;

@property BOOL blocksOtherRecognizers;

@end

@protocol NSSpeechRecognizerDelegate <NSObject>
@optional
- (void)speechRecognizer:(NSSpeechRecognizer *)sender didRecognizeCommand:(id)command;

@end

