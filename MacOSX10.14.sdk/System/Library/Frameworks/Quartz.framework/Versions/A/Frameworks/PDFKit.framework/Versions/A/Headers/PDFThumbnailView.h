//
//  PDFThumbnailView.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFThumbnailView is a custom view that contains a set of PDFPage thumbnails
//  that a user can scroll over, interact with, and have these interactions drive
//  view changes on PDFView.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN


@class PDFView, PDFPage, PDFThumbnailViewPrivateVars;

// Notification when PDFDocument is modified.
PDFKIT_EXTERN NSString *PDFThumbnailViewDocumentEditedNotification PDFKIT_AVAILABLE(10_4, 11_0);

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFThumbnailView : PDFKitPlatformView <NSCoding>
{
@private
    PDFThumbnailViewPrivateVars *_private;
}

// PDFView associated with the thumbnail view.
@property (nonatomic, strong, nullable) PDFView *PDFView;

// Background color of view.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *backgroundColor;

// This will return only a single page unless allowsMultipleSelection is set to YES.
@property (nonatomic, readonly, strong, nullable) NSArray<PDFPage*> *selectedPages;

// The maximum thumbnail size.
@property (nonatomic) PDFSize thumbnailSize;


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


@end

NS_ASSUME_NONNULL_END
