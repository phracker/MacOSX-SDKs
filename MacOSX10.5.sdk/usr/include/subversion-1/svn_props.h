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
 * @file svn_props.h
 * @brief Subversion properties
 */

/* ==================================================================== */

#ifndef SVN_PROPS_H
#define SVN_PROPS_H

#include <apr_pools.h>
#include <apr_tables.h>

#include "svn_string.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




/** A general in-memory representation of a single property.  Most of
 * the time, property lists will be stored completely in hashes.  But
 * sometimes it's useful to have an "ordered" collection of
 * properties, in which case we use an array of these structures.
 *
 * Also: sometimes we want a list that represents a set of property
 * *changes*, and in this case, an @c apr_hash_t won't work -- there's no
 * way to represent a property deletion, because we can't store a @c NULL
 * value in a hash.  So instead, we use these structures.
 */
typedef struct svn_prop_t
{
  const char *name;           /**< Property name */
  const svn_string_t *value;  /**< Property value */
} svn_prop_t;


/**
 * Return a duplicate of @a prop, allocated in @a pool. No part of the new
 * structure will be shared with @a prop.
 *
 * @since New in 1.3.
 */
svn_prop_t *svn_prop_dup(const svn_prop_t *prop, apr_pool_t *pool);


/**
 * Duplicate an @a array of svn_prop_t items using @a pool.
 *
 * @since New in 1.3.
 */
apr_array_header_t *
svn_prop_array_dup(const apr_array_header_t *array, apr_pool_t *pool);


/**
 * Subversion distinguishes among several kinds of properties,
 * particularly on the client-side.  There is no "unknown" kind; if
 * there's nothing special about a property name, the default category
 * is @c svn_prop_regular_kind.
 */ 
typedef enum svn_prop_kind
{
  /** In .svn/entries, i.e., author, date, etc. */
  svn_prop_entry_kind,

  /** Client-side only, stored by specific RA layer. */
  svn_prop_wc_kind,

  /** Seen if user does "svn proplist"; note that this includes some "svn:" 
   * props and all user props, i.e. ones stored in the repository fs.
   */
  svn_prop_regular_kind 
} svn_prop_kind_t;

/** Return the prop kind of a property named @a name, and (if @a prefix_len
 * is non-@c NULL) set @a *prefix_len to the length of the prefix of @a name
 * that was sufficient to distinguish its kind.
 */
svn_prop_kind_t svn_property_kind(int *prefix_len,
                                  const char *prop_name);


/** Return @c TRUE iff @a prop_name represents the name of a Subversion
 * property.
 */
svn_boolean_t svn_prop_is_svn_prop(const char *prop_name);


/** If @a propname requires that its value be stored as UTF8/LF in the
 * repository, then return @c TRUE.  Else return @c FALSE.  This is for
 * users of libsvn_client or libsvn_fs, since it their responsibility
 * to do this translation in both directions.  (See
 * svn_subst_translate_string()/svn_subst_detranslate_string() for
 * help with this task.)
 */
svn_boolean_t svn_prop_needs_translation(const char *propname);


/** Given a @a proplist array of @c svn_prop_t structures, allocate
 * three new arrays in @a pool.  Categorize each property and then
 * create new @c svn_prop_t structures in the proper lists.  Each new
 * @c svn_prop_t structure's fields will point to the same data within
 * @a proplist's structures.
 *
 * Callers may pass NULL for each of the property lists in which they
 * are uninterested.  If no props exist in a certain category, and the
 * property list argument for that category is non-NULL, then that
 * array will come back with <tt>->nelts == 0</tt>.
 *
 * ### Hmmm, maybe a better future interface is to return an array of
 *     arrays, where the index into the array represents the index
 *     into @c svn_prop_kind_t.  That way we can add more prop kinds
 *     in the future without changing this interface... 
 */
svn_error_t *svn_categorize_props(const apr_array_header_t *proplist,
                                  apr_array_header_t **entry_props,
                                  apr_array_header_t **wc_props,
                                  apr_array_header_t **regular_props,
                                  apr_pool_t *pool);


/** Given two property hashes (<tt>const char *name</tt> -> <tt>const 
 * svn_string_t *value</tt>), deduce the differences between them (from 
 * @a source_props -> @c target_props).  Return these changes as a series of 
 * @c svn_prop_t structures stored in @a propdiffs, allocated from @a pool.
 *
 * For note, here's a quick little table describing the logic of this
 * routine:
 *
 *<pre> basehash        localhash         event
 * --------        ---------         -----
 * value = foo     value = NULL      Deletion occurred.
 * value = foo     value = bar       Set occurred (modification)
 * value = NULL    value = baz       Set occurred (creation)</pre>
 */
