/*
     File:       Carbon/Carbon.h
 
     Contains:   Master include for all of Carbon
 
     Version:    Carbon-~1
 
     Copyright:  © 2000-2008 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CARBON__
#define __CARBON__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif


#ifndef __HITOOLBOX__
#include <HIToolbox/HIToolbox.h>
#endif

#if !__LP64__
#ifndef __CARBONSOUND__
#include <CarbonSound/CarbonSound.h>
#endif

#endif  /* !__LP64__ */

#ifndef __OPENSCRIPTING__
#include <OpenScripting/OpenScripting.h>
#endif

#ifndef __PRINT__
#include <Print/Print.h>
#endif

#if !__LP64__
#ifndef __NAVIGATIONSERVICES__
#include <NavigationServices/NavigationServices.h>
#endif

#endif  /* !__LP64__ */

#ifndef __COMMONPANELS__
#include <CommonPanels/CommonPanels.h>
#endif

#ifndef __SPEECHRECOGNITION__
#include <SpeechRecognition/SpeechRecognition.h>
#endif

#ifndef __SECURITYHI__
#include <SecurityHI/SecurityHI.h>
#endif

#ifndef __INK__
#include <Ink/Ink.h>
#endif

#ifndef __HELP__
#include <Help/Help.h>
#endif

#ifndef __IMAGECAPTURE__
#include <ImageCapture/ImageCapture.h>
#endif





#endif /* __CARBON__ */

