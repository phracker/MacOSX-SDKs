/*
    NSSavePanel.h
    Application Kit
    Copyright (c) 1994-2024, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSPanel.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSBox, NSTextField, NSTextView, NSView, NSURL, NSProgressIndicator, NSControl;
@protocol NSOpenSavePanelDelegate;
@class UTType;

@interface NSSavePanel : NSPanel
/**
 A note on when properties can be set.
 Both the NSSavePanel and NSOpenPanel have two phases — configuration and running.
 The configuration phase is when the panel is not displayed. The running phase is when the panel is displayed — i.e. after `-beginSheetModalForWindow:completionHandler:`, `-beginWithCompletionHandler:`, `-runModal`. When a panel is dismissed, the panel reverts back to the configuration phase and can be reused.
 Some properties can only be set during the configuration phase. Those properties may be changed by the panel during the run phase. Unless otherwise mentioned a property can be changed any time.
 */

/**
 Creates a new instance of the NSSavePanel. This class is not a singleton.
 */
+ (NSSavePanel *)savePanel;

// MARK: - Result Properties

/**
 `NSSavePanel`: Returns the URL to save the file at. A file may already exist at `url` if the user choose to overwrite it.
 `NSOpenPanel`: Returns the single filename selected by the user. Note: if -allowsMultipleSelection is set, you should use the -URLs on NSOpenPanel instead.
 */
@property (nullable, readonly, copy) NSURL *URL;

// MARK: - Configuration Properties

/**
 Sets and returns the identifier.

 The panel's current state such as the root directory and the current directory are saved and restored relative to the identifier.
 - Note: When the identifier is changed, the properties that depend on the identifier are updated from user defaults. Properties that have a null value in user defaults are not changed (and keep their existing value).
 - Note: Can only be set during the configuration phase.
 */
@property (nullable, copy) NSUserInterfaceItemIdentifier identifier;

/**
 `NSSavePanel`/`NSOpenPanel`: Sets and returns the directory that is displayed. Set to `nil` to display the default directory. This method will not block to resolve the URL, and the directory will asynchronously be set, if required.
 - Note: Can only be set during the configuration phase.
 */
@property (nullable, copy) NSURL *directoryURL API_AVAILABLE(macos(10.6));

/**
 `NSSavePanel`: An array of UTTypes specifying the file types the user can save the file as. Set to `@[]` to specify that any file type can be used. If no extension is given by the user, the first preferred extension from the array will be used as the extension for the save panel. If the user specifies a type not in the array, and `allowsOtherFileTypes` is `YES`, they will be presented with another dialog when prompted to save. The default value is the empty array.
 `NSOpenPanel`: This property determines which files should be enabled in the open panel. Using the deprecated methods to show the open panel (the ones that take a "types:" parameter) will overwrite this value, and should not be used. `allowedContentTypes` can be changed while the panel is running (ie: from an accessory view). This is also known as the "enabled file types". Set to `@[]` to specify that all files should be enabled.
 */
@property (copy) NSArray<UTType *> *allowedContentTypes API_AVAILABLE(macos(11.0));

/**
 `NSSavePanel`: Returns a BOOL value that indicates whether the panel allows the user to save files with an extension that is not in the list of `allowedFileTypes`.
 `NSOpenPanel`: Not used.
 */
@property BOOL allowsOtherFileTypes;

/**
 `NSSavePanel`:The current type. If set to `nil`, resets to the first allowed content type. Returns `nil` if `allowedContentTypes` is empty.
 `NSOpenPanel`: Not used.
 - Note: Asserts that `currentContentType` conforms to `UTTypeData` or `UTTypeDirectory`.
 */
@property (nullable, copy) UTType *currentContentType API_AVAILABLE(macos(15.0));

/**
 Sets and returns the accessory view shown in the panel.

 For applications that link on 10.6 and later, the accessoryView's frame will be observed, and any changes the programmer makes to the frame will automatically be reflected in the panel (including animated changes to the frame height).

 For applications that link on 26.0 and later and use the Liquid Glass design, the accessoryView's control metrics will be the larger Liquid Glass metrics.
 */
@property (nullable, strong) NSView *accessoryView;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-property-type"

/**
 `NSSavePanel`/`NSOpenPanel`: Sets and returns the delegate.
 */
@property (nullable, weak) id<NSOpenSavePanelDelegate> delegate;

#pragma clang diagnostic pop

/**
 `NSSavePanel`: Returns `YES` if the panel is expanded. Defaults to `NO`. Persists in the user defaults.
 `NSOpenPanel`: Not used.
 */
