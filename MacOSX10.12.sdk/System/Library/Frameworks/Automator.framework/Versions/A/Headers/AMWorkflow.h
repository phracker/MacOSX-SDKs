/*	
    AMWorkflow.h
    Copyright (C) 2005-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMAttributesForAnalyzer.h>

NS_ASSUME_NONNULL_BEGIN

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
	AM_UNUSED_FOR_ANALYZER BOOL _isLoading;
	AM_UNUSED_FOR_ANALYZER BOOL _workflowIsShared;
	NSUInteger _updateCount;
	id _inputType;
	id _outputType;
	
	id _future;
	AM_UNUSED_FOR_ANALYZER id _future2;
	AM_UNUSED_FOR_ANALYZER id _future3;
	AM_UNUSED_FOR_ANALYZER id _future4;
}

+ (nullable id)runWorkflowAtURL:(NSURL *)fileURL withInput:(nullable id)input error:(NSError **)error;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)fileURL error:(NSError **)outError;

- (BOOL)writeToURL:(NSURL *)fileURL error:(NSError **)outError;

- (BOOL)setValue:(nullable id)value forVariableWithName:(NSString *)variableName;
- (id)valueForVariableWithName:(NSString *)variableName;

- (void)addAction:(AMAction *)action;
- (void)removeAction:(AMAction *)action;
- (void)insertAction:(AMAction *)action atIndex:(NSUInteger)index;
- (void)moveActionAtIndex:(NSUInteger)startIndex toIndex:(NSUInteger)endIndex;

@property (nullable, readonly, copy) NSURL *fileURL;
@property (readonly, retain) NSArray<__kindof AMAction *> *actions;
@property (nullable, readwrite, retain) id input;
@property (nullable, readonly, retain) id output AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

NS_ASSUME_NONNULL_END
