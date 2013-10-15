/*
        NSLayoutManager.h
        Application Kit
        Copyright (c) 1994-2005, Apple Computer, Inc.
        All rights reserved.
*/

// An NSLayoutManager stores glyphs, attributes, and layout information generated from a NSTextStorage by a NSTextLayout.  It can map between ranges of unichars in the NSTextStorage and ranges of glyphs within itself.  It understands and keeps track of two types of range invalidation.  A character range can need glyphs generated for it or it can need its glyphs laid out.  
// When a NSLayoutManager is asked for information which would require knowledge of glyphs or layout which is not currently available, the NSLayoutManager must cause the appropriate recalculation to be done.

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

// These glyph attributes are used only inside the glyph generation machinery, but must be shared between components.
enum _NSGlyphAttribute {
    NSGlyphAttributeSoft = 0,
    NSGlyphAttributeElastic = 1,
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
    NSGlyphAttributeBidiLevel = 2,
#endif
    NSGlyphAttributeInscribe = 5
};

// The inscribe attribute of a glyph determines how it is laid out relative to the previous glyph.
typedef enum {
    NSGlyphInscribeBase = 0,
    NSGlyphInscribeBelow = 1,
    NSGlyphInscribeAbove = 2,
    NSGlyphInscribeOverstrike = 3,
    NSGlyphInscribeOverBelow = 4
} NSGlyphInscription;

/* The typesetting behavior (compatibility setting) values.
*/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
typedef enum {
    NSTypesetterLatestBehavior = -1,
    NSTypesetterOriginalBehavior = 0, // Mac OS X ver 10.0 and 10.1 (uses NSSimpleHorizontalTypesetter)
    NSTypesetterBehavior_10_2_WithCompatibility = 1, // 10.2 with backward compatibility layout (uses new ATS-based typestter)
    NSTypesetterBehavior_10_2 = 2,
    NSTypesetterBehavior_10_3 = 3
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    , NSTypesetterBehavior_10_4 = 4
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
} NSTypesetterBehavior;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
@interface NSLayoutManager : NSObject <NSCoding, NSGlyphStorage> {
#else
@interface NSLayoutManager : NSObject <NSCoding> {
#endif

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

        unsigned int _pad:2;
    } _lmFlags;

    id _delegate;

    // Enable/disable stacks
    unsigned short _textViewResizeDisableStack;
    unsigned short _displayInvalidationDisableStack;
    NSRange _deferredDisplayCharRange;

    // Cache for first text view (that is text view of the first text container which has one) (Cost: 4 bytes)
    NSTextView *_firstTextView;

    // Cache for rectangle arrays (Cost: 8 bytes + malloced 16 * <max number of rects returned in an array> bytes)
    NSRect *_cachedRectArray;
    unsigned _cachedRectArrayCapacity;

    // Cache for glyph strings (used when drawing) (Cost: 8 bytes + malloced glyph buffer size)
    char *_glyphBuffer;
    unsigned _glyphBufferSize;

    // Cache for faster glyph location lookup (Cost: 20 bytes)
    NSRange _cachedLocationNominalGlyphRange;
    unsigned _cachedLocationGlyphIndex;
    NSPoint _cachedLocation;

    // Cache for faster glyph location lookup (Cost: 12 bytes)
    NSRange _cachedFontCharRange;
    NSFont *_cachedFont;

    // Cache for first unlaid glypha and character (Cost: 8 bytes)
    unsigned _firstUnlaidGlyphIndex;
    unsigned _firstUnlaidCharIndex;

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
    // Designated Initializer.  Sets up this instance.  Finds the shared NSGlyphGenerator and the shared default NSTypesetter.  The NSLayoutManager starts off without an NSTextStorage

/*************************** Helper objects ***************************/

- (NSTextStorage *)textStorage;
- (void)setTextStorage:(NSTextStorage *)textStorage;
    // The set method generally should not be called directly, but you may want to override it.  Used to get and set the text storage.  The set method is called by the NSTextStorage's addLayoutManager:/removeLayoutManager: methods.

- (void)replaceTextStorage:(NSTextStorage *)newTextStorage;
    // This method should be used instead of the primitive -setTextStorage: if you need to replace a NSLayoutManager's NSTextStorage with a new one leaving the rest of the web intact.  This method deals with all the work of making sure the NSLayoutManager doesn't get deallocated and transferring all the NSLayoutManagers on the old NSTextStorage to the new one.
    
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSGlyphGenerator *)glyphGenerator;
- (void)setGlyphGenerator:(NSGlyphGenerator *)glyphGenerator;
    // Setting glyph generator invalidates all glyphs and layout in the NSLayoutManager.
