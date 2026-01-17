/*
	NSExceptionHandler.h
	Exception Handling
	Copyright (c) 1998, Apple Computer, Inc.
	All rights reserved.
*/

#import "ExceptionHandlingDefines.h"
#import <Foundation/NSObject.h>

@class NSString, NSException;

EXCEPTIONHANDLING_EXPORT NSString *NSUncaughtSystemExceptionException;
EXCEPTIONHANDLING_EXPORT NSString *NSUncaughtRuntimeErrorException;
EXCEPTIONHANDLING_EXPORT NSString *NSStackTraceKey;	// key for stack trace in exception's userInfo
EXCEPTIONHANDLING_EXPORT void NSExceptionHandlerResume();	// resume when hung for debugger

enum {
    NSLogUncaughtExceptionMask			= 1 << 0,
    NSHandleUncaughtExceptionMask		= 1 << 1,
    NSLogUncaughtSystemExceptionMask		= 1 << 2,
    NSHandleUncaughtSystemExceptionMask		= 1 << 3,
    NSLogUncaughtRuntimeErrorMask		= 1 << 4,
    NSHandleUncaughtRuntimeErrorMask		= 1 << 5,
    NSLogTopLevelExceptionMask			= 1 << 6,
    NSHandleTopLevelExceptionMask		= 1 << 7,
    NSLogOtherExceptionMask			= 1 << 8,
    NSHandleOtherExceptionMask			= 1 << 9
};

#define NSLogAndHandleEveryExceptionMask (NSLogUncaughtExceptionMask|NSLogUncaughtSystemExceptionMask|NSLogUncaughtRuntimeErrorMask|NSHandleUncaughtExceptionMask|NSHandleUncaughtSystemExceptionMask|NSHandleUncaughtRuntimeErrorMask|NSLogTopLevelExceptionMask|NSHandleTopLevelExceptionMask|NSLogOtherExceptionMask|NSHandleOtherExceptionMask)

enum {
    NSHangOnUncaughtExceptionMask		= 1 << 0,
    NSHangOnUncaughtSystemExceptionMask		= 1 << 1,
    NSHangOnUncaughtRuntimeErrorMask		= 1 << 2,
    NSHangOnTopLevelExceptionMask		= 1 << 3,
    NSHangOnOtherExceptionMask			= 1 << 4
};

#define NSHangOnEveryExceptionMask (NSHangOnUncaughtExceptionMask|NSHangOnUncaughtSystemExceptionMask|NSHangOnUncaughtRuntimeErrorMask|NSHangOnTopLevelExceptionMask|NSHangOnOtherExceptionMask)

@interface NSExceptionHandler : NSObject
{
@private
    id _delegate;
    NSString *_exceptionLoggingConnectionName;
    struct {
        unsigned int exceptionHandlingMask:10;
        unsigned int reserved:10;
        unsigned int exceptionHangingMask:5;
        unsigned int reserved1:5;
        unsigned int drwh:1;
        unsigned int drwl:1;
    } _ehFlags;
    void *_reserved;
}

+ (NSExceptionHandler *)defaultExceptionHandler;
- (void)setExceptionHandlingMask:(unsigned int)aMask;
- (unsigned int)exceptionHandlingMask;
- (void)setExceptionHangingMask:(unsigned int)aMask;
- (unsigned int)exceptionHangingMask;
- (void)setDelegate:(id)anObject;
- (id)delegate;

@end

@interface NSObject(NSExceptionHandlerDelegate)

- (BOOL)exceptionHandler:(NSExceptionHandler *)sender shouldLogException:(NSException *)exception mask:(unsigned int)aMask;	// mask is NSLog<exception type>Mask, exception's userInfo has stack trace for key NSStackTraceKey
- (BOOL)exceptionHandler:(NSExceptionHandler *)sender shouldHandleException:(NSException *)exception mask:(unsigned int)aMask;	// mask is NSHandle<exception type>Mask, exception's userInfo has stack trace for key NSStackTraceKey

@end

