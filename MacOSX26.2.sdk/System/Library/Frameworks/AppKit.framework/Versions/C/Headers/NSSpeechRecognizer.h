/*
	NSSpeechRecognizer.h
	Application Kit
	Copyright (c) 2003-2024, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSString;
@protocol NSSpeechRecognizerDelegate;


@interface NSSpeechRecognizer : NSObject

- (nullable instancetype)init;

- (void)startListening;
- (void)stopListening;

@property (nullable, weak) id<NSSpeechRecognizerDelegate> delegate;

@property (nullable, copy) NSArray<NSString *> *commands;

@property (nullable, copy) NSString *displayedCommandsTitle;

@property BOOL listensInForegroundOnly;

@property BOOL blocksOtherRecognizers;

@end

@protocol NSSpeechRecognizerDelegate <NSObject>
@optional
- (void)speechRecognizer:(NSSpeechRecognizer *)sender didRecognizeCommand:(NSString *)command NS_SWIFT_UI_ACTOR;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)

