/*
     File:       HIToolbox/HIToolbar.h
 
     Contains:   Toolbar and Toolbar Item API
 
     Version:    HIToolbox-145.48~1
 
     Copyright:  © 2001-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __HITOOLBAR__
#define __HITOOLBAR__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __HIOBJECT__
#include <HIToolbox/HIObject.h>
#endif

#ifndef __MENUS__
#include <HIToolbox/Menus.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef HIObjectRef                     HIToolbarRef;
typedef HIObjectRef                     HIToolbarItemRef;
/*----------------------------------------------------------------------------------*/
/* Config data keys used in HIToolbarSetItemsWithIdentifiers                        */
/*----------------------------------------------------------------------------------*/
#define kHIToolbarIdentifierKey         CFSTR("identifier")
#define kHIToolbarDataKey               CFSTR("data")
/*----------------------------------------------------------------------------------*/
/* Standard Toolbox-provided item identifiers                                       */
/*----------------------------------------------------------------------------------*/

#define kHIToolbarSeparatorIdentifier   CFSTR("com.apple.hitoolbox.toolbar.separator")
#define kHIToolbarSpaceIdentifier       CFSTR("com.apple.hitoolbox.toolbar.space")
#define kHIToolbarFlexibleSpaceIdentifier  CFSTR("com.apple.hitoolbox.toolbar.flexiblespace")
#define kHIToolbarCustomizeIdentifier   CFSTR("com.apple.hitoolbox.toolbar.customize")
#define kHIToolbarPrintItemIdentifier   CFSTR("com.apple.hitoolbox.toolbar.print")
#define kHIToolbarFontsItemIdentifier   CFSTR("com.apple.hitoolbox.toolbar.fonts")



/*
 *  Summary:
 *    Toolbar Display Mode
 */
enum {

  /*
   * This indicates to use the default display mode. Currently, this is
   * defined as being both icon and label, but could change in the
   * future.
   */
  kHIToolbarDisplayModeDefault  = 0,

  /*
   * This indicates to display the image as well as the label of the
   * toolbar items.
   */
  kHIToolbarDisplayModeIconAndLabel = 1,

  /*
   * This indicates that only the image should be shown.
   */
  kHIToolbarDisplayModeIconOnly = 2,

  /*
   * This indicates that only the label should be shown.
   */
  kHIToolbarDisplayModeLabelOnly = 3
};

typedef UInt32                          HIToolbarDisplayMode;

/*
 *  Summary:
 *    Toolbar Display Size
 */
enum {

  /*
   * This indicates to use the default display size. Currently, this is
   * defined as using 32 x 32 icons ("normal" size).
   */
  kHIToolbarDisplaySizeDefault  = 0,

  /*
   * This size uses a larger text and icon size.
   */
  kHIToolbarDisplaySizeNormal   = 1,

  /*
   * This size uses a smaller text and icon size.
   */
  kHIToolbarDisplaySizeSmall    = 2
};

typedef UInt32                          HIToolbarDisplaySize;

/*
 *  Summary:
 *    Toolbar Attributes
 */
enum {

  /*
   * Pass this to indicate no attributes at all.
   */
  kHIToolbarNoAttributes        = 0,

  /*
   * Pass this attribute to allow the toolbar to save its configuration
   * automatically to your application's preferences. You must make
   * sure to synchronize the prefs at some point to ensure it gets
   * written to disk. The toolbar will also read its config from the
   * prefs if this attribute is set.
   */
  kHIToolbarAutoSavesConfig     = (1 << 0),

  /*
   * This attribute indicates that the toolbar is configurable, i.e.
   * the user can drag items around and bring up the configuration
   * palette, etc.
   */
  kHIToolbarIsConfigurable      = (1 << 1),
  kHIToolbarValidAttrs          = kHIToolbarAutoSavesConfig | kHIToolbarIsConfigurable
};



/*
 *  Summary:
 *    Toolbar Commands
 */
enum {

  /*
   * Sending this to a window with a toolbar will cause the
   * configuration sheet to appear. You can set a menu item's command
   * to this command ID and it will be handled and updated
   * automatically for you.
   */
  kHICommandCustomizeToolbar    = 'tcfg',

  /*
   * This command causes a window's toolbar to be shown. You can set a
   * menu item's command to this ID and it will be handled and updated
   * automatically for you.
   */
  kHICommandShowToolbar         = 'tbsh',

  /*
   * This command causes a window's toolbar to be hidden. You can set a
   * menu item's command to this ID and it will be handled and updated
   * automatically for you.
   */
  kHICommandHideToolbar         = 'tbhd',

  /*
   * This command, when specified as a toolbar itemÕs command ID, will
   * cause a kEventToolbarItemPerformAction event to be generated when
   * the toolbar itemÕs menu item in the toolbar overflow menu is
   * selected. If the item has any other command ID, a
   * kEventCommandProcess event will be generated instead, containing
   * the itemÕs command ID.
   */
  kHIToolbarCommandPressAction  = 'tbpr'
};


