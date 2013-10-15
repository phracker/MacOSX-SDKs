/*
	NSDocument.h
	Application Kit
	Copyright (c) 1997-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSUserInterfaceValidation.h>

@class NSArray, NSData, NSDate, NSDictionary, NSError, NSFileWrapper, NSMenuItem, NSPageLayout, NSPrintInfo, NSPrintOperation, NSSavePanel, NSUndoManager, NSURL, NSView, NSWindow, NSWindowController;

enum {

/* The value to pass to -updateChangeCount: to indicate that a single change has been done. For example, NSDocument's built-in undo support uses this whenever a document receives an NSUndoManagerWillCloseUndoGroupNotification from its own undo manager.
*/
    NSChangeDone = 0,

/* The value to pass to indicate that a single change has been undone. For example, NSDocument's built-in undo support uses this whenever a document receives an NSUndoManagerDidUndoChangeNotification from its own undo manager.
*/
    NSChangeUndone = 1,

/* The value to pass to indicate that the document has been synchronized with its file or file package. For example, -saveToURL:ofType:forSaveOperation:error: uses this for a successful NSSaveOperation or NSSaveAsOperation. -revertDocumentToSaved: does too.
*/
    NSChangeCleared = 2,

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* The value to pass to indicate that a single change has been redone. For example, NSDocument's built-in undo support uses this whenever a document receives an NSUndoManagerDidRedoChangeNotification from its own undo manager.
*/
    NSChangeRedone = 5,

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* The value to pass to indicate that the document has been initialized with the contents of a file or file package other than the one whose location would be returned by -fileURL, and therefore can't possibly be synchronized with its persistent representation. For example, -initForURL:withContentsOfURL:ofType:error: uses this when the two passed-in URLs are not equal to indicate that an autosaved document is being reopened.
*/
    NSChangeReadOtherContents = 3,

/* The value to pass to indicate that the document's contents have been autosaved. For example, -saveToURL:ofType:forSaveOperation:error: uses this for a successful NSAutosaveOperation.
*/
    NSChangeAutosaved = 4
    
#endif

};
typedef NSUInteger NSDocumentChangeType;

enum {

/* The overwriting of a document's file or file package with the document's current contents.
*/
    NSSaveOperation = 0,

/* The writing of a document's current contents to a new file or file package, and then making the just-written file or file package the document's current one.
*/
    NSSaveAsOperation = 1,

/* The writing of a document's current contents to a new file or file package without changing the document's current one.
*/
    NSSaveToOperation = 2,

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    
/* The writing of a document's current contents to a file or file package that is separate from the document's current one, without changing the document's current one.
*/
    NSAutosaveOperation = 3
    
#endif
    
};
typedef NSUInteger NSSaveOperationType;

@interface NSDocument : NSObject <NSUserInterfaceValidations> {
    @private
    NSWindow *_window;
    id _windowControllers;
    NSURL *_fileURL;
    NSString *_fileType;
    NSPrintInfo *_printInfo;
    long _changeCount;
    NSView *savePanelAccessory;
    id _displayName;
    id _privateData;
    NSUndoManager *_undoManager;
    struct __docFlags {
	unsigned int inClose:1;
	unsigned int hasUndoManager:1;
	unsigned int isShowingPageLayout:1;
	unsigned int isRunningPrintOperation:1;
	unsigned int savePanelNameExtensionHidden:1;
	unsigned int reconciledToFileName:1;
	unsigned int checkingDisplayName:1;
	unsigned int definitelyHasUnsavedChanges:1;
	unsigned int definitelyHasUnautosavedChanges:1;
	unsigned int RESERVED:23;
    } _docFlags;
    NSString *_savePanelSaveType;
}

#pragma mark *** Initialization ***

/* The designated initializer. It is invoked by each of NSDocument's other initialization methods.

You can override this method to perform initialization that must be done both when creating new empty documents and when opening existing documents. Your override must invoke super to initialize private NSDocument instance variables. It must never return nil. If an error can occur during object initialization, check for the error in an override of -initWithType:error:, -initWithContentsOfURL:ofType:error:, or -initForURL:withContentsOfURL:ofType:error:, because those methods can return NSErrors.
*/
- (id)init;

#pragma mark *** Creation ***

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Initialize a new empty document of a specified type, and return it if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why the document could not be initialized. The default implementation of this method just invokes [self init] and [self setFileType:typeName].

You can override this method to perform initialization that must be done when creating new documents but should not be done when opening existing documents. Your override should typically invoke super, or at least it must invoke -init, NSDocument's designated initializer, to initialize NSDocument's private instance variables.
*/
- (id)initWithType:(NSString *)typeName error:(NSError **)outError;

#endif

#pragma mark *** Opening ***

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Initialize a document located by a URL, of a specified type, and return it if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why the document could not be initialized. The default implementation of this method invokes [self init], [self readFromURL:absoluteURL ofType:typeName error:outError], [self setFileURL:absoluteURL], [self setFileType:typeName], and [self setFileModificationDate:theModificationDate].

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self initWithContentsOfFile:absoluteURL ofType:typeName] if -initWithContentsOfFile:ofType: is overridden and the URL uses the "file:" scheme. It still invokes [self setFileModificationDate:theModificationDate] in this situation.
*/
- (id)initWithContentsOfURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)outError;

#endif

#pragma mark *** Reopening after Autosaving ***

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Initialize a document located by a URL, of a specified type, but by reading the contents for the document from another URL, and return it if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why the document could not be initialized. The default implementation of this method invokes [self readFromURL:absoluteDocumentContentsURL ofType:typeName error:outError], [self setFileURL:absoluteURL], [self setAutosavedContentsFileURL:absoluteDocumentContentsURL], [self setFileType:typeName], and [self setFileModificationDate:theModificationDate]. It also invokes [self updateChangeCount:NSChangeReadOtherContents] if the two URLs aren't identical, so that -isDocumentEdited will always return YES until the user saves or reverts the document.

