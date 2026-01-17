/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2000-2006 CollabNet.  All rights reserved.
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
 * @file svn_wc.h
 * @brief The Subversion Working Copy Library
 *
 * Requires:  
 *            - A working copy
 * 
 * Provides: 
 *            - Ability to manipulate working copy's versioned data.
 *            - Ability to manipulate working copy's administrative files.
 *
 * Used By:   
 *            - Clients.
 */

#ifndef SVN_WC_H
#define SVN_WC_H


#include <apr.h>
#include <apr_pools.h>
#include <apr_tables.h>
#include <apr_hash.h>

#include "svn_types.h"
#include "svn_string.h"
#include "svn_delta.h"
#include "svn_error.h"
#include "svn_opt.h"
#include "svn_ra.h"    /* for svn_ra_reporter_t type */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * Get libsvn_wc version information.
 *
 * @since New in 1.1.
 */
const svn_version_t *svn_wc_version(void);

/** Flags for use with svn_wc_translated_file2
 *
 * @defgroup translate_flags Translation flags
 *
 * @{
 */

  /** Translate from Normal Form.
   *
   * The working copy text bases and repository files are stored
   * in normal form.  Some files' contents - or ever representation -
   * differs between the working copy and the normal form.  This flag
   * specifies to take the latter form as input and transform it
   * to the former.
   *
   * Either this flag or @c SVN_WC_TRANSLATE_TO_NF should be specified,
   * but not both.
   */
#define SVN_WC_TRANSLATE_FROM_NF                 0x00000000

  /** Translate to Normal Form.
   *
   * Either this flag or @c SVN_WC_TRANSLATE_FROM_NF should be specified,
   * but not both.
   */
#define SVN_WC_TRANSLATE_TO_NF                   0x00000001

  /** Force repair of eol styles, making sure the output file consistently
   * contains the one eol style as specified by the svn:eol-style
   * property and the required translation direction.
   *
   */
#define SVN_WC_TRANSLATE_FORCE_EOL_REPAIR        0x00000002

  /** Don't register a pool cleanup to delete the output file */
#define SVN_WC_TRANSLATE_NO_OUTPUT_CLEANUP       0x00000004

  /** Guarantee a new file is created on successful return.
   * The default shortcuts translation by returning the path
   * of the untranslated file when no translation is required.
   */
#define SVN_WC_TRANSLATE_FORCE_COPY              0x00000008

  /** Use a non-wc-local tmp directory for creating output files,
   * instead of in the working copy admin tmp area which is the default.
   *
   * @since New in 1.4.
   */
#define SVN_WC_TRANSLATE_USE_GLOBAL_TMP          0x00000010

/** @} */


/* Locking/Opening/Closing */

/** Baton for access to a working copy administrative area.
 *
 * One day all such access will require a baton, we're not there yet.
 *
 * Access batons can be grouped into sets, by passing an existing open
 * baton when opening a new baton.  Given one baton in a set, other batons
 * may be retrieved.  This allows an entire hierarchy to be locked, and
 * then the set of batons can be passed around by passing a single baton.
 */
typedef struct svn_wc_adm_access_t svn_wc_adm_access_t;


/**
 * Return, in @a *adm_access, a pointer to a new access baton for the working
 * copy administrative area associated with the directory @a path.  If
 * @a write_lock is true the baton will include a write lock, otherwise the
 * baton can only be used for read access.  If @a path refers to a directory
 * that is already write locked then the error @c SVN_ERR_WC_LOCKED will be
 * returned.  The error @c SVN_ERR_WC_NOT_DIRECTORY will be returned if
 * @a path is not a versioned directory.
 *
 * If @a associated is an open access baton then @a adm_access will be added 
 * to the set containing @a associated.  @a associated can be @c NULL, in 
 * which case @a adm_access is the start of a new set.
 *
 * @a depth specifies how much to lock.  Zero means just the specified
 * directory.  Any negative value means to lock the entire working copy
 * directory hierarchy under @a path.  A positive value indicates the number of
 * levels of directories to lock -- 1 means just immediate subdirectories, 2
 * means immediate subdirectories and their subdirectories, etc.  All the
 * access batons will become part of the set containing @a adm_access.  This
 * is an all-or-nothing option, if it is not possible to lock all the
 * requested directories then an error will be returned and @a adm_access will
 * be invalid, with the exception that subdirectories of @a path that are
 * missing from the physical filesystem will not be locked and will not cause
 * an error.  The error @c SVN_ERR_WC_LOCKED will be returned if a
 * subdirectory of @a path is already write locked.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton to determine
 * if the client has cancelled the operation.
 *
 * @a pool will be used to allocate memory for the baton and any subsequently
 * cached items.  If @a adm_access has not been closed when the pool is
 * cleared, it will be closed automatically at that point, and removed from
 * its set.  A baton closed in this way will not remove physical locks from
 * the working copy if cleanup is required.
 *
 * The first baton in a set, with @a associated passed as @c NULL, must have 
 * the longest lifetime of all the batons in the set.  This implies it must be
 * the root of the hierarchy.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_adm_open3(svn_wc_adm_access_t **adm_access,
                              svn_wc_adm_access_t *associated,
                              const char *path,
                              svn_boolean_t write_lock,
                              int depth,
                              svn_cancel_func_t cancel_func,
                              void *cancel_baton,
                              apr_pool_t *pool);

/**
 * Similar to svn_wc_adm_open3(), but without cancellation support.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_adm_open2(svn_wc_adm_access_t **adm_access,
                              svn_wc_adm_access_t *associated,
                              const char *path,
                              svn_boolean_t write_lock,
                              int depth,
                              apr_pool_t *pool);

/**
 * Similar to svn_wc_adm_open2(), but with @a tree_lock instead of
 * @a depth.  @a depth is set to -1 if @a tree_lock is @c TRUE, else 0.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_wc_adm_open(svn_wc_adm_access_t **adm_access,
                             svn_wc_adm_access_t *associated,
                             const char *path,
                             svn_boolean_t write_lock,
                             svn_boolean_t tree_lock,
                             apr_pool_t *pool);

/**
 * Checks the working copy to determine the node type of @a path.  If 
 * @a path is a versioned directory then the behaviour is like that of
 * svn_wc_adm_open3(), otherwise, if @a path is a file or does not
 * exist, then the behaviour is like that of svn_wc_adm_open3() with
 * @a path replaced by the parent directory of @a path.  If @a path is
 * an unversioned directory, the behaviour is also like that of
 * svn_wc_adm_open3() on the parent, except that if the open fails,
 * then the returned SVN_ERR_WC_NOT_DIRECTORY error refers to @a path,
 * not to @a path's parent.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_adm_probe_open3(svn_wc_adm_access_t **adm_access,
                                    svn_wc_adm_access_t *associated,
                                    const char *path,
                                    svn_boolean_t write_lock,
                                    int depth,
                                    svn_cancel_func_t cancel_func,
                                    void *cancel_baton,
                                    apr_pool_t *pool);

/**
 * Similar to svn_wc_adm_probe_open3() without the cancel
 * functionality.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_adm_probe_open2(svn_wc_adm_access_t **adm_access,
                                    svn_wc_adm_access_t *associated,
                                    const char *path,
                                    svn_boolean_t write_lock,
                                    int depth,
                                    apr_pool_t *pool);

/**
 * Similar to svn_wc_adm_probe_open2(), but with @a tree_lock instead of
 * @a depth.  @a depth is set to -1 if @a tree_lock is @c TRUE, else 0.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_wc_adm_probe_open(svn_wc_adm_access_t **adm_access,
                                   svn_wc_adm_access_t *associated,
                                   const char *path,
                                   svn_boolean_t write_lock,
                                   svn_boolean_t tree_lock,
                                   apr_pool_t *pool);

/**
 * Open access batons for @a path and return in @a *anchor_access and
 * @a *target the anchor and target required to drive an editor.  Return
 * in @a *target_access the access baton for the target, which may be the
 * same as @a *anchor_access.  All the access batons will be in the
 * @a *anchor_access set.
 *
 * @a depth determines the depth used when opening @a path if @a path is a
 * versioned directory, @a depth is ignored otherwise.  If @a write_lock is
 * @c TRUE the access batons will hold write locks.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton to determine
 * if the client has cancelled the operation.
 *
 * This function is essentially a combination of svn_wc_adm_open3() and
 * svn_wc_get_actual_target(), with the emphasis on reducing physical IO.
 *
 * @since New in 1.2.
 */
svn_error_t *
svn_wc_adm_open_anchor(svn_wc_adm_access_t **anchor_access,
                       svn_wc_adm_access_t **target_access,
                       const char **target,
                       const char *path,
                       svn_boolean_t write_lock,
                       int depth,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       apr_pool_t *pool);

/** Return, in @a *adm_access, a pointer to an existing access baton associated
 * with @a path.  @a path must be a directory that is locked as part of the 
 * set containing the @a associated access baton.
 *
 * If the requested access baton is marked as missing in, or is simply
 * absent from, @a associated, return SVN_ERR_WC_NOT_LOCKED.
 *
 * @a pool is used only for local processing, it is not used for the batons.
 */
svn_error_t *svn_wc_adm_retrieve(svn_wc_adm_access_t **adm_access,
                                 svn_wc_adm_access_t *associated,
                                 const char *path,
                                 apr_pool_t *pool);

/** Check the working copy to determine the node type of @a path.  If
 * @a path is a versioned directory then the behaviour is like that of
 * svn_wc_adm_retrieve(), otherwise, if @a path is a file, an unversioned
 * directory, or does not exist, then the behaviour is like that of
 * svn_wc_adm_retrieve() with @a path replaced by the parent directory of
 * @a path.
 */
svn_error_t *svn_wc_adm_probe_retrieve(svn_wc_adm_access_t **adm_access,
                                       svn_wc_adm_access_t *associated,
                                       const char *path,
                                       apr_pool_t *pool);

/**
 * Try various ways to obtain an access baton for @a path.
 *
 * First, try to obtain @a *adm_access via svn_wc_adm_probe_retrieve(),
 * but if this fails because @a associated can't give a baton for
 * @a path or @a path's parent, then try svn_wc_adm_probe_open3(),
 * this time passing @a write_lock and @a depth.  If there is
 * still no access because @a path is not a versioned directory, then
 * just set @a *adm_access to null and return success.  But if it is
 * because @a path is locked, then return the error @c SVN_ERR_WC_LOCKED,
 * and the effect on @a *adm_access is undefined.  (Or if the attempt
 * fails for any other reason, return the corresponding error, and the
 * effect on @a *adm_access is also undefined.)
 *
 * If svn_wc_adm_probe_open3() succeeds, then add @a *adm_access to
 * @a associated.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton to determine
 * if the client has cancelled the operation.
 *
 * Use @a pool only for local processing, not to allocate @a *adm_access.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_adm_probe_try3(svn_wc_adm_access_t **adm_access,
                                   svn_wc_adm_access_t *associated,
                                   const char *path,
                                   svn_boolean_t write_lock,
                                   int depth,
                                   svn_cancel_func_t cancel_func,
                                   void *cancel_baton,
                                   apr_pool_t *pool);

/**
 * Similar to svn_wc_adm_probe_try3() without the cancel
 * functionality.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_adm_probe_try2(svn_wc_adm_access_t **adm_access,
                                   svn_wc_adm_access_t *associated,
                                   const char *path,
                                   svn_boolean_t write_lock,
                                   int depth,
                                   apr_pool_t *pool);

/**
 * Similar to svn_wc_adm_probe_try2(), but with @a tree_lock instead of
 * @a depth.  @a depth is set to -1 if @a tree_lock is @c TRUE, else 0.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_wc_adm_probe_try(svn_wc_adm_access_t **adm_access,
                                  svn_wc_adm_access_t *associated,
                                  const char *path,
                                  svn_boolean_t write_lock,
                                  svn_boolean_t tree_lock,
                                  apr_pool_t *pool);


/** Give up the access baton @a adm_access, and its lock if any. This will
 * recursively close any batons in the same set that are direct
 * subdirectories of @a adm_access.  Any physical locks will be removed from
 * the working copy.  Lock removal is unconditional, there is no check to
 * determine if cleanup is required.
 */
svn_error_t *svn_wc_adm_close(svn_wc_adm_access_t *adm_access);

/** Return the path used to open the access baton @a adm_access */
const char *svn_wc_adm_access_path(svn_wc_adm_access_t *adm_access);

/** Return the pool used by access baton @a adm_access */
apr_pool_t *svn_wc_adm_access_pool(svn_wc_adm_access_t *adm_access);

/** Return @c TRUE is the access baton @a adm_access has a write lock,
 * @c FALSE otherwise. Compared to svn_wc_locked() this is a cheap, fast
 * function that doesn't access the filesystem.
 */
svn_boolean_t svn_wc_adm_locked(svn_wc_adm_access_t *adm_access);

/** Set @a *locked to non-zero if @a path is locked, else set it to zero. */
svn_error_t *svn_wc_locked(svn_boolean_t *locked, 
                           const char *path,
                           apr_pool_t *pool);


/**
 * Return @c TRUE if @a name is the name of the WC administrative
 * directory.  Use @a pool for any temporary allocations.  Only works
 * with base directory names, not paths or URIs.
 *
 * For compatibility, the default name (.svn) will always be treated
 * as an admin dir name, even if the working copy is actually using an
 * alternative name.
 *
 * @since New in 1.3.
 */
svn_boolean_t svn_wc_is_adm_dir(const char *name, apr_pool_t *pool);


/**
 * Return the name of the administrative directory.
 * Use @a pool for any temporary allocations.
 *
 * The returned pointer will refer to either a statically allocated
 * string, or to a string allocated in @a pool.
 *
 * @since New in 1.3.
 */
const char *svn_wc_get_adm_dir(apr_pool_t *pool);


/**
 * Use @a name for the administrative directory in the working copy.
 * Use @a pool for any temporary allocations.
 *
 * The list of valid names is limited.  Currently only ".svn" (the
 * default) and "_svn" are allowed.
 *
 * @note This function changes global (per-process) state and must be
 * called in a single-threaded context during the initialization of a
 * Subversion client.
 *
 * @since New in 1.3.
 */
svn_error_t *svn_wc_set_adm_dir(const char *name, apr_pool_t *pool);



/** Traversal information is information gathered by a working copy
 * crawl or update.  For example, the before and after values of the
 * svn:externals property are important after an update, and since
 * we're traversing the working tree anyway (a complete traversal
 * during the initial crawl, and a traversal of changed paths during
 * the checkout/update/switch), it makes sense to gather the
 * property's values then instead of making a second pass.
 */
typedef struct svn_wc_traversal_info_t svn_wc_traversal_info_t;


/** Return a new, empty traversal info object, allocated in @a pool. */
svn_wc_traversal_info_t *svn_wc_init_traversal_info(apr_pool_t *pool);


