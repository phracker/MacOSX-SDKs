/*
     File:       HIToolbox/Lists.h
 
     Contains:   List Manager Interfaces.
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 1985-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __LISTS__
#define __LISTS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CONTROLS__
#include <HIToolbox/Controls.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef Point                           Cell;
typedef Rect                            ListBounds;
typedef char                            DataArray[32001];
typedef char *                          DataPtr;
typedef DataPtr *                       DataHandle;
typedef CALLBACK_API( short , ListSearchProcPtr )(Ptr aPtr, Ptr bPtr, short aLen, short bLen);
typedef CALLBACK_API( Boolean , ListClickLoopProcPtr )(void);
typedef STACK_UPP_TYPE(ListSearchProcPtr)                       ListSearchUPP;
typedef STACK_UPP_TYPE(ListClickLoopProcPtr)                    ListClickLoopUPP;
struct ListRec {
  Rect                rView;                  /* in Carbon use Get/SetListViewBounds*/
  GrafPtr             port;                   /* in Carbon use Get/SetListPort*/
  Point               indent;                 /* in Carbon use Get/SetListCellIndent*/
  Point               cellSize;               /* in Carbon use Get/SetListCellSize*/
  ListBounds          visible;                /* in Carbon use GetListVisibleCells*/
  ControlRef          vScroll;                /* in Carbon use GetListVerticalScrollBar*/
  ControlRef          hScroll;                /* in Carbon use GetListHorizontalScrollBar*/
  SInt8               selFlags;               /* in Carbon use Get/SetListSelectionFlags*/
  Boolean             lActive;                /* in Carbon use LActivate, GetListActive*/
  SInt8               lReserved;              /* not supported in Carbon */
  SInt8               listFlags;              /* in Carbon use Get/SetListFlags */
  long                clikTime;               /* in Carbon use Get/SetListClickTime*/
  Point               clikLoc;                /* in Carbon use GetListClickLocation*/
  Point               mouseLoc;               /* in Carbon use GetListMouseLocation*/
  ListClickLoopUPP    lClickLoop;             /* in Carbon use Get/SetListClickLoop*/
  Cell                lastClick;              /* in Carbon use SetListLastClick*/
  long                refCon;                 /* in Carbon use Get/SetListRefCon*/
  Handle              listDefProc;            /* not supported in Carbon */
  Handle              userHandle;             /* in Carbon use Get/SetListUserHandle*/
  ListBounds          dataBounds;             /* in Carbon use GetListDataBounds*/
  DataHandle          cells;                  /* in Carbon use LGet/SetCell*/
  short               maxIndex;               /* in Carbon use LGet/SetCell*/
  short               cellArray[1];           /* in Carbon use LGet/SetCell*/
};
typedef struct ListRec                  ListRec;
typedef ListRec *                       ListPtr;
typedef ListPtr *                       ListHandle;
/* ListRef is obsolete.  Use ListHandle. */
typedef ListHandle                      ListRef;


enum {
                                        /* ListRec.listFlags bits*/
  lDrawingModeOffBit            = 3,
  lDoVAutoscrollBit             = 1,
  lDoHAutoscrollBit             = 0
};

enum {
                                        /* ListRec.listFlags masks*/
  lDrawingModeOff               = 8,
  lDoVAutoscroll                = 2,
  lDoHAutoscroll                = 1
};


enum {
                                        /* ListRec.selFlags bits*/
  lOnlyOneBit                   = 7,
  lExtendDragBit                = 6,
  lNoDisjointBit                = 5,
  lNoExtendBit                  = 4,
  lNoRectBit                    = 3,
  lUseSenseBit                  = 2,
  lNoNilHiliteBit               = 1
};


enum {
                                        /* ListRec.selFlags masks*/
  lOnlyOne                      = -128,
  lExtendDrag                   = 64,
  lNoDisjoint                   = 32,
  lNoExtend                     = 16,
  lNoRect                       = 8,
  lUseSense                     = 4,
  lNoNilHilite                  = 2
};


enum {
                                        /* LDEF messages*/
  lInitMsg                      = 0,
  lDrawMsg                      = 1,
  lHiliteMsg                    = 2,
  lCloseMsg                     = 3
};

/*
   StandardIconListCellDataRec is the cell data format for
   use with the standard icon list (kListDefStandardIconType).
*/
struct StandardIconListCellDataRec {
  Handle              iconHandle;
  short               font;
  short               face;
  short               size;
  Str255              name;
};
typedef struct StandardIconListCellDataRec StandardIconListCellDataRec;
typedef StandardIconListCellDataRec *   StandardIconListCellDataPtr;


