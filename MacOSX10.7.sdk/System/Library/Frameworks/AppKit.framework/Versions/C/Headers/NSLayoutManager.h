/*
        NSLayoutManager.h
        Application Kit
        Copyright (c) 1994-2011, Apple Inc.
        All rights reserved.
*/

/* An NSLayoutManager stores glyphs, attributes, and layout information generated from an NSTextStorage.  It can map between ranges of characters in the NSTextStorage and ranges of glyphs within itself.  It understands and keeps track of two types of range invalidation:  a character range can need glyphs generated for it or it can need its glyphs laid out.  When an NSLayoutManager is asked for information which would require knowledge of glyphs or layout which is not currently available, the NSLayoutManager must cause the appropriate recalculation to be done.
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSFont.h>
#import <AppKit/NSImageCell.h>
#import <AppKit/NSGlyphGenerator.h>

@class NSTextStorage;
@class NSTypesetter;
@class NSTextContainer;
@class NSTextView;
@class NSWindow;
@class NSColor;
@class NSRulerView;
@class NSParagraphStyle;
@class NSRulerMarker;
@class NSBox;
@class NSTextField;
@class NSMatrix;
@class NSTabWell;
@class NSStorage;
@class NSRunStorage;
@class NSSortedArray;
@class NSView;
@class NSMutableArray;
@class NSEvent;
@class NSCell;
@class NSGlyphGenerator;
@class NSTextBlock;

@protocol NSLayoutManagerDelegate;

/* These glyph attributes are used only inside the glyph generation machinery, but must be shared between components. */
enum {
    NSGlyphAttributeSoft        = 0,
    NSGlyphAttributeElastic     = 1,
    NSGlyphAttributeBidiLevel   = 2,
    NSGlyphAttributeInscribe    = 5
};

/* Values for NSGlyphInscription.  The inscribe attribute of a glyph determines how it is laid out relative to the previous glyph. */
enum {
    NSGlyphInscribeBase         = 0,
    NSGlyphInscribeBelow        = 1,
    NSGlyphInscribeAbove        = 2,
    NSGlyphInscribeOverstrike   = 3,
    NSGlyphInscribeOverBelow    = 4
};
typedef NSUInteger NSGlyphInscription;

/* Values for NSTypesetterBehavior */
enum {
    NSTypesetterLatestBehavior                  = -1,
    NSTypesetterOriginalBehavior                = 0,    // Mac OS X versions 10.0 and 10.1 (uses NSSimpleHorizontalTypesetter)
    NSTypesetterBehavior_10_2_WithCompatibility = 1,    // 10.2 with backward compatibility layout (uses new ATS-based typestter)
    NSTypesetterBehavior_10_2                   = 2,
    NSTypesetterBehavior_10_3                   = 3,
    NSTypesetterBehavior_10_4                   = 4
}; 
typedef NSInteger NSTypesetterBehavior;


/* Values for NSTextLayoutOrientation */
enum {
    NSTextLayoutOrientationHorizontal = 0, // Lines rendered horizontally, grow top to bottom
    NSTextLayoutOrientationVertical = 1, // Lines rendered vertically, grow right to left
};
typedef NSInteger NSTextLayoutOrientation;

@protocol NSTextLayoutOrientationProvider
- (NSTextLayoutOrientation)layoutOrientation NS_AVAILABLE_MAC(10_7);
// A property describing the receiver's layout orientation.  This property defines the default value for the range of string laid out in the receiver in absence of explicit NSVerticalGlyphFormAttributeName attribute.  For example, when NSTextLayoutOrientationVertical, the default value for NSVerticalGlyphFormAttributeName is 1.  When rendering into the receiver, the Text System assumes the coordinate system is appropriately rotated.  NSTextAttachmentCell determines the image orientation based on the control view's layoutOrientation.  There are two public AppKit classes implementing this interface: NSTextContainer and NSTextView.  The NSTextContainer implementation just returns the value from its text view if non-nil; otherwise, returns NSTextLayoutOrientationHorizontal.  For working with non-NSTextView views, the NSTextContainer implementation can be overridden in order to support the custom layout orientation logic.
@end


@interface NSLayoutManager : NSObject <NSCoding, NSGlyphStorage> {

  /*All instance variables are private*/

  @private
    NSTextStorage *_textStorage;
    NSGlyphGenerator *_glyphGenerator;
    NSTypesetter *_typesetter;

    NSMutableArray *_textContainers;
    NSStorage *_containerUsedRects;

    NSStorage *_glyphs;
    NSRunStorage *_containerRuns;
    NSRunStorage *_fragmentRuns;
    NSRunStorage *_glyphLocations;
    NSRunStorage *_glyphRotationRuns;
    
    NSRect _extraLineFragmentRect;
    NSRect _extraLineFragmentUsedRect;
    NSTextContainer *_extraLineFragmentContainer;

    NSSortedArray *_glyphHoles;
    NSSortedArray *_layoutHoles;

    struct __lmFlags {
        unsigned int containersAreFull:1;
        unsigned int glyphsMightDrawOutsideLines:1;
        unsigned int backgroundLayoutEnabled:1;
        unsigned int resizingInProgress:1;
        unsigned int allowScreenFonts:1;
        unsigned int cachedRectArrayInUse:1;
        unsigned int displayInvalidationInProgress:1;
        unsigned int insertionPointNeedsUpdate:1;
        unsigned int layoutManagerInDirtyList:1;
        unsigned int usingGlyphCache:1;
        unsigned int showInvisibleCharacters:1;
        unsigned int showControlCharacters:1;
        unsigned int delegateRespondsToDidInvalidate:1;
        unsigned int delegateRespondsToDidComplete:1;
        unsigned int glyphFormat:2;
        unsigned int textStorageRespondsToIsEditing:1;
        unsigned int notifyEditedInProgress:1;
        unsigned int containersChanged:1;
        unsigned int isGeneratingGlyphs:1;
        unsigned int hasNonGeneratedGlyphData:1;
        unsigned int loggedBGLayoutException:1;
        unsigned int isLayoutRequestedFromSubthread:1;
        unsigned int defaultAttachmentScaling:2;
        unsigned int isInUILayoutMode:1;
        unsigned int seenRightToLeft:1;
        unsigned int ignoresViewTransformations:1;
        unsigned int needToFlushGlyph:1;
        unsigned int flipsIfNeeded:1;
        unsigned int allowNonContig:1;
        unsigned int useNonContig:1;
    } _lmFlags;

    id _delegate;

    // Enable/disable stacks
    unsigned short _textViewResizeDisableStack;
    unsigned short _displayInvalidationDisableStack;
    NSRange _deferredDisplayCharRange;

