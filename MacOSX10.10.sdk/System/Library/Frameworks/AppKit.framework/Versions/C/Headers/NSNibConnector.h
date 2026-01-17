/*
	NSNibConnector.h
	Application Kit
	Copyright (c) 1994-2014, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@interface NSNibConnector : NSObject <NSCoding>
{
    @private
    id _source;		/* The source of the connection. */
    id _destination;	/* The destination of the connection. */
    NSString *_label;	/* The label of the connection. */
}
@property (assign) id source;
@property (assign) id destination;
@property (copy) NSString *label;
- (void)replaceObject:(id)oldObject withObject:(id)newObject;
- (void)establishConnection;
@end
