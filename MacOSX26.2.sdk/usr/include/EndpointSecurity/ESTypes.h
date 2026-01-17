#ifndef __ENDPOINT_SECURITY_TYPES_H
#define __ENDPOINT_SECURITY_TYPES_H

#include <mach/message.h>
#include <os/availability.h>
#include <os/base.h>
#include <stdint.h>
#include <sys/types.h>
#include <uuid/uuid.h>

typedef struct {
	uint8_t reserved[32];
} es_event_id_t;

typedef enum {
	ES_ACTION_TYPE_AUTH,
	ES_ACTION_TYPE_NOTIFY
} es_action_type_t;

typedef enum {
	ES_SET,
	ES_CLEAR
} es_set_or_clear_t;

/**
 * @brief This enum describes the type of the es_event_proc_check_t event that are currently used
 *
 * @note ES_PROC_CHECK_TYPE_KERNMSGBUF, ES_PROC_CHECK_TYPE_TERMINATE and
 * ES_PROC_CHECK_TYPE_UDATA_INFO are deprecated and no proc_check messages will be generated
 * for the corresponding proc_info call numbers.
 * The terminate callnum is covered by the signal event.
 */
typedef enum {
	ES_PROC_CHECK_TYPE_LISTPIDS = 0x1,
	ES_PROC_CHECK_TYPE_PIDINFO = 0x2,
	ES_PROC_CHECK_TYPE_PIDFDINFO = 0x3,
	ES_PROC_CHECK_TYPE_KERNMSGBUF = 0x4, // deprecated, not generated
	ES_PROC_CHECK_TYPE_SETCONTROL = 0x5,
	ES_PROC_CHECK_TYPE_PIDFILEPORTINFO = 0x6,
	ES_PROC_CHECK_TYPE_TERMINATE = 0x7, // deprecated, not generated
	ES_PROC_CHECK_TYPE_DIRTYCONTROL = 0x8,
	ES_PROC_CHECK_TYPE_PIDRUSAGE = 0x9,
	ES_PROC_CHECK_TYPE_UDATA_INFO = 0xe, // deprecated, not generated
} es_proc_check_type_t;

/**
 * @brief This enum describes the types of XPC service domains.
 */
typedef enum {
	ES_XPC_DOMAIN_TYPE_SYSTEM = 1,
	ES_XPC_DOMAIN_TYPE_USER,
	ES_XPC_DOMAIN_TYPE_USER_LOGIN,
	ES_XPC_DOMAIN_TYPE_SESSION,
	ES_XPC_DOMAIN_TYPE_PID,
	ES_XPC_DOMAIN_TYPE_MANAGER,
	ES_XPC_DOMAIN_TYPE_PORT,
	ES_XPC_DOMAIN_TYPE_GUI,
} es_xpc_domain_type_t;

/**
 * @brief This enum describes the types of authentications that
 * ES_EVENT_TYPE_NOTIFY_AUTHENTICATION can describe.
 */
typedef enum {
	ES_AUTHENTICATION_TYPE_OD,
	ES_AUTHENTICATION_TYPE_TOUCHID,
	ES_AUTHENTICATION_TYPE_TOKEN,
	ES_AUTHENTICATION_TYPE_AUTO_UNLOCK,
	// ES_AUTHENTICATION_TYPE_LAST is not a valid type of authentication
	// but is a convenience value to operate on the range of defined
	// authentication types.
	ES_AUTHENTICATION_TYPE_LAST
} es_authentication_type_t;

/**
 * @brief This enum describes the type of plugin types in sudo
 */
typedef enum {
	ES_SUDO_PLUGIN_TYPE_UNKNOWN,
	ES_SUDO_PLUGIN_TYPE_FRONT_END,
	ES_SUDO_PLUGIN_TYPE_POLICY,
	ES_SUDO_PLUGIN_TYPE_IO,
	ES_SUDO_PLUGIN_TYPE_AUDIT,
	ES_SUDO_PLUGIN_TYPE_APPROVAL,
} es_sudo_plugin_type_t;

/**
 * The valid event types recognized by EndpointSecurity
 *
 * @discussion When a program subscribes to and receives an AUTH-related event, it must respond
 * with an appropriate result indicating whether or not the operation should be allowed to continue.
 * The valid API options are:
 * - es_respond_auth_result
 * - es_respond_flags_result
 *
 * Currently, only ES_EVENT_TYPE_AUTH_OPEN must use es_respond_flags_result. All other AUTH events
 * must use es_respond_auth_result.
 */
