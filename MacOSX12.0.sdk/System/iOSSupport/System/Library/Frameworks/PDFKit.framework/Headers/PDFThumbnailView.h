//
//  PDFThumbnailView.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  PDFThumbnailView is a custom view that contains a set of PDFPage thumbnails
//  that a user can scroll over, interact with, and have these interactions drive
//  view changes on PDFView.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(PDFKIT_PLATFORM_IOS)

// Layout mode for thumbnail view.
PDFKIT_ENUM_AVAILABLE(NA, 11_0)
typedef NS_ENUM(NSInteger, PDFThumbnailLayoutMode)
{
    PDFThumbnailLayoutModeVertical = 0,
    PDFThumbnailLayoutModeHorizontal = 1
};

#endif

@class PDFView, PDFPage;

// Notification when PDFDocument is modified.
PDFKIT_EXTERN NSString* const PDFThumbnailViewDocumentEditedNotification PDFKIT_AVAILABLE(10_4, 11_0);

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFThumbnailView : PDFKitPlatformView <NSCoding>

// PDFView associated with the thumbnail view.
@property (nonatomic, weak, nullable) PDFView *PDFView;

// Background color of view.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *backgroundColor;

// This will return only a single page unless allowsMultipleSelection is set to YES.
@property (nonatomic, readonly, strong, nullable) NSArray<PDFPage*> *selectedPages;

// The maximum thumbnail size.
@property (nonatomic) PDFSize thumbnailSize;

#if defined(PDFKIT_PLATFORM_OSX)

// Maximum number of columns (0 indicates no limit - as many columns as will fit).
@property (nonatomic) NSUInteger maximumNumberOfColumns;

// Font used for the page labels.
@property (nonatomic, copy, nullable) PDFKitPlatformFont *labelFont;

// Dragging. Allows a user to move icons within the PDFThumbnailView, changing page order. Default is false.
@property (nonatomic) BOOL allowsDragging;

// Multiple selections. By default, PDFThumbnailView allows only a single page to be selected at once - the selected 
// thumbnail always corresponds to -[PDFView currentPage]. When you enable multiple selections, the user is allowed to 
// select more than one thumbnail.
@property (nonatomic) BOOL allowsMultipleSelection;

#elif defined(PDFKIT_PLATFORM_IOS)

// Defines if the thumbnail view is to be displayed vertically or horizontally.
// Default PDFThumbnailLayoutModeVertical.
@property (nonatomic) PDFThumbnailLayoutMode layoutMode PDFKIT_AVAILABLE(NA, 11_0);

// Inset for the placement of icons within the thumbnail view. Default UIEdgeInsetsZero.
@property (nonatomic) UIEdgeInsets contentInset PDFKIT_AVAILABLE(NA, 11_0);

#endif //PDFKIT_PLATFORM_IOS

@end

NS_ASSUME_NONNULL_END
