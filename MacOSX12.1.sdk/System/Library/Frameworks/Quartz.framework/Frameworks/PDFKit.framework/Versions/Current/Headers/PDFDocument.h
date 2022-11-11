//
//  PDFDocument.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  PDFDocument is the logical representation of a PDF file. It is a container of PDFPages,
//  giving you the ability to load, modify, and save a set of PDF pages. It also gives you the
//  ability to unlock, search, and interact with the document's structure. You can instantiate
//  a PDFDocument with either the init method, initWithURL:, or initWithData:. Documents
//  that are locked or encrypted must be unlocked before reading or mutating any properties.
//  This is done via "unlockWithPassword:", and on success will return YES and post a
//  PDFDocumentDidUnlockNotification notification. You may search synchronously or asynchronously
//  via the set of "findString:" functions. When searching asynchronously, you will receive
//  periodic updates via search related notifications (See below).
//
//  Note that if you want your instance of a PDFDocument to be backed by a custom PDFPage
//  class, you can do so by register a delegate that overloads the method "classForPage".
//  In doing so, PDFDocument will instantiate your class via the init method.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFDestination, PDFOutline, PDFPage, PDFSelection, PDFDocumentPrivate;
@protocol PDFDocumentDelegate;

#if defined(PDFKIT_PLATFORM_OSX)

// Printing page-scaling modes (see PDFView).
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFPrintScalingMode)
{
    kPDFPrintPageScaleNone = 0, 
    kPDFPrintPageScaleToFit = 1, 
    kPDFPrintPageScaleDownToFit = 2
};

#endif

// Document permissions status. For encrypted PDF's, supplying the owner password will enable owner permission status.
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFDocumentPermissions)
{
	kPDFDocumentPermissionsNone = 0, 
	kPDFDocumentPermissionsUser = 1, 
	kPDFDocumentPermissionsOwner = 2
};

// Notifications.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidUnlockNotification PDFKIT_AVAILABLE(10_4, 11_0);           // The notification object is self.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidBeginFindNotification PDFKIT_AVAILABLE(10_4, 11_0);        // The notification object is self, no userInfo dictionary.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidEndFindNotification PDFKIT_AVAILABLE(10_4, 11_0);          // The notification object is self, no userInfo dictionary.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidBeginPageFindNotification PDFKIT_AVAILABLE(10_4, 11_0);    // The notification object is self, the userInfo dictionary
                                                                                                                //     contains the page index as an NSNumber for the key
                                                                                                                //     PDFDocumentPageIndexKey.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidEndPageFindNotification PDFKIT_AVAILABLE(10_4, 11_0);      // The notification object is self, the userInfo dictionary
                                                                                                                //     contains the page index as an NSNumber for the key
                                                                                                                //     PDFDocumentPageIndexKey.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidFindMatchNotification PDFKIT_AVAILABLE(10_4, 11_0);        // The notification object is self, the userInfo dictionary
                                                                                                                //     contains a PDFSelection (found instance) for the key
                                                                                                                //     @"PDFDocumentFoundSelection".
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidBeginWriteNotification PDFKIT_AVAILABLE(10_4, 11_0);       // The notification object is self, no userInfo dictionary.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidEndWriteNotification PDFKIT_AVAILABLE(10_4, 11_0);         // The notification object is self, no userInfo dictionary.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidBeginPageWriteNotification PDFKIT_AVAILABLE(10_4, 11_0);   // The notification object is self, the userInfo dictionary
                                                                                                                //     contains the page index as an NSNumber for the key
                                                                                                                //     PDFDocumentPageIndexKey.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidEndPageWriteNotification PDFKIT_AVAILABLE(10_4, 11_0);     // The notification object is self, the userInfo dictionary
                                                                                                                //     contains the page index as an NSNumber for the key
                                                                                                                //     PDFDocumentPageIndexKey.

// Notification keys
PDFKIT_EXTERN NSString* const PDFDocumentFoundSelectionKey PDFKIT_AVAILABLE(11_1, 15_0);                        // User info dictionary key to get PDFSelection from some
                                                                                                                // notifications described above
