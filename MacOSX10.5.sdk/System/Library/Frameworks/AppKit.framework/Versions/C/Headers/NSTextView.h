/*
        NSTextView.h
        Application Kit
        Copyright (c) 1994-2007, Apple Inc.
        All rights reserved.
*/

// NSTextView is a NSText subclass that displays the glyphs laid out in one NSTextContainer.

#import <AppKit/NSText.h>
#import <AppKit/NSInputManager.h>
#import <AppKit/NSTextAttachment.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSDragging.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSTextInputClient.h>

@class NSTextContainer;
@class NSTextStorage;
@class NSLayoutManager;
@class NSRulerView;
@class NSRulerMarker;
@class NSUndoManager;
@class NSParagraphStyle;

/* Values for NSSelectionGranularity */
enum {
    NSSelectByCharacter = 0,
    NSSelectByWord = 1,
    NSSelectByParagraph = 2
};
typedef NSUInteger NSSelectionGranularity;

/* Values for NSSelectionAffinity */
enum {
    NSSelectionAffinityUpstream = 0,
    NSSelectionAffinityDownstream = 1
};
typedef NSUInteger NSSelectionAffinity;

/* Values for NSFindPanelAction */
enum {
    NSFindPanelActionShowFindPanel = 1,
    NSFindPanelActionNext = 2,
    NSFindPanelActionPrevious = 3,
    NSFindPanelActionReplaceAll = 4,
    NSFindPanelActionReplace = 5,
    NSFindPanelActionReplaceAndFind = 6,
    NSFindPanelActionSetFindString = 7,
    NSFindPanelActionReplaceAllInSelection = 8
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    ,
    NSFindPanelActionSelectAll = 9,
    NSFindPanelActionSelectAllInSelection = 10
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
};
typedef NSUInteger NSFindPanelAction;

/* Values for NSFindPanel search metadata */

APPKIT_EXTERN NSString *NSFindPanelSearchOptionsPboardType  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

APPKIT_EXTERN NSString *NSFindPanelCaseInsensitiveSearch AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;     // BOOL
APPKIT_EXTERN NSString *NSFindPanelSubstringMatch AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;            // NSNumber containing NSFindPanelSubstringMatchType

enum {
    NSFindPanelSubstringMatchTypeContains = 0,
    NSFindPanelSubstringMatchTypeStartsWith = 1,
    NSFindPanelSubstringMatchTypeFullWord = 2,
    NSFindPanelSubstringMatchTypeEndsWith = 3
};
typedef NSUInteger NSFindPanelSubstringMatchType;


/* A meta locale identifier representing the set of Roman input sources available.  You can specify [NSArray arrayWithObject: NSAllRomanInputSourcesLocaleIdentifier] to restrict allowed input sources to Roman only.
*/
APPKIT_EXTERN NSString *NSAllRomanInputSourcesLocaleIdentifier AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@interface NSTextView : NSText <NSTextInput, NSUserInterfaceValidations
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
, NSTextInputClient
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */
>

/**************************** Initializing ****************************/

- (id)initWithFrame:(NSRect)frameRect textContainer:(NSTextContainer *)container;
    // Designated Initializer. container may be nil.

- (id)initWithFrame:(NSRect)frameRect;
    // This variant will create the text network (textStorage, layoutManager, and a container).

/***************** Get/Set the container and other stuff *****************/

- (NSTextContainer *)textContainer;
- (void)setTextContainer:(NSTextContainer *)container;
    // The set method should not be called directly, but you might want to override it.  Gets or sets the text container for this view.  Setting the text container marks the view as needing display.  The text container calls the set method from its setTextView: method.

- (void)replaceTextContainer:(NSTextContainer *)newContainer;
    // This method should be used instead of the primitive -setTextContainer: if you need to replace a view's text container with a new one leaving the rest of the web intact.  This method deals with all the work of making sure the view doesn't get deallocated and removing the old container from the layoutManager and replacing it with the new one.

