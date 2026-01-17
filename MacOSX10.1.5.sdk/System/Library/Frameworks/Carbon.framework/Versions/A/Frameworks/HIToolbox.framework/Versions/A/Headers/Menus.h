/*
     File:       HIToolbox/Menus.h
 
     Contains:   Menu Manager Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MENUS__
#define __MENUS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#ifndef __FONTS__
#include <QD/Fonts.h>
#endif

#ifndef __TEXTCOMMON__
#include <CarbonCore/TextCommon.h>
#endif

#ifndef __PROCESSES__
#include <HIToolbox/Processes.h>
#endif

#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
#endif

#ifndef __COLLECTIONS__
#include <CarbonCore/Collections.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __CFUUID__
#include <CoreFoundation/CFUUID.h>
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
 *  Menu Manager
 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Constants                                                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  noMark                        = 0     /* mark symbol for SetItemMark; other mark symbols are defined in Fonts.h */
};

/*
    A Short Course on Menu Definition Functions
    
    A menu definition function is used to implement a custom visual appearance for a menu.
    Menu definition functions are still supported in Carbon, but the messages sent to a
    menu definition function in Carbon are different than for a non-Carbon application.
    
    In general, Apple recommends using the system menu definition whenever possible.
    Menu definition functions will continue to be supported, but it is not easy to write
    a correct menu definition, especially one that attempts to imitate the standard system
    menu appearance. If you require special features in your menu that the system menu
    definition does not support, please mail <toolbox@apple.com> and describe your requirements;
    we would much rather enhance the system menu definition than have you write a custom one.
    
    Menu definition functions before Carbon used the following messages:
    
        kMenuDrawMsg
        kMenuChooseMsg
        kMenuSizeMsg
        kMenuPopUpMsg
        kMenuDrawItemMsg
        kMenuCalcItemMsg
        kMenuThemeSavvyMsg
        
    kMenuChooseMsg and kMenuDrawItemMsg are not supported in Carbon and are not sent to
    Carbon menu definitions. In Carbon, kMenuChooseMsg is replaced by kMenuFindItemMsg and
    kMenuHiliteItemMsg. Menu definition functions in Carbon use the following messages:
    
        kMenuInitMsg
        kMenuDisposeMsg
        kMenuFindItemMsg
        kMenuHiliteItemMsg
        kMenuDrawItemsMsg
        kMenuDrawMsg
        kMenuSizeMsg
        kMenuPopUpMsg
        kMenuCalcItemMsg
        kMenuThemeSavvyMsg
        
    The rest of this documentation will focus on Carbon menu definitions only.
    
    Menu Definition Messages
    
        Carbon menu definition functions should support the following messages:
        
        kMenuInitMsg
            
            menuRect        unused
            hitPt           unused
            whichItem       OSErr*
        
            Sent when a menu is created. This message gives the menu definition an opportunity
            to initialize its own state. If the menu definition encounters an error while
            initializing, it should set *whichItem to a non-zero error code; this will cause the
            Menu Manager to destroy the menu and return an error back from the API that was used
            to create the menu.
        
        kMenuDisposeMsg
            
            menuRect        unused
            hitPt           unused
            whichItem       unused
            
            Sent when a menu is destroyed. This message gives the menu definition an opportunity
            to destroy its own data.
            
        kMenuFindItemMsg
            
            menuRect        menu bounds
            hitPt           point to hit-test
            whichItem       MDEFFindItemData*
            
            Sent when the Menu Manager is displaying a menu and needs to know what item is under
            the mouse. The whichItem parameter is actually a pointer to a MenuTrackingData structure.
            On entry, the menu, virtualMenuTop, and virtualMenuBottom fields of this structure are
            valid. The menu definition should determine which item containst the given point, if any,
            and fill in the itemUnderMouse, itemSelected, and itemRect fields. If an item is found,
            the menu definition should always fill in the itemUnderMouse and itemRect fields. The
            menu definition should only fill in the itemSelected field if the item is available for
            selection; if it is unavailable (because it is disabled, or for some other reason), the
            menu definition should set the itemSelected field to zero.
            
            The values placed in the itemUnderMouse and itemSelected fields should be less than or
            equal to the number of items returned by CountMenuItems on this menu.
            
            The menu definition should not hilite the found item during this message. The Menu 
            Manager will send a separate kMenuHiliteItemMsg to request hiliting of the item.
            
            If the menu definition supports scrolling, it should scroll the menu during this message,
            and update the virtualMenuTop and virtualMenuBottom fields of the MenuTrackingData to
            indicate the menu's new scrolled position.
            
            If the menu definition uses QuickDraw to draw while scrolling, it should draw into the
            current port.
    
            If the menu definition uses CoreGraphics to draw while scrolling, it should use the
            CGContextRef passed in the context field of the MDEFHiliteItemData structure.
            
            Menu definitions must use the ScrollMenuImage API, if available, to scroll the menu contents.
            This API is available in CarbonLib 1.4 and later, and in Mac OS X after 10.0.x. ScrollMenuImage
            properly supports scrolling the alpha channel in the menu's image data. Use of QuickDraw's
            ScrollRect API to scroll the menu contents will result in the alpha channel being set to 0xFF
            (opaque) and the menu will no longer be transparent.
            
            The menu definition should not modify the menu field of the MenuTrackingData.
            
        kMenuHiliteItemMsg
        
            menuRect        menu bounds
            hitPt           unused
            whichItem       MDEFHiliteItemData*
            
            Sent when the Menu Manager is displaying a menu and needs to hilite a newly selected
            item. The whichItem parameter is actually a pointer to a MDEFHiliteItemData structure.
            The menu definition should unhilite the item in the previousItem field, if non-zero,
            and hilite the item in the newItem field.
            
            Menu definitions should use the EraseMenuBackground API to erase the old menu contents
            before unhiliting a menu item, if the menu definition is using the Appearance Manager's
            menu drawing APIs. This is necessary because the background of a menu is transparent on
            Aqua, and if the old hilite is not erased first, it will show through the new unhilited
            menu background.
            
            If the menu definition uses QuickDraw to draw, it should draw into the current port.
    
            If the menu definition uses CoreGraphics to draw, it should use the CGContextRef passed
            in the context field of the MDEFHiliteItemData structure.
            
        kMenuDrawItemsMsg
        
            menuRect        menu bounds
            hitPt           unused
            whichItem       MDEFDrawItemsData*
            
            Sent when the Menu Manager is displaying a menu and needs to redraw a portion of the
            menu. This message is used by the dynamic menu item support code in the Menu Manager;
            for example, if items five and six in a menu are a dynamic group, the Menu Manager will
            send a DrawItems message when the group's modifier key is pressed or released to redraw
            the appropriate item, but no other items in the menu.
            
            The whichItem parameter for this message is actually a pointer to a MDEFDrawItemsData
            structure. The menu definition should redraw the items starting with firstItem and
            ending with lastItem, inclusive.
            
            If the menu definition uses QuickDraw to draw, it should draw into the current port.
    
            If the menu definition uses CoreGraphics to draw, it should use the CGContextRef passed
            in the context field of the MDEFDrawItemsData structure.
            
        kMenuDrawMsg
            
            menuRect        menu bounds
            hitPt           unused
            whichItem       MDEFDrawData*
            
            Sent when the Menu Manager is displaying a menu and needs to redraw the entire menu.
            The whichItem parameter is actually a pointer to a MenuTrackingData structure. On entry,
            the menu field of this structure is valid. The menu definition should draw the menu and,
            if it supports scrolling, should also fill in the virtualMenuTop and virtualMenuBottom
            fields of the structure to indicate the menu's initial unscrolled position; typically, 
            virtualMenuTop would be set to the same value as the top coordinate of the menu rect,
            and virtualMenuBottom would be set to virtualMenuTop plus the virtual height of the menu.
            
            If the menu definition uses QuickDraw to draw, it should draw into the current port.
    
            If the menu definition uses CoreGraphics to draw, it should use the CGContextRef passed
            in the context field of the MDEFDrawData structure.
            
        kMenuSizeMsg
        
            menuRect        unused
            hitPt           maximum width and height of the menu
            whichItem       unused
            
            Sent when the Menu Manager needs to determine the size of a menu. The menu definition
            should calculate the width and height of the menu and store the sizes into the menu with
            SetMenuWidth and SetMenuHeight.
            
            If the gestaltMenuMgrSendsMenuBoundsToDefProc bit is set in the Menu Manager's Gestalt
            value, then the hitPt parameter to this message is the maximum width (hitPt.h) and height
            (hitPt.v) of the menu. The menu definition should ensure that the width and height that it
            places in the menu do not exceed these values. If the gestalt bit is not set, the menu
            definition should just use the main GDevice's width and height as constraints on the menu's
            width and height.
            
        kMenuPopUpMsg
        
            menuRect        on entry, constraints on the menu's position; on exit, menu bounds
            hitPt           requested menu location, with swapped coordinates
            whichItem       on entry, requested initial selection; on exit, virtual menu top
            
            Sent when the Menu Manager is about to display a popup menu. The menu definition should
            calculate the appropriate menu bounds to contain the menu based on the requested menu
            location and selected item. It should write the menuBounds into the rect given by the
            menuRect parameter.
            
            If the gestaltMenuMgrSendsMenuBoundsToDefProc bit is set in the Menu Manager's Gestalt
            value, then the menuRect parameter on entry to this message contains a constraint rect,
            in global coordinates, outside of which the popup menu should not be positioned. The menu
            definition should take this constraint rect into account as it calculates the menu bounds.
            If the gestalt bit is not set, the menu definition should use the bounds of the GDevice
            containing the menu's top left corner as a constraint on the menu's position.
            
            The hitPt parameter is a requested location for the top left corner of the menu. The
            coordinates of this parameter are swapped from their normal order; the h field of the
            hitPt parameter contains the vertical coordinate, and the v field of hitPt contains
            the horizontal coordinate.
            
            On entry, the whichItem parameter points at a menu item index which is requested to be
            the initial selection when the menu is displayed. After calculating the menu's bounds,
            the menu definition should write the menu's virtual top coordinate into the location
            pointed at by the whichItem parameter. If displaying the menu at the requested location
            does not require scrolling, the virtual top will be the same as the menu bounds top;
            if the menu must scroll to fit in the requested location, the virtual top may be different.
            
        kMenuCalcItemMsg
        
            menuRect        on exit, item bounds
            hitPt           unused
            whichItem       the item whose rect to calculate
            
            Sent when the Menu Manager needs to know the bounds of a menu item. The menu definition
            should calculate the size of the item specified by the whichItem parameter, and store 
            the bounds in the rect specified by the menuRect parameter.
            
            Some sample menu definition code provided by Apple has previously shown an implementation
            of this message that always sets the top left corner of the item bounds to (0,0), regardless
            of the item's actual position in the menu. For best future compatibility, menu definitions
            should begin storing an item bounds that gives the item's actual position in the menu based
            on the menu's current virtual top. For example, if the virtual menu top starts at 20, then
            the menu definition would calculate an item bounds for the first item that starts at (0,20),
            an item bounds for the second item that starts at (0,40), and so on. The menu definition
            should call GetMenuTrackingData to get the menu's current virtual position, and use zero
            for the menu top if GetMenuTrackingData returns an error.
            
        kMenuThemeSavvyMsg
        
            menuRect        unused
            hitPt           unused
            whichItem       on exit, indicates theme-savvyness of the menu definition
            
            Sent by the Menu Manager to determine whether the MDEF uses the Appearance Manager 
            menu-drawing functions to draw its menu. If it does, the menu definition should return
            kThemeSavvyMenuResponse in the location pointed to by whichItem. If the menu definition
            draws its own custom content without using the Appearance Manager menu-drawing functions,
            it should ignore this message.
    
    Low-memory Global Replacements
    
        Pre-Carbon menu definitions needed to use several low-memory globals to communicate with the
        Menu Manager. These globals have all been replaced or made obsolete in Carbon, as follows:
        
        MenuDisable
            
            MenuDisable is now set automatically by the Menu Manager using the value returned in the
            itemUnderMouse field of the MenuTrackingData structure passed to kMenuFindItemMsg.
            
        TopMenuItem
        AtMenuBottom
        
            TopMenuItem and AtMenuBottom are now set automatically by the Menu Manager using the
            values returned in the virtualMenuTop and virtualMenuBottom fields of the MenuTrackingData
            structure passed to kMenuDrawMsg and kMenuFindItemMsg.
            
        mbSaveLoc
    
            This undocumented low-memory global was used by pre-Carbon menu definitions to store
            the bounding rect of the currently selected item and to avoid drawing glitches while
            the menu definition was scrolling the contents of a menu that had submenus. The Menu
            Manager now automatically sets the selected item bounds using the value returned in
            the itemRect field of the MenuTrackingData structure passed to kMenuFindItemMsg. In
            order to correctly support scrolling of menus with submenus, a menu definition should
            verify, before scrolling the menu contents, that no submenus of the scrolling menu are
            currently visible. A menu definition can use GetMenuTrackingData to verify this condition,
            as follows:
            
                Boolean SafeToScroll( MenuRef menuBeingScrolled )
                {
                    MenuTrackingData lastMenuData;
                    return GetMenuTrackingData( NULL, &lastMenuData ) == noErr
                           && lastMenuData.menu == menuBeingScrolled;
                }
            
            If SafeToScroll returns false, the menu definition should not scroll the menu.
*/
enum {
                                        /* menu defProc messages */
  kMenuDrawMsg                  = 0,
  kMenuSizeMsg                  = 2,
  kMenuPopUpMsg                 = 3,
  kMenuCalcItemMsg              = 5,
  kMenuThemeSavvyMsg            = 7,    /* is your MDEF theme-savvy?  If so, return kThemeSavvyMenuResponse in the whichItem parameter*/
  mDrawMsg                      = 0,
  mSizeMsg                      = 2,
  mPopUpMsg                     = 3,    /* position the popup menu rect appropriately */
  mCalcItemMsg                  = 5
};

