// =====================================================================================================================
//  PDFDocument.h
// =====================================================================================================================


#import <AppKit/AppKit.h>


@class PDFDestination, PDFOutline, PDFPage, PDFSelection, PDFDocumentPrivateVars;


// Printing page-scaling modes (see PDFView).
typedef NSInteger PDFPrintScalingMode;
enum
{
    kPDFPrintPageScaleNone = 0, 
    kPDFPrintPageScaleToFit = 1, 
    kPDFPrintPageScaleDownToFit = 2
};

// Document permissions status. For encrypted PDF's, supplying the owner password will enable owner permission status.
typedef NSInteger PDFDocumentPermissions;
enum
{
	kPDFDocumentPermissionsNone = 0, 
	kPDFDocumentPermissionsUser = 1, 
	kPDFDocumentPermissionsOwner = 2
};


// Notifications.
extern NSString *PDFDocumentDidUnlockNotification;			// The notification object is self.

extern NSString *PDFDocumentDidBeginFindNotification;		// The notification object is self, no userInfo dictionary.
extern NSString *PDFDocumentDidEndFindNotification;			// The notification object is self, no userInfo dictionary.
extern NSString *PDFDocumentDidBeginPageFindNotification;	// The notification object is self, the userInfo dictionary 
															//  contains the page index as an NSNumber for the key 
															//  @"PDFDocumentPageIndex".
extern NSString *PDFDocumentDidEndPageFindNotification;		// The notification object is self, the userInfo dictionary 
															//  contains the page index as an NSNumber for the key 
															//  @"PDFDocumentPageIndex".
extern NSString *PDFDocumentDidFindMatchNotification;		// The notification object is self, the userInfo dictionary
															//  contains a PDFSelection (found instance) for the key 
															//  @"PDFDocumentFoundSelection".

extern NSString *PDFDocumentDidBeginWriteNotification;		// The notification object is self, no userInfo dictionary.
extern NSString *PDFDocumentDidEndWriteNotification;		// The notification object is self, no userInfo dictionary.
extern NSString *PDFDocumentDidBeginPageWriteNotification;	// The notification object is self, the userInfo dictionary 
															//  contains the page index as an NSNumber for the key 
															//  @"PDFDocumentPageIndex".
extern NSString *PDFDocumentDidEndPageWriteNotification;	// The notification object is self, the userInfo dictionary 
															//  contains the page index as an NSNumber for the key 
															//  @"PDFDocumentPageIndex".

// Document attributes (see -[documentAttributes] below).
extern NSString *PDFDocumentTitleAttribute;				// NSString containing document title.
extern NSString *PDFDocumentAuthorAttribute;			// NSString containing document author.
extern NSString *PDFDocumentSubjectAttribute;			// NSString containing document title.
extern NSString *PDFDocumentCreatorAttribute;			// NSString containing name of app that created document.
extern NSString *PDFDocumentProducerAttribute;			// NSString containing name of app that produced PDF data.
extern NSString *PDFDocumentCreationDateAttribute;		// NSDate representing document creation date.
extern NSString *PDFDocumentModificationDateAttribute;	// NSDate representing last document modification date.
extern NSString *PDFDocumentKeywordsAttribute;			// NSArray of NSStrings containing document keywords.


@interface PDFDocument : NSObject <NSCopying>
{
@private
    PDFDocumentPrivateVars *_pdfPriv;
}

// -------- init

// Initializers.
- (id) initWithURL: (NSURL *) url;
- (id) initWithData: (NSData *) data;

// -------- accessors

// May return NULL if the document was created from NSData.
- (NSURL *) documentURL;

// This is the CGPDFDocument associated with the PDFDocument object.  With this object you can call many CoreGraphics 
// API. May return NULL if the document was not created from an existing PDF file or data.
- (CGPDFDocumentRef) documentRef;

// Returns a dictionary with PDF metadata. Metadata is optional for PDF's and so some of the keys may be missing or the 
// entire dictionary may be empty.  See attributes above for keys.
- (NSDictionary *) documentAttributes;
- (void) setDocumentAttributes: (NSDictionary *) attributes;

// PDF version of the PDF file (example: major version = 1, minor = 4; PDF v1.4).
- (int) majorVersion;
- (int) minorVersion;

