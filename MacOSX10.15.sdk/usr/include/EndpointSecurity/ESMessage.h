#ifndef __ENDPOINT_SECURITY_MESSAGE_H
#define __ENDPOINT_SECURITY_MESSAGE_H

#ifndef __ENDPOINT_SECURITY_INDIRECT__
#error "Please #include <EndpointSecurity/EndpointSecurity.h> instead of this file directly."
#endif

#include <mach/message.h>
#include <stdbool.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <os/availability.h>
#include <os/base.h>

/**
 * The EndpointSecurity subsystem is responsible for creating, populating and
 * delivering these data structures to ES clients.
 */

/**
 * es_file_t provides the inode/devno and path to a file that relates to a security event
 * the path may be truncated, which is indicated by the path_truncated flag.
 *
 * @discussion Currently, path lengths are supported up to 16K in length (though this
 * number is subject to change at any time and users must not rely on this value being
 * constant). If a path is longer than the supported maximum length, it will be marked
 * as truncated via the `path_truncated` member.
 */
typedef struct {
	es_string_token_t path;
	bool path_truncated;
	struct stat64 stat;
} es_file_t;

/**
 * @brief describes a process that took the action being described in an es_message_t
 * For exec events also describes the newly executing process
 *
 * @discussion
 * - Values such as PID, UID, GID, etc. can be extraced from the audit token via API in libbsm.h.
 * - Clients should take caution when processing events where `is_es_client` is true. If multiple
 *   clients exist, actions taken by one client could trigger additional actions by the other client,
 *   causing a potentially infinite cycle.
 */
typedef struct {
	audit_token_t audit_token;
	pid_t ppid; //Note: This field tracks the current parent pid
	pid_t original_ppid; //Note: This field stays constant even in the event a process is reparented
	pid_t group_id;
	pid_t session_id;
	uint32_t codesigning_flags; //Note: The values for these flags can be found in the include file `cs_blobs.h` (`#include <kern/cs_blobs.h>`)
	bool is_platform_binary;
	bool is_es_client; //indicates this process is connected to the ES subsystem.
	uint8_t cdhash[CS_CDHASH_LEN];
	es_string_token_t signing_id;
	es_string_token_t team_id;
	es_file_t * _Nullable executable;
} es_process_t;


#ifdef KERNEL
	typedef struct statfs64 es_statfs_t;
#else
	#if !__DARWIN_64_BIT_INO_T
		#error This header requires __DARWIN_64_BIT_INO_T
	#endif
	typedef struct statfs es_statfs_t;
#endif

/**
 * Arguments and environment variables are packed, use the following functions to operate on this field:
 * `es_exec_env`, `es_exec_arg`, `es_exec_env_count`, and `es_exec_arg_count`
 */
typedef struct {
	es_process_t * _Nullable target;
	es_token_t args;
	uint8_t reserved[64];
} es_event_exec_t;

/**
 * Note: The `fflag` field represents the mask as applied by the kernel, not as represented by typical
 * open(2) `oflag` values. When responding to `ES_EVENT_TYPE_AUTH_OPEN` events using
 * es_respond_flags_result(), ensure that the same FFLAG values are used (e.g. FREAD, FWRITE instead
 * of O_RDONLY, O_RDWR, etc...).
 *
 * @see fcntl.h
 */
typedef struct {
	int32_t fflag;
	es_file_t * _Nullable file;
	uint8_t reserved[64];
} es_event_open_t;

typedef struct {
	es_string_token_t identifier;
	uint8_t reserved[64];
} es_event_kextload_t;

typedef struct {
	es_string_token_t identifier;
	uint8_t reserved[64];
} es_event_kextunload_t;

typedef struct {
	es_file_t * _Nullable target;
	es_file_t * _Nullable parent_dir;
	uint8_t reserved[64];
} es_event_unlink_t;

typedef struct {
	int32_t protection;
	int32_t max_protection;
	int32_t flags;
	uint64_t file_pos;
	es_file_t * _Nullable source;
	uint8_t reserved[64];
} es_event_mmap_t;

typedef struct {
	es_file_t * _Nullable source;
	es_file_t * _Nullable target_dir;
	es_string_token_t target_filename;
	uint8_t reserved[64];
} es_event_link_t;

typedef struct {
	es_statfs_t * _Nullable statfs;
	uint8_t reserved[64];
} es_event_mount_t;

typedef struct {
	es_statfs_t * _Nullable statfs;
	uint8_t reserved[64];
} es_event_unmount_t;

typedef struct {
	es_process_t * _Nullable child;
	uint8_t reserved[64];
} es_event_fork_t;

