// =====================================================================================================================
//  PDFActionNamed.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionNamedPrivateVars;

// Action names.
NS_ENUM_AVAILABLE_MAC(10_5)
typedef NS_ENUM(NSInteger, PDFActionNamedName)
{
    kPDFActionNamedNone = 0, 
    kPDFActionNamedNextPage = 1, 
    kPDFActionNamedPreviousPage = 2, 
    kPDFActionNamedFirstPage = 3, 
    kPDFActionNamedLastPage = 4, 
    kPDFActionNamedGoBack = 5, 
    kPDFActionNamedGoForward = 6, 
    kPDFActionNamedGoToPage = 7, 
    kPDFActionNamedFind = 8, 
    kPDFActionNamedPrint = 9, 
    kPDFActionNamedZoomIn = 10, 
    kPDFActionNamedZoomOut = 11
};

NS_CLASS_AVAILABLE_MAC(10_5)
@interface PDFActionNamed : PDFAction <NSCopying>
{
@private
    PDFActionNamedPrivateVars *_private2;
}

- (instancetype) initWithName: (PDFActionNamedName) name;

@property(nonatomic, assign) PDFActionNamedName name;

@end

NS_ASSUME_NONNULL_END
