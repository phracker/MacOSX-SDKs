/*
 * xmlreader.h : Interfaces, constants and types of the XML streaming API.
 *
 * See Copyright for the status of this software.
 *
 * daniel@veillard.com
 */

#ifndef __XML_XMLREADER_H__
#define __XML_XMLREADER_H__

#include <libxml/tree.h>
#include <libxml/xmlIO.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    XML_PARSER_LOADDTD = 1,
    XML_PARSER_DEFAULTATTRS = 2,
    XML_PARSER_VALIDATE = 3,
    XML_PARSER_SUBST_ENTITIES = 4
} xmlParserProperties;

typedef enum {
    XML_PARSER_SEVERITY_VALIDITY_WARNING = 1,
    XML_PARSER_SEVERITY_VALIDITY_ERROR = 2,
    XML_PARSER_SEVERITY_WARNING = 3,
    XML_PARSER_SEVERITY_ERROR = 4
} xmlParserSeverities;

typedef struct _xmlTextReader xmlTextReader;
typedef xmlTextReader *xmlTextReaderPtr;

/*
 * Constructors & Destructor
 */
xmlTextReaderPtr	xmlNewTextReader	(xmlParserInputBufferPtr input,
	                                         const char *URI);
xmlTextReaderPtr	xmlNewTextReaderFilename(const char *URI);
void			xmlFreeTextReader	(xmlTextReaderPtr reader);

/*
 * Iterators
 */
int		xmlTextReaderRead	(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderReadInnerXml	(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderReadOuterXml	(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderReadString		(xmlTextReaderPtr reader);
int		xmlTextReaderReadAttributeValue	(xmlTextReaderPtr reader);

/*
 * Attributes of the node
 */
int		xmlTextReaderAttributeCount(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderBaseUri	(xmlTextReaderPtr reader);
int		xmlTextReaderDepth	(xmlTextReaderPtr reader);
int		xmlTextReaderHasAttributes(xmlTextReaderPtr reader);
int		xmlTextReaderHasValue(xmlTextReaderPtr reader);
int		xmlTextReaderIsDefault	(xmlTextReaderPtr reader);
int		xmlTextReaderIsEmptyElement(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderLocalName	(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderName	(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderNamespaceUri(xmlTextReaderPtr reader);
int		xmlTextReaderNodeType	(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderPrefix	(xmlTextReaderPtr reader);
int		xmlTextReaderQuoteChar	(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderValue	(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderXmlLang	(xmlTextReaderPtr reader);
int		xmlTextReaderReadState	(xmlTextReaderPtr reader);

/*
 * Methods of the XmlTextReader
 */
int		xmlTextReaderClose		(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderGetAttributeNo	(xmlTextReaderPtr reader,
						 int no);
xmlChar *	xmlTextReaderGetAttribute	(xmlTextReaderPtr reader,
						 const xmlChar *name);
xmlChar *	xmlTextReaderGetAttributeNs	(xmlTextReaderPtr reader,
						 const xmlChar *localName,
						 const xmlChar *namespaceURI);
xmlParserInputBufferPtr xmlTextReaderGetRemainder(xmlTextReaderPtr reader);
xmlChar *	xmlTextReaderLookupNamespace	(xmlTextReaderPtr reader,
						 const xmlChar *prefix);
int		xmlTextReaderMoveToAttributeNo	(xmlTextReaderPtr reader,
						 int no);
int		xmlTextReaderMoveToAttribute	(xmlTextReaderPtr reader,
						 const xmlChar *name);
int		xmlTextReaderMoveToAttributeNs	(xmlTextReaderPtr reader,
						 const xmlChar *localName,
						 const xmlChar *namespaceURI);
int		xmlTextReaderMoveToFirstAttribute(xmlTextReaderPtr reader);
int		xmlTextReaderMoveToNextAttribute(xmlTextReaderPtr reader);
int		xmlTextReaderMoveToElement	(xmlTextReaderPtr reader);
int		xmlTextReaderNormalization	(xmlTextReaderPtr reader);

/*
 * Extensions
 */
int		xmlTextReaderSetParserProp	(xmlTextReaderPtr reader,
						 int prop,
						 int value);
int		xmlTextReaderGetParserProp	(xmlTextReaderPtr reader,
						 int prop);
xmlNodePtr	xmlTextReaderCurrentNode	(xmlTextReaderPtr reader);
xmlDocPtr	xmlTextReaderCurrentDoc		(xmlTextReaderPtr reader);

/*
 * Error handling extensions
 */
typedef void *  xmlTextReaderLocatorPtr;
typedef void   (*xmlTextReaderErrorFunc)        (void *arg, 
						 const char *msg,
						 xmlParserSeverities severity,
						 xmlTextReaderLocatorPtr locator);
int             xmlTextReaderLocatorLineNumber  (xmlTextReaderLocatorPtr locator);
/*int             xmlTextReaderLocatorLinePosition(xmlTextReaderLocatorPtr locator);*/
xmlChar *       xmlTextReaderLocatorBaseURI     (xmlTextReaderLocatorPtr locator);
void            xmlTextReaderSetErrorHandler    (xmlTextReaderPtr reader, 
						 xmlTextReaderErrorFunc f, 
						 void *arg);
void            xmlTextReaderGetErrorHandler    (xmlTextReaderPtr reader, 
						 xmlTextReaderErrorFunc *f, 
						 void **arg);

#ifdef __cplusplus
}
#endif
#endif /* __XML_XMLREADER_H__ */