typedef CALLBACK_API( void , ListDefProcPtr )(short lMessage, Boolean lSelect, Rect *lRect, Cell lCell, short lDataOffset, short lDataLen, ListHandle lHandle);
typedef STACK_UPP_TYPE(ListDefProcPtr)                          ListDefUPP;
/*
 *  NewListSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ListSearchUPP
NewListSearchUPP(ListSearchProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewListClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ListClickLoopUPP
NewListClickLoopUPP(ListClickLoopProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewListDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ListDefUPP
NewListDefUPP(ListDefProcPtr userRoutine)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeListSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeListSearchUPP(ListSearchUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeListClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeListClickLoopUPP(ListClickLoopUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeListDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeListDefUPP(ListDefUPP userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeListSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern short
InvokeListSearchUPP(
  Ptr            aPtr,
  Ptr            bPtr,
  short          aLen,
  short          bLen,
  ListSearchUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeListClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeListClickLoopUPP(ListClickLoopUPP userUPP)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeListDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeListDefUPP(
  short       lMessage,
  Boolean     lSelect,
  Rect *      lRect,
  Cell        lCell,
  short       lDataOffset,
  short       lDataLen,
  ListHandle  lHandle,
  ListDefUPP  userUPP)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

enum {
  kListDefProcPtr               = 0,
  kListDefUserProcType          = kListDefProcPtr,
  kListDefStandardTextType      = 1,
  kListDefStandardIconType      = 2
};

typedef UInt32                          ListDefType;
struct ListDefSpec {
  ListDefType         defType;
  union {
    ListDefUPP          userProc;
  }                       u;
};
typedef struct ListDefSpec              ListDefSpec;
typedef ListDefSpec *                   ListDefSpecPtr;
/*
 *  CreateCustomList()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCustomList(
  const Rect *         rView,
  const ListBounds *   dataBounds,
  Point                cellSize,
  const ListDefSpec *  theSpec,
  WindowRef            theWindow,
  Boolean              drawIt,
  Boolean              hasGrow,
  Boolean              scrollHoriz,
  Boolean              scrollVert,
  ListHandle *         outList)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LNew()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ListHandle 
LNew(
  const Rect *        rView,
  const ListBounds *  dataBounds,
  Point               cSize,
  short               theProc,
  WindowRef           theWindow,
  Boolean             drawIt,
  Boolean             hasGrow,
  Boolean             scrollHoriz,
  Boolean             scrollVert)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LDispose()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LDispose(ListHandle lHandle)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAddColumn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
LAddColumn(
  short        count,
  short        colNum,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAddRow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
LAddRow(
  short        count,
  short        rowNum,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LDelColumn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LDelColumn(
  short        count,
  short        colNum,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LDelRow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LDelRow(
  short        count,
  short        rowNum,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LGetSelect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
LGetSelect(
  Boolean      next,
  Cell *       theCell,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LLastClick()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Cell 
LLastClick(ListHandle lHandle)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LNextCell()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
LNextCell(
  Boolean      hNext,
  Boolean      vNext,
  Cell *       theCell,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LSearch()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
LSearch(
  const void *    dataPtr,
  short           dataLen,
  ListSearchUPP   searchProc,
  Cell *          theCell,
  ListHandle      lHandle)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LSize()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LSize(
  short        listWidth,
  short        listHeight,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LSetDrawingMode()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LSetDrawingMode(
  Boolean      drawIt,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LScroll()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LScroll(
  short        dCols,
  short        dRows,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAutoScroll()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LAutoScroll(ListHandle lHandle)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LUpdate()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LUpdate(
  RgnHandle    theRgn,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LActivate()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LActivate(
  Boolean      act,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LCellSize()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LCellSize(
  Point        cSize,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LClick()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
LClick(
  Point            pt,
  EventModifiers   modifiers,
  ListHandle       lHandle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAddToCell()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LAddToCell(
  const void *  dataPtr,
  short         dataLen,
  Cell          theCell,
  ListHandle    lHandle)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LClrCell()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LClrCell(
  Cell         theCell,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LGetCell()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LGetCell(
  void *       dataPtr,
  short *      dataLen,
  Cell         theCell,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LRect(
  Rect *       cellRect,
  Cell         theCell,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LSetCell()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LSetCell(
  const void *  dataPtr,
  short         dataLen,
  Cell          theCell,
  ListHandle    lHandle)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LSetSelect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LSetSelect(
  Boolean      setIt,
  Cell         theCell,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LDraw()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LDraw(
  Cell         theCell,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LGetCellDataLocation()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LGetCellDataLocation(
  short *      offset,
  short *      len,
  Cell         theCell,
  ListHandle   lHandle)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Routines available in Carbon only*/

