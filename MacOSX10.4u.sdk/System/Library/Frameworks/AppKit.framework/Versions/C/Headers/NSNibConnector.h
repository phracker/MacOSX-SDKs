/*
	NSNibConnector.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
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
- (id)source;
- (void)setSource:(id)source;
- (id)destination;
- (void)setDestination:(id)destination;
- (NSString *)label;
- (void)setLabel:(NSString *)label;
- (void)replaceObject:(id)oldObject withObject:(id)newObject;
- (void)establishConnection;
@end
