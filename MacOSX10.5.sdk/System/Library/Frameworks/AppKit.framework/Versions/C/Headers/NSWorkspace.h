/*
	NSWorkspace.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSAppleEventDescriptor.h>
#import <AppKit/AppKitDefines.h>

@class NSArray, NSError, NSImage, NSView, NSNotificationCenter, NSURL;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
typedef NSUInteger NSWorkspaceLaunchOptions;
enum {
     NSWorkspaceLaunchAndPrint = 0x00000002,
     NSWorkspaceLaunchInhibitingBackgroundOnly = 0x00000080,
     NSWorkspaceLaunchWithoutAddingToRecents = 0x00000100,
     NSWorkspaceLaunchWithoutActivation = 0x00000200,
     NSWorkspaceLaunchAsync = 0x00010000,
     NSWorkspaceLaunchAllowingClassicStartup = 0x00020000,
     NSWorkspaceLaunchPreferringClassic = 0x00040000,
     NSWorkspaceLaunchNewInstance = 0x00080000,
     NSWorkspaceLaunchAndHide = 0x00100000,
     NSWorkspaceLaunchAndHideOthers = 0x00200000,
     // NSWorkspaceLaunchAndDisplayFailures
     NSWorkspaceLaunchDefault = NSWorkspaceLaunchAsync | 
NSWorkspaceLaunchAllowingClassicStartup
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
typedef NSUInteger NSWorkspaceIconCreationOptions;
enum {
    NSExcludeQuickDrawElementsIconCreationOption    = 1 << 1,
    NSExclude10_4ElementsIconCreationOption	    = 1 << 2
};
#endif

@interface NSWorkspace : NSObject {
  /*All instance variables are private*/
  @private
    NSNotificationCenter *notificationCenter;
#if ! __LP64__
    int deviceStatusCount;
    int applicationStatusCount;
#endif
    void *_reservedWorkspace1;
}

+ (NSWorkspace *)sharedWorkspace;

- (NSNotificationCenter *)notificationCenter;

- (BOOL)openFile:(NSString *)fullPath;
- (BOOL)openFile:(NSString *)fullPath withApplication:(NSString *)appName;
- (BOOL)openFile:(NSString *)fullPath withApplication:(NSString *)appName andDeactivate:(BOOL)flag;

- (BOOL)openTempFile:(NSString *)fullPath;

- (BOOL)openFile:(NSString *)fullPath fromImage:(NSImage *)anImage at:(NSPoint)point inView:(NSView *)aView;

- (BOOL)openURL:(NSURL *)url;

- (BOOL)launchApplication:(NSString *)appName;
- (BOOL)launchApplication:(NSString *)appName showIcon:(BOOL)showIcon autolaunch:(BOOL)autolaunch;
- (NSString *)fullPathForApplication:(NSString *)appName;

- (BOOL)selectFile:(NSString *)fullPath inFileViewerRootedAtPath:(NSString *)rootFullpath;

- (void)findApplications;

- (void)noteFileSystemChanged;
- (void)noteFileSystemChanged:(NSString *)path;
- (BOOL)fileSystemChanged;
- (void)noteUserDefaultsChanged;
- (BOOL)userDefaultsChanged;

- (BOOL)getInfoForFile:(NSString *)fullPath application:(NSString **)appName type:(NSString **)type;
- (BOOL)isFilePackageAtPath:(NSString *)fullPath;

- (NSImage *)iconForFile:(NSString *)fullPath;
- (NSImage *)iconForFiles:(NSArray *)fullPaths;
- (NSImage *)iconForFileType:(NSString *)fileType;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)setIcon:(NSImage *)image forFile:(NSString *)fullPath options:(NSWorkspaceIconCreationOptions)options;
#endif

- (BOOL)getFileSystemInfoForPath:(NSString *)fullPath isRemovable:(BOOL *)removableFlag isWritable:(BOOL *)writableFlag isUnmountable:(BOOL *)unmountableFlag description:(NSString **)description type:(NSString **)fileSystemType;

- (BOOL)performFileOperation:(NSString *)operation source:(NSString *)source destination:(NSString *)destination files:(NSArray *)files tag:(NSInteger *)tag;	/* Returned tag < 0 on failure, 0 if sync, > 0 if async */

- (BOOL)unmountAndEjectDeviceAtPath:(NSString *)path;
- (NSInteger)extendPowerOffBy:(NSInteger)requested;

- (void)slideImage:(NSImage *)image from:(NSPoint)fromPoint to:(NSPoint)toPoint;

- (void)hideOtherApplications;

- (NSArray *)mountedLocalVolumePaths;
- (NSArray *)mountedRemovableMedia;
- (NSArray *)mountNewRemovableMedia;
- (void)checkForRemovableMedia;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSString *)absolutePathForAppBundleWithIdentifier:(NSString *)bundleIdentifier; 
- (BOOL)launchAppWithBundleIdentifier:(NSString *)bundleIdentifier options:(NSWorkspaceLaunchOptions)options additionalEventParamDescriptor:(NSAppleEventDescriptor *)descriptor launchIdentifier:(NSNumber **)identifier;
- (BOOL)openURLs:(NSArray *)urls withAppBundleIdentifier:(NSString *)bundleIdentifier options:(NSWorkspaceLaunchOptions)options additionalEventParamDescriptor:(NSAppleEventDescriptor *)descriptor launchIdentifiers:(NSArray **)identifiers;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

