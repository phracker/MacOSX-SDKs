/*	CFXMLNode.h
	Copyright (c) 1998-2019, Apple Inc. and the Swift project authors
 
	Portions Copyright (c) 2014-2019, Apple Inc. and the Swift project authors
	Licensed under Apache License v2.0 with Runtime Library Exception
	See http://swift.org/LICENSE.txt for license information
	See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
*/

/*  CFXMLParser (and thus CFXMLNode) are deprecated as of Mac OS X 10.8 and iOS 6.0. The suggested replacements are the Foundation classes NSXMLParser and NSXMLDocument, or the libxml2 library. */

#include <TargetConditionals.h>

#if TARGET_OS_OSX

#if !defined(__COREFOUNDATION_CFXMLNODE__)
#define __COREFOUNDATION_CFXMLNODE__ 1

#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFTree.h>
#include <CoreFoundation/CFURL.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN

#define __CFXMLNode_DEPRECATION_MSG "CFXMLNode is deprecated, use NSXMLParser, NSXMLDocument or libxml2 library instead"

CF_ENUM(CFIndex) {
	kCFXMLNodeCurrentVersion = 1
};

typedef const struct __CFXMLNode * CFXMLNodeRef;
typedef CFTreeRef CFXMLTreeRef;

/*  An CFXMLNode describes an individual XML construct - like a tag, or a comment, or a string
    of character data.  Each CFXMLNode contains 3 main pieces of information - the node's type,
    the data string, and a pointer to an additional data structure.  The node's type ID is an enum
    value of type CFXMLNodeTypeID.  The data string is always a CFStringRef; the meaning of the
    string is dependent on the node's type ID. The format of the additional data is also dependent
    on the node's type; in general, there is a custom structure for each type that requires
    additional data.  See below for the mapping from type ID to meaning of the data string and
    structure of the additional data.  Note that these structures are versioned, and may change
    as the parser changes.  The current version can always be identified by kCFXMLNodeCurrentVersion;
    earlier versions can be identified and used by passing earlier values for the version number
    (although the older structures would have been removed from the header).

    An CFXMLTree is simply a CFTree whose context data is known to be an CFXMLNodeRef.  As
    such, an CFXMLTree can be used to represent an entire XML document; the CFTree
    provides the tree structure of the document, while the CFXMLNodes identify and describe
    the nodes of the tree.  An XML document can be parsed to a CFXMLTree, and a CFXMLTree
    can generate the data for the equivalent XML document - see CFXMLParser.h for more
    information on parsing XML.
    */

/* Type codes for the different possible XML nodes; this list may grow.*/
typedef CF_ENUM(CFIndex, CFXMLNodeTypeCode) {
    kCFXMLNodeTypeDocument = 1,
    kCFXMLNodeTypeElement = 2,
    kCFXMLNodeTypeAttribute = 3,
    kCFXMLNodeTypeProcessingInstruction = 4,
    kCFXMLNodeTypeComment = 5,
    kCFXMLNodeTypeText = 6,
    kCFXMLNodeTypeCDATASection = 7,
    kCFXMLNodeTypeDocumentFragment = 8,
    kCFXMLNodeTypeEntity = 9,
    kCFXMLNodeTypeEntityReference = 10,
    kCFXMLNodeTypeDocumentType = 11,
    kCFXMLNodeTypeWhitespace = 12,
    kCFXMLNodeTypeNotation = 13,
    kCFXMLNodeTypeElementTypeDeclaration = 14,
    kCFXMLNodeTypeAttributeListDeclaration = 15
};

typedef struct {
    CFDictionaryRef attributes;
    CFArrayRef attributeOrder;
    Boolean isEmpty;
    char _reserved[3];
} CFXMLElementInfo;

typedef struct {
    CFStringRef dataString;
} CFXMLProcessingInstructionInfo;

typedef struct {
    CFURLRef sourceURL;
    CFStringEncoding encoding;
} CFXMLDocumentInfo;

typedef struct {
    CFURLRef systemID;
    CFStringRef publicID;
} CFXMLExternalID;

typedef struct {
    CFXMLExternalID externalID;
} CFXMLDocumentTypeInfo;

typedef struct {
    CFXMLExternalID externalID;
} CFXMLNotationInfo;

typedef struct {
    /* This is expected to change in future versions */
    CFStringRef contentDescription;
} CFXMLElementTypeDeclarationInfo;

