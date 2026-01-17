/*	NSScriptExecutionContext.h
	Copyright (c) 1997-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSConnection;

@interface NSScriptExecutionContext : NSObject {
    @private
    id _topLevelObject;
    id _objectBeingTested;
    id _rangeContainerObject;

    NSConnection *_connection;
}

+ (NSScriptExecutionContext *)sharedScriptExecutionContext;

- (id)topLevelObject;
- (void)setTopLevelObject:(id)obj;

- (id)objectBeingTested;
- (void)setObjectBeingTested:(id)obj;

- (id)rangeContainerObject;
- (void)setRangeContainerObject:(id)obj;

@end
