/*
 * Document-class: LibXML::XML::Document
 *
 * The XML::Document class provides a tree based API for working
 * with xml documents.  You may directly create a document and
 * manipulate it, or create a document from a data source by
 * using an XML::Parser object.
 *
 * To read a document from a file:
 *
 *   doc = XML::Document.file('my_file')
 *
 * To use a parser to read a document:
 *
 *   parser = XML::Parser.file('my_file')
 *   doc = parser.parse
 *
 * To create a document from scratch:
 *
 *  doc = XML::Document.new()
 *  doc.root = XML::Node.new('root_node')
 *  doc.root << XML::Node.new('elem1')
 *  doc.save(filename, :indent => true, :encoding => XML::Encoding::UTF_8)
 *
 * To write a document to a file:
 *
 *  doc = XML::Document.new()
 *  doc.root = XML::Node.new('root_node')
 *  root = doc.root
 *
 *  root << elem1 = XML::Node.new('elem1')
 *  elem1['attr1'] = 'val1'
 *  elem1['attr2'] = 'val2'
 *
 *  root << elem2 = XML::Node.new('elem2')
 *  elem2['attr1'] = 'val1'
 *  elem2['attr2'] = 'val2'
 *
 *  root << elem3 = XML::Node.new('elem3')
 *  elem3 << elem4 = XML::Node.new('elem4')
 *  elem3 << elem5 = XML::Node.new('elem5')
 *
 *  elem5 << elem6 = XML::Node.new('elem6')
 *  elem6 << 'Content for element 6'
 *
 *  elem3['attr'] = 'baz'
 *
 *  doc.save(filename, :indent => true, :encoding => XML::Encoding::UTF_8)
 */

#include <stdarg.h>
#include "ruby_libxml.h"
#include "ruby_xml_document.h"

VALUE cXMLDocument;

void rxml_document_free(xmlDocPtr xdoc)
{
  xdoc->_private = NULL;
  xmlFreeDoc(xdoc);
}

VALUE rxml_document_wrap(xmlDocPtr xdoc)
{
  VALUE result = Qnil;

  // Is this node is already wrapped?
  if (xdoc->_private != NULL)
  {
    result = (VALUE)xdoc->_private;
  }
  else
  {
    result = Data_Wrap_Struct(cXMLDocument, NULL, rxml_document_free, xdoc);
    xdoc->_private = (void*)result;
  }

  return result;
}

/*
 * call-seq:
 *    XML::Document.alloc(xml_version = 1.0) -> document
 *
 * Alocates a new XML::Document, optionally specifying the
 * XML version.
 */
static VALUE rxml_document_alloc(VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, rxml_document_free, NULL);
}

/*
 * call-seq:
 *    XML::Document.initialize(xml_version = 1.0) -> document
 *
 * Initializes a new XML::Document, optionally specifying the
 * XML version.
 */
static VALUE rxml_document_initialize(int argc, VALUE *argv, VALUE self)
{
  xmlDocPtr xdoc;
  VALUE xmlver;

  switch (argc)
  {
  case 0:
    xmlver = rb_str_new2("1.0");
    break;
  case 1:
    rb_scan_args(argc, argv, "01", &xmlver);
    break;
  default:
    rb_raise(rb_eArgError, "wrong number of arguments (need 0 or 1)");
  }

  Check_Type(xmlver, T_STRING);
  xdoc = xmlNewDoc((xmlChar*) StringValuePtr(xmlver));

  // Link the ruby object to the document and the document to the ruby object
  RDATA(self)->data = xdoc;
  xdoc->_private = (void*)self;

  return self;
}

/* XML_C14N_1* constants are not defined until libxml 1.1.25, so if they
   are not defined then define these constants to map to zero,
   the same value as XML_C14N_1_0. */

/* XML_C14N* constants are not defined until libxml 1.1.25, so define them
   if needed so things compile. */
#ifndef XML_C14N_1_0
#define XML_C14N_1_0 0
#define XML_C14N_EXCLUSIVE_1_0 XML_C14N_1_0
#define XML_C14N_1_1 XML_C14N_1_0
#endif

