#include "ruby_libxml.h"
#include "ruby_xml_schema_attribute.h"
#include "ruby_xml_schema_type.h"

VALUE cXMLSchemaAttribute;

static void rxml_schema_attribute_free(xmlSchemaAttributeUsePtr attr)
{
  attr = NULL;
  xmlFree(attr);
}

VALUE rxml_wrap_schema_attribute(xmlSchemaAttributeUsePtr attr)
{
  return Data_Wrap_Struct(cXMLSchemaAttribute, NULL, rxml_schema_attribute_free, attr);
}

static VALUE rxml_schema_attribute_namespace(VALUE self)
{
  xmlSchemaAttributeUsePtr attr;
  const xmlChar *tns;

  Data_Get_Struct(self, xmlSchemaAttributeUse, attr);

  if (attr == NULL)
    return Qnil;

  if (attr->type == XML_SCHEMA_EXTRA_ATTR_USE_PROHIB) {
      tns = ((xmlSchemaAttributeUseProhibPtr) attr)->targetNamespace;
  } else if (attr->type == XML_SCHEMA_EXTRA_QNAMEREF) {
      tns = ((xmlSchemaQNameRefPtr) attr)->targetNamespace;
  } else {
      tns = ((xmlSchemaAttributePtr) ((xmlSchemaAttributeUsePtr) (attr))->attrDecl)->targetNamespace;
  }

  QNIL_OR_STRING(tns)
}

static VALUE rxml_schema_attribute_name(VALUE self)
{
  xmlSchemaAttributeUsePtr attr;
  const xmlChar *name;

  Data_Get_Struct(self, xmlSchemaAttributeUse, attr);

  if (attr == NULL)
    return Qnil;

  if (attr->type == XML_SCHEMA_EXTRA_ATTR_USE_PROHIB) {
      name = ((xmlSchemaAttributeUseProhibPtr) attr)->name;
  } else if (attr->type == XML_SCHEMA_EXTRA_QNAMEREF) {
      name = ((xmlSchemaQNameRefPtr) attr)->name;
  } else {
      xmlSchemaAttributePtr attrDecl = ((xmlSchemaAttributeUsePtr) attr)->attrDecl;
      name = attrDecl->name;
  }

  QNIL_OR_STRING(name)
}

static VALUE rxml_schema_attribute_type(VALUE self)
{
  xmlSchemaAttributeUsePtr attr;
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaAttributeUse, attr);

  xtype = attr->attrDecl->subtypes;

  return rxml_wrap_schema_type((xmlSchemaTypePtr) xtype);
}

static VALUE rxml_schema_attribute_node(VALUE self)
{
  xmlSchemaAttributeUsePtr attr;

  Data_Get_Struct(self, xmlSchemaAttributeUse, attr);

  return rxml_node_wrap(attr->node);
}

static VALUE rxml_schema_attribute_value(VALUE self)
{
  xmlSchemaAttributeUsePtr attr;

  Data_Get_Struct(self, xmlSchemaAttributeUse, attr);

  QNIL_OR_STRING(attr->defValue)
}

static VALUE rxml_schema_attribute_occurs(VALUE self)
{
  xmlSchemaAttributeUsePtr attr;

  Data_Get_Struct(self, xmlSchemaAttributeUse, attr);

  return INT2NUM(attr->occurs);
}

void rxml_init_schema_attribute(void)
{
  cXMLSchemaAttribute = rb_define_class_under(cXMLSchema, "Attribute", rb_cObject);
  rb_define_method(cXMLSchemaAttribute, "namespace", rxml_schema_attribute_namespace, 0);
  rb_define_method(cXMLSchemaAttribute, "name", rxml_schema_attribute_name, 0);
  rb_define_method(cXMLSchemaAttribute, "type", rxml_schema_attribute_type, 0);
  rb_define_method(cXMLSchemaAttribute, "node", rxml_schema_attribute_node, 0);
  rb_define_method(cXMLSchemaAttribute, "value", rxml_schema_attribute_value, 0);
  rb_define_method(cXMLSchemaAttribute, "occurs", rxml_schema_attribute_occurs, 0);
}