/** Set @a *externals_old and @a *externals_new to hash tables representing
 * changes to values of the svn:externals property on directories
 * traversed by @a traversal_info.
 *
 * @a traversal_info is obtained from svn_wc_init_traversal_info(), but is
 * only useful after it has been passed through another function, such
 * as svn_wc_crawl_revisions(), svn_wc_get_update_editor(),
 * svn_wc_get_switch_editor(), etc.
 *
 * Each hash maps <tt>const char *</tt> directory names onto 
 * <tt>const char *</tt> values of the externals property for that directory.  
 * The dir names are full paths -- that is, anchor plus target, not target 
 * alone. The values are not parsed, they are simply copied raw, and are
 * never null: directories that acquired or lost the property are
 * simply omitted from the appropriate table.  Directories whose value
 * of the property did not change show the same value in each hash.
 *
 * The hashes, keys, and values have the same lifetime as @a traversal_info.
 */
void svn_wc_edited_externals(apr_hash_t **externals_old,
                             apr_hash_t **externals_new,
                             svn_wc_traversal_info_t *traversal_info);


/** One external item.  This usually represents one line from an
 * svn:externals description but with the path and URL
 * canonicalized.
 */
typedef struct svn_wc_external_item_t
{
  /** The name of the subdirectory into which this external should be
      checked out.  This is relative to the parent directory that
      holds this external item.  (Note that these structs are often
      stored in hash tables with the target dirs as keys, so this
      field will often be redundant.) */
  const char *target_dir;

  /** Where to check out from. */
  const char *url;

  /** What revision to check out.  The only valid kinds for this are
      svn_opt_revision_number, svn_opt_revision_date, and
      svn_opt_revision_head. */
  svn_opt_revision_t revision;

} svn_wc_external_item_t;


/**
 * Return a duplicate of @a item, allocated in @a pool.  No part of the new
 * item will be shared with @a item.
 *
 * @since New in 1.3.
 */
svn_wc_external_item_t *
svn_wc_external_item_dup(const svn_wc_external_item_t *item,
                         apr_pool_t *pool);


/**
 * If @a externals_p is non-null, set @a *externals_p to an array of
 * @c svn_wc_external_item_t * objects based on @a desc.
 *
 * If the format of @a desc is invalid, don't touch @a *externals_p and
 * return @c SVN_ERR_CLIENT_INVALID_EXTERNALS_DESCRIPTION.  Thus, if
 * you just want to check the validity of an externals description,
 * and don't care about the parsed result, pass null for @a externals_p.
 *
 * The format of @a desc is the same as for values of the directory
 * property @c SVN_PROP_EXTERNALS, which see.
 *
 * Allocate the table, keys, and values in @a pool.
 *
 * Use @a parent_directory only in constructing error strings.
 *
 * @since New in 1.1.
 */
svn_error_t *
svn_wc_parse_externals_description2(apr_array_header_t **externals_p,
                                    const char *parent_directory,
                                    const char *desc,
                                    apr_pool_t *pool);


/**
 * Similar to svn_wc_parse_externals_description2(), but returns the
 * parsed externals in a hash instead of an array.  This function
 * should not be used, as storing the externals in a hash causes their
 * order of evaluation to be not easily identifiable.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *
svn_wc_parse_externals_description(apr_hash_t **externals_p,
                                   const char *parent_directory,
                                   const char *desc,
                                   apr_pool_t *pool);



/* Notification/callback handling. */

/**
 * @defgroup svn_wc_notifications notification callback handling
 * @{
 *
 * In many cases, the WC library will scan a working copy and make
 * changes. The caller usually wants to know when each of these changes
 * has been made, so that it can display some kind of notification to
 * the user.
 *
 * These notifications have a standard callback function type, which
 * takes the path of the file that was affected, and a caller-
 * supplied baton.
 *
 * Note that the callback is a 'void' return -- this is a simple
 * reporting mechanism, rather than an opportunity for the caller to
 * alter the operation of the WC library.
 *
 * Note also that some of the actions are used across several
 * different Subversion commands.  For example, the update actions are
 * also used for checkouts, switches, and merges.
 */

/** The type of action occurring. */
typedef enum svn_wc_notify_action_t
{
  /** Adding a path to revision control. */
  svn_wc_notify_add = 0,

  /** Copying a versioned path. */
  svn_wc_notify_copy,
  
  /** Deleting a versioned path. */
  svn_wc_notify_delete,

  /** Restoring a missing path from the pristine text-base. */
  svn_wc_notify_restore,
  
  /** Reverting a modified path. */
  svn_wc_notify_revert,

  /** A revert operation has failed. */
  svn_wc_notify_failed_revert,

  /** Resolving a conflict. */
  svn_wc_notify_resolved,

  /** Skipping a path. */
  svn_wc_notify_skip,

  /** Got a delete in an update. */
  svn_wc_notify_update_delete,

  /** Got an add in an update. */
  svn_wc_notify_update_add,

  /** Got any other action in an update. */
  svn_wc_notify_update_update,

  /** The last notification in an update (including updates of externals). */
  svn_wc_notify_update_completed,

  /** Updating an external module. */
  svn_wc_notify_update_external,

  /** The last notification in a status (including status on externals). */
  svn_wc_notify_status_completed,

  /** Running status on an external module. */
  svn_wc_notify_status_external,

  /** Committing a modification. */
  svn_wc_notify_commit_modified,
  
  /** Committing an addition. */
  svn_wc_notify_commit_added,

  /** Committing a deletion. */
  svn_wc_notify_commit_deleted,

  /** Committing a replacement. */
  svn_wc_notify_commit_replaced,

  /** Transmitting post-fix text-delta data for a file. */
  svn_wc_notify_commit_postfix_txdelta,

  /** Processed a single revision's blame. */
  svn_wc_notify_blame_revision,

  /** Locking a path. @since New in 1.2. */
  svn_wc_notify_locked,

  /** Unlocking a path. @since New in 1.2. */
  svn_wc_notify_unlocked,

  /** Failed to lock a path. @since New in 1.2. */
  svn_wc_notify_failed_lock,

  /** Failed to unlock a path. @since New in 1.2. */
  svn_wc_notify_failed_unlock
} svn_wc_notify_action_t;


/** The type of notification that is occurring. */
typedef enum svn_wc_notify_state_t
{
  svn_wc_notify_state_inapplicable = 0,

  /** Notifier doesn't know or isn't saying. */
  svn_wc_notify_state_unknown,

  /** The state did not change. */
  svn_wc_notify_state_unchanged,

  /** The item wasn't present. */
  svn_wc_notify_state_missing,

  /** An unversioned item obstructed work. */
  svn_wc_notify_state_obstructed,

  /** Pristine state was modified. */
  svn_wc_notify_state_changed,

  /** Modified state had mods merged in. */
  svn_wc_notify_state_merged,

  /** Modified state got conflicting mods. */
  svn_wc_notify_state_conflicted

} svn_wc_notify_state_t;

/**
 * What happened to a lock during an operation.
 *
 * @since New in 1.2.
 */
typedef enum svn_wc_notify_lock_state_t {
  svn_wc_notify_lock_state_inapplicable = 0,
  svn_wc_notify_lock_state_unknown,
  /** The lock wasn't changed. */
  svn_wc_notify_lock_state_unchanged,
  /** The item was locked. */
  svn_wc_notify_lock_state_locked,
  /** The item was unlocked. */
  svn_wc_notify_lock_state_unlocked
} svn_wc_notify_lock_state_t;

/**
 * Structure used in the @c svn_wc_notify_func2_t function.
 *
 * @c path is either absolute or relative to the current working directory
 * (i.e., not relative to an anchor).  @c action describes what happened
 * to @c path.
 *
 * @c kind, @c content_state, @c prop_state and @c lock_state are from
 * after @c action, not before.  @c lock_state reflects the addition
 * or removal of a lock token in the working copy.
 *
 * If @c mime_type is non-null, it indicates the mime-type of @c path.
 * It is always @c NULL for directories.
 *
 * If @c action is @c svn_wc_notify_update_completed, @c revision is the
 * target revision of the update, or @c SVN_INVALID_REVNUM if not
 * available.  If @c action is @c svn_wc_notify_blame_revision, @c
 * revision is the processed revision.  In all other cases, @c
 * revision is @c SVN_INVALID_REVNUM.
 *
 * For an @c action of svn_wc_notify_locked, @c lock is the lock
 * structure received from the repository.  For other actions, it is
 * @c NULL.
 *
 * @c err is @c NULL, except when @c action is @c
 * svn_wc_notify_failed_lock or @c svn_wc_notify_failed_unlock, in
 * which case it points to an error describing the reason for the failure.
 *
 * Note that if @c action is @c svn_wc_notify_update, then @c path has 
 * already been installed, so it is legitimate for an implementation of
 * @c svn_wc_notify_func2_t to examine @c path in the working copy.
 *
 * @note The purpose of the @c kind, @c mime_type, @c content_state, and
 * @c prop_state fields is to provide "for free" information that an
 * implementation is likely to want, and which it would otherwise be
 * forced to deduce via expensive operations such as reading entries
 * and properties.  However, if the caller does not have this
 * information, it will simply pass the corresponding `*_unknown'
 * values, and it is up to the implementation how to handle that
 * (i.e., whether to attempt deduction, or just to punt and
 * give a less informative notification).
 *
 * @note Callers of notification functions should use svn_wc_create_notify()
 * to create structures of this type to allow for extensibility.
 *
 * @since New in 1.2.
 */
typedef struct svn_wc_notify_t {
  const char *path;
  svn_wc_notify_action_t action;
  svn_node_kind_t kind;
  const char *mime_type;
  const svn_lock_t *lock;
  svn_error_t *err;
  svn_wc_notify_state_t content_state;
  svn_wc_notify_state_t prop_state;
  svn_wc_notify_lock_state_t lock_state;
  svn_revnum_t revision;
  /* NOTE: Add new fields at the end to preserve binary compatibility.
     Also, if you add fields here, you have to update svn_wc_create_notify
     and svn_wc_dup_notify. */
} svn_wc_notify_t;

/**
 * Allocate an @c svn_wc_notify_t structure in @a pool, initialize and return
 * it.
 *
 * Set the @c path field of the created struct to @a path, and @c action to
 * @a action.  Set all other fields to their @c _unknown, @c NULL or
 * invalid value, respectively.
 *
 * @since New in 1.2.
 */
svn_wc_notify_t *
svn_wc_create_notify(const char *path, svn_wc_notify_action_t action,
                     apr_pool_t *pool);

/**
 * Return a deep copy of @a notify, allocated in @a pool.
 *
 * @since New in 1.2.
 */
svn_wc_notify_t *
svn_wc_dup_notify(const svn_wc_notify_t *notify, apr_pool_t *pool);

/**
 * Notify the world that @a notify->action has happened to @a notify->path.
 *
 * Recommendation: callers of @c svn_wc_notify_func2_t should avoid
 * invoking it multiple times on the same path within a given
 * operation, and implementations should not bother checking for such
 * duplicate calls.  For example, in an update, the caller should not
 * invoke the notify func on receiving a prop change and then again
 * on receiving a text change.  Instead, wait until all changes have
 * been received, and then invoke the notify func once (from within
 * an @c svn_delta_editor_t's close_file(), for example), passing 
 * the appropriate @a notify->content_state and @a notify->prop_state flags.
 *
 * @since New in 1.2.
 */
typedef void (*svn_wc_notify_func2_t)(void *baton,
                                      const svn_wc_notify_t *notify,
                                      apr_pool_t *pool);

/**
 * Similar to @c svn_wc_notify_func2_t, but takes the information as arguments
 * instead of struct fields.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
typedef void (*svn_wc_notify_func_t)(void *baton,
                                     const char *path,
                                     svn_wc_notify_action_t action,
                                     svn_node_kind_t kind,
                                     const char *mime_type,
                                     svn_wc_notify_state_t content_state,
                                     svn_wc_notify_state_t prop_state,
                                     svn_revnum_t revision);

/** @} */



/**
 * A callback vtable invoked by our diff-editors, as they receive
 * diffs from the server.  'svn diff' and 'svn merge' both implement
 * their own versions of this table.
 *
 * @since New in 1.2.
 */
