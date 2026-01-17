/*
 * Summary: compile-time version information
 * Description: compile-time version information for the XML library
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Daniel Veillard
 */

#ifndef __XML_VERSION_H__
#define __XML_VERSION_H__

#include <libxml/xmlexports.h>

#ifdef __APPLE__
#include <Availability.h>
#include <TargetConditionals.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * use those to be sure nothing nasty will happen if
 * your library and includes mismatch
 */
#ifndef LIBXML2_COMPILING_MSCCDEF
XMLPUBFUN void XMLCALL xmlCheckVersion(int version);
#endif /* LIBXML2_COMPILING_MSCCDEF */

/**
 * LIBXML_DOTTED_VERSION:
 *
 * the version string like "1.2.3"
 */
#define LIBXML_DOTTED_VERSION "2.9.13"

/**
 * LIBXML_VERSION:
 *
 * the version number: 1.2.3 value is 10203
 */
#define LIBXML_VERSION 20913

/**
 * LIBXML_VERSION_STRING:
 *
 * the version number string, 1.2.3 value is "10203"
 */
#define LIBXML_VERSION_STRING "20913"

/**
 * LIBXML_VERSION_EXTRA:
 *
 * extra version information, used to show a git commit description
 */
#define LIBXML_VERSION_EXTRA ""

/**
 * LIBXML_TEST_VERSION:
 *
 * Macro to check that the libxml version in use is compatible with
 * the version the software has been compiled against
 */
#define LIBXML_TEST_VERSION xmlCheckVersion(20913);

#ifndef VMS
#if 0
/**
 * WITH_TRIO:
 *
 * defined if the trio support need to be configured in
 */
#define WITH_TRIO
#else
/**
 * WITHOUT_TRIO:
 *
 * defined if the trio support should not be configured in
 */
#define WITHOUT_TRIO
#endif
#else /* VMS */
/**
 * WITH_TRIO:
 *
 * defined if the trio support need to be configured in
 */
#define WITH_TRIO 1
#endif /* VMS */

/**
 * LIBXML_THREAD_ENABLED:
 *
 * Whether the thread support is configured in
 */
#if 1
#define LIBXML_THREAD_ENABLED
#endif

/**
 * LIBXML_THREAD_ALLOC_ENABLED:
 *
 * Whether the allocation hooks are per-thread
 */
#if 0
#define LIBXML_THREAD_ALLOC_ENABLED
#endif

/**
 * LIBXML_TREE_ENABLED:
 *
 * Whether the DOM like tree manipulation API support is configured in
 */
#if 1
#define LIBXML_TREE_ENABLED
#endif

/**
 * LIBXML_OUTPUT_ENABLED:
 *
 * Whether the serialization/saving support is configured in
 */
#if 1
#define LIBXML_OUTPUT_ENABLED
#endif

/**
 * LIBXML_PUSH_ENABLED:
 *
 * Whether the push parsing interfaces are configured in
 */
#if 1
#define LIBXML_PUSH_ENABLED
#endif

/**
 * LIBXML_READER_ENABLED:
 *
 * Whether the xmlReader parsing interface is configured in
 */
#if 1
#define LIBXML_READER_ENABLED
#endif

/**
 * LIBXML_PATTERN_ENABLED:
 *
 * Whether the xmlPattern node selection interface is configured in
 */
#if 1
#define LIBXML_PATTERN_ENABLED
#endif

/**
 * LIBXML_WRITER_ENABLED:
 *
 * Whether the xmlWriter saving interface is configured in
 */
#if 1
#define LIBXML_WRITER_ENABLED
#endif

/**
 * LIBXML_SAX1_ENABLED:
 *
 * Whether the older SAX1 interface is configured in
 */
#if 1
#define LIBXML_SAX1_ENABLED
#endif

/**
 * LIBXML_FTP_ENABLED:
 *
 * Whether the FTP support is configured in
 */
#if 1
#define LIBXML_FTP_ENABLED
#endif

/**
 * LIBXML_HTTP_ENABLED:
 *
 * Whether the HTTP support is configured in
 */
#if 1
#define LIBXML_HTTP_ENABLED
#endif

/**
 * LIBXML_VALID_ENABLED:
 *
 * Whether the DTD validation support is configured in
 */
#if 1
#define LIBXML_VALID_ENABLED
#endif

/**
 * LIBXML_HTML_ENABLED:
 *
 * Whether the HTML support is configured in
 */
