/*	NSPortCoder.h
	Copyright (c) 1994-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSCoder.h>

@class NSConnection, NSPort, NSArray;

@interface NSPortCoder : NSCoder

- (BOOL)isBycopy;
- (BOOL)isByref;
- (void)encodePortObject:(NSPort *)aport;
- (NSPort *)decodePortObject;

// The following methods are deprecated. Instead of using these methods, NSPort subclasses should look up an NSConnection object using +connectionWithReceivePort:sendPort: and then ask that object to dispatch recieved component data using -dispatchWithComponents:. The NSConnection object will take care of creating the right kind of NSPortCoder object and giving it the data to decode and dispatch.
- (NSConnection *)connection NS_DEPRECATED(10_0, 10_7, 2_0, NA);
+ portCoderWithReceivePort:(NSPort *)rcvPort sendPort:(NSPort *)sndPort components:(NSArray *)comps NS_DEPRECATED(10_0, 10_7, 2_0, NA);
- (id)initWithReceivePort:(NSPort *)rcvPort sendPort:(NSPort *)sndPort components:(NSArray *)comps NS_DEPRECATED(10_0, 10_7, 2_0, NA);
- (void)dispatch NS_DEPRECATED(10_0, 10_7, 2_0, NA);

@end

@interface NSObject (NSDistributedObjects)

- (Class)classForPortCoder;

- (id)replacementObjectForPortCoder:(NSPortCoder *)coder;

@end
