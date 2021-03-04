/* Please see the LICENSE file for copyright and distribution information */

#include "ruby_libxml.h"
#include "ruby_xml_sax2_handler.h"


VALUE cbidOnCdataBlock;
VALUE cbidOnCharacters;
VALUE cbidOnComment;
VALUE cbidOnEndDocument;
VALUE cbidOnEndElement;
VALUE cbidOnEndElementNs;
VALUE cbidOnExternalSubset;
VALUE cbidOnHasExternalSubset;
VALUE cbidOnHasInternalSubset;
VALUE cbidOnInternalSubset;
VALUE cbidOnIsStandalone;
VALUE cbidOnError;
VALUE cbidOnProcessingInstruction;
VALUE cbidOnReference;
VALUE cbidOnStartElement;
VALUE cbidOnStartElementNs;
VALUE cbidOnStartDocument;

/* ======  Callbacks  =========== */
static void cdata_block_callback(void *ctx, const xmlChar *value, int len)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    rb_funcall(handler, cbidOnCdataBlock,1, rxml_new_cstr_len(value, len, NULL));
  }
}

static void characters_callback(void *ctx, const xmlChar *chars, int len)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    VALUE rchars = rxml_new_cstr_len(chars, len, NULL);
    rb_funcall(handler, cbidOnCharacters, 1, rchars);
  }
}

static void comment_callback(void *ctx, const xmlChar *msg)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    rb_funcall(handler, cbidOnComment, 1, rxml_new_cstr(msg, NULL));
  }
}

static void end_document_callback(void *ctx)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    rb_funcall(handler, cbidOnEndDocument, 0);
  }
}

static void end_element_ns_callback(void *ctx, const xmlChar *xlocalname, const xmlChar *xprefix, const xmlChar *xURI)
{
  VALUE handler = (VALUE) ctx;

  if (handler == Qnil)
    return;

  /* Call end element for old-times sake */
  if (rb_respond_to(handler, cbidOnEndElement))
  {
    VALUE name;
    if (xprefix)
    {
      name = rxml_new_cstr(xprefix, NULL);
      rb_str_cat2(name, ":"); 
      rb_str_cat2(name, (const char*)xlocalname);
    }
    else
    {
      name = rxml_new_cstr(xlocalname, NULL);
    }
    rb_funcall(handler, cbidOnEndElement, 1, name);
  }

  rb_funcall(handler, cbidOnEndElementNs, 3, 
             rxml_new_cstr(xlocalname, NULL),
             xprefix ? rxml_new_cstr(xprefix, NULL) : Qnil,
             xURI ? rxml_new_cstr(xURI, NULL) : Qnil);
}

static void external_subset_callback(void *ctx, const xmlChar *name, const xmlChar *extid, const xmlChar *sysid)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    VALUE rname = name ? rxml_new_cstr(name, NULL) : Qnil;
    VALUE rextid = extid ? rxml_new_cstr(extid, NULL) : Qnil;
    VALUE rsysid = sysid ? rxml_new_cstr(sysid, NULL) : Qnil;
    rb_funcall(handler, cbidOnExternalSubset, 3, rname, rextid, rsysid);
  }
}

static void has_external_subset_callback(void *ctx)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    rb_funcall(handler, cbidOnHasExternalSubset, 0);
  }
}

static void has_internal_subset_callback(void *ctx)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    rb_funcall(handler, cbidOnHasInternalSubset, 0);
  }
}

static void internal_subset_callback(void *ctx, const xmlChar *name, const xmlChar *extid, const xmlChar *sysid)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    VALUE rname = name ? rxml_new_cstr(name, NULL) : Qnil;
    VALUE rextid = extid ? rxml_new_cstr(extid, NULL) : Qnil;
    VALUE rsysid = sysid ? rxml_new_cstr(sysid, NULL) : Qnil;
    rb_funcall(handler, cbidOnInternalSubset, 3, rname, rextid, rsysid);
  }
}

static void is_standalone_callback(void *ctx)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    rb_funcall(handler, cbidOnIsStandalone,0);
  }
}

static void processing_instruction_callback(void *ctx, const xmlChar *target, const xmlChar *data)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    VALUE rtarget = target ? rxml_new_cstr(target, NULL) : Qnil;
    VALUE rdata = data ? rxml_new_cstr(data, NULL) : Qnil;
    rb_funcall(handler, cbidOnProcessingInstruction, 2, rtarget, rdata);
  }
}

static void reference_callback(void *ctx, const xmlChar *name)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    rb_funcall(handler, cbidOnReference, 1, rxml_new_cstr(name, NULL));
  }
}

static void start_document_callback(void *ctx)
{
  VALUE handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    rb_funcall(handler, cbidOnStartDocument, 0);
  }
}

