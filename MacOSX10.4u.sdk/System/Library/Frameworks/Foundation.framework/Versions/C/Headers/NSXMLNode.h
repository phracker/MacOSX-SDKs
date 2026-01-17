/*		NSXMLNode.h
		Copyright 2004-2005, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <Foundation/NSObject.h>
#import <Foundation/NSXMLNodeOptions.h>

@class NSArray, NSDictionary, NSError, NSString, NSURL;
@class NSXMLElement, NSXMLDocument;

/*!
    @typedef NSXMLNodeKind
*/
typedef enum {
	NSXMLInvalidKind = 0,
	NSXMLDocumentKind,
	NSXMLElementKind,
	NSXMLAttributeKind,
	NSXMLNamespaceKind,
	NSXMLProcessingInstructionKind,
	NSXMLCommentKind,
	NSXMLTextKind,
	NSXMLDTDKind,
	NSXMLEntityDeclarationKind,
	NSXMLAttributeDeclarationKind,
	NSXMLElementDeclarationKind,
	NSXMLNotationDeclarationKind
} NSXMLNodeKind;

// initWithKind options
//  NSXMLNodeOptionsNone
//  NSXMLNodePreserveAll
//  NSXMLNodePreserveNamespaceOrder
//  NSXMLNodePreserveAttributeOrder
//  NSXMLNodePreserveEntities
//  NSXMLNodePreservePrefixes
//  NSXMLNodeIsCDATA
//  NSXMLNodeExpandEmptyElement
//  NSXMLNodeCompactEmptyElement
//  NSXMLNodeUseSingleQuotes
//  NSXMLNodeUseDoubleQuotes

// Output options
//  NSXMLNodePrettyPrint

/*!
    @class NSXMLNode
    @abstract The basic unit of an XML document.
*/

@interface NSXMLNode : NSObject <NSCopying> {
@protected
	NSXMLNodeKind _kind;
	NSXMLNode *_parent;
	unsigned _index;
	id _objectValue;
}

/*!
    @method initWithKind:
    @abstract Invokes @link initWithKind:options: @/link with options set to NSXMLNodeOptionsNone
*/
- (id)initWithKind:(NSXMLNodeKind)kind;

/*!
    @method initWithKind:options:
    @abstract Inits a node with fidelity options as description NSXMLNodeOptions.h
*/
- (id)initWithKind:(NSXMLNodeKind)kind options:(unsigned int)options; //primitive

/*!
    @method document:
    @abstract Returns an empty document.
*/
+ (id)document;

/*!
    @method documentWithRootElement:
    @abstract Returns a document
    @param element The document's root node.
*/
+ (id)documentWithRootElement:(NSXMLElement *)element;

/*!
    @method elementWithName:
    @abstract Returns an element <tt>&lt;name>&lt;/name></tt>.
*/
+ (id)elementWithName:(NSString *)name;

/*!
    @method elementWithName:URI:
    @abstract Returns an element whose full QName is specified.
*/
+ (id)elementWithName:(NSString *)name URI:(NSString *)URI;

/*!
    @method elementWithName:stringValue:
    @abstract Returns an element with a single text node child <tt>&lt;name>string&lt;/name></tt>.
*/
+ (id)elementWithName:(NSString *)name stringValue:(NSString *)string;

/*!
    @method elementWithName:children:attributes:
    @abstract Returns an element children and attributes <tt>&lt;name attr1="foo" attr2="bar">&lt;-- child1 -->child2&lt;/name></tt>.
*/
+ (id)elementWithName:(NSString *)name children:(NSArray *)children attributes:(NSArray *)attributes;

/*!
    @method attributeWithName:stringValue:
    @abstract Returns an attribute <tt>name="stringValue"</tt>.
*/
+ (id)attributeWithName:(NSString *)name stringValue:(NSString *)stringValue;

/*!
    @method attributeWithLocalName:URI:stringValue:
    @abstract Returns an attribute whose full QName is specified.
*/
+ (id)attributeWithName:(NSString *)name URI:(NSString *)URI stringValue:(NSString *)stringValue;