    // Cache for first text view
    NSTextView *_firstTextView;

    // Cache for rectangle arrays 
    __strong NSRect *_cachedRectArray;
    NSUInteger _cachedRectArrayCapacity;

    // Cache for glyph strings
    __strong char *_glyphBuffer;
    NSUInteger _glyphBufferSize;

    // Cache for faster glyph location lookup
    NSRange _cachedLocationNominalGlyphRange;
    NSUInteger _cachedLocationGlyphIndex;
    NSPoint _cachedLocation;
    NSRange _cachedFontCharRange;
    NSFont *_cachedFont;

    // Cache for first unlaid glyph and character
    NSUInteger _firstUnlaidGlyphIndex;
    NSUInteger _firstUnlaidCharIndex;

    // Outlets for ruler accessory view.
    NSBox *_rulerAccView;
    id _rulerAccViewAlignmentButtons;
    id _rulerAccViewSpacing;
    NSTabWell *_rulerAccViewLeftTabWell;
    NSTabWell *_rulerAccViewRightTabWell;
    NSTabWell *_rulerAccViewCenterTabWell;
    NSTabWell *_rulerAccViewDecimalTabWell;
    id _rulerAccViewStyles;
    id _rulerAccViewLists;

    NSRange _newlyFilledGlyphRange;

    id _extraData;
}

/**************************** Initialization ****************************/

- (id)init;
    // Designated Initializer.  Sets up this instance.  The NSLayoutManager starts off without an NSTextStorage.

/*************************** Helper objects ***************************/

- (NSTextStorage *)textStorage;
- (void)setTextStorage:(NSTextStorage *)textStorage;
    // The set method generally should not be called directly, but you may wish to override it.  Used to get and set the text storage.  The set method is called by NSTextStorage's addLayoutManager:/removeLayoutManager: methods.

- (NSAttributedString *)attributedString;
    // Part of the NSGlyphStorage protocol, for use by the glyph generator.  For NSLayoutManager the attributed string is equivalent to the text storage.

- (void)replaceTextStorage:(NSTextStorage *)newTextStorage;
    // This method should be used instead of the primitive -setTextStorage: if you need to replace a NSLayoutManager's NSTextStorage with a new one, leaving all related objects intact.  This method deals with all the work of making sure the NSLayoutManager doesn't get deallocated and transferring all the NSLayoutManagers on the old NSTextStorage to the new one.
    
- (NSGlyphGenerator *)glyphGenerator;
- (void)setGlyphGenerator:(NSGlyphGenerator *)glyphGenerator;
    // By default an NSLayoutManager uses the shared default glyph generator.  Setting the glyph generator invalidates all glyphs and layout in the NSLayoutManager.

- (NSTypesetter *)typesetter;
- (void)setTypesetter:(NSTypesetter *)typesetter;
    // By default an NSLayoutManager uses the shared default typesetter.  Setting the typesetter invalidates all glyphs in the NSLayoutManager.  It can't just invalidate layout because the typesetter may have contributed to the actual glyphs as well (e.g. hyphenation).

- (id <NSLayoutManagerDelegate>)delegate;
- (void)setDelegate:(id <NSLayoutManagerDelegate>)delegate;
    // Sets or gets the NSLayoutManager's delegate.

/**************************** Text containers ****************************/

- (NSArray *)textContainers;

- (void)addTextContainer:(NSTextContainer *)container;
    // Add a container to the end of the array.  Must invalidate layout of all glyphs after the previous last container (i.e., glyphs that were not previously laid out because they would not fit anywhere).
- (void)insertTextContainer:(NSTextContainer *)container atIndex:(NSUInteger)index;
    // Insert a container into the array before the container at index.  Must invalidate layout of all glyphs in the containers from the one previously at index to the last container.
- (void)removeTextContainerAtIndex:(NSUInteger)index;
    // Removes the container at index from the array.  Must invalidate layout of all glyphs in the container being removed and any containers which come after it.

- (void)textContainerChangedGeometry:(NSTextContainer *)container;
    // Called by NSTextContainer whenever it changes size or shape.  Invalidates layout of all glyphs in container and all subsequent containers.  

- (void)textContainerChangedTextView:(NSTextContainer *)container;
    // Called by NSTextContainer whenever its textView changes.  Used to keep notifications in sync.

/*********************** Global layout manager options ***********************/

- (void)setBackgroundLayoutEnabled:(BOOL)flag;
- (BOOL)backgroundLayoutEnabled;
    // These methods allow you to set/query whether the NSLayoutManager will lay out text in the background, i.e. on the main thread when it is idle.  The default is YES, but this should be set to NO whenever the layout manager is being accessed from other threads.  

- (void)setUsesScreenFonts:(BOOL)flag;
- (BOOL)usesScreenFonts;
    // Sets whether this layoutManager will use screen fonts when it is possible to do so.  The default is YES, but this should be set to NO if the layout manager will be used to draw scaled or rotated text.

- (void)setShowsInvisibleCharacters:(BOOL)flag;
- (BOOL)showsInvisibleCharacters;
    // If YES, then whitespace and other "invisible" unicodes will be shown with special glyphs or other drawing.  The default is NO.

- (void)setShowsControlCharacters:(BOOL)flag;
- (BOOL)showsControlCharacters;
    // If YES, then control characters will be rendered visibly (usually like "^M").  The default is NO.

- (void)setHyphenationFactor:(float)factor;
- (float)hyphenationFactor;
    // 0.0 - 1.0.  Whenever (width of the real contents of the line) / (the line fragment width) is below this value, hyphenation will be attempted when laying out the line.  By default, the value is 0.0, meaning hyphenation is off.  A value of 1.0 causes hyphenation to be attempted always.  Note that hyphenation will slow down text layout and increase memory usage, so it should be used sparingly.  Maybe overridden on a per-paragraph basis by the NSParagraphStyle's hyphenationFactor.

- (void)setDefaultAttachmentScaling:(NSImageScaling)scaling;
- (NSImageScaling)defaultAttachmentScaling;
    // Specifies the default behavior desired if an attachment image is too large to fit in a text container.  Note that attachment cells control their own size and drawing, so this setting can only be advisory for them, but kit-supplied attachment cells will respect it.  The default is NSImageScaleNone, meaning that images will clip rather than scaling.

- (void)setTypesetterBehavior:(NSTypesetterBehavior)theBehavior;
- (NSTypesetterBehavior)typesetterBehavior;
    // Specifies the typesetter behavior (compatibility setting) value for the layout manager.  The default is determined by the version of AppKit against which the application is linked.