typedef enum {
	// The following events are available beginning in macOS 10.15
	ES_EVENT_TYPE_AUTH_EXEC,
	ES_EVENT_TYPE_AUTH_OPEN,
	ES_EVENT_TYPE_AUTH_KEXTLOAD,
	ES_EVENT_TYPE_AUTH_MMAP,
	ES_EVENT_TYPE_AUTH_MPROTECT,
	ES_EVENT_TYPE_AUTH_MOUNT,
	ES_EVENT_TYPE_AUTH_RENAME,
	ES_EVENT_TYPE_AUTH_SIGNAL,
	ES_EVENT_TYPE_AUTH_UNLINK,
	ES_EVENT_TYPE_NOTIFY_EXEC,
	ES_EVENT_TYPE_NOTIFY_OPEN,
	ES_EVENT_TYPE_NOTIFY_FORK,
	ES_EVENT_TYPE_NOTIFY_CLOSE,
	ES_EVENT_TYPE_NOTIFY_CREATE,
	ES_EVENT_TYPE_NOTIFY_EXCHANGEDATA,
	ES_EVENT_TYPE_NOTIFY_EXIT,
	ES_EVENT_TYPE_NOTIFY_GET_TASK,
	ES_EVENT_TYPE_NOTIFY_KEXTLOAD,
	ES_EVENT_TYPE_NOTIFY_KEXTUNLOAD,
	ES_EVENT_TYPE_NOTIFY_LINK,
	ES_EVENT_TYPE_NOTIFY_MMAP,
	ES_EVENT_TYPE_NOTIFY_MPROTECT,
	ES_EVENT_TYPE_NOTIFY_MOUNT,
	ES_EVENT_TYPE_NOTIFY_UNMOUNT,
	ES_EVENT_TYPE_NOTIFY_IOKIT_OPEN,
	ES_EVENT_TYPE_NOTIFY_RENAME,
	ES_EVENT_TYPE_NOTIFY_SETATTRLIST,
	ES_EVENT_TYPE_NOTIFY_SETEXTATTR,
	ES_EVENT_TYPE_NOTIFY_SETFLAGS,
	ES_EVENT_TYPE_NOTIFY_SETMODE,
	ES_EVENT_TYPE_NOTIFY_SETOWNER,
	ES_EVENT_TYPE_NOTIFY_SIGNAL,
	ES_EVENT_TYPE_NOTIFY_UNLINK,
	ES_EVENT_TYPE_NOTIFY_WRITE,
	ES_EVENT_TYPE_AUTH_FILE_PROVIDER_MATERIALIZE,
	ES_EVENT_TYPE_NOTIFY_FILE_PROVIDER_MATERIALIZE,
	ES_EVENT_TYPE_AUTH_FILE_PROVIDER_UPDATE,
	ES_EVENT_TYPE_NOTIFY_FILE_PROVIDER_UPDATE,
	ES_EVENT_TYPE_AUTH_READLINK,
	ES_EVENT_TYPE_NOTIFY_READLINK,
	ES_EVENT_TYPE_AUTH_TRUNCATE,
	ES_EVENT_TYPE_NOTIFY_TRUNCATE,
	ES_EVENT_TYPE_AUTH_LINK,
	ES_EVENT_TYPE_NOTIFY_LOOKUP,
	ES_EVENT_TYPE_AUTH_CREATE,
	ES_EVENT_TYPE_AUTH_SETATTRLIST,
	ES_EVENT_TYPE_AUTH_SETEXTATTR,
	ES_EVENT_TYPE_AUTH_SETFLAGS,
	ES_EVENT_TYPE_AUTH_SETMODE,
	ES_EVENT_TYPE_AUTH_SETOWNER,

	// The following events are available beginning in macOS 10.15.1
	ES_EVENT_TYPE_AUTH_CHDIR,
	ES_EVENT_TYPE_NOTIFY_CHDIR,
	ES_EVENT_TYPE_AUTH_GETATTRLIST,
	ES_EVENT_TYPE_NOTIFY_GETATTRLIST,
	ES_EVENT_TYPE_NOTIFY_STAT,
	ES_EVENT_TYPE_NOTIFY_ACCESS,
	ES_EVENT_TYPE_AUTH_CHROOT,
	ES_EVENT_TYPE_NOTIFY_CHROOT,
	ES_EVENT_TYPE_AUTH_UTIMES,
	ES_EVENT_TYPE_NOTIFY_UTIMES,
	ES_EVENT_TYPE_AUTH_CLONE,
	ES_EVENT_TYPE_NOTIFY_CLONE,
	ES_EVENT_TYPE_NOTIFY_FCNTL,
	ES_EVENT_TYPE_AUTH_GETEXTATTR,
	ES_EVENT_TYPE_NOTIFY_GETEXTATTR,
	ES_EVENT_TYPE_AUTH_LISTEXTATTR,
	ES_EVENT_TYPE_NOTIFY_LISTEXTATTR,
	ES_EVENT_TYPE_AUTH_READDIR,
	ES_EVENT_TYPE_NOTIFY_READDIR,
	ES_EVENT_TYPE_AUTH_DELETEEXTATTR,
	ES_EVENT_TYPE_NOTIFY_DELETEEXTATTR,
	ES_EVENT_TYPE_AUTH_FSGETPATH,
	ES_EVENT_TYPE_NOTIFY_FSGETPATH,
	ES_EVENT_TYPE_NOTIFY_DUP,
	ES_EVENT_TYPE_AUTH_SETTIME,
	ES_EVENT_TYPE_NOTIFY_SETTIME,
	ES_EVENT_TYPE_NOTIFY_UIPC_BIND,
	ES_EVENT_TYPE_AUTH_UIPC_BIND,
	ES_EVENT_TYPE_NOTIFY_UIPC_CONNECT,
	ES_EVENT_TYPE_AUTH_UIPC_CONNECT,
	ES_EVENT_TYPE_AUTH_EXCHANGEDATA,
	ES_EVENT_TYPE_AUTH_SETACL,
	ES_EVENT_TYPE_NOTIFY_SETACL,

	// The following events are available beginning in macOS 10.15.4
	ES_EVENT_TYPE_NOTIFY_PTY_GRANT,
	ES_EVENT_TYPE_NOTIFY_PTY_CLOSE,
	ES_EVENT_TYPE_AUTH_PROC_CHECK,
	ES_EVENT_TYPE_NOTIFY_PROC_CHECK,
	ES_EVENT_TYPE_AUTH_GET_TASK,

	// The following events are available beginning in macOS 11.0
	ES_EVENT_TYPE_AUTH_SEARCHFS,
	ES_EVENT_TYPE_NOTIFY_SEARCHFS,
	ES_EVENT_TYPE_AUTH_FCNTL,
	ES_EVENT_TYPE_AUTH_IOKIT_OPEN,
	ES_EVENT_TYPE_AUTH_PROC_SUSPEND_RESUME,
	ES_EVENT_TYPE_NOTIFY_PROC_SUSPEND_RESUME,
	ES_EVENT_TYPE_NOTIFY_CS_INVALIDATED,
	ES_EVENT_TYPE_NOTIFY_GET_TASK_NAME,
	ES_EVENT_TYPE_NOTIFY_TRACE,
	ES_EVENT_TYPE_NOTIFY_REMOTE_THREAD_CREATE,
	ES_EVENT_TYPE_AUTH_REMOUNT,
	ES_EVENT_TYPE_NOTIFY_REMOUNT,

	// The following events are available beginning in macOS 11.3
	ES_EVENT_TYPE_AUTH_GET_TASK_READ,
	ES_EVENT_TYPE_NOTIFY_GET_TASK_READ,
	ES_EVENT_TYPE_NOTIFY_GET_TASK_INSPECT,

	// The following events are available beginning in macOS 12.0
	ES_EVENT_TYPE_NOTIFY_SETUID,
	ES_EVENT_TYPE_NOTIFY_SETGID,
	ES_EVENT_TYPE_NOTIFY_SETEUID,
	ES_EVENT_TYPE_NOTIFY_SETEGID,
	ES_EVENT_TYPE_NOTIFY_SETREUID,
	ES_EVENT_TYPE_NOTIFY_SETREGID,
	ES_EVENT_TYPE_AUTH_COPYFILE,
	ES_EVENT_TYPE_NOTIFY_COPYFILE,

	// The following events are available beginning in macOS 13.0
	ES_EVENT_TYPE_NOTIFY_AUTHENTICATION,
	ES_EVENT_TYPE_NOTIFY_XP_MALWARE_DETECTED,
	ES_EVENT_TYPE_NOTIFY_XP_MALWARE_REMEDIATED,
	ES_EVENT_TYPE_NOTIFY_LW_SESSION_LOGIN,
	ES_EVENT_TYPE_NOTIFY_LW_SESSION_LOGOUT,
	ES_EVENT_TYPE_NOTIFY_LW_SESSION_LOCK,
	ES_EVENT_TYPE_NOTIFY_LW_SESSION_UNLOCK,
	ES_EVENT_TYPE_NOTIFY_SCREENSHARING_ATTACH,
	ES_EVENT_TYPE_NOTIFY_SCREENSHARING_DETACH,
	ES_EVENT_TYPE_NOTIFY_OPENSSH_LOGIN,
	ES_EVENT_TYPE_NOTIFY_OPENSSH_LOGOUT,
	ES_EVENT_TYPE_NOTIFY_LOGIN_LOGIN,
	ES_EVENT_TYPE_NOTIFY_LOGIN_LOGOUT,
	ES_EVENT_TYPE_NOTIFY_BTM_LAUNCH_ITEM_ADD,
	ES_EVENT_TYPE_NOTIFY_BTM_LAUNCH_ITEM_REMOVE,

	// The following events are available beginning in macOS 14.0
	ES_EVENT_TYPE_NOTIFY_PROFILE_ADD,
	ES_EVENT_TYPE_NOTIFY_PROFILE_REMOVE,
	ES_EVENT_TYPE_NOTIFY_SU,
	ES_EVENT_TYPE_NOTIFY_AUTHORIZATION_PETITION,
	ES_EVENT_TYPE_NOTIFY_AUTHORIZATION_JUDGEMENT,
	ES_EVENT_TYPE_NOTIFY_SUDO,
	ES_EVENT_TYPE_NOTIFY_OD_GROUP_ADD,
	ES_EVENT_TYPE_NOTIFY_OD_GROUP_REMOVE,
	ES_EVENT_TYPE_NOTIFY_OD_GROUP_SET,
	ES_EVENT_TYPE_NOTIFY_OD_MODIFY_PASSWORD,
	ES_EVENT_TYPE_NOTIFY_OD_DISABLE_USER,
	ES_EVENT_TYPE_NOTIFY_OD_ENABLE_USER,
	ES_EVENT_TYPE_NOTIFY_OD_ATTRIBUTE_VALUE_ADD,
	ES_EVENT_TYPE_NOTIFY_OD_ATTRIBUTE_VALUE_REMOVE,
	ES_EVENT_TYPE_NOTIFY_OD_ATTRIBUTE_SET,
	ES_EVENT_TYPE_NOTIFY_OD_CREATE_USER,
	ES_EVENT_TYPE_NOTIFY_OD_CREATE_GROUP,
	ES_EVENT_TYPE_NOTIFY_OD_DELETE_USER,
	ES_EVENT_TYPE_NOTIFY_OD_DELETE_GROUP,
	ES_EVENT_TYPE_NOTIFY_XPC_CONNECT,

	// The following events are available beginning in macOS 15.0
	ES_EVENT_TYPE_NOTIFY_GATEKEEPER_USER_OVERRIDE,

	// The following events are available beginning in macOS 15.4
	ES_EVENT_TYPE_NOTIFY_TCC_MODIFY,
	// ES_EVENT_TYPE_LAST is not a valid event type but a convenience
	// value for operating on the range of defined event types.
	// This value may change between releases and was available
	// beginning in macOS 10.15
	ES_EVENT_TYPE_LAST
} es_event_type_t;

