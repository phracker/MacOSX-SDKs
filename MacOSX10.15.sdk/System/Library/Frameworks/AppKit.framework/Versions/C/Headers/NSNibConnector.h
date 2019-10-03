/*
	NSNibConnector.h
	Application Kit
	Copyright (c) 1994-2019, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@interface NSNibConnector : NSObject <NSCoding>
@property (nullable, assign) id source;
@property (nullable, assign) id destination;
@property (copy) NSString *label;
- (void)replaceObject:(id)oldObject withObject:(id)newObject;
- (void)establishConnection;
@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
