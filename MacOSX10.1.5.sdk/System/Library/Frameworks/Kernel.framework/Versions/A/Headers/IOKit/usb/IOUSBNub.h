/*
 * Copyright (c) 1998-2001 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.2 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.  
 * Please see the License for the specific language governing rights and 
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#ifndef _IOKIT_IOUSBNUB_H
#define _IOKIT_IOUSBNUB_H

#include <IOKit/IOService.h>
#include <libkern/c++/OSData.h>
#include <IOKit/IOMemoryDescriptor.h>

#include <IOKit/usb/USB.h>

class IOUSBController;
class IOUSBPipe;

/*!
    @class IOUSBNub
    @abstract abstract base class for IOUSBDevice and IOUSBInterface
    @discussion This class provides functionality that is useful for both
    a device driver (which would attach to an IOUSBDevice) and an interface driver
    (which would attach to an IOUSBInterface).
*/

class IOUSBNub : public IOService
{
    OSDeclareDefaultStructors(IOUSBNub)

public:
    /*!
    	@function findNextDescriptor
        @abstract find next descriptor in configuration list of given type
	(kUSBAnyDesc matches any type).
        @discussion call this function with a pointer to a descriptor in a descriptor list,
	for example the descriptor list returned by IOUSBDevice::getFullConfigurationDescriptor().
        Returns NULL if no more descriptors match descType.
        @param cur current descriptor in list
        @param descType descriptor type to return (kUSBAnyDesc to match any type)
	@result Pointer to the next matching descriptor, or NULL if no more match.
    */
    // static const IOUSBDescriptorHeader *FindNextDescriptor(const void *cur, UInt8 descType);

    /*!
        @function USBCompareProperty
        Checks to see if a key exists in the property table AND in the dictionary and if
        they are equal.  It differs from from the IOService::compareProperty in that it
        does NOT return true if the property does not exist.
        @result true if it exists and it matches otherwise, it returns false.
    */
    virtual bool USBCompareProperty(OSDictionary   * matching,
                                    const char     * key );
    
};

#ifdef __cplusplus
extern "C" {
#endif

void printDescriptor(const IOUSBDescriptorHeader *desc);
void printDeviceDescriptor(const IOUSBDeviceDescriptor *desc);
void printConfigDescriptor(const IOUSBConfigurationDescriptor *cd);
void printEndpointDescriptor(const IOUSBEndpointDescriptor *ed);
void printInterfaceDescriptor(const IOUSBInterfaceDescriptor *id);

#ifdef __cplusplus
}
#endif

#endif /* _IOKIT_IOUSBNUB_H */
