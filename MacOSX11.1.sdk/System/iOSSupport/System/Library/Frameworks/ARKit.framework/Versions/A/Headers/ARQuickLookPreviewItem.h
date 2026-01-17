//
//  ARQuickLookPreviewItem.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLook/QLPreviewItem.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0))
@interface ARQuickLookPreviewItem : NSObject <QLPreviewItem>

/**
 Creates an object representing the 3D content that will be previewed in AR Quick Look.
 
 @discussion This object will be previewed in AR Quick Look using the default
 behavior:
 
 - Start in Object mode without camera passthrough
 
 - Display the Share button for 3D content sharing
 
 - Allow scaling content in both Object and AR mode
 
 This is a promise to the ARQuickLookPreviewItem class that the URL points to a 3D content file. This class does not deal with the file's existence or content, and leaves it up to QuickLook to handle and process the URL.
 
 @param url A file URL to 3D content file (e.g. usdz).
 @return The preview object to display in AR Quick Look.
 */
- (instancetype)initWithFileAtURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

/**
 An optional canonical web page URL for the 3D content that will be shared.
 
 @discussion If this is supplied, the URL to the canonical web page is shared instead of the 3D content file.
 For example, providing https://developer.apple.com/arkit/gallery/ as the canonical web page URL string will be shared via the Share button. If the web page URL string is malformed or not provided, then AR Quick Look will default to sharing the 3D content.
 */
@property (nonatomic, strong, nullable) NSURL *canonicalWebPageURL;

/**
 Whether or not AR Quick Look allows content scaling in AR mode.
 Defaults to `YES` which allows scaling content in AR mode.
 */
@property (nonatomic, assign) BOOL allowsContentScaling;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