/**
 * @brief Valid authorization values to be used when responding to a es_message_t auth event
 */
typedef enum {
	/// The event is authorized and should be allowed to continue
	ES_AUTH_RESULT_ALLOW,
	/// The event is not authorized and should be blocked
	ES_AUTH_RESULT_DENY
} es_auth_result_t;

/**
 * @brief Valid values for the result_type of es_result_t to indicate the appropriate union member to use
 */
typedef enum {
	/// The result is an auth result
	ES_RESULT_TYPE_AUTH,
	/// The result is a flags result
	ES_RESULT_TYPE_FLAGS
} es_result_type_t;

/**
 @brief Return value for functions that can only fail in one way
 */
typedef enum {
	ES_RETURN_SUCCESS,
	ES_RETURN_ERROR
} es_return_t;

/**
 @brief Error conditions for responding to a message
 */
typedef enum {
	ES_RESPOND_RESULT_SUCCESS,
	/// One or more invalid arguments were provided
	ES_RESPOND_RESULT_ERR_INVALID_ARGUMENT,
	/// Communication with the ES subsystem failed
	ES_RESPOND_RESULT_ERR_INTERNAL,
	/// The message being responded to could not be found
	ES_RESPOND_RESULT_NOT_FOUND,
	/// The provided message has been responded to more than once
	ES_RESPOND_RESULT_ERR_DUPLICATE_RESPONSE,
	/// Either an inappropriate response API was used for the event type (ensure using proper
	/// es_respond_auth_result or es_respond_flags_result function) or the event is notification only.
	ES_RESPOND_RESULT_ERR_EVENT_TYPE
} es_respond_result_t;

