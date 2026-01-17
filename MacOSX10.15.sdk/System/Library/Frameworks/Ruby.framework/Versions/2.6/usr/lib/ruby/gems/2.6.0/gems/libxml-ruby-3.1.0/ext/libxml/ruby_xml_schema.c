#include "ruby_libxml.h"
#define LIBXML_OUTPUT_ENABLED
#define DUMP_CONTENT_MODEL
#include "ruby_xml_schema.h"

#include "ruby_xml_schema_type.h"
#include "ruby_xml_schema_element.h"
#include "ruby_xml_schema_attribute.h"
#include "ruby_xml_schema_facet.h"

/*
 * Document-class: LibXML::XML::Schema
 *
 * The XML::Schema class is used to prepare XML Schemas for validation of xml
 * documents.
 *
 * Schemas can be created from XML documents, strinings or URIs using the
 * corresponding methods (new for URIs).
 *
 * Once a schema is prepared, an XML document can be validated by the
 * XML::Document#validate_schema method providing the XML::Schema object
 * as parameter. The method return true if the document validates, false
 * otherwise.
 *
 * Basic usage:
 *
 *  # parse schema as xml document
 *  schema_document = XML::Document.file('schema.rng')
 *
 *  # prepare schema for validation
 *  schema = XML::Schema.document(schema_document)
 *
 *  # parse xml document to be validated
 *  instance = XML::Document.file('instance.xml')
 *
 *  # validate
 *  instance.validate_schema(schema)
 */

VALUE cXMLSchema;

static void rxml_schema_free(xmlSchemaPtr xschema)
{
  xmlSchemaFree(xschema);
}

VALUE rxml_wrap_schema(xmlSchemaPtr xschema)
{
  return Data_Wrap_Struct(cXMLSchema, NULL, rxml_schema_free, xschema);
}


/*
 * call-seq:
 *    XML::Schema.initialize(schema_uri) -> schema
 *
 * Create a new schema from the specified URI.
 */
static VALUE rxml_schema_init_from_uri(VALUE class, VALUE uri)
{
  xmlSchemaParserCtxtPtr xparser;
  xmlSchemaPtr xschema;

  Check_Type(uri, T_STRING);

  xparser = xmlSchemaNewParserCtxt(StringValuePtr(uri));
  xschema = xmlSchemaParse(xparser);
  xmlSchemaFreeParserCtxt(xparser);

  return Data_Wrap_Struct(cXMLSchema, NULL, rxml_schema_free, xschema);
}

/*
 * call-seq:
 *    XML::Schema.document(document) -> schema
 *
 * Create a new schema from the specified document.
 */
static VALUE rxml_schema_init_from_document(VALUE class, VALUE document)
{
  xmlDocPtr xdoc;
  xmlSchemaPtr xschema;
  xmlSchemaParserCtxtPtr xparser;

  Data_Get_Struct(document, xmlDoc, xdoc);

  xparser = xmlSchemaNewDocParserCtxt(xdoc);
  xschema = xmlSchemaParse(xparser);
  xmlSchemaFreeParserCtxt(xparser);

  if (xschema == NULL)
    return Qnil;

  return Data_Wrap_Struct(cXMLSchema, NULL, rxml_schema_free, xschema);
}

/*
 * call-seq:
 *    XML::Schema.from_string("schema_data") -> "value"
 *
 * Create a new schema using the specified string.
 */
static VALUE rxml_schema_init_from_string(VALUE self, VALUE schema_str)
{
  xmlSchemaParserCtxtPtr xparser;
  xmlSchemaPtr xschema;

  Check_Type(schema_str, T_STRING);

  xparser = xmlSchemaNewMemParserCtxt(StringValuePtr(schema_str), (int)strlen(StringValuePtr(schema_str)));
  xschema = xmlSchemaParse(xparser);
  xmlSchemaFreeParserCtxt(xparser);

  return Data_Wrap_Struct(cXMLSchema, NULL, rxml_schema_free, xschema);
}


static VALUE rxml_schema_target_namespace(VALUE self)
{
  xmlSchemaPtr xschema;

  Data_Get_Struct(self, xmlSchema, xschema);

  QNIL_OR_STRING(xschema->targetNamespace)
}

static VALUE rxml_schema_name(VALUE self)
{
  xmlSchemaPtr xschema;

  Data_Get_Struct(self, xmlSchema, xschema);

  QNIL_OR_STRING(xschema->name)
}

static VALUE rxml_schema_version(VALUE self)
{
  xmlSchemaPtr xschema;

  Data_Get_Struct(self, xmlSchema, xschema);

  QNIL_OR_STRING(xschema->version)
}