/*
    kEventClassToolbar quick reference:
    
    kEventToolbarGetDefaultIdentifiers      = 1,
    kEventToolbarGetAllowedIdentifiers      = 2,
    kEventToolbarCreateItemWithIdentifier   = 3,
    kEventToolbarCreateItemFromDrag         = 4,
    kEventToolbarItemAdded                  = 5,
    kEventToolbarItemRemoved                = 6,
    kEventToolbarDisplayModeChanged         = 7,
    kEventToolbarDisplaySizeChanged         = 8,
    kEventToolbarLayoutChanged              = 9,
    kEventToolbarBeginMultiChange           = 12,
    kEventToolbarEndMultiChange             = 13
*/
/* Toolbar event parameters and types*/
enum {
  kEventParamToolbar            = 'tbar', /* typeHIToolbarRef*/
  kEventParamToolbarItem        = 'tbit', /* typeHIToolbarItemRef*/
  kEventParamToolbarItemIdentifier = 'tbii', /* typeCFStringRef*/
  kEventParamToolbarItemConfigData = 'tbid', /* typeCFTypeRef*/
  typeHIToolbarRef              = 'tbar', /* HIToolbarRef*/
  typeHIToolbarItemRef          = 'tbit' /* HIToolbarItemRef*/
};

/*
 *  kEventClassToolbar / kEventToolbarGetDefaultIdentifiers
 *  
 *  Summary:
 *    This event is sent to the delegate to get a list of all of the
 *    default item identifiers that should be created for a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamToolbar (in, typeHIToolbarRef)
 *          The toolbar for which to retrieve identifiers.
 *    
 *    --> kEventParamMutableArray (in, typeCFMutableArrayRef)
 *          A mutable array to fill in with the identifiers.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarGetDefaultIdentifiers = 1
};

/*
 *  kEventClassToolbar / kEventToolbarGetAllowedIdentifiers
 *  
 *  Summary:
 *    This event is sent to the delegate to get a list of all the items
 *    which could possibly be added to the toolbar. This is sent out
 *    when the configuration sheet is about to be displayed. You are
 *    passed a mutable array to fill in with the identifiers.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamToolbar (in, typeHIToolbarRef)
 *          The toolbar for which to retrieve identifiers.
 *    
 *    --> kEventParamMutableArray (in, typeCFMutableArrayRef)
 *          A mutable array to fill in with the identifiers.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarGetAllowedIdentifiers = 2
};

/*
 *  kEventClassToolbar / kEventToolbarCreateItemWithIdentifier
 *  
 *  Summary:
 *    This event is sent to the delegate when we need to create an item
 *    from an identifier.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamToolbar (in, typeHIToolbarRef)
 *          The toolbar for which to create an item.
 *    
 *    --> kEventParamToolbarItemIdentifier (in, typeCFStringRef)
 *          The toolbar item identifier.
 *    
 *    --> kEventParamToolbarItemConfigData (in, typeCFTypeRef)
 *          The toolbar item configuration data. This parameter is
 *          optional and may not be present in all instances of this
 *          event.
 *    
 *    <-- kEventParamToolbarItem (out, typeHIToolbarItemRef)
 *          On exit, contains the new toolbar item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarCreateItemWithIdentifier = 3
};

/*
 *  kEventClassToolbar / kEventToolbarCreateItemFromDrag
 *  
 *  Summary:
 *    This event is sent to the delegate to when we need to create an
 *    item from a drag.
 *  
 *  Discussion:
 *    This event allows you to be able to drag items into a toolbar
 *    that arenÕt normal toolbar items. You might use this to allow
 *    your toolbar to accept file system items, for example.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDragRef (in, typeDragRef)
 *          The DragRef with information about the drag.
 *    
 *    <-- kEventParamToolbarItem (out, typeHIToolbarItemRef)
 *          On exit, contains the new toolbar item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarCreateItemFromDrag = 4
};

/*
 *  kEventClassToolbar / kEventToolbarItemAdded
 *  
 *  Summary:
 *    Sent to interested parties when an item is added to the toolbar.
 *    The toolbar object sends this event to itself, so you'd need to
 *    install a handler on the toolbar to receive this event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamToolbarItem (in, typeHIToolbarItemRef)
 *          The item that was just added.
 *    
 *    --> kEventParamIndex (in, typeCFIndex)
 *          The index at which the item now exists.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemAdded        = 5
};

/*
 *  kEventClassToolbar / kEventToolbarItemRemoved
 *  
 *  Summary:
 *    Sent to interested parties when an item is removed from toolbar.
 *    It is called after the item has already been removed. The toolbar
 *    object sends this event to itself, so you'd need to install a
 *    handler on the toolbar to receive this event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamToolbarItem (in, typeHIToolbarItemRef)
 *          The item that was just removed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemRemoved      = 6
};

/*
 *  kEventClassToolbar / kEventToolbarDisplayModeChanged
 *  
 *  Summary:
 *    Sent to interested parties when an the display mode is changed
 *    for a toolbar. The toolbar object sends this event to itself, so
 *    you'd need to install a handler on the toolbar to receive this
 *    event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarDisplayModeChanged = 7
};

/*
 *  kEventClassToolbar / kEventToolbarDisplaySizeChanged
 *  
 *  Summary:
 *    Sent to interested parties when an the display size is changed
 *    for a toolbar. The toolbar object sends this event to itself, so
 *    you'd need to install a handler on the toolbar to receive this
 *    event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarDisplaySizeChanged = 8
};

/*
 *  kEventClassToolbar / kEventToolbarLayoutChanged
 *  
 *  Summary:
 *    Sent to interested parties when the layout of a toolbar changes
 *    (either an item has been moved, or the entire contents have been
 *    replaced). Basically it is sent for changes which would require a
 *    total resync with the current state of things. The toolbar object
 *    sends this event to itself, so you'd need to install a handler on
 *    the toolbar to receive this event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarLayoutChanged    = 9
};

/*
 *  kEventClassToolbar / kEventToolbarBeginMultiChange
 *  
 *  Summary:
 *    Sent to interested parties when multiple attributes are going to
 *    be changed at once. For example, it is possible for the display
 *    mode and size to change at the same time. When this happens,
 *    instead of reacting two times (one for display mode changed and
 *    one for display size changed), you can listen to see if we are
 *    going to change multiple attributes and hold off on doing any
 *    relayout, etc. until the EndMultiChange event comes in. The
 *    toolbar object sends this event to itself, so you'd need to
 *    install a handler on the toolbar to receive this event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarBeginMultiChange = 12
};

/*
 *  kEventClassToolbar / kEventToolbarEndMultiChange
 *  
 *  Summary:
 *    Sent to interested parties when the toolbar is done adjusting
 *    multiple attributes. See kEventToolbarBeginMultiChange for more
 *    information. The toolbar object sends this event to itself, so
 *    you'd need to install a handler on the toolbar to receive this
 *    event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarEndMultiChange   = 13
};

/*
    kEventClassToolbarItem quick reference:
    
    kEventToolbarItemImageChanged           = 1,
    kEventToolbarItemLabelChanged           = 2,
    kEventToolbarItemHelpTextChanged        = 3,
    kEventToolbarItemCommandIDChanged       = 4,
    kEventToolbarItemGetPersistentData      = 5,
    kEventToolbarItemCreateCustomView       = 6,
    kEventToolbarItemEnabledStateChanged    = 7,
    kEventToolbarItemPerformAction          = 8,
    kEventToolbarItemWouldAcceptDrop        = 10,
    kEventToolbarItemAcceptDrop             = 11

*/
/*
 *  kEventClassToolbarItem / kEventToolbarItemImageChanged
 *  
 *  Summary:
 *    This event is sent to the item (itself) when the image changes.
 *    Any interested parties can install handlers on the toolbar item
 *    to receive notifications.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemImageChanged = 1
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemLabelChanged
 *  
 *  Summary:
 *    This event is sent to the item (itself) when the label changes.
 *    Any interested parties can install handlers on the toolbar item
 *    to receive notifications.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemLabelChanged = 2
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemHelpTextChanged
 *  
 *  Summary:
 *    This event is sent to the item (itself) when the help text
 *    changes. Any interested parties can install handlers on the
 *    toolbar item to receive notifications.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemHelpTextChanged = 3
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemCommandIDChanged
 *  
 *  Summary:
 *    This event is sent to the item (itself) when the command ID
 *    changes. Any interested parties can install handlers on the
 *    toolbar item to receive notifications.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemCommandIDChanged = 4
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemGetPersistentData
 *  
 *  Summary:
 *    This event is sent to the item (itself) when the toolbar is going
 *    to write out the configuration information for the item. Any
 *    custom items can listen for this event and add any extra
 *    information to what is written out into the config so that it can
 *    be reanimated later on from the same config data. Typically,
 *    you'd not need to handle this event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    <-- kEventParamToolbarItemConfigData (out, typeCFTypeRef)
 *          On exit, contains configuration information for the item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemGetPersistentData = 5
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemCreateCustomView
 *  
 *  Summary:
 *    This event is sent to the toolbar item when it is time to create
 *    a view for it to display its contents. Implementors of custom
 *    toolbar items can install a handler for this event to create
 *    their own custom views for their items.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    <-- kEventParamControlRef (out, typeControlRef)
 *          On exit, contains the itemÕs custom view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemCreateCustomView = 6
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemEnabledStateChanged
 *  
 *  Summary:
 *    This event is sent to the item (itself) when the enabled state
 *    changes. Any interested parties can install handlers on the
 *    toolbar item to receive notifications.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemEnabledStateChanged = 7
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemPerformAction
 *  
 *  Summary:
 *    This event is sent when a toolbar item is clicked. Subclasses of
 *    toolbar items can choose to do special actions by overriding this
 *    event. If this event is unhandled, the default action of sending
 *    a command event will occur.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemPerformAction = 8
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemWouldAcceptDrop
 *  
 *  Summary:
 *    This event is sent when a drag enters a toolbar item. If the
 *    toolbar item wants to accept drags (like finder items can when
 *    they represent containers), simply respond to this event and
 *    return true in the kEventParamResult parameter. The toolbar item
 *    will hilite appropriately. If you are using a custom view, you do
 *    not need to respond to this, since you'll have full drag and drop
 *    capability via the view system. This is to support custom items
 *    which are using the standard view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDragRef (in, typeDragRef)
 *          The drag to test for tastiness of flavors.
 *    
 *    <-- kEventParamResult (out, typeBoolean)
 *          A boolean value representing whether the drag was something
 *          the item wants to accept (true) or not (false). If this
 *          parameter does not exist or is false, we do not consult any
 *          other parameters in this event.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemWouldAcceptDrop = 10
};

/*
 *  kEventClassToolbarItem / kEventToolbarItemAcceptDrop
 *  
 *  Summary:
 *    If you responded to kEventToolbarItemLikesDrag and returned true
 *    in the kEventParamResult parameter, and the user drops the drag
 *    onto your item, you will be called with this event.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDragRef (in, typeDragRef)
 *          The drag that was just dropped.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemAcceptDrop   = 11
};

/*
    kEventClassToolbarItemView quick reference:
    
    kEventToolbarItemViewConfigForMode      = 3,
    kEventToolbarItemViewConfigForSize      = 4,
    kEventToolbarItemViewEnterConfigMode    = 5,
    kEventToolbarItemViewExitConfigMode     = 6
*/
enum {
  kEventParamToolbarDisplayMode = 'tbdm', /* typeHIToolbarDisplayMode*/
  kEventParamToolbarDisplaySize = 'tbds', /* typeHIToolbarDisplaySize*/
  typeHIToolbarDisplayMode      = 'tbdm', /* HIToolbarDisplayMode*/
  typeHIToolbarDisplaySize      = 'tbds' /* HIToolbarDisplaySize*/
};

