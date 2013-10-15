/*
    NSOpenPanel.h
    Application Kit
    Copyright (c) 1994-2009, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSSavePanel.h>
@class NSArray;
@class NSString;
@class NSWindow;

@interface NSOpenPanel : NSSavePanel {
@private
    char _reservedOpenPanel[4];
    void *_privateOpenPanel;
}

/* Creates a new instance of the NSOpenPanel. This class is not a singleton. 
 */
+ (NSOpenPanel *)openPanel;

- (NSArray *)URLs;

- (BOOL)resolvesAliases;
- (void)setResolvesAliases:(BOOL)flag;

- (BOOL)canChooseDirectories;
- (void)setCanChooseDirectories:(BOOL)flag;

- (BOOL)allowsMultipleSelection;
- (void)setAllowsMultipleSelection:(BOOL)flag;

- (BOOL)canChooseFiles;
- (void)setCanChooseFiles:(BOOL)flag;

@end

@interface NSOpenPanel (NSDeprecated)

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. Use URLs instead.
 */
- (NSArray *)filenames;

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. Use -runModalForWindow:completionHandler: instead.
    Set the -directoryURL property instead of passing in a 'path'.
    Set the -allowedFileTypes property instead of passing in the 'fileTypes'.
 */
- (void)beginSheetForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes modalForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. Use -runWithCompletionHandler: instead. 
    Set the -directoryURL property instead of passing in a 'path'.
    Set the -allowedFileTypes property instead of passing in the 'fileTypes'.
 */
- (void)beginForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes modelessDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo ;

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. Use -runModal instead. 
    Set the -directoryURL property instead of passing in a 'path'.
    Set the -allowedFileTypes property instead of passing in the 'fileTypes'.
 */
- (NSInteger)runModalForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes;

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. Use -runModal instead. 
    Set the -allowedFileTypes property instead of passing in the 'fileTypes'.
 */
- (NSInteger)runModalForTypes:(NSArray *)fileTypes;

@end
