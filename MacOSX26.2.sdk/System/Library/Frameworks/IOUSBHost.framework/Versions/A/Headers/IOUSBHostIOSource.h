//
//  IOUSBHostIOSource.h
//  IOUSBHost
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IOUSBHost/IOUSBHostDefinitions.h>
#import <IOUSBHost/IOUSBHostInterface.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 * @class   IOUSBHostIOSource
 * @brief   The abstract class IOUSBHostPipe and IOUSBHostStream derive from.
 * @details Defines common methods that are shared between IOUSBHostPipe and IOUSBHostStream.
 */
@interface IOUSBHostIOSource : NSObject

- (instancetype)init __attribute__((unavailable("Please use copyPipe or copyStream")));

/*!
 * @brief   Retrieve the source's IOUSBHostInterface
 * @return  IOUSBHostInterface pointer that the IOSource was created from.
 */
@property(readonly) IOUSBHostInterface* hostInterface;

/*!
 * @brief   Retrieve the device's address
 * @return  Current address of the device
 */
@property(readonly) NSUInteger deviceAddress;

/*!
 * @brief   Retrieve the IOSource's endpoint address
 * @return  Current address of the endpoint
 */
@property(readonly) NSUInteger endpointAddress;

/*!
 * @struct      IOUSBHostIOSourceDescriptors
 * @brief       Encapsulates descriptors for a single endpoint
 * @discussion  The IOUSBHostIOSourceDescriptors struct is used to initialize and adjust
 *              pipes in the system. The bcdUSB member must be initialized to the USB revision
 *              supported by the device. Acceptable values are 0x0110, 0x0200, 0x0300, 0x0310. The
 *              descriptor member must always be initialized with a valid endpoint descriptor. The
 *              ssCompanionDescriptor and sspCompanionDescriptor members may be
 *              required for bcdUSB versions 0x0300 and greater, depending on device operating
 *              speed and values set in the descriptors.  See USB 3.1 § 9.5 for more information on
 *              when these descriptors may be required.
 */
typedef struct IOUSBHostIOSourceDescriptors
{
    uint16_t                                                  bcdUSB;
    IOUSBEndpointDescriptor                                   descriptor;
    IOUSBSuperSpeedEndpointCompanionDescriptor                ssCompanionDescriptor;
    IOUSBSuperSpeedPlusIsochronousEndpointCompanionDescriptor sspCompanionDescriptor;
} IOUSBHostIOSourceDescriptors;

@end

NS_ASSUME_NONNULL_END