static VALUE rxml_schema_id(VALUE self)
{
  xmlSchemaPtr xschema;

  Data_Get_Struct(self, xmlSchema, xschema);

  QNIL_OR_STRING(xschema->id)
}

static VALUE rxml_schema_document(VALUE self)
{
  xmlSchemaPtr xschema;

  Data_Get_Struct(self, xmlSchema, xschema);

  return rxml_node_wrap(xmlDocGetRootElement(xschema->doc));
}

static void scan_namespaces(xmlSchemaImportPtr ximport, VALUE array, xmlChar *nsname)
{
  xmlNodePtr xnode;
  xmlNsPtr xns;

  if (ximport->doc)
  {
    xnode = xmlDocGetRootElement(ximport->doc);
    xns = xnode->nsDef;

    while (xns)
	{
      VALUE namespace = rxml_namespace_wrap(xns);
      rb_ary_push(array, namespace);
      xns = xns->next;
    }
  }
}

static VALUE rxml_schema_namespaces(VALUE self)
{
  VALUE result;
  xmlSchemaPtr xschema;

  Data_Get_Struct(self, xmlSchema, xschema);

  result = rb_ary_new();
  xmlHashScan(xschema->schemasImports, (xmlHashScanner)scan_namespaces, (void *)result);

  return result;
}

static void scan_element(xmlSchemaElementPtr xelement, VALUE hash, xmlChar *name)
{
  VALUE element = rxml_wrap_schema_element(xelement);
  rb_hash_aset(hash, rb_str_new2((const char*)name), element);
}

static VALUE rxml_schema_elements(VALUE self)
{
  VALUE result = rb_hash_new();
  xmlSchemaPtr xschema;

  Data_Get_Struct(self, xmlSchema, xschema);
  xmlHashScan(xschema->elemDecl, (xmlHashScanner)scan_element, (void *)result);

  return result;
}

static void scan_type(xmlSchemaTypePtr xtype, VALUE hash, xmlChar *name)
{
	VALUE type = rxml_wrap_schema_type(xtype);
	rb_hash_aset(hash, rb_str_new2((const char*)name), type);
}

static VALUE rxml_schema_types(VALUE self)
{
	VALUE result = rb_hash_new();
	xmlSchemaPtr xschema;

	Data_Get_Struct(self, xmlSchema, xschema);

	if (xschema != NULL && xschema->typeDecl != NULL)
	{
		xmlHashScan(xschema->typeDecl, (xmlHashScanner)scan_type, (void *)result);
	}

	return result;
}

static void collect_imported_types(xmlSchemaImportPtr import, VALUE result)
{
  if (import->imported && import->schema)
  {
    xmlHashScan(import->schema->typeDecl, (xmlHashScanner)scan_type, (void *)result);
  }
}

static VALUE rxml_schema_imported_types(VALUE self)
{
  xmlSchemaPtr xschema;
  VALUE result = rb_hash_new();

  Data_Get_Struct(self, xmlSchema, xschema);

  if (xschema)
  {
	  xmlHashScan(xschema->schemasImports, (xmlHashScanner)collect_imported_types, (void *)result);
  }

  return result;
}

void rxml_init_schema(void)
{
  cXMLSchema = rb_define_class_under(mXML, "Schema", rb_cObject);
  rb_define_singleton_method(cXMLSchema, "new", rxml_schema_init_from_uri, 1);
  rb_define_singleton_method(cXMLSchema, "from_string", rxml_schema_init_from_string, 1);
  rb_define_singleton_method(cXMLSchema, "document", rxml_schema_init_from_document, 1);

  rb_define_method(cXMLSchema, "target_namespace", rxml_schema_target_namespace, 0);
  rb_define_method(cXMLSchema, "name", rxml_schema_name, 0);
  rb_define_method(cXMLSchema, "id", rxml_schema_id, 0);
  rb_define_method(cXMLSchema, "version", rxml_schema_version, 0);
  rb_define_method(cXMLSchema, "document", rxml_schema_document, 0);

  rb_define_method(cXMLSchema, "elements", rxml_schema_elements, 0);
  rb_define_method(cXMLSchema, "imported_types", rxml_schema_imported_types, 0);
  rb_define_method(cXMLSchema, "namespaces", rxml_schema_namespaces, 0);
  rb_define_method(cXMLSchema, "types", rxml_schema_types, 0);

  rxml_init_schema_facet();
  rxml_init_schema_element();
  rxml_init_schema_attribute();
  rxml_init_schema_type();
}
