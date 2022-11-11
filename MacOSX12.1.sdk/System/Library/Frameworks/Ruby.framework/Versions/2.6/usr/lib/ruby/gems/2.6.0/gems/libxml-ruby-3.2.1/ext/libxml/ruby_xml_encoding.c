/* Please see the LICENSE file for copyright and distribution information */

#include <stdarg.h>
#include "ruby_libxml.h"

/*
 * Document-class: LibXML::XML::Encoding
 *
 * The encoding class exposes the encodings that libxml
 * supports via constants.  
 *
 * LibXML converts all data sources to UTF8
 * internally before processing them.  By default, 
 * LibXML determines a data source's encoding 
 * using the algorithm described on its
 * website[http://xmlsoft.org/encoding.html].  
 *
 * However, you may override a data source's encoding 
 * by using the encoding constants defined in this
 * module.
 *
 * Example 1:
 *
 *   io = File.open('some_file', 'rb')
 *   parser = XML::Parser.io(io, :encoding => XML::Encoding::ISO_8859_1)
 *   doc = parser.parse
 *
 * Example 2:
 *
 *   parser = XML::HTMLParser.file("some_file", :encoding => XML::Encoding::ISO_8859_1)
 *   doc = parser.parse
 *
 * Example 3:
 *
 *   document = XML::Document.new
 *   document.encoding = XML::Encoding::ISO_8859_1
 *   doc << XML::Node.new
 */

VALUE mXMLEncoding;

/*
 * call-seq:
 *    Encoding.from_s("UTF_8") -> XML::Encoding::UTF_8
 *
 * Converts an encoding string to an encoding constant
 * defined on the XML::Encoding class.
 */
static VALUE rxml_encoding_from_s(VALUE klass, VALUE encoding)
{
  xmlCharEncoding xencoding;

  if (encoding == Qnil)
    return Qnil;

  xencoding = xmlParseCharEncoding(StringValuePtr(encoding));
  return INT2NUM(xencoding);
}

/*
 * call-seq:
 *    Encoding.to_s(XML::Encoding::UTF_8) -> "UTF-8"
 *
 * Converts an encoding constant defined on the XML::Encoding
 * class to its text representation.
 */
static VALUE rxml_encoding_to_s(VALUE klass, VALUE encoding)
{
  const xmlChar* xencoding = (const xmlChar*)xmlGetCharEncodingName(NUM2INT(encoding));

  if (!xencoding)
    return Qnil;
  else
    return rxml_new_cstr(xencoding, xencoding);
}

/*
 * Converts an xmlCharEncoding enum value into a Ruby Encoding object (available
 * on Ruby 1.9.* and higher).
 */
