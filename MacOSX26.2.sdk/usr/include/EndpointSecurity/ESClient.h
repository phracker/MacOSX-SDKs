#ifndef __ENDPOINT_SECURITY_CLIENT_H
#define __ENDPOINT_SECURITY_CLIENT_H

#ifndef __ENDPOINT_SECURITY_INDIRECT__
#error "Please #include <EndpointSecurity/EndpointSecurity.h> instead of this file directly."
#endif

#include <os/availability.h>
#include <os/base.h>

struct es_client_s;
/**
 * es_client_t is an opaque type that stores the endpoint security client state
 */
typedef struct es_client_s es_client_t;

__BEGIN_DECLS

/**
 * Subscribe to some set of events
 * @param client The client that will be subscribing
 * @param events Array of es_event_type_t to subscribe to
 * @param event_count Count of es_event_type_t in `events`
 * @return es_return_t indicating success or error
 *
 * @note Subscribing to new event types does not remove previous subscriptions.
 *
 * @note Subscribing to events is not optional for clients that have opted into
 *       early boot mode (see NSEndpointSecurityEarlyBoot in EndpointSecurity(7)).
 *       Early boot clients that fail to subscribe to at least one event type will
 *       cause early boot to time out, resulting in a bad user experience and
 *       risking watchdog timeout panics.
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_subscribe(es_client_t *_Nonnull client, const es_event_type_t *_Nonnull events, uint32_t event_count);

/**
 * Unsubscribe from some set of events
 * @param client The client that will be unsubscribing
 * @param events Array of es_event_type_t to unsubscribe from
 * @param event_count Count of es_event_type_t in `events`
 * @return es_return_t indicating success or error
 * @note Events not included in the given `events` array that were previously subscribed to will continue to be subscribed to
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_unsubscribe(es_client_t *_Nonnull client, const es_event_type_t *_Nonnull events, uint32_t event_count);

/**
 * Unsubscribe from all events
 * @param client The client that will be unsubscribing
 * @return es_return_t indicating success or error
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios) API_UNAVAILABLE(tvos, watchos) es_return_t es_unsubscribe_all(es_client_t *_Nonnull client);

/**
 * List subscriptions
 * @param client The client for which subscriptions will be listed
 * @param count Out param that reports the number of subscriptions written
 * @param subscriptions  Out param for pointer to subscription data
 * @return es_return_t indicating success or error
 * @brief The caller takes ownership of the memory at `*subscriptions` and must free it
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t
es_subscriptions(es_client_t *_Nonnull client, size_t *_Nonnull count, es_event_type_t *_Nonnull *_Nullable subscriptions);

/**
 * Respond to an auth event that requires an es_auth_result_t response
 * @param client The client that produced the event
 * @param message The message being responded to
 * @param result A result indicating the action the ES subsystem should take
 * @param cache Indicates if this result should be cached.  The specific
 *        caching semantics depend on es_event_type_t.  Cache key is generally
 *        the involved files, with modifications to those files invalidating
 *        the cache entry.  A cache hit leads to no AUTH event being produced,
 *        while still producing a NOTIFY event normally.
 *        The cache argument is ignored for events that do not support caching.
 * @return es_respond_result_t indicating success or an error
 * @brief Some events must be responded to with `es_respond_flags_result`. Responding to flags events with this function will
 * fail.
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_respond_result_t
es_respond_auth_result(es_client_t *_Nonnull client, const es_message_t *_Nonnull message, es_auth_result_t result, bool cache);

/**
 * Respond to an auth event that requires an uint32_t flags response
 * @param client The client that produced the event
 * @param message The message being responded to
 * @param authorized_flags A flags value that will mask the flags in event being
 *        responded to; pass 0 to deny and UINT32_MAX to allow regardless of what
 *        flags are set on the event.
 * @param cache Indicates if this result should be cached.  The specific
 *        caching semantics depend on es_event_type_t.  Cache key is generally
 *        the involved files, with modifications to those files invalidating
 *        the cache entry.  A cache hit leads to no AUTH event being produced,
 *        while still producing a NOTIFY event normally.
 *        The cache argument is ignored for events that do not support caching.
 * @return es_respond_result_t indicating success or an error
 * @brief Some events must be responded to with `es_respond_auth_result`. Responding to auth events with the function will fail.
 * @note Enabling caching caches authorized_flags.  Subsequent cache hits
 *       will result in the event being allowed only if the flags of the
 *       event are a subset of the flags in authorized_flags, and denied
 *       otherwise.  As a result, UINT32_MAX should be passed for
 *       authorized_flags, unless denying events with certain flags is
 *       intentional.  A common mistake is passing the flags from the
 *       event, which together with caching may result in subsequent
 *       events getting unintentionally denied if they have flags set
 *       that were not set in the cached authorized_flags.
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_respond_result_t es_respond_flags_result(
	es_client_t *_Nonnull client, const es_message_t *_Nonnull message, uint32_t authorized_flags, bool cache
);

/**
 * @brief Suppress all events from the process described by the given `audit_token`
 *
 * @param client The client for which events will be suppressed
 * @param audit_token The audit token of the process for which events will be suppressed
 *
 * @return es_return_t indicating success or error
 *
 * @see es_mute_process_events
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_mute_process(es_client_t *_Nonnull client, const audit_token_t *_Nonnull audit_token);

/**
 * @brief Suppress a subset of events from the process described by the given `audit_token`
 *
 * @param client The client for which events will be suppressed
 * @param audit_token The audit token of the process for which events will be suppressed
 * @param events Array of event types for which the audit_token should be muted.
 * @param event_count The number of items in the `events` array.
 *
 * @return es_return_t A value indicating whether or not the process was successfully muted.
 *
 * @see es_mute_process
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_mute_process_events(
	es_client_t *_Nonnull client,
	const audit_token_t *_Nonnull audit_token,
	const es_event_type_t *_Nonnull events,
	size_t event_count
);

/**
 * @brief Unmute a process for all event types
 *
 * @param client The client for which the process will be unmuted
 * @param audit_token The audit token of the process to be unmuted
 *
 * @return es_return_t indicating success or error
 *
 * @see es_unmute_process_events
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_unmute_process(es_client_t *_Nonnull client, const audit_token_t *_Nonnull audit_token);

/**
 * @brief Unmute a process for a subset of event types.
 *
 * @param client The client for which events will be unmuted
 * @param audit_token The audit token of the process for which events will be unmuted
 * @param events Array of event types to unmute for the process
 * @param event_count The number of items in the `events` array.
 *
 * @return es_return_t A value indicating whether or not the process was successfully unmuted.
 *
 * @see es_unmute_path
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_unmute_process_events(
	es_client_t *_Nonnull client,
	const audit_token_t *_Nonnull audit_token,
	const es_event_type_t *_Nonnull events,
	size_t event_count
);

/**
 * List muted processes
 * @param client The client for which muted processes will be listed
 * @param count Out param that reports the number of audit tokens written
 * @param audit_tokens  Out param for pointer to audit_token data
 * @return es_return_t indicating success or error
 * @brief The caller takes ownership of the memory at `*audit_tokens` and must free it.
 *        If there are no muted processes and the call completes successfully,
 *        `*count` is set to 0 and `*audit_token` is set to NULL.
 * @note The audit tokens are returned in the same state as they were passed to
 *       `es_mute_process` and may not accurately reflect the current state of the
 *       respective processes.
 */