- (NSUInteger)layoutOptions;
    // Part of the NSGlyphStorage protocol, for use by the glyph generator.  Allows the glyph generator to ask which options the layout manager requests.

- (void)setAllowsNonContiguousLayout:(BOOL)flag NS_AVAILABLE_MAC(10_5);
- (BOOL)allowsNonContiguousLayout NS_AVAILABLE_MAC(10_5);
    // If YES, then the layout manager may perform glyph generation and layout for a given portion of the text, without having glyphs or layout for preceding portions.  The default is NO.  Turning this setting on will significantly alter which portions of the text will have glyph generation or layout performed when a given generation-causing method is invoked.  It also gives significant performance benefits, especially for large documents.
- (BOOL)hasNonContiguousLayout NS_AVAILABLE_MAC(10_5);
    // Even if non-contiguous layout is allowed, it may not always be used, and there may not always be layout holes.  This method returns YES if there might currently be non-contiguous portions of the text laid out.

/************************** Invalidation **************************/

- (void)invalidateGlyphsForCharacterRange:(NSRange)charRange changeInLength:(NSInteger)delta actualCharacterRange:(NSRangePointer)actualCharRange;
    // This removes all glyphs for the old character range, adjusts the character indices of all the subsequent glyphs by the change in length, and invalidates the new character range.  If actualCharRange is non-NULL it will be set to the actual range invalidated after any necessary expansion.

- (void)invalidateLayoutForCharacterRange:(NSRange)charRange actualCharacterRange:(NSRangePointer)actualCharRange NS_AVAILABLE_MAC(10_5);
- (void)invalidateLayoutForCharacterRange:(NSRange)charRange isSoft:(BOOL)flag actualCharacterRange:(NSRangePointer)actualCharRange;
    // These methods invalidate the layout information for the given range of characters.  If actualCharRange is non-NULL it will be set to the actual range invalidated after any necessary expansion.  The first method has the same effect as the second with flag set to NO.  Soft layout holes are obsolete in 10.5 and later, so the flag is no longer necessary.

- (void)invalidateDisplayForCharacterRange:(NSRange)charRange;
- (void)invalidateDisplayForGlyphRange:(NSRange)glyphRange;
    // Invalidates display for the glyph or character range given.  For the character range variant, unlaid parts of the range are remembered and will be redisplayed at some point later when the layout is available.  For the glyph range variant any part of the range that does not yet have glyphs generated is ignored.  Neither method actually causes layout.

- (void)textStorage:(NSTextStorage *)str edited:(NSUInteger)editedMask range:(NSRange)newCharRange changeInLength:(NSInteger)delta invalidatedRange:(NSRange)invalidatedCharRange;
    // Sent from processEditing in NSTextStorage.  The newCharRange is the range in the final string which was explicitly edited.  The invalidatedRange includes portions that changed as a result of attribute fixing. invalidatedRange is either equal to newCharRange or larger.  Layout managers should not change the contents of the text storage during the execution of this message.

/************************ Causing glyph generation and layout ************************/

- (void)ensureGlyphsForCharacterRange:(NSRange)charRange NS_AVAILABLE_MAC(10_5);
- (void)ensureGlyphsForGlyphRange:(NSRange)glyphRange NS_AVAILABLE_MAC(10_5);
- (void)ensureLayoutForCharacterRange:(NSRange)charRange NS_AVAILABLE_MAC(10_5);
- (void)ensureLayoutForGlyphRange:(NSRange)glyphRange NS_AVAILABLE_MAC(10_5);
- (void)ensureLayoutForTextContainer:(NSTextContainer *)container NS_AVAILABLE_MAC(10_5);
- (void)ensureLayoutForBoundingRect:(NSRect)bounds inTextContainer:(NSTextContainer *)container NS_AVAILABLE_MAC(10_5);
    // These methods allow clients to specify exactly the portions of the document for which they wish to have glyphs or layout.  This is particularly important if non-contiguous layout is enabled.  The layout manager still reserves the right to perform glyph generation or layout for larger ranges.  If non-contiguous layout is not enabled, then the range in question will always effectively be extended to start at the beginning of the text.

/************************ Set glyphs and glyph attributes ************************/

// These methods are primitive.  They do not cause the bookkeeping of filling holes to happen.  They do not cause invalidation.  They are intended for use by the glyph generator (primarily the first) and the typesetter (the remainder, primarily the second.)

- (void)insertGlyphs:(const NSGlyph *)glyphs length:(NSUInteger)length forStartingGlyphAtIndex:(NSUInteger)glyphIndex characterIndex:(NSUInteger)charIndex;
    // Part of the NSGlyphStorage protocol, for use by the glyph generator.  Allows bulk insertion of glyphs.

- (void)insertGlyph:(NSGlyph)glyph atGlyphIndex:(NSUInteger)glyphIndex characterIndex:(NSUInteger)charIndex;
    // Inserts a single glyph into the glyph stream at glyphIndex.  The character index which this glyph corresponds to is given by charIndex.

- (void)replaceGlyphAtIndex:(NSUInteger)glyphIndex withGlyph:(NSGlyph)newGlyph;
    // Replaces the glyph currently at glyphIndex with newGlyph.  The character index of the glyph is assumed to remain the same (although it can, of course, be set explicitly if needed).

- (void)deleteGlyphsInRange:(NSRange)glyphRange;
    // Removes all glyphs in the given range from the storage.

- (void)setCharacterIndex:(NSUInteger)charIndex forGlyphAtIndex:(NSUInteger)glyphIndex;
    // Sets the index of the corresponding character for the glyph at the given glyphIndex.  The glyph must already be present.  This is intended for use in the cases where the mapping between characters and glyphs is not one-to-one, and should not be called in the normal case.

- (void)setIntAttribute:(NSInteger)attributeTag value:(NSInteger)val forGlyphAtIndex:(NSUInteger)glyphIndex;
    // Part of the NSGlyphStorage protocol, for use by the glyph generator.  Allows the glyph generator to set attributes.  It is not usually necessary for anyone but the glyph generator (and perhaps the typesetter) to call it.  It is provided as a public method so subclassers can extend it to accept other glyph attributes.  To add new glyph attributes to the text system you must do two things.  First, you need to arrange for the glyph generator and/or typesetter to generate and interpret it.  Second, you need to subclass NSLayoutManager to provide someplace to store the new attribute, overriding this method and -intAttribute:forGlyphAtIndex: to recognize the new attribute tags and respond to them, while passing any other attributes to the superclass's implementation.  NSLayoutManager's implementation understands the glyph attributes which it is prepared to store, as enumerated above.

