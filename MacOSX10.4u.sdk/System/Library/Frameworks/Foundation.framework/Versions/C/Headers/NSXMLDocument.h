/*		NSXMLDocument.h
		Copyright 2004-2005, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <Foundation/NSXMLNode.h>

@class NSData;
@class NSXMLDTD;

// Input options
//  NSXMLNodeOptionsNone
//  NSXMLNodePreserveAll
//  NSXMLNodePreserveNamespaceOrder
//  NSXMLNodePreserveAttributeOrder
//  NSXMLNodePreserveEntities
//  NSXMLNodePreservePrefixes
//  NSXMLNodePreserveCDATA
//  NSXMLNodePreserveEmptyElements
//  NSXMLNodePreserveQuotes
//  NSXMLNodePreserveWhitespace
	
//  NSXMLDocumentTidyHTML
//  NSXMLDocumentTidyXML

//  NSXMLDocumentValidate

// Output options
//  NSXMLNodePrettyPrint
//  NSXMLDocumentIncludeContentTypeDeclaration

/*!
    @typedef NSXMLDocumentContentKind
	@abstract Define what type of document this is.
	@constant NSXMLDocumentXMLKind The default document type
	@constant NSXMLDocumentXHTMLKind Set if NSXMLDocumentTidyHTML is set and HTML is detected
	@constant NSXMLDocumentHTMLKind Outputs empty tags without a close tag, eg <br>
	@constant NSXMLDocumentTextKind Output the string value of the document
*/
typedef enum {
	NSXMLDocumentXMLKind = 0,
	NSXMLDocumentXHTMLKind,
	NSXMLDocumentHTMLKind,
	NSXMLDocumentTextKind
} NSXMLDocumentContentKind;

/*!
    @class NSXMLDocument
    @abstract An XML Document
	@discussion Note: if the application of a method would result in more than one element in the children array, an exception is thrown. Trying to add a document, namespace, attribute, or node with a parent also throws an exception. To add a node with a parent first detach or create a copy of it.
*/
@interface NSXMLDocument : NSXMLNode {
@protected
	NSString *_encoding;
	NSString *_version;
	NSXMLDTD *_docType;
	NSArray *_children;
	BOOL _childrenHaveMutated;
	BOOL _standalone;
	uint8_t _padding3[2];
	NSXMLElement *_rootElement;
	NSString *_URI;
	NSString *_MIMEType;
	unsigned int _fidelityMask;
	NSXMLDocumentContentKind _contentKind;
}

/*!
    @method initWithXMLString:options:error:
    @abstract Returns a document created from either XML or HTML, if the HTMLTidy option is set. Parse errors are returned in <tt>error</tt>.
*/
- (id)initWithXMLString:(NSString *)string options:(unsigned int)mask error:(NSError **)error;

/*!
    @method initWithContentsOfURL:options:error:
    @abstract Returns a document created from the contents of an XML or HTML URL. Connection problems such as 404, parse errors are returned in <tt>error</tt>.
*/
- (id)initWithContentsOfURL:(NSURL *)url options:(unsigned int)mask error:(NSError **)error;

/*!
    @method initWithData:options:error:
    @abstract Returns a document created from data. Parse errors are returned in <tt>error</tt>.
*/
- (id)initWithData:(NSData *)data options:(unsigned int)mask error:(NSError **)error; //primitive

/*!
    @method initWithRootElement:
    @abstract Returns a document with a single child, the root element.
*/
- (id)initWithRootElement:(NSXMLElement *)element;

#pragma mark --- Properties ---

+ (Class)replacementClassForClass:(Class)cls;

/*!
    @method setCharacterEncoding:
    @abstract Sets the character encoding to an IANA type.
*/
- (void)setCharacterEncoding:(NSString *)encoding; //primitive

/*!
    @method characterEncoding
    @abstract The character encoding or nil.
*/
- (NSString *)characterEncoding; //primitive

/*!
    @method setVersion:
    @abstract Sets the XML version. Should be 1.0 or 1.1.
*/
- (void)setVersion:(NSString *)version; //primitive

/*!
    @method version
    @abstract The version or nil.
*/
- (NSString *)version; //primitive

