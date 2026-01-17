/*
        NSDocument.h
        Application Kit
        Copyright (c) 1997-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSUserInterfaceValidation.h>

@class NSArray, NSData, NSUndoManager, NSURL;
@class NSFileWrapper, NSMenuItem, NSPrintInfo, NSWindow, NSWindowController;
@class NSView, NSPopUpButton, NSSavePanel, NSPrintOperation;
@class NSPageLayout;
@class NSDictionary;

// ================================================================================
// Document enumerated types
// ================================================================================

typedef enum _NSDocumentChangeType {
    NSChangeDone = 0,
    NSChangeUndone = 1,
    NSChangeCleared = 2
} NSDocumentChangeType;

typedef enum _NSSaveOperationType {
    NSSaveOperation = 0,
    NSSaveAsOperation = 1,
    NSSaveToOperation = 2
} NSSaveOperationType;

// ================================================================================
// NSDocument
// ================================================================================

@interface NSDocument : NSObject {
    @private
    NSWindow *_window;
    id _windowControllers;
    NSString *_fileName;
    NSString *_fileType;
    NSPrintInfo *_printInfo;
    long _changeCount;
    NSView *savePanelAccessory;
    id _displayName;
    void *_privateData;
    NSUndoManager *_undoManager;
    struct __docFlags {
        unsigned int inClose:1;
        unsigned int hasUndoManager:1;
        unsigned int isShowingPageLayout:1;
        unsigned int isRunningPrintOperation:1;
        unsigned int savePanelNameExtensionHidden:1;
        unsigned int reconciledToFileName:1;
        unsigned int RESERVED:26;
    } _docFlags;
    NSString *_savePanelSaveType;
}

- (id)init;
    // Designated Initializer.  Inits an "empty" document.
    
- (id)initWithContentsOfFile:(NSString *)fileName ofType:(NSString *)fileType;
- (id)initWithContentsOfURL:(NSURL *)url ofType:(NSString *)fileType;
    // These call [self init] and then continue on to load the document contents from the specified location.  They call the appropriate -readFrom... method below to load the document.

// -----------------------------------------------------------------------------
// Window controller management
// -----------------------------------------------------------------------------

- (NSArray *)windowControllers;
    // Returns the list of window controllers attached to the document.

- (void)addWindowController:(NSWindowController *)windowController;
    // Adds a new window controller to the document.

- (void)removeWindowController:(NSWindowController *)windowController;
    // Removes a window controller from the document.  A document whose list of window controllers becomes empty because of this method is _not_ closed.  But see NSWindowController's -close method for more info.

- (NSString *)windowNibName;
    // Subclasses may override this method to return the name of a nib file.  Subclasses which wish to act as the nib file's owner instead of subclassing NSWindowController should override this.  If you need multiple window controllers or want to use an NSWindowController subclass, use -makeWindowControllers.
    
- (void)makeWindowControllers;
    // Subclasses may override this to create the initial window controller(s) for the document.  The base class implementation will create an NSWindowController with the -windowNibName and with the document as the file's owner if -windowNibName returns a name.  If you override to create your own window controllers, be sure to use -addWindowController: to add them to the document after creating them.  This method is called by NSDocumentController's -open... methods, but you might want to call it directly in some circumstances.

- (void)showWindows;
    // Sends -showWindow to each of the -windowControllers.

- (BOOL)shouldCloseWindowController:(NSWindowController *)windowController;
    /*** This method is obsolete.  Please use shouldCloseWindowController:delegate:shouldCloseSelector:contextInfo: instead ***/
    // This method will return the result of -canCloseDocument if the window controller that is closing is the last one or is marked as causing the document to close.  Otherwise it just returns YES.  This is called automatically by NSWindow for any window which has a window controller and a document associated with it.  NSWindow calls this prior to asking its delegate -windowShouldClose:.

- (void)shouldCloseWindowController:(NSWindowController *)windowController delegate:(id)delegate shouldCloseSelector:(SEL)callback contextInfo:(void *)contextInfo;
// This method replaces shouldCloseWindowController:.  This method will invoke the callback the result of -canCloseDocumentWithDelegate:shouldCloseSelector:contextInfo: if the window controller that is closing is the last one or is marked as causing the document to close.  Otherwise it invokes the callback with YES.  This is called automatically by NSWindow for any window which has a window controller and a document associated with it.  NSWindow calls this prior to asking its delegate -windowShouldClose:.
    // shouldCloseSelector should have the following signature:
    // - (void)document:(NSDocument *)document shouldClose:(BOOL)shouldClose contextInfo:(void *)contextInfo