- (void)invalidateGlyphsOnLayoutInvalidationForGlyphRange:(NSRange)glyphRange NS_AVAILABLE_MAC(10_5);
    // Used by the typesetter to indicate that the glyphs in the given range depend on layout, and so should be invalidated the next time their layout is invalidated, and therefore regenerated when relayout occurs.

/************************ Get glyphs and glyph attributes ************************/

- (NSUInteger)numberOfGlyphs;
    // Returns the total number of glyphs.  If non-contiguous layout is not enabled, this will force generation of glyphs for all characters.

- (NSGlyph)glyphAtIndex:(NSUInteger)glyphIndex isValidIndex:(BOOL *)isValidIndex;
- (NSGlyph)glyphAtIndex:(NSUInteger)glyphIndex;
- (BOOL)isValidGlyphIndex:(NSUInteger)glyphIndex;
    // If non-contiguous layout is not enabled, these will cause generation of all glyphs up to and including glyphIndex.  The first glyphAtIndex variant returns NSNullGlyph if the requested index is out of the range (0, numberOfGlyphs), and optionally returns a flag indicating whether the requested index is in range.  The second glyphAtIndex variant raises a NSRangeError if the requested index is in range.

- (NSUInteger)characterIndexForGlyphAtIndex:(NSUInteger)glyphIndex;
    // If non-contiguous layout is not enabled, this will cause generation of all glyphs up to and including glyphIndex.  It will return the character index for the first character associated with the glyph at the specified index.

- (NSUInteger)glyphIndexForCharacterAtIndex:(NSUInteger)charIndex NS_AVAILABLE_MAC(10_5);
    // If non-contiguous layout is not enabled, this will cause generation of all glyphs up to and including those associated with the specified character.  It will return the glyph index for the first glyph associated with the character at the specified index.

- (NSInteger)intAttribute:(NSInteger)attributeTag forGlyphAtIndex:(NSUInteger)glyphIndex;
    // If non-contiguous layout is not enabled, this will cause generation of all glyphs up to and including glyphIndex.  It will return the value for the given glyph attribute at the glyph index specified.  This is primarily for the use of the glyph generator and typesetter.  Clients may override this method to return any custom glyph attributes they wish to support.  

- (NSUInteger)getGlyphsInRange:(NSRange)glyphRange glyphs:(NSGlyph *)glyphBuffer characterIndexes:(NSUInteger *)charIndexBuffer glyphInscriptions:(NSGlyphInscription *)inscribeBuffer elasticBits:(BOOL *)elasticBuffer;
- (NSUInteger)getGlyphsInRange:(NSRange)glyphRange glyphs:(NSGlyph *)glyphBuffer characterIndexes:(NSUInteger *)charIndexBuffer glyphInscriptions:(NSGlyphInscription *)inscribeBuffer elasticBits:(BOOL *)elasticBuffer bidiLevels:(unsigned char *)bidiLevelBuffer;
    // These two methods fill a passed-in buffer with a sequence of NSGlyphs.  They will also optionally fill other passed-in buffers with the character indexes, glyph inscriptions, elastic bits, and bidi levels corresponding to these glyphs.  They are intended primarily to allow the typesetter to obtain in bulk the glyphs and other information that it needs to perform layout.  These methods will include in the result all glyphs in the range, including NSNullGlyphs and not-shown glyphs.  They do not null-terminate the results.  Each pointer passed in should either be NULL, or else point to sufficient memory to hold glyphRange.length elements.  These methods return the number of glyphs filled in.
    
- (NSUInteger)getGlyphs:(NSGlyph *)glyphArray range:(NSRange)glyphRange;
    // This method fills the passed-in buffer with a sequence of NSGlyphs.  It does not include in the result any NSNullGlyphs or glyphs that otherwise are not shown, but does null-terminate the result.  The memory passed in to the function should be large enough for at least glyphRange.length+1 elements.  The actual number of glyphs filled into the array is returned (not counting the null-termination).

/************************ Set layout information ************************/

// These methods are fairly primitive.  They are intended for use by the typesetter during layout.  They do not cause any kind of invalidation to happen.  The glyphs being set must already exist.  This is not a hardship since the NSTypesetter will have had to ask for the actual glyphs already by the time it goes to set this, and asking for the glyphs causes the glyph to be generated if necessary.

- (void)setTextContainer:(NSTextContainer *)container forGlyphRange:(NSRange)glyphRange;
    // Associates the given container with the given range of glyphs.  This method should be called by the typesetter first, before setting line fragment rect or any of the layout bits, for each range of glyphs it lays out.  This method will reset several key layout attributes (like not shown and draws outside line fragment) to their default values.  In the course of layout, all glyphs should end up being included in a range passed to this method.  The range passed in is not expected to be the entire range of glyphs for that text container; usually, in fact, it will be the range for a given line fragment being laid out in that container.

- (void)setLineFragmentRect:(NSRect)fragmentRect forGlyphRange:(NSRange)glyphRange usedRect:(NSRect)usedRect;
    // Associates the given line fragment bounds with the given range of glyphs.  The typesetter should call this method second, after setting the line fragment rect and before setting the location or any of the layout bits.  In the course of layout, all glyphs should end up being included in a range passed to this method, but only glyphs which start a new line fragment should be at the start of such ranges.  Line fragment rects and line fragment used rects are always in container coordinates.

- (void)setExtraLineFragmentRect:(NSRect)fragmentRect usedRect:(NSRect)usedRect textContainer:(NSTextContainer *)container;
    // Sets the bounds and container for the extra line fragment.  The extra line fragment is used when the text backing ends with a hard line break or when the text backing is totally empty, to define the extra line which needs to be displayed at the end of the text.  If the text backing is not empty and does not end with a hard line break, this should be set to NSZeroRect and nil.  Line fragment rects and line fragment used rects are always in container coordinates.

- (void)setLocation:(NSPoint)location forStartOfGlyphRange:(NSRange)glyphRange;
    // Sets the location for the first glyph of the given range.  Setting the location for a glyph range implies that its first glyph is not nominally spaced with respect to the previous glyph.  In the course of layout, all glyphs should end up being included in a range passed to this method, but only glyphs which start a new nominal range should be at the start of such ranges.  The first glyph in a line fragment should always start a new nominal range.  Glyph locations are given relative to their line fragment rect's origin.

- (void)setLocations:(NSPointArray)locations startingGlyphIndexes:(NSUInteger *)glyphIndexes count:(NSUInteger)count forGlyphRange:(NSRange)glyphRange NS_AVAILABLE_MAC(10_5);
    // Allows the typesetter to set locations for glyph ranges in bulk.  All of the glyph indexes should lie within the specified glyph range, the first of them should be equal to glyphRange.location, and the remainder should increase monotonically.  Each location will be set as the location for the range beginning at the corresponding glyph index, and continuing until the subsequent glyph index, or until the end of the glyph range for the last location.  Thus this method is equivalent to calling setLocation:forStartOfGlyphRange: for a set of ranges covering all of the glyphs in glyphRange.

