/*
        NSAppearance.h
        Application Kit
        Copyright (c) 2011-2017, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString, NSBundle;

typedef NSString * NSAppearanceName NS_EXTENSIBLE_STRING_ENUM;

NS_CLASS_AVAILABLE_MAC(10_9)
@interface NSAppearance : NSObject <NSCoding> {
@private
    NSAppearanceName _name;
    NSBundle *_bundle;
    void *_private;
    id _reserved;
    id _auxiliary;
#if !__LP64__
    id _extra[2];
#endif
}

@property (readonly, copy) NSAppearanceName name NS_AVAILABLE_MAC(10_9);

// Setting and identifying the current appearance in the thread.
@property (class, null_resettable, strong) NSAppearance *currentAppearance; // setting to nil indicates the default appearance

/* Finds and returns an NSAppearance based on the name. 
 For standard appearances such as NSAppearanceNameAqua, a built-in appearance is returned.
 For other names, the main bundle is searched.
 */
+ (nullable NSAppearance *)appearanceNamed:(NSAppearanceName)name;

/* Creates an NSAppearance by searching the specified bundle for a file with the specified name (without path extension).
    If bundle is nil, the main bundle is assumed.
 */
- (nullable instancetype)initWithAppearanceNamed:(NSAppearanceName)name bundle:(nullable NSBundle *)bundle NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/* Query allowsVibrancy to see if the given appearance actually needs vibrant drawing. You may want to draw differently if the current apperance is vibrant.
 */
@property (readonly) BOOL allowsVibrancy NS_AVAILABLE_MAC(10_10);

@end

#pragma mark -
#pragma mark Standard Appearances

APPKIT_EXTERN NSAppearanceName const NSAppearanceNameAqua NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSAppearanceName const NSAppearanceNameLightContent NS_DEPRECATED_MAC(10_9, 10_10, "Light content should use the default Aqua apppearance.");

/* The following two Vibrant appearances should only be set on an NSVisualEffectView, or one of its container subviews.
 */
APPKIT_EXTERN NSAppearanceName const NSAppearanceNameVibrantDark NS_AVAILABLE_MAC(10_10);
APPKIT_EXTERN NSAppearanceName const NSAppearanceNameVibrantLight NS_AVAILABLE_MAC(10_10);

#pragma mark -

@protocol NSAppearanceCustomization <NSObject>
@required

@property (nullable, strong) NSAppearance *appearance NS_AVAILABLE_MAC(10_9);

/* This returns the appearance that would be used when drawing the receiver, taking inherited appearances into account.
 */
@property (readonly, strong) NSAppearance *effectiveAppearance NS_AVAILABLE_MAC(10_9);

@end

NS_ASSUME_NONNULL_END
