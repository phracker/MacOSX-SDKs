//
//  VZVirtualMachine.h
//  Virtualization
//
//  Copyright © 2019-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZDirectorySharingDevice;
@class VZMemoryBalloonDevice;
@class VZNetworkDevice;
@class VZSocketDevice;
@class VZVirtualMachineConfiguration;
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
 @abstract Return the list of directory sharing devices configured on this virtual machine. Return an empty array if no directory sharing device is configured.
 @see VZVirtioFileSystemDeviceConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<VZDirectorySharingDevice *> *directorySharingDevices API_AVAILABLE(macos(12.0));

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
 @abstract Start a virtual machine.
 @discussion
    Start a virtual machine that is in either Stopped or Error state.
 @param completionHandler Block called after the virtual machine has been successfully started or on error.
    The error parameter passed to the block is nil if the start was successful.
 */
- (void)startWithCompletionHandler:(void (^)(NSError * _Nullable errorOrNil))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(start());

/*!
 @abstract Stop a virtual machine.
 @discussion
    Stop a virtual machine that is in either Running or Paused state.
 @param completionHandler Block called after the virtual machine has been successfully stopped or on error.
    The error parameter passed to the block is nil if the stop was successful.
 @discussion This is a destructive operation. It stops the virtual machine without giving the guest a chance to stop cleanly.
 @seealso -[VZVirtualMachine requestStopWithError:]
 */
- (void)stopWithCompletionHandler:(void (^)(NSError * _Nullable errorOrNil))completionHandler API_AVAILABLE(macos(12.0));

/*!
 @abstract Pause a virtual machine.
 @discussion
    Pause a virtual machine that is in Running state.
 @param completionHandler Block called after the virtual machine has been successfully paused or on error.
    The error parameter passed to the block is nil if the pause was successful.
 */
- (void)pauseWithCompletionHandler:(void (^)(NSError * _Nullable errorOrNil))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(pause());

/*!
 @abstract Resume a virtual machine.
 @discussion
    Resume a virtual machine that is in the Paused state.
 @param completionHandler Block called after the virtual machine has been successfully resumed or on error.
    The error parameter passed to the block is nil if the resumption was successful.
 */
- (void)resumeWithCompletionHandler:(void (^)(NSError * _Nullable errorOrNil))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(resume());

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