/**
 @brief Error conditions for creating a new client
 */
typedef enum {
	ES_NEW_CLIENT_RESULT_SUCCESS,
	/// One or more invalid arguments were provided.
	ES_NEW_CLIENT_RESULT_ERR_INVALID_ARGUMENT,
	/// Communication with the ES subsystem failed, or other error condition.
	ES_NEW_CLIENT_RESULT_ERR_INTERNAL,
	/// The caller is not properly entitled to connect.
	ES_NEW_CLIENT_RESULT_ERR_NOT_ENTITLED,
	/// The caller lacks Transparency, Consent, and Control (TCC) approval from the user.
	ES_NEW_CLIENT_RESULT_ERR_NOT_PERMITTED,
	/// The caller is not running as root.
	ES_NEW_CLIENT_RESULT_ERR_NOT_PRIVILEGED,
	/// The caller has reached the maximum number of allowed simultaneously connected clients.
	ES_NEW_CLIENT_RESULT_ERR_TOO_MANY_CLIENTS
} es_new_client_result_t;

/**
 @brief Error conditions for clearing the authorisation caches
 */
typedef enum {
	ES_CLEAR_CACHE_RESULT_SUCCESS,
	/// Communication with the ES subsystem failed
	ES_CLEAR_CACHE_RESULT_ERR_INTERNAL,
	/// Rate of calls is too high. Slow down.
	ES_CLEAR_CACHE_RESULT_ERR_THROTTLE
} es_clear_cache_result_t;