/*
  * :call-seq:
  *   document.canonicalize -> String
  *   document.canonicalize(options) -> String
  *
  * Returns a string containing the canonicalized form of the document.
  * Implemented to include all of the functionality of the libxml2
  * {xmlC14NDocDumpMemory}[http://xmlsoft.org/html/libxml-c14n.html#xmlC14NDocDumpMemory]
  * method.
  *
  * === Options
  * [comments]
  *   * *Type:* Boolean
  *   * *Default:* false
  *   Specifies if comments should be output.
  *   * Must be boolean, otherwise defaults to false.
  * [inclusive_ns_prefixes]
  *   * *Type:* Array of strings
  *   * *Default:* empty array
  *   Array of namespace prefixes to include in exclusive canonicalization only.
  *   * The last item in the list is reserved for a NULL value because the C method demands it, therefore
  *     up to the first 255 valid entries will be used.
  *   * <em>Only used for *XML_C14N_EXCLUSIVE_1_0* mode. Ignored otherwise.</em>
  * [mode]
  *   * *Type:* XML::Document Constant
  *   * *Default:* XML_C14N_1_0
  *   Specifies the mode of canonicalization.
  *   * *NOTE:* XML_C14N_1_1 may not be fully implemented upon compilation due to C library compatibility.
  *     Please check if XML_C14N_1_0 and XML_C14N_1_1 are the same value prior to using XML_C14N_1_1.
  * [nodes]
  *   * *Type:* Array of XML::Node objects
  *   * *Default:* empty array
  *   XML::Nodes to include in the canonicalization process
  *   * For large lists of more than 256 valid namespaces, up to the first 256 valid entries will be used.
  */
#define C14N_NS_LIMIT 256
#define C14N_NODESET_LIMIT 256