- (void)setTextContainerInset:(NSSize)inset;
- (NSSize)textContainerInset;
    // The textContainerInset determines the padding that the view provides around the container.  The container's origin will be inset by this amount from the bounds point {0,0} and padding will be left to the right and below the container of the same amount.  This inset affects the view sizing in response to new layout and is used by the rectangular text containers when they track the view's frame dimensions.

- (NSPoint)textContainerOrigin;
- (void)invalidateTextContainerOrigin;
    // The container's origin in the view is determined from the current usage of the container, the container inset, and the view size.  textContainerOrigin returns this point.  invalidateTextContainerOrigin is sent automatically whenever something changes that causes the origin to possibly move.  You usually do not need to call invalidate yourself. 

- (NSLayoutManager *)layoutManager;
- (NSTextStorage *)textStorage;
    // Convenience methods

/************************* Key binding entry-point *************************/

- (void)insertText:(id)insertString;
    // This method is the funnel point for text insertion after keys pass through the key binder.  Ordinarily it is not suitable for purposes other than handling user typing.

/*************************** Sizing methods ***************************/

- (void)setConstrainedFrameSize:(NSSize)desiredSize;
    // Sets the frame size of the view to desiredSize constrained within min and max size.

/***************** New miscellaneous API above and beyond NSText *****************/

// These two complete the set of range: type set methods. to be equivalent to the set of non-range taking varieties.
- (void)setAlignment:(NSTextAlignment)alignment range:(NSRange)range;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setBaseWritingDirection:(NSWritingDirection)writingDirection range:(NSRange)range;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

/*************************** New Font menu commands ***************************/

- (void)turnOffKerning:(id)sender;
- (void)tightenKerning:(id)sender;
- (void)loosenKerning:(id)sender;
- (void)useStandardKerning:(id)sender;
- (void)turnOffLigatures:(id)sender;
- (void)useStandardLigatures:(id)sender;
- (void)useAllLigatures:(id)sender;
- (void)raiseBaseline:(id)sender;
- (void)lowerBaseline:(id)sender;
- (void)toggleTraditionalCharacterShape:(id)sender;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)outline:(id)sender;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

/*************************** Find menu commands ***************************/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)performFindPanelAction:(id)sender;
    // See NSFindPanelAction for possible tags in sender
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

/*************************** New Text commands ***************************/

- (void)alignJustified:(id)sender;
- (void)changeColor:(id)sender;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)changeAttributes:(id)sender;
- (void)changeDocumentBackgroundColor:(id)sender;
- (void)toggleBaseWritingDirection:(id)sender;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)orderFrontSpacingPanel:(id)sender;
- (void)orderFrontLinkPanel:(id)sender;
- (void)orderFrontListPanel:(id)sender;
- (void)orderFrontTablePanel:(id)sender;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

/*************************** Ruler support ***************************/

- (void)rulerView:(NSRulerView *)ruler didMoveMarker:(NSRulerMarker *)marker;
- (void)rulerView:(NSRulerView *)ruler didRemoveMarker:(NSRulerMarker *)marker;
- (void)rulerView:(NSRulerView *)ruler didAddMarker:(NSRulerMarker *)marker;
- (BOOL)rulerView:(NSRulerView *)ruler shouldMoveMarker:(NSRulerMarker *)marker;
- (BOOL)rulerView:(NSRulerView *)ruler shouldAddMarker:(NSRulerMarker *)marker;
- (CGFloat)rulerView:(NSRulerView *)ruler willMoveMarker:(NSRulerMarker *)marker toLocation:(CGFloat)location;
- (BOOL)rulerView:(NSRulerView *)ruler shouldRemoveMarker:(NSRulerMarker *)marker;
- (CGFloat)rulerView:(NSRulerView *)ruler willAddMarker:(NSRulerMarker *)marker atLocation:(CGFloat)location;
- (void)rulerView:(NSRulerView *)ruler handleMouseDown:(NSEvent *)event;

/*************************** Fine display control ***************************/

- (void)setNeedsDisplayInRect:(NSRect)rect avoidAdditionalLayout:(BOOL)flag;
    // If flag is set, then this will attempt to avoid causing layout, if possible, when displaying the rect.  If flag is not set, this is equivalent to setNeedsDisplayInRect:.

