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
 * @file svn_io.h
 * @brief General file I/O for Subversion
 */

/* ==================================================================== */


#ifndef SVN_IO_H
#define SVN_IO_H

#include <apr.h>
#include <apr_pools.h>
#include <apr_file_io.h>
#include <apr_thread_proc.h>

#include "svn_types.h"
#include "svn_error.h"
#include "svn_string.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/** Used as an argument when creating temporary files to indicate
 * when a file should be removed.
 *
 * @since New in 1.4.
 *
 * Not specifying any of these means no removal at all. */
typedef enum svn_io_file_del_t
{
  /** No deletion ever */
  svn_io_file_del_none = 0,
  /** Remove when the file is closed */
  svn_io_file_del_on_close,
  /** Remove when the associated pool is cleared */
  svn_io_file_del_on_pool_cleanup
} svn_io_file_del_t;



/** Represents the kind and special status of a directory entry.
 *
 * @since New in 1.3.
 */
typedef struct svn_io_dirent_t {
  /** The kind of this entry. */
  svn_node_kind_t kind;
  /** If @c kind is @c svn_node_file, whether this entry is a special file;
   * else false.
   *
   * @see svn_io_check_special_path().
   */
  svn_boolean_t special;
} svn_io_dirent_t;

/** Determine the @a kind of @a path.
 *
 * If utf8-encoded @a path exists, set @a *kind to the appropriate kind,
 * else set it to @c svn_node_unknown. 
 *
 * If @a path is a file, @a *kind is set to @c svn_node_file.
 *
 * If @a path is a directory, @a *kind is set to @c svn_node_dir.
 *
 * If @a path does not exist in its final component, @a *kind is set to
 * @c svn_node_none.  
 *
 * If intermediate directories on the way to @a path don't exist, an
 * error is returned, and @a *kind's value is undefined.
 */
svn_error_t *svn_io_check_path(const char *path,
                               svn_node_kind_t *kind,
                               apr_pool_t *pool);

/**
 * Like svn_io_check_path(), but also set *is_special to @c TRUE if
 * the path is not a normal file.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_io_check_special_path(const char *path,
                                       svn_node_kind_t *kind,
                                       svn_boolean_t *is_special,
                                       apr_pool_t *pool);

/** Like svn_io_check_path(), but resolve symlinks.  This returns the
    same varieties of @a kind as svn_io_check_path(). */ 
svn_error_t *svn_io_check_resolved_path(const char *path,
                                        svn_node_kind_t *kind,
                                        apr_pool_t *pool);


/** Open a new file (for writing) with a unique name based on utf-8
 * encoded @a path, in the same directory as @a path.  The file handle is
 * returned in @a *f, and the name, which ends with @a suffix, is returned
 * in @a *unique_name_p, also utf8-encoded.  Either @a f or @a unique_name_p
 * may be @c NULL.
 *
 * If @a delete_when is @c svn_io_file_del_on_close, then the @c APR_DELONCLOSE
 * flag will be used when opening the file.  The @c APR_BUFFERED flag will
 * always be used.
 *
 * The first attempt will just append @a suffix.  If the result is not
 * a unique name, then subsequent attempts will append a dot,
 * followed by an iteration number ("2", then "3", and so on),
 * followed by the suffix.  For example, if @a path is
 *
 *    tests/t1/A/D/G/pi
 *
 * then successive calls to
 *
 *    svn_io_open_unique_file2(&f, &unique_name, @a path, ".tmp", ..., pool)
 *
 * will open
 *
 *    tests/t1/A/D/G/pi.tmp
 *    tests/t1/A/D/G/pi.2.tmp
 *    tests/t1/A/D/G/pi.3.tmp
 *    tests/t1/A/D/G/pi.4.tmp
 *    tests/t1/A/D/G/pi.5.tmp
 *    ...
 *
 * Assuming @a suffix is non-empty, @a *unique_name_p will never be exactly
 * the same as @a path, even if @a path does not exist.
 *
 * It doesn't matter if @a path is a file or directory, the unique name will
 * be in @a path's parent either way.
 *
 * Allocate @a *f and @a *unique_name_p in @a pool.
 *
 * If no unique name can be found, @c SVN_ERR_IO_UNIQUE_NAMES_EXHAUSTED is
 * the error returned.
 *
 * Claim of Historical Inevitability: this function was written
 * because
 *
 *    - tmpnam() is not thread-safe.
 *    - tempname() tries standard system tmp areas first.
 *
 *
 * @since New in 1.4
 *
 */
svn_error_t *svn_io_open_unique_file2(apr_file_t **f,
                                      const char **unique_name_p,
                                      const char *path,
                                      const char *suffix,
                                      svn_io_file_del_t delete_when,
                                      apr_pool_t *pool);

/** Like svn_io_open_unique_file2, but can't delete on pool cleanup.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API
 *
 * @note In 1.4 the API was extended to require either @a f or
 *       @a unique_name_p (the other can be NULL).  Before that, both were
 *       required.
 *
 */
