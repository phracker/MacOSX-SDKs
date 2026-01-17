/*
     File:       CarbonCore/TextUtils.h
 
     Contains:   Text Utilities Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1985-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TEXTUTILS__
#define __TEXTUTILS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __NUMBERFORMATTING__
#include <CarbonCore/NumberFormatting.h>
#endif

#ifndef __STRINGCOMPARE__
#include <CarbonCore/StringCompare.h>
#endif

#ifndef __DATETIMEUTILS__
#include <CarbonCore/DateTimeUtils.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/*

    Here are the current System 7 routine names and the translations to the older forms.
    Please use the newer forms in all new code and migrate the older names out of existing
    code as maintainance permits.
    
    NEW NAME                    OLD NAMEs                   OBSOLETE FORM (no script code)

    FindScriptRun
    FindWordBreaks                                          NFindWord, FindWord
    GetIndString            
    GetString
    Munger
    NewString               
    SetString               
    StyledLineBreak
    TruncString
    TruncText

    UpperString ($A054)         UprString, UprText
    UppercaseText               SCUpperText (a only)        UpperText ($A456)
    LowercaseText                                           LwrString, LowerText, LwrText ($A056)
    StripDiacritics                                         StripText ($A256)
    UppercaseStripDiacritics                                StripUpperText ($A656)


*/

/* TruncCode, StyledLineBreakCode, and truncation constants moved to QuickDrawText.i */
struct ScriptRunStatus {
  SInt8               script;
  SInt8               runVariant;
};
typedef struct ScriptRunStatus          ScriptRunStatus;
struct BreakTable {
  char                charTypes[256];
  short               tripleLength;
  short               triples[1];
};
typedef struct BreakTable               BreakTable;
typedef BreakTable *                    BreakTablePtr;
struct NBreakTable {
  SInt8               flags1;
  SInt8               flags2;
  short               version;
  short               classTableOff;
  short               auxCTableOff;
  short               backwdTableOff;
  short               forwdTableOff;
  short               doBackup;
  short               length;                 /* length of NBreakTable */
  char                charTypes[256];
  short               tables[1];
};
typedef struct NBreakTable              NBreakTable;
typedef NBreakTable *                   NBreakTablePtr;
/* The following functions are new names that work on 68k and PowerPC*/

/*
 *  Munger()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
Munger(
  Handle        h,
  long          offset,
  const void *  ptr1,
  long          len1,
  const void *  ptr2,
  long          len2)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewString()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringCreateCopy instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringCreateCopy instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StringHandle 
NewString(ConstStr255Param theString)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetString()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringCreateWithPascalString and CFStringReplaceAll instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringCreateWithPascalString and CFStringReplaceAll instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetString(
  StringHandle       theString,
  ConstStr255Param   strNew)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetString()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFBundleCopyLocalizedString instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFBundleCopyLocalizedString instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StringHandle 
GetString(short stringID)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetIndString()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFBundleCopyLocalizedString instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFBundleCopyLocalizedString instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetIndString(
  Str255   theString,
  short    strListID,
  short    index)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  setstring()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  newstring()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringCreateCopy instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringCreateCopy instead.
 *  
 *  Availability:
 *    Mac OS X:         not available but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getindstring()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FindWordBreaks()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringUppercase instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringUppercase instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FindWordBreaks(
  Ptr             textPtr,
  short           textLength,
  short           offset,
  Boolean         leadingEdge,
  BreakTablePtr   breaks,
  OffsetTable     offsets,
  ScriptCode      script)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LowercaseText()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringLowercase instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringLowercase instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LowercaseText(
  Ptr          textPtr,
  short        len,
  ScriptCode   script)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  UppercaseText()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringUppercase instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringUppercase instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UppercaseText(
  Ptr          textPtr,
  short        len,
  ScriptCode   script)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  StripDiacritics()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringTransform instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringTransform instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StripDiacritics(
  Ptr          textPtr,
  short        len,
  ScriptCode   script)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  UppercaseStripDiacritics()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringTransform instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringTransform instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UppercaseStripDiacritics(
  Ptr          textPtr,
  short        len,
  ScriptCode   script)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FindScriptRun()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer needed on MacOS X.
 *  
 *  Discussion:
 *    This function is obsolate.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ScriptRunStatus 
FindScriptRun(
  Ptr     textPtr,
  long    textLen,
  long *  lenUsed)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
    The following functions are old names, but are required for PowerPC builds
    because InterfaceLib exports these names, instead of the new ones.
*/

