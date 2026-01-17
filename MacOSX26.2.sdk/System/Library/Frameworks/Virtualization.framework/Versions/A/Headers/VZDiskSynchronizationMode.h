//
//  VZDiskSynchronizationMode.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

typedef NS_ENUM(NSInteger, VZDiskSynchronizationMode) {
    /*!
     Perform all synchronization operations as requested by the guest OS.

     With VZDiskSynchronizationModeFull, "flush" and "barrier" commands from the guest
     result in their counterpart synchronization commands being sent to the disk implementation.
     */
    VZDiskSynchronizationModeFull,

    /*!
     Do not synchronize the data with the permanent storage.
     This option does not guarantee data integrity if any error condition occurs such as disk full on the host,
     panic, power loss, etc.

     This mode is useful when a virtual machine is only run once to perform a task to completion or failure.
     In case of failure, the state of blocks on disk and their order is undefined.

     Using this mode may result in improved performance since no synchronization with the underlying storage is necessary.
     */
    VZDiskSynchronizationModeNone,
} API_AVAILABLE(macos(14.0));
