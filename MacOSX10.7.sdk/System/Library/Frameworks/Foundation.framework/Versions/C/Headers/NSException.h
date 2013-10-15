/*	NSException.h
	Copyright (c) 1994-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <stdarg.h>
#import <setjmp.h>

@class NSString, NSDictionary, NSArray;

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

#if __OBJC2__
__attribute__((__objc_exception__))
#endif
@interface NSException : NSObject <NSCopying, NSCoding> {
    @private
    NSString		*name;
    NSString		*reason;
    NSDictionary	*userInfo;
    id			reserved;
}

+ (NSException *)exceptionWithName:(NSString *)name reason:(NSString *)reason userInfo:(NSDictionary *)userInfo;
- (id)initWithName:(NSString *)aName reason:(NSString *)aReason userInfo:(NSDictionary *)aUserInfo;

- (NSString *)name;
- (NSString *)reason;
- (NSDictionary *)userInfo;

- (NSArray *)callStackReturnAddresses NS_AVAILABLE(10_5, 2_0);
- (NSArray *)callStackSymbols NS_AVAILABLE(10_6, 4_0);

- (void)raise;

@end

@interface NSException (NSExceptionRaisingConveniences)

+ (void)raise:(NSString *)name format:(NSString *)format, ... NS_FORMAT_FUNCTION(2,3);
+ (void)raise:(NSString *)name format:(NSString *)format arguments:(va_list)argList NS_FORMAT_FUNCTION(2,0);

@end


#define NS_DURING		@try {
#define NS_HANDLER		} @catch (NSException *localException) {
#define NS_ENDHANDLER		}
#define NS_VALUERETURN(v,t)	return (v)
#define NS_VOIDRETURN		return


typedef void NSUncaughtExceptionHandler(NSException *exception);

FOUNDATION_EXPORT NSUncaughtExceptionHandler *NSGetUncaughtExceptionHandler(void);
FOUNDATION_EXPORT void NSSetUncaughtExceptionHandler(NSUncaughtExceptionHandler *);


@class NSAssertionHandler;

#if defined(__STDC_VERSION__) && (199901L <= __STDC_VERSION__) && (defined(__GNUC__) || 0)

#if !defined(NS_BLOCK_ASSERTIONS)

#if !defined(_NSAssertBody)
#define NSAssert(condition, desc, ...) \
    do {			\
	if (!(condition)) {	\
	    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd \
		object:self file:[NSString stringWithUTF8String:__FILE__] \
	    	lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
	}			\
    } while(0)
#endif

#if !defined(_NSCAssertBody)
#define NSCAssert(condition, desc, ...) \
    do {			\
	if (!(condition)) {	\
	    [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
		file:[NSString stringWithUTF8String:__FILE__] \
	    	lineNumber:__LINE__ description:(desc), ##__VA_ARGS__]; \
	}			\
    } while(0)
#endif

#else // NS_BLOCK_ASSERTIONS defined

#if !defined(_NSAssertBody)
#define NSAssert(condition, desc, ...) do {} while (0)
#endif

#if !defined(_NSCAssertBody)
#define NSCAssert(condition, desc, ...) do {} while (0)
#endif

#endif

#if !defined(_NSAssertBody)
#define NSAssert1(condition, desc, arg1) NSAssert((condition), (desc), (arg1))
#define NSAssert2(condition, desc, arg1, arg2) NSAssert((condition), (desc), (arg1), (arg2))
#define NSAssert3(condition, desc, arg1, arg2, arg3) NSAssert((condition), (desc), (arg1), (arg2), (arg3))
#define NSAssert4(condition, desc, arg1, arg2, arg3, arg4) NSAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4))
#define NSAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5) NSAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))
#define NSParameterAssert(condition) NSAssert((condition), @"Invalid parameter not satisfying: %s", #condition)
#endif

#if !defined(_NSCAssertBody)
#define NSCAssert1(condition, desc, arg1) NSCAssert((condition), (desc), (arg1))
#define NSCAssert2(condition, desc, arg1, arg2) NSCAssert((condition), (desc), (arg1), (arg2))
#define NSCAssert3(condition, desc, arg1, arg2, arg3) NSCAssert((condition), (desc), (arg1), (arg2), (arg3))
#define NSCAssert4(condition, desc, arg1, arg2, arg3, arg4) NSCAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4))
#define NSCAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5) NSCAssert((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))
#define NSCParameterAssert(condition) NSCAssert((condition), @"Invalid parameter not satisfying: %s", #condition)
#endif

#endif


/* Non-vararg implementation of asserts (ignore) */
#if !defined(NS_BLOCK_ASSERTIONS)
#if !defined(_NSAssertBody)
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	if (!(condition)) {				\
	    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd object:self file:[NSString stringWithUTF8String:__FILE__] \
	    	lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
    } while(0)
#endif
#if !defined(_NSCAssertBody)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	if (!(condition)) {				\
	    [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] file:[NSString stringWithUTF8String:__FILE__] \
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
 
#if !defined(NSAssert)
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
#endif

#if !defined(NSParameterAssert)
#define NSParameterAssert(condition)			\
    _NSAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0)
#endif


#if !defined(NSCAssert)
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
#endif

#if !defined(NSCParameterAssert)
#define NSCParameterAssert(condition)			\
    _NSCAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0)
#endif


FOUNDATION_EXPORT NSString * const NSAssertionHandlerKey NS_AVAILABLE(10_6, 4_0);

@interface NSAssertionHandler : NSObject {
    @private
    void *_reserved;
}

+ (NSAssertionHandler *)currentHandler;

- (void)handleFailureInMethod:(SEL)selector object:(id)object file:(NSString *)fileName lineNumber:(NSInteger)line description:(NSString *)format,... NS_FORMAT_FUNCTION(5,6);

- (void)handleFailureInFunction:(NSString *)functionName file:(NSString *)fileName lineNumber:(NSInteger)line description:(NSString *)format,... NS_FORMAT_FUNCTION(4,5);

@end

