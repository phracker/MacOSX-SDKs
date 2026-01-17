/*	NSDistantObject.h
	Copyright (c) 1989-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSProxy.h>

@class Protocol, NSConnection, NSCoder;

@interface NSDistantObject : NSProxy <NSCoding> {
    @private
    id         _knownSelectors;
    NSUInteger _wireCount;
    NSUInteger _refCount;
    id         _proto;
    uint16_t   ___2;
    uint8_t    ___1;
    uint8_t    _wireType;
    id         _remoteClass;
}

// Do not attempt to subclass NSDistantObject -- it is futile
// Do not use these next two methods
+ (NSDistantObject *)proxyWithTarget:(id)target connection:(NSConnection *)connection;
- (id)initWithTarget:(id)target connection:(NSConnection *)connection;

+ (NSDistantObject *)proxyWithLocal:(id)target connection:(NSConnection *)connection;
- (id)initWithLocal:(id)target connection:(NSConnection *)connection;

- (void)setProtocolForProxy:(Protocol *)proto;

- (NSConnection *)connectionForProxy;

@end