- (void)setWindow:(NSWindow *)window;
    // This method is for getting the window outlet hooked up from IB in the case where the document is the nib file's owner (ie if the document implements -windowNibName).  You should not call this method.  You might override it, but overriding windowControllerDidLoadNib: is a better idea.

- (void)windowControllerWillLoadNib:(NSWindowController *)windowController;
- (void)windowControllerDidLoadNib:(NSWindowController *)windowController;
    // These methods are called when the nib loads if the document is the nib file's owner (ie if the document implements -windowNibName).

// -----------------------------------------------------------------------------
// Document dirty state management, closing, and undo management
// -----------------------------------------------------------------------------

- (BOOL)isDocumentEdited;
    // Returns YES if the document has unsaved changes.

- (void)updateChangeCount:(NSDocumentChangeType)change;
    // Update the change count.  Updating the change count is handled automatically by watching the document's undo manager and watching when the document is saved/loaded.  So in most cases you need not worry about it.  If your document does not support undo, you should call -updateChangeCount: yourself whenever changes are made.  If the document goes from dirty to clean or vice-versa, all the document's -windowControllers are sent -setDocumentEdited:.
    
- (BOOL)canCloseDocument;
    /** This method is obsolete.  Please use -canCloseDocumentWithDelegate:shouldCloseSelector:contextInfo: instead **/
    // This returns YES if it is OK to close.  If the document is dirty, an alert will be presented giving the user a chance to save, not save or cancel.  If the user chooses to save, this method will save the document.  

- (void)canCloseDocumentWithDelegate:(id)delegate shouldCloseSelector:(SEL)shouldCloseSelector contextInfo:(void *)contextInfo;
    // If the document is not dirty, this method will immediately call the callback with YES.  If the document is dirty, an alert will be presented giving the user a chance to save, not save or cancel.  If the user chooses to save, this method will save the document.  If the save completes successfully, this method will call the callback with YES.  If the save is cancelled or otherwise unsuccessful, this method will call the callback with NO.  This method is called by shouldCloseWindowController: sometimes.  It is also called by NSDocumentController's -closeAllDocuments.  You should call it before you call -close if you are closing the document and want to give the user a chance save any edits.
    // shouldCloseSelector should have the following signature:
    // - (void)document:(NSDocument *)doc shouldClose:(BOOL)shouldClose contextInfo:(void *)contextInfo

- (void)close;
    // This method will -close all remaining window controllers of the document and then close the document by removing it from the NSDocumentController with -removeDocument:.  It will not save unsaved changes or ask the user whether they want to save.  If you want to close the document nicely, call -canCloseDocument first and pay attention to the return value.

- (NSUndoManager *)undoManager;
- (void)setUndoManager:(NSUndoManager *)undoManager;
- (BOOL)hasUndoManager;
- (void)setHasUndoManager:(BOOL)flag;
    // By default an NSDocument is set to have an undo manager and an instance of NSUndoManager will be created the first time it is needed.  If a document has an undo manager and the document implements full undo support, then dirty state management is automatic.  If your subclass does not support undo, then you should call setHasUndoManager:NO and you must manage the document dirty state yourself with -updateChangeCount:.  Supporting undo only partially is a hard problem in multiple-undo systems.  In general, the simplest solution (if it is not possible to support undo for all changes) is to make sure that all undo operations are cleared from the undo manager whenever an non-undoable operation takes place.  This is pretty drastic behavior, though.  If you wish to set a custom undo manager subclass for a document, be sure to do it early, before any undo invocations get registered for the document.

// -----------------------------------------------------------------------------
// File name and type stuff
// -----------------------------------------------------------------------------

- (NSString *)fileName;
- (void)setFileName:(NSString *)fileName;
    // Get/set the file for the document.  An untitled document's fileName is nil.  Stting a new fileName will cause all the document's -windowControllers to get a -synchronizeWindowTitleWithDocumentName message.

- (NSString *)fileType;
- (void)setFileType:(NSString *)type;
    // Get/set the file type.  Setting the file type does not change the -fileName, so if it is necessary to change the name (for example to change the extension), you must do it.

