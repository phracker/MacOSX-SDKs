/*	NSProtocolChecker.h
	Copyright (c) 1995-2005, Apple, Inc. All rights reserved.
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