/*!
    @method setStandalone:
    @abstract Set whether this document depends on an external DTD. If this option is set the standalone declaration will appear on output.
*/
- (void)setStandalone:(BOOL)standalone; //primitive

/*!
    @method isStandalone
    @abstract Returns whether this document depends on an external DTD.
*/
- (BOOL)isStandalone; //primitive

/*!
    @method setDocumentContentKind:
    @abstract Set the kind of document.
*/
- (void)setDocumentContentKind:(NSXMLDocumentContentKind)kind; //primitive

/*!
    @method documentContentKind
    @abstract The kind of document.
*/
- (NSXMLDocumentContentKind)documentContentKind; //primitive

/*!
    @method setMIMEType:
    @abstract Set the MIME type, eg text/xml.
*/
- (void)setMIMEType:(NSString *)MIMEType; //primitive

/*!
    @method MIMEType
    @abstract The MIME type as set.
*/
- (NSString *)MIMEType; //primitive

/*!
    @method setDTD:
    @abstract Set the associated DTD. This DTD will be output with the document.
*/
- (void)setDTD:(NSXMLDTD *)documentTypeDeclaration; //primitive

/*!
    @method DTD
    @abstract The associated inline DTD.
*/
- (NSXMLDTD *)DTD; //primitive

/*!
    @method setRootElement:
    @abstract Set the root element. Removes all other children including comments and processing-instructions.
*/
- (void)setRootElement:(NSXMLNode *)root;

/*!
    @method rootElement
    @abstract The root element.
*/
- (NSXMLElement *)rootElement; //primitive

#pragma mark --- Children ---

/*!
    @method insertChild:atIndex:
    @abstract Inserts a child at a particular index.
*/
- (void)insertChild:(NSXMLNode *)child atIndex:(unsigned)index; //primitive

/*!
    @method insertChildren:atIndex:
    @abstract Insert several children at a particular index.
*/
- (void)insertChildren:(NSArray *)children atIndex:(unsigned)index;

/*!
    @method removeChildAtIndex:atIndex:
    @abstract Removes a child at a particular index.
*/
- (void)removeChildAtIndex:(unsigned)index; //primitive

/*!
    @method setChildren:
    @abstract Removes all existing children and replaces them with the new children. Set children to nil to simply remove all children.
*/
- (void)setChildren:(NSArray *)children; //primitive

/*!
    @method addChild:
    @abstract Adds a child to the end of the existing children.
*/
- (void)addChild:(NSXMLNode *)child;

/*!
    @method replaceChildAtIndex:withNode:
    @abstract Replaces a child at a particular index with another child.
*/
- (void)replaceChildAtIndex:(unsigned)index withNode:(NSXMLNode *)node;

#pragma mark --- Output ---

/*!
    @method XMLData
    @abstract Invokes XMLDataWithOptions with NSXMLNodeOptionsNone.
*/
- (NSData *)XMLData;

/*!
    @method XMLDataWithOptions:
    @abstract The representation of this node as it would appear in an XML document, encoded based on characterEncoding.
*/
- (NSData *)XMLDataWithOptions:(unsigned int)options;

#pragma mark --- XSLT ---

/*!
    @method objectByApplyingXSLTString:arguments:error:
    @abstract Applies XSLT with arguments (NSString key/value pairs) to this document, returning a new document.
*/
- (id)objectByApplyingXSLT:(NSData *)xslt arguments:(NSDictionary *)arguments error:(NSError **)error;

/*!
    @method objectByApplyingXSLTString:arguments:error:
    @abstract Applies XSLT with arguments (NSString key/value pairs) to this document, returning a new document.
*/
- (id)objectByApplyingXSLTString:(NSString *)xslt arguments:(NSDictionary *)arguments error:(NSError **)error;

/*!
    @method objectByApplyingXSLTAtURL:arguments:error:
    @abstract Applies the XSLT at a URL with arguments (NSString key/value pairs) to this document, returning a new document. Error may contain a connection error from the URL.
*/
- (id)objectByApplyingXSLTAtURL:(NSURL *)xsltURL arguments:(NSDictionary *)argument error:(NSError **)error;

#pragma mark --- Validation ---

- (BOOL)validateAndReturnError:(NSError **)error;

@end

#endif		// Availability guard
