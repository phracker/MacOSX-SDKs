/*
 * Summary: interface for the memory allocator
 * Description: provides interfaces for the memory allocator,
 *              including debugging capabilities.
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Daniel Veillard
 */


#ifndef __DEBUG_MEMORY_ALLOC__
#define __DEBUG_MEMORY_ALLOC__

#include <stdio.h>
#include <libxml/xmlversion.h>

/**
 * DEBUG_MEMORY:
 *
 * DEBUG_MEMORY replaces the allocator with a collect and debug
 * shell to the libc allocator.
 * DEBUG_MEMORY should only be activated when debugging
 * libxml i.e. if libxml has been configured with --with-debug-mem too.
 */
/* #define DEBUG_MEMORY_FREED */
/* #define DEBUG_MEMORY_LOCATION */

#ifdef DEBUG
#ifndef DEBUG_MEMORY
#define DEBUG_MEMORY
#endif
#endif

/**
 * DEBUG_MEMORY_LOCATION:
 *
 * DEBUG_MEMORY_LOCATION should be activated only when debugging
 * libxml i.e. if libxml has been configured with --with-debug-mem too.
 */
#ifdef DEBUG_MEMORY_LOCATION
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The XML memory wrapper support 4 basic overloadable functions.
 */
/**
 * xmlFreeFunc:
 * @mem: an already allocated block of memory
 *
 * Signature for a free() implementation.
 */
typedef void (XMLCALL *xmlFreeFunc)(void *mem);
/**
 * xmlMallocFunc:
 * @size:  the size requested in bytes
 *
 * Signature for a malloc() implementation.
 *
 * Returns a pointer to the newly allocated block or NULL in case of error.
 */
typedef void *(LIBXML_ATTR_ALLOC_SIZE(1) XMLCALL *xmlMallocFunc)(size_t size) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;

/**
 * xmlReallocFunc:
 * @mem: an already allocated block of memory
 * @size:  the new size requested in bytes
 *
 * Signature for a realloc() implementation.
 *
 * Returns a pointer to the newly reallocated block or NULL in case of error.
 */
typedef void *(XMLCALL *xmlReallocFunc)(void *mem, size_t size) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;

/**
 * xmlStrdupFunc:
 * @str: a zero terminated string
 *
 * Signature for an strdup() implementation.
 *
 * Returns the copy of the string or NULL in case of error.
 */
typedef char *(XMLCALL *xmlStrdupFunc)(const char *str) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;

/*
 * The 4 interfaces used for all memory handling within libxml.
LIBXML_DLL_IMPORT xmlFreeFunc xmlFree;
LIBXML_DLL_IMPORT xmlMallocFunc xmlMalloc;
LIBXML_DLL_IMPORT xmlMallocFunc xmlMallocAtomic;
LIBXML_DLL_IMPORT xmlReallocFunc xmlRealloc;
LIBXML_DLL_IMPORT xmlStrdupFunc xmlMemStrdup;
 */

/*
 * The way to overload the existing functions.
 * The xmlGc function have an extra entry for atomic block
 * allocations useful for garbage collected memory allocators
 */
XMLPUBFUN int XMLCALL
	xmlMemSetup	(xmlFreeFunc freeFunc,
			 xmlMallocFunc mallocFunc,
			 xmlReallocFunc reallocFunc,
			 xmlStrdupFunc strdupFunc) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN int XMLCALL
	xmlMemGet	(xmlFreeFunc *freeFunc,
			 xmlMallocFunc *mallocFunc,
			 xmlReallocFunc *reallocFunc,
			 xmlStrdupFunc *strdupFunc) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN int XMLCALL
	xmlGcMemSetup	(xmlFreeFunc freeFunc,
			 xmlMallocFunc mallocFunc,
			 xmlMallocFunc mallocAtomicFunc,
			 xmlReallocFunc reallocFunc,
			 xmlStrdupFunc strdupFunc) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN int XMLCALL
	xmlGcMemGet	(xmlFreeFunc *freeFunc,
			 xmlMallocFunc *mallocFunc,
			 xmlMallocFunc *mallocAtomicFunc,
			 xmlReallocFunc *reallocFunc,
			 xmlStrdupFunc *strdupFunc) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;

/*
 * Initialization of the memory layer.
 */
XMLPUBFUN int XMLCALL
	xmlInitMemory	(void);

