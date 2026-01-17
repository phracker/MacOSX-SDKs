/*
	NSFontPanel.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>

@class NSFontPanel, NSMutableDictionary, NSFontManager, NSMutableArray, NSTableView, NSFontDescriptor, NSFont;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@interface NSObject (NSFontPanelValidationAdditions)
- (NSUInteger) validModesForFontPanel: (NSFontPanel *) fontPanel;
@end

#endif

@interface NSFontPanel : NSPanel {
    /*All instance variables are private*/
    NSFontManager *_manager;
    NSArray *_collectionNames;
    id _selection;
    void *_carbonNotification; 
    id _targetObject;

    id			_familyList;
    id                  _faceList; 
    id                  _sizeList; 
    id                  _mainCollectionList;
    id			_sizeField;
    id                  _sizeSlider;
    id                  _sizeSliderBox;
    id			_preview;
    id			_previewCaption;
    id                  _mainSplitView;
    id			_mmCollectionList;	
    id			_mmFamilyList;
    id                  _mmFaceList;
    id                  _mmSizeList;
    id			_extrasPopup; 	
    id			_searchField;	
    id			_fixedListButton;
    id		        _sliderButton; 
    id		        _accessoryView; 
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
        unsigned int _uiMode:8;
        unsigned int _reserved:14;
    } _fpFlags;

    id			_regularModeBox; 
    id			_miniModeBox; 
    id			_modeBoxSuperview; 
    id			_collectionLabel; 
    id			_sizeLabel; 
    id			_faceLabel; 
    id			_familyLabel; 
    id			_sizeStyleButton; 
    id			_newSizeField; 
    id			_editSizeList; 
    id			_editSizeListBox; 
    id			_editSizeSliderBox; 
    id			_editSizeSliderMaxField; 
    id			_editSizeSliderMinField; 
    id			_sizeEditWindow; 
    id			_availableSizes; 

    id _addCollectionButton;
    id _removeCollectionButton;

    CGFloat _fontPanelPreviewHeight; 
    id _typographyPanel;
    id _actionButton;
    id _fontEffectsBox;
    int _sizeStyle;

#if !__LP64__
    id _fpUnused[72];
#endif /* !__LP64__ */
}

+ (NSFontPanel *)sharedFontPanel;
+ (BOOL)sharedFontPanelExists;

- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)aView;
- (void)setPanelFont:(NSFont *)fontObj isMultiple:(BOOL)flag;
- (NSFont *)panelConvertFont:(NSFont *)fontObj;
- (BOOL)worksWhenModal;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;

/* This method triggers a re-load to the default state, so that the delegate will be called, and have an opportunity to scrutinize the default list of fonts to be displayed in the panel.
*/
- (void) reloadDefaultFontFamilies;

@end


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
};


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
enum {
    NSFontPanelFaceModeMask = 1 << 0,
    NSFontPanelSizeModeMask = 1 << 1,
    NSFontPanelCollectionModeMask = 1 << 2,
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    NSFontPanelUnderlineEffectModeMask = 1<<8,
    NSFontPanelStrikethroughEffectModeMask = 1<<9,
    NSFontPanelTextColorEffectModeMask = 1<< 10,
    NSFontPanelDocumentColorEffectModeMask = 1<<11,
    NSFontPanelShadowEffectModeMask = 1<<12,
    NSFontPanelAllEffectsModeMask = 0XFFF00,
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
    NSFontPanelStandardModesMask = 0xFFFF,
    NSFontPanelAllModesMask = 0xFFFFFFFF
};
#endif