typedef struct svn_wc_diff_callbacks2_t
{
  /** A file @a path has changed.  If @a tmpfile2 is non-null, the
   * contents have changed and those changes can be seen by comparing
   * @a tmpfile1 and @a tmpfile2, which represent @a rev1 and @a rev2 of 
   * the file, respectively.
   *
   * If known, the @c svn:mime-type value of each file is passed into
   * @a mimetype1 and @a mimetype2;  either or both of the values can
   * be NULL.  The implementor can use this information to decide if
   * (or how) to generate differences.
   *
   * @a propchanges is an array of (@c svn_prop_t) structures. If it has
   * any elements, the original list of properties is provided in
   * @a originalprops, which is a hash of @c svn_string_t values, keyed on the
   * property name.
   * 
   * @a adm_access will be an access baton for the directory containing 
   * @a path, or @c NULL if the diff editor is not using access batons.
   *
   * If @a contentstate is non-null, set @a *contentstate to the state of
   * the file contents after the operation has been performed.  The same
   * applies for @a propstate regarding the property changes.  (In
   * practice, this is only useful with merge, not diff; diff callbacks
   * will probably set @a *contentstate and @a *propstate to
   * @c svn_wc_notify_state_unknown, since they do not change the state and
   * therefore do not bother to know the state after the operation.)
   */
  svn_error_t *(*file_changed)(svn_wc_adm_access_t *adm_access,
                               svn_wc_notify_state_t *contentstate,
                               svn_wc_notify_state_t *propstate,
                               const char *path,
                               const char *tmpfile1,
                               const char *tmpfile2,
                               svn_revnum_t rev1,
                               svn_revnum_t rev2,
                               const char *mimetype1,
                               const char *mimetype2,
                               const apr_array_header_t *propchanges,
                               apr_hash_t *originalprops,
                               void *diff_baton);

  /** A file @a path was added.  The contents can be seen by comparing
   * @a tmpfile1 and @a tmpfile2, which represent @a rev1 and @a rev2
   * of the file, respectively.  (If either file is empty, the rev
   * will be 0.)
   *
   * If known, the @c svn:mime-type value of each file is passed into
   * @a mimetype1 and @a mimetype2;  either or both of the values can
   * be NULL.  The implementor can use this information to decide if
   * (or how) to generate differences.
   *
   * @a propchanges is an array of (@c svn_prop_t) structures.  If it contains
   * any elements, the original list of properties is provided in
   * @a originalprops, which is a hash of @c svn_string_t values, keyed on the
   * property name.
   * 
   * @a adm_access will be an access baton for the directory containing 
   * @a path, or @c NULL if the diff editor is not using access batons.
   *
   * If @a contentstate is non-null, set @a *contentstate to the state of the
   * file contents after the operation has been performed.  The same
   * applies for @a propstate regarding the property changes.  (In practice,
   * this is only useful with merge, not diff; diff callbacks will
   * probably set @a *contentstate and *propstate to
   * @c svn_wc_notify_state_unknown, since they do not change the state
   * and therefore do not bother to know the state after the operation.)
   *
   */
  svn_error_t *(*file_added)(svn_wc_adm_access_t *adm_access,
                             svn_wc_notify_state_t *contentstate,
                             svn_wc_notify_state_t *propstate,
                             const char *path,
                             const char *tmpfile1,
                             const char *tmpfile2,
                             svn_revnum_t rev1,
                             svn_revnum_t rev2,
                             const char *mimetype1,
                             const char *mimetype2,
                             const apr_array_header_t *propchanges,
                             apr_hash_t *originalprops,
                             void *diff_baton);
  
  /** A file @a path was deleted.  The [loss of] contents can be seen by
   * comparing @a tmpfile1 and @a tmpfile2.  @a originalprops provides
   * the properties of the file.
   *
   * If known, the @c svn:mime-type value of each file is passed into
   * @a mimetype1 and @a mimetype2;  either or both of the values can
   * be NULL.  The implementor can use this information to decide if
   * (or how) to generate differences.
   *
   * @a adm_access will be an access baton for the directory containing 
   * @a path, or @c NULL if the diff editor is not using access batons.
   *
   * If @a state is non-null, set @a *state to the state of the item
   * after the delete operation has been performed.  (In practice,
   * this is only useful with merge, not diff; diff callbacks will
   * probably set @a *state to @c svn_wc_notify_state_unknown, since 
   * they do not change the state and therefore do not bother to know 
   * the state after the operation.)
   */
  svn_error_t *(*file_deleted)(svn_wc_adm_access_t *adm_access,
                               svn_wc_notify_state_t *state,
                               const char *path,
                               const char *tmpfile1,
                               const char *tmpfile2,
                               const char *mimetype1,
                               const char *mimetype2,
                               apr_hash_t *originalprops,
                               void *diff_baton);
  
  /** A directory @a path was added.  @a rev is the revision that the
   * directory came from.
   *
   * @a adm_access will be an access baton for the directory containing 
   * @a path, or @c NULL if the diff editor is not using access batons.
   */
  svn_error_t *(*dir_added)(svn_wc_adm_access_t *adm_access,
                            svn_wc_notify_state_t *state,
                            const char *path,
                            svn_revnum_t rev,
                            void *diff_baton);
  
  /** A directory @a path was deleted.
   *
   * @a adm_access will be an access baton for the directory containing 
   * @a path, or @c NULL if the diff editor is not using access batons.
   *
   * If @a state is non-null, set @a *state to the state of the item
   * after the delete operation has been performed.  (In practice,
   * this is only useful with merge, not diff; diff callbacks will
   * probably set @a *state to @c svn_wc_notify_state_unknown, since 
   * they do not change the state and therefore do not bother to know 
   * the state after the operation.)
   */
  svn_error_t *(*dir_deleted)(svn_wc_adm_access_t *adm_access,
                              svn_wc_notify_state_t *state,
                              const char *path,
                              void *diff_baton);
  
  /** A list of property changes (@a propchanges) was applied to the
   * directory @a path.
   *
   * The array is a list of (@c svn_prop_t) structures. 
   *
   * The original list of properties is provided in @a original_props,
   * which is a hash of @c svn_string_t values, keyed on the property
   * name.
   *
   * @a adm_access will be an access baton for the directory containing 
   * @a path, or @c NULL if the diff editor is not using access batons.
   *
   * If @a state is non-null, set @a *state to the state of the properties
   * after the operation has been performed.  (In practice, this is only 
   * useful with merge, not diff; diff callbacks will probably set @a *state 
   * to @c svn_wc_notify_state_unknown, since they do not change the state 
   * and therefore do not bother to know the state after the operation.)
   */
  svn_error_t *(*dir_props_changed)(svn_wc_adm_access_t *adm_access,
                                    svn_wc_notify_state_t *state,
                                    const char *path,
                                    const apr_array_header_t *propchanges,
                                    apr_hash_t *original_props,
                                    void *diff_baton);

} svn_wc_diff_callbacks2_t;

/**
 * Similar to @c svn_wc_diff_callbacks2_t, but with file additions/content
 * changes and property changes split into different functions.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
typedef struct svn_wc_diff_callbacks_t
{
  /** Similar to @c file_changed in @c svn_wc_diff_callbacks2_t, but without
   * property change information.  @a tmpfile2 is never NULL. @a state applies
   * to the file contents. */
  svn_error_t *(*file_changed)(svn_wc_adm_access_t *adm_access,
                               svn_wc_notify_state_t *state,
                               const char *path,
                               const char *tmpfile1,
                               const char *tmpfile2,
                               svn_revnum_t rev1,
                               svn_revnum_t rev2,
                               const char *mimetype1,
                               const char *mimetype2,
                               void *diff_baton);

  /** Similar to @c file_added in @c svn_wc_diff_callbacks2_t, but without
   * property change information.  @a *state applies to the file contents. */
  svn_error_t *(*file_added)(svn_wc_adm_access_t *adm_access,
                             svn_wc_notify_state_t *state,
                             const char *path,
                             const char *tmpfile1,
                             const char *tmpfile2,
                             svn_revnum_t rev1,
                             svn_revnum_t rev2,
                             const char *mimetype1,
                             const char *mimetype2,
                             void *diff_baton);
  
  /** Similar to @c file_deleted in @c svn_wc_diff_callbacks2_t, but without
   * the properties. */
  svn_error_t *(*file_deleted)(svn_wc_adm_access_t *adm_access,
                               svn_wc_notify_state_t *state,
                               const char *path,
                               const char *tmpfile1,
                               const char *tmpfile2,
                               const char *mimetype1,
                               const char *mimetype2,
                               void *diff_baton);
  
  /** The same as @c dir_added in @c svn_wc_diff_callbacks2_t. */
  svn_error_t *(*dir_added)(svn_wc_adm_access_t *adm_access,
                            svn_wc_notify_state_t *state,
                            const char *path,
                            svn_revnum_t rev,
                            void *diff_baton);
  
  /** The same as @c dir_deleted in @c svn_wc_diff_callbacks2_t. */
  svn_error_t *(*dir_deleted)(svn_wc_adm_access_t *adm_access,
                              svn_wc_notify_state_t *state,
                              const char *path,
                              void *diff_baton);
  
  /** Similar to @c dir_props_changed in @c svn_wc_diff_callbacks2_t, but this
   * function is called for files as well as directories. */
  svn_error_t *(*props_changed)(svn_wc_adm_access_t *adm_access,
                                svn_wc_notify_state_t *state,
                                const char *path,
                                const apr_array_header_t *propchanges,
                                apr_hash_t *original_props,
                                void *diff_baton);

} svn_wc_diff_callbacks_t;


/* Asking questions about a working copy. */

/** Set @a *wc_format to @a path's working copy format version number if 
 * @a path is a valid working copy directory, else set it to 0.  
 * Return error @c APR_ENOENT if @a path does not exist at all.
 */
svn_error_t *svn_wc_check_wc(const char *path,
                             int *wc_format,
                             apr_pool_t *pool);


/** Set @a *has_binary_prop to @c TRUE iff @a path has been marked 
 * with a property indicating that it is non-text (in other words, binary).
 * @a adm_access is an access baton set that contains @a path.
 */
svn_error_t *svn_wc_has_binary_prop(svn_boolean_t *has_binary_prop,
                                    const char *path,
                                    svn_wc_adm_access_t *adm_access,
                                    apr_pool_t *pool);


/* Detecting modification. */

/** Set @a *modified_p to non-zero if @a filename's text is modified
 * with regard to the base revision, else set @a *modified_p to zero.
 * @a filename is a path to the file, not just a basename. @a adm_access
 * must be an access baton for @a filename.
 *
 * If @a force_comparison is @c TRUE, this function will not allow
 * early return mechanisms that avoid actual content comparison.
 * Instead, if there is a text base, a full byte-by-byte comparison
 * will be done, and the entry checksum verified as well.  (This means
 * that if the text base is much longer than the working file, every
 * byte of the text base will still be examined.)
 *
 * If @a filename does not exist, consider it unmodified.  If it exists
 * but is not under revision control (not even scheduled for
 * addition), return the error @c SVN_ERR_ENTRY_NOT_FOUND.
 */
svn_error_t *svn_wc_text_modified_p(svn_boolean_t *modified_p,
                                    const char *filename,
                                    svn_boolean_t force_comparison,
                                    svn_wc_adm_access_t *adm_access,
                                    apr_pool_t *pool);


/** Set @a *modified_p to non-zero if @a path's properties are modified
 * with regard to the base revision, else set @a modified_p to zero. 
 * @a adm_access must be an access baton for @a path.
 */
svn_error_t *svn_wc_props_modified_p(svn_boolean_t *modified_p,
                                     const char *path,
                                     svn_wc_adm_access_t *adm_access,
                                     apr_pool_t *pool);




/** Administrative subdir.
 *
 * Ideally, this would be completely private to wc internals (in fact,
 * it used to be that adm_subdir() in adm_files.c was the only function
 * who knew the adm subdir's name).  However, import wants to protect
 * against importing administrative subdirs, so now the name is a
 * matter of public record.
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 */
#define SVN_WC_ADM_DIR_NAME   ".svn"



/* Entries and status. */

/** The schedule states an entry can be in. */
typedef enum svn_wc_schedule_t
{
  /** Nothing special here */
  svn_wc_schedule_normal,

  /** Slated for addition */
  svn_wc_schedule_add,

  /** Slated for deletion */
  svn_wc_schedule_delete,

  /** Slated for replacement (delete + add) */
  svn_wc_schedule_replace

} svn_wc_schedule_t;


/** A working copy entry -- that is, revision control information about
 * one versioned entity.
 */
typedef struct svn_wc_entry_t
{
  /* IMPORTANT: If you extend this structure, check svn_wc_entry_dup() to see
     if you need to extend that as well. */

  /* General Attributes */

  /** entry's name */
  const char *name;

  /** base revision */
  svn_revnum_t revision;

  /** url in repository */
  const char *url;

  /** canonical repository URL or NULL if not known */
  const char *repos;

  /** repository uuid */
  const char *uuid;

  /** node kind (file, dir, ...) */
  svn_node_kind_t kind;

  /* State information */

  /** scheduling (add, delete, replace ...) */
  svn_wc_schedule_t schedule;

  /** in a copied state */
  svn_boolean_t copied;

  /** deleted, but parent rev lags behind */
  svn_boolean_t deleted;

  /** absent -- we know an entry of this name exists, but that's all
      (usually this happens because of authz restrictions)  */
  svn_boolean_t absent;

  /** for THIS_DIR entry, implies whole entries file is incomplete */
  svn_boolean_t incomplete;

  /** copyfrom location */
  const char *copyfrom_url;

  /** copyfrom revision */
  svn_revnum_t copyfrom_rev;

  /** old version of conflicted file */
  const char *conflict_old;

  /** new version of conflicted file */
  const char *conflict_new;

  /** working version of conflicted file */
  const char *conflict_wrk;

  /** property reject file */
  const char *prejfile;

  /** last up-to-date time for text contents (0 means no information available)
   */
  apr_time_t text_time;

  /** last up-to-date time for properties (0 means no information available) */
  apr_time_t prop_time;

  /** Hex MD5 checksum for the untranslated text base file,
   * can be @c NULL for backwards compatibility.
   */
  const char *checksum;

  /* "Entry props" */

  /** last revision this was changed */
  svn_revnum_t cmt_rev;

  /** last date this was changed */
  apr_time_t cmt_date;

  /** last commit author of this item */
  const char *cmt_author;

  /** lock token or NULL if path not locked in this WC
   * @since New in 1.2.
   */
  const char *lock_token;
  /** lock owner, or NULL if not locked in this WC
   * @since New in 1.2.
   */
  const char *lock_owner;
  /** lock comment or NULL if not locked in this WC or no comment
   * @since New in 1.2.
   */
  const char *lock_comment;
  /** Lock creation date or 0 if not locked in this WC
   * @since New in 1.2.
   */
  apr_time_t lock_creation_date;

  /** Whether this entry has any working properties.
   * False if this information is not stored in the entry.
   *
   * @since New in 1.4. */
  svn_boolean_t has_props;

  /** Whether this entry has property modifications.
   *
   * @note For working copies in older formats, this flag is not valid.
   *
   * @see svn_wc_props_modified_p().
   *
   * @since New in 1.4. */
  svn_boolean_t has_prop_mods;

  /** A space-separated list of all properties whose presence/absence is cached
   * in this entry.
   *
   * @see @c present_props.
   *
   * @since New in 1.4. */
  const char *cachable_props;

  /** Cached property existence for this entry.
   * This is a space-separated list of property names.  If a name exists in
   * @c cachable_props but not in this list, this entry does not have that
   * property.  If a name exists in both lists, the property is present on this
   * entry.
   *
   * @since New in 1.4. */
  const char *present_props;

  /* IMPORTANT: If you extend this structure, check svn_wc_entry_dup() to see
     if you need to extend that as well. */
} svn_wc_entry_t;


/** How an entries file's owner dir is named in the entries file. */
#define SVN_WC_ENTRY_THIS_DIR  ""


/** Set @a *entry to an entry for @a path, allocated in the access baton 
 * pool.  If @a show_hidden is true, return the entry even if it's in 
 * 'deleted' or 'absent' state.  If @a path is not under revision
 * control, or if entry is hidden, not scheduled for re-addition,
 * and @a show_hidden is @c FALSE, then set @a *entry to @c NULL.
 *
 * @a *entry should not be modified, since doing so modifies the entries 
 * cache in @a adm_access without changing the entries file on disk.
 *
 * If @a path is not a directory then @a adm_access must be an access baton 
 * for the parent directory of @a path.  To avoid needing to know whether 
 * @a path is a directory or not, if @a path is a directory @a adm_access 
 * can still be an access baton for the parent of @a path so long as the 
 * access baton for @a path itself is in the same access baton set.
 *
 * Note that it is possible for @a path to be absent from disk but still
 * under revision control; and conversely, it is possible for @a path to
 * be present, but not under revision control.
 *
 * Use @a pool only for local processing.
 */
svn_error_t *svn_wc_entry(const svn_wc_entry_t **entry,
                          const char *path,
                          svn_wc_adm_access_t *adm_access,
                          svn_boolean_t show_hidden,
                          apr_pool_t *pool);