@property (getter=isExpanded, readonly) BOOL expanded;

/**
 `NSSavePanel`/`NSOpenPanel`: Set to `YES` to show the "New Folder" button. Default is `YES`.
 */
@property BOOL canCreateDirectories;

/**
 `NSSavePanel`: Set to `YES` to show the "Hide Extension" menu item.
 `NSOpenPanel`: Not used.
 */
@property BOOL canSelectHiddenExtension;

/**
 `NSSavePanel`: Set to `YES` if the filename extension should be hidden. Otherwise, `NO` if the filename extension should be shown. Default is `YES`.
 - Note: Can only be set during the configuration phase.
 `NSOpenPanel`: Not used.
*/
@property (getter=isExtensionHidden) BOOL extensionHidden;

/**
 `NSSavePanel`/`NSOpenPanel`: If set to `YES`, the user can navigate into file packages as if they were directories. Default is `NO`.
 */
@property BOOL treatsFilePackagesAsDirectories;

/**
 `NSSavePanel`/`NSOpenPanel`: Sets the text shown on the Open or Save button. If set to an empty string, it will show a localized "Open" for the NSOpenPanel and "Save" for the NSSavePanel. The default value will be the correct localized prompt for the open or save panel, as appropriate.
 */
@property (null_resettable, copy) NSString *prompt;

/**
 `NSSavePanel`/`NSOpenPanel`: Sets and returns the title for the panel shown at the top of the window.
 - Note: The open and save panel does not currently have a titlebar. So the title is not displayed.
 */
@property (null_resettable, copy) NSString *title;

/**
 `NSSavePanel`: Sets and returns the text shown to the left of the "name field". Default value is a localized "Save As:" string.
 `NSOpenPanel`: Not used.
*/
@property (null_resettable, copy) NSString *nameFieldLabel;

/**
 `NSSavePanel`: Sets and returns the user-editable file name shown in the name field.
 - Note: Calling the deprecated methods that take a "name:" parameter will overwrite any values set before the panel is shown.
 - Note: If `[panel isExtensionHidden]` is set to `YES`, the extension will be hidden.
 - Note: Can only be set during the configuration phase.
 `NSOpenPanel`: Not used.
*/
@property (copy) NSString *nameFieldStringValue API_AVAILABLE(macos(10.6));

/**
 `NSSavePanel`/`NSOpenPanel`: Sets and returns the message shown under title of the panel.
 */
@property (null_resettable, copy) NSString *message;

/**
 `NSSavePanel`/`NSOpenPanel`: If `showsHiddenFiles` is set to `YES`, files that are normally hidden from the user are displayed. This method was published in Mac OS 10.6, but has existed since Mac OS 10.4. This property is KVO compliant. The user may invoke the keyboard shortcut (cmd-shift-.) to show or hide hidden files. Any user interface shown in an an accessory view should be updated by using key value observing (KVO) to watch for changes of this property. Alternatively, the user interface can be directly bound to this property. The default value is `NO`.
 */
@property BOOL showsHiddenFiles;

/**
 `NSSavePanel`: Shows or hides the "Tags" field in the receiver. By passing `YES`, you become responsible for setting Tag names on the resulting file after saving is complete. Default is `YES`.
 `NSOpenPanel`: Not used.
*/
@property BOOL showsTagField API_AVAILABLE(macos(10.9));

/**
 `NSSavePanel`: When -showsTagField returns YES, set any initial Tag names to be displayed, if necessary, prior to displaying the receiver. Also, if the user clicks "Save", take the result of -tagNames, and set them on the resulting file after saving is complete. Tag names are NSStrings, arrays of which can be used directly with the NSURLTagNamesKey API for getting and setting tags on files. Passing `nil` or an empty array to -setTagNames: will result in no initial Tag names appearing in the receiver. When -showsTagField returns YES, -tagNames always returns a non-nil array, and when NO, -tagNames always returns `nil`.
 `NSOpenPanel`: Not used.
 */
@property (nullable, copy) NSArray<NSString *> *tagNames API_AVAILABLE(macos(10.9));

/**
 `NSSavePanel`: Whether or not to show a control for selecting the type of the saved file.
 The control shows the types in `allowedContentTypes`. Default is `NO`.
 `NSOpenPanel`: Not used.
 - Note: If `allowedContentTypes` is empty, the control is not displayed.
 */
@property BOOL showsContentTypes API_AVAILABLE(macos(15.0));

/**
 Refreshes the open or save panel's contents.
 */