/*
 *  kEventClassToolbarItemView / kEventToolbarItemViewConfigForMode
 *  
 *  Summary:
 *    Notifies a toolbar item view that the toolbar's display mode has
 *    changed.
 *  
 *  Discussion:
 *    Notifies a toolbar item view that the toolbar's display mode has
 *    changed. A custom toolbar item view can respond to this in any
 *    way it sees fit. Most times, responding to this is not necessary
 *    Ñ when the toolbar goes from icon to text only, for example, the
 *    view is automatically hidden, so there is not much to do. It is
 *    here for informational purposes only.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamToolbarDisplayMode (in, typeHIToolbarDisplayMode)
 *          The toolbar item view's new display mode.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemViewConfigForMode = 3
};

/*
 *  kEventClassToolbarItemView / kEventToolbarItemViewConfigForSize
 *  
 *  Summary:
 *    Notifies a toolbar item view that the toolbar's display size has
 *    changed.
 *  
 *  Discussion:
 *    Notifies a toolbar item view that the toolbar's display size has
 *    changed. A custom toolbar item view can respond to this in any
 *    way it sees fit. Most times, responding to this is not necessary.
 *    However, some custom views might need to flush metrics caches
 *    when the display size changes.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamToolbarDisplaySize (in, typeHIToolbarDisplaySize)
 *          The toolbar item view's new display size.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemViewConfigForSize = 4
};

/*
 *  kEventClassToolbarItemView / kEventToolbarItemViewEnterConfigMode
 *  
 *  Summary:
 *    Notifies a toolbar item view that we've entered configure mode.
 *  
 *  Discussion:
 *    Notifies a toolbar item view that we've entered configure mode. A
 *    custom toolbar item view can respond to this in any way it sees
 *    fit. For example, the space and flexible space mark themselves to
 *    draw a rectangle and merely invalidate so they get redrawn so you
 *    can see them during configure.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemViewEnterConfigMode = 5
};

/*
 *  kEventClassToolbarItemView / kEventToolbarItemViewExitConfigMode
 *  
 *  Summary:
 *    Notifies a toolbar item view that we've finished with configure
 *    mode.
 *  
 *  Discussion:
 *    Notifies a toolbar item view that we're now out of configure
 *    mode. A custom toolbar item view can respond to this in any way
 *    it sees fit.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventToolbarItemViewExitConfigMode = 6
};


/*
 *  Summary:
 *    Toolbar Item Attributes
 */