PDFKIT_EXTERN NSString* const PDFDocumentPageIndexKey PDFKIT_AVAILABLE(11_1, 15_0);                             // User info dictionary key to get page index from some
                                                                                                                // notifications described above

// Document attributes (see -[documentAttributes] below).
typedef NSString *PDFDocumentAttribute NS_STRING_ENUM;

PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentTitleAttribute PDFKIT_AVAILABLE(10_4, 11_0);                // NSString containing document title.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentAuthorAttribute PDFKIT_AVAILABLE(10_4, 11_0);               // NSString containing document author.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentSubjectAttribute PDFKIT_AVAILABLE(10_4, 11_0);              // NSString containing document title.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentCreatorAttribute PDFKIT_AVAILABLE(10_4, 11_0);              // NSString containing name of app that created document.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentProducerAttribute PDFKIT_AVAILABLE(10_4, 11_0);             // NSString containing name of app that produced PDF data.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentCreationDateAttribute PDFKIT_AVAILABLE(10_4, 11_0);         // NSDate representing document creation date.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentModificationDateAttribute PDFKIT_AVAILABLE(10_4, 11_0);     // NSDate representing last document modification date.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentKeywordsAttribute PDFKIT_AVAILABLE(10_4, 11_0);             // NSArray of NSStrings containing document keywords.

// File writing options (see -[writeToFile:withOptions:] or -[writeToURL:withOptions:options] below).
typedef NSString *PDFDocumentWriteOption NS_STRING_ENUM;

PDFKIT_EXTERN PDFDocumentWriteOption const PDFDocumentOwnerPasswordOption PDFKIT_AVAILABLE(10_4, 11_0);         // NSString for the owner's password. Required for encryption.
                                                                                                                // Owners have full privilege over the document.
PDFKIT_EXTERN PDFDocumentWriteOption const PDFDocumentUserPasswordOption PDFKIT_AVAILABLE(10_4, 11_0);          // NSString for the user's password. Optional for encryption.
                                                                                                                // Users can have limited access to modify, print, or write the file.
PDFKIT_EXTERN PDFDocumentWriteOption const PDFDocumentAccessPermissionsOption PDFKIT_AVAILABLE(12_0, 15_0);     // NSNumber containing a PDFAccessPermissions

// Some PDF access permissions are non-strict supersets of other permissions. Granting access to a superset
// permission also grants access to permission(s) it is a superset of. These permissions are as follows:
//
// * Granting PDFAllowsHighQualityPrinting also grants PDFAllowsLowQualityPrinting
// * Granting PDFAllowsDocumentChanges also grants PDFAllowsCommenting and PDFAllowsFormFieldEntry
// * Granting PDFAllowsContentCopying also grants PDFAllowsContentAccessibility
// * Granting PDFAllowsCommenting also grants PDFAllowsFormFieldEntry

typedef NS_ENUM(NSUInteger, PDFAccessPermissions) {
    PDFAllowsLowQualityPrinting    = (1 << 0),   // Print at up to 150 DPI
    PDFAllowsHighQualityPrinting   = (1 << 1),   // Print at any DPI
    PDFAllowsDocumentChanges       = (1 << 2),   // Modify the document contents except for page management
    PDFAllowsDocumentAssembly      = (1 << 3),   // Page management: insert, delete, and rotate pages
    PDFAllowsContentCopying        = (1 << 4),   // Extract content (text, images, etc.)
    PDFAllowsContentAccessibility  = (1 << 5),   // Extract content, but only for the purpose of accessibility
    PDFAllowsCommenting            = (1 << 6),   // Create or modify annotations, including form field entries
    PDFAllowsFormFieldEntry        = (1 << 7)    // Modify form field entries
};


PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFDocument : NSObject <NSCopying>
{
@private
    PDFDocumentPrivate* _private;
}

// -------- init

// Initializers.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

// -------- accessors

// May return NULL if the document was created from NSData.
@property (nonatomic, readonly, nullable) NSURL *documentURL;

// This is the CGPDFDocument associated with the PDFDocument object.  With this object you can call many CoreGraphics 
// API. May return NULL if the document was not created from an existing PDF file or data.
@property (nonatomic, readonly, nullable) CGPDFDocumentRef documentRef;