- (void)validateVisibleColumns;

// MARK: - Actions

- (IBAction)ok:(nullable id)sender;
- (IBAction)cancel:(nullable id)sender;

// MARK: - Displaying/Showing

/**
 `NSSavePanel`/`NSOpenPanel`: Presents the panel as a sheet modal to `window` and returns immediately. Configure the panel before calling this method. The completion handler block will be called after the user has closed the panel, however, the open/save panel sheet may still be on screen. If you require the sheet to be offscreen (for example, to show an alert), first call `[savePanel orderOut:nil]` to close it. The `result` will be `NSModalResponseOK`, `NSModalResponseCancel`, or if the panel fails to display, `NSModalResponseAbort`.
*/
- (void)beginSheetModalForWindow:(NSWindow *)window completionHandler:(void (^)(NSModalResponse result))handler API_AVAILABLE(macos(10.6));

/**
 `NSSavePanel`/`NSOpenPanel`: Presents the panel as a modeless window and returns immediately. Configure the panel before calling this method. The completion handler block will be called after the user has closed the panel. The `result` will be `NSModalResponseOK`, `NSModalResponseCancel`, or if the panel fails to display, `NSModalResponseAbort`.
*/
- (void)beginWithCompletionHandler:(void (^)(NSModalResponse result))handler API_AVAILABLE(macos(10.6));

/**
 `NSSavePanel`/`NSOpenPanel`: Presents the panel as an application modal window. Returns after the user has closed the panel.
  - Returns: `NSModalResponseOK`, `NSModalResponseCancel` or if the panel fails to display, `NSModalResponseAbort`.
*/
- (NSModalResponse)runModal;

@end

// MARK: -

@protocol NSOpenSavePanelDelegate <NSObject>
@optional

/** Optional — Enabling URLs.
 `NSSavePanel`: This method is not sent. All urls are always disabled.
 `NSOpenPanel`: Return `YES` to allow the `url` to be enabled in the panel. Delegate implementations should be fast to avoid stalling the UI. Applications linked on Mac OS 10.7 and later should be prepared to handle non-file URL schemes.
*/
- (BOOL)panel:(id)sender shouldEnableURL:(NSURL *)url NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.6));

/** Optional — URL validation for saving and opening files.
 `NSSavePanel`: Sent once by the save panel when the user clicks the Save button. The user is intending to save a file at `url`. Return `YES` if the `url` is a valid location to save to. Return `NO` and return by reference `outError` with a user displayable error message for why the `url` is not valid. If a recovery option is provided by the error, and recovery succeeded, the panel will attempt to close again.
 - Note: An item at `url` may not physically exist yet, unless the user decided to overwrite an existing item.
 `NSOpenPanel`: Sent once for each selected filename (or directory) when the user chooses the Open button. Return `YES` if the `url` is acceptable to open. Return `NO` and return by reference `outError` with a user displayable message for why the `url` is not valid for opening. If a recovery option is provided by the error, and recovery succeeded, the panel will attempt to close again.
 - Note: Implement this delegate method instead of  `panel:shouldEnableURL:` if the processing of the selected item takes a long time.
*/
- (BOOL)panel:(id)sender validateURL:(NSURL *)url error:(NSError **)outError NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.6));

/**
 Optional — Sent when the user selected the directory located at `url`. `url` may be `nil`. if the current directory can't be represented by an NSURL object (ie: the media sidebar directory, or the "Computer").
*/
- (void)panel:(id)sender didChangeToDirectoryURL:(nullable NSURL *)url NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.6));

/** Optional — Filename customization for the NSSavePanel. Allows the delegate to customize the filename entered by the user, before the extension is appended, and before the user is potentially asked to replace a file.
*/
- (nullable NSString *)panel:(id)sender userEnteredFilename:(NSString *)filename confirmed:(BOOL)okFlag NS_SWIFT_UI_ACTOR;

/** Optional — Sent when the user clicks the disclosure triangle to expand or collapse the file browser while in NSOpenPanel.
*/
- (void)panel:(id)sender willExpand:(BOOL)expanding NS_SWIFT_UI_ACTOR;

/** Optional — Sent when the user has changed the selection.
*/
- (void)panelSelectionDidChange:(nullable id)sender NS_SWIFT_UI_ACTOR;

/**
 `NSSavePanel`: Optional — Sent when the content type popup is displayed and the save panel needs the display name for a type. If `nil` is returned, the save panel will display type's `localizedDescription`.
  `NSOpenPanel`: Not sent.
*/
- (nullable NSString *)panel:(id)sender displayNameForType:(UTType *)type API_AVAILABLE(macos(15.0)) NS_SWIFT_UI_ACTOR;

