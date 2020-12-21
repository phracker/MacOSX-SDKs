//
//  PDFActionNamed.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  PDFActionNamed is an interaction event tied with an annotation. This action
//  allows the user to change their navigation stack or their current view. This
//  can manipulate the user's navigation stack (move to the previous page, next page etc.),
//  trigger some other forms of interactions (string search, printing, etc.), and
//  manipulate the current view (change zoom factors).
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionNamedPrivateVars;

// Action names.
PDFKIT_ENUM_AVAILABLE(10_5, 11_0)
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

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionNamed : PDFAction <NSCopying>
{
@private
    PDFActionNamedPrivateVars *_private2;
}

- (instancetype)initWithName:(PDFActionNamedName)name NS_DESIGNATED_INITIALIZER;

@property (nonatomic) PDFActionNamedName name;

@end

NS_ASSUME_NONNULL_END
