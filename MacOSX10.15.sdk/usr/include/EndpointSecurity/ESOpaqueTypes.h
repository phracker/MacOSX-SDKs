#ifndef __ENDPOINT_SECURITY_OPAQUE_TYPES_H
#define __ENDPOINT_SECURITY_OPAQUE_TYPES_H

#ifndef __ENDPOINT_SECURITY_INDIRECT__
#error "Please #include <EndpointSecurity/EndpointSecurity.h> instead of this file directly."
#endif

#include <stdint.h>
#include <Kernel/kern/cs_blobs.h>

typedef struct {
	uint8_t reserved[32];
} es_event_id_t;

#endif // __ENDPOINT_SECURITY_OPAQUE_TYPES_H
