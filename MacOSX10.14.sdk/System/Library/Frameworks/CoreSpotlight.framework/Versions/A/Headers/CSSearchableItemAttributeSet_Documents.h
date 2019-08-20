//
//  CSSearchableItemAttributeSet_Documents.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

@interface CSSearchableItemAttributeSet (CSDocuments)

///Subject of the this item.
@property(nullable, copy) NSString *subject;

//Theme of the this item.
@property(nullable, copy) NSString *theme;

//An account of the content of the resource. Description may include
//but is not limited to: an abstract, table of contents, reference
//to a graphical representation of content or a free-text account of
//the content.
@property(nullable, copy) NSString *contentDescription;

//Used  to reference to the resource within a given
//context. Recommended best practice is to identify the resource by
//means of a string or number conforming to a formal identification system.
@property(nullable, copy) NSString *identifier;

//A class of entity for whom the resource is intended or useful. A
//class of entity may be determined by the creator or the publisher
//or by a third party.
@property(nullable, copy) NSArray<NSString*> *audiences;

//Size of the document in MB.
@property(nullable, strong) NSNumber *fileSize;

//Number of pages in the item.
@property(nullable, strong) NSNumber *pageCount;

//Width in points (72 points per inch) of the document page
//(first page only for PDF's - other pages within the PDF may
//not be the same width).
@property(nullable, strong) NSNumber *pageWidth;

//Height in points (72 points per inch) of the document page
//(first page only for PDF's - other pages within the PDF may
//not be the same height).
@property(nullable, strong) NSNumber *pageHeight;

//Security (encryption) method used in the file
@property(nullable, strong) NSString *securityMethod;

//Application used to create the document content (e.g. "Word",
//"Framemaker", etc.).
@property(nullable, copy) NSString *creator;

//Software used to convert the original content into a PDF stream
//(e.g. "Distiller", etc.).
@property(nullable, copy) NSArray<NSString*> *encodingApplications;

//Kind that this item represents.
@property(nullable, copy) NSString *kind;

//Array of font names used in the item.
@property(nullable, copy) NSArray<NSString*> *fontNames;

@end
