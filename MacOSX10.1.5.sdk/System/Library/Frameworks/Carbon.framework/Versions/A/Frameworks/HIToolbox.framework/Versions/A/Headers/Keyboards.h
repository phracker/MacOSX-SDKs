/*
     File:       HIToolbox/Keyboards.h
 
     Contains:   Keyboard API.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1997-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __KEYBOARDS__
#define __KEYBOARDS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
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

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Keyboard API constants                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Keyboard API Trap Number. Should be moved to Traps.i */
enum {
  _KeyboardDispatch             = 0xAA7A
};

/* Gestalt selector and values for the Keyboard API */
enum {
  gestaltKeyboardsAttr          = 'kbds',
  gestaltKBPS2Keyboards         = 1,
  gestaltKBPS2SetIDToAny        = 2,
  gestaltKBPS2SetTranslationTable = 4
};

/* Keyboard API Error Codes */
/*
   I stole the range blow from the empty space in the Allocation project but should
   be updated to the officially registered range.
*/
enum {
  errKBPS2KeyboardNotAvailable  = -30850,
  errKBIlligalParameters        = -30851,
  errKBFailSettingID            = -30852,
  errKBFailSettingTranslationTable = -30853,
  errKBFailWritePreference      = -30854
};


/* Keyboard HW Layout Types */
enum {
  kKeyboardJIS                  = 'JIS ',
  kKeyboardANSI                 = 'ANSI',
  kKeyboardISO                  = 'ISO ',
  kKeyboardUnknown              = kUnknownType /* '????'*/
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Keyboard API types                                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Keyboard API routines                                                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

/*
 *  KBInitialize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBSetupPS2Keyboard()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBGetPS2KeyboardID()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBIsPS2KeyboardConnected()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBIsPS2KeyboardEnabled()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBGetPS2KeyboardAttributes()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBSetKCAPForPS2Keyboard()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBSetupPS2KeyboardFromLayoutType()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBGetPS2KeyboardLayoutType()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */


/*
 *  KBGetLayoutType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   in KeyboardsLib 1.0 and later
 */
extern OSType 
KBGetLayoutType(SInt16 keyboardType);




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

#endif /* __KEYBOARDS__ */

