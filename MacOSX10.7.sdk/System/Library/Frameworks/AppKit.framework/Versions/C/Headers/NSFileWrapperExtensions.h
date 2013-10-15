/*
	NSFileWrapperExtensions.h
	Application Kit
	Copyright (c) 2002-2011, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSFileWrapper.h>

@class NSImage;

@interface NSFileWrapper(NSExtensions)

/* The icon. -icon may return nil even if the receiver is the result of reading a parent from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that). The image that's returned might be shared by many NSFileWrappers so your application must not mutate it. If your application needs to mutate the returned image it should make a copy and mutate the copy instead.
*/
- (void)setIcon:(NSImage *)icon;
- (NSImage *)icon;

@end