OS_EXPORT
API_DEPRECATED("Please use es_muted_processes_events.", macos(10.15, 12.0))
API_UNAVAILABLE(ios, tvos, watchos)
es_return_t
es_muted_processes(es_client_t *_Nonnull client, size_t *_Nonnull count, audit_token_t *_Nonnull *_Nullable audit_tokens);

/**
 * @brief Retrieve a list of all muted processes.
 *
 * @param client The es_client_t for which the muted processes will be retrieved.
 * @param muted_processes OUT param the will contain newly created memory describing the set of
 *        muted processes. This memory must be deleted using `es_release_muted_processes`.
 *
 * @return es_return_t A value indicating whether or not the list of muted processes were
 *         successfully retrieved.
 *
 * @see es_release_muted_processes
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_muted_processes_events(es_client_t *_Nonnull client, es_muted_processes_t *_Nullable *_Nonnull muted_processes);

/**
 * @brief Delete a set of muted processes obtained from `es_muted_processes_events`, freeing resources.
 *
 * @param muted_processes A set of muted processes to delete.
 *
 * @see es_muted_processes_all_events
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
void es_release_muted_processes(es_muted_processes_t *_Nonnull muted_processes);

/**
 * @brief Suppress all events matching a path.
 *
 * @param client The es_client_t for which the path will be muted.
 * @param path The path to mute.
 * @param type Describes the type of the `path` parameter.
 *
 * @return es_return_t A value indicating whether or not the path was successfully muted.
 *
 * @note Path-based muting applies to the real and potentially firmlinked path
 *       of a file as seen by VFS, and as available from fcntl(2) F_GETPATH.
 *       No special provisions are made for files with multiple ("hard") links,
 *       or for symbolic links.
 *       In particular, when using inverted target path muting to monitor a
 *       particular path for writing, you will need to check if the file(s) of
 *       interest are also reachable via additional hard links outside of the
 *       paths you are observing.
 *
 * @see es_mute_path_events
 * @discussion When using the path types ES_MUTE_PATH_TYPE_TARGET_PREFIX and ES_MUTE_PATH_TYPE_TARGET_LITERAL Not all events are
 * supported. Furthermore the interpretation of target path is contextual. For events with more than one target path (such as
 * exchangedata) the behavior depends on the mute inversion state Under normal muting the event is suppressed only if ALL paths
 * are muted When target path muting is inverted the event is selected if ANY target path is muted For example a rename will be
 * suppressed if and only if both the source path and destination path are muted. Supported events are listed below. For each
 * event the target path is defined as:
 *
 * EXEC: The file being executed
 * OPEN: The file being opened
 * MMAP: The file being memory mapped
 * RENAME: Both the source and destination path.
 * SIGNAL: The path of the process being signalled
 * UNLINK: The file being unlinked
 * CLOSE: The file being closed
 * CREATE: The path to the file that will be created or replaced
 * GET_TASK: The path of the process for which the task port is being retrieved
 * LINK: Both the source and destination path
 * SETATTRLIST: The file for which the attributes are being set
 * SETEXTATTR: The file for which the extended attributes are being set
 * SETFLAGS: The file for which flags are being set
 * SETMODE: The file for which the mode is being set
 * SETOWNER: The file for which the owner is being set
 * WRITE: The file being written to
 * READLINK: The symbolic link being resolved
 * TRUNCATE: The file being truncated
 * CHDIR: The new working directory
 * GETATTRLIST: The file for which the attribute list is being retrieved
 * STAT: The file for which the stat is being retrieved
 * ACCESS: The file for which access is being tested
 * CHROOT: The file which will become the new root
 * UTIMES: The file for which times are being set
 * CLONE: Both the source file and target path
 * FCNTL: The file under file control
 * GETEXTATTR The file for which extended attributes are being retrieved
 * LISTEXTATTR The file for which extended attributes are being listed
 * READDIR The directory for whose contents will be read
 * DELETEEXTATTR The file for which extended attribues will be deleted
 * DUP: The file being duplicated
 * UIPC_BIND: The path to the unix socket that will be created
 * UIPC_CONNECT: The file that the unix socket being connected is bound to
 * EXCHANGEDATA: The path of both file1 and file2
 * SETACL: The file for which ACLs are being set
 * PROC_CHECK: The path of the process against which access is being checked
 * SEARCHFS: The path of the volume which will be searched
 * PROC_SUSPEND_RESUME: The path of the process being suspended or resumed
 * GET_TASK_NAME: The path of the process for which the task name port will be retrieved
 * TRACE: The path of the process that will be attached to
 * REMOTE_THREAD_CREATE: The path of the process in which the new thread is created
 * GET_TASK_READ: The path of the process for which the task read port will be retrieved
 * GET_TASK_INSPECT: The path of the process for which the task inspect port will be retrieved
 * COPYFILE: The path to the source file and the path to either the new file to be created or the existing file to be overwritten
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_mute_path(es_client_t *_Nonnull client, const char *_Nonnull path, es_mute_path_type_t type);

/**
 * @brief Suppress a subset of events matching a path.
 *
 * @param client The es_client_t for which the path will be muted.
 * @param path The path to mute.
 * @param type Describes the type of the `path` parameter, either a prefix path or literal path.
 * @param events Array of event types for which the path should be muted.
 * @param event_count The number of items in the `events` array.
 *
 * @return es_return_t A value indicating whether or not the path was successfully muted.
 *
 * @see es_mute_path
 * @discussion when using ES_MUTE_PATH_TYPE_TARGET_PREFIX and ES_MUTE_PATH_TYPE_TARGET_LITERAL not all events are supported.
 * Target muting a path for an event type that does not support target muting is a no-op.
 * If at least one event type was muted for a target path then ES_RETURN_SUCCESS is returned.
 * If all specified event types do not support target muting ES_RETURN_ERROR is returned.
 * See es_mute_path for the list of events that support target path muting.
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_mute_path_events(
	es_client_t *_Nonnull client,
	const char *_Nonnull path,
	es_mute_path_type_t type,
	const es_event_type_t *_Nonnull events,
	size_t event_count
);

/**
 * Suppress events matching a path prefix
 *
 * @deprecated Please use `es_mute_path` or `es_mute_path_events`
 *
 * @param client The client for which events will be suppressed
 * @param path_prefix The path against which suppressed executables must prefix match
 * @return es_return_t indicating success or error
 */
