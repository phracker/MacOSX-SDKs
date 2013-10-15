/*	
    AMAction.h
    Copyright (C) 2004-2007 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMAttributesForAnalyzer.h>

@class NSImage;

// AMAction
// =======

enum {
	AMLogLevelDebug = 0, 
	AMLogLevelInfo = 1, 
	AMLogLevelWarn = 2, 
	AMLogLevelError = 3
};

typedef NSUInteger AMLogLevel;

@interface AMAction : NSObject 
{
@private
    NSMutableDictionary *_definition;
    AM_UNUSED_FOR_ANALYZER NSDictionary *_argumentsWithOutlets;
    NSString *_currentInput;
    NSString *_error;
    NSString *_output;
    id _currentRunner;
    AMAction *_loopParent;
	NSString *_actionDescription;
	NSImage *_icon;
	NSUInteger _relevance;
	BOOL _showsRelevance;
	BOOL _stopped;
		
	id _future;
	id _future2;
	id _future3;
	id _future4;
}

// Construction
- (id)initWithDefinition:(NSDictionary *)dict fromArchive:(BOOL)archived;
- (id)initWithContentsOfURL:(NSURL *)fileURL error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// Accessors
#ifndef __LP64__
- (NSMutableDictionary *)definition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED;
#endif

- (NSString *)name AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)ignoresInput AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// The selected[Input, Output]Type must be a UTI in the action's Info.plist.  Set these to nil to restore default behavior.
- (NSString *)selectedInputType AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setSelectedInputType:(NSString *)inputType AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSString *)selectedOutputType AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setSelectedOutputType:(NSString *)outputType AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// Values from 0 to 1 are used to show or determinate progress
- (CGFloat)progressValue AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setProgressValue:(CGFloat)value AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// Operations
- (id)runWithInput:(id)input fromAction:(AMAction *)anAction error:(NSDictionary **)errorInfo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED;
#ifdef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER
- (id)runWithInput:(id)input error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
#endif

- (void)runAsynchronouslyWithInput:(id)input AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)willFinishRunning AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)didFinishRunningWithError:(NSDictionary *)errorInfo AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED;
#ifdef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER
- (void)finishRunningWithError:(NSError *)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
#endif

- (id)output AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setOutput:(id)theOutput AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)stop;
- (void)reset;
- (void)writeToDictionary:(NSMutableDictionary *)dictionary;

- (void)opened;
- (void)activated;
- (void)closed AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)updateParameters;
- (void)parametersUpdated;

#ifdef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER
- (void)logMessageWithLevel:(AMLogLevel)level format:(NSString *)format, ... NS_FORMAT_FUNCTION (2,3) AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
#endif

- (BOOL)isStopped;

@end