#endif

- (NSTypesetter *)typesetter;
- (void)setTypesetter:(NSTypesetter *)typesetter;
    // Setting the typesetter invalidates all glyphs in the NSLayoutManager.  It can't just invalidate layout because the typesetter may have contributed to the actual glyphs as well (e.g. hyphenation).

- (id)delegate;
- (void)setDelegate:(id)delegate;
    // Sets or gets the NSLayoutManager's delegate.

/**************************** Containers ****************************/

- (NSArray *)textContainers;

- (void)addTextContainer:(NSTextContainer *)container;
    // Add a container to the end of the array.  Must invalidate layout of all glyphs after the previous last container (i.e., glyphs that were not previously laid out because they would not fit anywhere).
- (void)insertTextContainer:(NSTextContainer *)container atIndex:(unsigned)index;
    // Insert a container into the array before the container at index.  Must invalidate layout of all glyphs in the containers from the one previously at index to the last container.
- (void)removeTextContainerAtIndex:(unsigned)index;
    // Removes the container at index from the array.  Must invalidate layout of all glyphs in the container being removed and any containers which come after it.

- (void)textContainerChangedGeometry:(NSTextContainer *)container;
    // Invalidates layout of all glyphs in container and all subsequent containers.

- (void)textContainerChangedTextView:(NSTextContainer *)container;
    // Called by NSTextContainer whenever its textView changes.  Used to keep notifications in sync.

/************************** Invalidation primitives **************************/

- (void)invalidateGlyphsForCharacterRange:(NSRange)charRange changeInLength:(int)delta actualCharacterRange:(NSRangePointer)actualCharRange;
    // This removes all glyphs for the old character range, adjusts the character indices of all the subsequent glyphs by the change in length, and invalidates the new character range.  If actualCharRange is non-NULL it will be set to the actual range invalidated after any necessary expansion.

- (void)invalidateLayoutForCharacterRange:(NSRange)charRange isSoft:(BOOL)flag actualCharacterRange:(NSRangePointer)actualCharRange;
    // This invalidates the layout information (glyph location and rotation) for the given range of characters.  If flag is YES then this range is marked as a hard layout invalidation.  If NO, then the invalidation is soft.  A hard invalid layout range indicates that layout information must be completely recalculated no matter what.  A soft invalid layout range means that there is already old layout info for the range in question, and if the NSLayoutManager is smart enough to figure out how to avoid doing the complete relayout, it may perform any optimization available.  If actualCharRange is non-NULL it will be set to the actual range invalidated after any necessary expansion.

- (void)invalidateDisplayForGlyphRange:(NSRange)glyphRange;
- (void)invalidateDisplayForCharacterRange:(NSRange)charRange;
    // Invalidates display for the glyph or character range given.  For the glyph range variant any part of the range that does not yet have glyphs generated is ignored.  For the character range variant, unlaid parts of the range are remembered and will definitely be redisplayed at some point later when the layout is available.  Neither method actually causes layout.

/******************* Invalidation sent by NSTextStorage *******************/

- (void)textStorage:(NSTextStorage *)str edited:(unsigned)editedMask range:(NSRange)newCharRange changeInLength:(int)delta invalidatedRange:(NSRange)invalidatedCharRange;
    // Sent from processEditing in NSTextStorage. newCharRange is the range in the final string which was explicitly edited. invalidatedRange includes stuff which was changed as a result of attribute fixing. invalidatedRange is either equal to newCharRange or larger. Layout managers should not change the contents of the text storage during the execution of this message.

/*********************** Global layout manager options ***********************/

- (void)setBackgroundLayoutEnabled:(BOOL)flag;
- (BOOL)backgroundLayoutEnabled;
    // These methods allow you to set/query whether text gets laid out in the background when there's nothing else to do.

- (void)setShowsInvisibleCharacters:(BOOL)flag;
- (BOOL)showsInvisibleCharacters;
    // If YES, and the rulebooks and fonts in use support it, whitespace and other "invisible" unicodes will be shown with special glyphs (ie "." for space, the little CR icon for new lines, etc...)

