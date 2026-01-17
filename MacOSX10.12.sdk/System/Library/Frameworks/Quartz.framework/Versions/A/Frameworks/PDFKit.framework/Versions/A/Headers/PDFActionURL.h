// ======================================================================================================================
//  PDFActionURL.h
// =====================================================================================================================


#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionURLPrivateVars;

NS_CLASS_AVAILABLE_MAC(10_5)
@interface PDFActionURL : PDFAction <NSCopying>
{
@private
    PDFActionURLPrivateVars *_private2;
}

- (nullable instancetype) initWithURL: (NSURL *) url;

@property(nonatomic, retain) NSURL* URL;

@end

NS_ASSUME_NONNULL_END
