/*
 * Copyright (c) 1998-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef IOUSBHostFamily_IOUSBHostNub_h
#define IOUSBHostFamily_IOUSBHostNub_h

#include <IOKit/IOService.h>
#include <libkern/c++/OSData.h>
#include <IOKit/IOMemoryDescriptor.h>

#include <IOKit/usb/IOUSBHostFamily.h>

class IOUSBHostPipe;

#define getExpansionData(name) _expansionData->name

/*!
   @class IOUSBHostNub
   @abstract Super class for for IOUSBHostDevice and IOUSBHostInterface.
 */
class IOUSBHostNub : public IOService
{
    OSDeclareDefaultStructors(IOUSBHostNub)

public:
    static void initialize();

    virtual bool USBCompareProperty(OSDictionary* matching, const OSSymbol* key);

    bool IsWildCardMatch(OSDictionary* matching, const char* key);
    bool USBComparePropertyWithMask(OSDictionary* matching, const char* key, const char* maskKey);
    bool USBComparePropertyInArray(OSDictionary* matching, const char* arrayName, const char* key, UInt32* theProductIDThatMatched);
    bool USBComparePropertyInArrayWithMask(OSDictionary* matching, const char* arrayName, const char* key, const char* maskKey, UInt32* theProductIDThatMatched);

protected:
    static const OSSymbol* gUSBVendorID;
    static const OSSymbol* gUSBProductID;
    static const OSSymbol* gUSBInterfaceNumber;
    static const OSSymbol* gUSBConfigurationValue;
    static const OSSymbol* gUSBDeviceReleaseNumber;
    static const OSSymbol* gUSBInterfaceClass;
    static const OSSymbol* gUSBInterfaceSubClass;
    static const OSSymbol* gUSBInterfaceProtocol;
    static const OSSymbol* gUSBProductIDMask;
    static const OSSymbol* gUSBDeviceClass;
    static const OSSymbol* gUSBDeviceSubClass;
    static const OSSymbol* gUSBDeviceProtocol;
    static const OSSymbol* gUSBSpeed;
    static const OSSymbol* gUSBPortType;

    uint32_t _debugLoggingMask;
};

#endif // IOUSBHostFamily_IOUSBHostNub_h
