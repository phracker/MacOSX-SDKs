#ifndef __XCB_WM_H__
#define __XCB_WM_H__

#include <xcb/xcb.h>
#include "xcb_atom.h"
#include "xcb_property.h"


#ifdef __cplusplus
extern "C" {
#endif


void reparent_window(xcb_connection_t *c, xcb_window_t child,
		xcb_visualid_t v, xcb_window_t r, uint8_t d,
		int16_t x, int16_t y, uint16_t width, uint16_t height);

typedef struct {
	xcb_window_t child;
	xcb_window_t parent;
	int name_len;
	char *name;
	xcb_gcontext_t titlegc;
} client_window_t;

typedef struct {
	enum xcb_atom_fast_tag_t tag;
	union {
		xcb_get_window_attributes_cookie_t cookie;
		uint8_t override_redirect;
	} u;
} window_attributes_t;

void manage_window(xcb_property_handlers_t *prophs, xcb_connection_t *c, xcb_window_t window, window_attributes_t wa);
int handle_map_notify_event(void *prophs, xcb_connection_t *c, xcb_map_notify_event_t *e);
int handle_unmap_notify_event(void *data, xcb_connection_t *c, xcb_unmap_notify_event_t *e);
void manage_existing_windows(xcb_connection_t *c, xcb_property_handlers_t *prophs, xcb_window_t root);

typedef struct table_t table_t;

table_t *alloc_table();
void free_table(table_t *table);

int table_put(table_t *table, uint32_t key, void *value);
void *table_get(table_t *table, uint32_t key);
void *table_remove(table_t *table, uint32_t key);

extern table_t *byChild;
extern table_t *byParent;


#ifdef __cplusplus
}
#endif


#endif /* __XCB_WM_H__ */