- (void)setShowsControlCharacters:(BOOL)flag;
- (BOOL)showsControlCharacters;
    // If YES, and the rulebooks and fonts in use support it, control characters will be rendered visibly (usually like "^M", but possibly with special glyphs if the the font and rulebook supports it).

- (void)setHyphenationFactor:(float)factor;
- (float)hyphenationFactor;
    // 0.0 - 1.0. Whenever (width of the real contents of the line) / (the line fragment width) is below this value, hyphenation will be attempted when laying out the line. By default, the value is 0, meaning hyphenation is off. 1.0 causes hyphenation to be attempted always. Note that hyphenation will slow down text layout and increase memory usage, so it should be used sparingly.

- (void)setDefaultAttachmentScaling:(NSImageScaling)scaling;
- (NSImageScaling)defaultAttachmentScaling;
    // Specifies the default behavior desired if an attachment image is too large to fit in a text container.  Note that attachment cells control their own size and drawing, so this setting can only be advisory for them, but kit-supplied attachment cells will respect it. 

/************************ Adding and removing glyphs ************************/

// These methods are primitive.  They do not cause the bookkeeping of filling holes to happen.  They do not cause invalidation of other stuff.

- (void)insertGlyph:(NSGlyph)glyph atGlyphIndex:(unsigned)glyphIndex characterIndex:(unsigned)charIndex;
    // Inserts a single glyph into the glyph stream at glyphIndex.  The character index which this glyph corresponds to is given by charIndex.

- (void)replaceGlyphAtIndex:(unsigned)glyphIndex withGlyph:(NSGlyph)newGlyph;
    // Replaces the glyph currently at glyphIndex with newGlyph.  The character index of the glyph is assumed to remain the same (although it can, of course, be set explicitly if needed).

- (void)deleteGlyphsInRange:(NSRange)glyphRange;
    // Removes all glyphs in the given range from the storage.

- (void)setCharacterIndex:(unsigned)charIndex forGlyphAtIndex:(unsigned)glyphIndex;
    // Sets the index of the corresponding character for the glyph at the given glyphIndex.

/************************ Accessing glyphs ************************/

- (unsigned)numberOfGlyphs;
    // If there are any holes in the glyph stream, this will cause all invalid character ranges to have glyphs generated for them.

- (NSGlyph)glyphAtIndex:(unsigned)glyphIndex;
- (NSGlyph)glyphAtIndex:(unsigned)glyphIndex isValidIndex:(BOOL *)isValidIndex;
- (BOOL)isValidGlyphIndex:(unsigned)glyphIndex;
    // If there are any holes in the glyph stream this will cause glyph generation for all holes sequentially encountered until the desired index is available.  The first variant raises a NSRangeError if the requested index is out of bounds, the second does not, but instead optionally returns a flag indicating whether the requested index exists.
    // Java note:  glyphAtIndex:isValidIndex: is the primitive but is not exposed in Java.  Therefore it is not currently possible to ovverride this functionality properly from Java.


- (unsigned)getGlyphs:(NSGlyph *)glyphArray range:(NSRange)glyphRange;
    // This causes glyph generation similarly to asking for a single glyph.  It formats a sequence of NSGlyphs (unsigned long ints).  It does not include glyphs that aren't shown in the result but does zero-terminate the array.  The memory passed in to the function should be large enough for at least glyphRange.length+1 elements.  The actual number of glyphs stuck into the array is returned (not counting the null-termination).

- (unsigned)characterIndexForGlyphAtIndex:(unsigned)glyphIndex;
    // If there are any holes in the glyph stream this will cause glyph generation for all holes sequentially encountered until the desired index is available.

/************************ Set/Get glyph attributes ************************/

// This method is primitive.  It does not cause any invalidation of other stuff.  This method also will not cause glyph generation.  The glyph being set must already be there.

- (void)setIntAttribute:(int)attributeTag value:(int)val forGlyphAtIndex:(unsigned)glyphIndex;
    // This method is used by the NSGlyphGenerator to set attributes.  It is not usually necessary for anyone but the glyph generator (and perhaps the typesetter) to call it.  It is provided as a public method so subclassers can extend it to accept other glyph attributes.  To add new glyph attributes to the text system you basically need to do two things.  You need to write a rulebook which will generate the attributes (in rulebooks attributes are identified by integer tags).  Then you need to subclass NSLayoutManager to provide someplace to store the new attribute and to override this method and -attribute:forGlyphAtIndex: to understand the integer tag which your new rulebook is generating.  NSLayoutManager's implementation understands the glyph attributes which it is prepared to remember.  Your override should pass any glyph attributes it does not understand up to the superclass's implementation.