/*!
    @method namespaceWithName:stringValue:
    @abstract Returns a namespace <tt>xmlns:name="stringValue"</tt>.
*/
+ (id)namespaceWithName:(NSString *)name stringValue:(NSString *)stringValue;

/*!
    @method processingInstructionWithName:stringValue:
    @abstract Returns a processing instruction <tt>&lt;?name stringValue></tt>.
*/
+ (id)processingInstructionWithName:(NSString *)name stringValue:(NSString *)stringValue;

/*!
    @method commentWithStringValue:
    @abstract Returns a comment <tt>&lt;--stringValue--></tt>.
*/
+ (id)commentWithStringValue:(NSString *)stringValue;

/*!
    @method textWithStringValue:
    @abstract Returns a text node.
*/
+ (id)textWithStringValue:(NSString *)stringValue;

/*!
    @method DTDNodeWithXMLString:
    @abstract Returns an element, attribute, entity, or notation DTD node based on the full XML string.
*/
+ (id)DTDNodeWithXMLString:(NSString *)string;

#pragma mark --- Properties ---

/*!
    @method kind:
    @abstract Returns an element, attribute, entity, or notation DTD node based on the full XML string.
*/
- (NSXMLNodeKind)kind; //primitive

/*!
    @method setName:
    @abstract Sets the nodes name. Applicable for element, attribute, namespace, processing-instruction, document type declaration, element declaration, attribute declaration, entity declaration, and notation declaration.
*/
- (void)setName:(NSString *)name; //primitive

/*!
    @method name:
    @abstract Returns the name or the empty string.
*/
- (NSString *)name; //primitive

/*!
    @method setObjectValue:
    @abstract Sets the content of the node. Setting the objectValue removes all existing children including processing instructions and comments. Setting the object value on an element creates a single text node child.
*/
- (void)setObjectValue:(id)value; //primitive

/*!
    @method objectValue
    @abstract The object value as set. May be nil.
*/
- (id)objectValue; //primitive

/*!
    @method setStringValue:
    @abstract Sets the content of the node. Setting the stringValue removes all existing children including processing instructions and comments. Setting the string value on an element creates a single text node child.
*/
- (void)setStringValue:(NSString *)string;

/*!
    @method setStringValue:
    @abstract Sets the content as with @link setStringValue: @/link, but when "resolve" is true, character references, predefined entities and user entities available in the document's dtd are resolved. Entities not available in the dtd remain in their entity form.
*/
- (void)setStringValue:(NSString *)string resolvingEntities:(BOOL)resolve; //primitive

/*!
    @method stringValue
    @abstract The string value of the node, which may be either its content or child text nodes, depending on the type of node. Elements are recursed and text nodes concatenated in document order with no intervening spaces.
*/
- (NSString *)stringValue; //primitive

#pragma mark --- Tree Navigation ---

/*!
    @method index
    @abstract A node's index amongst its siblings.
*/
- (unsigned)index; //primitive

/*!
    @method level
    @abstract The depth of the node within the tree. Documents and standalone nodes are level 0.
*/
- (unsigned)level;

/*!
    @method rootDocument
    @abstract The encompassing document or nil.
*/
- (NSXMLDocument *)rootDocument;

/*!
    @method parent
    @abstract The parent of this node. Documents and standalone Nodes have a nil parent; there is not a 1-to-1 relationship between parent and children, eg a namespace cannot be a child but has a parent element.
*/
- (NSXMLNode *)parent; //primitive

/*!
    @method childCount
    @abstract The amount of children, relevant for documents, elements, and document type declarations. Use this instead of [[self children] count].
*/
- (unsigned)childCount; //primitive

/*!
    @method children
    @abstract An immutable array of child nodes. Relevant for documents, elements, and document type declarations.
*/
- (NSArray *)children; //primitive

/*!
    @method childAtIndex:
    @abstract Returns the child node at a particular index.
*/
- (NSXMLNode *)childAtIndex:(unsigned)index; //primitive

/*!
    @method previousSibling:
    @abstract Returns the previous sibling, or nil if there isn't one.
*/
- (NSXMLNode *)previousSibling;

