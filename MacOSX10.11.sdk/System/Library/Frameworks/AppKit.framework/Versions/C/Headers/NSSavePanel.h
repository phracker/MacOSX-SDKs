/*
    NSSavePanel.h
    Application Kit
    Copyright (c) 1994-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSPanel.h>

NS_ASSUME_NONNULL_BEGIN

@class NSBox, NSTextField, NSTextView, NSView, NSURL, NSProgressIndicator, NSControl;
@protocol NSOpenSavePanelDelegate;

/* Return codes from the open/save panel.
*/
enum {
    NSFileHandlingPanelCancelButton	= NSModalResponseCancel,
    NSFileHandlingPanelOKButton	= NSModalResponseOK,
};

typedef struct __SPFlags {
    unsigned int saveMode:1;
    unsigned int isExpanded:1;
    unsigned int allowsOtherFileTypes:1;
    unsigned int canCreateDirectories:1;
    unsigned int canSelectedHiddenExtension:1;
    unsigned int reserved2:1;
    unsigned int delegate_shouldShowFilename:1;
    unsigned int delegate_compareFilename:1;
    unsigned int delegate_shouldEnableURL:1;
    unsigned int delegate_validateURL:1;
    unsigned int delegate_didChangeToDirectoryURL:1;
    unsigned int changingFrameSize:1;
    unsigned int movingAccessoryView:1;
    unsigned int userAccessoryViewFrameChange:1;
    unsigned int canChooseDirectories:1;
    unsigned int canChooseFiles:1;
    unsigned int delegate_selectionDidChange:1;
    unsigned int delegate_didChangeToDirectory:1;
    unsigned int calledWindowOrderedIn:1;
    unsigned int appCentric:1;
    unsigned int bottomControlsDisabled:1;
    unsigned int okButtonDisabled:1;
    unsigned int accessoryViewDisclosed:1;
    unsigned int delegate_isValidFilename:1;
    unsigned int delegate_userEnteredFilename:1;
    unsigned int delegate_panel_willExpand:1;
    unsigned int canResolveUbiquitousConflicts:1;
    unsigned int reserved:5;
} _SPFlags;

@class NSSavePanelAuxiliary;

@interface NSSavePanel : NSPanel {
@protected
    // All instance variables should be considered private
    NSView *__navView;
    NSView  *_accessoryView;
    NSArray *_allowedFileTypes;
    NSString *_validatedPosixName;
    NSString *_hiddenExtension;
        
    IBOutlet NSTextField  *_messageTextField;
    IBOutlet NSView       *_savePane;
    IBOutlet NSBox        *_saveNavSeparatorBox;
    IBOutlet NSView       *_savePaneTopPartsContainer;
    IBOutlet NSTextField  *_nameField;
    IBOutlet NSTextField  *_nameFieldLabel;
    IBOutlet NSButton     *_expansionButton;
    IBOutlet NSView       *_directoryPopUpContainer;
    IBOutlet NSControl    *_directoryPopUp;
    IBOutlet NSTextField  *_directoryPopUpLabel;
    IBOutlet NSBox        *_navViewContainer;
    IBOutlet NSBox        *_accessoryViewContainer;
    IBOutlet NSView       *_bottomControlsContainer;
    IBOutlet NSButton     *_hideExtensionButton;
    IBOutlet NSButton     *_newFolderButton;
    IBOutlet NSButton     *_cancelButton;
    IBOutlet NSButton     *_okButton;

    id _filepathInputController; // Unused
    id _reservedID;

    _SPFlags	_spFlags;
    
    NSSavePanelAuxiliary *_spAuxiliaryStorage;
    
@private
    char _unused:1;
#if !__LP64__
    char _reserved[4];
#endif
    IBOutlet NSProgressIndicator *_openProgressIndicator;
}

/* Creates a new instance of the NSSavePanel. This class is not a singleton. 
*/
+ (NSSavePanel *)savePanel;

#pragma mark -
#pragma mark Result Properties

/* NSSavePanel: Returns the URL to save the file at. A file may already exist at 'URL' if the user choose to overwrite it.
   NSOpenPanel: Returns the single filename selected by the user. Note: if -allowsMultipleSelection is set, you should use the -URLs on NSOpenPanel instead.
*/
@property (nullable, readonly, copy) NSURL *URL;

#pragma mark -
#pragma mark Configuration Properties