static void start_element_ns_callback(void *ctx, 
                                      const xmlChar *xlocalname, const xmlChar *xprefix, const xmlChar *xURI,
                                		  int nb_namespaces, const xmlChar **xnamespaces,
					                            int nb_attributes, int nb_defaulted, const xmlChar **xattributes)
{
  VALUE handler = (VALUE) ctx;
  VALUE attributes = rb_hash_new();
  VALUE namespaces = rb_hash_new();

  if (handler == Qnil)
    return;

  if (xattributes)
  {
    /* Each attribute is an array of [localname, prefix, URI, value, end] */
    int i;
    for (i = 0;i < nb_attributes * 5; i+=5) 
    {
      VALUE attrName = rxml_new_cstr(xattributes[i+0], NULL);
      long attrLen = (long)(xattributes[i+4] - xattributes[i+3]);
      VALUE attrValue = rxml_new_cstr_len(xattributes[i+3], attrLen, NULL);
      rb_hash_aset(attributes, attrName, attrValue);
    }
  }

  if (xnamespaces)
  {
    int i;
    for (i = 0;i < nb_namespaces * 2; i+=2) 
    {
      VALUE nsPrefix = xnamespaces[i+0] ? rxml_new_cstr(xnamespaces[i+0], NULL) : Qnil;
      VALUE nsURI = xnamespaces[i+1] ? rxml_new_cstr(xnamespaces[i+1], NULL) : Qnil;
      rb_hash_aset(namespaces, nsPrefix, nsURI);
    }
  }

  /* Call start element for old-times sake */
  if (rb_respond_to(handler, cbidOnStartElement))
  {
    VALUE name;
    if (xprefix)
    {
      name = rxml_new_cstr(xprefix, NULL);
      rb_str_cat2(name, ":");
      rb_str_cat2(name, (const char*)xlocalname);
    }
    else
    {
      name = rxml_new_cstr(xlocalname, NULL);
    }
    rb_funcall(handler, cbidOnStartElement, 2, name, attributes);
  }

  rb_funcall(handler, cbidOnStartElementNs, 5, 
             rxml_new_cstr(xlocalname, NULL),
             attributes,
             xprefix ? rxml_new_cstr(xprefix, NULL) : Qnil,
             xURI ? rxml_new_cstr(xURI, NULL) : Qnil,
             namespaces);
}

static void structured_error_callback(void *ctx, xmlErrorPtr xerror)
{
  /* Older versions of Libxml will pass a NULL context from the sax parser.  Fixed on
     Feb 23, 2011.  See:

     http://git.gnome.org/browse/libxml2/commit/?id=241d4a1069e6bedd0ee2295d7b43858109c1c6d1 */

  VALUE handler;

  #if LIBXML_VERSION <= 20708
    xmlParserCtxtPtr ctxt = (xmlParserCtxt*)(xerror->ctxt);
    ctx = ctxt->userData;
  #endif

  handler = (VALUE) ctx;

  if (handler != Qnil)
  {
    VALUE error = rxml_error_wrap(xerror);
    rb_funcall(handler, cbidOnError, 1, error);
  }
}

/* ======  Handler  =========== */
xmlSAXHandler rxml_sax_handler = {
  (internalSubsetSAXFunc) internal_subset_callback,
  (isStandaloneSAXFunc) is_standalone_callback,
  (hasInternalSubsetSAXFunc) has_internal_subset_callback,
  (hasExternalSubsetSAXFunc) has_external_subset_callback,
  0, /* resolveEntity */
  0, /* getEntity */
  0, /* entityDecl */
  0, /* notationDecl */
  0, /* attributeDecl */
  0, /* elementDecl */
  0, /* unparsedEntityDecl */
  0, /* setDocumentLocator */
  (startDocumentSAXFunc) start_document_callback,
  (endDocumentSAXFunc) end_document_callback,
  0, /* Use start_element_ns_callback instead */
  0, /* Use end_element_ns_callback instead */
  (referenceSAXFunc) reference_callback,
  (charactersSAXFunc) characters_callback,
  0, /* ignorableWhitespace */
  (processingInstructionSAXFunc) processing_instruction_callback,
  (commentSAXFunc) comment_callback,
  0, /* xmlStructuredErrorFunc is used instead */
  0, /* xmlStructuredErrorFunc is used instead */
  0, /* xmlStructuredErrorFunc is used instead */
  0, /* xmlGetParameterEntity */
  (cdataBlockSAXFunc) cdata_block_callback,
  (externalSubsetSAXFunc) external_subset_callback,
  XML_SAX2_MAGIC, /* force SAX2 */
  0, /* _private */
  (startElementNsSAX2Func) start_element_ns_callback,
  (endElementNsSAX2Func) end_element_ns_callback,
  (xmlStructuredErrorFunc) structured_error_callback
};

void rxml_init_sax2_handler(void)
{

  /* SaxCallbacks */
  cbidOnCdataBlock =            rb_intern("on_cdata_block");
  cbidOnCharacters =            rb_intern("on_characters");
  cbidOnComment =               rb_intern("on_comment");
  cbidOnEndDocument =           rb_intern("on_end_document");
  cbidOnEndElement =            rb_intern("on_end_element");
  cbidOnEndElementNs =          rb_intern("on_end_element_ns");
  cbidOnError =                 rb_intern("on_error");
  cbidOnExternalSubset =        rb_intern("on_external_subset");
  cbidOnHasExternalSubset =     rb_intern("on_has_external_subset");
  cbidOnHasInternalSubset =     rb_intern("on_has_internal_subset");
  cbidOnInternalSubset =        rb_intern("on_internal_subset");
  cbidOnIsStandalone =          rb_intern("on_is_standalone");
  cbidOnProcessingInstruction = rb_intern("on_processing_instruction");
  cbidOnReference =             rb_intern("on_reference");
  cbidOnStartElement =          rb_intern("on_start_element");
  cbidOnStartElementNs =        rb_intern("on_start_element_ns");
  cbidOnStartDocument =         rb_intern("on_start_document");
}
