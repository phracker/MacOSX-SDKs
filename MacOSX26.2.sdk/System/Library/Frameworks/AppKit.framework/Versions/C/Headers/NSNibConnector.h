/*
	NSNibConnector.h
	Application Kit
	Copyright (c) 1994-2024, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@interface NSNibConnector : NSObject <NSCoding>
@property (nullable, weak) id source;
@property (nullable, weak) id destination;
@property (copy) NSString *label;
- (void)replaceObject:(id)oldObject withObject:(id)newObject;
- (void)establishConnection;
@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