/* NSSavePanel/NSOpenPanel: Gets and sets the directoryURL shown. A value of nil indicates that the last directory shown to the user will be used. This method will not block to resolve the URL, and the directory will asyncronously be set, if required.
*/
@property (nullable, copy) NSURL *directoryURL NS_AVAILABLE_MAC(10_6);

/* 
    NSSavePanel: An array of NSStrings specifying the file types the user can save the file as. The file type can be a common file extension, or a UTI. A nil value indicates that any file type can be used. If the array is not nil and the array contains no items, an exception will be raised. If no extension is given by the user, the first item in the allowedFileTypes will be used as the extension for the save panel. If the user specifies a type not in the array, and 'allowsOtherFileTypes' is YES, they will be presented with another dialog when prompted to save. The default value is 'nil'.
    NSOpenPanel: On versions less than 10.6, this property is ignored. For applications that link against 10.6 and higher, this property will determine which files should be enabled in the open panel. Using the deprecated methods to show the open panel (the ones that take a "types:" parameter) will overwrite this value, and should not be used. The allowedFileTypes can be changed while the panel is running (ie: from an accessory view). The file type can be a common file extension, or a UTI. This is also known as the "enabled file types". A nil value indicates that all files should be enabled.
*/
@property (nullable, copy) NSArray<NSString *> *allowedFileTypes;

/*  NSSavePanel: Returns a BOOL value that indicates whether the receiver allows the user to save files with an extension that's not in the list of 'allowedFileTypes'.
    NSOpenPanel: Not used.
*/
@property BOOL allowsOtherFileTypes;

/* Gets and sets the accessory view shown in the panel. For applications that link on SnowLeopard and higher, the accessoryView's frame will be observed, and any changes the programmer makes to the frame will automatically be reflected in the panel (including animated changes to the frame height).
*/
@property (nullable, strong) NSView *accessoryView;

/* Gets and sets the delegate.
*/
@property (nullable, assign) id<NSOpenSavePanelDelegate> delegate;

/*  NSSavePanel: Returns YES if the panel is expanded. Defaults to NO, and persists in the user defaults.
    NSOpenPanel: Not used.
*/
@property (getter=isExpanded, readonly) BOOL expanded;

/*  NSSavePanel/NSOpenPanel: Set to YES to allow the "New Folder" button to be shown.
*/
@property BOOL canCreateDirectories;

/*  NSSavePanel: Set to YES to show the extension-hiding checkbox.
    NSOpenPanel: Should not be used.
*/
@property BOOL canSelectHiddenExtension;

/*  NSSavePanel: Set to YES if the extension-hiding checkbox should checked. The value persists in the user defaults specific for the application.
    NSOpenPanel: Should not be used.
*/
@property (getter=isExtensionHidden) BOOL extensionHidden;

/* NSSavePanel/NSOpenPanel: If set to YES, the user can open into file packages, as though they were directories.
*/
@property BOOL treatsFilePackagesAsDirectories;

/* NSSavePanel/NSOpenPanel: Sets the text shown on the Open or Save button. If set to an empty string, it will show a localized "Open" for the NSOpenPanel and "Save" for the NSSavePanel. The default value will be the correct localized prompt for the open or save panel, as appropriate.
*/
@property (null_resettable, copy) NSString *prompt;

/* NSSavePanel/NSOpenPanel: Gets and sets the title for the panel shown at the top of the window.
*/
@property (null_resettable, copy) NSString *title;

/*  NSSavePanel: Gets and sets the text shown to the left of the "name field". Default value is a localized "Save As:" string.
    NSOpenPanel: Not used.
*/
@property (null_resettable, copy) NSString *nameFieldLabel;

/*  NSSavePanel: Gets and sets the user-editable file name shown in the name field. 'value' must not be nil. NOTE: calling the deprecated methods that take a "name:" parameter will overwrite any values set before the panel was shown. Note that 'value' may have the file extension stripped, if [panel isExtensionHidden] is set to YES.
    NSOpenPanel: Not used.
*/
@property (copy) NSString *nameFieldStringValue NS_AVAILABLE_MAC(10_6);

/*  NSSavePanel/NSOpenPanel: Gets and sets the message shown under title of the panel. 'message' must not be nil.
*/
@property (null_resettable, copy) NSString *message;

- (void)validateVisibleColumns;