/** Parse the `entries' file for @a adm_access and return a hash @a entries, 
 * whose keys are (<tt>const char *</tt>) entry names and values are 
 * (<tt>svn_wc_entry_t *</tt>).  The hash @a entries, and its keys and
 * values, are allocated from the pool used to open the @a adm_access
 * baton (that's how the entries caching works).  @a pool is used for
 * transient allocations.
 *  
 * Entries that are in a 'deleted' or 'absent' state (and not
 * scheduled for re-addition) are not returned in the hash, unless
 * @a show_hidden is true.
 *
 * @par Important:
 * The @a entries hash is the entries cache in @a adm_access 
 * and so usually the hash itself, the keys and the values should be treated 
 * as read-only.  If any of these are modified then it is the caller's
 * responsibility to ensure that the entries file on disk is updated.  Treat
 * the hash values as type (<tt>const svn_wc_entry_t *</tt>) if you wish to 
 * avoid accidental modification.  Modifying the schedule member is a
 * particularly bad idea, as the entries writing process relies on having
 * access to the original schedule.  Use a duplicate entry to modify the
 * schedule.
 *
 * @par Important:
 * Only the entry structures representing files and
 * @c SVN_WC_ENTRY_THIS_DIR contain complete information.  The entry
 * structures representing subdirs have only the `kind' and `state'
 * fields filled in.  If you want info on a subdir, you must use this
 * routine to open its @a path and read the @c SVN_WC_ENTRY_THIS_DIR 
 * structure, or call svn_wc_entry() on its @a path.
 */
svn_error_t *svn_wc_entries_read(apr_hash_t **entries,
                                 svn_wc_adm_access_t *adm_access,
                                 svn_boolean_t show_hidden,
                                 apr_pool_t *pool);


/** Return a duplicate of @a entry, allocated in @a pool.  No part of the new
 * entry will be shared with @a entry.
 */
svn_wc_entry_t *svn_wc_entry_dup(const svn_wc_entry_t *entry,
                                 apr_pool_t *pool);


/** Given a @a dir_path under version control, decide if one of its
 * entries (@a entry) is in state of conflict; return the answers in
 * @a text_conflicted_p and @a prop_conflicted_p.  
 *
 * (If the entry mentions that a .rej or .prej exist, but they are
 * both removed, assume the conflict has been resolved by the user.)
 */
svn_error_t *svn_wc_conflicted_p(svn_boolean_t *text_conflicted_p,
                                 svn_boolean_t *prop_conflicted_p,
                                 const char *dir_path,
                                 const svn_wc_entry_t *entry,
                                 apr_pool_t *pool);

/** Set @a *url and @a *rev to the ancestor URL and revision for @a path,
 * allocating in @a pool.  @a adm_access must be an access baton for @a path. 
 *
 * If @a url or @a rev is null, then ignore it (just don't return the
 * corresponding information).
 */
svn_error_t *svn_wc_get_ancestry(char **url,
                                 svn_revnum_t *rev,
                                 const char *path,
                                 svn_wc_adm_access_t *adm_access,
                                 apr_pool_t *pool);


/** A callback vtable invoked by the generic entry-walker function. */
typedef struct svn_wc_entry_callbacks_t
{
  /** An @a entry was found at @a path. */
  svn_error_t *(*found_entry)(const char *path,
                              const svn_wc_entry_t *entry,
                              void *walk_baton,
                              apr_pool_t *pool);

  /* ### add more callbacks as new callers need them. */

} svn_wc_entry_callbacks_t;


/**
 * A generic entry-walker.
 *
 * Do a recursive depth-first entry-walk beginning on @a path, which can
 * be a file or dir.  Call callbacks in @a walk_callbacks, passing
 * @a walk_baton to each.  Use @a pool for looping, recursion, and to
 * allocate all entries returned.  @a adm_access must be an access baton
 * for @a path.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton to determine
 * if the client has cancelled the operation.
 *
 * Like our other entries interfaces, entries that are in a 'deleted'
 * or 'absent' state (and not scheduled for re-addition) are not
 * discovered, unless @a show_hidden is true.
 *
 * When a new directory is entered, @c SVN_WC_ENTRY_THIS_DIR will always
 * be returned first.
 *
 * @note Callers should be aware that each directory will be
 * returned *twice*:  first as an entry within its parent, and
 * subsequently as the '.' entry within itself.  The two calls can be
 * distinguished by looking for @c SVN_WC_ENTRY_THIS_DIR in the 'name'
 * field of the entry.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_walk_entries2(const char *path,
                                  svn_wc_adm_access_t *adm_access,
                                  const svn_wc_entry_callbacks_t 
                                  *walk_callbacks,
                                  void *walk_baton,
                                  svn_boolean_t show_hidden,
                                  svn_cancel_func_t cancel_func,
                                  void *cancel_baton,
                                  apr_pool_t *pool);

/**
 * Similar to svn_wc_walk_entries2(), but without cancellation support.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_wc_walk_entries(const char *path,
                                 svn_wc_adm_access_t *adm_access,
                                 const svn_wc_entry_callbacks_t 
                                 *walk_callbacks,
                                 void *walk_baton,
                                 svn_boolean_t show_hidden,
                                 apr_pool_t *pool);


/** Mark missing @a path as 'deleted' in its @a parent's list of entries.
 *
 * Return @c SVN_ERR_WC_PATH_FOUND if @a path isn't actually missing.
 */
svn_error_t *svn_wc_mark_missing_deleted(const char *path,
                                         svn_wc_adm_access_t *parent,
                                         apr_pool_t *pool);
                       


/** Ensure that an administrative area exists for @a path, so that @a
 * path is a working copy subdir based on @a url at @a revision, and
 * with repository UUID @a uuid and repository root URL @a repos.
 * @a uuid and @a repos may be @c NULL.  If non-@c NULL, @a repos must be a
 * prefix of @a url.
 *
 * If the administrative area does not exist, then create it and
 * initialize it to an unlocked state.
 *
 * If the administrative area already exists then the given @a url
 * must match the URL in the administrative area and the given
 * @a revision must match the BASE of the working copy dir unless
 * the admin directory is scheduled for deletion or the
 * SVN_ERR_WC_OBSTRUCTED_UPDATE error will be returned.
 *
 * Do not ensure existence of @a path itself; if @a path does not
 * exist, return error.
 *
 * @since New in 1.3.
 */
svn_error_t *svn_wc_ensure_adm2(const char *path,
                                const char *uuid,
                                const char *url,
                                const char *repos,
                                svn_revnum_t revision,
                                apr_pool_t *pool);


/** Similar to svn_wc_ensure_adm2(), but with @a repos set to @c NULL.
 *
 * @deprecated Provided for backwards compatibility with the 1.2 API.
 */
svn_error_t *svn_wc_ensure_adm(const char *path,
                               const char *uuid,
                               const char *url,
                               svn_revnum_t revision,
                               apr_pool_t *pool);


/** Set the repository root URL of @a path to @a repos, if possible.
 *
 * @a adm_access must contain @a path and be write-locked, if @a path
 * is versioned.  Return no error if path is missing or unversioned.
 * Use @a pool for temporary allocations.
 *
 * @note In some circumstances, the repository root can't be set
 * without making the working copy corrupt.  In such cases, this
 * function just returns no error, without modifying the @a path entry.
 *
 * @note This function exists to make it possible to try to set the repository
 * root in old working copies; new working copies normally get this set at
 * creation time.
 * 
 * @since New in 1.3.
 */
svn_error_t *
svn_wc_maybe_set_repos_root(svn_wc_adm_access_t *adm_access,
                            const char *path, const char *repos,
                            apr_pool_t *pool);


/** 
 * @defgroup svn_wc_status working copy status.
 * @{
 *
 * We have two functions for getting working copy status: one function
 * for getting the status of exactly one thing, and another for
 * getting the statuses of (potentially) multiple things.
 * 
 * The WebDAV concept of "depth" may be useful in understanding the
 * motivation behind this.  Suppose we're getting the status of
 * directory D.  The three depth levels would mean
 * 
 *    depth 0:         D itself (just the named directory)
 *    depth 1:         D and its immediate children (D + its entries)
 *    depth Infinity:  D and all its descendants (full recursion)
 * 
 * To offer all three levels, we could have one unified function,
 * taking a `depth' parameter.  Unfortunately, because this function
 * would have to handle multiple return values as well as the single
 * return value case, getting the status of just one entity would
 * become cumbersome: you'd have to roll through a hash to find one
 * lone status.
 * 
 * So we have svn_wc_status() for depth 0, and 
 * svn_wc_get_status_editor() for depths 1 and 2, since the latter
 * two involve multiple return values.
 *
 * @note The status structures may contain a @c NULL ->entry field.
 * This indicates an item that is not versioned in the working copy.
 */

enum svn_wc_status_kind
{
    /** does not exist */
    svn_wc_status_none = 1,

    /** is not a versioned thing in this wc */
    svn_wc_status_unversioned,

    /** exists, but uninteresting */
    svn_wc_status_normal,

    /** is scheduled for addition */
    svn_wc_status_added,

    /** under v.c., but is missing */
    svn_wc_status_missing,

    /** scheduled for deletion */
    svn_wc_status_deleted,

    /** was deleted and then re-added */
    svn_wc_status_replaced,

    /** text or props have been modified */
    svn_wc_status_modified,

    /** local mods received repos mods */
    svn_wc_status_merged,

    /** local mods received conflicting repos mods */
    svn_wc_status_conflicted,

    /** is unversioned but configured to be ignored */
    svn_wc_status_ignored,

    /** an unversioned resource is in the way of the versioned resource */
    svn_wc_status_obstructed,

    /** an unversioned path populated by an svn:externals property */
    svn_wc_status_external,

    /** a directory doesn't contain a complete entries list */
    svn_wc_status_incomplete
};

/**
 * Structure for holding the "status" of a working copy item. 
 *
 * The item's entry data is in @a entry, augmented and possibly shadowed
 * by the other fields.  @a entry is @c NULL if this item is not under
 * version control.
 *
 * @note Fields may be added to the end of this structure in future
 * versions.  Therefore, users shouldn't allocate structures of this
 * type, to preserve binary compatibility.
 *
 * @since New in 1.2.
 */
typedef struct svn_wc_status2_t
{
  /** Can be @c NULL if not under version control. */
  svn_wc_entry_t *entry;
  
  /** The status of the entries text. */
  enum svn_wc_status_kind text_status;

  /** The status of the entries properties. */
  enum svn_wc_status_kind prop_status;

  /** a directory can be 'locked' if a working copy update was interrupted. */
  svn_boolean_t locked;

  /** a file or directory can be 'copied' if it's scheduled for 
   * addition-with-history (or part of a subtree that is scheduled as such.).
   */
  svn_boolean_t copied;

  /** a file or directory can be 'switched' if the switch command has been 
   * used.
   */
  svn_boolean_t switched;

  /** The entry's text status in the repository. */
  enum svn_wc_status_kind repos_text_status;

  /** The entry's property status in the repository. */
  enum svn_wc_status_kind repos_prop_status;

  /** The entry's lock in the repository, if any. */
  svn_lock_t *repos_lock;

  /** Set to the URI (actual or expected) of the item.
   * @since New in 1.3
   */
  const char *url;

  /**
   * @defgroup svn_wc_status_ood WC out of date info from the repository
   * @{
   *
   * When the working copy item is out of date compared to the
   * repository, the following fields represent the state of the
   * youngest revision of the item in the repository.  If the working
   * copy is not out of date, the fields are initialized as described
   * below.
   */

  /** Set to the youngest committed revision, or @c SVN_INVALID_REVNUM
   * if not out of date.
   * @since New in 1.3
   */
  svn_revnum_t ood_last_cmt_rev;

  /** Set to the most recent commit date, or @c 0 if not out of date.
   * @since New in 1.3
   */
  apr_time_t ood_last_cmt_date;

  /** Set to the node kind of the youngest commit, or @c svn_node_none
   * if not out of date.
   * @since New in 1.3
   */
  svn_node_kind_t ood_kind;

  /** Set to the user name of the youngest commit, or @c NULL if not
   * out of date or non-existent.  Because a non-existent @c
   * svn:author property has the same behavior as an out of date
   * working copy, examine @c ood_last_cmt_rev to determine whether
   * the working copy is out of date.
   * @since New in 1.3
   */
  const char *ood_last_cmt_author;

  /** @} */

  /* NOTE! Please update svn_wc_dup_status2() when adding new fields here. */
} svn_wc_status2_t;



/**
 * Same as @c svn_wc_status2_t, but without the svn_lock_t 'repos_lock' field.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
typedef struct svn_wc_status_t
{
  /** Can be @c NULL if not under version control. */
  svn_wc_entry_t *entry;
  
  /** The status of the entries text. */
  enum svn_wc_status_kind text_status;

  /** The status of the entries properties. */
  enum svn_wc_status_kind prop_status;

  /** a directory can be 'locked' if a working copy update was interrupted. */
  svn_boolean_t locked;

  /** a file or directory can be 'copied' if it's scheduled for 
   * addition-with-history (or part of a subtree that is scheduled as such.).
   */
  svn_boolean_t copied;

  /** a file or directory can be 'switched' if the switch command has been 
   * used.
   */
  svn_boolean_t switched;

  /** The entry's text status in the repository. */
  enum svn_wc_status_kind repos_text_status;

  /** The entry's property status in the repository. */
  enum svn_wc_status_kind repos_prop_status;

} svn_wc_status_t;



/**
 * Return a deep copy of the @a orig_stat status structure, allocated
 * in @a pool.
 *
 * @since New in 1.2.
 */
svn_wc_status2_t *svn_wc_dup_status2(svn_wc_status2_t *orig_stat,
                                     apr_pool_t *pool);


/**
 * Same as svn_wc_dup_status2(), but for older svn_wc_status_t structures.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_wc_status_t *svn_wc_dup_status(svn_wc_status_t *orig_stat,
                                   apr_pool_t *pool);


/**
 * Fill @a *status for @a path, allocating in @a pool.
 * @a adm_access must be an access baton for @a path.
 *
 * Here are some things to note about the returned structure.  A quick
 * examination of the @c status->text_status after a successful return of
 * this function can reveal the following things:
 *
 *    - @c svn_wc_status_none : @a path is not versioned, and is either not
 *                              present on disk, or is ignored by svn's
 *                              default ignore regular expressions or the
 *                              svn:ignore property setting for @a path's
 *                              parent directory.
 *
 *    - @c svn_wc_status_missing : @a path is versioned, but is missing from
 *                                 the working copy.
 *
 *    - @c svn_wc_status_unversioned : @a path is not versioned, but is
 *                                     present on disk and not being
 *                                     ignored (see above).  
 *
 * The other available results for the @c text_status field are more
 * straightforward in their meanings.  See the comments on the
 * @c svn_wc_status_kind structure for some hints.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_status2(svn_wc_status2_t **status, 
                            const char *path, 
                            svn_wc_adm_access_t *adm_access,
                            apr_pool_t *pool);


/**
 *  Same as svn_wc_status2(), but for older svn_wc_status_t structures.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_status(svn_wc_status_t **status, 
                           const char *path, 
                           svn_wc_adm_access_t *adm_access,
                           apr_pool_t *pool);




/**
 * A callback for reporting a @a status about @a path. 
 *
 * @a baton is a closure object; it should be provided by the
 * implementation, and passed by the caller.
 *
 * @since New in 1.2.
 */
