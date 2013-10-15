/*	NSInvocation.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#include <stdbool.h>

@class NSMutableArray, NSMethodSignature;

enum _NSObjCValueType {
    NSObjCNoType = 0,
    NSObjCVoidType = 'v',
    NSObjCCharType = 'c',
    NSObjCShortType = 's',
    NSObjCLongType = 'l',
    NSObjCLonglongType = 'q',
    NSObjCFloatType = 'f',
    NSObjCDoubleType = 'd',
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
    NSObjCBoolType = 'B',
#endif
    NSObjCSelectorType = ':',
    NSObjCObjectType = '@',
    NSObjCStructType = '{',
    NSObjCPointerType = '^',
    NSObjCStringType = '*',
    NSObjCArrayType = '[',
    NSObjCUnionType = '(',
    NSObjCBitfield = 'b'
};

typedef struct {
    enum _NSObjCValueType type;
    union {
    	char charValue;
	short shortValue;
	long longValue;
	long long longlongValue;
	float floatValue;
	double doubleValue;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
	bool boolValue;
#endif
	SEL selectorValue;
	id objectValue;
	void *pointerValue;
	void *structLocation;
	char *cStringLocation;
    } value;
} NSObjCValue;

@interface NSInvocation : NSObject <NSCoding> {
    @private
    NSObjCValue	returnValue;
    void	*argumentFrame;
    NSMethodSignature	*signature;
    NSMutableArray	*container;
    unsigned 	retainedArgs:1;
    unsigned	isInvalid:1;
    unsigned	signatureValid:1;
    unsigned	retainedRet:1;
    unsigned	externalArgFrame:1;
    unsigned	unused:3;
    unsigned	refCount:24;
    void	*reserved;
}

+ (NSInvocation *)invocationWithMethodSignature:(NSMethodSignature *)sig;

- (SEL)selector;
- (void)setSelector:(SEL)selector;

- (id)target;
- (void)setTarget:(id)target;

- (void)retainArguments;
- (BOOL)argumentsRetained;

- (void)getReturnValue:(void *)retLoc;
- (void)setReturnValue:(void *)retLoc;

- (void)getArgument:(void *)argumentLocation atIndex:(int)index;
- (void)setArgument:(void *)argumentLocation atIndex:(int)index;

- (NSMethodSignature *)methodSignature;

- (void)invoke;
- (void)invokeWithTarget:(id)target;

@end

