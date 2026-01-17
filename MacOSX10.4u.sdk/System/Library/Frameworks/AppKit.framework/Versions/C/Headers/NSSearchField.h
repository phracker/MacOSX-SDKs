/*
    NSSearchField.h
    Application Kit
    Copyright (c) 2003-2005, Apple Computer, Inc.
    All rights reserved.
*/

#import <AppKit/NSTextField.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@interface NSSearchField : NSTextField {
  @private
    unsigned int _reserved1;
    unsigned int _reserved2;
    unsigned int _reserved3;
    unsigned int _reserved4;
}

- (void) setRecentSearches:(NSArray*)searches;
- (NSArray*) recentSearches;
    // forwarded to cell

- (void) setRecentsAutosaveName:(NSString*)string;
- (NSString*) recentsAutosaveName;
    // forwarded to cell

@end

#endif