- (void)setNotShownAttribute:(BOOL)flag forGlyphAtIndex:(NSUInteger)glyphIndex;
    // Some glyphs are not shown.  The typesetter decides which ones and sets this attribute in the layout manager to ensure that those glyphs will not be displayed.

- (void)setDrawsOutsideLineFragment:(BOOL)flag forGlyphAtIndex:(NSUInteger)glyphIndex;
    // Used to indicate that a particular glyph for some reason will draw outside of its line fragment rect.  This can commonly happen if a fixed line height is used (consider a 12 point line height and a 24 point glyph).  This information is important for determining whether additional lines need to be redrawn as a result of changes to any given line fragment.

- (void)setAttachmentSize:(NSSize)attachmentSize forGlyphRange:(NSRange)glyphRange;
   // For a glyph corresponding to an attachment, this method should be called to set the size the attachment cell will occupy.  The glyph's value should be NSControlGlyph.

/************************ Get layout information ************************/

// These three methods are used to inquire about the state of layout.  They cause no generation.

- (void)getFirstUnlaidCharacterIndex:(NSUInteger *)charIndex glyphIndex:(NSUInteger *)glyphIndex;
- (NSUInteger)firstUnlaidCharacterIndex;
- (NSUInteger)firstUnlaidGlyphIndex;
    // Returns (by reference for the "get" method) the character index or glyph index or both of the first unlaid character/glyph in the layout manager at this time.

// Except as otherwise indicated, these methods will cause glyph generation and layout as needed.

- (NSTextContainer *)textContainerForGlyphAtIndex:(NSUInteger)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
    // Returns the container in which the given glyph is laid and (optionally) by reference the whole range of glyphs that are in that container.  This will cause glyph generation and layout for the line fragment containing the specified glyph, or if non-contiguous layout is not enabled, up to and including that line fragment; if non-contiguous layout is not enabled and effectiveGlyphRange is non-NULL, this will additionally cause glyph generation and layout for the entire text container containing the specified glyph.

- (NSRect)usedRectForTextContainer:(NSTextContainer *)container;
    // Returns the container's currently used area.  This determines the size that the view would need to be in order to display all the glyphs that are currently laid into the container.  This causes neither glyph generation nor layout.  Used rects are always in container coordinates.

- (NSRect)lineFragmentRectForGlyphAtIndex:(NSUInteger)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
    // Returns the rect for the line fragment in which the given glyph is laid and (optionally) by reference the whole range of glyphs that are in that fragment.  This will cause glyph generation and layout for the line fragment containing the specified glyph, or if non-contiguous layout is not enabled, up to and including that line fragment.  Line fragment rects are always in container coordinates.

- (NSRect)lineFragmentUsedRectForGlyphAtIndex:(NSUInteger)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
    // Returns the usage rect for the line fragment in which the given glyph is laid and (optionally) by reference the whole range of glyphs that are in that fragment.  This will cause glyph generation and layout for the line fragment containing the specified glyph, or if non-contiguous layout is not enabled, up to and including that line fragment.  Line fragment used rects are always in container coordinates.

- (NSRect)lineFragmentRectForGlyphAtIndex:(NSUInteger)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange withoutAdditionalLayout:(BOOL)flag;
- (NSRect)lineFragmentUsedRectForGlyphAtIndex:(NSUInteger)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange withoutAdditionalLayout:(BOOL)flag;
- (NSTextContainer *)textContainerForGlyphAtIndex:(NSUInteger)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange withoutAdditionalLayout:(BOOL)flag;
    // If flag is YES, the withoutAdditionalLayout variants will not generate glyphs or perform layout in attempting to answer, so should not be used unless layout is known to be complete for the range in question, or unless non-contiguous layout is enabled.  Primarily for use from within NSTypesetter, after layout is complete for the range in question, but before the layout manager's call to NSTypesetter has returned.  In that case glyph and layout holes have not yet been recalculated, so the layout manager does not yet know that layout is complete for that range, and the withoutAdditionalLayout variants must be used.  Line fragment rects and line fragment used rects are always in container coordinates.  Note that in each case the method variants with and without the withoutAdditionalLayout argument are both primitive, and those overriding one should override the other.

- (NSRect)extraLineFragmentRect;
- (NSRect)extraLineFragmentUsedRect;
- (NSTextContainer *)extraLineFragmentTextContainer;
    // Return info about the extra line fragment.  Line fragment rects and line fragment used rects are always in container coordinates.

- (NSPoint)locationForGlyphAtIndex:(NSUInteger)glyphIndex;
    // Returns the location for the given glyph within its line fragment.  If this glyph does not have an explicit location set for it (i.e., it is part of (but not first in) a sequence of nominally spaced characters), the location is calculated by glyph advancements from the location of the most recent preceding glyph with a location set.  Glyph locations are relative to their line fragment rect's origin.  This will cause glyph generation and layout for the line fragment containing the specified glyph, or if non-contiguous layout is not enabled, up to and including that line fragment.

- (BOOL)notShownAttributeForGlyphAtIndex:(NSUInteger)glyphIndex;
    // Some glyphs are not shown.  This method returns whether the given glyph has been designated as not shown.  This will cause glyph generation and layout for the line fragment containing the specified glyph, or if non-contiguous layout is not enabled, up to and including that line fragment.

- (BOOL)drawsOutsideLineFragmentForGlyphAtIndex:(NSUInteger)glyphIndex;
    // Returns whether the glyph will draw outside of its line fragment rect.  This will cause glyph generation and layout for the line fragment containing the specified glyph, or if non-contiguous layout is not enabled, up to and including that line fragment.

- (NSSize)attachmentSizeForGlyphAtIndex:(NSUInteger)glyphIndex;
    // For a glyph corresponding to an attachment, this method returns the size the attachment cell will occupy.  Returns {-1,-1} if no attachment size has been set for the specified glyph.

/************************** Block information **************************/

- (void)setLayoutRect:(NSRect)rect forTextBlock:(NSTextBlock *)block glyphRange:(NSRange)glyphRange;
- (void)setBoundsRect:(NSRect)rect forTextBlock:(NSTextBlock *)block glyphRange:(NSRange)glyphRange;
- (NSRect)layoutRectForTextBlock:(NSTextBlock *)block glyphRange:(NSRange)glyphRange;
- (NSRect)boundsRectForTextBlock:(NSTextBlock *)block glyphRange:(NSRange)glyphRange;
    // Used to set and get information about layout of text blocks.  These methods cause glyph generation but not layout.  The latter two will return NSZeroRect if no rect has been set for the specified block and range since the last invalidation.  Block layout rects and bounds rects are always in container coordinates.
