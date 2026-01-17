//
//  ImageKitDeprecated.h
//  ImageKit
//
//  Copyright 2006 Apple. All rights reserved.
//


@interface NSObject (IKImageBrowserDataSourceDeprecated)

- (NSUInteger) numberOfCellsInImageBrowser:(IKImageBrowserView *) aBrowser;
- (id /*IKImageBrowserItem*/) imageBrowser:(IKImageBrowserView *) aBrowser cellAtIndex:(NSUInteger)index;
- (void) imageBrowser:(IKImageBrowserView *) aBrowser removeCellsAtIndexes:(NSIndexSet *) indexes; 
- (BOOL) imageBrowser:(IKImageBrowserView *) aBrowser moveCellsAtIndexes: (NSIndexSet *)indexes toIndex:(NSUInteger)destinationIndex;
- (void) imageBrowser:(IKImageBrowserView *) aBrowser writeCellsAtIndexes:(NSIndexSet *) itemIndexes toPasteboard:(NSPasteboard *)pasteboard;

@end


@interface IKImagePicker : IKPictureTaker
{
}

+ (IKImagePicker *) imagePicker;
- (void) beginImagePickerWithDelegate:(id) delegate didEndSelector:(SEL) didEndSelector contextInfo:(void *) contextInfo; 
- (void) beginImagePickerSheetForWindow:(NSWindow *)aWindow withDelegate:(id) delegate didEndSelector:(SEL) didEndSelector contextInfo:(void *) contextInfo; 

@end

#define IKImagePickerAllowsVideoCaptureKey IKPictureTakerAllowsVideoCaptureKey
#define IKImagePickerAllowsFileChoosingKey IKPictureTakerAllowsFileChoosingKey
#define IKImagePickerShowRecentPictureKey IKPictureTakerShowRecentPictureKey
#define IKImagePickerUpdateRecentPictureKey IKPictureTakerUpdateRecentPictureKey
#define IKImagePickerAllowsEditingKey IKPictureTakerAllowsEditingKey
#define IKImagePickerShowEffectsKey IKPictureTakerShowEffectsKey
#define IKImagePickerInformationalTextKey IKPictureTakerInformationalTextKey
#define IKImagePickerImageTransformsKey IKPictureTakerImageTransformsKey
#define IKImagePickerOutputImageMaxSizeKey IKPictureTakerOutputImageMaxSizeKey
#define IKImagePickerCropAreaSizeKey IKPictureTakerCropAreaSizeKey

extern NSString *const IKPictureTakerShowAddressBookPicture;
extern NSString *const IKPictureTakerShowEmptyPicture;


/* old types for layerForType: */
extern NSString *const IKImageBrowserCellLayerTypeBackground;
extern NSString *const IKImageBrowserCellLayerTypeForeground;
extern NSString *const IKImageBrowserCellLayerTypeSelection;
extern NSString *const IKImageBrowserCellLayerTypePlaceHolder;
