/*	NSException.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <stdarg.h>
#import <setjmp.h>

@class NSString, NSDictionary;

/***************	Generic Exception names		***************/

FOUNDATION_EXPORT NSString * const NSGenericException;
FOUNDATION_EXPORT NSString * const NSRangeException;
FOUNDATION_EXPORT NSString * const NSInvalidArgumentException;
FOUNDATION_EXPORT NSString * const NSInternalInconsistencyException;

FOUNDATION_EXPORT NSString * const NSMallocException;

FOUNDATION_EXPORT NSString * const NSObjectInaccessibleException;
FOUNDATION_EXPORT NSString * const NSObjectNotAvailableException;
FOUNDATION_EXPORT NSString * const NSDestinationInvalidException;
    
FOUNDATION_EXPORT NSString * const NSPortTimeoutException;
FOUNDATION_EXPORT NSString * const NSInvalidSendPortException;
FOUNDATION_EXPORT NSString * const NSInvalidReceivePortException;
FOUNDATION_EXPORT NSString * const NSPortSendException;
FOUNDATION_EXPORT NSString * const NSPortReceiveException;

FOUNDATION_EXPORT NSString * const NSOldStyleException;

/***************	Exception object	***************/

@interface NSException : NSObject <NSCopying, NSCoding> {
    @private
    NSString		*name;
    NSString		*reason;
    NSDictionary	*userInfo;
    void		*reserved;
}

+ (NSException *)exceptionWithName:(NSString *)name reason:(NSString *)reason userInfo:(NSDictionary *)userInfo;
- (id)initWithName:(NSString *)aName reason:(NSString *)aReason userInfo:(NSDictionary *)aUserInfo;

- (NSString *)name;
- (NSString *)reason;
- (NSDictionary *)userInfo;

- (void)raise;

@end

@interface NSException (NSExceptionRaisingConveniences)

+ (void)raise:(NSString *)name format:(NSString *)format, ...;
+ (void)raise:(NSString *)name format:(NSString *)format arguments:(va_list)argList;

@end


typedef struct _NSHandler NSHandler;	/* Private */

typedef struct _NSHandler2 {	/* Private */
    jmp_buf _state;
    NSException *_exception;
    void *_others;
    void *_thread;
    void *_reserved1;
} NSHandler2;

/* private support routines.  Do not call directly. */
FOUNDATION_EXPORT void _NSAddHandler2(NSHandler2 *handler);
FOUNDATION_EXPORT void _NSRemoveHandler2(NSHandler2 *handler);
FOUNDATION_EXPORT NSException *_NSExceptionObjectFromHandler2(NSHandler2 *handler);

#if !defined(_NSSETJMP)
#if defined(__svr4__) || defined(__WIN32__)
#define _NSSETJMP(B, S)	setjmp((B))
#elif defined(__hpux__)
#define _NSSETJMP(B, S)	sigsetjmp((B), (S))
#else
#define _NSSETJMP(B, S)	_setjmp((B))
#endif
#endif

#define NS_DURING { NSHandler2 _localHandler;			\
		    _NSAddHandler2(&_localHandler);		\
		    if (!_NSSETJMP(_localHandler._state, 0)) {

#define NS_HANDLER _NSRemoveHandler2(&_localHandler); } else { \
		    NSException	*localException = _NSExceptionObjectFromHandler2(&_localHandler);

#define NS_ENDHANDLER localException = nil; /* to avoid compiler warning */}}

#define NS_VALUERETURN(val,type)  do { type temp = (val);	\
			_NSRemoveHandler2(&_localHandler);	\
			return(temp); } while (0)

#define NS_VOIDRETURN	do { _NSRemoveHandler2(&_localHandler);	\
			return; } while (0)

typedef void NSUncaughtExceptionHandler(NSException *exception);

FOUNDATION_EXPORT NSUncaughtExceptionHandler *NSGetUncaughtExceptionHandler(void);
FOUNDATION_EXPORT void NSSetUncaughtExceptionHandler(NSUncaughtExceptionHandler *);

@class NSAssertionHandler;

/* Implementation of asserts (ignore) */
#if !defined(NS_BLOCK_ASSERTIONS)
#if !defined(_NSAssertBody)
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	if (!(condition)) {				\
	    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd object:self file:[NSString stringWithCString:__FILE__] \
	    	lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
    } while(0)
#endif
#if !defined(_NSCAssertBody)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	if (!(condition)) {				\
	    [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithCString:__PRETTY_FUNCTION__] file:[NSString stringWithCString:__FILE__] \
	    	lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
    } while(0)
#endif
#else
#if !defined(_NSAssertBody)
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)
#endif
#if !defined(_NSCAssertBody)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)
#endif
#endif


/*
 * Asserts to use in Objective-C method bodies
 */
 
#define NSAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))

#define NSAssert4(condition, desc, arg1, arg2, arg3, arg4)	\
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), 0)

#define NSAssert3(condition, desc, arg1, arg2, arg3)	\
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), 0, 0)

#define NSAssert2(condition, desc, arg1, arg2)		\
    _NSAssertBody((condition), (desc), (arg1), (arg2), 0, 0, 0)

#define NSAssert1(condition, desc, arg1)		\
    _NSAssertBody((condition), (desc), (arg1), 0, 0, 0, 0)

#define NSAssert(condition, desc)			\
    _NSAssertBody((condition), (desc), 0, 0, 0, 0, 0)


#define NSParameterAssert(condition)			\
    _NSAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0)
 
#define NSCAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))

#define NSCAssert4(condition, desc, arg1, arg2, arg3, arg4)	\
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), 0)

#define NSCAssert3(condition, desc, arg1, arg2, arg3)	\
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), 0, 0)

#define NSCAssert2(condition, desc, arg1, arg2)	\
    _NSCAssertBody((condition), (desc), (arg1), (arg2), 0, 0, 0)

#define NSCAssert1(condition, desc, arg1)		\
    _NSCAssertBody((condition), (desc), (arg1), 0, 0, 0, 0)

#define NSCAssert(condition, desc)			\
    _NSCAssertBody((condition), (desc), 0, 0, 0, 0, 0)


#define NSCParameterAssert(condition)			\
    _NSCAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0)


@interface NSAssertionHandler : NSObject {
    @private
    void *_reserved;
}

+ (NSAssertionHandler *)currentHandler;

- (void)handleFailureInMethod:(SEL)selector object:(id)object file:(NSString *)fileName lineNumber:(int)line description:(NSString *)format,...;

- (void)handleFailureInFunction:(NSString *)functionName file:(NSString *)fileName lineNumber:(int)line description:(NSString *)format,...;

@end
