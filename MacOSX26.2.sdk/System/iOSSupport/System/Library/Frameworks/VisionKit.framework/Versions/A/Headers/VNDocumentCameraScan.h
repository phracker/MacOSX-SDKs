#if (defined(USE_VISIONKIT_PUBLIC_HEADERS) && USE_VISIONKIT_PUBLIC_HEADERS) || !__has_include(<DocumentCamera/VNDocumentCameraScan.h>)
//
//  VNDocumentCameraScan.h
//  VisionKit
//
//  Copyright © 2017-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#elif TARGET_OS_OSX
#import <AppKit/NSImage.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/// A single document scanned in the document camera.
///
/// When the document camera scans a document, it returns the resulting
/// information in this format, through the delegate method
/// ``VisionKit/VNDocumentCameraViewControllerDelegate/documentCameraViewController(_:didFinishWith:)``.
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface VNDocumentCameraScan : NSObject

/// The number of pages in the scanned document.
@property (nonatomic, readonly) NSUInteger pageCount;

#if TARGET_OS_OSX

/// Requests the image of a page at a specified index.
///
/// - Parameter index: The index of the image in the scanned document you'd like to return. Page `1` is at index `0`.
/// - Returns: The image of the page at the specified index. If no page exists, this method returns `nil`.
- (NSImage *)imageOfPageAtIndex:(NSUInteger)index;

#elif TARGET_OS_IPHONE

/// The image of the page at a specified index.
///
/// - Parameter index: The index of the image in the scanned document you'd like to return. Page `1` is at index `0`.
/// - Returns: The image of the page at the specified index. If no page exists, this method returns `nil`.
- (UIImage *)imageOfPageAtIndex:(NSUInteger)index;

#endif

/// The title of the scanned document.
@property (nonatomic, strong, readonly) NSString *title;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <DocumentCamera/VNDocumentCameraScan.h>
#endif
