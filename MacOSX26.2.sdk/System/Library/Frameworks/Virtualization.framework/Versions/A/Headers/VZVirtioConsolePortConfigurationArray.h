//
//  VZVirtioConsolePortConfigurationArray.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>
#import <Virtualization/VZVirtioConsolePortConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Virtio Console Port Configuration Array
 @discussion
    This array stores a collection of port configurations for a VZVirtioConsoleConfiguration. The index in the array corresponds to the port index used in the virtual machine.

    A maximumPortCount value may be set but must be larger than the highest indexed port. If no maximumPortCount value is set, the highest indexed port will be used.
 @see VZVirtioConsoleConfiguration
 @see VZVirtioConsolePortConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZVirtioConsolePortConfigurationArray : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract The maximum number of ports allocated by this device. The default is the number of ports attached to this device.
 */
@property uint32_t maximumPortCount;

/*!
 @abstract Get a port configuration at the specified index.
 */
- (nullable VZVirtioConsolePortConfiguration *)objectAtIndexedSubscript:(NSUInteger)portIndex;

/*!
 @abstract Set a port configuration at the specified index.
 */
- (void)setObject:(nullable VZVirtioConsolePortConfiguration *)configuration atIndexedSubscript:(NSUInteger)portIndex;

@end

NS_ASSUME_NONNULL_END
