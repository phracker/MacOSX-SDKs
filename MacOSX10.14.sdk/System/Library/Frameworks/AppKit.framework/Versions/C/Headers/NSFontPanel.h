/*
	NSFontPanel.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFontPanel, NSMutableDictionary, NSFontManager, NSMutableArray, NSTableView, NSFontDescriptor, NSFont;


typedef NS_OPTIONS(NSUInteger, NSFontPanelModeMask) {
    NSFontPanelModeMaskFace = 1 << 0,
    NSFontPanelModeMaskSize = 1 << 1,
    NSFontPanelModeMaskCollection = 1 << 2,
    NSFontPanelModeMaskUnderlineEffect = 1<<8,
    NSFontPanelModeMaskStrikethroughEffect = 1<<9,
    NSFontPanelModeMaskTextColorEffect = 1<< 10,
    NSFontPanelModeMaskDocumentColorEffect = 1<<11,
    NSFontPanelModeMaskShadowEffect = 1<<12,
    NSFontPanelModeMaskAllEffects = 0XFFF00,
    NSFontPanelModesMaskStandardModes = 0xFFFF,
    NSFontPanelModesMaskAllModes = 0xFFFFFFFF
};

@protocol NSFontChanging <NSObject>
@optional

/* This is the message that's propagated up the responder chain.
 */
- (void)changeFont:(nullable NSFontManager *)sender;
- (NSFontPanelModeMask)validModesForFontPanel:(NSFontPanel *)fontPanel;
@end

#if __swift__ < 40200
@interface NSObject (NSFontPanelValidationAdditions)
- (NSFontPanelModeMask)validModesForFontPanel:(NSFontPanel *)fontPanel NS_DEPRECATED_MAC(10_0, API_TO_BE_DEPRECATED, "This is now an optional method of the NSFontChanging protocol.");
@end
#endif


NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSFontPanel : NSPanel {
    /*All instance variables are private*/
    NSFontManager *_manager APPKIT_IVAR;
    NSArray *_collectionNames APPKIT_IVAR;
    id _selection APPKIT_IVAR;
    void *_carbonNotification APPKIT_IVAR;
    id _targetObject APPKIT_IVAR;

    id			_familyList APPKIT_IVAR;
    id                  _faceList APPKIT_IVAR;
    id                  _sizeList APPKIT_IVAR;
    id                  _mainCollectionList APPKIT_IVAR;
    id			_sizeField APPKIT_IVAR;
    id                  _sizeSlider APPKIT_IVAR;
    id                  _sizeSliderBox APPKIT_IVAR;
    id			_preview APPKIT_IVAR;
    id			_previewContainer APPKIT_IVAR;
    id                  _mainSplitView APPKIT_IVAR;
    id			_mmCollectionList APPKIT_IVAR;
    id			_mmFamilyList APPKIT_IVAR;
    id                  _mmFaceList APPKIT_IVAR;
    id                  _mmSizeList APPKIT_IVAR;
    id			_fullSizeHeightConstraint APPKIT_IVAR;
    id                  _searchField APPKIT_IVAR;
    id			_fixedListButton APPKIT_IVAR;
    id		        _sliderButton APPKIT_IVAR;
    id		        _accessoryView APPKIT_IVAR;
    struct __fpFlags {
	unsigned int	    setFontChange:1;
	unsigned int	    setFontAttributeChange:1;
	unsigned int	    _delRespFamily:1;
	unsigned int	    _delRespFace:1;
	unsigned int	    _delRespSize:1;
	unsigned int	    _delRespColl:1;
	unsigned int	    _collectionDisabled:1; // used by validate font panel modes. 
	unsigned int	    _sizeDisabled:1; // used by validate font panel modes. 
	unsigned int	    _faceDisabled:1; // used by validate font panel modes. 
        unsigned int        showEffects:1;
        unsigned int        _uiMode:8;
        unsigned int        _miniMode:1;
        unsigned int _reserved:13;
    } _fpFlags APPKIT_IVAR;

    id			_regularModeBox APPKIT_IVAR;
    id			_miniModeBox APPKIT_IVAR;
    id			_sizeBox APPKIT_IVAR;
    id			_collectionLabel APPKIT_IVAR;
    id			_sizeLabel APPKIT_IVAR;
    id                  _faceDivider APPKIT_IVAR;
    id                  _familyLabel APPKIT_IVAR;
    id			_sizeStyleButton APPKIT_IVAR;
    id			_newSizeField APPKIT_IVAR;
    id			_editSizeList APPKIT_IVAR;
    id			_editSizeListBox APPKIT_IVAR;
    id			_editSizeSliderBox APPKIT_IVAR;
    id			_editSizeSliderMaxField APPKIT_IVAR;
    id			_editSizeSliderMinField APPKIT_IVAR;
    id			_sizeEditWindow APPKIT_IVAR;
    id			_availableSizes APPKIT_IVAR;

    id _addCollectionButton APPKIT_IVAR;
    id _removeCollectionButton APPKIT_IVAR;

    CGFloat _fontPanelPreviewHeight APPKIT_IVAR;
    id _typographyPanel APPKIT_IVAR;
    id _actionButton APPKIT_IVAR;
    id _fontEffectsBox APPKIT_IVAR;
    int _sizeStyle APPKIT_IVAR;

    id _fontPanelToolbar APPKIT_IVAR;
    id _fontPanelContentView APPKIT_IVAR;

#if !__LP64__
    id _fpUnused[69] APPKIT_IVAR;
#endif /* !__LP64__ */

@private
    id _familyToFaceConstraint APPKIT_IVAR;
}

@property (class, readonly, strong) NSFontPanel *sharedFontPanel;
@property (class, readonly) BOOL sharedFontPanelExists;

@property (nullable, strong) NSView *accessoryView;
- (void)setPanelFont:(NSFont *)fontObj isMultiple:(BOOL)flag;
- (NSFont *)panelConvertFont:(NSFont *)fontObj;
@property BOOL worksWhenModal;
@property (getter=isEnabled) BOOL enabled;

/* This method triggers a re-load to the default state, so that the delegate will be called, and have an opportunity to scrutinize the default list of fonts to be displayed in the panel.
*/
- (void) reloadDefaultFontFamilies;

@end


// The following enum items are deprecated. Use NSFontPanelModeMask instead
enum {
    NSFontPanelFaceModeMask = 1 << 0,
    NSFontPanelSizeModeMask = 1 << 1,
    NSFontPanelCollectionModeMask = 1 << 2,
    NSFontPanelUnderlineEffectModeMask = 1<<8,
    NSFontPanelStrikethroughEffectModeMask = 1<<9,
    NSFontPanelTextColorEffectModeMask = 1<< 10,
    NSFontPanelDocumentColorEffectModeMask = 1<<11,
    NSFontPanelShadowEffectModeMask = 1<<12,
    NSFontPanelAllEffectsModeMask = 0XFFF00,
    NSFontPanelStandardModesMask = 0xFFFF,
    NSFontPanelAllModesMask = 0xFFFFFFFF
};

/* Tags of views in the FontPanel
 THESE ARE ALL OBSOLETE and should not be used.
 */
enum {
    NSFPPreviewButton			= 131,
    NSFPRevertButton			= 130,
    NSFPSetButton			= 132,
    NSFPPreviewField			= 128,
    NSFPSizeField			= 129,
    NSFPSizeTitle			= 133,
    NSFPCurrentField			= 134
} NS_ENUM_DEPRECATED_MAC(10_0, 10_0);

NS_ASSUME_NONNULL_END