- (NSString *)displayName;
    // Returns the display name for the document.  By default this returns the name of the last file associated with the document, taking into account whether or not the file name's extension should be hidden, or an appropriate "Untitled" string if the document has never had a -fileName.  This is called by NSWindowController's -synchronizeWindowTitleWithDocumentName method.

// -----------------------------------------------------------------------------
// Primitive loading and saving override points
// -----------------------------------------------------------------------------

// The following three sets of methods are used to load and save the document.  The subclasser must implement this behavior.  But the subclass has several choices as to where to implement it.  Read the comments below to see how it all works.  Usually you would override just one of the following groups of methods.

- (NSData *)dataRepresentationOfType:(NSString *)type;
- (BOOL)loadDataRepresentation:(NSData *)data ofType:(NSString *)type;
    // For simple, flat-file documents, this is the simplest API to override.  These methods load or save using NSData objects to represent the document contents.  Reading and writing the data is handled automatically.

- (NSFileWrapper *)fileWrapperRepresentationOfType:(NSString *)type;
- (BOOL)loadFileWrapperRepresentation:(NSFileWrapper *)wrapper ofType:(NSString *)type;
    // These APIs are intended for documents that are stored as file wrappers using the NSFileWrapper class.  By default, these methods call the NSData based API above.  The default implementation only handles regular file file wrappers.

- (BOOL)writeToFile:(NSString *)fileName ofType:(NSString *)type;
- (BOOL)writeToURL:(NSURL *)url ofType:(NSString *)type;
- (BOOL)readFromFile:(NSString *)fileName ofType:(NSString *)type;
- (BOOL)readFromURL:(NSURL *)url ofType:(NSString *)type;
    // These methods are the more advanced override points.  If the NSFileWrapper or NSData based API above are not sufficient, then you can override these.  By default, these methods call the NSFileWrapper based APIs.  For the writing methods, there are some even more advanced override points below for even trickier cases.  The URL methods are (currently) implemented to just call he file methds with the url's path if it a file URL, but do not assume this will remain true.  Overriders should really override all four.

// -----------------------------------------------------------------------------
// More advanced loading and saving override points
// -----------------------------------------------------------------------------

- (BOOL)keepBackupFile;
    // Returns NO by default.  Subclasses can override if they wish backups to be kept after a save is completed.  This is called by -writeWithBackupToFile:ofType:saveOperation:.

- (BOOL)writeWithBackupToFile:(NSString *)fullDocumentPath ofType:(NSString *)documentTypeName saveOperation:(NSSaveOperationType)saveOperationType;
    // This method is called by NSDocument action methods like saveDocument:, saveDocumentAs:, etc...  It is responsible for handling backup of the existing file, if any, and removal of that backup if keepBackupFile is NO.  In between those two things, it calls -writeToFile:ofType:originalFile:saveOperation:.  You should never need to call this, but subclasses that want to change the way the backup stuff works can override it.

- (BOOL)writeToFile:(NSString *)fullDocumentPath ofType:(NSString *)documentTypeName originalFile:(NSString *)fullOriginalDocumentPath saveOperation:(NSSaveOperationType)saveOperationType;
    // This method is called from -writeWithBackupToFile:ofType:saveOperation: to actually write the file.  origFilename is the path to the orginal file if there is one and nil otherwise.  The default implementation simply calls writeToFile:ofType:.  You should not need to call this method directly, but subclasses that need access to the previously saved copy of their document while saving the new one can override this method.

- (NSDictionary *)fileAttributesToWriteToFile:(NSString *)fullDocumentPath ofType:(NSString *)documentTypeName saveOperation:(NSSaveOperationType)saveOperationType;
    // Returns the file attributes that should be written to the named document file of the specified document type, as part of a particular type of save operation.  The set of valid file attributes is a subset of those understood by the NSFileManager class.  This method can be overriden to customize the attributes that are written to document files.

- (BOOL)revertToSavedFromFile:(NSString *)fileName ofType:(NSString *)type;
- (BOOL)revertToSavedFromURL:(NSURL *)url ofType:(NSString *)type;
    // These merely call the corresponding -readFrom... method above, but these methods are used for reverting while the -readFrom... methods are called directly for a normal load.  So this API provides an override point for noticing a revert operation and possibly doing something special.


// -----------------------------------------------------------------------------
// UI actions for loading and saving
// -----------------------------------------------------------------------------

- (IBAction)saveDocument:(id)sender;
- (IBAction)saveDocumentAs:(id)sender;
- (IBAction)saveDocumentTo:(id)sender;
- (IBAction)revertDocumentToSaved:(id)sender;
    // These are the actual IB action methods for the Save, Save As..., Save To..., and Revert menu items. They are implemented in terms of the above methods (and the save panel methods below).

