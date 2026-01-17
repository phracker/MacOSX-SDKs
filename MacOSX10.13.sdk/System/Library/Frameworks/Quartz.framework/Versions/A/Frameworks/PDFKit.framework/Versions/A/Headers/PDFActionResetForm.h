//
//  PDFActionResetForm.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionResetForm is an interaction event tied with an annotation. This action
//  allows a user to reset all form fields (associated by their fieldNames) annotations.
//  Form field annotations are typically widget-type annotations.
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionResetFormPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionResetForm : PDFAction <NSCopying>
{
@private
    PDFActionResetFormPrivateVars *_private2;
}

// Initially there will be no fields, and -[fieldsIncludedAreCleared] will be YES.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// Fields are an array of NSString objects corresponding to the fieldNames of Widget annotations on the page.
// May return nil.
@property (nonatomic, copy, nullable) NSArray<NSString*> *fields;

// If -[fieldsIncludedAreCleared] is YES, then the widget annotations associated with the fieldNames in the fields
// array above are to be cleared, i.e. uncheck checkboxes, clear text fields, reset radio buttons, etc.
// If -[fieldsIncludedAreCleared] is NO, then every widget annotation associated with the fields array is not to be
// cleared, meaning that every widget annotation in the document whose field name is not listed is to be cleared.
// Both situations above only occur when this reset-form action is performed.
@property (nonatomic) BOOL fieldsIncludedAreCleared;

@end

NS_ASSUME_NONNULL_END
