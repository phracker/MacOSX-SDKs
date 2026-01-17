// =====================================================================================================================
//  PDFActionGoTo.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFDestination, PDFActionGoToPrivateVars;

NS_CLASS_AVAILABLE_MAC(10_5)
@interface PDFActionGoTo : PDFAction <NSCopying>
{
@private
    PDFActionGoToPrivateVars *_private2;
}

- (instancetype) initWithDestination: (PDFDestination *) destination;

@property(nonatomic, retain) PDFDestination* destination;

@end

NS_ASSUME_NONNULL_END
