#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDocument.h>)
//
//  UIDocument.h
//  UIKit
//
//  Copyright (c) 1997-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIUserActivity.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIDocumentChangeKind) {
    UIDocumentChangeDone,
    UIDocumentChangeUndone,
    UIDocumentChangeRedone,
    UIDocumentChangeCleared
} API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, UIDocumentSaveOperation) {
    UIDocumentSaveForCreating,
    UIDocumentSaveForOverwriting
} API_UNAVAILABLE(tvos);

typedef NS_OPTIONS(NSUInteger, UIDocumentState) {
    UIDocumentStateNormal            = 0,
    UIDocumentStateClosed            = 1 << 0, // The document has either not been successfully opened, or has been since closed. Document properties may not be valid.
    UIDocumentStateInConflict        = 1 << 1, // Conflicts exist for the document's fileURL. They can be accessed through +[NSFileVersion unresolvedConflictVersionsOfItemAtURL:].
    UIDocumentStateSavingError       = 1 << 2, // An error has occurred that prevents the document from saving.
    UIDocumentStateEditingDisabled   = 1 << 3, // Set before calling -disableEditing. The document is is busy and it is not currently safe to allow user edits. -enableEditing will be called when it becomes safe to edit again.
    UIDocumentStateProgressAvailable = 1 << 4  // Set if the document is busy loading or saving. Progress is valid while this is set.
} API_UNAVAILABLE(tvos);

UIKIT_EXTERN NSNotificationName const UIDocumentStateChangedNotification API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);

UIKIT_EXTERN API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos) @interface UIDocument : NSObject <NSFilePresenter, NSProgressReporting>

#pragma mark *** Initialization ***

// The designated initializer. Passing an empty URL will cause this method to throw an NSInvalidArgumentException.
- (instancetype)initWithFileURL:(NSURL *)url NS_DESIGNATED_INITIALIZER API_UNAVAILABLE(tvos);

#pragma mark *** Attributes Applicable to Every Kind of Document ***
// UIKit may call these methods on background threads, so subclasses that override them must have thread safe implementations.
// These values will be set by UIKit before the completion handlers to the opening, reverting, and saving methods are called.
// Clients that wish to access these properties outside of an open, save, or revert completion handler and wait for any pending file operations should wrap the accesses in -performAsynchronousFileAccessUsingBlock:

@property (readonly) NSURL *fileURL API_UNAVAILABLE(tvos);
@property (readonly, copy) NSString *localizedName API_UNAVAILABLE(tvos);  // The default implementation derives the name from the URL. Subclasses may override to provide a custom name for presentation to the user, such as in error strings.
@property (readonly, copy, nullable) NSString *fileType API_UNAVAILABLE(tvos);       // The file's UTI. Derived from the fileURL by default.
@property (copy, nullable) NSDate *fileModificationDate API_UNAVAILABLE(tvos);       // The last known modification date of the document's on-disk representation. Updated by openWithCompletionHandler:, revertToContentsOfURL:, and saveToURL: and will return nil if none of these has completed successfully at least once.

@property (readonly) UIDocumentState documentState API_UNAVAILABLE(tvos);

@property (readonly, nullable) NSProgress *progress API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos); // The download or upload progress of a document. Valid while UIDocumentStateProgressAvailable is set.

#pragma mark *** Opening and Closing ***

// Subclassing this method without calling super should be avoided. Subclassers who don't call super must use NSFileCoordinator for coordinated reading themselves.
// Open the document located by the fileURL.  This will call readFromURL:error: on a background queue and then invoke the completionHandler on the current dispatch queue when openWithCompletionHandler: is invoked.
- (void)openWithCompletionHandler:(void (^ __nullable)(BOOL success))completionHandler API_UNAVAILABLE(tvos);

// Close the document. The default implementation calls [self autosaveWithCompletionHandler:completionHandler] which will save if [self hasUnsavedChanges] returns YES.
- (void)closeWithCompletionHandler:(void (^ __nullable)(BOOL success))completionHandler API_UNAVAILABLE(tvos);

#pragma mark *** Simple Reading and Writing ***

// These methods will be all most apps need to access files. Applications with complex reading and writing needs should see the Advanced Reading and Writing section below.

// Typical subclasses will implement this method to do reading. UIKit will pass NSData typed contents for flat files and NSFileWrapper typed contents for file packages.
// typeName is the UTI of the loaded file.
- (BOOL)loadFromContents:(id)contents ofType:(nullable NSString *)typeName error:(NSError **)outError API_UNAVAILABLE(tvos);

// Typical subclasses will implement this method and return an NSFileWrapper or NSData encapsulating a snapshot of their data to be written to disk during saving.
// Subclasses that return something other than a valid NSFileWrapper or NSData instance, or don't override this method must override one of the writing methods in the Advanced Saving section to write data to disk.
- (nullable id)contentsForType:(NSString *)typeName error:(NSError **)outError API_UNAVAILABLE(tvos);

