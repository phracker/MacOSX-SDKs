/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2000-2004 CollabNet.  All rights reserved.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at http://subversion.tigris.org/license-1.html.
 * If newer versions of this license are posted there, you may use a
 * newer version instead, at your option.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://subversion.tigris.org/.
 * ====================================================================
 * @endcopyright
 *
 * @file svn_subst.h
 * @brief Data substitution (keywords and EOL style)
 */



#ifndef SVN_SUBST_H
#define SVN_SUBST_H

#include "svn_types.h"
#include "svn_string.h"
#include "svn_io.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* EOL conversion and keyword expansion. */

/** Valid states for 'svn:eol-style' property.
 *
 * Property nonexistence is equivalent to 'none'.
 */
typedef enum svn_subst_eol_style
{
  /** An unrecognized style */
  svn_subst_eol_style_unknown,

  /** EOL translation is "off" or ignored value */
  svn_subst_eol_style_none,

  /** Translation is set to client's native eol */
  svn_subst_eol_style_native,

  /** Translation is set to one of LF, CR, CRLF */
  svn_subst_eol_style_fixed

} svn_subst_eol_style_t;

/** Set @a *style to the appropriate @c svn_subst_eol_style_t and @a *eol to
 * the appropriate cstring for a given svn:eol-style property value.
 *
 * Set @a *eol to
 *
 *    - @c NULL for @c svn_subst_eol_style_none, or
 *
 *    - a null-terminated C string containing the native eol marker
 *      for this platform, for @c svn_subst_eol_style_native, or
 *
 *    - a null-terminated C string containing the eol marker indicated
 *      by the property value, for @c svn_subst_eol_style_fixed.
 *
 * If @a *style is NULL, it is ignored.
 */
void
svn_subst_eol_style_from_value(svn_subst_eol_style_t *style,
                               const char **eol,
                               const char *value);

/** Indicates whether the working copy and normalized versions of a file
 * with the given the parameters differ.  If @a force_eol_check is true,
 * the routine also accounts for all translations required due to repairing
 * fixed eol styles.
 *
 * @since New in 1.4
 *
 */
svn_boolean_t
svn_subst_translation_required(svn_subst_eol_style_t style,
                               const char *eol,
                               apr_hash_t *keywords,
                               svn_boolean_t special,
                               svn_boolean_t force_eol_check);


/** Values used in keyword expansion.
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 */
typedef struct svn_subst_keywords_t
{
  /**
   * @name svn_subst_keywords_t fields
   * String expansion of the like-named keyword, or NULL if the keyword
   * was not selected in the svn:keywords property.
   * @{
   */
  const svn_string_t *revision;
  const svn_string_t *date;
  const svn_string_t *author;
  const svn_string_t *url;
  const svn_string_t *id;
  /** @} */
} svn_subst_keywords_t;


/**
 * Set @a *kw to a new keywords hash filled with the appropriate contents
 * given a @a keywords_string (the contents of the svn:keywords
 * property for the file in question), the revision @a rev, the @a url, 
 * the @a date the file was committed on, and the @a author of the last 
 * commit.  Any of these can be @c NULL to indicate that the information is
 * not present, or @c 0 for @a date.
 *
 * Hash keys are of type <tt>const char *</tt>.
 * Hash values are of type <tt>svn_string_t *</tt>.
 * 
 * All memory is allocated out of @a pool.
 *
 * @since New in 1.3.
 */
svn_error_t *
svn_subst_build_keywords2(apr_hash_t **kw,
                          const char *keywords_string,
                          const char *rev,
                          const char *url,
                          apr_time_t date,
                          const char *author,
                          apr_pool_t *pool);

/** Similar to svn_subst_build_keywords2() except that it populates
 * an existing structure @a *kw instead of creating a keywords hash.
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 */
svn_error_t *
svn_subst_build_keywords(svn_subst_keywords_t *kw,
                         const char *keywords_string,
                         const char *rev,
                         const char *url,
                         apr_time_t date,
                         const char *author,
                         apr_pool_t *pool);


/** Return @c TRUE if @a a and @a b do not hold the same keywords.
 *
 * @a a and @a b are hashes of the form produced by
 * svn_subst_build_keywords2().
 *
 * @since New in 1.3.
 *
 * If @a compare_values is @c TRUE, "same" means that the @a a and @a b 
 * contain exactly the same set of keywords, and the values of corresponding
 * keywords match as well.  Else if @a compare_values is @c FALSE, then
 * "same" merely means that @a a and @a b hold the same set of keywords,
 * although those keywords' values might differ.
 *
 * @a a and/or @a b may be @c NULL; for purposes of comparison, @c NULL is
 * equivalent to holding no keywords.
 */
svn_boolean_t 
svn_subst_keywords_differ2(apr_hash_t *a,
                           apr_hash_t *b,
                           svn_boolean_t compare_values,
                           apr_pool_t *pool);

