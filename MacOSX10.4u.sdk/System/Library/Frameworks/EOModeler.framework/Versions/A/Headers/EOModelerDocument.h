// EOModelerDocument.h
// Copyright (c) 1995, 1998 Apple Computer, Inc.
// All rights reserved.

#import <EOInterface/EOInterface.h>
#import <EOAccess/EOAccess.h>

@class EOModelerEditor;

@interface EOModelerDocument:NSObject {
   EOModel          *_model;
   EOEditingContext *_editingContext;
   NSMutableArray   *_editors;
   NSDictionary     *_userInfo;
   NSDictionary 	*_lastModDate;
}

- initWithModel:(EOModel *)model;

// Model
- (EOAdaptor *)adaptor;
- (EOModel *)model;
- (EOEditingContext *)editingContext;

- (BOOL)isDirty;
- (BOOL)prepareToSave;
    // returns NO if save should be aborted (e.g. failed consistency check)
- (NSString *)documentPath;
- (BOOL)saveToPath:(NSString *)path;
    // programmatic saveAs
- (BOOL)checkCloseDocument;
    // try to close.  Returns NO if user refuses.
- (void)activate;
    // called to make the doc active (e.g. order its main editor to front)

// Editors
- (NSArray *)editors;
- (void)addEditor:(EOModelerEditor *)editor;
- (void)closeEditor:(EOModelerEditor *)editor;
- (BOOL)checkCloseEditor:(EOModelerEditor *)editor;
    // returns NO if the editor should not be allowed to close
- (EOModelerEditor *)addDefaultEditor;
    // creates a fresh instance of the default editor and adds it

// Only works if the current currentEditor is in the document
- (void)addEntity:(id)sender;
- (void)addAttribute:(id)sender;
- (void)addRelationship:(id)sender;
- (void)addFetchSpecification:(id)sender;
- (void)addStoredProcedure:(id)sender;
- (void)addArgument:(id)sender;

// when all editors are removed, the document will close
// Target/action

- (BOOL)canFlattenSelectedAttribute;
- (void)flattenAttribute:(id)sender;
- (void)save:(id)sender;
- (void)saveAs:(id)sender;
- (void)revertToSaved:(id)sender;
- (void)close:(id)sender;
- (void)undo:(id)sender;
- (void)redo:(id)sender;

//
// Callbacks used by client consistency checking extensions
//
- (void)appendConsistencyCheckErrorText:(NSAttributedString *)errorText;
    // Use this method from notification handlers for EOMCheckConsistencyForEntity, EOMCheckConsistencyForStoredProcedure, and EOMCheckConsistencyForModel
- (void)appendConsistencyCheckSuccessText:(NSAttributedString *)successText;
    // Use this method to report the consistency checks that succeeded. This should be called when you receive the EOMCheckConsistencyEnd notification

+ (void)setDefaultEditorClass:(Class)editorClass;
+ (Class)defaultEditorClass;
    // class of editor to assign to a newly created document

- (NSDictionary *)userInfo;
- (void)setUserInfo:(NSDictionary *)dictionary;
    // Arbitrary data for any viewer to tack onto the model.
    // This state is NOT saved in the model document.

@end


// Notifications
EOMODELER_EXTERN NSString *EOMDocumentWillSaveNotification;
EOMODELER_EXTERN NSString *EOMDocumentDidSaveNotification;
EOMODELER_EXTERN NSString *EOMDocumentDidOpenNotification;
EOMODELER_EXTERN NSString *EOMDocumentDidReverseEngineerModelNotification;
EOMODELER_EXTERN NSString *EOMCheckConsistencyBeginNotification;
EOMODELER_EXTERN NSString *EOMCheckConsistencyEndNotification;
EOMODELER_EXTERN NSString *EOMCheckConsistencyForEntityNotification;
EOMODELER_EXTERN NSString *EOMCheckConsistencyForStoredProcedureNotification;
EOMODELER_EXTERN NSString *EOMCheckConsistencyForModelNotification;

// key for model object in userInfo of notifications
EOMODELER_EXTERN NSString *EOMConsistencyModelObjectKey;

// Pasteboard management methods ----------------------------------------------

@interface EOModelerDocument (PasteboardManagement)

+ (NSArray *)lastCopied;
- (void)copy:(id)sender;
- (BOOL)copy:(NSArray *)editTargets toPasteboard:(NSPasteboard *)pasteboard;
- (void)cut:(id)sender;
- (BOOL)cut:(NSArray *)editTargets toPasteboard:(NSPasteboard *)pasteboard;
- (void)delete:(id)sender;
- (void)paste:(id)sender;
- (BOOL)pasteInto:(id)editTarget fromPasteboard:(NSPasteboard *)pasteboard;
- (void)preparePasteboard:(NSPasteboard *)pasteboard forObject:(id)object;

@end

// ----------------------------------------------------------------------------





