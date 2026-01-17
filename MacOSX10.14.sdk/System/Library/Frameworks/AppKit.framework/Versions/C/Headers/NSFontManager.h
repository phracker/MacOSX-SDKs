/*
	NSFontManager.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSMenu.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFont, NSFontPanel, NSMenu, NSFontDescriptor;

/*
 * Font Traits
 *
 * This list should be kept small since the more traits that are assigned
 * to a given font, the harder it will be to map it to some other family.
 * Some traits are mutually exclusive such as NSExpanded and NSCondensed.
 */
typedef NS_OPTIONS(NSUInteger, NSFontTraitMask) {
    NSItalicFontMask			= 0x00000001,
    NSBoldFontMask			= 0x00000002,
    NSUnboldFontMask			= 0x00000004,
    NSNonStandardCharacterSetFontMask	= 0x00000008,
    NSNarrowFontMask			= 0x00000010,
    NSExpandedFontMask			= 0x00000020,
    NSCondensedFontMask			= 0x00000040,
    NSSmallCapsFontMask			= 0x00000080,
    NSPosterFontMask			= 0x00000100,
    NSCompressedFontMask		= 0x00000200,
    NSFixedPitchFontMask		= 0x00000400,
    NSUnitalicFontMask			= 0x01000000
};


typedef NS_OPTIONS(NSUInteger, NSFontCollectionOptions) {
   NSFontCollectionApplicationOnlyMask = 1 << 0
};


/* And these "actions" are really tag values in Font Menu cells which send any of the action messages listed above.  Normally, they're pre-defined in the font panel.
 */
typedef NS_ENUM(NSUInteger, NSFontAction) {
    NSNoFontChangeAction		= 0,
    NSViaPanelFontAction		= 1,
    NSAddTraitFontAction		= 2,
    NSSizeUpFontAction			= 3,
    NSSizeDownFontAction		= 4,
    NSHeavierFontAction			= 5,
    NSLighterFontAction			= 6,
    NSRemoveTraitFontAction		= 7
};

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSFontManager : NSObject <NSMenuItemValidation>
{
/*All instance variables are private*/
@private
    NSFontPanel * _panel APPKIT_IVAR;
#ifndef __OBJC2__
    unsigned int _fmReserved1 APPKIT_IVAR;
#endif
    SEL _action APPKIT_IVAR;
    id _actionOrigin APPKIT_IVAR;
    id _target APPKIT_IVAR;
    NSFont *_selFont APPKIT_IVAR;
    struct _fmFlags {
	unsigned int multipleFont:1;
	unsigned int disabled:1;
        unsigned int senderTagMode:2;
	unsigned int _RESERVED:12;
    } _fmFlags APPKIT_IVAR;
#ifndef __OBJC2__
    unsigned short _fmReserved3 APPKIT_IVAR;
#endif
    id _delegate APPKIT_IVAR;
    id _collections APPKIT_IVAR;
#ifndef __OBJC2__
    id _hiddenCollections APPKIT_IVAR;
    NSUInteger _fmReserved4 APPKIT_IVAR;
#endif
}

+ (void)setFontPanelFactory:(nullable Class)factoryId;
+ (void)setFontManagerFactory:(nullable Class)factoryId;
@property (class, readonly, strong) NSFontManager *sharedFontManager;

@property (getter=isMultiple, readonly) BOOL multiple;
@property (nullable, readonly, strong) NSFont *selectedFont;
- (void)setSelectedFont:(NSFont *)fontObj isMultiple:(BOOL)flag;
- (void)setFontMenu:(NSMenu *)newMenu;
- (nullable NSMenu *)fontMenu:(BOOL)create;
- (nullable NSFontPanel *)fontPanel:(BOOL)create;
- (nullable NSFont *)fontWithFamily:(NSString *)family traits:(NSFontTraitMask)traits weight:(NSInteger)weight size:(CGFloat)size;
- (NSFontTraitMask)traitsOfFont:(NSFont *)fontObj;
- (NSInteger)weightOfFont:(NSFont *)fontObj;

/* Three methods for supporting app font management.  The fonts and names used/returned by these functions are the same as those used by the NSFontPanel.  The third method below takes as input a name as returned by "availableFontFamilies" and returns an NSArray of NSArrays.  The elements of the "inner" arrays are: (0) the font's name, (1) non-family part of the name as used by NSFontPanel, (2) an NSNumber indicating the weight, and (3) an NSNumber indicating the traits.
*/
@property (readonly, copy) NSArray<NSString *> *availableFonts;
@property (readonly, copy) NSArray<NSString *> *availableFontFamilies;
- (nullable NSArray<NSArray *> *)availableMembersOfFontFamily:(NSString *)fam;

