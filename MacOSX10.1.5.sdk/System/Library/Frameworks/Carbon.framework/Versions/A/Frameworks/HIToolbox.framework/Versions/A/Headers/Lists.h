/*
     File:       HIToolbox/Lists.h
 
     Contains:   List Manager Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __LISTS__
#define __LISTS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __CONTROLS__
#include <HIToolbox/Controls.h>
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
NewListSearchUPP(ListSearchProcPtr userRoutine);

/*
 *  NewListClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ListClickLoopUPP
NewListClickLoopUPP(ListClickLoopProcPtr userRoutine);

/*
 *  NewListDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ListDefUPP
NewListDefUPP(ListDefProcPtr userRoutine);

/*
 *  DisposeListSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeListSearchUPP(ListSearchUPP userUPP);

/*
 *  DisposeListClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeListClickLoopUPP(ListClickLoopUPP userUPP);

/*
 *  DisposeListDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeListDefUPP(ListDefUPP userUPP);

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
  ListSearchUPP  userUPP);

/*
 *  InvokeListClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeListClickLoopUPP(ListClickLoopUPP userUPP);

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
  ListDefUPP  userUPP);

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
  ListHandle *         outList);



/*
 *  LNew()
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
  Boolean             scrollVert);


/*
 *  LDispose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LDispose(ListHandle lHandle);


/*
 *  LAddColumn()
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
  ListHandle   lHandle);


/*
 *  LAddRow()
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
  ListHandle   lHandle);


/*
 *  LDelColumn()
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
  ListHandle   lHandle);


/*
 *  LDelRow()
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
  ListHandle   lHandle);


/*
 *  LGetSelect()
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
  ListHandle   lHandle);


/*
 *  LLastClick()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Cell 
LLastClick(ListHandle lHandle);


/*
 *  LNextCell()
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
  ListHandle   lHandle);


/*
 *  LSearch()
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
  ListHandle      lHandle);


/*
 *  LSize()
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
  ListHandle   lHandle);


/*
 *  LSetDrawingMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LSetDrawingMode(
  Boolean      drawIt,
  ListHandle   lHandle);


/*
 *  LScroll()
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
  ListHandle   lHandle);


/*
 *  LAutoScroll()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LAutoScroll(ListHandle lHandle);


/*
 *  LUpdate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LUpdate(
  RgnHandle    theRgn,
  ListHandle   lHandle);


/*
 *  LActivate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LActivate(
  Boolean      act,
  ListHandle   lHandle);


/*
 *  LCellSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LCellSize(
  Point        cSize,
  ListHandle   lHandle);


/*
 *  LClick()
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
  ListHandle       lHandle);


/*
 *  LAddToCell()
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
  ListHandle    lHandle);


/*
 *  LClrCell()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LClrCell(
  Cell         theCell,
  ListHandle   lHandle);


/*
 *  LGetCell()
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
  ListHandle   lHandle);


/*
 *  LRect()
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
  ListHandle   lHandle);


/*
 *  LSetCell()
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
  ListHandle    lHandle);


/*
 *  LSetSelect()
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
  ListHandle   lHandle);


/*
 *  LDraw()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LDraw(
  Cell         theCell,
  ListHandle   lHandle);


/*
 *  LGetCellDataLocation()
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
  ListHandle   lHandle);


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
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterListDefinition(
  SInt16           inResID,
  ListDefSpecPtr   inDefSpec);


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
#if CGLUESUPPORTED
#define lfind(offset, len, theCell, lHandle) lgetcelldatalocation(offset, len, theCell, lHandle)
#endif
#endif  /* OLDROUTINENAMES */

/* Getters */
/*
 *  GetListViewBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetListViewBounds(
  ListRef   list,
  Rect *    view);


/*
 *  GetListPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern CGrafPtr 
GetListPort(ListRef list);


/*
 *  GetListCellIndent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetListCellIndent(
  ListRef   list,
  Point *   indent);


/*
 *  GetListCellSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetListCellSize(
  ListRef   list,
  Point *   size);


/*
 *  GetListVisibleCells()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ListBounds * 
GetListVisibleCells(
  ListRef       list,
  ListBounds *  visible);


/*
 *  GetListVerticalScrollBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ControlRef 
GetListVerticalScrollBar(ListRef list);


/*
 *  GetListHorizontalScrollBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ControlRef 
GetListHorizontalScrollBar(ListRef list);


/*
 *  GetListActive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
GetListActive(ListRef list);


/*
 *  GetListClickTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern SInt32 
GetListClickTime(ListRef list);


/*
 *  GetListClickLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetListClickLocation(
  ListRef   list,
  Point *   click);


/*
 *  GetListMouseLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetListMouseLocation(
  ListRef   list,
  Point *   mouse);


/*
 *  GetListClickLoop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ListClickLoopUPP 
GetListClickLoop(ListRef list);


/*
 *  GetListRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern SInt32 
GetListRefCon(ListRef list);


/*
 *  GetListDefinition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Handle 
GetListDefinition(ListRef list);


/*
 *  GetListUserHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Handle 
GetListUserHandle(ListRef list);


/*
 *  GetListDataBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern ListBounds * 
GetListDataBounds(
  ListRef       list,
  ListBounds *  bounds);


/*
 *  GetListDataHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern DataHandle 
GetListDataHandle(ListRef list);


/*
 *  GetListFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern OptionBits 
GetListFlags(ListRef list);


/*
 *  GetListSelectionFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern OptionBits 
GetListSelectionFlags(ListRef list);


/* Setters */
/*
 *  SetListViewBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListViewBounds(
  ListRef       list,
  const Rect *  view);


/*
 *  SetListPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListPort(
  ListRef    list,
  CGrafPtr   port);


/*
 *  SetListCellIndent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListCellIndent(
  ListRef   list,
  Point *   indent);


/*
 *  SetListClickTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListClickTime(
  ListRef   list,
  SInt32    time);


/*
 *  SetListClickLoop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListClickLoop(
  ListRef            list,
  ListClickLoopUPP   clickLoop);


/*
 *  SetListLastClick()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListLastClick(
  ListRef   list,
  Cell *    lastClick);


/*
 *  SetListRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListRefCon(
  ListRef   list,
  SInt32    refCon);


/*
 *  SetListUserHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListUserHandle(
  ListRef   list,
  Handle    userHandle);


/*
 *  SetListFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListFlags(
  ListRef      list,
  OptionBits   listFlags);


/*
 *  SetListSelectionFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetListSelectionFlags(
  ListRef      list,
  OptionBits   selectionFlags);


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

#endif /* __LISTS__ */