- (BOOL)shouldDrawInsertionPoint;
- (void)drawInsertionPointInRect:(NSRect)rect color:(NSColor *)color turnedOn:(BOOL)flag;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)drawViewBackgroundInRect:(NSRect)rect;
    // This is the override point for view background drawing.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

/*************************** Especially for subclassers ***************************/

- (void)updateRuler;
- (void)updateFontPanel;

- (void)updateDragTypeRegistration;

- (NSRange)selectionRangeForProposedRange:(NSRange)proposedCharRange granularity:(NSSelectionGranularity)granularity;

/*************************** Especially for subclassers ***************************/

- (void)clickedOnLink:(id)link atIndex:(NSUInteger)charIndex;
    // Cause the text view to act as if someone clicked on a piece of text with link as the value of NSLinkAttributeName.  If, for instance, you have a special attachment cell that can end up following links, you can use this method to ask the text view to follow a link once you decide it should.  This method is invoked by the text view during mouse tracking if the user is clicking a link as well.  This sends the textView:clickedOnLink: delegation if the delegate responds.

/************************* Speech support *************************/

- (void)startSpeaking:(id)sender;
- (void)stopSpeaking:(id)sender;

/************************* Helper for subclassers *************************/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (NSUInteger)characterIndexForInsertionAtPoint:(NSPoint)point;
    // Here point is in view coordinates, and the return value is a character index appropriate for placing a zero-length selection for an insertion point associated with the mouse at the given point.  The NSTextInput method characterIndexForPoint: is not suitable for this role.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
@interface NSTextView (NSCompletion)

/************************* Completion support *********************/

- (void)complete:(id)sender;
    // Responder method for invoking completion.  May be invoked programmatically if autocompletion is desired.
    
- (NSRange)rangeForUserCompletion;
    // Usually returns the partial range from the most recent beginning of a word up to the insertion point.  May be overridden by subclassers to alter the range to be completed.  Returning (NSNotFound, 0) suppresses completion.
    
- (NSArray *)completionsForPartialWordRange:(NSRange)charRange indexOfSelectedItem:(NSInteger *)index;
    // Returns an array of potential completions, in the order to be presented, representing complete words that the user might be trying to type when starting by typing the partial word at the given range.  May be overridden by subclassers to modify or override this list.  Returning nil or a zero-length array suppresses completion.   The selected item index may optionally be set to indicate which completion should be initially selected; default is 0, and -1 indicates no selection.  This method should call the delegate method textView:completions:forPartialWordRange:indexOfSelectedItem: if implemented.

- (void)insertCompletion:(NSString *)word forPartialWordRange:(NSRange)charRange movement:(NSInteger)movement isFinal:(BOOL)flag;
    // Called with final == NO as the user moves through the potential completions, then with final == YES when a completion is definitively selected (or completion is cancelled and the original value is reinserted).  The default implementation inserts the completion into the text at the appropriate location.  The movement argument takes its values from the movement codes defined in NSText.h, and allows subclassers to distinguish between canceling completion and selection by arrow keys, by return, by tab, or by other means such as clicking.
@end
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

@interface NSTextView (NSPasteboard)

/******************* Pasteboard support (mainly for subclassers) *******************/

// To implement support for writing a new type, override -writeSelectionToPasteboard:type: to support your new type (and call super if you're not going to handle it.)  Then you can override -writablePasteboardTypes and optionally the +registerForServices methods to enable the new type.

// To implement support for reading a new type, override -readSelectionFromPasteboard:type: to support your new type (and call super if you're not going to handle it.)  Then you can override -readablePasteboardTypes and optionally the +registerForServices and acceptableDragTypes methods to enable the new type.  Advanced drag acceptance behavior can be implemented with dragOperationForDraggingInfo:type: and cleanUpAfterDragOperation.

// To implement new mechanisms that cause data to be written to the pasteboard you can call writablePasteboardTypes and writeSelectionToPasteboard:types:.