/*!
    @method nextSibling:
    @abstract Returns the next sibling, or nil if there isn't one.
*/
- (NSXMLNode *)nextSibling;

/*!
    @method previousNode:
    @abstract Returns the previous node in document order. This can be used to walk the tree backwards.
*/
- (NSXMLNode *)previousNode;

/*!
    @method nextNode:
    @abstract Returns the next node in document order. This can be used to walk the tree forwards.
*/
- (NSXMLNode *)nextNode;

/*!
    @method detach:
    @abstract Detaches this node from its parent.
*/
- (void)detach; //primitive

/*!
    @method detach:
    @abstract Returns the XPath to this node, for example foo/bar[2]/baz.
*/
- (NSString *)XPath;

#pragma mark --- QNames ---

/*!
	@method localName
	@abstract Returns the local name bar if this attribute or element's name is foo:bar
*/
- (NSString *)localName; //primitive

/*!
	@method prefix
	@abstract Returns the prefix foo if this attribute or element's name if foo:bar
*/
- (NSString *)prefix; //primitive

/*!
	@method setURI
	@abstract Set the URI of this element, attribute, or document. For documents it is the URI of document origin.
*/
- (void)setURI:(NSString *)URI; //primitive

/*!
	@method URI
	@abstract Returns the URI of this element, attribute, or document. For documents it is the URI of document origin and is automatically set when using initWithContentsOfURL.
*/
- (NSString *)URI; //primitive

/*!
    @method localNameForName:
    @abstract Returns the local name bar in foo:bar.
*/
+ (NSString *)localNameForName:(NSString *)name;

/*!
    @method localNameForName:
    @abstract Returns the prefix foo in the name foo:bar.
*/
+ (NSString *)prefixForName:(NSString *)name;


/*!
    @method predefinedNamespaceForPrefix:
    @abstract Returns the namespace belonging to one of the predefined namespaces xml, xs, or xsi
*/
+ (NSXMLNode *)predefinedNamespaceForPrefix:(NSString *)name;

#pragma mark --- Output ---

/*!
    @method description
    @abstract Used for debugging. May give more information than XMLString.
*/
- (NSString *)description;

/*!
    @method XMLString
    @abstract The representation of this node as it would appear in an XML document.
*/
- (NSString *)XMLString;

/*!
    @method XMLStringWithOptions:
    @abstract The representation of this node as it would appear in an XML document, with various output options available.
*/
- (NSString *)XMLStringWithOptions:(unsigned int)options;

/*!
    @method canonicalXMLStringPreservingComments:
    @abstract W3 canonical form (http://www.w3.org/TR/xml-c14n). The input option NSXMLNodePreserveWhitespace should be set for true canonical form.
*/
- (NSString *)canonicalXMLStringPreservingComments:(BOOL)comments;

#pragma mark --- XPath/XQuery ---

/*!
    @method nodesForXPath:error:
    @abstract Returns the nodes resulting from applying an XPath to this node using the node as the context item ("."). normalizeAdjacentTextNodesPreservingCDATA:NO should be called if there are adjacent text nodes since they are not allowed under the XPath/XQuery Data Model.
	@returns An array whose elements are a kind of NSXMLNode.
*/
- (NSArray *)nodesForXPath:(NSString *)xpath error:(NSError **)error;

/*!
    @method objectsForXQuery:constants:error:
    @abstract Returns the objects resulting from applying an XQuery to this node using the node as the context item ("."). Constants are a name-value dictionary for constants declared "external" in the query. normalizeAdjacentTextNodesPreservingCDATA:NO should be called if there are adjacent text nodes since they are not allowed under the XPath/XQuery Data Model.
	@returns An array whose elements are kinds of NSArray, NSData, NSDate, NSNumber, NSString, NSURL, or NSXMLNode.
*/
- (NSArray *)objectsForXQuery:(NSString *)xquery constants:(NSDictionary *)constants error:(NSError **)error;

- (NSArray *)objectsForXQuery:(NSString *)xquery error:(NSError **)error;
@end

#endif		// Availability guard