enum {

  /*
   * Pass this to indicate no attributes at all.
   */
  kHIToolbarItemNoAttributes    = 0,

  /*
   * This indicates that an item can have more than one instance of
   * itself in the toolbar. If this is not set, only one can be
   * present. By default, the determining factor for what determines if
   * two items are identical is the toolbar identifier. Subclasses of
   * HIToolbarItem can specify more elaborate equality.
   */
  kHIToolbarItemAllowDuplicates = (1 << 0),

  /*
   * This item can be rearranged, but it cannot be removed from the
   * Toolbar by the user.
   */
  kHIToolbarItemCantBeRemoved   = (1 << 1),

  /*
   * This item cannot be moved at all by the user. It is anchored to
   * the left of the toolbar. It is important that there not be any
   * unanchored items to the left of this item, else dragging items
   * around will be a bit wacky. It is up you you, the home viewer, to
   * make sure that anchored items are all on the left. This allows you
   * to do toolbars like the the one in the System Preferences app,
   * where the first couple of items are stuck in place.
   */
  kHIToolbarItemAnchoredLeft    = (1 << 2),

  /*
   * This indicates the item acts as a separator. This means two things
   * at present. First, it means that it automatically shows up as a
   * divider line in a menu representation of the toolbar, and second
   * it means the view that represents this item can draw in the full
   * top to bottom space that the toolbar item occupies in the toolbar.
   */
  kHIToolbarItemIsSeparator     = (1 << 3),

