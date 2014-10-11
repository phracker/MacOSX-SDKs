/*
     File:       AE/AEPackObject.h
 
     Contains:   AppleEvents object packing Interfaces.
 
     Version:    AppleEvents-116~3
 
     Copyright:  © 1991-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AEPACKOBJECT__
#define __AEPACKOBJECT__

#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
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

/* These are the object packing routines.  */
/*
 *  CreateOffsetDescriptor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
CreateOffsetDescriptor(
  long      theOffset,
  AEDesc *  theDescriptor);


/*
 *  CreateCompDescriptor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
CreateCompDescriptor(
  DescType   comparisonOperator,
  AEDesc *   operand1,
  AEDesc *   operand2,
  Boolean    disposeInputs,
  AEDesc *   theDescriptor);


/*
 *  CreateLogicalDescriptor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
CreateLogicalDescriptor(
  AEDescList *  theLogicalTerms,
  DescType      theLogicOperator,
  Boolean       disposeInputs,
  AEDesc *      theDescriptor);



/*
 *  CreateObjSpecifier()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
CreateObjSpecifier(
  DescType   desiredClass,
  AEDesc *   theContainer,
  DescType   keyForm,
  AEDesc *   keyData,
  Boolean    disposeInputs,
  AEDesc *   objSpecifier);


/*
 *  CreateRangeDescriptor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
CreateRangeDescriptor(
  AEDesc *  rangeStart,
  AEDesc *  rangeStop,
  Boolean   disposeInputs,
  AEDesc *  theDescriptor);



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

#endif /* __AEPACKOBJECT__ */