OS_EXPORT
API_DEPRECATED("Please use es_mute_path or es_mute_path_events.", macos(10.15, 12.0))
API_UNAVAILABLE(ios, tvos, watchos)
es_return_t es_mute_path_prefix(es_client_t *_Nonnull client, const char *_Nonnull path_prefix);

/**
 * Suppress events matching a path literal
 *
 * @deprecated Please use `es_mute_path` or `es_mute_path_events`
 *
 * @param client The client for which events will be suppressed
 * @param path_literal The path against which suppressed executables must match exactly
 * @return es_return_t indicating success or error
 *
 * @see es_mute_path
 * @see es_mute_path_events
 */
OS_EXPORT
API_DEPRECATED("Please use es_mute_path or es_mute_path_events.", macos(10.15, 12.0))
API_UNAVAILABLE(ios, tvos, watchos)
es_return_t es_mute_path_literal(es_client_t *_Nonnull client, const char *_Nonnull path_literal);

/**
 * Unmute all paths
 * @param client The client for which all currently muted paths will be unmuted
 * @return es_return_t indicating success or error
 *
 * @note Only unmutes executable paths. To unmute target paths see: `es_unmute_all_target_paths`.
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios) API_UNAVAILABLE(tvos, watchos) es_return_t es_unmute_all_paths(es_client_t *_Nonnull client);

/**
 * Unmute all target paths
 * @param client The client for which all currently muted target paths will be unmuted
 * @return es_return_t indicating success or error
 */
