/*
	IMKCandidates.h
	Input Method Kit
	Copyright (c) 2006, Apple Computer, Inc.
	All rights reserved.
*/

#import <Cocoa/Cocoa.h>
#import <InputMethodKit/InputMethodKit.h>


/*!
 @enum		IMKCandidatePanelType
 @abstract   Lists the basic candidate panel types that are supplied by the InputMethodKit.
 @constant	kIMKSingleColumnScrollingCandidatePanel creates a window with a 1 column X 9 row grid.  If there are more than 9 rows this will display a scroll bar.
 @constant  kIMKScrollingGridCandidatePanel a grid with 5 columns is used to display.  If necessary, a scroll bar will be displayed.
 @constant	kIMKSingleRowSteppingCandidatePanel a 9 column x 1 row grid is displayed.  If there are more than 9 candidates, a stepper controller will be displayed.
 */
enum {
	kIMKSingleColumnScrollingCandidatePanel		=	1,
	kIMKScrollingGridCandidatePanel				=	2,
	kIMKSingleRowSteppingCandidatePanel			=	3
};
typedef NSUInteger IMKCandidatePanelType;

enum {
	kIMKMain									=   0,
	kIMKAnnotation								=	1,
	kIMKSubList									=	2,
};
typedef NSUInteger IMKStyleType;


/*!
 @enum		IMKCandidatesLocationHint
 @abstract   Provides a hint where to place the candidates display.
 @discussion The IMKCandidatePanelType will use the hint to place the candidate display, being sure that the display is always fully visible.
 @constant   kIMKLocateCandidatesAboveHint	Place the candidates above the start of the current text selection.
 @constant	kIMKLocateCandidatesBelowHint	Place the candidates below the start of the current text selection.
 @constant	kIMKLocateCandidatesLeftHint	Place the candidates to the left of the current text selection.
 @constant	kIMKLocateCandidatesRightHint	Place the candidates to the right of the current text selection.
 */
enum {
	kIMKLocateCandidatesAboveHint			=	1,
	kIMKLocateCandidatesBelowHint			=	2,
	kIMKLocateCandidatesLeftHint			=	3,
	kIMKLocateCandidatesRightHint			=	4
};
typedef NSUInteger	IMKCandidatesLocationHint;

/*!
 @const		IMKCandidatesOpacityAttributeName
 @abstract	The level of opacity.
 
 @discussion Value must be a NSNumber with a value from 0 to 1.
 */
extern const NSString* IMKCandidatesOpacityAttributeName;

/*! 
 @const		IMKCandidatesSendServerKeyEventFirst
 @abstract	Control when key events are sent to a candidate window.
 
 @discussion	Value is a NSNumber with a boolean value of NO (key events are sent to the candidate window first) or YES (key events are sent to the IMKInputController first). Note that this is only applicable when a candidate window is displayed.  The default behavior is to send the key event to the candidate window first, and if it is not processed there, to send it on to the input controller.
 */
extern const NSString*	IMKCandidatesSendServerKeyEventFirst;



@class IMKCandidatesPrivate;
@class IMKServer;

@interface IMKCandidates : NSResponder {
@protected
	IMKCandidatesPrivate *_private;
}

/*!
 @method     
 @abstract   Default initializer for the class.
 @discussion When an input method allocates an IMKCandidate object it should initialize that object by calling this method passing the IMKServer that will manage the candidates and the initial panel type.
 */

-(id)initWithServer:(IMKServer*)server panelType:(IMKCandidatePanelType)panelType;

- (id)initWithServer:(IMKServer*)server panelType:(IMKCandidatePanelType)panelType styleType:(IMKStyleType)style;

/*!
 @method     
 @abstract   Return the panel type.
 */
- (IMKCandidatePanelType)panelType;

/*!
 @method     
 @abstract   Change the panel type.
 */
- (void)setPanelType:(IMKCandidatePanelType)panelType;

/*!
 @method     
 @abstract   If a candidate window type has been provided, show the candidate window. The caller provides a location hint that is used to position the window.
 
 Input methods call this method when it is appropriate, during text conversion, to display a list of candidates.
 */
- (void)show:(IMKCandidatesLocationHint)locationHint;

/*!
 @method     
 @abstract   If the candidate window is visible, hide it.
 */
- (void)hide;

/*!
 @method     
 @abstract   Utility method returns YES if a candidate display is visible.
 */
- (BOOL)isVisible;


