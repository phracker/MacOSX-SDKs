/*
	NSWorkspace.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSAppleEventDescriptor.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSError, NSImage, NSView, NSNotificationCenter, NSURL, NSScreen, NSRunningApplication;

typedef NS_OPTIONS(NSUInteger, NSWorkspaceLaunchOptions) {
    NSWorkspaceLaunchAndPrint                 = 0x00000002,
    NSWorkspaceLaunchWithErrorPresentation    = 0x00000040,
    NSWorkspaceLaunchInhibitingBackgroundOnly = 0x00000080,
    NSWorkspaceLaunchWithoutAddingToRecents   = 0x00000100,
    NSWorkspaceLaunchWithoutActivation        = 0x00000200,
    NSWorkspaceLaunchAsync                    = 0x00010000,
    NSWorkspaceLaunchNewInstance              = 0x00080000,
    NSWorkspaceLaunchAndHide                  = 0x00100000,
    NSWorkspaceLaunchAndHideOthers            = 0x00200000,
    NSWorkspaceLaunchDefault = NSWorkspaceLaunchAsync,

    // Deprecated options
    NSWorkspaceLaunchAllowingClassicStartup   NS_ENUM_DEPRECATED_MAC(10_3, 10_11, "The Classic environment is no longer supported.") = 0x00020000,
    NSWorkspaceLaunchPreferringClassic        NS_ENUM_DEPRECATED_MAC(10_3, 10_11, "The Classic environment is no longer supported.") = 0x00040000,
};

typedef NS_OPTIONS(NSUInteger, NSWorkspaceIconCreationOptions) {
    NSExcludeQuickDrawElementsIconCreationOption    = 1 << 1,
    NSExclude10_4ElementsIconCreationOption	    = 1 << 2
};

@interface NSWorkspace : NSObject {
  /*All instance variables are private*/
  @private
    NSNotificationCenter *notificationCenter;
#if ! __LP64__
    int deviceStatusCount;
    int applicationStatusCount;
    id _reservedWorkspace1;
#endif
}

/* Get the shared instance of NSWorkspace.  This method will create an instance of NSWorkspace if it has not been created yet.  You should not attempt to instantiate instances of NSWorkspace yourself, and you should not attempt to subclass NSWorkspace. */
+ (NSWorkspace *)sharedWorkspace;

/* Returns the NSNotificationCenter for this NSWorkspace.  All notifications in this header file must be registered on this notification center.  If you register on other notification centers, you will not receive the notifications. */
@property (readonly, strong) NSNotificationCenter *notificationCenter;

/* Open a file at some path.  If you use the variant without the withApplication: parameter, or if you pass nil for this parameter, the default application is used.  The appName parameter may be a full path to an application, or just the application's name, with or without the .app extension.  If you pass YES for andDeactivate:, or call a variant without this parameter, the calling app is deactivated before the new app is launched, so that the new app may come to the foreground unless the user switches to another application in the interim.  Passing YES for andDeactivate: is generally recommended.
 */
- (BOOL)openFile:(NSString *)fullPath;
- (BOOL)openFile:(NSString *)fullPath withApplication:(nullable NSString *)appName;
- (BOOL)openFile:(NSString *)fullPath withApplication:(nullable NSString *)appName andDeactivate:(BOOL)flag;

/* Open a URL, using the default handler for the URL's scheme. */
- (BOOL)openURL:(NSURL *)url;

/* Launches an application.  The appName may be a full path to the app, or the name alone, with or without the .app extension. */
- (BOOL)launchApplication:(NSString *)appName;

/* Launches the app at the given URL.  If the app is successfully launched, a reference to the new running app is returned.  If the app is already running, and NSWorkspaceLaunchNewInstance is not specified, then a reference to the existing app is returned.  If the app could not be launched, nil is returned and an NSError is returned by reference.

  The configuration dictionary can be used to pass additional options to the app.  Possible keys are listed later in this file (search for NSWorkspaceLaunchConfiguration). The configuration dictionary may be empty, in which case default behavior applies.
*/
- (nullable NSRunningApplication *)launchApplicationAtURL:(NSURL *)url options:(NSWorkspaceLaunchOptions)options configuration:(NSDictionary<NSString *, id> *)configuration error:(NSError **)error NS_AVAILABLE_MAC(10_6);