#if CALL_NOT_IN_CARBON
/*
   Carbon MDEFs must replace mChooseMsg with the new messages kMenuFindItemMsg and kMenuHiliteItemMsg. 
   mDrawItemMsg was used by the popup menu control before 8.5, but is no longer used. 
*/
enum {
  mChooseMsg                    = 1,
  mDrawItemMsg                  = 4,
  kMenuChooseMsg                = 1,
  kMenuDrawItemMsg              = 4
};

#endif  /* CALL_NOT_IN_CARBON */

enum {
  kThemeSavvyMenuResponse       = 0x7473 /* should be returned in *whichItem when handling kMenuThemeSavvyMsg*/
};

/* these MDEF messages are only supported in Carbon*/
enum {
  kMenuInitMsg                  = 8,
  kMenuDisposeMsg               = 9,
  kMenuFindItemMsg              = 10,
  kMenuHiliteItemMsg            = 11,
  kMenuDrawItemsMsg             = 12
};

enum {
  textMenuProc                  = 0,
  hMenuCmd                      = 27,   /*itemCmd == 0x001B ==> hierarchical menu*/
  hierMenu                      = -1,   /*a hierarchical menu - for InsertMenu call*/
  kInsertHierarchicalMenu       = -1,   /*a better name for hierMenu */
  mctAllItems                   = -98,  /*search for all Items for the given ID*/
  mctLastIDIndic                = -99   /*last color table entry has this in ID field*/
};

/* Constants for use with MacOS 8.0 (Appearance 1.0) and later*/
enum {
  kMenuStdMenuProc              = 63,
  kMenuStdMenuBarProc           = 63
};

/* For use with Get/SetMenuItemModifiers*/
enum {
  kMenuNoModifiers              = 0,    /* Mask for no modifiers*/
  kMenuShiftModifier            = (1 << 0), /* Mask for shift key modifier*/
  kMenuOptionModifier           = (1 << 1), /* Mask for option key modifier*/
  kMenuControlModifier          = (1 << 2), /* Mask for control key modifier*/
  kMenuNoCommandModifier        = (1 << 3) /* Mask for no command key modifier*/
};

/* For use with Get/SetMenuItemIconHandle*/
enum {
  kMenuNoIcon                   = 0,    /* No icon*/
  kMenuIconType                 = 1,    /* Type for ICON*/
  kMenuShrinkIconType           = 2,    /* Type for ICON plotted 16 x 16*/
  kMenuSmallIconType            = 3,    /* Type for SICN*/
  kMenuColorIconType            = 4,    /* Type for cicn*/
  kMenuIconSuiteType            = 5,    /* Type for Icon Suite*/
  kMenuIconRefType              = 6,    /* Type for Icon Ref*/
  kMenuCGImageRefType           = 7,    /* Type for a CGImageRef (Mac OS X only)*/
  kMenuSystemIconSelectorType   = 8,    /* Type for an IconRef registered with Icon Services under kSystemIconsCreator (after Mac OS X 10.0.x only)*/
  kMenuIconResourceType         = 9     /* Type for a CFStringRef naming a resource in the main bundle of the process (after Mac OS X 10.0.x only)*/
};

/* For use with Get/SetMenuItemKeyGlyph*/
enum {
  kMenuNullGlyph                = 0x00, /* Null (always glyph 1)*/
  kMenuTabRightGlyph            = 0x02, /* Tab to the right key (for left-to-right script systems)*/
  kMenuTabLeftGlyph             = 0x03, /* Tab to the left key (for right-to-left script systems)*/
  kMenuEnterGlyph               = 0x04, /* Enter key*/
  kMenuShiftGlyph               = 0x05, /* Shift key*/
  kMenuControlGlyph             = 0x06, /* Control key*/
  kMenuOptionGlyph              = 0x07, /* Option key*/
  kMenuSpaceGlyph               = 0x09, /* Space (always glyph 3) key*/
  kMenuDeleteRightGlyph         = 0x0A, /* Delete to the right key (for right-to-left script systems)*/
  kMenuReturnGlyph              = 0x0B, /* Return key (for left-to-right script systems)*/
  kMenuReturnR2LGlyph           = 0x0C, /* Return key (for right-to-left script systems)*/
  kMenuNonmarkingReturnGlyph    = 0x0D, /* Nonmarking return key*/
  kMenuPencilGlyph              = 0x0F, /* Pencil key*/
  kMenuDownwardArrowDashedGlyph = 0x10, /* Downward dashed arrow key*/
  kMenuCommandGlyph             = 0x11, /* Command key*/
  kMenuCheckmarkGlyph           = 0x12, /* Checkmark key*/
  kMenuDiamondGlyph             = 0x13, /* Diamond key*/
  kMenuAppleLogoFilledGlyph     = 0x14, /* Apple logo key (filled)*/
  kMenuParagraphKoreanGlyph     = 0x15, /* Unassigned (paragraph in Korean)*/
  kMenuDeleteLeftGlyph          = 0x17, /* Delete to the left key (for left-to-right script systems)*/
  kMenuLeftArrowDashedGlyph     = 0x18, /* Leftward dashed arrow key*/
  kMenuUpArrowDashedGlyph       = 0x19, /* Upward dashed arrow key*/
  kMenuRightArrowDashedGlyph    = 0x1A, /* Rightward dashed arrow key*/
  kMenuEscapeGlyph              = 0x1B, /* Escape key*/
  kMenuClearGlyph               = 0x1C, /* Clear key*/
  kMenuLeftDoubleQuotesJapaneseGlyph = 0x1D, /* Unassigned (left double quotes in Japanese)*/
  kMenuRightDoubleQuotesJapaneseGlyph = 0x1E, /* Unassigned (right double quotes in Japanese)*/
  kMenuTrademarkJapaneseGlyph   = 0x1F, /* Unassigned (trademark in Japanese)*/
  kMenuBlankGlyph               = 0x61, /* Blank key*/
  kMenuPageUpGlyph              = 0x62, /* Page up key*/
  kMenuCapsLockGlyph            = 0x63, /* Caps lock key*/
  kMenuLeftArrowGlyph           = 0x64, /* Left arrow key*/
  kMenuRightArrowGlyph          = 0x65, /* Right arrow key*/
  kMenuNorthwestArrowGlyph      = 0x66, /* Northwest arrow key*/
  kMenuHelpGlyph                = 0x67, /* Help key*/
  kMenuUpArrowGlyph             = 0x68, /* Up arrow key*/
  kMenuSoutheastArrowGlyph      = 0x69, /* Southeast arrow key*/
  kMenuDownArrowGlyph           = 0x6A, /* Down arrow key*/
  kMenuPageDownGlyph            = 0x6B, /* Page down key*/
  kMenuAppleLogoOutlineGlyph    = 0x6C, /* Apple logo key (outline)*/
  kMenuContextualMenuGlyph      = 0x6D, /* Contextual menu key*/
  kMenuPowerGlyph               = 0x6E, /* Power key*/
  kMenuF1Glyph                  = 0x6F, /* F1 key*/
  kMenuF2Glyph                  = 0x70, /* F2 key*/
  kMenuF3Glyph                  = 0x71, /* F3 key*/
  kMenuF4Glyph                  = 0x72, /* F4 key*/
  kMenuF5Glyph                  = 0x73, /* F5 key*/
  kMenuF6Glyph                  = 0x74, /* F6 key*/
  kMenuF7Glyph                  = 0x75, /* F7 key*/
  kMenuF8Glyph                  = 0x76, /* F8 key*/
  kMenuF9Glyph                  = 0x77, /* F9 key*/
  kMenuF10Glyph                 = 0x78, /* F10 key*/
  kMenuF11Glyph                 = 0x79, /* F11 key*/
  kMenuF12Glyph                 = 0x7A, /* F12 key*/
  kMenuF13Glyph                 = 0x87, /* F13 key*/
  kMenuF14Glyph                 = 0x88, /* F14 key*/
  kMenuF15Glyph                 = 0x89, /* F15 key*/
  kMenuControlISOGlyph          = 0x8A  /* Control key (ISO standard)*/
};


/*
 *  MenuAttributes
 *  
 *  Summary:
 *    Menu attributes control behavior of the entire menu. They are
 *    used with the Get/ChangeMenuAttributes APIs.
 */

  /*
   * No column space is allocated for the mark character when this menu
   * is drawn.
   */
typedef UInt32 MenuAttributes;
enum {
  kMenuAttrExcludesMarkColumn   = (1 << 0),

  /*
   * The menu title is automatically disabled when all items are
   * disabled.
   */
  kMenuAttrAutoDisable          = (1 << 2),

  /*
   * The pencil glyph from the Keyboard font (kMenuPencilGlyph) is used
   * to draw the Control modifier key in menu keyboard equivalents.
   * This appearance is typically used only by Japanese input method
   * menus.
   */
  kMenuAttrUsePencilGlyph       = (1 << 3)
};

enum {
  kMenuAttrCanBeTornOff         = (1 << 1) /* Menu can be torn off [not yet implemented]*/
};


/*
 *  MenuItemAttributes
 *  
 *  Summary:
 *    Menu item attributes control behavior of individual menu items.
 *    They are used with the Get/ChangeMenuItemAttributes APIs.
 */

  /*
   * This item is disabled.
   */
typedef UInt32 MenuItemAttributes;
enum {
  kMenuItemAttrDisabled         = (1 << 0),

  /*
   * This item's icon is disabled.
   */
  kMenuItemAttrIconDisabled     = (1 << 1),

  /*
   * Allows the parent item of a submenu to be selectable.
   */
  kMenuItemAttrSubmenuParentChoosable = (1 << 2),

  /*
   * This item changes dynamically based on modifier key state.
   */
  kMenuItemAttrDynamic          = (1 << 3),

  /*
   * This item is not part of the same dynamic group as the previous
   * item.
   */
  kMenuItemAttrNotPreviousAlternate = (1 << 4),

  /*
   * This item is not drawn when the menu is displayed.
   */
  kMenuItemAttrHidden           = (1 << 5),

  /*
   * This item is a separator; the text of the item is ignored.
   */
  kMenuItemAttrSeparator        = (1 << 6),

  /*
   * This item is a menu section header; it is disabled and
   * unselectable.
   */
  kMenuItemAttrSectionHeader    = (1 << 7),

  /*
   * Metacharacters in the text of this item (such as the dash) are
   * ignored.
   */
  kMenuItemAttrIgnoreMeta       = (1 << 8),

  /*
   * This item is recognized by IsMenuKeyEvent when it is passed an
   * auto-repeat keyboard event.
   */
  kMenuItemAttrAutoRepeat       = (1 << 9),

  /*
   * When MenuEvent and IsMenuKeyEvent compare this item's keyboard
   * equivalent against a keyboard event, they use the item's virtual
   * keycode equivalent rather than its character code equivalent.
   */
  kMenuItemAttrUseVirtualKey    = (1 << 10),

  /*
   * This item is drawn in a customized fashion by the application.
   * Causes custom menu item drawing Carbon events to be sent. This
   * attribute is available in CarbonLib 1.4 and later, and in Mac OS X
   * after 10.0.x.
   */
  kMenuItemAttrCustomDraw       = (1 << 11)
};


/*
 *  MenuTrackingMode
 *  
 *  Summary:
 *    A menu tracking mode constant is part of the
 *    kEventMenuBeginTracking and kEventMenuChangeTrackingMode Carbon
 *    events. It indicates whether menus are being tracked using the
 *    mouse or keyboard.
 */

  /*
   * Menus are being tracked using the mouse.
   */
typedef UInt32 MenuTrackingMode;
enum {
  kMenuTrackingModeMouse        = 1,

  /*
   * Menus are being tracked using the keyboard.
   */
  kMenuTrackingModeKeyboard     = 2
};


/*
 *  MenuEventOptions
 *  
 *  Summary:
 *    Menu event options control how the menus are searched for an item
 *    matching a particular keyboard event. They are used with the
 *    IsMenuKeyEvent API.
 */

  /*
   * Disabled items are examined for a match.
   */
typedef UInt32 MenuEventOptions;
enum {
  kMenuEventIncludeDisabledItems = 0x0001,

  /*
   * Don't hilite the menu title if a match is found.
   */
  kMenuEventQueryOnly           = 0x0002,