typedef struct {
    /* This is expected to change in future versions */
    CFStringRef attributeName;
    CFStringRef typeString;
    CFStringRef defaultString;
} CFXMLAttributeDeclarationInfo;

typedef struct {
    CFIndex numberOfAttributes;
    CFXMLAttributeDeclarationInfo *attributes;
} CFXMLAttributeListDeclarationInfo;

typedef CF_ENUM(CFIndex, CFXMLEntityTypeCode) {
    kCFXMLEntityTypeParameter,       /* Implies parsed, internal */
    kCFXMLEntityTypeParsedInternal,
    kCFXMLEntityTypeParsedExternal,
    kCFXMLEntityTypeUnparsed,
    kCFXMLEntityTypeCharacter
};

typedef struct {
    CFXMLEntityTypeCode entityType;
    CFStringRef replacementText;     /* NULL if entityType is external or unparsed */
    CFXMLExternalID entityID;          /* entityID.systemID will be NULL if entityType is internal */
    CFStringRef notationName;        /* NULL if entityType is parsed */
} CFXMLEntityInfo;

typedef struct {
    CFXMLEntityTypeCode entityType;
} CFXMLEntityReferenceInfo;

/*
 dataTypeCode                       meaning of dataString                format of infoPtr
 ===========                        =====================                =================
 kCFXMLNodeTypeDocument             <currently unused>                   CFXMLDocumentInfo *
 kCFXMLNodeTypeElement              tag name                             CFXMLElementInfo *
 kCFXMLNodeTypeAttribute            <currently unused>                   <currently unused>
 kCFXMLNodeTypeProcessingInstruction   name of the target                   CFXMLProcessingInstructionInfo *
 kCFXMLNodeTypeComment              text of the comment                  NULL
 kCFXMLNodeTypeText                 the text's contents                  NULL
 kCFXMLNodeTypeCDATASection         text of the CDATA                    NULL
 kCFXMLNodeTypeDocumentFragment     <currently unused>                   <currently unused>
 kCFXMLNodeTypeEntity               name of the entity                   CFXMLEntityInfo *
 kCFXMLNodeTypeEntityReference      name of the referenced entity        CFXMLEntityReferenceInfo *
 kCFXMLNodeTypeDocumentType         name given as top-level element      CFXMLDocumentTypeInfo *
 kCFXMLNodeTypeWhitespace           text of the whitespace               NULL
 kCFXMLNodeTypeNotation             notation name                        CFXMLNotationInfo *
 kCFXMLNodeTypeElementTypeDeclaration     tag name                       CFXMLElementTypeDeclarationInfo *
 kCFXMLNodeTypeAttributeListDeclaration   tag name                       CFXMLAttributeListDeclarationInfo *
*/

CF_EXPORT
CFTypeID CFXMLNodeGetTypeID(void) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

/* Creates a new node based on xmlType, dataString, and additionalInfoPtr.  version (together with xmlType) determines the expected structure of additionalInfoPtr */
CF_EXPORT
CFXMLNodeRef CFXMLNodeCreate(CFAllocatorRef alloc, CFXMLNodeTypeCode xmlType, CFStringRef dataString, const void *additionalInfoPtr, CFIndex version) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

/* Creates a copy of origNode (which may not be NULL). */
CF_EXPORT
CFXMLNodeRef CFXMLNodeCreateCopy(CFAllocatorRef alloc, CFXMLNodeRef origNode) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

CF_EXPORT
CFXMLNodeTypeCode CFXMLNodeGetTypeCode(CFXMLNodeRef node) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

CF_EXPORT
CFStringRef CFXMLNodeGetString(CFXMLNodeRef node) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

CF_EXPORT
const void *CFXMLNodeGetInfoPtr(CFXMLNodeRef node) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

CF_EXPORT
CFIndex CFXMLNodeGetVersion(CFXMLNodeRef node) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

/* CFXMLTreeRef */

/* Creates a childless, parentless tree from node */
CF_EXPORT
CFXMLTreeRef CFXMLTreeCreateWithNode(CFAllocatorRef allocator, CFXMLNodeRef node) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

/* Extracts and returns the node stored in xmlTree */
CF_EXPORT
CFXMLNodeRef CFXMLTreeGetNode(CFXMLTreeRef xmlTree) API_DEPRECATED(__CFXMLNode_DEPRECATION_MSG, macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

#undef __CFXMLNode_DEPRECATION_MSG
    
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif /* ! __COREFOUNDATION_CFXMLNODE__ */

#endif /* TARGET_OS_OSX */
