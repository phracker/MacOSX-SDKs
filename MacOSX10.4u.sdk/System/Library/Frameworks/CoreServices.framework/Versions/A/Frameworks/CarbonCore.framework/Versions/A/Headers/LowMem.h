/*
     File:       CarbonCore/LowMem.h
 
     Contains:   Low Memory Accessor Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1993-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __LOWMEM__
#define __LOWMEM__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __MACMEMORY__
#include <CarbonCore/MacMemory.h>
#endif

#ifndef __OSUTILS__
#include <CarbonCore/OSUtils.h>
#endif

#ifndef __RESOURCES__
#include <CarbonCore/Resources.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/**************************************************************************************

    SIMPLE LOWMEM ACCESSORS

**************************************************************************************/
/*
    The following functions were moved to Quickdraw.h:
    
        LMSetDeviceList
        LMSetLastSPExtra
        LMGetWidthListHand
        LMSetWidthListHand
        LMGetScrHRes
        LMSetScrHRes
        LMSetScrVRes
        LMGetScrVRes
        LMGetHiliteMode
        LMSetHiliteMode
        LMGetMainDevice
        LMSetMainDevice
        LMGetDeviceList
        LMGetQDColors
        LMSetQDColors
        LMGetWidthPtr
        LMSetWidthPtr
        LMGetWidthTabHandle
        LMSetWidthTabHandle
        LMGetLastSPExtra
        LMGetLastFOND
        LMSetLastFOND
        LMGetFractEnable
        LMSetFractEnable
        LMGetTheGDevice
        LMSetTheGDevice
        LMGetCursorNew
        LMSetCursorNew
        LMGetHiliteRGB
        LMSetHiliteRGB
    
    The following functions were moved to TextEdit.h:
    
        LMGetWordRedraw
        LMSetWordRedraw

    The following functions were moved to Menus.h:
    
        LMGetTheMenu
    
    The following functions were moved to Events.h:
    
        LMGetKeyRepThresh
        LMSetKeyRepThresh
        LMGetKeyThresh
        LMSetKeyRepThresh
        LMGetKbdLast
        LMSetKbdLast
        LMGetKbdType
        LMSetKbdType

*/

/*
 *  LMGetMemTop()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr  LMGetMemTop(void)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetMemTop()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetMemTop(Ptr value)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  LMGetBufPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr  LMGetBufPtr(void)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetBufPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetBufPtr(Ptr value)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  LMGetHeapEnd()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr  LMGetHeapEnd(void)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetHeapEnd()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetHeapEnd(Ptr value)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetCPUFlag()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8  LMGetCPUFlag(void)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetCPUFlag()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetCPUFlag(UInt8 value)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  LMGetRndSeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32  LMGetRndSeed(void)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetRndSeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetRndSeed(SInt32 value)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetSEvtEnb()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8  LMGetSEvtEnb(void)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetSEvtEnb()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSEvtEnb(UInt8 value)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetBootDrive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetBootDrive(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetBootDrive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetBootDrive(SInt16 value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetSdVolume()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8  LMGetSdVolume(void)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetSdVolume()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSdVolume(UInt8 value)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  LMGetSoundPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr  LMGetSoundPtr(void)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetSoundPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSoundPtr(Ptr value)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  LMGetSoundBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr  LMGetSoundBase(void)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetSoundBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSoundBase(Ptr value)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetSoundLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8  LMGetSoundLevel(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetSoundLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSoundLevel(UInt8 value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetCurPitch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetCurPitch(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetCurPitch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetCurPitch(SInt16 value)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetROM85()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  LMSetROM85()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
 *  LMGetPortBUse()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  LMSetPortBUse()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
 *  LMGetGNEFilter()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  LMSetGNEFilter()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
 *  LMGetROMBase()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  LMSetROMBase()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
 *  LMGetRAMBase()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  LMSetRAMBase()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */




/*
 *  LMGetDSAlertTab()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  LMSetDSAlertTab()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */




