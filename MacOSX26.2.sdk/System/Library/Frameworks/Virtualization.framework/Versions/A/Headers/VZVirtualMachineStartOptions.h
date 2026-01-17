//
//  VZVirtualMachineStartOptions.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for virtual machine start options.

 @see VZMacOSVirtualMachineStartOptions
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZVirtualMachineStartOptions : NSObject

@end

NS_ASSUME_NONNULL_END
