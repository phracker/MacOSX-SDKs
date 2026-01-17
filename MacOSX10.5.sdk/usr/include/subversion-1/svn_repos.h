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
 * @file svn_repos.h
 * @brief tools built on top of the filesystem.
 */


#ifndef SVN_REPOS_H
#define SVN_REPOS_H

#include <apr_pools.h>
#include <apr_hash.h>
#include "svn_fs.h"
#include "svn_delta.h"
#include "svn_types.h"
#include "svn_error.h"
#include "svn_version.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ---------------------------------------------------------------*/

/**
 * Get libsvn_repos version information.
 *
 * @since New in 1.1.
 */
const svn_version_t *svn_repos_version(void);



/** Callback type for checking authorization on paths produced by (at
 * least) svn_repos_dir_delta().
 *
 * Set @a *allowed to TRUE to indicate that some operation is
 * authorized for @a path in @a root, or set it to FALSE to indicate
 * unauthorized (presumably according to state stored in @a baton).
 * 
 * Do not assume @a pool has any lifetime beyond this call.
 *
 * The exact operation being authorized depends on the callback
 * implementation.  For read authorization, for example, the caller
 * would implement an instance that does read checking, and pass it as
 * a parameter named [perhaps] 'authz_read_func'.  The receiver of
 * that parameter might also take another parameter named
 * 'authz_write_func', which although sharing this type, would be a
 * different implementation.
 *
 * @note If someday we want more sophisticated authorization states
 * than just yes/no, @a allowed can become an enum type.
 */
typedef svn_error_t *(*svn_repos_authz_func_t)(svn_boolean_t *allowed,
                                               svn_fs_root_t *root,
                                               const char *path,
                                               void *baton,
                                               apr_pool_t *pool);


/** An enum defining the kinds of access authz looks up.
 *
 * @since New in 1.3.
 */
typedef enum
{
  /** No access. */
  svn_authz_none = 0,

  /** Path can be read. */
  svn_authz_read = 1,

  /** Path can be altered. */
  svn_authz_write = 2,

  /** The other access credentials are recursive. */
  svn_authz_recursive = 4
} svn_repos_authz_access_t;


/** Callback type for checking authorization on paths produced by
 * the repository commit editor.
 *
 * Set @a *allowed to TRUE to indicate that the @a required access on
 * @a path in @a root is authorized, or set it to FALSE to indicate
 * unauthorized (presumable according to state stored in @a baton).
 *
 * If @a path is NULL, the callback should perform a global authz
 * lookup for the @a required access.  That is, the lookup should
 * check if the @a required access is granted for at least one path of
 * the repository, and set @a *allowed to TRUE if so.  @a root may
 * also be NULL if @a path is NULL.
 *
 * This callback is very similar to svn_repos_authz_func_t, with the
 * exception of the addition of the @a required parameter.
 * This is due to historical reasons: when authz was first implemented
 * for svn_repos_dir_delta(), it seemed there would need only checks
 * for read and write operations, hence the svn_repos_authz_func_t
 * callback prototype and usage scenario.  But it was then realized
 * that lookups due to copying needed to be recursive, and that
 * brute-force recursive lookups didn't square with the O(1)
 * performances a copy operation should have.
 *
 * So a special way to ask for a recursive lookup was introduced.  The
 * commit editor needs this capability to retain acceptable
 * performance.  Instead of revving the existing callback, causing
 * unnecessary revving of functions that don't actually need the
 * extended functionality, this second, more complete callback was
 * introduced, for use by the commit editor.
 *
 * Some day, it would be nice to reunite these two callbacks and do
 * the necessary revving anyway, but for the time being, this dual
 * callback mechanism will do.
 */
typedef svn_error_t *(*svn_repos_authz_callback_t)
  (svn_repos_authz_access_t required,
   svn_boolean_t *allowed,
   svn_fs_root_t *root,
   const char *path,
   void *baton,
   apr_pool_t *pool);

/**
 * A callback function type for use in svn_repos_get_file_revs().
 * @a baton is provided by the caller, @a path is the pathname of the file
 * in revision @a rev and @a rev_props are the revision properties.
 * If @a delta_handler and @a delta_baton are non-NULL, they may be set to a
 * handler/baton which will be called with the delta between the previous
 * revision and this one after the return of this callback.  They may be
 * left as NULL/NULL.
 * @a prop_diffs is an array of svn_prop_t elements indicating the property
 * delta for this and the previous revision.
 * @a pool may be used for temporary allocations, but you can't rely
 * on objects allocated to live outside of this particular call and the
 * immediately following calls to @a *delta_handler if any.
 *
 * @since New in 1.1.
 */
typedef svn_error_t *(*svn_repos_file_rev_handler_t)
  (void *baton,
   const char *path,
   svn_revnum_t rev,
   apr_hash_t *rev_props,
   svn_txdelta_window_handler_t *delta_handler,
   void **delta_baton,
   apr_array_header_t *prop_diffs,
   apr_pool_t *pool);


/** The repository object. */
typedef struct svn_repos_t svn_repos_t;

/* Opening and creating repositories. */


/** Find the root path of the repository that contains @a path.
 *
 * If a repository was found, the path to the root of the repository
 * is returned, else @c NULL. The pointer to the returned path may be
 * equal to @a path.
 */
const char *svn_repos_find_root_path(const char *path,
                                     apr_pool_t *pool);

/** Set @a *repos_p to a repository object for the repository at @a path.
 *
 * Allocate @a *repos_p in @a pool.
 *
 * Acquires a shared lock on the repository, and attaches a cleanup
 * function to @a pool to remove the lock.  If no lock can be acquired,
 * returns error, with undefined effect on @a *repos_p.  If an exclusive
 * lock is present, this blocks until it's gone.
 */
svn_error_t *svn_repos_open(svn_repos_t **repos_p,
                            const char *path,
                            apr_pool_t *pool);

/** Create a new Subversion repository at @a path, building the necessary
 * directory structure, creating the filesystem, and so on.
 * Return the repository object in @a *repos_p, allocated in @a pool.
 *
 * @a config is a client configuration hash of @c svn_config_t * items
 * keyed on config category names, and may be NULL.
 *
 * @a fs_config is passed to the filesystem, and may be NULL.
 *
 * @a unused_1 and @a unused_2 are not used and should be NULL.
 */
svn_error_t *svn_repos_create(svn_repos_t **repos_p, 
                              const char *path,
                              const char *unused_1,
                              const char *unused_2,
                              apr_hash_t *config,
                              apr_hash_t *fs_config,
                              apr_pool_t *pool);

/** Destroy the Subversion repository found at @a path, using @a pool for any
 * necessary allocations.
 */
svn_error_t *svn_repos_delete(const char *path, apr_pool_t *pool);

/** Return the filesystem associated with repository object @a repos. */
svn_fs_t *svn_repos_fs(svn_repos_t *repos);


/** Make a hot copy of the Subversion repository found at @a src_path 
 * to @a dst_path. 
 *
 * Copy a possibly live Subversion repository from @a src_path to
 * @a dst_path.  If @a clean_logs is @c TRUE, perform cleanup on the
 * source filesystem as part of the copy operation; currently, this
 * means deleting copied, unused logfiles for a Berkeley DB source
 * repository.
 */
svn_error_t * svn_repos_hotcopy(const char *src_path,
                                const char *dst_path,
                                svn_boolean_t clean_logs,
                                apr_pool_t *pool);

/**
 * Run database recovery procedures on the repository at @a path,
 * returning the database to a consistent state.  Use @a pool for all
 * allocation.
 *
 * Acquires an exclusive lock on the repository, recovers the
 * database, and releases the lock.  If an exclusive lock can't be
 * acquired, returns error.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_repos_recover(const char *path, apr_pool_t *pool);

/**
 * Run database recovery procedures on the repository at @a path,
 * returning the database to a consistent state.  Use @a pool for all
 * allocation.
 *
 * Acquires an exclusive lock on the repository, recovers the
 * database, and releases the lock.  If an exclusive lock can't be
 * acquired, returns error.
 *
 * If @a nonblocking is TRUE, an error of type EWOULDBLOCK is
 * returned if the lock is not immediately available.
 *
 * If @a start_callback is not NULL, it will be called with @a
 * start_callback_baton as argument before the recovery starts, but
 * after the exclusive lock has been acquired.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_repos_recover2(const char *path,
                                svn_boolean_t nonblocking,
                                svn_error_t *(*start_callback)(void *baton),
                                void *start_callback_baton,
                                apr_pool_t *pool);

/** This function is a wrapper around svn_fs_berkeley_logfiles(),
 * returning log file paths relative to the root of the repository.
 *
 * @copydoc svn_fs_berkeley_logfiles()
 */