/*
    NOTE:   LMGetABusVars and LMSetABusVars have been removed.
            Their implememtation in InterfaceLib was inconsistent
            with their prototypes here.  In InterfaceLib LMSetABusVars 
            would copy eight bytes and LMGetABusVars would return the
            value 0x02D8 instead of the long at that location.
            
            Use LMGetABusGlobals/LMSetABusGlobals to get/set the
            long at location 0x02D8 which is a pointer to the AppleTalk
            globals.  Use LMGetABusDCE/LMSetABusDCE to get/set the
            long at location 0x02DC which is the .MPP driver
            Device Control Entry. 
            
*/
/*
 *  LMGetABusGlobals()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  LMGetABusDCE()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */



/*
 *  LMSetABusGlobals()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  LMSetABusDCE()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  LMGetScrDmpEnb()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8  LMGetScrDmpEnb(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetScrDmpEnb()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetScrDmpEnb(UInt8 value)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  LMGetBufTgFNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32  LMGetBufTgFNum(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetBufTgFNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetBufTgFNum(SInt32 value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetBufTgFFlg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetBufTgFFlg(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetBufTgFFlg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetBufTgFFlg(SInt16 value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetBufTgFBkNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetBufTgFBkNum(void)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetBufTgFBkNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetBufTgFBkNum(SInt16 value)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetBufTgDate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32  LMGetBufTgDate(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetBufTgDate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetBufTgDate(SInt32 value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetMinStack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32  LMGetMinStack(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetMinStack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetMinStack(SInt32 value)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetDefltStack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32  LMGetDefltStack(void)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetDefltStack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetDefltStack(SInt32 value)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetGZRootHnd()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle  LMGetGZRootHnd(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetGZRootHnd()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetGZRootHnd(Handle value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  LMGetGZMoveHnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle  LMGetGZMoveHnd(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetGZMoveHnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetGZMoveHnd(Handle value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetToExtFS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UniversalProcPtr  LMGetToExtFS(void)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetToExtFS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetToExtFS(UniversalProcPtr value)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetJStash()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UniversalProcPtr  LMGetJStash(void)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetJStash()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetJStash(UniversalProcPtr value)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetCurApRefNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetCurApRefNum(void)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetCurApRefNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetCurApRefNum(SInt16 value)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetCurStackBase()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    If using the Thread Manager APIs, use ThreadCurrentStackSpace(). 
 *    If using pthreads(), get the stack with
 *    pthread_get_stackaddr_np().
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr  LMGetCurStackBase(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetCurStackBase()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Mac OS X does not support setting the stack base.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetCurStackBase(Ptr value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetCurPageOption()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetCurPageOption(void)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetCurPageOption()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetCurPageOption(SInt16 value)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;




/*
 *  LMGetPrintErr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetPrintErr(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetPrintErr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetPrintErr(SInt16 value)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetApFontID()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Get the id of the application font.  Use GetAppFont() in the
 *    Quickdraw framework instead of this.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetApFontID(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetApFontID()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Set the id of the application font.  Don't use this call anymore;
 *    this functionality is not supported on Mac OS X.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetApFontID(SInt16 value)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetOneOne()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32  LMGetOneOne(void)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetOneOne()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetOneOne(SInt32 value)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetMinusOne()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32  LMGetMinusOne(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetMinusOne()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetMinusOne(SInt32 value)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetSysMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetSysMap(void)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetSysMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSysMap(SInt16 value)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetResLoad()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8  LMGetResLoad(void)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetResLoad()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetResLoad(UInt8 value)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetResErr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetResErr(void)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetResErr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetResErr(SInt16 value)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetTmpResLoad()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8  LMGetTmpResLoad(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetTmpResLoad()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetTmpResLoad(UInt8 value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetIntlSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr  LMGetIntlSpec(void)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetIntlSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetIntlSpec(Ptr value)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* LMGetWordRedraw and LMSetWordRedraw moved to TextEdit.h */