svn_error_t *svn_prop_diffs(apr_array_header_t **propdiffs,
                            apr_hash_t *target_props,
                            apr_hash_t *source_props,
                            apr_pool_t *pool);



/* Defines for reserved ("svn:") property names.  */

/** All Subversion property names start with this. */
#define SVN_PROP_PREFIX "svn:"


/** Visible properties
 *
 * These are regular properties that are attached to ordinary files
 * and dirs, and are visible (and tweakable) by svn client programs
 * and users.  Adding these properties causes specific effects.
 *
 * @note the values of these properties are always UTF8-encoded with
 * LF line-endings.  It is the burden of svn library users to enforce
 * this.  Use svn_prop_needs_translation() to discover if a
 * certain property needs translation, and you can use
 * svn_subst_translate_string()/svn_subst_detranslate_string() 
 * to do the translation.
 *
 * @defgroup svn_prop_visible_props Visible properties
 * @{
 */

/** The mime-type of a given file. */
#define SVN_PROP_MIME_TYPE  SVN_PROP_PREFIX "mime-type"

/** The ignore patterns for a given directory. */
#define SVN_PROP_IGNORE  SVN_PROP_PREFIX "ignore"

/** The line ending style for a given file. */
#define SVN_PROP_EOL_STYLE  SVN_PROP_PREFIX "eol-style"

/** The "activated" keywords (for keyword substitution) for a given file. */
#define SVN_PROP_KEYWORDS  SVN_PROP_PREFIX "keywords"

/** Set to either TRUE or FALSE if we want a file to be executable or not. */
#define SVN_PROP_EXECUTABLE  SVN_PROP_PREFIX "executable"

/** The value to force the executable property to when set */
#define SVN_PROP_EXECUTABLE_VALUE "*"

/** Set to TRUE ('*') if we want a file to be set to read-only when
 * not locked.  FALSE is indicated by deleting the property. */
#define SVN_PROP_NEEDS_LOCK  SVN_PROP_PREFIX "needs-lock"

/** The value to force the needs-lock property to when set */
#define SVN_PROP_NEEDS_LOCK_VALUE "*"

/** Set if the file should be treated as a special file. */
#define SVN_PROP_SPECIAL  SVN_PROP_PREFIX "special"

/** The value to force the special property to when set. */
#define SVN_PROP_SPECIAL_VALUE "*"

/** Describes external items to check out into this directory. 
 *
 * The format is a series of lines, such as:
 *
 *<pre>   localdir1           http://url.for.external.source/etc/
 *   localdir1/foo       http://url.for.external.source/foo
 *   localdir1/bar       http://blah.blah.blah/repositories/theirproj
 *   localdir1/bar/baz   http://blorg.blorg.blorg/basement/code
 *   localdir2           http://another.url/blah/blah/blah
 *   localdir3           http://and.so.on/and/so/forth</pre>
 *
 * The subdir names on the left side are relative to the directory on
 * which this property is set.
 */
#define SVN_PROP_EXTERNALS  SVN_PROP_PREFIX "externals"

/** @} */

/** WC props are props that are invisible to users:  they're generated
 * by an RA layer, and stored in secret parts of .svn/.
 *
 * @defgroup svn_prop_invisible_props Invisible properties
 * @{
 */

/** The propname *prefix* that makes a propname a "WC property". 
 *
 * For example, ra_dav might store a versioned-resource url as a WC
 * prop like this:
 *
 *<pre>    name = svn:wc:dav_url
 *    val  = http://www.lyra.org/repos/452348/e.289</pre>
 *
 * The client will try to protect WC props by warning users against
 * changing them.  The client will also send them back to the RA layer
 * when committing.
 */
#define SVN_PROP_WC_PREFIX     SVN_PROP_PREFIX "wc:"

/** Another type of non-user-visible property.  "Entry properties" are
 * stored as fields with the administrative 'entries' file.  
 */
#define SVN_PROP_ENTRY_PREFIX  SVN_PROP_PREFIX "entry:"

/** The revision this entry was last committed to on. */
#define SVN_PROP_ENTRY_COMMITTED_REV     SVN_PROP_ENTRY_PREFIX "committed-rev"