/*
 *  FindWord()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NFindWord()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
   On 68K machines, LwrText, LowerText, StripText, UpperText and StripUpperText
   return an error code in register D0, but System 7 PowerMacs do not emulate
   this properly, so checking D0 is unreliable.
*/

/*
 *  LwrText()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  LowerText()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  StripText()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  UpperText()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  StripUpperText()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/* The following are new names which are exported by InterfaceLib*/

/*
 *  UpperString()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringUppercase instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringUppercase instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UpperString(
  Str255    theString,
  Boolean   diacSensitive)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  upperstring()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringUppercase instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringUppercase instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
upperstring(
  char *    theString,
  Boolean   diacSensitive)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* The following are macros which map old names to the names exported by InterfaceLib*/
#if OLDROUTINENAMES
#define UprString(theString, diacSensitive)  \
         UpperString(theString, diacSensitive)
#endif  /* OLDROUTINENAMES */

/* Old routine name but no new names are mapped to it:*/
/*
 *  UprText()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
    Functions for converting between C and Pascal Strings
    (Previously in Strings.h)
    
    Note: CopyPascalStringToC, CopyCStringToPascal, c2pstrcpy, and p2cstrcpy
          are written to allow inplace conversion.  That is, the src and dst
          parameters can point to the memory location.  These functions
          are available in CarbonLib and CarbonAccessors.o.
          
    Note: c2pstr, C2PStr, p2cstr, and P2CStr are all deprecated.  These functions
          only do inplace conversion and often require casts to call them.  This can
          cause bugs because you can easily cast away a const and change the 
          contents of a read-only buffer.  These functions are available
          in InterfaceLib, or when building for Carbon if you #define OLDP2C,
          then they are available as a macro.
    
*/
/*
 *  c2pstrcpy()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFString instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use CFString
 *    instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern void 
c2pstrcpy(
  Str255        dst,
  const char *  src)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  p2cstrcpy()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFString instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use CFString
 *    instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern void 
p2cstrcpy(
  char *             dst,
  ConstStr255Param   src)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  CopyPascalStringToC()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFString instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use CFString
 *    instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern void 
CopyPascalStringToC(
  ConstStr255Param   src,
  char *             dst)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  CopyCStringToPascal()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFString instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use CFString
 *    instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern void 
CopyCStringToPascal(
  const char *  src,
  Str255        dst)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  c2pstr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StringPtr 
c2pstr(char * aStr)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED;


/*
 *  C2PStr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StringPtr 
C2PStr(Ptr cString)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED;


/*
 *  p2cstr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern char * 
p2cstr(StringPtr aStr)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  P2CStr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
P2CStr(StringPtr pString)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#if !TARGET_OS_MAC
    /* Added for QuickTime 3.0 */
    #define C2PStr(a)  (StringPtr)c2pstr((Ptr)(a))
    #define P2CStr(a)  (Ptr)p2cstr(a)

    #define CopyPascalStringToC(src,dst) p2cstrcpy(dst,src)
    #define CopyCStringToPascal(src,dst) c2pstrcpy(dst,src)
#endif
#if TARGET_OS_MAC && TARGET_API_MAC_CARBON && OLDP2C
    /* macros to help source code that uses deprecated inplace  */
    /* conversion routines to compiler for carbon */
    #define p2cstr(aStr) (p2cstrcpy((char *) aStr, aStr) , (char *) aStr)
    #define c2pstr(aStr) (c2pstrcpy((StringPtr)aStr, aStr) , (StringPtr) aStr)

    #define C2PStr(a)  (StringPtr)c2pstr((Ptr)(a))
    #define P2CStr(a)  (Ptr)p2cstr(a)
#endif



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __TEXTUTILS__ */