  /*
   * Don't look for a match in submenus of the starting menu.
   */
  kMenuEventDontCheckSubmenus   = 0x0004
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Types                                                                        */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef SInt16                          MenuID;
typedef UInt16                          MenuItemIndex;
typedef UInt32                          MenuCommand;
#if !OPAQUE_TOOLBOX_STRUCTS
struct MenuInfo {
  MenuID              menuID;                 /* in Carbon use Get/SetMenuID*/
  short               menuWidth;              /* in Carbon use Get/SetMenuWidth*/
  short               menuHeight;             /* in Carbon use Get/SetMenuHeight*/
  Handle              menuProc;               /* not supported in Carbon*/
  long                enableFlags;            /* in Carbon use Enable/DisableMenuItem, IsMenuItemEnable*/
  Str255              menuData;               /* in Carbon use Get/SetMenuTitle*/
};
typedef struct MenuInfo                 MenuInfo;
typedef MenuInfo *                      MenuPtr;
typedef MenuPtr *                       MenuHandle;
#else
typedef struct OpaqueMenuHandle*        MenuHandle;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/* MenuRef and MenuHandle are equivalent. Use either. We don't care.*/
typedef MenuHandle                      MenuRef;
typedef Handle                          MenuBarHandle;
struct MCEntry {
  MenuID              mctID;                  /*menu ID.  ID = 0 is the menu bar*/
  short               mctItem;                /*menu Item. Item = 0 is a title*/
  RGBColor            mctRGB1;                /*usage depends on ID and Item*/
  RGBColor            mctRGB2;                /*usage depends on ID and Item*/
  RGBColor            mctRGB3;                /*usage depends on ID and Item*/
  RGBColor            mctRGB4;                /*usage depends on ID and Item*/
  short               mctReserved;            /*reserved for internal use*/
};
typedef struct MCEntry                  MCEntry;
typedef MCEntry *                       MCEntryPtr;
typedef MCEntry                         MCTable[1];
typedef MCEntry *                       MCTablePtr;
typedef MCTablePtr *                    MCTableHandle;
struct MenuCRsrc {
  short               numEntries;             /*number of entries*/
  MCTable             mcEntryRecs;            /*ARRAY [1..numEntries] of MCEntry*/
};
typedef struct MenuCRsrc                MenuCRsrc;
typedef MenuCRsrc *                     MenuCRsrcPtr;
typedef MenuCRsrcPtr *                  MenuCRsrcHandle;
#if TARGET_OS_WIN32
/* QuickTime 3.0 */
struct MenuAccessKeyRec {
  short               count;
  long                flags;
  unsigned char       keys[1];
};
typedef struct MenuAccessKeyRec         MenuAccessKeyRec;
typedef MenuAccessKeyRec *              MenuAccessKeyPtr;
typedef MenuAccessKeyPtr *              MenuAccessKeyHandle;
/*
 *  SetMenuItemHotKey()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* TARGET_OS_WIN32 */


/*
 *  MenuTrackingData
 *  
 *  Summary:
 *    The MenuTrackingData structure contains information about a menu
 *    currently being displayed. It is used with the
 *    GetMenuTrackingData API.
 */
struct MenuTrackingData {
  MenuRef             menu;
  MenuItemIndex       itemSelected;
  MenuItemIndex       itemUnderMouse;
  Rect                itemRect;
  SInt32              virtualMenuTop;
  SInt32              virtualMenuBottom;
};
typedef struct MenuTrackingData         MenuTrackingData;
typedef MenuTrackingData *              MenuTrackingDataPtr;

/*
 *  MDEFHiliteItemData
 *  
 *  Summary:
 *    The MDEFHiliteItemData structure contains information about which
 *    menu items should be hilited and unhilited as the user moves
 *    through the menus. It is used by menu definition functions, which
 *    receive a pointer to an MDEFHiliteItemData structure as the
 *    whichItem parameter during kMenuHiliteItemMsg.
 */
struct MDEFHiliteItemData {

  /*
   * The item that was previously selected. It should be redrawn in an
   * unhilited state. May be zero if no item was previously selected.
   */
  MenuItemIndex       previousItem;

  /*
   * The item that is now selected. It should be redrawn in a hilited
   * state. May be zero if no item is now selected.
   */
  MenuItemIndex       newItem;

  /*
   * A CoreGraphics context that the MDEF should draw into. The Menu
   * Manager will flush the context after the MDEF has returned.
   */
  void *              context;
};
typedef struct MDEFHiliteItemData       MDEFHiliteItemData;
typedef MDEFHiliteItemData *            MDEFHiliteItemDataPtr;
typedef MDEFHiliteItemData              HiliteMenuItemData;
typedef MDEFHiliteItemDataPtr           HiliteMenuItemDataPtr;

/*
 *  MDEFDrawData
 *  
 *  Summary:
 *    The MDEFDrawData structure contains information needed to draw a
 *    menu. It is used by menu definition functions, which receive a
 *    pointer to an MDEFDrawData structure as the whichItem parameter
 *    during kMenuDrawMsg.
 */
struct MDEFDrawData {

  /*
   * Information about the menu being drawn. The MDEF should fill in
   * the virtualMenuTop and virtualMenuBottom fields of this structure
   * while drawing the menu.
   */
  MenuTrackingData    trackingData;

  /*
   * A CoreGraphics context that the MDEF should draw into. The Menu
   * Manager will flush the context after the MDEF has returned.
   */
  void *              context;
};
typedef struct MDEFDrawData             MDEFDrawData;
typedef MDEFDrawData *                  MDEFDrawDataPtr;

/*
 *  MDEFFindItemData
 *  
 *  Summary:
 *    The MDEFFindItemData structure contains information needed to
 *    determine which item is currently selected by the user. It is
 *    used by menu definition functions, which receive a pointer to an
 *    MDEFDrawData structure as the whichItem parameter during
 *    kMenuFindItemMsg.
 */
struct MDEFFindItemData {

  /*
   * Information about the menu being drawn. The MDEF should fill in
   * the itemSelected, itemUnderMouse, and itemRect fields of this
   * structure after determining which item is at the specified point.
   */
  MenuTrackingData    trackingData;

  /*
   * A CoreGraphics context that the MDEF should draw into if it needs
   * to scroll the menu during the FindItem message. The Menu Manager
   * will flush the context after the MDEF has returned.
   */
  void *              context;
};
typedef struct MDEFFindItemData         MDEFFindItemData;
typedef MDEFFindItemData *              MDEFFindItemDataPtr;

/*
 *  MDEFDrawItemsData
 *  
 *  Summary:
 *    The MDEFDrawItemsData structure contains information about which
 *    menu items to redraw. It is used by menu definition functions,
 *    which receive a pointer to an MDEFDrawItemsData structure as the
 *    whichItem parameter during kMenuDrawItemsMsg.
 */
struct MDEFDrawItemsData {

  /*
   * The first item to draw.
   */
  MenuItemIndex       firstItem;

  /*
   * The last item to draw.
   */
  MenuItemIndex       lastItem;

  /*
   * Information about the menu's tracking state. The virtualMenuTop
   * and virtualMenuBottom fields in this structure will be the most
   * useful in handling the DrawItems message.
   */
  MenuTrackingData *  trackingData;

  /*
   * A CoreGraphics context that the MDEF should draw into. The Menu
   * Manager will flush the context after the MDEF returns.
   */
  void *              context;
};
typedef struct MDEFDrawItemsData        MDEFDrawItemsData;
typedef MDEFDrawItemsData *             MDEFDrawItemsDataPtr;

/*
 *  Summary:
 *    A MenuItemDataFlags value indicates which fields of a
 *    MenuItemDataRec structure should be used by the
 *    Copy/SetMenuItemData APIs. All MenuItemDataFlags may be used when
 *    getting or setting the contents of a menu item; some may also be
 *    used when getting or setting information about the menu itself,
 *    if the item index given to Copy/SetMenuItemData is 0.
 */

  /*
   * Set or return the Str255 text of a menu using the
   * MenuItemDataRec.text field. If getting the text, the text field
   * must be initialized with a pointer to a Str255 variable before
   * calling CopyMenuItemData. If both kMenuItemDataText and
   * kMenuItemCFString are set on entry to CopyMenuItemData, the API
   * will determine whether the menu text was most recently set using a
   * Str255 or CFString, and return only that text format; the flags
   * value for the other format will be cleared. Valid for both menu
   * items and the menu title (if item number is 0).
   */
enum {
  kMenuItemDataText             = (1 << 0),

  /*
   * Set or return the mark character of a menu item using the
   * MenuItemDataRec.mark field. Valid only for menu items.
   */
  kMenuItemDataMark             = (1 << 1),

  /*
   * Set or return the command key of a menu item using the
   * MenuItemDataRec.cmdKey field. Valid only for menu items.
   */
  kMenuItemDataCmdKey           = (1 << 2),

  /*
   * Set or return the command key glyph of a menu item using the
   * MenuItemDataRec.cmdKeyGlyph field. Valid only for menu items.
   */
  kMenuItemDataCmdKeyGlyph      = (1 << 3),

  /*
   * Set or return the command key modifiers of a menu item using the
   * MenuItemDataRec.cmdKeyModifiers field. Valid only for menu items.
   */
  kMenuItemDataCmdKeyModifiers  = (1 << 4),

  /*
   * Set or return the QuickDraw text style of a menu item using the
   * MenuItemDataRec.style field. Valid only for menu items.
   */
  kMenuItemDataStyle            = (1 << 5),

  /*
   * Set or return the enable state of a menu using the
   * MenuItemDataRec.enabled field. Valid for both menu items and the
   * menu itself (if item number is 0).
   */
  kMenuItemDataEnabled          = (1 << 6),

  /*
   * Set or return the enable state of a menu item icon using the
   * MenuItemDataRec.iconEnabled field. Valid only for menu items.
   */
  kMenuItemDataIconEnabled      = (1 << 7),

  /*
   * Set or return the icon resource ID of a menu item using the
   * MenuItemDataRec.iconID field. Valid only for menu items.
   */
  kMenuItemDataIconID           = (1 << 8),

  /*
   * Set or return the icon handle of a menu item using the
   * MenuItemDataRec.iconType and MenuItemDataRec.iconHandle fields.
   * Both fields must be initialized if setting the icon handle; both
   * fields will be returned when getting the handle. The iconType
   * field should contain one of the constants kMenuIconType,
   * kMenuShrinkIconType, kMenuSmallIconType, kMenuColorIconType,
   * kMenuIconSuiteType, or kMenuIconRefType. An icon handle may be a
   * handle to an ICON resource, a SICN resource, a cicn resource, an
   * IconSuite, or an IconRef. Valid only for menu items.
   */
  kMenuItemDataIconHandle       = (1 << 9),

  /*
   * Set or return the command ID of a menu item using the
   * MenuItemDataRec.cmdID field. Valid only for menu items.
   */
  kMenuItemDataCommandID        = (1 << 10),

  /*
   * Set or return the text encoding of a menu item using the
   * MenuItemDataRec.encoding field. Valid only for menu items.
   */
  kMenuItemDataTextEncoding     = (1 << 11),
  kMenuItemDataSubmenuID        = (1 << 12),
  kMenuItemDataSubmenuHandle    = (1 << 13),
  kMenuItemDataFontID           = (1 << 14),
  kMenuItemDataRefcon           = (1 << 15),
  kMenuItemDataAttributes       = (1 << 16),
  kMenuItemDataCFString         = (1 << 17),

  /*
   * Set or return the properties of a menu using the
   * MenuItemDataRec.properties field. If setting the properties, the
   * properties field should contain a collection with the new
   * properties; existing menu properties with the same collection
   * creator and tag will be replaced by the new properties. If getting
   * the properties, the properties field should either be set to NULL
   * or to a valid Collection. If NULL, a new collection is allocated
   * by the CopyMenuItemData and returned in the properties field. If
   * not NULL, the entire contents of the collection are replaced by
   * the properties of the menu. Valid for both menu items and the menu
   * itself (if item number is 0).
   */
  kMenuItemDataProperties       = (1 << 18),

  /*
   * Set or return the item indent level of a menu item using the
   * MenuItemDataRec.indent field. Valid only for menu items.
   */
  kMenuItemDataIndent           = (1 << 19),

  /*
   * Set or return the virtual key code keyboard equivalent of a menu
   * item using the MenuItemDataRec.cmdVirtualKey field. Valid only for
   * menu items. On output, only valid if the item has the
   * kMenuItemAttrUseVirtualKeyCode attribute.
   */
  kMenuItemDataCmdVirtualKey    = (1 << 20),
  kMenuItemDataAllDataVersionOne = 0x000FFFFF,
  kMenuItemDataAllDataVersionTwo = kMenuItemDataAllDataVersionOne | kMenuItemDataCmdVirtualKey
};

enum {
  kMenuItemDataAllData          = kMenuItemDataAllDataVersionTwo
};

typedef UInt64                          MenuItemDataFlags;

/*
 *  MenuItemDataRec
 *  
 *  Summary:
 *    The MenuItemDataRec structure is used to get and change aspects
 *    of a menu item. It is used with the Copy/SetMenuItemData APIs.
 *  
 *  Discussion:
 *    When using this structure with Copy/SetMenuItemData, the caller
 *    must first set the whichData field to a combination of
 *    MenuItemDataFlags indicating which specific data should be
 *    retrieved or set. Some fields also require initialization before
 *    calling CopyMenuItemData; see the individual MenuItemDataFlags
 *    documentation for details.
 */
struct MenuItemDataRec {
  MenuItemDataFlags   whichData;
  StringPtr           text;
  UniChar             mark;
  UniChar             cmdKey;
  UInt32              cmdKeyGlyph;
  UInt32              cmdKeyModifiers;
  Style               style;
  Boolean             enabled;
  Boolean             iconEnabled;
  UInt8               filler1;
  SInt32              iconID;
  UInt32              iconType;
  Handle              iconHandle;
  MenuCommand         cmdID;
  TextEncoding        encoding;
  MenuID              submenuID;
  MenuRef             submenuHandle;
  SInt32              fontID;
  UInt32              refcon;
  OptionBits          attr;
  CFStringRef         cfText;
  Collection          properties;
  UInt32              indent;
  UInt16              cmdVirtualKey;
};
typedef struct MenuItemDataRec          MenuItemDataRec;
typedef MenuItemDataRec *               MenuItemDataPtr;
typedef UInt32                          MenuItemID;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu ProcPtrs                                                                     */
/*                                                                                      */
/*  All of these procs are considered deprecated.  Developers interested in portability */
/*  to Carbon should avoid them entirely, if at all possible.                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef CALLBACK_API( void , MenuDefProcPtr )(short message, MenuRef theMenu, Rect *menuRect, Point hitPt, short *whichItem);
typedef STACK_UPP_TYPE(MenuDefProcPtr)                          MenuDefUPP;
/*
 *  NewMenuDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MenuDefUPP
NewMenuDefUPP(MenuDefProcPtr userRoutine);

/*
 *  DisposeMenuDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMenuDefUPP(MenuDefUPP userUPP);

/*
 *  InvokeMenuDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeMenuDefUPP(
  short       message,
  MenuRef     theMenu,
  Rect *      menuRect,
  Point       hitPt,
  short *     whichItem,
  MenuDefUPP  userUPP);

typedef CALLBACK_API( long , MenuBarDefProcPtr )(short selector, short message, short parameter1, long parameter2);
typedef CALLBACK_API( void , MenuHookProcPtr )(void);
typedef CALLBACK_API( short , MBarHookProcPtr )(Rect * menuRect);
typedef STACK_UPP_TYPE(MenuBarDefProcPtr)                       MenuBarDefUPP;
typedef STACK_UPP_TYPE(MenuHookProcPtr)                         MenuHookUPP;
typedef STACK_UPP_TYPE(MBarHookProcPtr)                         MBarHookUPP;
/*
 *  NewMenuBarDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  NewMenuHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  NewMBarHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeMenuBarDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeMenuHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeMBarHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeMenuBarDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeMenuHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeMBarHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

enum {
  kMenuDefProcPtr               = 0     /* raw proc-ptr access based on old MDEF */
};

