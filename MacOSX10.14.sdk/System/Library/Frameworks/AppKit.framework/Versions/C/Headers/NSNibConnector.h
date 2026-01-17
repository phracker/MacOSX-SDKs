/*
	NSNibConnector.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSNibConnector : NSObject <NSCoding>
{
    @private
    id _source APPKIT_IVAR;		/* The source of the connection. */
    id _destination APPKIT_IVAR;	/* The destination of the connection. */
    NSString *_label APPKIT_IVAR;	/* The label of the connection. */
}
@property (nullable, assign) id source;
@property (nullable, assign) id destination;
@property (copy) NSString *label;
- (void)replaceObject:(id)oldObject withObject:(id)newObject;
- (void)establishConnection;
@end

NS_ASSUME_NONNULL_END