typedef void (*svn_wc_status_func2_t)(void *baton,
                                      const char *path,
                                      svn_wc_status2_t *status);

/**
 *  Same as svn_wc_status_func2_t(), but for older svn_wc_status_t structures.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
typedef void (*svn_wc_status_func_t)(void *baton,
                                     const char *path,
                                     svn_wc_status_t *status);


/**
 * Set @a *editor and @a *edit_baton to an editor that generates @c
 * svn_wc_status2_t structures and sends them through @a status_func /
 * @a status_baton.  @a anchor is an access baton, with a tree lock,
 * for the local path to the working copy which will be used as the
 * root of our editor.  If @a target is not empty, it represents an
 * entry in the @a anchor path which is the subject of the editor
 * drive (otherwise, the @a anchor is the subject).
 * 
 * If @a set_locks_baton is non-@c NULL, it will be set to a baton that can
 * be used in a call to the svn_wc_status_set_repos_locks() function.
 *
 * Callers drive this editor to describe working copy out-of-dateness
 * with respect to the repository.  If this information is not
 * available or not desired, callers should simply call the
 * close_edit() function of the @a editor vtable.
 *
 * If the editor driver calls @a editor's set_target_revision() vtable
 * function, then when the edit drive is completed, @a *edit_revision
 * will contain the revision delivered via that interface.
 *
 * @a config is a hash mapping @c SVN_CONFIG_CATEGORY's to @c
 * svn_config_t's.
 *
 * Assuming the target is a directory, then:
 * 
 *   - If @a get_all is false, then only locally-modified entries will be
 *     returned.  If true, then all entries will be returned.
 *
 *   - If @a recurse is false, status structures will be returned only
 *     for the target and its immediate children.  Otherwise, this
 *     operation is fully recursive.
 *
 * If @a no_ignore is set, statuses that would typically be ignored
 * will instead be reported.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton while building 
 * the @a statushash to determine if the client has cancelled the operation.
 *
 * If @a traversal_info is non-null, then record pre-update traversal
 * state in it.  (Caller should obtain @a traversal_info from
 * svn_wc_init_traversal_info().)
 *
 * Allocate the editor itself in @a pool, but the editor does temporary
 * allocations in a subpool of @a pool.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_get_status_editor2(const svn_delta_editor_t **editor,
                                       void **edit_baton,
                                       void **set_locks_baton,
                                       svn_revnum_t *edit_revision,
                                       svn_wc_adm_access_t *anchor,
                                       const char *target,
                                       apr_hash_t *config,
                                       svn_boolean_t recurse,
                                       svn_boolean_t get_all,
                                       svn_boolean_t no_ignore,
                                       svn_wc_status_func2_t status_func,
                                       void *status_baton,
                                       svn_cancel_func_t cancel_func,
                                       void *cancel_baton,
                                       svn_wc_traversal_info_t *traversal_info,
                                       apr_pool_t *pool);


/**
 * Same as svn_wc_get_status_editor2(), but with @a set_locks_baton set
 * to @c NULL, and taking a deprecated svn_wc_status_func_t argument.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_get_status_editor(const svn_delta_editor_t **editor,
                                      void **edit_baton,
                                      svn_revnum_t *edit_revision,
                                      svn_wc_adm_access_t *anchor,
                                      const char *target,
                                      apr_hash_t *config,
                                      svn_boolean_t recurse,
                                      svn_boolean_t get_all,
                                      svn_boolean_t no_ignore,
                                      svn_wc_status_func_t status_func,
                                      void *status_baton,
                                      svn_cancel_func_t cancel_func,
                                      void *cancel_baton,
                                      svn_wc_traversal_info_t *traversal_info,
                                      apr_pool_t *pool);


/**
 * Associate @a locks, a hash table mapping <tt>const char*</tt>
 * absolute repository paths to <tt>svn_lock_t</tt> objects, with a
 * @a set_locks_baton returned by an earlier call to
 * svn_wc_get_status_editor2().  @a repos_root is the repository root URL.
 * Perform all allocations in @a pool.
 *
 * @note @a locks will not be copied, so it must be valid throughout the
 * edit.  @a pool must also not be destroyed or cleared before the edit is
 * finished.
 *
 * @since New in 1.2.
 */
svn_error_t *
svn_wc_status_set_repos_locks(void *set_locks_baton,
                              apr_hash_t *locks,
                              const char *repos_root,
                              apr_pool_t *pool);

/** @} */


/**
 * Copy @a src to @a dst_basename in @a dst_parent, and schedule 
 * @a dst_basename for addition to the repository, remembering the copy 
 * history.
 *
 * @a src must be a file or directory under version control; @a dst_parent
 * must be a directory under version control in the same working copy;
 * @a dst_basename will be the name of the copied item, and it must not
 * exist already.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton at
 * various points during the operation.  If it returns an error
 * (typically @c SVN_ERR_CANCELLED), return that error immediately.
 *
 * For each file or directory copied, @a notify_func will be called
 * with its path and the @a notify_baton.  @a notify_func may be @c NULL 
 * if you are not interested in this information.
 *
 * @par Important:
 * This is a variant of svn_wc_add().  No changes will happen
 * to the repository until a commit occurs.  This scheduling can be
 * removed with svn_client_revert().
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_copy2(const char *src,
                          svn_wc_adm_access_t *dst_parent,
                          const char *dst_basename,
                          svn_cancel_func_t cancel_func,
                          void *cancel_baton,
                          svn_wc_notify_func2_t notify_func,
                          void *notify_baton,
                          apr_pool_t *pool);

/**
 * Similar to svn_wc_copy2(), but takes an @c svn_wc_notify_func_t instead.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_copy(const char *src,
                         svn_wc_adm_access_t *dst_parent,
                         const char *dst_basename,
                         svn_cancel_func_t cancel_func,
                         void *cancel_baton,
                         svn_wc_notify_func_t notify_func,
                         void *notify_baton,
                         apr_pool_t *pool);

/**
 * Schedule @a path for deletion, it will be deleted from the repository on
 * the next commit.  If @a path refers to a directory, then a recursive
 * deletion will occur.  @a adm_access must hold a write lock for the parent 
 * of @a path.
 *
 * This function immediately deletes all files, modified and unmodified,
 * versioned and unversioned from the working copy. It also immediately
 * deletes unversioned directories and directories that are scheduled to be
 * added.  Only versioned directories will remain in the working copy,
 * these get deleted by the update following the commit.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton at
 * various points during the operation.  If it returns an error
 * (typically @c SVN_ERR_CANCELLED), return that error immediately.
 *
 * For each path marked for deletion, @a notify_func will be called with
 * the @a notify_baton and that path. The @a notify_func callback may be
 * @c NULL if notification is not needed.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_delete2(const char *path,
                            svn_wc_adm_access_t *adm_access,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            svn_wc_notify_func2_t notify_func,
                            void *notify_baton,
                            apr_pool_t *pool);

/**
 * Similar to svn_wc_delete2(), but takes an @c svn_wc_notify_func_t instead.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_delete(const char *path,
                           svn_wc_adm_access_t *adm_access,
                           svn_cancel_func_t cancel_func,
                           void *cancel_baton,
                           svn_wc_notify_func_t notify_func,
                           void *notify_baton,
                           apr_pool_t *pool);


/**
 * Put @a path under version control by adding an entry in its parent,
 * and, if @a path is a directory, adding an administrative area.  The
 * new entry and anything under it is scheduled for addition to the
 * repository.  @a parent_access should hold a write lock for the parent
 * directory of @a path.  If @a path is a directory then an access baton 
 * for @a path will be added to the set containing @a parent_access.
 *
 * If @a path does not exist, return @c SVN_ERR_WC_PATH_NOT_FOUND.
 *
 * If @a copyfrom_url is non-null, it and @a copyfrom_rev are used as
 * `copyfrom' args.  This is for copy operations, where one wants
 * to schedule @a path for addition with a particular history.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton at
 * various points during the operation.  If it returns an error
 * (typically @c SVN_ERR_CANCELLED), return that error immediately.
 *
 * When the @a path has been added, then @a notify_func will be called
 * (if it is not @c NULL) with the @a notify_baton and the path.
 *
 * Return @c SVN_ERR_WC_NODE_KIND_CHANGE if @a path is both an unversioned
 * directory and a file that is scheduled for deletion or in state deleted.
 *
 *<pre> ### This function currently does double duty -- it is also
 * ### responsible for "switching" a working copy directory over to a
 * ### new copyfrom ancestry and scheduling it for addition.  Here is
 * ### the old doc string from Ben, lightly edited to bring it
 * ### up-to-date, explaining the true, secret life of this function:</pre>
 *
 * Given a @a path within a working copy of type KIND, follow this algorithm:
 *
 *    - if @a path is not under version control:
 *       - Place it under version control and schedule for addition; 
 *         if @a copyfrom_url is non-null, use it and @a copyfrom_rev as
 *         'copyfrom' history
 *
 *    - if @a path is already under version control:
 *          (This can only happen when a directory is copied, in which
 *           case ancestry must have been supplied as well.)
 *
 *       -  Schedule the directory itself for addition with copyfrom history.
 *       -  Mark all its children with a 'copied' flag
 *       -  Rewrite all the URLs to what they will be after a commit.
 *       -  ### TODO:  remove old wcprops too, see the '###'below
 *
 *<pre> ### I think possibly the "switchover" functionality should be
 * ### broken out into a separate function, but its all intertwined in
 * ### the code right now.  Ben, thoughts?  Hard?  Easy?  Mauve?</pre>
 *
 * ### Update: see "###" comment in svn_wc_add_repos_file()'s doc
 * string about this.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_add2(const char *path,
                         svn_wc_adm_access_t *parent_access,
                         const char *copyfrom_url,
                         svn_revnum_t copyfrom_rev,
                         svn_cancel_func_t cancel_func,
                         void *cancel_baton,
                         svn_wc_notify_func2_t notify_func,
                         void *notify_baton,
                         apr_pool_t *pool);

/**
 * Similar to svn_wc_add2(), but takes an @c svn_wc_notify_func_t instead.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_add(const char *path,
                        svn_wc_adm_access_t *parent_access,
                        const char *copyfrom_url,
                        svn_revnum_t copyfrom_rev,
                        svn_cancel_func_t cancel_func,
                        void *cancel_baton,
                        svn_wc_notify_func_t notify_func,
                        void *notify_baton,
                        apr_pool_t *pool);

/** Add a file to a working copy at @a dst_path, obtaining the base-text's
 * contents from @a new_text_base_path, the wc file's content from
 * @a new_text_path, its base properties from @a new_base_props and
 * wc properties from @a new_props.
 * The base text and props normally come from the repository file
 * represented by the copyfrom args, see below.  The new file will
 * be scheduled for addition with history.
 *
 * Automatically remove @a new_text_path and @a new_text_path upon
 * successful completion.
 *
 * @a new_text_path and @a new_props may be null, in which case
 * the working copy text and props are taken from the base files with
 * appropriate translation of the file's content.
 *
 * @a adm_access, or an access baton in its associated set, must
 * contain a write lock for the parent of @a dst_path.
 *
 * If @a copyfrom_url is non-null, then @a copyfrom_rev must be a
 * valid revision number, and together they are the copyfrom history
 * for the new file.
 *
 * Use @a pool for temporary allocations.
 *
 * ### This function is very redundant with svn_wc_add().  Ideally,
 * we'd merge them, so that svn_wc_add() would just take optional
 * new_props and optional copyfrom information.  That way it could be
 * used for both 'svn add somefilesittingonmydisk' and for adding
 * files from repositories, with or without copyfrom history.
 *
 * The problem with this Ideal Plan is that svn_wc_add() also takes
 * care of recursive URL-rewriting.  There's a whole comment in its
 * doc string about how that's really weird, outside its core mission,
 * etc, etc.  So another part of the Ideal Plan is that that
 * functionality of svn_wc_add() would move into a separate function.
 *
 * @since New in 1.4
 */

svn_error_t *svn_wc_add_repos_file2(const char *dst_path,
                                    svn_wc_adm_access_t *adm_access,
                                    const char *new_text_base_path,
                                    const char *new_text_path,
                                    apr_hash_t *new_base_props,
                                    apr_hash_t *new_props,
                                    const char *copyfrom_url,
                                    svn_revnum_t copyfrom_rev,
                                    apr_pool_t *pool);

/** Same as svn_wc_add_repos_file2(), except that it doesn't have the
 * new_text_base_path and new_base_props arguments.
 *
 * @deprecated Provided for compatibility with the 1.3 API
 *
 */

svn_error_t *svn_wc_add_repos_file(const char *dst_path,
                                   svn_wc_adm_access_t *adm_access,
                                   const char *new_text_path,
                                   apr_hash_t *new_props,
                                   const char *copyfrom_url,
                                   svn_revnum_t copyfrom_rev,
                                   apr_pool_t *pool);


/** Remove entry @a name in @a adm_access from revision control.  @a name 
 * must be either a file or @c SVN_WC_ENTRY_THIS_DIR.  @a adm_access must 
 * hold a write lock.
 *
 * If @a name is a file, all its info will be removed from @a adm_access's
 * administrative directory.  If @a name is @c SVN_WC_ENTRY_THIS_DIR, then
 * @a adm_access's entire administrative area will be deleted, along with
 * *all* the administrative areas anywhere in the tree below @a adm_access.
 *
 * Normally, only administrative data is removed.  However, if
 * @a destroy_wf is true, then all working file(s) and dirs are deleted
 * from disk as well.  When called with @a destroy_wf, any locally
 * modified files will *not* be deleted, and the special error
 * @c SVN_ERR_WC_LEFT_LOCAL_MOD might be returned.  (Callers only need to
 * check for this special return value if @a destroy_wf is true.)
 *
 * If @a instant_error is TRUE, then return @c
 * SVN_ERR_WC_LEFT_LOCAL_MOD the instant a locally modified file is
 * encountered.  Otherwise, leave locally modified files in place and
 * return the error only after all the recursion is complete.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton at
 * various points during the removal.  If it returns an error
 * (typically @c SVN_ERR_CANCELLED), return that error immediately.
 *
 * WARNING:  This routine is exported for careful, measured use by
 * libsvn_client.  Do *not* call this routine unless you really
 * understand what the heck you're doing.
 */
svn_error_t *
svn_wc_remove_from_revision_control(svn_wc_adm_access_t *adm_access,
                                    const char *name,
                                    svn_boolean_t destroy_wf,
                                    svn_boolean_t instant_error,
                                    svn_cancel_func_t cancel_func,
                                    void *cancel_baton,
                                    apr_pool_t *pool);