typedef UInt32                          MenuDefType;
enum {
  kMenuDefObjectClass           = 1     /* event-based definition (not yet implemented)*/
};

typedef struct OpaqueMenuLayoutRef*     MenuLayoutRef;
struct MenuDefSpec {
  MenuDefType         defType;
  union {
    MenuDefUPP          defProc;
  }                       u;
};
typedef struct MenuDefSpec              MenuDefSpec;
typedef MenuDefSpec *                   MenuDefSpecPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Manager Initialization                                                       */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  InitProcMenu()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  InitMenus()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Manipulation                                                                 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  NewMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern MenuRef 
NewMenu(
  MenuID             menuID,
  ConstStr255Param   menuTitle);


/*
 *  [Mac]GetMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacGetMenu GetMenu
#endif
extern MenuRef 
MacGetMenu(short resourceID);


/*
 *  DisposeMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeMenu(MenuRef theMenu);


/*
 *  CalcMenuSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CalcMenuSize(MenuRef theMenu);


/*
 *  CountMItems()
 *  
 *  Summary:
 *    Renamed to CountMenuItems in Carbon
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
 *  CountMenuItems()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.3 and later or as macro/inline
 */
extern UInt16 
CountMenuItems(MenuRef theMenu);




/* Routines available in Mac OS 8.5 and later, and on Mac OS 8.1 and later using CarbonLib 1.1 and later*/

/*
 *  GetMenuFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
GetMenuFont(
  MenuRef   menu,
  SInt16 *  outFontID,
  UInt16 *  outFontSize);


/*
 *  SetMenuFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
SetMenuFont(
  MenuRef   menu,
  SInt16    inFontID,
  UInt16    inFontSize);


/*
 *  GetMenuExcludesMarkColumn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern Boolean 
GetMenuExcludesMarkColumn(MenuRef menu);


/*
 *  SetMenuExcludesMarkColumn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
SetMenuExcludesMarkColumn(
  MenuRef   menu,
  Boolean   excludesMark);


/*
 *  RegisterMenuDefinition()
 *  
 *  Summary:
 *    Registers or unregisters a binding between a resource ID and a
 *    menu definition function.
 *  
 *  Discussion:
 *    In the Mac OS 8.x Menu Manager, a 'MENU' resource can contain an
 *    embedded MDEF procID that is used by the Menu Manager as the
 *    resource ID of an 'MDEF' resource to measure and draw the menu.
 *    The 'MDEF' resource is loaded by the Menu Manager when you load
 *    the menu with GetMenu. Since MDEFs can no longer be packaged as
 *    code resources on Carbon, the procID can no longer refer directly
 *    to an MDEF resource. However, using RegisterMenuDefinition you
 *    can instead specify a UniversalProcPtr pointing to code in your
 *    application code fragment.
 *  
 *  Parameters:
 *    
 *    inResID:
 *      An MDEF proc ID, as used in a 'MENU' resource.
 *    
 *    inDefSpec:
 *      Specifies the MenuDefUPP that should be used for menus with the
 *      given MDEF proc ID. Passing NULL allows you to unregister the
 *      menu definition that had been associated with the given MDEF
 *      proc ID.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterMenuDefinition(
  SInt16           inResID,
  MenuDefSpecPtr   inDefSpec);


/*
 *  CreateNewMenu()
 *  
 *  Summary:
 *    Creates a new, untitled, empty menu.
 *  
 *  Discussion:
 *    CreateNewMenu is preferred over NewMenu because it allows you to
 *    specify the menu's attributes and it does not require you to
 *    specify a Str255-based menu title. To set the menu title, you can
 *    use either SetMenuTitle or SetMenuTitleWithCFString.
 *  
 *  Parameters:
 *    
 *    inMenuID:
 *      The menu ID to use for the new menu.
 *    
 *    inMenuAttributes:
 *      The menu attributes to use for the new menu.
 *    
 *    outMenuRef:
 *      On exit, contains the new menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateNewMenu(
  MenuID           inMenuID,
  MenuAttributes   inMenuAttributes,
  MenuRef *        outMenuRef);


/*
 *  CreateCustomMenu()
 *  
 *  Summary:
 *    Creates a new, untitled, empty menu using a custom menu
 *    definition function.
 *  
 *  Discussion:
 *    Similar to CreateNewMenu, but also allows you to specify a custom
 *    menu definition function.
 *  
 *  Parameters:
 *    
 *    inDefSpec:
 *      Specifies a custom menu definition function. defSpec->defType
 *      must be kMenuDefProcPtr.
 *    
 *    inMenuID:
 *      The menu ID to use for the new menu.
 *    
 *    inMenuAttributes:
 *      The menu attributes to use for the new menu.
 *    
 *    outMenuRef:
 *      On exit, contains the new menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCustomMenu(
  const MenuDefSpec *  inDefSpec,
  MenuID               inMenuID,
  MenuAttributes       inMenuAttributes,
  MenuRef *            outMenuRef);


/*
 *  IsValidMenu()
 *  
 *  Summary:
 *    Determines if a menu is valid.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu to check for validity.
 *  
 *  Result:
 *    Indicates whether the menu is valid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsValidMenu(MenuRef inMenu);


/*
 *  GetMenuRetainCount()
 *  
 *  Summary:
 *    Returns the retain count of this menu.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose retain count to increment.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern ItemCount 
GetMenuRetainCount(MenuRef inMenu);


/*
 *  RetainMenu()
 *  
 *  Summary:
 *    Increments the retain count of a menu.
 *  
 *  Discussion:
 *    RetainMenu does not create a new menu. It simply adds one to the
 *    retain count. If called on a menu that was not created by
 *    CarbonLib, it will not affect the menu's retain count.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose retain count to increment.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RetainMenu(MenuRef inMenu);


/*
 *  ReleaseMenu()
 *  
 *  Summary:
 *    Decrements the retain count of a menu.
 *  
 *  Discussion:
 *    If called on a menu that was not created by CarbonLib, it will
 *    not affect the menu's retain count.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose retain count to decrement. If the retain count
 *      falls to zero, the menu is destroyed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ReleaseMenu(MenuRef inMenu);


/*
 *  DuplicateMenu()
 *  
 *  Summary:
 *    Creates a new menu that is a copy of another menu.
 *  
 *  Discussion:
 *    Unlike CloneMenu, DuplicateMenu creates an entirely new menu that
 *    is an exact copy of the original menu. The MDEF for the new menu
 *    will receive an init message after the menu has been fully
 *    created.
 *  
 *  Parameters:
 *    
 *    inSourceMenu:
 *      The menu to duplicate.
 *    
 *    outMenu:
 *      On exit, a copy of the source menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DuplicateMenu(
  MenuRef    inSourceMenu,
  MenuRef *  outMenu);


/*
 *  CopyMenuTitleAsCFString()
 *  
 *  Summary:
 *    Returns a CFString containing the title of a menu.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose title to return.
 *    
 *    outString:
 *      On exit, a CFString containing the menu's title. This string
 *      must be released by the caller.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyMenuTitleAsCFString(
  MenuRef        inMenu,
  CFStringRef *  outString);


/*
 *  SetMenuTitleWithCFString()
 *  
 *  Summary:
 *    Sets the title of a menu to the text contained in a CFString.
 *  
 *  Discussion:
 *    The Menu Manager will either make its own copy or just increment
 *    the refcount of the CFString before returning from
 *    SetMenuTitleWithCFString, depending on whether the string is
 *    mutable or immutable. If the string is mutable, modifying the
 *    string after calling SetMenuTitleWithCFString will have no effect
 *    on the menu's actual title. The caller may release the string
 *    after calling SetMenuTitleWithCFString.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose title to set.
 *    
 *    inString:
 *      The string containing the new menu title text.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuTitleWithCFString(
  MenuRef       inMenu,
  CFStringRef   inString);


/*
 *  SetMenuTitleIcon()
 *  
 *  Summary:
 *    Sets the title of a menu to be an icon.
 *  
 *  Discussion:
 *    The Menu Manager takes ownership of the supplied icon after this
 *    call. When a menu with an title icon is disposed, the Menu
 *    Manager will dispose the icon also; the Menu Manager will also
 *    dispose of the current title icon when a new text or icon title
 *    is supplied for a menu. If an IconRef is specified, the Menu
 *    Manager will increment its refcount, so you may freely release
 *    your reference to the IconRef without invalidating the Menu
 *    Manager's copy. The menubar will be invalidated by this call, and
 *    redrawn at the next opportunity.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose title to set.
 *    
 *    inType:
 *      The type of icon being used to specify the icon title; use
 *      kMenuNoIcon to remove the icon from the menu title. The
 *      supported types are kMenuIconSuiteType and kMenuIconRefType.
 *    
 *    inIcon:
 *      The icon; must be NULL if inType is kMenuNoIcon. The supported
 *      icon formats are IconSuiteRef and IconRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuTitleIcon(
  MenuRef   inMenu,
  UInt32    inType,
  void *    inIcon);


/*
 *  GetMenuTitleIcon()
 *  
 *  Summary:
 *    Retrieves the icon, if any, being used as the title of a menu.
 *  
 *  Discussion:
 *    This API does not increment a refcount on the returned icon. The
 *    caller should not release the icon.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose icon title to retrieve.
 *    
 *    outType:
 *      On exit, contains the type of icon being used as the title of
 *      the menu. Contains kMenuNoIcon if the menu does not have an
 *      icon title.
 *    
 *    outIcon:
 *      On exit, contains the IconSuiteRef or IconRef being used as the
 *      title of the menu, or NULL if the menu does not have an icon
 *      title. May be NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuTitleIcon(
  MenuRef   inMenu,
  UInt32 *  outType,       /* can be NULL */
  void **   outIcon);      /* can be NULL */


/*
 *  InvalidateMenuSize()
 *  
 *  Summary:
 *    Invalidates the menu size so that it will be recalculated when
 *    next displayed.
 *  
 *  Discussion:
 *    The pre-Carbon technique for invalidating the menu size was to
 *    set the width and height to -1. Although this technique still
 *    works, for best compatibility it's preferable to use the
 *    InvalidateMenuSize API so that the Menu Manager has explicit
 *    notification that the menu is invalid.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose size to invalidate.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
InvalidateMenuSize(MenuRef inMenu);


/*
 *  IsMenuSizeInvalid()
 *  
 *  Summary:
 *    Determines if a menu's size is invalid and should be recalculated.
 *  
 *  Discussion:
 *    The pre-Carbon technique for determining if a menu's size is
 *    invalid was to check if the width or height was -1. This
 *    technique is not always reliable on Carbon due to implementation
 *    changes in the Menu Manager. You should now use IsMenuSizeInvalid
 *    instead.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose size to examine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsMenuSizeInvalid(MenuRef inMenu);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ÊMDEF support                                                                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  EraseMenuBackground()
 *  
 *  Summary:
 *    Erases a portion of a menu background in preparation for further
 *    drawing.
 *  
 *  Discussion:
 *    It is necessary to erase the menu background before calling
 *    DrawThemeMenuBackground because some themes (such as Aqua on Mac
 *    OS X) draw the menu background using the alpha channel, and if
 *    the area underneath the menu background is not erased, portions
 *    of the old image will show through the menu background.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose background to erase.
 *    
 *    inEraseRect:
 *      The bounds of the area to erase, in local coordinates to the
 *      current port.
 *    
 *    inContext:
 *      The CG context to erase. If NULL, EraseMenuBackground will
 *      create a context based on the current port.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
EraseMenuBackground(
  MenuRef        inMenu,
  const Rect *   inEraseRect,
  CGContextRef   inContext);        /* can be NULL */


/*
 *  ScrollMenuImage()
 *  
 *  Summary:
 *    Scrolls a portion of the menu image.
 *  
 *  Discussion:
 *    Menus on Mac OS X use an alpha channel, and QuickDraw does not
 *    support alpha channels. Therefore, scrolling a menu image with
 *    ScrollRect or other QuickDraw APIs does not work correctly; it
 *    results in the destruction of the alpha channel data. The
 *    ScrollMenuImage API uses CoreGraphics to move the menu image,
 *    preserving the alpha channel.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu whose image to scroll.
 *    
 *    inScrollRect:
 *      The bounds of the rect to scroll.
 *    
 *    inHScroll:
 *      The distance to scroll horizontally.
 *    
 *    inVScroll:
 *      The distance to scroll vertically.
 *    
 *    inContext:
 *      The CG context to erase. If NULL, ScrollMenuImage will create a
 *      context based on the current port.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ScrollMenuImage(
  MenuRef        inMenu,
  const Rect *   inScrollRect,
  int            inHScroll,
  int            inVScroll,
  CGContextRef   inContext);         /* can be NULL */


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Item Insertion                                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  [Mac]AppendMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacAppendMenu AppendMenu
#endif
extern void 
MacAppendMenu(
  MenuRef            menu,
  ConstStr255Param   data);