To ease the adoption of the autosaving feature introduced in Mac OS 10.4, the default implementation of this method invokes [self initWithContentsOfFile:[absoluteDocumentContentsURL path] ofType:typeName] if -initWithContentsOfFile:ofType: is overridden and the URL uses the "file:" scheme. It still invokes [self setFileModificationDate:theModificationDate] and [self updateChangeCount:NSChangeReadOtherContents] in this situation. It still also invokes [self setFileURL:absoluteURL], to overwrite the incorrect invocation of -setFileName: that the override of -initWithContentsOfFile:ofType: likely did.

absoluteDocumentURL will be nil if the initializing is being done as part of the reopening of an autosaved document when the autosaved document had never been saved in the first place.
*/
- (id)initForURL:(NSURL *)absoluteDocumentURL withContentsOfURL:(NSURL *)absoluteDocumentContentsURL ofType:(NSString *)typeName error:(NSError **)outError;

#endif

#pragma mark *** Attributes Applicable to Every Kind of Document ***

/* These should be set at initialization time, but not as part of reading the document, and during NSSaveOperations and NSSaveAsOperations, but not as part of writing the document. Specifically, there should be no need to set these from within an override of a -read... or -write... method.
*/

/* The name of the document's format. The set method isn't for _changing_ the document's format, it's just for initially recording the document's format during opening or saving.
*/
- (void)setFileType:(NSString *)typeName;
- (NSString *)fileType;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* The location of the document's on-disk representation. The set method doesn't actually rename the document, it's just for recording the document's location during initial opening or saving. The default implementation of -setFileURL: just records the URL so that the default implementation of -fileURL can return it. The default implementation of -fileURL returns whatever was stored by a previous invocation of the default implementation of -setFileURL:.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of -setFileURL: instead invokes [self setFileName:[absoluteURL path]] if -setFileName: is overridden and the URL is nil or uses the "file:" scheme. Likewise, the default implementation of -fileURL instead invokes -[self fileName] and returns the result as a URL if -fileName is overridden.
*/
- (void)setFileURL:(NSURL *)absoluteURL;
- (NSURL *)fileURL;

/* The last known modification date of the document's on-disk representation.
*/
- (void)setFileModificationDate:(NSDate *)modificationDate;
- (NSDate *)fileModificationDate;

#endif

#pragma mark *** Reverting ***

/* The action of the File menu's Revert to Saved item in a document-based application. The default implementation of this method presents a panel giving the user the opportunity to cancel the operation and, and if the user chooses to continue, makes sure that any editor registered using Cocoa Bindings' NSEditorRegistration informal protocol has discarded its changes and then invokes [self revertToContentsOfURL:[self url] ofType:[self fileType] error:outError]. If that returns NO, it presents the error to the user in an document-modal alert panel.
*/
- (IBAction)revertDocumentToSaved:(id)sender;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Discard all unsaved document modifications and replace the document's contents by reading a file or file package located by a URL, of a specified type, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be reverted. The default implementation of this method invokes [self readFromURL:absoluteURL ofType:typeName error:outError], [self setFileModificationDate:theModificationDate], [self updateChangeCount:NSChangeCleared], and, if the document has an undo manager, [[self undoManager] removeAllActions]. It also deletes autosaved contents files when they have become obsolete.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self revertToSavedFromFile:[absoluteURL path] ofType:typeName] if -revertToSavedFromFile:ofType: is overridden and the URL uses the "file:" scheme. It still invokes [self updateChangeCount:NSChangeCleared] and [[self undoManager] removeAllActions] in this situation (because the default implementation of -revertToSavedFromFile:ofType: does not; -revertDocumentToSaved: used to, but doesn't any longer).
*/
- (BOOL)revertToContentsOfURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)outError;

#endif

#pragma mark *** Simple Reading and Writing ***

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Typically you would override one of the next three methods... */

/* Set the contents of this document by reading from a file or file package located by a URL, of a specified type, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be read. The default implementation of this method just creates an NSFileWrapper and invokes [self readFromFileWrapper:theFileWrapper ofType:typeName error:outError].

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self readFromFile:[absoluteURL path] ofType:typeName] if -readFromFile:ofType: is overridden and the URL uses the "file:" scheme.
*/
- (BOOL)readFromURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)outError;

/* Set the contents of this document by reading from a file wrapper of a specified type, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be read. The default implementation of this method invokes [self readFromData:[fileWrapper regularFileContents] ofType:typeName error:outError].

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self loadFileWrapperRepresentation:fileWrapper ofType:typeName] if -loadFileWrapperRepresentation:ofType: is overridden.
*/
- (BOOL)readFromFileWrapper:(NSFileWrapper *)fileWrapper ofType:(NSString *)typeName error:(NSError **)outError;

/* Set the contents of this document by reading from data of a specified type, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be read. The default implementation of this method throws an exception because at least one of these three reading methods, or every method that may invoke -readFromURL:ofType:error: (!), must be overridden. 

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self loadDataRepresentation:data ofType:typeName] if -loadDataRepresentation:ofType: is overridden.
*/
- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError;

/* ...and also one of these. */

/* Write the contents of this document to a file or file package located by a URL, formatted to a specified type, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be written. The default implementation of this method just invokes [self fileWrapperOfType:typeName error:outError] and writes the returned file wrapper to disk.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self writeToFile:[absoluteURL path] ofType:typeName] if -writeToFile:ofType: is overridden and the URL uses the "file:" scheme.
*/
- (BOOL)writeToURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)outError;

/* Create and return a file wrapper that contains the contents of this document, formatted to a specified type, or return nil after setting *outError to an NSError that encapsulates the reason why the file wrapper could not be created. The default implementation of this method just invokes [self dataOfType:typeName], makes a file wrapper for that data, and returns the file wrapper.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self fileWrapperRepresentationOfType:typeName] if -fileWrapperRepresentationOfType: is overridden.
*/
- (NSFileWrapper *)fileWrapperOfType:(NSString *)typeName error:(NSError **)outError;