/*!
 @method     
 @abstract   Call this method to update the candidates displayed in the candidate window.
 @discussion Calling this method will result in a call being made to the IMKInputController's candidates method. Note that the candidate list will be updated, but the window's visible state will not change; that is to say, if the window is hidden it will remain hidden, and vice versa.
 */
-(void)updateCandidates;


/*!
 @method     
 @abstract   Displays an annotation window whose contents are the annotationString.
 @discussion An annotation is additional text that explains or somehow adds to the candidate string in a candidate window. Annotations are displayed in a small borderless window that is aligned with the current candidate panel. An input method calls showAnnotation: when the method [IMKInputController candidateSelectionChanged:] is called, and the candidateString has annotations.  
 */
-(void)showAnnotation:(NSAttributedString*)annotationString;

-(void)showSublist:(NSArray *)candidates subListDelegate:(id)delegate;

-(NSRect)candidateFrame;

#pragma mark __Appearance__


/*!
 @method     
 @abstract   Set the selection keys for the candidates.
 @discussion Selection keys are an array of NSNumbers where each NSNumber is a virtual key code that the controller will map to characters that are displayed either across the top of the candidates, if the candidates are laid out horizontally, or along the left edge of the candidates, if they are aligned vertically.
 
 The number of selection keys determines how many candidates are displayed per page.  For example, if you
 passed an array of 4 key codes, then 4 candidates are displayed per page.  If you passed 11 key codes, then 11 candidates would be displayed.
 
 By default the key codes are mapped using the keyboard layout whose source id is com.apple.keylayout.US.  The default layout can be replaced by calling
 setSelectionKeysKeylayout (see below).
 
 The default selection keys are the digits 1 through 9, or in terms of key codes: 18-21,23,22, 26, 28, 25.
 */
-(void)setSelectionKeys:(NSArray*)keyCodes;

/*!
 @method     
 @abstract   Returns an NSArray of NSNumbers where each NSNumber is a virtual key code.
 
 The NSArray is an autoreleased object. Do not release unless it is first retained.
 */
-(NSArray*)selectionKeys;

/*!
 @method     
 @abstract   Sets the key layout that is used to map virtual key codes to characters.
 */
-(void)setSelectionKeysKeylayout:(TISInputSourceRef)layout;

/*!
 @method     
 @abstract   Returns the key layout that is used to map virtual key codes for the selection keys.  By default this is the key layout whose source id is com.apple.keylayout.US.
 
 This is an autoreleased object.  Retain it if you need to keep it.
 */
-(TISInputSourceRef)selectionKeysKeylayout;

/*!
 @method     
 @abstract   Sets the "style" attributes for the candidates window.  The keys for the attributes dictionary and the values are:
 
 NSFontAttributeName (value = NSFont)  Setting the font attribute sets the font that is used to draw Candidates.  It does not effect the selection keys which are always drawn in the same font.  Note that to set the font size you should use this key/value pair.
 
 IMKCandidatesOpacityAttributeName (value = NSNumber with a float value between 0 and 1).  Sets the opacity level to transparent (0.0) to completely opaque (1.0). The default opacity is 1.0.  This constant is declared above.
 
 NSForegroundColorAttributeName (value = NSColor) Sets the text color used for the candidate text.  By default it is black.
 
 NSBackgroundColorDocumentAttribute (value = NSColor).  Set the background color that is drawn behind the candidate text.
 
 IMKCandidatesSendServerKeyEventFirst (value = NSNumber).  NO (default) gives the candidate window first chance at key events.  YES causes events to first be routed to the current IMKInputController.  In that case, if the event is not handled, it will then be sent to the candidate window.
 */
-(void)setAttributes:(NSDictionary*)attributes;

/*!
 @method     
 @abstract   Returns the attributes dictionary.
 */
-(NSDictionary*)attributes;

#pragma mark __Dismissing_the_Candidates__
/*!
 @method     
 @abstract   Setting the dismissesAutomatically flag determines what happens to displayed candidates when the return key or enter key is typed.  
 @discussion By default, if a return or enter key is typed, the candidates are dismissed and a candidateSelected: message is sent to the input controller.  However  if setDismissesAutomatically is passed a NO flag  the candidate display will not be dismissed when a return or enter key is typed.  The input controller will still be sent the candidatesSelected: message, but, as stated, the candidates display will not be dismissed.
 
 Setting this flag to NO lets an input method process text input while keeping a dynamically changing candidates display in view throughout the text input process.
 
 When you set this to NO the candidate display will still be hidden when when a session deactivates.
 */
