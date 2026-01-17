//
//  InstallerPane.h
//  InstallerSection
//
//  Created by Christopher Ryan on Mon Dec 01 2003.
//  Copyright (c) 2003 Apple Computer. All rights reserved.
//

/*!
    @header InstallerPane
    @discussion Contains the InstallerPane class definition
*/


#import <Cocoa/Cocoa.h>

/*!
    @enum InstallerSectionDirection
    @discussion Describes the direction in which a pane is entered or exited.
    @constant   InstallerDirectionForward Specifies that the pane was entered/exited while moving in the forward direction.
	@constant   InstallerDirectionBackward Specifies that the pane was entered/exited while moving backwards.
	@constant   InstallerDirectionUndefined Specifies that the pane was entered/exited using the gotoPane: method.  Since the pane
				is "jumped" to rather then moved to going forward or back, InstallerDirectionUndefined is used.
*/

typedef enum{
	InstallerDirectionForward = 0,
	InstallerDirectionBackward,
	InstallerDirectionUndefined
} InstallerSectionDirection;

#pragma mark -

@class InstallerSection;

/*!
    @class		InstallerPane
    @discussion InstallerPane represents one display element of an InstallerSection within the Installer's UI.
				When a InstallerPane is entered the subviews from contentView are placed on the screen
				and made active.  If defined, the initialKeyView is set as key and the keyView chain
				is setup using the firstKeyView and lastKeyView outlets.
 
				Since the InstallerPane's parent InstallerSection is not defined until the pane is first diplayed,
				the parentSection outlet can be connected within the nib in which the InstallerPane is loaded
				in order to have access to the parent section at an earlier time.
*/

typedef struct InstallerPane_Private InstallerPane_Private;

@interface InstallerPane : NSObject {
	@private
		IBOutlet NSView *contentView;
	
		IBOutlet NSView *initialKeyView;
		IBOutlet NSView *firstKeyView;
		IBOutlet NSView *lastKeyView;
	
		IBOutlet InstallerPane	*nextPane;
		
		IBOutlet id				parentSection;
	
		InstallerPane_Private	*_private;
}

/*!
    @method     initWithSection
    @discussion Init method for InstallerPane.  This method takes it's parent section as an argument.
*/
- (id)initWithSection:(id)parent;

/*!
    @method     title
    @discussion Title text for the pane while being displayed.  The title is retrieved and displayed
				every time a pane is entered.  The title must be vaild after the willEnter method is called.
 
				You must override this method if you would like a title for a custom pane.
*/
- (NSString *)title;

/*!
    @method     section
    @discussion The parent section for this pane.
*/
- (InstallerSection *)section;
   
/*!
    @method     contentView
    @discussion Returns the contentView outlet.  ContentView is used to determine what is to
				be displayed on screen when this pane is active.  The contentView must be the 
				same view when the pane is exited, as when the pane is first entered.
	
				Subclasses can override this method to return dynamic views which are not loaded
				from a nib.
*/
- (NSView *)contentView;

/*!
    @method     initialKeyView
    @discussion Returns the view that should have the keyboard focus when the pane is entered.
				This method returns the initialKeyView outlet.  This outlet should be connected
				in the nib containing the pane.
				
				A subclass can override this method to return a dynamically defined initialKeyView.
*/
- (NSView *)initialKeyView;


/*!
    @method     firstKeyView
	@discussion Returns the view that should first have keyboard focus when the content view of the pane
				first becomes key.  This method returns the firstKeyView outlet.  This outlet should be connected
				in the nib containing the pane.
	 
				A subclass can override this method to return a dynamically defined firstKeyView.
*/
- (NSView *)firstKeyView;

/*!
	@method     lastKeyView
	@discussion Returns the lastKeyView which has focus before the contentView of the pane is no longer
				the key view.
	 
				A subclass can override this method to return a dynamically defined lastKeyView.
*/
- (NSView *)lastKeyView;

/*!
    @method     nextPane
    @discussion Returns the next InstallerPane to follow this one.  Set the nextPane outlet in a nib to define
				a default nextPane.
 
				A subclass may want to override nextPane if the pane determines it's nextPane dynamically.
*/
- (InstallerPane *)nextPane;

/*!
    @method     willEnterPane:
    @discussion Called immediatly before the InstallerPane is displayed on the screen.
	@param		dir The direction in which the pane will be entered from
*/
- (void)willEnterPane:(InstallerSectionDirection)dir;

/*!
	@method     didEnterPane:
	@discussion Called immediatly after the InstallerPane is displayed on the screen.
	@param		dir The direction in which the pane was entered
*/
- (void)didEnterPane:(InstallerSectionDirection)dir;

/*!
	@method     shouldExitPane:
	@discussion Called to determine if a pane should exit and allow another pane to be display on screen.
				
				A subclass should override this method if it needs to prevent the InstallerPane from exiting.
				
				Once the InstallerPane decides it is time to exit, it can call gotoNextPane or gotoPreviousPane
				to exit without calling shouldExitPane again.
 
	@param		dir The direction in which the pane was entered
	@result		Yes or No defining if the pane should really exit
*/
- (BOOL)shouldExitPane:(InstallerSectionDirection)dir;

/*!
	@method     willExitPane:
	@discussion Called immediatly before the InstallerPane will exit and be removed from the screen.
	@param		dir The direction in which the pane will exit to
*/
- (void)willExitPane:(InstallerSectionDirection)dir;

/*!
	@method     willExitPane:
	@discussion Called immediatly after the InstallerPane has exited and has been removed from the screen.
	@param		dir The direction in which the pane exited
*/
- (void)didExitPane:(InstallerSectionDirection)dir;


/*!
	@method     setNextEnabled:
	@discussion Call this method to enable or disable the user from leaving this InstallerSection pane in the forward
				direction. Subclasses should not override this method.
*/
- (void)setNextEnabled:(BOOL)enabled;

/*!
	@method     nextEnabled
	@discussion Specifies whether going to the next pane is enabled in the UI.
*/
- (BOOL)nextEnabled;

/*!
	@method     setPreviousEnabled:
	@discussion Call this method to enable or disable the user from leaving this InstallerSection pane in the backward
	 direction. Subclasses should not override this method.
*/
- (void)setPreviousEnabled:(BOOL)enabled;

/*!
	@method     previousEnabled
	@discussion Specifies whether going to the previous pane is enabled in the UI.
*/
- (BOOL)previousEnabled;

/*!
    @method     gotoNextPane
    @discussion Causes the current pane to exit and the following pane available to be loaded.  gotoNextPane causes this pane's
				shouldExit: method to be skipped.
	@result		gotoNextPane will return NO if there is no nextPane (in any sections) or there is an error loading the nextPane.
*/
- (BOOL)gotoNextPane;

//  gotoPreviousPane resign's active for the current pane and causes the previous
//  pane to become active
/*!
	@method     gotoPreviousPane
	@discussion Causes the current pane to exit and the previous pane in the Installer's Pane Stack to be displayed.  
				gotoNextPane causes this pane's shouldExit: method to be skipped.
	@result		gotoPreviousPane will return NO if there is no previous (in any sections) or there is an error loading the previousPane.
*/
- (BOOL)gotoPreviousPane;
@end
