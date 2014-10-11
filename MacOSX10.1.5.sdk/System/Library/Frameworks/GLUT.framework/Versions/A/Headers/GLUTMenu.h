
/* Copyright (c) Dietmar Planitzer, 1998 */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */


#import <AppKit/NSMenu.h>
#import "macxglut_private.h"




/* *** types *** */

/* *** GLUTMenu class *** */


@interface GLUTMenu : NSObject
{
@private
	
	NSMenu *					_menu;
	GLUTMenuCallback		_callback;
}

- (id)initWithCallback: (GLUTMenuCallback)func;
- (void)dealloc;

		/* accessors */
- (int)numberOfItems;
- (NSMenu *)nativeMenu;

- (void)makeCurrent;
- (IBAction)menuItemAction: (id)sender;
- (BOOL)validateMenuItem:(id <NSMenuItem>)menuItem;

		/* menu items */
- (void)addMenuItemWithTitle: (NSString *)title tag: (int)value;
- (void)addSubMenuWithTitle: (NSString *)title menu: (GLUTMenu *)submenu;
- (void)setMenuItemAtIndex: (int)index toTitle: (NSString *)title tag: (int)value;
- (void)setMenuItemAtIndex: (int)index toTitle: (NSString *)title menu: (GLUTMenu *)submenu;
- (void)removeMenuItemAtIndex: (int)index;
- (void)attachToMouseButton: (int)button;
- (void)detachFromMouseButton: (int)button;

@end
