//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraFolder.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ICCameraItem.h>

CF_ASSUME_NONNULL_BEGIN

//--------------------------------------------------------------------------------------------------------------- ICCameraFolder
/*!
  @class ICCameraFolder
  @abstract This class represents a folder on an ICCameraDevice object.
 */
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICCameraFolder : ICCameraItem
{
}

/*!
  @property contents
  @abstract ￼A list of items contained by this folder.
 */
@property (nonatomic, readonly, nullable) NSArray<ICCameraItem*>* contents IC_AVAILABLE(macos(10.4), ios(13.0));

@end

CF_ASSUME_NONNULL_END