/**
 * @brief Binary CDHash
 *
 * The Code Directory Hash (CDHash) is a hash of hashes, covering a macho or an entire application bundle.
 * The Code Directory contains the hash of each executable page in the main executable. Only when:
 *
 *    - The subject process has opted into the hardened runtime (CS_HARD/CS_KILL)
 * 	  - The subject process is not being debugged
 *    - The subject process is running
 *
 * is it guaranteed that the ES provided cdhash value matches the binary observed by the kernel and that the
 * pages actually executed have not been modified.
 */
typedef uint8_t es_cdhash_t[20];

/**
 * @brief Binary Sha256 Digest
 */
typedef uint8_t es_sha256_t[32];

/**
 * @brief Structure buffer with size
 */
typedef struct {
	// Size of the `data` field in bytes
	size_t size;
	const uint8_t *data;
} es_token_t;

/**
 * @brief Structure for handling strings
 */
typedef struct {
	// Length of the `data` field. Equivalent to strlen().
	size_t length;
	const char *data;
} es_string_token_t;

/*
 * @brief Values that will be paired with path strings to describe the type of the path
 */
typedef enum {
	/// Value to describe a path prefix
	ES_MUTE_PATH_TYPE_PREFIX,
	/// Value to describe a path literal
	ES_MUTE_PATH_TYPE_LITERAL,
	/// Value to describe a target path prefix
	ES_MUTE_PATH_TYPE_TARGET_PREFIX
	API_AVAILABLE(macos(13.0)),
	/// Value to describe a target path literal
	ES_MUTE_PATH_TYPE_TARGET_LITERAL
	API_AVAILABLE(macos(13.0))
} es_mute_path_type_t;

/*
 * Structure to describe attributes of a muted path.
 *
 * @field type Indicates if the path is a prefix or literal, and what type of muting applies.
 * @field event_count The number of events contained in the `events` array.
 * @field events Array of event types for which the path is muted.
 * @field path The muted path. (Note: es_string_token_t is a char array and length)
 */
typedef struct {
	es_mute_path_type_t type;
	size_t event_count;
	const es_event_type_t *events;
	es_string_token_t path;
} es_muted_path_t;

/*
 * Structure for a set of muted paths.
 *
 * @field count The number of elements in the `paths` array.
 * @field paths Array of muted paths.
 */
typedef struct {
	size_t count;
	const es_muted_path_t *paths;
} es_muted_paths_t;

/*
 * Structure to describe attributes of a muted process.
 *
 * @field token The audit token of a muted process.
 * @field event_count The number of events contained in the `events` array.
 * @field events Array of event types for which the process is muted.
 */