/* Opens the given URL in an the application that claims it. An NSRunningApplication instance representing the app that the URL was opened in is returned. If the app could not be launched or no app claims the URL, nil is returned and an NSError is returned by reference. The options and configuration parameters are the same as those in launchApplicationAtURL:options:configuration:error:. */
- (nullable NSRunningApplication *)openURL:(NSURL *)url options:(NSWorkspaceLaunchOptions)options configuration:(NSDictionary<NSString *, id> *)configuration error:(NSError **)error NS_AVAILABLE_MAC(10_10);

/* Opens the given URLs in the application at applicationURL. Returns the NSRunningApplication for the app the URLs were opened in. If the app could not be launched, nil is returned and an NSError is returned by reference. The options and configuration parameters are the same as those in launchApplicationAtURL:options:configuration:error:. */
- (nullable NSRunningApplication *)openURLs:(NSArray<NSURL *> *)urls withApplicationAtURL:(NSURL *)applicationURL options:(NSWorkspaceLaunchOptions)options configuration:(NSDictionary<NSString *, id> *)configuration error:(NSError **)error NS_AVAILABLE_MAC(10_10);

/* This currently does the same thing as launchApplication:.  Its use is discouraged. */
- (BOOL)launchApplication:(NSString *)appName showIcon:(BOOL)showIcon autolaunch:(BOOL)autolaunch;

/* Get the full path for a given application name, which may or may not have the .app extension.  This indicates the application that will be opened by methods such as launchApplication:.  If the application could not be found, returns nil. */
- (nullable NSString *)fullPathForApplication:(NSString *)appName;

/* Activate the Finder and open a window selecting the file at the given path.  If fullPath is nil, this will instead open the directory specified by rootFullPath, and not select any file. If rootFullPath is the empty string (@""), the file is selected in the main viewer. Otherwise, a new file viewer is opened.
 */
- (BOOL)selectFile:(nullable NSString *)fullPath inFileViewerRootedAtPath:(NSString *)rootFullPath;

/* Activate the Finder, and open one or more windows selecting the files at the given fileURLs. */
- (void)activateFileViewerSelectingURLs:(NSArray<NSURL *> *)fileURLs NS_AVAILABLE_MAC(10_6);

/* Displays a Spotlight search results window in Finder for the specified query string. Finder becomes the active application, if possible. The user can further refine the search via the Finder UI. Returns YES if the communication with Finder was successful.
 */
- (BOOL)showSearchResultsForQueryString:(NSString *)queryString NS_AVAILABLE_MAC(10_6);

/* noteFileSystemChanged: informs listeners of a filesystem change, using the FNNotifyByPath() API.  As the FNNotify API has been supplanted by the FSEvents API, the use of this method is discouraged. */
- (void)noteFileSystemChanged:(NSString *)path;

/* Get, by reference, the name of the app used to open a file at the given path, and the type of the file.  The type of the file will either be a filename extension or an HFS type encoded with NSFileTypeForHFSTypeCode(). Both strings are returned autoreleased.  The method returns YES if successful, NO if not. */
- (BOOL)getInfoForFile:(NSString *)fullPath application:(NSString * __nullable* __nullable)appName type:(NSString * __nullable* __nullable)type;

/* Indicates whether a given directory is a package.  Returns YES if the file is a package, NO if not, or if the file does not exist or the operation otherwise failed.  A file may be a package because its filename extension indicates so (for example, .framework) or because it has the package bit set. */
- (BOOL)isFilePackageAtPath:(NSString *)fullPath;

/* Returns the icon for a file at a given path, or a generic icon if the operation fails. */
- (NSImage *)iconForFile:(NSString *)fullPath;

/* Returns the icon for a group of files at the given paths. */
- (nullable NSImage *)iconForFiles:(NSArray<NSString *> *)fullPaths;

/* Get the icon for a given file type.  The file type may be a filename extension, or a HFS code encoded via NSFileTypeForHFSTypeCode, or a Universal Type Identifier (UTI).   Returns a default icon if the operation fails.  */
- (NSImage *)iconForFileType:(NSString *)fileType;


/* If image is not nil, this sets a custom icon for the file at the given path.  If image is nil, this removes any custom icon at the given path.  Returns YES if successful, NO if not. */
- (BOOL)setIcon:(nullable NSImage *)image forFile:(NSString *)fullPath options:(NSWorkspaceIconCreationOptions)options;

