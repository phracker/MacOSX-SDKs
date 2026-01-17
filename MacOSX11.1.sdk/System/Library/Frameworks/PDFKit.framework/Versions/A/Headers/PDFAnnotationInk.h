//
//  PDFAnnotationInk.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

PDFKIT_CLASS_DEPRECATED(10_4, 10_12, NA, NA)
@interface PDFAnnotationInk : PDFAnnotation <NSCopying, NSCoding>
{
@private
}

// Array of NSBezierPaths that comprise the annotation.
- (NSArray *) paths;

// Add or remove paths from the annotation.
// Path points are specified relative to the annotation's bound's origin.
- (void) addBezierPath: (PDFKitPlatformBezierPath *) path;
- (void) removeBezierPath: (PDFKitPlatformBezierPath *) path;

@end
