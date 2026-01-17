/*	
    AMWorkflow.h
    Copyright (C) 2005-2006 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>

@class AMAction;
@class AMWorkflowController;

@interface AMWorkflow : NSObject <NSCopying>
{
@private
	NSString *_uuid;
	NSURL *_fileURL;
	id _actions;
	id _variables;
	id _connectors;
	AMWorkflowController *_controller;
	id _options;
	id _input;
	id _scriptingRunData;
	id _owningApplication;
	NSDictionary *_savedPropertyList;
	NSArray *_loadingErrors;
	BOOL _isBeingEdited;
	BOOL _hasUnsavedChanges;
	BOOL _isLoading;
	BOOL _workflowIsShared;
	NSUInteger _updateCount;
	id _inputType;
	id _outputType;
	
	id _future;
	id _future2;
	id _future3;
	id _future4;
}

+ (id)runWorkflowAtURL:(NSURL *)fileURL withInput:(id)input error:(NSError **)error;

- (id)initWithContentsOfURL:(NSURL *)fileURL error:(NSError **)outError;

- (BOOL)writeToURL:(NSURL *)fileURL error:(NSError **)outError;

- (NSURL *)fileURL;
- (NSArray *)actions;

- (id)input;
- (void)setInput:(id)input;

- (BOOL)setValue:(id)value forVariableWithName:(NSString *)variableName;
- (id)valueForVariableWithName:(NSString *)variableName;

- (void)addAction:(AMAction *)action;
- (void)removeAction:(AMAction *)action;
- (void)insertAction:(AMAction *)action atIndex:(NSUInteger)index;
- (void)moveActionAtIndex:(NSUInteger)startIndex toIndex:(NSUInteger)endIndex;

@end
