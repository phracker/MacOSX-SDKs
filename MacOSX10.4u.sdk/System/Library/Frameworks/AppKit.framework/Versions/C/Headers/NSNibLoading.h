/*
	NSNibLoading.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSBundle.h>

@class NSString, NSDictionary;

@interface NSBundle(NSNibLoading)

+ (BOOL)loadNibFile:(NSString *)fileName externalNameTable:(NSDictionary *)context withZone:(NSZone *)zone;
    /* This is the primitive that loads the contents of a .nib file.  Context holds key value pairs that can name objects that are referenced by the objects within the nib file (e.g., "NSOwner").  Objects from the nib are allocated in zone. */

+ (BOOL)loadNibNamed:(NSString *)nibName owner:(id)owner;
    /* A cover method where an external name table is created with owner as the only element with key "NSOwner".  Objects from the nib are allocated in owner's zone. If there is a bundle for owner's class, this method looks in that bundle for a nib with the given file name.  Otherwise, it looks in the mainBundle. */

- (BOOL)loadNibFile:(NSString *)fileName externalNameTable:(NSDictionary *)context withZone:(NSZone *)zone;
    /* This is the instance version of the above class method by the same name. */

@end

@interface NSObject (NSNibAwaking)
- (void)awakeFromNib;
@end
