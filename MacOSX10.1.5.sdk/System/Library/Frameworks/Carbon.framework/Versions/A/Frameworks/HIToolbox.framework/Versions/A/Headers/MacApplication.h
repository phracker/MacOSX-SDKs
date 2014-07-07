/*
     File:       HIToolbox/MacApplication.h
 
     Contains:   Application-level APIs
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MACAPPLICATION__
#define __MACAPPLICATION__

#ifndef __COREGRAPHICS__
#include <CoreGraphics/CoreGraphics.h>
#endif

#ifndef __QD__
#include <QD/QD.h>
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
 *  SetApplicationDockTileImage()
 *  
 *  Discussion:
 *    Sets the image for the tile in the dock that represents your
 *    application while it is running. If you set the image, it will
 *    revert back to its original image when your application
 *    terminates automatically. You do not need to manually restore it.
 *  
 *  Parameters:
 *    
 *    inImage:
 *      The image you wish to have as your tile image.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetApplicationDockTileImage(CGImageRef inImage);


/*
 *  OverlayApplicationDockTileImage()
 *  
 *  Discussion:
 *    Takes the image passed in and composites it on top of the current
 *    image of your application's dock tile. You might do this to put a
 *    standard badge over your application's icon to indicate something
 *    to the user.
 *  
 *  Parameters:
 *    
 *    inImage:
 *      The image you wish to overlay onto your tile image.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
OverlayApplicationDockTileImage(CGImageRef inImage);


/*
 *  RestoreApplicationDockTileImage()
 *  
 *  Discussion:
 *    Restores the tile for your appliation in the dock to its normal
 *    image (your application icon). You would use this if some overlay
 *    or change of the application icon needed to be removed.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RestoreApplicationDockTileImage(void);


/*
 *  BeginCGContextForApplicationDockTile()
 *  
 *  Discussion:
 *    Creates and returns a CGContextRef. You can use this context to
 *    draw into your application's dock tile with Quartz. You **MUST**
 *    call EndCGContextForApplicationDockTile and NOT CGEndContext when
 *    using this API, as it locks your application's tile in the dock.
 *    If you call CGEndContext, the dock will never know you are done
 *    with the tile.
 *  
 *  Result:
 *    An Quartz (Core Graphics) context reference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern CGContextRef 
BeginCGContextForApplicationDockTile(void);


/*
 *  EndCGContextForApplicationDockTile()
 *  
 *  Discussion:
 *    Ends the CG context for your application tile and frees the lock
 *    on the application dock tile. You **MUST** call this routine and
 *    NOT CGEndContext when using BeginCGContextForApplicationDockTile,
 *    as it locks your application's tile in the dock. If you call
 *    CGEndContext, the dock will never know you are done with the tile.
 *  
 *  Parameters:
 *    
 *    inContext:
 *      The context to end. The context is invalid after this call and
 *      should no longer be used.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
EndCGContextForApplicationDockTile(CGContextRef inContext);




/*
 *  BeginQDContextForApplicationDockTile()
 *  
 *  Discussion:
 *    Creates and returns a CGrafPtr for your application's tile in the
 *    dock. You can use this port to draw into your application's dock
 *    tile with Quickdraw. You **MUST** call
 *    EndQDContextForApplicationDockTile and NOT DisposePort when using
 *    this API, as it locks your application's tile in the dock. If you
 *    call DisposePort, the dock will never know you are done with the
 *    tile.
 *  
 *  Result:
 *    A Quickdraw port reference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern CGrafPtr 
BeginQDContextForApplicationDockTile(void);


/*
 *  EndQDContextForApplicationDockTile()
 *  
 *  Discussion:
 *    Disposes the Quickdraw port for your application tile and frees
 *    the lock on the application dock tile. You **MUST** call this
 *    routine and NOT DisposePort when using
 *    BeginQDContextForApplicationDockTile, else the dock will never
 *    know you are done with the tile.
 *  
 *  Parameters:
 *    
 *    inContext:
 *      The context to end. The context is invalid after this call and
 *      should no longer be used.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
EndQDContextForApplicationDockTile(CGrafPtr inContext);



/*
 *  SetApplicationDockTileMenu()
 *  
 *  Summary:
 *    Sets the menu that is displayed by the application's dock tile.
 *  
 *  Discussion:
 *    The Carbon Window Manager and the Dock will always automatically
 *    display a menu containing a list of the application's document
 *    windows. If the application wants to add other additional menu
 *    items, it can use the SetApplicationDockTileMenu API to provide
 *    those items. The items in the specified menu will be combined
 *    with the window title items. This API increments the refcount of
 *    the specified menu. Before the menu is actually displayed, it
 *    will receive kEventMenuPopulate, kEventMenuOpening, and
 *    kEventMenuEnableItems Carbon events, so any event handlers for
 *    these events may update the menu appropriately for the current
 *    state of the application. The application should set a command ID
 *    for each menu item in the dock tile menu, and when that item is
 *    chosen, a kEventCommandProcess Carbon event containing the item's
 *    command ID will be sent to the user focus target.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu to display, or NULL to remove the current dock tile
 *      menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetApplicationDockTileMenu(MenuRef inMenu);


/*
 *  GetApplicationDockTileMenu()
 *  
 *  Summary:
 *    Returns the menu that is displayed by the application's dock tile.
 *  
 *  Result:
 *    The application's dock tile menu, or NULL if none.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern MenuRef 
GetApplicationDockTileMenu(void);



/* This API needs to go into Quickdraw.h sometime...*/
/*
 *  CreateCGImageFromPixMaps()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCGImageFromPixMaps(
  PixMapHandle   inImage,
  PixMapHandle   inMask,
  CGImageRef *   outImage);




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

#endif /* __MACAPPLICATION__ */

