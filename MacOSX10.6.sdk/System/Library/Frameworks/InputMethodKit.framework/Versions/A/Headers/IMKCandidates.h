/*
	IMKCandidates.h
	Input Method Kit
	Copyright (c) 2006, Apple Computer, Inc.
	All rights reserved.
*/

/*!
	@header
	
	@abstract	Provides basic candidate window management.
	
	@discussion	If you want to use candidate windows in your input method you create a IMKCandidates objects and attach it to your IMKServer object.  You then need to override the IMKInputConroller methods candidateSelectionChanged: and candidateSelected: as well as implement a candidates method in your delegate object.  When you are ready do display a candidate window call the method [IMKCandidates updateCandidates] and then call [IMKCandidates show].
	
	@availability System 10.5 and later.
*/

#include <Foundation/Foundation.h>


/*!
    @enum		IMKCandidatePanelType
    @abstract   Lists the basic candidate panel types that are supplied by the InputMethodKit.
*/
enum {
	kIMKSingleColumnScrollingCandidatePanel		=	1,
	kIMKScrollingGridCandidatePanel				=	2,
	kIMKSingleRowSteppingCandidatePanel			=	3
};
typedef NSUInteger IMKCandidatePanelType;

/*!
    @enum		IMKCandidatesLocationHint
    @abstract   Provides a hint where to place the candidates display.
    @discussion The IMKCandidatePanelType will use the hint to place the candidate display being sure that the display is always fully visible.
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
	
	@discussion	Value is a NSNumber with a boolean value of NO (keyevents are sent to the candidate window first) or YES (keyevents are sent to the IMKInputController first). Note this is only applicable when a candidate window is displayed.  The default behavior is to send the key event to the candidate window first.  Then if it is not processed there to send it on to the input controller.
*/
extern const NSString*	IMKCandidatesSendServerKeyEventFirst;



@class IMKServer;
@class IMKCandidatesPrivate;

/*!
    @class     IMKCandidates
    @abstract   Manages the display of candidates and potentially candidate annotations.
    @discussion An input method can use this object to display candidates and annotations.  The input method should call show to display the candidates.  The IMKCandidates will call back to the IMKInputController's candidates method to obtain the array of candidates to display.  The IMKCandidates class takes care of placing and drawing the candidates. Typically candidates will be displayed in a window, but window's are purposely not mentioned in the class since in the future candidates might be displayed in some different way.
*/
@interface IMKCandidates : NSObject {
	@protected
		IMKCandidatesPrivate	*_private;
}


/*!
    @method     
    @abstract   Default initializer for the class.
    @discussion When an input method allocates an IMKCandidate object is should initialize that object by calling this method passing the IMKServer that will manage the candiates and the initial panel type.
*/
-(id)initWithServer:(IMKServer*)server panelType:(IMKCandidatePanelType)panelType;

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
    @abstract   If a candidate window type has been provided show the candidate window. The caller provides a location hint that is used to position the window.
				
				Input method's call this method when it is appropriate during text conversion to display a list of candidates.  
*/
- (void)show:(IMKCandidatesLocationHint)locationHint;

/*!
    @method     
    @abstract   If the candidate window is visible hide it.
*/
- (void)hide;

/*!
    @method     
    @abstract   Utility method returns YES if a candidate display is visble.
*/
- (BOOL)isVisible;


/*!
    @method     
    @abstract   Call this method to update the candidates displayed in the candidate window.
    @discussion Calling this method will result in a call being made to the IMKInputController's candidates method. Note that the candidate list will be updated, but the window's visible state will not change.  That is to say if the window is hidden it will remain hidden and vice versa.
*/
-(void)updateCandidates;


/*!
    @method     
    @abstract   Displays an annotation window whose contents are the annotationString.
    @discussion An annotation is additional text that explains or somehow adds to the candidate string in a candidate window. Annotations are displayed in a small borderless window that is aligned with the current candidate panel. An input method calls showAnnotation: when the method [IMKInputController candidateSelectionChanged:] is called, and the candidateString has annotations.  
*/
-(void)showAnnotation:(NSAttributedString*)annotationString;



#pragma mark __Appearance__


/*!
    @method     
    @abstract   Set the selection keys for the candidates.
    @discussion Selection keys are an array of NSNumbers where each NSNumber is a virtual key codes that the controller will map to characters that are displayed either across the top of the candidates, if the candidates are laid out horizontally, or along the left edge of the candidates if they are aligned vertically.  
    
    The number of selection keys determines how many candidates are displayed per page.  For example, if you
    passed an array of 4 key codes then 4 candidates are displayed per page.  If you passed 11 key codes then 11 candidates would be displayed.
    
    By default the key codes are mapped using the keyboard layout whose source id is com.apple.keylayout.US.  The default layout can be replaced by calling
    setSelectionKeysKeylayout (see below).
    
    The default selection keys are the digits 1 through 9 or in terms of key codes: 18-21,23,22, 26, 28, 25.
*/
-(void)setSelectionKeys:(NSArray*)keyCodes;

/*!
    @method     
    @abstract   Returns an NSArray of NSNumbers where each NSNumber is a virtual key code.
				
				The NSArray is an autorelease object. Do not release unless it is first retained.
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
				
				This is an autorelease object.  Retain it if you need to keep it.
*/
-(TISInputSourceRef)selectionKeysKeylayout;

/*!
    @method     
    @abstract   Sets the "style" attributes for the candidates window.  The keys for the attributes dictionary and the values are:
    
   NSFontAttributeName (value = NSFont)  Setting the font attribute sets the font that is used to draw Candidates.  It does not effect the selection keys which are always drawn in the same font.  Note that to set the font size you should use this key/value pair.
   
   IMKCandidatesOpacityAttributeName (value = NSNumber with a float value between 0 and 1).  Sets the opacity level to transparent (0.0) to completely opaque (1.0). The default opacity is 1.0.  This constant is declared above.
   
   NSForegroundColorAttributeName (value = NSColor) Sets the text color used for the candidate text.  By default it is black.
   
   NSBackgroundColorDocumentAttribute (value = NSColor).  Set the background color that is drawn behind the candidate text.
   
   IMKCandidatesSendServerKeyEventFirst (value = NSNumber).  NO (default) gives the candidate window first chance at key events.  YES causes events to first be routed to the current IMKInputController.  In that case, if the event is not handled it will then be sent to the candidate window.
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
    @abstract   Setting the dismissesAutomatically flag determines what happens to displayed candidates when the return key or enter key is typed.  @discussion By default if a return or enter key is typed the candidates are dismissed and a candidateSelected: message is sent to the input controller.  However if  setDismissesAutomatically is passed a NO flag  the candidate display will not be dismissed when a return or enter key is typed.  The input controller will still be sent the candidatesSelected: message, but, as stated, the candidates display will not be dismissed.  
    
    Setting this flag to NO lets an input method process text input while keeping a dynamically changing candidates display in view throughout the text input process.
    
    When you set this to NO the candidate display will still be hidden when when a session deactivates.
*/
-(void)setDismissesAutomatically:(BOOL)flag;

/*!
    @method     
    @abstract   Returns the dismissesAutomatically flag.
*/
-(BOOL)dismissesAutomatically;

@end