/*
 *  InsertResMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InsertResMenu(
  MenuRef   theMenu,
  ResType   theType,
  short     afterItem);


/*
 *  AppendResMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AppendResMenu(
  MenuRef   theMenu,
  ResType   theType);


/*
 *  [Mac]InsertMenuItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacInsertMenuItem InsertMenuItem
#endif
extern void 
MacInsertMenuItem(
  MenuRef            theMenu,
  ConstStr255Param   itemString,
  short              afterItem);


/*
 *  DeleteMenuItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DeleteMenuItem(
  MenuRef   theMenu,
  short     item);


/*
 *  InsertFontResMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InsertFontResMenu(
  MenuRef   theMenu,
  short     afterItem,
  short     scriptFilter);


/*
 *  InsertIntlResMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InsertIntlResMenu(
  MenuRef   theMenu,
  ResType   theType,
  short     afterItem,
  short     scriptFilter);


/*
 *  AppendMenuItemText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
AppendMenuItemText(
  MenuRef            menu,
  ConstStr255Param   inString);


/*
 *  InsertMenuItemText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
InsertMenuItemText(
  MenuRef            menu,
  ConstStr255Param   inString,
  MenuItemIndex      afterItem);


/*
 *  CopyMenuItems()
 *  
 *  Summary:
 *    Copies menu items from one menu to another.
 *  
 *  Parameters:
 *    
 *    inSourceMenu:
 *      The menu from which to copy items.
 *    
 *    inFirstItem:
 *      The first item to copy.
 *    
 *    inNumItems:
 *      The number of items to copy.
 *    
 *    inDestMenu:
 *      The menu to which to copy items.
 *    
 *    inInsertAfter:
 *      The menu item in the destination menu after which to insert the
 *      copied items.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyMenuItems(
  MenuRef         inSourceMenu,
  MenuItemIndex   inFirstItem,
  ItemCount       inNumItems,
  MenuRef         inDestMenu,
  MenuItemIndex   inInsertAfter);


/*
 *  DeleteMenuItems()
 *  
 *  Summary:
 *    Deletes multiple menu items.
 *  
 *  Discussion:
 *    This API is more efficient than calling DeleteMenuItem multiple
 *    times.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu from which to delete items.
 *    
 *    inFirstItem:
 *      The first item to delete.
 *    
 *    inNumItems:
 *      The number of items to delete.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DeleteMenuItems(
  MenuRef         inMenu,
  MenuItemIndex   inFirstItem,
  ItemCount       inNumItems);


/*
 *  AppendMenuItemTextWithCFString()
 *  
 *  Summary:
 *    Appends a new menu item with text from a CFString.
 *  
 *  Discussion:
 *    The Menu Manager will either make its own copy or just increment
 *    the refcount of the CFString before returning from
 *    AppendMenuItemWithTextCFString, depending on whether the string
 *    is mutable or immutable. If the string is mutable, modifying the
 *    string after calling AppendMenuItemTextWithCFString will have no
 *    effect on the menu item's actual text. The caller may release the
 *    string after calling AppendMenuItemTextWithCFString.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu to which to append the new item.
 *    
 *    inString:
 *      The text of the new item.
 *    
 *    inAttributes:
 *      The attributes of the new item.
 *    
 *    inCommandID:
 *      The command ID of the new item.
 *    
 *    outNewItem:
 *      On exit, the index of the new item. May be NULL if the caller
 *      does not need this information.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
AppendMenuItemTextWithCFString(
  MenuRef              inMenu,
  CFStringRef          inString,
  MenuItemAttributes   inAttributes,
  MenuCommand          inCommandID,
  MenuItemIndex *      outNewItem);        /* can be NULL */


/*
 *  InsertMenuItemTextWithCFString()
 *  
 *  Summary:
 *    Inserts a new menu item with text from a CFString.
 *  
 *  Discussion:
 *    The Menu Manager will either make its own copy or just increment
 *    the refcount of the CFString before returning from
 *    InsertMenuItemWithCFString, depending on whether the string is
 *    mutable or immutable. If the string is mutable, modifying the
 *    string after calling InsertMenuItemWithCFString will have no
 *    effect on the menu item's actual text. The caller may release the
 *    string after calling InsertMenuItemWithCFString.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to insert the new item.
 *    
 *    inString:
 *      The text of the new item.
 *    
 *    inAfterItem:
 *      The item after which to insert the new item.
 *    
 *    inAttributes:
 *      The attributes of the new item.
 *    
 *    inCommandID:
 *      The command ID of the new item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
InsertMenuItemTextWithCFString(
  MenuRef              inMenu,
  CFStringRef          inString,
  MenuItemIndex        inAfterItem,
  MenuItemAttributes   inAttributes,
  MenuCommand          inCommandID);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Events                                                                       */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  MenuKey()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
MenuKey(CharParameter ch);


/*
 *  MenuSelect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
MenuSelect(Point startPt);


/*
 *  PopUpMenuSelect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
PopUpMenuSelect(
  MenuRef   menu,
  short     top,
  short     left,
  short     popUpItem);


/*
 *  MenuChoice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
MenuChoice(void);


/*
 *  MenuEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern UInt32 
MenuEvent(const EventRecord * inEvent);


/*
 *  IsMenuKeyEvent()
 *  
 *  Summary:
 *    Determines if an event corresponds to a menu command key.
 *  
 *  Discussion:
 *    By default, IsMenuKeyEvent searches the menus in the current menu
 *    bar and hilites the menu title of the menu containing the
 *    selected item.
 *  
 *  Parameters:
 *    
 *    inStartMenu:
 *      IsMenuKeyEvent searches for matching menu items in this menu
 *      and all of its submenus. May be NULL to search the current menu
 *      bar contents.
 *    
 *    inEvent:
 *      The event to match against. Non-keyboard events are ignored.
 *    
 *    inOptions:
 *      Options controlling how to search. Pass kNilOptions for the
 *      default behavior.
 *    
 *    outMenu:
 *      On exit, the menu containing the matching item. May be NULL.
 *    
 *    outMenuItem:
 *      On exit, the menu item that matched. May be NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsMenuKeyEvent(
  MenuRef            inStartMenu,
  EventRef           inEvent,
  MenuEventOptions   inOptions,
  MenuRef *          outMenu,           /* can be NULL */
  MenuItemIndex *    outMenuItem);      /* can be NULL */


/*
 *  InvalidateMenuEnabling()
 *  
 *  Summary:
 *    Causes the menu enable state to be recalculated at the next
 *    convenient opportunity.
 *  
 *  Discussion:
 *    It is common for state changes in an application (for example,
 *    selection of text) to cause a change in the enabling of items in
 *    the application's menu (for example, the Copy menu item might
 *    become enabled). In a Carbon-event-savvy application, menu items
 *    are enabled or disabled in response to an
 *    kEventCommandUpdateStatus event; however, this event is normally
 *    only sent before a command key press or a click in the menubar.
 *    You can request an explicit recalculation of a menu's enable
 *    state with the InvalidateMenuEnabling API. The Carbon Event
 *    Manager will automatically invalidate the enable state of all
 *    top-level menus when a user event is dispatched, the user focus
 *    changes, or the active window changes, so in many cases you will
 *    not need to explicitly invalidate the menu enabling state.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      A menu to re-enable, or NULL if all menus in the root menu
 *      should be re-enabled.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
InvalidateMenuEnabling(MenuRef inMenu);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Bar                                                                          */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetMBarHeight()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetMBarHeight(void);


/*
 *  [Mac]DrawMenuBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacDrawMenuBar DrawMenuBar
#endif
extern void 
MacDrawMenuBar(void);


/*
 *  InvalMenuBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvalMenuBar(void);


/*
 *  IsMenuBarInvalid()
 *  
 *  Summary:
 *    Determines if the menubar is invalid and should be redrawn.
 *  
 *  Parameters:
 *    
 *    rootMenu:
 *      The root menu for the menubar to be examined. Pass NULL to
 *      check the state of the current menubar.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsMenuBarInvalid(MenuRef rootMenu);


/*
 *  HiliteMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HiliteMenu(MenuID menuID);


/*
 *  GetNewMBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern MenuBarHandle 
GetNewMBar(short menuBarID);


/*
 *  GetMenuBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern MenuBarHandle 
GetMenuBar(void);


/*
 *  SetMenuBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetMenuBar(MenuBarHandle mbar);


/*
 *  DuplicateMenuBar()
 *  
 *  Summary:
 *    Duplicates a menubar handle.
 *  
 *  Discussion:
 *    This API should be used in Carbon applications when duplicating a
 *    handle returned from GetMenuBar or GetNewMBar. You should not use
 *    Memory Manager APIs (HandToHand, NewHandle, etc) to duplicate
 *    such a handle. This is necessary in Carbon so that the refcounts
 *    of the menus in the menubar handle can be incremented when the
 *    handle is duplicated.
 *  
 *  Parameters:
 *    
 *    inMbar:
 *      The menubar handle to duplicate.
 *    
 *    outMbar:
 *      On exit, contains the new menubar handle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DuplicateMenuBar(
  MenuBarHandle    inMbar,
  MenuBarHandle *  outMbar);


/*
 *  DisposeMenuBar()
 *  
 *  Summary:
 *    Releases a menubar handle.
 *  
 *  Discussion:
 *    This API should be used in Carbon applications when releasing a
 *    handle returned from GetMenuBar or GetNewMBar. You should not use
 *    DisposeHandle to release such a handle. This is necessary in
 *    Carbon so that the refcounts of the menus in the menubar handle
 *    can be decremented when the handle is released.
 *  
 *  Parameters:
 *    
 *    inMbar:
 *      The menubar handle to release.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DisposeMenuBar(MenuBarHandle inMbar);


/*
 *  GetMenuHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern MenuRef 
GetMenuHandle(MenuID menuID);


#define GetMenuRef GetMenuHandle
/*
 *  [Mac]InsertMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacInsertMenu InsertMenu
#endif
extern void 
MacInsertMenu(
  MenuRef   theMenu,
  MenuID    beforeID);


/*
 *  [Mac]DeleteMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacDeleteMenu DeleteMenu
#endif
extern void 
MacDeleteMenu(MenuID menuID);


/*
 *  ClearMenuBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ClearMenuBar(void);


/*
 *  SetMenuFlash()
 *  
 *  Summary:
 *    Renamed to SetMenuFlashCount in Carbon
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
 *  SetMenuFlashCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.3 and later or as macro/inline
 */
extern void 
SetMenuFlashCount(short count);



/*
 *  FlashMenuBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FlashMenuBar(MenuID menuID);


/* These are obsolete because Carbon does not support desk accessories.*/
/*
 *  SystemEdit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SystemMenu()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  IsMenuBarVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern Boolean 
IsMenuBarVisible(void);


/*
 *  ShowMenuBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern void 
ShowMenuBar(void);


/*
 *  HideMenuBar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern void 
HideMenuBar(void);


/*
 *  AcquireRootMenu()
 *  
 *  Summary:
 *    Get the menu whose contents are displayed in the menubar.
 *  
 *  Discussion:
 *    The refcount of the root menu is incremented by this API. The
 *    caller should release a refcount with ReleaseMenu when itÕs done
 *    with the menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern MenuRef 
AcquireRootMenu(void);


/*
 *  SetRootMenu()
 *  
 *  Summary:
 *    Sets the menu whose contents are displayed in the menubar.
 *  
 *  Discussion:
 *    The refcount of the root menu is incremented by this API. The
 *    caller may release the menu after calling SetRootMenu.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The new root menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetRootMenu(MenuRef inMenu);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Item Accessors                                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  CheckItem()
 *  
 *  Summary:
 *    Renamed to CheckMenuItem in Carbon
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
 *  [Mac]CheckMenuItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.3 and later or as macro/inline
 */
#if TARGET_OS_MAC
    #define MacCheckMenuItem CheckMenuItem
#endif
extern void 
MacCheckMenuItem(
  MenuRef   theMenu,
  short     item,
  Boolean   checked);



