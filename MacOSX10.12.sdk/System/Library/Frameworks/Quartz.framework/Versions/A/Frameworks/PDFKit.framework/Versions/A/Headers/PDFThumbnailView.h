#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFView, PDFPage, PDFThumbnailViewPrivateVars;

NS_CLASS_AVAILABLE_MAC(10_5)
@interface PDFThumbnailView : PDFKitPlatformView <NSCoding>
{
@private
    PDFThumbnailViewPrivateVars *_pdfPriv;
}

extern NSString *PDFThumbnailViewDocumentEditedNotification;		// Notification when PDFDocument is modified.

// PDFView associated with the thumbnail view.
@property (nonatomic, strong, nullable) PDFView *PDFView;

// Background color of view.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *backgroundColor;

// This will return only a single page unless allowsMultipleSelection is set to YES.
- (NSArray<PDFPage*> *) selectedPages;

// The maximum thumbnail size.
@property (nonatomic, assign) PDFSize thumbnailSize;




// Maximum number of columns (0 indicates no limit - as many columns as will fit).
@property (nonatomic, assign) NSUInteger maximumNumberOfColumns;

// Font used for the page labels.
@property (nonatomic, copy, nullable) PDFKitPlatformFont *labelFont;

// Dragging.
@property (nonatomic, assign) BOOL allowsDragging;

// Multiple selections. By default, PDFThumbnailView allows only a single page to be selected at once - the selected 
// thumbnail always corresponds to -[PDFView currentPage]. When you enable multiple selections, the user is allowed to 
// select more  than one thumbnail.

@property (nonatomic, assign) BOOL allowsMultipleSelection;




@end

NS_ASSUME_NONNULL_END