svn_error_t *svn_io_open_unique_file(apr_file_t **f,
                                     const char **unique_name_p,
                                     const char *path,
                                     const char *suffix,
                                     svn_boolean_t delete_on_close,
                                     apr_pool_t *pool);

/**
 * Like svn_io_open_unique_file(), except that instead of creating a
 * file, a symlink is generated that references the path @a dest.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_io_create_unique_link(const char **unique_name_p,
                                       const char *path,
                                       const char *dest,
                                       const char *suffix,
                                       apr_pool_t *pool);


/**
 * Set @a *dest to the path that the symlink at @a path references.
 * Allocate the string from @a pool.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_io_read_link(svn_string_t **dest,
                              const char *path,
                              apr_pool_t *pool);


/** Set @a *dir to a directory path (allocated in @a pool) deemed
 * usable for the creation of temporary files and subdirectories.
 */
svn_error_t *svn_io_temp_dir(const char **dir,
                             apr_pool_t *pool);


/** Copy @a src to @a dst atomically, in a "byte-for-byte" manner.
 * Overwrite @a dst if it exists, else create it.  Both @a src and @a dst
 * are utf8-encoded filenames.  If @a copy_perms is true, set @a dst's
 * permissions to match those of @a src.
 */
svn_error_t *svn_io_copy_file(const char *src,
                              const char *dst,
                              svn_boolean_t copy_perms,
                              apr_pool_t *pool);

/**
 * Copy symbolic link @a src to @a dst atomically.  Overwrite @a dst
 * if it exists, else create it.  Both @a src and @a dst are
 * utf8-encoded filenames.  After copying, the @a dst link will point
 * to the same thing @a src does.
 * 
 * @since New in 1.1.
 */
svn_error_t *svn_io_copy_link(const char *src,
                              const char *dst,
                              apr_pool_t *pool);


/** Recursively copy directory @a src into @a dst_parent, as a new entry named
 * @a dst_basename.  If @a dst_basename already exists in @a dst_parent, 
 * return error.  @a copy_perms will be passed through to svn_io_copy_file()
 * when any files are copied.  @a src, @a dst_parent, and @a dst_basename are 
 * all utf8-encoded.
 *
 * If @a cancel_func is non-null, invoke it with @a cancel_baton at
 * various points during the operation.  If it returns any error
 * (typically @c SVN_ERR_CANCELLED), return that error immediately.
 */ 
svn_error_t *svn_io_copy_dir_recursively(const char *src,
                                         const char *dst_parent,
                                         const char *dst_basename,
                                         svn_boolean_t copy_perms,
                                         svn_cancel_func_t cancel_func,
                                         void *cancel_baton,
                                         apr_pool_t *pool);



/** Create directory @a path on the file system, creating intermediate
 * directories as required, like <tt>mkdir -p</tt>.  Report no error if @a 
 * path already exists.  @a path is utf8-encoded.
 *
 * This is essentially a wrapper for apr_dir_make_recursive(), passing
 * @c APR_OS_DEFAULT as the permissions.
 */
svn_error_t *svn_io_make_dir_recursively(const char *path, apr_pool_t *pool);


/** Set @a *is_empty_p to @c TRUE if directory @a path is empty, else to 
 * @c FALSE if it is not empty.  @a path must be a directory, and is
 * utf8-encoded.  Use @a pool for temporary allocation.
 */
svn_error_t *
svn_io_dir_empty(svn_boolean_t *is_empty_p,
                 const char *path,
                 apr_pool_t *pool);


/** Append @a src to @a dst.  @a dst will be appended to if it exists, else it
 * will be created.  Both @a src and @a dst are utf8-encoded.
 */
svn_error_t *svn_io_append_file(const char *src,
                                const char *dst,
                                apr_pool_t *pool);


/** Make a file as read-only as the operating system allows.
 * @a path is the utf8-encoded path to the file. If @a ignore_enoent is
 * @c TRUE, don't fail if the target file doesn't exist.
 */
svn_error_t *svn_io_set_file_read_only(const char *path,
                                       svn_boolean_t ignore_enoent,
                                       apr_pool_t *pool);


/** Make a file as writable as the operating system allows.
 * @a path is the utf8-encoded path to the file.  If @a ignore_enoent is
 * @c TRUE, don't fail if the target file doesn't exist.
 * @warning On Unix this function will do the equivalent of chmod a+w path.
 * If this is not what you want you should not use this function, but rather
 * use apr_file_perms_set().
 */
svn_error_t *svn_io_set_file_read_write(const char *path,
                                        svn_boolean_t ignore_enoent,
                                        apr_pool_t *pool);


/** Similar to svn_io_set_file_read_* functions.
 * Change the read-write permissions of a file.
 * @since New in 1.1.
 *
 * When making @a path read-write on operating systems with unix style
 * permissions, set the permissions on @a path to the permissions that
 * are set when a new file is created (effectively honoring the user's
 * umask).
 *
 * When making the file read-only on operating systems with unix style
 * permissions, remove all write permissions.
 *
 * On other operating systems, toggle the file's "writability" as much as
 * the operating system allows.
 *
 * @a path is the utf8-encoded path to the file.  If @a enable_write
 * is @c TRUE, then make the file read-write.  If @c FALSE, make it
 * read-only.  If @a ignore_enoent is @c TRUE, don't fail if the target
 * file doesn't exist.
 *
 * @deprecated Provided for backward compatibility with the 1.3 API.
 */
