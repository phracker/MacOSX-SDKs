/*
 *  cache_callbacks.h
 *
 *  Copyright 2008 Apple. All rights reserved.
 *
 */

#include <stdbool.h>

#ifndef _CACHE_CALLBACKS_H_
#define _CACHE_CALLBACKS_H_

#ifndef PUBLIC_API
#ifdef __GNUC__
#define PUBLIC_API     __attribute__((__visibility__("default")))
#else
#define PUBLIC_API
#endif /* __GNUC__ */
#endif /* PUBLIC_API */

__BEGIN_DECLS

/*
 * Pre-defined callback functions.
 */

PUBLIC_API uintptr_t cache_key_hash_cb_cstring(void *key, void *unused);
PUBLIC_API uintptr_t cache_key_hash_cb_integer(void *key, void *unused);

PUBLIC_API bool cache_key_is_equal_cb_cstring(void *key1, void *key2, void *unused);
PUBLIC_API bool cache_key_is_equal_cb_integer(void *key1, void *key2, void *unused);

PUBLIC_API void cache_release_cb_free(void *key_or_value, void *unused);

PUBLIC_API void cache_value_make_purgeable_cb(void *value, void *unused);
PUBLIC_API bool cache_value_make_nonpurgeable_cb(void *value, void *unused);

/* Default hash function for byte strings.  */
uintptr_t cache_hash_byte_string(const char *data, size_t bytes);

__END_DECLS

#endif /* _CACHE_CALLBACKS_H_ */
