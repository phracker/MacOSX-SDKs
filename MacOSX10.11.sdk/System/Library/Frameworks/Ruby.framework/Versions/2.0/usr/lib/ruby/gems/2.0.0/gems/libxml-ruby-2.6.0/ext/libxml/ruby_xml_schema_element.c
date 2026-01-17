#include "ruby_libxml.h"
#include "ruby_xml_schema_element.h"
#include "ruby_xml_schema_type.h"

VALUE cXMLSchemaElement;

static void rxml_schema_element_free(xmlSchemaElementPtr xschema_element)
{
  xschema_element = NULL;
  xmlFree(xschema_element);
}

VALUE rxml_wrap_schema_element(xmlSchemaElementPtr xelement)
{
  return Data_Wrap_Struct(cXMLSchemaElement, NULL, rxml_schema_element_free, xelement);
}

static VALUE rxml_schema_element_namespace(VALUE self)
{
  xmlSchemaElementPtr xelem;

  Data_Get_Struct(self, xmlSchemaElement, xelem);

  QNIL_OR_STRING(xelem->targetNamespace)
}

static VALUE rxml_schema_element_name(VALUE self)
{
  xmlSchemaElementPtr xelem;

  Data_Get_Struct(self, xmlSchemaElement, xelem);


  QNIL_OR_STRING(xelem->name)
}

static VALUE rxml_schema_element_type(VALUE self)
{
  xmlSchemaElementPtr xelem;
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaElement, xelem);

  xtype = xelem->subtypes;

  return rxml_wrap_schema_type((xmlSchemaTypePtr) xtype);
}

static VALUE rxml_schema_element_node(VALUE self)
{
  xmlSchemaElementPtr xelem;

  Data_Get_Struct(self, xmlSchemaElement, xelem);

  return rxml_node_wrap(xelem->node);
}

static VALUE rxml_schema_element_value(VALUE self)
{
  xmlSchemaElementPtr xelem;

  Data_Get_Struct(self, xmlSchemaElement, xelem);

  QNIL_OR_STRING(xelem->value)
}

static VALUE rxml_schema_element_min_occurs(VALUE self)
{
  return rb_iv_get(self, "@min");
}

static VALUE rxml_schema_element_max_occurs(VALUE self)
{
  return rb_iv_get(self, "@max");
}

static VALUE rxml_schema_element_annot(VALUE self)
{
  return rb_iv_get(self, "@annotation");
}


void rxml_init_schema_element(void)
{
  cXMLSchemaElement = rb_define_class_under(cXMLSchema, "Element", rb_cObject);
  rb_define_method(cXMLSchemaElement, "namespace", rxml_schema_element_namespace, 0);
  rb_define_method(cXMLSchemaElement, "name", rxml_schema_element_name, 0);
  rb_define_method(cXMLSchemaElement, "type", rxml_schema_element_type, 0);
  rb_define_method(cXMLSchemaElement, "node", rxml_schema_element_node, 0);
  rb_define_method(cXMLSchemaElement, "value", rxml_schema_element_value, 0);
  rb_define_method(cXMLSchemaElement, "min_occurs", rxml_schema_element_min_occurs, 0);
  rb_define_method(cXMLSchemaElement, "max_occurs", rxml_schema_element_max_occurs, 0);
  rb_define_method(cXMLSchemaElement, "annotation", rxml_schema_element_annot, 0);
}