/* Create and return a data object that contains the contents of this document, formatted to a specified type, or return nil after setting *outError to an NSError that encapsulates the reason why the data object could not be created. The default implementation of this method throws an exception because at least one of these three writing methods, or -writeToURL:ofType:saveOperation:originalContentsURL:error:, must be overridden.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self dataRepresentationOfType:typeName] if -dataRepresentationOfType: is overridden.
*/
- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError;

#endif

#pragma mark *** Advanced Writing ***

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Write the contents of the document to a file or file package located by a URL, formatted to a specified type, for a particular kind of save operation, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be written. The default implementation of this method:
    1) Either creates a temporary directory in which the document writing should be done, or renames the old on-disk revision of the document, depending on what sort of save operation is being done, whether or not there's already a copy of the document on disk, and the capabilities of the file system to which writing is being done. The details of this are subject to change.
    2) Invokes -writeToURL:ofType:forSaveOperation:originalContentsURL:error:.
    3) Invokes -fileAttributesToWriteToURL:ofType:forSaveOperation:originalContentsURL: and writes the returned attributes, if any, to the file. Some attributes from the old on-disk revision of the document may be copied at the same time, if applicable.
    4) Moves the just-written file to its final location, or deletes the old on-disk revision of the document, and deletes any temporary directories, depending on the same factors listed for step 1.

For NSSaveOperation the default implementation of this method invokes -keepBackupFile to determine whether or not the old on-disk revision of the document, if there was one, should be preserved after being renamed.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self writeWithBackupToFile:[absoluteURL path] ofType:typeName saveOperation:aSaveOperation] if -writeWithBackupToFile:ofType:saveOperation: is overridden and the URL uses the "file:" scheme. The save operation used in this case will never be NSAutosaveOperation; NSSaveToOperation will be used instead.

This method is responsible for doing document writing in a way that minimizes the danger of leaving the disk to which writing is being done in an inconsistent state in the event of an application crash, system crash, hardware failure, power outage, etc. Because it does several different things, and because the things are likely to change in future releases of Mac OS X, it's probably not a good idea to override this method without invoking super (the same was true of -writeWithBackupToFile:ofType:saveOperation:).
*/
- (BOOL)writeSafelyToURL:(NSURL *)absoluteURL ofType:(NSString *)typeName forSaveOperation:(NSSaveOperationType)saveOperation error:(NSError **)outError;

/* Write the contents of the document to a file or file package located by a URL, formatted to a specified type, for a particular kind of save operation, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be written. The default implementation of this method merely invokes [self writeToURL:absoluteURL ofType:typeName error:outError]. You can override this method instead of one of the methods in the "Simple Reading and Writing" section above if your document writing machinery needs access to the on-disk representation of the document revision that is about to be overwritten. absoluteURL will often not be the same value as [self fileURL]. Other times it will not be the same as the URL for the final save destination. Likewise, absoluteOriginalContentsURL will often not be the same value as [self fileURL], though it will be nil for documents that have never been saved. It will point to nothing if the document's on-disk representation has been deleted.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self writeToFile:[absoluteURL path] ofType:typeName originalFile:[absoluteOriginalContentsURL path] saveOperation:aSaveOperation] if -writeToFile:ofType:originalFile:saveOperation: is overridden and both URLs use the "file:" scheme. The save operation used in this case will never be NSAutosaveOperation; NSSaveToOperation will be used instead.
*/
- (BOOL)writeToURL:(NSURL *)absoluteURL ofType:(NSString *)typeName forSaveOperation:(NSSaveOperationType)saveOperation originalContentsURL:(NSURL *)absoluteOriginalContentsURL error:(NSError **)outError;

/* Given that a file is being saved, return the attributes that should be written to a file or file package located by a URL, formatted to a specified type, for a particular kind of save operation. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why attributes could not be returned. The set of valid file attributes is a subset of those understood by the NSFileManager class. The default implementation of this method returns a dictionary with NSFileHFSCreatorCode and NSFileHFSTypeCode entries that have a value of 0 for NSSaveOperation, or a dictionary with an appropriate NSFileExtensionHidden entry for NSSaveAsOperation and NSSaveToOperation. You can override this method to customize the attributes that are written to document files.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self fileAttributesToWriteToFile:[absoluteURL path] ofType:typeName saveOperation:aSaveOperation] if -fileAttributesToWriteToFile:ofType:saveOperation: is overridden and the URL uses the "file:" scheme. The save operation used in this case will never be NSAutosaveOperation; NSSaveToOperation will be used instead.

-[NSDocument writeSafelyToURL:ofType:forSaveOperation:error:] automatically copies important attributes like file permissions, creation date, and Finder info from the old on-disk revision of a document to the new one during NSSaveOperations. This method is meant to be used just for attributes that need to be written for the first time, for NSSaveAsOperations and NSSaveToOperations. Actually, absoluteURL and absoluteOriginalContentsURL are passed in just for completeness; NSDocument's default implementation for instance doesn't even need to use them.
*/
- (NSDictionary *)fileAttributesToWriteToURL:(NSURL *)absoluteURL ofType:(NSString *)typeName forSaveOperation:(NSSaveOperationType)saveOperation originalContentsURL:(NSURL *)absoluteOriginalContentsURL error:(NSError **)outError;

#endif

/* Return YES if the old on-disk revision of a document that is being overwritten should be preserved during a NSSaveOperation, NO otherwise. The default implementation of this method returns NO.
*/
- (BOOL)keepBackupFile;

#pragma mark *** Saving ***

/* The action of the File menu's Save item in a document-based application. The default implementation of this method merely invokes [self saveDocumentWithDelegate:nil didSaveSelector:NULL contextInfo:NULL].
*/
- (IBAction)saveDocument:(id)sender;

/* The action of the File menu's Save As... item in a document-based application. The default implementation of this method merely invokes [self runModalSavePanelForSaveOperation:NSSaveAsOperation delegate:nil didSaveSelector:NULL contextInfo:NULL].
*/
- (IBAction)saveDocumentAs:(id)sender;

