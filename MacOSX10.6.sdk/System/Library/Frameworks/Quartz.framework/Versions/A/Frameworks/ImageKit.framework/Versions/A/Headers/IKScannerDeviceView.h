//
//  IKScannerView.h
//  ImageKit
//
//  Copyright 2008 Apple Inc.. All rights reserved.
//

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

#import <Cocoa/Cocoa.h>
#import <ImageCaptureCore/ImageCaptureCore.h>

@class IKScannerDeviceView;


/*! 
 @protocol IKScannerDeviceViewDelegate
 @abstract A delegate of IKScannerDeviceView must conform to IKScannerDeviceViewDelegate protocol.
 */
@protocol IKScannerDeviceViewDelegate
@optional
/*! 
 @method scannerDeviceView:didScanToURL:fileData:error:
 @abstract This message is sent for each image that gets scanned.
 @discussion Based on the IKScannerDeviceViewTransferMode the downloaded file will be saved on disk using the 'url', or returned in memory as NSData
 */
- (void)scannerDeviceView: (IKScannerDeviceView *)scannerDeviceView didScanToURL: (NSURL *)url fileData: (NSData *)data error: (NSError *)error;

/*! 
 @method scannerDeviceView:didEncounterError:
 @abstract This message is sent every time the scanner device reports an error.
 */
- (void)scannerDeviceView: (IKScannerDeviceView *)scannerDeviceView didEncounterError: (NSError *)error;
@end




enum 
{
    IKScannerDeviceViewTransferModeFileBased = 0,
    IKScannerDeviceViewTransferModeMemoryBased
    
};
typedef NSInteger IKScannerDeviceViewTransferMode;



enum 
{
    IKScannerDeviceViewDisplayModeSimple,
    IKScannerDeviceViewDisplayModeAdvanced
};
typedef NSInteger IKScannerDeviceViewDisplayMode;




/*! 
 @class IKScannerDeviceView
 @abstract IKScannerDeviceView displays a UI to work with Image Capture supported scanners.
 */
@interface IKScannerDeviceView : NSView 
{
@private
    id _privateData;
}

/*!
 @property delegate
 @abstract delegate of the IKScannerDeviceView.
 */
@property (assign) id<IKScannerDeviceViewDelegate> delegate;

/*!
 @property scannerDevice
 @abstract the scanner device.
 */
@property (assign) ICScannerDevice * scannerDevice;

/*!
 @property mode
 @abstract current display mode.
 */
@property IKScannerDeviceViewDisplayMode mode;

/*!
 @property hasDisplayModeSimple
 @abstract support a simple scanning UI.
 */
@property BOOL hasDisplayModeSimple;

/*!
 @property hasDisplayModeAdvanced
 @abstract support advanced scanning UI.
 */
@property BOOL  hasDisplayModeAdvanced;
    
/*!
 @property transferMode
 @abstract transfer mode either file based - or - in memory.
 */
@property IKScannerDeviceViewTransferMode transferMode;

/*!
 @property scanControlLabel
 @abstract label for the 'Scan' control.
 */
@property (copy) NSString * scanControlLabel;

/*!
 @property overviewControlLabel
 @abstract label for the 'Overview' control.
 */
@property (copy) NSString *  overviewControlLabel;

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
 @property documentName
 @abstract document name.
 */
@property (copy) NSString * documentName;

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

@end

#endif

