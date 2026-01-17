//
//  VZVirtualMachine.h
//  Virtualization
//
//  Copyright © 2019-2025 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZConsoleDevice;
@class VZDirectorySharingDevice;
@class VZGraphicsDevice;
@class VZMemoryBalloonDevice;
@class VZNetworkDevice;
@class VZSocketDevice;
@class VZUSBController;
@class VZVirtualMachineConfiguration;
@class VZVirtualMachineStartOptions;
@protocol VZVirtualMachineDelegate;

/*!
 @abstract Execution state of the virtual machine.
*/
typedef NS_ENUM(NSInteger, VZVirtualMachineState) {
    /*! Initial state before the virtual machine is started. */
    VZVirtualMachineStateStopped,

    /*! Running virtual machine. */
    VZVirtualMachineStateRunning,

    /*! A started virtual machine is paused. This state can only be transitioned from VZVirtualMachineStatePausing. */
    VZVirtualMachineStatePaused,

    /*! The virtual machine has encountered an internal error. */
    VZVirtualMachineStateError,

    /*! The virtual machine is configuring the hardware and starting. */
    VZVirtualMachineStateStarting,

    /*! The virtual machine is being paused. This is the intermediate state between VZVirtualMachineStateRunning and VZVirtualMachineStatePaused. */
    VZVirtualMachineStatePausing,

    /*! The virtual machine is being resumed. This is the intermediate state between VZVirtualMachineStatePaused and VZVirtualMachineStateRunning. */
    VZVirtualMachineStateResuming,

    /*! The virtual machine is being stopped. This is the intermediate state between VZVirtualMachineStateRunning and VZVirtualMachineStateStop. */
    VZVirtualMachineStateStopping API_AVAILABLE(macos(12.0)),

    /*! The virtual machine is being saved. This is the intermediate state between VZVirtualMachineStatePaused and VZVirtualMachineStatePaused. */
    VZVirtualMachineStateSaving API_AVAILABLE(macos(14.0)),

    /*! The virtual machine is being restored. This is the intermediate state between VZVirtualMachineStateStopped and either VZVirtualMachineStatePaused on success or VZVirtualMachineStateStopped on failure. */
    VZVirtualMachineStateRestoring API_AVAILABLE(macos(14.0)),
} NS_SWIFT_NAME(VZVirtualMachine.State) API_AVAILABLE(macos(11.0));

/*!
 @abstract VZVirtualMachine represents the entire state of a single virtual machine.
 @discussion
    A Virtual Machine is the emulation of a complete hardware machine of the same architecture as the real hardware machine.
    When executing the Virtual Machine, the Virtualization framework uses certain hardware resources and emulates others to provide isolation
    and great performance.

    The definition of a virtual machine starts with its configuration. This is done by setting up a VZVirtualMachineConfiguration object.
    Once configured, the virtual machine can be started with [VZVirtualMachine startWithCompletionHandler:].

    To install macOS on a virtual machine, configure a new virtual machine with a suitable VZMacPlatformConfiguration, then use a VZMacOSInstaller
    to install the restore image on it.

    Creating a virtual machine using the Virtualization framework requires the app to have the "com.apple.security.virtualization" entitlement.
 @seealso VZVirtualMachineConfiguration
 @seealso VZMacOSInstaller
*/
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtualMachine : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize the virtual machine.
 @discussion
    This initializer uses the main queue to operate the virtual machine. Every call must be done on the main queue and the callbacks are invoked
    on the main queue.
 @param configuration The configuration of the virtual machine.
    The configuration must be valid. Validation can be performed at runtime with [VZVirtualMachineConfiguration validateWithError:].
    The configuration is copied by the initializer.
 */
- (instancetype)initWithConfiguration:(VZVirtualMachineConfiguration *)configuration;

/*!
 @abstract Initialize the virtual machine.
 @param configuration The configuration of the virtual machine.
    The configuration must be valid. Validation can be performed at runtime with [VZVirtualMachineConfiguration validateWithError:].
    The configuration is copied by the initializer.
 @param queue The serial queue on which the virtual machine operates.
    Every operation on the virtual machine must be done on that queue. The callbacks and delegate methods are invoked on that queue.
    If the queue is not serial, the behavior is undefined.
 */