// Whether the PDF is encrypted. With the right password, a PDF can be unlocked - nontheless, the PDF still indicates 
// that it is encrypted - just no longer locked. Some PDF's may be encrypted but can be unlocked with the empty string. 
// These are unlocked automatically. 
- (BOOL) isEncrypted;

// See comments above.
- (BOOL) isLocked;

// Means of passing in a password to unlock encrypted PDF's.  Calling -[unlockWithPassword:] will attempt to unlock the 
// PDF. If successful, a PDFDocumentDidUnlockNotification notification is sent. You cannot "re-lock" a PDF by passing 
// in a bogus password.  Returns YES if the document is now unlocked, NO otherwise ([self isLocked] == NO).
- (BOOL) unlockWithPassword: (NSString *) password;

// Even unlocked, encrypted PDF's may have certain restrictions regarding copying or printing placed upon them. These 
// indicate the current state.
- (BOOL) allowsPrinting;
- (BOOL) allowsCopying;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

// Returns the permissions status of the PDF document. You have kPDFDocumentPermissionsNone status for an encrypted 
// document that you have not supplied either a valid user or owner password. For a document with no encryption, you 
// automatically have kPDFDocumentPermissionsOwner status.
- (PDFDocumentPermissions) permissionsStatus;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

// Convenience method. Returns a string representing the entire document (each page's string concatenated with line 
// feeds between pages).
- (NSString *) string;

// If a PDFDocument has a delegate, delegate methods may be called.  See: PDFDocumentNotifications and 
// PDFDocumentDelegate below.
- (void) setDelegate: (id) anObject;
- (id) delegate;

// Methods to record the current state of the PDFDocument as data or a file.  Passing a QuartzFilter object in the 
// options dictionary with the key @"QuartzFilter" will allow you to have the filter applied when saving the PDF.
// NOTE: Versions of PDFKit before SnowLeopard did not return autorelease data for -[dataRepresentation]. You had to 
// release the data yourself.  Beginning with apps compiled on SnowLeopard the data returned is autoreleased.
- (NSData *) dataRepresentation;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
- (NSData *) dataRepresentationWithOptions: (NSDictionary *) options;
#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
- (BOOL) writeToFile: (NSString *) path;
- (BOOL) writeToFile: (NSString *) path withOptions: (NSDictionary *) options;
- (BOOL) writeToURL: (NSURL *) url;
- (BOOL) writeToURL: (NSURL *) url withOptions: (NSDictionary *) options;

// -------- outline

// Returns the root outline object for the PDF (or NULL if none).
- (PDFOutline *) outlineRoot;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Allows you specify a PDFOutline as the root outline item for this document.  When the PDF is saved the outline tree 
// structure is written out to the destination PDF file. Passing NULL is a way to strip any outline from a document.
- (void) setOutlineRoot: (PDFOutline *) outline;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Given a PDFSelection, this method returns the child outline item the selection most closely falls beneath. Since a 
// selection may span multiple outline items, only the point representing the first character of the PDFSelection is 
// considered. Typically, outline's indicate things like chapters for the PDF.  Therefore, this method would help you 
// identify the chapter the selection falls within.
- (PDFOutline *) outlineItemForSelection: (PDFSelection *) selection;

// -------- pages

// The number of pages in the document.
- (NSUInteger) pageCount;

// Returns a PDFPage object representing the page at index. Will raise an exception if index is out of bounds. Indicees 
// are zero-based.
- (PDFPage *) pageAtIndex: (NSUInteger) index;

// Given a PDFPage, returns the pages index within the document. Indicees are zero-based.
- (NSUInteger) indexForPage: (PDFPage *) page;

// Methods allowing pages to be inserted, removed, and re-ordered. Can throw range exceptions.
// Note: when inserting a PDFPage, you have to be careful if that page came from another PDFDocument. PDFPage's have a 
// notion of a single document that owns them and when you call the methods below the PDFPage passed in is assigned a 
// new owning document.  You'll want to call -[PDFPage copy] first then and pass this copy to the blow methods. This 
// allows the orignal PDFPage to maintina its original document.
- (void) insertPage: (PDFPage *) page atIndex: (NSUInteger) index;
- (void) removePageAtIndex: (NSUInteger) index;
- (void) exchangePageAtIndex: (NSUInteger) indexA withPageAtIndex: (NSUInteger) indexB;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// This is the class that will be allocated and initialized when page objects are created for the document.  The 
// default implementation returns [PDFPage class] but if you want PDFDocument to use your own custom class you can 
// subclass PDFDocument and implement this method to return your own custom class.  Your class should be a subclass of 
// PDFPage (otherwise the behavior is undefined).
- (Class) pageClass;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// -------- find

