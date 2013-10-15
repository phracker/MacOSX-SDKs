/*
	NSDockTile.h
	Application Kit
	Copyright (c) 2006-2011, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

#define NSAppKitVersionNumberWithDockTilePlugInSupport 1001.0


@class NSView;

NS_CLASS_AVAILABLE(10_5, NA)
@interface NSDockTile : NSObject {
    @private;
    id _owner;
    void *_dockContextRef;
    NSView *_contentView;
    NSView *_frameView;
    NSView *_backstopView;
    NSString *_badgeLabel;
    struct {
        unsigned int showsAppBadge:1;
        unsigned int reserved:31;
    } _dFlags;
    NSSize _dockTileSize;
    id _miniViewController;
    id reserved[4];
}

/* get the size of the dock tile, in screen coordinates
*/
- (NSSize)size;

/* set the content view to view.  view should be height and width resizable.  In order to initiate drawing in view, you must call -[NSDockTile display]. 
*/
- (void)setContentView:(NSView *)view;
- (NSView *)contentView;

/* cause the dock tile to be redrawn.  The contentView and any subviews will be sent drawRect: messages.
*/
- (void)display;

/* setShowsApplicationBadge: sets whether or not the dock tile should be badged with the application icon.  Default is YES for NSWindow dock tiles, NO for the NSApplication dock tile.
*/
- (void)setShowsApplicationBadge:(BOOL)flag;
- (BOOL)showsApplicationBadge;

/* Badge the dock icon with a localized string.  The badge appearance is system defined.  This is often used to show an unread count in the application dock icon.
*/
- (void)setBadgeLabel:(NSString *)string;
- (NSString *)badgeLabel;

/* -owner will return NSApp for the application dock tile, or the NSWindow for a mini window dock tile.
*/
- (id)owner;

@end



@class NSMenu;

/* An application may customize its dock tile when not running via a plugin whose principal class implements the NSDockTilePlugIn protocol.  The name of the plugin is indicated by a NSDockTilePlugIn key in the application's Info.plist file.  The plugin is loaded in a system process at login time or when the application tile is added to the Dock.  When the plugin is loaded, the principal class' implementation of -setDockTile: is invoked.  If the principal class implements -dockMenu, -dockMenu is invoked whenever the user causes the application's dock menu to be shown.  When the dock tile is no longer valid (eg. the application has been removed from the dock, -setDockTile: is invoked with a nil NSDockTile.
*/
@protocol NSDockTilePlugIn <NSObject>
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

@required
- (void)setDockTile:(NSDockTile*)dockTile;

@optional
- (NSMenu*)dockMenu;
#endif
@end