svn_error_t *svn_io_set_file_read_write_carefully(const char *path,
                                                  svn_boolean_t enable_write,
                                                  svn_boolean_t ignore_enoent,
                                                  apr_pool_t *pool);
    
/** Toggle a file's "executability".
 *
 * When making the file executable on operating systems with unix style
 * permissions, never add an execute permission where there is not
 * already a read permission: that is, only make the file executable
 * for the user, group or world if the corresponding read permission
 * is already set for user, group or world.
 *
 * When making the file non-executable on operating systems with unix style
 * permissions, remove all execute permissions.
 *
 * On other operating systems, toggle the file's "executability" as much as
 * the operating system allows.
 *
 * @a path is the utf8-encoded path to the file.  If @a executable
 * is @c TRUE, then make the file executable.  If @c FALSE, make it
 * non-executable.  If @a ignore_enoent is @c TRUE, don't fail if the target
 * file doesn't exist.
 */
svn_error_t *svn_io_set_file_executable(const char *path,
                                        svn_boolean_t executable,
                                        svn_boolean_t ignore_enoent,
                                        apr_pool_t *pool);

/** Determine whether a file is executable by the current user.  
 * Set @a *executable to @c TRUE if the file @a path is executable by the 
 * current user, otherwise set it to @c FALSE.  
 * 
 * On Windows and on platforms without userids, always returns @c FALSE.
 */
svn_error_t *svn_io_is_file_executable(svn_boolean_t *executable, 
                                       const char *path, 
                                       apr_pool_t *pool);


/** Read a line from @a file into @a buf, but not exceeding @a *limit bytes.
 * Does not include newline, instead '\\0' is put there.
 * Length (as in strlen) is returned in @a *limit.
 * @a buf should be pre-allocated.
 * @a file should be already opened. 
 *
 * When the file is out of lines, @c APR_EOF will be returned.
 */
svn_error_t *
svn_io_read_length_line(apr_file_t *file, char *buf, apr_size_t *limit,
                        apr_pool_t *pool);


/** Set @a *apr_time to the time of last modification of the contents of the
 * file @a path.  @a path is utf8-encoded.
 *
 * @note This is the APR mtime which corresponds to the traditional mtime
 * on Unix, and the last write time on Windows.
 */
svn_error_t *svn_io_file_affected_time(apr_time_t *apr_time,
                                       const char *path,
                                       apr_pool_t *pool);

/** Set the timestamp of file @a path to @a apr_time.  @a path is
 *  utf8-encoded.
 *
 * @note This is the APR mtime which corresponds to the traditional mtime
 * on Unix, and the last write time on Windows.
 */
svn_error_t *svn_io_set_file_affected_time(apr_time_t apr_time,
                                           const char *path,
                                           apr_pool_t *pool);



/** Set @a *different_p to non-zero if @a file1 and @a file2 have different
 * sizes, else set to zero.  Both @a file1 and @a file2 are utf8-encoded.
 *
 * Setting @a *different_p to zero does not mean the files definitely
 * have the same size, it merely means that the sizes are not
 * definitely different.  That is, if the size of one or both files
 * cannot be determined, then the sizes are not known to be different,
 * so @a *different_p is set to 0.
 */
svn_error_t *svn_io_filesizes_different_p(svn_boolean_t *different_p,
                                          const char *file1,
                                          const char *file2,
                                          apr_pool_t *pool);


/** Put the md5 checksum of @a file into @a digest.
 * @a digest points to @c APR_MD5_DIGESTSIZE bytes of storage.
 * Use @a pool only for temporary allocations.
 */
svn_error_t *svn_io_file_checksum(unsigned char digest[],
                                  const char *file,
                                  apr_pool_t *pool);


/** Set @a *same to TRUE if @a file1 and @a file2 have the same
 * contents, else set it to FALSE.  Use @a pool for temporary allocations.
 */
svn_error_t *svn_io_files_contents_same_p(svn_boolean_t *same,
                                          const char *file1,
                                          const char *file2,
                                          apr_pool_t *pool);

/** Create file at @a file with contents @a contents.
 * will be created.  Path @a file is utf8-encoded.
 * Use @a pool for memory allocations.
 */
svn_error_t *svn_io_file_create(const char *file,
                                const char *contents,
                                apr_pool_t *pool);

