/*	SBElementArray.h
	Copyright (c) 2006, Apple, Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <ScriptingBridge/SBObject.h>


@interface SBElementArray : NSMutableArray
{
	SBObject *_parent;
	DescType _elementCode;
	void *_reserved;
}

- (id) objectWithName:(NSString *)name;
- (id) objectWithID:(id)identifier;
- (id) objectAtLocation:(id)location;

- (NSArray *) arrayByApplyingSelector:(SEL)selector;
- (NSArray *) arrayByApplyingSelector:(SEL)aSelector withObject:(id)argument;

- (NSArray *) get;

@end