- (instancetype)initWithConfiguration:(VZVirtualMachineConfiguration *)configuration queue:(dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The queue associated with this virtual machine.
 @discussion
    This property is a reference to the queue used to create the virtual machine.
    If no queue was passed, the default queue is the main queue.

    The property can be accessed from any queue or actor.

    Other properties or function calls on the VZVirtualMachine must happen on this queue.
    The completion handlers from the asynchronous functions are also invoked on this queue.
 */
@property (readonly, nonatomic) dispatch_queue_t queue NS_SWIFT_NONISOLATED API_AVAILABLE(macos(26.0));

/*!
 @abstract Indicate whether or not virtualization is available.
 @discussion
    If virtualization is unavailable, no VZVirtualMachineConfiguration will validate.
    The validation error of the VZVirtualMachineConfiguration provides more information about why virtualization is unavailable.
 */
@property (class, readonly, getter=isSupported) BOOL supported;

/*! @abstract Execution state of the virtual machine. */
@property (readonly) VZVirtualMachineState state;

/*! @abstract The virtual machine delegate. */
@property (nullable, weak) id <VZVirtualMachineDelegate> delegate;

/*!
 @abstract Return YES if the machine is in a state that can be started.
 @see -[VZVirtualMachine startWithCompletionHandler:].
 @see -[VZVirtualMachine state]
 */
@property (readonly) BOOL canStart;

/*!
 @abstract Return YES if the machine is in a state that can be stopped.
 @see -[VZVirtualMachine stopWithCompletionHandler:]
 @see -[VZVirtualMachine state]
 */
@property (readonly) BOOL canStop API_AVAILABLE(macos(12.0));

/*!
 @abstract Return YES if the machine is in a state that can be paused.
 @see -[VZVirtualMachine pauseWithCompletionHandler:]
 @see -[VZVirtualMachine state]
 */
@property (readonly) BOOL canPause;

/*!
 @abstract Return YES if the machine is in a state that can be resumed.
 @see -[VZVirtualMachine resumeWithCompletionHandler:]
 @see -[VZVirtualMachine state]
 */
@property (readonly) BOOL canResume;

/*!
 @abstract Returns whether the machine is in a state where the guest can be asked to stop.
 @see -[VZVirtualMachine requestStopWithError:]
 @see -[VZVirtualMachine state]
 */
@property (readonly) BOOL canRequestStop;

/*!
 @abstract Return the list of console devices configured on this virtual machine. Return an empty array if no console device is configured.
 @see VZVirtioConsoleDeviceConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<VZConsoleDevice *> *consoleDevices API_AVAILABLE(macos(13.0));

/*!
 @abstract Return the list of directory sharing devices configured on this virtual machine. Return an empty array if no directory sharing device is configured.
 @see VZVirtioFileSystemDeviceConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<VZDirectorySharingDevice *> *directorySharingDevices API_AVAILABLE(macos(12.0));

/*!
 @abstract Return the list of graphics devices configured on this virtual machine. Return an empty array if no graphics device is configured.
 @see VZGraphicsDeviceConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<VZGraphicsDevice *> *graphicsDevices API_AVAILABLE(macos(14.0));

/*!
 @abstract Return the list of memory balloon devices configured on this virtual machine. Return an empty array if no memory balloon device is configured.
 @see VZVirtioTraditionalMemoryBalloonDeviceConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<VZMemoryBalloonDevice *> *memoryBalloonDevices;

/*!
 @abstract Return the list of network devices configured on this virtual machine. Return an empty array if no network device is configured.
 @see VZVirtioNetworkDeviceConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<VZNetworkDevice *> *networkDevices API_AVAILABLE(macos(12.0));

/*!
 @abstract Return the list of socket devices configured on this virtual machine. Return an empty array if no socket device is configured.
 @see VZVirtioSocketDeviceConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<VZSocketDevice *> *socketDevices;

/*!
 @abstract Return the list of USB controllers configured on this virtual machine. Return an empty array if no USB controller is configured.
 @see VZUSBControllerConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<VZUSBController *> *usbControllers API_AVAILABLE(macos(15.0));

/*!
 @abstract Start a virtual machine.
 @discussion
    Start a virtual machine that is in either Stopped or Error state.
 @param completionHandler Block called after the virtual machine has been successfully started or on error.
    The error parameter passed to the block is nil if the start was successful.
 */
- (void)startWithCompletionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(start());

/*!
 @abstract Start a virtual machine with options.
 @discussion
    Start a virtual machine that is in either Stopped or Error state.
 @param options Options used to control how the virtual machine is started.
 @param completionHandler Block called after the virtual machine has been successfully started or on error.
    The error parameter passed to the block is nil if the start was successful.
 @seealso VZMacOSVirtualMachineStartOptions
 */
- (void)startWithOptions:(VZVirtualMachineStartOptions *)options completionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler API_AVAILABLE(macos(13.0)) NS_SWIFT_NAME(start(options:completionHandler:));

/*!
 @abstract Stop a virtual machine.
 @discussion
    Stop a virtual machine that is in either Running or Paused state.
 @param completionHandler Block called after the virtual machine has been successfully stopped or on error.
    The error parameter passed to the block is nil if the stop was successful.
 @discussion This is a destructive operation. It stops the virtual machine without giving the guest a chance to stop cleanly.
 @seealso -[VZVirtualMachine requestStopWithError:]
 */
- (void)stopWithCompletionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler API_AVAILABLE(macos(12.0));

/*!
 @abstract Pause a virtual machine.
 @discussion
    Pause a virtual machine that is in Running state.
 @param completionHandler Block called after the virtual machine has been successfully paused or on error.
    The error parameter passed to the block is nil if the pause was successful.
 */
- (void)pauseWithCompletionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(pause());

/*!
 @abstract Resume a virtual machine.
 @discussion
    Resume a virtual machine that is in the Paused state.
 @param completionHandler Block called after the virtual machine has been successfully resumed or on error.
    The error parameter passed to the block is nil if the resumption was successful.
 */
- (void)resumeWithCompletionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(resume());

#if defined(__arm64__)
/*!
 @abstract Restore a virtual machine.
 @discussion
    Restore a stopped virtual machine to a state previously saved to file through `saveMachineStateToURL:completionHandler:`.

    If the file cannot be read, or contains otherwise invalid contents, this operation will fail with a `VZErrorRestore` error.
    If the virtual machine is not in the stopped state, this operation will fail with a `VZErrorInvalidVirtualMachineStateTransition` error.
    If the virtual machine cannot be started due to an internal error, this operation will fail with a `VZErrorInternal` error.
    The `VZVirtualMachineConfiguration` must also support restoring, which can be checked with  `-[VZVirtualMachineConfiguration validateSaveRestoreSupportWithError:]`.

    If this operation fails, the virtual machine state is unchanged.
    If successful, the virtual machine is restored and placed in the paused state.
 @param saveFileURL URL to file containing saved state of a suspended virtual machine.
    The file must have been generated by `saveMachineStateToURL:completionHandler:` on the same host.
    Otherwise, this operation will fail with a `VZErrorRestore` error indicating a permission denied failure reason.

    The virtual machine must also be configured compatibly with the state contained in the file.
    If the `VZVirtualMachineConfiguration` is not compatible with the content of the file, this operation will fail with a `VZErrorRestore` error indicating an invalid argument failure reason.

    Files generated with `saveMachineStateToURL:completionHandler:` on a software version that is newer than the current version will also be rejected with an invalid argument failure reason.
    In some cases, `restoreMachineStateFromURL:completionHandler:` can fail if a software update has changed the host in a way that would be incompatible with the previous format.
    In this case, an invalid argument error will be surfaced. In most cases, the virtual machine should be restarted with `startWithCompletionHandler:`.
 @param completionHandler Block called after the virtual machine has been successfully started or on error.
    The error parameter passed to the block is nil if the restore was successful.
 @see -[VZVirtualMachineConfiguration validateSaveRestoreSupportWithError:]
 */
- (void)restoreMachineStateFromURL:(NSURL *)saveFileURL completionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler NS_SWIFT_NAME(restoreMachineStateFrom(url:completionHandler:)) API_AVAILABLE(macos(14.0));

/*!
 @abstract Save a virtual machine.
 @discussion
    Save a paused virtual machine to file.
    The contents of this file can be used later to restore the state of the paused virtual machine.

    If the virtual machine is not paused, this operation will fail with a `VZErrorInvalidVirtualMachineState` error.
    If the virtual machine cannot be saved, this operation will fail with a `VZErrorSave` error.
    The `VZVirtualMachineConfiguration` must also support saving, which can be checked with  `-[VZVirtualMachineConfiguration validateSaveRestoreSupportWithError:]`.

    If this operation fails, the virtual machine state is unchanged.
    If successful, the file is written out and the virtual machine state is unchanged.
 @param saveFileURL URL to location where the saved state of the virtual machine is to be written.
    Each file is protected by an encryption key that is tied to the host on which it is created.
 @param completionHandler Block called after the virtual machine has been successfully saved or on error.
    The error parameter passed to the block is nil if the save was successful.
 @see -[VZVirtualMachineConfiguration validateSaveRestoreSupportWithError:]
 */
- (void)saveMachineStateToURL:(NSURL *)saveFileURL completionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler NS_SWIFT_NAME(saveMachineStateTo(url:completionHandler:)) API_AVAILABLE(macos(14.0));
#endif

/*!
 @abstract Request that the guest turns itself off.
 @param error If not nil, assigned with the error if the request failed.
 @return YES if the request was made successfully.
 @discussion The -[VZVirtualMachineDelegate guestDidStopVirtualMachine:] delegate method is invoked when the guest has turned itself off.
 @seealso -[VZVirtualMachineDelegate guestDidStopVirtualMachine:].
 */
- (BOOL)requestStopWithError:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
