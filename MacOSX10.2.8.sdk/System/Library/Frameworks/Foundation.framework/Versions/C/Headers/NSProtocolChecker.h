/*	NSProtocolChecker.h
	Copyright 1995-2002, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSProxy.h>
#import <Foundation/NSObject.h>

@interface NSProtocolChecker : NSProxy

- (Protocol *)protocol;
- (NSObject *)target;

@end

@interface NSProtocolChecker (NSProtocolCheckerCreation)

+ (id)protocolCheckerWithTarget:(NSObject *)anObject protocol:(Protocol *)aProtocol;
- (id)initWithTarget:(NSObject *)anObject protocol:(Protocol *)aProtocol;

@end