  /*
   * If this attribute bit is set, the command that gets sent out will
   * be directed at the user focus instead of at the window the toolbar
   * is attached to.
   */
  kHIToolbarItemSendCmdToUserFocus = (1 << 4),

  /*
   * If this attribute bit is set, clicking on the label of an item
   * does nothing. This attribute is ONLY considered when a custom view
   * is present. What it really does is make the toolbar item view dead
   * to clicks while still allowing clicks to be sent to the custom
   * view. When the toolbar is in text-only mode and this attribute is
   * set, it displays the label in a disabled (grayed) appearance. You
   * might want to change this attribute when switching between display
   * modes. For example, the view switcher in finder does not allow
   * clicks on the label when in icon and text mode, but it does
   * respond to clicks when in text only mode. To change this on the
   * fly, you should listen for kEventToolbarItemViewConfigForMode in
   * your custom view and adjust this attribute as you desire. This
   * attribute is available in Mac OS X 10.3 and later.
   */
  kHIToolbarItemLabelDisabled   = (1 << 5),
  kHIToolbarItemValidAttrs      = kHIToolbarItemAllowDuplicates | kHIToolbarItemIsSeparator | kHIToolbarItemCantBeRemoved | kHIToolbarItemAnchoredLeft | kHIToolbarItemSendCmdToUserFocus | kHIToolbarItemLabelDisabled,
  kHIToolbarItemMutableAttrs    = kHIToolbarItemCantBeRemoved | kHIToolbarItemAnchoredLeft | kHIToolbarItemLabelDisabled
};