/**
 * Assuming @a path is under version control and in a state of conflict, 
 * then take @a path *out* of this state.  If @a resolve_text is true then 
 * any text conflict is resolved, if @a resolve_props is true then any 
 * property conflicts are resolved.  If @a recurse is true, then search
 * recursively for conflicts to resolve.
 *
 * @a adm_access is an access baton, with a write lock, for @a path.
 *
 * Needless to say, this function doesn't touch conflict markers or
 * anything of that sort -- only a human can semantically resolve a
 * conflict.  Instead, this function simply marks a file as "having
 * been resolved", clearing the way for a commit.  
 *
 * The implementation details are opaque, as our "conflicted" criteria
 * might change over time.  (At the moment, this routine removes the
 * three fulltext 'backup' files and any .prej file created in a conflict,
 * and modifies @a path's entry.)
 *
 * If @a path is not under version control, return @c SVN_ERR_ENTRY_NOT_FOUND.  
 * If @a path isn't in a state of conflict to begin with, do nothing, and
 * return @c SVN_NO_ERROR.
 *
 * If @c path was successfully taken out of a state of conflict, report this
 * information to @c notify_func (if non-@c NULL.)  If only text or only 
 * property conflict resolution was requested, and it was successful, then 
 * success gets reported.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_resolved_conflict2(const char *path,
                                       svn_wc_adm_access_t *adm_access,
                                       svn_boolean_t resolve_text,
                                       svn_boolean_t resolve_props,
                                       svn_boolean_t recurse,
                                       svn_wc_notify_func2_t notify_func,
                                       void *notify_baton,
                                       svn_cancel_func_t cancel_func,
                                       void *cancel_baton,
                                       apr_pool_t *pool);

/**
 * Similar to svn_wc_resolved_conflict2(), but takes an
 * svn_wc_notify_func_t and doesn't have cancellation support.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_wc_resolved_conflict(const char *path,
                                      svn_wc_adm_access_t *adm_access,
                                      svn_boolean_t resolve_text,
                                      svn_boolean_t resolve_props,
                                      svn_boolean_t recurse,
                                      svn_wc_notify_func_t notify_func,
                                      void *notify_baton,
                                      apr_pool_t *pool);


/* Commits. */

/**
 * Bump a successfully committed absolute @a path to @a new_revnum after a
 * commit succeeds.  @a rev_date and @a rev_author are the (server-side)
 * date and author of the new revision; one or both may be @c NULL.
 * @a adm_access must hold a write lock appropriate for @a path.
 *
 * If non-null, @a wcprop_changes is an array of <tt>svn_prop_t *</tt>
 * changes to wc properties; if an @c svn_prop_t->value is null, then
 * that property is deleted.
 *
 * If @a remove_lock is @c TRUE, any entryprops related to a repository
 * lock will be removed.
 *
 * If @a path is a file and @a digest is non-null, use @a digest as
 * the checksum for the new text base.  Else, calculate the checksum
 * if needed.
 *
 * If @a recurse is true and @a path is a directory, then bump every
 * versioned object at or under @a path.  This is usually done for
 * copied trees.
 *
 * @since New in 1.4.
 */
svn_error_t *svn_wc_process_committed3(const char *path,
                                       svn_wc_adm_access_t *adm_access,
                                       svn_boolean_t recurse,
                                       svn_revnum_t new_revnum,
                                       const char *rev_date,
                                       const char *rev_author,
                                       apr_array_header_t *wcprop_changes,
                                       svn_boolean_t remove_lock,
                                       const unsigned char *digest,
                                       apr_pool_t *pool);

/** Similar to svn_wc_process_committed3(), but with @a digest set to
 * null.
 *
 * @since New in 1.2.
 *
 * @deprecated Provided for backwards compatibility with the 1.3 API.
 */
svn_error_t *svn_wc_process_committed2(const char *path,
                                       svn_wc_adm_access_t *adm_access,
                                       svn_boolean_t recurse,
                                       svn_revnum_t new_revnum,
                                       const char *rev_date,
                                       const char *rev_author,
                                       apr_array_header_t *wcprop_changes,
                                       svn_boolean_t remove_lock,
                                       apr_pool_t *pool);

/**
 * Similar to svn_wc_process_committed2(), but with @a remove_lock set to
 * @c FALSE.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_process_committed(const char *path,
                                      svn_wc_adm_access_t *adm_access,
                                      svn_boolean_t recurse,
                                      svn_revnum_t new_revnum,
                                      const char *rev_date,
                                      const char *rev_author,
                                      apr_array_header_t *wcprop_changes,
                                      apr_pool_t *pool);





/**
 * Do a depth-first crawl in a working copy, beginning at @a path.
 *
 * Communicate the `state' of the working copy's revisions to
 * @a reporter/@a report_baton.  Obviously, if @a path is a file instead 
 * of a directory, this depth-first crawl will be a short one.
 *
 * No locks are or logs are created, nor are any animals harmed in the
 * process.  No cleanup is necessary.  @a adm_access must be an access 
 * baton for the @a path hierarchy, it does not require a write lock.
 *
 * After all revisions are reported, @a reporter->finish_report() is
 * called, which immediately causes the RA layer to update the working
 * copy.  Thus the return value may very well reflect the result of
 * the update!
 *
 * If @a restore_files is true, then unexpectedly missing working files
 * will be restored from the administrative directory's cache. For each
 * file restored, the @a notify_func function will be called with the
 * @a notify_baton and the path of the restored file. @a notify_func may
 * be @c NULL if this notification is not required.  If @a
 * use_commit_times is true, then set restored files' timestamps to
 * their last-commit-times.
 *
 * If @a traversal_info is non-null, then record pre-update traversal
 * state in it.  (Caller should obtain @a traversal_info from
 * svn_wc_init_traversal_info().)
 *
 * @since New in 1.2.
 */
svn_error_t *
svn_wc_crawl_revisions2(const char *path,
                        svn_wc_adm_access_t *adm_access,
                        const svn_ra_reporter2_t *reporter,
                        void *report_baton,
                        svn_boolean_t restore_files,
                        svn_boolean_t recurse,
                        svn_boolean_t use_commit_times,
                        svn_wc_notify_func2_t notify_func,
                        void *notify_baton,
                        svn_wc_traversal_info_t *traversal_info,
                        apr_pool_t *pool);

/**
 * Similar to svn_wc_crawl_revisions2(), but takes an svn_wc_notify_func_t
 * and a @c svn_reporter_t instead.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *
svn_wc_crawl_revisions(const char *path,
                       svn_wc_adm_access_t *adm_access,
                       const svn_ra_reporter_t *reporter,
                       void *report_baton,
                       svn_boolean_t restore_files,
                       svn_boolean_t recurse,
                       svn_boolean_t use_commit_times,
                       svn_wc_notify_func_t notify_func,
                       void *notify_baton,
                       svn_wc_traversal_info_t *traversal_info,
                       apr_pool_t *pool);


/* Updates. */

/** Set @a *wc_root to @c TRUE if @a path represents a "working copy root",
 * @c FALSE otherwise.  Use @a pool for any intermediate allocations.
 *
 * If @a path is not found, return the error @c SVN_ERR_ENTRY_NOT_FOUND.
 *
 * @note Due to the way in which "WC-root-ness" is calculated, passing
 * a @a path of `.' to this function will always return @c TRUE.
 */
svn_error_t *svn_wc_is_wc_root(svn_boolean_t *wc_root,
                               const char *path,
                               svn_wc_adm_access_t *adm_access,
                               apr_pool_t *pool);


/** Conditionally split @a path into an @a anchor and @a target for the 
 * purpose of updating and committing.
 *
 * @a anchor is the directory at which the update or commit editor
 * should be rooted.
 *
 * @a target is the actual subject (relative to the @a anchor) of the
 * update/commit, or "" if the @a anchor itself is the subject.
 *
 * Allocate @a anchor and @a target in @a pool.  
 */
svn_error_t *svn_wc_get_actual_target(const char *path,
                                      const char **anchor,
                                      const char **target,
                                      apr_pool_t *pool);



/* Update and update-like functionality. */

/**
 * Set @a *editor and @a *edit_baton to an editor and baton for updating a
 * working copy.
 *
 * If @a ti is non-null, record traversal info in @a ti, for use by
 * post-traversal accessors such as svn_wc_edited_externals().
 * 
 * @a anchor is an access baton, with a write lock, for the local path to the
 * working copy which will be used as the root of our editor.  Further
 * locks will be acquired if the update creates new directories.  All
 * locks, both those in @a anchor and newly acquired ones, will be released
 * when the editor driver calls @c close_edit.
 *
 * @a target is the entry in @a anchor that will actually be updated, or 
 * empty if all of @a anchor should be updated.
 *
 * The editor invokes @a notify_func with @a notify_baton as the update
 * progresses, if @a notify_func is non-null.
 *
 * If @a cancel_func is non-null, the editor will invoke @a cancel_func with 
 * @a cancel_baton as the update progresses to see if it should continue.
 *
 * If @a diff3_cmd is non-null, then use it as the diff3 command for
 * any merging; otherwise, use the built-in merge code.
 *
 * @a target_revision is a pointer to a revision location which, after
 * successful completion of the drive of this editor, will be
 * populated with the revision to which the working copy was updated.
 *
 * If @a use_commit_times is TRUE, then all edited/added files will
 * have their working timestamp set to the last-committed-time.  If
 * FALSE, the working files will be touched with the 'now' time.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_get_update_editor2(svn_revnum_t *target_revision,
                                       svn_wc_adm_access_t *anchor,
                                       const char *target,
                                       svn_boolean_t use_commit_times,
                                       svn_boolean_t recurse,
                                       svn_wc_notify_func2_t notify_func,
                                       void *notify_baton,
                                       svn_cancel_func_t cancel_func,
                                       void *cancel_baton,
                                       const char *diff3_cmd,
                                       const svn_delta_editor_t **editor,
                                       void **edit_baton,
                                       svn_wc_traversal_info_t *ti,
                                       apr_pool_t *pool);

/**
 * Similar to svn_wc_get_update_editor2(), but takes an svn_wc_notify_func_t
 * instead.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_get_update_editor(svn_revnum_t *target_revision,
                                      svn_wc_adm_access_t *anchor,
                                      const char *target,
                                      svn_boolean_t use_commit_times,
                                      svn_boolean_t recurse,
                                      svn_wc_notify_func_t notify_func,
                                      void *notify_baton,
                                      svn_cancel_func_t cancel_func,
                                      void *cancel_baton,
                                      const char *diff3_cmd,
                                      const svn_delta_editor_t **editor,
                                      void **edit_baton,
                                      svn_wc_traversal_info_t *ti,
                                      apr_pool_t *pool);

/**
 * A variant of svn_wc_get_update_editor().
 *
 * Set @a *editor and @a *edit_baton to an editor and baton for "switching"
 * a working copy to a new @a switch_url.  (Right now, this URL must be
 * within the same repository that the working copy already comes
 * from.)  @a switch_url must not be @c NULL.
 *
 * If @a ti is non-null, record traversal info in @a ti, for use by
 * post-traversal accessors such as svn_wc_edited_externals().
 * 
 * @a anchor is an access baton, with a write lock, for the local path to the
 * working copy which will be used as the root of our editor.  Further
 * locks will be acquired if the switch creates new directories.  All
 * locks, both those in @a anchor and newly acquired ones, will be released
 * when the editor driver calls @c close_edit.
 *
 * @a target is the entry in @a anchor that will actually be updated, or 
 * empty if all of @a anchor should be updated.
 *
 * The editor invokes @a notify_func with @a notify_baton as the switch
 * progresses, if @a notify_func is non-null.
 *
 * If @a cancel_func is non-null, it will be called with @a cancel_baton as 
 * the switch progresses to determine if it should continue.
 *
 * If @a diff3_cmd is non-null, then use it as the diff3 command for
 * any merging; otherwise, use the built-in merge code.
 *
 * @a target_revision is a pointer to a revision location which, after
 * successful completion of the drive of this editor, will be
 * populated with the revision to which the working copy was updated.
 *
 * If @a use_commit_times is TRUE, then all edited/added files will
 * have their working timestamp set to the last-committed-time.  If
 * FALSE, the working files will be touched with the 'now' time.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_get_switch_editor2(svn_revnum_t *target_revision,
                                       svn_wc_adm_access_t *anchor,
                                       const char *target,
                                       const char *switch_url,
                                       svn_boolean_t use_commit_times,
                                       svn_boolean_t recurse,
                                       svn_wc_notify_func2_t notify_func,
                                       void *notify_baton,
                                       svn_cancel_func_t cancel_func,
                                       void *cancel_baton,
                                       const char *diff3_cmd,
                                       const svn_delta_editor_t **editor,
                                       void **edit_baton,
                                       svn_wc_traversal_info_t *ti,
                                       apr_pool_t *pool);

/**
 * Similar to svn_wc_get_switch_editor2(), but takes an
 * @c svn_wc_notify_func_t instead.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_get_switch_editor(svn_revnum_t *target_revision,
                                      svn_wc_adm_access_t *anchor,
                                      const char *target,
                                      const char *switch_url,
                                      svn_boolean_t use_commit_times,
                                      svn_boolean_t recurse,
                                      svn_wc_notify_func_t notify_func,
                                      void *notify_baton,
                                      svn_cancel_func_t cancel_func,
                                      void *cancel_baton,
                                      const char *diff3_cmd,
                                      const svn_delta_editor_t **editor,
                                      void **edit_baton,
                                      svn_wc_traversal_info_t *ti,
                                      apr_pool_t *pool);



/* A word about the implementation of working copy property storage:
 *
 * Since properties are key/val pairs, you'd think we store them in
 * some sort of Berkeley DB-ish format, and even store pending changes
 * to them that way too.
 *
 * However, we already have libsvn_subr/hashdump.c working, and it
 * uses a human-readable format.  That will be very handy when we're
 * debugging, and presumably we will not be dealing with any huge
 * properties or property lists initially.  Therefore, we will
 * continue to use hashdump as the internal mechanism for storing and
 * reading from property lists, but note that the interface here is
 * _not_ dependent on that.  We can swap in a DB-based implementation
 * at any time and users of this library will never know the
 * difference.
 */

/** Set @a *props to a hash table mapping <tt>char *</tt> names onto
 * <tt>svn_string_t *</tt> values for all the regular properties of 
 * @a path.  Allocate the table, names, and values in @a pool.  If 
 * the node has no properties, or does not exist in the working copy,
 * then an empty hash is returned.  @a adm_access is an access baton
 * set that contains @a path.
 */
svn_error_t *svn_wc_prop_list(apr_hash_t **props,
                              const char *path,
                              svn_wc_adm_access_t *adm_access,
                              apr_pool_t *pool);