- (NSRect)layoutRectForTextBlock:(NSTextBlock *)block atIndex:(NSUInteger)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
- (NSRect)boundsRectForTextBlock:(NSTextBlock *)block atIndex:(NSUInteger)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
    // Similar to the above, but they can be passed any index in the range and will return the range by reference if effectiveGlyphRange is not NULL.

/************************ More sophisticated queries ************************/

// These two methods can cause glyph generation.

- (NSRange)glyphRangeForCharacterRange:(NSRange)charRange actualCharacterRange:(NSRangePointer)actualCharRange;
    // Returns the range of glyphs that are generated from the characters in the given charRange.  If actualCharRange is not NULL, it will return by reference the actual range of characters that fully define the glyph range returned.  This range may be identical to or slightly larger than the requested character range.  For example, if the text storage contains the characters "o" and (umlaut) and the glyph store contains the single precomposed glyph (o-umlaut), and if the character range given encloses only the first or second character, then actualCharRange will be set to enclose both characters.  If the length of charRange is zero, the resulting glyph range will be a zero-length range just after the glyph(s) corresponding to the preceding character, and actualCharRange will also be zero-length.  If non-contiguous layout is not enabled, this will force the generation of glyphs for all characters up to and including the end of the specified range.

- (NSRange)characterRangeForGlyphRange:(NSRange)glyphRange actualGlyphRange:(NSRangePointer)actualGlyphRange;
    // Returns the range of characters that generated the glyphs in the given glyphRange.  If actualGlyphRange is not NULL, it will return by reference the full range of glyphs generated by the character range returned.  This range may be identical or slightly larger than the requested glyph range.  For example, if the text storage contains the character (o-umlaut) and the glyph store contains the two atomic glyphs "o" and (umlaut), and if the glyph range given encloses only the first or second glyph, then actualGlyphRange will be set to enclose both glyphs.  If the length of glyphRange is zero, the resulting character range will be a zero-length range just after the character(s) corresponding to the preceding glyph, and actualGlyphRange will also be zero-length.  If non-contiguous layout is not enabled, this will force the generation of glyphs for all characters up to and including the end of the returned range.

// All of these methods can cause glyph generation and layout.  If non-contiguous layout is not enabled, they will cause generation and layout for all glyphs up to and including the last glyph referenced.  If non-contiguous layout is enabled, they will cause generation and layout for a much smaller set of glyphs, and ensureGlyphs... or ensureLayout... methods should be used to force generation or layout.

- (NSRange)glyphRangeForTextContainer:(NSTextContainer *)container;
    // Returns the range of characters which have been laid into the given container.  This is a less efficient method than the similar -textContainerForGlyphAtIndex:effectiveRange:.

- (NSRange)rangeOfNominallySpacedGlyphsContainingIndex:(NSUInteger)glyphIndex;
    // Returns the range including the first glyph from glyphIndex on back that has a location set and up to, but not including the next glyph that has a location set.
    
- (NSRectArray)rectArrayForCharacterRange:(NSRange)charRange withinSelectedCharacterRange:(NSRange)selCharRange inTextContainer:(NSTextContainer *)container rectCount:(NSUInteger *)rectCount;
- (NSRectArray)rectArrayForGlyphRange:(NSRange)glyphRange withinSelectedGlyphRange:(NSRange)selGlyphRange inTextContainer:(NSTextContainer *)container rectCount:(NSUInteger *)rectCount;
    // Returns an array of NSRects and the number of rects by reference which define the region in container that encloses the given range.  If a selected range is given in the second argument, the rectangles returned will be correct for drawing the selection.  Selection rectangles are generally more complicated than enclosing rectangles and supplying a selected range is the clue these methods use to determine whether to go to the trouble of doing this special work. 
    // If the caller is interested in this more from an enclosing point of view rather than a selection point of view, pass {NSNotFound, 0} as the selected range.  This method will do the minimum amount of work required to answer the question.  The resulting array is owned by the layoutManager and will be reused when either of these two methods OR -boundingRectForGlyphRange:inTextContainer: is called.  Note that one of these methods may be called indirectly.  The upshot is that if you aren't going to use the rects right away, you should copy them to another location.  These rects are always in container coordinates.

- (NSRect)boundingRectForGlyphRange:(NSRange)glyphRange inTextContainer:(NSTextContainer *)container;
    // Returns the smallest bounding rect which completely encloses the glyphs in the given glyphRange that are in the given container.  The range is intersected with the container's range before computing the bounding rect.  This method can be used to translate glyph ranges into display rectangles for invalidation.  Bounding rects are always in container coordinates.

- (NSRange)glyphRangeForBoundingRect:(NSRect)bounds inTextContainer:(NSTextContainer *)container;
- (NSRange)glyphRangeForBoundingRectWithoutAdditionalLayout:(NSRect)bounds inTextContainer:(NSTextContainer *)container;
    // Returns a contiguous glyph range containing all glyphs that would need to be displayed in order to draw all glyphs that fall (even partially) within the bounding rect given.  This range might include glyphs which do not fall into the rect at all.  At most this will return the glyph range for the whole container.  The WithoutAdditionalLayout variant will not generate glyphs or perform layout in attempting to answer, and thus may not be entirely correct.  Bounding rects are always in container coordinates.

- (NSUInteger)glyphIndexForPoint:(NSPoint)point inTextContainer:(NSTextContainer *)container fractionOfDistanceThroughGlyph:(CGFloat *)partialFraction;
- (NSUInteger)glyphIndexForPoint:(NSPoint)point inTextContainer:(NSTextContainer *)container;
- (CGFloat)fractionOfDistanceThroughGlyphForPoint:(NSPoint)point inTextContainer:(NSTextContainer *)container;
    // Returns the index of the glyph falling under the given point, expressed in the given container's coordinate system.  If no glyph is under the point, the nearest glyph is returned, where nearest is defined according to the requirements of selection by mouse.  Clients who wish to determine whether the the point actually lies within the bounds of the glyph returned should follow this with a call to boundingRectForGlyphRange:inTextContainer: and test whether the point falls in the rect returned by that method.  If partialFraction is non-NULL, it will return by reference the fraction of the distance between the location of the glyph returned and the location of the next glyph. 