/*
 *  SetMenuItemText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetMenuItemText(
  MenuRef            theMenu,
  short              item,
  ConstStr255Param   itemString);


/*
 *  GetMenuItemText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetMenuItemText(
  MenuRef   theMenu,
  short     item,
  Str255    itemString);


/*
 *  SetItemMark()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetItemMark(
  MenuRef         theMenu,
  short           item,
  CharParameter   markChar);


/*
 *  GetItemMark()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetItemMark(
  MenuRef          theMenu,
  short            item,
  CharParameter *  markChar);


/*
 *  SetItemCmd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetItemCmd(
  MenuRef         theMenu,
  short           item,
  CharParameter   cmdChar);


/*
 *  GetItemCmd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetItemCmd(
  MenuRef          theMenu,
  short            item,
  CharParameter *  cmdChar);


/*
 *  SetItemIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetItemIcon(
  MenuRef   theMenu,
  short     item,
  short     iconIndex);


/* icon is returned in high byte of 16-bit iconIndex */
/*
 *  GetItemIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetItemIcon(
  MenuRef   theMenu,
  short     item,
  short *   iconIndex);


/*
 *  SetItemStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetItemStyle(
  MenuRef          theMenu,
  short            item,
  StyleParameter   chStyle);


/*
 *  GetItemStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetItemStyle(
  MenuRef   theMenu,
  short     item,
  Style *   chStyle);


/* These APIs are not supported in Carbon. Please use EnableMenuItem and */
/* DisableMenuItem (available back through Mac OS 8.5) instead.          */
/*
 *  DisableItem()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  EnableItem()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SetMenuItemCommandID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetMenuItemCommandID(
  MenuRef       inMenu,
  SInt16        inItem,
  MenuCommand   inCommandID);


/*
 *  GetMenuItemCommandID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetMenuItemCommandID(
  MenuRef        inMenu,
  SInt16         inItem,
  MenuCommand *  outCommandID);


/*
 *  SetMenuItemModifiers()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetMenuItemModifiers(
  MenuRef   inMenu,
  SInt16    inItem,
  UInt8     inModifiers);


/*
 *  GetMenuItemModifiers()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetMenuItemModifiers(
  MenuRef   inMenu,
  SInt16    inItem,
  UInt8 *   outModifiers);


/*
 *  SetMenuItemIconHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetMenuItemIconHandle(
  MenuRef   inMenu,
  SInt16    inItem,
  UInt8     inIconType,
  Handle    inIconHandle);


/*
 *  GetMenuItemIconHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetMenuItemIconHandle(
  MenuRef   inMenu,
  SInt16    inItem,
  UInt8 *   outIconType,
  Handle *  outIconHandle);


/*
 *  SetMenuItemTextEncoding()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetMenuItemTextEncoding(
  MenuRef        inMenu,
  SInt16         inItem,
  TextEncoding   inScriptID);


/*
 *  GetMenuItemTextEncoding()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetMenuItemTextEncoding(
  MenuRef         inMenu,
  SInt16          inItem,
  TextEncoding *  outScriptID);


/*
 *  SetMenuItemHierarchicalID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetMenuItemHierarchicalID(
  MenuRef   inMenu,
  SInt16    inItem,
  MenuID    inHierID);


/*
 *  GetMenuItemHierarchicalID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetMenuItemHierarchicalID(
  MenuRef   inMenu,
  SInt16    inItem,
  MenuID *  outHierID);


/*
 *  SetMenuItemFontID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetMenuItemFontID(
  MenuRef   inMenu,
  SInt16    inItem,
  SInt16    inFontID);


/*
 *  GetMenuItemFontID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetMenuItemFontID(
  MenuRef   inMenu,
  SInt16    inItem,
  SInt16 *  outFontID);


/*
 *  SetMenuItemRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetMenuItemRefCon(
  MenuRef   inMenu,
  SInt16    inItem,
  UInt32    inRefCon);


/*
 *  GetMenuItemRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetMenuItemRefCon(
  MenuRef   inMenu,
  SInt16    inItem,
  UInt32 *  outRefCon);


/* Please use the menu item property APIs in Carbon.*/
/*
 *  SetMenuItemRefCon2()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */


/*
 *  GetMenuItemRefCon2()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */


/*
 *  SetMenuItemKeyGlyph()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetMenuItemKeyGlyph(
  MenuRef   inMenu,
  SInt16    inItem,
  SInt16    inGlyph);


/*
 *  GetMenuItemKeyGlyph()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetMenuItemKeyGlyph(
  MenuRef   inMenu,
  SInt16    inItem,
  SInt16 *  outGlyph);


/* Routines available in Mac OS 8.5 and later (supporting enabling/disabling of > 31 items)*/

/*
 *  [Mac]EnableMenuItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
#if TARGET_OS_MAC
    #define MacEnableMenuItem EnableMenuItem
#endif
extern void 
MacEnableMenuItem(
  MenuRef         theMenu,
  MenuItemIndex   item);


/*
 *  DisableMenuItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern void 
DisableMenuItem(
  MenuRef         theMenu,
  MenuItemIndex   item);


/*
 *  IsMenuItemEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern Boolean 
IsMenuItemEnabled(
  MenuRef         menu,
  MenuItemIndex   item);


/*
 *  EnableMenuItemIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern void 
EnableMenuItemIcon(
  MenuRef         theMenu,
  MenuItemIndex   item);


/*
 *  DisableMenuItemIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern void 
DisableMenuItemIcon(
  MenuRef         theMenu,
  MenuItemIndex   item);


/*
 *  IsMenuItemIconEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern Boolean 
IsMenuItemIconEnabled(
  MenuRef         menu,
  MenuItemIndex   item);


/*
 *  SetMenuItemHierarchicalMenu()
 *  
 *  Summary:
 *    Attaches a submenu to a menu item.
 *  
 *  Discussion:
 *    Using SetMenuItemHierarchicalMenu, it is possible to directly
 *    specify the submenu for a menu item without specifying its menu
 *    ID. It is not necessary to insert the submenu into the
 *    hierarchical portion of the menubar, and it is not necessary for
 *    the submenu to have a unique menu ID; it is recommended that you
 *    use 0 as the menu ID for the submenu, and identify selections
 *    from the menu by command ID. The Menu Manager will increment the
 *    refcount of the submenu that you specify, and the submenu's
 *    refcount will be decremented automatically when the parent menu
 *    item is deleted or the parent menu is disposed.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The parent menu.
 *    
 *    inItem:
 *      The parent item.
 *    
 *    inHierMenu:
 *      The submenu. You may pass NULL to remove any existing submenu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuItemHierarchicalMenu(
  MenuRef         inMenu,
  MenuItemIndex   inItem,
  MenuRef         inHierMenu);      /* can be NULL */


/*
 *  GetMenuItemHierarchicalMenu()
 *  
 *  Summary:
 *    Returns the submenu attached to a menu item.
 *  
 *  Discussion:
 *    GetMenuItemHierarchicalMenu will return the submenu attached to a
 *    menu item regardless of how the submenu was specified. If the
 *    submenu was specified by menu ID (using SetItemCmd or
 *    SetMenuItemHierarchicalID), GetMenuItemHierarchicalMenu will
 *    return the currently installed menu with that ID, if any. The
 *    only case where GetMenuItemHierarchicalMenu will fail to return
 *    the item's submenu is when the submenu is specified by menu ID,
 *    but the submenu is not currently inserted in the menu bar.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The parent menu.
 *    
 *    inItem:
 *      The parent item.
 *    
 *    outHierMenu:
 *      On exit, the item's submenu, or NULL if it does not have one.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuItemHierarchicalMenu(
  MenuRef         inMenu,
  MenuItemIndex   inItem,
  MenuRef *       outHierMenu);


/*
 *  CopyMenuItemTextAsCFString()
 *  
 *  Summary:
 *    Returns a CFString containing the text of a menu item.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu containing the item.
 *    
 *    inItem:
 *      The item whose text to return.
 *    
 *    outString:
 *      On exit, a CFString containing the item's text. This string
 *      must be released by the caller.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyMenuItemTextAsCFString(
  MenuRef         inMenu,
  MenuItemIndex   inItem,
  CFStringRef *   outString);


/*
 *  SetMenuItemTextWithCFString()
 *  
 *  Summary:
 *    Sets the text of a menu item to the text contained in a CFString.
 *  
 *  Discussion:
 *    The Menu Manager will either make its own copy or just increment
 *    the refcount of the CFString before returning from
 *    SetMenuItemTextWithCFString, depending on whether the string is
 *    mutable or immutable. If the string is mutable, modifying the
 *    string after calling SetMenuItemTextWithCFString will have no
 *    effect on the menu item's actual text. The caller may release the
 *    string after calling SetMenuItemTextWithCFString.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu containing the item.
 *    
 *    inItem:
 *      The item whose text to return.
 *    
 *    inString:
 *      The string containing the new menu item text.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuItemTextWithCFString(
  MenuRef         inMenu,
  MenuItemIndex   inItem,
  CFStringRef     inString);


/*
 *  GetMenuItemIndent()
 *  
 *  Summary:
 *    Gets the indent level of a menu item.
 *  
 *  Discussion:
 *    The indent level of an item is an amount of extra space added to
 *    the left of the item's icon or checkmark. The level is simply a
 *    number, starting at zero, which the Menu Manager multiplies by a
 *    constant to get the indent in pixels. The default indent level is
 *    zero.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu containing the item.
 *    
 *    inItem:
 *      The item whose indent to retrieve.
 *    
 *    outIndent:
 *      On exit, the indent level of the item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuItemIndent(
  MenuRef         inMenu,
  MenuItemIndex   inItem,
  UInt32 *        outIndent);


/*
 *  SetMenuItemIndent()
 *  
 *  Summary:
 *    Sets the indent level of a menu item.
 *  
 *  Discussion:
 *    The indent level of an item is an amount of extra space added to
 *    the left of the item's icon or checkmark. The level is simply a
 *    number, starting at zero, which the Menu Manager multiplies by a
 *    constant to get the indent in pixels. The default indent level is
 *    zero.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu containing the item.
 *    
 *    inItem:
 *      The item whose indent to set.
 *    
 *    inIndent:
 *      The new indent level of the item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuItemIndent(
  MenuRef         inMenu,
  MenuItemIndex   inItem,
  UInt32          inIndent);


/*
 *  GetMenuItemCommandKey()
 *  
 *  Summary:
 *    Gets the keyboard equivalent of a menu item.
 *  
 *  Discussion:
 *    A menu item's keyboard equivalent may be either a character code
 *    or a virtual keycode. An item's character code and virtual
 *    keycode are stored separately and may contain different values,
 *    but only one is used by the Menu Manager at any given time. When
 *    requesting a menu item's virtual keycode equivalent, you should
 *    first check that the item is using a virtual keycode by testing
 *    the kMenuItemAttrUseVirtualKey attribute for that item. If this
 *    attribute is not set, the item's virtual keycode is ignored by
 *    the Menu Manager. Note that zero is a valid virtual keycode, so
 *    you cannot test the returned keycode against zero to determine if
 *    the item is using a virtual keycode equivalent. You must test the
 *    kMenuItemAttrUseVirtualKey attribute.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu containing the item.
 *    
 *    inItem:
 *      The item whose keyboard equivalent to retrieve.
 *    
 *    inGetVirtualKey:
 *      Indicates whether to retrieve the item's character code or
 *      virtual keycode equivalent.
 *    
 *    outKey:
 *      On exit, the keyboard equivalent of the item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuItemCommandKey(
  MenuRef         inMenu,
  MenuItemIndex   inItem,
  Boolean         inGetVirtualKey,
  UInt16 *        outKey);


/*
 *  SetMenuItemCommandKey()
 *  
 *  Summary:
 *    Sets the keyboard equivalent of a menu item.
 *  
 *  Discussion:
 *    A menu item's keyboard equivalent may be either a character code
 *    or a virtual keycode. The character code is always used to draw
 *    the item's keyboard equivalent in the menu, but either may be
 *    used for keyboard equivalent matching by MenuEvent and
 *    IsMenuKeyEvent, depending on whether the
 *    kMenuItemAttrUseVirtualKey item attribute is set. If
 *    SetMenuItemCommandKey is used to set the virtual keycode
 *    equivalent for a menu item, it also automatically sets the
 *    kMenuItemAttrUseVirtualKey item attribute. To make the menu item
 *    stop using the virtual keycode equivalent and use the character
 *    code equivalent instead, use ChangeMenuItemAttributes to clear
 *    the kMenuItemAttrUseVirtualKey item attribute.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu containing the item.
 *    
 *    inItem:
 *      The item whose keyboard equivalent to set.
 *    
 *    inSetVirtualKey:
 *      Indicates whether to set the item's character code or virtual
 *      keycode equivalent.
 *    
 *    inKey:
 *      The item's new character code or virtual keycode equivalent.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuItemCommandKey(
  MenuRef         inMenu,
  MenuItemIndex   inItem,
  Boolean         inSetVirtualKey,
  UInt16          inKey);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu Item Color Tables                                                            */
/*                                                                                      */
/*  Menu color manipulation is considered deprecated with the advent of the Appearance  */
/*  Manager.  Avoid using these routines if possible                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  DeleteMCEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DeleteMCEntries(
  MenuID   menuID,
  short    menuItem);


/*
 *  GetMCInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern MCTableHandle 
GetMCInfo(void);


/*
 *  SetMCInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetMCInfo(MCTableHandle menuCTbl);


/*
 *  DisposeMCInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeMCInfo(MCTableHandle menuCTbl);


/*
 *  GetMCEntry()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern MCEntryPtr 
GetMCEntry(
  MenuID   menuID,
  short    menuItem);


/*
 *  SetMCEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetMCEntries(
  short        numEntries,
  MCTablePtr   menuCEntries);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Properties  (Mac OS 8.5 and later)                                                 */
/*                                                                                      */
/* With the following property APIs, you can attach any piece of data you'd like to a   */
/* menu or menu item. Passing zero for the item number parameter indicates you'd like   */
/* to attach the data to the menu itself, and not to any specific menu item.            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kMenuPropertyPersistent       = 0x00000001 /* whether this property gets saved when flattening the menu*/
};

/*
 *  GetMenuItemProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
GetMenuItemProperty(
  MenuRef         menu,
  MenuItemIndex   item,
  OSType          propertyCreator,
  OSType          propertyTag,
  UInt32          bufferSize,
  UInt32 *        actualSize,
  void *          propertyBuffer);


/*
 *  GetMenuItemPropertySize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
GetMenuItemPropertySize(
  MenuRef         menu,
  MenuItemIndex   item,
  OSType          propertyCreator,
  OSType          propertyTag,
  UInt32 *        size);


/*
 *  SetMenuItemProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
SetMenuItemProperty(
  MenuRef         menu,
  MenuItemIndex   item,
  OSType          propertyCreator,
  OSType          propertyTag,
  UInt32          propertySize,
  const void *    propertyData);


/*
 *  RemoveMenuItemProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in MenusLib 8.5 and later
 */
extern OSStatus 
RemoveMenuItemProperty(
  MenuRef         menu,
  MenuItemIndex   item,
  OSType          propertyCreator,
  OSType          propertyTag);


