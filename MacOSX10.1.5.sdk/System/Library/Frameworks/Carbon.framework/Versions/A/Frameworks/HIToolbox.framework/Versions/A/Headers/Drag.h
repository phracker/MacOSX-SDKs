/*
     File:       HIToolbox/Drag.h
 
     Contains:   Drag and Drop Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1992-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DRAG__
#define __DRAG__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
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

/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG MANAGER DATA TYPES
  _________________________________________________________________________________________________________
*/

typedef struct OpaqueDragRef*           DragRef;
typedef UInt32                          DragItemRef;
typedef OSType                          FlavorType;
/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG ATTRIBUTES
  _________________________________________________________________________________________________________
*/
typedef UInt32 DragAttributes;
enum {
  kDragHasLeftSenderWindow      = (1L << 0), /* drag has left the source window since TrackDrag*/
  kDragInsideSenderApplication  = (1L << 1), /* drag is occurring within the sender application*/
  kDragInsideSenderWindow       = (1L << 2) /* drag is occurring within the sender window*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG BEHAVIORS
  _________________________________________________________________________________________________________
*/
typedef UInt32 DragBehaviors;
enum {
  kDragBehaviorNone             = 0,
  kDragBehaviorZoomBackAnimation = (1L << 0) /* do zoomback animation for failed drags (normally enabled).*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG IMAGE FLAGS
  _________________________________________________________________________________________________________
*/
typedef UInt32 DragImageFlags;
enum {
  kDragRegionAndImage           = (1L << 4) /* drag region and image*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG IMAGE TRANSLUCENCY LEVELS
  _________________________________________________________________________________________________________
*/

enum {
  kDragStandardTranslucency     = 0L,   /* 65% image translucency (standard)*/
  kDragDarkTranslucency         = 1L,   /* 50% image translucency*/
  kDragDarkerTranslucency       = 2L,   /* 25% image translucency*/
  kDragOpaqueTranslucency       = 3L    /* 0% image translucency (opaque)*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG DRAWING PROCEDURE MESSAGES
  _________________________________________________________________________________________________________
*/

typedef SInt16 DragRegionMessage;
enum {
  kDragRegionBegin              = 1,    /* initialize drawing*/
  kDragRegionDraw               = 2,    /* draw drag feedback*/
  kDragRegionHide               = 3,    /* hide drag feedback*/
  kDragRegionIdle               = 4,    /* drag feedback idle time*/
  kDragRegionEnd                = 5     /* end of drawing*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ ZOOM ACCELERATION
  _________________________________________________________________________________________________________
*/

typedef SInt16 ZoomAcceleration;
enum {
  kZoomNoAcceleration           = 0,    /* use linear interpolation*/
  kZoomAccelerate               = 1,    /* ramp up step size*/
  kZoomDecelerate               = 2     /* ramp down step size*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ FLAVOR FLAGS
  _________________________________________________________________________________________________________
*/

typedef UInt32 FlavorFlags;
enum {
  flavorSenderOnly              = (1 << 0), /* flavor is available to sender only*/
  flavorSenderTranslated        = (1 << 1), /* flavor is translated by sender*/
  flavorNotSaved                = (1 << 2), /* flavor should not be saved*/
  flavorSystemTranslated        = (1 << 8), /* flavor is translated by system*/
  flavorDataPromised            = (1 << 9) /* flavor data is promised by sender*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ FILE SYSTEM CONSTANTS
  _________________________________________________________________________________________________________
*/

enum {
  kDragFlavorTypeHFS            = 'hfs ', /* flavor type for HFS data*/
  kDragFlavorTypePromiseHFS     = 'phfs', /* flavor type for promised HFS data*/
  flavorTypeHFS                 = kDragFlavorTypeHFS, /* old name*/
  flavorTypePromiseHFS          = kDragFlavorTypePromiseHFS /* old name*/
};

enum {
  kDragPromisedFlavorFindFile   = 'rWm1', /* promisedFlavor value for Find File*/
  kDragPromisedFlavor           = 'fssP' /* promisedFlavor value for everything else*/
};

enum {
  kDragPseudoCreatorVolumeOrDirectory = 'MACS', /* "creator code" for volume or directory*/
  kDragPseudoFileTypeVolume     = 'disk', /* "file type" for volume*/
  kDragPseudoFileTypeDirectory  = 'fold' /* "file type" for directory*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ SPECIAL FLAVORS
  _________________________________________________________________________________________________________
*/

enum {
  flavorTypeDirectory           = 'diry' /* flavor type for AOCE directories*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ FLAVORS FOR FINDER 8.0 AND LATER
  _________________________________________________________________________________________________________
*/

enum {
  kFlavorTypeClippingName       = 'clnm', /* name hint for clipping file (preferred over 'clfn')*/
  kFlavorTypeClippingFilename   = 'clfn', /* name for clipping file*/
  kFlavorTypeDragToTrashOnly    = 'fdtt', /* for apps that want to allow dragging private data to the trash*/
  kFlavorTypeFinderNoTrackingBehavior = 'fntb' /* Finder completely ignores any drag containing this flavor*/
};

/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG TRACKING HANDLER MESSAGES
  _________________________________________________________________________________________________________
*/

typedef SInt16 DragTrackingMessage;
enum {
  kDragTrackingEnterHandler     = 1,    /* drag has entered handler*/
  kDragTrackingEnterWindow      = 2,    /* drag has entered window*/
  kDragTrackingInWindow         = 3,    /* drag is moving within window*/
  kDragTrackingLeaveWindow      = 4,    /* drag has exited window*/
  kDragTrackingLeaveHandler     = 5     /* drag has exited handler*/
};


/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG ACTIONS
  _________________________________________________________________________________________________________
*/

enum {
  kDragActionNothing            = 0L,
  kDragActionCopy               = 1L,
  kDragActionAlias              = (1L << 1),
  kDragActionGeneric            = (1L << 2),
  kDragActionPrivate            = (1L << 3),
  kDragActionMove               = (1L << 4),
  kDragActionDelete             = (1L << 5),
  kDragActionAll                = (long)0xFFFFFFFF
};

typedef UInt32                          DragActions;
/*
  _________________________________________________________________________________________________________
      
   ¥ HFS FLAVORS
  _________________________________________________________________________________________________________
*/
struct HFSFlavor {
  OSType              fileType;               /* file type */
  OSType              fileCreator;            /* file creator */
  UInt16              fdFlags;                /* Finder flags */
  FSSpec              fileSpec;               /* file system specification */
};
typedef struct HFSFlavor                HFSFlavor;
struct PromiseHFSFlavor {
  OSType              fileType;               /* file type */
  OSType              fileCreator;            /* file creator */
  UInt16              fdFlags;                /* Finder flags */
  FlavorType          promisedFlavor;         /* promised flavor containing an FSSpec */
};
typedef struct PromiseHFSFlavor         PromiseHFSFlavor;
/*
  _________________________________________________________________________________________________________
      
   ¥ APPLICATION-DEFINED DRAG HANDLER ROUTINES
  _________________________________________________________________________________________________________
*/
typedef CALLBACK_API( OSErr , DragTrackingHandlerProcPtr )(DragTrackingMessage message, WindowRef theWindow, void *handlerRefCon, DragRef theDrag);
typedef CALLBACK_API( OSErr , DragReceiveHandlerProcPtr )(WindowRef theWindow, void *handlerRefCon, DragRef theDrag);
typedef STACK_UPP_TYPE(DragTrackingHandlerProcPtr)              DragTrackingHandlerUPP;
typedef STACK_UPP_TYPE(DragReceiveHandlerProcPtr)               DragReceiveHandlerUPP;
/*
 *  NewDragTrackingHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragTrackingHandlerUPP
NewDragTrackingHandlerUPP(DragTrackingHandlerProcPtr userRoutine);

/*
 *  NewDragReceiveHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragReceiveHandlerUPP
NewDragReceiveHandlerUPP(DragReceiveHandlerProcPtr userRoutine);

/*
 *  DisposeDragTrackingHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragTrackingHandlerUPP(DragTrackingHandlerUPP userUPP);

/*
 *  DisposeDragReceiveHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragReceiveHandlerUPP(DragReceiveHandlerUPP userUPP);

/*
 *  InvokeDragTrackingHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeDragTrackingHandlerUPP(
  DragTrackingMessage     message,
  WindowRef               theWindow,
  void *                  handlerRefCon,
  DragRef                 theDrag,
  DragTrackingHandlerUPP  userUPP);

/*
 *  InvokeDragReceiveHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeDragReceiveHandlerUPP(
  WindowRef              theWindow,
  void *                 handlerRefCon,
  DragRef                theDrag,
  DragReceiveHandlerUPP  userUPP);

/*
  _________________________________________________________________________________________________________
      
   ¥ APPLICATION-DEFINED ROUTINES
  _________________________________________________________________________________________________________
*/
typedef CALLBACK_API( OSErr , DragSendDataProcPtr )(FlavorType theType, void *dragSendRefCon, DragItemRef theItemRef, DragRef theDrag);
typedef CALLBACK_API( OSErr , DragInputProcPtr )(Point *mouse, SInt16 *modifiers, void *dragInputRefCon, DragRef theDrag);
typedef CALLBACK_API( OSErr , DragDrawingProcPtr )(DragRegionMessage message, RgnHandle showRegion, Point showOrigin, RgnHandle hideRegion, Point hideOrigin, void *dragDrawingRefCon, DragRef theDrag);
typedef STACK_UPP_TYPE(DragSendDataProcPtr)                     DragSendDataUPP;
typedef STACK_UPP_TYPE(DragInputProcPtr)                        DragInputUPP;
typedef STACK_UPP_TYPE(DragDrawingProcPtr)                      DragDrawingUPP;
/*
 *  NewDragSendDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragSendDataUPP
NewDragSendDataUPP(DragSendDataProcPtr userRoutine);

/*
 *  NewDragInputUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragInputUPP
NewDragInputUPP(DragInputProcPtr userRoutine);

/*
 *  NewDragDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragDrawingUPP
NewDragDrawingUPP(DragDrawingProcPtr userRoutine);

/*
 *  DisposeDragSendDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragSendDataUPP(DragSendDataUPP userUPP);

/*
 *  DisposeDragInputUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragInputUPP(DragInputUPP userUPP);

/*
 *  DisposeDragDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragDrawingUPP(DragDrawingUPP userUPP);

/*
 *  InvokeDragSendDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeDragSendDataUPP(
  FlavorType       theType,
  void *           dragSendRefCon,
  DragItemRef      theItemRef,
  DragRef          theDrag,
  DragSendDataUPP  userUPP);

/*
 *  InvokeDragInputUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeDragInputUPP(
  Point *       mouse,
  SInt16 *      modifiers,
  void *        dragInputRefCon,
  DragRef       theDrag,
  DragInputUPP  userUPP);

/*
 *  InvokeDragDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeDragDrawingUPP(
  DragRegionMessage  message,
  RgnHandle          showRegion,
  Point              showOrigin,
  RgnHandle          hideRegion,
  Point              hideOrigin,
  void *             dragDrawingRefCon,
  DragRef            theDrag,
  DragDrawingUPP     userUPP);

/*
  _________________________________________________________________________________________________________
      
   ¥ INSTALLING AND REMOVING HANDLERS API'S
  _________________________________________________________________________________________________________
*/

/*
 *  InstallTrackingHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
InstallTrackingHandler(
  DragTrackingHandlerUPP   trackingHandler,
  WindowRef                theWindow,
  void *                   handlerRefCon);


/*
 *  InstallReceiveHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
InstallReceiveHandler(
  DragReceiveHandlerUPP   receiveHandler,
  WindowRef               theWindow,
  void *                  handlerRefCon);


/*
 *  RemoveTrackingHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
RemoveTrackingHandler(
  DragTrackingHandlerUPP   trackingHandler,
  WindowRef                theWindow);


/*
 *  RemoveReceiveHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
RemoveReceiveHandler(
  DragReceiveHandlerUPP   receiveHandler,
  WindowRef               theWindow);


/*
  _________________________________________________________________________________________________________
      
   ¥ CREATING & DISPOSING
  _________________________________________________________________________________________________________
*/

/*
 *  NewDrag()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
NewDrag(DragRef * theDrag);


/*
 *  DisposeDrag()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
DisposeDrag(DragRef theDrag);


/*
  _________________________________________________________________________________________________________
      
   ¥ ADDING DRAG ITEM FLAVORS
  _________________________________________________________________________________________________________
*/

/*
    The method for setting Drag Manager promises differs from that for Scrap Manger promises.  This chart
    describes the method for setting drag promises via AddDragItemFlavor().
    
        dataPtr         dataSize                                result
     pointer value  actual data size    The data of size dataSize pointed to by dataPtr is added to the drag.
        NULL             ignored        A promise is placed on the drag.
*/
/*
 *  AddDragItemFlavor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
AddDragItemFlavor(
  DragRef       theDrag,
  DragItemRef   theItemRef,
  FlavorType    theType,
  const void *  dataPtr,
  Size          dataSize,
  FlavorFlags   theFlags);


/*
 *  SetDragItemFlavorData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDragItemFlavorData(
  DragRef       theDrag,
  DragItemRef   theItemRef,
  FlavorType    theType,
  const void *  dataPtr,
  Size          dataSize,
  UInt32        dataOffset);


/*
  _________________________________________________________________________________________________________
      
   ¥ PROVIDING CALLBACK PROCEDURES
  _________________________________________________________________________________________________________
*/

/*
 *  SetDragSendProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDragSendProc(
  DragRef           theDrag,
  DragSendDataUPP   sendProc,
  void *            dragSendRefCon);



/*
 *  SetDragInputProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDragInputProc(
  DragRef        theDrag,
  DragInputUPP   inputProc,
  void *         dragInputRefCon);


/*
 *  SetDragDrawingProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDragDrawingProc(
  DragRef          theDrag,
  DragDrawingUPP   drawingProc,
  void *           dragDrawingRefCon);


/*
  _________________________________________________________________________________________________________
      
   ¥ SETTING THE DRAG IMAGE
  _________________________________________________________________________________________________________
*/

/*
 *  SetDragImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 7.5 and later
 */
extern OSErr 
SetDragImage(
  DragRef          theDrag,
  PixMapHandle     imagePixMap,
  RgnHandle        imageRgn,
  Point            imageOffsetPt,
  DragImageFlags   theImageFlags);



/*
  _________________________________________________________________________________________________________
      
   ¥ ALTERING THE BEHAVIOR OF A DRAG
  _________________________________________________________________________________________________________
*/
/*
 *  ChangeDragBehaviors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 9.0 and later
 */
extern OSErr 
ChangeDragBehaviors(
  DragRef         theDrag,
  DragBehaviors   inBehaviorsToSet,
  DragBehaviors   inBehaviorsToClear);


/*
  _________________________________________________________________________________________________________
      
   ¥ PERFORMING A DRAG
  _________________________________________________________________________________________________________
*/
/*
 *  TrackDrag()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
TrackDrag(
  DragRef              theDrag,
  const EventRecord *  theEvent,
  RgnHandle            theRegion);



/*
  _________________________________________________________________________________________________________
      
   ¥ GETTING DRAG ITEM INFORMATION
  _________________________________________________________________________________________________________
*/

/*
 *  CountDragItems()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
CountDragItems(
  DragRef   theDrag,
  UInt16 *  numItems);


/*
 *  GetDragItemReferenceNumber()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDragItemReferenceNumber(
  DragRef        theDrag,
  UInt16         index,
  DragItemRef *  theItemRef);


/*
 *  CountDragItemFlavors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
CountDragItemFlavors(
  DragRef       theDrag,
  DragItemRef   theItemRef,
  UInt16 *      numFlavors);


/*
 *  GetFlavorType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetFlavorType(
  DragRef       theDrag,
  DragItemRef   theItemRef,
  UInt16        index,
  FlavorType *  theType);


/*
 *  GetFlavorFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetFlavorFlags(
  DragRef        theDrag,
  DragItemRef    theItemRef,
  FlavorType     theType,
  FlavorFlags *  theFlags);


/*
 *  GetFlavorDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetFlavorDataSize(
  DragRef       theDrag,
  DragItemRef   theItemRef,
  FlavorType    theType,
  Size *        dataSize);


/*
 *  GetFlavorData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetFlavorData(
  DragRef       theDrag,
  DragItemRef   theItemRef,
  FlavorType    theType,
  void *        dataPtr,
  Size *        dataSize,
  UInt32        dataOffset);


/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG ITEM BOUNDS
  _________________________________________________________________________________________________________
*/

/*
 *  GetDragItemBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDragItemBounds(
  DragRef       theDrag,
  DragItemRef   theItemRef,
  Rect *        itemBounds);


/*
 *  SetDragItemBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDragItemBounds(
  DragRef       theDrag,
  DragItemRef   theItemRef,
  const Rect *  itemBounds);


/*
  _________________________________________________________________________________________________________
      
   ¥ DROP LOCATIONS
  _________________________________________________________________________________________________________
*/

/*
 *  GetDropLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDropLocation(
  DragRef   theDrag,
  AEDesc *  dropLocation);


/*
 *  SetDropLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDropLocation(
  DragRef         theDrag,
  const AEDesc *  dropLocation);


/*
  _________________________________________________________________________________________________________
      
   ¥ GETTING INFORMATION ABOUT A DRAG
  _________________________________________________________________________________________________________
*/

/*
 *  GetDragAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDragAttributes(
  DragRef           theDrag,
  DragAttributes *  flags);


/*
 *  GetDragMouse()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDragMouse(
  DragRef   theDrag,
  Point *   mouse,
  Point *   globalPinnedMouse);


/*
 *  SetDragMouse()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDragMouse(
  DragRef   theDrag,
  Point     globalPinnedMouse);


/*
 *  GetDragOrigin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDragOrigin(
  DragRef   theDrag,
  Point *   globalInitialMouse);


/*
 *  GetDragModifiers()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDragModifiers(
  DragRef   theDrag,
  SInt16 *  modifiers,
  SInt16 *  mouseDownModifiers,
  SInt16 *  mouseUpModifiers);


/*
  _________________________________________________________________________________________________________
      
   ¥ ACCESSING DRAG ACTIONS
  _________________________________________________________________________________________________________
*/

/*
 *  GetDragAllowableActions()
 *  
 *  Discussion:
 *    Gets the actions the drag sender has allowed the receiver to
 *    perform. These are not requirements, but they highly suggested
 *    actions which allows the drag receiver to improve harmony across
 *    the system.  The allowable actions received are always those
 *    local to the caller's process.
 *  
 *  Parameters:
 *    
 *    theDrag:
 *      The drag reference from which to retreive the allowable drag
 *      actions.
 *    
 *    outActions:
 *      A pointer to receive the field of allowable drag actions.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDragAllowableActions(
  DragRef        theDrag,
  DragActions *  outActions);


/*
 *  SetDragAllowableActions()
 *  
 *  Discussion:
 *    Sets the actions the receiver of the drag is allowed to perform. 
 *    These are not requirements, but they highly suggested actions
 *    which allows the drag receiver to improve harmony across the
 *    system.  The caller may select wether these drag actions apply to
 *    a local or remote process.
 *  
 *  Parameters:
 *    
 *    theDrag:
 *      The drag reference in which to set the allowable drag actions.
 *    
 *    inActions:
 *      A field of allowable drag actions to be set.
 *    
 *    isLocal:
 *      A boolean value allowing the drag sender to distinguish between
 *      those drag actions allowable by the local receiver versus a
 *      remote one.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDragAllowableActions(
  DragRef       theDrag,
  DragActions   inActions,
  Boolean       isLocal);


/*
 *  GetDragDropAction()
 *  
 *  Discussion:
 *    Gets the action performed by the receiver of the drag.  More than
 *    one action may have been performed.
 *  
 *  Parameters:
 *    
 *    theDrag:
 *      The drag reference from which to retreive the performed drop
 *      action.
 *    
 *    outAction:
 *      A pointer to receive the drag action performed.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDragDropAction(
  DragRef        theDrag,
  DragActions *  outAction);


/*
 *  SetDragDropAction()
 *  
 *  Discussion:
 *    Sets the action performed by the receiver of the drag.  More than
 *    one action may be performed.
 *  
 *  Parameters:
 *    
 *    theDrag:
 *      The drag reference in which to set the performed drop action.
 *    
 *    inAction:
 *      The drop action performed.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDragDropAction(
  DragRef       theDrag,
  DragActions   inAction);


/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG HIGHLIGHTING
  _________________________________________________________________________________________________________
*/

/*
 *  ShowDragHilite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
ShowDragHilite(
  DragRef     theDrag,
  RgnHandle   hiliteFrame,
  Boolean     inside);


/*
 *  HideDragHilite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
HideDragHilite(DragRef theDrag);


/*
 *  DragPreScroll()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
DragPreScroll(
  DragRef   theDrag,
  SInt16    dH,
  SInt16    dV);


/*
 *  DragPostScroll()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
DragPostScroll(DragRef theDrag);


/*
 *  UpdateDragHilite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
UpdateDragHilite(
  DragRef     theDrag,
  RgnHandle   updateRgn);


/*
 *  GetDragHiliteColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 7.5 and later
 */
extern OSErr 
GetDragHiliteColor(
  WindowRef   window,
  RGBColor *  color);



/*
  _________________________________________________________________________________________________________
      
   ¥ UTILITIES
  _________________________________________________________________________________________________________
*/


/*
 *  WaitMouseMoved()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern Boolean 
WaitMouseMoved(Point initialMouse);



/*
 *  ZoomRects()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
ZoomRects(
  const Rect *       fromRect,
  const Rect *       toRect,
  SInt16             zoomSteps,
  ZoomAcceleration   acceleration);


/*
 *  ZoomRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
ZoomRegion(
  RgnHandle          region,
  Point              zoomDistance,
  SInt16             zoomSteps,
  ZoomAcceleration   acceleration);



/*
  _________________________________________________________________________________________________________
   ¥ OLD NAMES
     These are provided for compatiblity with older source bases.  It is recommended to not use them since
     they may removed from this interface file at any time.
  _________________________________________________________________________________________________________
*/


typedef DragRef                         DragReference;
typedef DragItemRef                     ItemReference;
#if OLDROUTINENAMES
enum {
  dragHasLeftSenderWindow       = kDragHasLeftSenderWindow, /* drag has left the source window since TrackDrag */
  dragInsideSenderApplication   = kDragInsideSenderApplication, /* drag is occurring within the sender application */
  dragInsideSenderWindow        = kDragInsideSenderWindow /* drag is occurring within the sender window */
};

enum {
  dragTrackingEnterHandler      = kDragTrackingEnterHandler, /* drag has entered handler */
  dragTrackingEnterWindow       = kDragTrackingEnterWindow, /* drag has entered window */
  dragTrackingInWindow          = kDragTrackingInWindow, /* drag is moving within window */
  dragTrackingLeaveWindow       = kDragTrackingLeaveWindow, /* drag has exited window */
  dragTrackingLeaveHandler      = kDragTrackingLeaveHandler /* drag has exited handler */
};

enum {
  dragRegionBegin               = kDragRegionBegin, /* initialize drawing */
  dragRegionDraw                = kDragRegionDraw, /* draw drag feedback */
  dragRegionHide                = kDragRegionHide, /* hide drag feedback */
  dragRegionIdle                = kDragRegionIdle, /* drag feedback idle time */
  dragRegionEnd                 = kDragRegionEnd /* end of drawing */
};

enum {
  zoomNoAcceleration            = kZoomNoAcceleration, /* use linear interpolation */
  zoomAccelerate                = kZoomAccelerate, /* ramp up step size */
  zoomDecelerate                = kZoomDecelerate /* ramp down step size */
};

enum {
  kDragStandardImage            = kDragStandardTranslucency, /* 65% image translucency (standard)*/
  kDragDarkImage                = kDragDarkTranslucency, /* 50% image translucency*/
  kDragDarkerImage              = kDragDarkerTranslucency, /* 25% image translucency*/
  kDragOpaqueImage              = kDragOpaqueTranslucency /* 0% image translucency (opaque)*/
};

#endif  /* OLDROUTINENAMES */


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

#endif /* __DRAG__ */

