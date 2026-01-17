/*
     File:       HIToolbox/Drag.h
 
     Contains:   Drag and Drop Interfaces.
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 1992-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DRAG__
#define __DRAG__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __HIGEOMETRY__
#include <HIToolbox/HIGeometry.h>
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

/*
 *  DragImageFlags
 *  
 *  Summary:
 *    Parameters to SetDragImage and SetDragImageWithCGImage.
 */
typedef UInt32 DragImageFlags;
enum {

  /*
   * Indicates that the outline region passed to TrackDrag should be
   * drawn onscreen, in addition to the translucent drag image.
   */
  kDragRegionAndImage           = 1 << 4,

  /*
   * Indicates that the image and offset being passed in are already at
   * device resolution, and the image should be drawn as-is. If this
   * option is not specified, the image will be scaled according to the
   * user's current scaling factor. Available in Mac OS X 10.4 and
   * later.
   */
  kDragDoNotScaleImage          = 1 << 5
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
  kFlavorTypeUnicodeClippingName = 'ucln', /* unicode name hint for clipping file (preferred over 'uclf')*/
  kFlavorTypeUnicodeClippingFilename = 'uclf', /* unicode name for clipping file*/
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
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
   ¥ STANDARD DROP LOCATIONS
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/


/*
 *  Summary:
 *    Standard Drop Location constants
 *  
 *  Discussion:
 *    The following constants define common "meta" drop locations.
 */
enum {

  /*
   * The drop location was in the trash.  This is set when a drag is
   * dropped on the trash icon.  Setting this standard drop location
   * sets the traditional drop location to an alias to the trash folder
   * automatically.
   */
  kDragStandardDropLocationTrash = 'trsh',

  /*
   * The receiver did not specify a drop lcoation. This is the default.
   */
  kDragStandardDropLocationUnknown = 'unkn'
};

typedef OSType                          StandardDropLocation;
/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG ACTIONS
  _________________________________________________________________________________________________________
*/

/*
 *  Summary:
 *    Drag Action constants
 *  
 *  Discussion:
 *    The following constants define, in a general way, what actions a
 *    drag should or has performed.  Some drag actions enforce a mode
 *    of operation while others are flexible suggestions.  These
 *    constants are used in conjunction with the
 *    Get/SetDragAllowableActions() and Get/SetDragDropAction() APIs. 
 *    Adopting the Drag Action APIs increases compatability with the
 *    Cocoa drag operation model.
 */
enum {

  /*
   * Suggests nothing should be/was done with the data in a drag.  When
   * set as an allowable action for remote drags, the drag will not be
   * sent to apps other than the sender.
   */
  kDragActionNothing            = 0L,

  /*
   * Suggests the data contained within the drag can be/was copied.
   */
  kDragActionCopy               = 1L,

  /*
   * Suggests the data contained within the drag can be/is shared.
   */
  kDragActionAlias              = (1L << 1),

  /*
   * Suggests the drag action is can be defined by the drag destination
   * or was not defined by the drag destination.
   */
  kDragActionGeneric            = (1L << 2),

  /*
   * Suggests the drag action should be negotiated privately between
   * the drag source and destination.
   */
  kDragActionPrivate            = (1L << 3),

  /*
   * Description forthcoming.
   */
  kDragActionMove               = (1L << 4),

  /*
   * Description forthcoming.
   */
  kDragActionDelete             = (1L << 5),