OS_EXPORT
API_AVAILABLE(macos(13.0))
API_UNAVAILABLE(ios) API_UNAVAILABLE(tvos, watchos) es_return_t es_unmute_all_target_paths(es_client_t *_Nonnull client);

/**
 * @brief Unmute a path for all event types.
 *
 * @param client The es_client_t for which the path will be unmuted.
 * @param path The path to unmute.
 * @param type Describes the type of the `path` parameter, either a prefix path or literal path.
 *
 * @return es_return_t A value indicating whether or not the path was successfully unmuted.
 *
 * @note Muting and unmuting operations logically work on a set of (path_type, path, es_event_type_t) tuples
 * Subtracting an element from the set that is not present has no effect
 * For example if `(literal, /foo/bar/, *)` is muted
 * Then `(prefix, /foo, *)` is unmuted the mute set is still:
 * `(literal, /foo/bar, *)`.
 * Prefixes only apply to mute evaluation not to modifications of the mute set.
 *
 * @see es_unmute_path_events
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_unmute_path(es_client_t *_Nonnull client, const char *_Nonnull path, es_mute_path_type_t type);

/**
 * @brief Unmute a path for a subset of event types.
 *
 * @param client The es_client_t for which the path will be unmuted.
 * @param path The path to unmute.
 * @param type Describes the type of the `path` parameter, either a prefix path or literal path.
 * @param events Array of event types for which the path should be unmuted.
 * @param event_count The number of items in the `events` array.
 *
 * @return es_return_t A value indicating whether or not the path was successfully unmuted.
 *
 * @see es_unmute_path
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_unmute_path_events(
	es_client_t *_Nonnull client,
	const char *_Nonnull path,
	es_mute_path_type_t type,
	const es_event_type_t *_Nonnull events,
	size_t event_count
);

/**
 * @brief Retrieve a list of all muted paths.
 *
 * @param client The es_client_t for which the muted paths will be retrieved.
 * @param muted_paths OUT param the will contain newly created memory describing the set of
 *        muted paths. This memory must be deleted using `es_release_muted_paths`.
 *
 * @return es_return_t A value indicating whether or not the list of muted paths were successfully retrieved.
 *
 * @see es_release_muted_paths
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_return_t es_muted_paths_events(es_client_t *_Nonnull client, es_muted_paths_t *_Nonnull *_Nullable muted_paths);

/**
 * @brief Delete a set of muted paths obtained from `es_muted_paths_events`, freeing resources.
 *
 * @param muted_paths A set of muted paths to delete.
 *
 * @see es_muted_paths_events
 */
