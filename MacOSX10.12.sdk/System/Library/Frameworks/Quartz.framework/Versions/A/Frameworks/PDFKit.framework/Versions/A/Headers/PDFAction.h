// =====================================================================================================================
//  PDFAction.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionPrivate;

NS_CLASS_AVAILABLE_MAC(10_5)
@interface PDFAction : NSObject <NSCopying>
{
@private
    PDFActionPrivate* _private;
}

// Type of action.  These won't always correspond to the PDFAction subclass in the way you might expect.  For example, 
// a PDFActionURL may return "URI" or "Launch" depending upon the original action (as defined in thePDF spec. - for 
// the PDFKit API we decided to handle the two actions within the same class and also use the more familiar 'URL' term 
// rather than 'URI').
- (NSString *) type;

@end

NS_ASSUME_NONNULL_END
