/*
 * relaxng.h: header for the implementation of the Relax-NG validation
 *
 * See Copyright for the status of this software.
 *
 * daniel@veillard.com
 */

#ifndef __XML_RELAX_NG__
#define __XML_RELAX_NG__

#include <libxml/hash.h>

typedef struct _xmlRelaxNG xmlRelaxNG;
typedef xmlRelaxNG *xmlRelaxNGPtr;


/**
 * A schemas validation context
 */
typedef void (*xmlRelaxNGValidityErrorFunc) (void *ctx, const char *msg, ...);
typedef void (*xmlRelaxNGValidityWarningFunc) (void *ctx, const char *msg, ...);

typedef struct _xmlRelaxNGParserCtxt xmlRelaxNGParserCtxt;
typedef xmlRelaxNGParserCtxt *xmlRelaxNGParserCtxtPtr;

typedef struct _xmlRelaxNGValidCtxt xmlRelaxNGValidCtxt;
typedef xmlRelaxNGValidCtxt *xmlRelaxNGValidCtxtPtr;

/*
 * Interfaces for parsing.
 */
xmlRelaxNGParserCtxtPtr xmlRelaxNGNewParserCtxt	(const char *URL);
xmlRelaxNGParserCtxtPtr xmlRelaxNGNewMemParserCtxt(const char *buffer,
						 int size);
void		xmlRelaxNGFreeParserCtxt	(xmlRelaxNGParserCtxtPtr ctxt);
void		xmlRelaxNGSetParserErrors(xmlRelaxNGParserCtxtPtr ctxt,
					 xmlRelaxNGValidityErrorFunc err,
					 xmlRelaxNGValidityWarningFunc warn,
					 void *ctx);
xmlRelaxNGPtr	xmlRelaxNGParse		(xmlRelaxNGParserCtxtPtr ctxt);
void		xmlRelaxNGFree		(xmlRelaxNGPtr schema);
void		xmlRelaxNGDump		(FILE *output,
					 xmlRelaxNGPtr schema);
void		xmlRelaxNGDumpTree	(FILE * output,
					 xmlRelaxNGPtr schema);
/*
 * Interfaces for validating
 */
void		xmlRelaxNGSetValidErrors(xmlRelaxNGValidCtxtPtr ctxt,
					 xmlRelaxNGValidityErrorFunc err,
					 xmlRelaxNGValidityWarningFunc warn,
					 void *ctx);
xmlRelaxNGValidCtxtPtr	xmlRelaxNGNewValidCtxt	(xmlRelaxNGPtr schema);
void			xmlRelaxNGFreeValidCtxt	(xmlRelaxNGValidCtxtPtr ctxt);
int			xmlRelaxNGValidateDoc	(xmlRelaxNGValidCtxtPtr ctxt,
					 	 xmlDocPtr instance);
int			xmlRelaxNGValidateStream(xmlRelaxNGValidCtxtPtr ctxt,
						 xmlParserInputBufferPtr input,
						 xmlCharEncoding enc,
					 	 xmlSAXHandlerPtr sax,
						 void *user_data);
void			xmlRelaxNGCleanupTypes	(void);
#endif /* __XML_RELAX_NG__ */