/* The following methods return information about an application as a dictionary containing as many of the following keys as are available:
        NSApplicationPath (the full path to the application, as a string)
        NSApplicationName (the application's name, as a string)
        NSApplicationBundleIdentifier (the application's bundle identifier, as a string)
        NSApplicationProcessIdentifier (the application's process id, as an NSNumber)
        NSApplicationProcessSerialNumberHigh (the high long of the PSN, as an NSNumber)
        NSApplicationProcessSerialNumberLow (the low long of the PSN, as an NSNumber)
   The same information will now be provided in the userInfo of the NSWorkspace notifications for application launch and termination.
*/

- (NSArray *)launchedApplications;	/* Returns an array of dictionaries, one for each running application. */
- (NSDictionary *)activeApplication;	/* Returns a dictionary with information about the current active application. */

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Given an absolute file path, return the uniform type identifier (UTI) of the file, if one can be determined. Otherwise, return nil after setting *outError to an NSError that encapsulates the reason why the file's type could not be determined. If the file at the end of the path is a symbolic link the type of the symbolic link will be returned.

You can invoke this method to get the UTI of an existing file.
*/
- (NSString *)typeOfFile:(NSString *)absoluteFilePath error:(NSError **)outError;

/* Given a UTI, return a string that describes the document type and is fit to present to the user, or nil for failure.

You can invoke this method to get the name of a type that must be shown to the user, in an alert about your application's inability to handle the type, for instance.
*/
- (NSString *)localizedDescriptionForType:(NSString *)typeName;

/* Given a UTI, return the best file name extension to use when creating a file of that type, or nil for failure.

You can invoke this method when your application has only the base name of a file that's being written and it has to append a file name extension so that the file's type can be reliably identified later on.
*/
- (NSString *)preferredFilenameExtensionForType:(NSString *)typeName;

/* Given a file name extension and a UTI, return YES if the file name extension is a valid tag for the identified type, NO otherwise.

You can invoke this method when your application needs to check if a file name extension can be used to reliably identify the type later on. For example, NSSavePanel uses this method to validate any extension that the user types in the panel's file name field.  
*/
- (BOOL)filenameExtension:(NSString *)filenameExtension isValidForType:(NSString *)typeName;

/* Given two UTIs, return YES if the first "conforms to" to the second in the uniform type identifier hierarchy, NO otherwise. This method will always return YES if the two strings are equal, so you can also use it with other kinds of type name, including those declared in CFBundleTypeName Info.plist entries in apps that don't take advantage of the support for UTIs that was added to Cocoa in Mac OS 10.5.

You can invoke this method when your application must determine whether it can handle a file of a known type, returned by -typeOfFile:error: for instance.
    
Use this method instead of merely comparing UTIs for equality.
*/
- (BOOL)type:(NSString *)firstTypeName conformsToType:(NSString *)secondTypeName;

#endif

@end

/* Notifications (through the special notification center) 
*/									// userInfo keys:
APPKIT_EXTERN NSString *NSWorkspaceDidLaunchApplicationNotification;	//	see above
APPKIT_EXTERN NSString *NSWorkspaceDidMountNotification;		//	@"NSDevicePath"
APPKIT_EXTERN NSString *NSWorkspaceDidPerformFileOperationNotification;	//	@"NSOperationNumber"
APPKIT_EXTERN NSString *NSWorkspaceDidTerminateApplicationNotification;	//	see above
APPKIT_EXTERN NSString *NSWorkspaceDidUnmountNotification;		//	@"NSDevicePath"
APPKIT_EXTERN NSString *NSWorkspaceWillLaunchApplicationNotification;	//	see above
APPKIT_EXTERN NSString *NSWorkspaceWillPowerOffNotification;
APPKIT_EXTERN NSString *NSWorkspaceWillUnmountNotification;		//	@"NSDevicePath"

APPKIT_EXTERN NSString *NSWorkspaceWillSleepNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSWorkspaceDidWakeNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

APPKIT_EXTERN NSString *NSWorkspaceSessionDidBecomeActiveNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSWorkspaceSessionDidResignActiveNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Return values for type in getInfoForFile: 
*/
APPKIT_EXTERN NSString *NSPlainFileType, *NSDirectoryFileType, *NSApplicationFileType;
APPKIT_EXTERN NSString *NSFilesystemFileType, *NSShellCommandFileType;

/* Possible values for operation in performFileOperation:... 
*/
APPKIT_EXTERN NSString *NSWorkspaceMoveOperation;
APPKIT_EXTERN NSString *NSWorkspaceCopyOperation;
APPKIT_EXTERN NSString *NSWorkspaceLinkOperation;
APPKIT_EXTERN NSString *NSWorkspaceCompressOperation;
APPKIT_EXTERN NSString *NSWorkspaceDecompressOperation;
APPKIT_EXTERN NSString *NSWorkspaceEncryptOperation;
APPKIT_EXTERN NSString *NSWorkspaceDecryptOperation;
APPKIT_EXTERN NSString *NSWorkspaceDestroyOperation;
APPKIT_EXTERN NSString *NSWorkspaceRecycleOperation;
APPKIT_EXTERN NSString *NSWorkspaceDuplicateOperation;