// This method will cause glyph generation as necessary to answer the question.

- (int)intAttribute:(int)attributeTag forGlyphAtIndex:(unsigned)glyphIndex;
    // This returns the value for the given glyph attribute at the glyph index specified.  Most apps will not have much use for this info but the typesetter and glyph generator might need to know about certain attributes.  You can override this method to know how to return any custom glyph attributes you want to support.

/************************ Set/Get layout attributes ************************/

// These methods are fairly primitive.  They do not cause any kind of invalidation to happen.  The glyphs being set must already exist.  This is not a hardship since the NSTypesetter will have had to ask for the actual glyphs already by the time it goes to set this, and asking for the glyphs causes the glyph to be generated if necessary.

- (void)setTextContainer:(NSTextContainer *)container forGlyphRange:(NSRange)glyphRange;
    // Associates the given container with the given range of glyphs.  This method should be called by the typesetter first (ie before setting line fragment rect or any of the layout bits) for each range of glyphs it lays out.  This method will set several key layout atttributes (like not shown and draws outside line fragment) to their default values.

- (void)setLineFragmentRect:(NSRect)fragmentRect forGlyphRange:(NSRange)glyphRange usedRect:(NSRect)usedRect;
    // Associates the given line fragment bounds with the given range of glyphs.

- (void)setExtraLineFragmentRect:(NSRect)fragmentRect usedRect:(NSRect)usedRect textContainer:(NSTextContainer *)container;
    // Sets the bounds and container for the extra line fragment.  The extra line fragment is used when the text backing ends with a hard line break or when the text backing is totally empty to define the extra line which needs to be displayed.  If the text backing does not end with a hard line break this should be set to NSZeroRect and nil.

- (void)setDrawsOutsideLineFragment:(BOOL)flag forGlyphAtIndex:(unsigned)glyphIndex;
    // Used to indicate that a particular glyph for some reason marks outside its line fragment bounding rect.  This can commonly happen if a fixed line height is used (consider a 12 point line height and a 24 point glyph).

- (void)setLocation:(NSPoint)location forStartOfGlyphRange:(NSRange)glyphRange;
    // Sets the location to draw the first glyph of the given range at.  Setting the location for a glyph range implies that its first glyph is NOT nominally spaced with respect to the previous glyph.  When all is said and done all glyphs in the layoutManager should have been included in a range passed to this method.  But only glyphs which start a new nominal range should be at the start of such ranges.  Glyph locations are given relative the their line fragment bounding rect's origin.

- (void)setNotShownAttribute:(BOOL)flag forGlyphAtIndex:(unsigned)glyphIndex;
    // Some glyphs are not shown.  The typesetter decides which ones and sets this attribute in layoutManager where the view can find it.

- (void)setAttachmentSize:(NSSize)attachmentSize forGlyphRange:(NSRange)glyphRange;
   // Sets the size the given glyph (assumed to be an attachment) will be asked to draw at.

- (NSTextContainer *)textContainerForGlyphAtIndex:(unsigned)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
    // Returns the container in which the given glyph is laid and (optionally) by reference the whole range of glyphs that are in that container.  This will cause glyph generation AND layout as needed.

- (NSRect)usedRectForTextContainer:(NSTextContainer *)container;
    // Returns the container's currently used area.  This is the size that the view would need to be in order to display all the stuff that is currently laid into the container.  This causes no generation.

- (NSRect)lineFragmentRectForGlyphAtIndex:(unsigned)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
    // Returns the rect for the line fragment in which the given glyph is laid and (optionally) by reference the whole range of glyphs that are in that fragment.  This will cause glyph generation AND layout as needed.

