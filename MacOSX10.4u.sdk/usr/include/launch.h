/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#ifndef _LAUNCH_H_
#define _LAUNCH_H_

#include <stddef.h>
#include <stdbool.h>


#define LAUNCH_KEY_SUBMITJOB			"SubmitJob"
#define LAUNCH_KEY_REMOVEJOB			"RemoveJob"
#define LAUNCH_KEY_STARTJOB			"StartJob"
#define LAUNCH_KEY_STOPJOB			"StopJob"
#define LAUNCH_KEY_GETJOB			"GetJob"
#define LAUNCH_KEY_GETJOBWITHHANDLES		"GetJobWithHandles"
#define LAUNCH_KEY_GETJOBS			"GetJobs"
#define LAUNCH_KEY_CHECKIN			"CheckIn"

#define LAUNCH_JOBKEY_LABEL			"Label"
#define LAUNCH_JOBKEY_DISABLED			"Disabled"
#define LAUNCH_JOBKEY_USERNAME			"UserName"
#define LAUNCH_JOBKEY_GROUPNAME			"GroupName"
#define LAUNCH_JOBKEY_TIMEOUT			"TimeOut"
#define LAUNCH_JOBKEY_INITGROUPS		"InitGroups"
#define LAUNCH_JOBKEY_SOCKETS			"Sockets"
#define LAUNCH_JOBKEY_EVENTSOURCES		"EventSources"
#define LAUNCH_JOBKEY_INETDCOMPATIBILITY	"inetdCompatibility"
#define LAUNCH_JOBKEY_PROGRAMARGUMENTS		"ProgramArguments"
#define LAUNCH_JOBKEY_PROGRAM			"Program"
#define LAUNCH_JOBKEY_ONDEMAND			"OnDemand"
#define LAUNCH_JOBKEY_RUNATLOAD			"RunAtLoad"
#define LAUNCH_JOBKEY_ROOTDIRECTORY		"RootDirectory"
#define LAUNCH_JOBKEY_WORKINGDIRECTORY		"WorkingDirectory"
#define LAUNCH_JOBKEY_SERVICEDESCRIPTION	"ServiceDescription"
#define LAUNCH_JOBKEY_ENVIRONMENTVARIABLES	"EnvironmentVariables"
#define LAUNCH_JOBKEY_USERENVIRONMENTVARIABLES	"UserEnvironmentVariables"
#define LAUNCH_JOBKEY_PID			"PID"
#define LAUNCH_JOBKEY_UMASK			"Umask"
#define LAUNCH_JOBKEY_NICE			"Nice"
#define LAUNCH_JOBKEY_LOWPRIORITYIO		"LowPriorityIO"
#define LAUNCH_JOBKEY_SESSIONCREATE		"SessionCreate"
#define LAUNCH_JOBKEY_SOFTRESOURCELIMITS	"SoftResourceLimits"
#define LAUNCH_JOBKEY_HARDRESOURCELIMITS	"HardResourceLimits"
#define LAUNCH_JOBKEY_SERVICEIPC		"ServiceIPC"
#define LAUNCH_JOBKEY_STANDARDOUTPATH		"StandardOutPath"
#define LAUNCH_JOBKEY_STANDARDERRORPATH		"StandardErrorPath"
#define LAUNCH_JOBKEY_DEBUG			"Debug"
#define LAUNCH_JOBKEY_QUEUEDIRECTORIES		"QueueDirectories"
#define LAUNCH_JOBKEY_WATCHPATHS		"WatchPaths"
#define LAUNCH_JOBKEY_STARTINTERVAL		"StartInterval"
#define LAUNCH_JOBKEY_STARTCALENDARINTERVAL	"StartCalendarInterval"
#define LAUNCH_JOBKEY_BONJOURFDS		"BonjourFDs"

#define LAUNCH_JOBINETDCOMPATIBILITY_WAIT	"Wait"

#define LAUNCH_JOBKEY_CAL_MINUTE		"Minute"
#define LAUNCH_JOBKEY_CAL_HOUR			"Hour"
#define LAUNCH_JOBKEY_CAL_DAY			"Day"
#define LAUNCH_JOBKEY_CAL_WEEKDAY		"Weekday"
#define LAUNCH_JOBKEY_CAL_MONTH			"Month"

