/* Please see the LICENSE file for copyright and distribution information */

#ifndef __RXML_ENCODING__
#define __RXML_ENCODING__

extern VALUE mXMLEncoding;

void rxml_init_encoding();

VALUE rxml_new_cstr(const xmlChar* xstr, const xmlChar* xencoding);
VALUE rxml_new_cstr_len(const xmlChar* xstr, const long length, const xmlChar* xencoding);

rb_encoding* rxml_xml_encoding_to_rb_encoding(VALUE klass, xmlCharEncoding xmlEncoding);
rb_encoding* rxml_figure_encoding(const xmlChar* xencoding);

#endif
