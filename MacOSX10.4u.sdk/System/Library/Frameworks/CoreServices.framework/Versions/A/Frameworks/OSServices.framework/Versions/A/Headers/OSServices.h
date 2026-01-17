/*
     File:       OSServices/OSServices.h
 
     Contains:   Master include for OSServices private framework
 
     Version:    OSServices-101.1~790
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __OSSERVICES__
#define __OSSERVICES__

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif


#ifndef __APPLEDISKPARTITIONS__
#include <OSServices/AppleDiskPartitions.h>
#endif

#ifndef __ICONSTORAGE__
#include <OSServices/IconStorage.h>
#endif

#ifndef __POWER__
#include <OSServices/Power.h>
#endif

#ifndef __SCSI__
#include <OSServices/SCSI.h>
#endif

#ifndef __SYSTEMSOUND__
#include <OSServices/SystemSound.h>
#endif


#include <OSServices/OpenTransport.h>
#include <OSServices/OpenTransportProviders.h>
#include <OSServices/OpenTransportProtocol.h>
#include <OSServices/NSLCore.h>
#include <OSServices/SecurityCore.h>

#endif /* __OSSERVICES__ */