- (NSUInteger)characterIndexForPoint:(NSPoint)point inTextContainer:(NSTextContainer *)container fractionOfDistanceBetweenInsertionPoints:(CGFloat *)partialFraction NS_AVAILABLE_MAC(10_6);
    // Returns the index of the character falling under the given point, expressed in the given container's coordinate system.  If no character is under the point, the nearest character is returned, where nearest is defined according to the requirements of selection by mouse.  This is not simply equivalent to taking the result of the corresponding glyph index method and converting it to a character index, because in some cases a single glyph represents more than one selectable character, for example an fi ligature glyph.  In that case, there will be an insertion point within the glyph, and this method will return one character or the other, depending on whether the specified point lies to the left or the right of that insertion point.  In general, this method will return only character indexes for which there is an insertion point (see next method).  The partial fraction is a fraction of the distance from the insertion point logically before the given character to the next one, which may be either to the right or to the left depending on directionality.

- (NSUInteger)getLineFragmentInsertionPointsForCharacterAtIndex:(NSUInteger)charIndex alternatePositions:(BOOL)aFlag inDisplayOrder:(BOOL)dFlag positions:(CGFloat *)positions characterIndexes:(NSUInteger *)charIndexes NS_AVAILABLE_MAC(10_5);
    // Allows clients to obtain all insertion points for a line fragment in one call.  The caller specifies the line fragment by supplying one character index within it, and can choose whether to obtain primary or alternate insertion points, and whether they should be in logical or in display order.  The return value is the number of insertion points returned.  Each pointer passed in should either be NULL, or else point to sufficient memory to hold as many elements as there are insertion points in the line fragment (which cannot be more than the number of characters + 1).  The positions buffer passed in will be filled in with the positions of the insertion points, in the order specified, and the charIndexes buffer passed in will be filled in with the corresponding character indexes.  Positions indicate a transverse offset relative to the line fragment rect's origin.  Internal caching is used to ensure that repeated calls to this method for the same line fragment (possibly with differing values for other arguments) will not be significantly more expensive than a single call.

/************************ Temporary attribute support ************************/

- (NSDictionary *)temporaryAttributesAtCharacterIndex:(NSUInteger)charIndex effectiveRange:(NSRangePointer)effectiveCharRange;
- (void)setTemporaryAttributes:(NSDictionary *)attrs forCharacterRange:(NSRange)charRange;
- (void)addTemporaryAttributes:(NSDictionary *)attrs forCharacterRange:(NSRange)charRange;
- (void)removeTemporaryAttribute:(NSString *)attrName forCharacterRange:(NSRange)charRange;
    // Temporary attributes provide a way to override attributes for drawing on a per-layout manager basis, without affecting the underlying stored text.  Clients may set any attributes they wish, but the only attributes that the layout manager will recognize for drawing are those that do not affect layout (color, underline, etc.). 

- (id)temporaryAttribute:(NSString *)attrName atCharacterIndex:(NSUInteger)location effectiveRange:(NSRangePointer)range NS_AVAILABLE_MAC(10_5);
- (id)temporaryAttribute:(NSString *)attrName atCharacterIndex:(NSUInteger)location longestEffectiveRange:(NSRangePointer)range inRange:(NSRange)rangeLimit NS_AVAILABLE_MAC(10_5);
- (NSDictionary *)temporaryAttributesAtCharacterIndex:(NSUInteger)location longestEffectiveRange:(NSRangePointer)range inRange:(NSRange)rangeLimit NS_AVAILABLE_MAC(10_5);
- (void)addTemporaryAttribute:(NSString *)attrName value:(id)value forCharacterRange:(NSRange)charRange NS_AVAILABLE_MAC(10_5);
    // A more complete set of temporary attribute methods is available starting in 10.5.

/******************************* Font handling ******************************/

- (NSFont *)substituteFontForFont:(NSFont *)originalFont;
    // Returns a font to use in place of originalFont.  This method is used to substitute screen fonts for regular fonts.  If the layout manager uses screen fonts and a screen font is available for originalFont, it is returned, otherwise originalFont is returned.

- (CGFloat)defaultLineHeightForFont:(NSFont *)theFont;
    // Returns the default line height specified by the layout manager's typesetter behavior for the given font.
- (CGFloat)defaultBaselineOffsetForFont:(NSFont *)theFont;
    // Returns the default baseline offset specified by the layout manager's typesetter behavior for the given font.
- (BOOL)usesFontLeading;
- (void)setUsesFontLeading:(BOOL)flag;
    // By default, a layout manager will use leading as specified by the font.  However, this is not appropriate for most UI text, for which a fixed leading is usually specified by UI layout guidelines.  These methods allow the use of the font's leading to be turned off.

@end

@interface NSLayoutManager (NSTextViewSupport)

/***************************** Ruler support *****************************/

- (NSArray *)rulerMarkersForTextView:(NSTextView *)view paragraphStyle:(NSParagraphStyle *)style ruler:(NSRulerView *)ruler;
- (NSView *)rulerAccessoryViewForTextView:(NSTextView *)view paragraphStyle:(NSParagraphStyle *)style ruler:(NSRulerView *)ruler enabled:(BOOL)isEnabled;
    // These return, respectively, an array of text ruler objects for the current selection, and the accessory view that the text system uses for its ruler.  If you have turned off automatic ruler updating through the use of setUsesRulers: so that you can do more complex things, but you still want to display the appropriate text ruler objects and/or accessory view, you can use these methods.

/************************ First responder support ************************/

- (BOOL)layoutManagerOwnsFirstResponderInWindow:(NSWindow *)window;
    // Returns YES if the firstResponder of the given window is one of the NSTextViews attached to this NSLayoutManager.

- (NSTextView *)firstTextView;

- (NSTextView *)textViewForBeginningOfSelection;
    // This method is special in that it won't cause layout if the beginning of the selected range is not yet laid out.  Other than that this method could be done through other API.

/************************ Drawing support ************************/

- (void)drawBackgroundForGlyphRange:(NSRange)glyphsToShow atPoint:(NSPoint)origin;
- (void)drawGlyphsForGlyphRange:(NSRange)glyphsToShow atPoint:(NSPoint)origin;
    // These methods are called by NSTextView for drawing.  You can override these to perform additional drawing, or to replace text drawing entirely, but not to change layout.  You can call them if you want, but focus must already be locked on the destination view or image.  -drawBackgroundForGlyphRange:atPoint: draws the background color and selection and marked range aspects of the text display, along with block decoration such as table backgrounds and borders.  -drawGlyphsForGlyphRange:atPoint: draws the actual glyphs, including attachments, as well as any underlines or strikethoughs.  In either case all of the specified glyphs must lie in a single container.  The origin point in either method is that container's origin in the currently focused view's coordinates.