/*
 *  RegisterListDefinition()
 *  
 *  Summary:
 *    Registers a binding between a resource ID and a list definition
 *    function.
 *  
 *  Discussion:
 *    In the Mac OS 8.x List Manager, a 'ldes' resource can contain an
 *    embedded LDEF procID that is used by the List Manager as the
 *    resource ID of an 'LDEF' resource to measure and draw the list.
 *    Since LDEFs can no longer be packaged as code resources on
 *    Carbon, the procID can no longer refer directly to an LDEF
 *    resource. However, using RegisterListDefinition you can instead
 *    specify a UniversalProcPtr pointing to code in your application
 *    code fragment.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inResID:
 *      An LDEF proc ID, as used in a 'ldes' resource.
 *    
 *    inDefSpec:
 *      Specifies the ListDefUPP that should be used for lists with the
 *      given LDEF procID.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterListDefinition(
  SInt16           inResID,
  ListDefSpecPtr   inDefSpec)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if CALL_NOT_IN_CARBON
/*
 *  SetListDefinitionProc()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* CALL_NOT_IN_CARBON */

/*
 *  laddtocell()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lclrcell()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lgetcelldatalocation()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lgetcell()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lnew()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lrect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lsetcell()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lsetselect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ldraw()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lclick()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  lcellsize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#if OLDROUTINENAMES
#define LDoDraw(drawIt, lHandle) LSetDrawingMode(drawIt, lHandle)
#define LFind(offset, len, theCell, lHandle) LGetCellDataLocation(offset, len, theCell, lHandle)
#endif  /* OLDROUTINENAMES */

/* Getters */
/*
 *  GetListViewBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetListViewBounds(
  ListHandle   list,
  Rect *       view)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListPort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern CGrafPtr 
GetListPort(ListHandle list)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListCellIndent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetListCellIndent(
  ListHandle   list,
  Point *      indent)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListCellSize()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetListCellSize(
  ListHandle   list,
  Point *      size)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListVisibleCells()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ListBounds * 
GetListVisibleCells(
  ListHandle    list,
  ListBounds *  visible)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListVerticalScrollBar()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ControlRef 
GetListVerticalScrollBar(ListHandle list)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListHorizontalScrollBar()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ControlRef 
GetListHorizontalScrollBar(ListHandle list)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListActive()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
GetListActive(ListHandle list)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListClickTime()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern SInt32 
GetListClickTime(ListHandle list)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListClickLocation()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetListClickLocation(
  ListHandle   list,
  Point *      click)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListMouseLocation()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetListMouseLocation(
  ListHandle   list,
  Point *      mouse)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListClickLoop()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ListClickLoopUPP 
GetListClickLoop(ListHandle list)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListRefCon()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern SInt32 
GetListRefCon(ListHandle list)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListDefinition()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Handle 
GetListDefinition(ListHandle list)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListUserHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Handle 
GetListUserHandle(ListHandle list)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListDataBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ListBounds * 
GetListDataBounds(
  ListHandle    list,
  ListBounds *  bounds)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListDataHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern DataHandle 
GetListDataHandle(ListHandle list)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern OptionBits 
GetListFlags(ListHandle list)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetListSelectionFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern OptionBits 
GetListSelectionFlags(ListHandle list)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Setters */
/*
 *  SetListViewBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListViewBounds(
  ListHandle    list,
  const Rect *  view)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListPort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListPort(
  ListHandle   list,
  CGrafPtr     port)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListCellIndent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListCellIndent(
  ListHandle   list,
  Point *      indent)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListClickTime()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListClickTime(
  ListHandle   list,
  SInt32       time)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListClickLoop()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListClickLoop(
  ListHandle         list,
  ListClickLoopUPP   clickLoop)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListLastClick()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListLastClick(
  ListHandle   list,
  Cell *       lastClick)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListRefCon()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListRefCon(
  ListHandle   list,
  SInt32       refCon)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListUserHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListUserHandle(
  ListHandle   list,
  Handle       userHandle)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListFlags(
  ListHandle   list,
  OptionBits   listFlags)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetListSelectionFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListSelectionFlags(
  ListHandle   list,
  OptionBits   selectionFlags)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* WARNING: These may go away in a future build.  Beware! */
/*
 *  SetListDefinition()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  SetListCellSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  SetListHorizontalScrollBar()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  SetListVerticalScrollBar()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  SetListVisibleCells()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __LISTS__ */

