//
//  PDFActionGoto.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionGoTo is an interaction event tied with an annotation. This action
//  allows the user to jump to a PDFDestination, which is typically a position
//  on a page paired with a zoom factor.
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFDestination, PDFActionGoToPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionGoTo : PDFAction <NSCopying>
{
@private
    PDFActionGoToPrivateVars *_private2;
}

- (instancetype)initWithDestination:(PDFDestination *)destination NS_DESIGNATED_INITIALIZER;

@property (nonatomic, strong) PDFDestination *destination;

@end

NS_ASSUME_NONNULL_END
