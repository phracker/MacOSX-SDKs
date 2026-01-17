//
//  PDFActionURL.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionURL is an interaction event tied with an annotation. This action allows
//  the user to open a URL, either being a local file or web URL.
//

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionURLPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionURL : PDFAction <NSCopying>
{
@private
    PDFActionURLPrivateVars *_private2;
}

- (instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) NSURL *URL;

@end

NS_ASSUME_NONNULL_END
