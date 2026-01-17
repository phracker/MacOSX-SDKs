/*
        NSMenuItem.h
        Application Kit
        Copyright (c) 1996-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSUserInterfaceValidation.h>

@class NSMenu;
@class NSImage, NSAttributedString;

// This protocol is deprecated.  Use the NSMenuItem class in your code.
@protocol NSMenuItem <NSObject, NSCopying, NSCoding, NSValidatedUserInterfaceItem>

+ (void)setUsesUserKeyEquivalents:(BOOL)flag;
+ (BOOL)usesUserKeyEquivalents;

+ (id <NSMenuItem>)separatorItem;

- (id)initWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode;

- (void)setMenu:(NSMenu *)menu;
- (NSMenu *)menu;
    // Never call the set method directly it is there only for subclassers.

- (BOOL)hasSubmenu;
- (void)setSubmenu:(NSMenu *)submenu;
- (NSMenu *)submenu;

- (void)setTitle:(NSString *)aString;
- (NSString *)title;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setAttributedTitle:(NSAttributedString*)string;
- (NSAttributedString*)attributedTitle;
#endif

- (BOOL)isSeparatorItem;

- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalentModifierMask:(unsigned int)mask;
- (unsigned int)keyEquivalentModifierMask;

- (NSString *)userKeyEquivalent;
- (unsigned int)userKeyEquivalentModifierMask;

- (void)setMnemonicLocation:(unsigned)location;
- (unsigned)mnemonicLocation;
- (NSString *)mnemonic;
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;

- (void)setImage:(NSImage *)menuImage;
- (NSImage *)image;

- (void)setState:(int)state;
- (int)state;
- (void)setOnStateImage:(NSImage *)image;  // checkmark by default
- (NSImage *)onStateImage;
- (void)setOffStateImage:(NSImage *)image;  // none by default
- (NSImage *)offStateImage;
- (void)setMixedStateImage:(NSImage *)image;  // horizontal line by default?
- (NSImage *)mixedStateImage;

- (void)setEnabled:(BOOL)flag;
- (BOOL)isEnabled;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void) setAlternate:(BOOL)isAlternate;
- (BOOL) isAlternate;

- (void) setIndentationLevel:(int)indentationLevel;
- (int) indentationLevel;
#endif

- (void)setTarget:(id)anObject;
- (id)target;
- (void)setAction:(SEL)aSelector;
- (SEL)action;

- (void)setTag:(int)anInt;
- (int)tag;

- (void)setRepresentedObject:(id)anObject;
- (id)representedObject;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void) setToolTip:(NSString*)toolTip;
- (NSString*) toolTip;
#endif

@end

@interface NSMenuItem : NSObject <NSMenuItem> {
    /*All instance variables are private*/
    @private
    NSMenu *_menu;
    NSString *_title;
    NSString *_keyEquivalent;
    unsigned _keyEquivalentModifierMask;
    unsigned _mnemonicLocation;
    int _state;
    NSImage *_image;
    NSImage *_onStateImage;
    NSImage *_offStateImage;
    NSImage *_mixedStateImage;
    id _target;
    SEL _action;
    int _tag;
    id _extraData;
    struct __miFlags {
        unsigned int disabled:1;
        unsigned int isSeparator:1;
        unsigned int hidden:1;
        unsigned int alternate:1;
        unsigned int indent:4;
	unsigned int changed:10;
	unsigned int RESERVED:14;
    } _miFlags;
}

+ (void)setUsesUserKeyEquivalents:(BOOL)flag;
+ (BOOL)usesUserKeyEquivalents;

+ (id <NSMenuItem>)separatorItem;

- (id)initWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode;

- (void)setMenu:(NSMenu *)menu;
- (NSMenu *)menu;
    // Never call the set method directly it is there only for subclassers.

- (BOOL)hasSubmenu;
- (void)setSubmenu:(NSMenu *)submenu;
- (NSMenu *)submenu;

- (void)setTitle:(NSString *)aString;
- (NSString *)title;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setAttributedTitle:(NSAttributedString*)string;
- (NSAttributedString*)attributedTitle;
#endif

- (BOOL)isSeparatorItem;

- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalentModifierMask:(unsigned int)mask;
- (unsigned int)keyEquivalentModifierMask;

- (NSString *)userKeyEquivalent;

- (void)setMnemonicLocation:(unsigned)location;
- (unsigned)mnemonicLocation;
- (NSString *)mnemonic;
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;

- (void)setImage:(NSImage *)menuImage;
- (NSImage *)image;

- (void)setState:(int)state;
- (int)state;
- (void)setOnStateImage:(NSImage *)image;  // checkmark by default
- (NSImage *)onStateImage;
- (void)setOffStateImage:(NSImage *)image;  // none by default
- (NSImage *)offStateImage;
- (void)setMixedStateImage:(NSImage *)image;  // horizontal line by default?
- (NSImage *)mixedStateImage;

- (void)setEnabled:(BOOL)flag;
- (BOOL)isEnabled;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void) setAlternate:(BOOL)isAlternate;
- (BOOL) isAlternate;

- (void) setIndentationLevel:(int)indentationLevel;
- (int) indentationLevel;
#endif

- (void)setTarget:(id)anObject;
- (id)target;
- (void)setAction:(SEL)aSelector;
- (SEL)action;

- (void)setTag:(int)anInt;
- (int)tag;

- (void)setRepresentedObject:(id)anObject;
- (id)representedObject;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void) setToolTip:(NSString*)toolTip;
- (NSString*) toolTip;
#endif

@end
