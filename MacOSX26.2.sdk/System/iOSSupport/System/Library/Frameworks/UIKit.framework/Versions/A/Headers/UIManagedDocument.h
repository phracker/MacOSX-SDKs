#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIManagedDocument.h>)
//
//  UIManagedDocument.h
//  UIKit
//
//  Copyright (c) 2011-2018 Apple Inc.
//  All rights reserved.
//

#import <UIKit/UIDocument.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSManagedObjectModel;
@class NSManagedObjectContext;
@class NSPersistentStoreCoordinator;

UIKIT_EXTERN API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIManagedDocument : UIDocument

/* The name for the persistent store file inside the document's file wrapper.  When working with the Core Data APIs, this path component is appended to the document URL provided by the UIDocument APIs.  The default name is @"documentpersistentstore.db"
 */
@property(class, nonatomic, readonly) NSString *persistentStoreName;

/* Persistent documents always have a managed object context and a persistent store coordinator through that context.  The managed object context is required to be initialized with the concurrency type NSMainQueueConcurrencyType and it must have a parent context initialized with the concurrency type NSPrivateQueueConcurrencyType.
 */
@property (nonatomic, strong, readonly) NSManagedObjectContext *managedObjectContext;

/* Persistent documents always have a managed object model.  The default model is the union of all models in the main bundle.
 */
@property (nonatomic, strong, readonly) NSManagedObjectModel* managedObjectModel;

/* Optionally provide a collection of store options to be passed when configuring the persistent store
 */
@property (nullable, nonatomic, copy) NSDictionary *persistentStoreOptions;

/* Optionally specify a model configuration name to be passed when configuring the persistent store
 */
@property (nullable, nonatomic, copy) NSString *modelConfiguration;

/* Customize the loading or creation of a persistent store to the coordinator.
 */
- (BOOL)configurePersistentStoreCoordinatorForURL:(NSURL *)storeURL ofType:(NSString *)fileType modelConfiguration:(nullable NSString *)configuration storeOptions:(nullable NSDictionary *)storeOptions error:(NSError **)error;

/* Returns the Core Data store type string for the given document fileType. The default returns NSSQLiteStoreType. See NSPersistentStoreCoordinator.h for store type information. 
 */
- (NSString *)persistentStoreTypeForFileType:(NSString *)fileType;

/* An optional call out by readFromURL:error: to handle non-Core Data content in the document's file wrapper.  It is not necessary to call super.
 */
- (BOOL)readAdditionalContentFromURL:(NSURL *)absoluteURL error:(NSError **)error;

/* An optional call out by contentsForType:error: to handle non-Core Data content in the document's file wrapper.  The returned object will be passed to -writeAdditionalContent: It is not necessary to call super.
 */
- (nullable id)additionalContentForURL:(NSURL *)absoluteURL error:(NSError **)error;

/* An optional call out by writeContents:andAttributes:safelyToURL:forSaveOperation:error: to handle non-Core Data content in the document's file wrapper.  The Core Data content is handled by the primary UIDocument -writeContents:andAttributes:safelyToURL:forSaveOperation:error: method.  It is not necessary to call super.
 */
- (BOOL)writeAdditionalContent:(id)content toURL:(NSURL *)absoluteURL originalContentsURL:(nullable NSURL *)absoluteOriginalContentsURL error:(NSError **)error;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIManagedDocument.h>
#endif