/*======================================================================================*/
/* FUNCTIONS                                                                            */
/*======================================================================================*/
/*
 *  HIToolbarCreate()
 *  
 *  Discussion:
 *    Creates a toolbar. After creating a toolbar, one would normally
 *    attach it to a window using SetWindowToolbar, described in
 *    MacWindows.h. Since the toolbar is merely the model (as opposed
 *    to the view), there are no routines to hide/show it here. Please
 *    look to MacWindows.h for the routines ShowHideWindowToolbar and
 *    IsWindowToolbarVisible there for more information.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inIdentifier:
 *      The identifier of the toolbar. If you specify that the toolbar
 *      auto-saves its configuration, this identifier is used to mark
 *      the config info in your application's preferences. You must
 *      specify an identifier.
 *    
 *    inAttributes:
 *      Any attributes you wish to specify.
 *    
 *    outToolbar:
 *      The toolbar reference to your shiny new toolbar.
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
HIToolbarCreate(
  CFStringRef     inIdentifier,
  OptionBits      inAttributes,
  HIToolbarRef *  outToolbar)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarGetAttributes()
 *  
 *  Discussion:
 *    Returns the attributes for the given toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose attributes you desire.
 *    
 *    outAttributes:
 *      The attributes.
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
HIToolbarGetAttributes(
  HIToolbarRef   inToolbar,
  OptionBits *   outAttributes)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarChangeAttributes()
 *  
 *  Discussion:
 *    Changes the attributes of a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose attributes you want to change.
 *    
 *    inAttrsToSet:
 *      The attributes you wish to set/enable.
 *    
 *    inAttrsToClear:
 *      The attributes you wish to clear/disable.
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
HIToolbarChangeAttributes(
  HIToolbarRef   inToolbar,
  OptionBits     inAttrsToSet,
  OptionBits     inAttrsToClear)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarGetDisplayMode()
 *  
 *  Discussion:
 *    Returns the current display mode of a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose display mode you wish to receive.
 *    
 *    outDisplayMode:
 *      The display mode.
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
HIToolbarGetDisplayMode(
  HIToolbarRef            inToolbar,
  HIToolbarDisplayMode *  outDisplayMode)                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarSetDisplayMode()
 *  
 *  Discussion:
 *    Sets the current display mode of a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose display mode you wish to set.
 *    
 *    inDisplayMode:
 *      The display mode. If the toolbar is visible, it will be redrawn.
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
HIToolbarSetDisplayMode(
  HIToolbarRef           inToolbar,
  HIToolbarDisplayMode   inDisplayMode)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarGetDisplaySize()
 *  
 *  Discussion:
 *    Gets the current display size of a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose display size you wish to get.
 *    
 *    outSize:
 *      The display size.
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
HIToolbarGetDisplaySize(
  HIToolbarRef            inToolbar,
  HIToolbarDisplaySize *  outSize)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarSetDisplaySize()
 *  
 *  Discussion:
 *    Sets the current display size of a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose display size you wish to set.
 *    
 *    inSize:
 *      The display size. If the toolbar is visible, it will be redrawn.
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
HIToolbarSetDisplaySize(
  HIToolbarRef           inToolbar,
  HIToolbarDisplaySize   inSize)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarCopyIdentifier()
 *  
 *  Discussion:
 *    Returns the identifier for a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose identifier you wish to get.
 *    
 *    outIdentifier:
 *      The identifier. You must release it when you are finished with
 *      it.
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
HIToolbarCopyIdentifier(
  HIToolbarRef   inToolbar,
  CFStringRef *  outIdentifier)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarSetItemsWithIdentifiers()
 *  
 *  Discussion:
 *    Allows you to set a toolbar's items all at once. The array
 *    contains either CFStringRefs of item identifiers, or a small
 *    CFDictionaryRef containing the identifier string, and the config
 *    data (if the item requires it). The key for the identifier string
 *    is kHIToolbarIdentifierKey and the key for the config data string
 *    is kHIToolbarDataKey.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose items you wish to set.
 *    
 *    inArray:
 *      The array of toolbar items to create.
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
HIToolbarSetItemsWithIdentifiers(
  HIToolbarRef   inToolbar,
  CFArrayRef     inArray)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HIToolbarCopyItems()
 *  
 *  Discussion:
 *    Returns the array of toolbar items for a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose items you wish to receive.
 *    
 *    outItems:
 *      The array of toolbar items owned by the toolbar. You must
 *      release the array when you are finished with it.
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
HIToolbarCopyItems(
  HIToolbarRef   inToolbar,
  CFArrayRef *   outItems)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarCreateItemWithIdentifier()
 *  
 *  Discussion:
 *    Creates an item specified by a particular identifier. Using this
 *    function allows you to create any item a delegate supports by
 *    naming its identifier. It also allows you to create standard
 *    items supplied by the Toolbox, such as the separator item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar you are adding to.
 *    
 *    inIdentifier:
 *      The identifier of the item you wish to add.
 *    
 *    inConfigData:
 *      Any config data required by the item to safely construct.
 *      Standard items do not require any extra data, so NULL can be
 *      passed.
 *    
 *    outItem:
 *      The newly created toolbar item.
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
HIToolbarCreateItemWithIdentifier(
  HIToolbarRef        inToolbar,
  CFStringRef         inIdentifier,
  CFTypeRef           inConfigData,       /* can be NULL */
  HIToolbarItemRef *  outItem)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  HIToolbarInsertItemAtIndex()
 *  
 *  Discussion:
 *    Inserts a toolbar item at a given index into a toolbar.
 *    Generally, you should always add items via identifier, and not
 *    with this routine.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar to receive the new item.
 *    
 *    inItem:
 *      The item reference of the toolbar item you are adding.
 *    
 *    inIndex:
 *      The index you wish to add the item at. This index is zero-based.
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
HIToolbarInsertItemAtIndex(
  HIToolbarRef       inToolbar,
  HIToolbarItemRef   inItem,
  CFIndex            inIndex)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  HIToolbarAppendItem()
 *  
 *  Discussion:
 *    Appends an item to the end of a toolbar. Generally, you should
 *    always add items via identifier, and not with this routine.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar to receive the new item.
 *    
 *    inItem:
 *      The item reference of the toolbar item you are adding.
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
HIToolbarAppendItem(
  HIToolbarRef       inToolbar,
  HIToolbarItemRef   inItem)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarRemoveItemAtIndex()
 *  
 *  Discussion:
 *    Removes an item at a given index from a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar you are removing the item from.
 *    
 *    inIndex:
 *      The index of the item to remove. This index is zero-based.
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
HIToolbarRemoveItemAtIndex(
  HIToolbarRef   inToolbar,
  CFIndex        inIndex)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarSetDelegate()
 *  
 *  Discussion:
 *    Sets the delegate event target for a toolbar. This is necessary
 *    for a toolbar to work properly if it wants items of its own. The
 *    delegate is who is asked to create toolbar items. If the delegate
 *    does not respond, the toolbar will attempt to create a toolbar
 *    item, but it can only create the standard items defined at the
 *    top of this header.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar whose delegate you want to set.
 *    
 *    inDelegate:
 *      The HIObjectRef to act as the delegate.
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
HIToolbarSetDelegate(
  HIToolbarRef   inToolbar,
  HIObjectRef    inDelegate)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarGetDelegate()
 *  
 *  Discussion:
 *    Returns the current delegate in use by a toolbar.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inToolbar:
 *      The toolbar you want the delegate from.
 *  
 *  Result:
 *    An HIObjectRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern HIObjectRef 