/*
 * Cleanup of the memory layer.
 */
XMLPUBFUN void XMLCALL
                xmlCleanupMemory        (void);
/*
 * These are specific to the XML debug memory wrapper.
 */
XMLPUBFUN size_t XMLCALL
	xmlMemSize	(void *ptr) LIBXML_API_AVAILABLE_MACOS14_IOS17_WATCHOS10_TVOS17;
XMLPUBFUN int XMLCALL
	xmlMemUsed	(void);
XMLPUBFUN int XMLCALL
	xmlMemBlocks	(void);
XMLPUBFUN void XMLCALL
	xmlMemDisplay	(FILE *fp);
XMLPUBFUN void XMLCALL
	xmlMemDisplayLast(FILE *fp, long nbBytes);
XMLPUBFUN void XMLCALL
	xmlMemShow	(FILE *fp, int nr);
XMLPUBFUN void XMLCALL
	xmlMemoryDump	(void);
XMLPUBFUN void * XMLCALL
	xmlMemMalloc	(size_t size) LIBXML_ATTR_ALLOC_SIZE(1) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN void * XMLCALL
	xmlMemRealloc	(void *ptr,size_t size) LIBXML_ATTR_ALLOC_SIZE(2) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN void XMLCALL
	xmlMemFree	(void *ptr) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN char * XMLCALL
	xmlMemoryStrdup	(const char *str) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN void * XMLCALL
	xmlMallocLoc	(size_t size, const char *file, int line) LIBXML_ATTR_ALLOC_SIZE(1) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN void * XMLCALL
	xmlReallocLoc	(void *ptr, size_t size, const char *file, int line) LIBXML_ATTR_ALLOC_SIZE(2) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN void * XMLCALL
	xmlMallocAtomicLoc (size_t size, const char *file, int line) LIBXML_ATTR_ALLOC_SIZE(1) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;
XMLPUBFUN char * XMLCALL
	xmlMemStrdupLoc	(const char *str, const char *file, int line) LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS;


#ifdef DEBUG_MEMORY_LOCATION
/**
 * xmlMalloc:
 * @size:  number of bytes to allocate
 *
 * Wrapper for the malloc() function used in the XML library.
 *
 * Returns the pointer to the allocated area or NULL in case of error.
 */
#define xmlMalloc(size) xmlMallocLoc((size), __FILE__, __LINE__)
/**
 * xmlMallocAtomic:
 * @size:  number of bytes to allocate
 *
 * Wrapper for the malloc() function used in the XML library for allocation
 * of block not containing pointers to other areas.
 *
 * Returns the pointer to the allocated area or NULL in case of error.
 */
#define xmlMallocAtomic(size) xmlMallocAtomicLoc((size), __FILE__, __LINE__)
/**
 * xmlRealloc:
 * @ptr:  pointer to the existing allocated area
 * @size:  number of bytes to allocate
 *
 * Wrapper for the realloc() function used in the XML library.
 *
 * Returns the pointer to the allocated area or NULL in case of error.
 */
#define xmlRealloc(ptr, size) xmlReallocLoc((ptr), (size), __FILE__, __LINE__)
/**
 * xmlMemStrdup:
 * @str:  pointer to the existing string
 *
 * Wrapper for the strdup() function, xmlStrdup() is usually preferred.
 *
 * Returns the pointer to the allocated area or NULL in case of error.
 */
#define xmlMemStrdup(str) xmlMemStrdupLoc((str), __FILE__, __LINE__)

#endif /* DEBUG_MEMORY_LOCATION */

#if defined(LIBXML_HAS_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS)
#define xmlMemMalloc(size) malloc(size)
#define xmlMemRealloc(ptr, size) realloc(ptr, size)
#define xmlMemFree(ptr) free(ptr)
#define xmlMemoryStrdup(str) strdup(str)

#define xmlMallocLoc(size, file, line) malloc(size)
#define xmlReallocLoc(ptr, size, file, line) realloc((ptr), (size))
#define xmlMallocAtomicLoc(size, file, line) malloc(size)
#define xmlMemStrdupLoc(str, file, line) strdup(str)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifndef __XML_GLOBALS_H
#ifndef __XML_THREADS_H__
#include <libxml/threads.h>
#include <libxml/globals.h>
#endif
#endif

#endif  /* __DEBUG_MEMORY_ALLOC__ */

