/*
 * Copyright © 2001-2006 Apple Inc.  All rights reserved.
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

#ifndef _IOKIT_IOUSBWORKLOOP_H
#define _IOKIT_IOUSBWORKLOOP_H

#include <IOKit/IOWorkLoop.h>

/*
 class IOUSBWorkLoop
 Subclass of IOWorkloop that allows the USB stack to more finely control sleep and wake.
*/
class IOUSBWorkLoop : public IOWorkLoop
{    
    OSDeclareDefaultStructors(IOUSBWorkLoop)
    
protected:
    void *			fSleepToken;
#ifndef __OPEN_SOURCE__
	lck_grp_t *		fLockGroup;
#endif
	bool init ( const char * controllerLocation );
	void free ( void );
	
    // Overrides to check for sleeping
    virtual void closeGate();
    virtual bool tryCloseGate();
    
public:
    // Create a workloop
    static IOUSBWorkLoop * workLoop(const char * controllerLocation);
    
    // Put workloop to sleep (Must have gate closed, opens gate if successful)
    virtual IOReturn sleep(void *token);
    
    // Wake workloop up (closes gate if successful)
    virtual IOReturn wake(void *token);
    
    void CloseGate(void);
    void OpenGate(void);
    
    int SleepWithTimeout(void *token, UInt64 timeout);
    void Wakeup(void *token, bool oneThread);
};

#endif