typedef struct {
	audit_token_t audit_token;
	size_t event_count;
	const es_event_type_t *events;
} es_muted_process_t;

/*
 * Structure for a set of muted processes.
 *
 * @field count The number of elements in the `processes` array.
 * @field processes Array of muted processes.
 */
typedef struct {
	size_t count;
	const es_muted_process_t *processes;
} es_muted_processes_t;

/*
 * Type of a network address.
 */
typedef enum {
	/// No source address available.
	ES_ADDRESS_TYPE_NONE,
	/// Source address is IPv4.
	ES_ADDRESS_TYPE_IPV4,
	/// Source address is IPv6.
	ES_ADDRESS_TYPE_IPV6,
	/// Source address is named UNIX socket.
	ES_ADDRESS_TYPE_NAMED_SOCKET,
} es_address_type_t;

typedef enum {
	ES_MUTE_INVERSION_TYPE_PROCESS,
	ES_MUTE_INVERSION_TYPE_PATH,
	ES_MUTE_INVERSION_TYPE_TARGET_PATH,
	ES_MUTE_INVERSION_TYPE_LAST
} es_mute_inversion_type_t API_AVAILABLE(macos(13.0));

typedef enum {
	/// The type of muted queried was inverted
	ES_MUTE_INVERTED,
	/// The type of muted queried was not inverted
	ES_MUTE_NOT_INVERTED,
	/// There was an error querying mute inversion state
	ES_MUTE_INVERTED_ERROR
} es_mute_inverted_return_t;

/*
 * The class of rules used to evaluate the petition for a specific authorization right
 */
typedef enum {
	/// Right is judged on user properties
	ES_AUTHORIZATION_RULE_CLASS_USER,
	/// Right is judged by a tree of sub-rules
	ES_AUTHORIZATION_RULE_CLASS_RULE,
	/// Right is judged by one or more plugins
	ES_AUTHORIZATION_RULE_CLASS_MECHANISM,
	/// Right is always granted
	ES_AUTHORIZATION_RULE_CLASS_ALLOW,
	/// Right is always denied
	ES_AUTHORIZATION_RULE_CLASS_DENY,
	/// Right is unknown
	ES_AUTHORIZATION_RULE_CLASS_UNKNOWN,
	/// Right is invalid
	ES_AUTHORIZATION_RULE_CLASS_INVALID
} es_authorization_rule_class_t;

// The following types are used in OpenDirectory (od) events
/*
 * Type of a group member
 */
typedef enum {
	/// Group member is a user, designated by name
	ES_OD_MEMBER_TYPE_USER_NAME,
	/// Group member is a user, designated by UUID
	ES_OD_MEMBER_TYPE_USER_UUID,
	/// Group member is another group, designated by UUID
	ES_OD_MEMBER_TYPE_GROUP_UUID
} es_od_member_type_t;

/*
 * Type of an account
 */
typedef enum {
	ES_OD_ACCOUNT_TYPE_USER,
	ES_OD_ACCOUNT_TYPE_COMPUTER
} es_od_account_type_t;

/*
 * Type of a record
 */
typedef enum {
	ES_OD_RECORD_TYPE_USER,
	ES_OD_RECORD_TYPE_GROUP
} es_od_record_type_t;
// end od types

typedef enum {
	/// Signals that file is a string of a path since file could not be resolved on disk at time of event submission
	ES_GATEKEEPER_USER_OVERRIDE_FILE_TYPE_PATH,
	/// Signals that file is a es_file_t
	ES_GATEKEEPER_USER_OVERRIDE_FILE_TYPE_FILE
} es_gatekeeper_user_override_file_type_t;

/*
 * Information from a signed file. If the file is a multiarchitecture binary, only the
 * signing information for the native host architecture is reported. I.e. the CDHash
 * from the AArch64 slice if the host is AArch64.
 *
 * @field cdhash         Code Directory Hash
 * @field teamID         Team Identifier, if available in the signing information.
 * @field signingID      Signing Identifier, if available in the signing information.
 */
typedef struct {
	es_cdhash_t cdhash;
	es_string_token_t signing_id;
	es_string_token_t team_id;
} es_signed_file_info_t;

/**
 * @typedef ess_tcc_event_type_t
 *
 *  Represent the type of TCC modification event.
 *
 * - ES_TCC_EVENT_TYPE_UNKNOWN: Unknown prior state.
 * - ES_TCC_EVENT_TYPE_CREATE: A new TCC authorization record was created.
 * - ES_TCC_EVENT_TYPE_MODIFY: An existing TCC authorization record was modified.
 * - ES_TCC_EVENT_TYPE_DELETE: An existing TCC authorization record was deleted.
 */