svn_error_t *svn_repos_db_logfiles(apr_array_header_t **logfiles,
                                   const char *path,
                                   svn_boolean_t only_unused,
                                   apr_pool_t *pool);



/* Repository Paths */

/** Return the top-level repository path allocated in @a pool. */
const char *svn_repos_path(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's filesystem directory, allocated in
 * @a pool.
 */
const char *svn_repos_db_env(svn_repos_t *repos, apr_pool_t *pool);

/** Return path to @a repos's config directory, allocated in @a pool. */
const char *svn_repos_conf_dir(svn_repos_t *repos, apr_pool_t *pool);

/** Return path to @a repos's svnserve.conf, allocated in @a pool. */
const char *svn_repos_svnserve_conf(svn_repos_t *repos, apr_pool_t *pool);

/** Return path to @a repos's lock directory, allocated in @a pool. */
const char *svn_repos_lock_dir(svn_repos_t *repos, apr_pool_t *pool);

/** Return path to @a repos's db lockfile, allocated in @a pool. */
const char *svn_repos_db_lockfile(svn_repos_t *repos, apr_pool_t *pool);

/** Return path to @a repos's db logs lockfile, allocated in @a pool. */
const char *svn_repos_db_logs_lockfile(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's hook directory, allocated in @a pool. */
const char *svn_repos_hook_dir(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's start-commit hook, allocated in @a pool. */
const char *svn_repos_start_commit_hook(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's pre-commit hook, allocated in @a pool. */
const char *svn_repos_pre_commit_hook(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's post-commit hook, allocated in @a pool. */
const char *svn_repos_post_commit_hook(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's pre-revprop-change hook, allocated in 
 * @a pool.
 */
const char *svn_repos_pre_revprop_change_hook(svn_repos_t *repos,
                                              apr_pool_t *pool);

/** Return the path to @a repos's post-revprop-change hook, allocated in 
 * @a pool.
 */
const char *svn_repos_post_revprop_change_hook(svn_repos_t *repos,
                                               apr_pool_t *pool);


/** @defgroup svn_repos_lock_hooks paths to lock hooks
 * @{ 
 * @since New in 1.2. */

/** Return the path to @a repos's pre-lock hook, allocated in @a pool. */
const char *svn_repos_pre_lock_hook(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's post-lock hook, allocated in @a pool. */
const char *svn_repos_post_lock_hook(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's pre-unlock hook, allocated in @a pool. */
const char *svn_repos_pre_unlock_hook(svn_repos_t *repos, apr_pool_t *pool);

/** Return the path to @a repos's post-unlock hook, allocated in @a pool. */
const char *svn_repos_post_unlock_hook(svn_repos_t *repos, apr_pool_t *pool);

/** @} */

/* ---------------------------------------------------------------*/

/* Reporting the state of a working copy, for updates. */


/**
 * Construct and return a @a report_baton that will be passed to the
 * other functions in this section to describe the state of a pre-existing
 * tree (typically, a working copy).  When the report is finished,
 * @a editor/@a edit_baton will be driven in such a way as to transform the
 * existing tree to @a revnum and, if @a tgt_path is non-NULL, switch the
 * reported hierarchy to @a tgt_path.
 *
 * @a fs_base is the absolute path of the node in the filesystem at which
 * the comparison should be rooted.  @a target is a single path component,
 * used to limit the scope of the report to a single entry of @a fs_base,
 * or "" if all of @a fs_base itself is the main subject of the report.
 *
 * @a tgt_path and @a revnum is the fs path/revision pair that is the
 * "target" of the delta.  @a tgt_path should be provided only when
 * the source and target paths of the report differ.  That is, @a tgt_path
 * should *only* be specified when specifying that the resultant editor
 * drive be one that transforms the reported hierarchy into a pristine tree
 * of @a tgt_path at revision @a revnum.  A @c NULL value for @a tgt_path
 * will indicate that the editor should be driven in such a way as to
 * transform the reported hierarchy to revision @a revnum, preserving the
 * reported hierarchy.
 *
 * @a text_deltas instructs the driver of the @a editor to enable
 * the generation of text deltas.
 *
 * @a recurse instructs the driver of the @a editor to send a recursive
 * delta (or not.)
 *
 * @a ignore_ancestry instructs the driver to ignore node ancestry
 * when determining how to transmit differences.
 *
 * The @a authz_read_func and @a authz_read_baton are passed along to
 * svn_repos_dir_delta(); see that function for how they are used.
 *
 * All allocation for the context and collected state will occur in
 * @a pool.
 *
 * @note @a username isn't used and should be removed if this function is
 * revised.
 */
svn_error_t *
svn_repos_begin_report(void **report_baton,
                       svn_revnum_t revnum,
                       const char *username,
                       svn_repos_t *repos,
                       const char *fs_base,
                       const char *target,
                       const char *tgt_path,
                       svn_boolean_t text_deltas,
                       svn_boolean_t recurse,
                       svn_boolean_t ignore_ancestry,
                       const svn_delta_editor_t *editor,
                       void *edit_baton,
                       svn_repos_authz_func_t authz_read_func,
                       void *authz_read_baton,
                       apr_pool_t *pool);

/**
 * Given a @a report_baton constructed by svn_repos_begin_report(),
 * record the presence of @a path at @a revision in the current tree.
 *
 * @a path is relative to the anchor/target used in the creation of the
 * @a report_baton.
 *
 * @a revision may be SVN_INVALID_REVNUM if (for example) @a path represents
 * a locally-added path with no revision number.
 *
 * The first call of this in a given report usually passes an empty
 * @a path; this is used to set up the correct root revision for the editor
 * drive.
 *
 * If @a start_empty is true and @a path is a directory, then require the
 * caller to explicitly provide all the children of @path - do not assume
 * that the tree also contains all the children of @a path at @a revision.
 * This is for 'low confidence' client reporting.
 * 
 * If the caller has a lock token for @a path, then @a lock_token should
 * be set to that token.  Else, @a lock_token should be NULL.
 *
 * All temporary allocations are done in @a pool.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_repos_set_path2(void *report_baton,
                                 const char *path,
                                 svn_revnum_t revision,
                                 svn_boolean_t start_empty,
                                 const char *lock_token,
                                 apr_pool_t *pool);

/**
 * Similar to svn_repos_set_path2(), but with @a lock_token set to @c NULL.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_repos_set_path(void *report_baton,
                                const char *path,
                                svn_revnum_t revision,
                                svn_boolean_t start_empty,
                                apr_pool_t *pool);

/**
 * Given a @a report_baton constructed by svn_repos_begin_report(), 
 * record the presence of @path in the current tree, containing the contents
 * of @a link_path at @a revision.
 *
 * Note that while @a path is relative to the anchor/target used in the
 * creation of the @a report_baton, @a link_path is an absolute filesystem
 * path!
 *
 * If @a start_empty is true and @a path is a directory, then require the
 * caller to explicitly provide all the children of @path - do not assume
 * that the tree also contains all the children of @a link_path at
 * @a revision.  This is for 'low confidence' client reporting.
 *
 * If the caller has a lock token for @a link_path, then @a lock_token
 * should be set to that token.  Else, @a lock_token should be NULL.
 *
 * All temporary allocations are done in @a pool.
 *
 * @since New in 1.2.
 */
svn_error_t *svn_repos_link_path2(void *report_baton,
                                  const char *path,
                                  const char *link_path,
                                  svn_revnum_t revision,
                                  svn_boolean_t start_empty,
                                  const char *lock_token,
                                  apr_pool_t *pool);

/**
 * Similar to svn_repos_link_path2(), but with @a lock_token set to @c NULL.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_repos_link_path(void *report_baton,
                                 const char *path,
                                 const char *link_path,
                                 svn_revnum_t revision,
                                 svn_boolean_t start_empty,
                                 apr_pool_t *pool);

/** Given a @a report_baton constructed by svn_repos_begin_report(), 
 * record the non-existence of @a path in the current tree.
 *
 * (This allows the reporter's driver to describe missing pieces of a
 * working copy, so that 'svn up' can recreate them.)
 *
 * All temporary allocations are done in @a pool.
 */
svn_error_t *svn_repos_delete_path(void *report_baton,
                                   const char *path,
                                   apr_pool_t *pool);

/** Given a @a report_baton constructed by svn_repos_begin_report(),
 * finish the report and drive the editor as specified when the report
 * baton was constructed.
 *
 * If an error occurs during the driving of the editor, do NOT abort the
 * edit; that responsibility belongs to the caller of this function, if
 * it happens at all.
 *
 * After the call to this function, @a report_baton is no longer valid;
 * it should not be passed to any other reporting functions, including
 * svn_repos_abort_report().
 */
svn_error_t *svn_repos_finish_report(void *report_baton,
                                     apr_pool_t *pool);


/** Given a @a report_baton constructed by svn_repos_begin_report(),
 * abort the report.  This function can be called anytime before
 * svn_repos_finish_report() is called.
 *
 * After the call to this function, @a report_baton is no longer valid;
 * it should not be passed to any other reporting functions.
 */
svn_error_t *svn_repos_abort_report(void *report_baton,
                                    apr_pool_t *pool);


/* ---------------------------------------------------------------*/

/* The magical dir_delta update routines. */

/** Use the provided @a editor and @a edit_baton to describe the changes
 * necessary for making a given node (and its descendants, if it is a
 * directory) under @a src_root look exactly like @a tgt_path under
 * @a tgt_root.  @a src_entry is the node to update.  If @a src_entry
 * is empty, then compute the difference between the entire tree
 * anchored at @a src_parent_dir under @a src_root and @a tgt_path
 * under @a target_root.  Else, describe the changes needed to update
 * only that entry in @a src_parent_dir.  Typically, callers of this
 * function will use a @a tgt_path that is the concatenation of @a
 * src_parent_dir and @a src_entry.
 *
 * @a src_root and @a tgt_root can both be either revision or transaction
 * roots.  If @a tgt_root is a revision, @a editor's set_target_revision()
 * will be called with the @a tgt_root's revision number, else it will
 * not be called at all.
 *
 * If @a authz_read_func is non-null, invoke it before any call to
 *
 *    @a editor->open_root
 *    @a editor->add_directory
 *    @a editor->open_directory
 *    @a editor->add_file
 *    @a editor->open_file
 *
 * passing @a tgt_root, the same path that would be passed to the
 * editor function in question, and @a authz_read_baton.  If the
 * @a *allowed parameter comes back TRUE, then proceed with the planned
 * editor call; else if FALSE, then invoke @a editor->absent_file or
 * @a editor->absent_directory as appropriate, except if the planned
 * editor call was open_root, throw SVN_ERR_AUTHZ_ROOT_UNREADABLE.
 *
 * If @a text_deltas is @c FALSE, send a single @c NULL txdelta window to 
 * the window handler returned by @a editor->apply_textdelta().
 *
 * If @a entry_props is @c TRUE, accompany each opened/added entry with
 * propchange editor calls that relay special "entry props" (this
 * is typically used only for working copy updates).
 *
 * @a ignore_ancestry instructs the function to ignore node ancestry
 * when determining how to transmit differences.
 *
 * Before completing successfully, this function calls @a editor's
 * close_edit(), so the caller should expect its @a edit_baton to be
 * invalid after its use with this function.
 *
 * Do any allocation necessary for the delta computation in @a pool.
 * This function's maximum memory consumption is at most roughly
 * proportional to the greatest depth of the tree under @a tgt_root, not
 * the total size of the delta.
 */
svn_error_t *
svn_repos_dir_delta(svn_fs_root_t *src_root,
                    const char *src_parent_dir,
                    const char *src_entry,
                    svn_fs_root_t *tgt_root,
                    const char *tgt_path,
                    const svn_delta_editor_t *editor,
                    void *edit_baton,
                    svn_repos_authz_func_t authz_read_func,
                    void *authz_read_baton,
                    svn_boolean_t text_deltas,
                    svn_boolean_t recurse,
                    svn_boolean_t entry_props,
                    svn_boolean_t ignore_ancestry,
                    apr_pool_t *pool);

/** Use the provided @a editor and @a edit_baton to describe the
 * skeletal changes made in a particular filesystem @a root
 * (revision or transaction).
 *
 * Changes will be limited to those within @a base_dir, and if 
 * @a low_water_mark is set to something other than @c SVN_INVALID_REVNUM
 * it is assumed that the client has no knowledge of revisions prior to
 * @a low_water_mark.  Together, these two arguments define the portion of
 * the tree that the client is assumed to have knowledge of, and thus any
 * copies of data from outside that part of the tree will be sent in their
 * entirety, not as simple copies or deltas against a previous version.
 *
 * The @a editor passed to this function should be aware of the fact
 * that, if @a send_deltas is false, calls to its change_dir_prop(),
 * change_file_prop(), and apply_textdelta() functions will not
 * contain meaningful data, and merely serve as indications that
 * properties or textual contents were changed.
 *
 * If @a send_deltas is @c TRUE, the text and property deltas for changes
 * will be sent, otherwise null text deltas and empty prop changes will be
 * used.
 *
 * If @a authz_read_func is non-NULL, it will be used to determine if the
 * user has read access to the data being accessed.  Data that the user
 * cannot access will be skipped.
 *
 * @note This editor driver passes SVN_INVALID_REVNUM for all
 * revision parameters in the editor interface except the copyfrom
 * parameter of the add_file() and add_directory() editor functions.
 *
 * @since New in 1.4.
 */
svn_error_t *
svn_repos_replay2(svn_fs_root_t *root,
                  const char *base_dir,
                  svn_revnum_t low_water_mark,
                  svn_boolean_t send_deltas,
                  const svn_delta_editor_t *editor,
                  void *edit_baton,
                  svn_repos_authz_func_t authz_read_func,
                  void *authz_read_baton,
                  apr_pool_t *pool);

/**
 * Similar to svn_repos_replay2(), but with @a base_dir set to @c "",
 * @a low_water_mark set to @c SVN_INVALID_REVNUM, @a send_deltas
 * set to @c FALSE, and @a authz_read_func and @a authz_read_baton
 * set to @c NULL.
 *
 * @deprecated Provided for backward compatibility with the 1.3 API.
 */
svn_error_t *
svn_repos_replay(svn_fs_root_t *root,
                 const svn_delta_editor_t *editor,
                 void *edit_baton,
                 apr_pool_t *pool);

/* ---------------------------------------------------------------*/

/* Making commits. */

/**
 * Return an @a editor and @a edit_baton to commit changes to @a session->fs,
 * beginning at location 'rev:@a base_path', where "rev" is the argument
 * given to open_root().
 *
 * @a repos is a previously opened repository.  @a repos_url is the
 * decoded URL to the base of the repository, and is used to check
 * copyfrom paths.  @a txn is a filesystem transaction object to use
 * during the commit, or @c NULL to indicate that this function should
 * create (and fully manage) a new transaction.
 *
 * Iff @a user is not @c NULL, store it as the author of the commit
 * transaction.
 *
 * Iff @a log_msg is not @c NULL, store it as the log message
 * associated with the commit transaction.
 *
 * Iff @a authz_callback is provided, check read/write authorizations
 * on paths accessed by editor operations.  An operation which fails
 * due to authz will return SVN_ERR_AUTHZ_UNREADABLE or
 * SVN_ERR_AUTHZ_UNWRITABLE.
 *
 * Calling @a (*editor)->close_edit completes the commit.  Before
 * @c close_edit returns, but after the commit has succeeded, it will
 * invoke @a callback with the new revision number, the commit date (as a
 * <tt>const char *</tt>), commit author (as a <tt>const char *</tt>), and
 * @a callback_baton as arguments.  If @a callback returns an error, that
 * error will be returned from @c close_edit, otherwise if there was a
 * post-commit hook failure, then that error will be returned and will
 * have code SVN_ERR_REPOS_POST_COMMIT_HOOK_FAILED.
 *
 * Calling @a (*editor)->abort_edit aborts the commit, and will also
 * abort the commit transaction unless @a txn was supplied (not @c
 * NULL).  Callers who supply their own transactions are responsible
 * for cleaning them up (either by committing them, or aborting them).
 *
 * @since New in 1.4.
 */
svn_error_t *
svn_repos_get_commit_editor4(const svn_delta_editor_t **editor,
                             void **edit_baton,
                             svn_repos_t *repos,
                             svn_fs_txn_t *txn,
                             const char *repos_url,
                             const char *base_path,
                             const char *user,
                             const char *log_msg,
                             svn_commit_callback2_t callback,
                             void *callback_baton,
                             svn_repos_authz_callback_t authz_callback,
                             void *authz_baton,
                             apr_pool_t *pool);

/**
 * Similar to svn_repos_get_commit_editor4(), but
 * uses the svn_commit_callback_t type.
 *
 * @since New in 1.3.
 *
 * @deprecated Provided for backward compatibility with the 1.3 API.
 */
svn_error_t *
svn_repos_get_commit_editor3(const svn_delta_editor_t **editor,
                             void **edit_baton,
                             svn_repos_t *repos,
                             svn_fs_txn_t *txn,
                             const char *repos_url,
                             const char *base_path,
                             const char *user,
                             const char *log_msg,
                             svn_commit_callback_t callback,
                             void *callback_baton,
                             svn_repos_authz_callback_t authz_callback,
                             void *authz_baton,
                             apr_pool_t *pool);

/**
 * Similar to svn_repos_get_commit_editor3(), but with @a
 * authz_callback and @a authz_baton set to @c NULL.
 *
 * @deprecated Provided for backward compatibility with the 1.2 API.
 */
svn_error_t *svn_repos_get_commit_editor2(const svn_delta_editor_t **editor,
                                          void **edit_baton,
                                          svn_repos_t *repos,
                                          svn_fs_txn_t *txn,
                                          const char *repos_url,
                                          const char *base_path,
                                          const char *user,
                                          const char *log_msg,
                                          svn_commit_callback_t callback,
                                          void *callback_baton,
                                          apr_pool_t *pool);


/**
 * Similar to svn_repos_get_commit_editor2(), but with @a txn always
 * set to @c NULL.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *svn_repos_get_commit_editor(const svn_delta_editor_t **editor,
                                         void **edit_baton,
                                         svn_repos_t *repos,
                                         const char *repos_url,
                                         const char *base_path,
                                         const char *user,
                                         const char *log_msg,
                                         svn_commit_callback_t callback,
                                         void *callback_baton,
                                         apr_pool_t *pool);

/* ---------------------------------------------------------------*/

/* Finding particular revisions. */

/** Set @a *revision to the revision number in @a repos's filesystem that was
 * youngest at time @a tm.
 */
svn_error_t *
svn_repos_dated_revision(svn_revnum_t *revision,
                         svn_repos_t *repos,
                         apr_time_t tm,
                         apr_pool_t *pool);
                          

/** Given a @a root/@a path within some filesystem, return three pieces of
 * information allocated in @a pool:
 *
 *    - set @a *committed_rev to the revision in which the object was
 *      last modified.  (In fs parlance, this is the revision in which
 *      the particular node-rev-id was 'created'.)
 *  
 *    - set @a *committed_date to the date of said revision, or @c NULL
 *      if not available.
 *
 *    - set @a *last_author to the author of said revision, or @c NULL
 *      if not available.
 */
svn_error_t *
svn_repos_get_committed_info(svn_revnum_t *committed_rev,
                             const char **committed_date,
                             const char **last_author,
                             svn_fs_root_t *root,
                             const char *path,
                             apr_pool_t *pool);


/**
 * Set @a *dirent to an @c svn_dirent_t associated with @a path in @a
 * root.  If @a path does not exist in @a root, set @a *dirent to
 * NULL.  Use @a pool for memory allocation.
 *
 * @since New in 1.2.
 */
svn_error_t *
svn_repos_stat(svn_dirent_t **dirent,
               svn_fs_root_t *root,
               const char *path,
               apr_pool_t *pool);


/** Callback type for use with svn_repos_history().  @a path and @a
 * revision represent interesting history locations in the lifetime
 * of the path passed to svn_repos_history().  @a baton is the same
 * baton given to svn_repos_history().  @a pool is provided for the
 * convenience of the implementor, who should not expect it to live
 * longer than a single callback call.
 */
typedef svn_error_t *(*svn_repos_history_func_t)(void *baton,
                                                 const char *path,
                                                 svn_revnum_t revision,
                                                 apr_pool_t *pool);

/**
 * Call @a history_func (with @a history_baton) for each interesting
 * history location in the lifetime of @a path in @a fs, from the
 * youngest of @a end and @ start to the oldest.  Only cross
 * filesystem copy history if @a cross_copies is @c TRUE.  And do all
 * of this in @a pool.
 *
 * If @a authz_read_func is non-NULL, then use it (and @a
 * authz_read_baton) to verify that @a path in @a end is readable; if
 * not, return SVN_ERR_AUTHZ_UNREADABLE.  Also verify the readability
 * of every ancestral path/revision pair before pushing them at @a
 * history_func.  If a pair is deemed unreadable, then do not send
 * them; instead, immediately stop traversing history and return
 * SVN_NO_ERROR.
 *
 * @since New in 1.1.
 */
svn_error_t *
svn_repos_history2(svn_fs_t *fs,
                   const char *path,
                   svn_repos_history_func_t history_func,
                   void *history_baton,
                   svn_repos_authz_func_t authz_read_func,
                   void *authz_read_baton,
                   svn_revnum_t start,
                   svn_revnum_t end,
                   svn_boolean_t cross_copies,
                   apr_pool_t *pool);

/**
 * Similar to svn_repos_history2(), but with @a authz_read_func
 * and @a authz_read_baton always set to NULL.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *
svn_repos_history(svn_fs_t *fs,
                  const char *path,
                  svn_repos_history_func_t history_func,
                  void *history_baton,
                  svn_revnum_t start,
                  svn_revnum_t end,
                  svn_boolean_t cross_copies,
                  apr_pool_t *pool);


/**
 * Set @a *locations to be a mapping of the revisions to the paths of
 * the file @a fs_path present at the repository in revision
 * @a peg_revision, where the revisions are taken out of the array
 * @a location_revisions.
 *
 * @a location_revisions is an array of svn_revnum_t's and @a *locations
 * maps 'svn_revnum_t *' to 'const char *'.
 *
 * If optional @a authz_read_func is non-NULL, then use it (and @a
 * authz_read_baton) to verify that the peg-object is readable.  If not,
 * return SVN_ERR_AUTHZ_UNREADABLE.  Also use the @a authz_read_func
 * to check that every path returned in the hash is readable.  If an
 * unreadable path is encountered, stop tracing and return
 * SVN_NO_ERROR.
 *
 * @a pool is used for all allocations.
 *
 * @since New in 1.1.
 */
svn_error_t *
svn_repos_trace_node_locations(svn_fs_t *fs,
                               apr_hash_t **locations,
                               const char *fs_path,
                               svn_revnum_t peg_revision,
                               apr_array_header_t *location_revisions,
                               svn_repos_authz_func_t authz_read_func,
                               void *authz_read_baton,
                               apr_pool_t *pool);

/* ### other queries we can do someday --

     * fetch the last revision created by <user>
         (once usernames become revision properties!)
     * fetch the last revision where <path> was modified
     
*/



/* ---------------------------------------------------------------*/

/* Retrieving log messages. */


/**
 * Invoke @a receiver with @a receiver_baton on each log message from 
 * @a start to @a end in @a repos's filesystem.  @a start may be greater 
 * or less than @a end; this just controls whether the log messages are 
 * processed in descending or ascending revision number order.
 *
 * If @a start or @a end is @c SVN_INVALID_REVNUM, it defaults to youngest.
 *
 * If @a paths is non-null and has one or more elements, then only show
 * revisions in which at least one of @a paths was changed (i.e., if
 * file, text or props changed; if dir, props or entries changed or any node
 * changed below it).  Each path is a <tt>const char *</tt> representing
 * an absolute path in the repository.
 *
 * If @a limit is non-zero then only invoke @a receiver on the first
 * @a limit logs.
 *
 * If @a discover_changed_paths, then each call to @a receiver passes a
 * hash mapping paths committed in that revision to information about them
 * as the receiver's @a changed_paths argument.
 * Otherwise, each call to @a receiver passes null for @a changed_paths.
 *
 * If @a strict_node_history is set, copy history (if any exists) will
 * not be traversed while harvesting revision logs for each path.
 *
 * If any invocation of @a receiver returns error, return that error
 * immediately and without wrapping it.
 *
 * If @a start or @a end is a non-existent revision, return the error
 * @c SVN_ERR_FS_NO_SUCH_REVISION, without ever invoking @a receiver.
 *
 * If optional @a authz_read_func is non-NULL, then use this function
 * (along with optional @a authz_read_baton) to check the readability
 * of each changed-path in each revision about to be "pushed" at
 * @a receiver.  If a revision has all unreadable changed-paths, then
 * don't push the revision at all.  If a revision has a mixture of
 * readable and unreadable changed-paths, then silently omit the
 * unreadable changed-paths when pushing the revision.
 *
 * See also the documentation for @c svn_log_message_receiver_t.
 *
 * Use @a pool for temporary allocations.
 *
 * @since New in 1.2.
 */
svn_error_t *
svn_repos_get_logs3(svn_repos_t *repos,
                    const apr_array_header_t *paths,
                    svn_revnum_t start,
                    svn_revnum_t end,
                    int limit,
                    svn_boolean_t discover_changed_paths,
                    svn_boolean_t strict_node_history,
                    svn_repos_authz_func_t authz_read_func,
                    void *authz_read_baton,
                    svn_log_message_receiver_t receiver,
                    void *receiver_baton,
                    apr_pool_t *pool);


/**
 * Same as svn_repos_get_logs3(), but with @a limit always set to 0.
 *
 * @deprecated Provided for backward compatibility with the 1.1 API.
 */
svn_error_t *
svn_repos_get_logs2(svn_repos_t *repos,
                    const apr_array_header_t *paths,
                    svn_revnum_t start,
                    svn_revnum_t end,
                    svn_boolean_t discover_changed_paths,
                    svn_boolean_t strict_node_history,
                    svn_repos_authz_func_t authz_read_func,
                    void *authz_read_baton,
                    svn_log_message_receiver_t receiver,
                    void *receiver_baton,
                    apr_pool_t *pool);

/**
 * Same as svn_repos_get_logs2(), but with @a authz_read_func and
 * @a authz_read_baton always set to NULL.
 * 
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *
svn_repos_get_logs(svn_repos_t *repos,
                   const apr_array_header_t *paths,
                   svn_revnum_t start,
                   svn_revnum_t end,
                   svn_boolean_t discover_changed_paths,
                   svn_boolean_t strict_node_history,
                   svn_log_message_receiver_t receiver,
                   void *receiver_baton,
                   apr_pool_t *pool);



/* ---------------------------------------------------------------*/

/* Retreiving multiple revisions of a file. */

/**
 * Retrieve a subset of the interesting revisions of a file @a path in
 * @a repos as seen in revision @a end.  Invoke @a handler with
 * @a handler_baton as its first argument for each such revision.
 * @a pool is used for all allocations.  See svn_fs_history_prev() for
 * a discussion of interesting revisions.
 *
 * If optional @a authz_read_func is non-NULL, then use this function
 * (along with optional @a authz_read_baton) to check the readability
 * of the rev-path in each interesting revision encountered.
 *
 * Revision discovery happens from @a end to @a start, and if an
 * unreadable revision is encountered before @a start is reached, then
 * revision discovery stops and only the revisions from @a end to the
 * oldest readable revision are returned (So it will appear that @a
 * path was added without history in the latter revision).
 *
 * If there is an interesting revision of the file that is less than or
 * equal to start, the iteration will start at that revision.  Else, the
 * iteration will start at the first revision of the file in the repository,
 * which has to be less than or equal to end.  Note that if the function
 * succeeds, @a handler will have been called at least once.
 *
 * In a series of calls, the file contents for the first interesting revision
 * will be provided as a text delta against the empty file.  In the following
 * calls, the delta will be against the contents for the previous call.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_repos_get_file_revs(svn_repos_t *repos,
                                     const char *path,
                                     svn_revnum_t start,
                                     svn_revnum_t end,
                                     svn_repos_authz_func_t authz_read_func,
                                     void *authz_read_baton,
                                     svn_repos_file_rev_handler_t handler,
                                     void *handler_baton,
                                     apr_pool_t *pool);


/* ---------------------------------------------------------------*/

/**
 * @defgroup svn_repos_hook_wrappers Hook-sensitive wrappers for libsvn_fs 
 * routines.
 * @{
 */

/** Like svn_fs_commit_txn(), but invoke the @a repos's pre- and
 * post-commit hooks around the commit.  Use @a pool for any necessary
 * allocations.
 *
 * If the pre-commit hook or svn_fs_commit_txn() fails, throw the
 * original error to caller.  If an error occurs when running the
 * post-commit hook, return the original error wrapped with
 * SVN_ERR_REPOS_POST_COMMIT_HOOK_FAILED.  If the caller sees this
 * error, it knows that the commit succeeded anyway.
 *
 * @a conflict_p, @a new_rev, and @a txn are as in svn_fs_commit_txn().
 */
svn_error_t *svn_repos_fs_commit_txn(const char **conflict_p,
                                     svn_repos_t *repos,
                                     svn_revnum_t *new_rev,
                                     svn_fs_txn_t *txn,
                                     apr_pool_t *pool);

/** Like svn_fs_begin_txn(), but use @a author and @a log_msg to set the
 * corresponding properties on transaction @a *txn_p.  @a repos is the
 * repository object which contains the filesystem.  @a rev, @a *txn_p, and
 * @a pool are as in svn_fs_begin_txn().
 *
 * Before a txn is created, the repository's start-commit hooks are
 * run; if any of them fail, no txn is created, @a *txn_p is unaffected, 
 * and @c SVN_ERR_REPOS_HOOK_FAILURE is returned.
 *
 * @a log_msg may be @c NULL to indicate the message is not (yet) available.
 * The caller will need to attach it to the transaction at a later time.
 */
svn_error_t *svn_repos_fs_begin_txn_for_commit(svn_fs_txn_t **txn_p,
                                               svn_repos_t *repos,
                                               svn_revnum_t rev,
                                               const char *author,
                                               const char *log_msg,
                                               apr_pool_t *pool);


/** Like svn_fs_begin_txn(), but use @a author to set the corresponding
 * property on transaction @a *txn_p.  @a repos is the repository object
 * which contains the filesystem.  @a rev, @a *txn_p, and @a pool are as in
 * svn_fs_begin_txn().
 *
 * ### Someday: before a txn is created, some kind of read-hook could
 *              be called here.
 */
svn_error_t *svn_repos_fs_begin_txn_for_update(svn_fs_txn_t **txn_p,
                                               svn_repos_t *repos,
                                               svn_revnum_t rev,
                                               const char *author,
                                               apr_pool_t *pool);


/** @defgroup svn_repos_fs_locks repository lock wrappers
 * @{ 
 * @since New in 1.2. */

/** Like svn_fs_lock(), but invoke the @a repos's pre- and
 * post-lock hooks before and after the locking action.  Use @a pool
 * for any necessary allocations.
 *
 * If the pre-lock hook or svn_fs_lock() fails, throw the original
 * error to caller.  If an error occurs when running the post-lock
 * hook, return the original error wrapped with
 * SVN_ERR_REPOS_POST_LOCK_HOOK_FAILED.  If the caller sees this
 * error, it knows that the lock succeeded anyway.
 */
svn_error_t *svn_repos_fs_lock(svn_lock_t **lock,
                               svn_repos_t *repos,
                               const char *path,
                               const char *token,
                               const char *comment,
                               svn_boolean_t is_dav_comment,
                               apr_time_t expiration_date,
                               svn_revnum_t current_rev,
                               svn_boolean_t steal_lock,
                               apr_pool_t *pool);


/** Like svn_fs_unlock(), but invoke the @a repos's pre- and
 * post-unlock hooks before and after the unlocking action.  Use @a
 * pool for any necessary allocations.
 *
 * If the pre-unlock hook or svn_fs_unlock() fails, throw the original
 * error to caller.  If an error occurs when running the post-unlock
 * hook, return the original error wrapped with
 * SVN_ERR_REPOS_POST_UNLOCK_HOOK_FAILED.  If the caller sees this
 * error, it knows that the unlock succeeded anyway.
 */
svn_error_t *svn_repos_fs_unlock(svn_repos_t *repos,
                                 const char *path,
                                 const char *token,
                                 svn_boolean_t break_lock,
                                 apr_pool_t *pool);



/** Look up all the locks in and under @a path in @a repos, setting @a
 * *locks to a hash which maps <tt>const char *</tt> paths to the @c
 * svn_lock_t locks associated with those paths.  Use @a
 * authz_read_func and @a authz_read_baton to "screen" all returned
 * locks.  That is: do not return any locks on any paths that are
 * unreadable in HEAD, just silently omit them.
 */
svn_error_t *svn_repos_fs_get_locks(apr_hash_t **locks,
                                    svn_repos_t *repos,
                                    const char *path,
                                    svn_repos_authz_func_t authz_read_func,
                                    void *authz_read_baton,
                                    apr_pool_t *pool);

/** @} */

/**
 * Like svn_fs_change_rev_prop(), but invoke the @a repos's pre- and
 * post-revprop-change hooks around the change.  Use @a pool for
 * temporary allocations.
 *
 * @a rev is the revision whose property to change, @a name is the
 * name of the property, and @a new_value is the new value of the
 * property.   @a author is the authenticated username of the person
 * changing the property value, or null if not available.
 *
 * If @a authz_read_func is non-NULL, then use it (with @a
 * authz_read_baton) to validate the changed-paths associated with @a
 * rev.  If the revision contains any unreadable changed paths, then
 * return SVN_ERR_AUTHZ_UNREADABLE.
 * 
 * @since New in 1.1.
 */
svn_error_t *svn_repos_fs_change_rev_prop2(svn_repos_t *repos,
                                           svn_revnum_t rev,
                                           const char *author,
                                           const char *name,
                                           const svn_string_t *new_value,
                                           svn_repos_authz_func_t
                                           authz_read_func,
                                           void *authz_read_baton,
                                           apr_pool_t *pool);

/**
 * Similar to svn_repos_fs_change_rev_prop2(), but with the
 * @a authz_read_func parameter always NULL.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_repos_fs_change_rev_prop(svn_repos_t *repos,
                                          svn_revnum_t rev,
                                          const char *author,
                                          const char *name,
                                          const svn_string_t *new_value,
                                          apr_pool_t *pool);



/**
 * Set @a *value_p to the value of the property named @a propname on
 * revision @a rev in the filesystem opened in @a repos.  If @a rev
 * has no property by that name, set @a *value_p to zero.  Allocate
 * the result in @a pool.
 *
 * If @a authz_read_func is non-NULL, then use it (with @a
 * authz_read_baton) to validate the changed-paths associated with @a
 * rev.  If the changed-paths are all unreadable, then set @a *value_p
 * to zero unconditionally.  If only some of the changed-paths are
 * unreadable, then allow 'svn:author' and 'svn:date' propvalues to be
 * fetched, but return 0 for any other property.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_repos_fs_revision_prop(svn_string_t **value_p,
                                        svn_repos_t *repos,
                                        svn_revnum_t rev,
                                        const char *propname,
                                        svn_repos_authz_func_t
                                        authz_read_func,
                                        void *authz_read_baton,
                                        apr_pool_t *pool);


/**
 * Set @a *table_p to the entire property list of revision @a rev in
 * filesystem opened in @a repos, as a hash table allocated in @a
 * pool.  The table maps <tt>char *</tt> property names to @c
 * svn_string_t * values; the names and values are allocated in @a
 * pool.
 *
 * If @a authz_read_func is non-NULL, then use it (with @a
 * authz_read_baton) to validate the changed-paths associated with @a
 * rev.  If the changed-paths are all unreadable, then return an empty
 * hash. If only some of the changed-paths are unreadable, then return
 * an empty hash, except for 'svn:author' and 'svn:date' properties
 * (assuming those properties exist).
 *
 * @since New in 1.1.
 */
svn_error_t *svn_repos_fs_revision_proplist(apr_hash_t **table_p,
                                            svn_repos_t *repos,
                                            svn_revnum_t rev,
                                            svn_repos_authz_func_t
                                            authz_read_func,
                                            void *authz_read_baton,
                                            apr_pool_t *pool);



/* ---------------------------------------------------------------*/

/* Prop-changing wrappers for libsvn_fs routines. */

/* NOTE: svn_repos_fs_change_rev_prop() also exists, but is located
   above with the hook-related functions. */


/** Validating wrapper for svn_fs_change_node_prop() (which see for
 * argument descriptions).
 */
svn_error_t *svn_repos_fs_change_node_prop(svn_fs_root_t *root,
                                           const char *path,
                                           const char *name,
                                           const svn_string_t *value,
                                           apr_pool_t *pool);

/** Validating wrapper for svn_fs_change_txn_prop() (which see for
 * argument descriptions).
 */
svn_error_t *svn_repos_fs_change_txn_prop(svn_fs_txn_t *txn,
                                          const char *name,
                                          const svn_string_t *value,
                                          apr_pool_t *pool);

/** @} */

/* ---------------------------------------------------------------*/

/**
 * @defgroup svn_repos_inspection Data structures and editor things for 
 * repository inspection.
 * @{
 *
 * As it turns out, the svn_repos_dir_delta() interface can be
 * extremely useful for examining the repository, or more exactly,
 * changes to the repository.  svn_repos_dir_delta() allows for
 * differences between two trees to be described using an editor.
 *
 * By using the editor obtained from svn_repos_node_editor() with
 * svn_repos_dir_delta(), the description of how to transform one tree
 * into another can be used to build an in-memory linked-list tree,
 * which each node representing a repository node that was changed as a
 * result of having svn_repos_dir_delta() drive that editor.
 */

/** A node in the repository. */
typedef struct svn_repos_node_t
{
  /** Node type (file, dir, etc.) */
  svn_node_kind_t kind;

  /** How this node entered the node tree: 'A'dd, 'D'elete, 'R'eplace */
  char action; 

  /** Were there any textual mods? (files only) */
  svn_boolean_t text_mod;

  /** Where there any property mods? */
  svn_boolean_t prop_mod;

  /** The name of this node as it appears in its parent's entries list */
  const char *name;

  /** The filesystem revision where this was copied from (if any) */
  svn_revnum_t copyfrom_rev;

  /** The filesystem path where this was copied from (if any) */
  const char *copyfrom_path;

  /** Pointer to the next sibling of this node */
  struct svn_repos_node_t *sibling;

  /** Pointer to the first child of this node */
  struct svn_repos_node_t *child;

  /** Pointer to the parent of this node */
  struct svn_repos_node_t *parent;

} svn_repos_node_t;


/** Set @a *editor and @a *edit_baton to an editor that, when driven by
 * svn_repos_dir_delta(), builds an <tt>svn_repos_node_t *</tt> tree
 * representing the delta from @a base_root to @a root in @a repos's 
 * filesystem.
 *  
 * Invoke svn_repos_node_from_baton() on @a edit_baton to obtain the root
 * node afterwards.
 *
 * Note that the delta includes "bubbled-up" directories; that is,
 * many of the directory nodes will have no prop_mods.
 *
 * Allocate the tree and its contents in @a node_pool; do all other
 * allocation in @a pool.
 */
svn_error_t *svn_repos_node_editor(const svn_delta_editor_t **editor,
                                   void **edit_baton,
                                   svn_repos_t *repos,
                                   svn_fs_root_t *base_root,
                                   svn_fs_root_t *root,
                                   apr_pool_t *node_pool,
                                   apr_pool_t *pool);

/** Return the root node of the linked-list tree generated by driving
 * the editor created by svn_repos_node_editor() with
 * svn_repos_dir_delta(), which is stored in @a edit_baton.  This is 
 * only really useful if used *after* the editor drive is completed.
 */
svn_repos_node_t *svn_repos_node_from_baton(void *edit_baton);

/** @} */

/* ---------------------------------------------------------------*/

/**
 * @defgroup svn_repos_dump_load Dumping and loading filesystem data
 * @{
 *
 * The filesystem 'dump' format contains nothing but the abstract
 * structure of the filesystem -- independent of any internal node-id
 * schema or database back-end.  All of the data in the dumpfile is
 * acquired by public function calls into svn_fs.h.  Similarly, the
 * parser which reads the dumpfile is able to reconstruct the
 * filesystem using only public svn_fs.h routines.
 *
 * Thus the dump/load feature's main purpose is for *migrating* data
 * from one svn filesystem to another -- presumably two filesystems
 * which have different internal implementations.
 *
 * If you simply want to backup your filesystem, you're probably
 * better off using the built-in facilities of the DB backend (using
 * Berkeley DB's hot-backup feature, for example.)
 * 
 * For a description of the dumpfile format, see
 * /trunk/notes/fs_dumprestore.txt.
 */

/* The RFC822-style headers in our dumpfile format. */
#define SVN_REPOS_DUMPFILE_MAGIC_HEADER            "SVN-fs-dump-format-version"
#define SVN_REPOS_DUMPFILE_FORMAT_VERSION           3
#define SVN_REPOS_DUMPFILE_UUID                      "UUID"
#define SVN_REPOS_DUMPFILE_CONTENT_LENGTH            "Content-length"

#define SVN_REPOS_DUMPFILE_REVISION_NUMBER           "Revision-number"

#define SVN_REPOS_DUMPFILE_NODE_PATH                 "Node-path"
#define SVN_REPOS_DUMPFILE_NODE_KIND                 "Node-kind"
#define SVN_REPOS_DUMPFILE_NODE_ACTION               "Node-action"
#define SVN_REPOS_DUMPFILE_NODE_COPYFROM_PATH        "Node-copyfrom-path"
#define SVN_REPOS_DUMPFILE_NODE_COPYFROM_REV         "Node-copyfrom-rev"
#define SVN_REPOS_DUMPFILE_TEXT_COPY_SOURCE_CHECKSUM "Text-copy-source-md5"
#define SVN_REPOS_DUMPFILE_TEXT_CONTENT_CHECKSUM     "Text-content-md5"

#define SVN_REPOS_DUMPFILE_PROP_CONTENT_LENGTH       "Prop-content-length"
#define SVN_REPOS_DUMPFILE_TEXT_CONTENT_LENGTH       "Text-content-length"

/* @since New in 1.1. */
#define SVN_REPOS_DUMPFILE_PROP_DELTA                "Prop-delta"
/* @since New in 1.1. */
#define SVN_REPOS_DUMPFILE_TEXT_DELTA                "Text-delta"

/** The different "actions" attached to nodes in the dumpfile. */
enum svn_node_action
{
  svn_node_action_change,
  svn_node_action_add,
  svn_node_action_delete,
  svn_node_action_replace
};

/** The different policies for processing the UUID in the dumpfile. */
enum svn_repos_load_uuid
{
  svn_repos_load_uuid_default,
  svn_repos_load_uuid_ignore,
  svn_repos_load_uuid_force
};

/**
 * Dump the contents of the filesystem within already-open @a repos into
 * writable @a dumpstream.  Begin at revision @a start_rev, and dump every
 * revision up through @a end_rev.  Use @a pool for all allocation.  If
 * non-@c NULL, send feedback to @a feedback_stream. @a dumpstream can be
 * @c NULL for the purpose of verifying the repository.
 *
 * If @a start_rev is @c SVN_INVALID_REVNUM, then start dumping at revision 
 * 0.  If @a end_rev is @c SVN_INVALID_REVNUM, then dump through the @c HEAD 
 * revision.
 *
 * If @a incremental is @c TRUE, the first revision dumped will be a diff
 * against the previous revision (usually it looks like a full dump of
 * the tree).
 *
 * If @a use_deltas is @c TRUE, output only node properties which have
 * changed relative to the previous contents, and output text contents
 * as svndiff data against the previous contents.  Regardless of how
 * this flag is set, the first revision of a non-incremental dump will
 * be done with full plain text.  A dump with @a use_deltas set cannot
 * be loaded by Subversion 1.0.x.
 *
 * If @a cancel_func is not @c NULL, it is called periodically with
 * @a cancel_baton as argument to see if the client wishes to cancel
 * the dump.
 * 
 * @since New in 1.1.
 */
svn_error_t *svn_repos_dump_fs2(svn_repos_t *repos,
                                svn_stream_t *dumpstream,
                                svn_stream_t *feedback_stream,
                                svn_revnum_t start_rev,
                                svn_revnum_t end_rev,
                                svn_boolean_t incremental,
                                svn_boolean_t use_deltas,
                                svn_cancel_func_t cancel_func,
                                void *cancel_baton,
                                apr_pool_t *pool);


/**
 * Similar to svn_repos_dump_fs2(), but with the @a use_deltas
 * parameter always set to @c FALSE.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_repos_dump_fs(svn_repos_t *repos,
                               svn_stream_t *dumpstream,
                               svn_stream_t *feedback_stream,
                               svn_revnum_t start_rev,
                               svn_revnum_t end_rev,
                               svn_boolean_t incremental,
                               svn_cancel_func_t cancel_func,
                               void *cancel_baton,
                               apr_pool_t *pool);


/**
 * Read and parse dumpfile-formatted @a dumpstream, reconstructing
 * filesystem revisions in already-open @a repos, handling uuids
 * in accordance with @a uuid_action.
 *
 * Read and parse dumpfile-formatted @a dumpstream, reconstructing
 * filesystem revisions in already-open @a repos.  Use @a pool for all
 * allocation.  If non-@c NULL, send feedback to @a feedback_stream.
 *
 * If the dumpstream contains copy history that is unavailable in the
 * repository, an error will be thrown.
 *
 * The repository's UUID will be updated iff
 *   the dumpstream contains a UUID and
 *   @a uuid_action is not equal to @c svn_repos_load_uuid_ignore and
 *   either the repository contains no revisions or
 *          @a uuid_action is equal to @c svn_repos_load_uuid_force.
 *
 * If the dumpstream contains no UUID, then @a uuid_action is
 * ignored and the repository UUID is not touched.
 *
 * If @a parent_dir is not null, then the parser will reparent all the
 * loaded nodes, from root to @a parent_dir.  The directory @a parent_dir
 * must be an existing directory in the repository.
 *
 * If @a use_pre_commit_hook is set, call the repository's pre-commit
 * hook before committing each loaded revision.  
 *
 * If @a use_post_commit_hook is set, call the repository's
 * post-commit hook after committing each loaded revision.
 *
 * If @a cancel_func is not @c NULL, it is called periodically with
 * @a cancel_baton as argument to see if the client wishes to cancel
 * the load.
 * 
 * @since New in 1.2.
 */
svn_error_t *svn_repos_load_fs2(svn_repos_t *repos,
                                svn_stream_t *dumpstream,
                                svn_stream_t *feedback_stream,
                                enum svn_repos_load_uuid uuid_action,
                                const char *parent_dir,
                                svn_boolean_t use_pre_commit_hook,
                                svn_boolean_t use_post_commit_hook,
                                svn_cancel_func_t cancel_func,
                                void *cancel_baton,
                                apr_pool_t *pool);

/**
 * Similar to svn_repos_load_fs2(), but with @a use_pre_commit_hook and
 * @a use_post_commit_hook always @c FALSE.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_repos_load_fs(svn_repos_t *repos,
                               svn_stream_t *dumpstream,
                               svn_stream_t *feedback_stream,
                               enum svn_repos_load_uuid uuid_action,
                               const char *parent_dir,
                               svn_cancel_func_t cancel_func,
                               void *cancel_baton,
                               apr_pool_t *pool);


/**
 * A vtable that is driven by svn_repos_parse_dumpstream2().
 * 
 * @since New in 1.1.
 */
typedef struct svn_repos_parse_fns2_t
{
  /** The parser has discovered a new revision record within the
   * parsing session represented by @a parse_baton.  All the headers are
   * placed in @a headers (allocated in @a pool), which maps <tt>const 
   * char *</tt> header-name ==> <tt>const char *</tt> header-value.  
   * The @a revision_baton received back (also allocated in @a pool) 
   * represents the revision.
   */
  svn_error_t *(*new_revision_record)(void **revision_baton,
                                      apr_hash_t *headers,
                                      void *parse_baton,
                                      apr_pool_t *pool);

  /** The parser has discovered a new uuid record within the parsing
   * session represented by @a parse_baton.  The uuid's value is
   * @a uuid, and it is allocated in @a pool.
   */
  svn_error_t *(*uuid_record)(const char *uuid,
                              void *parse_baton,
                              apr_pool_t *pool);

  /** The parser has discovered a new node record within the current
   * revision represented by @a revision_baton.  All the headers are
   * placed in @a headers (as with @c new_revision_record), allocated in
   * @a pool.  The @a node_baton received back is allocated in @a pool
   * and represents the node.
   */
  svn_error_t *(*new_node_record)(void **node_baton,
                                  apr_hash_t *headers,
                                  void *revision_baton,
                                  apr_pool_t *pool);

  /** For a given @a revision_baton, set a property @a name to @a value. */
  svn_error_t *(*set_revision_property)(void *revision_baton,
                                        const char *name,
                                        const svn_string_t *value);

  /** For a given @a node_baton, set a property @a name to @a value. */
  svn_error_t *(*set_node_property)(void *node_baton,
                                    const char *name,
                                    const svn_string_t *value);

  /** For a given @a node_baton, delete property @a name. */
  svn_error_t *(*delete_node_property)(void *node_baton, const char *name);

  /** For a given @a node_baton, remove all properties. */
  svn_error_t *(*remove_node_props)(void *node_baton);

  /** For a given @a node_baton, receive a writable @a stream capable of
   * receiving the node's fulltext.  After writing the fulltext, call
   * the stream's close() function.
   *
   * If a @c NULL is returned instead of a stream, the vtable is
   * indicating that no text is desired, and the parser will not
   * attempt to send it.
   */
  svn_error_t *(*set_fulltext)(svn_stream_t **stream,
                               void *node_baton);

  /** For a given @a node_baton, set @a handler and @a handler_baton
   * to a window handler and baton capable of receiving a delta
   * against the node's previous contents.  A NULL window will be
   * sent to the handler after all the windows are sent.
   *
   * If a @c NULL is returned instead of a handler, the vtable is
   * indicating that no delta is desired, and the parser will not
   * attempt to send it.
   */
  svn_error_t *(*apply_textdelta)(svn_txdelta_window_handler_t *handler,
                                  void **handler_baton,
                                  void *node_baton);

  /** The parser has reached the end of the current node represented by
   * @a node_baton, it can be freed.
   */
  svn_error_t *(*close_node)(void *node_baton);

  /** The parser has reached the end of the current revision
   * represented by @a revision_baton.  In other words, there are no more
   * changed nodes within the revision.  The baton can be freed.
   */
  svn_error_t *(*close_revision)(void *revision_baton);

} svn_repos_parse_fns2_t;

/** @deprecated Provided for backward compatibility with the 1.2 API. */
typedef svn_repos_parse_fns2_t svn_repos_parser_fns2_t;


/**
 * Read and parse dumpfile-formatted @a stream, calling callbacks in
 * @a parse_fns/@a parse_baton, and using @a pool for allocations.
 *
 * If @a cancel_func is not @c NULL, it is called periodically with
 * @a cancel_baton as argument to see if the client wishes to cancel
 * the dump.
 *
 * This parser has built-in knowledge of the dumpfile format, but only
 * in a general sense:
 *
 *    * it recognizes revision and node records by looking for either
 *      a REVISION_NUMBER or NODE_PATH headers.
 *
 *    * it recognizes the CONTENT-LENGTH headers, so it knows if and
 *      how to suck up the content body.
 *
 *    * it knows how to parse a content body into two parts:  props
 *      and text, and pass the pieces to the vtable.
 *
 * This is enough knowledge to make it easy on vtable implementors,
 * but still allow expansion of the format:  most headers are ignored.
 * 
 * @since New in 1.1.
 */
svn_error_t *
svn_repos_parse_dumpstream2(svn_stream_t *stream,
                            const svn_repos_parse_fns2_t *parse_fns,
                            void *parse_baton,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            apr_pool_t *pool);


/**
 * Set @a *parser and @a *parse_baton to a vtable parser which commits new
 * revisions to the fs in @a repos.  The constructed parser will treat
 * UUID records in a manner consistent with @a uuid_action.  Use @a pool
 * to operate on the fs.
 *
 * If @a use_history is set, then the parser will require relative
 * 'copyfrom' history to exist in the repository when it encounters
 * nodes that are added-with-history.
 *
 * If @a parent_dir is not null, then the parser will reparent all the
 * loaded nodes, from root to @a parent_dir.  The directory @a parent_dir
 * must be an existing directory in the repository.
 *
 * Print all parsing feedback to @a outstream (if non-@c NULL).
 *
 * 
 * @since New in 1.1.
 */
svn_error_t *
svn_repos_get_fs_build_parser2(const svn_repos_parse_fns2_t **parser,
                               void **parse_baton,
                               svn_repos_t *repos,
                               svn_boolean_t use_history,
                               enum svn_repos_load_uuid uuid_action,
                               svn_stream_t *outstream,
                               const char *parent_dir,
                               apr_pool_t *pool);


/**
 * A vtable that is driven by svn_repos_parse_dumpstream().
 * Similar to @c svn_repos_parse_fns2_t except that it lacks
 * the delete_node_property and apply_textdelta callbacks.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
typedef struct svn_repos_parse_fns_t
{
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*new_revision_record)(void **revision_baton,
                                      apr_hash_t *headers,
                                      void *parse_baton,
                                      apr_pool_t *pool);
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*uuid_record)(const char *uuid,
                              void *parse_baton,
                              apr_pool_t *pool);
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*new_node_record)(void **node_baton,
                                  apr_hash_t *headers,
                                  void *revision_baton,
                                  apr_pool_t *pool);
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*set_revision_property)(void *revision_baton,
                                        const char *name,
                                        const svn_string_t *value);
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*set_node_property)(void *node_baton,
                                    const char *name,
                                    const svn_string_t *value);
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*remove_node_props)(void *node_baton);
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*set_fulltext)(svn_stream_t **stream,
                               void *node_baton);
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*close_node)(void *node_baton);
  /** Same as the corresponding field in @c svn_repos_parse_fns2_t. */
  svn_error_t *(*close_revision)(void *revision_baton);
} svn_repos_parser_fns_t;


/**
 * Similar to svn_repos_parse_dumpstream2(), but uses the more limited
 * @c svn_repos_parser_fns_t vtable type.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *
svn_repos_parse_dumpstream(svn_stream_t *stream,
                           const svn_repos_parser_fns_t *parse_fns,
                           void *parse_baton,
                           svn_cancel_func_t cancel_func,
                           void *cancel_baton,
                           apr_pool_t *pool);


/**
 * Similar to svn_repos_get_fs_build_parser2(), but yields the more
 * limited svn_repos_parser_fns_t vtable type.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *
svn_repos_get_fs_build_parser(const svn_repos_parser_fns_t **parser,
                              void **parse_baton,
                              svn_repos_t *repos,
                              svn_boolean_t use_history,
                              enum svn_repos_load_uuid uuid_action,
                              svn_stream_t *outstream,
                              const char *parent_dir,
                              apr_pool_t *pool);


/** @} */

/** A data type which stores the authz information. 
 *
 * @since New in 1.3.
 */
typedef struct svn_authz_t svn_authz_t;

/** Read authz configuration data from @a file (a file or registry
 * path) into @a *authz_p, allocated in @a pool.
 *
 * If @a file is not a valid authz rule file, then return
 * SVN_AUTHZ_INVALID_CONFIG.  The contents of @a *authz_p is then
 * undefined.  If @a must_exist is TRUE, a missing authz file is also
 * an error.
 *
 * @since New in 1.3.
 */
svn_error_t *
svn_repos_authz_read(svn_authz_t **authz_p, const char *file,
                     svn_boolean_t must_exist, apr_pool_t *pool);

/**
 * Check whether @a user can access @a path in the repository @a
 * repos_name with the @a required_access.  @a authz lists the ACLs to
 * check against.  Set @a *access_granted to indicate if the requested
 * access is granted.
 *
 * If @a path is NULL, then check whether @a user has the @a
 * required_access anywhere in the repository.  Set @a *access_granted
 * to TRUE if at least one path is accessible with the @a
 * required_access.
 *
 * @since New in 1.3.
 */
svn_error_t *
svn_repos_authz_check_access(svn_authz_t *authz, const char *repos_name,
                             const char *path, const char *user,
                             svn_repos_authz_access_t required_access,
                             svn_boolean_t *access_granted,
                             apr_pool_t *pool);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_REPOS_H */
