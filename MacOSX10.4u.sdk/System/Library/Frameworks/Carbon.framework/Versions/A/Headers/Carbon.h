/*
     File:       Carbon/Carbon.h
 
     Contains:   Master include for all of Carbon
 
     Version:    Carbon-129~3631
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CARBON__
#define __CARBON__

#if __LP64__
    #error 64-bit not supported
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif


#ifndef __HITOOLBOX__
#include <HIToolbox/HIToolbox.h>
#endif

#ifndef __CARBONSOUND__
#include <CarbonSound/CarbonSound.h>
#endif

#ifndef __OPENSCRIPTING__
#include <OpenScripting/OpenScripting.h>
#endif

#ifndef __PRINT__
#include <Print/Print.h>
#endif

#ifndef __NAVIGATIONSERVICES__
#include <NavigationServices/NavigationServices.h>
#endif

#ifndef __COMMONPANELS__
#include <CommonPanels/CommonPanels.h>
#endif

#ifndef __HTMLRENDERING__
#include <HTMLRendering/HTMLRendering.h>
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

