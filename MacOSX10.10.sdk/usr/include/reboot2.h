#ifndef __REBOOT2_H__
#define __REBOOT2_H__

#ifndef __XPC_INDIRECT__
#define __XPC_INDIRECT__
#endif // __XPC_INDIRECT__

#include <xpc/base.h>
#include <Availability.h>

__BEGIN_DECLS;

#include <sys/reboot.h>
#include <stdint.h>

#define RB2_FULLREBOOT 0x8000000000000000llu

__OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0)
XPC_EXPORT
void *
reboot2(uint64_t flags);

__END_DECLS;

#endif // __REBOOT2_H__