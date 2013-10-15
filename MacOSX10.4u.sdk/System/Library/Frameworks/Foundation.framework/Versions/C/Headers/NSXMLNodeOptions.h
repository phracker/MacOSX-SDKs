/*		NSXMLNodeOptions.h
		Copyright 2004-2005, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

/*!
    @enum Init, input, and output options
    @constant NSXMLNodeIsCDATA This text node is CDATA
    @constant NSXMLNodeExpandEmptyElement This element should be expanded when empty, ie &lt;a>&lt;/a>. This is the default.
    @constant NSXMLNodeCompactEmptyElement This element should contract when empty, ie &lt;a/>
    @constant NSXMLNodeUseSingleQuotes Use single quotes on this attribute or namespace
    @constant NSXMLNodeUseDoubleQuotes Use double quotes on this attribute or namespace. This is the default.

    @constant NSXMLNodeOptionsNone Use the default options
    @constant NSXMLNodePreserveAll Turn all preservation options on
    @constant NSXMLNodePreserveNamespaceOrder Preserve the order of namespaces
    @constant NSXMLNodePreserveAttributeOrder Preserve the order of attributes
    @constant NSXMLNodePreserveEntities Entities should not be resolved on output
    @constant NSXMLNodePreservePrefixes Prefixes should not be chosen based on closest URI definition
    @constant NSXMLNodePreserveCDATA CDATA should be preserved
    @constant NSXMLNodePreserveEmptyElements Remember whether an empty element was in expanded or contracted form
    @constant NSXMLNodePreserveQuotes Remember whether an attribute used single or double quotes
    @constant NSXMLNodePreserveWhitespace Preserve non-content whitespace
    @constant NSXMLNodePreserveDTD Preserve the DTD until it is modified
    
    @constant NSXMLDocumentTidyHTML Try to change HTML into valid XHTML
    @constant NSXMLDocumentTidyXML Try to change malformed XML into valid XML
    
    @constant NSXMLDocumentValidate Valid this document against its DTD

    @constant NSXMLNodePrettyPrint Output this node with extra space for readability
    @constant NSXMLDocumentIncludeContentTypeDeclaration Include a content type declaration for HTML or XHTML
*/

enum {
    NSXMLNodeOptionsNone = 0,
    
    // Init
    NSXMLNodeIsCDATA = 1 << 0,
    NSXMLNodeExpandEmptyElement = 1 << 1, // <a></a>
    NSXMLNodeCompactEmptyElement =  1 << 2, // <a/>
    NSXMLNodeUseSingleQuotes = 1 << 3,
    NSXMLNodeUseDoubleQuotes = 1 << 4,
    
    // Tidy
    NSXMLDocumentTidyHTML = 1 << 9,
    NSXMLDocumentTidyXML = 1 << 10,
    
    // Validate
    NSXMLDocumentValidate = 1 << 13,

    // Parse
    NSXMLDocumentXInclude = 1 << 16,
    
    // Output
    NSXMLNodePrettyPrint = 1 << 17,
    NSXMLDocumentIncludeContentTypeDeclaration = 1 << 18,
    
    // Fidelity
    NSXMLNodePreserveNamespaceOrder = 1 << 20,
    NSXMLNodePreserveAttributeOrder = 1 << 21,
    NSXMLNodePreserveEntities = 1 << 22,
    NSXMLNodePreservePrefixes = 1 << 23,
    NSXMLNodePreserveCDATA = 1 << 24,
    NSXMLNodePreserveWhitespace = 1 << 25,
    NSXMLNodePreserveDTD = 1 << 26,
    NSXMLNodePreserveCharacterReferences = 1 << 27,    
    NSXMLNodePreserveEmptyElements = 
            (NSXMLNodeExpandEmptyElement | NSXMLNodeCompactEmptyElement),
    NSXMLNodePreserveQuotes = 
            (NSXMLNodeUseSingleQuotes | NSXMLNodeUseDoubleQuotes),	
    NSXMLNodePreserveAll = (
            NSXMLNodePreserveNamespaceOrder | 
            NSXMLNodePreserveAttributeOrder | 
            NSXMLNodePreserveEntities | 
            NSXMLNodePreservePrefixes | 
            NSXMLNodePreserveCDATA | 
            NSXMLNodePreserveEmptyElements | 
            NSXMLNodePreserveQuotes | 
            NSXMLNodePreserveWhitespace |
            NSXMLNodePreserveDTD |
            NSXMLNodePreserveCharacterReferences |
            0xFFF00000) // high 12 bits
};

#endif		// Availability guard

