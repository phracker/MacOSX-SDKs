//
//  PDFAction.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFAction is an abstract class, representing an event a user can trigger through
//  interaction with the owning annotation. These events are PDFActionGoTo, PDFActionNamed,
//  PDFActionRemoveGoTo, PDFActionResetForm, and PDFActionURL. Typically these events
//  are for moving the PDFView view-portal, open a web browser, clear out forms, etc.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionPrivate;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFAction : NSObject <NSCopying>
{
@private
    PDFActionPrivate *_private;
}

// Type of action.  These won't always correspond to the PDFAction subclass in the way you might expect.  For example, 
// a PDFActionURL may return "URI" or "Launch" depending upon the original action (as defined in the PDF spec. - for 
// the PDFKit API we decided to handle the two actions within the same class and also use the more familiar 'URL' term 
// rather than 'URI').
// Type based on the Adobe PDF Specification (1.7), Table 8.48: Action types.
@property (nonatomic, readonly) NSString *type;

@end

NS_ASSUME_NONNULL_END