OS_EXPORT
API_AVAILABLE(macos(12.0))
API_UNAVAILABLE(ios) API_UNAVAILABLE(tvos, watchos) void es_release_muted_paths(es_muted_paths_t *_Nonnull muted_paths);

/*
 * @brief Invert the mute state of a given mute dimension
 *
 * @param client The es_client_t for which muting will be inverted
 * @param mute_type The type of muting to invert (process, path, or target path).
 *
 * @return es_return_t A value indicating whether or not muting was inverted
 *
 * @discussion Inverting muting can be used to create a client that monitors a specific process(es) or set of directories
 * When muting is inverted it still combines with other types of muting using OR, and inversion happens first.
 * Consider a series of inputs for a system where pid 12 is muted, process muting is inverted, and /bin/bash is also path muted:
 *   (12, /bin/foo)  MATCHING (true, false)  INVERSION (false, false) || false → event is not suppressed
 *   (13, /bin/foo)  MATCHING (false, false) INVERSION (true, false)  || true  → event is suppressed
 *   (12, /bin/bash) MATCHING (true, true)   INVERSION (false, true)  || true  → event is suppressed
 *
 *   Note that because muting is combined using OR even when pid 12 is being selected using inverted process muting,
 *   (12, /bin/bash) is still suppressed because the path is muted
 *
 * The relationship between all three types of muting (proc,path,target-path) and how each can be inverted is complex.
 * The below flow chart explains in detail exactly how muting is applied in the kernel:
 *
 *  ┌──────────────────┐
 *  │      Event       │
 *  └──────────────────┘
 *            │
 *            ▼
 *  ┌──────────────────┐                                           ┌──────────────────┐
 *  │  Is Subscribed?  │────No────────────────────────────────────▶│  Suppress Event  │
 *  └──────────────────┘                                           └──────────────────┘
 *            │                                                              ▲
 *         Yes│                                                              │
 *            ▼                ┌────────────────┐                            │
 *  ┌──────────────────┐       │ Is Proc Muting │                            │
 *  │  Is Proc Muted?  ├─Yes──▶│   Inverted?    ├──No───────────────────────▶│
 *  └─────────┬────────┘       └────────────────┘                            │
 *            │                         │                                    │
 *          No│                        Yes                                   │
 *            ▼                         │                                    │
 *  ┌──────────────────┐                │                                    │
 *  │  Is Proc Muting  │                │                                    │
 *  │    Inverted?     │──Yes───────────)───────────────────────────────────▶│
 *  └─────────┬────────┘                │                                    │
 *            │                         │                                    │
 *          No│◀────────────────────────┘                                    │
 *            ▼                 ┌───────────────┐                            │
 *  ┌──────────────────┐        │Is Path Muting │                            │
 *  │  Is Path Muted?  │──Yes──▶│   Inverted?   ├──No───────────────────────▶│
 *  └─────────┬────────┘        └───────┬───────┘                            │
 *            │                         │                                    │
 *          No│                        Yes                                   │
 *            ▼                         │                                    │
 *  ┌──────────────────┐                │                                    │
 *  │  Is Path Muting  │                │                                    │
 *  │    Inverted?     │──Yes───────────)───────────────────────────────────▶│
 *  └─────────┬────────┘                │                                    │
 *            │                         │                                    │
 *          No│◀────────────────────────┘                                    │
 *            ▼                                                              │
 *  ┌──────────────────┐                                                     │
 *  │  Event Supports  │      ┌───────────────┐      ┌─────────────────┐     │
 *  │   Target Path    │─Yes─▶│Is Target Path ├─Yes─▶│ Are ANY target  ├─No─▶│
 *  │     Muting?      │      │Muting Inverted│      │  paths muted?   │     │
 *  └──────────────────┘      └──────┬────────┘      └───────┬─────────┘     │
 *            │                      │                       │               │
 *          No│                    No│                      Yes              │
 *            │                      ▼                       │               │
 *            │              ┌────────────────┐              │               │
 *            │              │ Are ALL target │              │               │
 *            │              │  paths muted?  ├─Yes──────────)───────────────┘
 *            │              └───────┬────────┘              │
 *            │                      │                       │
 *            │                    No│                       │
 *            │◀─────────────────────┘                       │
 *            │                                              │
 *            │◀─────────────────────────────────────────────┘
 *            │
 *            ▼
 *  ┌──────────────────┐
 *  │  Deliver Event   │
 *  └──────────────────┘
 *
 * @note Mute inversion does NOT clear the default mute set.
 * When a new `es_client_t` is created certain paths are muted by default.
 * This is known as "the default mute set".
 * The default mute set exists to protect ES clients from deadlocks, and to prevent watchdog timeout panics.
 * Creating a new client and calling `es_invert_muting(c, ES_MUTE_INVERSION_TYPE_PATH)` will result in the default mute set being
 * selected rather than muted. In most cases this is unintended. Consider calling `es_unmute_all_paths` before inverting process
 * path muting. Consider calling `es_unmute_all_target_paths` before inverting target path muting. Make sure the client has no
 * auth subscriptions before doing so. If desired the default mute set can be saved using `es_muted_paths_events` and then
 * restored after inverting again.
 *
 */
