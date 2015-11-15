/*
	NSSpeechRecognizer.h
	Application Kit
	Copyright (c) 2003-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString;
@protocol NSSpeechRecognizerDelegate;


@interface NSSpeechRecognizer : NSObject {
@private // All instance variables are private
    id	_privateNSSpeechRecognizerVars;
}

- (nullable instancetype)init;

- (void)startListening;
- (void)stopListening;

@property (nullable, assign) id<NSSpeechRecognizerDelegate> delegate;

@property (nullable, copy) NSArray<NSString *> *commands;

@property (nullable, copy) NSString *displayedCommandsTitle;

@property BOOL listensInForegroundOnly;

@property BOOL blocksOtherRecognizers;

@end

@protocol NSSpeechRecognizerDelegate <NSObject>
@optional
- (void)speechRecognizer:(NSSpeechRecognizer *)sender didRecognizeCommand:(NSString *)command;

@end

NS_ASSUME_NONNULL_END