  /*
   * All of the above drag actions are allowed.
   */
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
NewDragTrackingHandlerUPP(DragTrackingHandlerProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDragReceiveHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragReceiveHandlerUPP
NewDragReceiveHandlerUPP(DragReceiveHandlerProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDragTrackingHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragTrackingHandlerUPP(DragTrackingHandlerUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDragReceiveHandlerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragReceiveHandlerUPP(DragReceiveHandlerUPP userUPP)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  DragTrackingHandlerUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  DragReceiveHandlerUPP  userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
NewDragSendDataUPP(DragSendDataProcPtr userRoutine)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDragInputUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragInputUPP
NewDragInputUPP(DragInputProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDragDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragDrawingUPP
NewDragDrawingUPP(DragDrawingProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDragSendDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragSendDataUPP(DragSendDataUPP userUPP)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDragInputUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragInputUPP(DragInputUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDragDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragDrawingUPP(DragDrawingUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  DragSendDataUPP  userUPP)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  DragInputUPP  userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  DragDrawingUPP     userUPP)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
  _________________________________________________________________________________________________________
      
   ¥ INSTALLING AND REMOVING HANDLERS API'S
  _________________________________________________________________________________________________________
*/

/*
 *  InstallTrackingHandler()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  void *                   handlerRefCon)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InstallReceiveHandler()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  void *                  handlerRefCon)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveTrackingHandler()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
RemoveTrackingHandler(
  DragTrackingHandlerUPP   trackingHandler,
  WindowRef                theWindow)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveReceiveHandler()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
RemoveReceiveHandler(
  DragReceiveHandlerUPP   receiveHandler,
  WindowRef               theWindow)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ CREATING & DISPOSING
  _________________________________________________________________________________________________________
*/

/*
 *  NewDrag()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
NewDrag(DragRef * theDrag)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeDrag()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
DisposeDrag(DragRef theDrag)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG PASTEBOARD
  _________________________________________________________________________________________________________
*/

/*
 *  NewDragWithPasteboard()
 *  
 *  Discussion:
 *    Creates a new Drag reference containing the pasteboard reference
 *    provided.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inPasteboard:
 *      A pasteboard created by the drag sender for use with the drag.
 *      Items may be added to the pasteboard via the Pasteboard Manager
 *      API either before or after this routine is called. It is still
 *      possible to add data via the Drag Manager API, but only after
 *      this routine is called. It is the drag sender's responsibility
 *      to clear the pasteboard before adding items. It is also the
 *      drag sender's responsibility to release the pasteboard.  This
 *      may be done at any time after this routine is called. The
 *      pasteboard is retained by the Drag Manager for the duration of
 *      the drag.
 *    
 *    outDrag:
 *      A drag reference which receives the newly created drag.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NewDragWithPasteboard(
  PasteboardRef   inPasteboard,
  DragRef *       outDrag)                                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GetDragPasteboard()
 *  
 *  Discussion:
 *    Returns the pasteboard reference contained within the provided
 *    drag reference. This routine may be called by a drag sender or
 *    receiver at any point after a valid drag reference has been
 *    created/received.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inDrag:
 *      The drag reference containing the requested pasteboard.
 *    
 *    outPasteboard:
 *      A pasteboard reference which receives the pasteboard contained
 *      by the drag.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDragPasteboard(
  DragRef          inDrag,
  PasteboardRef *  outPasteboard)                             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


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
 *  Mac OS X threading:
 *    Not thread safe
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
  FlavorFlags   theFlags)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDragItemFlavorData()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  UInt32        dataOffset)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ PROVIDING CALLBACK PROCEDURES
  _________________________________________________________________________________________________________
*/

/*
 *  SetDragSendProc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  void *            dragSendRefCon)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetDragInputProc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  void *         dragInputRefCon)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDragDrawingProc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  void *           dragDrawingRefCon)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ SETTING THE DRAG IMAGE
  _________________________________________________________________________________________________________
*/

/*
 *  SetDragImageWithCGImage()
 *  
 *  Discussion:
 *    Used by the sender of the drag to set the image, in CGImage
 *    format, to be displayed as user feedback during the drag.  This
 *    API may be called  at any point during the drag to update the
 *    image.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inDrag:
 *      The drag reference for which the image will be displayed.
 *    
 *    inCGImage:
 *      The CGImageRef for the image to be displayed during the drag. 
 *      The image is retained internally by the Drag Manager for the
 *      duration of the drag so it may be released by the client
 *      immediately after setting.
 *    
 *    inImageOffsetPt:
 *      A pointer to the offset from the mouse to the upper left of the
 *      image (normally expressed in negative values).  This differs
 *      from the usage of the offset passed to SetDragImage().  Here,
 *      an offset of ( -30, -30 ) will center a 60x60 pixel image on
 *      the drag mouse.
 *    
 *    inImageFlags:
 *      The flags determining image drawing during the drag.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDragImageWithCGImage(
  DragRef          inDrag,
  CGImageRef       inCGImage,
  const HIPoint *  inImageOffsetPt,
  DragImageFlags   inImageFlags)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ ALTERING THE BEHAVIOR OF A DRAG
  _________________________________________________________________________________________________________
*/
/*
 *  ChangeDragBehaviors()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  DragBehaviors   inBehaviorsToClear)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ PERFORMING A DRAG
  _________________________________________________________________________________________________________
*/
/*
 *  TrackDrag()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  RgnHandle            theRegion)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  _________________________________________________________________________________________________________
      
   ¥ GETTING DRAG ITEM INFORMATION
  _________________________________________________________________________________________________________
*/

/*
 *  CountDragItems()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
CountDragItems(
  DragRef   theDrag,
  UInt16 *  numItems)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDragItemReferenceNumber()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  DragItemRef *  theItemRef)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CountDragItemFlavors()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  UInt16 *      numFlavors)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFlavorType()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  FlavorType *  theType)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFlavorFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  FlavorFlags *  theFlags)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFlavorDataSize()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  Size *        dataSize)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFlavorData()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  UInt32        dataOffset)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG ITEM BOUNDS
  _________________________________________________________________________________________________________
*/

/*
 *  GetDragItemBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  Rect *        itemBounds)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDragItemBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  const Rect *  itemBounds)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ DROP LOCATIONS
  _________________________________________________________________________________________________________
*/

/*
 *  GetDropLocation()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDropLocation(
  DragRef   theDrag,
  AEDesc *  dropLocation)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDropLocation()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDropLocation(
  DragRef         theDrag,
  const AEDesc *  dropLocation)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ STANDARD DROP LOCATIONS
  _________________________________________________________________________________________________________
*/
/*
 *  GetStandardDropLocation()
 *  
 *  Discussion:
 *    Gets the standard drop location that was set by the receiver of
 *    the drag.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    theDrag:
 *      The drag reference from which to retrieve the allowable drag
 *      actions.
 *    
 *    outDropLocation:
 *      A pointer to the standard drop location, set by the receiver,
 *      representing the location where the drag was dropped.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetStandardDropLocation(
  DragRef                 theDrag,
  StandardDropLocation *  outDropLocation)                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SetStandardDropLocation()
 *  
 *  Discussion:
 *    Used by the receiver of the drag to set the standard drop
 *    location.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    theDrag:
 *      The drag reference from which to retrieve the allowable drag
 *      actions.
 *    
 *    dropLocation:
 *      The standard drop location representing the location where the
 *      drag was dropped.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetStandardDropLocation(
  DragRef                theDrag,
  StandardDropLocation   dropLocation)                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ GETTING INFORMATION ABOUT A DRAG
  _________________________________________________________________________________________________________
*/

/*
 *  GetDragAttributes()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDragAttributes(
  DragRef           theDrag,
  DragAttributes *  flags)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDragMouse()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  Point *   globalPinnedMouse)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDragMouse()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
SetDragMouse(
  DragRef   theDrag,
  Point     globalPinnedMouse)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDragOrigin()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
GetDragOrigin(
  DragRef   theDrag,
  Point *   globalInitialMouse)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDragModifiers()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  SInt16 *  mouseUpModifiers)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
 *  Mac OS X threading:
 *    Not thread safe
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
  DragActions *  outActions)                                  AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


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
 *  Mac OS X threading:
 *    Not thread safe
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
  Boolean       isLocal)                                      AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  GetDragDropAction()
 *  
 *  Discussion:
 *    Gets the action performed by the receiver of the drag.  More than
 *    one action may have been performed.
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  DragActions *  outAction)                                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  SetDragDropAction()
 *  
 *  Discussion:
 *    Sets the action performed by the receiver of the drag.  More than
 *    one action may be performed.
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  DragActions   inAction)                                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
  _________________________________________________________________________________________________________
      
   ¥ DRAG HIGHLIGHTING
  _________________________________________________________________________________________________________
*/

/*
 *  ShowDragHilite()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  Boolean     inside)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HideDragHilite()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
HideDragHilite(DragRef theDrag)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DragPreScroll()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  SInt16    dV)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DragPostScroll()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
DragPostScroll(DragRef theDrag)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UpdateDragHilite()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
UpdateDragHilite(
  DragRef     theDrag,
  RgnHandle   updateRgn)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDragHiliteColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 7.5 and later
 */
extern OSErr 
GetDragHiliteColor(
  WindowRef   window,
  RGBColor *  color)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  _________________________________________________________________________________________________________
      
   ¥ UTILITIES
  _________________________________________________________________________________________________________
*/


/*
 *  WaitMouseMoved()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern Boolean 
WaitMouseMoved(Point initialGlobalMouse)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  ZoomRects()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  ZoomAcceleration   acceleration)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ZoomRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
  ZoomAcceleration   acceleration)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*--------------------------------------------------------------------------------------*/
/*  ¥ DEPRECATED                                                                        */
/*                                                                                      */
/*  All functions below this point are either deprecated (they continue to function     */
/*  but are not the most modern nor most efficient solution to a problem), or they are  */
/*  completely unavailable on Mac OS X.                                                 */
/*--------------------------------------------------------------------------------------*/


/*
 *  SetDragImage()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Applications should use SetDragImageWithCGImage instead.
 *  
 *  Summary:
 *    Associates an image with a drag reference.
 *  
 *  Discussion:
 *    Used by the sender of the drag to set the image, in PixMapHandle
 *    format, to be displayed as user feedback during the drag.  This
 *    API may be called  at any point during the drag to update the
 *    image.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inDrag:
 *      The drag reference for which the image will be displayed.
 *    
 *    inImagePixMap:
 *      The PixMapHandle for the image to be displayed during the drag.
 *    
 *    inImageRgn:
 *      A mask describing the portion of the PixMap contained in the
 *      imagePixMap parameter which contains the drag image. Pass NULL
 *      for inImageRgn if the entire PixMap, including white space,
 *      should be dragged.
 *    
 *    inImageOffsetPt:
 *      The offset required to move the PixMap specified in the
 *      imagePixMap parameter to the global coordinates where the image
 *      initially appears. If this parameter is (0,0), the PixMap
 *      should already be in global coordinates.
 *    
 *    inImageFlags:
 *      Flags controlling the appearance of the drag image.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 7.5 and later
 */
extern OSErr 
SetDragImage(
  DragRef          inDrag,
  PixMapHandle     inImagePixMap,
  RgnHandle        inImageRgn,
  Point            inImageOffsetPt,
  DragImageFlags   inImageFlags)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



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


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __DRAG__ */

