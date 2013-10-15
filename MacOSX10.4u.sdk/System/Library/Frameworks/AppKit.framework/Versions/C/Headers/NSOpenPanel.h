/*
	NSOpenPanel.h
	Application Kit
	Copyright (c) 1994-2004, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSSavePanel.h>

@interface NSOpenPanel : NSSavePanel {
    char _reservedOpenPanel[4];
    void *_privateOpenPanel;
}

+ (NSOpenPanel *)openPanel;

- (NSArray *)URLs;
- (NSArray *)filenames;

- (BOOL)resolvesAliases;
- (void)setResolvesAliases:(BOOL)flag;

- (BOOL)canChooseDirectories;
- (void)setCanChooseDirectories:(BOOL)flag;

- (BOOL)allowsMultipleSelection;
- (void)setAllowsMultipleSelection:(BOOL)flag;

- (BOOL)canChooseFiles;
- (void)setCanChooseFiles:(BOOL)flag;

@end

@interface NSOpenPanel (NSOpenPanelRuntime)

- (void)beginSheetForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes modalForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)beginForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes modelessDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;
#endif

- (int)runModalForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes;
- (int)runModalForTypes:(NSArray *)fileTypes;

@end
