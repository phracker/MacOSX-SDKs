/*
        NSApplicationScripting.h
        AppKit Framework
        Copyright (c) 1997-2004, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSApplication.h>

@interface NSApplication(NSScripting)

// A key value coding compliant get-accessor for the orderedDocuments to-many-relationship declared in Cocoa's definition of the Standard Suite.  Return an array of currently open scriptable documents, in a predictable order that will be meaningful to script writers.  NSApplication's implementation of this method returns pointers to all NSDocuments in the front-to-back order of each document's frontmost window.  NSDocuments that have no associated windows are at the end of the array.
- (NSArray *)orderedDocuments;

// A key value coding compliant get-accessor for the orderedWindows to-many-relationship declared in Cocoa's definition of the Standard Suite.  Return an array of currently open scriptable windows, including hidden windows, but typically not includings things like panels.
- (NSArray *)orderedWindows;

@end

@interface NSObject(NSApplicationScriptingDelegation)

// Return YES if the receiving delegate object can respond to key value coding messages for a specific keyed attribute, to-one relationship, or to-many relationship.  Return NO otherwise.
- (BOOL)application:(NSApplication *)sender delegateHandlesKey:(NSString *)key;

@end