/* Get the array of file labels as NSStrings.  The file label index for a particular file is available as a property on the URL.  You may listen for NSWorkspaceDidChangeFileLabelsNotification to be notified when these change. */
@property (readonly, copy) NSArray<NSString *> *fileLabels NS_AVAILABLE_MAC(10_6);

/* Get the corresponding array of file label colors.  This array has the same number of elements as fileLabels, and the color at a given index corresponds to the label at the same index . You may listen for NSWorkspaceDidChangeFileLabelsNotification to be notified when these change. */
@property (readonly, copy) NSArray<NSColor *> *fileLabelColors NS_AVAILABLE_MAC(10_6);

/* Asynchronous file operations.  recycleURLs moves the given files to the trash, and duplicateURLs duplicates them in the same manner as the Finder.  If completionHandler is not nil, it will be called when the operation is complete, on the same dispatch queue that was used for the recycleURLs: call.  Within the completion handler, the newURLs dictionary parameter maps the given URLs to their new URLs in the Trash.  Files that could not be moved to the Trash will not be present in the dictionary.
 
If the operation succeeded for every file, the error parameter will be nil.  If it failed for one or more files, the error parameter will describe the overall result of the operation in a manner suitable for presentation to the user.  The completionHandler may be nil if you are not interested in the results.
 
 These methods may show a progress indicator, or other user interface elements, at AppKit's discretion.  In Mac OS X 10.6, these methods require that the main run loop be run in a common mode.
*/
- (void)recycleURLs:(NSArray<NSURL *> *)URLs completionHandler:(void (^ __nullable)(NSDictionary<NSURL *, NSURL *> * newURLs, NSError * __nullable error))handler NS_AVAILABLE_MAC(10_6);
- (void)duplicateURLs:(NSArray<NSURL *> *)URLs completionHandler:(void (^ __nullable)(NSDictionary<NSURL *, NSURL *> * newURLs, NSError * __nullable error))handler NS_AVAILABLE_MAC(10_6);

/* Gets information about the filesystem.  fullPath is the path to any file or directory on the filesystem, including the filesystem's mount point.  The returned values have the following significance:
   - isRemovable: whether the filesystem is backed by removable media, such as a CD or floppy disk.
   - isWritable: whether the filesystem can be written to
   - isUnmountable: whether the filesystem can be unmounted.
   - description: typically the type of the volume or the name of the filesystem
   - the file system type, for example, 'hfs'
*/
- (BOOL)getFileSystemInfoForPath:(NSString *)fullPath isRemovable:(nullable BOOL *)removableFlag isWritable:(nullable BOOL *)writableFlag isUnmountable:(nullable BOOL *)unmountableFlag description:(NSString * __nullable * __nullable)description type:(NSString * __nullable * __nullable)fileSystemType;

/* Attempt to eject the volume mounted at the given path.  Returns YES if successful, NO if not, for example, if the volume is not ejectable. */
- (BOOL)unmountAndEjectDeviceAtPath:(NSString *)path;

/* Same as unmountAndEjectDeviceAtPath, except it takes an NSURL and returns an NSError. */
- (BOOL)unmountAndEjectDeviceAtURL:(NSURL *)url error:(NSError **)error NS_AVAILABLE_MAC(10_6);

/* extendPowerOffBy: is currently not implemented.  Do not use it. */
- (NSInteger)extendPowerOffBy:(NSInteger)requested;

/* Attempt to hide all other applications. */
- (void)hideOtherApplications;

/* Get the URL for the application with the given identifier.  This uses various heuristics in case multiple apps have the same bundle ID.  This returns nil if no app has the bundle identifier.*/
- (nullable NSURL *)URLForApplicationWithBundleIdentifier:(NSString *)bundleIdentifier NS_AVAILABLE_MAC(10_6);

/* Returns the URL to the default application that would be used to open the given URL, as if the file were double clicked in the Finder (for file URLs).  This returns nil if no app can open it, or if the file does not exist. */
- (nullable NSURL *)URLForApplicationToOpenURL:(NSURL *)url NS_AVAILABLE_MAC(10_6);

/* Get the path for the application with the given identifier.  This uses various heuristics in case multiple apps have the same bundle ID. */
- (nullable NSString *)absolutePathForAppBundleWithIdentifier:(NSString *)bundleIdentifier; 

/* The following methods launch an app with the given bundle identifier.  The descriptor describes the first AppleEvent to be sent to the process.  The launchIdentifier is currently of no significance.
If the application is already running, and NSWorkspaceLaunchNewInstance is not specified in the options, then the descriptor is delivered to the currently running app, and YES is returned.
 */
