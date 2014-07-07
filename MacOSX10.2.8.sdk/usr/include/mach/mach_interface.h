/*
 * Copyright (C) Apple Computer 1998
 * ALL Rights Reserved
 */
/*
 * This file represents the interfaces that used to come
 * from creating the user headers from the mach.defs file.
 * Because mach.defs was decomposed, this file now just
 * wraps up all the new interface headers generated from
 * each of the new .defs resulting from that decomposition.
 */
#ifndef	_MACH_INTERFACE_H_
#define _MACH_INTERFACE_H_

#include <mach/clock_priv.h>
#include <mach/host_priv.h>
#include <mach/host_security.h>
#include <mach/ledger.h>
#include <mach/lock_set.h>
#include <mach/processor.h>
#include <mach/processor_set.h>
#include <mach/semaphore.h>
#include <mach/task.h>
#include <mach/thread_act.h>
#include <mach/vm_map.h>

#endif /* _MACH_INTERFACE_H_ */