// Returns a dictionary with PDF metadata. Metadata is optional for PDF's and so some of the keys may be missing or the 
// entire dictionary may be empty.  See attributes above for keys.
@property (nonatomic, copy, nullable) NSDictionary *documentAttributes;

// PDF version of the PDF file (example: major version = 1, minor = 4; PDF v1.4).
@property (nonatomic, readonly) NSInteger majorVersion;
@property (nonatomic, readonly) NSInteger minorVersion;

// Whether the PDF is encrypted. With the right password, a PDF can be unlocked - nonetheless, the PDF still indicates
// that it is encrypted - just no longer locked. Some PDF's may be encrypted but can be unlocked with the empty string. 
// These are unlocked automatically. 
@property (nonatomic, readonly) BOOL isEncrypted;

// See comments above.
@property (nonatomic, readonly) BOOL isLocked;

// Means of passing in a password to unlock encrypted PDF's.  Calling -[unlockWithPassword:] will attempt to unlock the 
// PDF. If successful, a PDFDocumentDidUnlockNotification notification is sent. You cannot "re-lock" a PDF by passing 
// in a bogus password.  Returns YES if the document is now unlocked, NO otherwise ([self isLocked] == NO).
- (BOOL)unlockWithPassword:(NSString *)password;

// Even unlocked, encrypted PDF's may have certain restrictions regarding printing, copying, etc. placed upon them. These
// indicate the current state.
// Based on Adobe PDF Specification (1.7) Table 3.20: User access permissions
@property (nonatomic, readonly) BOOL allowsPrinting PDFKIT_AVAILABLE(10_4, 11_0);                 // Printing the document
@property (nonatomic, readonly) BOOL allowsCopying PDFKIT_AVAILABLE(10_4, 11_0);                  // Extract content (text, images, etc.)
@property (nonatomic, readonly) BOOL allowsDocumentChanges PDFKIT_AVAILABLE(10_13, 11_0);         // Modify the document contents except for page management (document attrubutes)
@property (nonatomic, readonly) BOOL allowsDocumentAssembly PDFKIT_AVAILABLE(10_13, 11_0);        // Page management: insert, delete, and rotate pages
@property (nonatomic, readonly) BOOL allowsContentAccessibility PDFKIT_AVAILABLE(10_13, 11_0);    // Extract content, but only for the purpose of accessibility
@property (nonatomic, readonly) BOOL allowsCommenting PDFKIT_AVAILABLE(10_13, 11_0);              // Create or modify annotations, including form field entries
@property (nonatomic, readonly) BOOL allowsFormFieldEntry PDFKIT_AVAILABLE(10_13, 11_0);          // Modify form field entries, even if allowsCommenting is NO

// Returns all 7 properties above as a PDFAccessPermissions value.
@property (nonatomic, readonly) PDFAccessPermissions accessPermissions;

// Returns the permissions status of the PDF document. You have kPDFDocumentPermissionsNone status for an encrypted 
// document that you have not supplied either a valid user or owner password. For a document with no encryption, you 
// automatically have kPDFDocumentPermissionsOwner status.
@property (nonatomic, readonly) PDFDocumentPermissions permissionsStatus PDFKIT_AVAILABLE(10_6, 11_0);

// Convenience method. Returns a string representing the entire document (each page's string concatenated with line
// feeds between pages).
@property (nonatomic, readonly, nullable) NSString *string;

// If a PDFDocument has a delegate, delegate methods may be called.  See: NSNotificationNames and 
// PDFDocumentDelegate below.
@property (nonatomic, weak, nullable) id<PDFDocumentDelegate> delegate;

// Methods to record the current state of the PDFDocument as data or a file.  Passing a QuartzFilter object in the 
// options dictionary with the key @"QuartzFilter" will allow you to have the filter applied when saving the PDF.
// NOTE: Versions of PDFKit before SnowLeopard did not return autorelease data for -[dataRepresentation]. You had to 
// release the data yourself.  Beginning with apps compiled on SnowLeopard the data returned is autoreleased.
- (nullable NSData *)dataRepresentation;
- (nullable NSData *)dataRepresentationWithOptions:(NSDictionary *)options PDFKIT_AVAILABLE(10_6, 11_0);