// Searches entire document for string and returns an array of PDFSelections representing all instances found. May 
// return an empty array (if not found). Supported options are: NSCaseInsensitiveSearch, NSLiteralSearch, and 
// NSBackwardsSearch.
- (NSArray *) findString: (NSString *) string withOptions: (NSUInteger) options;

// Begins a find, searching the document for string.  Search results are handled via a 
// PDFDocumentDidFindMatchNotification or if the delegate implements -[didMatchString:]. Supported options are: 
// NSCaseInsensitiveSearch, NSLiteralSearch, and NSBackwardsSearch.
- (void) beginFindString: (NSString *) string withOptions: (NSUInteger) options;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Like -[beginFindString:withOptions:] above but it accepts an array of strings to search for.
// All other comments for -[beginFindString:withOptions:] above apply.
- (void) beginFindStrings: (NSArray *) strings withOptions: (NSUInteger) options;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Searches for only the next instance of string beginning after the last character of selection with options (or 
// preceding the first character of the selection if NSBackwardsSearch is specified as a search option).
// Returns next instance as a PDFSelection or NULL if the end of the document is reached. Supported options are: 
// NSCaseInsensitiveSearch, NSLiteralSearch, and NSBackwardsSearch. Passing in NULL for selection will start the 
// search from the beginning of the document (or end if NSBackwardsSearch is specified).
- (PDFSelection *) findString: (NSString *) string fromSelection: (PDFSelection *) selection withOptions: (NSUInteger) options;

// Returns YES if document is currently searching for a string.
- (BOOL) isFinding;

// Method to cancel a search.  Can be called from a user method being serviced by a find notification.
- (void) cancelFindString;

// -------- printing

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

// Returns a print operation suitable for printing the PDF document. Specify scaling mode and autorotate behaviors desired.
- (NSPrintOperation *) printOperationForPrintInfo: (NSPrintInfo *) printInfo scalingMode: (PDFPrintScalingMode) scaleMode autoRotate: (BOOL) doRotate;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

// -------- selections

// Returns a selection representing text for the entire document.
- (PDFSelection *) selectionForEntireDocument;

// Returns a selection representing text from page startPage and point startPt to page endPage and to point endPt on 
// that page. Points are in page-space and relative to their respective pages.  Start and end page can be the same 
// (and are then equivalent to calling -[PDFPage selectionFromPoint: toPoint:]).
- (PDFSelection *) selectionFromPage: (PDFPage *) startPage atPoint: (NSPoint) startPt toPage: (PDFPage *) endPage 
		atPoint: (NSPoint) endPt;

// Similar to the obove method but allows you to specify a character index for the start and end pages.
- (PDFSelection *) selectionFromPage: (PDFPage *) startPage atCharacterIndex: (NSUInteger) startChar 
		toPage: (PDFPage *) endPage atCharacterIndex: (NSUInteger) endChar;

@end

// Notification delegate methods. If implemented by the delegate, these are called. See notification comments above.

@interface NSObject(PDFDocumentNotifications)
- (void) documentDidUnlock: (NSNotification *) notification;
- (void) documentDidBeginDocumentFind: (NSNotification *) notification;
- (void) documentDidEndDocumentFind: (NSNotification *) notification;
- (void) documentDidBeginPageFind: (NSNotification *) notification;
- (void) documentDidEndPageFind: (NSNotification *) notification;
- (void) documentDidFindMatch: (NSNotification *) notification;
@end

@interface NSObject(PDFDocumentDelegate)

// If implemented by the delegate, called for every search instance found during a find. PDFDocument's implementation 
// accumulates each PDFSelection (instance) in an NSArray.
- (void) didMatchString: (PDFSelection *) instance;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

// If implemented by the delegate, will be called when a PDFPage is instantiated. PDFDocument's implementation calls
// -[PDFDocument pageClass] (see above). 
- (Class) classForPage;

// If implemented by the delegate, will be called when a PDFAnnotation is instantiated by a page. PDFPage by default 
// will instantiate object of class. This allows you to instead return your own PDFAnnotationXxxx subclass.
- (Class) classForAnnotationClass: (Class) annotationClass;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

@end
