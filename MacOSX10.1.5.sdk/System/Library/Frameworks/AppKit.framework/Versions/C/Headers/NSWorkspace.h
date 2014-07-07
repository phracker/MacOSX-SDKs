/*
	NSWorkspace.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

@class NSArray, NSImage, NSView, NSNotificationCenter, NSURL;

@interface NSWorkspace : NSObject {
  /*All instance variables are private*/
  @private
    NSNotificationCenter *notificationCenter;
    int deviceStatusCount;
    int applicationStatusCount;
    int _reservedWorkspace1;
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

@end

/* Notifications (through the special notification center) 
*/									// userInfo keys:
APPKIT_EXTERN NSString *NSWorkspaceDidLaunchApplicationNotification;	//	@"NSApplicationName"
APPKIT_EXTERN NSString *NSWorkspaceDidMountNotification;		//	@"NSDevicePath"
APPKIT_EXTERN NSString *NSWorkspaceDidPerformFileOperationNotification;	//	@"NSOperationNumber"
APPKIT_EXTERN NSString *NSWorkspaceDidTerminateApplicationNotification;	//	@"NSApplicationName"
APPKIT_EXTERN NSString *NSWorkspaceDidUnmountNotification;		//	@"NSDevicePath"
APPKIT_EXTERN NSString *NSWorkspaceWillLaunchApplicationNotification;	//	@"NSApplicationName"
APPKIT_EXTERN NSString *NSWorkspaceWillPowerOffNotification;
APPKIT_EXTERN NSString *NSWorkspaceWillUnmountNotification;		//	@"NSDevicePath"

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

