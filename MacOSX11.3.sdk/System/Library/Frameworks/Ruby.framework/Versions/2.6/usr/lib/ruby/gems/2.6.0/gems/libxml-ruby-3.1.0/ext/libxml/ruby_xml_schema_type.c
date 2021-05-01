#include "ruby_libxml.h"
#include "ruby_xml_schema_type.h"
#include "ruby_xml_schema_element.h"
#include "ruby_xml_schema_attribute.h"
#include "ruby_xml_schema_facet.h"

#define UNBOUNDED 1 << 30
#define FREE_AND_NULL(str) if ((str) != NULL) { xmlFree((xmlChar *) (str)); str = NULL; }

VALUE cXMLSchemaType;

static void rxml_schema_type_free(xmlSchemaTypePtr xschema_type)
{
  xschema_type = NULL;
  xmlFree(xschema_type);
}

VALUE rxml_wrap_schema_type(xmlSchemaTypePtr xtype)
{
  return Data_Wrap_Struct(cXMLSchemaType, NULL, rxml_schema_type_free, xtype);
}

static VALUE rxml_schema_type_namespace(VALUE self)
{
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  QNIL_OR_STRING(xtype->targetNamespace)
}

static VALUE rxml_schema_type_name(VALUE self)
{
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  QNIL_OR_STRING(xtype->name)
}

static VALUE rxml_schema_type_base(VALUE self)
{
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  return Data_Wrap_Struct(cXMLSchemaType, NULL, rxml_schema_type_free, xtype->baseType);
}

static VALUE rxml_schema_type_facets(VALUE self)
{
  xmlSchemaTypePtr xtype;
  xmlSchemaFacetPtr xfacet;
  VALUE result = rb_ary_new();
  VALUE facet;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  xfacet = xtype->facets;

  while (xfacet != NULL)
  {
    facet = rxml_wrap_schema_facet((xmlSchemaFacetPtr)xfacet);
    rb_ary_push(result, facet);
    xfacet = xfacet->next;
  }

  return result;
}

static VALUE rxml_schema_type_node(VALUE self)
{
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  if(xtype->node != NULL)
    return rxml_node_wrap(xtype->node);
  else
    return Qnil;
}

static VALUE rxml_schema_type_kind(VALUE self)
{
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  return INT2NUM(xtype->type);
}

static VALUE rxml_schema_type_annot(VALUE self)
{
  VALUE result = Qnil;
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  if(xtype != NULL && xtype->annot != NULL && xtype->annot->content != NULL)
  {
    xmlChar *content = xmlNodeGetContent(xtype->annot->content);
	if (content)
	{
	  result = rxml_new_cstr(content, NULL);
	  xmlFree(content);
    }
  }
  return result;
}

static void rxmlSchemaCollectElements(xmlSchemaParticlePtr xparticle, VALUE hash)
{
  VALUE element;
  xmlSchemaTreeItemPtr xterm;

  if (xparticle == NULL)
    return;

  xterm = xparticle->children;

  if (xterm != NULL)
  {
    switch (xterm->type)
	{
      case XML_SCHEMA_TYPE_ELEMENT:
        element = rxml_wrap_schema_element((xmlSchemaElementPtr)xterm);
        rb_iv_set(element, "@min", INT2NUM(xparticle->minOccurs));

        if (xparticle->maxOccurs >= UNBOUNDED)
          rb_iv_set(element, "@max", rb_const_get(rb_path2class("Float"), rb_intern("INFINITY")));
        else
          rb_iv_set(element, "@max", INT2NUM(xparticle->maxOccurs));

        if (xparticle->annot != NULL)
        {
          xmlChar *content = xmlNodeGetContent(xparticle->annot->content);

          if (content != NULL)
          {
            rb_iv_set(element, "@annotation", rb_str_new2((const char *) content));
            xmlFree(content);
          }
        }

        rb_hash_aset(hash, rb_str_new2((const char *) ((xmlSchemaElementPtr)xterm)->name), element);
        break;

      case XML_SCHEMA_TYPE_SEQUENCE:
        break;

      case XML_SCHEMA_TYPE_CHOICE:
        break;

      case XML_SCHEMA_TYPE_ALL:
        break;

      case XML_SCHEMA_TYPE_ANY:
        break;

      default:
        return;
    }
  }

  if (xterm &&
      ((xterm->type == XML_SCHEMA_TYPE_SEQUENCE) || (xterm->type == XML_SCHEMA_TYPE_CHOICE) || (xterm->type == XML_SCHEMA_TYPE_ALL)) &&
      (xterm->children != NULL))
  {
    rxmlSchemaCollectElements((xmlSchemaParticlePtr)xterm->children, hash);
  }

  if (xparticle->next != NULL)
  {
	rxmlSchemaCollectElements((xmlSchemaParticlePtr)xparticle->next, hash);
  }
}

static VALUE rxml_schema_type_elements(VALUE self)
{
  VALUE result = rb_hash_new();
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);
  rxmlSchemaCollectElements((xmlSchemaParticlePtr) xtype->subtypes, result);

  return result;
}

static VALUE rxml_schema_type_attributes(VALUE self)
{
  VALUE result = rb_ary_new();
  xmlSchemaTypePtr xtype;
  xmlSchemaAttributeUsePtr xuse;
  xmlSchemaItemListPtr xuses;
  int i;

  Data_Get_Struct(self, xmlSchemaType, xtype);
  xuses = xtype->attrUses;

  if (xuses != NULL)
  {
    for (i = 0; i < xuses->nbItems; i++)
	{
      xuse = (xmlSchemaAttributeUsePtr)xuses->items[i];
      rb_ary_push(result, rxml_wrap_schema_attribute(xuse));
    }
  }

  return result;
}

void rxml_init_schema_type(void)
{
  /* Add in infinity support for ruby 1.8.7 */
  #if !defined(RUBY_VM) && defined(INFINITY)
  ID infinityId = rb_intern("INFINITY");
  if (rb_const_defined(rb_cFloat, infinityId) == Qfalse)
    rb_define_const(rb_cFloat, "INFINITY", rb_float_new(INFINITY));
  #endif

  cXMLSchemaType = rb_define_class_under(cXMLSchema, "Type", rb_cObject);

  rb_define_method(cXMLSchemaType, "namespace", rxml_schema_type_namespace, 0);
  rb_define_method(cXMLSchemaType, "name", rxml_schema_type_name, 0);
  rb_define_method(cXMLSchemaType, "elements", rxml_schema_type_elements, 0);
  rb_define_method(cXMLSchemaType, "attributes", rxml_schema_type_attributes, 0);
  rb_define_method(cXMLSchemaType, "base", rxml_schema_type_base, 0);
  rb_define_method(cXMLSchemaType, "kind", rxml_schema_type_kind, 0);
  rb_define_method(cXMLSchemaType, "node", rxml_schema_type_node, 0);
  rb_define_method(cXMLSchemaType, "facets", rxml_schema_type_facets, 0);
  rb_define_method(cXMLSchemaType, "annotation", rxml_schema_type_annot, 0);
}
