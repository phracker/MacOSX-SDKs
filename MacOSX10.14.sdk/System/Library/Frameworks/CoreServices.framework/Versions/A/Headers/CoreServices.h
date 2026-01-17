/*
     File:       CoreServices/CoreServices.h
 
     Contains:   Master include for CoreServices
  
     Copyright:  (c) 1999-2012 Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __CORESERVICES__
#define __CORESERVICES__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#if TARGET_OS_OSX
#ifndef __AE__
#include <AE/AE.h>
#endif
#endif

#if TARGET_OS_OSX
#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif
#endif

#ifndef __CFNETWORK__
#include <CFNetwork/CFNetwork.h>
#endif

#if TARGET_OS_OSX
#ifndef __DICTIONARYSERVICES__
#include <DictionaryServices/DictionaryServices.h>
#endif
#endif

#ifndef __LAUNCHSERVICES__
#include <LaunchServices/LaunchServices.h>
#endif

#if TARGET_OS_OSX
#ifndef __METADATA_METADATA__
#include <Metadata/Metadata.h>
#endif
#endif

#ifndef __OSSERVICES__
#include <OSServices/OSServices.h>
#endif

#if TARGET_OS_OSX
#ifndef __SEARCHKIT__
#include <SearchKit/SearchKit.h>
#endif
#endif

#ifndef __FSEVENTS__
#include <FSEvents/FSEvents.h>
#endif

#if TARGET_OS_OSX
#ifndef __SHAREDFILELIST__
#include <SharedFileList/SharedFileList.h>
#endif
#endif

#endif /* __CORESERVICES__ */
