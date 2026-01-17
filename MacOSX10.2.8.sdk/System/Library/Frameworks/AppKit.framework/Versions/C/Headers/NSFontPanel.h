/*
	NSFontPanel.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>
#import <AppKit/NSBrowser.h>

@class NSButton, NSFont, NSMatrix, NSMutableArray, NSMutableDictionary;

@interface NSFontPanel : NSPanel {
    /*All instance variables are private*/
    NSMatrix 		*_faces;
    NSMatrix 		*_families;
    id                  _preview; 
    id                  _current; // no longer used
    id                  _size;
    NSMatrix 		*_sizes;
    id                  _manager;
    id                  _selFont;
    NSMutableArray	*_collections;
    NSMutableDictionary *_collectionDicts;
    id                  _accessoryView;
    id			_browser;	
    NSButton		*_setButton;
    id                  _separator;
    id                  _sizeTitle;
    id			_titles; 	// No longer used - reserved.
    id			_fontSetButton;	// No longer used - reserved.
    id			_fontSetMatrix;
    id		        _chooser; // The family, face, and size list group
    id		        _previewBox; // no longer used.
    struct __fpFlags {
        unsigned int        multipleFont:1;
        unsigned int        dirty:1;
        unsigned int        amPreviewing:1;
        unsigned int        alwaysPreview:1;
        unsigned int        dontPreview:1;
	unsigned int	    sizeFieldChanged:1;
	unsigned int	    sizeValueCacheIsValid:1;
	unsigned int	    sizeFieldIsRelative:1;
	unsigned int	    inittedCollPane:1;
	unsigned int	    inittedFavePane:1;
	unsigned int	    didInitialPaneSetup:1;
	unsigned int	    _inNewCol:1;
	unsigned int	    _delRespFamily:1;
	unsigned int	    _delRespFace:1;
	unsigned int	    _delRespSize:1;
	unsigned int	    _delRespColl:1;
	unsigned int	    _miniModeActive; // true if we are in "mini mode".
	unsigned int	    _miniFavsActive; // true if "favorites" is active in mini-mode.
	unsigned int	    _mainFavActive; // true if main mode "Favorites" is active.
	unsigned int	    _inTakingSizeFromSlider; // true if in process of taking slider value.
        unsigned int        RESERVED2:13;
    } _fpFlags;
    float		_cachedSizeValue;
    id _familyDict; /* current family dict, obtained from manager */
    id _curSelFace;
    id _tabVue; // the big tab view in the main panel.
    id _choosePanelButton; // popup button for choosing what sub-panel to display.
    id _collectionBox;
    id _favoritesBox; // no longer used.
    id _mainBrowserBox;
    id _collectionBrowser;
    id _colFamilies;
    id _allFamiliesBrowser;
    id _favoritesBrowser;
    id _favoritesDict;
    NSString *_curFontSetName;
    id _passedCel;
    id _passedStr;
    id faces;
    id families;
    id _addFavButton;
    id _lboxSep, _rboxSep; // will no longer be used
    id _removeFromColButton;
    id _addToColButton;
    int _lastPane;
    id _splitVue; // will no longer be used
    id _fontSizesEditingPaneInnerBox;
    id _collectionAddButton;
    id _collectionRemoveButton;
    id _collectionRenameButton;
    id _reserved3[2];

    id _mainColBrowser;
    id _fontSizeChooserTabVue;
    id _fixedListBox;
    id _adjSliderBox;
    id _fontSizesEditingPane;

    id _miniModeBox; // box containing mini mode main items.
    id _miniModeCollectionsPopup;
    id _miniModeCollectionsPopupBox;
    id _miniModeFamPopup;
    id _miniModeFavoritesPopup;
    id _miniModeFavoritesPopupBox;
    id _miniModeTypefacePopup;
    id _miniModeTypefacesBox;
    id _miniModeSizesPopup;
    id _sizeSliderBox;
    id _sizesBox;
    int _fontSizeChooserType; // fixed list or adj slider
    id _sizesSlider; // the slider from SizeSlider+Favs view
    id _collectionMatrix; // (new) main "collections" one-column browser
    id _fixedListScrollView; // scroll view in size editing list box
    id _sizesEditList; // the matrix of cells in the size editing scroll view

    id _mmTitleCollections; // titles of various mini-mode items...
    id _mmTitleFavorites;
    id _mmTitleFamily;
    id _mmTitleTypeface;
    id _mmTitleSize;

    id _mainBox;  // box containing tab view and fontExtras button
    id _mainBoxSuperview; // the "real" saved superview of the mainBox...
    id _sizesScrollView; // super view of the _sizes matrix...
    id _fontColBox; // box containing the collection editor pane...

    id _doneButton; // done with col editing.

    id _familyList;
    id _faceList;
    id _familyBrowser;
    id _faceBrowser;
    id _favoritesList;
    id _mainCollectionList;
    id _sizeList;
    id _allFamiliesList;
    id _curFont;
    id _sizeEditDoneButton;
    id _carbonNotification;
    id _resetSizesButton;
    id _Reserved32[16]; // Some reserved thingies for ui widgets.
    id _sizeChooser; // matrix of radio buttons to choose list/slider mode
    id _sizeChooserFld_New; // text fields in the size edit pane.
    id _sizeChooserFld_Min;
    id _sizeChooserFld_Max;
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