HIToolbarGetDelegate(HIToolbarRef inToolbar)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*==========================================================================*/
/* HITOOLBARITEM                                                            */
/*==========================================================================*/
/* The HIObject class ID for the ToolbarItem class. */

#define kHIToolbarItemClassID           CFSTR("com.apple.hitoolbaritem")


/* Required construction parameters                                         */
/*                                                                          */
/* You must pass these parameters in the initialization event if you are    */
/* subclassing the toolbar item                                             */
/*                                                                          */
/*      kEventParamToolbarItemIdentifier            typeCFStringRef         */
/*      kEventParamAttibutes                        typeUInt32              */


/*
 *  HIToolbarItemCreate()
 *  
 *  Discussion:
 *    Creates a toolbar item for use in a toolbar. Typically, you would
 *    create toolbar items in your delegate. When a toolbar needs to
 *    create an item with a given identifier, your delegate is asked to
 *    create it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inIdentifier:
 *      The identifier of the item in question.
 *    
 *    inOptions:
 *      Any options for the item.
 *    
 *    outItem:
 *      The item you created.
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
HIToolbarItemCreate(
  CFStringRef         inIdentifier,
  OptionBits          inOptions,
  HIToolbarItemRef *  outItem)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#define _HIToolbarItemCopyIdentifier HIToolbarItemCopyIdentifier
/*
 *  HIToolbarItemCopyIdentifier()
 *  
 *  Discussion:
 *    Returns the identifier of the given item. The toolbar uses this
 *    identifier when writing the config information to the preferences
 *    (if set up for auto-config).
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    outIdentifier:
 *      The identifier of the item. You should release this string when
 *      you are finished with it.
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
HIToolbarItemCopyIdentifier(
  HIToolbarItemRef   inItem,
  CFStringRef *      outIdentifier)                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemGetAttributes()
 *  
 *  Discussion:
 *    Returns the attributes of the given item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    outAttributes:
 *      The attributes of the item.
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
HIToolbarItemGetAttributes(
  HIToolbarItemRef   inItem,
  OptionBits *       outAttributes)                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemChangeAttributes()
 *  
 *  Discussion:
 *    Changes the attributes of a toolbar item. Only those attributes
 *    defined by the kHIToolbarItemMutableAttrs can be passed into this
 *    API. All other options can only be specified at creation.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    inAttrsToSet:
 *      The attributes to set on the item. This value can be
 *      kHIToolbarItemNoAttributes if you are only clearing attributes.
 *    
 *    inAttrsToClear:
 *      The attributes to clear on the item. This value can be
 *      kHIToolbarItemNoAttributes if you are only setting attributes.
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
HIToolbarItemChangeAttributes(
  HIToolbarItemRef   inItem,
  OptionBits         inAttrsToSet,
  OptionBits         inAttrsToClear)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemSetLabel()
 *  
 *  Discussion:
 *    Sets the label of a toolbar item. This is what the toolbar view
 *    will display underneath the image. It is also used in the
 *    configuration palette for configurable toolbars.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    inLabel:
 *      The label. The toolbox will copy the string passed in.
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
HIToolbarItemSetLabel(
  HIToolbarItemRef   inItem,
  CFStringRef        inLabel)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemCopyLabel()
 *  
 *  Discussion:
 *    Returns the label of a toolbar item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    outLabel:
 *      The label of the item. You should release this when you are
 *      finished with it.
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
HIToolbarItemCopyLabel(
  HIToolbarItemRef   inItem,
  CFStringRef *      outLabel)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemSetHelpText()
 *  
 *  Discussion:
 *    Sets the text used for help tags for a toolbar item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    inShortText:
 *      The short help text. This is what is displayed normally by the
 *      help tag system when the user hovers over the toolbar item with
 *      the mouse.
 *    
 *    inLongText:
 *      The long help text. This is what is displayed by the help tag
 *      system when the user hovers over the toolbar item with the
 *      mouse and holds the command key down. This parameter is
 *      optional, you may pass NULL.
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
HIToolbarItemSetHelpText(
  HIToolbarItemRef   inItem,
  CFStringRef        inShortText,
  CFStringRef        inLongText)        /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemCopyHelpText()
 *  
 *  Discussion:
 *    Returns the text used for help tags for a toolbar item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    outShortText:
 *      The short help text. This is what is displayed normally by the
 *      help tag system when the user hovers over the toolbar item with
 *      the mouse. You should release this string when you are finished
 *      with it. If you do not wish to receive the short help text,
 *      pass NULL for this parameter.
 *    
 *    outLongText:
 *      The long help text. This is what is displayed by the help tag
 *      system when the user hovers over the toolbar item with the
 *      mouse and holds the command key down. You should release this
 *      string when you are finished with it. If you do not wish to
 *      receive the long help text, pass NULL for this parameter.
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
HIToolbarItemCopyHelpText(
  HIToolbarItemRef   inItem,
  CFStringRef *      outShortText,       /* can be NULL */
  CFStringRef *      outLongText)        /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemSetCommandID()
 *  
 *  Discussion:
 *    Sets the command ID of a toolbar item. When an toolbar item is
 *    clicked, the default behavior is to send out the command assigned
 *    to the item. This API lets you set that command ID. The command
 *    is sent out via the ProcessHICommand API, so it uses Carbon
 *    Events.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    inCommandID:
 *      The command ID.
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
HIToolbarItemSetCommandID(
  HIToolbarItemRef   inItem,
  MenuCommand        inCommandID)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemGetCommandID()
 *  
 *  Discussion:
 *    Gets the command ID of a toolbar item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    outCommandID:
 *      The command ID.
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
HIToolbarItemGetCommandID(
  HIToolbarItemRef   inItem,
  MenuCommand *      outCommandID)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#define _HIToolbarItemSetIconRef HIToolbarItemSetIconRef