// To implement new mechanisms that cause data to be read from the pasteboard you can call preferredPasteboardTypeFromArray:restrictedToTypesFromArray: and readSelectionFromPasteboard:type:.

- (NSArray *)writablePasteboardTypes;
    // Returns an array of pasteboard types that can be provided from the current selection.  Overriders should copy the result from super and add their own new types.

- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard type:(NSString *)type;
    // Invoked automatically to write a single type to the pasteboard.  The type will already have been declared to the pasteboard so this should merely write the data using the appropriate set method on the pasteboard.

- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;
    // Declares all the types to the pasteboard then calls writeSelectionToPasteboard:type: for each type in the array.


- (NSArray *)readablePasteboardTypes;
    // Returns an array of types that could be read currently in order of preference.  Subclassers should take care to consider the "preferred" part of the semantics of this method.  Figure out where your new type should fit into the preferred order.  The preferred order should usually be from the richest types down to the less rich.  The default array will start with RTFD, RTF, strings, files, images, colors and so on.  The ordering list really starts to lose significance after the first few elements.  If the new format you are supporting is richer than RTFD, put it at the head of the list, otherwise try to find the right place for it, but don't count on the actual contents of the list you get from super either.

- (NSString *)preferredPasteboardTypeFromArray:(NSArray *)availableTypes restrictedToTypesFromArray:(NSArray *)allowedTypes;
    // Returns the most preferred type from the available types array that it is currently possible to read.  If allowedTypes is provided then only those types will be considered regardless of whether others could currently be read.  You should not have to override this to support new types.

- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard type:(NSString *)type;
    // Invoked automatically to read a specific type from the pasteboard.  The type will already have been by the preferredPasteboardTypeFromArray:restrictedToTypesFromArray: method so this should merely read the data using the appropriate accessor method on the pasteboard.

- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard;
    // Part of the services mechanism.  This is implemented such that you should not need to override it to support new types.  It should not be necessary to call this.

+ (void)registerForServices;
    // Automatically invoked when the first instance of NSTextView is created.  Subclassing this is necessary to add support for new service types (in addition to actually supporting writing or reading the types, of course).  Override it to call super and then register your own new types.  You should probably never need to call this except to message super in an override.

- (id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;
    // This method is part of the services protocol and is implemented in such a way that if you extend the type support correctly you should not need to override it.  You should never need to call it either.

- (void)pasteAsPlainText:(id)sender;
- (void)pasteAsRichText:(id)sender;
    // These methods are like paste: (from NSResponder) but they restrict the acceptable type of the pasted data.  They are suitable as menu actions for appropriate "Paste As" submenu commands.

@end

@interface NSTextView (NSDragging)

- (BOOL)dragSelectionWithEvent:(NSEvent *)event offset:(NSSize)mouseOffset slideBack:(BOOL)slideBack;
    // Causes textview to begin dragging current selected range, returning YES if it succeeds in initiating the drag.  Primarily for subclassers, who can override it to intervene at beginning of a drag.

- (NSImage *)dragImageForSelectionWithEvent:(NSEvent *)event origin:(NSPointPointer)origin;
    // Used by dragSelectionWithEvent:offset:slideBack: to get an appropriate image.  Returns the lower-left point of the image in view coordinates as origin.  Can be called by others who need such an image, or can be overridden by subclassers to return a different image (if it returns nil, a default icon will be used).

- (NSArray *)acceptableDragTypes;
    // Must be overridden to support new drag types in addition to adding support for reading and writing the type.  Override it to call super, then make a copy of the result and add your own new types before returning the copy.  You should probably never need to call this except to message super in an override.

- (NSDragOperation)dragOperationForDraggingInfo:(id <NSDraggingInfo>)dragInfo type:(NSString *)type;
        // This is called by draggingEntered:... and draggingUpdated:...  It should return the drag operation constant appropriate to the current situation or NSDragOperationNone.  It can also do any other auxiliary stuff like drawing a ghost to indicate where the dragged thing will go when it is dropped.  Be aware that this is called over and over so if you're going to draw a ghost or something avoid doing it over and over unless you need to.  Any state you set up in this method that needs to be cleared can be cleared by overriding the next method.  You should probably never need to call this except to message super in an override.  Clients should override this method rather than draggingEntered:... and draggingUpdated:... to control the drag operation.  Clients overriding this method must message super to get the standard drag insertion indicator.

- (void)cleanUpAfterDragOperation;
    // If you set up persistent state that should go away when the drag operation finishes, you can clean it up here.  Such state is usually set up in -dragOperationForDraggingInfo:type:.  You should probably never need to call this except to message super in an override.

@end

@interface NSTextView (NSSharing)

// The methods in this category deal with settings that need to be shared by all the NSTextViews of a single NSLayoutManager.  Many of these methods are overrides of NSText or NSResponder methods.

/*************************** Selected/Marked range ***************************/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSArray *)selectedRanges;
- (void)setSelectedRanges:(NSArray *)ranges affinity:(NSSelectionAffinity)affinity stillSelecting:(BOOL)stillSelectingFlag;
- (void)setSelectedRanges:(NSArray *)ranges;
    // These multiple-range methods supersede the corresponding single-range methods.  The ranges argument must be a non-nil, non-empty array of objects responding to rangeValue.  The return value of selectedRanges obeys the same restrictions, and in addition its elements are sorted, non-overlapping, non-contiguous, and (except for the case of a single range) have non-zero-length.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