/**
 * Lock file at @a lock_file. If @a exclusive is TRUE,
 * obtain exclusive lock, otherwise obtain shared lock.
 * Lock will be automatically released when @a pool is cleared or destroyed.
 * Use @a pool for memory allocations.
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_io_file_lock(const char *lock_file,
                              svn_boolean_t exclusive,
                              apr_pool_t *pool);

/**
 * Lock file at @a lock_file. If @a exclusive is TRUE,
 * obtain exclusive lock, otherwise obtain shared lock.
 *
 * If @a nonblocking is TRUE, do not wait for the lock if it
 * is not available: throw an error instead.
 *
 * Lock will be automatically released when @a pool is cleared or destroyed.
 * Use @a pool for memory allocations.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_io_file_lock2(const char *lock_file,
                               svn_boolean_t exclusive,
                               svn_boolean_t nonblocking,
                               apr_pool_t *pool);
/**
 * Flush any unwritten data from @a file to disk.  Use @a pool for
 *  memory allocations.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_io_file_flush_to_disk(apr_file_t *file,
                                       apr_pool_t *pool);

/** Copy file @a file from location @a src_path to location @a dest_path.
 * Use @a pool for memory allocations.
 */
svn_error_t *svn_io_dir_file_copy(const char *src_path, 
                                  const char *dest_path, 
                                  const char *file,
                                  apr_pool_t *pool);


/** Generic byte-streams
 *
 * @defgroup svn_io_byte_streams generic byte streams
 * @{
 */

/** An abstract stream of bytes--either incoming or outgoing or both.
 *
 * The creator of a stream sets functions to handle read and write.
 * Both of these handlers accept a baton whose value is determined at
 * stream creation time; this baton can point to a structure
 * containing data associated with the stream.  If a caller attempts
 * to invoke a handler which has not been set, it will generate a
 * runtime assertion failure.  The creator can also set a handler for
 * close requests so that it can flush buffered data or whatever;
 * if a close handler is not specified, a close request on the stream
 * will simply be ignored.  Note that svn_stream_close() does not
 * deallocate the memory used to allocate the stream structure; free
 * the pool you created the stream in to free that memory.
 *
 * The read and write handlers accept length arguments via pointer.
 * On entry to the handler, the pointed-to value should be the amount
 * of data which can be read or the amount of data to write.  When the
 * handler returns, the value is reset to the amount of data actually
 * read or written.  Handlers are obliged to complete a read or write
 * to the maximum extent possible; thus, a short read with no
 * associated error implies the end of the input stream, and a short
 * write should never occur without an associated error.
 */
typedef struct svn_stream_t svn_stream_t;



/** Read handler function for a generic stream.  @see svn_stream_t. */
typedef svn_error_t *(*svn_read_fn_t)(void *baton,
                                      char *buffer,
                                      apr_size_t *len);

/** Write handler function for a generic stream.  @see svn_stream_t. */
typedef svn_error_t *(*svn_write_fn_t)(void *baton,
                                       const char *data,
                                       apr_size_t *len);

/** Close handler function for a generic stream.  @see svn_stream_t. */
typedef svn_error_t *(*svn_close_fn_t)(void *baton);


/** Create a generic stream.  @see svn_stream_t. */
svn_stream_t *svn_stream_create(void *baton, apr_pool_t *pool);

/** Set @a stream's baton to @a baton */
void svn_stream_set_baton(svn_stream_t *stream, void *baton);

/** Set @a stream's read function to @a read_fn */
void svn_stream_set_read(svn_stream_t *stream, svn_read_fn_t read_fn);

/** Set @a stream's write function to @a write_fn */
void svn_stream_set_write(svn_stream_t *stream, svn_write_fn_t write_fn);

/** Set @a stream's close function to @a close_fn */
void svn_stream_set_close(svn_stream_t *stream, svn_close_fn_t close_fn);


/** Create a stream that is empty for reading and infinite for writing. */
svn_stream_t *svn_stream_empty(apr_pool_t *pool);

/** Return a stream allocated in @a pool which forwards all requests
 * to @a stream.  Destruction is explicitly excluded from forwarding.
 *
 * @see notes/destruction-of-stacked-resources
 *
 * @since New in 1.4.
 */
svn_stream_t *svn_stream_disown(svn_stream_t *stream, apr_pool_t *pool);

/** Create a stream from an APR file.  For convenience, if @a file is
 * @c NULL, an empty stream created by svn_stream_empty() is returned.
 *
 * This function should normally be called with @a disown set to false,
 * in which case closing the stream will also close the underlying file.
 *
 * If @a disown is true, the stream will disown the underlying file,
 * meaning that svn_stream_close() will not close the file.
 *
 * @since New in 1.4.
 */
svn_stream_t * svn_stream_from_aprfile2(apr_file_t *file,
                                        svn_boolean_t disown,
                                        apr_pool_t *pool);

/** Similar to svn_stream_from_aprfile2(), except that the file will
 * always be disowned.
 *
 * @note The stream returned is not considered to "own" the underlying
 *       file, meaning that svn_stream_close() on the stream will not
 *       close the file.
 *
 * @deprecated Provided for backward compatibility with the 1.3 API.
 */
svn_stream_t *svn_stream_from_aprfile(apr_file_t *file, apr_pool_t *pool);

/** Set @a *out to a generic stream connected to stdout, allocated in 
 * @a pool.  The stream and its underlying APR handle will be closed
 * when @a pool is cleared or destroyed.
 */
svn_error_t *svn_stream_for_stdout(svn_stream_t **out, apr_pool_t *pool);

