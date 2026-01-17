/*
 	NSDocumentController.h
        Application Kit
        Copyright (c) 1997-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSUserInterfaceValidation.h>

@class NSArray, NSMutableArray, NSURL, NSOpenPanel, NSWindow, NSMenuItem, NSDocument;

// ================================================================================
// NSDocumentController
// ================================================================================

@interface NSDocumentController : NSObject <NSCoding> {
    @private
    id _documents;
    struct __controllerFlags {
        unsigned int shouldCreateUI:1;
        unsigned int notingRecentNSDocument:1;
        unsigned int RESERVED:30;
    } _controllerFlags;
    NSArray *_types;  // from info.plist with key NSTypes
    NSMutableArray *_recents;
    int _recentsLimit;
}

// -----------------------------------------------------------------------------
// The shared instance
// -----------------------------------------------------------------------------

+ (id)sharedDocumentController;
    // This returns the shared instance for the app.  It will create an instance of NSDocumentController if there is no existing shared instance.  Currently there are two ways to subclass NSDocumentController and have an instance of your subclass be the shared instance.  First, you can create an instance of your subclass in your application's main nib file.  Or second, you can alloc/init an instance of your subclass in your application delegate's implementation of -applicationWillFinishLaunching:.  The first instance which gets alloc/init'd becomes the shared instance.

- (id)init;
    // This is the designated initializer for the class.  The first instance of NSDocumentController or any of its subclasses which is created becomes the shared instance.

// -----------------------------------------------------------------------------
// Open document list management
// -----------------------------------------------------------------------------

- (NSArray *)documents;
    // Returns the list of open documents.

- (id)currentDocument;
- (NSString *)currentDirectory;
    // These conveniences return the current/active document or its file's directory (is any).
    
- (id)documentForWindow:(NSWindow *)window;
- (id)documentForFileName:(NSString *)fileName;
    // These allow finding the document that corresponds to a window or file

- (void)addDocument:(NSDocument *)document;
- (void)removeDocument:(NSDocument *)document;
    // Adds/removes the document from the list of open documents.  The -open... methods below will automatically call -addDocument.  A document will automatically call -removeDocument: when it closes.  These are mostly provided for subclassers that want to know when documents come and go.  You might send -addDocument: directly in cases where the -make... methods below are used or when a NSDocument subclass is alloc/init'd directly.

// -----------------------------------------------------------------------------
// Document creation
// -----------------------------------------------------------------------------

- (id)makeUntitledDocumentOfType:(NSString *)type;
- (id)makeDocumentWithContentsOfFile:(NSString *)fileName ofType:(NSString *)type;
- (id)makeDocumentWithContentsOfURL:(NSURL *)url ofType:(NSString *)type;
    // These methods figure out what kind of document to create (ie which subclass of NSDocument) based on the given type.  The document is not added to the NSDocumentController's list of open documents.  Also, no window controllers are created (ie -makeWindowControllers is not sent to the new document).  The returned document is autoreleased.

- (id)openUntitledDocumentOfType:(NSString*)type display:(BOOL)display;
- (id)openDocumentWithContentsOfFile:(NSString *)fileName display:(BOOL)display;
- (id)openDocumentWithContentsOfURL:(NSURL *)url display:(BOOL)display;
    // If a document for the given file or URL already exists, this method just returns it (after sending it a -showWindows call if display and -shouldCreateUI are YES).  Otherwise these methods use the corresponding "make" methods above to create a new document.  They then use -addDocument: to add the resulting NSDocument to the NSDocumentController's list of open documents.  If the -shouldCreateUI flag is YES then -makeWindowControllers will be sent to the new document and if the display argument is YES -showWindows will be sent as well.  The returned document is retained by the NSDocumentController until it is closed (and should be treated by the caller as autoreleased).

- (BOOL)shouldCreateUI;
- (void)setShouldCreateUI:(BOOL)flag;
    // These methods control whether the "open" methods will send -makeWindowControllers to newly created documents and whether the "display" argument to the -open... methods is respected.

// -----------------------------------------------------------------------------
// Menu actions
// -----------------------------------------------------------------------------

- (IBAction)saveAllDocuments:(id)sender;
- (IBAction)openDocument:(id)sender;
- (IBAction)newDocument:(id)sender;
    // Action methods for the corresponding File menu commands (Save All, New, and Open...).

- (BOOL)validateUserInterfaceItem:(id <NSValidatedUserInterfaceItem>)anItem;
    // Save All is enabled based on whether any documents are dirty. New and Open are enabled based on whether there are any types known to the app.

- (BOOL)validateMenuItem:(NSMenuItem *)anItem;
    // This is for backward compatibility. It just calls -validateUserInterfaceItem:. Override - validateUserInterfaceItem: to add your custom validation if it does not require menu item specific validation.

// -----------------------------------------------------------------------------
// Open Panel
// -----------------------------------------------------------------------------

- (NSArray *)fileNamesFromRunningOpenPanel;
- (NSArray *)URLsFromRunningOpenPanel;
    // These create an NSOpenPanel, set it up appropriately and use the -runModalOpenPanel:... method below to run it.  They then return the chosen files as either string paths or URLs.
    
- (int)runModalOpenPanel:(NSOpenPanel *)openPanel forTypes:(NSArray *)openableFileExtensions;
    // Runs the given open panel with the given types.  This is a good override point for customizing the panel setup.  It would rarely be useful for invoking directly.

// -----------------------------------------------------------------------------
// Batch document operations
// -----------------------------------------------------------------------------

- (BOOL)closeAllDocuments;
    /*** This method is obsolete.  Please use closeAllDocumentsWithDelegate:didCloseAllSelector:contextInfo: instead ***/
    // This method goes through all the open documents and tries to close them one by one.  Each NSDocument is sent -canCloseDocument which, if it is dirty, gives it a chance to refuse to close or to save itself first and may put up UI to ask whether to save or to ask perform a save.  This method returns YES if there are no open documents remaining at the end and NO otherwise. 