- (NSRect)lineFragmentUsedRectForGlyphAtIndex:(unsigned)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
    // Returns the usage rect for the line fragment in which the given glyph is laid and (optionally) by reference the whole range of glyphs that are in that fragment.  This will cause glyph generation AND layout as needed.

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSRect)lineFragmentRectForGlyphAtIndex:(unsigned)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange withoutAdditionalLayout:(BOOL)flag;
- (NSRect)lineFragmentUsedRectForGlyphAtIndex:(unsigned)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange withoutAdditionalLayout:(BOOL)flag;
- (NSTextContainer *)textContainerForGlyphAtIndex:(unsigned)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange withoutAdditionalLayout:(BOOL)flag;
    // If flag is YES, the withoutAdditionalLayout variants will not generate glyphs or perform layout in attempting to answer, so should not be used unless layout is known to be complete for the range in question.  Primarily for use from within NSTypesetter, after layout is complete for the range in question, but before the layout manager's call to NSTypesetter has returned.  In that case glyph and layout holes have not yet been recalculated, so the layout manager does not yet know that layout is complete for that range, and the withoutAdditionalLayout: variants must be used.
#endif

- (NSSize)attachmentSizeForGlyphAtIndex:(unsigned)glyphIndex;
    // Returns the size at which the glyph should be drawn.

- (NSRect)extraLineFragmentRect;
- (NSRect)extraLineFragmentUsedRect;
- (NSTextContainer *)extraLineFragmentTextContainer;
    // Return info about the extra line fragment.

- (BOOL)drawsOutsideLineFragmentForGlyphAtIndex:(unsigned) glyphIndex;
    // Returns whether the glyph will make marks outside its line fragment's bounds.

- (NSPoint)locationForGlyphAtIndex:(unsigned)glyphIndex;
    // Returns the location that the given glyph will draw at.  If this glyph doesn't have an explicit location set for it (i.e., it is part of (but not first in) a sequence of nominally spaced characters), the location is calculated from the location of the last glyph with a location set.  Glyph locations are relative the their line fragment bounding rect's origin (see -lineFragmentForGlyphAtIndex:effectiveRange: below for finding line fragment bounding rects).  This will cause glyph generation and layout as needed.

- (BOOL)notShownAttributeForGlyphAtIndex:(unsigned) glyphIndex;
    // Some glyphs are not shown.  This will cause glyph generation and layout as needed..

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/************************** Block information **************************/

- (void)setLayoutRect:(NSRect)rect forTextBlock:(NSTextBlock *)block glyphRange:(NSRange)glyphRange;
- (void)setBoundsRect:(NSRect)rect forTextBlock:(NSTextBlock *)block glyphRange:(NSRange)glyphRange;
- (NSRect)layoutRectForTextBlock:(NSTextBlock *)block glyphRange:(NSRange)glyphRange;
- (NSRect)boundsRectForTextBlock:(NSTextBlock *)block glyphRange:(NSRange)glyphRange;
    // Used to set and get information about layout of text blocks.  These methods cause glyph generation but not layout.  The latter two will return NSZeroRect if no rect has been set for the specified block and range since the last invalidation.
- (NSRect)layoutRectForTextBlock:(NSTextBlock *)block atIndex:(unsigned)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
- (NSRect)boundsRectForTextBlock:(NSTextBlock *)block atIndex:(unsigned)glyphIndex effectiveRange:(NSRangePointer)effectiveGlyphRange;
    // Similar to the above, but they can be passed any index in the range and will return the range by reference.
#endif

/************************ More sophisticated queries ************************/

// These two methods can cause glyph generation.

- (NSRange)glyphRangeForCharacterRange:(NSRange)charRange actualCharacterRange:(NSRangePointer)actualCharRange;
    // Returns the range of glyphs that are generated from the unichars in the given charRange.  actualCharRange, if not NULL, will be set to the actual range of characters that fully define the glyph range returned.  This range may be identical or slightly larger than the requested characterRange.  For instance, if the text storage contains the unichars "o" and (umlaut) and the glyph store contains the single precomposed glyph (o-umlaut), and if the charcterRange given encloses only the first or second unichar, the actualCharRange will be set to enclose both unichars.

- (NSRange)characterRangeForGlyphRange:(NSRange)glyphRange actualGlyphRange:(NSRangePointer)actualGlyphRange;
    // Returns the range of characters that generated the glyphs in the given glyphRange.  actualGlyphRange, if not NULL, will be set to the full range of glyphs that the character range returned generated.  This range may be identical or slightly larger than the requested glyphRange.  For instance, if the text storage contains the unichar (o-umlaut) and the glyph store contains the two atomic glyphs "o" and (umlaut), and if the glyphRange given encloses only the first or second glyph, the actualGlyphRange will be set to enclose both glyphs.

