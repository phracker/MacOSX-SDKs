// EOModelerEditor.h
// Copyright (c) 1995, 1998 Apple Computer, Inc.
// All rights reserved.

#import <EOModeler/EODefines.h>
#import <EOInterface/EOInterface.h>

EOMODELER_EXTERN NSString *EOMExplorerPathViewHint;
EOMODELER_EXTERN NSString *EOMIconPathViewHint;
EOMODELER_EXTERN NSString *EOMNoPathViewHint;

@class EOModelerDocument;

@interface EOModelerEditor : NSObject
{
    EOModelerDocument *_document;
}
- initWithDocument:(EOModelerDocument *)document;

- (EOModelerDocument *)document;

// Must be implemented by subclasses:
- (void)setSelectionPath:(NSArray *)newSelection;
- (NSArray *)selectionPath;
    // An array of model objects making up the selection, starting with the 
    // EOModel. The final element of the array will itself be an array (to 
    // support multiple selection).  E.g.: (EOModel, EOEntity, EORelationship, 
    // (EOAttribute, EOAttribute)) or (EOModel, (EOEntity)).  Subclasses must 
    // override these methods or they will raise.

- (void)activate;
    // this editor should become active

- (NSArray *)selectionWithinViewedObject;
    // just the selection for the current viewed object.  E.g. in the example
    // above, this would return an array of 0 or more entities.

- (void)setSelectionWithinViewedObject:(NSArray *)newSelection;

- (void)setViewedObjectPath:(NSArray *)newPath;

- (NSArray *)viewedObjectPath;
    // Returns the path up to but not including the currently viewed object,
    // e.g. if an editor is showing all entities, viewedObjectPath returns
    // an NSArray containing the EOModel regardless of whether or not an 
    // entity is selected.

@end

@class EOModelerEmbedibleEditor;

@interface EOModelerCompoundEditor : EOModelerEditor
{
   NSMutableArray           *_editors;
   EOModelerEmbedibleEditor *_activeEditor;
   NSArray                  *_viewedObjectPath;
   NSArray                  *_selectionWithinViewedObject;
   BOOL                      _storedProceduresSelected;
}

- (EOModelerEmbedibleEditor *)activeEditor;

- (void)activateEditorWithClass:(Class)embedibleEditorClass;
   // Activates the instance of embedibleEditorClass returned by
   // embedibleEditorOfClass:.

- (void)activateEmbeddedEditor:(EOModelerEmbedibleEditor *)editor;

- (EOModelerEmbedibleEditor *)embedibleEditorOfClass:(Class) editorClass;
   // Returns an existing or newly created and registered instance of 
   // embedibleEditorClass.

- (void)registerEmbedibleEditor:(EOModelerEmbedibleEditor *)editor;

- (NSArray *)selectionPath;
    // Returns a concatenation of the viewedObjectPath and the 
    // selectionWithinViewedObject.

- (void)setSelectionPath:(NSArray *)newSelection;
    // Sets viewedObjectPath to all but the last element of the array, 
    // and the selectionWithinViewedObject to the last.

- (void)setStoredProceduresSelected:(BOOL)selected;

- (BOOL)storedProceduresSelected;
   // Returns YES if the model is the only object in the selection path
   // and the user has indicated that they want to view stored procedures
   // rather than entities (by selecting the stored procedure folder in the
   // TreeView, for instance). Returns NO otherwise.
   // Note that this method currently returns no if one or more stored procedure
   // objects are actually selected in the selection path (the caller can check for
   // that explicitly).

- (void)viewSelectedObject;
    // makes the currently selected object into the viewed object

@end

@interface EOModelerEmbedibleEditor : EOModelerEditor 
{
   EOModelerCompoundEditor *_parentEditor;
}

- initWithParentEditor:(EOModelerCompoundEditor *)parentEditor;
- (EOModelerCompoundEditor *)parentEditor;

- (void)selectionDidChange:(NSNotification *)notification;
   // Invoked when parent editor broadcasts selection change notification.
   // The default implementation simply calls [self activate] if the receiver
   // is the activeEditor.

// The following methods should be implemented by EOModelerEmbedibleEditor 
// subclasses.

- (BOOL)canSupportCurrentSelection;
   // Returns YES if the receiver is able to support the current selection
   // (as defined by the parent editor), NO otherwise.  The default 
   // implementation returns NO.

- (NSArray *)friendEditorClasses;
   // Returns an instance of NSArray containing the EOModelerEmbedibleEditor
   // classes that the receiver is friends with.  This is used to keep editing
   // in the same vein whenever possible as the selection path changes.  The
   // default implementation returns nil

- (NSView *)mainView;
   // Returns that instance of NSView which should be mapped into the 
   // parent editor when the receiver is active.  The default implementation
   // returns nil.

- (NSString *)pathViewPreferenceHint;
   // Returns a string representing the receiver's preference in path views.
   // The three currently supported hints are EOMExplorerPathViewHint, 
   // EOMIconPathViewHint and EOMNoPathViewHint.  The default implementation
   // returns EOMExplorerPathViewHint.

- (void)print;
   // Respond to the Print menu command by printing whatever is the most
   // appropriate view the editor manages.

@end
