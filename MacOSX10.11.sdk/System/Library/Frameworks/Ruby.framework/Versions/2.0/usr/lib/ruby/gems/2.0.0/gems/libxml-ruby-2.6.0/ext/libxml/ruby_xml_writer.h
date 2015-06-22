#ifndef __RXML_WRITER__
# define __RXML_WRITER__

# include <libxml/xmlversion.h>

# ifdef LIBXML_WRITER_ENABLED

#  include <libxml/xmlwriter.h>

extern VALUE cXMLWriter;

void rxml_init_writer(void);

# endif /* LIBXML_WRITER_ENABLED */

#endif /* __RXML_WRITER__ */