- (BOOL)launchAppWithBundleIdentifier:(NSString *)bundleIdentifier options:(NSWorkspaceLaunchOptions)options additionalEventParamDescriptor:(nullable NSAppleEventDescriptor *)descriptor launchIdentifier:(NSNumber * __nullable * __nullable)identifier;
- (BOOL)openURLs:(NSArray<NSURL *> *)urls withAppBundleIdentifier:(nullable NSString *)bundleIdentifier options:(NSWorkspaceLaunchOptions)options additionalEventParamDescriptor:(nullable NSAppleEventDescriptor *)descriptor launchIdentifiers:(NSArray<NSNumber *> * __nullable * __nullable)identifiers;



/* Gets the frontmost application, which is the application that will receive key events.  This is observable through KVO. */
@property (nullable, readonly, strong) NSRunningApplication *frontmostApplication NS_AVAILABLE_MAC(10_7);

/* Gets the menu bar owning application, which is the application that currently owns and draws the menu bar. This is observable through KVO. */
@property (nullable, readonly, strong) NSRunningApplication *menuBarOwningApplication NS_AVAILABLE_MAC(10_7);


/* Given an absolute file path, return the uniform type identifier (UTI) of the file, if one can be determined. Otherwise, return nil after setting *outError to an NSError that encapsulates the reason why the file's type could not be determined. If the file at the end of the path is a symbolic link the type of the symbolic link will be returned.

You can invoke this method to get the UTI of an existing file.  To get the UTI of a URL, use the NSURLTypeIdentifierKey file system resource key from NSURL.h.
*/
- (nullable NSString *)typeOfFile:(NSString *)absoluteFilePath error:(NSError **)outError NS_AVAILABLE_MAC(10_5);

/* Given a UTI, return a string that describes the document type and is fit to present to the user, or nil for failure.

You can invoke this method to get the name of a type that must be shown to the user, in an alert about your application's inability to handle the type, for instance.
*/
- (nullable NSString *)localizedDescriptionForType:(NSString *)typeName NS_AVAILABLE_MAC(10_5);

/* Given a UTI, return the best file name extension to use when creating a file of that type, or nil for failure.

You can invoke this method when your application has only the base name of a file that's being written and it has to append a file name extension so that the file's type can be reliably identified later on.
*/
- (nullable NSString *)preferredFilenameExtensionForType:(NSString *)typeName NS_AVAILABLE_MAC(10_5);

/* Given a file name extension and a UTI, return YES if the file name extension is a valid tag for the identified type, NO otherwise.

You can invoke this method when your application needs to check if a file name extension can be used to reliably identify the type later on. For example, NSSavePanel uses this method to validate any extension that the user types in the panel's file name field.  
*/
- (BOOL)filenameExtension:(NSString *)filenameExtension isValidForType:(NSString *)typeName NS_AVAILABLE_MAC(10_5);

/* Given two UTIs, return YES if the first "conforms to" to the second in the uniform type identifier hierarchy, NO otherwise. This method will always return YES if the two strings are equal, so you can also use it with other kinds of type name, including those declared in CFBundleTypeName Info.plist entries in apps that don't take advantage of the support for UTIs that was added to Cocoa in Mac OS 10.5.

You can invoke this method when your application must determine whether it can handle a file of a known type, returned by -typeOfFile:error: for instance.
    
Use this method instead of merely comparing UTIs for equality.
*/
- (BOOL)type:(NSString *)firstTypeName conformsToType:(NSString *)secondTypeName NS_AVAILABLE_MAC(10_5);


@end


/* Desktop images */
@interface NSWorkspace (NSDesktopImages)

/* Sets the desktop image for the given screen to the image at the given URL.  The URL must be a file URL and may not be nil.  The options dictionary may contain any of the NSWorkspaceDesktopImage keys, which control how the image is scaled on the screen.  This returns YES if the image was successfully set; otherwise, NO is returned and an error is returned by reference.

  You should normally NOT present a user interface for picking the options.  Instead, just choose appropriate defaults and allow the user to adjust them in the System Preference Pane.
 */
- (BOOL)setDesktopImageURL:(NSURL *)url forScreen:(NSScreen *)screen options:(NSDictionary<NSString *, id> *)options error:(NSError **)error NS_AVAILABLE_MAC(10_6);

