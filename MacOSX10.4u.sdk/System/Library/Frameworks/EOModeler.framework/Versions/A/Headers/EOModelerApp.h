// EOModelerApp.h
// Copyright (c) 1995, 1998 Apple Computer, Inc.
// All rights reserved.

#import <EOInterface/EOInterface.h>
#import <EOAccess/EOAccess.h>
#import <InterfaceBuilder/InterfaceBuilder.h>
#import <EOModeler/EODefines.h>

@class EOModelerDocument;
@class EOModelerEditor;

@protocol EOMColumnProvider
- (void)initColumn:(NSTableColumn *)col class:(Class)class name:(NSString *)name displayGroup:(EODisplayGroup *)displayGroup document:(EOModelerDocument *)doc;
@end


@interface EOModelerApp : NSApplication
{
    NSMutableArray *_documents;
    EOModelerEditor *_currentEditor;
    NSMutableDictionary *_columnsByClass;
}

- (NSArray *)allPasteboardTypes;

- (EOModelerEditor *)currentEditor;
- (void)setCurrentEditor:(EOModelerEditor *)newOwner;

// manage list of open documents
- (void)addDocument:(EOModelerDocument *)document;
- (void)removeDocument:(EOModelerDocument *)document;
- (NSArray *)documents;
- (EOModelerDocument *)activeDocument;

- (EOModelerDocument *)loadDocumentAtPath:(NSString *)path;
    // Loads new doc at given path

- (EOModelerDocument *)documentWithPath:(NSString *)path;
    // returns already loaded document with given path, or nil.

- (void)registerColumnName:(NSString *)name forClass:(Class)class provider:(id <EOMColumnProvider>)provider;
- (void)registerColumnNames:(NSArray *)names forClass:(Class)class provider:(id <EOMColumnProvider>)provider;
- (NSArray *)columnNamesForClass:(Class)class;
- (id <EOMColumnProvider>)providerForName:(NSString *)name class:(Class)class;

+ (EOModel *)modelWithPath:(NSString *)path;
    // load model with given path (creates appropriate model group)

+ (EOModel *)modelContainingFetchSpecification:(EOFetchSpecification *)fs;
+ (NSString *)nameForFetchSpecification:(EOFetchSpecification *)fs;

@end

// Typed NSApp pointer
EOMODELER_EXTERN EOModelerApp *EOMApp;

// Pasteboard type
EOMODELER_EXTERN NSString *EOMPropertyPboardType;
EOMODELER_EXTERN NSString *EOMPropertyListPboardType;


// Notifications
EOMODELER_EXTERN NSString *EOMSelectionChangedNotification;
    // This notification is sent whenever the selection has changed and the
    // inspector needs to update its contents

EOMODELER_EXTERN NSString *EOMDataSourceChanged;
    // Temporary solution to having ModelDocument pretend to be an EditingContext:
    // ModelDocuments send this notification with the data source as object when
    // objects from that datasource got changed