/** Set @a *value to the value of property @a name for @a path, allocating
 * @a *value in @a pool.  If no such prop, set @a *value to @c NULL.  
 * @a name may be a regular or wc property; if it is an entry property, 
 * return the error @c SVN_ERR_BAD_PROP_KIND.  @a adm_access is an access
 * baton set that contains @a path.
 */
svn_error_t *svn_wc_prop_get(const svn_string_t **value,
                             const char *name,
                             const char *path,
                             svn_wc_adm_access_t *adm_access,
                             apr_pool_t *pool);

/** 
 * Set property @a name to @a value for @a path, or if @a value is
 * null, remove property @a name from @a path.  @a adm_access is an
 * access baton with a write lock for @a path.
 *
 * If @a skip_checks is true, do no validity checking.  But if @a
 * skip_checks is false, and @a name is not a valid property for @a
 * path, return an error, either @c SVN_ERR_ILLEGAL_TARGET (if the
 * property is not appropriate for @a path), or @c
 * SVN_ERR_BAD_MIME_TYPE (if @a name is "svn:mime-type", but @a value
 * is not a valid mime-type).
 *
 * @a name may be a wc property or a regular property; but if it is an
 * entry property, return the error @c SVN_ERR_BAD_PROP_KIND, even if
 * @a skip_checks is true.
 *
 * Use @a pool for temporary allocation.  
 * 
 * @since New in 1.2.
 */
svn_error_t *svn_wc_prop_set2(const char *name,
                              const svn_string_t *value,
                              const char *path,
                              svn_wc_adm_access_t *adm_access,
                              svn_boolean_t skip_checks,
                              apr_pool_t *pool);


/**
 * Like svn_wc_prop_set2(), but with @a skip_checks always false.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_prop_set(const char *name,
                             const svn_string_t *value,
                             const char *path,
                             svn_wc_adm_access_t *adm_access,
                             apr_pool_t *pool);


/** Return true iff @a name is a 'normal' property name.  'Normal' is
 * defined as a user-visible and user-tweakable property that shows up
 * when you fetch a proplist.
 *
 * The function currently parses the namespace like so:
 *
 *   - 'svn:wc:'  ==>  a wcprop, stored/accessed separately via different API.
 *
 *   - 'svn:entry:' ==> an "entry" prop, shunted into the 'entries' file.
 *
 * If these patterns aren't found, then the property is assumed to be
 * Normal.
 */
svn_boolean_t svn_wc_is_normal_prop(const char *name);



/** Return true iff @a name is a 'wc' property name. */
svn_boolean_t svn_wc_is_wc_prop(const char *name);

/** Return true iff @a name is a 'entry' property name. */
svn_boolean_t svn_wc_is_entry_prop(const char *name);




/* Diffs */


/**
 * Return an @a editor/@a edit_baton for diffing a working copy against the
 * repository.
 *
 * @a anchor/@a target represent the base of the hierarchy to be compared.
 *
 * @a callbacks/@a callback_baton is the callback table to use when two
 * files are to be compared.
 *
 * @a recurse determines whether to descend into subdirectories when @a target
 * is a directory.  If @a recurse is @c TRUE then @a anchor should be part of 
 * an access baton set for the @a target hierarchy.
 *
 * @a ignore_ancestry determines whether paths that have discontinuous node
 * ancestry are treated as delete/add or as simple modifications.  If
 * @a ignore_ancestry is @c FALSE, then any discontinuous node ancestry will
 * result in the diff given as a full delete followed by an add.
 *
 * If @a use_text_base is true, then compare the repository against
 * the working copy's text-base files, rather than the working files.
 *
 * Normally, the difference from repository->working_copy is shown.
 * If @ reverse_order is true, then show working_copy->repository diffs.
 *
 * If @a cancel_func is non-null, it will be used along with @a cancel_baton 
 * to periodically check if the client has canceled the operation.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_get_diff_editor3(svn_wc_adm_access_t *anchor,
                                     const char *target,
                                     const svn_wc_diff_callbacks2_t *callbacks,
                                     void *callback_baton,
                                     svn_boolean_t recurse,
                                     svn_boolean_t ignore_ancestry,
                                     svn_boolean_t use_text_base,
                                     svn_boolean_t reverse_order,
                                     svn_cancel_func_t cancel_func,
                                     void *cancel_baton,
                                     const svn_delta_editor_t **editor,
                                     void **edit_baton,
                                     apr_pool_t *pool);


/**
 * Similar to svn_wc_get_diff_editor3(), but with an
 * @c svn_wc_diff_callbacks_t instead of @c svn_wc_diff_callbacks2_t.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_get_diff_editor2(svn_wc_adm_access_t *anchor,
                                     const char *target,
                                     const svn_wc_diff_callbacks_t *callbacks,
                                     void *callback_baton,
                                     svn_boolean_t recurse,
                                     svn_boolean_t ignore_ancestry,
                                     svn_boolean_t use_text_base,
                                     svn_boolean_t reverse_order,
                                     svn_cancel_func_t cancel_func,
                                     void *cancel_baton,
                                     const svn_delta_editor_t **editor,
                                     void **edit_baton,
                                     apr_pool_t *pool);


/**
 * Similar to svn_wc_get_diff_editor2(), but with @a ignore_ancestry
 * always set to @c FALSE.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_wc_get_diff_editor(svn_wc_adm_access_t *anchor,
                                    const char *target,
                                    const svn_wc_diff_callbacks_t *callbacks,
                                    void *callback_baton,
                                    svn_boolean_t recurse,
                                    svn_boolean_t use_text_base,
                                    svn_boolean_t reverse_order,
                                    svn_cancel_func_t cancel_func,
                                    void *cancel_baton,
                                    const svn_delta_editor_t **editor,
                                    void **edit_baton,
                                    apr_pool_t *pool);


/**
 * Compare working copy against the text-base.
 *
 * @a anchor/@a target represent the base of the hierarchy to be compared.
 *
 * @a callbacks/@a callback_baton is the callback table to use when two
 * files are to be compared.
 *
 * @a recurse determines whether to descend into subdirectories when @a target
 * is a directory.  If @a recurse is @c TRUE then @a anchor should be part of 
 * an access baton set for the @a target hierarchy.
 *
 * @a ignore_ancestry determines whether paths that have discontinuous node
 * ancestry are treated as delete/add or as simple modifications.  If
 * @a ignore_ancestry is @c FALSE, then any discontinuous node ancestry will
 * result in the diff given as a full delete followed by an add.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_wc_diff3(svn_wc_adm_access_t *anchor,
                          const char *target,
                          const svn_wc_diff_callbacks2_t *callbacks,
                          void *callback_baton,
                          svn_boolean_t recurse,
                          svn_boolean_t ignore_ancestry,
                          apr_pool_t *pool);

/**
 * Similar to svn_wc_diff3(), but with a @c svn_wc_diff_callbacks_t argument
 * instead of @c svn_wc_diff_callbacks2_t.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_wc_diff2(svn_wc_adm_access_t *anchor,
                          const char *target,
                          const svn_wc_diff_callbacks_t *callbacks,
                          void *callback_baton,
                          svn_boolean_t recurse,
                          svn_boolean_t ignore_ancestry,
                          apr_pool_t *pool);

/**
 * Similar to svn_wc_diff2(), but with @a ignore_ancestry always set
 * to @c FALSE.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_wc_diff(svn_wc_adm_access_t *anchor,
                         const char *target,
                         const svn_wc_diff_callbacks_t *callbacks,
                         void *callback_baton,
                         svn_boolean_t recurse,
                         apr_pool_t *pool);


/** Given a @a path to a file or directory under version control, discover
 * any local changes made to properties and/or the set of 'pristine'
 * properties.  @a adm_access is an access baton set for @a path.
 *
 * If @a propchanges is non-@c NULL, return these changes as an array of
 * @c svn_prop_t structures stored in @a *propchanges.  The structures and
 * array will be allocated in @a pool.  If there are no local property
 * modifications on @a path, then set @a *propchanges to @c NULL.
 *
 * If @a original_props is non-@c NULL, then set @a *original_props to
 * hashtable (<tt>const char *name</tt> -> <tt>const svn_string_t *value</tt>)
 * that represents the 'pristine' property list of @a path.  This hashtable is
 * allocated in @a pool, and can be used to compare old and new values of
 * properties.
 */
svn_error_t *svn_wc_get_prop_diffs(apr_array_header_t **propchanges,
                                   apr_hash_t **original_props,
                                   const char *path,
                                   svn_wc_adm_access_t *adm_access,
                                   apr_pool_t *pool);


/** The outcome of a merge carried out (or tried as a dry-run) by 
 * svn_wc_merge()
 */
typedef enum svn_wc_merge_outcome_t
{
   /** The working copy is (or would be) unchanged.  The changes to be
    * merged were already present in the working copy
    */
   svn_wc_merge_unchanged,

   /** The working copy has been (or would be) changed. */
   svn_wc_merge_merged,

   /** The working copy has been (or would be) changed, but there was (or
    * would be) a conflict
    */
   svn_wc_merge_conflict,

   /** No merge was performed, probably because the target file was
    * either absent or not under version control.
    */
   svn_wc_merge_no_merge

} svn_wc_merge_outcome_t;

/** Given paths to three fulltexts, merge the differences between @a left
 * and @a right into @a merge_target.  (It may help to know that @a left,
 * @a right, and @a merge_target correspond to "OLDER", "YOURS", and "MINE",
 * respectively, in the diff3 documentation.)  Use @a pool for any
 * temporary allocation.
 *
 * @a adm_access is an access baton with a write lock for the directory
 * containing @a merge_target.
 *
 * This function assumes that @a left and @a right are in repository-normal
 * form (linefeeds, with keywords contracted); if necessary,
 * @a merge_target is temporarily converted to this form to receive the
 * changes, then translated back again.
 *
 * If @a merge_target is absent, or present but not under version
 * control, then set @a *merge_outcome to @c svn_wc_merge_no_merge and
 * return success without merging anything.  (The reasoning is that if
 * the file is not versioned, then it is probably unrelated to the
 * changes being considered, so they should not be merged into it.)
 *
 * @a dry_run determines whether the working copy is modified.  When it
 * is @c FALSE the merge will cause @a merge_target to be modified, when it
 * is @c TRUE the merge will be carried out to determine the result but
 * @a merge_target will not be modified.
 *
 * If @a diff3_cmd is non-null, then use it as the diff3 command for
 * any merging; otherwise, use the built-in merge code.  If @a
 * merge_options is non-null, either pass its elements to @a diff3_cmd or
 * parse it and use as options to the internal merge code (@see
 * svn_diff_file_options_parse()).  @a merge_options must contain
 * <tt>const char *</tt> elements.
 *
 * The outcome of the merge is returned in @a *merge_outcome. If there is
 * a conflict and @a dry_run is @c FALSE, then
 *
 *   * Put conflict markers around the conflicting regions in
 *     @a merge_target, labeled with @a left_label, @a right_label, and
 *     @a target_label.  (If any of these labels are @c NULL, default 
 *     values will be used.)
 * 
 *   * Copy @a left, @a right, and the original @a merge_target to unique 
 *     names in the same directory as @a merge_target, ending with the 
 *     suffixes ".LEFT_LABEL", ".RIGHT_LABEL", and ".TARGET_LABEL"
 *     respectively.
 *
 *   * Mark the entry for @a merge_target as "conflicted", and track the
 *     above mentioned backup files in the entry as well.
 *
 * Binary case:
 *
 *  If @a merge_target is a binary file, then no merging is attempted,
 *  the merge is deemed to be a conflict.  If @a dry_run is @c FALSE the
 *  working @a merge_target is untouched, and copies of @a left and 
 *  @a right are created next to it using @a left_label and @a right_label.
 *  @a merge_target's entry is marked as "conflicted", and begins
 *  tracking the two backup files.  If @a dry_run is @c TRUE no files are
 *  changed.  The outcome of the merge is returned in @a *merge_outcome.
 *
 * @since New in 1.4.
 */
svn_error_t *svn_wc_merge2(enum svn_wc_merge_outcome_t *merge_outcome,
                           const char *left,
                           const char *right,
                           const char *merge_target,
                           svn_wc_adm_access_t *adm_access,
                           const char *left_label,
                           const char *right_label,
                           const char *target_label,
                           svn_boolean_t dry_run,
                           const char *diff3_cmd,
                           const apr_array_header_t *merge_options,
                           apr_pool_t *pool);


/** Similar to svn_wc_merge2(), but with @a merge_options set to NULL.
 *
 * @deprecated Provided for backwards compatibility with the 1.3 API.
 */
svn_error_t *svn_wc_merge(const char *left,
                          const char *right,
                          const char *merge_target,
                          svn_wc_adm_access_t *adm_access,
                          const char *left_label,
                          const char *right_label,
                          const char *target_label,
                          svn_boolean_t dry_run,
                          enum svn_wc_merge_outcome_t *merge_outcome,
                          const char *diff3_cmd,
                          apr_pool_t *pool);


/** Given a @a path under version control, merge an array of @a
 * propchanges into the path's existing properties.  @a propchanges is
 * an array of @c svn_prop_t objects, and @a baseprops is a hash
 * representing the original set of properties that @a propchanges is
 * working against.  @a adm_access is an access baton for the directory
 * containing @a path.
 *
 * If @a base_merge is @c FALSE only the working properties will be changed,
 * if it is @c TRUE both the base and working properties will be changed.
 *
 * If @a state is non-null, set @a *state to the state of the properties
 * after the merge.
 *
 * If conflicts are found when merging working properties, they are
 * described in a temporary .prej file (or appended to an already-existing
 * .prej file), and the entry is marked "conflicted".  Base properties
 * are changed unconditionally, if @a base_merge is @c TRUE, they never result
 * in a conflict.
 *
 * If @a path is not under version control, return the error
 * SVN_ERR_UNVERSIONED_RESOURCE and don't touch anyone's properties.
 *
 * @since New in 1.3.
 */
svn_error_t *
svn_wc_merge_props(svn_wc_notify_state_t *state,
                   const char *path,
                   svn_wc_adm_access_t *adm_access,
                   apr_hash_t *baseprops,
                   const apr_array_header_t *propchanges,
                   svn_boolean_t base_merge,
                   svn_boolean_t dry_run,
                   apr_pool_t *pool);


/** 
 * Similar to svn_wc_merge_props(), but no baseprops are given.
 * Instead, it's assumed that the incoming propchanges are based
 * against the working copy's own baseprops.  While this assumption is
 * correct for 'svn update', it's incorrect for 'svn merge', and can
 * cause flawed behavior.  (See issue #2035.)
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 */
svn_error_t *
svn_wc_merge_prop_diffs(svn_wc_notify_state_t *state,
                        const char *path,
                        svn_wc_adm_access_t *adm_access,
                        const apr_array_header_t *propchanges,
                        svn_boolean_t base_merge,
                        svn_boolean_t dry_run,
                        apr_pool_t *pool);