// -[writeToFile:withOptions:] and -[writeToURL:withOptions:] methods may take any CoreGraphics options that are typically
// passed into CGPDFContextCreate(...) and CGPDFContextCreateWithURL(...)'s auxiliaryInfo dictionary. For encryption, you
// may provide an owner and user password via the keys PDFDocumentWriteOption, where the values should be non-zero length
// strings.
- (BOOL)writeToFile:(NSString *)path;
- (BOOL)writeToFile:(NSString *)path withOptions:(nullable NSDictionary<PDFDocumentWriteOption, id> *)options;
- (BOOL)writeToURL:(NSURL *)url;
- (BOOL)writeToURL:(NSURL *)url withOptions:(nullable NSDictionary<PDFDocumentWriteOption, id> *)options;

// -------- outline

// Allows you specify a PDFOutline as the root outline item for this document.  When the PDF is saved the outline tree
// structure is written out to the destination PDF file. Passing NULL is a way to strip any outline from a document.
// Returns the root outline object for the PDF (or NULL if none).
@property (nonatomic, strong, nullable) PDFOutline *outlineRoot PDFKIT_AVAILABLE(10_6, 11_0);

// Given a PDFSelection, this method returns the child outline item the selection most closely falls beneath. Since a
// selection may span multiple outline items, only the point representing the first character of the PDFSelection is 
// considered. Typically, outlines indicate things like chapters for the PDF. Therefore, this method would help you
// identify the chapter the selection falls within.
- (nullable PDFOutline *)outlineItemForSelection:(PDFSelection *)selection;

// -------- pages

// The number of pages in the document.
@property (nonatomic, readonly) NSUInteger pageCount;

// Returns a PDFPage object representing the page at index. Will raise an exception if index is out of bounds. Indices
// are zero-based.
- (nullable PDFPage *)pageAtIndex:(NSUInteger)index;

// Given a PDFPage, returns the pages index within the document. Indices are zero-based.
- (NSUInteger)indexForPage:(PDFPage *)page;

// Methods allowing pages to be inserted, removed, and re-ordered. Can throw range exceptions.
// Note: when inserting a PDFPage, you have to be careful if that page came from another PDFDocument. PDFPage's have a 
// notion of a single document that owns them and when you call the methods below the PDFPage passed in is assigned a 
// new owning document.  You'll want to call -[PDFPage copy] first then and pass this copy to the blow methods. This 
// allows the orignal PDFPage to maintain its original document.
- (void)insertPage:(PDFPage *)page atIndex:(NSUInteger)index;
- (void)removePageAtIndex:(NSUInteger)index;
- (void)exchangePageAtIndex:(NSUInteger)indexA withPageAtIndex:(NSUInteger)indexB;

// This is the class that will be allocated and initialized when page objects are created for the document.  The 
// default implementation returns [PDFPage class] but if you want PDFDocument to use your own custom class you can 
// subclass PDFDocument and implement this method to return your own custom class.  Your class should be a subclass of 
// PDFPage (otherwise the behavior is undefined).
@property (nonatomic, readonly) Class pageClass;

// -------- find

// Searches entire document for string and returns an array of PDFSelections representing all instances found. May 
// return an empty array (if not found). Supported options are: NSCaseInsensitiveSearch, NSLiteralSearch, and 
// NSBackwardsSearch.
- (NSArray<PDFSelection*>*)findString:(NSString *)string withOptions:(NSStringCompareOptions)options;

// Begins a find, searching the document for string.  Search results are handled via a 
// PDFDocumentDidFindMatchNotification or if the delegate implements -[didMatchString:]. Supported options are: 
// NSCaseInsensitiveSearch, NSLiteralSearch, and NSBackwardsSearch.
- (void)beginFindString:(NSString *)string withOptions:(NSStringCompareOptions)options;

// Like -[beginFindString:withOptions:] above but it accepts an array of strings to search for.
// All other comments for -[beginFindString:withOptions:] above apply.
- (void)beginFindStrings:(NSArray<NSString*>*)strings withOptions:(NSStringCompareOptions)options PDFKIT_AVAILABLE(10_5, 11_0);