#if 1
#define LIBXML_HTML_ENABLED
#endif

/**
 * LIBXML_LEGACY_ENABLED:
 *
 * Whether the deprecated APIs are compiled in for compatibility
 */
#if 1
#define LIBXML_LEGACY_ENABLED
#endif

/**
 * LIBXML_C14N_ENABLED:
 *
 * Whether the Canonicalization support is configured in
 */
#if 1
#define LIBXML_C14N_ENABLED
#endif

/**
 * LIBXML_CATALOG_ENABLED:
 *
 * Whether the Catalog support is configured in
 */
#if 1
#define LIBXML_CATALOG_ENABLED
#endif

/**
 * LIBXML_DOCB_ENABLED:
 *
 * Whether the SGML Docbook support is configured in
 */
#if 1
#define LIBXML_DOCB_ENABLED
#endif

/**
 * LIBXML_XPATH_ENABLED:
 *
 * Whether XPath is configured in
 */
#if 1
#define LIBXML_XPATH_ENABLED
#endif

/**
 * LIBXML_XPTR_ENABLED:
 *
 * Whether XPointer is configured in
 */
#if 1
#define LIBXML_XPTR_ENABLED
#endif

/**
 * LIBXML_XPTR_LOCS_ENABLED:
 *
 * Whether support for XPointer locations is configured in
 */
#if 1
#define LIBXML_XPTR_LOCS_ENABLED
#endif

/**
 * LIBXML_XINCLUDE_ENABLED:
 *
 * Whether XInclude is configured in
 */
#if 1
#define LIBXML_XINCLUDE_ENABLED
#endif

/**
 * LIBXML_ICONV_ENABLED:
 *
 * Whether iconv support is available
 */
#if 0
#define LIBXML_ICONV_ENABLED
#endif

/**
 * LIBXML_ICU_ENABLED:
 *
 * Whether icu support is available
 */
#if 1
#define LIBXML_ICU_ENABLED
#endif

/**
 * LIBXML_ISO8859X_ENABLED:
 *
 * Whether ISO-8859-* support is made available in case iconv is not
 */
#if 1
#define LIBXML_ISO8859X_ENABLED
#endif

/**
 * LIBXML_DEBUG_ENABLED:
 *
 * Whether Debugging module is configured in
 */
#if 1
#define LIBXML_DEBUG_ENABLED
#endif

/**
 * DEBUG_MEMORY_LOCATION:
 *
 * Whether the memory debugging is configured in
 */
#if 0
#define DEBUG_MEMORY_LOCATION
#endif

/**
 * LIBXML_DEBUG_RUNTIME:
 *
 * Whether the runtime debugging is configured in
 */
#if 0
#define LIBXML_DEBUG_RUNTIME
#endif

/**
 * LIBXML_UNICODE_ENABLED:
 *
 * Whether the Unicode related interfaces are compiled in
 */
#if 1
#define LIBXML_UNICODE_ENABLED
#endif

/**
 * LIBXML_REGEXP_ENABLED:
 *
 * Whether the regular expressions interfaces are compiled in
 */
#if 1
#define LIBXML_REGEXP_ENABLED
#endif

/**
 * LIBXML_AUTOMATA_ENABLED:
 *
 * Whether the automata interfaces are compiled in
 */
#if 1
#define LIBXML_AUTOMATA_ENABLED
#endif

/**
 * LIBXML_EXPR_ENABLED:
 *
 * Whether the formal expressions interfaces are compiled in
 *
 * This code is unused and disabled unconditionally for now.
 */
#if 0
#define LIBXML_EXPR_ENABLED
#endif

/**
 * LIBXML_SCHEMAS_ENABLED:
 *
 * Whether the Schemas validation interfaces are compiled in
 */
#if 1
#define LIBXML_SCHEMAS_ENABLED
#endif

/**
 * LIBXML_SCHEMATRON_ENABLED:
 *
 * Whether the Schematron validation interfaces are compiled in
 */
#if 1
#define LIBXML_SCHEMATRON_ENABLED
#endif

/**
 * LIBXML_MODULES_ENABLED:
 *
 * Whether the module interfaces are compiled in
 */
#if 1
#define LIBXML_MODULES_ENABLED
/**
 * LIBXML_MODULE_EXTENSION:
 *
 * the string suffix used by dynamic modules (usually shared libraries)
 */