/** Given a @a path to a wc file, return a @a pristine_path which points to a
 * pristine version of the file.  This is needed so clients can do
 * diffs.  If the WC has no text-base, return a @c NULL instead of a
 * path.
 */
svn_error_t *svn_wc_get_pristine_copy_path(const char *path,
                                           const char **pristine_path,
                                           apr_pool_t *pool);


/**
 * Recurse from @a path, cleaning up unfinished log business.  Perform
 * necessary allocations in @a pool.  Any working copy locks under @a path 
 * will be taken over and then cleared by this function.  If @a diff3_cmd
 * is non-null, then use it as the diff3 command for any merging; otherwise,
 * use the built-in merge code.
 *
 * WARNING: there is no mechanism that will protect locks that are still 
 * being used.
 *
 * If @a cancel_func is non-null, invoke it with @a cancel_baton at
 * various points during the operation.  If it returns an error
 * (typically @c SVN_ERR_CANCELLED), return that error immediately.
 *
 * @since New in 1.2.
 */
svn_error_t *
svn_wc_cleanup2(const char *path,
                const char *diff3_cmd,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *pool);

/**
 * Similar to svn_wc_cleanup2(). @a optional_adm_access is an historic
 * relic and not used, it may be NULL.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *
svn_wc_cleanup(const char *path,
               svn_wc_adm_access_t *optional_adm_access,
               const char *diff3_cmd,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               apr_pool_t *pool);


/** Relocation validation callback typedef.
 *
 * Called for each relocated file/directory.  @a uuid, if non-null, contains
 * the expected repository UUID, @a url contains the tentative URL.
 *
 * @a baton is a closure object; it should be provided by the
 * implementation, and passed by the caller.
 *
 * If @a root is true, then the implementation should make sure that @a url
 * is the repository root.  Else, it can be an URL inside the repository.
 * @a pool may be used for temporary allocations.
 *
 * @since New in 1.4.
 */
typedef svn_error_t *(*svn_wc_relocation_validator2_t)(void *baton,
                                                       const char *uuid,
                                                       const char *url,
                                                       svn_boolean_t root,
                                                       apr_pool_t *pool);

/** Similar to @c svn_wc_relocation_validator2_t, but without
 * the @a root and @a pool arguments.  @a uuid will not be NULL in this version
 * of the function.
 *
 * @deprecated Provided for backwards compatibility with the 1.3 API.
 */
typedef svn_error_t *(*svn_wc_relocation_validator_t)(void *baton,
                                                      const char *uuid,
                                                      const char *url);

/** Change repository references at @a path that begin with @a from
 * to begin with @a to instead.  Perform necessary allocations in @a pool. 
 * If @a recurse is true, do so.  @a validator (and its baton,
 * @a validator_baton), will be called for each newly generated URL.
 *
 * @a adm_access is an access baton for the directory containing
 * @a path.
 */
svn_error_t *
svn_wc_relocate2(const char *path,
                 svn_wc_adm_access_t *adm_access,
                 const char *from,
                 const char *to,
                 svn_boolean_t recurse,
                 svn_wc_relocation_validator2_t validator,
                 void *validator_baton,
                 apr_pool_t *pool);

/** Similar to svn_wc_relocate2(), but uses @c svn_wc_relocation_validator_t.
 *
 * @deprecated Provided for backwards compatibility with the 1.3 API. */
svn_error_t *
svn_wc_relocate(const char *path,
                svn_wc_adm_access_t *adm_access,
                const char *from,
                const char *to,
                svn_boolean_t recurse,
                svn_wc_relocation_validator_t validator,
                void *validator_baton,
                apr_pool_t *pool);


/**
 * Revert changes to @a path (perhaps in a @a recursive fashion).  Perform
 * necessary allocations in @a pool.
 *
 * @a parent_access is an access baton for the directory containing @a path,
 * unless @a path is a wc root, in which case @a parent_access refers to 
 * @a path itself.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton at
 * various points during the reversion process.  If it returns an
 * error (typically @c SVN_ERR_CANCELLED), return that error
 * immediately.
 *
 * If @a use_commit_times is TRUE, then all reverted working-files
 * will have their timestamp set to the last-committed-time.  If
 * FALSE, the reverted working-files will be touched with the 'now' time.
 *
 * For each item reverted, @a notify_func will be called with @a notify_baton
 * and the path of the reverted item. @a notify_func may be @c NULL if this
 * notification is not needed.
 *
 * If @a path is not under version control, return the error
 * SVN_ERR_UNVERSIONED_RESOURCE.
 *
 * @since New in 1.2.
 */
svn_error_t *
svn_wc_revert2(const char *path, 
               svn_wc_adm_access_t *parent_access,
               svn_boolean_t recursive, 
               svn_boolean_t use_commit_times,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               svn_wc_notify_func2_t notify_func,
               void *notify_baton,
               apr_pool_t *pool);

/**
 * Similar to svn_wc_revert2(), but takes an @c svn_wc_notify_func_t instead.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *
svn_wc_revert(const char *path, 
              svn_wc_adm_access_t *parent_access,
              svn_boolean_t recursive, 
              svn_boolean_t use_commit_times,
              svn_cancel_func_t cancel_func,
              void *cancel_baton,
              svn_wc_notify_func_t notify_func,
              void *notify_baton,
              apr_pool_t *pool);


/* Tmp files */

/** Create a unique temporary file in administrative tmp/ area of
 * directory @a path.  Return a handle in @a *fp and the path
 * in @a *new_name. Either @a fp or @a new_name can be null.
 *
 * The flags will be <tt>APR_WRITE | APR_CREATE | APR_EXCL</tt> and
 * optionally @c APR_DELONCLOSE (if the @a delete_when argument is
 * set to @c svn_io_file_del_on_close).
 *
 * This means that as soon as @a fp is closed, the tmp file will vanish.
 *
 * @since New in 1.4
 */
svn_error_t *
svn_wc_create_tmp_file2(apr_file_t **fp,
                        const char **new_name,
                        const char *path,
                        svn_io_file_del_t delete_when,
                        apr_pool_t *pool);


/** Same as svn_wc_create_tmp_file2(), but with @a new_name set to @c NULL,
 * and without the ability to delete the file on pool cleanup.
 *
 * @deprecated For compatibility with 1.3 API
 */
svn_error_t *
svn_wc_create_tmp_file(apr_file_t **fp,
                       const char *path,
                       svn_boolean_t delete_on_close,
                       apr_pool_t *pool);



/* EOL conversion and keyword expansion. */

/** Set @a xlated_path to a translated copy of @a src
 * or to @a src itself if no translation is necessary.
 * That is, if @a versioned_file's properties indicate newline conversion or
 * keyword expansion, point @a *xlated_path to a copy of @a src
 * whose newlines and keywords are converted using the translation
 * as requested by @a flags.
 *
 * When translating to the normal form, inconsistent eol styles will be
 * repaired when appropriate for the given setting.  When translating
 * from normal form, no EOL repair is performed (consistency is assumed).
 * This behaviour can be overridden by specifying
 * @c SVN_WC_TRANSLATE_FORCE_EOL_REPAIR.
 *
 * The caller can explicitly request a new file to be returned by setting the
 * @c SVN_WC_TRANSLATE_FORCE_COPY flag in @a flags.
 *
 * This function is generally used to get a file that can be compared
 * meaningfully against @a versioned_file's text base, if
 * @c SVN_WC_TRANSLATE_TO_NF is specified, against @a versioned_file itself
 * if @c SVN_WC_TRANSLATE_FROM_NF is specified.
 *
 * Output files are created in the temp file area belonging to
 * @a versioned_file.  By default they will be deleted at pool cleanup.
 *
 * If @c SVN_WC_TRANSLATE_NO_OUTPUT_CLEANUP is specified, the default
 * pool cleanup handler to remove @a *xlated_path is not registered.
 *
 * If an error is returned, the effect on @a *xlated_path is undefined.
 *
 * @since New in 1.4
 */
svn_error_t *
svn_wc_translated_file2(const char **xlated_path,
                        const char *src,
                        const char *versioned_file,
                        svn_wc_adm_access_t *adm_access,
                        apr_uint32_t flags,
                        apr_pool_t *pool);


/** Same as svn_wc_translated_file2, but will never clean up
 * temporary files.
 *
 * @deprecated Provided for compatibility with the 1.3 API
 */
svn_error_t *svn_wc_translated_file(const char **xlated_p,
                                    const char *vfile,
                                    svn_wc_adm_access_t *adm_access,
                                    svn_boolean_t force_repair,
                                    apr_pool_t *pool);


/* Text/Prop Deltas Using an Editor */


/** Send the local modifications for versioned file @a path (with
 * matching @a file_baton) through @a editor, then close @a file_baton
 * afterwards.  Use @a pool for any temporary allocation and
 * @a adm_access as an access baton for @a path.
 * 
 * This process creates a copy of @a path with keywords and eol
 * untranslated.  If @a tempfile is non-null, set @a *tempfile to the
 * path to this copy.  Do not clean up the copy; caller can do that.
 * If @a digest is non-null, put the MD5 checksum of the
 * temporary file into @a digest, which must point to @c APR_MD5_DIGESTSIZE
 * bytes of storage.  (The purpose of handing back the tmp copy is that
 * it is usually about to become the new text base anyway, but the
 * installation of the new text base is outside the scope of this
 * function.)
 *
 * If @a fulltext, send the untranslated copy of @a path through @a editor 
 * as full-text; else send it as svndiff against the current text base.
 *
 * If sending a diff, and the recorded checksum for @a path's text-base
 * does not match the current actual checksum, then remove the tmp
 * copy (and set @a *tempfile to null if appropriate), and return the
 * error @c SVN_ERR_WC_CORRUPT_TEXT_BASE.
 *
 * @note This is intended for use with both infix and postfix
 * text-delta styled editor drivers.
 *
 * @since New in 1.4.
 */
svn_error_t *svn_wc_transmit_text_deltas2(const char **tempfile,
                                          unsigned char digest[],
                                          const char *path,
                                          svn_wc_adm_access_t *adm_access,
                                          svn_boolean_t fulltext,
                                          const svn_delta_editor_t *editor,
                                          void *file_baton,
                                          apr_pool_t *pool);

/** Similar to svn_wc_transmit_text_deltas2(), but with @a digest set to null.
 *
 * @deprecated Provided for backwards compatibility with the 1.3 API.
 */
svn_error_t *svn_wc_transmit_text_deltas(const char *path,
                                         svn_wc_adm_access_t *adm_access,
                                         svn_boolean_t fulltext,
                                         const svn_delta_editor_t *editor,
                                         void *file_baton,
                                         const char **tempfile,
                                         apr_pool_t *pool);


/** Given a @a path with its accompanying @a entry, transmit all local 
 * property modifications using the appropriate @a editor method (in 
 * conjunction with @a baton). @a adm_access is an access baton set
 * that contains @a path.  Use @a pool for all allocations.
 *
 * If a temporary file remains after this function is finished, the
 * path to that file is returned in @a *tempfile (so the caller can 
 * clean this up if it wishes to do so).
 */
svn_error_t *svn_wc_transmit_prop_deltas(const char *path,
                                         svn_wc_adm_access_t *adm_access,
                                         const svn_wc_entry_t *entry,
                                         const svn_delta_editor_t *editor,
                                         void *baton,
                                         const char **tempfile,
                                         apr_pool_t *pool);


/** Get the run-time configured list of ignore patterns from the 
 * @c svn_config_t's in the @a config hash, and store them in @a *patterns.
 * Allocate @a *patterns and its contents in @a pool.
 */
svn_error_t *svn_wc_get_default_ignores(apr_array_header_t **patterns,
                                        apr_hash_t *config,
                                        apr_pool_t *pool);

/** Get the list of ignore patterns from the @c svn_config_t's in the 
 * @a config hash and the local ignore patterns from the directory
 * in @a adm_access, and store them in @a *patterns.
 * Allocate @a *patterns and its contents in @a pool.
 *
 * @since New in 1.3.
 */
svn_error_t *svn_wc_get_ignores(apr_array_header_t **patterns,
                                apr_hash_t *config,
                                svn_wc_adm_access_t *adm_access,
                                apr_pool_t *pool);


/** Add @a lock to the working copy for @a path.  @a adm_access must contain
 * a write lock for @a path.  If @a path is read-only, due to locking
 * properties, make it writable.  Perform temporary allocations in @a
 * pool. */
svn_error_t *svn_wc_add_lock(const char *path, const svn_lock_t *lock,
                             svn_wc_adm_access_t *adm_access,
                             apr_pool_t *pool);

/** Remove any lock from @a path.  @a adm_access must contain a
 * write-lock for @a path.  If @a path has a lock and the locking
 * so specifies, make the file read-only.  Don't return an error if @a
 * path didn't have a lock.  Perform temporary allocations in @a pool. */
svn_error_t *svn_wc_remove_lock(const char *path,
                                svn_wc_adm_access_t *adm_access,
                                apr_pool_t *pool);


/** A structure to report the mix of revisions found within a working copy,
 * and whether any parts are switched or locally modified.
 *
 * @note Fields may be added to the end of this structure in future
 * versions.  Therefore, users shouldn't allocate structures of this
 * type, to preserve binary compatibility.
 *
 * @since New in 1.4
 */
typedef struct svn_wc_revision_status_t
{
  svn_revnum_t min_rev;   /**< Lowest revision found */
  svn_revnum_t max_rev;   /**< Highest revision found */

  svn_boolean_t switched; /**< Is anything switched? */
  svn_boolean_t modified; /**< Is anything modified? */
}
svn_wc_revision_status_t;

/** Set @a *result_p to point to a new @c svn_wc_revision_status_t structure
 * containing a summary of the revision range and status of the working copy
 * at @a wc_path (not including "externals").
 *
 * Set @a (*result_p)->min_rev and @a (*result_p)->max_rev respectively to the
 * lowest and highest revision numbers in the working copy.  If @a committed
 * is true, summarize the last-changed revisions, else the base revisions.
 *
 * Set @a (*result_p)->switched to indicate whether any item in the WC is
 * switched relative to its parent.  If @a trail_url is non-null, use it to
 * determine if @a wc_path itself is switched.  It should be any trailing
 * portion of @a wc_path's expected URL, long enough to include any parts
 * that the caller considers might be changed by a switch.  If it does not
 * match the end of @a wc_path's actual URL, then report a "switched"
 * status.
 *
 * Set @a (*result_p)->modified to indicate whether any item is locally
 * modified.
 *
 * If @a cancel_func is non-null, call it with @a cancel_baton to determine
 * if the client has cancelled the operation.
 *
 * Allocate *result_p in @a pool.
 *
 * @since New in 1.4
 */
svn_error_t *
svn_wc_revision_status(svn_wc_revision_status_t **result_p,
                       const char *wc_path,
                       const char *trail_url,
                       svn_boolean_t committed,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       apr_pool_t *pool);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* SVN_WC_H */