/* The action of the File menu's Export... item in a document-based application (actually, the menu item goes by different names in different applications; check the Human Interface Guidelines). The default implementation of this method merely invokes [self runModalSavePanelForSaveOperation:NSSaveToOperation delegate:nil didSaveSelector:NULL contextInfo:NULL].
*/
- (IBAction)saveDocumentTo:(id)sender;

/* If an NSSaveOperation can be performed without further user intervention (at the very least, neither -fileURL nor -fileType return nil), then save the document. Otherwise, present a save panel to the user and then save the document if the user OKs the panel. When saving is completed or has been cancelled, send the message selected by didSaveSelector to the delegate, with the contextInfo as the last argument. The method selected by didSaveSelector must have the same signature as:

    - (void)document:(NSDocument *)document didSave:(BOOL)didSaveSuccessfully contextInfo:(void *)contextInfo;

The default implementation of this method first makes sure that any editor registered using Cocoa Bindings' NSEditorRegistration informal protocol has committed its changes, then invokes [self runModalSavePanelForSaveOperation:NSSaveOperation delegate:delegate didSaveSelector:didSaveSelector contextInfo:inContextInfo] right away if a save panel must be presented. Otherwise, it may present a panel asking the user to make a decision for any of the following situations:
    1) The document's file or file package was modified by something other than the current application since it was opened or most recently saved.
    2) The document's file or file package was moved or renamed since it was opened or most recently saved.
    3) The document's file or file package was deleted or trashed since it was opened or most recently saved.
The list of conditions for which NSDocument checks is subject to change. Regardless, the default implementation of this method always invokes either -runModalSavePanelForSaveOperation:delegate:didSaveSelector:contextInfo: or -saveToURL:ofType:forSaveOperation:delegate:didSaveSelector:contextInfo: unless the user cancels one of the panels it presents.
*/
- (void)saveDocumentWithDelegate:(id)delegate didSaveSelector:(SEL)didSaveSelector contextInfo:(void *)contextInfo;

/* Present a save panel to the user, then try to save the document if the user OKs the panel. When saving is completed, regardless of success or failure, or has been cancelled, send the message selected by didSaveSelector to the delegate, with the contextInfo as the last argument. The method selected by didSaveSelector must have the same signature as:

    - (void)document:(NSDocument *)document didSave:(BOOL)didSaveSuccessfully contextInfo:(void *)contextInfo;

The default implementation of this method first makes sure that any editor registered using Cocoa Bindings' NSEditorRegistration informal protocol has committed its changes, then creates a save panel, adds a standard "file format" accessory view if there is more than one file type for the user to choose from and [self shouldRunSavePanelWithAccessoryView] returns YES, sets various attributes of the panel, invokes [self prepareSavePanel:theSavePanel] to provide an opportunity for customization, then presents the panel. If the user OKs the panel -saveToURL:ofType:forSaveOperation:delegate:didSaveSelector:contextInfo: is invoked.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self saveToFile:nil saveOperation:saveOperation delegate:delegate didSaveSelector:contextInfo:] if -saveToFile:saveOperation:delegate:didSaveSelector:contextInfo: is overridden, even if the user cancels the panel (because that's what 10.3 did).
*/
- (void)runModalSavePanelForSaveOperation:(NSSaveOperationType)saveOperation delegate:(id)delegate didSaveSelector:(SEL)didSaveSelector contextInfo:(void *)contextInfo;

/* Return YES if -runModalSavePanelForSaveOperation:delegate:didSaveSelector:contextInfo: should add NSDocument's standard file format accessory view to the save panel, NO otherwise. The default implementation of this method returns YES. You can override this method to prevent NSDocument from adding an accessory view to the save panel so that your application can add its own when -prepareSavePanel is invoked.
*/
- (BOOL)shouldRunSavePanelWithAccessoryView;

/* Given the save panel that -runModalSavePanelForSaveOperation:delegate:didSaveSelector:contextInfo: is about to present to the user, make any final changes before it is presented, and return YES for success. Return NO for failure, to cancel the save operation. The default implementation of this method just returns YES.
*/
- (BOOL)prepareSavePanel:(NSSavePanel *)savePanel;

/* Return YES if a save panel has been presented by this document and the user chose to hide the name extension of the file that was selected in that save panel, NO otherwise.
*/
- (BOOL)fileNameExtensionWasHiddenInLastRunSavePanel;

/* If a save panel has been presented by this document, and a choice of file type was presented in that panel, return the name of the file type that the user chose.
*/
- (NSString *)fileTypeFromLastRunSavePanel;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Save the contents of the document to a file or file package located by a URL, formatted to a specified type, for a particular kind of save operation. When saving is completed, regardless of success or failure, send the message selected by didSaveSelector to the delegate, with the contextInfo as the last argument. The method selected by didSaveSelector must have the same signature as:

    - (void)document:(NSDocument *)document didSave:(BOOL)didSaveSuccessfully contextInfo:(void *)contextInfo;

The default implementation of this method first makes sure that any editor registered using Cocoa Bindings' NSEditorRegistration informal protocol has committed its changes (except for autosave operations), then invokes [self saveToURL:absoluteURL ofType:typeName forSaveOperation:saveOperation error:&anError] and, if NO is returned, presents the error to the user in a document-modal panel before messaging the delegate.
*/
- (void)saveToURL:(NSURL *)absoluteURL ofType:(NSString *)typeName forSaveOperation:(NSSaveOperationType)saveOperation delegate:(id)delegate didSaveSelector:(SEL)didSaveSelector contextInfo:(void *)contextInfo;

/* Save the contents of the document to a file or file package located by a URL, formatted to a specified type, for a particular kind of save operation, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be save.

The default implementation of this method invokes [self writeSafelyToURL:absoluteURL ofType:typeName forSaveOperation:saveOperation error:outError]. If that returns YES, it also invokes some combination of -setFileModificationDate:, -setFileType:, -setFileURL:, -updateChangeCount:, and -setAutosavedContentsFileURL:, as appropriate for the kind of save operation. It also updates information that -saveDocumentWithDelegate:didSaveSelector:contextInfo: uses to check for modification, renaming, moving, deleting, and trashing of open documents, and deletes autosaved contents files when they have become obsolete. Because this method does several different things, and because the things are likely to change in future releases of Mac OS X, it's probably not a good idea to override this method without invoking super.
*/
- (BOOL)saveToURL:(NSURL *)absoluteURL ofType:(NSString *)typeName forSaveOperation:(NSSaveOperationType)saveOperation error:(NSError **)outError;