- (void)setSelectedRange:(NSRange)charRange affinity:(NSSelectionAffinity)affinity stillSelecting:(BOOL)stillSelectingFlag;
- (NSSelectionAffinity)selectionAffinity;
- (NSSelectionGranularity)selectionGranularity;
- (void)setSelectionGranularity:(NSSelectionGranularity)granularity;

- (void)setSelectedTextAttributes:(NSDictionary *)attributeDictionary;
- (NSDictionary *)selectedTextAttributes;
    // Selected text attributes are applied as temporary attributes to selected text.  Candidates include those attributes that do not affect layout.

- (void)setInsertionPointColor:(NSColor *)color;
- (NSColor *)insertionPointColor;

- (void)updateInsertionPointStateAndRestartTimer:(BOOL)restartFlag;

- (void)setMarkedTextAttributes:(NSDictionary *)attributeDictionary;
- (NSDictionary *)markedTextAttributes;
    // Marked text attributes are applied as temporary attributes to selected text.  Candidates include those attributes that do not affect layout.

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setLinkTextAttributes:(NSDictionary *)attributeDictionary;
- (NSDictionary *)linkTextAttributes;
    // Link text attributes are applied as temporary attributes to any text with a link attribute.  Candidates include those attributes that do not affect layout.  Default attributes are blue color, single underline, and the pointing hand cursor.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (BOOL)displaysLinkToolTips;
- (void)setDisplaysLinkToolTips:(BOOL)flag;
    // If set, then text with a link attribute will automatically be treated as if it had an implicit tooltip attribute with the same value as the link attribute.  An explicit tooltip attribute will take precedence over this implicit one.  The textView:willDisplayToolTip:forCharacterAtIndex: delegate method affects these tooltips as it does any other.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

/************************* Glyph info support *************************/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (BOOL)acceptsGlyphInfo;
- (void)setAcceptsGlyphInfo:(BOOL)flag;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2 */

/*************************** Other NSTextView methods ***************************/

- (void)setRulerVisible:(BOOL)flag;
- (BOOL)usesRuler;
- (void)setUsesRuler:(BOOL)flag;

- (void)setContinuousSpellCheckingEnabled:(BOOL)flag;
- (BOOL)isContinuousSpellCheckingEnabled;
- (void)toggleContinuousSpellChecking:(id)sender;

- (NSInteger)spellCheckerDocumentTag;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)setGrammarCheckingEnabled:(BOOL)flag;
- (BOOL)isGrammarCheckingEnabled;
- (void)toggleGrammarChecking:(id)sender;
    // If grammar checking is enabled, then it is performed whenever spellchecking is performed, whether continuously or manually.  

