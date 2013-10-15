/*
 * Copyright (c) 1998-2010 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_IOAUDIOSELECTORCONTROL_H
#define _IOKIT_IOAUDIOSELECTORCONTROL_H

#ifndef IOAUDIOFAMILY_SELF_BUILD
#include <IOKit/audio/IOAudioControl.h>
#else
#include "IOAudioControl.h"
#endif

class OSString;
class OSArray;

class IOAudioSelectorControl : public IOAudioControl
{
    OSDeclareDefaultStructors(IOAudioSelectorControl)
    
protected:

    OSArray *availableSelections;

protected:
    struct ExpansionData { };
    
    ExpansionData *reserved;

public:
	static IOAudioSelectorControl *createOutputSelector(SInt32 initialValue,
															UInt32 channelID,
															const char *channelName = 0,
															UInt32 cntrlID = 0);
	static IOAudioSelectorControl *createOutputClockSelector(SInt32 initialValue,
                                                                    UInt32 channelID,
																	UInt32 clockSource,
                                                                    const char *channelName = 0,
                                                                    UInt32 cntrlID = 0);
	static IOAudioSelectorControl *createInputClockSelector(SInt32 initialValue,
                                                                    UInt32 channelID,
																	UInt32 clockSource,
                                                                    const char *channelName = 0,
                                                                    UInt32 cntrlID = 0);

    // OSMetaClassDeclareReservedUsed(IOAudioSelectorControl, 0);
	virtual IOReturn removeAvailableSelection(SInt32 selectionValue);
    // OSMetaClassDeclareReservedUsed(IOAudioSelectorControl, 1);
	virtual IOReturn replaceAvailableSelection(SInt32 selectionValue, const char *selectionDescription);
    // OSMetaClassDeclareReservedUsed(IOAudioSelectorControl, 2);
	virtual IOReturn replaceAvailableSelection(SInt32 selectionValue, OSString *selectionDescription);
    // OSMetaClassDeclareReservedUsed(IOAudioSelectorControl, 3);
	virtual IOReturn addAvailableSelection(SInt32 selectionValue, OSString *selectionDescription, const char* pszName, OSObject* tag);		// <rdar://8202424>

private:
    OSMetaClassDeclareReservedUsed(IOAudioSelectorControl, 0);
    OSMetaClassDeclareReservedUsed(IOAudioSelectorControl, 1);
    OSMetaClassDeclareReservedUsed(IOAudioSelectorControl, 2);
    OSMetaClassDeclareReservedUsed(IOAudioSelectorControl, 3);			// <rdar://8202424>

    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 4);		// <rdar://8202424>

    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 5);		// <rdar://8202424>
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 6);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 7);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 8);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 9);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 10);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 11);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 12);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 13);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 14);
    OSMetaClassDeclareReservedUnused(IOAudioSelectorControl, 15);

public:
    static IOAudioSelectorControl *create(SInt32 initialValue,
                                            UInt32 channelID,
                                            const char *channelName = 0,
                                            UInt32 cntrlID = 0,
                                            UInt32 subType = 0,
                                            UInt32 usage = 0);
                                            
    static IOAudioSelectorControl *createInputSelector(SInt32 initialValue,
                                                        UInt32 channelID,
                                                        const char *channelName = 0,
                                                        UInt32 cntrlID = 0);
                                                        
    virtual bool init(SInt32 initialValue,
                      UInt32 channelID,
                      const char *channelName = 0,
                      UInt32 cntrlID = 0,
                      UInt32 subType = 0,
                      UInt32 usage = 0,
                      OSDictionary *properties = 0);

    virtual void free();

    virtual IOReturn addAvailableSelection(SInt32 selectionValue, const char *selectionDescription);
    virtual IOReturn addAvailableSelection(SInt32 selectionValue, OSString *selectionDescription);

    virtual bool valueExists(SInt32 selectorValue);

    virtual IOReturn validateValue(OSObject *newValue);

};

#endif /* _IOKIT_IOAUDIOSELECTORCONTROL_H */