/* NSSavePanel/NSOpenPanel: If showsHiddenFiles is set to YES, files that are normally hidden from the user are displayed. This method was published in Mac OS 10.6, but has existed since Mac OS 10.4. This property is KVO compliant. The user may invoke the keyboard shortcut (cmd-shift-.) to show or hide hidden files. Any user interface shown in an an accessory view should be updated by using key value observing (KVO) to watch for changes of this property. Alternatively, the user interface can be directly bound to this property. The default value is NO.
*/
@property BOOL showsHiddenFiles;

/*  NSSavePanel: Shows or hides the "Tags" field in the receiver. By passing YES, you become responsible for setting Tag names on the resulting file after saving is complete.
    NSOpenPanel: Should not be used.
*/
@property BOOL showsTagField NS_AVAILABLE_MAC(10_9);

/*  NSSavePanel: When -showsTagField returns YES, set any initial Tag names to be displayed, if necessary, prior to displaying the receiver. Also, if the user clicks "Save", take the result of -tagNames, and set them on the resulting file after saving is complete. Tag names are NSStrings, arrays of which can be used directly with the NSURLTagNamesKey API for getting and setting tags on files. Passing nil or an empty array to -setTagNames: will result in no initial Tag names appearing in the receiver. When -showsTagField returns YES, -tagNames always returns a non-nil array, and when NO, -tagNames always returns nil.
    NSOpenPanel: Should not be used.
*/
@property (nullable, copy) NSArray<NSString *> *tagNames NS_AVAILABLE_MAC(10_9);

#pragma mark -
#pragma mark Actions

- (IBAction)ok:(nullable id)sender;
- (IBAction)cancel:(nullable id)sender;

#pragma mark -
#pragma mark Displaying/Showing

/* NSSavePanel/NSOpenPanel: Presents the panel as a sheet modal to 'window' and returns immediately. Desired properties of the panel should be properly setup before calling this method. The completion handler block will be called after the user has closed the panel, however, the open/save panel sheet may still be on screen. If you require the sheet to be offscreen (for example, to show an alert), first call [savePanel orderOut:nil] to close it. The passed in 'result' will be NSFileHandlingPanelOKButton==1 or NSFileHandlingPanelCancelButton==0.
*/
- (void)beginSheetModalForWindow:(NSWindow *)window completionHandler:(void (^)(NSInteger result))handler NS_AVAILABLE_MAC(10_6);

/* NSSavePanel/NSOpenPanel: Presents the panel as a modeless window and returns immediately. Desired properties of the panel should be properly setup before calling this method. The completion handler block will be called after the user has closed the panel. The passed in 'result' will be NSFileHandlingPanelOKButton==1 or NSFileHandlingPanelCancelButton==0.
*/
- (void)beginWithCompletionHandler:(void (^)(NSInteger result))handler NS_AVAILABLE_MAC(10_6);

/* NSSavePanel/NSOpenPanel: Presents the panel as an application modal window. It returns only after the user has closed the panel. The return value is NSFileHandlingPanelOKButton==1 or NSFileHandlingPanelCancelButton==0.
*/
- (NSInteger)runModal;

@end


@protocol NSOpenSavePanelDelegate <NSObject>
@optional

/* Optional - enabled URLs.
    NSOpenPanel: Return YES to allow the 'url' to be enabled in the panel. Delegate implementations should be fast to avoid stalling the UI. Applications linked on Mac OS 10.7 and later should be prepared to handle non-file URL schemes.
    NSSavePanel: This method is not called; all urls are always disabled.
*/
- (BOOL)panel:(id)sender shouldEnableURL:(NSURL *)url NS_AVAILABLE_MAC(10_6);

/* Optional - URL validation for saving and opening files. 
    NSSavePanel: The method is called once by the save panel when the user chooses the Save button. The user is intending to save a file at 'url'. Return YES if the 'url' is a valid location to save to. Note that an item at 'url' may not physically exist yet, unless the user decided to overwrite an existing item. Return NO and fill in the 'outError' with a user displayable error message for why the 'url' is not valid. If a recovery option is provided by the error, and recovery succeeded, the panel will attempt to close again.
    NSOpenPanel: The method is called once for each selected filename (or directory) when the user chooses the Open button. Return YES if the 'url' is acceptable to open. Return NO and fill in the 'outError' with a user displayable message for why the 'url' is not valid for opening. You would use this method over panel:shouldEnableURL: if the processing of the selected item takes a long time. If a recovery option is provided by the error, and recovery succeeded, the panel will attempt to close again.
*/
- (BOOL)panel:(id)sender validateURL:(NSURL *)url error:(NSError **)outError NS_AVAILABLE_MAC(10_6);

