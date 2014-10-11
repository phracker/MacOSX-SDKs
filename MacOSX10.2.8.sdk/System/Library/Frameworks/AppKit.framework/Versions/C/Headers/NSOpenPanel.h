/*
	NSOpenPanel.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSSavePanel.h>

/* Tags of views in the OpenPanel */

@interface NSOpenPanel : NSSavePanel
{
    /*All instance variables are private*/
    NSArray	       *_filterTypes;
    void               *_auxiliaryOpenPanelStorage;
}

+ (NSOpenPanel *)openPanel;

- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;
- (void)setCanChooseDirectories:(BOOL)flag;
- (BOOL)canChooseDirectories;
- (void)setCanChooseFiles:(BOOL)flag;
- (BOOL)canChooseFiles;
- (void)setResolvesAliases:(BOOL)flag;
- (BOOL)resolvesAliases;
- (NSArray *)filenames;
- (NSArray *)URLs;

/* Present a sheet openPanel on a given window.  When the modal session is ended, 
** the didEndSelector will be invoked.  The didEndSelector method should
** have the following signature:
    ** - (void)openPanelDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
**
*/

- (void)beginSheetForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes modalForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

/*
 ** runModalForDirectory:file:types:relativeToWindow: is deprecated
 ** Please use beginSheetForDirectory:file:types:modalForWindow:modalDelegate:didEndSelector:contextInfo: instead
 */
- (int)runModalForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes relativeToWindow:(NSWindow*)window;
- (int)runModalForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes;
- (int)runModalForTypes:(NSArray *)fileTypes;

@end