/** The date this entry was last committed to on. */
#define SVN_PROP_ENTRY_COMMITTED_DATE    SVN_PROP_ENTRY_PREFIX "committed-date"

/** The author who last committed to this entry. */
#define SVN_PROP_ENTRY_LAST_AUTHOR       SVN_PROP_ENTRY_PREFIX "last-author"

/** The UUID of this entry's repository. */
#define SVN_PROP_ENTRY_UUID       SVN_PROP_ENTRY_PREFIX "uuid"

/** The lock token for this entry.
 * @since New in 1.2. */
#define SVN_PROP_ENTRY_LOCK_TOKEN SVN_PROP_ENTRY_PREFIX "lock-token"

/** When custom, user-defined properties are passed over the wire, they will
 * have this prefix added to their name.
 */
#define SVN_PROP_CUSTOM_PREFIX SVN_PROP_PREFIX "custom:"

/** @} */

/**
 * These are reserved properties attached to a "revision" object in
 * the repository filesystem.  They can be queried by using
 * svn_fs_revision_prop().  They are invisible to svn clients.
 *
 * @defgroup svn_props_revision_props Revision properties
 * @{
 */

/** The fs revision property that stores a commit's author. */
#define SVN_PROP_REVISION_AUTHOR  SVN_PROP_PREFIX "author"

/** The fs revision property that stores a commit's log message. */
#define SVN_PROP_REVISION_LOG  SVN_PROP_PREFIX "log"

/** The fs revision property that stores a commit's date. */
#define SVN_PROP_REVISION_DATE  SVN_PROP_PREFIX "date"

/** The fs revision property that stores a commit's "original" date.
 *
 * The svn:date property must be monotonically increasing, along with
 * the revision number. In certain scenarios, this may pose a problem
 * when the revision represents a commit that occurred at a time which
 * does not fit within the sequencing required for svn:date. This can
 * happen, for instance, when the revision represents a commit to a
 * foreign version control system, or possibly when two Subversion
 * repositories are combined. This property can be used to record the
 * true, original date of the commit.
 */
#define SVN_PROP_REVISION_ORIG_DATE  SVN_PROP_PREFIX "original-date"

/** The presence of this fs revision property indicates that the
 * revision was automatically generated by the mod_dav_svn
 * autoversioning feature.  The value is irrelevant.
 */
#define SVN_PROP_REVISION_AUTOVERSIONED  SVN_PROP_PREFIX "autoversioned"


/* More reserved revision props in the 'svn:' namespace, used by the
   svnsync tool:   */

/** Prefix for all svnsync custom properties. */
#define SVNSYNC_PROP_PREFIX             SVN_PROP_PREFIX "sync-"

/* The following revision properties are set on revision 0 of
 * destination repositories by svnsync:
 */

/** Used to enforce mutually exclusive destination repository access. */
#define SVNSYNC_PROP_LOCK               SVNSYNC_PROP_PREFIX "lock"

/** Identifies the repository's source URL. */
#define SVNSYNC_PROP_FROM_URL           SVNSYNC_PROP_PREFIX "from-url"
/** Identifies the repository's source UUID. */
#define SVNSYNC_PROP_FROM_UUID          SVNSYNC_PROP_PREFIX "from-uuid"

/** Identifies the last completely mirrored revision. */
#define SVNSYNC_PROP_LAST_MERGED_REV    SVNSYNC_PROP_PREFIX "last-merged-rev"

/** Identifies the revision currently being copied. */
#define SVNSYNC_PROP_CURRENTLY_COPYING  SVNSYNC_PROP_PREFIX "currently-copying"


/**
 * This is a list of all revision properties.
 */ 
#define SVN_PROP_REVISION_ALL_PROPS SVN_PROP_REVISION_AUTHOR, \
                                    SVN_PROP_REVISION_LOG, \
                                    SVN_PROP_REVISION_DATE, \
                                    SVN_PROP_REVISION_AUTOVERSIONED, \
                                    SVN_PROP_REVISION_ORIG_DATE, \
                                    SVNSYNC_PROP_LOCK, \
                                    SVNSYNC_PROP_FROM_URL, \
                                    SVNSYNC_PROP_FROM_UUID, \
                                    SVNSYNC_PROP_LAST_MERGED_REV, \
                                    SVNSYNC_PROP_CURRENTLY_COPYING,

/** @} */



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_PROPS_H */