/*
 *  GetMenuItemPropertyAttributes()
 *  
 *  Summary:
 *    Gets the attributes of a menu item property.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu.
 *    
 *    item:
 *      The menu item.
 *    
 *    propertyCreator:
 *      The creator code of the property.
 *    
 *    propertyTag:
 *      The property tag.
 *    
 *    attributes:
 *      On exit, contains the attributes of the property.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuItemPropertyAttributes(
  MenuRef         menu,
  MenuItemIndex   item,
  OSType          propertyCreator,
  OSType          propertyTag,
  UInt32 *        attributes);


/*
 *  ChangeMenuItemPropertyAttributes()
 *  
 *  Summary:
 *    Changes the attributes of a menu item property.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu.
 *    
 *    item:
 *      The menu item.
 *    
 *    propertyCreator:
 *      The creator code of the property.
 *    
 *    propertyTag:
 *      The property tag.
 *    
 *    attributesToSet:
 *      The attributes to add to the menu item property.
 *    
 *    attributesToClear:
 *      The attributes to remove from the menu item property.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ChangeMenuItemPropertyAttributes(
  MenuRef         menu,
  MenuItemIndex   item,
  OSType          propertyCreator,
  OSType          propertyTag,
  UInt32          attributesToSet,
  UInt32          attributesToClear);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Attributes (Carbon and later)                                                     */
/*                                                                                      */
/*  Each menu and menu item has attribute flags.                                        */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetMenuAttributes()
 *  
 *  Summary:
 *    Gets the attributes of a menu.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu.
 *    
 *    outAttributes:
 *      On exit, contains the attributes of the menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuAttributes(
  MenuRef           menu,
  MenuAttributes *  outAttributes);


/*
 *  ChangeMenuAttributes()
 *  
 *  Summary:
 *    Changes the attributes of a menu.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu.
 *    
 *    setTheseAttributes:
 *      The attributes to add to the menu.
 *    
 *    clearTheseAttributes:
 *      The attributes to remove from the menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ChangeMenuAttributes(
  MenuRef          menu,
  MenuAttributes   setTheseAttributes,
  MenuAttributes   clearTheseAttributes);


/*
 *  GetMenuItemAttributes()
 *  
 *  Summary:
 *    Gets the attributes of a menu item.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu.
 *    
 *    item:
 *      The menu item.
 *    
 *    outAttributes:
 *      On exit, contains the attributes of the menu item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuItemAttributes(
  MenuRef               menu,
  MenuItemIndex         item,
  MenuItemAttributes *  outAttributes);


/*
 *  ChangeMenuItemAttributes()
 *  
 *  Summary:
 *    Changes the attributes of a menu item.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu.
 *    
 *    item:
 *      The menu item.
 *    
 *    setTheseAttributes:
 *      The attributes to add to the menu item.
 *    
 *    clearTheseAttributes:
 *      The attributes to remove from the menu item.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ChangeMenuItemAttributes(
  MenuRef              menu,
  MenuItemIndex        item,
  MenuItemAttributes   setTheseAttributes,
  MenuItemAttributes   clearTheseAttributes);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Mass menu item enabling and disabling (Carbon and later)                          */
/*                                                                                      */
/*  Useful when rewriting code that modifies the enableFlags field directly.            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  DisableAllMenuItems()
 *  
 *  Summary:
 *    Disables all items in a menu.
 *  
 *  Discussion:
 *    This API is equivalent to pre-Carbon code that masked the
 *    enableFlags field of the MenuInfo with 0x01. It disables all
 *    items (including items past item 31) but does not affect the
 *    state of the menu title.
 *  
 *  Parameters:
 *    
 *    theMenu:
 *      The menu whose items to disable.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
DisableAllMenuItems(MenuRef theMenu);


/*
 *  EnableAllMenuItems()
 *  
 *  Summary:
 *    Enables all items in a menu.
 *  
 *  Discussion:
 *    This API is equivalent to pre-Carbon code that or'd the
 *    enableFlags field of the MenuInfo with 0xFFFFFFFE. It enables all
 *    items (including items past item 31) but does not affect the
 *    state of the menu title.
 *  
 *  Parameters:
 *    
 *    theMenu:
 *      The menu whose items to enable.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
EnableAllMenuItems(MenuRef theMenu);


/*
 *  MenuHasEnabledItems()
 *  
 *  Summary:
 *    Determines if any items in a menu are enabled.
 *  
 *  Discussion:
 *    This API is equivalent to pre-Carbon code that compared the
 *    enableFlags field of the MenuInfo with 0. It checks the enable
 *    state of all items to see if any are enabled, but ignores the
 *    state of the menu title. It will return true even if the menu
 *    title is disabled.
 *  
 *  Parameters:
 *    
 *    theMenu:
 *      The menu whose items to examine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
MenuHasEnabledItems(MenuRef theMenu);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Menu tracking status (Carbon and later)                                           */
/*                                                                                      */
/*  Get info about the selected menu item during menu tracking. Replaces direct access  */
/*  to low-mem globals that previously held this info.                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetMenuTrackingData()
 *  
 *  Summary:
 *    Gets information about the menu currently selected by the user.
 *  
 *  Discussion:
 *    This API replaces direct access to the low-memory globals
 *    TopMenuItem, AtMenuBottom, MenuDisable, and mbSaveLoc. It is only
 *    valid to call this API while menu tracking is occurring. This API
 *    will most commonly be used by custom MDEFs.
 *  
 *  Parameters:
 *    
 *    theMenu:
 *      The menu about which to get tracking information. May be NULL
 *      to get information about the menu that the user is currently
 *      selecting. If the menu is not currently open, menuNotFoundErr
 *      is returned.
 *    
 *    outData:
 *      On exit, contains tracking data about the menu. On CarbonLib,
 *      the itemRect field is not supported and is always set to an
 *      empty rect.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuTrackingData(
  MenuRef             theMenu,
  MenuTrackingData *  outData);


/*
 *  GetMenuType()
 *  
 *  Summary:
 *    Gets the display type (pulldown, hierarchical, or popup) of a
 *    menu.
 *  
 *  Discussion:
 *    This API may only be called when the menu is displayed. If the
 *    menu is not currently open, an error is returned. The display
 *    type of a menu may vary from one menu tracking session to
 *    another; for example, the same menu might be displayed as a
 *    pulldown menu and as a popup menu.
 *  
 *  Parameters:
 *    
 *    theMenu:
 *      The menu whose type to get.
 *    
 *    outType:
 *      On exit, the type of the menu. The returned value will be one
 *      of the ThemeMenuType constants: kThemeMenuTypePullDown, PopUp,
 *      or Hierarchical. The kThemeMenuTypeInactive bit will never be
 *      set.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuType(
  MenuRef   theMenu,
  UInt16 *  outType);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ÊUniversal command ID access (Carbon and later)                                    */
/*                                                                                      */
/*  These APIs allow you to operate on menu items strictly by command ID, with no       */
/*  knowledge of a menu item's index.                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  CountMenuItemsWithCommandID()
 *  
 *  Summary:
 *    Counts the menu items with a specified command ID.
 *  
 *  Discussion:
 *    In CarbonLib 1.0.x and 1.1, this API will always return zero or
 *    one; it stops after finding the first menu item with the
 *    specified command ID. In CarbonLib 1.2 and Mac OS X 1.0, it will
 *    count all menu items with the specified command ID.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for items with the
 *      specified command ID. Pass NULL to hegin searching with the
 *      root menu. The search will descend into all submenus of this
 *      menu.
 *    
 *    inCommandID:
 *      The command ID for which to search.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ItemCount 
CountMenuItemsWithCommandID(
  MenuRef       inMenu,
  MenuCommand   inCommandID);


/*
 *  GetIndMenuItemWithCommandID()
 *  
 *  Summary:
 *    Finds a menu item with a specified command ID.
 *  
 *  Discussion:
 *    This API searches the specified menu and its submenus for the
 *    n'th menu item with the specified command ID. In CarbonLib 1.0.x
 *    and 1.1, only the first menu item will be returned. In CarbonLib
 *    1.2 and Mac OS X 1.0, this API will iterate over all menu items
 *    with the specified command ID.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for items with the
 *      specified command ID. Pass NULL to hegin searching with the
 *      root menu. The search will descend into all submenus of this
 *      menu.
 *    
 *    inCommandID:
 *      The command ID for which to search.
 *    
 *    inItemIndex:
 *      The 1-based index of the menu item to retrieve. In CarbonLib
 *      1.0.x and 1.1, this parameter must be 1. In CarbonLib 1.2 and
 *      Mac OS X 1.0, this parameter may vary from 1 to the number of
 *      menu items with the specified command ID.
 *    
 *    outMenu:
 *      On exit, the menu containing the menu item with the specified
 *      command ID.
 *    
 *    outIndex:
 *      On exit, the item index of the menu item with the specified
 *      command ID.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetIndMenuItemWithCommandID(
  MenuRef          inMenu,
  MenuCommand      inCommandID,
  UInt32           inItemIndex,
  MenuRef *        outMenu,           /* can be NULL */
  MenuItemIndex *  outIndex);         /* can be NULL */


/*
 *  EnableMenuCommand()
 *  
 *  Summary:
 *    Enables the menu item with a specified command ID.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item to be enabled. If more than one
 *      item has this command ID, only the first will be enabled.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
EnableMenuCommand(
  MenuRef       inMenu,
  MenuCommand   inCommandID);


/*
 *  DisableMenuCommand()
 *  
 *  Summary:
 *    Disables the menu item with a specified command ID.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item to be disabled. If more than
 *      one item has this command ID, only the first will be disabled.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
DisableMenuCommand(
  MenuRef       inMenu,
  MenuCommand   inCommandID);


/*
 *  IsMenuCommandEnabled()
 *  
 *  Summary:
 *    Determines if the menu item with a specified command ID is
 *    enabled.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item to examine. If more than one
 *      item has this command ID, only the first will be examined.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsMenuCommandEnabled(
  MenuRef       inMenu,
  MenuCommand   inCommandID);


/*
 *  SetMenuCommandMark()
 *  
 *  Summary:
 *    Locates the menu item with a specified command ID and sets its
 *    mark character.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item to be modified. If more than
 *      one item has this command ID, only the first will be modified.
 *    
 *    inMark:
 *      The new mark character. This is a Unicode character. On Mac OS
 *      8.x, the low byte of this character will be used as the mark
 *      character. On Mac OS X, the entire UniChar will be used and
 *      drawn.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuCommandMark(
  MenuRef       inMenu,
  MenuCommand   inCommandID,
  UniChar       inMark);


/*
 *  GetMenuCommandMark()
 *  
 *  Summary:
 *    Locates the menu item with a specified command ID and returns its
 *    mark character.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item to be examined. If more than
 *      one item has this command ID, only the first will be examined.
 *    
 *    outMark:
 *      On exit, the menu item's mark character.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuCommandMark(
  MenuRef       inMenu,
  MenuCommand   inCommandID,
  UniChar *     outMark);


/*
 *  GetMenuCommandProperty()
 *  
 *  Summary:
 *    Retrives property data for a menu item with a specified command
 *    ID.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item containing the property. If
 *      more than one item has this command ID, only the first will be
 *      used.
 *    
 *    inPropertyCreator:
 *      The property creator.
 *    
 *    inPropertyTag:
 *      The property tag.
 *    
 *    inBufferSize:
 *      The size of the output buffer, in bytes.
 *    
 *    outActualSize:
 *      On exit, contains the actual size of the property data. May be
 *      NULL if you do not need this information.
 *    
 *    inPropertyBuffer:
 *      The address of a buffer in which to place the property data.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuCommandProperty(
  MenuRef       inMenu,
  MenuCommand   inCommandID,
  OSType        inPropertyCreator,
  OSType        inPropertyTag,
  ByteCount     inBufferSize,
  ByteCount *   outActualSize,           /* can be NULL */
  void *        inPropertyBuffer);


/*
 *  GetMenuCommandPropertySize()
 *  
 *  Summary:
 *    Retrives the size of property data for a menu item with a
 *    specified command ID.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item containing the property. If
 *      more than one item has this command ID, only the first will be
 *      used.
 *    
 *    inPropertyCreator:
 *      The property creator.
 *    
 *    inPropertyTag:
 *      The property tag.
 *    
 *    outSize:
 *      On exit, contains the size of the property data.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuCommandPropertySize(
  MenuRef       inMenu,
  MenuCommand   inCommandID,
  OSType        inPropertyCreator,
  OSType        inPropertyTag,
  ByteCount *   outSize);


/*
 *  SetMenuCommandProperty()
 *  
 *  Summary:
 *    Sets property data for a menu item with a specified command ID.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item that will receive the property.
 *      If more than one item has this command ID, only the first will
 *      be modified.
 *    
 *    inPropertyCreator:
 *      The property creator.
 *    
 *    inPropertyTag:
 *      The property tag.
 *    
 *    inPropertySize:
 *      The size of the property data, in bytes.
 *    
 *    inPropertyData:
 *      The address of the property data.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuCommandProperty(
  MenuRef       inMenu,
  MenuCommand   inCommandID,
  OSType        inPropertyCreator,
  OSType        inPropertyTag,
  ByteCount     inPropertySize,
  const void *  inPropertyData);


/*
 *  RemoveMenuCommandProperty()
 *  
 *  Summary:
 *    Removes a property from a menu item with a specified command ID.
 *  
 *  Parameters:
 *    
 *    inMenu:
 *      The menu in which to begin searching for the item. Pass NULL to
 *      begin searching with the root menu. The search will descend
 *      into all submenus of this menu.
 *    
 *    inCommandID:
 *      The command ID of the menu item from which the property will be
 *      removed. If more than one item has this command ID, only the
 *      first will be modified.
 *    
 *    inPropertyCreator:
 *      The property creator.
 *    
 *    inPropertyTag:
 *      The property tag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RemoveMenuCommandProperty(
  MenuRef       inMenu,
  MenuCommand   inCommandID,
  OSType        inPropertyCreator,
  OSType        inPropertyTag);



/*
 *  CopyMenuItemData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyMenuItemData(
  MenuRef           menu,
  MenuItemID        item,
  Boolean           isCommandID,
  MenuItemDataPtr   outData);


/*
 *  SetMenuItemData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuItemData(
  MenuRef                  menu,
  MenuItemID               item,
  Boolean                  isCommandID,
  const MenuItemDataRec *  data);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Dynamic menu item support (CarbonLib 1.1 and Carbon for Mac OS X, and later)      */
