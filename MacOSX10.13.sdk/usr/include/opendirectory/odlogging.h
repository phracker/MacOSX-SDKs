/*
 * Copyright (c) 2017 Apple Inc. All rights reserved.
 */

#ifndef odlogging_h
#define odlogging_h

#include <os/log.h>

#define OD_LOG_UUID  "%{public,uuid_t}.16P"
#define OD_LOG_ODERROR "%{odtypes:ODError}d"
#define OD_LOG_ERRNO "%{darwin.errno}d"
#define OD_LOG_MACHERROR "%{odtypes:mach_error_t}d"
#define OD_LOG_CSSMSTATUS "%{odtypes:CSSMstatus}d"
#define OD_LOG_ODCBRESULT "%{odtypes:ODCallbackResult}d"

#if ODMODULE
#define _log_subsystem() "com.apple.opendirectoryd"
#else
#if __BUILDING_OPENDIRECTORYD__
extern int32_t od_installer_mode;
#define _log_subsystem() (od_installer_mode ? "com.apple.opendirectoryd-installer" : "com.apple.opendirectoryd")
#else
#define _log_subsystem() "com.apple.opendirectoryd"
#endif
#endif

OS_ALWAYS_INLINE
static inline os_log_t
_log_default(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create(_log_subsystem(), "default");
    });

    return log;
}

OS_ALWAYS_INLINE
static inline os_log_t
_log_auditing(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create(_log_subsystem(), "audit");
    });

    return log;
}

OS_ALWAYS_INLINE
static inline os_log_t
_log_auths(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create(_log_subsystem(), "auth");
    });

    return log;
}

OS_ALWAYS_INLINE
static inline os_log_t
_log_policy(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create(_log_subsystem(), "policy");
    });

    return log;
}

OS_ALWAYS_INLINE
static inline os_log_t
_log_session(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create(_log_subsystem(), "session");
    });

    return log;
}

OS_ALWAYS_INLINE
static inline os_log_t
_log_mappings(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create("com.apple.opendirectoryd", "mappings");
    });

    return log;
}

OS_ALWAYS_INLINE
static inline os_log_t
_log_pipeline(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create("com.apple.opendirectoryd", "pipeline");
    });

    return log;
}

OS_ALWAYS_INLINE
static inline os_log_t
_log_discovery(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create(_log_subsystem(), "discovery");
    });

    return log;
}

OS_ALWAYS_INLINE
static inline os_log_t
_log_object_lifetime(void)
{
    static os_log_t log;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        log = os_log_create("com.apple.opendirectoryd", "object-lifetime");
    });

    return log;
}

#endif /* odlogging_h */
