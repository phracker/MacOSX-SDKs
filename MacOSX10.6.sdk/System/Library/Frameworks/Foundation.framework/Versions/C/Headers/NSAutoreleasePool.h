/*	NSAutoreleasePool.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@interface NSAutoreleasePool : NSObject {
@private
    void	*_token;
    void	*_reserved3;
    void	*_reserved2;
    void	*_reserved;
}

+ (void)addObject:(id)anObject;

- (void)addObject:(id)anObject;

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (void)drain;
#endif

@end

