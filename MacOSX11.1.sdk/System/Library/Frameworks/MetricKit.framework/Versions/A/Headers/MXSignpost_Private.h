//
//  MXSignpost_Private.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#ifndef MXSignpost_Private_h
#define MXSignpost_Private_h

#include <os/signpost.h>
#pragma mark - Implementation details. DO NOT CALL DIRECTLY

/*!
 * @header MXSignpost_Private.h
 *
 * This header contains implementation details that are not meant for clients
 * to call directly. The header must be public to allow clients to compile properly.
 *
 * Please refer to MXSignpost.h for the client-facing API surface.
 */

#if TARGET_OS_SIMULATOR

#define _MXSignpostEventEmit_guaranteed_args(log, event_id, name, format,...)
#define _MXSignpostIntervalBegin_guaranteed_args(log, event_id, name, format,...)
#define _MXSignpostIntervalEnd_guaranteed_args(log, event_id, name, format,...)

#else

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
void* _Nonnull _MXSignpostMetricsSnapshot(void);
#define _METRICS_SIGNPOST_TYPE_TOKEN "signpost:metrics"
#define _MXSIGNPOST_METRICS_SNAPSHOT_FORMAT "\n%{public, " _METRICS_SIGNPOST_TYPE_TOKEN "}@"

#define _MXSignpostEventEmit_guaranteed_args(log, event_id, name, format,...) os_signpost_event_emit(log, event_id, name, format _MXSIGNPOST_METRICS_SNAPSHOT_FORMAT, ##__VA_ARGS__, _MXSignpostMetricsSnapshot())
#define _MXSignpostIntervalBegin_guaranteed_args(log, event_id, name, format,...) os_signpost_interval_begin(log, event_id, name, format _MXSIGNPOST_METRICS_SNAPSHOT_FORMAT, ##__VA_ARGS__, _MXSignpostMetricsSnapshot())
#define _MXSignpostIntervalEnd_guaranteed_args(log, event_id, name, format,...) os_signpost_interval_end(log, event_id, name, format _MXSIGNPOST_METRICS_SNAPSHOT_FORMAT, ##__VA_ARGS__, _MXSignpostMetricsSnapshot())
#endif

#endif /* MXSignpost_Private_h */
