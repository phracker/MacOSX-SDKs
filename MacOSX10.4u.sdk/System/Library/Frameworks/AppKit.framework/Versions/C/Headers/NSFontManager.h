/*
	NSFontManager.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSFont, NSFontPanel, NSMenu, NSFontDescriptor;

typedef unsigned int NSFontTraitMask;

/*
 * Font Traits
 *
 * This list should be kept small since the more traits that are assigned
 * to a given font, the harder it will be to map it to some other family.
 * Some traits are mutually exclusive such as NSExpanded and NSCondensed.
 */

enum {
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


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

enum {
   NSFontCollectionApplicationOnlyMask = 1 << 0  
};

#endif

@interface NSFontManager : NSObject
{
/*All instance variables are private*/
@private
    id                  _panel;
    unsigned int        _myNotification;
    SEL                 _action;
    int                 _whatToDo;
    NSFontTraitMask     _traitToChange;
    NSFont *            _selFont;
    struct _fmFlags {
	unsigned int        multipleFont:1;
	unsigned int        disabled:1;
	unsigned int	    makePanelKey:1;
	unsigned int        _RESERVED:13;
    }                   _fmFlags;
    unsigned short      _lastPos;
    id		        _delegate;
    id			_collections;
    id			_hiddenCollections;
    unsigned int        _reservedFMint4;
}

+ (void)setFontPanelFactory:(Class)factoryId;
+ (void)setFontManagerFactory:(Class)factoryId;
+ (NSFontManager *)sharedFontManager;

- (BOOL)isMultiple;
- (NSFont *)selectedFont;
- (void)setSelectedFont:(NSFont *)fontObj isMultiple:(BOOL)flag;
- (void)setFontMenu:(NSMenu *)newMenu;
- (NSMenu *)fontMenu:(BOOL)create;
- (NSFontPanel *)fontPanel:(BOOL)create;
- (NSFont *)fontWithFamily:(NSString *)family traits:(NSFontTraitMask)traits weight:(int)weight size:(float)size;
- (NSFontTraitMask)traitsOfFont:(NSFont *)fontObj;
- (int)weightOfFont:(NSFont *)fontObj;

/* Three methods for supporting app font management.  The fonts and names used/returned by these functions are the same as those used by the NSFontPanel.  The third method below takes as input a name as returned by "availableFontFamilies" and returns an NSArray of NSArrays.  The elements of the "inner" arrays are: (0) the font's name, (1) non-family part of the name as used by NSFontPanel, (2) an NSNumber indicating the weight, and (3) an NSNumber indicating the traits.
*/
- (NSArray *)availableFonts;
- (NSArray *)availableFontFamilies;
- (NSArray *)availableMembersOfFontFamily:(NSString *)fam;

- (NSFont *)convertFont:(NSFont *)fontObj;
- (NSFont *)convertFont:(NSFont *)fontObj toSize:(float)size;
- (NSFont *)convertFont:(NSFont *)fontObj toFace:(NSString *)typeface;
- (NSFont *)convertFont:(NSFont *)fontObj toFamily:(NSString *)family;
- (NSFont *)convertFont:(NSFont *)fontObj toHaveTrait:(NSFontTraitMask)trait;
- (NSFont *)convertFont:(NSFont *)fontObj toNotHaveTrait:(NSFontTraitMask)trait;
- (NSFont *)convertWeight:(BOOL)upFlag ofFont:(NSFont *)fontObj;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (BOOL)sendAction;
- (void)setDelegate:(id)anObject;
- (id)delegate;

- (NSString *) localizedNameForFamily:(NSString *)family face:(NSString *)faceKey;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setSelectedAttributes:(NSDictionary *)attributes isMultiple:(BOOL)flag;
- (NSDictionary *)convertAttributes:(NSDictionary *)attributes;

- (NSArray *) availableFontNamesMatchingFontDescriptor: (NSFontDescriptor *) descriptor;

- (NSArray *) collectionNames;
- (NSArray *) fontDescriptorsInCollection: (NSString *) collectionNames;
- (BOOL) addCollection: (NSString *) collectionName options: (int) collectionOptions;
- (BOOL) removeCollection: (NSString *) collectionName;

- (void) addFontDescriptors: (NSArray *) descriptors  toCollection: (NSString *) collectionName;
- (void) removeFontDescriptor: (NSFontDescriptor *) descriptor fromCollection: (NSString *) collection;
#endif

@end

@interface NSFontManager(NSFontManagerMenuActionMethods)

- (BOOL)fontNamed:(NSString *)fName hasTraits:(NSFontTraitMask)someTraits;

/* The following is like "availableFonts", but checks traits.  Returns an auto-released instance.  To get fonts with "non-italic" or "non-bold" combine the flags NSUnitalicFontMask and/or NSUnboldFontMask as the argument "someTraits".
*/
- (NSArray *)availableFontNamesWithTraits:(NSFontTraitMask)someTraits;

/* These methods are action messages sent from Font Menu items:
*/
- (void)addFontTrait:(id)sender;
- (void)removeFontTrait:(id)sender;
- (void)modifyFontViaPanel:(id)sender;
- (void)modifyFont:(id)sender;
- (void)orderFrontFontPanel:(id)sender;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)orderFrontStylesPanel:(id)sender;
#endif

@end

/* And these "actions" are really tag values in Font Menu cells which send any of the action messages listed above.  Normally, they're pre-defined in the font panel.
*/
typedef enum _NSFontAction {
    NSNoFontChangeAction		= 0,
    NSViaPanelFontAction		= 1,
    NSAddTraitFontAction		= 2,
    NSSizeUpFontAction			= 3,
    NSSizeDownFontAction		= 4,
    NSHeavierFontAction			= 5,
    NSLighterFontAction			= 6,
    NSRemoveTraitFontAction		= 7
} NSFontAction;

/* This method is perhaps inappropriately named; it is sent to the delegate of the shared NSFontPanel instance, not to the delegate of the NSFontManager.
*/
@interface NSObject(NSFontManagerDelegate)
- (BOOL)fontManager:(id)sender willIncludeFont:(NSString *)fontName;
@end

/* This is the message that's propagated up the responder chain.
*/
@interface NSObject(NSFontManagerResponderMethod)
- (void)changeFont:(id)sender;
@end

