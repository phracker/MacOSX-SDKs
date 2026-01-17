// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBResourceManager.h
//	Copyright (c) 1996-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBDocuments.h>
#import <InterfaceBuilder/IBProjectFiles.h>

enum IBResourceLocation {
    kNibResource = 0,
    kProjectResource,
    kPaletteResource,
    kSystemResource,
    kUnknownResource
};

typedef enum IBResourceLocation IBResourceLocation;

@interface IBResourceManager : NSObject
{
    @private
    id <IBDocuments> _document;
}
+ (void)registerResourceManagerClass:(Class)managerClass;
+ (void)registerResourceManagerClass:(Class)managerClass forFrameworks:(NSArray*)frameworks;

+ (NSArray *)registeredResourceManagerClasses;
+ (NSArray *)registeredResourceManagerClassesForFramework:(NSString*)framework;

- (id)initWithDocument:(id <IBDocuments>)document;
- (id <IBDocuments>)document;
- (void)writeToDocumentPath:(NSString *)path;

- (NSArray *)supportedFrameworks;
- (NSArray *)resourceFileTypes;
- (NSArray *)resourcePasteboardTypes;
- (BOOL)acceptsResourcesFromPasteboard:(NSPasteboard *)pasteboard;
- (void)addResourcesFromPasteboard:(NSPasteboard *)pasteboard;

- (NSArray *)resourcesForObjects:(NSArray *)objects;
- (void)addResources:(NSArray *)resources;

// Some managers (like the image manager for Carbon) are read only
- (BOOL)isReadOnly;

/* Only sent if `[file fileType]' is equal to `IBProjectResourcesFileType' &
 * file extension is one of resource file types.  If you want to track
 * other project changes, you must register for the appropriate
 * notification yourself. */
- (void)project:(id <IBProjects>)project
	didAddFile:(id <IBProjectFiles>)file;
- (void)project:(id <IBProjects>)project
	didRemoveFile:(id <IBProjectFiles>)file;
- (void)project:(id <IBProjects>)project
	didChangeLocalizationOfFile:(id <IBProjectFiles>)file;

/* Called when an application posts the appropriate notification to IB's DO
 * port.  This is a convenience for the IBApplicationDidChangeFileNotification
 * below.  Only sent if the file extension of the path is one of resource
 * file types. */
- (void)application:(NSString *)applicationName
	didModifyFileAtPath:(NSString *)path;
@end

/* Notifications. */

/* Notification object is the new IBResourceManager class. */
IB_EXTERN NSString * const IBResourceManagerRegistryDidChangeNotification;