static VALUE
rxml_document_canonicalize(int argc, VALUE *argv, VALUE self)
{
  VALUE result = Qnil;
  xmlDocPtr xdoc;
  xmlChar *buffer = NULL;
  VALUE option_hash = Qnil;
  VALUE o_nodes = Qnil;

  // :comments option
  int comments = 0;
  // :mode option
  int c14n_mode = XML_C14N_1_0;
  // :inclusive_ns_prefixes option (ARRAY)

  xmlChar * inc_ns_prefixes_ptr[C14N_NS_LIMIT];

  // :nodes option (ARRAY)
  xmlNodePtr  node_ptr_array[C14N_NODESET_LIMIT];
  xmlNodeSet nodeset = {
    0, C14N_NODESET_LIMIT, NULL
  };

  /* At least one NULL value must be defined in the array or the extension will
   * segfault when using XML_C14N_EXCLUSIVE_1_0 mode.
   * API docs: "list of inclusive namespace prefixes ended with a NULL"
   */
  inc_ns_prefixes_ptr[0] = NULL;

  rb_scan_args(argc, argv, "01", &option_hash);
  // Do stuff if ruby hash passed as argument
  if (!NIL_P(option_hash)) 
  {
	VALUE o_comments = Qnil;
	VALUE o_mode = Qnil;
	VALUE o_i_ns_prefixes = Qnil;
		
    Check_Type(option_hash, T_HASH);

    o_comments = rb_hash_aref(option_hash, ID2SYM(rb_intern("comments")));
    comments = (RTEST(o_comments) ? 1 : 0);

    o_mode = rb_hash_aref(option_hash, ID2SYM(rb_intern("mode")));
    if (!NIL_P(o_mode)) 
	{
      Check_Type(o_mode, T_FIXNUM);
      c14n_mode = NUM2INT(o_mode);
      //TODO: clean this up
      //if (c14n_mode > 2) { c14n_mode = 0; }
      //mode_int = (NUM2INT(o_mode) > 2 ? 0 : NUM2INT(o_mode));
    }

    o_i_ns_prefixes = rb_hash_aref(option_hash, ID2SYM(rb_intern("inclusive_ns_prefixes")));
    if (!NIL_P(o_i_ns_prefixes)) 
	{
      int i;
      int p = 0; //pointer array index
      VALUE *list_in = NULL;
      long list_size = 0;

	  Check_Type(o_i_ns_prefixes, T_ARRAY);
      list_in = RARRAY_PTR(o_i_ns_prefixes);
      list_size = RARRAY_LEN(o_i_ns_prefixes);

      if (list_size > 0) 
	  {
        for(i=0; i < list_size; ++i) {
          if (p >= C14N_NS_LIMIT) { break; }

          if (RTEST(list_in[i])) 
		  {
            if (TYPE(list_in[i]) == T_STRING) 
			{
              inc_ns_prefixes_ptr[p] = (xmlChar *)StringValueCStr(list_in[i]);
              p++;
            }
          }
        }
      }

      // ensure p is not out of bound
      p = (p >= C14N_NS_LIMIT ? (C14N_NS_LIMIT-1) : p);

      // API docs: "list of inclusive namespace prefixes ended with a NULL"
      // Set last element to NULL
      inc_ns_prefixes_ptr[p] = NULL;
    }
    //o_ns_prefixes will free at end of block

    o_nodes = rb_hash_aref(option_hash, ID2SYM(rb_intern("nodes")));
    if (!NIL_P(o_nodes)) 
	{
      int i;
      int p = 0; // index of pointer array
      VALUE * list_in = NULL;
      long node_list_size = 0;

	  if (CLASS_OF(o_nodes) == cXMLXPathObject)
	  {
		  o_nodes = rb_funcall(o_nodes, rb_intern("to_a"), 0);
	  }
	  else
	  {
		  Check_Type(o_nodes, T_ARRAY);
	  }
      list_in = RARRAY_PTR(o_nodes);
      node_list_size = RARRAY_LEN(o_nodes);

      for (i=0; i < node_list_size; ++i)
	  {
        if (p >= C14N_NODESET_LIMIT) { break; }

        if (RTEST(list_in[i])) 
		{
          xmlNodePtr node_ptr;
          Data_Get_Struct(list_in[i], xmlNode, node_ptr);
          node_ptr_array[p] = node_ptr;
          p++;
        }
      }

      // Need to set values in nodeset struct
      nodeset.nodeNr = (node_list_size > C14N_NODESET_LIMIT ?
                        C14N_NODESET_LIMIT :
                        (int)node_list_size);
      nodeset.nodeTab = node_ptr_array;
    }
  }//option_hash

  Data_Get_Struct(self, xmlDoc, xdoc);
  xmlC14NDocDumpMemory(xdoc,
                       (nodeset.nodeNr == 0 ? NULL : &nodeset),
                       c14n_mode,
                       inc_ns_prefixes_ptr,
                       comments,
                       &buffer);

  if (buffer)
  {
    result = rxml_new_cstr( buffer, NULL);
    xmlFree(buffer);
  }

  return result;
}


/*
 * call-seq:
 *    document.compression -> num
 *
 * Obtain this document's compression mode identifier.
 */
static VALUE rxml_document_compression_get(VALUE self)
{
#ifdef HAVE_ZLIB_H
  xmlDocPtr xdoc;

  int compmode;
  Data_Get_Struct(self, xmlDoc, xdoc);

  compmode = xmlGetDocCompressMode(xdoc);
  if (compmode == -1)
  return(Qnil);
  else
  return(INT2NUM(compmode));
#else
  rb_warn("libxml not compiled with zlib support");
  return (Qfalse);
#endif
}

/*
 * call-seq:
 *    document.compression = num
 *
 * Set this document's compression mode.
 */
static VALUE rxml_document_compression_set(VALUE self, VALUE num)
{
#ifdef HAVE_ZLIB_H
  xmlDocPtr xdoc;

  int compmode;
  Check_Type(num, T_FIXNUM);
  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc == NULL)
  {
    return(Qnil);
  }
  else
  {
    xmlSetDocCompressMode(xdoc, NUM2INT(num));

    compmode = xmlGetDocCompressMode(xdoc);
    if (compmode == -1)
    return(Qnil);
    else
    return(INT2NUM(compmode));
  }
#else
  rb_warn("libxml compiled without zlib support");
  return (Qfalse);
#endif
}

/*
 * call-seq:
 *    document.compression? -> (true|false)
 *
 * Determine whether this document is compressed.
 */
static VALUE rxml_document_compression_q(VALUE self)
{
#ifdef HAVE_ZLIB_H
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->compression != -1)
  return(Qtrue);
  else
  return(Qfalse);