typedef struct {
	int32_t protection;
	user_addr_t address;
	user_size_t size;
	uint8_t reserved[64];
} es_event_mprotect_t;

typedef struct {
	int sig;
	es_process_t * _Nullable target;
	uint8_t reserved[64];
} es_event_signal_t;

typedef enum {
	ES_DESTINATION_TYPE_EXISTING_FILE,
	ES_DESTINATION_TYPE_NEW_PATH,
} es_destination_type_t;

typedef struct {
	es_file_t * _Nullable source;
	es_destination_type_t destination_type;
	union {
		es_file_t * _Nullable existing_file;
		struct {
			es_file_t * _Nullable dir;
			es_string_token_t filename;
		} new_path;
	} destination;
	uint8_t reserved[64];
} es_event_rename_t;

typedef struct {
	es_file_t * _Nullable target;
	es_string_token_t extattr;
	uint8_t reserved[64];
} es_event_setextattr_t;

typedef struct {
	mode_t mode;
	es_file_t * _Nullable target;
	uint8_t reserved[64];
} es_event_setmode_t;

typedef struct {
	uint32_t flags;
	es_file_t * _Nullable target;
	uint8_t reserved[64];
} es_event_setflags_t;

typedef struct {
	uid_t uid;
	gid_t gid;
	es_file_t * _Nullable target;
	uint8_t reserved[64];
} es_event_setowner_t;

typedef struct {
	bool modified;
	es_file_t * _Nullable target;
	uint8_t reserved[64];
} es_event_close_t;

/**
 * @note If an object is being created but has not yet been created, the
 * `destination_type` will be `ES_DESTINATION_TYPE_NEW_PATH`.
 *
 * Typically, `ES_EVENT_TYPE_NOTIFY_CREATE` events are created after the
 * object has been created and the `destination_type` will be
 * `ES_DESTINATION_TYPE_EXISTING_FILE`. The exception to this is for
 * notifications that occur if an ES client responds to an
 * `ES_EVENT_TYPE_AUTH_CREATE` event with `ES_AUTH_RESULT_DENY`.
 *
 */
typedef struct {
	es_destination_type_t destination_type;
	union {
		es_file_t * _Nullable existing_file;
		struct {
			es_file_t * _Nullable dir;
			es_string_token_t filename;
			mode_t mode;
		} new_path;
	} destination;
	uint8_t reserved[64];
} es_event_create_t;

typedef struct {
	int stat; /* same format as wait() */
	uint8_t reserved[64];
} es_event_exit_t;

typedef struct {
	es_file_t * _Nullable file1;
	es_file_t * _Nullable file2;
	uint8_t reserved[64];
} es_event_exchangedata_t;

typedef struct {
	es_file_t * _Nullable target;
	uint8_t reserved[64];
} es_event_write_t;

typedef struct {
	uint32_t user_client_type;
	es_string_token_t user_client_class;
	uint8_t reserved[64];
} es_event_iokit_open_t;

typedef struct {
	es_process_t * _Nullable target;
	uint8_t reserved[64];
} es_event_get_task_t;

typedef struct {
	struct attrlist attrlist;
	es_file_t * _Nullable target;
	uint8_t reserved[64];
} es_event_setattrlist_t;

typedef struct {
	es_file_t * _Nullable source;
	es_string_token_t target_path;
	uint8_t reserved[64];
} es_event_file_provider_update_t;

typedef struct {
	es_process_t * _Nullable instigator;
	es_file_t * _Nullable source;
	es_file_t * _Nullable target;
	uint8_t reserved[64];
} es_event_file_provider_materialize_t;

typedef struct {
	es_file_t * _Nullable source;
	uint8_t reserved[64];
} es_event_readlink_t;

typedef struct {
	es_file_t * _Nullable target;
	uint8_t reserved[64];
} es_event_truncate_t;

typedef struct {
	es_file_t * _Nullable source_dir;
	es_string_token_t relative_target;
} es_event_lookup_t;

/**
 * Union of all possble events that can appear in an es_message_t
 */
