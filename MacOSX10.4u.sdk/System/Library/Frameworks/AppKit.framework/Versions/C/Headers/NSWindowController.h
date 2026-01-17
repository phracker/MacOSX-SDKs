/*
	NSWindowController.h
	Application Kit
	Copyright (c) 1997-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSResponder.h>
#import <AppKit/NSNibDeclarations.h>

@class NSArray, NSDocument, NSWindow;

@interface NSWindowController : NSResponder <NSCoding> {
    @private
    NSWindow *_window;
    NSString *_windowNibName;
    NSDocument *_document;
    NSArray *_topLevelObjects;
    id _owner;
    struct __wcFlags {
        unsigned int shouldCloseDocument:1;
        unsigned int shouldCascade:1;
        unsigned int nibIsLoaded:1;
        unsigned int nibNameIsPath:1;
        unsigned int RESERVED:28;
    } _wcFlags;
    id _autounbinder;
    void *_reserved;
}

- (id)initWithWindow:(NSWindow *)window;
    // Designated Initializer.  window can be nil.  All other -init... methods call this, and then possibly do other setup.

- (id)initWithWindowNibName:(NSString *)windowNibName;	// self is the owner
- (id)initWithWindowNibName:(NSString *)windowNibName owner:(id)owner;
- (id)initWithWindowNibPath:(NSString *)windowNibPath owner:(id)owner;
    // Instances initialized with the "Name" methods will eventually locate their nib file in the file's owner's class' bundle or in the app's +mainBundle using standard NSBundle API.  Use the "Path" method if your nib file is at a fixed location (which is not inside one of those bundles).

// -----------------------------------------------------------------------------
// Basic properties
// -----------------------------------------------------------------------------

- (NSString *)windowNibName;
    // Returns nib name.  If -initWithWindowNibPath:owner: was used to initialize the instance, this returns the last path component with its extension stripped off.  If -initWithWindowNibName:[owner:] was used this just returns that name.
    
- (NSString *)windowNibPath;  
    // Returns full path of nib.  If -initWithWindowNibPath:owner: was used to initialize the instance, the path is just returned.  If -initWithWindowNibName:[owner:] was used this locates the nib in the file's owner's class' bundle or in the app's mainBundle and returns the full path (or nil if it cannot be located).  Subclasses can override this to augment the search behavior, but probably ought to call super first.
    
- (id)owner;
    // Returns the file's owner for the controller's nib file.  Usually this is either the controller itself or the controller's document, but, in general, it is specified by the -init... methods.

- (void)setWindowFrameAutosaveName:(NSString *)name;
- (NSString *)windowFrameAutosaveName;
    // This allows setting and accessing the autosave name for the controller's window.  If the controller has a window frame autosave name, it will automatically make sure its window gets it set appropriately whenever it gets its window set.

- (void)setShouldCascadeWindows:(BOOL)flag;
- (BOOL)shouldCascadeWindows;
    // If this is set to YES then new windows loaded from nibs (only windows from nibs) will be cascaded based on the original frame of the window from the nib.
    
// -----------------------------------------------------------------------------
// Dealing with the document
// -----------------------------------------------------------------------------

- (id)document;
    // Returns the document associated with the window controller (if any).
    
- (void)setDocument:(NSDocument *)document;
    // You should not call this.  It is invoked automatically from NSDocument's -addWindowController:.  You can override it if you need to, but call super's implementation.

- (void)setDocumentEdited:(BOOL)dirtyFlag;
    // NSDocument calls this method for its window controllers whenever the document is made dirty or clean.  By default this calls -setDocumentEdited: on the controller's window (if any).  A controller calls this on itself when its document gets set or its window gets set.

- (void)setShouldCloseDocument:(BOOL)flag;
- (BOOL)shouldCloseDocument;
    // This indicates whether closing this controller should cause the associated document to close even if the document has other open window controllers.  Normally a document will close automatically only when its last window controller closes.  See the -close method below for more info.

// -----------------------------------------------------------------------------
// Dealing with the window
// -----------------------------------------------------------------------------

- (void)setWindow:(NSWindow *)window;
    // This method is used internally from -initWithWindow: or when a controller's nib file is loaded (as the "window" outlet gets connected).  You can also call it yourself if you want to create the window for a window controller lazily, but you aren't loading it from a nib.  This can also be used to set the window to nil for cases where your subclass might not want to keep the window it loaded from a nib, but rather only wants the contents of the window.  Setting the window to nil, after the nib has been loaded, does not reset the -isWindowLoaded state.  A window controller will only load its nib file once.  This method makes sure the window does not release when closed, and it sets the controller's -windowFrameAutosaveName onto the window and updates the window's dirty state to match the controller's document (if any).  It also calls -setWindowController: on the window.  You can override this if you need to know when the window gets set, but call super.
    
- (NSWindow *)window;
    // This will load the nib file (if there is one and it has not yet been loaded) and then return the window.  If it has to load the window, it will first call -windowWillLoad, then -loadWindow, then -windowDidLoad.  To affect nib loading or do something before or after it happens, you should always override those other methods.

- (void)synchronizeWindowTitleWithDocumentName;
    // This method is invoked automatically whenever the controller's document has changed that would affect the window title.  (For instance, when the fileName of the document changes, or when the controller gets a new document.)  This method uses the -displayName method of NSDocument to find out the display name.  It then passes the display name to -windowTitleForDocumentDisplayName: to give it a chance to change it.  Finally, if the document has a -fileName and the display name is the same as the -fileName's last component, it actually sets the title from the -fileName instead of the display name.  Otherwise it sets the title from the display name.  If there is a -fileName, that file is always set as the window's represented file  The window title is left alone if the controller has no document.  This method can be overridden if you need to do something else.

- (NSString *)windowTitleForDocumentDisplayName:(NSString *)displayName;
    // This method can be overridden to modify or replace the display name computed by the document's -displayName.  If you return something other than the given display name, it will be used as-is for the window title.

- (void)close;
    // This will close the window controller.  If the controller belongs to a document and it is either the last controller for the document or -shouldCloseDocument is YES, then this will also -close the document.
    
- (IBAction)showWindow:(id)sender;
    // This will show the controller's window, if any.  If the window is a panel and the panel becomes key only if needed, this method just orders it front.  Otherwise it makes the window key and orders it front.

// -----------------------------------------------------------------------------
// Nib loading
// -----------------------------------------------------------------------------

- (BOOL)isWindowLoaded;
    // Returns YES if the receiver has loded its -windowNibName OR has no -windowNibName.  In other words, if there is no nib to load, this always returns YES.

- (void)windowDidLoad;
- (void)windowWillLoad;
    // These are called immediately before and after the controller loads its nib file.  You can subclass these but should not call them directly.  Always call super from your override.

- (void)loadWindow;
    // This method can be overridden by advanced users.  It should not be called directly (doing so will cause the window controller to be improperly set up).  Call the -window method to force loading of the nib.

@end