typedef enum {
	ES_TCC_EVENT_TYPE_UNKNOWN,
	ES_TCC_EVENT_TYPE_CREATE,
	ES_TCC_EVENT_TYPE_MODIFY,
	ES_TCC_EVENT_TYPE_DELETE,
} es_tcc_event_type_t;

/**
 * ess_tcc_authorization_right_t
 *
 * Represents the type of authorization permission an application has to a TCC Service.
 */
typedef enum {
	ES_TCC_AUTHORIZATION_RIGHT_DENIED,           // 0
	ES_TCC_AUTHORIZATION_RIGHT_UNKNOWN,          // 1
	ES_TCC_AUTHORIZATION_RIGHT_ALLOWED,          // 2
	ES_TCC_AUTHORIZATION_RIGHT_LIMITED,          // 3
	ES_TCC_AUTHORIZATION_RIGHT_ADD_MODIFY_ADDED, // 4
	ES_TCC_AUTHORIZATION_RIGHT_SESSION_PID,      // 5
	ES_TCC_AUTHORIZATION_RIGHT_LEARN_MORE,       // 6
} es_tcc_authorization_right_t;

/**
 * ess_tcc_authorization_reason_t
 *
 * Represents the reason a TCC permission was updated.
 */
typedef enum {
	ES_TCC_AUTHORIZATION_REASON_NONE = 0,
	ES_TCC_AUTHORIZATION_REASON_ERROR,
	ES_TCC_AUTHORIZATION_REASON_USER_CONSENT, /// User answered a prompt
	ES_TCC_AUTHORIZATION_REASON_USER_SET,     /// User changed the authorization right via Preferences
	ES_TCC_AUTHORIZATION_REASON_SYSTEM_SET,   /// A system process changed the authorization right
	ES_TCC_AUTHORIZATION_REASON_SERVICE_POLICY,
	ES_TCC_AUTHORIZATION_REASON_MDM_POLICY,
	ES_TCC_AUTHORIZATION_REASON_SERVICE_OVERRIDE_POLICY,
	ES_TCC_AUTHORIZATION_REASON_MISSING_USAGE_STRING,
	ES_TCC_AUTHORIZATION_REASON_PROMPT_TIMEOUT,
	ES_TCC_AUTHORIZATION_REASON_PREFLIGHT_UNKNOWN,
	ES_TCC_AUTHORIZATION_REASON_ENTITLED,
	ES_TCC_AUTHORIZATION_REASON_APP_TYPE_POLICY,
	ES_TCC_AUTHORIZATION_REASON_PROMPT_CANCEL,
} es_tcc_authorization_reason_t;

/**
 * es_tcc_identity_type_t
 *
 * Represent the identity type of an application which has access to a TCC service.
 */
typedef enum {
	ES_TCC_IDENTITY_TYPE_BUNDLE_ID,
	ES_TCC_IDENTITY_TYPE_EXECUTABLE_PATH,
	ES_TCC_IDENTITY_TYPE_POLICY_ID,
	ES_TCC_IDENTITY_TYPE_FILE_PROVIDER_DOMAIN_ID,
} es_tcc_identity_type_t;

/**
 * es_cs_validation_category
 *
 * Indicates the code signature validation policy that was applied to a binary
 */
typedef enum {
	ES_CS_VALIDATION_CATEGORY_INVALID = 0,
	ES_CS_VALIDATION_CATEGORY_PLATFORM = 1,
	ES_CS_VALIDATION_CATEGORY_TESTFLIGHT = 2,
	ES_CS_VALIDATION_CATEGORY_DEVELOPMENT = 3,
	ES_CS_VALIDATION_CATEGORY_APP_STORE = 4,
	ES_CS_VALIDATION_CATEGORY_ENTERPRISE = 5,
	ES_CS_VALIDATION_CATEGORY_DEVELOPER_ID = 6,
	ES_CS_VALIDATION_CATEGORY_LOCAL_SIGNING = 7,
	ES_CS_VALIDATION_CATEGORY_ROSETTA = 8,
	ES_CS_VALIDATION_CATEGORY_OOPJIT = 9,
	ES_CS_VALIDATION_CATEGORY_NONE = 10,
} es_cs_validation_category_t;

/**
 * es_auto_unlock_type_t
 *
 * See es_event_authentication_auto_unlock_t
 */