/* Returns the URL for the desktop image for the given screen.
 */
- (nullable NSURL *)desktopImageURLForScreen:(NSScreen *)screen NS_AVAILABLE_MAC(10_6);

/* Returns the options dictionary for the desktop image for the given screen.
 */
- (nullable NSDictionary<NSString *, id> *)desktopImageOptionsForScreen:(NSScreen *)screen NS_AVAILABLE_MAC(10_6);

@end

/* The following keys may be specified or returned in the options dictionary for setDesktopImageURL:forScreen:options:error: and desktopImageURLForScreen:options:. */

/* The value is an NSNumber containing an NSImageScaling.  If this is not specified, NSImageScaleProportionallyUpOrDown is used.  Note: NSImageScaleProportionallyDown is not currently supported.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDesktopImageScalingKey NS_AVAILABLE_MAC(10_6);

/* The value is an NSNumber containing a BOOL, which affects the interpretation of Proportional scaling types.  A NO value will make the image fully visible, but there may be empty space on the sides or top and bottom.  A YES value will cause the image to fill the entire screen, but the image may be clipped.  If this is not specified, NO is assumed.  Non-proportional scaling types ignore this value.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDesktopImageAllowClippingKey NS_AVAILABLE_MAC(10_6);

/* The value is an NSColor, which is used to fill any empty space around the image.  If not specified, a default value is used.  Currently, only colors that use or can be converted to use NSCalibratedRGBColorSpace are supported, and any alpha value is ignored.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDesktopImageFillColorKey NS_AVAILABLE_MAC(10_6);


/* Application notifications */

/* In Mac OS X 10.6 and later, all application notifications have the following key in their userInfo.  Its value is an instance of NSRunningApplication, representing the affected app.
 */
APPKIT_EXTERN NSString * const NSWorkspaceApplicationKey NS_AVAILABLE_MAC(10_6);

APPKIT_EXTERN NSString * NSWorkspaceWillLaunchApplicationNotification;	//	see above
APPKIT_EXTERN NSString * NSWorkspaceDidLaunchApplicationNotification;	//	see above
APPKIT_EXTERN NSString * NSWorkspaceDidTerminateApplicationNotification;	//	see above
APPKIT_EXTERN NSString * const NSWorkspaceDidHideApplicationNotification NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSWorkspaceDidUnhideApplicationNotification NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSWorkspaceDidActivateApplicationNotification NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSWorkspaceDidDeactivateApplicationNotification NS_AVAILABLE_MAC(10_6);


/* Volume notifications */

/* In Mac OS X 10.6 and later, the following keys are available in the userInfo of NSWorkspaceDidMountNotification, NSWorkspaceWillUnmountNotification, NSWorkspaceDidUnmountNotification, and NSWorkspaceDidRenameVolumeNotification.
*/
APPKIT_EXTERN NSString * const NSWorkspaceVolumeLocalizedNameKey NS_AVAILABLE_MAC(10_6); //NSString containing the user-visible name of the volume
APPKIT_EXTERN NSString * const NSWorkspaceVolumeURLKey NS_AVAILABLE_MAC(10_6);  //NSURL containing the mount path of the volume

/* The following additional keys are provided in the userInfo of NSWorkspaceDidRenameVolumeNotification.
 */
APPKIT_EXTERN NSString * const NSWorkspaceVolumeOldLocalizedNameKey NS_AVAILABLE_MAC(10_6); //NSString containing the old user-visible name of the volume
APPKIT_EXTERN NSString * const NSWorkspaceVolumeOldURLKey NS_AVAILABLE_MAC(10_6);  //NSURL containing the old mount path of the volume

APPKIT_EXTERN NSString * NSWorkspaceDidMountNotification;		//	@"NSDevicePath"
APPKIT_EXTERN NSString * NSWorkspaceDidUnmountNotification;		//	@"NSDevicePath"
APPKIT_EXTERN NSString * NSWorkspaceWillUnmountNotification;		//	@"NSDevicePath"

/* NSWorkspaceDidRenameVolumeNotification is posted when a volume changes its name and/or mount path.  These typically change simultaneously, in which case only one notification is posted.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDidRenameVolumeNotification NS_AVAILABLE_MAC(10_6);


/* Power notifications */
APPKIT_EXTERN NSString * const NSWorkspaceWillPowerOffNotification;

