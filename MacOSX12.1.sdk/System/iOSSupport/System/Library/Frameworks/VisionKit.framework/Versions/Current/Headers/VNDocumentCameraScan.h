#if (defined(USE_VISIONKIT_PUBLIC_HEADERS) && USE_VISIONKIT_PUBLIC_HEADERS) || !__has_include(<DocumentCamera/VNDocumentCameraScan.h>)
//
//  VNDocumentCameraScan.h
//  VisionKit
//
//  Copyright © 2017-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface VNDocumentCameraScan : NSObject

// The number of pages in the scanned document.
@property (nonatomic, readonly) NSUInteger pageCount;
// The image of the page at a specified index.
- (UIImage *)imageOfPageAtIndex:(NSUInteger)index;
// The title of the scanned document.
@property (nonatomic, strong, readonly) NSString *title;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <DocumentCamera/VNDocumentCameraScan.h>
#endif