/** Return a generic stream connected to stringbuf @a str.  Allocate the
 * stream in @a pool.
 */
svn_stream_t *svn_stream_from_stringbuf(svn_stringbuf_t *str,
                                        apr_pool_t *pool);

/** Return a stream that decompresses all data read and compresses all
 * data written. The stream @a stream is used to read and write all
 * compressed data. All compression data structures are allocated on
 * @a pool. If compression support is not compiled in then
 * svn_stream_compressed() returns @a stream unmodified. Make sure you
 * call svn_stream_close() on the stream returned by this function,
 * so that all data are flushed and cleaned up.
 */
svn_stream_t *svn_stream_compressed(svn_stream_t *stream, 
                                    apr_pool_t *pool);

/** Return a stream that calculates checksums for all data read
 * and written.  The stream @a stream is used to read and write all data.
 * The stream and the resulting digests are allocated in @a pool.
 *
 * When the stream is closed, @a read_digest and @a write_digest
 * are set to point to the resulting digests.
 *
 * Both @a read_digest and @a write_digest
 * can be @c NULL, in which case the respective checksum isn't calculated.
 *
 * If @a read_all is true, make sure that all data available on @a
 * stream is read (and checksummed) when the stream is closed.
 *
 * Read and write operations can be mixed without interfering.
 *
 * The @a stream passed into this function is closed when the created
 * stream is closed.
 *
 * @since New in 1.4.
 */
svn_stream_t *svn_stream_checksummed(svn_stream_t *stream,
                                     const unsigned char **read_digest,
                                     const unsigned char **write_digest,
                                     svn_boolean_t read_all,
                                     apr_pool_t *pool);

/** Read from a generic stream. @see svn_stream_t. */
svn_error_t *svn_stream_read(svn_stream_t *stream, char *buffer,
                             apr_size_t *len);

/** Write to a generic stream. @see svn_stream_t. */
svn_error_t *svn_stream_write(svn_stream_t *stream, const char *data,
                              apr_size_t *len);

/** Close a generic stream. @see svn_stream_t. */
svn_error_t *svn_stream_close(svn_stream_t *stream);


/** Write to @a stream using a printf-style @a fmt specifier, passed through
 * apr_psprintf() using memory from @a pool.
 */
svn_error_t *svn_stream_printf(svn_stream_t *stream,
                               apr_pool_t *pool,
                               const char *fmt,
                               ...)
       __attribute__ ((format(printf, 3, 4)));

/** Write to @a stream using a printf-style @a fmt specifier, passed through
 * apr_psprintf() using memory from @a pool.  The resulting string
 * will be translated to @a encoding before it is sent to @a stream.
 *
 * @note Use @c APR_LOCALE_CHARSET to translate to the encoding of the
 * current locale.
 *
 * @since New in 1.3.
 */
svn_error_t *svn_stream_printf_from_utf8(svn_stream_t *stream,
                                         const char *encoding,
                                         apr_pool_t *pool,
                                         const char *fmt,
                                         ...)
       __attribute__ ((format(printf, 4, 5)));

/** Allocate @a *stringbuf in @a pool, and read into it one line (terminated
 * by @a eol) from @a stream. The line-terminator is read from the stream,
 * but is not added to the end of the stringbuf.  Instead, the stringbuf
 * ends with a usual '\\0'.
 *
 * If @a stream runs out of bytes before encountering a line-terminator,
 * then set @a *eof to @c TRUE, otherwise set @a *eof to FALSE.
 */
svn_error_t *
svn_stream_readline(svn_stream_t *stream,
                    svn_stringbuf_t **stringbuf,
                    const char *eol,
                    svn_boolean_t *eof,
                    apr_pool_t *pool);

/**
 * Read the contents of the readable stream @a from and write them to the
 * writable stream @a to.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_stream_copy(svn_stream_t *from, svn_stream_t *to,
                             apr_pool_t *pool);

/** Set @a *same to TRUE if @a stream1 and @a stream2 have the same
 * contents, else set it to FALSE.  Use @a pool for temporary allocations.
 *
 * @since New in 1.4.
 */
svn_error_t *
svn_stream_contents_same(svn_boolean_t *same,
                         svn_stream_t *stream1,
                         svn_stream_t *stream2,
                         apr_pool_t *pool);

/** @} */

/** Sets @a *result to a string containing the contents of @a filename, a
 * utf8-encoded path. 
 *
 * If @a filename is "-", return the error @c SVN_ERR_UNSUPPORTED_FEATURE
 * and don't touch @a *result.
 *
 * ### Someday, "-" will fill @a *result from stdin.  The problem right
 * now is that if the same command invokes the editor, stdin is crap,
 * and the editor acts funny or dies outright.  One solution is to
 * disallow stdin reading and invoking the editor, but how to do that
 * reliably?
 */
svn_error_t *svn_stringbuf_from_file(svn_stringbuf_t **result, 
                                     const char *filename, 
                                     apr_pool_t *pool);

/** Sets @a *result to a string containing the contents of the already opened
 * @a file.  Reads from the current position in file to the end.  Does not
 * close the file or reset the cursor position.
 */
