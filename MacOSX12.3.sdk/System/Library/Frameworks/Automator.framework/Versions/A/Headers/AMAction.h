/*	
    AMAction.h
    Copyright (C) 2004-2007, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMAttributesForAnalyzer.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(ios)

@class NSImage;

typedef NS_ENUM(NSUInteger, AMLogLevel)
{
	AMLogLevelDebug = 0,
	AMLogLevelInfo = 1,
	AMLogLevelWarn = 2,
	AMLogLevelError = 3
};

NS_CLASS_AVAILABLE_MAC(10_4)
@interface AMAction : NSObject
{
	@private
	NSMutableDictionary *_definition;
	AM_UNUSED_FOR_ANALYZER NSDictionary *_argumentsWithOutlets;
	AM_UNUSED_FOR_ANALYZER NSString *_currentInput;
	NSString *_error;
	NSString *_output;
	__weak id _currentRunner;
	__weak AMAction *_loopParent;
	AM_UNUSED_FOR_ANALYZER NSString *_actionDescription;
	NSImage *_icon;
	NSUInteger _relevance;
	AM_UNUSED_FOR_ANALYZER BOOL _showsRelevance;
	BOOL _stopped;

	id _future;
	__weak id _future2;
	__weak id _future3;
	id _future4;
}

// Construction
- (nullable instancetype)initWithDefinition:(NSDictionary<NSString *, id> *__nullable)dict fromArchive:(BOOL)archived;
- (nullable instancetype)initWithContentsOfURL:(NSURL *)fileURL error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@property (readonly, strong, nonatomic) NSString *name AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
@property (readonly, nonatomic) BOOL ignoresInput AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

// The selected[Input, Output]Type must be a UTI in the action's Info.plist.  Set these to nil to restore default behavior.
@property (nullable, strong, nonatomic) NSString *selectedInputType AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
@property (nullable, strong, nonatomic) NSString *selectedOutputType AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// Values from 0 to 1 are used to show or determinate progress
@property (atomic) CGFloat progressValue AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// Operations
- (nullable id)runWithInput:(nullable id)input fromAction:(nullable AMAction *)anAction error:(NSDictionary<NSString *, id> *__nullable *__nullable)errorInfo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED;
- (nullable id)runWithInput:(nullable id)input error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

- (void)runAsynchronouslyWithInput:(nullable id)input AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)willFinishRunning AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)didFinishRunningWithError:(nullable NSDictionary<NSString *, id> *)errorInfo AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED;
- (void)finishRunningWithError:(nullable NSError *)error AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

@property (nullable, strong, nonatomic) id output AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)stop;
- (void)reset;
- (void)writeToDictionary:(NSMutableDictionary<NSString *, id> *)dictionary;

- (void)opened;
- (void)activated;
- (void)closed AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (void)updateParameters;
- (void)parametersUpdated;

- (void)logMessageWithLevel:(AMLogLevel)level format:(NSString *)format, ... NS_FORMAT_FUNCTION(2, 3) AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

@property (readonly, nonatomic, getter=isStopped) BOOL stopped;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