APPKIT_EXTERN NSString * NSWorkspaceWillSleepNotification;
APPKIT_EXTERN NSString * NSWorkspaceDidWakeNotification;

APPKIT_EXTERN NSString * const NSWorkspaceScreensDidSleepNotification	NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString * const NSWorkspaceScreensDidWakeNotification	NS_AVAILABLE_MAC(10_6);

/* Session notifications */
APPKIT_EXTERN NSString * NSWorkspaceSessionDidBecomeActiveNotification;
APPKIT_EXTERN NSString * NSWorkspaceSessionDidResignActiveNotification;


/* Miscellaneous notifications */

/* NSWorkspaceDidChangeFileLabelsNotification is posted when the user changes a file label color name or the color itself.  The notification object is always NSWorkspace, and there is no user info.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDidChangeFileLabelsNotification NS_AVAILABLE_MAC(10_6);

APPKIT_EXTERN NSString * const NSWorkspaceActiveSpaceDidChangeNotification NS_AVAILABLE_MAC(10_6);


/* The following keys can be used in the configuration dictionary of the launchApplicationAtURL:, openURL:, and openURL:withApplicationAtURL: methods.  Each key is optional, and if omitted, default behavior is applied. */

APPKIT_EXTERN NSString * const NSWorkspaceLaunchConfigurationAppleEvent NS_AVAILABLE_MAC(10_6); //the first NSAppleEventDescriptor to send to the new app.  If an instance of the app is already running, this is sent to that app.
APPKIT_EXTERN NSString * const NSWorkspaceLaunchConfigurationArguments NS_AVAILABLE_MAC(10_6); //an NSArray of NSStrings, passed to the new app in the argv parameter.  Ignored if a new instance is not launched.
APPKIT_EXTERN NSString * const NSWorkspaceLaunchConfigurationEnvironment NS_AVAILABLE_MAC(10_6); //an NSDictionary, mapping NSStrings to NSStrings, containing environment variables to set for the new app.  Ignored if a new instance is not launched.
APPKIT_EXTERN NSString * const NSWorkspaceLaunchConfigurationArchitecture NS_AVAILABLE_MAC(10_6); //an NSNumber containing an NSBundleExecutableArchitecture (from NSBundle.h).  Ignored if a new instance is not launched.


/* Everything remaining in this header is deprecated and should not be used. */

@interface NSWorkspace (NSDeprecated)
- (BOOL)openTempFile:(NSString *)fullPath NS_DEPRECATED_MAC(10_0, 10_6);
- (void)findApplications NS_DEPRECATED_MAC(10_0, 10_6);
- (void)noteUserDefaultsChanged NS_DEPRECATED_MAC(10_0, 10_6);
- (void)slideImage:(NSImage *)image from:(NSPoint)fromPoint to:(NSPoint)toPoint NS_DEPRECATED_MAC(10_0, 10_6);
- (void)checkForRemovableMedia NS_DEPRECATED_MAC(10_0, 10_6);
- (void)noteFileSystemChanged NS_DEPRECATED_MAC(10_0, 10_6);
- (BOOL)fileSystemChanged NS_DEPRECATED_MAC(10_0, 10_6);
- (BOOL)userDefaultsChanged NS_DEPRECATED_MAC(10_0, 10_6);
- (nullable NSArray *)mountNewRemovableMedia NS_DEPRECATED_MAC(10_0, 10_6);


/* The following methods return information about an application as a dictionary containing as many of the following keys as are available:
 NSApplicationPath (the full path to the application, as a string)
 NSApplicationName (the application's name, as a string)
 NSApplicationBundleIdentifier (the application's bundle identifier, as a string)
 NSApplicationProcessIdentifier (the application's process id, as an NSNumber)
 NSApplicationProcessSerialNumberHigh (the high long of the PSN, as an NSNumber)
 NSApplicationProcessSerialNumberLow (the low long of the PSN, as an NSNumber)
 The same information will now be provided in the userInfo of the NSWorkspace notifications for application launch and termination.
 */

/* Get an NSDictionary representing the currently frontmost app, with the above keys.  The NSWorkspaceApplicationKey is also provided.  On Mac OS X 10.7 and later, use -frontmostApplication. */
- (nullable NSDictionary *)activeApplication NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSWorkspace frontmostApplication] instead.");

