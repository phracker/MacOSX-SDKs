/*
	NSSavePanel.h
	Application Kit
	Copyright (c) 1994-2004, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSPanel.h>

@class NSBox, NSMutableArray, NSNavView, NSNavNodePopUpButton, NSTextField, NSTextView, NSView, NSURL, NSNavFilepathInputController, NSNavNewFolderController;

enum {
    NSFileHandlingPanelCancelButton	= NSCancelButton,
    NSFileHandlingPanelOKButton		= NSOKButton,
};		

typedef struct __SPFlags {
    unsigned int saveMode:1;
    unsigned int isExpanded:1;
    unsigned int allowsOtherFileTypes:1;
    unsigned int canCreateDirectories:1;
    unsigned int canSelectedHiddenExtension:1;
    unsigned int reserved:27;
} _SPFlags;

@class NSSavePanelAuxiliary;

@interface NSSavePanel : NSPanel {
    NSNavView *_navView;
    NSView *_accessoryView;
    NSArray *_allowedFileTypes;
    NSString *_validatedPosixName;
    NSString *_hiddenExtension;
        
    IBOutlet NSTextField  *_messageTextField;
    IBOutlet NSView       *_savePane;
    IBOutlet NSBox        *_saveNavSeparatorBox;
    IBOutlet NSView         *_savePaneTopPartsContainer;
    IBOutlet NSTextField      *_nameField;
    IBOutlet NSTextField      *_nameFieldLabel;
    IBOutlet NSButton         *_expansionButton;
    IBOutlet NSView         *_directoryPopUpContainer;
    IBOutlet NSNavNodePopUpButton *_directoryPopUp;
    IBOutlet NSTextField       *_directoryPopUpLabel;
    IBOutlet NSBox        *_navViewContainer;
    IBOutlet NSBox        *_accessoryViewContainer;
    IBOutlet NSView       *_bottomControlsContainer;
    IBOutlet NSButton       *_hideExtensionButton;
    IBOutlet NSButton       *_newFolderButton;
    IBOutlet NSButton       *_cancelButton;
    IBOutlet NSButton       *_okButton;
    
    IBOutlet NSNavFilepathInputController *_filepathInputController;
    IBOutlet NSNavNewFolderController *_newFolderController;

    _SPFlags	_spFlags;
    
    NSSavePanelAuxiliary   *_spAuxiliaryStorage;
    
    char _reserved[5];

    void *_private;
}

+ (NSSavePanel *)savePanel;

- (NSURL *)URL;

- (NSString *)filename;

- (NSString *)directory;
- (void)setDirectory:(NSString *)path;

- (NSString *)requiredFileType;
- (void)setRequiredFileType:(NSString *)type;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSArray *)allowedFileTypes;
- (void)setAllowedFileTypes:(NSArray *)types;

- (BOOL)allowsOtherFileTypes;
- (void)setAllowsOtherFileTypes:(BOOL)flag;
#endif

- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)view;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (id)delegate;
#endif
- (void)setDelegate:(id)delegate;

- (BOOL)isExpanded;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (BOOL)canCreateDirectories;
- (void)setCanCreateDirectories:(BOOL)flag;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (BOOL)canSelectHiddenExtension;
#endif
- (void)setCanSelectHiddenExtension:(BOOL)flag;
- (BOOL)isExtensionHidden;
- (void)setExtensionHidden:(BOOL)flag;

- (BOOL)treatsFilePackagesAsDirectories;
- (void)setTreatsFilePackagesAsDirectories:(BOOL)flag;

- (NSString *)prompt;
- (void)setPrompt:(NSString *)prompt;

- (NSString *)title;
- (void)setTitle:(NSString *)title;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSString *)nameFieldLabel;
- (void)setNameFieldLabel:(NSString *)label;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSString *)message;
- (void)setMessage:(NSString *)message;
#endif

- (void)validateVisibleColumns;

// A method that was deprecated in Mac OS 10.3.  -[NSSavePanel selectText:] does nothing.
- (IBAction)selectText:(id)sender;

@end


@interface NSSavePanel (NSSavePanelRuntime)

- (IBAction)ok:(id)sender;
- (IBAction)cancel:(id)sender;

- (void)beginSheetForDirectory:(NSString *)path file:(NSString *)name modalForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

- (int)runModalForDirectory:(NSString *)path file:(NSString *)name;
- (int)runModal;

@end


@interface NSObject (NSSavePanelDelegate)

- (BOOL)panel:(id)sender shouldShowFilename:(NSString *)filename;
- (NSComparisonResult)panel:(id)sender compareFilename:(NSString *)name1 with:(NSString *)name2 caseSensitive:(BOOL)caseSensitive;
- (BOOL)panel:(id)sender isValidFilename:(NSString *)filename;
- (NSString *)panel:(id)sender userEnteredFilename:(NSString *)filename confirmed:(BOOL)okFlag;
- (void)panel:(id)sender willExpand:(BOOL)expanding;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)panel:(id)sender directoryDidChange:(NSString *)path;
- (void)panelSelectionDidChange:(id)sender;
#endif

@end
