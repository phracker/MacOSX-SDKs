/*
        NSTextStorageScripting.h
        AppKit Framework
        Copyright (c) 1997-2014, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSTextStorage.h>

@interface NSTextStorage (Scripting)

@property (copy) NSArray *attributeRuns;

@property (copy) NSArray *paragraphs;

@property (copy) NSArray *words;

@property (copy) NSArray *characters;

@property (strong) NSFont *font;

@property (strong) NSColor *foregroundColor;

@end