// All of these methods can cause glyph generation AND layout.

- (NSRange)glyphRangeForTextContainer:(NSTextContainer *)container;
    // Returns the range of characters which have been laid into the given container.  This is a less efficient method than the similar -textContainerForGlyphAtIndex:effectiveRange:.

- (NSRange)rangeOfNominallySpacedGlyphsContainingIndex:(unsigned)glyphIndex;
    // Returns the range including the first glyph from glyphIndex on back that has a location set and up to, but not including the next glyph that has a location set.  This is a range of glyphs that could potentially be shown with a single postscript show operation (not considering changes in color or other attributes not affecting layout).

- (NSRectArray)rectArrayForCharacterRange:(NSRange)charRange withinSelectedCharacterRange:(NSRange)selCharRange inTextContainer:(NSTextContainer *)container rectCount:(unsigned *)rectCount;
- (NSRectArray)rectArrayForGlyphRange:(NSRange)glyphRange withinSelectedGlyphRange:(NSRange)selGlyphRange inTextContainer:(NSTextContainer *)container rectCount:(unsigned *)rectCount;
    // Returns an array of NSRects and the number of rects by reference which define the region in container that encloses the given range.  If a selected range is given in the second argument, the rectangles returned will be correct for drawing the selection.  Selection rectangles are generally more complicated than enclosing rectangles and supplying a selected range is the clue these methods use to determine whether to go to the trouble of doing this special work. 
    // If the caller is interested in this more from an enclosing point of view rather than a selection point of view pass {NSNotFound, 0} as the selected range.  This method works hard to do the minimum amount of work required to answer the question.  The resulting array is owned by the layoutManager and will be reused when either of these two methods OR -boundingRectForGlyphRange:inTextContainer: is called.  Note that one of these methods may be called indirectly.  The upshot is that if you aren't going to use the rects right away, you should copy them to another location.

- (NSRect)boundingRectForGlyphRange:(NSRange)glyphRange inTextContainer:(NSTextContainer *)container;
    // Returns the smallest bounding rect (in container coordinates) which completely encloses the glyphs in the given glyphRange that are in the given container.  Basically, the range is intersected with the container's range before computing the bounding rect.  This method can be used to translate glyph ranges into display rectangles for invalidation.

- (NSRange)glyphRangeForBoundingRect:(NSRect)bounds inTextContainer:(NSTextContainer *)container;
- (NSRange)glyphRangeForBoundingRectWithoutAdditionalLayout:(NSRect)bounds inTextContainer:(NSTextContainer *)container;
    // Returns the minimum contiguous glyph range that would need to be displayed in order to draw all glyphs that fall (even partially) within the bounding rect given.  This range might include glyphs which do not fall into the rect at all.  At most this will return the glyph range for the whole container.  The "WithoutAdditionalLayout" variant will not generate glyphs or perform layout in attempting to answer, and, thus, will potentially not be totally correct.

- (unsigned)glyphIndexForPoint:(NSPoint)point inTextContainer:(NSTextContainer *)container fractionOfDistanceThroughGlyph:(float *)partialFraction;
- (unsigned)glyphIndexForPoint:(NSPoint)point inTextContainer:(NSTextContainer *)container;
- (float)fractionOfDistanceThroughGlyphForPoint:(NSPoint)point inTextContainer:(NSTextContainer *)container;
    // Returns the index of the glyph which under the given point which is expressed in the given container's coordinate system.  If no glyph is under the point the "nearest" glyph is returned where "nearest" is defined in such a way that selection works like it should.  See the implementation for details.  partialFraction, if provided, is set to the fraction of the distance between the location of the glyph returned and the location of the next glyph that the point is at.
    // Java note: The second and third methods are the primitives and are the methods exposed in Java.  The first method calls the other two.  All Objective-C code calls the first method.  In either Objective-C or Java any overriding should be done for the second and third methods, not the first method.  This will all work out correctly with the exception of existing code that overrides the first method.  Existing subclasses that do this will not have their implementations available to Java developers.

