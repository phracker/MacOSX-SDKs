/*
	NSWorkspace.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSAppleEventDescriptor.h>
#import <AppKit/AppKitDefines.h>

@class NSArray, NSImage, NSView, NSNotificationCenter, NSURL;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
typedef unsigned int NSWorkspaceLaunchOptions;
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
typedef unsigned int NSWorkspaceIconCreationOptions;
enum {
    NSExcludeQuickDrawElementsIconCreationOption    = 1 << 1,
    NSExclude10_4ElementsIconCreationOption	    = 1 << 2
};
#endif

@interface NSWorkspace : NSObject {
  /*All instance variables are private*/
  @private
    NSNotificationCenter *notificationCenter;
    int deviceStatusCount;
    int applicationStatusCount;
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
- (BOOL)setIcon:(NSImage *)image forFile:(NSString *)fullPath options:(unsigned)options;
#endif

- (BOOL)getFileSystemInfoForPath:(NSString *)fullPath isRemovable:(BOOL *)removableFlag isWritable:(BOOL *)writableFlag isUnmountable:(BOOL *)unmountableFlag description:(NSString **)description type:(NSString **)fileSystemType;

- (BOOL)performFileOperation:(NSString *)operation source:(NSString *)source destination:(NSString *)destination files:(NSArray *)files tag:(int *)tag;	/* Returned tag < 0 on failure, 0 if sync, > 0 if async */

- (BOOL)unmountAndEjectDeviceAtPath:(NSString *)path;
- (int)extendPowerOffBy:(int)requested;

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
        NSApplicationProcessIdentifier (the application's process id, as an NSNumber)
        NSApplicationProcessSerialNumberHigh (the high long of the PSN, as an NSNumber)
        NSApplicationProcessSerialNumberLow (the low long of the PSN, as an NSNumber)
   The same information will now be provided in the userInfo of the NSWorkspace notifications for application launch and termination.
*/

- (NSArray *)launchedApplications;	/* Returns an array of dictionaries, one for each running application. */
- (NSDictionary *)activeApplication;	/* Returns a dictionary with information about the current active application. */

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

