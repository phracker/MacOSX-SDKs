/*
     File:       HIToolbox/TypeSelect.h
 
     Contains:   TypeSelect Utilties
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TYPESELECT__
#define __TYPESELECT__

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
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

typedef SInt16 TSCode;
enum {
  tsPreviousSelectMode          = -1,
  tsNormalSelectMode            = 0,
  tsNextSelectMode              = 1
};

struct TypeSelectRecord {
  unsigned long       tsrLastKeyTime;
  ScriptCode          tsrScript;
  Str63               tsrKeyStrokes;
};
typedef struct TypeSelectRecord         TypeSelectRecord;
typedef CALLBACK_API( Boolean , IndexToStringProcPtr )(short item, ScriptCode *itemsScript, StringPtr *itemsStringPtr, void *yourDataPtr);
typedef STACK_UPP_TYPE(IndexToStringProcPtr)                    IndexToStringUPP;
/*
 *  TypeSelectClear()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TypeSelectClear(TypeSelectRecord * tsr);


/*
        Long ago the implementation of TypeSelectNewKey had a bug that
        required the high word of D0 to be zero or the function did not work.
        Although fixed now, we are continuing to clear the high word
        just in case someone tries to run on an older system.
    */
/*
 *  TypeSelectNewKey()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
TypeSelectNewKey(
  const EventRecord *  theEvent,
  TypeSelectRecord *   tsr);


/*
 *  TypeSelectFindItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
TypeSelectFindItem(
  const TypeSelectRecord *  tsr,
  short                     listSize,
  TSCode                    selectMode,
  IndexToStringUPP          getStringProc,
  void *                    yourDataPtr);



/*
 *  TypeSelectCompare()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
TypeSelectCompare(
  const TypeSelectRecord *  tsr,
  ScriptCode                testStringScript,
  StringPtr                 testStringPtr);


/*
 *  NewIndexToStringUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern IndexToStringUPP
NewIndexToStringUPP(IndexToStringProcPtr userRoutine);

/*
 *  DisposeIndexToStringUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeIndexToStringUPP(IndexToStringUPP userUPP);

/*
 *  InvokeIndexToStringUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeIndexToStringUPP(
  short             item,
  ScriptCode *      itemsScript,
  StringPtr *       itemsStringPtr,
  void *            yourDataPtr,
  IndexToStringUPP  userUPP);





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

#endif /* __TYPESELECT__ */