/* Optional - Sent when the user has changed the selected directory to the directory located at 'url'. 'url' may be nil, if the current directory can't be represented by an NSURL object (ie: the media sidebar directory, or the "Computer").
*/
- (void)panel:(id)sender didChangeToDirectoryURL:(nullable NSURL *)url NS_AVAILABLE_MAC(10_6);

/* Optional - Filename customization for the NSSavePanel. Allows the delegate to customize the filename entered by the user, before the extension is appended, and before the user is potentially asked to replace a file.
*/
- (nullable NSString *)panel:(id)sender userEnteredFilename:(NSString *)filename confirmed:(BOOL)okFlag;

/* Optional - Sent when the user clicks the disclosure triangle to expand or collapse the file browser while in NSOpenPanel.
*/
- (void)panel:(id)sender willExpand:(BOOL)expanding;

/* Optional - Sent when the user has changed the selection.
*/
- (void)panelSelectionDidChange:(nullable id)sender;

@end

@interface NSObject(NSSavePanelDelegateDeprecated)

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. Use panel:validateURL:error: instead. If both methods are implemented, the URL version will be called.
*/
- (BOOL)panel:(id)sender isValidFilename:(NSString *)filename NS_DEPRECATED_MAC(10_0, 10_6, "Use -panel:validateURL:error: instead");

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. Use panel:didChangeToDirectoryURL: instead.
*/
- (void)panel:(id)sender directoryDidChange:(NSString *)path NS_DEPRECATED_MAC(10_3, 10_6, "Use -panel:didChangeToDirectoryURL: instead");

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. This method should not be used anymore to control sort ordering.
*/
- (NSComparisonResult)panel:(id)sender compareFilename:(NSString *)name1 with:(NSString *)name2 caseSensitive:(BOOL)caseSensitive NS_DEPRECATED_MAC(10_0, 10_6);

/* This method is deprecated in 10.6, and will be formally deprecated in a future release. Use panel:shouldEnableURL:  instead
*/
- (BOOL)panel:(id)sender shouldShowFilename:(NSString *)filename NS_DEPRECATED_MAC(10_0, 10_6, "Use -panel:shouldEnableURL: instead");

@end

@interface NSSavePanel(NSDeprecated)

/* Use -URL instead.
*/
- (NSString *)filename NS_DEPRECATED_MAC(10_0, 10_6);

/* Use directoryURL/setDirectoryURL: instead.
*/
- (NSString *)directory NS_DEPRECATED_MAC(10_0, 10_6);
- (void)setDirectory:(nullable NSString *)path NS_DEPRECATED_MAC(10_0, 10_6);

/* Use allowedFileTypes/setAllowedFileTypes: instead. If no extension is given by the user, the first item in the allowedFileTypes will be used as the extension for the save panel.
*/
- (nullable NSString *)requiredFileType NS_DEPRECATED_MAC(10_0, 10_6);
- (void)setRequiredFileType:(nullable NSString *)type NS_DEPRECATED_MAC(10_0, 10_6);

/* Use beginSheetModalForWindow:completionHandler: instead. The following parameters are replaced by properties: 'path' is replaced by 'directoryURL' and 'name' by 'nameFieldStringValue'. 'delegate/didEndSelector/contextInfo' is replaced by the 'completionHandler'.
*/
- (void)beginSheetForDirectory:(NSString *)path file:(nullable NSString *)name modalForWindow:(nullable NSWindow *)docWindow modalDelegate:(nullable id)delegate didEndSelector:(nullable SEL)didEndSelector contextInfo:(nullable void *)contextInfo NS_DEPRECATED_MAC(10_0, 10_6);

/* Use -runModal after setting up desired properties. The following parameters are replaced by properties: 'path' is replaced by 'directoryURL' and 'name' by 'nameFieldStringValue'.
*/
- (NSInteger)runModalForDirectory:(nullable NSString *)path file:(nullable NSString *)name NS_DEPRECATED_MAC(10_0, 10_6);

/* Deprecated in 10.3. -[NSSavePanel selectText:] does nothing.
*/
- (IBAction)selectText:(nullable id)sender NS_DEPRECATED_MAC(10_0, 10_3);

@end

NS_ASSUME_NONNULL_END
