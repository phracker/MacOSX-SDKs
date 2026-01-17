//
//  IOUSBHostDevice.h
//  IOUSBHost
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IOUSBHost/IOUSBHostObject.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class       IOUSBHostDevice
 * @brief       The IOUSBHostObject representing a USB device
 * @discussion  This class provides functionality to send control requests to the default control endpoint
 */
@interface IOUSBHostDevice : IOUSBHostObject

#pragma mark Device Dictionary helpers
/*!
 * @brief       Creates a matching dictionary for an IOUSBHostDevice to be passed into
 *              IOServiceGetMatchingService
 * @param       vendorID NSNumber representation of device vendorID
 * @param       productID NSNumber representation of device productID
 * @param       bcdDevice NSNumber representation of device release number
 * @param       deviceClass NSNumber representation of device class
 * @param       deviceSubclass NSNumber representation of device subclass
 * @param       deviceProtocol NSNumber representation of device protocol
 * @param       speed NSNumber representation of device speed
 * @param       productIDArray NSArray of NSNumbers representing all productIDs interested in.
 *              If used do not specify the NSNumber productID field
 * @return      CFMutableDictionaryRef to be used with IOService matching methods. To be released by
 *              caller.
 */
+ (CFMutableDictionaryRef)createMatchingDictionaryWithVendorID:(nullable NSNumber*)vendorID
                                                     productID:(nullable NSNumber*)productID
                                                     bcdDevice:(nullable NSNumber*)bcdDevice
                                                   deviceClass:(nullable NSNumber*)deviceClass
                                                deviceSubclass:(nullable NSNumber*)deviceSubclass
                                                deviceProtocol:(nullable NSNumber*)deviceProtocol
                                                         speed:(nullable NSNumber*)speed
                                                productIDArray:(nullable NSArray*)productIDArray NS_REFINED_FOR_SWIFT;

#pragma mark Requests
/*!
 * @brief       Select a new configuration for the device
 * @discussion  This method will select a new configuration for a device. If the device was
 *              previously configured all child interfaces will be terminated prior to setting
 *              the new configuration.  This method will send the SET_CONFIGURATION control request
 *              (USB 2.0 9.4.7) to the device. The interfaces will be registered for matching by
 *              default. After the completion of this call, the interfaces are not guaranteed
 *              to be immediately available.
 * @param       value Configuration value to select
 * @param       matchInterfaces If YES, any interfaces within the new configuration will be
 *              registered for matching. By default this is set to YES.
 * @return      YES on success, an IOReturn error code will be reported on failure.
 */
- (BOOL)configureWithValue:(NSUInteger)value
           matchInterfaces:(BOOL)matchInterfaces
                     error:(NSError* _Nullable*)error NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Select a new configuration for the device
 * @discussion  This method will select a new configuration for a device.  If the device was
 *              previously configured all child interfaces will be terminated prior to setting
 *              the new configuration.  This method will send the SET_CONFIGURATION control request
 *              (USB 2.0 9.4.7) to the device. The interfaces will be registered for matching by
 *              default. After the completion of this call, the interfaces are not guaranteed
 *              to be immediately available.
 * @param       value Configuration value to select
 * @return      YES on success, an IOReturn error code will be reported on failure.
 */
- (BOOL)configureWithValue:(NSUInteger)value
                     error:(NSError* _Nullable*)error NS_SWIFT_UNAVAILABLE("Please use the refined for Swift API");

#pragma mark Descriptors

/*!
 * @brief       Return the device descriptor
 * @discussion  This method uses descriptorWithType to retrieve the device descriptor.
 * @return      Pointer to the device descriptor, or nil if the service is terminating.
 */
@property(readonly, nullable) const IOUSBDeviceDescriptor* deviceDescriptor;

/*!
 * @brief       Return the capability descriptors of the device
 * @discussion  This method uses descriptorWithType to return the device's BOS descriptors
 * @return      Pointer to the BOS descriptor if found, otherwise nil.
 */
@property(readonly, nullable) const IOUSBBOSDescriptor* capabilityDescriptors;

/*!
 * @brief       Return the configuration descriptor at a specified index
 * @discussion  This method uses descriptorWithType to retrieve the configuration descriptor.
 * @param       index Descriptor index value
 * @return      Pointer of the configuration descriptor if found, otherwise nil. An IOReturn error
 *              code will be reported on failure.
 */
-(nullable const IOUSBConfigurationDescriptor*)configurationDescriptorWithIndex:(NSUInteger)index
                                                                          error:(NSError* _Nullable*)error;

/*!
 * @brief       Return the configuration descriptor with a specified value
 * @discussion  This method uses descriptorWithType to search for a configuration descriptor with a
 *              specific <code>bConfigurationValue</code> field.
 * @param       configurationValue Value to match
 * @return      Pointer of the configuration descriptor if found, otherwise nil. An IOReturn error
 *              code will be reported on failure.
 */
-(nullable const IOUSBConfigurationDescriptor*)configurationDescriptorWithConfigurationValue:(NSUInteger)configurationValue
                                                                                       error:(NSError* _Nullable*)error;

/*!
 * @brief       Return the currently selected configuration descriptor
 * @discussion  This method uses descriptorWithType to return the configuration descriptor currently
 *              selected after a successful setConfiguration call
 * @return      Pointer to the configuration descriptor if found, or nil if the device is not
 *              configured
 */
@property(readonly, nullable) const IOUSBConfigurationDescriptor* configurationDescriptor;

#pragma mark Miscellaneous
/*!
 * @brief       Terminate the device and attempt to reenumerate it
 * @discussion  This function will reset and attempt to reenumerate the USB device.
 *              The current IOUSBHostDevice object and all of its children will be terminated.
 *              A new IOUSBHostDevice IOService object will be created and registered if the reset
 *              is successful and the previous object has finished terminating. The framework IOUSBHostDevice
 *              will no longer have a valid connection with IOService userclient after the call returns
 *              successfully. A new framework client will need to be created to use the re-enumerated device.
 * @return      YES on success, an IOReturn error code will be reported on failure.
 */
- (BOOL)resetWithError:(NSError* _Nullable*)error;

@end

NS_ASSUME_NONNULL_END
