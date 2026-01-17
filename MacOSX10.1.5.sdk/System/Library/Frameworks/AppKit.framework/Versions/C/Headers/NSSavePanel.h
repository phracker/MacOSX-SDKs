/*
	NSSavePanel.h - Nav Services version.
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>

@class NSBrowser, NSURL;

/* Tags of views in the SavePanel */

enum {
    NSFileHandlingPanelImageButton	= 150,
    NSFileHandlingPanelTitleField	= 151,
    NSFileHandlingPanelBrowser		= 152,
    NSFileHandlingPanelCancelButton	= NSCancelButton,
    NSFileHandlingPanelOKButton		= NSOKButton,
    NSFileHandlingPanelForm		= 155,

    // these are obsolete and are no longer in the panel
    NSFileHandlingPanelHomeButton	= 156,
    NSFileHandlingPanelDiskButton	= 157,
    NSFileHandlingPanelDiskEjectButton	= 158
};		

#ifndef WIN32
@interface NSSavePanel : NSPanel
{
    /*All instance variables are private*/
    NSBrowser		*_browser;
    id                  _form;
    id                  _homeButton;
    id                  _okButton;
    id			_hideExtensionButton;
    id                  _separator;
    id                  _accessoryView;
    NSString		*_filename;
    NSString		*_directory;
    NSArray		*_filenames;
    NSString		*_requiredType;
    void		*_columns;
    NSString		*_reserved2;
    int                 _cdcolumn;
    id                  _scroller;
    id                  _expandButton;
    id                  _browserBox;
    id                  _favoritesPopup;
    NSArray		*_recents;
    NSSize              _minCollapsedSize;
    NSSize              _minExpandedSize;
    NSSize              _expandedSize;          
    BOOL		_recyclable;
    BOOL		_docModal;
    struct __spFlags {
        unsigned int        opening:1;
        unsigned int        exitOk:1;
        unsigned int        allowMultiple:1;
        unsigned int        dirty:1;
        unsigned int        invalidateMatrices:1;
        unsigned int        filtered:1;
        unsigned int        canChooseFolders:1;
        unsigned int        treatsFilePackagesAsDirectories:1;
        unsigned int        largeFS:1;
        unsigned int	    delegateValidatesNew:1;
        unsigned int	    canChooseFiles:1;
        unsigned int        checkCase:1;
        unsigned int        cancd:1;
        unsigned int        UnixExpert:1;
	unsigned int	    delegateUserEnteredFilename:1;
        unsigned int        reserved:1;
        unsigned int        delegateCompares:1;
        unsigned int        delegateFilters:1;
        unsigned int	    collapsed:1;
        unsigned int	    editingNewFolder:1;
        unsigned int	    delegateNotifyExpands:1;
        unsigned int	    exitNextTime:1;
	unsigned int	    enableLeafSave:1;
        unsigned int	    openApps:1;
        unsigned int        updateFavorites:1;
        unsigned int	    includeNewFolder:1;
        unsigned int	    delegateNotifyDirectoryDidChange:1;
        unsigned int	    dontResolveAliases:1;
        unsigned int	    allowHideExtension:1;
        unsigned int	    hideExtension:1;
        unsigned int	    RESERVED:2;
    }                   _spFlags;
    id			_saveDelegate;
    SEL			_didEndSelector;
}
#else
@interface NSSavePanel : NSObject
{
    /*All instance variables are private*/
    NSString *_filename;
    NSString *_directory;
    NSArray  *_filenames;
    NSString *_requiredType;
    NSString *_title;
    NSView   *_accessoryView;
    struct __spFlags {
        unsigned int        RESERVED2:1;
        unsigned int        allowMultiple:1;
        unsigned int        canChooseFolders:1;
        unsigned int        RESERVED:29;
    }         _spFlags;
}
#endif WIN32

+ (NSSavePanel *)savePanel;

- (void)ok:(id)sender;
- (void)cancel:(id)sender;
- (int)runModalForDirectory:(NSString *)path file:(NSString *)name;
/*
**  Present a sheet savePanel on the given window.  When the modal session is
** ended, the didEndSelector will be invoked. The didEndSelector method should
** have the following signature:
** - (void)savePanelDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
**
*/
- (void)beginSheetForDirectory:(NSString *)path file:(NSString *)name modalForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;
/* 
** runModalForDirectory:file:relativeToWindow: is deprecated. 
** Please use beginSheetForDirectory:file:modalForWindow:modalDelegate:didEndSelector:contextInfo: instead
*/
- (int)runModalForDirectory:(NSString *)path file:(NSString *)name relativeToWindow:(NSWindow*)window;
- (int)runModal;
- (NSString *)filename;
- (NSURL *)URL;
- (void)setDirectory:(NSString *)path;
- (NSString *)directory;
- (void)setPrompt:(NSString *)prompt;
- (NSString *)prompt;
- (void)setTitle:(NSString *)title;
- (NSString *)title;
- (void)setRequiredFileType:(NSString *)type;
- (NSString *)requiredFileType;
- (void)setTreatsFilePackagesAsDirectories:(BOOL)flag;
- (BOOL)treatsFilePackagesAsDirectories;
- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)setDelegate:(id)anObject;
- (void)validateVisibleColumns;
- (void)selectText:(id)sender;
- (BOOL)isExpanded;

- (void)setCanSelectHiddenExtension:(BOOL)flag;
- (BOOL)isExtensionHidden;
- (void)setExtensionHidden:(BOOL)flag;
@end

@interface NSObject(NSSavePanelDelegate)
- (NSString *)panel:(id)sender userEnteredFilename:(NSString *)filename confirmed:(BOOL)okFlag;
- (BOOL)panel:(id)sender isValidFilename:(NSString *)filename;
- (BOOL)panel:(id)sender shouldShowFilename:(NSString *)filename;
- (NSComparisonResult)panel:(id)sender compareFilename:(NSString *)file1 with:(NSString *)file2 caseSensitive:(BOOL)caseSensitive;
- (void)panel:(id)sender willExpand:(BOOL)expanding;
@end
