/*	
    AMAction.h
    Copyright (C) 2004 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>


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
	unsigned _relevance;
	BOOL _showsRelevance;
	BOOL _stopped;
		
	id _future;
	id _future2;
	id _future3;
	id _future4;
}

// Construction
- (id)initWithDefinition:(NSDictionary *)dict fromArchive:(BOOL)archived;

// Accessors
- (NSMutableDictionary *)definition;

// Operations
- (id)runWithInput:(id)input fromAction:(AMAction *)anAction error:(NSDictionary **)errorInfo;
- (void)stop;
- (void)reset;
- (void)writeToDictionary:(NSMutableDictionary *)dictionary;

- (void)opened;
- (void)activated;
- (void)updateParameters;
- (void)parametersUpdated;

@end