OS_EXPORT
API_AVAILABLE(macos(13.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos) es_return_t es_invert_muting(es_client_t *_Nonnull client, es_mute_inversion_type_t mute_type);

/*
 * @brief Query mute inversion state
 *
 * @param client The es_client_t for which mute inversion state is being queried.
 * @param mute_type The type of muting to query (process, path, or target path).
 *
 * @return es_mute_inverted_return_t Indicates if muting was inverted, not inverted, or if an error occurred.
 */
OS_EXPORT
API_AVAILABLE(macos(13.0))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_mute_inverted_return_t es_muting_inverted(es_client_t *_Nonnull client, es_mute_inversion_type_t mute_type);

/**
 * Clear all cached results for all clients.
 * @param client that will perform the request
 * @return es_clear_cache_result_t value indicating success or an error
 * @discussion This functions clears the shared cache for all ES clients and is hence rate limited.
 *             If es_clear_cache is called too frequently it will return ES_CLEAR_CACHE_RESULT_ERR_THROTTLE
 *             It is permissible to pass any valid es_client_t object created by `es_new_client`
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos) es_clear_cache_result_t es_clear_cache(es_client_t *_Nonnull client);

/**
 * es_handler_block_t The type of block that will be invoked to handled messages from the ES subsystem
 * The es_client_t is a handle to the client being sent the event. It must be passed to any "respond" functions
 * The es_message_t is the message that must be handled
 */
typedef void (^es_handler_block_t)(es_client_t *_Nonnull, const es_message_t *_Nonnull);

/**
 * Initialise a new es_client_t and connect to the ES subsystem
 * @param client Out param. On success this will be set to point to the newly allocated es_client_t.
 * @param handler The handler block that will be run on all messages sent to this client
 * @return es_new_client_result_t indicating success or a specific error.
 * @discussion Messages are handled strictly serially and in the order they are delivered.
 *             Returning control from the handler causes the next available message to be dequeued.
 *             Messages can be responded to out of order by returning control before calling es_respond_*.
 *             The es_message_t is only guaranteed to live as long as the scope it is passed into.
 *             The memory for the given es_message_t is NOT owned by clients and it must not be freed.
 *             For out of order responding the handler must retain the message with es_retain_message.
 *             Callers are required to be entitled with com.apple.developer.endpoint-security.client.
 *             The application calling this interface must also be approved by users via Transparency, Consent & Control
 *             (TCC) mechanisms using the Privacy Preferences pane and adding the application to Full Disk Access.
 *             When a new client is successfully created, all cached results are automatically cleared.
 *
 * @note When a new client is initialized, there will be a set of paths and a subset of `es_event_type_t` events that are
 *       automatically muted by default. Generally, most AUTH event variants are muted but NOTIFY event variants will
 *       still be sent to the client. The set of paths muted by default are ones that can have an extremely negative impact to
 *       end users if their AUTH events are not allowed in a timely manner (for example, executable paths for processes
 *       that are monitored by the watchdogd daemon). It is important to understand that this list is *not* exhaustive and
 *       developers using the EndpointSecurity framework can still interfere with critical system components and must use
 *       caution to limit user impact. The set of default muted paths and event types may change across macOS releases.
 *       It is possible to both inspect and unmute the set of default muted paths and associated event types using the
 *       appropriate mute-related API, however it is not recommended to unmute these items.
 *
 * @note The only supported way to check if an application is properly TCC authorized for Full Disk Access
 *       is to call es_new_client and handling ES_NEW_CLIENT_RESULT_ERR_NOT_PERMITTED in a way appropriate
 *       to your application.  Most applications will want to ask the user for TCC authorization when
 *       es_new_client returns ES_NEW_CLIENT_RESULT_ERR_NOT_PERMITTED.
 *       To direct the user to the Full Disk Access section in System Settings, applications can use the following URLs:
 *       `x-apple.systempreferences:com.apple.settings.PrivacySecurity.extension?Privacy_AllFiles` (macOS 13 and later)
 *       `x-apple.systempreferences:com.apple.preference.security?Privacy_AllFiles` (until macOS 12)
 *       Applications are advised to use the new URL in macOS 13 as the old one may stop working in a future release.
 *
 * @see es_retain_message
 * @see es_release_message
 * @see es_new_client_result_t
 * @see es_muted_paths_events
 * @see es_unmute_path_events
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios)
API_UNAVAILABLE(tvos, watchos)
es_new_client_result_t es_new_client(es_client_t *_Nullable *_Nonnull client, es_handler_block_t _Nonnull handler);

/**
 * Destroy an es_client_t, freeing resources and disconnecting from the ES subsystem
 * @param client The client to be destroyed
 * @return  ES_RETURN_SUCCESS indicates all resources were freed.
 *          ES_RETURN_ERROR indicates an error occurred during shutdown and resources were leaked.
 * @note Must be called from the same thread that originally called `es_new_client`.
 */
OS_EXPORT
API_AVAILABLE(macos(10.15))
API_UNAVAILABLE(ios) API_UNAVAILABLE(tvos, watchos) es_return_t es_delete_client(es_client_t *_Nullable client);

__END_DECLS;

#endif /* __ENDPOINT_SECURITY_CLIENT_H */