typedef union {
	es_event_close_t close;
	es_event_create_t create;
	es_event_exchangedata_t exchangedata;
	es_event_exec_t exec;
	es_event_exit_t exit;
	es_event_file_provider_materialize_t file_provider_materialize;
	es_event_file_provider_update_t file_provider_update;
	es_event_fork_t fork;
	es_event_get_task_t get_task;
	es_event_iokit_open_t iokit_open;
	es_event_kextload_t kextload;
	es_event_kextunload_t kextunload;
	es_event_link_t link;
	es_event_lookup_t lookup;
	es_event_mmap_t mmap;
	es_event_mount_t mount;
	es_event_mprotect_t mprotect;
	es_event_open_t open;
	es_event_readlink_t readlink;
	es_event_rename_t rename;
	es_event_setattrlist_t setattrlist;
	es_event_setextattr_t setextattr;
	es_event_setflags_t setflags;
	es_event_setmode_t setmode;
	es_event_setowner_t setowner;
	es_event_signal_t signal;
	es_event_truncate_t truncate;
	es_event_unlink_t unlink;
	es_event_unmount_t unmount;
	es_event_write_t write;
} es_events_t;

/**
 * es_result_t indicates the result of the ES subsystem authorization process
 * The result_type field indicates if the result is an es_auth_result_t or a uint32_t (flags)
 */
typedef struct {
	es_result_type_t result_type;
	union {
		es_auth_result_t auth;
		uint32_t flags;
		uint8_t reserved[32];
	} result;
} es_result_t;

/**
 * es_message_t is the top level datatype that encodes information sent from the ES subsystem to its clients
 * Each security event being processed by the ES subsystem will be encoded in an es_message_t
 * A message can be an authorization request or a notification of an event that has already taken place
 * The action_type indicates if the action field is an auth or notify action
 * The event_type indicates which event struct is defined in the event union.
 * For events that can be authorized there are unique NOTIFY and AUTH event types for the same event data
 * eg: event.exec is the correct union label for both ES_EVENT_TYPE_AUTH_EXEC and ES_EVENT_TYPE_NOTIFY_EXEC event types
 */
typedef struct {
	uint32_t version;
	struct timespec time;
	uint64_t mach_time;
	uint64_t deadline;
	es_process_t * _Nullable process;
	uint8_t reserved[8];
	es_action_type_t action_type;
	union {
		es_event_id_t auth;
		es_result_t notify;
	} action;
	es_event_type_t event_type;
	es_events_t event;
	uint64_t opaque[]; /* Opaque data that must not be accessed directly */
} es_message_t;

__BEGIN_DECLS

/**
 * Calculate the size of an es_message_t.
 * @param msg The message for which the size will be calculated
 * @return Size of the message
 */
OS_EXPORT
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
size_t
es_message_size(const es_message_t * _Nonnull msg);

/**
 * Copy an es_message_t, allocating new memory.
 * @param msg The message to be copied
 * @return pointer to newly allocated es_message_t.
 *
 * @brief The caller owns the memory for the returned es_message_t and must free it using es_free_message.
 */
OS_EXPORT
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
es_message_t * _Nullable
es_copy_message(const es_message_t * _Nonnull msg);

/**
 * Frees the memory associated with the given es_message_t
 * @param msg The message to be freed
 */
OS_EXPORT
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
void
es_free_message(es_message_t * _Nonnull msg);

/**
 * Get the number of arguments in a message containing an es_event_exec_t
 * @param event The es_exec_event_t being inspected
 * @return The number of arguments
 */
OS_EXPORT
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
uint32_t
es_exec_arg_count(const es_event_exec_t * _Nonnull event);

/**
 * Get the number of environment variables in a message containing an es_event_exec_t
 * @param event The es_exec_event_t being inspected
 * @return The number of environment variables
 */
OS_EXPORT
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
uint32_t
es_exec_env_count(const es_event_exec_t * _Nonnull event);

/**
 * Get the argument at the specified position in the message containing an es_event_exec_t
 * @param event The es_exec_event_t being inspected
 * @param index Index of the arguement to retrieve (starts from 0)
 * @return  es_string_token_t containing a pointer to the argument and its length.
 *          This is a zero-allocation operation. The returned pointer must not outlive exec_event.
 * @brief Reading an an argument where `index` >= `es_exec_arg_count()` is undefined
 */
OS_EXPORT
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
es_string_token_t
es_exec_arg(const es_event_exec_t * _Nonnull event, uint32_t index);

/**
 * Get the environemnt variable at the specified position in the message containing an es_event_exec_t
 * @param event The es_exec_event_t being inspected
 * @param index Index of the environemnt variable to retrieve (starts from 0)
 * @return  es_string_token_t containing a pointer to the environment variable and its length.
 *          This is zero-allocation operation. The returned pointer must not outlive exec_event.
 * @brief Reading an an env where `index` >= `es_exec_env_count()` is undefined
 */
OS_EXPORT
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
es_string_token_t
es_exec_env(const es_event_exec_t * _Nonnull event, uint32_t index);

__END_DECLS

#endif /* __ENDPOINT_SECURITY_MESSAGE_H */
