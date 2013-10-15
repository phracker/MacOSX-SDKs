/*	
    AMAction.h
    Copyright (C) 2004-2007 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>

@class NSImage;

// AMAction
// =======

@interface AMAction : NSObject 
{
@private
    NSMutableDictionary *_definition;
    NSDictionary *_argumentsWithOutlets;
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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (id)initWithContentsOfURL:(NSURL *)fileURL error:(NSError **)outError;
#endif

// Accessors
#ifndef __LP64__
- (NSMutableDictionary *)definition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (NSString *)name;
- (BOOL)ignoresInput;
#endif

// Operations
- (id)runWithInput:(id)input fromAction:(AMAction *)anAction error:(NSDictionary **)errorInfo;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)willFinishRunning;
- (id)output;

- (void)runAsynchronouslyWithInput:(id)input;
- (void)didFinishRunningWithError:(NSDictionary *)errorInfo;
#endif

- (void)stop;
- (void)reset;
- (void)writeToDictionary:(NSMutableDictionary *)dictionary;

- (void)opened;
- (void)activated;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)closed;
#endif

- (void)updateParameters;
- (void)parametersUpdated;

@end
