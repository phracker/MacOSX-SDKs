//
//  InstallerSection.h
//  InstallerSection
//
//  Created by Christopher Ryan on Mon Dec 01 2003.
//  Copyright (c) 2003 Apple Comptuer. All rights reserved.
//
/*!
    @header InstallerSection
    @discussion Contains the InstallerSection class definition
*/

#import <Foundation/Foundation.h>
#import "InstallerPane.h"

/*!
    @class		InstallerSection
    @abstract   An object representing a specific Section of the Installer's UI.
	@discussion The InstallerSection class declares an interface for a section within the Installer's UI.
 
				The InstallerSection is the main controller of this section and contains all the panes which
				are actually displayed in the Installer's UI.  The InstallerSection itself does not display
				anything, but rather provides the InstallerPanes which do.
 
				Each InstallerSection (or subclass) must be within its own bundle.  The NSPrincipalClass for
				this bundle must be specified as an InstallerSection or a subclass.
 
				Typically an InstallerSection is not subclassed because most of the functionality can be
				provided through the Info.plist and the default nib.
 
				The default nib for a section is specified by the NSMainNibFile key in the Info.plist
				for the section's bundle.
 
				The title for the section is specified by the InstallerSectionTitle key.				
*/

@class InstallerState;

typedef struct InstallerSection_Private InstallerSection_Private;

@interface InstallerSection : NSObject{	
	@private
		IBOutlet InstallerPane		*firstPane;
		
	InstallerSection_Private   *_private;
}

/*!
	@method     bundle
	@discussion This method returns the NSBundle in which the InstallerSection is located.  Since InstallerSection is not
				typically overriden, the bundle returned may not necessarily be the same bundle as the InstallerSection
				class.  
			
				Use this method to gain access to bundle resources.
*/
- (NSBundle *)bundle;

/*!
    @method		title
    @discussion Returns the title for the section defined in the Info.plist file for the section's bundle.  The title
				retrieved using the "InstallerSectionTitle" key in the Info.plist for the section's bundle and that key must
				be present in the InfoPlist.strings file for title to be localized.
	
				Although subclasses can override this method and return a dynamic title at runtime, the title is only
				retrieved for display once (immediatly following the shouldLoad method, if shouldLoad returns YES).
*/
- (NSString *)title;


/*!
    @method     firstPane
    @discussion Returns the first pane specified by the firstPane outlet.  This pane is the first
				pane entered when the section first becomes active.
*/
- (InstallerPane *)firstPane;

/*!
	@method     shouldLoad
	@discussion Called when a section is first about to be fully loaded.  By default this method
				returns YES.  A Subclass can override this method and determine at runtime if the
				section makes sense.  Return NO and the section will not be further loaded.  sections are
				never fully unloaded.
*/
- (BOOL)shouldLoad;

/*!
    @method willLoadMainNib
    @discussion Each InstallerSection object can define a default nib to be loaded by the Installer at the optimal
				time.  Before this default nib is loaded willLoadMainNib will be called.  didLoadMainNib is
				called when the nib is successfully loaded.  The nib may be loaded way before the content
				is display on the screen, so awakeFromNib methods should not assume the content is displayed
				to the user.  WillEnter/DidEnter method should be used to determine when views are actually "in view."
				
				A default nib is specified for a section in the Info.plist for the section using the NSMainNibFile key.
				
				A subclass can override this method to do any necessary work before the main nib is loaded or
				to actually load a custom nib if no default nib is specified.
*/
- (void)willLoadMainNib;

/*!
    @method     didLoadMainNib
    @discussion Called immediatly after the default nib for the section is loaded.  If no default nib is specified,
				didLoadMainNib is called immediatly after willLoadMainNib is called.
 
				didLoadMainNib is called before the section's panes are in view.
 
*/
- (void)didLoadMainNib;

/*!
    @method		sharedDictionary
    @discussion A global Mutable Dictionary which is global to the Install session.  Use this dictionary to pass information
				between sections.
 
				This dictionary should not be used to store state for your section or it's panes.
*/
- (NSMutableDictionary *)sharedDictionary;

/*!
    @method     installerState
    @abstract   Returns the Installer State object for the current install session.
    @discussion Returns an object which describes the Installer choices and status 
 				at the given time.  Plugins cannot influence this state, it should only
 				be used for informational purposes.  See InstallerState.h for more details.
*/
- (InstallerState *)installerState;

/*!
    @method     activePane
    @abstract   Returns the current active page for this section.
    @discussion If the section is active, it will return the current active page.  If the section
				is not active, nil will be returned.
*/
- (InstallerPane *)activePane;

/*!
    @method     gotoPane:
    @discussion This method causes the current pane to exit and "pane" to be made active.  This effectively replaces the current
				pane and does not place the current pane onto the pane stack.
 
				gotoPane does not invoke shouldExit method for the current pane.
 
				gotoPane is typically not overriden by a subclass.
*/
- (BOOL)gotoPane:(InstallerPane *)pane;

@end