/**
  `NSSavePanel`: Optional — Sent when the user changes the current type.
  `NSOpenPanel`: Not sent.
*/
- (void)panel:(id)sender didSelectType:(nullable UTType *)type API_AVAILABLE(macos(15.0)) NS_SWIFT_UI_ACTOR;

@end

// MARK: -

@interface NSObject(NSSavePanelDelegateDeprecated)

- (BOOL)panel:(id)sender isValidFilename:(NSString *)filename API_DEPRECATED("Use -panel:validateURL:error: instead", macos(10.0,10.6));
- (void)panel:(id)sender directoryDidChange:(NSString *)path API_DEPRECATED("Use -panel:didChangeToDirectoryURL: instead", macos(10.3,10.6));
- (NSComparisonResult)panel:(id)sender compareFilename:(NSString *)name1 with:(NSString *)name2 caseSensitive:(BOOL)caseSensitive API_DEPRECATED("Filenames in the save panel should not have a custom sort. This method is never called on 10.14, and rarely called after 10.6", macos(10.0,10.6));
- (BOOL)panel:(id)sender shouldShowFilename:(NSString *)filename API_DEPRECATED("Use -panel:shouldEnableURL: instead", macos(10.0,10.6));

@end

// MARK: -

@interface NSSavePanel(NSDeprecated)

- (NSString *)filename API_DEPRECATED("Use -URL instead", macos(10.0,10.6));
- (NSString *)directory API_DEPRECATED("Use -directoryURL instead", macos(10.0,10.6));
- (void)setDirectory:(nullable NSString *)path API_DEPRECATED("Use -setDirectoryURL: instead", macos(10.0,10.6));
- (nullable NSString *)requiredFileType API_DEPRECATED("Use -allowedContentTypes instead", macos(10.0,10.6));
- (void)setRequiredFileType:(nullable NSString *)type API_DEPRECATED("Use -allowedContentTypes: instead", macos(10.0,10.6));
- (void)beginSheetForDirectory:(nullable NSString *)path file:(nullable NSString *)name modalForWindow:(nullable NSWindow *)docWindow modalDelegate:(nullable id)delegate didEndSelector:(nullable SEL)didEndSelector contextInfo:(nullable void *)contextInfo API_DEPRECATED("Use beginSheetModalForWindow:completionHandler: instead. The following parameters are replaced by properties: 'path' is replaced by 'directoryURL' and 'name' by 'nameFieldStringValue'.", macos(10.0,10.6));
- (NSInteger)runModalForDirectory:(nullable NSString *)path file:(nullable NSString *)name API_DEPRECATED("Use -runModal instead. The following parameters are replaced by properties: 'path' is replaced by 'directoryURL' and 'name' by 'nameFieldStringValue'.", macos(10.0,10.6));
- (IBAction)selectText:(nullable id)sender API_DEPRECATED("Default implementation does nothing.", macos(10.0,10.3));

/**
 `NSSavePanel`: An array of NSStrings specifying the file types the user can save the file as. The file type can be a common file extension, or a UTI. A nil value indicates that any file type can be used. If the array is not nil and the array contains no items, an exception will be raised. If no extension is given by the user, the first item in the allowedFileTypes will be used as the extension for the save panel. If the user specifies a type not in the array, and 'allowsOtherFileTypes' is YES, they will be presented with another dialog when prompted to save. The default value is 'nil'.
 `NSOpenPanel`: On versions less than 10.6, this property is ignored. For applications that link against 10.6 and higher, this property will determine which files should be enabled in the open panel. Using the deprecated methods to show the open panel (the ones that take a "types:" parameter) will overwrite this value, and should not be used. The allowedFileTypes can be changed while the panel is running (ie: from an accessory view). The file type can be a common file extension, or a UTI. This is also known as the "enabled file types". A nil value indicates that all files should be enabled.
 */
@property (nullable, copy) NSArray<NSString *> *allowedFileTypes API_DEPRECATED("Use -allowedContentTypes instead", macos(10.3,12.0));
@end

enum {
    NSFileHandlingPanelCancelButton API_DEPRECATED_WITH_REPLACEMENT("NSModalResponseCancel", macos(10.0,10.13)) = NSModalResponseCancel,
    NSFileHandlingPanelOKButton	API_DEPRECATED_WITH_REPLACEMENT("NSModalResponseOK", macos(10.0,10.13)) = NSModalResponseOK,
};

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
