//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraItem.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

/*!
    @header ICCameraItem
    @abstract ICCameraItem is an abstract class that represents an item in an ICCameraDevice object. ICCameraDevice object creates instances of two concrete subclasses of ICCameraItem: ICCameraFolder and ICCameraFile.
*/

//------------------------------------------------------------------------------------------------------------------------------

#import <ImageCaptureCore/ICCommonConstants.h>

//------------------------------------------------------------------------------------------------------------------------------

@class ICCameraDevice;
@class ICCameraFolder;

//----------------------------------------------------------------------------------------------------------------- ICCameraItem
/*! 
  @class ICCameraItem
  @abstract ICCameraItem is an abstract class that represents an item in an ICCameraDevice object. ICCameraDevice object creates instances of two concrete subclasses of ICCameraItem: ICCameraFolder and ICCameraFile.
*/
CF_ASSUME_NONNULL_BEGIN

@interface ICCameraItem : NSObject
{
@private
    id  _itemProperties;
}

/*!
    @property device
    @abstract ￼Parent device of this folder.

*/
@property(readonly)                                             ICCameraDevice* device;

/*!
    @property parentFolder
    @abstract ￼Parent folder of this folder. The root folder's parentFolder is nil.

*/
@property(readonly)                                             ICCameraFolder* parentFolder;

/*!
    @property name
    @abstract ￼Name of this folder.

*/
@property(readonly)                                             NSString*       name;

/*!
    @property UTI
    @abstract ￼Item UTI. This is an Uniform Type Identifier string. It is one of: kUTTypeFolder, kUTTypeImage, kUTTypeMovie, kUTTypeAudio, or kUTTypeData.

*/
@property(readonly)                                             NSString*       UTI;

/*!
    @property fileSystemPath
    @abstract ￼The file system path of the item for items on a device with transportType of ICTransportTypeMassStorage.

*/
@property(readonly)                                             NSString*       fileSystemPath;

/*!
    @property locked
    @abstract ￼Indicates the protection state of this folder. It is locked if the storage card in the camera is locked.

*/
@property(readonly, getter=isLocked)                            BOOL            locked;

/*!
    @property raw
    @abstract ￼Indicates if the file is a raw image file.

*/
@property(readonly, getter=isRaw)                               BOOL            raw;

/*!
    @property inTemporaryStore
    @abstract ￼Indicates if this folder is in a temporary store. A temporary store may be used by the device when images are captures on the device when it is tethered to the computer.

*/
@property(readonly, getter=isInTemporaryStore)                  BOOL            inTemporaryStore;

/*!
    @property creationDate
    @abstract ￼Creation date of this file. This information is usually the same as the EXIF creation date.

*/
@property(readonly)                                             NSDate*         creationDate;

/*!
    @property modificationDate
    @abstract ￼Modification date of this file. This information is usually the same as the EXIF modification date.

*/
@property(readonly)                                             NSDate*         modificationDate;

/*!
    @property thumbnailIfAvailable
    @abstract ￼Thumbnail for the item if one is readily available. If one is not readily available, accessing this property will send a message to the device requesting a thumbnail for the file. The delegate of the device will be notified via method "cameraDevice:didReceiveThumbnailForItem:", if this method is implemented on by the delegate.

*/
@property(nullable,readonly)                                             CGImageRef      thumbnailIfAvailable;

/*!
 @property largeThumbnailIfAvailable
 @abstract Large thumbnail for the item if one is readily available. If one is not readily available, accessing this property will send a message to the device requesting a thumbnail for the file. The delegate of the device will be notified via method "cameraDevice:didReceiveThumbnailForItem:", if this method is implemented on by the delegate.
 
 */
@property(nullable,readonly)                                             CGImageRef      largeThumbnailIfAvailable;

/*!
    @property metadataIfAvailable
    @abstract ￼Metadata for the file if one is readily available. If one is not readily available, accessing this property will send a message to the device requesting a thumbnail for the file. The delegate of the device will be notified via method "cameraDevice:didReceiveMetadataForItem:", if this method is implemented on by the delegate.

*/
@property(nullable,readonly)                                             NSDictionary<NSString*,id>*   metadataIfAvailable;

/*!
    @property userData
    @abstract ￼A mutable dictionary to store arbitrary key-value pairs associated with a camera item object. This can be used by view objects that bind to this object to store "house-keeping" information.

*/
@property(nullable,readonly)                                             NSMutableDictionary*  userData;

/*!
    @property ptpObjectHandle
    @abstract PTP object handle value if the item is on a camera that uses PTP protocol. The value of this property is set to 0 if the camera does not use PTP protocol.

*/
@property(readonly)                                             unsigned int    ptpObjectHandle;

/*!
 @property addedAfterContentCatalogCompleted
 @abstract This property is set if the file is captured on the device after the device's content is fully enumerated. This does not apply to files added as a result of adding a new store to the device. 
 
 */
@property(readonly, getter=wasAddedAfterContentCatalogCompleted) BOOL           addedAfterContentCatalogCompleted;

@end

//--------------------------------------------------------------------------------------------------------------- ICCameraFolder
/*! 
  @class ICCameraFolder
  @abstract This class represents a folder on an ICCameraDevice object.
*/

@interface ICCameraFolder : ICCameraItem
{
@private
    id  _folderProperties;
}

/*!
    @property contents
    @abstract ￼A list of items contained by this folder.

*/
@property(readonly)   NSArray<ICCameraItem*>*      contents;

@end

//----------------------------------------------------------------------------------------------------------------- ICCameraFile
/*! 
  @class ICCameraFile
  @abstract This class represents a file on an ICCameraDevice object.
*/

@interface ICCameraFile : ICCameraItem
{
@private
    id  _fileProperties;
}

/*!
    @property fileSize
    @abstract ￼Size of file in bytes.

*/
@property(readonly)   off_t                 fileSize;

/*!
    @property orientation
    @abstract ￼Desired orientation of image to use when it is downloaded.
    @discussion This property is set to ICEXIFOrientation1 initially. If the format of this file supports EXIF orientation tag, then this property will be updated to match the value of that tag, when the thumbnail or metadata for this file is received. 

*/
@property(readwrite)  ICEXIFOrientationType orientation;

/*!
    @property duration
    @abstract ￼Duration of audio/video file in seconds.

*/
@property(readonly)   double                duration;

/*!
    @property sidecarFiles
    @abstract This property is NULL if there are no sidecar files associated with this file. Otherwise it is an array of ICCameraFile instances of sidecar files associated with this file. An example of a sidecar file is a file with the same base name as this file and having an extension XMP.

*/
@property(readonly)    NSArray<ICCameraItem*>*      sidecarFiles;

CF_ASSUME_NONNULL_END

@end

//------------------------------------------------------------------------------------------------------------------------------

