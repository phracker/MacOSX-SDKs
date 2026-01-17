/*
	NSScriptExecutionContext.h
	Copyright (c) 1997-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSConnection;

@interface NSScriptExecutionContext : NSObject {
    @private
    id _topLevelObject;
    id _objectBeingTested;
    id _rangeContainerObject;
    id _moreVars;
}

+ (NSScriptExecutionContext *)sharedScriptExecutionContext;

@property (retain) id topLevelObject;
@property (retain) id objectBeingTested;
@property (retain) id rangeContainerObject;

@end