#else
  rb_warn("libxml compiled without zlib support");
  return (Qfalse);
#endif
}

/*
 * call-seq:
 *    document.child -> node
 *
 * Get this document's child node.
 */
static VALUE rxml_document_child_get(VALUE self)
{
  xmlDocPtr xdoc;
  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->children == NULL)
    return (Qnil);

  return rxml_node_wrap(xdoc->children);
}

/*
 * call-seq:
 *    document.child? -> (true|false)
 *
 * Determine whether this document has a child node.
 */
static VALUE rxml_document_child_q(VALUE self)
{
  xmlDocPtr xdoc;
  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->children == NULL)
    return (Qfalse);
  else
    return (Qtrue);
}


/*
 * call-seq:
 *    node.debug -> true|false
 *
 * Print libxml debugging information to stdout.
 * Requires that libxml was compiled with debugging enabled.
*/
static VALUE rxml_document_debug(VALUE self)
{
#ifdef LIBXML_DEBUG_ENABLED
  xmlDocPtr xdoc;
  Data_Get_Struct(self, xmlDoc, xdoc);
  xmlDebugDumpDocument(NULL, xdoc);
  return Qtrue;
#else
  rb_warn("libxml was compiled without debugging support.");
  return Qfalse;
#endif
}

/*
 * call-seq:
 *    document.encoding -> XML::Encoding::UTF_8
 *
 * Returns the LibXML encoding constant specified by this document.
 */
static VALUE rxml_document_encoding_get(VALUE self)
{
  xmlDocPtr xdoc;
  const char *xencoding;
  Data_Get_Struct(self, xmlDoc, xdoc);

  xencoding = (const char*)xdoc->encoding;
  return INT2NUM(xmlParseCharEncoding(xencoding));
}


/*
 * call-seq:
 *    document.rb_encoding -> Encoding
 *
 * Returns the Ruby encoding specified by this document
 * (available on Ruby 1.9.x and higher).
 */
#ifdef HAVE_RUBY_ENCODING_H
static VALUE rxml_document_rb_encoding_get(VALUE self)
{
  xmlDocPtr xdoc;
  rb_encoding* rbencoding;
  Data_Get_Struct(self, xmlDoc, xdoc);

  rbencoding = rxml_xml_encoding_to_rb_encoding(mXMLEncoding, xmlParseCharEncoding((const char*)xdoc->encoding));
  return rb_enc_from_encoding(rbencoding);
}
#endif

/*
 * call-seq:
 *    document.encoding = XML::Encoding::UTF_8
 *
 * Set the encoding for this document.
 */
static VALUE rxml_document_encoding_set(VALUE self, VALUE encoding)
{
  xmlDocPtr xdoc;
  const char* xencoding = xmlGetCharEncodingName((xmlCharEncoding)NUM2INT(encoding));

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->encoding != NULL)
    xmlFree((xmlChar *) xdoc->encoding);

  xdoc->encoding = xmlStrdup((xmlChar *)xencoding);
  return self;
}

/*
 * call-seq:
 *    document.import(node) -> XML::Node
 *
 * Creates a copy of the node that can be inserted into the
 * current document.
 *
 * IMPORTANT - The returned node MUST be inserted into the document.
 * This is because the returned node refereces internal LibXML data
 * structures owned by the document.  Therefore, if the document is
 * is freed before the the node is freed a segmentation fault will occur.
 */
static VALUE rxml_document_import(VALUE self, VALUE node)
{
  xmlDocPtr xdoc;
  xmlNodePtr xnode, xresult;

  Data_Get_Struct(self, xmlDoc, xdoc);
  Data_Get_Struct(node, xmlNode, xnode);

  xresult = xmlDocCopyNode(xnode, xdoc, 1);

  if (xresult == NULL)
    rxml_raise(&xmlLastError);

  return rxml_node_wrap(xresult);
}

/*
 * call-seq:
 *    document.last -> node
 *
 * Obtain the last node.
 */
static VALUE rxml_document_last_get(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->last == NULL)
    return (Qnil);

  return rxml_node_wrap(xdoc->last);
}

/*
 * call-seq:
 *    document.last? -> (true|false)
 *
 * Determine whether there is a last node.
 */
