/*	NSMethodSignature.h
	Copyright (c) 1994-2003, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@interface NSMethodSignature : NSObject {
    @private
    const char	*_types;
    int		_nargs;
    unsigned	_sizeofParams;
    unsigned	_returnValueLength;
    void	*_parmInfoP;
    int		*_fixup;
    void	*_reserved;
}

- (unsigned)numberOfArguments;
- (const char *)getArgumentTypeAtIndex:(unsigned)index;

- (unsigned)frameLength;

- (BOOL)isOneway;

- (const char *)methodReturnType;
- (unsigned)methodReturnLength;

@end
