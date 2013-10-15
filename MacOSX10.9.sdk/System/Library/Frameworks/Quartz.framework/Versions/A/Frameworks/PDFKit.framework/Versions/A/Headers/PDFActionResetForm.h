// =====================================================================================================================
//  PDFActionResetForm.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAction.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFActionResetFormPrivateVars;


@interface PDFActionResetForm : PDFAction <NSCopying>
{
@private
    PDFActionResetFormPrivateVars *_pdfPriv2;
}

// Initially there will be no fields, and -[fieldsIncludedAreCleared] will be YES.
- (id) init;

// Fields are an array of NSString objects corresponding to the fieldNames of Widget annotations on the page.
// May return nil.
- (NSArray *) fields;
- (void) setFields: (NSArray *) fields;

// If -[fieldsIncludedAreCleared] is YES, then the fields above are to be cleared when this action is performed.
// Otherwise, the fields identified are ones not to be cleared: ones to be excluded.
- (BOOL) fieldsIncludedAreCleared;
- (void) setFieldsIncludedAreCleared: (BOOL) include;

@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