rb_encoding* rxml_xml_encoding_to_rb_encoding(VALUE klass, xmlCharEncoding xmlEncoding)
{
  const char* encodingName;

  switch (xmlEncoding)
  {
    case XML_CHAR_ENCODING_UTF8:
      encodingName = "UTF-8";
      break;
    case XML_CHAR_ENCODING_UTF16LE:
      encodingName = "UTF-16LE";
      break;
    case XML_CHAR_ENCODING_UTF16BE:
      encodingName = "UTF-16BE";
      break;
    case XML_CHAR_ENCODING_UCS4LE:
      encodingName = "UCS-4LE";
      break;
    case XML_CHAR_ENCODING_UCS4BE:
      encodingName = "UCS-4BE";
      break;
    case XML_CHAR_ENCODING_UCS2:
      encodingName = "UCS-2";
      break;
    case XML_CHAR_ENCODING_8859_1:
      encodingName = "ISO8859-1";
      break;
    case XML_CHAR_ENCODING_8859_2:
      encodingName = "ISO8859-2";
      break;
    case XML_CHAR_ENCODING_8859_3:
      encodingName = "ISO8859-3";
      break;
    case XML_CHAR_ENCODING_8859_4:
      encodingName = "ISO8859-4";
      break;
    case XML_CHAR_ENCODING_8859_5:
      encodingName = "ISO8859-5";
      break;
    case XML_CHAR_ENCODING_8859_6:
      encodingName = "ISO8859-6";
      break;
    case XML_CHAR_ENCODING_8859_7:
      encodingName = "ISO8859-7";
      break;
    case XML_CHAR_ENCODING_8859_8:
      encodingName = "ISO8859-8";
      break;
    case XML_CHAR_ENCODING_8859_9:
      encodingName = "ISO8859-9";
      break;
    case XML_CHAR_ENCODING_2022_JP:
      encodingName = "ISO-2022-JP";
      break;
    case XML_CHAR_ENCODING_SHIFT_JIS:
      encodingName = "SHIFT-JIS";
      break;
    case XML_CHAR_ENCODING_EUC_JP:
      encodingName = "EUC-JP";
      break;
    case XML_CHAR_ENCODING_ASCII:
      encodingName = "US-ASCII";
      break;
    default:
      /* Covers XML_CHAR_ENCODING_ERROR, XML_CHAR_ENCODING_NONE, XML_CHAR_ENCODING_EBCDIC */
      encodingName = "ASCII-8BIT";
      break;
  }

  return rb_enc_find(encodingName);
}

/*
 * call-seq:
 *    Input.encoding_to_rb_encoding(Input::ENCODING) -> Encoding
 *
 * Converts an encoding constant defined on the XML::Encoding
 * class to a Ruby encoding object (available on Ruby 1.9.* and higher).
 */
VALUE rxml_encoding_to_rb_encoding(VALUE klass, VALUE encoding)
{
  xmlCharEncoding xmlEncoding = (xmlCharEncoding)NUM2INT(encoding);
  rb_encoding* rbencoding = rxml_xml_encoding_to_rb_encoding(klass, xmlEncoding);
  return rb_enc_from_encoding(rbencoding);
}

rb_encoding* rxml_figure_encoding(const xmlChar* xencoding)
{
  rb_encoding* result;
  if (xencoding)
  {
    xmlCharEncoding xmlEncoding = xmlParseCharEncoding((const char*)xencoding);
    result = rxml_xml_encoding_to_rb_encoding(mXMLEncoding, xmlEncoding);
  }
  else
  {
    result = rb_utf8_encoding();
  }
  return result;
}

VALUE rxml_new_cstr(const xmlChar* xstr, const xmlChar* xencoding)
{
  rb_encoding *rbencoding = rxml_figure_encoding(xencoding);
  return rb_external_str_new_with_enc((const char*)xstr, strlen((const char*)xstr), rbencoding);
}

VALUE rxml_new_cstr_len(const xmlChar* xstr, const long length, const xmlChar* xencoding)
{
  rb_encoding *rbencoding = rxml_figure_encoding(xencoding);
  return rb_external_str_new_with_enc((const char*)xstr, length, rbencoding);
}