- (void)closeAllDocumentsWithDelegate:(id)delegate didCloseAllSelector:(SEL)didAllCloseSelector contextInfo:(void *)contextInfo;
    // This method goes through all the open documents and tries to close them one by one.  Each NSDocument is sent -canCloseDocument:didCloseSelector:contextInfo which, if it is dirty, gives it a chance to refuse to close or to save itself first and may put up UI to ask whether to save or to perform a save.
    // didCloseAllSelector is invoked with YES if all documents are closed, and NO otherwise.  It should have the following signature:
    // - (void)documentController:(NSDocumentController *)docController didCloseAll:(BOOL)didCloseAll contextInfo:(void *)contextInfo


- (BOOL)reviewUnsavedDocumentsWithAlertTitle:(NSString *)title cancellable:(BOOL)cancellable;
    /*** This method is obsolete.  Please use reviewUnsavedDocumentsWithAlertTitle:cancellable:delegate:didReviewAllSelector:contextInfo: instead ***/
    // This method returns YES if it is OK to Quit.  If there are unsaved documents open, an alert is presented allowing the user to review dirty documents or quit without saving.  If cancellable is YES then a third Cancel button is added as well.  If the user chooses to Review Unsaved, -closeAllDocuments is used to perform the review.

- (void)reviewUnsavedDocumentsWithAlertTitle:(NSString *)title cancellable:(BOOL)cancellable delegate:(id)delegate didReviewAllSelector:(SEL)didReviewAllSelector contextInfo:(void *)contextInfo;
    // Displays an attention panel (a dialog) asking users if they want to review unsaved documents, quit regardless of unsaved documents, or (if flag is YES) if they want to cancel the impending save operation.  This method invokes didReviewAllSelector with YES if quit without saving is chosen or if there are no dirty documents, and NO otherwise.   If the user selects the Review Unsaved option, closeAllDocumentsWithDelegate:didCloseAllSelector:contextInfo: is invoked.  This method is invoked when users choose the Quit menu command and when the computer power is being turned off (in which case, flag is NO).
    // didReviewAllSelector should have the following signature:
    // - (void)documentController:(NSDocumentController *)docController didReviewAll:(BOOL)didReviewAll contextInfo:(void *)contextInfo


- (BOOL)hasEditedDocuments;
    // Returns YES if any open document is dirty.

// -----------------------------------------------------------------------------
// Types API
// -----------------------------------------------------------------------------

- (NSString *)displayNameForType:(NSString *)documentTypeName;
- (NSString *)typeFromFileExtension:(NSString *)fileNameExtensionOrHFSFileType;
- (NSArray *)fileExtensionsFromType:(NSString *)documentTypeName;
- (Class)documentClassForType:(NSString *)documentTypeName;
    // These methods give general information about types.  These methods cannot really be effectively overridden.

// -----------------------------------------------------------------------------
// Open Recent Menu
// -----------------------------------------------------------------------------

- (NSArray *)recentDocumentURLs;
    // Returns the list of recent document urls.  This is not a good method for overriding since the internals of NSDocumentController do not generally use it.

- (void)noteNewRecentDocumentURL:(NSURL *)url;
    // This method should be called by non NSDocument-based apps when they open/save documents.
- (void)noteNewRecentDocument:(NSDocument *)document;
    // This is called by NSDocuments at the appropriate times for managing the recents list.  This just constructs an URL and calls noteNewRecentDocumentURL:.  Subclassers might override this to prevent certain documents or kinds of documents from getting into the list.

- (IBAction)clearRecentDocuments:(id)sender;
    // Empties the recent documents list for the app.  This is the action for the Clear Menu command, but it can be invoked directly if necessary.

@end