svn_error_t *svn_stringbuf_from_aprfile(svn_stringbuf_t **result,
                                        apr_file_t *file,
                                        apr_pool_t *pool);

/** Remove file @a path, a utf8-encoded path.  This wraps apr_file_remove(), 
 * converting any error to a Subversion error.
 */
svn_error_t *svn_io_remove_file(const char *path, apr_pool_t *pool);

/** Recursively remove directory @a path.  @a path is utf8-encoded. */
svn_error_t *svn_io_remove_dir(const char *path, apr_pool_t *pool);

/** Read all of the disk entries in directory @a path, a utf8-encoded
 * path.  Set @a *dirents to a hash mapping dirent names (<tt>char *</tt>) to
 * undefined non-NULL values, allocated in @a pool.
 *
 * @note The `.' and `..' directories normally returned by
 * apr_dir_read() are NOT returned in the hash.
 *
 * @since New in 1.4.
 */
svn_error_t *svn_io_get_dir_filenames(apr_hash_t **dirents,
                                      const char *path,
                                      apr_pool_t *pool);

/** Read all of the disk entries in directory @a path, a utf8-encoded
 * path.  Set @a *dirents to a hash mapping dirent names (<tt>char *</tt>) to
 * @c svn_io_dirent_t structures, allocated in @a pool.
 *
 * @note The `.' and `..' directories normally returned by
 * apr_dir_read() are NOT returned in the hash.
 *
 * @since New in 1.3.
 */
svn_error_t *svn_io_get_dirents2(apr_hash_t **dirents,
                                 const char *path,
                                 apr_pool_t *pool);

/** Similar to svn_io_get_dirents2(), but @a *dirents is a hash table
 * with @c svn_node_kind_t values.
 *
 * @deprecated Provided for backwards compatibility with the 1.2 API.
 */
svn_error_t *svn_io_get_dirents(apr_hash_t **dirents,
                                const char *path,
                                apr_pool_t *pool);


/** Callback function type for svn_io_dir_walk() */
typedef svn_error_t * (*svn_io_walk_func_t)(void *baton,
                                            const char *path,
                                            const apr_finfo_t *finfo,
                                            apr_pool_t *pool);

/** This function will recursively walk over the files and directories
 * rooted at @a dirname, a utf8-encoded path. For each file or directory,
 * @a walk_func is invoked, passing in the @a walk_baton, the utf8-encoded
 * full path to the entry, an @c apr_finfo_t structure, and a temporary
 * pool for allocations.  For any directory, @a walk_func will be invoked
 * on the directory itself before being invoked on any subdirectories or
 * files within the directory.
 *
 * The set of information passed to @a walk_func is specified by @a wanted,
 * and the items specified by @c APR_FINFO_TYPE and @c APR_FINFO_NAME.
 *
 * All allocations will be performed in @a pool.
 */
svn_error_t *svn_io_dir_walk(const char *dirname,
                             apr_int32_t wanted,
                             svn_io_walk_func_t walk_func,
                             void *walk_baton,
                             apr_pool_t *pool);

/**
 * Start @a cmd with @a args, using utf8-encoded @a path as working 
 * directory.  Connect @a cmd's stdin, stdout, and stderr to @a infile, 
 * @a outfile, and @a errfile, except where they are null.  Return the
 * process handle for the invoked program in @a *cmd_proc.
 *
 * @a args is a list of utf8-encoded <tt>const char *</tt> arguments,
 * terminated by @c NULL.  @a args[0] is the name of the program, though it
 * need not be the same as @a cmd.
 *
 * If @a inherit is true, the invoked program inherits its environment from
 * the caller and @a cmd, if not absolute, is searched for in PATH.
 * Otherwise, the invoked program runs with an empty environment and @a cmd
 * must be an absolute path.
 *
 * @note On some platforms, failure to execute @a cmd in the child process
 * will result in error output being written to @a errfile, if non-NULL, and
 * a non-zero exit status being returned to the parent process.
 *
 * @since New in 1.3.
 */
svn_error_t *svn_io_start_cmd(apr_proc_t *cmd_proc,
                              const char *path,
                              const char *cmd,
                              const char *const *args,
                              svn_boolean_t inherit,
                              apr_file_t *infile,
                              apr_file_t *outfile,
                              apr_file_t *errfile,
                              apr_pool_t *pool);

/**
 * Wait for the process @a *cmd_proc to complete and optionally retrieve
 * its exit code.  @a cmd is used only in error messages.
 *
 * If @a exitcode is not null, @a *exitcode will contain the exit code
 * of the process upon return, and if @a exitwhy is not null, @a
 * *exitwhy will indicate why the process terminated.  If @a exitwhy is 
 * null, and the exit reason is not @c APR_PROC_CHECK_EXIT(), or if 
 * @a exitcode is null and the exit code is non-zero, then an
 * @c SVN_ERR_EXTERNAL_PROGRAM error will be returned.
 *
 * @since New in 1.3.
 */
