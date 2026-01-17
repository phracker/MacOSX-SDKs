//
//  QLPreviewingController.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#if !defined(USE_PUBLIC_QUICKLOOK_HEADERS) && __has_include(<QuickLookThumbnailing/QLThumbnailRequest.h>)
#import <QuickLookThumbnailing/QLThumbnailRequest.h>
#else

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

/**
 @abstract This class contains information about the thumbnail that should be provided.
 */
NS_CLASS_AVAILABLE_IOS(11_0) QL_EXPORT @interface QLFileThumbnailRequest : NSObject

@property (nonatomic, readonly) CGSize maximumSize;
@property (nonatomic, readonly) CGSize minimumSize;
@property (nonatomic, readonly) CGFloat scale;
@property (nonatomic, copy, readonly) NSURL* fileURL;

@end

NS_ASSUME_NONNULL_END

#endif