#endif

#pragma mark *** Autosaving ***

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Return YES if the document has changes that have not been autosaved, NO otherwise, as determined by the history of previous invocations of -updateChangeCount:. The default implementation of this method returns NO immediately after invocation of -updateChangeCount:NSChangeCleared or -updateChangeCount:NSChangeAutosaved. It will then return YES if subsequent invocations of -updateChangeCount: have recorded a situation in which the document has changes that have not been autosaved. (-updateChangeCount:NSChangeReadOtherContents has no effect on what the default implementation of this method returns.)
*/
- (BOOL)hasUnautosavedChanges;

/* Autosave the document's contents at an appropriate location, and then send the message selected by didAutosaveSelector to the delegate, with the contextInfo as the last argument. The method selected by didAutosaveSelector must have the same signature as:

    - (void)document:(NSDocument *)document didAutosave:(BOOL)didAutosaveSuccessfully contextInfo:(void *)contextInfo;

If any error occurs while autosaving, it must be reported to the user, typically in a document-modal alert panel, before the delegate is messaged with succeeded:NO.

The default implementation of this method figures out where the autosaved document contents should go and invokes [self saveToURL:autosavedDocumentContentsURL ofType:[self autosavingFileType] forSaveOperation:NSAutosaveOperation delegate:inDelegate didSaveSelector:inDidAutosaveSelector contextInfo:inContextInfo].
*/
- (void)autosaveDocumentWithDelegate:(id)delegate didAutosaveSelector:(SEL)didAutosaveSelector contextInfo:(void *)contextInfo;

/* Return the document type that should be used for an autosave operation. The default implementation just returns [self fileType]. You can override this method and return nil in your override to completely disable autosaving of individual documents (NSDocumentController will not send -autosaveDocumentWithDelegate:didAutosaveSelector:contextInfo: to a document that has no autosaving file type.) You can also override it if your application defines a document type that is specifically designed for autosaving. For example, one that efficiently represents document contents _changes_ instead of complete document contents.
*/
- (NSString *)autosavingFileType;

/* The location of the most recently autosaved document contents. The default implementation of -setAutosavedContentsFileURL: records the URL and notifies the shared document controller that this document should be autoreopened if the application is quit or crashes before the document is saved. The default implementation of -autosavedContentsFileURL just returns whatever was stored by a previous invocation of the default implementation of -setAutosavedContentsFileURL:.
*/
- (void)setAutosavedContentsFileURL:(NSURL *)absoluteURL;
- (NSURL *)autosavedContentsFileURL;

#endif

#pragma mark *** Closing ***

/* If the document is modified, present a panel to the user informing them that the document is modified and asking if it should be saved. If the user indicates that it should be, then try to save it. When saving is completed, regardless of success or failure, or has been rejected one way or another by the user, send the message selected by shouldCloseSelector to the delegate, with the contextInfo as the last argument. If the document is not modified then just send the mesage selected by shouldCloseSelector right away. The method selected by shouldCloseSelector must have the same signature as:

    - (void)document:(NSDocument *)document shouldClose:(BOOL)shouldClose contextInfo:(void *)contextInfo;

The default implementation of this method presents a panel giving the user the choice of canceling, discarding changes, or saving. The shouldClose value passed to the delegate will be YES if the document was not modified in the first place, or the user chose to discard modifications, or chose to save and the saving was successful. NO will be passed if the user chose to cancel the operation or saving was unsuccessful. Because -saveDocumentWithDelegate:didSaveSelector:contextInfo: is used, an alert panel will be presented before the delegate is messaged if saving is attempted but does not succeed.
*/
- (void)canCloseDocumentWithDelegate:(id)delegate shouldCloseSelector:(SEL)shouldCloseSelector contextInfo:(void *)contextInfo;

/* Close the document, discarding any as-yet-unsaved modifications. The default implementation of this method first makes sure that any editor registered using Cocoa Bindings' NSEditorRegistration informal protocol has discarded its changes, then sends each of the document's window controllers a -close message and then invokes [[NSDocumentController sharedDocumentController] removeDocument:self]. This is typically the method to use to close open documents (instead of just causing them to be deallocated by some other means). Often it's appropriate to use -canCloseDocumentWithDelegate:shouldCloseSelector:contextInfo: first to give the user a chance to save modifications.
*/
- (void)close;

#pragma mark *** Printing ***

/* The action of the File menu's Page Setup... item in a document-based application. The default implementation of this method invokes [self printInfo], makes a copy of the print info object, and invokes [self runModalPageLayoutWithPrintInfo:printInfoCopy delegate:aPrivateDelegate didRunSelector:aSelectorForAPrivateMethod contextInfo:privateContextInfo]. If the user OKs the page layout panel, [self shouldChangePrintInfo:printInfoCopy] is invoked. If that returns YES, [self setPrintInfo:printInfoCopy] is invoked.
*/
- (IBAction)runPageLayout:(id)sender;

/* Present a page layout panel to the user. When the page layout panel has been dismissed, regardless of whether the user cancelled or OK'ed it, send the message selected by didRunSelector to the delegate, with the contextInfo as the last argument. The method selected by didRunSelector must have the same signature as:

    - (void)document:(NSDocument *)document didRunPageLayoutAndUserAccepted:(BOOL)userAccepted contextInfo:(void *)contextInfo;

The default implementation of this method creates a page layout panel, invokes [self preparePageLayout:thePageLayoutPanel] to provide an opportunity for customization, then presents the panel.
*/
- (void)runModalPageLayoutWithPrintInfo:(NSPrintInfo *)printInfo delegate:(id)delegate didRunSelector:(SEL)didRunSelector contextInfo:(void *)contextInfo;

