// ======================================================================================================================
//  PDFDocument.h
// ======================================================================================================================


@class PDFDestination, PDFOutline, PDFPage, PDFSelection, PDFDocumentPrivateVars;


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

// Document attributes (see -[documentAttributes] below).
extern NSString *PDFDocumentTitleAttribute;				// NSString containing document title.
extern NSString *PDFDocumentAuthorAttribute;			// NSString containing document author.
extern NSString *PDFDocumentSubjectAttribute;			// NSString containing document title.
extern NSString *PDFDocumentCreatorAttribute;			// NSString containing name of app that created document content.
extern NSString *PDFDocumentProducerAttribute;			// NSString containing name of app that produced PDF data.
extern NSString *PDFDocumentCreationDateAttribute;		// NSDate representing document creation date.
extern NSString *PDFDocumentModificationDateAttribute;	// NSDate representing last document modification date.
extern NSString *PDFDocumentKeywordsAttribute;			// NSArray of NSStrings containing document keywords.


@interface PDFDocument : NSObject
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

// Convenience method. Returns a string representing the entire document (each page's string concatenated with line 
// feeds between pages).
- (NSString *) string;

// If a PDFDocument has a delegate, delegate methods may be called.  See: PDFDocumentNotifications and 
// PDFDocumentDelegate below.
- (void) setDelegate: (id) anObject;
- (id) delegate;

// Methods to record the current state of the PDFDocument as data or a file.
- (NSData *) dataRepresentation;
- (BOOL) writeToFile: (NSString *) path;
- (BOOL) writeToFile: (NSString *) path withOptions: (NSDictionary *) options;
- (BOOL) writeToURL: (NSURL *) url;
- (BOOL) writeToURL: (NSURL *) url withOptions: (NSDictionary *) options;

// -------- outline

// Returns the root outline object for the PDF (or NULL if none).
- (PDFOutline *) outlineRoot;

// Given a PDFSelection, this method returns the child outline item the selection most closely falls beneath. Since a 
// selection may span multiple outline items, only the point representing the first character of the PDFSelection is 
// considered. Typically, outline's indicate things like chapters for the PDF.  Therefore, this method would help you 
// identify the chapter the selection falls within.
- (PDFOutline *) outlineItemForSelection: (PDFSelection *) selection;

// -------- pages

// The number of pages in the document.
- (unsigned int) pageCount;

// Returns a PDFPage object representing the page at index. Will raise an exception if index is out of bounds. Indicees 
// are zero-based.
- (PDFPage *) pageAtIndex: (unsigned int) index;

// Given a PDFPage, returns the pages index within the document. Indicees are zero-based.
- (unsigned int) indexForPage: (PDFPage *) page;

// Methods allowing pages to be inserted, removed, and re-ordered. Can throw range exceptions.
- (void) insertPage: (PDFPage *) page atIndex: (unsigned int) index;
- (void) removePageAtIndex: (unsigned int) index;
- (void) exchangePageAtIndex: (unsigned int) indexA withPageAtIndex: (unsigned int) indexB;

// -------- find

// Searches entire document for string and returns an array of PDFSelections representing all instances found. May 
// return an empty array (if not found). Supported options are: NSCaseInsensitiveSearch, NSLiteralSearch, and 
// NSBackwardsSearch.
- (NSArray *) findString: (NSString *) string withOptions: (int) options;

// Begins a find, searching the document for string.  Search results are handled via a 
// PDFDocumentDidFindMatchNotification or if the delegate implements -[didMatchString:]. Supported options are: 
// NSCaseInsensitiveSearch, NSLiteralSearch, and NSBackwardsSearch.
- (void) beginFindString: (NSString *) string withOptions: (int) options;

// Searches for only the next instance of string beginning after the last character of selection with options (or 
// preceding the first character of the selection if NSBackwardsSearch is specified as a search option).
// Returns next instance as a PDFSelection or NULL if the end of the document is reached. Supported options are: 
// NSCaseInsensitiveSearch, NSLiteralSearch, and NSBackwardsSearch. Passing in NULL for selection will start the 
// search from the beginning of the document (or end if NSBackwardsSearch is specified).
- (PDFSelection *) findString: (NSString *) string fromSelection: (PDFSelection *) selection 
		withOptions: (int) options;

// Returns YES if document is currently searching for a string.
- (BOOL) isFinding;

// Method to cancel a search.  Can be called from a user method being serviced by a find notification.
- (void) cancelFindString;

// -------- selections

// Returns a selection representing text for the entire document.
- (PDFSelection *) selectionForEntireDocument;

// Returns a selection representing text from page startPage and point startPt to page endPage and to point endPt on 
// that page. Points are in page-space and relative to their respective pages.  Start and end page can be the same 
// (and are then equivalent to calling -[PDFPage selectionFromPoint: toPoint:]).
- (PDFSelection *) selectionFromPage: (PDFPage *) startPage atPoint: (NSPoint) startPt toPage: (PDFPage *) endPage 
		atPoint: (NSPoint) endPt;

// Similar to the obove method but allows you to specify a character index for the start and end pages.
- (PDFSelection *) selectionFromPage: (PDFPage *) startPage atCharacterIndex: (unsigned int) startChar 
		toPage: (PDFPage *) endPage atCharacterIndex: (unsigned int) endChar;

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

// If implemented by the delegate, called for every search instance found during a find. PDFDocument's implentation 
// accumulates each PDFSelection (instance) in an NSArray.
- (void) didMatchString: (PDFSelection *) instance;
@end