- (void)setSpellingState:(NSInteger)value range:(NSRange)charRange;
    // May be called or overridden to control setting of spelling and grammar indicators.  Values are those listed for NSSpellingStateAttributeName.  Calls the delegate method textView:shouldSetSpellingState:range:.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

- (NSDictionary *)typingAttributes;
- (void)setTypingAttributes:(NSDictionary *)attrs;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    // These multiple-range methods supersede the corresponding single-range methods.  For the first method, the affectedRanges argument obeys the same restrictions as the argument to setSelectedRanges:, and the replacementStrings array should either be nil (for attribute-only changes) or have the same number of elements as affectedRanges.  For the remaining three methods, the return values obey the same restrictions as that for selectedRanges, except that they will be nil if the corresponding change is not permitted, where the corresponding single-range methods return (NSNotFound, 0).
- (BOOL)shouldChangeTextInRanges:(NSArray *)affectedRanges replacementStrings:(NSArray *)replacementStrings;
- (NSArray *)rangesForUserTextChange;
- (NSArray *)rangesForUserCharacterAttributeChange;
- (NSArray *)rangesForUserParagraphAttributeChange;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

- (BOOL)shouldChangeTextInRange:(NSRange)affectedCharRange replacementString:(NSString *)replacementString;
- (void)didChangeText;

- (NSRange)rangeForUserTextChange;
- (NSRange)rangeForUserCharacterAttributeChange;
- (NSRange)rangeForUserParagraphAttributeChange;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setUsesFindPanel:(BOOL)flag;
- (BOOL)usesFindPanel;

- (void)setAllowsDocumentBackgroundColorChange:(BOOL)flag;
- (BOOL)allowsDocumentBackgroundColorChange;

- (void)setDefaultParagraphStyle:(NSParagraphStyle *)paragraphStyle;
- (NSParagraphStyle *)defaultParagraphStyle;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

- (void)setAllowsUndo:(BOOL)flag;
- (BOOL)allowsUndo;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)breakUndoCoalescing;
    // May be called to introduce a break in the coalescing of undo actions for user typing, for example at a save point.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (BOOL)allowsImageEditing;
- (void)setAllowsImageEditing:(BOOL)flag;
    // Specifies whether image attachments should permit editing of their images, if the text view is editable and the text attachment cell supports image editing.
    
- (void)showFindIndicatorForRange:(NSRange)charRange;
    // Applies a temporary highlighting effect, intended to indicate the result of a find operation.  Clients should perform any necessary scrolling before calling this method.  The effect will be removed after a certain time, or when other actions (such as scrolling) take place, but it can be removed immediately by calling this method again with a zero-length range.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

/*************************** NSText methods ***************************/

- (id)delegate;
- (void)setDelegate:(id)anObject;
- (BOOL)isEditable;
- (void)setEditable:(BOOL)flag;
- (BOOL)isSelectable;
- (void)setSelectable:(BOOL)flag;
- (BOOL)isRichText;
- (void)setRichText:(BOOL)flag;
- (BOOL)importsGraphics;
- (void)setImportsGraphics:(BOOL)flag;
- (BOOL)drawsBackground;
- (void)setDrawsBackground:(BOOL)flag;
- (NSColor *)backgroundColor;
- (void)setBackgroundColor:(NSColor *)color;
- (BOOL)isFieldEditor;
- (void)setFieldEditor:(BOOL)flag;
- (BOOL)usesFontPanel;
- (void)setUsesFontPanel:(BOOL)flag;
- (BOOL)isRulerVisible;
- (void)setSelectedRange:(NSRange)charRange;
    // Other NSText methods are implemented in the base NSTextView implementation rather than in this category.  See NSText.h for declarations.

/*************************** Smart copy/paste/delete/substitution support ***************************/

- (BOOL)smartInsertDeleteEnabled;
- (void)setSmartInsertDeleteEnabled:(BOOL)flag;
- (NSRange)smartDeleteRangeForProposedRange:(NSRange)proposedCharRange;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)toggleSmartInsertDelete:(id)sender;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