/* Given the page layout panel that -runModalPageLayoutWithPrintInfo:delegate:didRunSelector:contextInfo: is about to present to the user, make any final changes before it is presented, and return YES for success. Return NO for failure, to cancel the presentation of the panel. The default implementation of this method just returns YES.
*/
- (BOOL)preparePageLayout:(NSPageLayout *)pageLayout;

/* Given a print info object that is the result of the user OK'ing the page layout panel presented by -runPageLayout:, return YES if the print info should be set in the document, NO otherwise.
*/
- (BOOL)shouldChangePrintInfo:(NSPrintInfo *)newPrintInfo;

/* The print info for the document. The default implementation of -setPrintInfo: records the change as an undoable change, if the document has an undo manager. If the document has no undo manager, it invokes [self updateChangeCount:NSChangeDone].
*/
- (void)setPrintInfo:(NSPrintInfo *)printInfo;
- (NSPrintInfo *)printInfo;

/* The action of the File menu's Print... item item in a document-based application. The default implementation of this method merely invokes [self printDocumentWithSettings:[NSDictionary dictionary] showPrintPanel:YES delegate:nil didPrintSelector:NULL contextInfo:NULL].
*/
- (IBAction)printDocument:(id)sender;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Print the document. If showing of the print panel is specified, present it first, and print only if the user OKs the panel. The NSPrintInfo attributes in the passed-in printSettings dictionary should be added to a copy of the document's print info, and the resulting print info should be used for the operation. When printing is completed or has been cancelled, send the message selected by didPrintSelector to the delegate, with the contextInfo as the last argument. The method selected by didPrintSelector must have the same signature as:

    - (void)document:(NSDocument *)document didPrint:(BOOL)didPrintSuccessfully contextInfo:(void *)contextInfo;

The default implementation of this method first makes sure that any editor registered using Cocoa Bindings' NSEditorRegistration informal protocol has committed its changes, then invokes [self printOperationWithSettings:printSettings error:&anError]. If nil is returned it presents the error to the user in a document-modal panel before messaging the delegate. Otherwise it invokes [thePrintOperation setShowsPrintPanel:showPrintPanel] then [self runModalPrintOperation:thePrintOperation delegate:delegate didRunSelector:didPrintSelector contextInfo:contextInfo].

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method invokes [self printShowingPrintPanel:showPrintPanel] if -printShowingPrintPanel: is overridden. When doing this it uses private functionality to arrange for 1) the print settings to take effect despite the fact that the override of -printShowingPrintPanel: can't possibly know about them, and 2) getting notified when the print operation has been completed, so it can message the delegate at the correct time. Correct messaging of the delegate is necessary for correct handling of the Print Apple event.
*/
- (void)printDocumentWithSettings:(NSDictionary *)printSettings showPrintPanel:(BOOL)showPrintPanel delegate:(id)delegate didPrintSelector:(SEL)didPrintSelector contextInfo:(void *)contextInfo;

/* Create a print operation that can be run to print the document's current contents, and return it if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why the print operation could not be created. The NSPrintInfo attributes in the passed-in printSettings dictionary should be added to a copy of the document's print info, and the resulting print info should be used for the operation. The default implementation of this method does nothing. You must override it to enable printing in your application.
*/
- (NSPrintOperation *)printOperationWithSettings:(NSDictionary *)printSettings error:(NSError **)outError;

#endif

/* Run a print operation, possibly with printing UI presented document-modally. When printing is completed, regardless of success or failure, or has been cancelled, send the message selected by didRunSelector to the delegate, with the contextInfo as the last argument. The method selected by didRunSelector must have the same signature as:

    - (void)document:(NSDocument *)document didRunPrintOperation:(BOOL)didPrintSuccessfully contextInfo:(void *)contextInfo;
*/
- (void)runModalPrintOperation:(NSPrintOperation *)printOperation delegate:(id)delegate didRunSelector:(SEL)didRunSelector contextInfo:(void *)contextInfo;

#pragma mark *** Change Management ***

/* Return YES if the document has changes that have not been saved, NO otherwise, primarily determined by the history of previous invocations of -updateChangeCount:. The default implementation of this method returns NO immediately after invocation of -updateChangeCount:NSChangeCleared. It will then return YES if subsequent invocations of -updateChangeCount: have recorded a situation in which the document has changes that have not been saved. Also, it will always return YES after invocation of -updateChangeCount:NSChangeReadOtherContents, until the next invocation of -updateChangeCount:NSChangeCleared. (-updateChangeCount:NSChangeAutosaved has no effect on what the default implementation of this method returns.) Lastly, because NSDocument implements Cooa Bindings' NSEditorRegistration informal protocol, the default implementation will return YES whenever there are registered key-value binding editors.
*/
- (BOOL)isDocumentEdited;

/* Record the fact that a change affecting the value returned by -isDocumentEdited has occurred. See the comments for NSDocumentChangeType for examples of when this method is invoked by NSDocument's own method implementations. Your application only needs to invoke this method explicitly if it is not taking advantage of NSDocument's built-in undo support. The default implementation of this method also sends all of the document's window controllers -setDocumentEdited: messages when appropriate.
*/
- (void)updateChangeCount:(NSDocumentChangeType)change;

/* The document's undo manager. The default implementation of -setUndoManager:, in addition to recording the undo manager, registers the document as an observer of various NSUndoManager notifications so that -updateChangeCount: is invoked as undoable changes are made to the document. The default implementation of -undoManager creates an undo manager if the document does not already have one and -hasUndoManager would return YES. */
- (void)setUndoManager:(NSUndoManager *)undoManager;
- (NSUndoManager *)undoManager;

/* Whether or not the document has an undo manager. The default implementation of -setHasUndoManager: releases the document's current undo manager if it has one before the invocation but is not to have one afterward. */
- (void)setHasUndoManager:(BOOL)hasUndoManager;
- (BOOL)hasUndoManager;