#define LIBXML_MODULE_EXTENSION ".so" 
#endif

/**
 * LIBXML_ZLIB_ENABLED:
 *
 * Whether the Zlib support is compiled in
 */
#if 1
#define LIBXML_ZLIB_ENABLED
#endif

/**
 * LIBXML_LZMA_ENABLED:
 *
 * Whether the Lzma support is compiled in
 */
#if 0
#define LIBXML_LZMA_ENABLED
#endif

#ifdef __GNUC__

/**
 * ATTRIBUTE_UNUSED:
 *
 * Macro used to signal to GCC unused function parameters
 */

#ifndef ATTRIBUTE_UNUSED
# if ((__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 7)))
#  define ATTRIBUTE_UNUSED __attribute__((unused))
# else
#  define ATTRIBUTE_UNUSED
# endif
#endif

/**
 * LIBXML_ATTR_ALLOC_SIZE:
 *
 * Macro used to indicate to GCC this is an allocator function
 */

#ifndef LIBXML_ATTR_ALLOC_SIZE
# if (!defined(__clang__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3))))
#  define LIBXML_ATTR_ALLOC_SIZE(x) __attribute__((alloc_size(x)))
# else
#  define LIBXML_ATTR_ALLOC_SIZE(x)
# endif
#else
# undef LIBXML_ATTR_ALLOC_SIZE(x)
# define LIBXML_ATTR_ALLOC_SIZE(x)
#endif

/**
 * LIBXML_ATTR_FORMAT:
 *
 * Macro used to indicate to GCC the parameter are printf like
 */

#ifndef LIBXML_ATTR_FORMAT
# if ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)))
#  define LIBXML_ATTR_FORMAT(fmt,args) __attribute__((__format__(__printf__,fmt,args)))
# else
#  define LIBXML_ATTR_FORMAT(fmt,args)
# endif
#else
# undef LIBXML_ATTR_FORMAT(fmt,args)
# define LIBXML_ATTR_FORMAT(fmt,args)
#endif

#ifndef XML_DEPRECATED
#  ifdef IN_LIBXML
#    define XML_DEPRECATED
#  elif defined(__APPLE__)
/* Apple has its own deprecation macros that include OS versions. */
#    define XML_DEPRECATED
#  else
/* Available since at least GCC 3.1 */
#    define XML_DEPRECATED __attribute__((deprecated))
#  endif
#endif

#else /* ! __GNUC__ */
/**
 * ATTRIBUTE_UNUSED:
 *
 * Macro used to signal to GCC unused function parameters
 */
#define ATTRIBUTE_UNUSED
/**
 * LIBXML_ATTR_ALLOC_SIZE:
 *
 * Macro used to indicate to GCC this is an allocator function
 */
#define LIBXML_ATTR_ALLOC_SIZE(x)
/**
 * LIBXML_ATTR_FORMAT:
 *
 * Macro used to indicate to GCC the parameter are printf like
 */
#define LIBXML_ATTR_FORMAT(fmt,args)
/**
 * XML_DEPRECATED:
 *
 * Macro used to indicate that a function, variable, type or struct member
 * is deprecated.
 */
#ifndef XML_DEPRECATED
#define XML_DEPRECATED
#endif
#endif /* __GNUC__ */

/**
 * LIBXML_API_AVAILABLE_MACOS13_IOS16_WATCHOS9_TVOS16:
 * LIBXML_HAS_XPATH_RESOURCE_LIMITS:
 *
 * Macros used for binary compatibility between Apple's v2.9.4 and v2.9.12+.
 */

#ifdef __APPLE__

#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 160000 \
    || defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 130000 \
    || defined(__TV_OS_VERSION_MIN_REQUIRED) && __TV_OS_VERSION_MIN_REQUIRED >= 160000 \
    || defined(__WATCH_OS_VERSION_MIN_REQUIRED) && __WATCH_OS_VERSION_MIN_REQUIRED >= 90000
#define LIBXML_API_AVAILABLE_MACOS13_IOS16_WATCHOS9_TVOS16 \
        __IOS_AVAILABLE(16.0) __OSX_AVAILABLE(13.0) __TVOS_AVAILABLE(16.0) __WATCHOS_AVAILABLE(9.0)