typedef enum {
	/// Unlock the machine using Apple Watch.
	ES_AUTO_UNLOCK_MACHINE_UNLOCK = 1,
	/// Approve an authorization prompt using Apple Watch.
	ES_AUTO_UNLOCK_AUTH_PROMPT = 2
} es_auto_unlock_type_t;

/**
 * es_btm_item_type_t
 *
 * See es_btm_launch_item_t
 */
typedef enum {
	ES_BTM_ITEM_TYPE_USER_ITEM,
	ES_BTM_ITEM_TYPE_APP,
	ES_BTM_ITEM_TYPE_LOGIN_ITEM,
	ES_BTM_ITEM_TYPE_AGENT,
	ES_BTM_ITEM_TYPE_DAEMON
} es_btm_item_type_t;

/**
 * es_destination_type_t
 *
 * See es_event_create_t / es_event_rename_t
 */
typedef enum {
	ES_DESTINATION_TYPE_EXISTING_FILE,
	ES_DESTINATION_TYPE_NEW_PATH,
} es_destination_type_t;

/**
 * es_get_task_type_t
 *
 * See es_event_get_task_t
 */
typedef enum {
	// Task port obtained by calling e.g. task_for_pid(), where the caller
	// obtains a task port for a process identified by pid.
	ES_GET_TASK_TYPE_TASK_FOR_PID,
	// Task port obtained by calling e.g. processor_set_tasks(), where the
	// caller obtains a set of task ports.
	ES_GET_TASK_TYPE_EXPOSE_TASK,
	// Task port obtained by calling e.g. task_identity_token_get_task_port(),
	// where the caller obtains a task port for a process identified by an
	// identity token.  Task identity tokens generally have to be given up
	// by the target process voluntarily prior to the conversion into task
	// ports.
	ES_GET_TASK_TYPE_IDENTITY_TOKEN,
} es_get_task_type_t;

/**
 * es_openssh_login_result_type_t
 *
 * See es_event_openssh_login_t
 */
typedef enum {
	ES_OPENSSH_LOGIN_EXCEED_MAXTRIES = 0,
	ES_OPENSSH_LOGIN_ROOT_DENIED = 1,
	ES_OPENSSH_AUTH_SUCCESS = 2,
	ES_OPENSSH_AUTH_FAIL_NONE = 3,
	ES_OPENSSH_AUTH_FAIL_PASSWD = 4,
	ES_OPENSSH_AUTH_FAIL_KBDINT = 5,
	ES_OPENSSH_AUTH_FAIL_PUBKEY = 6,
	ES_OPENSSH_AUTH_FAIL_HOSTBASED = 7,
	ES_OPENSSH_AUTH_FAIL_GSSAPI = 8,
	ES_OPENSSH_INVALID_USER = 9,
} es_openssh_login_result_type_t;

/**
 * es_mount_disposition_t
 *
 * See es_event_mount_t
 */
typedef enum {
	ES_MOUNT_DISPOSITION_EXTERNAL, // device is external storage
	ES_MOUNT_DISPOSITION_INTERNAL, // device is internal storage
	ES_MOUNT_DISPOSITION_NETWORK,  // device is a network share
	ES_MOUNT_DISPOSITION_VIRTUAL,  // device is virtual (dmg or file)
	ES_MOUNT_DISPOSITION_NULLFS,   // mount uses nullfs, commonly for app translocation
	ES_MOUNT_DISPOSITION_UNKNOWN   // unable to determine disposition
} es_mount_disposition_t;

/**
 * @brief This enum describes the type of suspend/resume operations that are currently used.
 */
typedef enum {
	ES_PROC_SUSPEND_RESUME_TYPE_SUSPEND = 0,
	ES_PROC_SUSPEND_RESUME_TYPE_RESUME = 1,
	ES_PROC_SUSPEND_RESUME_TYPE_SHUTDOWN_SOCKETS = 3,
} es_proc_suspend_resume_type_t;

/**
 * es_profile_source_t
 *
 * See es_profile_t
 */
typedef enum {
	ES_PROFILE_SOURCE_MANAGED,
	ES_PROFILE_SOURCE_INSTALL,
} es_profile_source_t;

/**
 * es_touchid_mode_t
 *
 * See es_event_authentication_touchid_t
 */
typedef enum {
	ES_TOUCHID_MODE_VERIFICATION,
	ES_TOUCHID_MODE_IDENTIFICATION
} es_touchid_mode_t;

#endif /* __ENDPOINT_SECURITY_TYPES_H */