#pragma mark *** Error Presentation ***

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Methods that are declared by NSResponder and also implemented by NSDocument, even though for historical reasons NSDocument is not a subclass of NSResponder. NSDocument's default implementations are equivalent to NSResponder's while treating the shared NSDocumentController as the "next responder" and forwarding error presentation messages to it, despite the fact that for historical reasons NSDocumentController is not a subclass of NSResponder either.

NSWindowController has overrides of -presentError:modalForWindow:delegate:didPresentSelector:contextInfo: and -presentError: that treat the window controller's document as the "next responder" and forward these messages to it, if the window controller has a document (some do, some don't).

The default implementations of several NSDocument methods invoke -presentError:modalForWindow:delegate:didPresentSelector:contextInfo:.

You can customize the presentation of errors on a per-NSDocument-subclass basis by overriding -willPresentError:. Your override should follow the advice given for overriding of -[NSResponder willPresentError:].
*/
- (void)presentError:(NSError *)error modalForWindow:(NSWindow *)window delegate:(id)delegate didPresentSelector:(SEL)didPresentSelector contextInfo:(void *)contextInfo;
- (BOOL)presentError:(NSError *)error;
- (NSError *)willPresentError:(NSError *)error;

#endif

#pragma mark *** Windows and Window Controllers ***

/* Create the user interface for this document, but don't show it yet. The default implementation of this method invokes [self windowNibName], creates a new window controller using the resulting nib name (if it is not nil), specifying this document as the nib file's owner, and then invokes [self addWindowController:theNewWindowController] to attach it. You can override this method to use a custom subclass of NSWindowController or to create more than one window controller right away. NSDocumentController invokes this method when creating or opening new documents.
*/
- (void)makeWindowControllers;

/* Return the name of the nib to be used by -makeWindowControllers. The default implementation returns nil. You can override this method to return the name of a nib in your application's resources; the class of the file's owner in that nib must match the class of this object, and the window outlet of the file's owner should be connected to a window. Virtually every subclass of NSDocument has to override either -makeWindowControllers or -windowNibName.
*/
- (NSString *)windowNibName;

/* Be notified that a window controller will or did load a nib with this document as the nib file's owner. The default implementations of these methods do nothing. You can override these methods to do additional setup during the creation of the document's user interface, especially when there's no other reason to create a custom subclass of NSWindowController, so you're not, and you're simply overriding -windowNibName instead of -makeWindowControllers.
*/
- (void)windowControllerWillLoadNib:(NSWindowController *)windowController;
- (void)windowControllerDidLoadNib:(NSWindowController *)windowController;

/* The setter for the "window" IB outlet of this class. It is invoked automatically during the loading of any nib for which this document is the file's owner, if the file's owner window outlet is connected in the nib. You should not invoke this method directly, and typically you would not override it either.
*/
- (void)setWindow:(NSWindow *)window;

/* Add or remove a window controller from this document's list of attached window controllers, and set the document of the passed-in window controller. You cannot attach a window controller to more than one document at a time. The default implementation of -addWindowController: removes the passed-in window controller from the document to which it is attached, if it is already attached to one. It also ignores redundant invocations. The default implementations of both of these methods send -setDocument: messages to the passed-in window controller (with a nil argument, in the latter case). You wouldn't typically override either of these methods. You typically invoke -addWindowController: once or more from an override of -makeWindowControllers, if you override -makeWindowControllers, and can invoke it at other times in applications that present multiple windows per document to the user.
*/
- (void)addWindowController:(NSWindowController *)windowController;
- (void)removeWindowController:(NSWindowController *)windowController;

/* Present the user interface for this document. The default implementation of this method merely sends -showWindow: messages to each of the attached window controllers. You typically would not invoke or override this method. NSDocumentController invokes this method when creating or opening new documents.
*/
- (void)showWindows;

/* Return an array of all window controllers that have been added to this document with -addWindowController: but not yet removed with -removeWindowController:.
*/
- (NSArray *)windowControllers;

/* If the window controller is one whose closing results in the document being closed too, or there is only one window controller attached to the document, do the exact same thing that -canCloseDocumentWithDelegate:shouldCloseSelector:contextInfo: would do. Otherwise send the message selected by shouldCloseSelector to the delegate, with the contextInfo as the last argument, specifying that the window controller should be closed. The method selected by shouldCloseSelector must have the same signature as:

    - (void)document:(NSDocument *)document shouldClose:(BOOL)shouldClose contextInfo:(void *)contextInfo;

The default implementation of this method sends the window controller a -shouldCloseDocument message and, if the result is YES or the current count of window controllers is one, merely invokes [self canCloseDocumentWithDelegate:delegate shouldCloseSelector:shouldCloseSelector contextInfo:contextInfo]. Otherwise it messages the delegate as described above. You can override this method, but typically you would not invoke it. NSWindow invokes this method for any window that has a window controller and a document associated with it, before sending the window delegate any -windowShouldClose: message.
*/
- (void)shouldCloseWindowController:(NSWindowController *)windowController delegate:(id)delegate shouldCloseSelector:(SEL)shouldCloseSelector contextInfo:(void *)contextInfo;

/* Returns a name for this document that is fit for presentation to the user. The default implementation of this returns the name of the last file associated with this document, taking into account whether or not the file name's extension should be hidden, or an appropriate "Untitled" string if the document has never been associated with a file. You can override this method, but overriding -[NSWindowController windowTitleForDocumentDisplayName:] is usually better, because a document's display name is used in error alerts, alerts presented during document saving, the alert that's presented when the user attempts to save a document that has unsaved changes, and save panels (as the default value of the "Save As:" field). In those places the document file's actual name really is what should be used.
*/
- (NSString *)displayName;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_1

/* Of the windows associated with this document, return the one most appropriate to use as the parent window of a document-modal sheet. This method may return nil, in which case the invoker should present an application-modal panel. NSDocument's implementation of this method returns the window of the first window controller, or nil if there are no window controllers or if the first window controller has no window.
*/
- (NSWindow *)windowForSheet;