static VALUE rxml_document_last_q(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->last == NULL)
    return (Qfalse);
  else
    return (Qtrue);
}

/*
 * call-seq:
 *    document.next -> node
 *
 * Obtain the next node.
 */
static VALUE rxml_document_next_get(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->next == NULL)
    return (Qnil);

  return rxml_node_wrap(xdoc->next);
}

/*
 * call-seq:
 *    document.next? -> (true|false)
 *
 * Determine whether there is a next node.
 */
static VALUE rxml_document_next_q(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->next == NULL)
    return (Qfalse);
  else
    return (Qtrue);
}

/*
 * call-seq:
 *    node.type -> num
 *
 * Obtain this node's type identifier.
 */
static VALUE rxml_document_node_type(VALUE self)
{
  xmlNodePtr xnode;
  Data_Get_Struct(self, xmlNode, xnode);
  return (INT2NUM(xnode->type));
}

/*
 * call-seq:
 *    document.parent -> node
 *
 * Obtain the parent node.
 */
static VALUE rxml_document_parent_get(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->parent == NULL)
    return (Qnil);

  return rxml_node_wrap(xdoc->parent);
}

/*
 * call-seq:
 *    document.parent? -> (true|false)
 *
 * Determine whether there is a parent node.
 */
static VALUE rxml_document_parent_q(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->parent == NULL)
    return (Qfalse);
  else
    return (Qtrue);
}

/*
 * call-seq:
 *    document.prev -> node
 *
 * Obtain the previous node.
 */
static VALUE rxml_document_prev_get(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->prev == NULL)
    return (Qnil);

  return rxml_node_wrap(xdoc->prev);
}

/*
 * call-seq:
 *    document.prev? -> (true|false)
 *
 * Determine whether there is a previous node.
 */
static VALUE rxml_document_prev_q(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);

  if (xdoc->prev == NULL)
    return (Qfalse);
  else
    return (Qtrue);
}

/*
 * call-seq:
 *    document.root -> node
 *
 * Obtain the root node.
 */
static VALUE rxml_document_root_get(VALUE self)
{
  xmlDocPtr xdoc;
  xmlNodePtr root;

  Data_Get_Struct(self, xmlDoc, xdoc);
  root = xmlDocGetRootElement(xdoc);

  if (root == NULL)
    return (Qnil);

  return rxml_node_wrap(root);
}

/*
 * call-seq:
 *    document.root = node
 *
 * Set the root node.
 */
static VALUE rxml_document_root_set(VALUE self, VALUE node)
{
  xmlDocPtr xdoc;
  xmlNodePtr xnode;

  if (rb_obj_is_kind_of(node, cXMLNode) == Qfalse)
    rb_raise(rb_eTypeError, "must pass an XML::Node type object");

  Data_Get_Struct(self, xmlDoc, xdoc);
  Data_Get_Struct(node, xmlNode, xnode);

  if (xnode->doc != NULL && xnode->doc != xdoc)
    rb_raise(eXMLError, "Nodes belong to different documents.  You must first import the node by calling XML::Document.import");

  xmlDocSetRootElement(xdoc, xnode);

  // Ruby no longer manages this nodes memory
  rxml_node_unmanage(xnode, node);

  return node;
}

/*
 * call-seq:
 *    document.save(filename) -> int
 *    document.save(filename, :indent => true, :encoding => XML::Encoding::UTF_8) -> int
 *
 * Saves a document to a file.  You may provide an optional hash table
 * to control how the string is generated.  Valid options are:
 *
 * :indent - Specifies if the string should be indented.  The default value
 * is true.  Note that indentation is only added if both :indent is
 * true and XML.indent_tree_output is true.  If :indent is set to false,
 * then both indentation and line feeds are removed from the result.
 *
 * :encoding - Specifies the output encoding of the string.  It
 * defaults to the original encoding of the document (see
 * #encoding.  To override the orginal encoding, use one of the
 * XML::Encoding encoding constants. */
