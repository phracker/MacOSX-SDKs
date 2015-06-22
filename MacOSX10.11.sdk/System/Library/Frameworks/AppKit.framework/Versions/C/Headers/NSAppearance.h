/*
        NSAppearance.h
        Application Kit
        Copyright (c) 2011-2015, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString, NSBundle;

NS_CLASS_AVAILABLE_MAC(10_9)
@interface NSAppearance : NSObject <NSCoding> {
@private
    NSString *_name;
    NSBundle *_bundle;
    void *_private;
    id _reserved;
    id _auxiliary;
#if !__LP64__
    id _extra[2];
#endif
}

@property (readonly, copy) NSString *name NS_AVAILABLE_MAC(10_9);

// Setting and identifying the current appearance in the thread.
+ (NSAppearance *)currentAppearance;
+ (void)setCurrentAppearance:(nullable NSAppearance *)appearance; // nil is valid and indicates the default appearance.

/* Finds and returns an NSAppearance based on the name. 
 For standard appearances such as NSAppearanceNameAqua, a built-in appearance is returned.
 For other names, the main bundle is searched.
 */
+ (nullable NSAppearance *)appearanceNamed:(NSString *)name;

/* Creates an NSAppearance by searching the specified bundle for a file with the specified name (without path extension).
    If bundle is nil, the main bundle is assumed.
 */
- (nullable instancetype)initWithAppearanceNamed:(NSString *)name bundle:(nullable NSBundle *)bundle;

/* Query allowsVibrancy to see if the given appearance actually needs vibrant drawing. You may want to draw differently if the current apperance is vibrant.
 */
@property (readonly) BOOL allowsVibrancy NS_AVAILABLE_MAC(10_10);

@end

#pragma mark -
#pragma mark Standard Appearances

APPKIT_EXTERN NSString * const NSAppearanceNameAqua NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString * const NSAppearanceNameLightContent NS_DEPRECATED_MAC(10_9, 10_10, "Light content should use the default Aqua apppearance.");

/* The following two Vibrant appearances should only be set on an NSVisualEffectView, or one of its container subviews.
 */
APPKIT_EXTERN NSString * const NSAppearanceNameVibrantDark NS_AVAILABLE_MAC(10_10);
APPKIT_EXTERN NSString * const NSAppearanceNameVibrantLight NS_AVAILABLE_MAC(10_10);

#pragma mark -

@protocol NSAppearanceCustomization <NSObject>
@required

@property (nullable, strong) NSAppearance *appearance NS_AVAILABLE_MAC(10_9);

/* This returns the appearance that would be used when drawing the receiver, taking inherited appearances into account.
 */
@property (readonly, strong) NSAppearance *effectiveAppearance NS_AVAILABLE_MAC(10_9);

@end

NS_ASSUME_NONNULL_END