/*
 *  LMGetSysFontFam()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Get the id of the system font family.  Use GetSysFont() in the
 *    Quickdraw framework instead of this.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetSysFontFam(void)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetSysFontFam()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Set the id of the system font family.  This is not supported on
 *    Mac OS X.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSysFontFam(SInt16 value)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetSysFontSize()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Get the size of the system font.  Use DefFontSize() in the
 *    Quickdraw framework instead of this.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16  LMGetSysFontSize(void)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetSysFontSize()
 *  
 *  Summary:
 *    Set the size for the system font.  This is not supported on Mac
 *    OS X.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSysFontSize(SInt16 value)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/**************************************************************************************
    "BLOCKMOVE ACCESSORS"
    
        These lowmem accessors use the BlockMove to set
**************************************************************************************/
/*
 *  LMGetCurApName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StringPtr  LMGetCurApName(void)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetCurApName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetCurApName(ConstStr31Param curApNameValue)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetSysResName()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Mac OS X does not have the concept of a "System" file name. 
 *    Remove usage of this lowmem value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StringPtr  LMGetSysResName(void)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetSysResName()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Mac OS X does not have the concept of a "System" file name. 
 *    Remove usage of this lowmem value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetSysResName(ConstStr15Param sysResNameValue) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetFinderName()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Getting the name of the Finder isn't terribly useful.  If you
 *    need to find the Finder process, look it up with the CFBundle
 *    calls by bundle id ( "com.apple.finder" ).  Remove usage of this
 *    lowmem value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StringPtr  LMGetFinderName(void)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetFinderName()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Setting the name of the Finder application is not supported on
 *    Mac OS X.  Remove usage of this lowmem accessor.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetFinderName(ConstStr15Param finderNameValue) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMGetToolScratch()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Mac OS X gives each process its own tool scratch area, so this
 *    accessor is fairly useless. If you really need to share 8 bytes
 *    of memory among various libraries, just make it a global and
 *    export it from one library and import it into the others.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr  LMGetToolScratch(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetToolScratch()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Mac OS X gives each process its own tool scratch area, so this
 *    accessor is fairly useless. If you really need to share 8 bytes
 *    of memory among various libraries, just make it a global and
 *    export it from one library and import it into the others.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetToolScratch(const void * toolScratchValue)  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/**************************************************************************************
    "INDEXED ACCESSORS"
    
        These lowmem accessors take an index parameter to get/set an indexed
        lowmem global.
**************************************************************************************/
/*
 *  LMGetLvl2DT()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UniversalProcPtr  LMGetLvl2DT(short vectorNumber)      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetLvl2DT()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void  LMSetLvl2DT(UniversalProcPtr Lvl2DTValue, short vectorNumber)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/**************************************************************************************
    "Missing Accessors"
    
        These lowmem accessors are not in the original InterfaceLib.  They were
        added to InterfaceLib in Mac OS 8.5.  In Universal Interfaces 3.2 they
        were defined via a macro. In you want to use these functions on a pre-8.5
        systems, you must write your own macros to override the function prototype
        or write your own implementation.
    
**************************************************************************************/


/* accesses "HiHeapMark"*/
/*
 *  LMGetHighHeapMark()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern Ptr  LMGetHighHeapMark(void)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetHighHeapMark()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void  LMSetHighHeapMark(Ptr value)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* accesses "StkLowPt"*/
/*
 *  LMGetStackLowPoint()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern Ptr  LMGetStackLowPoint(void)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetStackLowPoint()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void  LMSetStackLowPoint(Ptr value)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* accesses "FmtDefaults"*/
/*
 *  LMGetDiskFormatingHFSDefaults()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern Ptr  LMGetDiskFormatingHFSDefaults(void)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  LMSetDiskFormatingHFSDefaults()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void  LMSetDiskFormatingHFSDefaults(Ptr value)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;




#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __LOWMEM__ */

