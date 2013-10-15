/*
 * Copyright (c) 2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef SYS_MEMORYSTATUS_H
#define SYS_MEMORYSTATUS_H

#include <stdint.h>
#include <sys/time.h>
#include <sys/proc.h>
#include <sys/param.h>

#define JETSAM_PRIORITY_REVISION                  2

#define JETSAM_PRIORITY_IDLE                      0
#define JETSAM_PRIORITY_IDLE_DEFERRED             1
#define JETSAM_PRIORITY_BACKGROUND_OPPORTUNISTIC  2
#define JETSAM_PRIORITY_BACKGROUND                3
#define JETSAM_PRIORITY_MAIL                      4
#define JETSAM_PRIORITY_PHONE                     5
#define JETSAM_PRIORITY_UI_SUPPORT                8
#define JETSAM_PRIORITY_FOREGROUND_SUPPORT        9
#define JETSAM_PRIORITY_FOREGROUND               10
#define JETSAM_PRIORITY_AUDIO_AND_ACCESSORY      12
#define JETSAM_PRIORITY_CONDUCTOR                13
#define JETSAM_PRIORITY_HOME                     16
#define JETSAM_PRIORITY_EXECUTIVE                17
#define JETSAM_PRIORITY_IMPORTANT                18
#define JETSAM_PRIORITY_CRITICAL                 19

#define JETSAM_PRIORITY_MAX                      21

/* TODO - tune. This should probably be lower priority */
#define JETSAM_PRIORITY_DEFAULT                  18
#define JETSAM_PRIORITY_TELEPHONY                19

/* Compatibility */
#define DEFAULT_JETSAM_PRIORITY                  18

#define DEFERRED_IDLE_EXIT_TIME_SECS             10

#define KEV_MEMORYSTATUS_SUBCLASS                 3

enum {
	kMemorystatusLevelNote = 1,
	kMemorystatusSnapshotNote = 2,
	kMemorystatusFreezeNote = 3,
	kMemorystatusPressureNote = 4
};

enum {
	kMemorystatusLevelAny = -1,
	kMemorystatusLevelNormal = 0,
	kMemorystatusLevelWarning = 1,
	kMemorystatusLevelUrgent = 2,
	kMemorystatusLevelCritical = 3
};

typedef struct memorystatus_priority_entry {
	pid_t pid;
	int32_t priority;
	uint64_t user_data;
	int32_t limit;
	uint32_t state;
} memorystatus_priority_entry_t;

typedef struct memorystatus_kernel_stats {
	uint32_t free_pages;
	uint32_t active_pages;
	uint32_t inactive_pages;
	uint32_t throttled_pages;
	uint32_t purgeable_pages;
	uint32_t wired_pages;
	uint32_t speculative_pages;
	uint32_t filebacked_pages;
	uint32_t anonymous_pages;
	uint32_t compressor_pages;
	uint64_t compressions;
	uint64_t decompressions;
	uint64_t total_uncompressed_pages_in_compressor;
} memorystatus_kernel_stats_t;

/*
** This is a variable-length struct.
** Allocate a buffer of the size returned by the sysctl, cast to a memorystatus_snapshot_t *
*/

typedef struct jetsam_snapshot_entry {
	pid_t    pid;
	char     name[MAXCOMLEN+1];
	int32_t  priority;
	uint32_t pages;
	uint32_t max_pages;
	uint32_t state;
	uint32_t killed;
	uint64_t user_data;
	uint8_t  uuid[16];
	uint32_t fds;
} memorystatus_jetsam_snapshot_entry_t;

typedef struct jetsam_snapshot {
	uint64_t snapshot_time;
	uint64_t notification_time;
	memorystatus_kernel_stats_t stats;
	size_t entry_count;
	memorystatus_jetsam_snapshot_entry_t entries[];
} memorystatus_jetsam_snapshot_t;

typedef struct memorystatus_freeze_entry {
 	int32_t pid;
 	uint32_t flags;
 	uint32_t pages;
} memorystatus_freeze_entry_t;

/* TODO - deprecate; see <rdar://problem/12969599> */
#define kMaxSnapshotEntries 192

/* State */
#define kMemorystatusSuspended        0x01
#define kMemorystatusFrozen           0x02
#define kMemorystatusWasThawed        0x04
#define kMemorystatusTracked          0x08
#define kMemorystatusSupportsIdleExit 0x10
#define kMemorystatusDirty            0x20

/* Cause */
enum {
	kMemorystatusKilled = 1,
	kMemorystatusKilledHiwat,
 	kMemorystatusKilledVnodes,
  	kMemorystatusKilledVMPageShortage,
  	kMemorystatusKilledVMThrashing,
  	kMemorystatusKilledPerProcessLimit,
	kMemorystatusKilledDiagnostic,
	kMemorystatusKilledIdleExit
};

/* Temporary, to prevent the need for a linked submission of ReportCrash */
/* Remove when <rdar://problem/13210532> has been integrated */
enum {
	kMemorystatusKilledVM = kMemorystatusKilledVMPageShortage
};

/* Memorystatus control */
#define MEMORYSTATUS_BUFFERSIZE_MAX 65536


/* Commands */
#define MEMORYSTATUS_CMD_GET_PRIORITY_LIST            1
#define MEMORYSTATUS_CMD_SET_PRIORITY_PROPERTIES      2
#define MEMORYSTATUS_CMD_GET_JETSAM_SNAPSHOT          3
#define MEMORYSTATUS_CMD_GET_PRESSURE_STATUS          4
#define MEMORYSTATUS_CMD_SET_JETSAM_HIGH_WATER_MARK   5 /* TODO: deprecate */


typedef struct memorystatus_priority_properties {
	int32_t  priority;
	uint64_t user_data;
} memorystatus_priority_properties_t;


#endif /* SYS_MEMORYSTATUS_H */