/** Similar to svn_subst_keywords_differ2() except that it compares
 * two @c svn_subst_keywords_t structs instead of keyword hashes.
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 */
svn_boolean_t 
svn_subst_keywords_differ(const svn_subst_keywords_t *a,
                          const svn_subst_keywords_t *b,
                          svn_boolean_t compare_values);


/** 
 * Copy and translate the data in stream @a src into stream @a dst.  It is
 * assumed that @a src is a readable stream and @a dst is a writable stream.
 *
 * @since New in 1.3.
 *
 * If @a eol_str is non-@c NULL, replace whatever bytestring @a src uses to
 * denote line endings with @a eol_str in the output.  If @a src has an
 * inconsistent line ending style, then: if @a repair is @c FALSE, return
 * @c SVN_ERR_IO_INCONSISTENT_EOL, else if @a repair is @c TRUE, convert any
 * line ending in @a src to @a eol_str in @a dst.  Recognized line endings are:
 * "\n", "\r", and "\r\n".
 *
 * Expand and contract keywords using the contents of @a keywords as the
 * new values.  If @a expand is @c TRUE, expand contracted keywords and
 * re-expand expanded keywords.  If @a expand is @c FALSE, contract expanded
 * keywords and ignore contracted ones.  Keywords not found in the hash are
 * ignored (not contracted or expanded).  If the @a keywords hash
 * itself is @c NULL, keyword substitution will be altogether ignored.
 *
 * Detect only keywords that are no longer than @c SVN_IO_MAX_KEYWORD_LEN
 * bytes, including the delimiters and the keyword itself.
 *
 * Note that a translation request is *required*:  one of @a eol_str or
 * @a keywords must be non-@c NULL.
 *
 * Recommendation: if @a expand is false, then you don't care about the
 * keyword values, so use empty strings as non-null signifiers when you
 * build the keywords hash.
 *
 * Notes: 
 *
 * See svn_wc__get_keywords() and svn_wc__get_eol_style() for a
 * convenient way to get @a eol_str and @a keywords if in libsvn_wc.
 */
svn_error_t *
svn_subst_translate_stream3(svn_stream_t *src,
                            svn_stream_t *dst,
                            const char *eol_str,
                            svn_boolean_t repair,
                            apr_hash_t *keywords,
                            svn_boolean_t expand,
                            apr_pool_t *pool);

/** Return a stream which performs eol translation and keyword
 * expansion when read from or written to.  The stream @a stream
 * is used to read and write all data.  Make sure you call
 * svn_stream_close() on @a stream to make sure all data are flushed
 * and cleaned up.
 *
 * Read operations from and write operations to the stream
 * perform the same operation: if @a expand is @c FALSE, both
 * contract keywords.  One stream supports both read and write
 * operations.  Reads and writes may be mixed.
 *
 * The stream returned is allocated in @a pool.
 *
 * @since New in 1.4.
 */
svn_stream_t *
svn_subst_stream_translated(svn_stream_t *stream,
                            const char *eol_str,
                            svn_boolean_t repair,
                            apr_hash_t *keywords,
                            svn_boolean_t expand,
                            apr_pool_t *pool);

/** Similar to svn_subst_translate_stream3() except relies upon a
 * @c svn_subst_keywords_t struct instead of a hash for the keywords.
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 */
svn_error_t *
svn_subst_translate_stream2(svn_stream_t *src,
                            svn_stream_t *dst,
                            const char *eol_str,
                            svn_boolean_t repair,
                            const svn_subst_keywords_t *keywords,
                            svn_boolean_t expand,
                            apr_pool_t *pool);


/**
 * Same as svn_subst_translate_stream2(), but does not take a @a pool
 * argument, instead creates a temporary subpool of the global pool, and
 * destroys it before returning.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *
svn_subst_translate_stream(svn_stream_t *src,
                           svn_stream_t *dst,
                           const char *eol_str,
                           svn_boolean_t repair,
                           const svn_subst_keywords_t *keywords,
                           svn_boolean_t expand);


/**
 * Translates the file at path @a src into a file at path @a dst.  The
 * parameters @a *eol_str, @a repair, @a *keywords and @a expand are
 * defined the same as in svn_subst_translate_stream3().
 *
 * In addition, it will create a special file from normal form or
 * translate one to normal form if @a special is @c TRUE.
 *
 * Copy the contents of file-path @a src to file-path @a dst atomically,
 * either creating @a dst (or overwriting @a dst if it exists), possibly
 * performing line ending and keyword translations.
 *
 * If anything goes wrong during the copy, attempt to delete @a dst (if
 * it exists).
 *
 * If @a eol_str and @a keywords are @c NULL, behavior is just a byte-for-byte
 * copy.
 *
 * @since New in 1.3.
 */
svn_error_t *
svn_subst_copy_and_translate3(const char *src,
                              const char *dst,
                              const char *eol_str,
                              svn_boolean_t repair,
                              apr_hash_t *keywords,
                              svn_boolean_t expand,
                              svn_boolean_t special,
                              apr_pool_t *pool);