/*                                                                                      */
/*  Dynamic menu item support allows a menu item to be redrawn while the menu is open   */
/*  and visible to the user. Carbon contains automatic support for dynamic items based  */
/*  on keyboard modifier state. If you need to implement your own variable item state   */
/*  based on other system state, you can use these APIs to implement it.                */
/*                                                                                      */
/*  To use the built-in support for dynamic items, you should create a menu containing  */
/*  several contiguous items with the same command key but different text and modifier  */
/*  keys. For example, you might have:                                                  */
/*                                                                                      */
/*      Close       cmd-W                                                               */
/*      Close All   cmd-option-W                                                        */
/*                                                                                      */
/*  In your MENU resource, you would create the Close and Close All items and give      */
/*  them each the letter 'W' as the command key; using an associated xmnu resource,     */
/*  you would specify kMenuOptionModifier as the modifier for the Close All item.       */
/*                                                                                      */
/*  After loading your menu from the resource, you must set the kMenuItemAttrDynamic    */
/*  flag for each dynamic item. In this example, you would use:                         */
/*                                                                                      */
/*      ChangeMenuItemAttributes( menu, kCloseItem, kMenuItemAttrDynamic, 0 );          */
/*      ChangeMenuItemAttributes( menu, kCloseAllItem, kMenuItemAttrDynamic, 0 );       */
/*                                                                                      */
/*  The Menu Manager will now automatically display the correct item depending on       */
/*  whether the Option key is pressed. The result from MenuSelect will be the item      */
/*  number of the item that was visible when the menu closed.                           */
/*                                                                                      */
/*  If the Menu Manager's built-in support is not sufficient, you can also change the   */
/*  attributes of an item yourself and use the UpdateInvalidMenuItems API to cause      */
/*  the menu to redraw. Changes to a menu item (changing text, command key, style,      */
/*  etc.) that occur while the menu is open will cause the menu item to be invalidated, */
/*  but not redrawn. If you need to invalidate the item explicitly yourself, perhaps    */
/*  because you have a custom MDEF that depends on state not accessed using Menu        */
/*  Manager APIs, you can use the InvalidateMenuItems API. UpdateInvalidMenuItems will  */
/*  scan the menu for invalid items and redraw each, clearing its invalid flag          */
/*  afterwards.                                                                         */
/*                                                                                      */
/*  If you need to change menu contents based on modifier key state without using the   */
/*  built-in support in the Menu Manager, we recommend that you install a Carbon event  */
/*  handler on your menu for the [kEventClassKeyboard, kEventRawKeyModifiersChanged]    */
/*  event. Modifier key events are passed to the currently open menu before being sent  */
/*  to the user focus target.                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  IsMenuItemInvalid()
 *  
 *  Summary:
 *    Determines if a menu item is invalid and should be redrawn.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu whose item to examine.
 *    
 *    item:
 *      The item to examine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsMenuItemInvalid(
  MenuRef         menu,
  MenuItemIndex   item);


/*
 *  InvalidateMenuItems()
 *  
 *  Summary:
 *    Invalidates a group of menu items so that they will be redrawn
 *    when UpdateInvalidMenuItems is next called.
 *  
 *  Discussion:
 *    Menu items are automatically invalidated when their contents are
 *    changed using Menu Manager APIs while the menu is open. However,
 *    you might need to use this API if you have a custom MDEF that
 *    draws using state not contained in the menu.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu whose items to invalidate.
 *    
 *    firstItem:
 *      The first item to invalidate.
 *    
 *    numItems:
 *      The number of items to invalidate.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
InvalidateMenuItems(
  MenuRef         menu,
  MenuItemIndex   firstItem,
  ItemCount       numItems);


/*
 *  UpdateInvalidMenuItems()
 *  
 *  Summary:
 *    Redraws the invalid items of an open menu.
 *  
 *  Discussion:
 *    It is not necessary to use UpdateInvalidMenuItems if you are
 *    using Carbon's built-in support for dynamic items based on
 *    modifier key state. However, if you are modifying items
 *    dynamically using your own implementation, you should call
 *    UpdateInvalidMenuItems after completing your modifications for a
 *    single menu. It will redraw any items that have been marked as
 *    invalid, and clear the invalid flag for those items.
 *  
 *  Parameters:
 *    
 *    menu:
 *      The menu to update.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
UpdateInvalidMenuItems(MenuRef menu);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ÊStandard font menu (Carbon and later)                                             */
/*                                                                                      */
/*  These APIs allow you to create and use the standard font menu.                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kHierarchicalFontMenuOption   = 0x00000001
};

/*
 *  CreateStandardFontMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateStandardFontMenu(
  MenuRef         menu,
  MenuItemIndex   afterItem,
  MenuID          firstHierMenuID,
  OptionBits      options,
  ItemCount *     outHierMenuCount);


/*
 *  UpdateStandardFontMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
UpdateStandardFontMenu(
  MenuRef      menu,
  ItemCount *  outHierMenuCount);


/*
 *  GetFontFamilyFromMenuSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetFontFamilyFromMenuSelection(
  MenuRef         menu,
  MenuItemIndex   item,
  FMFontFamily *  outFontFamily,
  FMFontStyle *   outStyle);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Contextual Menu routines and constants                                            */
/*  available with Conxtextual Menu extension 1.0 and later                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Gestalt Selector for classic 68K apps only. */
/* CFM apps should weak link and check the symbols. */
enum {
  gestaltContextualMenuAttr     = 'cmnu',
  gestaltContextualMenuUnusedBit = 0,
  gestaltContextualMenuTrapAvailable = 1
};

/* Values indicating what kind of help the application supports */
enum {
  kCMHelpItemNoHelp             = 0,
  kCMHelpItemAppleGuide         = 1,
  kCMHelpItemOtherHelp          = 2
};

/* Values indicating what was chosen from the menu */
enum {
  kCMNothingSelected            = 0,
  kCMMenuItemSelected           = 1,
  kCMShowHelpSelected           = 3
};

/*
 *  InitContextualMenus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ContextualMenu 1.0 and later
 */
extern OSStatus 
InitContextualMenus(void);


/*
 *  IsShowContextualMenuClick()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ContextualMenu 1.0 and later
 */
extern Boolean 
IsShowContextualMenuClick(const EventRecord * inEvent);


/*
 *  IsShowContextualMenuEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsShowContextualMenuEvent(EventRef inEvent);


/*
 *  ContextualMenuSelect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ContextualMenu 1.0 and later
 */
extern OSStatus 
ContextualMenuSelect(
  MenuRef            inMenu,
  Point              inGlobalLocation,
  Boolean            inReserved,
  UInt32             inHelpType,
  ConstStr255Param   inHelpItemString,           /* can be NULL */
  const AEDesc *     inSelection,                /* can be NULL */
  UInt32 *           outUserSelectionType,
  SInt16 *           outMenuID,
  MenuItemIndex *    outMenuItem);


/*
 *  ProcessIsContextualMenuClient()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ContextualMenu 1.0 and later
 */
extern Boolean 
ProcessIsContextualMenuClient(ProcessSerialNumber * inPSN);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Contextual Menu Plugin Interface                                                    */
/*                                                                                      */
/*  For Mac OS X, we will support a new type of Contextual Menu Plugin: the CFPlugIn    */
/*  based plugin.  Each plugin must be in a CFPlugIn in the Contextual Menu Items       */
/*  folder in one of these paths:                                                       */
/*      /System/Library/Contextual Menu Items/                                          */
/*      /Library/Contextual Menu Items/                                                 */
/*      ~/Library/Contextual Menu Items/                                                */
/*                                                                                      */
/*  It must export the following functions using the following interface or a C++       */
/*  interface inheriting from IUnknown and including similar functions.                 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

// The Contextual Menu Manager will only load CFPlugIns of type kContextualMenuTypeID
#define kContextualMenuTypeID    ( CFUUIDGetConstantUUIDWithBytes( NULL, \
  0x2F, 0x65, 0x22, 0xE9, 0x3E, 0x66, 0x11, 0xD5, \
  0x80, 0xA7, 0x00, 0x30, 0x65, 0xB3, 0x00, 0xBC ) )
 // 2F6522E9-3E66-11D5-80A7-003065B300BC

// Contextual Menu Plugins must implement this Contexual Menu Plugin Interface.
#define kContextualMenuInterfaceID ( CFUUIDGetConstantUUIDWithBytes( NULL, \
  0x32, 0x99, 0x7B, 0x62, 0x3E, 0x66, 0x11, 0xD5, \
  0xBE, 0xAB, 0x00, 0x30, 0x65, 0xB3, 0x00, 0xBC ) )
 // 32997B62-3E66-11D5-BEAB-003065B300BC

#define CM_IUNKNOWN_C_GUTS \
  void *_reserved; \
 SInt32 (*QueryInterface)(void *thisPointer, CFUUIDBytes iid, void ** ppv); \
   UInt32 (*AddRef)(void *thisPointer); \
 UInt32 (*Release)(void *thisPointer)

// The function table for the interface.
struct ContextualMenuInterfaceStruct
{
  CM_IUNKNOWN_C_GUTS;
    OSStatus ( *ExamineContext )(
          void*               thisInstance,
          const AEDesc*       inContext,
         AEDescList*         outCommandPairs );
 OSStatus ( *HandleSelection )(
         void*               thisInstance,
          AEDesc*             inContext,
         SInt32              inCommandID );
 void ( *PostMenuCleanup )(
         void*               thisInstance );
};
typedef struct ContextualMenuInterfaceStruct ContextualMenuInterfaceStruct;

/*
 *  CMPluginExamineContext()
 *  
 *  Availability:
 *    Implemented by client
 */
extern OSStatus 
CMPluginExamineContext(
  void *          thisInstance,
  const AEDesc *  inContext,
  AEDescList *    outCommandPairs);


/*
 *  CMPluginHandleSelection()
 *  
 *  Availability:
 *    Implemented by client
 */
extern OSStatus 
CMPluginHandleSelection(
  void *    thisInstance,
  AEDesc *  inContext,
  SInt32    inCommandID);


/*
 *  CMPluginPostMenuCleanup()
 *  
 *  Availability:
 *    Implemented by client
 */
extern void 
CMPluginPostMenuCleanup(void * thisInstance);



/* previously in LowMem.h.  This functions return the menu ID of the hilited menu */
/*
 *  LMGetTheMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
LMGetTheMenu(void);




/*
 *  newmenu()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  appendmenu()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  insertmenuitem()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  menuselect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  setmenuitemtext()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getmenuitemtext()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#if OLDROUTINENAMES
#define AddResMenu(theMenu, theType) AppendResMenu(theMenu, theType)
#define InsMenuItem(theMenu, itemString, afterItem) InsertMenuItem(theMenu, itemString, afterItem)
#define DelMenuItem( theMenu, item ) DeleteMenuItem( theMenu, item )
#if TARGET_OS_MAC
#define SetItem MacSetItem
#define GetItem MacGetItem
#endif
#define MacSetItem(theMenu, item, itemString) SetMenuItemText(theMenu, item, itemString)
#define MacGetItem(theMenu, item, itemString) GetMenuItemText(theMenu, item, itemString)
#define GetMHandle(menuID) GetMenuHandle(menuID)
#define DelMCEntries(menuID, menuItem) DeleteMCEntries(menuID, menuItem)
#define DispMCInfo(menuCTbl) DisposeMCInfo(menuCTbl)
#if CALL_NOT_IN_CARBON
#define addresmenu(menu, data) appendresmenu(menu, data)
#define getitem(menu, item, itemString) getmenuitemtext(menu, item, itemString)
#define setitem(menu, item, itemString) setmenuitemtext(menu, item, itemString)
#define insmenuitem(theMenu, itemString, afterItem) insertmenuitem(theMenu, itemString, afterItem)
#endif
#endif  /* OLDROUTINENAMES */

/* Getters */
/*
 *  GetMenuID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern MenuID 
GetMenuID(MenuRef menu);


/*
 *  GetMenuWidth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern SInt16 
GetMenuWidth(MenuRef menu);


/*
 *  GetMenuHeight()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern SInt16 
GetMenuHeight(MenuRef menu);


/*
 *  GetMenuTitle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern StringPtr 
GetMenuTitle(
  MenuRef   menu,
  Str255    title);


/*
 *  GetMenuDefinition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMenuDefinition(
  MenuRef          menu,
  MenuDefSpecPtr   outDefSpec);


/* Setters */
/*
 *  SetMenuID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetMenuID(
  MenuRef   menu,
  MenuID    menuID);


/*
 *  SetMenuWidth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetMenuWidth(
  MenuRef   menu,
  SInt16    width);


/*
 *  SetMenuHeight()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetMenuHeight(
  MenuRef   menu,
  SInt16    height);


/*
 *  SetMenuTitle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern OSStatus 
SetMenuTitle(
  MenuRef            menu,
  ConstStr255Param   title);


/*
 *  SetMenuDefinition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuDefinition(
  MenuRef              menu,
  const MenuDefSpec *  defSpec);





#if TARGET_OS_WIN32
#endif  /* TARGET_OS_WIN32 */


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

#endif /* __MENUS__ */

