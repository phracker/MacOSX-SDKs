/*		NSXMLDTDNode.h
		Copyright 2004-2005, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <Foundation/NSXMLNode.h>

/*!
    @typedef NSXMLDTDNodeKind
	@abstract The subkind of a DTD node kind.
*/
typedef enum {
	NSXMLEntityGeneralKind = 1,
	NSXMLEntityParsedKind,
	NSXMLEntityUnparsedKind,
	NSXMLEntityParameterKind,
	NSXMLEntityPredefined,

	NSXMLAttributeCDATAKind,
	NSXMLAttributeIDKind,
	NSXMLAttributeIDRefKind,
	NSXMLAttributeIDRefsKind,
	NSXMLAttributeEntityKind,
	NSXMLAttributeEntitiesKind,
	NSXMLAttributeNMTokenKind,
	NSXMLAttributeNMTokensKind,
	NSXMLAttributeEnumerationKind,
	NSXMLAttributeNotationKind,

	NSXMLElementDeclarationUndefinedKind,
	NSXMLElementDeclarationEmptyKind,
	NSXMLElementDeclarationAnyKind,
	NSXMLElementDeclarationMixedKind,
	NSXMLElementDeclarationElementKind
} NSXMLDTDNodeKind;

/*!
    @class NSXMLDTDNode
    @abstract The nodes that are exclusive to a DTD
	@discussion Every DTD node has a name. Object value is defined as follows:<ul>
		<li><b>Entity declaration</b> - the string that that entity resolves to eg "&lt;"</li>
		<li><b>Attribute declaration</b> - the default value, if any</li>
		<li><b>Element declaration</b> - the validation string</li>
		<li><b>Notation declaration</b> - no objectValue</li></ul>
*/
@interface NSXMLDTDNode : NSXMLNode {
@protected
	NSXMLDTDNodeKind _DTDKind;
	NSString *_name;
	NSString *_notationName;
	NSString *_publicID;
	NSString *_systemID;
}

/*!
    @method initWithXMLString:
    @abstract Returns an element, attribute, entity, or notation DTD node based on the full XML string.
*/
- (id)initWithXMLString:(NSString *)string; //primitive

/*!
    @method setDTDKind:
    @abstract Sets the DTD sub kind.
*/
- (void)setDTDKind:(NSXMLDTDNodeKind)kind; //primitive

/*!
    @method DTDKind
    @abstract The DTD sub kind.
*/
- (NSXMLDTDNodeKind)DTDKind; //primitive

/*!
    @method isExternal
    @abstract True if the system id is set. Valid for entities and notations.
*/
- (BOOL)isExternal; //primitive

/*!
    @method setPublicID:
    @abstract Sets the public id. This identifier should be in the default catalog in /etc/xml/catalog or in a path specified by the environment variable XML_CATALOG_FILES. When the public id is set the system id must also be set. Valid for entities and notations.
*/
- (void)setPublicID:(NSString *)publicID; //primitive

/*!
    @method publicID
    @abstract The public id.
*/
- (NSString *)publicID; //primitive

/*!
    @method setSystemID:
    @abstract Sets the system id. This should be a URL that points to a valid DTD. Valid for entities and notations.
*/
- (void)setSystemID:(NSString *)systemID; //primitive

/*!
    @method systemID
    @abstract The system id.
*/
- (NSString *)systemID; //primitive

/*!
    @method setNotationName:
    @abstract Set the notation name. Valid for entities only.
*/
- (void)setNotationName:(NSString *)notationName; //primitive

/*!
    @method notationName
    @abstract The notation name.
*/
- (NSString *)notationName; //primitive

@end

#endif		// Availability guard