svn_error_t *svn_io_wait_for_cmd(apr_proc_t *cmd_proc,
                                 const char *cmd,
                                 int *exitcode,
                                 apr_exit_why_e *exitwhy,
                                 apr_pool_t *pool);

/** Run a command to completion, by first calling svn_io_start_cmd() and
 * then calling svn_io_wait_for_cmd().  The parameters correspond to
 * the same-named parameters of those two functions.
 */
svn_error_t *svn_io_run_cmd(const char *path,
                            const char *cmd,
                            const char *const *args,
                            int *exitcode,
                            apr_exit_why_e *exitwhy,
                            svn_boolean_t inherit,
                            apr_file_t *infile,
                            apr_file_t *outfile,
                            apr_file_t *errfile,
                            apr_pool_t *pool);

/** Invoke @c the configured diff program, with @a user_args (an array
 * of utf8-encoded @a num_user_args arguments), if they are specified,
 * or "-u" if they are not.
 *
 * Diff runs in utf8-encoded @a dir, and its exit status is stored in
 * @a exitcode, if it is not @c NULL.  
 *
 * If @a label1 and/or @a label2 are not null they will be passed to the diff
 * process as the arguments of "-L" options.  @a label1 and @a label2 are also 
 * in utf8, and will be converted to native charset along with the other args.
 *
 * @a from is the first file passed to diff, and @a to is the second.  The
 * stdout of diff will be sent to @a outfile, and the stderr to @a errfile.
 *
 * @a diff_cmd must be non-null.
 *
 * Do all allocation in @a pool. 
 */
svn_error_t *svn_io_run_diff(const char *dir,
                             const char *const *user_args,
                             int num_user_args,
                             const char *label1,
                             const char *label2,
                             const char *from,
                             const char *to,
                             int *exitcode,
                             apr_file_t *outfile,
                             apr_file_t *errfile,
                             const char *diff_cmd,
                             apr_pool_t *pool);


/** Invoke @c the configured diff3 program, in utf8-encoded @a dir
 * like this:
 *
 *          diff3 -E -m @a mine @a older @a yours > @a merged
 *
 * (See the diff3 documentation for details.)
 *
 * If @a user_args is non-NULL, replace "-E" with the <tt>const char*</tt>
 * elements that @a user_args contains.
 *
 * @a mine, @a older, and @a yours are utf8-encoded paths, relative to @a dir, 
 * to three files that already exist.  @a merged is an open file handle, and
 * is left open after the merge result is written to it. (@a merged
 * should *not* be the same file as @a mine, or nondeterministic things
 * may happen!)
 *
 * @a mine_label, @a older_label, @a yours_label are utf8-encoded label
 * parameters for diff3's -L option.  Any of them may be @c NULL, in
 * which case the corresponding @a mine, @a older, or @a yours parameter is
 * used instead.
 *
 * Set @a *exitcode to diff3's exit status.  If @a *exitcode is anything
 * other than 0 or 1, then return @c SVN_ERR_EXTERNAL_PROGRAM.  (Note the
 * following from the diff3 info pages: "An exit status of 0 means
 * `diff3' was successful, 1 means some conflicts were found, and 2
 * means trouble.") 
 *
 * @a diff3_cmd must be non-null.
 *
 * Do all allocation in @a pool.
 *
 * @since New in 1.4.
 */
svn_error_t *svn_io_run_diff3_2(int *exitcode,
                                const char *dir,
                                const char *mine,
                                const char *older,
                                const char *yours,
                                const char *mine_label,
                                const char *older_label,
                                const char *yours_label,
                                apr_file_t *merged,
                                const char *diff3_cmd,
                                const apr_array_header_t *user_args,
                                apr_pool_t *pool);

/** Similar to @a svn_io_run_diff3_2(), but with @a user_args set to @c NULL.
 *
 * @deprecated Provided for backwards compatibility with the 1.3 API.
 */
svn_error_t *svn_io_run_diff3(const char *dir,
                              const char *mine,
                              const char *older,
                              const char *yours,
                              const char *mine_label,
                              const char *older_label,
                              const char *yours_label,
                              apr_file_t *merged,
                              int *exitcode,
                              const char *diff3_cmd,
                              apr_pool_t *pool);


/** Examine utf8-encoded @a file to determine if it can be described by a
 * known (as in, known by this function) Multipurpose Internet Mail
 * Extension (MIME) type.  If so, set @a *mimetype to a character string
 * describing the MIME type, else set it to @c NULL.  Use @a pool for any
 * necessary allocations.
 */
svn_error_t *svn_io_detect_mimetype(const char **mimetype,
                                    const char *file,
                                    apr_pool_t *pool);
                                      

/** Wrapper for apr_file_open(), which see.  @a fname is utf8-encoded. */
svn_error_t *
svn_io_file_open(apr_file_t **new_file, const char *fname,
                 apr_int32_t flag, apr_fileperms_t perm,
                 apr_pool_t *pool);


/** Wrapper for apr_file_close(), which see. */
svn_error_t *
svn_io_file_close(apr_file_t *file, apr_pool_t *pool);