#pragma mark *** Disabling and Enabling Editing
// Subclasses should override these methods so that they do not allow the user to edit the document between calls to -disableEditing and -enableEditing.
// UIKit will call -disableEditing when it is unsafe to make changes to the document, such as during a close or revert, and call -enableEditing when it is safe again.
// The default implementation of these methods do nothing.

- (void)disableEditing API_UNAVAILABLE(tvos);
- (void)enableEditing API_UNAVAILABLE(tvos);

#pragma mark *** Change Management ***

// The document's undo manager. Setting the undo manager also registers the document as an observer of various NSUndoManager notifications so that -updateChangeCount: is invoked as undoable changes are made to the document. 
// Asking for the undo manager creates a default one if one is not already set.
// Typically, when a subclass sets the undoManager, it does not need to override -hasUnsavedChanges or call updateChangeCount: manually.
@property (strong, null_resettable) NSUndoManager *undoManager API_UNAVAILABLE(tvos);

// Subclasses should generally not need to override this. Instead they should use the undoManager or call -updateChangeCount: every time they get a change and UIKit will calculate -hasUnsavedChanges automatically.
// The default implementation of -autosaveWithCompletionHandler: initiates a save if [self hasUnsavedChanges] is YES.
@property(nonatomic, readonly) BOOL hasUnsavedChanges API_UNAVAILABLE(tvos);

// Record the fact that a change affecting the value returned by -hasUnsavedChanges has occurred. Subclasses should not need to call this if they set the undoManager.
- (void)updateChangeCount:(UIDocumentChangeKind)change API_UNAVAILABLE(tvos);

// Change count tokens can be used to encapsulate the record of document changes being made in a particular save.
// Subclasses that don't register changes via -updateChangeCount: or by using the undoManager should implement these methods to determine if the model has new unsaved changes at the end of a save.
// -changeCountTokenForSaveOperation: is called at the beginning of a save operation and the token returned is passed to -updateChangeCountWithToken:forSaveOperation: at the conclusion of a save.
// The default implementation of updateChangeCountWithToken:forSaveOperation: calls [self updateChangeCount:UIDocumentChangeCleared] if no changes are made during the save.
- (id)changeCountTokenForSaveOperation:(UIDocumentSaveOperation)saveOperation API_UNAVAILABLE(tvos);
- (void)updateChangeCountWithToken:(id)changeCountToken forSaveOperation:(UIDocumentSaveOperation)saveOperation API_UNAVAILABLE(tvos);

#pragma mark *** Advanced Reading and Writing ***

// Subclassing this method without calling super should be avoided. Subclassers  who don't call super must use NSFileCoordinator for coordinated writing themselves.
// The default implementation of this method invokes [self contentsOfType:error:] synchronously on the calling queue, and then invokes [self writeContents:andAttributes:safelyToURL:ForSaveOperation:completionHandler:] on a background queue.
// The completion handler is executed on the calling queue.
- (void)saveToURL:(NSURL *)url forSaveOperation:(UIDocumentSaveOperation)saveOperation completionHandler:(void (^ __nullable)(BOOL success))completionHandler API_UNAVAILABLE(tvos);

// Clients should not need to call this method directly. It exists as an override point for subclasses that want to do special things with autosaving.
// The default implementation of this method invokes [self hasUnsavedChanges] and, if that returns YES, invokes [self saveToURL:[self fileURL] forSaveOperation:UIDocumentSaveForOverwriting completionHandler:completionHandler].
- (void)autosaveWithCompletionHandler:(void (^ __nullable)(BOOL success))completionHandler API_UNAVAILABLE(tvos);

@property(nonatomic, readonly, nullable) NSString *savingFileType API_UNAVAILABLE(tvos); // The default implementation returns the current file type. saveToURL: will save to an extension based on this type so subclasses can override this to allow moving the document to a new type.
- (NSString *)fileNameExtensionForType:(nullable NSString *)typeName saveOperation:(UIDocumentSaveOperation)saveOperation API_UNAVAILABLE(tvos); // For a specified type, and a particular kind of save operation, return a file name extension that can be appended to a base file name.

// This method is responsible for doing document writing in a way that minimizes the danger of leaving the disk to which writing is being done in an inconsistent state in the event of an application crash, system crash, hardware failure, power outage, etc.
// Because it does several different things, and because the things are likely to change in future releases of iOS, it's probably not a good idea to override this method without invoking super.
- (BOOL)writeContents:(id)contents andAttributes:(nullable NSDictionary *)additionalFileAttributes safelyToURL:(NSURL *)url forSaveOperation:(UIDocumentSaveOperation)saveOperation error:(NSError **)outError API_UNAVAILABLE(tvos);