static VALUE rxml_document_save(int argc, VALUE *argv, VALUE self)
{
  VALUE options = Qnil;
  VALUE filename = Qnil;
  xmlDocPtr xdoc;
  int indent = 1;
  const char *xfilename;
  const xmlChar *xencoding;
  int length;

  rb_scan_args(argc, argv, "11", &filename, &options);

  Check_Type(filename, T_STRING);
  xfilename = StringValuePtr(filename);

  Data_Get_Struct(self, xmlDoc, xdoc);
  xencoding = xdoc->encoding;

  if (!NIL_P(options))
  {
    VALUE rencoding, rindent;
    Check_Type(options, T_HASH);
    rencoding = rb_hash_aref(options, ID2SYM(rb_intern("encoding")));
    rindent = rb_hash_aref(options, ID2SYM(rb_intern("indent")));

    if (rindent == Qfalse)
      indent = 0;

    if (rencoding != Qnil)
    {
      xencoding = (const xmlChar*)xmlGetCharEncodingName((xmlCharEncoding)NUM2INT(rencoding));
      if (!xencoding)
        rb_raise(rb_eArgError, "Unknown encoding value: %d", NUM2INT(rencoding));
    }
  }

  length = xmlSaveFormatFileEnc(xfilename, xdoc, (const char*)xencoding, indent);

  if (length == -1)
    rxml_raise(&xmlLastError);

  return (INT2NUM(length));
}

/*
 * call-seq:
 *    document.standalone? -> (true|false)
 *
 * Determine whether this is a standalone document.
 */
static VALUE rxml_document_standalone_q(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);
  if (xdoc->standalone)
    return (Qtrue);
  else
    return (Qfalse);
}

/*
 * call-seq:
 *    document.to_s -> "string"
 *    document.to_s(:indent => true, :encoding => XML::Encoding::UTF_8) -> "string"
 *
 * Converts a document, and all of its children, to a string representation.
 * You may provide an optional hash table to control how the string is
 * generated.  Valid options are:
 *
 * :indent - Specifies if the string should be indented.  The default value
 * is true.  Note that indentation is only added if both :indent is
 * true and XML.indent_tree_output is true.  If :indent is set to false,
 * then both indentation and line feeds are removed from the result.
 *
 * :encoding - Specifies the output encoding of the string.  It
 * defaults to XML::Encoding::UTF8.  To change it, use one of the
 * XML::Encoding encoding constants. */
static VALUE rxml_document_to_s(int argc, VALUE *argv, VALUE self)
{
  VALUE result;
  VALUE options = Qnil;
  xmlDocPtr xdoc;
  int indent = 1;
  const xmlChar *xencoding = (const xmlChar*) "UTF-8";
  xmlChar *buffer;
  int length;

  rb_scan_args(argc, argv, "01", &options);

  if (!NIL_P(options))
  {
    VALUE rencoding, rindent;
    Check_Type(options, T_HASH);
    rencoding = rb_hash_aref(options, ID2SYM(rb_intern("encoding")));
    rindent = rb_hash_aref(options, ID2SYM(rb_intern("indent")));

    if (rindent == Qfalse)
      indent = 0;

    if (rencoding != Qnil)
    {
      xencoding = (const xmlChar*)xmlGetCharEncodingName((xmlCharEncoding)NUM2INT(rencoding));
      if (!xencoding)
        rb_raise(rb_eArgError, "Unknown encoding value: %d", NUM2INT(rencoding));
    }
  }

  Data_Get_Struct(self, xmlDoc, xdoc);
  xmlDocDumpFormatMemoryEnc(xdoc, &buffer, &length, (const char*)xencoding, indent);

  result = rxml_new_cstr(buffer, xencoding);
  xmlFree(buffer);
  return result;
}

/*
 * call-seq:
 *    document.url -> "url"
 *
 * Obtain this document's source URL, if any.
 */
static VALUE rxml_document_url_get(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);
  if (xdoc->URL == NULL)
    return (Qnil);
  else
    return (rxml_new_cstr( xdoc->URL, NULL));
}

/*
 * call-seq:
 *    document.version -> "version"
 *
 * Obtain the XML version specified by this document.
 */
static VALUE rxml_document_version_get(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);
  if (xdoc->version == NULL)
    return (Qnil);
  else
    return (rxml_new_cstr( xdoc->version, NULL));
}

