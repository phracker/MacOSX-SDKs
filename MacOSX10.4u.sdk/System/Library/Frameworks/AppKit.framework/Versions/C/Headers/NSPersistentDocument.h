/*
	NSPersistentDocument.h
	Application Kit
	Copyright (c) 2004-2005, Apple Computer, Inc.
	All rights reserved.
 */

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <AppKit/NSDocument.h>
@class NSManagedObjectModel, NSManagedObjectContext;

@interface NSPersistentDocument : NSDocument {
@private
    NSManagedObjectModel *_managedObjectModel;
    NSManagedObjectContext *_managedObjectContext;
	id _store;
    void *_reserved;
    void *_reserved2;
    void *_reserved3;
    void *_reserved4;
}

// Persistent documents always have a managed context (and a persistent store coordinator through that context).
- (NSManagedObjectContext *)managedObjectContext;
- (void)setManagedObjectContext:(NSManagedObjectContext *)managedObjectContext;

- (id)managedObjectModel;    // By default the framework will create a merged model of all models found in an application and its frameworks. Subclasses can return a specific model to use for creating persistent stores.

- (BOOL)configurePersistentStoreCoordinatorForURL:(NSURL *)url ofType:(NSString *)fileType error:(NSError **)error;    // Configures the persistent store coordinator with the appropriate stores. Subclasses can create the store to save to or load from (invoked from within the other NSDocument methods to read/write files), which gives developers the ability to load/save from/to different persistent store types (default type is XML).

- (NSString *)persistentStoreTypeForFileType:(NSString *)fileType;  // Returns the name identifying the store type to save to for the given fileType. The default implementation of this method returns information derived from the application's Info.plist. If no store type information is in the Info.plist, the default implementation returns NSXMLStoreType. See NSPersistentStoreCoordinator.h for store type information. 

- (BOOL)writeToURL:(NSURL *)absoluteURL ofType:(NSString *)typeName forSaveOperation:(NSSaveOperationType)saveOperation originalContentsURL:(NSURL *)absoluteOriginalContentsURL error:(NSError **)error; // Overridden to save the document's managed objects referenced by the managed object context. If this is the first time the document is being saved, simply pass nil as the originalContentsURL. 

- (BOOL)readFromURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)error; // Overridden to load the document's managed objects through the managed object context. 

- (BOOL)revertToContentsOfURL:(NSURL *)inAbsoluteURL ofType:(NSString *)inTypeName error:(NSError **)outError; //Overridden to clean up the managedObjectContext and controllers during a revert. 

@end

#endif