- (void)getFirstUnlaidCharacterIndex:(unsigned *)charIndex glyphIndex:(unsigned *)glyphIndex;
- (unsigned)firstUnlaidCharacterIndex;
- (unsigned)firstUnlaidGlyphIndex;
    // Returns (by reference for the "get" method) the character index or glyph index or both of the first unlaid character/glyph in the layout manager at this time.
    // Java note: The two "firstUnlaid" methods are the primitives and are the methods exposed in Java.  The "getFirstUnlaid" method calls the other two.  All Objective-C code calls the "getFirstUnlaid" method.  In either Objective-C or Java any overriding should be done for the "firstUnlaid" methods, not the "getFirstUnlaid" method.  This will all work out correctly with the exception of existing code that overrides the "getFirstUnlaid" method.  Existing subclasses that do this will not have their implementations available to Java developers.

/************************ Screen font usage control ************************/

- (BOOL)usesScreenFonts;
- (void)setUsesScreenFonts:(BOOL)flag;
    // Sets whether this layoutManager will use screen fonts when it is possible to do so.

- (NSFont *)substituteFontForFont:(NSFont *)originalFont;
    // Returns a font to use in place of originalFont.  This method is used to substitute screen fonts for regular fonts.  If screen fonts are allowed and a screen font is available for originalFont, it is returned, otherwise originalFont is returned.  This method causes no generation.

/************************ Temporary attribute support ************************/
- (NSDictionary *)temporaryAttributesAtCharacterIndex:(unsigned)charIndex effectiveRange:(NSRangePointer)effectiveCharRange;
- (void)setTemporaryAttributes:(NSDictionary *)attrs forCharacterRange:(NSRange)charRange;
- (void)addTemporaryAttributes:(NSDictionary *)attrs forCharacterRange:(NSRange)charRange;
- (void)removeTemporaryAttribute:(NSString *)name forCharacterRange:(NSRange)charRange;

/************************ Typesetting support ************************/

// Bulk methods to retrieve many glyphs, with their attributes, and fill buffers supplied by the caller.
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (unsigned)getGlyphsInRange:(NSRange)glyphsRange glyphs:(NSGlyph *)glyphBuffer characterIndexes:(unsigned *)charIndexBuffer glyphInscriptions:(NSGlyphInscription *)inscribeBuffer elasticBits:(BOOL *)elasticBuffer bidiLevels:(unsigned char *)bidiLevelBuffer;
#endif
- (unsigned)getGlyphsInRange:(NSRange)glyphsRange glyphs:(NSGlyph *)glyphBuffer characterIndexes:(unsigned *)charIndexBuffer glyphInscriptions:(NSGlyphInscription *)inscribeBuffer elasticBits:(BOOL *)elasticBuffer;

/************************ Typesetting compatibility ************************/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (NSTypesetterBehavior)typesetterBehavior;
- (void)setTypesetterBehavior:(NSTypesetterBehavior)theBehavior;

- (float)defaultLineHeightForFont:(NSFont *)theFont;
#endif
@end

@interface NSLayoutManager (NSTextViewSupport)

/************************ Ruler stuff ************************/

- (NSArray *)rulerMarkersForTextView:(NSTextView *)view paragraphStyle:(NSParagraphStyle *)style ruler:(NSRulerView *)ruler;
- (NSView *)rulerAccessoryViewForTextView:(NSTextView *)view paragraphStyle:(NSParagraphStyle *)style ruler:(NSRulerView *)ruler enabled:(BOOL)isEnabled;
    // These return, respectively, an array of text ruler objects for the current selection and the accessory view that the text system uses for ruler.  If you have turned off automatic ruler updating through the use of setUsesRulers: so that you can do more complex things, but you still want to display the appropriate text ruler objects and/or accessory view, you can use these methods.

/************************ First responder support ************************/

- (BOOL)layoutManagerOwnsFirstResponderInWindow:(NSWindow *)window;
    // Returns YES if the firstResponder of the given window is one of the NSTextViews attached to this NSLayoutManager.

- (NSTextView *)firstTextView;

- (NSTextView *)textViewForBeginningOfSelection;
    // This method is special in that it won't cause layout if the beginning of the selected range is not yet laid out.  Other than that this method could be done through other API.

/************************ Drawing support ************************/

- (void)drawBackgroundForGlyphRange:(NSRange)glyphsToShow atPoint:(NSPoint)origin;
- (void)drawGlyphsForGlyphRange:(NSRange)glyphsToShow atPoint:(NSPoint)origin;
    // These methods are called by NSTextView to do drawing.  You can override these if you think you can draw the stuff any better (but not to change layout).  You can call them if you want, but focus must already be locked on the destination view or image.  -drawBackgroundGorGlyphRange:atPoint: should draw the background color and selection and marked range aspects of the text display.  -drawGlyphsForGlyphRange:atPoint: should draw the actual glyphs.  The point in either method is the container origin in the currently focused view's coordinates for the container the glyphs lie in.

