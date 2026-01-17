/*
     File:       CoreServices/CoreServices.h
 
     Contains:   Master include for CoreServices (non-UI toolbox)
 
     Version:    CoreServices-17~2493
 
     Copyright:  © 1999-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CORESERVICES__
#define __CORESERVICES__

#if __LP64__
    #error 64-bit not supported
#endif

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif

#ifndef __OSSERVICES__
#include <OSServices/OSServices.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __CFNETWORK__
#include <CFNetwork/CFNetwork.h>
#endif

#ifndef __WEBSERVICESCORE__
#include <WebServicesCore/WebServicesCore.h>
#endif

#ifndef __SEARCHKIT__
#include <SearchKit/SearchKit.h>
#endif

#include <Metadata/Metadata.h>

#endif /* __CORESERVICES__ */

