//
//  VZError.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

VZ_EXPORT NSErrorDomain const VZErrorDomain API_AVAILABLE(macos(11.0));

/*!
 @enum VZErrorCode
 @abstract
    Error type returned by the Virtualization framework.
    The NSError domain is VZErrorDomain, the code is one of the VZErrorCode constants.

    The virtualization framework can also reports errors from other domains when the error originates from a lower level component.

 @constant VZErrorInternal							Internal error such as the virtual machine unexpectely stopping.
 @constant VZErrorInvalidVirtualMachineConfiguration		Invalid machine configuration.
 @constant VZErrorInvalidVirtualMachineState				API used with a machine in the wrong state (e.g. interacting with a machine before it is running).
 @constant VZErrorInvalidVirtualMachineStateTransition		Invalid change of state (e.g. pausing a virtual machine that is not started).
 @constant VZErrorInvalidDiskImage					Unrecognized disk image format or invalid disk image.
*/
typedef NS_ERROR_ENUM(VZErrorDomain, VZErrorCode) {
    VZErrorInternal NS_SWIFT_NAME(internalError) = 1,
    VZErrorInvalidVirtualMachineConfiguration = 2,
    VZErrorInvalidVirtualMachineState = 3,
    VZErrorInvalidVirtualMachineStateTransition = 4,
    VZErrorInvalidDiskImage = 5,
};