#define LAUNCH_JOBKEY_RESOURCELIMIT_CORE	"Core"
#define LAUNCH_JOBKEY_RESOURCELIMIT_CPU		"CPU"
#define LAUNCH_JOBKEY_RESOURCELIMIT_DATA	"Data"
#define LAUNCH_JOBKEY_RESOURCELIMIT_FSIZE	"FileSize"
#define LAUNCH_JOBKEY_RESOURCELIMIT_MEMLOCK	"MemoryLock"
#define LAUNCH_JOBKEY_RESOURCELIMIT_NOFILE	"NumberOfFiles"
#define LAUNCH_JOBKEY_RESOURCELIMIT_NPROC	"NumberOfProcesses"
#define LAUNCH_JOBKEY_RESOURCELIMIT_RSS		"ResidentSetSize"
#define LAUNCH_JOBKEY_RESOURCELIMIT_STACK	"Stack"

#define LAUNCH_JOBSOCKETKEY_TYPE		"SockType"
#define LAUNCH_JOBSOCKETKEY_PASSIVE		"SockPassive"
#define LAUNCH_JOBSOCKETKEY_BONJOUR		"Bonjour"
#define LAUNCH_JOBSOCKETKEY_SECUREWITHKEY	"SecureSocketWithKey"
#define LAUNCH_JOBSOCKETKEY_PATHNAME		"SockPathName"
#define LAUNCH_JOBSOCKETKEY_PATHMODE		"SockPathMode"
#define LAUNCH_JOBSOCKETKEY_NODENAME		"SockNodeName"
#define LAUNCH_JOBSOCKETKEY_SERVICENAME		"SockServiceName"
#define LAUNCH_JOBSOCKETKEY_FAMILY		"SockFamily"
#define LAUNCH_JOBSOCKETKEY_PROTOCOL		"SockProtocol"
#define LAUNCH_JOBSOCKETKEY_MULTICASTGROUP	"MulticastGroup"

typedef struct _launch_data *launch_data_t;

typedef enum {
	LAUNCH_DATA_DICTIONARY = 1,
	LAUNCH_DATA_ARRAY,
	LAUNCH_DATA_FD,
	LAUNCH_DATA_INTEGER,
	LAUNCH_DATA_REAL,
	LAUNCH_DATA_BOOL,
	LAUNCH_DATA_STRING,
	LAUNCH_DATA_OPAQUE,
	LAUNCH_DATA_ERRNO,
} launch_data_type_t;

launch_data_t		launch_data_alloc(launch_data_type_t);
launch_data_t		launch_data_copy(launch_data_t);
launch_data_type_t	launch_data_get_type(launch_data_t);
void			launch_data_free(launch_data_t);

/* Generic Dictionaries */
/* the value should not be changed while iterating */
bool		launch_data_dict_insert(launch_data_t, launch_data_t, const char *);
launch_data_t	launch_data_dict_lookup(launch_data_t, const char *);
bool		launch_data_dict_remove(launch_data_t, const char *);
void		launch_data_dict_iterate(launch_data_t, void (*)(launch_data_t, const char *, void *), void *);
size_t		launch_data_dict_get_count(launch_data_t);

/* Generic Arrays */
bool		launch_data_array_set_index(launch_data_t, launch_data_t, size_t);
launch_data_t	launch_data_array_get_index(launch_data_t, size_t);
size_t		launch_data_array_get_count(launch_data_t);

launch_data_t	launch_data_new_fd(int);
launch_data_t	launch_data_new_integer(long long);
launch_data_t	launch_data_new_bool(bool);
launch_data_t	launch_data_new_real(double);
launch_data_t	launch_data_new_string(const char *);
launch_data_t	launch_data_new_opaque(const void *, size_t);

bool		launch_data_set_fd(launch_data_t, int);
bool		launch_data_set_integer(launch_data_t, long long);
bool		launch_data_set_bool(launch_data_t, bool);
bool		launch_data_set_real(launch_data_t, double);
bool		launch_data_set_string(launch_data_t, const char *);
bool		launch_data_set_opaque(launch_data_t, const void *, size_t);

int		launch_data_get_fd(launch_data_t);
long long	launch_data_get_integer(launch_data_t);
bool		launch_data_get_bool(launch_data_t);
double		launch_data_get_real(launch_data_t);
const char *	launch_data_get_string(launch_data_t);
void *		launch_data_get_opaque(launch_data_t);
size_t		launch_data_get_opaque_size(launch_data_t);
int		launch_data_get_errno(launch_data_t);


/* launch_get_fd()
 *
 * Use this to get the FD if you're doing asynchronous I/O with select(),
 * poll() or kevent().
 */
int launch_get_fd(void);

/* launch_msg()
 *
 * Use this API to send and receive messages.
 * Calling launch_msg() with no message to send is a valid way to get
 * asynchronously received messages.
 *
 * If a message was to be sent, it returns NULL and errno on failure.
 *
 * If no messages were to be sent, it returns NULL and errno is set to zero if
 * no more asynchronous messages are available.
 */
launch_data_t launch_msg(launch_data_t);

#endif
