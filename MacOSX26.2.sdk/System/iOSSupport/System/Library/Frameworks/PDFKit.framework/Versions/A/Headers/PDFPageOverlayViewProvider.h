//
//  PDFPageOverlayViewProvider.h
//  PDFKit
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFPage, PDFView;

API_AVAILABLE(macos(13.0), ios(16.0))
@protocol PDFPageOverlayViewProvider <NSObject>

@required

// Asks the provider for a view to be displayed on top of the specified page.
- (nullable PDFKitPlatformView*)pdfView:(PDFView*)view overlayViewForPage:(PDFPage*)page;

@optional

// Tells the provider that a view returned from `overlayViewForPage` has been added
// to the view hierarchy and constraints have been set up. At this point, gesture failure
// handlers may be set up with those of `pdfView`.
- (void)pdfView:(PDFView*)pdfView willDisplayOverlayView:(PDFKitPlatformView*)overlayView forPage:(PDFPage*)page;

// Tells the provider that a view returned from `overlayViewForPage` will be removed.
// This can be used to restore whatever was done in `overlayView:wasAddedForPage`.
- (void)pdfView:(PDFView*)pdfView willEndDisplayingOverlayView:(PDFKitPlatformView*)overlayView forPage:(PDFPage*)page;

@end

NS_ASSUME_NONNULL_END