// -----------------------------------------------------------------------------
// Save panel API
// -----------------------------------------------------------------------------


- (NSString *)fileNameFromRunningSavePanelForSaveOperation:(NSSaveOperationType)saveOperation;
    /*** This method is obsolete.  Please use saveDocumentWithDelegate:didSaveSelector:contextInfo: instead ***/
    // This is the API that is used to run the save panel and return a fileName for saving.  It is called from the -save... action methods when the user needs to choose a file name.

- (void)saveDocumentWithDelegate:(id)delegate didSaveSelector:(SEL)didSaveSelector contextInfo:(void *)contextInfo;
    // This method runs the save panel and invokes saveToFile:saveOperation:delegate:didSaveSelector:contextInfo: with the result.  It is called from the -saveDocument: action method, and from canCloseDocumentWithDelegate:shouldCloseSelector:contextInfo: if the user chooses to save.
    // didSaveSelector should have the following signature:
    // - (void)document:(NSDocument *)doc didSave:(BOOL)didSave contextInfo:(void *)contextInfo

- (void)saveToFile:(NSString *)fileName saveOperation:(NSSaveOperationType)saveOperation delegate:(id)delegate didSaveSelector:(SEL)didSaveSelector contextInfo:(void *)contextInfo;
    // This method gets called after the user has been given the opportunity to select a destination through the modal save panel presented by runModalSavePanelForSaveOperation:delegate:didSaveSelector:contextInfo:.  If fileName is non-nil, this method writes the document to fileName, sets the document's file location and document type (if a native type), and clears the document's edited status.   didSaveSelector gets called with YES if the document is saved successfully and NO otherwise.
    // didSaveSelector should have the following signature:
    // - (void)document:(NSDocument *)doc didSave:(BOOL)didSave contextInfo:(void *)contextInfo


- (NSString *)fileTypeFromLastRunSavePanel;
    // This returns the file type that was last selected in the save panel.  This is primarily used by the -saveDocument:, -saveDocumentAs:, and -saveDocumentTo: methods to determine the type the user chose after the save panel has been run.

- (BOOL)fileNameExtensionWasHiddenInLastRunSavePanel;
    // This returns YES if a save panel has been presented by this document, and the user chose to hide the name extension of the file that was selected in that save panel, NO otherwise.

- (BOOL)shouldRunSavePanelWithAccessoryView;
    // This returns YES by default, but subclasses can override.  If this returns YES, NSDocument will supply an accessory view for the save panel when there is more than one possible document format to be saved.  The default accessory view contains a popup button with a list of the possible save types.  The accessory view is only used on platforms where it is needed.  On Windows, the default save panel has built in support for choosing types so that facility is used instead.

- (int)runModalSavePanel:(NSSavePanel *)savePanel withAccessoryView:(NSView *)accessoryView;
    /*** This method is obsolete.  Please use runModalSavePanelForSaveOperation:delegate:didSaveSelector:contextInfo: instead ***/
    // This is the primitive for running the save panel.  It is called by fileNameFromRunningSavePanelForSaveOperation:, so you should not have to call it, but it can be overridden if you need to do custom setup of the panel before running it.  If you have a custom accesory view, you can swap yours in for the default one here.

- (void)runModalSavePanelForSaveOperation:(NSSaveOperationType)saveOperation delegate:(id)delegate didSaveSelector:(SEL)didSaveSelector contextInfo:(void *)contextInfo;
    // This method prepares and runs the modal save panel.  It is invoked from saveDocumentWithDelegate:didSaveSelector:contextInfo:, and the action methods  saveDocumentAs:, and saveDocumentTo:.  This method will call prepareSavePanel: to allow further customization of the savePanel.
    // didSaveSelector should have the following signature:
    // - (void)document:(NSDocument *)doc didSave:(BOOL)didSave contextInfo:(void *)contextInfo

- (BOOL)prepareSavePanel:(NSSavePanel *)savePanel;
    // This method is invoked by runModalSavePanelForSaveOperation:delegate:didSaveSelector:contextInfo: to do any customization of the save panel.  It returns YES if successfully prepared, and NO otherwise.  The default implementation is empty and returns YES.

// -----------------------------------------------------------------------------
// Printing API
// -----------------------------------------------------------------------------

