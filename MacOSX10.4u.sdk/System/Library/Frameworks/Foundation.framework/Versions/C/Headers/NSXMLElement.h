/*		NSXMLElement.h
		Copyright 2004-2005, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <Foundation/NSXMLNode.h>

@class NSDictionary, NSMutableArray, NSEnumerator;

/*!
    @class NSXMLElement
    @abstract An XML element
    @discussion Note: Trying to add a document, namespace, attribute, or node with a parent throws an exception. To add a node with a parent first detach or create a copy of it.
*/
@interface NSXMLElement : NSXMLNode {
@protected
	NSString *_name;
	NSMutableArray *_attributes;
	NSMutableArray *_namespaces;
	NSArray *_children;
	BOOL _childrenHaveMutated;
	uint8_t _padding3[3];
	NSString *_URI;	
	int _prefixIndex;
}

/*!
    @method initWithName:
    @abstract Returns an element <tt>&lt;name>&lt;/name></tt>.
*/
- (id)initWithName:(NSString *)name;

/*!
    @method initWithName:URI:
    @abstract Returns an element whose full QName is specified.
*/
- (id)initWithName:(NSString *)name URI:(NSString *)URI; //primitive

/*!
    @method initWithName:stringValue:
    @abstract Returns an element with a single text node child <tt>&lt;name>string&lt;/name></tt>.
*/
- (id)initWithName:(NSString *)name stringValue:(NSString *)string;

/*!
    @method initWithXMLString:error:
    @abstract Returns an element created from a string. Parse errors may are collected in <tt>error</tt>.
*/
- (id)initWithXMLString:(NSString *)string error:(NSError **)error;

#pragma mark --- Elements by name ---

/*!
    @method elementsForName:
    @abstract Returns all of the child elements that match this name.
*/
- (NSArray *)elementsForName:(NSString *)name;

/*!
    @method elementsForLocalName:URI
    @abstract Returns all of the child elements that match this localname URI pair.
*/
- (NSArray *)elementsForLocalName:(NSString *)localName URI:(NSString *)URI;

#pragma mark --- Attributes ---

/*!
    @method addAttribute:
    @abstract Adds an attribute. Attributes with duplicate names are not added.
*/
- (void)addAttribute:(NSXMLNode *)attribute; //primitive

/*!
    @method removeAttributeForName:
    @abstract Removes an attribute based on its name.
*/
- (void)removeAttributeForName:(NSString *)name; //primitive

/*!
    @method setAttributes:
    @abstract Set the attributes. In the case of duplicate names, the first attribute with the name is used.
*/
- (void)setAttributes:(NSArray *)attributes; //primitive

/*!
    @method setAttributesAsDictionary:
    @abstract Set the attributes base on a name-value dictionary.
*/
- (void)setAttributesAsDictionary:(NSDictionary *)attributes;

/*!
    @method attributes
    @abstract The attributes.
*/
- (NSArray *)attributes; //primitive

/*!
    @method attributeForName:
    @abstract Returns an attribute matching this name.
*/
- (NSXMLNode *)attributeForName:(NSString *)name;

/*!
    @method attributeForLocalName:URI:
    @abstract Returns an attribute matching this localname URI pair.
*/
- (NSXMLNode *)attributeForLocalName:(NSString *)localName URI:(NSString *)URI; //primitive

#pragma mark --- Namespaces ---

/*!
    @method addNamespace:URI:
    @abstract Adds a namespace. Namespaces with duplicate names are not added.
*/
- (void)addNamespace:(NSXMLNode *)aNamespace; //primitive

/*!
    @method addNamespace:URI:
    @abstract Removes a namespace with a particular name.
*/
- (void)removeNamespaceForPrefix:(NSString *)name; //primitive

/*!
    @method setNamespaces:
    @abstract Set the namespaces. In the case of duplicate names, the first namespace with the name is used.
*/
- (void)setNamespaces:(NSArray *)namespaces; //primitive

/*!
    @method setNamespaces:
    @abstract The namespaces.
*/
- (NSArray *)namespaces; //primitive

/*!
    @method namespaceForPrefix:
    @abstract Returns the namespace matching this prefix.
*/
- (NSXMLNode *)namespaceForPrefix:(NSString *)name;

/*!
    @method resolveNamespaceForName:
    @abstract Returns the namespace who matches the prefix of the name given. Looks in the entire namespace chain.
*/
- (NSXMLNode *)resolveNamespaceForName:(NSString *)name;

/*!
    @method resolvePrefixForNamespaceURI:
    @abstract Returns the URI of this prefix. Looks in the entire namespace chain.
*/
- (NSString *)resolvePrefixForNamespaceURI:(NSString *)namespaceURI;

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

/*!
    @method normalizeAdjacentTextNodesPreservingCDATA:
    @abstract Adjacent text nodes are coalesced. If the node's value is the empty string, it is removed. This should be called with a value of NO before using XQuery or XPath.
*/
- (void)normalizeAdjacentTextNodesPreservingCDATA:(BOOL)preserve;

@end

#endif		// Availability guard

