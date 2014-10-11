/*
        NSApplicationScripting.h
        AppKit Framework
        Copyright (c) 1997-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSApplication.h>

@interface NSApplication (NSScripting)

- (NSArray *)orderedDocuments;
- (NSArray *)orderedWindows;

@end

@interface NSObject (NSApplicationScriptingDelegation)

- (BOOL)application:(NSApplication *)sender delegateHandlesKey:(NSString *)key;

@end
