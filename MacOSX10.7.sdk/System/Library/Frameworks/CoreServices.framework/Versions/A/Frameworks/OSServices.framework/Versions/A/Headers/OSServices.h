/*
     File:       OSServices/OSServices.h
 
     Contains:   Master include for OSServices private framework
 
     Copyright:  � 2000-2010 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __OSSERVICES__
#define __OSSERVICES__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif

#ifndef __CSIDENTITYAUTHORITY__
#include <OSServices/CSIdentityAuthority.h>
#endif

#ifndef __CSIDENTITYBASE__
#include <OSServices/CSIdentityBase.h>
#endif

#ifndef __CSIDENTITY__
#include <OSServices/CSIdentity.h>
#endif

#ifndef __CSIDENTITYQUERY__
#include <OSServices/CSIdentityQuery.h>
#endif

#ifndef __ICONSTORAGE__
#include <OSServices/IconStorage.h>
#endif

#ifndef __SYSTEMSOUND__
#include <OSServices/SystemSound.h>
#endif

#ifndef __WSTYPES__
#include <OSServices/WSTypes.h>
#endif

#ifndef __WSMETHODINVOCATION__
#include <OSServices/WSMethodInvocation.h>
#endif

#ifndef __WSPROTOCOLHANDLER__
#include <OSServices/WSProtocolHandler.h>
#endif

#ifndef __POWER__
#include <OSServices/Power.h>
#endif


#if !__LP64__
#ifndef __SCSI__
#include <OSServices/SCSI.h>
#endif

#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_4
#include <OSServices/OpenTransport.h>
#include <OSServices/OpenTransportProviders.h>
#include <OSServices/OpenTransportProtocol.h>
#endif
#endif
#include <OSServices/SecurityCore.h>

#endif /* __OSSERVICES__ */

