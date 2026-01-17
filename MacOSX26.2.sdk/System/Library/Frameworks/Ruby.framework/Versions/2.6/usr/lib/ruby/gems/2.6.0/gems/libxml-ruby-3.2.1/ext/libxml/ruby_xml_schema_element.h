#ifndef __RXML_SCHEMA_ELEMENT__
#define __RXML_SCHEMA_ELEMENT__

#include "ruby_xml_schema.h"
#include <libxml/schemasInternals.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>

extern VALUE cXMLSchemaElement;

VALUE rxml_wrap_schema_element(xmlSchemaElementPtr xelement);
void rxml_init_schema_element(void);

#endif
