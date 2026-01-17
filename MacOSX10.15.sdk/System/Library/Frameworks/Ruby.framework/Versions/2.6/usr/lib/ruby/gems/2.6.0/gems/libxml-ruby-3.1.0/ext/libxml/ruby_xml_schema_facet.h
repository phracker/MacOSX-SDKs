#ifndef __RXML_SCHEMA_FACET__
#define __RXML_SCHEMA_FACET__

#include <libxml/schemasInternals.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>

extern VALUE cXMLSchemaFacet;

VALUE rxml_wrap_schema_facet(xmlSchemaFacetPtr facet);
void rxml_init_schema_facet(void);

#endif
