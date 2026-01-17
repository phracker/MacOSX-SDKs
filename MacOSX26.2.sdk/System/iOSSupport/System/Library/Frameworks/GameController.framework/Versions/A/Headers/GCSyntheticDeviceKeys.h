//  
//  GCSyntheticDeviceKeys.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef GCSyntheticDeviceKeys_h
#define GCSyntheticDeviceKeys_h

/**
 *  This key is present with a \c Boolean value of \c true on all synthetic
 *  HID devices created by the GameController framework.
 *
 *  If your application needs to exclude these synthetic HID devices from being
 *  discovered by \c IOHIDManager, \c IOServiceGetMatchingServices, or
 *  \c IOServiceAddMatchingNotification, include '"GCSyntheticDevice" = false'
 *  in your matching criteria.
 *
 *  Example using \c IOHIDManager to discover connected HID devices, excluding
 *  synthetic HID devices:
 *
 *    IOHIDManagerRef manager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDManagerOptionNone);
 *    IOHIDManagerSetDeviceMatching(manager, (__bridge CFDictionaryRef)@{
 *        @kIOProviderClassKey: @kIOHIDDeviceKey,
 *        @kIOHIDGCSyntheticDeviceKey: @(NO)
 *    });
 *
 *  Example using \c IOServiceAddMatchingNotification to discover kernel
 *  \c IOHIDDevice objects, excluding synthetic HID devices:
 *
 *    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOHIDDeviceKey);
 *    CFDictionarySetValue(matchingDict, CFSTR(kIOHIDGCSyntheticDeviceKey), kCFBooleanFalse);
 *
 *    io_iterator_t iterator = IO_OBJECT_NULL;
 *    IOServiceAddMatchingNotification(
 *      notifyPort,
 *      kIOFirstMatchNotification,
 *      matchingDict,
 *      NULL,
 *      serviceMatchedCallback,
 *      &iterator);
 *
 *  If you have an \c io_service_t or \c IOHIDDeviceRef, you can check if it
 *  refers to a synthetic HID device by querying the "GCSyntheticDevice"
 *  property.
 *
 *    if ( IOHIDDeviceGetProperty(device, CFSTR(kIOHIDGCSyntheticDeviceKey)) == kCFBooleanTrue ) {
 *        // Is synthetic HID device
 *    }
 *
 *  @note
 *  Checking for the "GCSyntheticDevice" property is the ONLY supported way to
 *  determine if a \c IOHIDDeviceRef or \c io_service_t refers to a synthetic
 *  HID device.
 */
#define kIOHIDGCSyntheticDeviceKey          "GCSyntheticDevice"

#endif /* GCSyntheticDeviceKeys_h */
