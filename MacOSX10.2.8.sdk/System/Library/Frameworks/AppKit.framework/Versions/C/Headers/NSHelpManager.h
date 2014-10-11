/*
	NSHelpManager.h
	Application Kit
	Copyright (c) 1995-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSMapTable.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSBundle.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSApplication.h>

@class NSAttributedString, NSWindow;

@interface NSHelpManager : NSObject
{
    /*All instance variables are private*/
    NSMapTable		*_helpMapTable;
    NSMapTable		*_keyMapTable;
    NSMapTable		*_bundleMapTable;
    NSWindow		*_helpWindow;
    NSWindow		*_shadowWindow;
    NSWindow		*_evtWindow;
    NSBundle		*_helpBundle;
}

+ (NSHelpManager *)sharedHelpManager;
+ (void)setContextHelpModeActive:(BOOL)active;
+ (BOOL)isContextHelpModeActive;

- (void)setContextHelp:(NSAttributedString *)attrString forObject:(id)object;
- (void)removeContextHelpForObject:(id)object;
- (NSAttributedString *)contextHelpForObject:(id)object;

- (BOOL)showContextHelpForObject:(id)object locationHint:(NSPoint)pt;

@end

//
// Notifications for the activation/deactivation of the context help mode
//

APPKIT_EXTERN NSString *NSContextHelpModeDidActivateNotification;
APPKIT_EXTERN NSString *NSContextHelpModeDidDeactivateNotification;

//
//  Conveniences for accessing Help.plist
//

@interface NSBundle(NSBundleHelpExtension)
- (NSAttributedString *)contextHelpForKey:(NSString *)key;	/* return nil if not found */
@end

//
//  Convenience methods on NSApplication
//

@interface NSApplication(NSApplicationHelpExtension)
- (void)activateContextHelpMode:(id)sender;
  // Target method cover for [NSHelpManager setContextHelpModeActive:YES];
- (void)showHelp:(id)sender;
@end
