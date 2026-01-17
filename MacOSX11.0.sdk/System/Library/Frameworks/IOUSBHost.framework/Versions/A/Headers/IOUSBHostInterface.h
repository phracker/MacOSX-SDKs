//
//  IOUSBHostInterface.h
//  IOUSBHost
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <IOUSBHost/IOUSBHostObject.h>

@class IOUSBHostPipe;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class       IOUSBHostInterface
 * @brief       The IOUSBHostObject representing a USB interface
 * @discussion  This class provides functionality to send control requests to the default control endpoint, as well as
 *              create IOUSBHostPipe objects to transfer data.
 */
@interface IOUSBHostInterface : IOUSBHostObject

#pragma mark Interface Dictionary helpers
/*!
 * @brief       Creates a matching dictionary for an IOUSBHostInterface to be passed into
 *              IOServiceGetMatchingService
 * @param       vendorID NSNumber representation of device vendorID
 * @param       productID NSNumber representation of device productID
 * @param       bcdDevice NSNumber representation of device release number
 * @param       interfaceNumber NSNumber representation of interface number
 * @param       configurationValue NSNumber representation of the device's configurationValue
 * @param       interfaceClass NSNumber representation of interface class
 * @param       interfaceSubclass NSNumber representation of interface subclass
 * @param       interfaceProtocol NSNumber representation of interface protocol
 * @param       speed NSNumber representation of device speed
 * @param       productIDArray NSArray of NSNumbers representing all productIDs interested in.
 *              If used do not specify the NSNumber productID field
 * @return      CFMutableDictionaryRef to be used with IOService matching methods. To be released
 *              by caller.
 */
+ (CFMutableDictionaryRef)createMatchingDictionaryWithVendorID:(nullable NSNumber*)vendorID
                                                     productID:(nullable NSNumber*)productID
                                                     bcdDevice:(nullable NSNumber*)bcdDevice
                                               interfaceNumber:(nullable NSNumber*)interfaceNumber
                                            configurationValue:(nullable NSNumber*)configurationValue
                                                interfaceClass:(nullable NSNumber*)interfaceClass
                                             interfaceSubclass:(nullable NSNumber*)interfaceSubclass
                                             interfaceProtocol:(nullable NSNumber*)interfaceProtocol
                                                         speed:(nullable NSNumber*)speed
                                                productIDArray:(nullable NSArray*)productIDArray NS_REFINED_FOR_SWIFT;
#pragma mark Power management

/*!
 * @brief       Retrieve the current idle suspend timeout.
 *              See @link setIdleTimeout @/link
 * @return      The amount of time after all pipes are idle to wait before
 *              suspending the device,
 */
@property(readonly) NSTimeInterval idleTimeout;

/*!
 * @brief       Sets the desired idle suspend timeout for the interface
 * @discussion  Once the interface is considered idle, it will defer electrical suspend of the
 *              device for the specified duration.
 * @param       idleTimeout The amount of time after all pipes are idle to
 *              wait before suspending the device.
 * @return      YES on success. An IOReturn error code will be reported on failure.
 */
- (BOOL)setIdleTimeout:(NSTimeInterval)idleTimeout
                 error:(NSError* _Nullable*)error;

#pragma mark Descriptors

/*!
 * @brief       Retrieve the configuration descriptor associated with this interface
 * @return      IOUSBConfigurationDescriptor pointer
 */
@property(readonly) const IOUSBConfigurationDescriptor* configurationDescriptor;

/*!
 * @brief       Retrieve the interface descriptor associated with this interface.
 * @return      IOUSBInterfaceDescriptor pointer
 */
@property(readonly) const IOUSBInterfaceDescriptor* interfaceDescriptor;

#pragma mark Alternate setting and pipe management

/*!
 * @brief       Select an alternate setting for this interface
 * @discussion  This method is used to select an alternate setting for the interface. All pending IO
 *              on the interface's pipes will be aborted, and the open pipes will be closed. The
 *              IOUSBHostPipe objects already created will no longer be valid. The new alternate
 *              setting will be selected via SET_INTERFACE control request (USB 2.0 9.4.10).
 * @param       alternateSetting Alternate interface number to activate
 * @return      YES on success, an IOReturn error code will be reported on failure.
 */
- (BOOL)selectAlternateSetting:(NSUInteger)alternateSetting
                         error:(NSError* _Nullable*)error;

/*!
 * @brief       Return the pipe whose <code>bEndpointAddress</code> matches <code>address</code>
 * @discussion  This method will return the pipe whose <code>bEndpointAddress</code>
 *              matches <code>address</code>. If the pipe is returned successfully, it will maintain
 *              a reference to the IOUSBHostInterface.
 * @param       address Endpoint address of the pipe
 * @return      Pointer to an IOUSBHostPipe object or nil. The IOUSBHostPipe is to be released by the caller.
 *              An IOReturn error code will be reported on failure.
 */
- (nullable IOUSBHostPipe*)copyPipeWithAddress:(NSUInteger)address
                                         error:(NSError* _Nullable*)error;

@end

NS_ASSUME_NONNULL_END
