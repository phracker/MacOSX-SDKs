//
//  IKPictureTaker.h
//  ImageKit
//
//  Copyright (c) 2006 Apple Inc. All rights reserved.
//

/*!
	@header IKPictureTaker
    PictureTaker is a panel that let users choosing and cropping images.
*/

#import <AppKit/AppKit.h>
#import <ImageKit/ImageKitBase.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5


/*! 
  @class IKPictureTaker
  @abstract An IKPictureTaker object is a panel that allows users to choose and crop an image. It supports browsing of the file system and includes a recents popup-menu. The IKPictureTaker lets the user to crop a choosen image or to take snapshot from a camera like the built-in iSight. 
*/

@interface IKPictureTaker : NSPanel
{
@private
    void * _ikReserved;
}

/*!
  @method pictureTaker
  @abstract Returns the shared IKPictureTaker instance, creating it if necessary.
*/
+ (IKPictureTaker *) pictureTaker NS_SWIFT_NAME(pictureTaker());

/*!
  @method runModal
  @abstract Launches a modal PictureTaker session.
  @result Returns NSOKButton if the user edits or chooses an image and confirm panel, NSCancelButton if the user canceled or didn't change the image.
*/
- (NSInteger) runModal;

/*!
  @method beginPictureTakerWithDelegate:didEndSelector:contextInfo:
  @abstract Launch the PictureTaker.
  @param delegate the object to invoke didEndSelector when the PictureTaker terminates.
  @param didEndSelector the selector to invoke when the PictureTaker terminates.
  @param contextInfo Any data that will be passed as an argument to the delegate through didEndSelector after the session has ended.
  @discussion didEndSelector should have the following signature: - (void)pictureTakerDidEnd:(IKPictureTaker *)pictureTaker returnCode:(NSInteger)returnCode contextInfo:(void  *)contextInfo;
  returnCode value is set to NSOKButton if the user validate, or to NSCancelButton if the user cancel.
*/
- (void) beginPictureTakerWithDelegate:(id) delegate didEndSelector:(SEL) didEndSelector contextInfo:(void *) contextInfo; 

/*!
  @method beginPictureTakerSheetForWindow:withDelegate:didEndSelector:contextInfo:
  @abstract Launch the PictureTaker as a sheet for aWindow
  @param delegate the object to invoke didEndSelector when the PictureTaker terminates 
  @param didEndSelector the selector to invoke when the PictureTaker terminates 
  @param contextInfo Any data that will be passed as an argument to the delegate through didEndSelector after the session has ended
  @discussion didEndSelector should have the following signature: - (void)pictureTakerDidEnd:(IKPictureTaker *)pictureTaker returnCode:(NSInteger)returnCode contextInfo:(void  *)contextInfo;
  returnCode value is set to NSOKButton if the user validate, or to NSCancelButton if the user cancel.
*/
- (void) beginPictureTakerSheetForWindow:(NSWindow *)aWindow withDelegate:(id) delegate didEndSelector:(SEL) didEndSelector contextInfo:(void *) contextInfo; 

/*!
  @method popUpRecentsMenuForView:withDelegate:didEndSelector:contextInfo:
  @abstract Launch the PictureTaker's recent popup.
  @param delegate the object to invoke didEndSelector when the PictureTaker terminates.
  @param didEndSelector the selector to invoke when the PictureTaker terminates.
  @param contextInfo Any data that will be passed as an argument to the delegate through didEndSelector after the session has ended.
  @discussion didEndSelector should have the following signature: - (void)pictureTakerDidEnd:(IKPictureTaker *)pictureTaker returnCode:(NSInteger)returnCode contextInfo:(void  *)contextInfo;
  returnCode value is set to NSOKButton if the user validate, or to NSCancelButton if the user cancel.
*/
- (void) popUpRecentsMenuForView:(NSView *) aView withDelegate:(id) delegate didEndSelector:(SEL) didEndSelector contextInfo:(void *) contextInfo; 

/*!
  @method setInputImage:
  @abstract Set the image input for the PictureTaker.
  @param image A valid NSImage.
  @discussion The input image is never modified by the PictureTaker.
*/
- (void) setInputImage:(NSImage *) image;

/*!
  @method inputImage
  @abstract return the original PictureTaker's input-image.
  @discussion The input image is never modified by the PictureTaker.
*/
- (NSImage*) inputImage;

/*!
  @method outputImage
  @abstract return the edited image.
*/
- (NSImage*) outputImage;

/*!
 @method setMirroring:
 @abstract Controls whether the receiver enable/disable video mirroring durring snapshots (default is YES).
 */
- (void) setMirroring:(BOOL)b;

/*!
 @method mirroring
 @abstract Returns YES if video mirroring is enabled, NO otherwise.
 */
- (BOOL) mirroring;

@end



/* use - (void) setValue:(id)aValue forKey:(id) aKey (NSKeyValueCoding) to customize the pictureTaker panel appearance and behaviors
 *
 *   <key>                                    <class>						 <default>
 *   IKPictureTakerAllowsVideoCaptureKey	  NSNumber(BOOL)					YES
 *   IKPictureTakerAllowsFileChoosingKey	  NSNumber(BOOL)					YES
 *   IKPictureTakerShowRecentPictureKey		  NSNumber(BOOL)					YES
 *   IKPictureTakerUpdateRecentPictureKey     NSNumber(BOOL)					YES
 *   IKPictureTakerAllowsEditingKey           NSNumber(BOOL)					YES
 *   IKPictureTakerShowEffectsKey			  NSNumber(BOOL)					NO
 *   IKPictureTakerInformationalTextKey		  NSString or NSAttributedString    "Drag Image Here"
 *   IKPictureTakerImageTransformsKey         NSDictionary(serializable)		none
 *   IKPictureTakerOutputImageMaxSizeKey      NSValue(NSSize)				    none
 *   IKPictureTakerShowAddressBookPictureKey  NSNumber(BOOL)					NO
 *   IKPictureTakerShowEmptyPictureKey        NSImage						    nil
 *   IKPictureTakerRemainOpenAfterValidateKey NSNumber(BOOL)					NO
 */
extern NSString *const IKPictureTakerAllowsVideoCaptureKey;
extern NSString *const IKPictureTakerAllowsFileChoosingKey;
extern NSString *const IKPictureTakerShowRecentPictureKey;
extern NSString *const IKPictureTakerUpdateRecentPictureKey;
extern NSString *const IKPictureTakerAllowsEditingKey;
extern NSString *const IKPictureTakerShowEffectsKey;
extern NSString *const IKPictureTakerInformationalTextKey;
extern NSString *const IKPictureTakerImageTransformsKey;
extern NSString *const IKPictureTakerOutputImageMaxSizeKey;
extern NSString *const IKPictureTakerShowAddressBookPictureKey;
extern NSString *const IKPictureTakerShowEmptyPictureKey;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
extern NSString *const IKPictureTakerRemainOpenAfterValidateKey;
#endif

#endif

