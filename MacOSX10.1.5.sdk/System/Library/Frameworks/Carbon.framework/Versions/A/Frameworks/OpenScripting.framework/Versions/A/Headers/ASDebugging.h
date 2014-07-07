/*
     File:       OpenScripting/ASDebugging.h
 
     Contains:   AppleScript Debugging Interfaces.
 
     Version:    OSA-30~10
 
     Copyright:  © 1992-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ASDEBUGGING__
#define __ASDEBUGGING__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __COMPONENTS__
#include <CarbonCore/Components.h>
#endif

#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
#endif

#ifndef __APPLESCRIPT__
#include <OpenScripting/AppleScript.h>
#endif




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/**************************************************************************
    Mode Flags
**************************************************************************/
/*    This mode flag can be passed to OSASetProperty or OSASetHandler
    and will prevent properties or handlers from being defined in a context
    that doesn't already have bindings for them. An error is returned if
    a current binding doesn't already exist. 
*/
enum {
  kOSAModeDontDefine            = 0x0001
};

/**************************************************************************
    Component Selectors
**************************************************************************/
enum {
  kASSelectSetPropertyObsolete  = 0x1101,
  kASSelectGetPropertyObsolete  = 0x1102,
  kASSelectSetHandlerObsolete   = 0x1103,
  kASSelectGetHandlerObsolete   = 0x1104,
  kASSelectGetAppTerminologyObsolete = 0x1105,
  kASSelectSetProperty          = 0x1106,
  kASSelectGetProperty          = 0x1107,
  kASSelectSetHandler           = 0x1108,
  kASSelectGetHandler           = 0x1109,
  kASSelectGetAppTerminology    = 0x110A,
  kASSelectGetSysTerminology    = 0x110B,
  kASSelectGetPropertyNames     = 0x110C,
  kASSelectGetHandlerNames      = 0x110D
};

/**************************************************************************
    Context Accessors
**************************************************************************/
/*
 *  OSASetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSASetProperty(
  ComponentInstance   scriptingComponent,
  long                modeFlags,
  OSAID               contextID,
  const AEDesc *      variableName,
  OSAID               scriptValueID);


/*
 *  OSAGetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetProperty(
  ComponentInstance   scriptingComponent,
  long                modeFlags,
  OSAID               contextID,
  const AEDesc *      variableName,
  OSAID *             resultingScriptValueID);


/*
 *  OSAGetPropertyNames()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetPropertyNames(
  ComponentInstance   scriptingComponent,
  long                modeFlags,
  OSAID               contextID,
  AEDescList *        resultingPropertyNames);


/*
 *  OSASetHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSASetHandler(
  ComponentInstance   scriptingComponent,
  long                modeFlags,
  OSAID               contextID,
  const AEDesc *      handlerName,
  OSAID               compiledScriptID);


/*
 *  OSAGetHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetHandler(
  ComponentInstance   scriptingComponent,
  long                modeFlags,
  OSAID               contextID,
  const AEDesc *      handlerName,
  OSAID *             resultingCompiledScriptID);


/*
 *  OSAGetHandlerNames()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetHandlerNames(
  ComponentInstance   scriptingComponent,
  long                modeFlags,
  OSAID               contextID,
  AEDescList *        resultingHandlerNames);


/*
 *  OSAGetAppTerminology()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetAppTerminology(
  ComponentInstance   scriptingComponent,
  long                modeFlags,
  FSSpec *            fileSpec,
  short               terminologyID,
  Boolean *           didLaunch,
  AEDesc *            terminologyList);


/* Errors:
       errOSASystemError        operation failed
    */
/*
 *  OSAGetSysTerminology()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetSysTerminology(
  ComponentInstance   scriptingComponent,
  long                modeFlags,
  short               terminologyID,
  AEDesc *            terminologyList);


/* Errors:
       errOSASystemError        operation failed
    */
/* Notes on terminology ID

    A terminology ID is derived from script code and language code
    as follows;

        terminologyID = ((scriptCode & 0x7F) << 8) | (langCode & 0xFF)
*/
/**************************************************************************
    Obsolete versions provided for backward compatibility:
*/
/*
 *  ASSetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
ASSetProperty(
  ComponentInstance   scriptingComponent,
  OSAID               contextID,
  const AEDesc *      variableName,
  OSAID               scriptValueID);


/*
 *  ASGetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
ASGetProperty(
  ComponentInstance   scriptingComponent,
  OSAID               contextID,
  const AEDesc *      variableName,
  OSAID *             resultingScriptValueID);


/*
 *  ASSetHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
ASSetHandler(
  ComponentInstance   scriptingComponent,
  OSAID               contextID,
  const AEDesc *      handlerName,
  OSAID               compiledScriptID);


/*
 *  ASGetHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
ASGetHandler(
  ComponentInstance   scriptingComponent,
  OSAID               contextID,
  const AEDesc *      handlerName,
  OSAID *             resultingCompiledScriptID);


/*
 *  ASGetAppTerminology()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
ASGetAppTerminology(
  ComponentInstance   scriptingComponent,
  FSSpec *            fileSpec,
  short               terminologID,
  Boolean *           didLaunch,
  AEDesc *            terminologyList);


/* Errors:
        errOSASystemError       operation failed
    */
/**************************************************************************/



#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __ASDEBUGGING__ */

