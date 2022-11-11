/*
    IKImageEditPanel.h
    ImageKit Framework
    Copyright (c) 2006 - 2008, Apple, Inc.
    All rights reserved.
 */

#ifndef IKImageEditPanel_h
#define IKImageEditPanel_h

#import <AppKit/NSPanel.h>
#import <ApplicationServices/ApplicationServices.h>
#import <ImageKit/ImageKitBase.h>

@class IKImageEditPanel;

/*! 
 @protocol IKImageEditPanelDataSource
 @abstract The data source of IKImageEditPanel must conform to IKImageEditPanelDataSource protocol.
 */
@protocol IKImageEditPanelDataSource

@required
/*! 
 @method image
 @abstract Returns an image.
 */
- (CGImageRef)image;

/*! 
 @method setImage:imageProperties:
 @abstract Sets an image with the specifies properties.
 */
- (void)setImage: (CGImageRef)image
 imageProperties: (NSDictionary *)metaData;

@optional

/*! 
 @method thumbnailWithMaximumSize:
 @abstract Returns a thumbnail image whose size is no larger than the specified size.
 */
- (CGImageRef)thumbnailWithMaximumSize: (NSSize)size;

/*! 
 @method imageProperties
 @abstract Returns a dictionary of the image properties associated with the image in the image edit panel.
 */
- (NSDictionary *)imageProperties;

/*! 
 @method hasAdjustMode
 @abstract Show the adjust view tab
 */
- (BOOL)hasAdjustMode;

/*! 
 @method hasEffectsMode
 @abstract Show the effects view tab
 */
- (BOOL)hasEffectsMode;

/*! 
 @method hasDetailsMode
 @abstract Show the details view tab
 */
- (BOOL)hasDetailsMode;
@end



/*! 
 @class IKImageEditPanel
 @abstract The IKImageEditPanel class provides a panel, that is, a utility window that floats on top of document windows, optimized for image editing.
 */
IK_CLASS_AVAILABLE(10.5)
@interface IKImageEditPanel : NSPanel
{
@private
    void * _privateData;
}

/*!
 @property dataSource
 @abstract Data source associated with an image editing panel
 */
@property (assign) id<IKImageEditPanelDataSource> dataSource;

/*!
 @property filterArray
 @abstract Array of filters reflecting the current user adjustments in the adjust or effects tab.
 */
@property (readonly) NSArray * filterArray;


/*! 
 @method sharedImageEditPanel
 @abstract Creates a shared instance of an image editing panel.
 */
+ (IKImageEditPanel *) sharedImageEditPanel;

/*! 
 @method reloadData
 @abstract Reloads the data from the data associated with an image editing panel.
 */
- (void)reloadData;

@end

#endif