/*
 *  HIToolbarItemSetIconRef()
 *  
 *  Discussion:
 *    Sets the icon for a toolbar item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    inIcon:
 *      The icon ref. The toolbar will create an appropriate CGImageRef
 *      for the icon passed in. The icon can be released after this API
 *      is called.
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
HIToolbarItemSetIconRef(
  HIToolbarItemRef   inItem,
  IconRef            inIcon)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemSetImage()
 *  
 *  Discussion:
 *    Sets the image for a toolbar item. Currently, the image should be
 *    no higher than 32 pixels. This image is used both in the toolbar
 *    as well as the configuration sheet, if the toolbar is
 *    configurable.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    inImage:
 *      The image. This image is retained by the toolbar item. You may
 *      release it after calling this API.
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
HIToolbarItemSetImage(
  HIToolbarItemRef   inItem,
  CGImageRef         inImage)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemCopyImage()
 *  
 *  Discussion:
 *    Returns the image for a toolbar item. This image is already
 *    retained by the time you receive it, so you can release it when
 *    you are done with it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    outImage:
 *      The retained image. You should release it when finished with it.
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
HIToolbarItemCopyImage(
  HIToolbarItemRef   inItem,
  CGImageRef *       outImage)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemSetMenu()
 *  
 *  Discussion:
 *    Sets the submenu for a toolbar item. Normally, items do not have
 *    a submenu. You can attach one with this API. The submenu will, by
 *    default, show up in the 'more items' indicator popup, as a
 *    submenu of the menu item corresponding to the toolbar item. It
 *    will also appear if the toolbar is in text only mode and the
 *    label is clicked. You should attach a Carbon Event handler to the
 *    menu to handle updating the menu items as appropriate before the
 *    menu is displayed.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    inMenu:
 *      The menu. It is retained by the toolbar item, so you can safely
 *      release it after calling this API. On Mac OS X 10.3 and later,
 *      you can pass NULL for this parameter to remove and release any
 *      menu that might be attached.
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
HIToolbarItemSetMenu(
  HIToolbarItemRef   inItem,
  MenuRef            inMenu)       /* can be NULL */          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemCopyMenu()
 *  
 *  Discussion:
 *    Gets the submenu for a toolbar item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    outMenu:
 *      The retained menu. You should release it when you are finished
 *      with it.
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
HIToolbarItemCopyMenu(
  HIToolbarItemRef   inItem,
  MenuRef *          outMenu)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  HIToolbarItemGetToolbar()
 *  
 *  Discussion:
 *    Gets the toolbar a toolbar item is attached to.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *  
 *  Result:
 *    The toolbar item reference of the toolbar this item is bound to,
 *    or NULL if this toolbar item is not attached to any toolbar.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern HIToolbarRef 
HIToolbarItemGetToolbar(HIToolbarItemRef inItem)              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemIsEnabled()
 *  
 *  Discussion:
 *    Used to determine if a toolbar item is enabled.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *  
 *  Result:
 *    A boolean result.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIToolbarItemIsEnabled(HIToolbarItemRef inItem)               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemSetEnabled()
 *  
 *  Discussion:
 *    Enables or disables a toolbar item.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item in question.
 *    
 *    inEnabled:
 *      The new enabled state.
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
HIToolbarItemSetEnabled(
  HIToolbarItemRef   inItem,
  Boolean            inEnabled)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIToolbarItemConfigDataChanged()
 *  
 *  Discussion:
 *    Informs the toolbar that the config data for a toolbar item has
 *    changed and should be written to the toolbar config prefs. This
 *    is used when a custom toolbar item has extra data (config data)
 *    that has changed (perhaps you've changed an alias that a toolbar
 *    item points to, for example). This function does nothing if the
 *    toolbar is not set to auto save its configuration.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The item whose information has changed.
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
HIToolbarItemConfigDataChanged(HIToolbarItemRef inItem)       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __HITOOLBAR__ */

