// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBDocuments.h
//	Copyright (c) 1995-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBEditors.h>
#import <InterfaceBuilder/IBConnectors.h>
#import <InterfaceBuilder/IBProjects.h>

// ================================================================================
//	protocol IBDocuments
// ================================================================================

@protocol IBDocuments <NSObject>

// Managing the document.

- (NSString *)documentPath;
- (void)touch;
- (BOOL)isUntitled;

// Managing the document hierarchy.

    // `attachObject:toParent:' properly handles changing parents of objects;
    // don't call detachObject: to change the parent of an object. 
- (void)attachObject:(id)object toParent:(id)parent;
- (void)attachObjects:(NSArray *)objects toParent:(id)parent;

   // `detachObject: removes objects from the object hierarchy.  All
   // references to the object in the nib file will be removed.  Doesn't
   // explicitly deallocate the objects.
- (void)detachObject:(id)object;
- (void)detachObjects:(NSArray *)objects;

- (NSArray *)objects;
- (BOOL)containsObject:(id)object;
- (id)parentOfObject:(id)object;

// Copying and pasting objects.

- (BOOL)copyObject:(id)object type:(NSString *)type
	toPasteboard:(NSPasteboard *)pasteboard;
- (BOOL)copyObjects:(NSArray *)objects type:(NSString *)type
	toPasteboard:(NSPasteboard *)pasteboard;
- (NSArray *)pasteType:(NSString *)type
	fromPasteboard:(NSPasteboard *)pasteboard parent:(id)parent;

// Setting object names.

- (void)setName:(NSString *)name forObject:(id)object;
- (NSString *)nameForObject:(id)object;
- (BOOL)containsObjectWithName:(NSString *)name forParent:(id)parent;

// Replacing objects.

- (void)replaceObject:(id)oldObject withObject:(id)newObject;

// Managing connectors.

- (void)addConnector:(id <IBConnectors>)connector;
- (void)removeConnector:(id <IBConnectors>)connector;
- (NSArray *)connectorsForSource:(id)source;
- (NSArray *)connectorsForSource:(id)source ofClass:(Class)connnectorClass;
- (NSArray *)connectorsForDestination:(id)destination;
- (NSArray *)connectorsForDestination:(id)destination
			      ofClass:(Class)connnectorClass;
- (NSArray *)allConnectors;

// Managing editors.

- (id <IBEditors>)openEditorForObject:(id)object;
- (id <IBEditors>)editorForObject:(id)object create:(BOOL)createIt;
- (id <IBEditors>)parentEditorForEditor:(id <IBEditors>)editor;
- (void)setSelectionFromEditor:(id <IBEditors>)editor;
- (void)resignSelectionForEditor:(id <IBEditors>)editor;
- (void)editor:(id <IBEditors>)editor didCloseForObject:(id)object;

// Updating the display.

- (void)drawObject:(id)object;

// Accessing the project.

- (id <IBProjects>)project;

// Interface style.
- (NSInterfaceStyle)interfaceStyle;

@end

// ================================================================================
//	Notifications
// ================================================================================
// The notification object is the document.

IB_EXTERN NSString * const IBDidOpenDocumentNotification;
IB_EXTERN NSString * const IBWillSaveDocumentNotification;
IB_EXTERN NSString * const IBDidSaveDocumentNotification;
IB_EXTERN NSString * const IBWillCloseDocumentNotification;
