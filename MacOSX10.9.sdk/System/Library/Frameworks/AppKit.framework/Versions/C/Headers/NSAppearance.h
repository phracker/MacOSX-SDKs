/*
        NSAppearance.h
        Application Kit
        Copyright (c) 2011-2013, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>

@class NSString, NSBundle;

NS_CLASS_AVAILABLE_MAC(10_9)
@interface NSAppearance : NSObject <NSCoding> {
@private
    NSString *_name;
    NSBundle *_bundle;
    void *_private;
    id _reserved;
#if !__LP64__
    id _extra[3];
#endif
}

// Setting and identifying the current appearance in the thread.
+ (NSAppearance *)currentAppearance;
+ (void)setCurrentAppearance:(NSAppearance *)appearance; // nil is valid and indicates the default appearance.

/* Finds and returns an NSAppearance based on the name. 
 For standard appearances such as NSAppearanceNameAqua, a built-in appearance is returned.
 For other names, the main bundle is searched.
 */
+ (NSAppearance *)appearanceNamed:(NSString *)name;

/* Creates an NSAppearance by searching the specified bundle for a file with the specified name (without path extension).
    If bundle is nil, the main bundle is assumed.
 */
- (id)initWithAppearanceNamed:(NSString *)name bundle:(NSBundle *)bundle;

@end

#pragma mark -
#pragma mark Standard Appearances

APPKIT_EXTERN NSString *const NSAppearanceNameAqua NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString *const NSAppearanceNameLightContent NS_AVAILABLE_MAC(10_9);

#pragma mark -

@protocol NSAppearanceCustomization <NSObject>
@required

@property(retain) NSAppearance *appearance NS_AVAILABLE_MAC(10_9);

/* This returns the appearance that would be used when drawing the receiver, taking inherited appearances into account.
 */
@property(readonly) NSAppearance *effectiveAppearance NS_AVAILABLE_MAC(10_9);

@end
