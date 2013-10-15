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
  xmlSchemaFacetPtr facet;
  VALUE facets;
  VALUE rfacet;

  facets = rb_iv_get(self, "@facets");

  if (facets == Qnil) {
    facets = rb_ary_new();
    Data_Get_Struct(self, xmlSchemaType, xtype);

    facet = xtype->facets;

    while (facet != NULL) {
      rfacet = rxml_wrap_schema_facet((xmlSchemaFacetPtr) facet);
      rb_ary_push(facets, rfacet);
      facet = facet->next;
    }

    rb_iv_set(self, "@facets", facets);
  }

  return facets;
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

static VALUE get_annotation(xmlSchemaAnnotPtr annot)
{
  if(annot != NULL && annot->content != NULL && annot->content->content != NULL)
    return rb_str_new2((const char *) annot->content->content);
  else
    return Qnil;
}

static VALUE rxml_schema_type_annot(VALUE self)
{
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  if(xtype != NULL && xtype->annot != NULL)
    return get_annotation(xtype->annot);
  else
    return Qnil;
}

static void rxmlSchemaCollectElements(xmlSchemaParticlePtr particle, VALUE self)
{
  VALUE elements;
  VALUE relement;
  xmlSchemaTreeItemPtr term;

  if (particle == NULL)
    return;

  term = particle->children;

  if (term != NULL) {
    elements = rb_iv_get(self, "@elements");

    switch (term->type) {
      case XML_SCHEMA_TYPE_ELEMENT:
        relement = rxml_wrap_schema_element((xmlSchemaElementPtr) term);


        rb_iv_set(relement, "@min", INT2NUM(particle->minOccurs));

        if (particle->maxOccurs >= UNBOUNDED)
          rb_iv_set(relement, "@max", rb_const_get(rb_path2class("Float"), rb_intern("INFINITY")));
        else
          rb_iv_set(relement, "@max", INT2NUM(particle->maxOccurs));

        if (particle->annot != NULL)
        {
          xmlChar *content;

          content = xmlNodeGetContent(particle->annot->content);

          if (content != NULL)
          {
            rb_iv_set(relement, "@annotation", rb_str_new2((const char *) content));
            xmlFree(content);
          }
        }

        rb_hash_aset(elements, rb_str_new2((const char *) ((xmlSchemaElementPtr) term)->name), relement);

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

  if (term &&
      ((term->type == XML_SCHEMA_TYPE_SEQUENCE) ||
          (term->type == XML_SCHEMA_TYPE_CHOICE) ||
          (term->type == XML_SCHEMA_TYPE_ALL)) &&
      (term->children != NULL)) {

    rxmlSchemaCollectElements((xmlSchemaParticlePtr) term->children, self);
  }

  if (particle->next != NULL)
    rxmlSchemaCollectElements((xmlSchemaParticlePtr) particle->next, self);
}

static VALUE
rxml_schema_type_elements(VALUE self)
{
  VALUE elements;
  xmlSchemaTypePtr xtype;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  if (rb_iv_get(self, "@elements") == Qnil) {
    elements = rb_hash_new();
    rb_iv_set(self, "@elements", elements);
    rxmlSchemaCollectElements((xmlSchemaParticlePtr) xtype->subtypes, self);
  }

  return rb_iv_get(self, "@elements");
}

static VALUE
rxml_schema_type_attributes(VALUE self)
{
  VALUE attributes;
  xmlSchemaTypePtr xtype;
  xmlSchemaAttributeUsePtr use;
  xmlSchemaItemListPtr uses;
  int i;

  Data_Get_Struct(self, xmlSchemaType, xtype);

  if (rb_iv_get(self, "@attributes") == Qnil) {
    attributes = rb_ary_new();
    rb_iv_set(self, "@attributes", attributes);

    uses = xtype->attrUses;

    if ((uses == NULL) || (uses->nbItems == 0))
      return rb_iv_get(self, "@attributes");

    for (i = 0; i < uses->nbItems; i++) {
      use = (xmlSchemaAttributeUsePtr) uses->items[i];
      rb_ary_push(attributes, rxml_wrap_schema_attribute(use));
    }
  }

  return rb_iv_get(self, "@attributes");
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