#define LIBXML_API_DEPRECATED_MACOS13_IOS16_WATCHOS9_TVOS16(libxml2_version) \
        __OSX_DEPRECATED(10.4, 13.0, "Also deprecated in libxml2 " # libxml2_version) \
        __IOS_DEPRECATED(2.0, 16.0, "Also deprecated in libxml2 " # libxml2_version) \
        __TVOS_DEPRECATED(9.0, 16.0, "Also deprecated in libxml2 " # libxml2_version) \
        __WATCHOS_DEPRECATED(1.0, 9.0, "Also deprecated in libxml2 " # libxml2_version)
#define LIBXML_HAS_ICU_PIVOT_BUFFER
#define LIBXML_HAS_XPATH_RESOURCE_LIMITS
#else
#define LIBXML_API_AVAILABLE_MACOS13_IOS16_WATCHOS9_TVOS16
#define LIBXML_API_DEPRECATED_MACOS13_IOS16_WATCHOS9_TVOS16(libxml2_version)
#undef LIBXML_HAS_ICU_PIVOT_BUFFER
#undef LIBXML_HAS_XPATH_RESOURCE_LIMITS
#endif

#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 170000 \
    || defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 140000 \
    || defined(__TV_OS_VERSION_MIN_REQUIRED) && __TV_OS_VERSION_MIN_REQUIRED >= 170000 \
    || defined(__WATCH_OS_VERSION_MIN_REQUIRED) && __WATCH_OS_VERSION_MIN_REQUIRED >= 100000
#define LIBXML_API_AVAILABLE_MACOS14_IOS17_WATCHOS10_TVOS17 \
        __IOS_AVAILABLE(17.0) __OSX_AVAILABLE(14.0) __TVOS_AVAILABLE(17.0) __WATCHOS_AVAILABLE(10.0)
#else
#define LIBXML_API_AVAILABLE_MACOS14_IOS17_WATCHOS10_TVOS17
#endif

#if (defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 180400) \
    || (defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 150400) \
    || (defined(__TV_OS_VERSION_MAX_ALLOWED) && __TV_OS_VERSION_MAX_ALLOWED >= 180400) \
    || (defined(__VISION_OS_VERSION_MAX_ALLOWED) && __VISION_OS_VERSION_MAX_ALLOWED >= 20400) \
    || (defined(__WATCH_OS_VERSION_MAX_ALLOWED) && __WATCH_OS_VERSION_MAX_ALLOWED >= 110400)
#define LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS \
        __OSX_DEPRECATED(10.0, 15.4, "Memory allocation functions deprecated") \
        __IOS_DEPRECATED(2.0, 18.4, "Memory allocation functions deprecated") \
        __TVOS_DEPRECATED(9.0, 18.4, "Memory allocation functions deprecated") \
        __WATCHOS_DEPRECATED(1.0, 11.4, "Memory allocation functions deprecated")
#define LIBXML_HAS_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS
#else
#define LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS
#undef LIBXML_HAS_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS
#endif

#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 260000 \
    || defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 260000 \
    || defined(__TV_OS_VERSION_MIN_REQUIRED) && __TV_OS_VERSION_MIN_REQUIRED >= 260000 \
    || defined(__WATCH_OS_VERSION_MIN_REQUIRED) && __WATCH_OS_VERSION_MIN_REQUIRED >= 260000
#define LIBXML_API_AVAILABLE_MACOS26_IOS26_WATCHOS26_TVOS26 \
        __IOS_AVAILABLE(26.0) __OSX_AVAILABLE(26.0) __TVOS_AVAILABLE(26.0) __WATCHOS_AVAILABLE(26.0)
#else
#define LIBXML_API_AVAILABLE_MACOS26_IOS26_WATCHOS26_TVOS26
#endif

#else /* !defined(__APPLE__) */

#define LIBXML_API_AVAILABLE_MACOS13_IOS16_WATCHOS9_TVOS16
#define LIBXML_API_DEPRECATED_MACOS13_IOS16_WATCHOS9_TVOS16(libxml2_version)
#define LIBXML_HAS_ICU_PIVOT_BUFFER
#define LIBXML_HAS_XPATH_RESOURCE_LIMITS

#define LIBXML_API_AVAILABLE_MACOS14_IOS17_WATCHOS10_TVOS17

#define LIBXML_API_AVAILABLE_MACOS26_IOS26_WATCHOS26_TVOS26

#define LIBXML_API_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS
#undef LIBXML_HAS_DEPRECATED_MEMORY_ALLOCATION_FUNCTIONS

#endif /* defined(__APPLE__) */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif


