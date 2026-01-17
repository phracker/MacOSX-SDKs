/*
 * Copyright (c) 1998-2001 Apple Computer, Inc. All rights reserved.
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
 *  IOFireWireUserClientIniter.h
 *  IOFireWireFamily
 *
 *  Created by NWG on Wed Jan 24 2001.
 *  Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __IOKIT_IOFireWireUserClientIniter_H__
#define __IOKIT_IOFireWireUserClientIniter_H__

#include <IOKit/IOService.h>

class IOFireWireUserClientIniter : public IOService 
{
    OSDeclareDefaultStructors(IOFireWireUserClientIniter);

private:
	/*! @struct ExpansionData
		@discussion This structure will be used to expand the capablilties of the class in the future.
		*/    
	struct ExpansionData { };
	
	/*! @var reserved
		Reserved for future use.  (Internal use only)  */
	ExpansionData *reserved;

    static UInt32 						fHasUCIniter; // zzz why not boolean?
    static IOFireWireUserClientIniter*	fUCIniter;
    static OSDictionary*				fProviderMergeProperties;
	static OSDictionary*				fPropTable ;
	static IOService*					fProvider ;

public:
	virtual IOService*				probe(IOService* provider, SInt32* score) ;
	virtual bool					start(IOService*	provider) ;
	virtual bool					init(OSDictionary*	propTable) ;
	virtual void					stop(IOService*		provider) ;
	
protected:
	virtual void					mergeProperties(OSObject* dest, OSObject* src) ;
	virtual OSDictionary*			copyDictionaryProperty(OSDictionary*	srcDictionary) ;

private:
    OSMetaClassDeclareReservedUnused(IOFireWireUserClientIniter, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireUserClientIniter, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireUserClientIniter, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireUserClientIniter, 3);
};

#endif//#ifndef __IOKIT_IOFireWireUserClientIniter_H__