#endif

#pragma mark *** Types ***

/* Return the names of the types for which this class can be instantiated for the application to play the Editor or Viewer role. The default implementation of this method returns information derived from the application's Info.plist. You must typically override it in document classes that are dynamically loaded from plugins. NSDocumentController uses this method when presenting an open panel and when trying to figure the NSDocument subclass to instantiate when opening a particular type of document.
*/
+ (NSArray *)readableTypes;

/* Return the names of the types which this class can save. Typically this includes types for which the application can play the Editor role, plus types than can be merely exported by the application. The default implementation of this method returns information derived from the application's Info.plist. You must typically override it in document classes that are dynamically loaded from plugins.
*/
+ (NSArray *)writableTypes;

/* Return YES if instances of this class can be instantiated for the application to play the Editor role, NO otherwise. The default implementation of this method returns information derived from the application's Info.plist. You must typically override it in document classes that are dynamically loaded from plugins. NSDocument uses this method when presenting a save panel for an NSSaveOperation or NSSaveAsOperation; in that situation all types returned by -writableTypes are presented in the standard file format popup, except the ones for which -isNativeType returns NO.
*/
+ (BOOL)isNativeType:(NSString *)type;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Return the names of the types to which this document can be saved for a kind of save operation. For every kind of save operation except NSSaveToOperation the returned array must only include types for which the the application can play the Editor role. For NSSaveToOperation the returned array may include types for which the application can only play the Viewer role, and other types that the application can merely export. The default implementation of this method returns [[self class] writableTypes] with, except during NSSaveToOperations, types for which +isNativeType returns NO filtered out.

You can override this method to limit the set of writable types when the documently currently contains data that is not representable in all types. For example, you can disallow saving to .rtf files when the document contains an attachment and can only be saved properly to .rtfd files. NSDocument uses this this method during save operations that present save panels, and during scripted save operations that do not. It may be called at additional times in future releases of Mac OS X. 

You can invoke this method when creating a custom save panel accessory view to easily present the same set of types that NSDocument would in its standard file format popup menu.
*/
- (NSArray *)writableTypesForSaveOperation:(NSSaveOperationType)saveOperation;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* For a specified type, and a particular kind of save operation, return a file name extension that can be appended to a base file name. The default implementation of this method invokes [[NSWorkspace sharedWorkspace] preferredFilenameExtensionForType:typeName] if the type is a UTI or, for backward binary compatibility with Mac OS 10.4 and earlier, invokes [[NSDocumentController sharedDocumentController] fileExtensionsFromType:typeName] and chooses the first file name extension in the returned array if not.

You can override this method to customize the appending of extensions to file names by NSDocument. In Mac OS 10.5 it's only invoked from two places within Cocoa: 1) -autosaveDocumentWithDelegate:didAutosaveSelector:contextInfo: uses this method when creating a new file name for the autosaved contents. 2) -[NSDocument(NSScripting) handleSaveScriptCommand:] uses this method when adding an extension to the file name specified by a script. In all other cases the name of any file being saved will have been fully specified by the user, with the save panel (whether they know it or not).
*/
- (NSString *)fileNameExtensionForType:(NSString *)typeName saveOperation:(NSSaveOperationType)saveOperation;

#endif

#pragma mark *** Menu Item Validation ***

/* Conformance to the NSUserInterfaceValidations protocol. NSDocument's implementation of this method conditionally enables menu items for all of the action methods listed in this header file.
*/
- (BOOL)validateUserInterfaceItem:(id <NSValidatedUserInterfaceItem>)anItem;

@end

@interface NSDocument(NSDeprecated)

#pragma mark *** Backward Compatibility ***

/* Methods that were deprecated in Mac OS 10.4. See the comments above for information about when your overrides of them are still invoked, for backward binary compatibility.
*/
- (NSData *)dataRepresentationOfType:(NSString *)type;
- (NSDictionary *)fileAttributesToWriteToFile:(NSString *)fullDocumentPath ofType:(NSString *)documentTypeName saveOperation:(NSSaveOperationType)saveOperationType;
- (NSString *)fileName;
- (NSFileWrapper *)fileWrapperRepresentationOfType:(NSString *)type;
- (id)initWithContentsOfFile:(NSString *)absolutePath ofType:(NSString *)typeName;
- (id)initWithContentsOfURL:(NSURL *)absoluteURL ofType:(NSString *)typeName;
- (BOOL)loadDataRepresentation:(NSData *)data ofType:(NSString *)type;
- (BOOL)loadFileWrapperRepresentation:(NSFileWrapper *)wrapper ofType:(NSString *)type;
- (void)printShowingPrintPanel:(BOOL)flag;
- (BOOL)readFromFile:(NSString *)fileName ofType:(NSString *)type;
- (BOOL)readFromURL:(NSURL *)url ofType:(NSString *)type;
- (BOOL)revertToSavedFromFile:(NSString *)fileName ofType:(NSString *)type;
- (BOOL)revertToSavedFromURL:(NSURL *)url ofType:(NSString *)type;
- (NSInteger)runModalPageLayoutWithPrintInfo:(NSPrintInfo *)printInfo;
- (void)saveToFile:(NSString *)fileName saveOperation:(NSSaveOperationType)saveOperation delegate:(id)delegate didSaveSelector:(SEL)didSaveSelector contextInfo:(void *)contextInfo;
- (void)setFileName:(NSString *)fileName;
- (BOOL)writeToFile:(NSString *)fileName ofType:(NSString *)type;
- (BOOL)writeToFile:(NSString *)fullDocumentPath ofType:(NSString *)documentTypeName originalFile:(NSString *)fullOriginalDocumentPath saveOperation:(NSSaveOperationType)saveOperationType;
- (BOOL)writeToURL:(NSURL *)url ofType:(NSString *)type;
- (BOOL)writeWithBackupToFile:(NSString *)fullDocumentPath ofType:(NSString *)documentTypeName saveOperation:(NSSaveOperationType)saveOperationType;

@end
