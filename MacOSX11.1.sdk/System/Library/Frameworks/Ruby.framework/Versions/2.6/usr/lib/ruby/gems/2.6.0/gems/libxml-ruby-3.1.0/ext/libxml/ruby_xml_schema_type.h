#ifndef __RXML_SCHEMA_TYPE__
#define __RXML_SCHEMA_TYPE__

extern VALUE cXMLSchemaType;

VALUE rxml_wrap_schema_type(xmlSchemaTypePtr xtype);
void rxml_init_schema_type(void);

#endif