- (void)showPackedGlyphs:(char *)glyphs length:(unsigned)glyphLen glyphRange:(NSRange)glyphRange atPoint:(NSPoint)point font:(NSFont *)font color:(NSColor *)color printingAdjustment:(NSSize)printingAdjustment;
    // This is the primitive for drawing a range of glyphs that can all be shown with a single show operator.  The glyphRange, point, font, and color are passed in merely for information purposes.  They will all be set already in the graphics state.  If for any reason you modify the set color or font, you must restore it before returning from this method.  You should never call this method, but you might override it.  printingAdjustment will be NSZeroSize when drawing to the screen, but when printing this may contain values by which the nominal spacing between the characters should be adjusted.  The width and height of this size are suitable for passing to the postscript operator ashow, for example.  Direct use of the pswraps PSshow() and PSashow() (or any other wrap that takes a (char *) argument instead of a char array and a length) will not work in all cases since the glyph encoding might be an encoding where embedded NULL bytes do not indicate the end of the string.  The length argument (glyphLen) is the number of bytes pointed at by the "glyphs" argument; for some glyph packings, this will not be an even number; for NSNativeShortGlyphPacking, it will be even.

- (void)showAttachmentCell:(NSCell *)cell inRect:(NSRect)rect characterIndex:(unsigned)attachmentIndex;
   // This is the primitive for actually drawing an attachment cell.  The attachment should be drawn within the given rect.  The character index is provided for those cells that alter their appearance based on their location.

- (void)drawUnderlineForGlyphRange:(NSRange)glyphRange underlineType:(int)underlineVal baselineOffset:(float)baselineOffset lineFragmentRect:(NSRect)lineRect lineFragmentGlyphRange:(NSRange)lineGlyphRange containerOrigin:(NSPoint)containerOrigin;
- (void)underlineGlyphRange:(NSRange)glyphRange underlineType:(int)underlineVal lineFragmentRect:(NSRect)lineRect lineFragmentGlyphRange:(NSRange)lineGlyphRange containerOrigin:(NSPoint)containerOrigin;
    // The first of these methods actually draws an appropriate underline for the glyph range given.  The second method potentailly breaks the range it is given up into subranges and calls drawUnderline... for ranges that should actually have the underline drawn.  As examples of why there are two methods, consider two situations.  First, in all cases you don't want to underline the leading and trailing whitespace on a line.  The -underlineGlyphRange... method is passed glyph ranges that have underlining turned on, but it will then look for this leading and trailing white space and only pass the ranges that should actually be underlined to -drawUnderline...  Second, if the underlineType: indicates that only words, (ie no whitespace), should be underlined, then -underlineGlyphRange... will carve the range it is passed up into words and only pass word ranges to -drawUnderline.

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)drawStrikethroughForGlyphRange:(NSRange)glyphRange strikethroughType:(int)strikethroughVal baselineOffset:(float)baselineOffset lineFragmentRect:(NSRect)lineRect lineFragmentGlyphRange:(NSRange)lineGlyphRange containerOrigin:(NSPoint)containerOrigin;
- (void)strikethroughGlyphRange:(NSRange)glyphRange strikethroughType:(int)strikethroughVal lineFragmentRect:(NSRect)lineRect lineFragmentGlyphRange:(NSRange)lineGlyphRange containerOrigin:(NSPoint)containerOrigin;
    // These two methods parallel the two corresponding underline methods, but draw strikethroughs instead of underlines.
#endif

@end

@interface NSObject (NSLayoutManagerDelegate)

- (void)layoutManagerDidInvalidateLayout:(NSLayoutManager *)sender;
    // This is sent whenever layout or glyphs become invalidated in a layout manager which previously had all layout complete.

- (void)layoutManager:(NSLayoutManager *)layoutManager didCompleteLayoutForTextContainer:(NSTextContainer *)textContainer atEnd:(BOOL)layoutFinishedFlag;
    // This is sent whenever a container has been filled.  This method can be useful for paginating.  The textContainer might be nil if we have completed all layout and not all of it fit into the existing containers.  atEnd indicates whether all layout is complete.

@end