/*
 * call-seq:
 *    document.xhtml? -> (true|false)
 *
 * Determine whether this is an XHTML document.
 */
static VALUE rxml_document_xhtml_q(VALUE self)
{
  xmlDocPtr xdoc;
	xmlDtdPtr xdtd;
  Data_Get_Struct(self, xmlDoc, xdoc);
	xdtd = xmlGetIntSubset(xdoc);
  if (xdtd != NULL && xmlIsXHTML(xdtd->SystemID, xdtd->ExternalID) > 0)
    return (Qtrue);
  else
    return (Qfalse);
}

/*
 * call-seq:
 *    document.xinclude -> num
 *
 * Process xinclude directives in this document.
 */
static VALUE rxml_document_xinclude(VALUE self)
{
#ifdef LIBXML_XINCLUDE_ENABLED
  xmlDocPtr xdoc;

  int ret;

  Data_Get_Struct(self, xmlDoc, xdoc);
  ret = xmlXIncludeProcess(xdoc);
  if (ret >= 0)
  {
    return(INT2NUM(ret));
  }
  else
  {
    rxml_raise(&xmlLastError);
    return Qnil;
  }
#else
  rb_warn(
      "libxml was compiled without XInclude support.  Please recompile libxml and ruby-libxml");
  return (Qfalse);
#endif
}

/*
 * call-seq:
 *    document.order_elements!
 *
 * Call this routine to speed up XPath computation on static documents.
 * This stamps all the element nodes with the document order.
 */
static VALUE rxml_document_order_elements(VALUE self)
{
  xmlDocPtr xdoc;

  Data_Get_Struct(self, xmlDoc, xdoc);
  return LONG2FIX(xmlXPathOrderDocElems(xdoc));
}

/*
 * call-seq:
 *    document.validate_schema(schema)
 *
 * Validate this document against the specified XML::Schema.
 * If the document is valid the method returns true.  Otherwise an
 * exception is raised with validation information.
 */
static VALUE rxml_document_validate_schema(VALUE self, VALUE schema)
{
  xmlSchemaValidCtxtPtr vptr;
  xmlDocPtr xdoc;
  xmlSchemaPtr xschema;
  int is_invalid;

  Data_Get_Struct(self, xmlDoc, xdoc);
  Data_Get_Struct(schema, xmlSchema, xschema);

  vptr = xmlSchemaNewValidCtxt(xschema);

  is_invalid = xmlSchemaValidateDoc(vptr, xdoc);
  xmlSchemaFreeValidCtxt(vptr);
  if (is_invalid)
  {
    rxml_raise(&xmlLastError);
    return Qfalse;
  }
  else
  {
    return Qtrue;
  }
}

/*
 * call-seq:
 *    document.validate_relaxng(relaxng)
 *
 * Validate this document against the specified XML::RelaxNG.
 * If the document is valid the method returns true.  Otherwise an
 * exception is raised with validation information.
 */
static VALUE rxml_document_validate_relaxng(VALUE self, VALUE relaxng)
{
  xmlRelaxNGValidCtxtPtr vptr;
  xmlDocPtr xdoc;
  xmlRelaxNGPtr xrelaxng;
  int is_invalid;

  Data_Get_Struct(self, xmlDoc, xdoc);
  Data_Get_Struct(relaxng, xmlRelaxNG, xrelaxng);

  vptr = xmlRelaxNGNewValidCtxt(xrelaxng);

  is_invalid = xmlRelaxNGValidateDoc(vptr, xdoc);
  xmlRelaxNGFreeValidCtxt(vptr);
  if (is_invalid)
  {
    rxml_raise(&xmlLastError);
    return Qfalse;
  }
  else
  {
    return Qtrue;
  }
}

/*
 * call-seq:
 *    document.validate(dtd) -> (true|false)
 *
 * Validate this document against the specified XML::DTD.
 * If the document is valid the method returns true.  Otherwise an
 * exception is raised with validation information.
 */
