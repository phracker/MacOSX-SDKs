/*
	NSNibConnector.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSNibConnector : NSObject <NSCoding>
{
    @private
    id _source;		/* The source of the connection. */
    id _destination;	/* The destination of the connection. */
    NSString *_label;	/* The label of the connection. */
}
@property (assign) id source;
@property (nullable, assign) id destination;
@property (copy) NSString *label;
- (void)replaceObject:(id)oldObject withObject:(id)newObject;
- (void)establishConnection;
@end

NS_ASSUME_NONNULL_END