- (NSPrintInfo *)printInfo;
- (void)setPrintInfo:(NSPrintInfo *)printInfo;
    // Primitives for accessing and setting the document's NSPrintInfo.  Changing the document's printInfo is considered an edit.  If the document has an undo manager, the operation is recorded as an undo-able change.  If the document does not have an undo manager then -updateChangeCount:NSChangeDone is called.
    
- (int)runModalPageLayoutWithPrintInfo:(NSPrintInfo *)printInfo;
    // This method runs the page layout panel with the given NSPrintInfo and returns the modal result code (NSOKButton for OK and NSCancelButton for cancel.)  This method will invoke the -preparePageLayout: method to allow further customization of the page layout panel.  If the result is NSOKButton the NSPrintInfo will have been modified according to the changes made by the user in the panel.

- (void)runModalPageLayoutWithPrintInfo:(NSPrintInfo *)printInfo delegate:(id)delegate didRunSelector:(SEL)didRunSelector contextInfo:(void *)contextInfo;
    // This method prepares and runs the modal page layout panel.  It is invoked from the action metbod -[NSDocument runPageLayout:].  This method will invoke the -preparePageLayout: method to allow further customization of the page layout panel.
    // didRunSelector should have the same signature as:
    // - (void)documentDidRunModalPageLayout:(NSDocument *)document accepted:(BOOL)accepted contextInfo:(void *)contextInfo;

- (BOOL)shouldChangePrintInfo:(NSPrintInfo *)newPrintInfo;
    // This method returns YES by default.  Subclassers may override.  This method is called by runPageLayout: after it runs the panel using -runModalPageLayoutWithPrintInfo:delegate:didRunSelector:contextInfo: to decide whether or not to accept the new NSPrintInfo.  If it returns YES the new print info will be set using -setPrintInfo:.

- (IBAction)runPageLayout:(id)sender;
    // Runs the page layout panel with a copy of the document's current -printInfo.  If the user accepts the changes and -shouldChangePrintInfo: returns YES, then the new printInfo is set using -setPrintInfo:, otherwise the old printInfo is kept.  This is the action for the Page Setup... menu item.

- (BOOL)preparePageLayout:(NSPageLayout *)pageLayout;
    // This method is invoked by -runModalPageLayoutWithPrintInfo: and -runModalPageLayoutWithPrintInfo:delegate:didRunSelector:contextInfo: to do any customization of the page layout panel.  It returns YES if successfully prepared, and NO otherwise.  The default implementation is empty and returns YES.

- (void)runModalPrintOperation:(NSPrintOperation *)printOperation delegate:(id)delegate didRunSelector:(SEL)didRunSelector contextInfo:(void *)contextInfo;
    // This method runs a print operation, modally.  Overrides of printShowingPrintPanel: can invoke this method.
    // didRunSelector should have the same signature as:
    // - (void)documentDidRunModalPrintOperation:(NSDocument *)document success:(BOOL)success contextInfo:(void *)contextInfo;

- (void)printShowingPrintPanel:(BOOL)flag;
    // This method does nothing by default.  Subclasses should override in order to implement document printing.
    
- (IBAction)printDocument:(id)sender;
    // This method just calls [self printShowingPrintPanel:YES].  This is the action of the Print... menu item.

// -----------------------------------------------------------------------------
// Generic UI validation
// -----------------------------------------------------------------------------

- (BOOL)validateUserInterfaceItem:(id <NSValidatedUserInterfaceItem>)anItem;
    // This validates user interface items that NSDocument manages.  This currently only includes Revert (which is enabled only if the document has a fileName). You can override this method to add more selectors validated by your document subclass.
- (BOOL)validateMenuItem:(NSMenuItem *)anItem;
    // This just calls validateUserInterfaceItem:.

// -----------------------------------------------------------------------------
// Types API
// -----------------------------------------------------------------------------

+ (NSArray *)readableTypes;
    // Returns all types that the receiving document class can play the role of Editor or Viewer for.  This method cannot currently be overridden in any meaningful way.
    
+ (NSArray *)writableTypes;
    // Returns all types that the receiving document class can play the role of Editor for as well as all types that the receiving document class can export.  This method cannot currently be overridden in any meaningful way.
    
+ (BOOL)isNativeType:(NSString *)type;
    // Returns YES if the receiving document class can play the role of Editor for the given type.  This method cannot currently be overridden in any meaningful way.
    
@end