- (void)smartInsertForString:(NSString *)pasteString replacingRange:(NSRange)charRangeToReplace beforeString:(NSString **)beforeString afterString:(NSString **)afterString;
- (NSString *)smartInsertBeforeStringForString:(NSString *)pasteString replacingRange:(NSRange)charRangeToReplace;
- (NSString *)smartInsertAfterStringForString:(NSString *)pasteString replacingRange:(NSRange)charRangeToReplace;
    // Java note: The second and third methods are the primitives and are the methods exposed in Java.  The first method calls the other two.  All Objective-C code calls the first method.  In either Objective-C or Java any overriding should be done for the second and third methods, not the first method.  This will all work out correctly with the exception of existing code that overrides the first method.  Existing subclasses that do this will not have their implementations available to Java developers.  Isn't Java wonderful?

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)setAutomaticQuoteSubstitutionEnabled:(BOOL)flag;
- (BOOL)isAutomaticQuoteSubstitutionEnabled;
- (void)toggleAutomaticQuoteSubstitution:(id)sender;
- (void)setAutomaticLinkDetectionEnabled:(BOOL)flag;
- (BOOL)isAutomaticLinkDetectionEnabled;
- (void)toggleAutomaticLinkDetection:(id)sender;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

/*************************** Input Source support ***************************/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* Returns an array of locale identifiers representing input sources allowed to be enabled when the receiver has the keyboard focus.
 */
- (NSArray *)allowedInputSourceLocales;
- (void)setAllowedInputSourceLocales:(NSArray *)localeIdentifiers;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */
@end

// Note that all delegation messages come from the first textView

@interface NSObject (NSTextViewDelegate)

- (BOOL)textView:(NSTextView *)textView clickedOnLink:(id)link atIndex:(NSUInteger)charIndex;
    // Delegate only.

- (void)textView:(NSTextView *)textView clickedOnCell:(id <NSTextAttachmentCell>)cell inRect:(NSRect)cellFrame atIndex:(NSUInteger)charIndex;
    // Delegate only.

- (void)textView:(NSTextView *)textView doubleClickedOnCell:(id <NSTextAttachmentCell>)cell inRect:(NSRect)cellFrame atIndex:(NSUInteger)charIndex;
    // Delegate only.

- (void)textView:(NSTextView *)view draggedCell:(id <NSTextAttachmentCell>)cell inRect:(NSRect)rect event:(NSEvent *)event atIndex:(NSUInteger)charIndex;
    // Delegate only.  Allows the delegate to take over attachment dragging altogether.

- (NSArray *)textView:(NSTextView *)view writablePasteboardTypesForCell:(id <NSTextAttachmentCell>)cell atIndex:(NSUInteger)charIndex;
    // Delegate only.  If the previous method is not used, this method and the next allow the textview to take care of attachment dragging and pasting, with the delegate responsible only for writing the attachment to the pasteboard.  In this method, the delegate should return an array of types that it can write to the pasteboard for the given attachment.

- (BOOL)textView:(NSTextView *)view writeCell:(id <NSTextAttachmentCell>)cell atIndex:(NSUInteger)charIndex toPasteboard:(NSPasteboard *)pboard type:(NSString *)type ;
    // Delegate only.  In this method, the delegate should attempt to write the given attachment to the pasteboard with the given type, and return success or failure.

- (NSRange)textView:(NSTextView *)textView willChangeSelectionFromCharacterRange:(NSRange)oldSelectedCharRange toCharacterRange:(NSRange)newSelectedCharRange;
    // Delegate only.  Will not be called if textView:willChangeSelectionFromCharacterRanges:toCharacterRanges: is implemented.  Effectively prevents multiple selection.

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSArray *)textView:(NSTextView *)textView willChangeSelectionFromCharacterRanges:(NSArray *)oldSelectedCharRanges toCharacterRanges:(NSArray *)newSelectedCharRanges;
    // Delegate only.  Supersedes textView:willChangeSelectionFromCharacterRange:toCharacterRange:.  Return value must be a non-nil, non-empty array of objects responding to rangeValue.

