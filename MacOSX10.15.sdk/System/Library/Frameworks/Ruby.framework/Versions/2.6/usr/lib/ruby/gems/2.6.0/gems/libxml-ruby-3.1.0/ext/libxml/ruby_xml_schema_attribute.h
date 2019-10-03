#ifndef __RXML_SCHEMA_ATTRIBUTE__
#define __RXML_SCHEMA_ATTRIBUTE__

#include "ruby_xml_schema.h"
#include <libxml/schemasInternals.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>

extern VALUE cXMLSchemaAttribute;


void rxml_init_schema_attribute(void);
VALUE rxml_wrap_schema_attribute(xmlSchemaAttributeUsePtr attr);

#endif
