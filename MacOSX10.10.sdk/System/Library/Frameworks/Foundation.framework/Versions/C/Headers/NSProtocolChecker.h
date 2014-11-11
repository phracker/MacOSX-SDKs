/*	NSProtocolChecker.h
	Copyright (c) 1995-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSProxy.h>
#import <Foundation/NSObject.h>

@interface NSProtocolChecker : NSProxy

@property (readonly) Protocol *protocol;
@property (readonly, retain) NSObject *target;

@end

@interface NSProtocolChecker (NSProtocolCheckerCreation)

+ (instancetype)protocolCheckerWithTarget:(NSObject *)anObject protocol:(Protocol *)aProtocol;
- (instancetype)initWithTarget:(NSObject *)anObject protocol:(Protocol *)aProtocol;

@end