- (BOOL)textView:(NSTextView *)textView shouldChangeTextInRanges:(NSArray *)affectedRanges replacementStrings:(NSArray *)replacementStrings;
    // Delegate only.  Supersedes textView:shouldChangeTextInRange:replacementString:.  The affectedRanges argument obeys the same restrictions as selectedRanges, and the replacementStrings argument will either be nil (for attribute-only changes) or have the same number of elements as affectedRanges.

- (NSDictionary *)textView:(NSTextView *)textView shouldChangeTypingAttributes:(NSDictionary *)oldTypingAttributes toAttributes:(NSDictionary *)newTypingAttributes;
    // Delegate only.  The delegate should return newTypingAttributes to allow the change, oldTypingAttributes to prevent it, or some other dictionary to modify it.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

- (void)textViewDidChangeSelection:(NSNotification *)notification;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)textViewDidChangeTypingAttributes:(NSNotification *)notification;

- (NSString *)textView:(NSTextView *)textView willDisplayToolTip:(NSString *)tooltip forCharacterAtIndex:(NSUInteger)characterIndex;
    // Delegate only.  Allows delegate to modify the tooltip that will be displayed from that specified by the NSToolTipAttributeName, or to suppress display of the tooltip (by returning nil).

- (NSArray *)textView:(NSTextView *)textView completions:(NSArray *)words forPartialWordRange:(NSRange)charRange indexOfSelectedItem:(NSInteger *)index;
    // Delegate only.  Allows delegate to modify the list of completions that will be presented for the partial word at the given range.  Returning nil or a zero-length array suppresses completion.  Optionally may specify the index of the initially selected completion; default is 0, and -1 indicates no selection.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */

- (BOOL)textView:(NSTextView *)textView shouldChangeTextInRange:(NSRange)affectedCharRange replacementString:(NSString *)replacementString;
    // Delegate only.  If characters are changing, replacementString is what will replace the affectedCharRange.  If attributes only are changing, replacementString will be nil.  Will not be called if textView:shouldChangeTextInRanges:replacementStrings: is implemented.

- (BOOL)textView:(NSTextView *)textView doCommandBySelector:(SEL)commandSelector;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (NSInteger)textView:(NSTextView *)textView shouldSetSpellingState:(NSInteger)value range:(NSRange)affectedCharRange;
    // Delegate only.  Allows delegate to control the setting of spelling and grammar indicators.  Values are those listed for NSSpellingStateAttributeName. 

- (NSMenu *)textView:(NSTextView *)view menu:(NSMenu *)menu forEvent:(NSEvent *)event atIndex:(NSUInteger)charIndex;
    // Delegate only.  Allows delegate to control the context menu returned by menuForEvent:.  The menu parameter is the context menu NSTextView would otherwise return; charIndex is the index of the character that was right-clicked. 
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */


// The following delegate-only methods are deprecated in favor of the more verbose ones above.
- (BOOL)textView:(NSTextView *)textView clickedOnLink:(id)link;
- (void)textView:(NSTextView *)textView clickedOnCell:(id <NSTextAttachmentCell>)cell inRect:(NSRect)cellFrame;
- (void)textView:(NSTextView *)textView doubleClickedOnCell:(id <NSTextAttachmentCell>)cell inRect:(NSRect)cellFrame;
- (void)textView:(NSTextView *)view draggedCell:(id <NSTextAttachmentCell>)cell inRect:(NSRect)rect event:(NSEvent *)event;
- (NSUndoManager *)undoManagerForTextView:(NSTextView *)view;

@end

APPKIT_EXTERN NSString *NSTextViewWillChangeNotifyingTextViewNotification;
    // NSOldNotifyingTextView -> the old view, NSNewNotifyingTextView -> the new view.  The text view delegate is not automatically registered to receive this notification because the text machinery will automatically switch over the delegate to observe the new first text view as the first text view changes.

APPKIT_EXTERN NSString *NSTextViewDidChangeSelectionNotification;
    // NSOldSelectedCharacterRange -> NSValue with old range.

APPKIT_EXTERN NSString *NSTextViewDidChangeTypingAttributesNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
