/*
 * Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
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
/*
 * Copyright (c) 2001 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 */


#ifndef _IOKIT_IOFWWORKLOOP_H
#define _IOKIT_IOFWWORKLOOP_H

#include <IOKit/IOWorkLoop.h>
class IOFWWorkLoop : public IOWorkLoop
{
    OSDeclareDefaultStructors(IOFWWorkLoop)
    
protected:
    void *fSleepToken;

    // Overrides to check for sleeping
    virtual void closeGate();
    virtual bool tryCloseGate();
    
public:
    // Create a workloop
    static IOFWWorkLoop * workLoop();
    
    // Put workloop to sleep (Must have gate closed, opens gate if successful)
    virtual IOReturn sleep(void *token);
    
    // Wake workloop up (closes gate if successful)
    virtual IOReturn wake(void *token);
};

#endif /* ! _IOKIT_IOFWWORKLOOP_H */