static VALUE rxml_document_validate_dtd(VALUE self, VALUE dtd)
{
  xmlValidCtxt ctxt;
  xmlDocPtr xdoc;
  xmlDtdPtr xdtd;

  Data_Get_Struct(self, xmlDoc, xdoc);
  Data_Get_Struct(dtd, xmlDtd, xdtd);

  /* Setup context */
  memset(&ctxt, 0, sizeof(xmlValidCtxt));

  if (xmlValidateDtd(&ctxt, xdoc, xdtd))
  {
    return Qtrue;
  }
  else
  {
    rxml_raise(&xmlLastError);
    return Qfalse;
  }
}

void rxml_init_document(void)
{
  cXMLDocument = rb_define_class_under(mXML, "Document", rb_cObject);
  rb_define_alloc_func(cXMLDocument, rxml_document_alloc);

  /* Original C14N 1.0 spec */
  rb_define_const(cXMLDocument, "XML_C14N_1_0", INT2NUM(XML_C14N_1_0));
  /* Exclusive C14N 1.0 spec */
  rb_define_const(cXMLDocument, "XML_C14N_EXCLUSIVE_1_0", INT2NUM(XML_C14N_EXCLUSIVE_1_0));
  /* C14N 1.1 spec */
  rb_define_const(cXMLDocument, "XML_C14N_1_1", INT2NUM(XML_C14N_1_1));

  rb_define_method(cXMLDocument, "initialize", rxml_document_initialize, -1);
  rb_define_method(cXMLDocument, "canonicalize", rxml_document_canonicalize, -1);
  rb_define_method(cXMLDocument, "child", rxml_document_child_get, 0);
  rb_define_method(cXMLDocument, "child?", rxml_document_child_q, 0);
  rb_define_method(cXMLDocument, "compression", rxml_document_compression_get, 0);
  rb_define_method(cXMLDocument, "compression=", rxml_document_compression_set, 1);
  rb_define_method(cXMLDocument, "compression?", rxml_document_compression_q, 0);
  rb_define_method(cXMLDocument, "debug", rxml_document_debug, 0);
  rb_define_method(cXMLDocument, "encoding", rxml_document_encoding_get, 0);
#ifdef HAVE_RUBY_ENCODING_H
  rb_define_method(cXMLDocument, "rb_encoding", rxml_document_rb_encoding_get, 0);
#endif
  rb_define_method(cXMLDocument, "encoding=", rxml_document_encoding_set, 1);
  rb_define_method(cXMLDocument, "import", rxml_document_import, 1);
  rb_define_method(cXMLDocument, "last", rxml_document_last_get, 0);
  rb_define_method(cXMLDocument, "last?", rxml_document_last_q, 0);
  rb_define_method(cXMLDocument, "next", rxml_document_next_get, 0);
  rb_define_method(cXMLDocument, "next?", rxml_document_next_q, 0);
  rb_define_method(cXMLDocument, "node_type", rxml_document_node_type, 0);
  rb_define_method(cXMLDocument, "order_elements!", rxml_document_order_elements, 0);
  rb_define_method(cXMLDocument, "parent", rxml_document_parent_get, 0);
  rb_define_method(cXMLDocument, "parent?", rxml_document_parent_q, 0);
  rb_define_method(cXMLDocument, "prev", rxml_document_prev_get, 0);
  rb_define_method(cXMLDocument, "prev?", rxml_document_prev_q, 0);
  rb_define_method(cXMLDocument, "root", rxml_document_root_get, 0);
  rb_define_method(cXMLDocument, "root=", rxml_document_root_set, 1);
  rb_define_method(cXMLDocument, "save", rxml_document_save, -1);
  rb_define_method(cXMLDocument, "standalone?", rxml_document_standalone_q, 0);
  rb_define_method(cXMLDocument, "to_s", rxml_document_to_s, -1);
  rb_define_method(cXMLDocument, "url", rxml_document_url_get, 0);
  rb_define_method(cXMLDocument, "version", rxml_document_version_get, 0);
  rb_define_method(cXMLDocument, "xhtml?", rxml_document_xhtml_q, 0);
  rb_define_method(cXMLDocument, "xinclude", rxml_document_xinclude, 0);
  rb_define_method(cXMLDocument, "validate", rxml_document_validate_dtd, 1);
  rb_define_method(cXMLDocument, "validate_schema", rxml_document_validate_schema, 1);
  rb_define_method(cXMLDocument, "validate_relaxng", rxml_document_validate_relaxng, 1);
}
