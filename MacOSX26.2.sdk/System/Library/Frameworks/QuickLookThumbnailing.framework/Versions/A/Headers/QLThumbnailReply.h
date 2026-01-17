//
//  QLThumbnailReply.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 To provide a thumbnail for a request, you have to return a QLThumbnailReply object.

 @discussion To provide a thumbnail, you have two options:
 1. Draw the thumbnail, by providing a QLThumbnailReply created with a drawing block.
 2. Pass the thumbnail file URL, by providing a QLThumbnailReply created with a file URL.
 */
API_AVAILABLE(ios(11.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos)  __attribute__((visibility("default")))
@interface QLThumbnailReply : NSObject

///The extensionBadge is a short string identifying the file type used as a badge when producing an icon.
@property (nonatomic, copy) NSString* extensionBadge API_AVAILABLE(ios(15.0), macos(12.0));

- (instancetype)init NS_UNAVAILABLE;

/**
 You can create a reply with a drawing block that will draw into a given context with the coordinate system of Core Graphics.

 @param contextSize The desired size of the context that will be passed to the drawing block.
 It should be as close as possible to the maximumSize of the QLFileThumbnailRequest and it has to be greater than or equal to its minimumSize.

 Ideally, at least either contextSize's width matches maximumSize's width or contextSize's height matches maximumSize's height.
 The context size will be scaled to QLFileThumbnailRequest's scale value (if you pass (x, y), the size of the context will be (scale * x, scale * y)).
 @param drawingBlock The thumbnail should be drawn into the context passed to this block. It is a context of type CGBitmapContext, set up to be used with the coordinate system of Core Graphics.
 Return YES if the thumbnail was successfully drawn into the context. Return NO otherwise.
 */
+ (instancetype)replyWithContextSize:(CGSize)contextSize drawingBlock:(BOOL (^)(CGContextRef context))drawingBlock;

/**
 You can create a reply with a drawing block that will draw into the current context with the coordinate system of UIKit or AppKit.

 @param contextSize The desired size of the context that will be passed to the drawing block.
 It should be as close as possible to the maximumSize of the QLFileThumbnailRequest and it has to be greater than or equal to its minimumSize.

 Ideally, at least either contextSize's width matches maximumSize's width or contextSize's height matches maximumSize's height.
 The context size will be scaled to QLFileThumbnailRequest's scale value (if you pass (x, y), the size of the context will be (scale * x, scale * y)).
 @param drawingBlock A block that draws the thumbnail into the current context which you can access via UIGraphicsGetCurrentContext() or [NSGraphicsContext currentContext].
 It is a context of type CGBitmapContext, set up to be used with the coordinate system of UIKit or AppKit.
 Return YES if the thumbnail was successfully drawn into the current context. Return NO otherwise.
 */
+ (instancetype)replyWithContextSize:(CGSize)contextSize currentContextDrawingBlock:(BOOL (^)(void))drawingBlock;

/**
 You can create a reply object with a file URL of an image that will be used as the thumbnail.
 The image will be downscaled to fit the size of the QLFileThumbnailRequest if necessary.
 */
+ (instancetype)replyWithImageFileURL:(NSURL *)fileURL;

@end

NS_ASSUME_NONNULL_END