- (NSFont *)convertFont:(NSFont *)fontObj;
- (NSFont *)convertFont:(NSFont *)fontObj toSize:(CGFloat)size;
- (nullable NSFont *)convertFont:(NSFont *)fontObj toFace:(NSString *)typeface;
- (NSFont *)convertFont:(NSFont *)fontObj toFamily:(NSString *)family;
- (NSFont *)convertFont:(NSFont *)fontObj toHaveTrait:(NSFontTraitMask)trait;
- (NSFont *)convertFont:(NSFont *)fontObj toNotHaveTrait:(NSFontTraitMask)trait;
- (NSFont *)convertWeight:(BOOL)upFlag ofFont:(NSFont *)fontObj;
@property (getter=isEnabled) BOOL enabled;
@property SEL action;
@property (nullable, assign) id delegate NS_DEPRECATED_MAC(10_0, 10_11, "NSFontManager doesn't have any delegate method. This property should not be used.");


- (BOOL)sendAction;

- (NSString *) localizedNameForFamily:(NSString *)family face:(nullable NSString *)faceKey;

- (void)setSelectedAttributes:(NSDictionary<NSString *, id> *)attributes isMultiple:(BOOL)flag;
- (NSDictionary<NSString *, id> *)convertAttributes:(NSDictionary<NSString *, id> *)attributes;

- (nullable NSArray *)availableFontNamesMatchingFontDescriptor:(NSFontDescriptor *)descriptor NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSFontDescriptor matchingFontDescriptorsWithMandatoryKeys:] instead");

@property (readonly, copy) NSArray *collectionNames NS_DEPRECATED_MAC(10_0, 10_11, "Use +[NSFontCollection allFontCollectionNames] instead");
- (nullable NSArray *)fontDescriptorsInCollection:(NSString *)collectionNames NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSFontCollection matchingDescriptors] instead");
- (BOOL)addCollection:(NSString *)collectionName options:(NSFontCollectionOptions)collectionOptions NS_DEPRECATED_MAC(10_0, 10_11, "Use +[NSFontCollection showFontCollection:withName:visibility:name:] instead");
- (BOOL)removeCollection:(NSString *)collectionName NS_DEPRECATED_MAC(10_0, 10_11, "Use +[NSFontCollection hideFontCollectionWithName:visibility:error:] instead");

- (void)addFontDescriptors:(NSArray *)descriptors  toCollection:(NSString *)collectionName NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSMutableFontCollection addQueryForDescriptors:] instead");
- (void)removeFontDescriptor:(NSFontDescriptor *)descriptor fromCollection:(NSString *)collection NS_DEPRECATED_MAC(10_0, 10_11, "Use -[NSMutableFontCollection removeQueryForDescriptors:] instead");

/* Returns the current font action used by -convertFont:. This method is intended to be invoked to query the font conversion action while the action message (usually -changeFont:) is being invoked.
 */
@property (readonly) NSFontAction currentFontAction NS_AVAILABLE_MAC(10_5);

/* Converts fontTraits to a new traits mask value just as -convertFont:. This method is intended to be invoked to query the font traits while the action message (usually -changeFont:) is being invoked when the current font action is either NSAddTraitFontAction or NSRemoveTraitFontAction.
 */
- (NSFontTraitMask)convertFontTraits:(NSFontTraitMask)traits NS_AVAILABLE_MAC(10_5);

@property (nullable, weak) id target NS_AVAILABLE_MAC(10_5);

@end

@interface NSFontManager(NSFontManagerMenuActionMethods)

- (BOOL)fontNamed:(NSString *)fName hasTraits:(NSFontTraitMask)someTraits;

/* The following is like "availableFonts", but checks traits.  Returns an auto-released instance.  To get fonts with "non-italic" or "non-bold" combine the flags NSUnitalicFontMask and/or NSUnboldFontMask as the argument "someTraits".
*/
- (nullable NSArray<NSString *> *)availableFontNamesWithTraits:(NSFontTraitMask)someTraits;

/* These methods are action messages sent from Font Menu items:
*/
- (void)addFontTrait:(nullable id)sender;
- (void)removeFontTrait:(nullable id)sender;
- (void)modifyFontViaPanel:(nullable id)sender;
- (void)modifyFont:(nullable id)sender;
- (void)orderFrontFontPanel:(nullable id)sender;
- (void)orderFrontStylesPanel:(nullable id)sender;

@end

/* This method is perhaps inappropriately named; it is sent to the delegate of the shared NSFontPanel instance, not to the delegate of the NSFontManager.
*/
@interface NSObject(NSFontManagerDelegate)
- (BOOL)fontManager:(id)sender willIncludeFont:(NSString *)fontName NS_DEPRECATED_MAC(10_0, 10_11, "Use NSFontCollection for providing filtered font lists");
@end

#if __swift__ < 40200
/* This is the message that's propagated up the responder chain.
*/
@interface NSObject(NSFontManagerResponderMethod)
- (void)changeFont:(nullable id)sender NS_DEPRECATED_MAC(10_0, API_TO_BE_DEPRECATED, "This is now an optional method of the NSFontChanging protocol.");
@end
#endif

NS_ASSUME_NONNULL_END

