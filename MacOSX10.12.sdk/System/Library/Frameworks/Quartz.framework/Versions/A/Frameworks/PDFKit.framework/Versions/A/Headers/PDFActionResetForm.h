// =====================================================================================================================
//  PDFActionResetForm.h
// =====================================================================================================================

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionResetFormPrivateVars;

NS_CLASS_AVAILABLE_MAC(10_5)
@interface PDFActionResetForm : PDFAction <NSCopying>
{
@private
    PDFActionResetFormPrivateVars *_private2;
}

// Initially there will be no fields, and -[fieldsIncludedAreCleared] will be YES.
- (instancetype) init;

// Fields are an array of NSString objects corresponding to the fieldNames of Widget annotations on the page.
// May return nil.
@property(nonatomic, assign) NSArray<NSString*>* fields;

// If -[fieldsIncludedAreCleared] is YES, then the fields above are to be cleared when this action is performed.
// Otherwise, the fields identified are ones not to be cleared: ones to be excluded.
@property(nonatomic, assign) BOOL fieldsIncludedAreCleared;

@end

NS_ASSUME_NONNULL_END
