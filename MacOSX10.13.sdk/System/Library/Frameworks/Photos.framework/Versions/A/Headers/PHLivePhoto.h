//
//  PHLivePhoto.h
//  Photos
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class PHLivePhoto
 @abstract Encapsulate the information needed to display a live photo in a PHLivePhotoView
 */

NS_CLASS_AVAILABLE(10_12, 9_1) @interface PHLivePhoto : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// The dimensions of the live photo measured in pixels.
@property (readonly, nonatomic) CGSize size;

@end

NS_ASSUME_NONNULL_END