/**
 * Similar to svn_subst_copy_and_translate3() except that @a keywords is a
 * @c svn_subst_keywords_t struct instead of a keywords hash.
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 * @since New in 1.1.
 */
svn_error_t *
svn_subst_copy_and_translate2(const char *src,
                              const char *dst,
                              const char *eol_str,
                              svn_boolean_t repair,
                              const svn_subst_keywords_t *keywords,
                              svn_boolean_t expand,
                              svn_boolean_t special,
                              apr_pool_t *pool);

/**
 * Similar to svn_subst_copy_and_translate2() except that @a special is
 * always set to @c FALSE.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *
svn_subst_copy_and_translate(const char *src,
                             const char *dst,
                             const char *eol_str,
                             svn_boolean_t repair,
                             const svn_subst_keywords_t *keywords,
                             svn_boolean_t expand,
                             apr_pool_t *pool);


/**
 * Convenience routine: a variant of svn_subst_translate_stream3() which
 * operates on cstrings.
 *
 * @since New in 1.3.
 *
 * Return a new string in @a *dst, allocated in @a pool, by copying the
 * contents of string @a src, possibly performing line ending and keyword
 * translations.
 *
 * If @a eol_str and @a keywords are @c NULL, behavior is just a byte-for-byte
 * copy.
 */
svn_error_t *
svn_subst_translate_cstring2(const char *src,
                             const char **dst,
                             const char *eol_str,
                             svn_boolean_t repair,
                             apr_hash_t *keywords,
                             svn_boolean_t expand,
                             apr_pool_t *pool);

/**
 * Similar to svn_subst_translate_cstring2() except that @a keywords is a
 * @c svn_subst_keywords_t struct instead of a keywords hash.
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 */
svn_error_t *
svn_subst_translate_cstring(const char *src,
                            const char **dst,
                            const char *eol_str,
                            svn_boolean_t repair,
                            const svn_subst_keywords_t *keywords,
                            svn_boolean_t expand,
                            apr_pool_t *pool);

/**
 * Translates a file @a src in working copy form to a file @a dst in
 * normal form.
 *
 * The values specified for @a eol_style, @a *eol_str, @a keywords and
 * @a special, should be the ones used to translate the file to its
 * working copy form.  Usually, these are the values specified by the
 * user in the files' properties.
 *
 * Inconsistent line endings in the file will be automatically repaired
 * (made consistent) for some eol styles.  For all others, an error is
 * returned.  By setting @a always_repair_eols to @c TRUE, eols will be
 * made consistent even for those styles which don't have it by default.
 *
 * @note To translate a file FROM normal form, use
 *       svn_subst_copy_and_translate3().
 *
 * @since New in 1.4
 *
 */
svn_error_t *
svn_subst_translate_to_normal_form(const char *src,
                                   const char *dst,
                                   svn_subst_eol_style_t eol_style,
                                   const char *eol_str,
                                   svn_boolean_t always_repair_eols,
                                   apr_hash_t *keywords,
                                   svn_boolean_t special,
                                   apr_pool_t *pool);

/**
 * Set @a *stream_p to a stream that detranslates the file @a src from
 * working copy form to normal form, allocated in @a pool.
 *
 * The values specified for @a eol_style, @a *eol_str, @a keywords and
 * @a special, should be the ones used to translate the file to its
 * working copy form.  Usually, these are the values specified by the
 * user in the files' properties.
 *
 * Inconsistent line endings in the file will be automatically repaired
 * (made consistent) for some eol styles.  For all others, an error is
 * returned.  By setting @a always_repair_eols to @c TRUE, eols will be
 * made consistent even for those styles which don't have it by default.
 *
 * @since New in 1.4.
 *
 */
svn_error_t *
svn_subst_stream_detranslated(svn_stream_t **stream_p, 
                              const char *src,
                              svn_subst_eol_style_t eol_style,
                              const char *eol_str,
                              svn_boolean_t always_repair_eols,
                              apr_hash_t *keywords,
                              svn_boolean_t special,
                              apr_pool_t *pool);


/* EOL conversion and character encodings */

/** Translate the data in @a value (assumed to be in encoded in charset
 * @a encoding) to UTF8 and LF line-endings.  If @a encoding is @c NULL, 
 * then assume that @a value is in the system-default language encoding.
 * Return the translated data in @a *new_value, allocated in @a pool.  
 */
svn_error_t *svn_subst_translate_string(svn_string_t **new_value,
                                        const svn_string_t *value,
                                        const char *encoding,
                                        apr_pool_t *pool);

/** Translate the data in @a value from UTF8 and LF line-endings into
 * native locale and native line-endings, or to the output locale if
 * @a for_output is TRUE.  Return the translated data in @a
 * *new_value, allocated in @a pool.
 */
svn_error_t *svn_subst_detranslate_string(svn_string_t **new_value,
                                          const svn_string_t *value,
                                          svn_boolean_t for_stdout,
                                          apr_pool_t *pool);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_SUBST_H */
