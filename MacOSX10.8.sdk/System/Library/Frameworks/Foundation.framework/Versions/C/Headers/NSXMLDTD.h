/*	NSXMLDTD.h
	Copyright (c) 2004-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSXMLNode.h>

@class NSData, NSMutableDictionary;
@class NSXMLDTDNode;

/*!
    @class NSXMLDTD
    @abstract Defines the order, repetition, and allowable values for a document
*/
@interface NSXMLDTD : NSXMLNode {
@private
	NSString *_name;
	NSString *_publicID;
	NSString *_systemID;
	NSArray *_children;
	BOOL _childrenHaveMutated;
	uint8_t _padding3[3];
	NSMutableDictionary *_entities;
	NSMutableDictionary *_elements;
	NSMutableDictionary *_notations;
	NSMutableDictionary *_attributes;
	NSString *_original;
	BOOL _modified;
	uint8_t _padding2[3];
}

#if 0
#pragma mark --- Properties ---
#endif

- (id)initWithContentsOfURL:(NSURL *)url options:(NSUInteger)mask error:(NSError **)error;
- (id)initWithData:(NSData *)data options:(NSUInteger)mask error:(NSError **)error; //primitive

/*!
    @method setPublicID:
    @abstract Sets the public id. This identifier should be in the default catalog in /etc/xml/catalog or in a path specified by the environment variable XML_CATALOG_FILES. When the public id is set the system id must also be set.
*/
- (void)setPublicID:(NSString *)publicID; //primitive

/*!
    @method publicID
    @abstract The public id.
*/
- (NSString *)publicID; //primitive

/*!
    @method setSystemID:
    @abstract Sets the system id. This should be a URL that points to a valid DTD.
*/
- (void)setSystemID:(NSString *)systemID; //primitive

/*!
    @method systemID
    @abstract The system id.
*/
- (NSString *)systemID; //primitive

#if 0
#pragma mark --- Children ---
#endif

/*!
    @method insertChild:atIndex:
    @abstract Inserts a child at a particular index.
*/
- (void)insertChild:(NSXMLNode *)child atIndex:(NSUInteger)index; //primitive

/*!
    @method insertChildren:atIndex:
    @abstract Insert several children at a particular index.
*/
- (void)insertChildren:(NSArray *)children atIndex:(NSUInteger)index;

/*!
    @method removeChildAtIndex:
    @abstract Removes a child at a particular index.
*/
- (void)removeChildAtIndex:(NSUInteger)index; //primitive

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
- (void)replaceChildAtIndex:(NSUInteger)index withNode:(NSXMLNode *)node;

#if 0
#pragma mark --- Accessors ---
#endif

/*!
    @method entityDeclarationForName:
    @abstract Returns the entity declaration matching this name.
*/
- (NSXMLDTDNode *)entityDeclarationForName:(NSString *)name; //primitive

/*!
    @method notationDeclarationForName:
    @abstract Returns the notation declaration matching this name.
*/
- (NSXMLDTDNode *)notationDeclarationForName:(NSString *)name; //primitive

/*!
    @method elementDeclarationForName:
    @abstract Returns the element declaration matching this name.
*/
- (NSXMLDTDNode *)elementDeclarationForName:(NSString *)name; //primitive

/*!
    @method attributeDeclarationForName:
    @abstract Returns the attribute declaration matching this name.
*/
- (NSXMLDTDNode *)attributeDeclarationForName:(NSString *)name elementName:(NSString *)elementName; //primitive

/*!
    @method predefinedEntityDeclarationForName:
    @abstract Returns the predefined entity declaration matching this name.
	@discussion The five predefined entities are
	<ul><li>&amp;lt; - &lt;</li><li>&amp;gt; - &gt;</li><li>&amp;amp; - &amp;</li><li>&amp;quot; - &quot;</li><li>&amp;apos; - &amp;</li></ul>
*/
+ (NSXMLDTDNode *)predefinedEntityDeclarationForName:(NSString *)name;
@end
