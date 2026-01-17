/*
        NSTextStorageScripting.h
        AppKit Framework
        Copyright (c) 1997-2024, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSTextStorage.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
#if !TARGET_OS_IPHONE

@interface NSTextStorage (Scripting)

@property (copy) NSArray<NSTextStorage *> *attributeRuns;

@property (copy) NSArray<NSTextStorage *> *paragraphs;

@property (copy) NSArray<NSTextStorage *> *words;

@property (copy) NSArray<NSTextStorage *> *characters;

@property (nullable, strong) NSFont *font;

@property (nullable, strong) NSColor *foregroundColor;

@end
#endif // !TARGET_OS_IPHONE
NS_HEADER_AUDIT_END(nullability, sendability)