void rxml_init_encoding(void)
{
  mXMLEncoding = rb_define_module_under(mXML, "Encoding");
  rb_define_module_function(mXMLEncoding, "from_s", rxml_encoding_from_s, 1);
  rb_define_module_function(mXMLEncoding, "to_s", rxml_encoding_to_s, 1);

  rb_define_module_function(mXMLEncoding, "to_rb_encoding", rxml_encoding_to_rb_encoding, 2);

  /* -1: No char encoding detected. */
  rb_define_const(mXMLEncoding, "ERROR", INT2NUM(XML_CHAR_ENCODING_ERROR));
  /* 0: No char encoding detected. */
  rb_define_const(mXMLEncoding, "NONE", INT2NUM(XML_CHAR_ENCODING_NONE));
  /* 1: UTF-8 */
  rb_define_const(mXMLEncoding, "UTF_8", INT2NUM(XML_CHAR_ENCODING_UTF8));
  /* 2: UTF-16 little endian. */
  rb_define_const(mXMLEncoding, "UTF_16LE", INT2NUM(XML_CHAR_ENCODING_UTF16LE));
  /* 3: UTF-16 big endian. */
  rb_define_const(mXMLEncoding, "UTF_16BE", INT2NUM(XML_CHAR_ENCODING_UTF16BE)); 
  /* 4: UCS-4 little endian. */
  rb_define_const(mXMLEncoding, "UCS_4LE", INT2NUM(XML_CHAR_ENCODING_UCS4LE));
  /* 5: UCS-4 big endian. */
  rb_define_const(mXMLEncoding, "UCS_4BE", INT2NUM(XML_CHAR_ENCODING_UCS4BE));
  /* 6: EBCDIC uh! */
  rb_define_const(mXMLEncoding, "EBCDIC", INT2NUM(XML_CHAR_ENCODING_EBCDIC)); 
  /* 7: UCS-4 unusual ordering. */
  rb_define_const(mXMLEncoding, "UCS_4_2143", INT2NUM(XML_CHAR_ENCODING_UCS4_2143));
  /* 8: UCS-4 unusual ordering. */
  rb_define_const(mXMLEncoding, "UCS_4_3412", INT2NUM(XML_CHAR_ENCODING_UCS4_3412));
  /* 9: UCS-2. */
  rb_define_const(mXMLEncoding, "UCS_2", INT2NUM(XML_CHAR_ENCODING_UCS2));
  /* 10: ISO-8859-1 ISO Latin 1. */
  rb_define_const(mXMLEncoding, "ISO_8859_1", INT2NUM(XML_CHAR_ENCODING_8859_1));
  /* 11: ISO-8859-2 ISO Latin 2. */
  rb_define_const(mXMLEncoding, "ISO_8859_2", INT2NUM(XML_CHAR_ENCODING_8859_2));
  /* 12: ISO-8859-3. */
  rb_define_const(mXMLEncoding, "ISO_8859_3", INT2NUM(XML_CHAR_ENCODING_8859_3));
  /* 13: ISO-8859-4. */
  rb_define_const(mXMLEncoding, "ISO_8859_4", INT2NUM(XML_CHAR_ENCODING_8859_4));
  /* 14: ISO-8859-5. */
  rb_define_const(mXMLEncoding, "ISO_8859_5", INT2NUM(XML_CHAR_ENCODING_8859_5));
  /* 15: ISO-8859-6. */
  rb_define_const(mXMLEncoding, "ISO_8859_6", INT2NUM(XML_CHAR_ENCODING_8859_6));
  /* 16: ISO-8859-7. */
  rb_define_const(mXMLEncoding, "ISO_8859_7", INT2NUM(XML_CHAR_ENCODING_8859_7));
  /* 17: ISO-8859-8. */
  rb_define_const(mXMLEncoding, "ISO_8859_8", INT2NUM(XML_CHAR_ENCODING_8859_8));
  /* 18: ISO-8859-9. */
  rb_define_const(mXMLEncoding, "ISO_8859_9", INT2NUM(XML_CHAR_ENCODING_8859_9));
  /* 19: ISO-2022-JP. */
  rb_define_const(mXMLEncoding, "ISO_2022_JP", INT2NUM(XML_CHAR_ENCODING_2022_JP));
  /* 20: Shift_JIS. */
  rb_define_const(mXMLEncoding, "SHIFT_JIS", INT2NUM(XML_CHAR_ENCODING_SHIFT_JIS));
  /* 21: EUC-JP. */
  rb_define_const(mXMLEncoding, "EUC_JP", INT2NUM(XML_CHAR_ENCODING_EUC_JP));
  /* 22: pure ASCII. */
  rb_define_const(mXMLEncoding, "ASCII", INT2NUM(XML_CHAR_ENCODING_ASCII));
}