- (void)showCGGlyphs:(const CGGlyph *)glyphs positions:(const NSPoint *)positions count:(NSUInteger)glyphCount font:(NSFont *)font matrix:(NSAffineTransform *)textMatrix attributes:(NSDictionary *)attributes inContext:(NSGraphicsContext *)graphicsContext NS_AVAILABLE_MAC(10_7);
    // The new glyph rendering primitive method replacing -showPackedGlyphs:length:glyphRange:atFont:color:printingAdjustment:.  Renders glyphs at positions into the graphicsContext.  The positions are in the user space coordinate system.  If non-nil, graphicsContext that passed in is already configured according to the text attributes arguments: font, textMatrix, and attributes.  The font argument represents the font applied to the graphics state.  The value can be different from the NSFontAttributeName value in the attributes argument because of various font substitutions that the system automatically executes.  The textMatrix is the affine transform mapping the text space coordinate system to the user space coordinate system.  The tx and ty components of textMatrix are ignored since Quartz overrides them with the glyph positions.  NSLayoutManager invokes this new primitive method unless an override implementation of -showPackagedGlyphs:... and no override for this method existed.

- (void)showPackedGlyphs:(char *)glyphs length:(NSUInteger)glyphLen glyphRange:(NSRange)glyphRange atPoint:(NSPoint)point font:(NSFont *)font color:(NSColor *)color printingAdjustment:(NSSize)printingAdjustment NS_DEPRECATED_MAC(10_0, 10_7);
    // This was the primitive for drawing a range of glyphs before Mac OS X 10.7.  It is now deprecated and replaced by the -showCGGlyphs:... method above.  The glyphRange, point, font, and color are passed in merely for information purposes.  They will all be set already in the graphics state.  If for any reason you modify the set color or font, you must restore it before returning from this method.  You should never call this method, but you might override it.  printingAdjustment will be NSZeroSize when drawing to the screen, but when printing this may contain values by which the nominal spacing between the characters should be adjusted.  The length argument (glyphLen) is the number of bytes pointed at by the glyphs argument; this will be twice the number of glyphs contained.  Note that the glyphs array may contain embedded NULLs.
    
- (void)showAttachmentCell:(NSCell *)cell inRect:(NSRect)rect characterIndex:(NSUInteger)attachmentIndex;
   // This is the primitive for actually drawing an attachment cell.  The attachment should be drawn within the given rect.  The character index is provided for those cells that alter their appearance based on their location.

- (void)fillBackgroundRectArray:(NSRectArray)rectArray count:(NSUInteger)rectCount forCharacterRange:(NSRange)charRange color:(NSColor *)color NS_AVAILABLE_MAC(10_6);
   // This is the primitive used by -drawBackgroundForGlyphRange:atPoint: for actually filling rects with a particular background color, whether due to a background color attribute, a selected or marked range highlight, a block decoration, or any other rect fill needed by that method.  As with -showPackedGlyphs:..., the character range and color are merely for informational purposes; the color will already be set in the graphics state.  If for any reason you modify it, you must restore it before returning from this method.  You should never call this method, but you might override it.  The default implementation will simply fill the specified rect array.

- (void)drawUnderlineForGlyphRange:(NSRange)glyphRange underlineType:(NSInteger)underlineVal baselineOffset:(CGFloat)baselineOffset lineFragmentRect:(NSRect)lineRect lineFragmentGlyphRange:(NSRange)lineGlyphRange containerOrigin:(NSPoint)containerOrigin;
- (void)underlineGlyphRange:(NSRange)glyphRange underlineType:(NSInteger)underlineVal lineFragmentRect:(NSRect)lineRect lineFragmentGlyphRange:(NSRange)lineGlyphRange containerOrigin:(NSPoint)containerOrigin;
    // The first of these methods actually draws an appropriate underline for the glyph range given.  The second method potentially breaks the range it is given up into subranges and calls drawUnderline... for ranges that should actually have the underline drawn.  As examples of why there are two methods, consider two situations.  First, in all cases you don't want to underline the leading and trailing whitespace on a line.  The -underlineGlyphRange... method is passed glyph ranges that have underlining turned on, but it will then look for this leading and trailing white space and only pass the ranges that should actually be underlined to -drawUnderline...  Second, if the underlineType: indicates that only words, (i.e., no whitespace), should be underlined, then -underlineGlyphRange... will carve the range it is passed up into words and only pass word ranges to -drawUnderline.

- (void)drawStrikethroughForGlyphRange:(NSRange)glyphRange strikethroughType:(NSInteger)strikethroughVal baselineOffset:(CGFloat)baselineOffset lineFragmentRect:(NSRect)lineRect lineFragmentGlyphRange:(NSRange)lineGlyphRange containerOrigin:(NSPoint)containerOrigin;
- (void)strikethroughGlyphRange:(NSRange)glyphRange strikethroughType:(NSInteger)strikethroughVal lineFragmentRect:(NSRect)lineRect lineFragmentGlyphRange:(NSRange)lineGlyphRange containerOrigin:(NSPoint)containerOrigin;
    // These two methods parallel the two corresponding underline methods, but draw strikethroughs instead of underlines.

@end

@protocol NSLayoutManagerDelegate <NSObject>
@optional
- (void)layoutManagerDidInvalidateLayout:(NSLayoutManager *)sender;
    // This is sent whenever layout or glyphs become invalidated in a layout manager which previously had all layout complete.

- (void)layoutManager:(NSLayoutManager *)layoutManager didCompleteLayoutForTextContainer:(NSTextContainer *)textContainer atEnd:(BOOL)layoutFinishedFlag;
    // This is sent whenever a container has been filled.  This method can be useful for paginating.  The textContainer might be nil if we have completed all layout and not all of it fit into the existing containers.  The atEnd flag indicates whether all layout is complete.

- (NSDictionary *)layoutManager:(NSLayoutManager *)layoutManager shouldUseTemporaryAttributes:(NSDictionary *)attrs forDrawingToScreen:(BOOL)toScreen atCharacterIndex:(NSUInteger)charIndex effectiveRange:(NSRangePointer)effectiveCharRange NS_AVAILABLE_MAC(10_5);
    // This is sent when the layout manager is drawing and needs to decide whether to use temporary attributes or not.  The delegate returns a dictionary of temporary attributes to be used, or nil to suppress the use of temporary attributes altogether.  The effectiveCharRange argument is both an in and out by-reference effective range for those attributes.  The default behavior if this method is not implemented is to use temporary attributes only when drawing to the screen, so an implementation to match that behavior would return attrs if toScreen is YES and nil otherwise, without changing effectiveCharRange.

@end
