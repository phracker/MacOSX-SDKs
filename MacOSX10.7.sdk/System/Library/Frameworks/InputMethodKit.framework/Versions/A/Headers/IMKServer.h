/*
	IMKServer.h
	Input Method Kit
	Copyright (c) 2006, Apple Computer, Inc.
	All rights reserved.
*/

/*!
	@header
	
	@abstract	An IMKServer represents your input method to the rest of the system.  Every input method should create one in the input method's main function.
	
	@discussion Your IMKServer will manage connections to clients.  You should never have to override this class.
	
	@availability	10.5 and later.
*/
#import <Foundation/Foundation.h>
#import <Carbon/Carbon.h>


@class IMKInputController;
@protocol IMKServerProxy;

// This is for the candidate window event sending stuff

/*!
    @const      IMKModeDictionary
    @abstract   Key used to obtain an input method's mode dictionary from the input method's bundle.
*/
extern const NSString*	IMKModeDictionary;

/*!
    @const      IMKControllerClass
    @abstract   Key used to find an input method's input controller class name from the input method's bundle.
*/
extern const NSString*	IMKControllerClass;

/*!
    @const      IMKDelegateClass
    @abstract   Key used to find an input method's delegate class name from the input method's bundle.
*/
extern const NSString*	IMKDelegateClass;

@class IMKServerPrivate;


/*!
    @class      IMKServer
    @abstract   This class manages input sessions.
    @discussion An input method should create one and only one of these objects.  An IMKServer creates an NSConnection that can be connected to by input clients.  After a connection has been made an IMKServer manages communication between the client and the input method.  For each communication session the IMKServer will create an IMKInputController class as well as delegate classes for that controller.  Each controller object then serves as a proxy for the input session on the client side.  This means that input methods do not have to concern themselves with managing client sessions.  A given controller will only receive communication from a single session.
    
    			IMKServer's also will manage a basic candidate window for an input method.  See IMKCandidates.h to understand how to create a candidate window and associate the candidate window with the IMKServer object.
*/
@interface IMKServer : NSObject <IMKServerProxy> {
@private
      IMKServerPrivate			*_private;
}

/*!
    @method     
    @abstract   Create a IMKServer from information in the bundle's Info.plist.
    @discussion This method will look into the info.plist for a controller class and delegate class.  The class names will be loaded, no classes will be instantiated.  Additionally, an NSConnection will be allocated and registered with the name parameter.
                
*/
- (id)initWithName:(NSString*)name bundleIdentifier:(NSString*)bundleIdentifier;

/*!
    @method    
    @abstract   Creates an IMKServer using the parameters.
    @discussion This method creates an IMKServer object without attempting to examine the bundle instead the class names provided as parameters are used to create input controller objects and delegate objects.
                
*/
- (id)initWithName:(NSString*)name  controllerClass:(Class)controllerClassID delegateClass:(Class)delegateClassID;


/*!
    @method     
    @abstract   Returns an NSBundle for the input method.
    @discussion If the IMKServer contains a bundle identifier the NSBundle is created from that.  Otherwise, the bundle  is created for the main bundle.  The returned NSBundle is an autoreleased object.
*/
- (NSBundle*)bundle;

/*!
 @method     
 @abstract   Call this before terminating a palette IM.
 @discussion Palettes need to be able to terminate.  When this method is called the IMKServer will notify each client of the palette that
			 the palette is about to terminate.  The palette can terminate safely if a value of YES is returned.  If the caller of this method is not
			 an input method of type palette an exception will be thrown.
 
			 If the method returns NO the palette should not terminate.  
 */
-(BOOL)paletteWillTerminate AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method     
 @abstract   Returns a BOOL indicating whether or not the last key press was a dead key.
 */
- (BOOL)lastKeyEventWasDeadKey AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;;



@end
