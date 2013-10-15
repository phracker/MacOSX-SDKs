/*
     File:       SecurityHI/SecurityHI.h
 
     Contains:   Master include for SecurityHI private framework
 
     Version:    SecurityHI-55002~1072
 
     Copyright:  © 2000-2008 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SECURITYHI__
#define __SECURITYHI__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#ifndef __KEYCHAINHI__
#include <SecurityHI/KeychainHI.h>
#endif

#ifndef __URLACCESS__
#include <SecurityHI/URLAccess.h>
#endif

#ifndef __SECCERTIFICATESUPPORT__
#include <SecurityHI/SecCertificateSupport.h>
#endif

#endif /* __SECURITYHI__ */

