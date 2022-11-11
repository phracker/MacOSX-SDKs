//
//  IKCameraDeviceView.h
//  ImageKit
//
//  Copyright 2008 Apple Inc.. All rights reserved.
//

#ifndef IKCameraDeviceView_h
#define IKCameraDeviceView_h

#import <Cocoa/Cocoa.h>
#import <ImageCaptureCore/ImageCaptureCore.h>
#import <ImageKit/ImageKitBase.h>

@class IKCameraDeviceView;



/*! 
 @protocol IKCameraDeviceView
 @abstract A delegate of IKCameraDeviceView must conform to IKCameraDeviceViewDelegate protocol.
 */
@protocol IKCameraDeviceViewDelegate
@optional

/*! 
 @method cameraDeviceViewSelectionDidChange:
 @abstract This message is sent when the user selection did change.
 */
- (void)cameraDeviceViewSelectionDidChange: (IKCameraDeviceView *)cameraDeviceView;

/*! 
 @method cameraDeviceView:didDownloadFile:location:fileData:error:
 @abstract This message is sent for each file that gets downloaded.
 @discussion Based on the IKCameraDeviceViewDisplayMode the downloaded file will be saved on disk using the 'url', or returned in memory as NSData
 */
- (void)cameraDeviceView: (IKCameraDeviceView *)cameraDeviceView didDownloadFile: (ICCameraFile *)file location: (NSURL *)url fileData: (NSData *)data error: (NSError *)error;

/*! 
 @method cameraDeviceView:didEncounterError:
 @abstract This message is sent every time the camera device reports an error.
 */
- (void)cameraDeviceView: (IKCameraDeviceView *)cameraDeviceView didEncounterError: (NSError *)error;
@end




typedef NS_CLOSED_ENUM(NSInteger, IKCameraDeviceViewDisplayMode)
{
    IKCameraDeviceViewDisplayModeNone = -1,
    IKCameraDeviceViewDisplayModeTable = 0,
    IKCameraDeviceViewDisplayModeIcon
    
};

typedef NS_CLOSED_ENUM(NSInteger, IKCameraDeviceViewTransferMode)
{
    IKCameraDeviceViewTransferModeFileBased = 0,
    IKCameraDeviceViewTransferModeMemoryBased
    
};




/*! 
 @class IKCameraDeviceView
 @abstract IKCameraDeviceView displays content of a Image Capture supported camera.
 */
IK_CLASS_AVAILABLE(10.6)
@interface IKCameraDeviceView : NSView
{
@private
    id _privateData;
}

/*!
 @property delegate
 @abstract Delegate of the IKCameraDeviceView.
 */
@property (assign) IBOutlet id<IKCameraDeviceViewDelegate> delegate;

/*!
 @property cameraDevice
 @abstract the camera device.
 */
@property (assign) ICCameraDevice * cameraDevice;

/*!
 @property mode
 @abstract current display mode.
 */
@property IKCameraDeviceViewDisplayMode mode;

/*!
 @property hasDisplayModeTable
 @abstract support table view display mode.
 */
@property BOOL hasDisplayModeTable;

/*!
 @property hasDisplayModeIcon
 @abstract support icon view display mode.
 */
@property BOOL hasDisplayModeIcon;

/*!
 @property downloadAllControlLabel
 @abstract label for the 'Download All' control - allows for example renaming to 'Import All'.
 */
@property (copy) NSString * downloadAllControlLabel;

/*!
 @property downloadSelectedControlLabel
 @abstract label for the 'Download Selected' control.
 */
@property (copy) NSString * downloadSelectedControlLabel;

/*!
 @property iconSize
 @abstract in icon mode: size of the image thumbnails.
 */
@property NSUInteger iconSize;

/*!
 @property transferMode
 @abstract transfer mode either file based - or - in memory.
 */
@property IKCameraDeviceViewTransferMode transferMode;

/*!
 @property displaysDownloadsDirectoryControl
 @abstract show a downloads directory control.
 */
@property BOOL displaysDownloadsDirectoryControl;

/*!
 @property downloadsDirectory
 @abstract downloads directory.
 */
@property (retain) NSURL * downloadsDirectory;

/*!
 @property displaysPostProcessApplicationControl
 @abstract show a postprocessing application control.
 */
@property BOOL displaysPostProcessApplicationControl;

/*!
 @property postProcessApplication
 @abstract postprocessing application.
 */
@property (retain) NSURL * postProcessApplication;

/*!
 @property canRotateSelectedItemsLeft
 @abstract indicates if the user selected items can be rotated left.
 */
@property (readonly) BOOL canRotateSelectedItemsLeft;

/*!
 @property canRotateSelectedItemsRight
 @abstract indicates if the user selected items can be rotated right.
 */
@property (readonly) BOOL canRotateSelectedItemsRight;

/*!
 @property canDeleteSelectedItems
 @abstract indicates if the user selected items can be deleted.
 */
@property (readonly) BOOL canDeleteSelectedItems;

/*!
 @property canDownloadSelectedItems
 @abstract indicates if the user selected items can be downloaded.
 */
@property (readonly) BOOL canDownloadSelectedItems;

/*!
 @method selectedIndexes
 @abstract current user selection.
 */
- (NSIndexSet *)selectedIndexes;

/*!
 @method selectIndexes:byExtendingSelection:
 @abstract setting current user selection.
 */
- (void)selectIndexes: (NSIndexSet *)indexes byExtendingSelection: (BOOL)extend;

/*!
 @method rotateLeft:
 @abstract rotate selected items left.
 */
- (IBAction)rotateLeft: (id)sender; 

/*!
 @method rotateRight:
 @abstract rotate selected items right.
 */
- (IBAction)rotateRight: (id)sender;

/*!
 @method deleteSelectedItems:
 @abstract delete selected items.
 */
- (IBAction)deleteSelectedItems: (id)sender;

/*!
 @method downloadSelectedItems:
 @abstract download selected items.
 */
- (IBAction)downloadSelectedItems: (id)sender;

/*!
 @method downloadAllItems:
 @abstract download all items.
 */
- (IBAction)downloadAllItems: (id)sender;


/*!
 @method setCustomIconSizeSlider:
 @abstract provide your own NSSlider to resize item thumbnails
 */
- (void)setCustomIconSizeSlider: (NSSlider*)slider;

/*!
 @method setCustomModeControl:
 @abstract provide your own control to toggle between IKCameraDeviceViewDisplayMode table / icon
 */
- (void)setCustomModeControl: (NSSegmentedControl*)control;

/*!
 @method setCustomActionButton:
 @abstract provide your own control to toggle between IKCameraDeviceViewDisplayMode table / icon
 */
- (void)setCustomActionControl: (NSSegmentedControl*)control;

/*!
 @method setCustomRotateButton:
 @abstract provide your own control to rotate items (multiple of 90º)
 */
- (void)setCustomRotateControl: (NSSegmentedControl*)control;

/*!
 @method setCustomDeleteControl:
 @abstract provide your own control to delete selected items
*/
- (void)setCustomDeleteControl: (NSSegmentedControl*)control;

/*!
 @method setShowStatusInfoAsWindowSubtitle:
 @abstract display status info as window subtitle
 */
- (void)setShowStatusInfoAsWindowSubtitle: (BOOL)value;

@end

#endif