// Called by -writeContents:andAttributes:safelyToURL:forSaveOperation:error: to write the data to disk. Override point for subclasses that need access to the on-disk representation of the document while saving.
- (BOOL)writeContents:(id)contents toURL:(NSURL *)url forSaveOperation:(UIDocumentSaveOperation)saveOperation originalContentsURL:(nullable NSURL *)originalContentsURL error:(NSError **)outError API_UNAVAILABLE(tvos);

// Called by -saveToURL: before executing asynchronous writing to get a dictionary of attributes understood by NSFileManager for writing to the file.
// The attributes are passed to -writeContents:andAttributes:safelyToURL:forSaveOperation:error: for writing to the file
- (nullable NSDictionary *)fileAttributesToWriteToURL:(NSURL *)url forSaveOperation:(UIDocumentSaveOperation)saveOperation error:(NSError **)outError API_UNAVAILABLE(tvos);

// Direct calls to this method should not be necessary for typical subclasses where the entire file is read during opening.
// If direct calls are used, the client must use NSFileCoordinator API to ensure coordinated reads and performAsynchronousFileAccessUsingBlock: to serialize with any active writes.
// Default implementation calls [self loadFromContents:ofType:error:] on the queue that called openWithCompletionHandler:, or the main queue if called directly, with NSData or NSFileWrapper contents.
- (BOOL)readFromURL:(NSURL *)url error:(NSError **)outError API_UNAVAILABLE(tvos);

#pragma mark *** File Access Serialization ***

// The default implementations of saveToURL: and openWithCompletionHandler: both use this to serialize file access. Direct calls to reading and writing methods should use this method to serialize file access on a background queue.
- (void)performAsynchronousFileAccessUsingBlock:(void (^)(void))block API_UNAVAILABLE(tvos);

#pragma mark *** Error Presentation ***
// These are advanced methods for dealing with errors in UIDocument.
// Most clients should not need to override or call them.
// Instead, they should respond to the UIDocumentStateChangedNotification to give the user the proper feedback when the document is in UIDocumentStateSavingError.

// Called by the default implementations of -openWithCompletionHandler: and -saveToURL:forSaveOperation:completionHandler:.
// Subclasses should call -handleError:userInteractionPermitted: with any errors that arise from direct calls to the advanced reading and writing methods that return NSErrors by indirection.
// Notes for overriding:
// 1. Subclasses that do not call super are responsible for calling -finishedHandlingError: when done with the error (i.e. when the app will not require any additional user feedback from the error).
// 2. Subclasses that do not call super are also responsible for implementing -userInteractionNoLongerPermittedForError: to wrap up error handling immediately when required.
// 3. If the userInteractionPermitted flag is NO, you should immediately handle the error and call [self finishedHandlingError:] within the context of -handleError:userInteractionPermitted:
- (void)handleError:(NSError *)error userInteractionPermitted:(BOOL)userInteractionPermitted API_UNAVAILABLE(tvos);

// Called when handling of an error (including any user interaction) is complete.
// Subclasses only need to call this method if they override -handleError:userInteractionPermitted: and do not call super.
// If overridden, subclasses must call super
- (void)finishedHandlingError:(NSError *)error recovered:(BOOL)recovered API_UNAVAILABLE(tvos);

// UIKit calls this method when it is no longer safe to proceed without immediately handling the error, such as when the app is being suspended.
// Subclasses must immediately wrap up error handling (including dismissing any interactive UI) and call [self finishedHandlingError:] before returning.
// It is only necessary to override this method if you override -handleError:userInteractionPermitted: without calling super
- (void)userInteractionNoLongerPermittedForError:(NSError *)error API_UNAVAILABLE(tvos);

#pragma mark *** Reverting ***

// Discard all unsaved document modifications and replace the document's contents by reading a file or file package located by a URL.
// Default implementation calls [self disableEditing] in the beginning and [self enableEditing] on completion to indicate that the document should not accept changes from the user while this is happening.
// The default implementation also calls [self openWithCompletionHandler:] after updating the fileURL.
// Subclasses that override this method must call super or use NSFileCoordinator directly to initiate a coordinated read.
- (void)revertToContentsOfURL:(NSURL *)url completionHandler:(void (^ __nullable)(BOOL success))completionHandler API_UNAVAILABLE(tvos);

@end

#pragma mark *** Activity Continuation ***

UIKIT_EXTERN NSString* const NSUserActivityDocumentURLKey API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos);

@interface UIDocument (ActivityContinuation) <UIUserActivityRestoring>
@property (nonatomic, strong, nullable) NSUserActivity *userActivity API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos);
- (void)updateUserActivityState:(NSUserActivity *)userActivity API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos);
- (void)restoreUserActivityState:(NSUserActivity *)userActivity API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos);
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDocument.h>
#endif
