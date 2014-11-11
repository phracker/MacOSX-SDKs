// =====================================================================================================================
//  PDFThumbnailView.h
// =====================================================================================================================


#import <AppKit/AppKit.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFView, PDFThumbnailViewPrivateVars;


@interface PDFThumbnailView : NSView <NSCoding>
{
@private
    PDFThumbnailViewPrivateVars *_pdfPriv;
}


extern NSString *PDFThumbnailViewDocumentEditedNotification;		// Notification when PDFDocument is modified.


// PDFView associated with the thumbnail view.
- (void) setPDFView: (PDFView *) view;
- (PDFView *) PDFView;

// The maximum thumbnail size.
- (void) setThumbnailSize: (NSSize) size;
- (NSSize) thumbnailSize;

// Maximum number of columns (0 indicates no limit - as many columns as will fit).
- (void) setMaximumNumberOfColumns: (NSUInteger) maxColumns;
- (NSUInteger) maximumNumberOfColumns;

// Font used for the page labels.
- (void) setLabelFont: (NSFont *) font;
- (NSFont *) labelFont;

// Background color of view.
- (void) setBackgroundColor: (NSColor *) color;
- (NSColor *) backgroundColor;

// Dragging.
- (void) setAllowsDragging: (BOOL) allow;
- (BOOL) allowsDragging;

// Multiple selections. By default, PDFThumbnailView allows only a single page to be selected at once - the selected 
// thumbnail always corresponds to -[PDFView currentPage]. When you enable multiple selections, the user is allowed to 
// select more  than one thumbnail.  To find the selected page(s) then call -[selectedPages] below.
- (void) setAllowsMultipleSelection: (BOOL) flag;
- (BOOL) allowsMultipleSelection;
- (NSArray *) selectedPages;

@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