-(void)setDismissesAutomatically:(BOOL)flag;

/*!
 @method     
 @abstract   Returns the dismissesAutomatically flag.
 */
-(BOOL)dismissesAutomatically;

/*!
 @method
 @abstract	Returns the currently selected candidate identifer.
 @discussion Attempts to determine the identifier for the selected candidate.  If there is no selection the return value will be NSNotFound.
 */
-(NSInteger)selectedCandidate AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Positions the top-left corner of the candidate window’s frame rectangle at a given point in screen coordinates. 
 */
-(void) setCandidateFrameTopLeft:(NSPoint)point AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	If the current selection has a child IMKCandidates object that will be shown.
 @discussion If there is a failure in showing the child this method will throw an exception.
*/
-(void)showChild AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	If the current selection has a child IMKCandidates that is being shown hide it.
 @discussion Typically a client will not need to call this as IMKCandidates automatically hides and shows children.
 */
-(void)hideChild AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Attach an IMKCandidates object to the specified selection.
 @discussion The IMKCandidate can be a sublist or an annotation.
 */
-(void)attachChild:(IMKCandidates*)child toCandidate:(NSInteger)candidateIdentifier type:(IMKStyleType)theType AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Detach the IMKCandidates object attached to candidate
 */
-(void)detachChild:(NSInteger)candidateIdentifier AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Set the candidates data directly rather than supplying data via [IMKInputContoller candidates:].
 @discussion The elements of the array can be strings or attributed strings.
 */
-(void)setCandidateData:(NSArray*)candidatesArray AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Select the candidate whose identifier matches the identifier parameter.
 @result YES if the candidateIdentifier is valid an the selection was made.  NO if canidateIdentifier is invalid or it was not possible make the selection.
 @param An identifier for a candidate.  You can obtain an identifier by mapping a candidate to an identifier via the [IMKCandidates candidateStringIdentifier:].
 */
-(BOOL)selectCandidateWithIdentifier:(NSInteger)candidateIdentifier AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/* temporary use this until all the clients have moved to selectCandidateWithIdentifier */
-(void)selectCandidate:(NSInteger)candidateIdentifier;

/*!
 @method
 @abstract	Show the candidate window.
 @discussion This simply shows the candidates.  No effort is made to position the candidate.  The caller should move the candidate window to an appropriate location prior to showing.
 */
-(void)showCandidates AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Map a candidateString to an identifier.
 @discussion Beginning with MacOS 10.7, candidate strings are mapped internally to an unique identifier of type NSInteger.  Using identifiers to identify a particular candidate is the first stage of enabling data types other than NSString and NSAttributedString for containing the contents of a candidate.
 */
-(NSInteger)candidateStringIdentifier:(id)candidateString AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Returns the currently selected candidate string.
 @discussion Attempts to determine the string for the selected candidate.  If there is no selection the return value can be nil.  The attributed string is an autoreleased object.
 */
-(NSAttributedString*)selectedCandidateString AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	 Returns the candidate identifier for a given line in the candidate window display.
 @discussion Maps the lineNumber to a candidate identifier.  Line number 0 corresponds to the candidate in the cell currently in the first (top for vertical) line of the candidate window.  This is convienient for input methods that support selecting a candidate by a number key. Line Number values depend on the column arrangement of your candidate.  If you are displaying a single column candidate window, lines that have been scrolled out of view will have negative values.  For a single row grid line, numbers will correspond to the cell's position in the row (i.e. the first cell will be 0, the second 1, etc).  Finally, for a grid, the line numbers correspond to the grid row.  If the line number is invalid, NSNotFound is returned.
 @param lineNumber a number representing a cells position in the candidate window.
 */
-(NSInteger)candidateIdentifierAtLineNumber:(NSInteger)lineNumber AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Returns the line number for a given CandidateID.
 @result  The line number.  NSNotFound if the candidateID is invalid.
 @param  candidateIdentifier - A valid identifier for a candidate.
 @discussion If the cell that contains the candidate is at the top line of the candidate window, the return value will be 0.
 */
-(NSInteger)lineNumberForCandidateWithIdentifier:(NSInteger)candidateIdentifier AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method
 @abstract	Clears the current selection.
 */

-(void)clearSelection AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;




@end
