/* Please see the LICENSE file for copyright and distribution information */

#ifndef __RUBY_XML_H__
#define __RUBY_XML_H__

extern VALUE mXML;
int rxml_libxml_default_options();
void rxml_init_xml(void);

void rxml_register_node(xmlNodePtr node, VALUE value);
void rxml_register_doc(xmlDocPtr doc, VALUE value);
void rxml_register_dtd(xmlDtdPtr dtd, VALUE value);
void rxml_unregister_node(xmlNodePtr node);
void rxml_unregister_doc(xmlDocPtr doc);
void rxml_unregister_dtd(xmlDtdPtr dtd);
VALUE rxml_lookup_node(xmlNodePtr node);
VALUE rxml_lookup_doc(xmlDocPtr doc);
VALUE rxml_lookup_dtd(xmlDtdPtr dtd);

#endif