/** Wrapper for apr_file_getc(), which see. */
svn_error_t *
svn_io_file_getc(char *ch, apr_file_t *file, apr_pool_t *pool);


/** Wrapper for apr_file_info_get(), which see. */
svn_error_t *
svn_io_file_info_get(apr_finfo_t *finfo, apr_int32_t wanted, 
                     apr_file_t *file, apr_pool_t *pool);


/** Wrapper for apr_file_read(), which see. */
svn_error_t *
svn_io_file_read(apr_file_t *file, void *buf, 
                 apr_size_t *nbytes, apr_pool_t *pool);


/** Wrapper for apr_file_read_full(), which see. */
svn_error_t *
svn_io_file_read_full(apr_file_t *file, void *buf, 
                      apr_size_t nbytes, apr_size_t *bytes_read,
                      apr_pool_t *pool);


/** Wrapper for apr_file_seek(), which see. */
svn_error_t *
svn_io_file_seek(apr_file_t *file, apr_seek_where_t where, 
                 apr_off_t *offset, apr_pool_t *pool);


/** Wrapper for apr_file_write(), which see. */
svn_error_t *
svn_io_file_write(apr_file_t *file, const void *buf, 
                  apr_size_t *nbytes, apr_pool_t *pool);


/** Wrapper for apr_file_write_full(), which see. */
svn_error_t *
svn_io_file_write_full(apr_file_t *file, const void *buf, 
                       apr_size_t nbytes, apr_size_t *bytes_written,
                       apr_pool_t *pool);


/** Wrapper for apr_stat(), which see.  @a fname is utf8-encoded. */
svn_error_t *
svn_io_stat(apr_finfo_t *finfo, const char *fname,
            apr_int32_t wanted, apr_pool_t *pool);


/** Wrapper for apr_file_rename(), which see.  @a from_path and @a to_path
 * are utf8-encoded.
 */
svn_error_t *
svn_io_file_rename(const char *from_path, const char *to_path,
                   apr_pool_t *pool);


/** Move the file from @a from_path to @a to_path, even across device
 * boundaries. Overwrite @a to_path if it exists.
 *
 * @note This function is different from svn_io_file_rename in that the
 * latter fails in the 'across device boundaries' case.
 *
 * @since New in 1.3.
 */
svn_error_t *
svn_io_file_move(const char *from_path, const char *to_path,
                 apr_pool_t *pool);


/** Wrapper for apr_dir_make(), which see.  @a path is utf8-encoded. */
svn_error_t *
svn_io_dir_make(const char *path, apr_fileperms_t perm, apr_pool_t *pool);

/** Same as svn_io_dir_make(), but sets the hidden attribute on the
    directory on systems that support it. */
svn_error_t *
svn_io_dir_make_hidden(const char *path, apr_fileperms_t perm,
                       apr_pool_t *pool);

/**
 * Same as svn_io_dir_make(), but attempts to set the sgid on the
 * directory on systems that support it.  Does not return an error if
 * the attempt to set the sgid bit fails.  On Unix filesystems,
 * setting the sgid bit on a directory ensures that files and
 * subdirectories created within inherit group ownership from the
 * parent instead of from the primary gid.
 *
 * @since New in 1.1.
 */
svn_error_t *
svn_io_dir_make_sgid(const char *path, apr_fileperms_t perm,
                     apr_pool_t *pool);

/** Wrapper for apr_dir_open(), which see.  @a dirname is utf8-encoded. */
svn_error_t *
svn_io_dir_open(apr_dir_t **new_dir, const char *dirname, apr_pool_t *pool);


/** Wrapper for apr_dir_remove(), which see.  @a dirname is utf8-encoded.
 * @note This function has this name to avoid confusion with
 * svn_io_remove_dir(), which is recursive.
 */
svn_error_t *
svn_io_dir_remove_nonrecursive(const char *dirname, apr_pool_t *pool);


/** Wrapper for apr_dir_read().  Ensures that @a finfo->name is
 * utf8-encoded, which means allocating @a finfo->name in @a pool,
 * which may or may not be the same as @a finfo's pool.  Use @a pool
 * for error allocation as well.
 */
svn_error_t *
svn_io_dir_read(apr_finfo_t *finfo,
                apr_int32_t wanted,
                apr_dir_t *thedir,
                apr_pool_t *pool);



/** Version/format files. 
 *
 * @defgroup svn_io_format_files version/format files
 * @{
 */

/** Set @a *version to the integer that starts the file at @a path.  If the
 * file does not begin with a series of digits followed by a newline,
 * return the error @c SVN_ERR_BAD_VERSION_FILE_FORMAT.  Use @a pool for
 * all allocations.
 */
svn_error_t *
svn_io_read_version_file(int *version, const char *path, apr_pool_t *pool);

/** Create (or overwrite) the file at @a path with new contents,
 * formatted as a non-negative integer @a version followed by a single
 * newline.  On successful completion the file will be read-only.  Use
 * @a pool for all allocations.
 */
svn_error_t *
svn_io_write_version_file(const char *path, int version, apr_pool_t *pool);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_IO_H */