/* Get the mount paths of all volumes. Despite its name, this method returns URLs for network volumes as well. On Mac OS X 10.6 and later, use -[NSFileManager mountedVolumeURLsIncludingResourceValuesForKeys:options:] instead. */
- (nullable NSArray *)mountedLocalVolumePaths NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSFileManager mountedVolumeURLsIncludingResourceValuesForKeys:options:] instead.");

/* Get the mount paths of all volumes backed by removable media, such as DVDs. On Mac OS X 10.6 and later, use -[NSFileManager mountedVolumeURLsIncludingResourceValuesForKeys:options:] instead. */
- (nullable NSArray *)mountedRemovableMedia NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSFileManager mountedVolumeURLsIncludingResourceValuesForKeys:options:] instead.");


/* Gets an array of NSDictionaries with the above keys.  In addition, the NSWorkspaceApplicationKey is provided, and vends an instance of NSRunningApplication.  This method does not return applications that are UIElement or BackgroundOnly.  To access the entire list of running applications, use the -[NSWorkspace runningApplications] method, declared in NSRunningApplication.h.
 */
- (nullable NSArray *)launchedApplications NS_DEPRECATED_MAC(10_0, 10_7, "Use -[NSWorkspace runningApplications] instead.");

/* Open a file with an animation.  This currently does the same thing as openFile: and its use is discouraged. */
- (BOOL)openFile:(NSString *)fullPath fromImage:(nullable NSImage *)anImage at:(NSPoint)point inView:(nullable NSView *)aView NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSWorkspace openURL:] instead.");


/* Performs the given file operation, blocking until complete.  source should be the directory containing the file(s).  For operations that require a destination, such as Move and Copy, destination should be the destination directory; otherwise it should be nil.  files is an array of file names that are in the source directory.
 A value is returned by reference in the tag parameter, either 0 for success, or -1 for failure.  tag may be NULL.
 */
- (BOOL)performFileOperation:(NSString *)operation source:(NSString *)source destination:(NSString *)destination files:(NSArray *)files tag:(nullable NSInteger *)tag NS_DEPRECATED_MAC(10_0, 10_11);

@end

/* Possible values for operation in performFileOperation:...
 */
APPKIT_EXTERN NSString * NSWorkspaceMoveOperation NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSFileManager moveItemAtURL:toURL:error:] instead.");
APPKIT_EXTERN NSString * NSWorkspaceCopyOperation NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSFileManager copyItemAtURL:toURL:error:] instead.");
APPKIT_EXTERN NSString * NSWorkspaceLinkOperation NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSFileManager linkItemAtURL:toURL:error:] instead.");
APPKIT_EXTERN NSString * NSWorkspaceCompressOperation NS_DEPRECATED_MAC(10_0, 10_11, "This operation is unimplemented.");
APPKIT_EXTERN NSString * NSWorkspaceDecompressOperation NS_DEPRECATED_MAC(10_0, 10_11, "This operation is unimplemented.");
APPKIT_EXTERN NSString * NSWorkspaceEncryptOperation NS_DEPRECATED_MAC(10_0, 10_11, "This operation is unimplemented.");
APPKIT_EXTERN NSString * NSWorkspaceDecryptOperation NS_DEPRECATED_MAC(10_0, 10_11, "This operation is unimplemented.");
APPKIT_EXTERN NSString * NSWorkspaceDestroyOperation NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSFileManager removeItemAtURL:error:] instead.");
APPKIT_EXTERN NSString * NSWorkspaceRecycleOperation NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSWorkspace recycleURLs:completionHandler:] instead.");
APPKIT_EXTERN NSString * NSWorkspaceDuplicateOperation NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSWorkspace duplicateURLs:completionHandler:] instead.");

APPKIT_EXTERN NSString * NSWorkspaceDidPerformFileOperationNotification NS_DEPRECATED_MAC(10_0, 10_11);	//	@"NSOperationNumber"

APPKIT_EXTERN NSString * NSPlainFileType NS_DEPRECATED_MAC(10_0, 10_6);
APPKIT_EXTERN NSString * NSDirectoryFileType NS_DEPRECATED_MAC(10_0, 10_6);
APPKIT_EXTERN NSString * NSApplicationFileType NS_DEPRECATED_MAC(10_0, 10_6);
APPKIT_EXTERN NSString * NSFilesystemFileType NS_DEPRECATED_MAC(10_0, 10_6);
APPKIT_EXTERN NSString * NSShellCommandFileType NS_DEPRECATED_MAC(10_0, 10_6);

NS_ASSUME_NONNULL_END