// Searches for only the next instance of string beginning after the last character of selection with options (or 
// preceding the first character of the selection if NSBackwardsSearch is specified as a search option).
// Returns next instance as a PDFSelection or NULL if the end of the document is reached. Supported options are: 
// NSCaseInsensitiveSearch, NSLiteralSearch, and NSBackwardsSearch. Passing in NULL for selection will start the 
// search from the beginning of the document (or end if NSBackwardsSearch is specified).
- (nullable PDFSelection *)findString:(NSString *)string fromSelection:(nullable PDFSelection *)selection withOptions:(NSStringCompareOptions)options;

// Returns YES if document is currently searching for a string.
@property (nonatomic, readonly) BOOL isFinding;

// Method to cancel a search.  Can be called from a user method being serviced by a find notification.
- (void)cancelFindString;

#if defined(PDFKIT_PLATFORM_OSX)

// -------- printing

// Returns a print operation suitable for printing the PDF document. Specify scaling mode and autorotate behaviors desired.
- (nullable NSPrintOperation *)printOperationForPrintInfo:(nullable NSPrintInfo *)printInfo scalingMode:(PDFPrintScalingMode)scaleMode autoRotate:(BOOL)doRotate PDFKIT_AVAILABLE(10_7, NA);

#endif

// -------- selections

// Returns a selection representing text for the entire document.
@property (nonatomic, readonly, nullable) PDFSelection *selectionForEntireDocument;

// Returns a selection representing text from page startPage and point startPt to page endPage and to point endPt on 
// that page. Points are in page-space and relative to their respective pages.  Start and end page can be the same 
// (and are then equivalent to calling -[PDFPage selectionFromPoint: toPoint:]).
- (nullable PDFSelection *)selectionFromPage:(PDFPage *)startPage atPoint:(PDFPoint)startPoint toPage:(PDFPage *)endPage atPoint:(PDFPoint)endPoint;

// Similar to the above method but allows you to specify a character index for the start and end pages.
- (nullable PDFSelection *)selectionFromPage:(PDFPage *)startPage atCharacterIndex:(NSUInteger)startCharacter toPage:(PDFPage *)endPage atCharacterIndex:(NSUInteger)endCharacter;

@end

// Document delegate
@protocol PDFDocumentDelegate< NSObject >
@optional

// Notification delegate methods. If implemented by the delegate, these are called. See notification comments above.
- (void)documentDidUnlock:(NSNotification *)notification;
- (void)documentDidBeginDocumentFind:(NSNotification *)notification;
- (void)documentDidEndDocumentFind:(NSNotification *)notification;
- (void)documentDidBeginPageFind:(NSNotification *)notification;
- (void)documentDidEndPageFind:(NSNotification *)notification;
- (void)documentDidFindMatch:(NSNotification *)notification;

// If implemented by the delegate, called for every search instance found during a find. PDFDocument's implementation 
// accumulates each PDFSelection (instance) in an NSArray.
- (void)didMatchString:(PDFSelection *)instance;

// If implemented by the delegate, will be called when a PDFPage is instantiated. PDFDocument's implementation calls
// -[PDFDocument pageClass] (see above). 
- (Class)classForPage PDFKIT_AVAILABLE(10_6, 11_0);

// If implemented by the delegate, will be called when a PDFAnnotation is instantiated by a page. PDFPage by default
// will instantiate object of class. This allows you to instead return your own PDFAnnotation subclass.
// Return nil for annotation types you do not subclass.
- (Class)classForAnnotationType:(NSString*)annotationType PDFKIT_AVAILABLE(10_13, 11_0);

#if defined(PDFKIT_PLATFORM_OSX)

// If implemented by the delegate, will be called when a PDFAnnotation is instantiated by a page. PDFPage by default 
// will instantiate object of class. This allows you to instead return your own PDFAnnotationXxxx subclass.
// If you would like to return your own PDFAnnotation subclass, use PDFDocument's delegate method
// -[classForAnnotationType:] instead.
- (Class)classForAnnotationClass:(Class)annotationClass PDFKIT_DEPRECATED(10_6, 10_12, NA, NA);

#endif

@end

NS_ASSUME_NONNULL_END
