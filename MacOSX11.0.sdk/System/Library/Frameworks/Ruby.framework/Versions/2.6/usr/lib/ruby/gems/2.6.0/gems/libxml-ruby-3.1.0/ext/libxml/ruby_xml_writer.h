#ifndef __RXML_WRITER__
#define __RXML_WRITER__

#ifdef LIBXML_WRITER_ENABLED
#include <libxml/xmlwriter.h>
#endif

extern VALUE cXMLWriter;
void rxml_init_writer(void);
#endif
