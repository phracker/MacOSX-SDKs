/*
 * This file generated automatically from xproto.xml by c_client.py.
 * Edit at your peril.
 */

/**
 * @defgroup XCB__API XCB  API
 * @brief  XCB Protocol Implementation.
 * @{
 **/

#ifndef __XPROTO_H
#define __XPROTO_H

#include "xcb.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief xcb_char2b_t
 **/
typedef struct xcb_char2b_t {
    uint8_t byte1; /**<  */
    uint8_t byte2; /**<  */
} xcb_char2b_t;

/**
 * @brief xcb_char2b_iterator_t
 **/
typedef struct xcb_char2b_iterator_t {
    xcb_char2b_t *data; /**<  */
    int           rem; /**<  */
    int           index; /**<  */
} xcb_char2b_iterator_t;

typedef uint32_t xcb_window_t;

/**
 * @brief xcb_window_iterator_t
 **/
typedef struct xcb_window_iterator_t {
    xcb_window_t *data; /**<  */
    int           rem; /**<  */
    int           index; /**<  */
} xcb_window_iterator_t;

typedef uint32_t xcb_pixmap_t;

/**
 * @brief xcb_pixmap_iterator_t
 **/
typedef struct xcb_pixmap_iterator_t {
    xcb_pixmap_t *data; /**<  */
    int           rem; /**<  */
    int           index; /**<  */
} xcb_pixmap_iterator_t;

typedef uint32_t xcb_cursor_t;

/**
 * @brief xcb_cursor_iterator_t
 **/
typedef struct xcb_cursor_iterator_t {
    xcb_cursor_t *data; /**<  */
    int           rem; /**<  */
    int           index; /**<  */
} xcb_cursor_iterator_t;

typedef uint32_t xcb_font_t;

/**
 * @brief xcb_font_iterator_t
 **/
typedef struct xcb_font_iterator_t {
    xcb_font_t *data; /**<  */
    int         rem; /**<  */
    int         index; /**<  */
} xcb_font_iterator_t;

typedef uint32_t xcb_gcontext_t;

/**
 * @brief xcb_gcontext_iterator_t
 **/
typedef struct xcb_gcontext_iterator_t {
    xcb_gcontext_t *data; /**<  */
    int             rem; /**<  */
    int             index; /**<  */
} xcb_gcontext_iterator_t;

typedef uint32_t xcb_colormap_t;

/**
 * @brief xcb_colormap_iterator_t
 **/
typedef struct xcb_colormap_iterator_t {
    xcb_colormap_t *data; /**<  */
    int             rem; /**<  */
    int             index; /**<  */
} xcb_colormap_iterator_t;

typedef uint32_t xcb_atom_t;

/**
 * @brief xcb_atom_iterator_t
 **/
typedef struct xcb_atom_iterator_t {
    xcb_atom_t *data; /**<  */
    int         rem; /**<  */
    int         index; /**<  */
} xcb_atom_iterator_t;

typedef uint32_t xcb_drawable_t;

/**
 * @brief xcb_drawable_iterator_t
 **/
typedef struct xcb_drawable_iterator_t {
    xcb_drawable_t *data; /**<  */
    int             rem; /**<  */
    int             index; /**<  */
} xcb_drawable_iterator_t;

typedef uint32_t xcb_fontable_t;

/**
 * @brief xcb_fontable_iterator_t
 **/
typedef struct xcb_fontable_iterator_t {
    xcb_fontable_t *data; /**<  */
    int             rem; /**<  */
    int             index; /**<  */
} xcb_fontable_iterator_t;

typedef uint32_t xcb_visualid_t;

/**
 * @brief xcb_visualid_iterator_t
 **/
typedef struct xcb_visualid_iterator_t {
    xcb_visualid_t *data; /**<  */
    int             rem; /**<  */
    int             index; /**<  */
} xcb_visualid_iterator_t;

typedef uint32_t xcb_timestamp_t;

/**
 * @brief xcb_timestamp_iterator_t
 **/
typedef struct xcb_timestamp_iterator_t {
    xcb_timestamp_t *data; /**<  */
    int              rem; /**<  */
    int              index; /**<  */
} xcb_timestamp_iterator_t;

typedef uint32_t xcb_keysym_t;

/**
 * @brief xcb_keysym_iterator_t
 **/
typedef struct xcb_keysym_iterator_t {
    xcb_keysym_t *data; /**<  */
    int           rem; /**<  */
    int           index; /**<  */
} xcb_keysym_iterator_t;

typedef uint8_t xcb_keycode_t;

/**
 * @brief xcb_keycode_iterator_t
 **/
typedef struct xcb_keycode_iterator_t {
    xcb_keycode_t *data; /**<  */
    int            rem; /**<  */
    int            index; /**<  */
} xcb_keycode_iterator_t;

typedef uint8_t xcb_button_t;

/**
 * @brief xcb_button_iterator_t
 **/
typedef struct xcb_button_iterator_t {
    xcb_button_t *data; /**<  */
    int           rem; /**<  */
    int           index; /**<  */
} xcb_button_iterator_t;

/**
 * @brief xcb_point_t
 **/
typedef struct xcb_point_t {
    int16_t x; /**<  */
    int16_t y; /**<  */
} xcb_point_t;

/**
 * @brief xcb_point_iterator_t
 **/
typedef struct xcb_point_iterator_t {
    xcb_point_t *data; /**<  */
    int          rem; /**<  */
    int          index; /**<  */
} xcb_point_iterator_t;

/**
 * @brief xcb_rectangle_t
 **/
typedef struct xcb_rectangle_t {
    int16_t  x; /**<  */
    int16_t  y; /**<  */
    uint16_t width; /**<  */
    uint16_t height; /**<  */
} xcb_rectangle_t;

/**
 * @brief xcb_rectangle_iterator_t
 **/
typedef struct xcb_rectangle_iterator_t {
    xcb_rectangle_t *data; /**<  */
    int              rem; /**<  */
    int              index; /**<  */
} xcb_rectangle_iterator_t;

/**
 * @brief xcb_arc_t
 **/
typedef struct xcb_arc_t {
    int16_t  x; /**<  */
    int16_t  y; /**<  */
    uint16_t width; /**<  */
    uint16_t height; /**<  */
    int16_t  angle1; /**<  */
    int16_t  angle2; /**<  */
} xcb_arc_t;

/**
 * @brief xcb_arc_iterator_t
 **/
typedef struct xcb_arc_iterator_t {
    xcb_arc_t *data; /**<  */
    int        rem; /**<  */
    int        index; /**<  */
} xcb_arc_iterator_t;

/**
 * @brief xcb_format_t
 **/
typedef struct xcb_format_t {
    uint8_t depth; /**<  */
    uint8_t bits_per_pixel; /**<  */
    uint8_t scanline_pad; /**<  */
    uint8_t pad0[5]; /**<  */
} xcb_format_t;

/**
 * @brief xcb_format_iterator_t
 **/
typedef struct xcb_format_iterator_t {
    xcb_format_t *data; /**<  */
    int           rem; /**<  */
    int           index; /**<  */
} xcb_format_iterator_t;

typedef enum xcb_visual_class_t {
    XCB_VISUAL_CLASS_STATIC_GRAY = 0,
    XCB_VISUAL_CLASS_GRAY_SCALE = 1,
    XCB_VISUAL_CLASS_STATIC_COLOR = 2,
    XCB_VISUAL_CLASS_PSEUDO_COLOR = 3,
    XCB_VISUAL_CLASS_TRUE_COLOR = 4,
    XCB_VISUAL_CLASS_DIRECT_COLOR = 5
} xcb_visual_class_t;

/**
 * @brief xcb_visualtype_t
 **/
typedef struct xcb_visualtype_t {
    xcb_visualid_t visual_id; /**<  */
    uint8_t        _class; /**<  */
    uint8_t        bits_per_rgb_value; /**<  */
    uint16_t       colormap_entries; /**<  */
    uint32_t       red_mask; /**<  */
    uint32_t       green_mask; /**<  */
    uint32_t       blue_mask; /**<  */
    uint8_t        pad0[4]; /**<  */
} xcb_visualtype_t;

/**
 * @brief xcb_visualtype_iterator_t
 **/
typedef struct xcb_visualtype_iterator_t {
    xcb_visualtype_t *data; /**<  */
    int               rem; /**<  */
    int               index; /**<  */
} xcb_visualtype_iterator_t;

/**
 * @brief xcb_depth_t
 **/
typedef struct xcb_depth_t {
    uint8_t  depth; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t visuals_len; /**<  */
    uint8_t  pad1[4]; /**<  */
} xcb_depth_t;

/**
 * @brief xcb_depth_iterator_t
 **/
typedef struct xcb_depth_iterator_t {
    xcb_depth_t *data; /**<  */
    int          rem; /**<  */
    int          index; /**<  */
} xcb_depth_iterator_t;

typedef enum xcb_event_mask_t {
    XCB_EVENT_MASK_NO_EVENT = 0,
    XCB_EVENT_MASK_KEY_PRESS = 1,
    XCB_EVENT_MASK_KEY_RELEASE = 2,
    XCB_EVENT_MASK_BUTTON_PRESS = 4,
    XCB_EVENT_MASK_BUTTON_RELEASE = 8,
    XCB_EVENT_MASK_ENTER_WINDOW = 16,
    XCB_EVENT_MASK_LEAVE_WINDOW = 32,
    XCB_EVENT_MASK_POINTER_MOTION = 64,
    XCB_EVENT_MASK_POINTER_MOTION_HINT = 128,
    XCB_EVENT_MASK_BUTTON_1_MOTION = 256,
    XCB_EVENT_MASK_BUTTON_2_MOTION = 512,
    XCB_EVENT_MASK_BUTTON_3_MOTION = 1024,
    XCB_EVENT_MASK_BUTTON_4_MOTION = 2048,
    XCB_EVENT_MASK_BUTTON_5_MOTION = 4096,
    XCB_EVENT_MASK_BUTTON_MOTION = 8192,
    XCB_EVENT_MASK_KEYMAP_STATE = 16384,
    XCB_EVENT_MASK_EXPOSURE = 32768,
    XCB_EVENT_MASK_VISIBILITY_CHANGE = 65536,
    XCB_EVENT_MASK_STRUCTURE_NOTIFY = 131072,
    XCB_EVENT_MASK_RESIZE_REDIRECT = 262144,
    XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY = 524288,
    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT = 1048576,
    XCB_EVENT_MASK_FOCUS_CHANGE = 2097152,
    XCB_EVENT_MASK_PROPERTY_CHANGE = 4194304,
    XCB_EVENT_MASK_COLOR_MAP_CHANGE = 8388608,
    XCB_EVENT_MASK_OWNER_GRAB_BUTTON = 16777216
} xcb_event_mask_t;

typedef enum xcb_backing_store_t {
    XCB_BACKING_STORE_NOT_USEFUL = 0,
    XCB_BACKING_STORE_WHEN_MAPPED = 1,
    XCB_BACKING_STORE_ALWAYS = 2
} xcb_backing_store_t;

/**
 * @brief xcb_screen_t
 **/
typedef struct xcb_screen_t {
    xcb_window_t   root; /**<  */
    xcb_colormap_t default_colormap; /**<  */
    uint32_t       white_pixel; /**<  */
    uint32_t       black_pixel; /**<  */
    uint32_t       current_input_masks; /**<  */
    uint16_t       width_in_pixels; /**<  */
    uint16_t       height_in_pixels; /**<  */
    uint16_t       width_in_millimeters; /**<  */
    uint16_t       height_in_millimeters; /**<  */
    uint16_t       min_installed_maps; /**<  */
    uint16_t       max_installed_maps; /**<  */
    xcb_visualid_t root_visual; /**<  */
    uint8_t        backing_stores; /**<  */
    uint8_t        save_unders; /**<  */
    uint8_t        root_depth; /**<  */
    uint8_t        allowed_depths_len; /**<  */
} xcb_screen_t;

/**
 * @brief xcb_screen_iterator_t
 **/
typedef struct xcb_screen_iterator_t {
    xcb_screen_t *data; /**<  */
    int           rem; /**<  */
    int           index; /**<  */
} xcb_screen_iterator_t;

/**
 * @brief xcb_setup_request_t
 **/
typedef struct xcb_setup_request_t {
    uint8_t  byte_order; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t protocol_major_version; /**<  */
    uint16_t protocol_minor_version; /**<  */
    uint16_t authorization_protocol_name_len; /**<  */
    uint16_t authorization_protocol_data_len; /**<  */
    uint8_t  pad1[2]; /**<  */
} xcb_setup_request_t;

/**
 * @brief xcb_setup_request_iterator_t
 **/
typedef struct xcb_setup_request_iterator_t {
    xcb_setup_request_t *data; /**<  */
    int                  rem; /**<  */
    int                  index; /**<  */
} xcb_setup_request_iterator_t;

/**
 * @brief xcb_setup_failed_t
 **/
typedef struct xcb_setup_failed_t {
    uint8_t  status; /**<  */
    uint8_t  reason_len; /**<  */
    uint16_t protocol_major_version; /**<  */
    uint16_t protocol_minor_version; /**<  */
    uint16_t length; /**<  */
} xcb_setup_failed_t;

/**
 * @brief xcb_setup_failed_iterator_t
 **/
typedef struct xcb_setup_failed_iterator_t {
    xcb_setup_failed_t *data; /**<  */
    int                 rem; /**<  */
    int                 index; /**<  */
} xcb_setup_failed_iterator_t;

/**
 * @brief xcb_setup_authenticate_t
 **/
typedef struct xcb_setup_authenticate_t {
    uint8_t  status; /**<  */
    uint8_t  pad0[5]; /**<  */
    uint16_t length; /**<  */
} xcb_setup_authenticate_t;

/**
 * @brief xcb_setup_authenticate_iterator_t
 **/
typedef struct xcb_setup_authenticate_iterator_t {
    xcb_setup_authenticate_t *data; /**<  */
    int                       rem; /**<  */
    int                       index; /**<  */
} xcb_setup_authenticate_iterator_t;

typedef enum xcb_image_order_t {
    XCB_IMAGE_ORDER_LSB_FIRST = 0,
    XCB_IMAGE_ORDER_MSB_FIRST = 1
} xcb_image_order_t;

/**
 * @brief xcb_setup_t
 **/
typedef struct xcb_setup_t {
    uint8_t       status; /**<  */
    uint8_t       pad0; /**<  */
    uint16_t      protocol_major_version; /**<  */
    uint16_t      protocol_minor_version; /**<  */
    uint16_t      length; /**<  */
    uint32_t      release_number; /**<  */
    uint32_t      resource_id_base; /**<  */
    uint32_t      resource_id_mask; /**<  */
    uint32_t      motion_buffer_size; /**<  */
    uint16_t      vendor_len; /**<  */
    uint16_t      maximum_request_length; /**<  */
    uint8_t       roots_len; /**<  */
    uint8_t       pixmap_formats_len; /**<  */
    uint8_t       image_byte_order; /**<  */
    uint8_t       bitmap_format_bit_order; /**<  */
    uint8_t       bitmap_format_scanline_unit; /**<  */
    uint8_t       bitmap_format_scanline_pad; /**<  */
    xcb_keycode_t min_keycode; /**<  */
    xcb_keycode_t max_keycode; /**<  */
    uint8_t       pad1[4]; /**<  */
} xcb_setup_t;

/**
 * @brief xcb_setup_iterator_t
 **/
typedef struct xcb_setup_iterator_t {
    xcb_setup_t *data; /**<  */
    int          rem; /**<  */
    int          index; /**<  */
} xcb_setup_iterator_t;

typedef enum xcb_mod_mask_t {
    XCB_MOD_MASK_SHIFT = 1,
    XCB_MOD_MASK_LOCK = 2,
    XCB_MOD_MASK_CONTROL = 4,
    XCB_MOD_MASK_1 = 8,
    XCB_MOD_MASK_2 = 16,
    XCB_MOD_MASK_3 = 32,
    XCB_MOD_MASK_4 = 64,
    XCB_MOD_MASK_5 = 128,
    XCB_MOD_MASK_ANY = 32768
} xcb_mod_mask_t;

typedef enum xcb_key_but_mask_t {
    XCB_KEY_BUT_MASK_SHIFT = 1,
    XCB_KEY_BUT_MASK_LOCK = 2,
    XCB_KEY_BUT_MASK_CONTROL = 4,
    XCB_KEY_BUT_MASK_MOD_1 = 8,
    XCB_KEY_BUT_MASK_MOD_2 = 16,
    XCB_KEY_BUT_MASK_MOD_3 = 32,
    XCB_KEY_BUT_MASK_MOD_4 = 64,
    XCB_KEY_BUT_MASK_MOD_5 = 128,
    XCB_KEY_BUT_MASK_BUTTON_1 = 256,
    XCB_KEY_BUT_MASK_BUTTON_2 = 512,
    XCB_KEY_BUT_MASK_BUTTON_3 = 1024,
    XCB_KEY_BUT_MASK_BUTTON_4 = 2048,
    XCB_KEY_BUT_MASK_BUTTON_5 = 4096
} xcb_key_but_mask_t;

typedef enum xcb_window_enum_t {
    XCB_WINDOW_NONE = 0
} xcb_window_enum_t;

/** Opcode for xcb_key_press. */
#define XCB_KEY_PRESS 2

/**
 * @brief xcb_key_press_event_t
 **/
typedef struct xcb_key_press_event_t {
    uint8_t         response_type; /**<  */
    xcb_keycode_t   detail; /**<  */
    uint16_t        sequence; /**<  */
    xcb_timestamp_t time; /**<  */
    xcb_window_t    root; /**<  */
    xcb_window_t    event; /**<  */
    xcb_window_t    child; /**<  */
    int16_t         root_x; /**<  */
    int16_t         root_y; /**<  */
    int16_t         event_x; /**<  */
    int16_t         event_y; /**<  */
    uint16_t        state; /**<  */
    uint8_t         same_screen; /**<  */
    uint8_t         pad0; /**<  */
} xcb_key_press_event_t;

/** Opcode for xcb_key_release. */
#define XCB_KEY_RELEASE 3

typedef xcb_key_press_event_t xcb_key_release_event_t;

typedef enum xcb_button_mask_t {
    XCB_BUTTON_MASK_1 = 256,
    XCB_BUTTON_MASK_2 = 512,
    XCB_BUTTON_MASK_3 = 1024,
    XCB_BUTTON_MASK_4 = 2048,
    XCB_BUTTON_MASK_5 = 4096,
    XCB_BUTTON_MASK_ANY = 32768
} xcb_button_mask_t;

/** Opcode for xcb_button_press. */
#define XCB_BUTTON_PRESS 4

/**
 * @brief xcb_button_press_event_t
 **/
typedef struct xcb_button_press_event_t {
    uint8_t         response_type; /**<  */
    xcb_button_t    detail; /**<  */
    uint16_t        sequence; /**<  */
    xcb_timestamp_t time; /**<  */
    xcb_window_t    root; /**<  */
    xcb_window_t    event; /**<  */
    xcb_window_t    child; /**<  */
    int16_t         root_x; /**<  */
    int16_t         root_y; /**<  */
    int16_t         event_x; /**<  */
    int16_t         event_y; /**<  */
    uint16_t        state; /**<  */
    uint8_t         same_screen; /**<  */
    uint8_t         pad0; /**<  */
} xcb_button_press_event_t;

/** Opcode for xcb_button_release. */
#define XCB_BUTTON_RELEASE 5

typedef xcb_button_press_event_t xcb_button_release_event_t;

typedef enum xcb_motion_t {
    XCB_MOTION_NORMAL = 0,
    XCB_MOTION_HINT = 1
} xcb_motion_t;

/** Opcode for xcb_motion_notify. */
#define XCB_MOTION_NOTIFY 6

/**
 * @brief xcb_motion_notify_event_t
 **/
typedef struct xcb_motion_notify_event_t {
    uint8_t         response_type; /**<  */
    uint8_t         detail; /**<  */
    uint16_t        sequence; /**<  */
    xcb_timestamp_t time; /**<  */
    xcb_window_t    root; /**<  */
    xcb_window_t    event; /**<  */
    xcb_window_t    child; /**<  */
    int16_t         root_x; /**<  */
    int16_t         root_y; /**<  */
    int16_t         event_x; /**<  */
    int16_t         event_y; /**<  */
    uint16_t        state; /**<  */
    uint8_t         same_screen; /**<  */
    uint8_t         pad0; /**<  */
} xcb_motion_notify_event_t;

typedef enum xcb_notify_detail_t {
    XCB_NOTIFY_DETAIL_ANCESTOR = 0,
    XCB_NOTIFY_DETAIL_VIRTUAL = 1,
    XCB_NOTIFY_DETAIL_INFERIOR = 2,
    XCB_NOTIFY_DETAIL_NONLINEAR = 3,
    XCB_NOTIFY_DETAIL_NONLINEAR_VIRTUAL = 4,
    XCB_NOTIFY_DETAIL_POINTER = 5,
    XCB_NOTIFY_DETAIL_POINTER_ROOT = 6,
    XCB_NOTIFY_DETAIL_NONE = 7
} xcb_notify_detail_t;

typedef enum xcb_notify_mode_t {
    XCB_NOTIFY_MODE_NORMAL = 0,
    XCB_NOTIFY_MODE_GRAB = 1,
    XCB_NOTIFY_MODE_UNGRAB = 2,
    XCB_NOTIFY_MODE_WHILE_GRABBED = 3
} xcb_notify_mode_t;

/** Opcode for xcb_enter_notify. */
#define XCB_ENTER_NOTIFY 7

/**
 * @brief xcb_enter_notify_event_t
 **/
typedef struct xcb_enter_notify_event_t {
    uint8_t         response_type; /**<  */
    uint8_t         detail; /**<  */
    uint16_t        sequence; /**<  */
    xcb_timestamp_t time; /**<  */
    xcb_window_t    root; /**<  */
    xcb_window_t    event; /**<  */
    xcb_window_t    child; /**<  */
    int16_t         root_x; /**<  */
    int16_t         root_y; /**<  */
    int16_t         event_x; /**<  */
    int16_t         event_y; /**<  */
    uint16_t        state; /**<  */
    uint8_t         mode; /**<  */
    uint8_t         same_screen_focus; /**<  */
} xcb_enter_notify_event_t;

/** Opcode for xcb_leave_notify. */
#define XCB_LEAVE_NOTIFY 8

typedef xcb_enter_notify_event_t xcb_leave_notify_event_t;

/** Opcode for xcb_focus_in. */
#define XCB_FOCUS_IN 9

/**
 * @brief xcb_focus_in_event_t
 **/
typedef struct xcb_focus_in_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      detail; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t event; /**<  */
    uint8_t      mode; /**<  */
    uint8_t      pad0[3]; /**<  */
} xcb_focus_in_event_t;

/** Opcode for xcb_focus_out. */
#define XCB_FOCUS_OUT 10

typedef xcb_focus_in_event_t xcb_focus_out_event_t;

/** Opcode for xcb_keymap_notify. */
#define XCB_KEYMAP_NOTIFY 11

/**
 * @brief xcb_keymap_notify_event_t
 **/
typedef struct xcb_keymap_notify_event_t {
    uint8_t response_type; /**<  */
    uint8_t keys[31]; /**<  */
} xcb_keymap_notify_event_t;

/** Opcode for xcb_expose. */
#define XCB_EXPOSE 12

/**
 * @brief xcb_expose_event_t
 **/
typedef struct xcb_expose_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t window; /**<  */
    uint16_t     x; /**<  */
    uint16_t     y; /**<  */
    uint16_t     width; /**<  */
    uint16_t     height; /**<  */
    uint16_t     count; /**<  */
    uint8_t      pad1[2]; /**<  */
} xcb_expose_event_t;

/** Opcode for xcb_graphics_exposure. */
#define XCB_GRAPHICS_EXPOSURE 13

/**
 * @brief xcb_graphics_exposure_event_t
 **/
typedef struct xcb_graphics_exposure_event_t {
    uint8_t        response_type; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       sequence; /**<  */
    xcb_drawable_t drawable; /**<  */
    uint16_t       x; /**<  */
    uint16_t       y; /**<  */
    uint16_t       width; /**<  */
    uint16_t       height; /**<  */
    uint16_t       minor_opcode; /**<  */
    uint16_t       count; /**<  */
    uint8_t        major_opcode; /**<  */
    uint8_t        pad1[3]; /**<  */
} xcb_graphics_exposure_event_t;

/** Opcode for xcb_no_exposure. */
#define XCB_NO_EXPOSURE 14

/**
 * @brief xcb_no_exposure_event_t
 **/
typedef struct xcb_no_exposure_event_t {
    uint8_t        response_type; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       sequence; /**<  */
    xcb_drawable_t drawable; /**<  */
    uint16_t       minor_opcode; /**<  */
    uint8_t        major_opcode; /**<  */
    uint8_t        pad1; /**<  */
} xcb_no_exposure_event_t;

typedef enum xcb_visibility_t {
    XCB_VISIBILITY_UNOBSCURED = 0,
    XCB_VISIBILITY_PARTIALLY_OBSCURED = 1,
    XCB_VISIBILITY_FULLY_OBSCURED = 2
} xcb_visibility_t;

/** Opcode for xcb_visibility_notify. */
#define XCB_VISIBILITY_NOTIFY 15

/**
 * @brief xcb_visibility_notify_event_t
 **/
typedef struct xcb_visibility_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t window; /**<  */
    uint8_t      state; /**<  */
    uint8_t      pad1[3]; /**<  */
} xcb_visibility_notify_event_t;

/** Opcode for xcb_create_notify. */
#define XCB_CREATE_NOTIFY 16

/**
 * @brief xcb_create_notify_event_t
 **/
typedef struct xcb_create_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t parent; /**<  */
    xcb_window_t window; /**<  */
    int16_t      x; /**<  */
    int16_t      y; /**<  */
    uint16_t     width; /**<  */
    uint16_t     height; /**<  */
    uint16_t     border_width; /**<  */
    uint8_t      override_redirect; /**<  */
    uint8_t      pad1; /**<  */
} xcb_create_notify_event_t;

/** Opcode for xcb_destroy_notify. */
#define XCB_DESTROY_NOTIFY 17

/**
 * @brief xcb_destroy_notify_event_t
 **/
typedef struct xcb_destroy_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t event; /**<  */
    xcb_window_t window; /**<  */
} xcb_destroy_notify_event_t;

/** Opcode for xcb_unmap_notify. */
#define XCB_UNMAP_NOTIFY 18

/**
 * @brief xcb_unmap_notify_event_t
 **/
typedef struct xcb_unmap_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t event; /**<  */
    xcb_window_t window; /**<  */
    uint8_t      from_configure; /**<  */
    uint8_t      pad1[3]; /**<  */
} xcb_unmap_notify_event_t;

/** Opcode for xcb_map_notify. */
#define XCB_MAP_NOTIFY 19

/**
 * @brief xcb_map_notify_event_t
 **/
typedef struct xcb_map_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t event; /**<  */
    xcb_window_t window; /**<  */
    uint8_t      override_redirect; /**<  */
    uint8_t      pad1[3]; /**<  */
} xcb_map_notify_event_t;

/** Opcode for xcb_map_request. */
#define XCB_MAP_REQUEST 20

/**
 * @brief xcb_map_request_event_t
 **/
typedef struct xcb_map_request_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t parent; /**<  */
    xcb_window_t window; /**<  */
} xcb_map_request_event_t;

/** Opcode for xcb_reparent_notify. */
#define XCB_REPARENT_NOTIFY 21

/**
 * @brief xcb_reparent_notify_event_t
 **/
typedef struct xcb_reparent_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t event; /**<  */
    xcb_window_t window; /**<  */
    xcb_window_t parent; /**<  */
    int16_t      x; /**<  */
    int16_t      y; /**<  */
    uint8_t      override_redirect; /**<  */
    uint8_t      pad1[3]; /**<  */
} xcb_reparent_notify_event_t;

/** Opcode for xcb_configure_notify. */
#define XCB_CONFIGURE_NOTIFY 22

/**
 * @brief xcb_configure_notify_event_t
 **/
typedef struct xcb_configure_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t event; /**<  */
    xcb_window_t window; /**<  */
    xcb_window_t above_sibling; /**<  */
    int16_t      x; /**<  */
    int16_t      y; /**<  */
    uint16_t     width; /**<  */
    uint16_t     height; /**<  */
    uint16_t     border_width; /**<  */
    uint8_t      override_redirect; /**<  */
    uint8_t      pad1; /**<  */
} xcb_configure_notify_event_t;

/** Opcode for xcb_configure_request. */
#define XCB_CONFIGURE_REQUEST 23

/**
 * @brief xcb_configure_request_event_t
 **/
typedef struct xcb_configure_request_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      stack_mode; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t parent; /**<  */
    xcb_window_t window; /**<  */
    xcb_window_t sibling; /**<  */
    int16_t      x; /**<  */
    int16_t      y; /**<  */
    uint16_t     width; /**<  */
    uint16_t     height; /**<  */
    uint16_t     border_width; /**<  */
    uint16_t     value_mask; /**<  */
} xcb_configure_request_event_t;

/** Opcode for xcb_gravity_notify. */
#define XCB_GRAVITY_NOTIFY 24

/**
 * @brief xcb_gravity_notify_event_t
 **/
typedef struct xcb_gravity_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t event; /**<  */
    xcb_window_t window; /**<  */
    int16_t      x; /**<  */
    int16_t      y; /**<  */
} xcb_gravity_notify_event_t;

/** Opcode for xcb_resize_request. */
#define XCB_RESIZE_REQUEST 25

/**
 * @brief xcb_resize_request_event_t
 **/
typedef struct xcb_resize_request_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t window; /**<  */
    uint16_t     width; /**<  */
    uint16_t     height; /**<  */
} xcb_resize_request_event_t;

typedef enum xcb_place_t {
    XCB_PLACE_ON_TOP = 0,
    XCB_PLACE_ON_BOTTOM = 1
} xcb_place_t;

/** Opcode for xcb_circulate_notify. */
#define XCB_CIRCULATE_NOTIFY 26

/**
 * @brief xcb_circulate_notify_event_t
 **/
typedef struct xcb_circulate_notify_event_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    xcb_window_t event; /**<  */
    xcb_window_t window; /**<  */
    uint8_t      pad1[4]; /**<  */
    uint8_t      place; /**<  */
    uint8_t      pad2[3]; /**<  */
} xcb_circulate_notify_event_t;

/** Opcode for xcb_circulate_request. */
#define XCB_CIRCULATE_REQUEST 27

typedef xcb_circulate_notify_event_t xcb_circulate_request_event_t;

typedef enum xcb_property_t {
    XCB_PROPERTY_NEW_VALUE = 0,
    XCB_PROPERTY_DELETE = 1
} xcb_property_t;

/** Opcode for xcb_property_notify. */
#define XCB_PROPERTY_NOTIFY 28

/**
 * @brief xcb_property_notify_event_t
 **/
typedef struct xcb_property_notify_event_t {
    uint8_t         response_type; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        sequence; /**<  */
    xcb_window_t    window; /**<  */
    xcb_atom_t      atom; /**<  */
    xcb_timestamp_t time; /**<  */
    uint8_t         state; /**<  */
    uint8_t         pad1[3]; /**<  */
} xcb_property_notify_event_t;

/** Opcode for xcb_selection_clear. */
#define XCB_SELECTION_CLEAR 29

/**
 * @brief xcb_selection_clear_event_t
 **/
typedef struct xcb_selection_clear_event_t {
    uint8_t         response_type; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        sequence; /**<  */
    xcb_timestamp_t time; /**<  */
    xcb_window_t    owner; /**<  */
    xcb_atom_t      selection; /**<  */
} xcb_selection_clear_event_t;

typedef enum xcb_time_t {
    XCB_TIME_CURRENT_TIME = 0
} xcb_time_t;

typedef enum xcb_atom_enum_t {
    XCB_ATOM_NONE = 0,
    XCB_ATOM_ANY = 0,
    XCB_ATOM_PRIMARY,
    XCB_ATOM_SECONDARY,
    XCB_ATOM_ARC,
    XCB_ATOM_ATOM,
    XCB_ATOM_BITMAP,
    XCB_ATOM_CARDINAL,
    XCB_ATOM_COLORMAP,
    XCB_ATOM_CURSOR,
    XCB_ATOM_CUT_BUFFER0,
    XCB_ATOM_CUT_BUFFER1,
    XCB_ATOM_CUT_BUFFER2,
    XCB_ATOM_CUT_BUFFER3,
    XCB_ATOM_CUT_BUFFER4,
    XCB_ATOM_CUT_BUFFER5,
    XCB_ATOM_CUT_BUFFER6,
    XCB_ATOM_CUT_BUFFER7,
    XCB_ATOM_DRAWABLE,
    XCB_ATOM_FONT,
    XCB_ATOM_INTEGER,
    XCB_ATOM_PIXMAP,
    XCB_ATOM_POINT,
    XCB_ATOM_RECTANGLE,
    XCB_ATOM_RESOURCE_MANAGER,
    XCB_ATOM_RGB_COLOR_MAP,
    XCB_ATOM_RGB_BEST_MAP,
    XCB_ATOM_RGB_BLUE_MAP,
    XCB_ATOM_RGB_DEFAULT_MAP,
    XCB_ATOM_RGB_GRAY_MAP,
    XCB_ATOM_RGB_GREEN_MAP,
    XCB_ATOM_RGB_RED_MAP,
    XCB_ATOM_STRING,
    XCB_ATOM_VISUALID,
    XCB_ATOM_WINDOW,
    XCB_ATOM_WM_COMMAND,
    XCB_ATOM_WM_HINTS,
    XCB_ATOM_WM_CLIENT_MACHINE,
    XCB_ATOM_WM_ICON_NAME,
    XCB_ATOM_WM_ICON_SIZE,
    XCB_ATOM_WM_NAME,
    XCB_ATOM_WM_NORMAL_HINTS,
    XCB_ATOM_WM_SIZE_HINTS,
    XCB_ATOM_WM_ZOOM_HINTS,
    XCB_ATOM_MIN_SPACE,
    XCB_ATOM_NORM_SPACE,
    XCB_ATOM_MAX_SPACE,
    XCB_ATOM_END_SPACE,
    XCB_ATOM_SUPERSCRIPT_X,
    XCB_ATOM_SUPERSCRIPT_Y,
    XCB_ATOM_SUBSCRIPT_X,
    XCB_ATOM_SUBSCRIPT_Y,
    XCB_ATOM_UNDERLINE_POSITION,
    XCB_ATOM_UNDERLINE_THICKNESS,
    XCB_ATOM_STRIKEOUT_ASCENT,
    XCB_ATOM_STRIKEOUT_DESCENT,
    XCB_ATOM_ITALIC_ANGLE,
    XCB_ATOM_X_HEIGHT,
    XCB_ATOM_QUAD_WIDTH,
    XCB_ATOM_WEIGHT,
    XCB_ATOM_POINT_SIZE,
    XCB_ATOM_RESOLUTION,
    XCB_ATOM_COPYRIGHT,
    XCB_ATOM_NOTICE,
    XCB_ATOM_FONT_NAME,
    XCB_ATOM_FAMILY_NAME,
    XCB_ATOM_FULL_NAME,
    XCB_ATOM_CAP_HEIGHT,
    XCB_ATOM_WM_CLASS,
    XCB_ATOM_WM_TRANSIENT_FOR
} xcb_atom_enum_t;

/** Opcode for xcb_selection_request. */
#define XCB_SELECTION_REQUEST 30

/**
 * @brief xcb_selection_request_event_t
 **/
typedef struct xcb_selection_request_event_t {
    uint8_t         response_type; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        sequence; /**<  */
    xcb_timestamp_t time; /**<  */
    xcb_window_t    owner; /**<  */
    xcb_window_t    requestor; /**<  */
    xcb_atom_t      selection; /**<  */
    xcb_atom_t      target; /**<  */
    xcb_atom_t      property; /**<  */
} xcb_selection_request_event_t;

/** Opcode for xcb_selection_notify. */
#define XCB_SELECTION_NOTIFY 31

/**
 * @brief xcb_selection_notify_event_t
 **/
typedef struct xcb_selection_notify_event_t {
    uint8_t         response_type; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        sequence; /**<  */
    xcb_timestamp_t time; /**<  */
    xcb_window_t    requestor; /**<  */
    xcb_atom_t      selection; /**<  */
    xcb_atom_t      target; /**<  */
    xcb_atom_t      property; /**<  */
} xcb_selection_notify_event_t;

typedef enum xcb_colormap_state_t {
    XCB_COLORMAP_STATE_UNINSTALLED = 0,
    XCB_COLORMAP_STATE_INSTALLED = 1
} xcb_colormap_state_t;

typedef enum xcb_colormap_enum_t {
    XCB_COLORMAP_NONE = 0
} xcb_colormap_enum_t;

/** Opcode for xcb_colormap_notify. */
#define XCB_COLORMAP_NOTIFY 32

/**
 * @brief xcb_colormap_notify_event_t
 **/
typedef struct xcb_colormap_notify_event_t {
    uint8_t        response_type; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       sequence; /**<  */
    xcb_window_t   window; /**<  */
    xcb_colormap_t colormap; /**<  */
    uint8_t        _new; /**<  */
    uint8_t        state; /**<  */
    uint8_t        pad1[2]; /**<  */
} xcb_colormap_notify_event_t;

/**
 * @brief xcb_client_message_data_t
 **/
typedef union xcb_client_message_data_t {
    uint8_t  data8[20]; /**<  */
    uint16_t data16[10]; /**<  */
    uint32_t data32[5]; /**<  */
} xcb_client_message_data_t;

/**
 * @brief xcb_client_message_data_iterator_t
 **/
typedef struct xcb_client_message_data_iterator_t {
    xcb_client_message_data_t *data; /**<  */
    int                        rem; /**<  */
    int                        index; /**<  */
} xcb_client_message_data_iterator_t;

/** Opcode for xcb_client_message. */
#define XCB_CLIENT_MESSAGE 33

/**
 * @brief xcb_client_message_event_t
 **/
typedef struct xcb_client_message_event_t {
    uint8_t                   response_type; /**<  */
    uint8_t                   format; /**<  */
    uint16_t                  sequence; /**<  */
    xcb_window_t              window; /**<  */
    xcb_atom_t                type; /**<  */
    xcb_client_message_data_t data; /**<  */
} xcb_client_message_event_t;

typedef enum xcb_mapping_t {
    XCB_MAPPING_MODIFIER = 0,
    XCB_MAPPING_KEYBOARD = 1,
    XCB_MAPPING_POINTER = 2
} xcb_mapping_t;

/** Opcode for xcb_mapping_notify. */
#define XCB_MAPPING_NOTIFY 34

/**
 * @brief xcb_mapping_notify_event_t
 **/
typedef struct xcb_mapping_notify_event_t {
    uint8_t       response_type; /**<  */
    uint8_t       pad0; /**<  */
    uint16_t      sequence; /**<  */
    uint8_t       request; /**<  */
    xcb_keycode_t first_keycode; /**<  */
    uint8_t       count; /**<  */
    uint8_t       pad1; /**<  */
} xcb_mapping_notify_event_t;

/** Opcode for xcb_request. */
#define XCB_REQUEST 1

/**
 * @brief xcb_request_error_t
 **/
typedef struct xcb_request_error_t {
    uint8_t  response_type; /**<  */
    uint8_t  error_code; /**<  */
    uint16_t sequence; /**<  */
    uint32_t bad_value; /**<  */
    uint16_t minor_opcode; /**<  */
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
} xcb_request_error_t;

/** Opcode for xcb_value. */
#define XCB_VALUE 2

/**
 * @brief xcb_value_error_t
 **/
typedef struct xcb_value_error_t {
    uint8_t  response_type; /**<  */
    uint8_t  error_code; /**<  */
    uint16_t sequence; /**<  */
    uint32_t bad_value; /**<  */
    uint16_t minor_opcode; /**<  */
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
} xcb_value_error_t;

/** Opcode for xcb_window. */
#define XCB_WINDOW 3

typedef xcb_value_error_t xcb_window_error_t;

/** Opcode for xcb_pixmap. */
#define XCB_PIXMAP 4

typedef xcb_value_error_t xcb_pixmap_error_t;

/** Opcode for xcb_atom. */
#define XCB_ATOM 5

typedef xcb_value_error_t xcb_atom_error_t;

/** Opcode for xcb_cursor. */
#define XCB_CURSOR 6

typedef xcb_value_error_t xcb_cursor_error_t;

/** Opcode for xcb_font. */
#define XCB_FONT 7

typedef xcb_value_error_t xcb_font_error_t;

/** Opcode for xcb_match. */
#define XCB_MATCH 8

typedef xcb_request_error_t xcb_match_error_t;

/** Opcode for xcb_drawable. */
#define XCB_DRAWABLE 9

typedef xcb_value_error_t xcb_drawable_error_t;

/** Opcode for xcb_access. */
#define XCB_ACCESS 10

typedef xcb_request_error_t xcb_access_error_t;

/** Opcode for xcb_alloc. */
#define XCB_ALLOC 11

typedef xcb_request_error_t xcb_alloc_error_t;

/** Opcode for xcb_colormap. */
#define XCB_COLORMAP 12

typedef xcb_value_error_t xcb_colormap_error_t;

/** Opcode for xcb_g_context. */
#define XCB_G_CONTEXT 13

typedef xcb_value_error_t xcb_g_context_error_t;

/** Opcode for xcb_id_choice. */
#define XCB_ID_CHOICE 14

typedef xcb_value_error_t xcb_id_choice_error_t;

/** Opcode for xcb_name. */
#define XCB_NAME 15

typedef xcb_request_error_t xcb_name_error_t;

/** Opcode for xcb_length. */
#define XCB_LENGTH 16

typedef xcb_request_error_t xcb_length_error_t;

/** Opcode for xcb_implementation. */
#define XCB_IMPLEMENTATION 17

typedef xcb_request_error_t xcb_implementation_error_t;

typedef enum xcb_window_class_t {
    XCB_WINDOW_CLASS_COPY_FROM_PARENT = 0,
    XCB_WINDOW_CLASS_INPUT_OUTPUT = 1,
    XCB_WINDOW_CLASS_INPUT_ONLY = 2
} xcb_window_class_t;

typedef enum xcb_cw_t {
    XCB_CW_BACK_PIXMAP = 1,
    XCB_CW_BACK_PIXEL = 2,
    XCB_CW_BORDER_PIXMAP = 4,
    XCB_CW_BORDER_PIXEL = 8,
    XCB_CW_BIT_GRAVITY = 16,
    XCB_CW_WIN_GRAVITY = 32,
    XCB_CW_BACKING_STORE = 64,
    XCB_CW_BACKING_PLANES = 128,
    XCB_CW_BACKING_PIXEL = 256,
    XCB_CW_OVERRIDE_REDIRECT = 512,
    XCB_CW_SAVE_UNDER = 1024,
    XCB_CW_EVENT_MASK = 2048,
    XCB_CW_DONT_PROPAGATE = 4096,
    XCB_CW_COLORMAP = 8192,
    XCB_CW_CURSOR = 16384
} xcb_cw_t;

typedef enum xcb_back_pixmap_t {
    XCB_BACK_PIXMAP_NONE = 0,
    XCB_BACK_PIXMAP_PARENT_RELATIVE = 1
} xcb_back_pixmap_t;

typedef enum xcb_gravity_t {
    XCB_GRAVITY_BIT_FORGET = 0,
    XCB_GRAVITY_WIN_UNMAP = 0,
    XCB_GRAVITY_NORTH_WEST = 1,
    XCB_GRAVITY_NORTH = 2,
    XCB_GRAVITY_NORTH_EAST = 3,
    XCB_GRAVITY_WEST = 4,
    XCB_GRAVITY_CENTER = 5,
    XCB_GRAVITY_EAST = 6,
    XCB_GRAVITY_SOUTH_WEST = 7,
    XCB_GRAVITY_SOUTH = 8,
    XCB_GRAVITY_SOUTH_EAST = 9,
    XCB_GRAVITY_STATIC = 10
} xcb_gravity_t;

/** Opcode for xcb_create_window. */
#define XCB_CREATE_WINDOW 1

/**
 * @brief xcb_create_window_request_t
 **/
typedef struct xcb_create_window_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        depth; /**<  */
    uint16_t       length; /**<  */
    xcb_window_t   wid; /**<  */
    xcb_window_t   parent; /**<  */
    int16_t        x; /**<  */
    int16_t        y; /**<  */
    uint16_t       width; /**<  */
    uint16_t       height; /**<  */
    uint16_t       border_width; /**<  */
    uint16_t       _class; /**<  */
    xcb_visualid_t visual; /**<  */
    uint32_t       value_mask; /**<  */
} xcb_create_window_request_t;

/** Opcode for xcb_change_window_attributes. */
#define XCB_CHANGE_WINDOW_ATTRIBUTES 2

/**
 * @brief xcb_change_window_attributes_request_t
 **/
typedef struct xcb_change_window_attributes_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
    uint32_t     value_mask; /**<  */
} xcb_change_window_attributes_request_t;

typedef enum xcb_map_state_t {
    XCB_MAP_STATE_UNMAPPED = 0,
    XCB_MAP_STATE_UNVIEWABLE = 1,
    XCB_MAP_STATE_VIEWABLE = 2
} xcb_map_state_t;

/**
 * @brief xcb_get_window_attributes_cookie_t
 **/
typedef struct xcb_get_window_attributes_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_window_attributes_cookie_t;

/** Opcode for xcb_get_window_attributes. */
#define XCB_GET_WINDOW_ATTRIBUTES 3

/**
 * @brief xcb_get_window_attributes_request_t
 **/
typedef struct xcb_get_window_attributes_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_get_window_attributes_request_t;

/**
 * @brief xcb_get_window_attributes_reply_t
 **/
typedef struct xcb_get_window_attributes_reply_t {
    uint8_t        response_type; /**<  */
    uint8_t        backing_store; /**<  */
    uint16_t       sequence; /**<  */
    uint32_t       length; /**<  */
    xcb_visualid_t visual; /**<  */
    uint16_t       _class; /**<  */
    uint8_t        bit_gravity; /**<  */
    uint8_t        win_gravity; /**<  */
    uint32_t       backing_planes; /**<  */
    uint32_t       backing_pixel; /**<  */
    uint8_t        save_under; /**<  */
    uint8_t        map_is_installed; /**<  */
    uint8_t        map_state; /**<  */
    uint8_t        override_redirect; /**<  */
    xcb_colormap_t colormap; /**<  */
    uint32_t       all_event_masks; /**<  */
    uint32_t       your_event_mask; /**<  */
    uint16_t       do_not_propagate_mask; /**<  */
    uint8_t        pad0[2]; /**<  */
} xcb_get_window_attributes_reply_t;

/** Opcode for xcb_destroy_window. */
#define XCB_DESTROY_WINDOW 4

/**
 * @brief xcb_destroy_window_request_t
 **/
typedef struct xcb_destroy_window_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_destroy_window_request_t;

/** Opcode for xcb_destroy_subwindows. */
#define XCB_DESTROY_SUBWINDOWS 5

/**
 * @brief xcb_destroy_subwindows_request_t
 **/
typedef struct xcb_destroy_subwindows_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_destroy_subwindows_request_t;

typedef enum xcb_set_mode_t {
    XCB_SET_MODE_INSERT = 0,
    XCB_SET_MODE_DELETE = 1
} xcb_set_mode_t;

/** Opcode for xcb_change_save_set. */
#define XCB_CHANGE_SAVE_SET 6

/**
 * @brief xcb_change_save_set_request_t
 **/
typedef struct xcb_change_save_set_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      mode; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_change_save_set_request_t;

/** Opcode for xcb_reparent_window. */
#define XCB_REPARENT_WINDOW 7

/**
 * @brief xcb_reparent_window_request_t
 **/
typedef struct xcb_reparent_window_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
    xcb_window_t parent; /**<  */
    int16_t      x; /**<  */
    int16_t      y; /**<  */
} xcb_reparent_window_request_t;

/** Opcode for xcb_map_window. */
#define XCB_MAP_WINDOW 8

/**
 * @brief xcb_map_window_request_t
 **/
typedef struct xcb_map_window_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_map_window_request_t;

/** Opcode for xcb_map_subwindows. */
#define XCB_MAP_SUBWINDOWS 9

/**
 * @brief xcb_map_subwindows_request_t
 **/
typedef struct xcb_map_subwindows_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_map_subwindows_request_t;

/** Opcode for xcb_unmap_window. */
#define XCB_UNMAP_WINDOW 10

/**
 * @brief xcb_unmap_window_request_t
 **/
typedef struct xcb_unmap_window_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_unmap_window_request_t;

/** Opcode for xcb_unmap_subwindows. */
#define XCB_UNMAP_SUBWINDOWS 11

/**
 * @brief xcb_unmap_subwindows_request_t
 **/
typedef struct xcb_unmap_subwindows_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_unmap_subwindows_request_t;

typedef enum xcb_config_window_t {
    XCB_CONFIG_WINDOW_X = 1,
    XCB_CONFIG_WINDOW_Y = 2,
    XCB_CONFIG_WINDOW_WIDTH = 4,
    XCB_CONFIG_WINDOW_HEIGHT = 8,
    XCB_CONFIG_WINDOW_BORDER_WIDTH = 16,
    XCB_CONFIG_WINDOW_SIBLING = 32,
    XCB_CONFIG_WINDOW_STACK_MODE = 64
} xcb_config_window_t;

typedef enum xcb_stack_mode_t {
    XCB_STACK_MODE_ABOVE = 0,
    XCB_STACK_MODE_BELOW = 1,
    XCB_STACK_MODE_TOP_IF = 2,
    XCB_STACK_MODE_BOTTOM_IF = 3,
    XCB_STACK_MODE_OPPOSITE = 4
} xcb_stack_mode_t;

/** Opcode for xcb_configure_window. */
#define XCB_CONFIGURE_WINDOW 12

/**
 * @brief xcb_configure_window_request_t
 **/
typedef struct xcb_configure_window_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
    uint16_t     value_mask; /**<  */
    uint8_t      pad1[2]; /**<  */
} xcb_configure_window_request_t;

typedef enum xcb_circulate_t {
    XCB_CIRCULATE_RAISE_LOWEST = 0,
    XCB_CIRCULATE_LOWER_HIGHEST = 1
} xcb_circulate_t;

/** Opcode for xcb_circulate_window. */
#define XCB_CIRCULATE_WINDOW 13

/**
 * @brief xcb_circulate_window_request_t
 **/
typedef struct xcb_circulate_window_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      direction; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_circulate_window_request_t;

/**
 * @brief xcb_get_geometry_cookie_t
 **/
typedef struct xcb_get_geometry_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_geometry_cookie_t;

/** Opcode for xcb_get_geometry. */
#define XCB_GET_GEOMETRY 14

/**
 * @brief xcb_get_geometry_request_t
 **/
typedef struct xcb_get_geometry_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
} xcb_get_geometry_request_t;

/**
 * @brief xcb_get_geometry_reply_t
 **/
typedef struct xcb_get_geometry_reply_t {
    uint8_t      response_type; /**<  */
    uint8_t      depth; /**<  */
    uint16_t     sequence; /**<  */
    uint32_t     length; /**<  */
    xcb_window_t root; /**<  */
    int16_t      x; /**<  */
    int16_t      y; /**<  */
    uint16_t     width; /**<  */
    uint16_t     height; /**<  */
    uint16_t     border_width; /**<  */
    uint8_t      pad0[2]; /**<  */
} xcb_get_geometry_reply_t;

/**
 * @brief xcb_query_tree_cookie_t
 **/
typedef struct xcb_query_tree_cookie_t {
    unsigned int sequence; /**<  */
} xcb_query_tree_cookie_t;

/** Opcode for xcb_query_tree. */
#define XCB_QUERY_TREE 15

/**
 * @brief xcb_query_tree_request_t
 **/
typedef struct xcb_query_tree_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_query_tree_request_t;

/**
 * @brief xcb_query_tree_reply_t
 **/
typedef struct xcb_query_tree_reply_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    uint32_t     length; /**<  */
    xcb_window_t root; /**<  */
    xcb_window_t parent; /**<  */
    uint16_t     children_len; /**<  */
    uint8_t      pad1[14]; /**<  */
} xcb_query_tree_reply_t;

/**
 * @brief xcb_intern_atom_cookie_t
 **/
typedef struct xcb_intern_atom_cookie_t {
    unsigned int sequence; /**<  */
} xcb_intern_atom_cookie_t;

/** Opcode for xcb_intern_atom. */
#define XCB_INTERN_ATOM 16

/**
 * @brief xcb_intern_atom_request_t
 **/
typedef struct xcb_intern_atom_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  only_if_exists; /**<  */
    uint16_t length; /**<  */
    uint16_t name_len; /**<  */
    uint8_t  pad0[2]; /**<  */
} xcb_intern_atom_request_t;

/**
 * @brief xcb_intern_atom_reply_t
 **/
typedef struct xcb_intern_atom_reply_t {
    uint8_t    response_type; /**<  */
    uint8_t    pad0; /**<  */
    uint16_t   sequence; /**<  */
    uint32_t   length; /**<  */
    xcb_atom_t atom; /**<  */
} xcb_intern_atom_reply_t;

/**
 * @brief xcb_get_atom_name_cookie_t
 **/
typedef struct xcb_get_atom_name_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_atom_name_cookie_t;

/** Opcode for xcb_get_atom_name. */
#define XCB_GET_ATOM_NAME 17

/**
 * @brief xcb_get_atom_name_request_t
 **/
typedef struct xcb_get_atom_name_request_t {
    uint8_t    major_opcode; /**<  */
    uint8_t    pad0; /**<  */
    uint16_t   length; /**<  */
    xcb_atom_t atom; /**<  */
} xcb_get_atom_name_request_t;

/**
 * @brief xcb_get_atom_name_reply_t
 **/
typedef struct xcb_get_atom_name_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t name_len; /**<  */
    uint8_t  pad1[22]; /**<  */
} xcb_get_atom_name_reply_t;

typedef enum xcb_prop_mode_t {
    XCB_PROP_MODE_REPLACE = 0,
    XCB_PROP_MODE_PREPEND = 1,
    XCB_PROP_MODE_APPEND = 2
} xcb_prop_mode_t;

/** Opcode for xcb_change_property. */
#define XCB_CHANGE_PROPERTY 18

/**
 * @brief xcb_change_property_request_t
 **/
typedef struct xcb_change_property_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      mode; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
    xcb_atom_t   property; /**<  */
    xcb_atom_t   type; /**<  */
    uint8_t      format; /**<  */
    uint8_t      pad0[3]; /**<  */
    uint32_t     data_len; /**<  */
} xcb_change_property_request_t;

/** Opcode for xcb_delete_property. */
#define XCB_DELETE_PROPERTY 19

/**
 * @brief xcb_delete_property_request_t
 **/
typedef struct xcb_delete_property_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
    xcb_atom_t   property; /**<  */
} xcb_delete_property_request_t;

typedef enum xcb_get_property_type_t {
    XCB_GET_PROPERTY_TYPE_ANY = 0
} xcb_get_property_type_t;

/**
 * @brief xcb_get_property_cookie_t
 **/
typedef struct xcb_get_property_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_property_cookie_t;

/** Opcode for xcb_get_property. */
#define XCB_GET_PROPERTY 20

/**
 * @brief xcb_get_property_request_t
 **/
typedef struct xcb_get_property_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      _delete; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
    xcb_atom_t   property; /**<  */
    xcb_atom_t   type; /**<  */
    uint32_t     long_offset; /**<  */
    uint32_t     long_length; /**<  */
} xcb_get_property_request_t;

/**
 * @brief xcb_get_property_reply_t
 **/
typedef struct xcb_get_property_reply_t {
    uint8_t    response_type; /**<  */
    uint8_t    format; /**<  */
    uint16_t   sequence; /**<  */
    uint32_t   length; /**<  */
    xcb_atom_t type; /**<  */
    uint32_t   bytes_after; /**<  */
    uint32_t   value_len; /**<  */
    uint8_t    pad0[12]; /**<  */
} xcb_get_property_reply_t;

/**
 * @brief xcb_list_properties_cookie_t
 **/
typedef struct xcb_list_properties_cookie_t {
    unsigned int sequence; /**<  */
} xcb_list_properties_cookie_t;

/** Opcode for xcb_list_properties. */
#define XCB_LIST_PROPERTIES 21

/**
 * @brief xcb_list_properties_request_t
 **/
typedef struct xcb_list_properties_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_list_properties_request_t;

/**
 * @brief xcb_list_properties_reply_t
 **/
typedef struct xcb_list_properties_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t atoms_len; /**<  */
    uint8_t  pad1[22]; /**<  */
} xcb_list_properties_reply_t;

/** Opcode for xcb_set_selection_owner. */
#define XCB_SET_SELECTION_OWNER 22

/**
 * @brief xcb_set_selection_owner_request_t
 **/
typedef struct xcb_set_selection_owner_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        length; /**<  */
    xcb_window_t    owner; /**<  */
    xcb_atom_t      selection; /**<  */
    xcb_timestamp_t time; /**<  */
} xcb_set_selection_owner_request_t;

/**
 * @brief xcb_get_selection_owner_cookie_t
 **/
typedef struct xcb_get_selection_owner_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_selection_owner_cookie_t;

/** Opcode for xcb_get_selection_owner. */
#define XCB_GET_SELECTION_OWNER 23

/**
 * @brief xcb_get_selection_owner_request_t
 **/
typedef struct xcb_get_selection_owner_request_t {
    uint8_t    major_opcode; /**<  */
    uint8_t    pad0; /**<  */
    uint16_t   length; /**<  */
    xcb_atom_t selection; /**<  */
} xcb_get_selection_owner_request_t;

/**
 * @brief xcb_get_selection_owner_reply_t
 **/
typedef struct xcb_get_selection_owner_reply_t {
    uint8_t      response_type; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     sequence; /**<  */
    uint32_t     length; /**<  */
    xcb_window_t owner; /**<  */
} xcb_get_selection_owner_reply_t;

/** Opcode for xcb_convert_selection. */
#define XCB_CONVERT_SELECTION 24

/**
 * @brief xcb_convert_selection_request_t
 **/
typedef struct xcb_convert_selection_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        length; /**<  */
    xcb_window_t    requestor; /**<  */
    xcb_atom_t      selection; /**<  */
    xcb_atom_t      target; /**<  */
    xcb_atom_t      property; /**<  */
    xcb_timestamp_t time; /**<  */
} xcb_convert_selection_request_t;

typedef enum xcb_send_event_dest_t {
    XCB_SEND_EVENT_DEST_POINTER_WINDOW = 0,
    XCB_SEND_EVENT_DEST_ITEM_FOCUS = 1
} xcb_send_event_dest_t;

/** Opcode for xcb_send_event. */
#define XCB_SEND_EVENT 25

/**
 * @brief xcb_send_event_request_t
 **/
typedef struct xcb_send_event_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      propagate; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t destination; /**<  */
    uint32_t     event_mask; /**<  */
    char         event[32]; /**<  */
} xcb_send_event_request_t;

typedef enum xcb_grab_mode_t {
    XCB_GRAB_MODE_SYNC = 0,
    XCB_GRAB_MODE_ASYNC = 1
} xcb_grab_mode_t;

typedef enum xcb_grab_status_t {
    XCB_GRAB_STATUS_SUCCESS = 0,
    XCB_GRAB_STATUS_ALREADY_GRABBED = 1,
    XCB_GRAB_STATUS_INVALID_TIME = 2,
    XCB_GRAB_STATUS_NOT_VIEWABLE = 3,
    XCB_GRAB_STATUS_FROZEN = 4
} xcb_grab_status_t;

typedef enum xcb_cursor_enum_t {
    XCB_CURSOR_NONE = 0
} xcb_cursor_enum_t;

/**
 * @brief xcb_grab_pointer_cookie_t
 **/
typedef struct xcb_grab_pointer_cookie_t {
    unsigned int sequence; /**<  */
} xcb_grab_pointer_cookie_t;

/** Opcode for xcb_grab_pointer. */
#define XCB_GRAB_POINTER 26

/**
 * @brief xcb_grab_pointer_request_t
 **/
typedef struct xcb_grab_pointer_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         owner_events; /**<  */
    uint16_t        length; /**<  */
    xcb_window_t    grab_window; /**<  */
    uint16_t        event_mask; /**<  */
    uint8_t         pointer_mode; /**<  */
    uint8_t         keyboard_mode; /**<  */
    xcb_window_t    confine_to; /**<  */
    xcb_cursor_t    cursor; /**<  */
    xcb_timestamp_t time; /**<  */
} xcb_grab_pointer_request_t;

/**
 * @brief xcb_grab_pointer_reply_t
 **/
typedef struct xcb_grab_pointer_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  status; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
} xcb_grab_pointer_reply_t;

/** Opcode for xcb_ungrab_pointer. */
#define XCB_UNGRAB_POINTER 27

/**
 * @brief xcb_ungrab_pointer_request_t
 **/
typedef struct xcb_ungrab_pointer_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        length; /**<  */
    xcb_timestamp_t time; /**<  */
} xcb_ungrab_pointer_request_t;

typedef enum xcb_button_index_t {
    XCB_BUTTON_INDEX_ANY = 0,
    XCB_BUTTON_INDEX_1 = 1,
    XCB_BUTTON_INDEX_2 = 2,
    XCB_BUTTON_INDEX_3 = 3,
    XCB_BUTTON_INDEX_4 = 4,
    XCB_BUTTON_INDEX_5 = 5
} xcb_button_index_t;

/** Opcode for xcb_grab_button. */
#define XCB_GRAB_BUTTON 28

/**
 * @brief xcb_grab_button_request_t
 **/
typedef struct xcb_grab_button_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      owner_events; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t grab_window; /**<  */
    uint16_t     event_mask; /**<  */
    uint8_t      pointer_mode; /**<  */
    uint8_t      keyboard_mode; /**<  */
    xcb_window_t confine_to; /**<  */
    xcb_cursor_t cursor; /**<  */
    uint8_t      button; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     modifiers; /**<  */
} xcb_grab_button_request_t;

/** Opcode for xcb_ungrab_button. */
#define XCB_UNGRAB_BUTTON 29

/**
 * @brief xcb_ungrab_button_request_t
 **/
typedef struct xcb_ungrab_button_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      button; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t grab_window; /**<  */
    uint16_t     modifiers; /**<  */
    uint8_t      pad0[2]; /**<  */
} xcb_ungrab_button_request_t;

/** Opcode for xcb_change_active_pointer_grab. */
#define XCB_CHANGE_ACTIVE_POINTER_GRAB 30

/**
 * @brief xcb_change_active_pointer_grab_request_t
 **/
typedef struct xcb_change_active_pointer_grab_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        length; /**<  */
    xcb_cursor_t    cursor; /**<  */
    xcb_timestamp_t time; /**<  */
    uint16_t        event_mask; /**<  */
    uint8_t         pad1[2]; /**<  */
} xcb_change_active_pointer_grab_request_t;

/**
 * @brief xcb_grab_keyboard_cookie_t
 **/
typedef struct xcb_grab_keyboard_cookie_t {
    unsigned int sequence; /**<  */
} xcb_grab_keyboard_cookie_t;

/** Opcode for xcb_grab_keyboard. */
#define XCB_GRAB_KEYBOARD 31

/**
 * @brief xcb_grab_keyboard_request_t
 **/
typedef struct xcb_grab_keyboard_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         owner_events; /**<  */
    uint16_t        length; /**<  */
    xcb_window_t    grab_window; /**<  */
    xcb_timestamp_t time; /**<  */
    uint8_t         pointer_mode; /**<  */
    uint8_t         keyboard_mode; /**<  */
    uint8_t         pad0[2]; /**<  */
} xcb_grab_keyboard_request_t;

/**
 * @brief xcb_grab_keyboard_reply_t
 **/
typedef struct xcb_grab_keyboard_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  status; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
} xcb_grab_keyboard_reply_t;

/** Opcode for xcb_ungrab_keyboard. */
#define XCB_UNGRAB_KEYBOARD 32

/**
 * @brief xcb_ungrab_keyboard_request_t
 **/
typedef struct xcb_ungrab_keyboard_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        length; /**<  */
    xcb_timestamp_t time; /**<  */
} xcb_ungrab_keyboard_request_t;

typedef enum xcb_grab_t {
    XCB_GRAB_ANY = 0
} xcb_grab_t;

/** Opcode for xcb_grab_key. */
#define XCB_GRAB_KEY 33

/**
 * @brief xcb_grab_key_request_t
 **/
typedef struct xcb_grab_key_request_t {
    uint8_t       major_opcode; /**<  */
    uint8_t       owner_events; /**<  */
    uint16_t      length; /**<  */
    xcb_window_t  grab_window; /**<  */
    uint16_t      modifiers; /**<  */
    xcb_keycode_t key; /**<  */
    uint8_t       pointer_mode; /**<  */
    uint8_t       keyboard_mode; /**<  */
    uint8_t       pad0[3]; /**<  */
} xcb_grab_key_request_t;

/** Opcode for xcb_ungrab_key. */
#define XCB_UNGRAB_KEY 34

/**
 * @brief xcb_ungrab_key_request_t
 **/
typedef struct xcb_ungrab_key_request_t {
    uint8_t       major_opcode; /**<  */
    xcb_keycode_t key; /**<  */
    uint16_t      length; /**<  */
    xcb_window_t  grab_window; /**<  */
    uint16_t      modifiers; /**<  */
    uint8_t       pad0[2]; /**<  */
} xcb_ungrab_key_request_t;

typedef enum xcb_allow_t {
    XCB_ALLOW_ASYNC_POINTER = 0,
    XCB_ALLOW_SYNC_POINTER = 1,
    XCB_ALLOW_REPLAY_POINTER = 2,
    XCB_ALLOW_ASYNC_KEYBOARD = 3,
    XCB_ALLOW_SYNC_KEYBOARD = 4,
    XCB_ALLOW_REPLAY_KEYBOARD = 5,
    XCB_ALLOW_ASYNC_BOTH = 6,
    XCB_ALLOW_SYNC_BOTH = 7
} xcb_allow_t;

/** Opcode for xcb_allow_events. */
#define XCB_ALLOW_EVENTS 35

/**
 * @brief xcb_allow_events_request_t
 **/
typedef struct xcb_allow_events_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         mode; /**<  */
    uint16_t        length; /**<  */
    xcb_timestamp_t time; /**<  */
} xcb_allow_events_request_t;

/** Opcode for xcb_grab_server. */
#define XCB_GRAB_SERVER 36

/**
 * @brief xcb_grab_server_request_t
 **/
typedef struct xcb_grab_server_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_grab_server_request_t;

/** Opcode for xcb_ungrab_server. */
#define XCB_UNGRAB_SERVER 37

/**
 * @brief xcb_ungrab_server_request_t
 **/
typedef struct xcb_ungrab_server_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_ungrab_server_request_t;

/**
 * @brief xcb_query_pointer_cookie_t
 **/
typedef struct xcb_query_pointer_cookie_t {
    unsigned int sequence; /**<  */
} xcb_query_pointer_cookie_t;

/** Opcode for xcb_query_pointer. */
#define XCB_QUERY_POINTER 38

/**
 * @brief xcb_query_pointer_request_t
 **/
typedef struct xcb_query_pointer_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_query_pointer_request_t;

/**
 * @brief xcb_query_pointer_reply_t
 **/
typedef struct xcb_query_pointer_reply_t {
    uint8_t      response_type; /**<  */
    uint8_t      same_screen; /**<  */
    uint16_t     sequence; /**<  */
    uint32_t     length; /**<  */
    xcb_window_t root; /**<  */
    xcb_window_t child; /**<  */
    int16_t      root_x; /**<  */
    int16_t      root_y; /**<  */
    int16_t      win_x; /**<  */
    int16_t      win_y; /**<  */
    uint16_t     mask; /**<  */
    uint8_t      pad0[2]; /**<  */
} xcb_query_pointer_reply_t;

/**
 * @brief xcb_timecoord_t
 **/
typedef struct xcb_timecoord_t {
    xcb_timestamp_t time; /**<  */
    int16_t         x; /**<  */
    int16_t         y; /**<  */
} xcb_timecoord_t;

/**
 * @brief xcb_timecoord_iterator_t
 **/
typedef struct xcb_timecoord_iterator_t {
    xcb_timecoord_t *data; /**<  */
    int              rem; /**<  */
    int              index; /**<  */
} xcb_timecoord_iterator_t;

/**
 * @brief xcb_get_motion_events_cookie_t
 **/
typedef struct xcb_get_motion_events_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_motion_events_cookie_t;

/** Opcode for xcb_get_motion_events. */
#define XCB_GET_MOTION_EVENTS 39

/**
 * @brief xcb_get_motion_events_request_t
 **/
typedef struct xcb_get_motion_events_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         pad0; /**<  */
    uint16_t        length; /**<  */
    xcb_window_t    window; /**<  */
    xcb_timestamp_t start; /**<  */
    xcb_timestamp_t stop; /**<  */
} xcb_get_motion_events_request_t;

/**
 * @brief xcb_get_motion_events_reply_t
 **/
typedef struct xcb_get_motion_events_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint32_t events_len; /**<  */
    uint8_t  pad1[20]; /**<  */
} xcb_get_motion_events_reply_t;

/**
 * @brief xcb_translate_coordinates_cookie_t
 **/
typedef struct xcb_translate_coordinates_cookie_t {
    unsigned int sequence; /**<  */
} xcb_translate_coordinates_cookie_t;

/** Opcode for xcb_translate_coordinates. */
#define XCB_TRANSLATE_COORDINATES 40

/**
 * @brief xcb_translate_coordinates_request_t
 **/
typedef struct xcb_translate_coordinates_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t src_window; /**<  */
    xcb_window_t dst_window; /**<  */
    int16_t      src_x; /**<  */
    int16_t      src_y; /**<  */
} xcb_translate_coordinates_request_t;

/**
 * @brief xcb_translate_coordinates_reply_t
 **/
typedef struct xcb_translate_coordinates_reply_t {
    uint8_t      response_type; /**<  */
    uint8_t      same_screen; /**<  */
    uint16_t     sequence; /**<  */
    uint32_t     length; /**<  */
    xcb_window_t child; /**<  */
    uint16_t     dst_x; /**<  */
    uint16_t     dst_y; /**<  */
} xcb_translate_coordinates_reply_t;

/** Opcode for xcb_warp_pointer. */
#define XCB_WARP_POINTER 41

/**
 * @brief xcb_warp_pointer_request_t
 **/
typedef struct xcb_warp_pointer_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t src_window; /**<  */
    xcb_window_t dst_window; /**<  */
    int16_t      src_x; /**<  */
    int16_t      src_y; /**<  */
    uint16_t     src_width; /**<  */
    uint16_t     src_height; /**<  */
    int16_t      dst_x; /**<  */
    int16_t      dst_y; /**<  */
} xcb_warp_pointer_request_t;

typedef enum xcb_input_focus_t {
    XCB_INPUT_FOCUS_NONE = 0,
    XCB_INPUT_FOCUS_POINTER_ROOT = 1,
    XCB_INPUT_FOCUS_PARENT = 2,
    XCB_INPUT_FOCUS_FOLLOW_KEYBOARD = 3
} xcb_input_focus_t;

/** Opcode for xcb_set_input_focus. */
#define XCB_SET_INPUT_FOCUS 42

/**
 * @brief xcb_set_input_focus_request_t
 **/
typedef struct xcb_set_input_focus_request_t {
    uint8_t         major_opcode; /**<  */
    uint8_t         revert_to; /**<  */
    uint16_t        length; /**<  */
    xcb_window_t    focus; /**<  */
    xcb_timestamp_t time; /**<  */
} xcb_set_input_focus_request_t;

/**
 * @brief xcb_get_input_focus_cookie_t
 **/
typedef struct xcb_get_input_focus_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_input_focus_cookie_t;

/** Opcode for xcb_get_input_focus. */
#define XCB_GET_INPUT_FOCUS 43

/**
 * @brief xcb_get_input_focus_request_t
 **/
typedef struct xcb_get_input_focus_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_get_input_focus_request_t;

/**
 * @brief xcb_get_input_focus_reply_t
 **/
typedef struct xcb_get_input_focus_reply_t {
    uint8_t      response_type; /**<  */
    uint8_t      revert_to; /**<  */
    uint16_t     sequence; /**<  */
    uint32_t     length; /**<  */
    xcb_window_t focus; /**<  */
} xcb_get_input_focus_reply_t;

/**
 * @brief xcb_query_keymap_cookie_t
 **/
typedef struct xcb_query_keymap_cookie_t {
    unsigned int sequence; /**<  */
} xcb_query_keymap_cookie_t;

/** Opcode for xcb_query_keymap. */
#define XCB_QUERY_KEYMAP 44

/**
 * @brief xcb_query_keymap_request_t
 **/
typedef struct xcb_query_keymap_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_query_keymap_request_t;

/**
 * @brief xcb_query_keymap_reply_t
 **/
typedef struct xcb_query_keymap_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint8_t  keys[32]; /**<  */
} xcb_query_keymap_reply_t;

/** Opcode for xcb_open_font. */
#define XCB_OPEN_FONT 45

/**
 * @brief xcb_open_font_request_t
 **/
typedef struct xcb_open_font_request_t {
    uint8_t    major_opcode; /**<  */
    uint8_t    pad0; /**<  */
    uint16_t   length; /**<  */
    xcb_font_t fid; /**<  */
    uint16_t   name_len; /**<  */
    uint8_t    pad1[2]; /**<  */
} xcb_open_font_request_t;

/** Opcode for xcb_close_font. */
#define XCB_CLOSE_FONT 46

/**
 * @brief xcb_close_font_request_t
 **/
typedef struct xcb_close_font_request_t {
    uint8_t    major_opcode; /**<  */
    uint8_t    pad0; /**<  */
    uint16_t   length; /**<  */
    xcb_font_t font; /**<  */
} xcb_close_font_request_t;

typedef enum xcb_font_draw_t {
    XCB_FONT_DRAW_LEFT_TO_RIGHT = 0,
    XCB_FONT_DRAW_RIGHT_TO_LEFT = 1
} xcb_font_draw_t;

/**
 * @brief xcb_fontprop_t
 **/
typedef struct xcb_fontprop_t {
    xcb_atom_t name; /**<  */
    uint32_t   value; /**<  */
} xcb_fontprop_t;

/**
 * @brief xcb_fontprop_iterator_t
 **/
typedef struct xcb_fontprop_iterator_t {
    xcb_fontprop_t *data; /**<  */
    int             rem; /**<  */
    int             index; /**<  */
} xcb_fontprop_iterator_t;

/**
 * @brief xcb_charinfo_t
 **/
typedef struct xcb_charinfo_t {
    int16_t  left_side_bearing; /**<  */
    int16_t  right_side_bearing; /**<  */
    int16_t  character_width; /**<  */
    int16_t  ascent; /**<  */
    int16_t  descent; /**<  */
    uint16_t attributes; /**<  */
} xcb_charinfo_t;

/**
 * @brief xcb_charinfo_iterator_t
 **/
typedef struct xcb_charinfo_iterator_t {
    xcb_charinfo_t *data; /**<  */
    int             rem; /**<  */
    int             index; /**<  */
} xcb_charinfo_iterator_t;

/**
 * @brief xcb_query_font_cookie_t
 **/
typedef struct xcb_query_font_cookie_t {
    unsigned int sequence; /**<  */
} xcb_query_font_cookie_t;

/** Opcode for xcb_query_font. */
#define XCB_QUERY_FONT 47

/**
 * @brief xcb_query_font_request_t
 **/
typedef struct xcb_query_font_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_fontable_t font; /**<  */
} xcb_query_font_request_t;

/**
 * @brief xcb_query_font_reply_t
 **/
typedef struct xcb_query_font_reply_t {
    uint8_t        response_type; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       sequence; /**<  */
    uint32_t       length; /**<  */
    xcb_charinfo_t min_bounds; /**<  */
    uint8_t        pad1[4]; /**<  */
    xcb_charinfo_t max_bounds; /**<  */
    uint8_t        pad2[4]; /**<  */
    uint16_t       min_char_or_byte2; /**<  */
    uint16_t       max_char_or_byte2; /**<  */
    uint16_t       default_char; /**<  */
    uint16_t       properties_len; /**<  */
    uint8_t        draw_direction; /**<  */
    uint8_t        min_byte1; /**<  */
    uint8_t        max_byte1; /**<  */
    uint8_t        all_chars_exist; /**<  */
    int16_t        font_ascent; /**<  */
    int16_t        font_descent; /**<  */
    uint32_t       char_infos_len; /**<  */
} xcb_query_font_reply_t;

/**
 * @brief xcb_query_text_extents_cookie_t
 **/
typedef struct xcb_query_text_extents_cookie_t {
    unsigned int sequence; /**<  */
} xcb_query_text_extents_cookie_t;

/** Opcode for xcb_query_text_extents. */
#define XCB_QUERY_TEXT_EXTENTS 48

/**
 * @brief xcb_query_text_extents_request_t
 **/
typedef struct xcb_query_text_extents_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        odd_length; /**<  */
    uint16_t       length; /**<  */
    xcb_fontable_t font; /**<  */
} xcb_query_text_extents_request_t;

/**
 * @brief xcb_query_text_extents_reply_t
 **/
typedef struct xcb_query_text_extents_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  draw_direction; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    int16_t  font_ascent; /**<  */
    int16_t  font_descent; /**<  */
    int16_t  overall_ascent; /**<  */
    int16_t  overall_descent; /**<  */
    int32_t  overall_width; /**<  */
    int32_t  overall_left; /**<  */
    int32_t  overall_right; /**<  */
} xcb_query_text_extents_reply_t;

/**
 * @brief xcb_str_t
 **/
typedef struct xcb_str_t {
    uint8_t name_len; /**<  */
} xcb_str_t;

/**
 * @brief xcb_str_iterator_t
 **/
typedef struct xcb_str_iterator_t {
    xcb_str_t *data; /**<  */
    int        rem; /**<  */
    int        index; /**<  */
} xcb_str_iterator_t;

/**
 * @brief xcb_list_fonts_cookie_t
 **/
typedef struct xcb_list_fonts_cookie_t {
    unsigned int sequence; /**<  */
} xcb_list_fonts_cookie_t;

/** Opcode for xcb_list_fonts. */
#define XCB_LIST_FONTS 49

/**
 * @brief xcb_list_fonts_request_t
 **/
typedef struct xcb_list_fonts_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
    uint16_t max_names; /**<  */
    uint16_t pattern_len; /**<  */
} xcb_list_fonts_request_t;

/**
 * @brief xcb_list_fonts_reply_t
 **/
typedef struct xcb_list_fonts_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t names_len; /**<  */
    uint8_t  pad1[22]; /**<  */
} xcb_list_fonts_reply_t;

/**
 * @brief xcb_list_fonts_with_info_cookie_t
 **/
typedef struct xcb_list_fonts_with_info_cookie_t {
    unsigned int sequence; /**<  */
} xcb_list_fonts_with_info_cookie_t;

/** Opcode for xcb_list_fonts_with_info. */
#define XCB_LIST_FONTS_WITH_INFO 50

/**
 * @brief xcb_list_fonts_with_info_request_t
 **/
typedef struct xcb_list_fonts_with_info_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
    uint16_t max_names; /**<  */
    uint16_t pattern_len; /**<  */
} xcb_list_fonts_with_info_request_t;

/**
 * @brief xcb_list_fonts_with_info_reply_t
 **/
typedef struct xcb_list_fonts_with_info_reply_t {
    uint8_t        response_type; /**<  */
    uint8_t        name_len; /**<  */
    uint16_t       sequence; /**<  */
    uint32_t       length; /**<  */
    xcb_charinfo_t min_bounds; /**<  */
    uint8_t        pad0[4]; /**<  */
    xcb_charinfo_t max_bounds; /**<  */
    uint8_t        pad1[4]; /**<  */
    uint16_t       min_char_or_byte2; /**<  */
    uint16_t       max_char_or_byte2; /**<  */
    uint16_t       default_char; /**<  */
    uint16_t       properties_len; /**<  */
    uint8_t        draw_direction; /**<  */
    uint8_t        min_byte1; /**<  */
    uint8_t        max_byte1; /**<  */
    uint8_t        all_chars_exist; /**<  */
    int16_t        font_ascent; /**<  */
    int16_t        font_descent; /**<  */
    uint32_t       replies_hint; /**<  */
} xcb_list_fonts_with_info_reply_t;

/** Opcode for xcb_set_font_path. */
#define XCB_SET_FONT_PATH 51

/**
 * @brief xcb_set_font_path_request_t
 **/
typedef struct xcb_set_font_path_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
    uint16_t font_qty; /**<  */
} xcb_set_font_path_request_t;

/**
 * @brief xcb_get_font_path_cookie_t
 **/
typedef struct xcb_get_font_path_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_font_path_cookie_t;

/** Opcode for xcb_get_font_path. */
#define XCB_GET_FONT_PATH 52

/**
 * @brief xcb_get_font_path_request_t
 **/
typedef struct xcb_get_font_path_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_get_font_path_request_t;

/**
 * @brief xcb_get_font_path_reply_t
 **/
typedef struct xcb_get_font_path_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t path_len; /**<  */
    uint8_t  pad1[22]; /**<  */
} xcb_get_font_path_reply_t;

/** Opcode for xcb_create_pixmap. */
#define XCB_CREATE_PIXMAP 53

/**
 * @brief xcb_create_pixmap_request_t
 **/
typedef struct xcb_create_pixmap_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        depth; /**<  */
    uint16_t       length; /**<  */
    xcb_pixmap_t   pid; /**<  */
    xcb_drawable_t drawable; /**<  */
    uint16_t       width; /**<  */
    uint16_t       height; /**<  */
} xcb_create_pixmap_request_t;

/** Opcode for xcb_free_pixmap. */
#define XCB_FREE_PIXMAP 54

/**
 * @brief xcb_free_pixmap_request_t
 **/
typedef struct xcb_free_pixmap_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_pixmap_t pixmap; /**<  */
} xcb_free_pixmap_request_t;

typedef enum xcb_gc_t {
    XCB_GC_FUNCTION = 1,
    XCB_GC_PLANE_MASK = 2,
    XCB_GC_FOREGROUND = 4,
    XCB_GC_BACKGROUND = 8,
    XCB_GC_LINE_WIDTH = 16,
    XCB_GC_LINE_STYLE = 32,
    XCB_GC_CAP_STYLE = 64,
    XCB_GC_JOIN_STYLE = 128,
    XCB_GC_FILL_STYLE = 256,
    XCB_GC_FILL_RULE = 512,
    XCB_GC_TILE = 1024,
    XCB_GC_STIPPLE = 2048,
    XCB_GC_TILE_STIPPLE_ORIGIN_X = 4096,
    XCB_GC_TILE_STIPPLE_ORIGIN_Y = 8192,
    XCB_GC_FONT = 16384,
    XCB_GC_SUBWINDOW_MODE = 32768,
    XCB_GC_GRAPHICS_EXPOSURES = 65536,
    XCB_GC_CLIP_ORIGIN_X = 131072,
    XCB_GC_CLIP_ORIGIN_Y = 262144,
    XCB_GC_CLIP_MASK = 524288,
    XCB_GC_DASH_OFFSET = 1048576,
    XCB_GC_DASH_LIST = 2097152,
    XCB_GC_ARC_MODE = 4194304
} xcb_gc_t;

typedef enum xcb_gx_t {
    XCB_GX_CLEAR = 0,
    XCB_GX_AND = 1,
    XCB_GX_AND_REVERSE = 2,
    XCB_GX_COPY = 3,
    XCB_GX_AND_INVERTED = 4,
    XCB_GX_NOOP = 5,
    XCB_GX_XOR = 6,
    XCB_GX_OR = 7,
    XCB_GX_NOR = 8,
    XCB_GX_EQUIV = 9,
    XCB_GX_INVERT = 10,
    XCB_GX_OR_REVERSE = 11,
    XCB_GX_COPY_INVERTED = 12,
    XCB_GX_OR_INVERTED = 13,
    XCB_GX_NAND = 14,
    XCB_GX_SET = 15
} xcb_gx_t;

typedef enum xcb_line_style_t {
    XCB_LINE_STYLE_SOLID = 0,
    XCB_LINE_STYLE_ON_OFF_DASH = 1,
    XCB_LINE_STYLE_DOUBLE_DASH = 2
} xcb_line_style_t;

typedef enum xcb_cap_style_t {
    XCB_CAP_STYLE_NOT_LAST = 0,
    XCB_CAP_STYLE_BUTT = 1,
    XCB_CAP_STYLE_ROUND = 2,
    XCB_CAP_STYLE_PROJECTING = 3
} xcb_cap_style_t;

typedef enum xcb_join_style_t {
    XCB_JOIN_STYLE_MITER = 0,
    XCB_JOIN_STYLE_ROUND = 1,
    XCB_JOIN_STYLE_BEVEL = 2
} xcb_join_style_t;

typedef enum xcb_fill_style_t {
    XCB_FILL_STYLE_SOLID = 0,
    XCB_FILL_STYLE_TILED = 1,
    XCB_FILL_STYLE_STIPPLED = 2,
    XCB_FILL_STYLE_OPAQUE_STIPPLED = 3
} xcb_fill_style_t;

typedef enum xcb_fill_rule_t {
    XCB_FILL_RULE_EVEN_ODD = 0,
    XCB_FILL_RULE_WINDING = 1
} xcb_fill_rule_t;

typedef enum xcb_subwindow_mode_t {
    XCB_SUBWINDOW_MODE_CLIP_BY_CHILDREN = 0,
    XCB_SUBWINDOW_MODE_INCLUDE_INFERIORS = 1
} xcb_subwindow_mode_t;

typedef enum xcb_arc_mode_t {
    XCB_ARC_MODE_CHORD = 0,
    XCB_ARC_MODE_PIE_SLICE = 1
} xcb_arc_mode_t;

/** Opcode for xcb_create_gc. */
#define XCB_CREATE_GC 55

/**
 * @brief xcb_create_gc_request_t
 **/
typedef struct xcb_create_gc_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_gcontext_t cid; /**<  */
    xcb_drawable_t drawable; /**<  */
    uint32_t       value_mask; /**<  */
} xcb_create_gc_request_t;

/** Opcode for xcb_change_gc. */
#define XCB_CHANGE_GC 56

/**
 * @brief xcb_change_gc_request_t
 **/
typedef struct xcb_change_gc_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_gcontext_t gc; /**<  */
    uint32_t       value_mask; /**<  */
} xcb_change_gc_request_t;

/** Opcode for xcb_copy_gc. */
#define XCB_COPY_GC 57

/**
 * @brief xcb_copy_gc_request_t
 **/
typedef struct xcb_copy_gc_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_gcontext_t src_gc; /**<  */
    xcb_gcontext_t dst_gc; /**<  */
    uint32_t       value_mask; /**<  */
} xcb_copy_gc_request_t;

/** Opcode for xcb_set_dashes. */
#define XCB_SET_DASHES 58

/**
 * @brief xcb_set_dashes_request_t
 **/
typedef struct xcb_set_dashes_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_gcontext_t gc; /**<  */
    uint16_t       dash_offset; /**<  */
    uint16_t       dashes_len; /**<  */
} xcb_set_dashes_request_t;

typedef enum xcb_clip_ordering_t {
    XCB_CLIP_ORDERING_UNSORTED = 0,
    XCB_CLIP_ORDERING_Y_SORTED = 1,
    XCB_CLIP_ORDERING_YX_SORTED = 2,
    XCB_CLIP_ORDERING_YX_BANDED = 3
} xcb_clip_ordering_t;

/** Opcode for xcb_set_clip_rectangles. */
#define XCB_SET_CLIP_RECTANGLES 59

/**
 * @brief xcb_set_clip_rectangles_request_t
 **/
typedef struct xcb_set_clip_rectangles_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        ordering; /**<  */
    uint16_t       length; /**<  */
    xcb_gcontext_t gc; /**<  */
    int16_t        clip_x_origin; /**<  */
    int16_t        clip_y_origin; /**<  */
} xcb_set_clip_rectangles_request_t;

/** Opcode for xcb_free_gc. */
#define XCB_FREE_GC 60

/**
 * @brief xcb_free_gc_request_t
 **/
typedef struct xcb_free_gc_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_gcontext_t gc; /**<  */
} xcb_free_gc_request_t;

/** Opcode for xcb_clear_area. */
#define XCB_CLEAR_AREA 61

/**
 * @brief xcb_clear_area_request_t
 **/
typedef struct xcb_clear_area_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      exposures; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
    int16_t      x; /**<  */
    int16_t      y; /**<  */
    uint16_t     width; /**<  */
    uint16_t     height; /**<  */
} xcb_clear_area_request_t;

/** Opcode for xcb_copy_area. */
#define XCB_COPY_AREA 62

/**
 * @brief xcb_copy_area_request_t
 **/
typedef struct xcb_copy_area_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t src_drawable; /**<  */
    xcb_drawable_t dst_drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
    int16_t        src_x; /**<  */
    int16_t        src_y; /**<  */
    int16_t        dst_x; /**<  */
    int16_t        dst_y; /**<  */
    uint16_t       width; /**<  */
    uint16_t       height; /**<  */
} xcb_copy_area_request_t;

/** Opcode for xcb_copy_plane. */
#define XCB_COPY_PLANE 63

/**
 * @brief xcb_copy_plane_request_t
 **/
typedef struct xcb_copy_plane_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t src_drawable; /**<  */
    xcb_drawable_t dst_drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
    int16_t        src_x; /**<  */
    int16_t        src_y; /**<  */
    int16_t        dst_x; /**<  */
    int16_t        dst_y; /**<  */
    uint16_t       width; /**<  */
    uint16_t       height; /**<  */
    uint32_t       bit_plane; /**<  */
} xcb_copy_plane_request_t;

typedef enum xcb_coord_mode_t {
    XCB_COORD_MODE_ORIGIN = 0,
    XCB_COORD_MODE_PREVIOUS = 1
} xcb_coord_mode_t;

/** Opcode for xcb_poly_point. */
#define XCB_POLY_POINT 64

/**
 * @brief xcb_poly_point_request_t
 **/
typedef struct xcb_poly_point_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        coordinate_mode; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
} xcb_poly_point_request_t;

/** Opcode for xcb_poly_line. */
#define XCB_POLY_LINE 65

/**
 * @brief xcb_poly_line_request_t
 **/
typedef struct xcb_poly_line_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        coordinate_mode; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
} xcb_poly_line_request_t;

/**
 * @brief xcb_segment_t
 **/
typedef struct xcb_segment_t {
    int16_t x1; /**<  */
    int16_t y1; /**<  */
    int16_t x2; /**<  */
    int16_t y2; /**<  */
} xcb_segment_t;

/**
 * @brief xcb_segment_iterator_t
 **/
typedef struct xcb_segment_iterator_t {
    xcb_segment_t *data; /**<  */
    int            rem; /**<  */
    int            index; /**<  */
} xcb_segment_iterator_t;

/** Opcode for xcb_poly_segment. */
#define XCB_POLY_SEGMENT 66

/**
 * @brief xcb_poly_segment_request_t
 **/
typedef struct xcb_poly_segment_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
} xcb_poly_segment_request_t;

/** Opcode for xcb_poly_rectangle. */
#define XCB_POLY_RECTANGLE 67

/**
 * @brief xcb_poly_rectangle_request_t
 **/
typedef struct xcb_poly_rectangle_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
} xcb_poly_rectangle_request_t;

/** Opcode for xcb_poly_arc. */
#define XCB_POLY_ARC 68

/**
 * @brief xcb_poly_arc_request_t
 **/
typedef struct xcb_poly_arc_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
} xcb_poly_arc_request_t;

typedef enum xcb_poly_shape_t {
    XCB_POLY_SHAPE_COMPLEX = 0,
    XCB_POLY_SHAPE_NONCONVEX = 1,
    XCB_POLY_SHAPE_CONVEX = 2
} xcb_poly_shape_t;

/** Opcode for xcb_fill_poly. */
#define XCB_FILL_POLY 69

/**
 * @brief xcb_fill_poly_request_t
 **/
typedef struct xcb_fill_poly_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
    uint8_t        shape; /**<  */
    uint8_t        coordinate_mode; /**<  */
    uint8_t        pad1[2]; /**<  */
} xcb_fill_poly_request_t;

/** Opcode for xcb_poly_fill_rectangle. */
#define XCB_POLY_FILL_RECTANGLE 70

/**
 * @brief xcb_poly_fill_rectangle_request_t
 **/
typedef struct xcb_poly_fill_rectangle_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
} xcb_poly_fill_rectangle_request_t;

/** Opcode for xcb_poly_fill_arc. */
#define XCB_POLY_FILL_ARC 71

/**
 * @brief xcb_poly_fill_arc_request_t
 **/
typedef struct xcb_poly_fill_arc_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
} xcb_poly_fill_arc_request_t;

typedef enum xcb_image_format_t {
    XCB_IMAGE_FORMAT_XY_BITMAP = 0,
    XCB_IMAGE_FORMAT_XY_PIXMAP = 1,
    XCB_IMAGE_FORMAT_Z_PIXMAP = 2
} xcb_image_format_t;

/** Opcode for xcb_put_image. */
#define XCB_PUT_IMAGE 72

/**
 * @brief xcb_put_image_request_t
 **/
typedef struct xcb_put_image_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        format; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
    uint16_t       width; /**<  */
    uint16_t       height; /**<  */
    int16_t        dst_x; /**<  */
    int16_t        dst_y; /**<  */
    uint8_t        left_pad; /**<  */
    uint8_t        depth; /**<  */
    uint8_t        pad0[2]; /**<  */
} xcb_put_image_request_t;

/**
 * @brief xcb_get_image_cookie_t
 **/
typedef struct xcb_get_image_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_image_cookie_t;

/** Opcode for xcb_get_image. */
#define XCB_GET_IMAGE 73

/**
 * @brief xcb_get_image_request_t
 **/
typedef struct xcb_get_image_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        format; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    int16_t        x; /**<  */
    int16_t        y; /**<  */
    uint16_t       width; /**<  */
    uint16_t       height; /**<  */
    uint32_t       plane_mask; /**<  */
} xcb_get_image_request_t;

/**
 * @brief xcb_get_image_reply_t
 **/
typedef struct xcb_get_image_reply_t {
    uint8_t        response_type; /**<  */
    uint8_t        depth; /**<  */
    uint16_t       sequence; /**<  */
    uint32_t       length; /**<  */
    xcb_visualid_t visual; /**<  */
    uint8_t        pad0[20]; /**<  */
} xcb_get_image_reply_t;

/** Opcode for xcb_poly_text_8. */
#define XCB_POLY_TEXT_8 74

/**
 * @brief xcb_poly_text_8_request_t
 **/
typedef struct xcb_poly_text_8_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
    int16_t        x; /**<  */
    int16_t        y; /**<  */
} xcb_poly_text_8_request_t;

/** Opcode for xcb_poly_text_16. */
#define XCB_POLY_TEXT_16 75

/**
 * @brief xcb_poly_text_16_request_t
 **/
typedef struct xcb_poly_text_16_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
    int16_t        x; /**<  */
    int16_t        y; /**<  */
} xcb_poly_text_16_request_t;

/** Opcode for xcb_image_text_8. */
#define XCB_IMAGE_TEXT_8 76

/**
 * @brief xcb_image_text_8_request_t
 **/
typedef struct xcb_image_text_8_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        string_len; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
    int16_t        x; /**<  */
    int16_t        y; /**<  */
} xcb_image_text_8_request_t;

/** Opcode for xcb_image_text_16. */
#define XCB_IMAGE_TEXT_16 77

/**
 * @brief xcb_image_text_16_request_t
 **/
typedef struct xcb_image_text_16_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        string_len; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    xcb_gcontext_t gc; /**<  */
    int16_t        x; /**<  */
    int16_t        y; /**<  */
} xcb_image_text_16_request_t;

typedef enum xcb_colormap_alloc_t {
    XCB_COLORMAP_ALLOC_NONE = 0,
    XCB_COLORMAP_ALLOC_ALL = 1
} xcb_colormap_alloc_t;

/** Opcode for xcb_create_colormap. */
#define XCB_CREATE_COLORMAP 78

/**
 * @brief xcb_create_colormap_request_t
 **/
typedef struct xcb_create_colormap_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        alloc; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t mid; /**<  */
    xcb_window_t   window; /**<  */
    xcb_visualid_t visual; /**<  */
} xcb_create_colormap_request_t;

/** Opcode for xcb_free_colormap. */
#define XCB_FREE_COLORMAP 79

/**
 * @brief xcb_free_colormap_request_t
 **/
typedef struct xcb_free_colormap_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
} xcb_free_colormap_request_t;

/** Opcode for xcb_copy_colormap_and_free. */
#define XCB_COPY_COLORMAP_AND_FREE 80

/**
 * @brief xcb_copy_colormap_and_free_request_t
 **/
typedef struct xcb_copy_colormap_and_free_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t mid; /**<  */
    xcb_colormap_t src_cmap; /**<  */
} xcb_copy_colormap_and_free_request_t;

/** Opcode for xcb_install_colormap. */
#define XCB_INSTALL_COLORMAP 81

/**
 * @brief xcb_install_colormap_request_t
 **/
typedef struct xcb_install_colormap_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
} xcb_install_colormap_request_t;

/** Opcode for xcb_uninstall_colormap. */
#define XCB_UNINSTALL_COLORMAP 82

/**
 * @brief xcb_uninstall_colormap_request_t
 **/
typedef struct xcb_uninstall_colormap_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
} xcb_uninstall_colormap_request_t;

/**
 * @brief xcb_list_installed_colormaps_cookie_t
 **/
typedef struct xcb_list_installed_colormaps_cookie_t {
    unsigned int sequence; /**<  */
} xcb_list_installed_colormaps_cookie_t;

/** Opcode for xcb_list_installed_colormaps. */
#define XCB_LIST_INSTALLED_COLORMAPS 83

/**
 * @brief xcb_list_installed_colormaps_request_t
 **/
typedef struct xcb_list_installed_colormaps_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
} xcb_list_installed_colormaps_request_t;

/**
 * @brief xcb_list_installed_colormaps_reply_t
 **/
typedef struct xcb_list_installed_colormaps_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t cmaps_len; /**<  */
    uint8_t  pad1[22]; /**<  */
} xcb_list_installed_colormaps_reply_t;

/**
 * @brief xcb_alloc_color_cookie_t
 **/
typedef struct xcb_alloc_color_cookie_t {
    unsigned int sequence; /**<  */
} xcb_alloc_color_cookie_t;

/** Opcode for xcb_alloc_color. */
#define XCB_ALLOC_COLOR 84

/**
 * @brief xcb_alloc_color_request_t
 **/
typedef struct xcb_alloc_color_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
    uint16_t       red; /**<  */
    uint16_t       green; /**<  */
    uint16_t       blue; /**<  */
    uint8_t        pad1[2]; /**<  */
} xcb_alloc_color_request_t;

/**
 * @brief xcb_alloc_color_reply_t
 **/
typedef struct xcb_alloc_color_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t red; /**<  */
    uint16_t green; /**<  */
    uint16_t blue; /**<  */
    uint8_t  pad1[2]; /**<  */
    uint32_t pixel; /**<  */
} xcb_alloc_color_reply_t;

/**
 * @brief xcb_alloc_named_color_cookie_t
 **/
typedef struct xcb_alloc_named_color_cookie_t {
    unsigned int sequence; /**<  */
} xcb_alloc_named_color_cookie_t;

/** Opcode for xcb_alloc_named_color. */
#define XCB_ALLOC_NAMED_COLOR 85

/**
 * @brief xcb_alloc_named_color_request_t
 **/
typedef struct xcb_alloc_named_color_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
    uint16_t       name_len; /**<  */
    uint8_t        pad1[2]; /**<  */
} xcb_alloc_named_color_request_t;

/**
 * @brief xcb_alloc_named_color_reply_t
 **/
typedef struct xcb_alloc_named_color_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint32_t pixel; /**<  */
    uint16_t exact_red; /**<  */
    uint16_t exact_green; /**<  */
    uint16_t exact_blue; /**<  */
    uint16_t visual_red; /**<  */
    uint16_t visual_green; /**<  */
    uint16_t visual_blue; /**<  */
} xcb_alloc_named_color_reply_t;

/**
 * @brief xcb_alloc_color_cells_cookie_t
 **/
typedef struct xcb_alloc_color_cells_cookie_t {
    unsigned int sequence; /**<  */
} xcb_alloc_color_cells_cookie_t;

/** Opcode for xcb_alloc_color_cells. */
#define XCB_ALLOC_COLOR_CELLS 86

/**
 * @brief xcb_alloc_color_cells_request_t
 **/
typedef struct xcb_alloc_color_cells_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        contiguous; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
    uint16_t       colors; /**<  */
    uint16_t       planes; /**<  */
} xcb_alloc_color_cells_request_t;

/**
 * @brief xcb_alloc_color_cells_reply_t
 **/
typedef struct xcb_alloc_color_cells_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t pixels_len; /**<  */
    uint16_t masks_len; /**<  */
    uint8_t  pad1[20]; /**<  */
} xcb_alloc_color_cells_reply_t;

/**
 * @brief xcb_alloc_color_planes_cookie_t
 **/
typedef struct xcb_alloc_color_planes_cookie_t {
    unsigned int sequence; /**<  */
} xcb_alloc_color_planes_cookie_t;

/** Opcode for xcb_alloc_color_planes. */
#define XCB_ALLOC_COLOR_PLANES 87

/**
 * @brief xcb_alloc_color_planes_request_t
 **/
typedef struct xcb_alloc_color_planes_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        contiguous; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
    uint16_t       colors; /**<  */
    uint16_t       reds; /**<  */
    uint16_t       greens; /**<  */
    uint16_t       blues; /**<  */
} xcb_alloc_color_planes_request_t;

/**
 * @brief xcb_alloc_color_planes_reply_t
 **/
typedef struct xcb_alloc_color_planes_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t pixels_len; /**<  */
    uint8_t  pad1[2]; /**<  */
    uint32_t red_mask; /**<  */
    uint32_t green_mask; /**<  */
    uint32_t blue_mask; /**<  */
    uint8_t  pad2[8]; /**<  */
} xcb_alloc_color_planes_reply_t;

/** Opcode for xcb_free_colors. */
#define XCB_FREE_COLORS 88

/**
 * @brief xcb_free_colors_request_t
 **/
typedef struct xcb_free_colors_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
    uint32_t       plane_mask; /**<  */
} xcb_free_colors_request_t;

typedef enum xcb_color_flag_t {
    XCB_COLOR_FLAG_RED = 1,
    XCB_COLOR_FLAG_GREEN = 2,
    XCB_COLOR_FLAG_BLUE = 4
} xcb_color_flag_t;

/**
 * @brief xcb_coloritem_t
 **/
typedef struct xcb_coloritem_t {
    uint32_t pixel; /**<  */
    uint16_t red; /**<  */
    uint16_t green; /**<  */
    uint16_t blue; /**<  */
    uint8_t  flags; /**<  */
    uint8_t  pad0; /**<  */
} xcb_coloritem_t;

/**
 * @brief xcb_coloritem_iterator_t
 **/
typedef struct xcb_coloritem_iterator_t {
    xcb_coloritem_t *data; /**<  */
    int              rem; /**<  */
    int              index; /**<  */
} xcb_coloritem_iterator_t;

/** Opcode for xcb_store_colors. */
#define XCB_STORE_COLORS 89

/**
 * @brief xcb_store_colors_request_t
 **/
typedef struct xcb_store_colors_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
} xcb_store_colors_request_t;

/** Opcode for xcb_store_named_color. */
#define XCB_STORE_NAMED_COLOR 90

/**
 * @brief xcb_store_named_color_request_t
 **/
typedef struct xcb_store_named_color_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        flags; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
    uint32_t       pixel; /**<  */
    uint16_t       name_len; /**<  */
    uint8_t        pad0[2]; /**<  */
} xcb_store_named_color_request_t;

/**
 * @brief xcb_rgb_t
 **/
typedef struct xcb_rgb_t {
    uint16_t red; /**<  */
    uint16_t green; /**<  */
    uint16_t blue; /**<  */
    uint8_t  pad0[2]; /**<  */
} xcb_rgb_t;

/**
 * @brief xcb_rgb_iterator_t
 **/
typedef struct xcb_rgb_iterator_t {
    xcb_rgb_t *data; /**<  */
    int        rem; /**<  */
    int        index; /**<  */
} xcb_rgb_iterator_t;

/**
 * @brief xcb_query_colors_cookie_t
 **/
typedef struct xcb_query_colors_cookie_t {
    unsigned int sequence; /**<  */
} xcb_query_colors_cookie_t;

/** Opcode for xcb_query_colors. */
#define XCB_QUERY_COLORS 91

/**
 * @brief xcb_query_colors_request_t
 **/
typedef struct xcb_query_colors_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
} xcb_query_colors_request_t;

/**
 * @brief xcb_query_colors_reply_t
 **/
typedef struct xcb_query_colors_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t colors_len; /**<  */
    uint8_t  pad1[22]; /**<  */
} xcb_query_colors_reply_t;

/**
 * @brief xcb_lookup_color_cookie_t
 **/
typedef struct xcb_lookup_color_cookie_t {
    unsigned int sequence; /**<  */
} xcb_lookup_color_cookie_t;

/** Opcode for xcb_lookup_color. */
#define XCB_LOOKUP_COLOR 92

/**
 * @brief xcb_lookup_color_request_t
 **/
typedef struct xcb_lookup_color_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        pad0; /**<  */
    uint16_t       length; /**<  */
    xcb_colormap_t cmap; /**<  */
    uint16_t       name_len; /**<  */
    uint8_t        pad1[2]; /**<  */
} xcb_lookup_color_request_t;

/**
 * @brief xcb_lookup_color_reply_t
 **/
typedef struct xcb_lookup_color_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t exact_red; /**<  */
    uint16_t exact_green; /**<  */
    uint16_t exact_blue; /**<  */
    uint16_t visual_red; /**<  */
    uint16_t visual_green; /**<  */
    uint16_t visual_blue; /**<  */
} xcb_lookup_color_reply_t;

typedef enum xcb_pixmap_enum_t {
    XCB_PIXMAP_NONE = 0
} xcb_pixmap_enum_t;

/** Opcode for xcb_create_cursor. */
#define XCB_CREATE_CURSOR 93

/**
 * @brief xcb_create_cursor_request_t
 **/
typedef struct xcb_create_cursor_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_cursor_t cid; /**<  */
    xcb_pixmap_t source; /**<  */
    xcb_pixmap_t mask; /**<  */
    uint16_t     fore_red; /**<  */
    uint16_t     fore_green; /**<  */
    uint16_t     fore_blue; /**<  */
    uint16_t     back_red; /**<  */
    uint16_t     back_green; /**<  */
    uint16_t     back_blue; /**<  */
    uint16_t     x; /**<  */
    uint16_t     y; /**<  */
} xcb_create_cursor_request_t;

typedef enum xcb_font_enum_t {
    XCB_FONT_NONE = 0
} xcb_font_enum_t;

/** Opcode for xcb_create_glyph_cursor. */
#define XCB_CREATE_GLYPH_CURSOR 94

/**
 * @brief xcb_create_glyph_cursor_request_t
 **/
typedef struct xcb_create_glyph_cursor_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_cursor_t cid; /**<  */
    xcb_font_t   source_font; /**<  */
    xcb_font_t   mask_font; /**<  */
    uint16_t     source_char; /**<  */
    uint16_t     mask_char; /**<  */
    uint16_t     fore_red; /**<  */
    uint16_t     fore_green; /**<  */
    uint16_t     fore_blue; /**<  */
    uint16_t     back_red; /**<  */
    uint16_t     back_green; /**<  */
    uint16_t     back_blue; /**<  */
} xcb_create_glyph_cursor_request_t;

/** Opcode for xcb_free_cursor. */
#define XCB_FREE_CURSOR 95

/**
 * @brief xcb_free_cursor_request_t
 **/
typedef struct xcb_free_cursor_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_cursor_t cursor; /**<  */
} xcb_free_cursor_request_t;

/** Opcode for xcb_recolor_cursor. */
#define XCB_RECOLOR_CURSOR 96

/**
 * @brief xcb_recolor_cursor_request_t
 **/
typedef struct xcb_recolor_cursor_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_cursor_t cursor; /**<  */
    uint16_t     fore_red; /**<  */
    uint16_t     fore_green; /**<  */
    uint16_t     fore_blue; /**<  */
    uint16_t     back_red; /**<  */
    uint16_t     back_green; /**<  */
    uint16_t     back_blue; /**<  */
} xcb_recolor_cursor_request_t;

typedef enum xcb_query_shape_of_t {
    XCB_QUERY_SHAPE_OF_LARGEST_CURSOR = 0,
    XCB_QUERY_SHAPE_OF_FASTEST_TILE = 1,
    XCB_QUERY_SHAPE_OF_FASTEST_STIPPLE = 2
} xcb_query_shape_of_t;

/**
 * @brief xcb_query_best_size_cookie_t
 **/
typedef struct xcb_query_best_size_cookie_t {
    unsigned int sequence; /**<  */
} xcb_query_best_size_cookie_t;

/** Opcode for xcb_query_best_size. */
#define XCB_QUERY_BEST_SIZE 97

/**
 * @brief xcb_query_best_size_request_t
 **/
typedef struct xcb_query_best_size_request_t {
    uint8_t        major_opcode; /**<  */
    uint8_t        _class; /**<  */
    uint16_t       length; /**<  */
    xcb_drawable_t drawable; /**<  */
    uint16_t       width; /**<  */
    uint16_t       height; /**<  */
} xcb_query_best_size_request_t;

/**
 * @brief xcb_query_best_size_reply_t
 **/
typedef struct xcb_query_best_size_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t width; /**<  */
    uint16_t height; /**<  */
} xcb_query_best_size_reply_t;

/**
 * @brief xcb_query_extension_cookie_t
 **/
typedef struct xcb_query_extension_cookie_t {
    unsigned int sequence; /**<  */
} xcb_query_extension_cookie_t;

/** Opcode for xcb_query_extension. */
#define XCB_QUERY_EXTENSION 98

/**
 * @brief xcb_query_extension_request_t
 **/
typedef struct xcb_query_extension_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
    uint16_t name_len; /**<  */
    uint8_t  pad1[2]; /**<  */
} xcb_query_extension_request_t;

/**
 * @brief xcb_query_extension_reply_t
 **/
typedef struct xcb_query_extension_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint8_t  present; /**<  */
    uint8_t  major_opcode; /**<  */
    uint8_t  first_event; /**<  */
    uint8_t  first_error; /**<  */
} xcb_query_extension_reply_t;

/**
 * @brief xcb_list_extensions_cookie_t
 **/
typedef struct xcb_list_extensions_cookie_t {
    unsigned int sequence; /**<  */
} xcb_list_extensions_cookie_t;

/** Opcode for xcb_list_extensions. */
#define XCB_LIST_EXTENSIONS 99

/**
 * @brief xcb_list_extensions_request_t
 **/
typedef struct xcb_list_extensions_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_list_extensions_request_t;

/**
 * @brief xcb_list_extensions_reply_t
 **/
typedef struct xcb_list_extensions_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  names_len; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint8_t  pad0[24]; /**<  */
} xcb_list_extensions_reply_t;

/** Opcode for xcb_change_keyboard_mapping. */
#define XCB_CHANGE_KEYBOARD_MAPPING 100

/**
 * @brief xcb_change_keyboard_mapping_request_t
 **/
typedef struct xcb_change_keyboard_mapping_request_t {
    uint8_t       major_opcode; /**<  */
    uint8_t       keycode_count; /**<  */
    uint16_t      length; /**<  */
    xcb_keycode_t first_keycode; /**<  */
    uint8_t       keysyms_per_keycode; /**<  */
} xcb_change_keyboard_mapping_request_t;

/**
 * @brief xcb_get_keyboard_mapping_cookie_t
 **/
typedef struct xcb_get_keyboard_mapping_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_keyboard_mapping_cookie_t;

/** Opcode for xcb_get_keyboard_mapping. */
#define XCB_GET_KEYBOARD_MAPPING 101

/**
 * @brief xcb_get_keyboard_mapping_request_t
 **/
typedef struct xcb_get_keyboard_mapping_request_t {
    uint8_t       major_opcode; /**<  */
    uint8_t       pad0; /**<  */
    uint16_t      length; /**<  */
    xcb_keycode_t first_keycode; /**<  */
    uint8_t       count; /**<  */
} xcb_get_keyboard_mapping_request_t;

/**
 * @brief xcb_get_keyboard_mapping_reply_t
 **/
typedef struct xcb_get_keyboard_mapping_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  keysyms_per_keycode; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint8_t  pad0[24]; /**<  */
} xcb_get_keyboard_mapping_reply_t;

typedef enum xcb_kb_t {
    XCB_KB_KEY_CLICK_PERCENT = 1,
    XCB_KB_BELL_PERCENT = 2,
    XCB_KB_BELL_PITCH = 4,
    XCB_KB_BELL_DURATION = 8,
    XCB_KB_LED = 16,
    XCB_KB_LED_MODE = 32,
    XCB_KB_KEY = 64,
    XCB_KB_AUTO_REPEAT_MODE = 128
} xcb_kb_t;

typedef enum xcb_led_mode_t {
    XCB_LED_MODE_OFF = 0,
    XCB_LED_MODE_ON = 1
} xcb_led_mode_t;

typedef enum xcb_auto_repeat_mode_t {
    XCB_AUTO_REPEAT_MODE_OFF = 0,
    XCB_AUTO_REPEAT_MODE_ON = 1,
    XCB_AUTO_REPEAT_MODE_DEFAULT = 2
} xcb_auto_repeat_mode_t;

/** Opcode for xcb_change_keyboard_control. */
#define XCB_CHANGE_KEYBOARD_CONTROL 102

/**
 * @brief xcb_change_keyboard_control_request_t
 **/
typedef struct xcb_change_keyboard_control_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
    uint32_t value_mask; /**<  */
} xcb_change_keyboard_control_request_t;

/**
 * @brief xcb_get_keyboard_control_cookie_t
 **/
typedef struct xcb_get_keyboard_control_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_keyboard_control_cookie_t;

/** Opcode for xcb_get_keyboard_control. */
#define XCB_GET_KEYBOARD_CONTROL 103

/**
 * @brief xcb_get_keyboard_control_request_t
 **/
typedef struct xcb_get_keyboard_control_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_get_keyboard_control_request_t;

/**
 * @brief xcb_get_keyboard_control_reply_t
 **/
typedef struct xcb_get_keyboard_control_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  global_auto_repeat; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint32_t led_mask; /**<  */
    uint8_t  key_click_percent; /**<  */
    uint8_t  bell_percent; /**<  */
    uint16_t bell_pitch; /**<  */
    uint16_t bell_duration; /**<  */
    uint8_t  pad0[2]; /**<  */
    uint8_t  auto_repeats[32]; /**<  */
} xcb_get_keyboard_control_reply_t;

/** Opcode for xcb_bell. */
#define XCB_BELL 104

/**
 * @brief xcb_bell_request_t
 **/
typedef struct xcb_bell_request_t {
    uint8_t  major_opcode; /**<  */
    int8_t   percent; /**<  */
    uint16_t length; /**<  */
} xcb_bell_request_t;

/** Opcode for xcb_change_pointer_control. */
#define XCB_CHANGE_POINTER_CONTROL 105

/**
 * @brief xcb_change_pointer_control_request_t
 **/
typedef struct xcb_change_pointer_control_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
    int16_t  acceleration_numerator; /**<  */
    int16_t  acceleration_denominator; /**<  */
    int16_t  threshold; /**<  */
    uint8_t  do_acceleration; /**<  */
    uint8_t  do_threshold; /**<  */
} xcb_change_pointer_control_request_t;

/**
 * @brief xcb_get_pointer_control_cookie_t
 **/
typedef struct xcb_get_pointer_control_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_pointer_control_cookie_t;

/** Opcode for xcb_get_pointer_control. */
#define XCB_GET_POINTER_CONTROL 106

/**
 * @brief xcb_get_pointer_control_request_t
 **/
typedef struct xcb_get_pointer_control_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_get_pointer_control_request_t;

/**
 * @brief xcb_get_pointer_control_reply_t
 **/
typedef struct xcb_get_pointer_control_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t acceleration_numerator; /**<  */
    uint16_t acceleration_denominator; /**<  */
    uint16_t threshold; /**<  */
    uint8_t  pad1[18]; /**<  */
} xcb_get_pointer_control_reply_t;

typedef enum xcb_blanking_t {
    XCB_BLANKING_NOT_PREFERRED = 0,
    XCB_BLANKING_PREFERRED = 1,
    XCB_BLANKING_DEFAULT = 2
} xcb_blanking_t;

typedef enum xcb_exposures_t {
    XCB_EXPOSURES_NOT_ALLOWED = 0,
    XCB_EXPOSURES_ALLOWED = 1,
    XCB_EXPOSURES_DEFAULT = 2
} xcb_exposures_t;

/** Opcode for xcb_set_screen_saver. */
#define XCB_SET_SCREEN_SAVER 107

/**
 * @brief xcb_set_screen_saver_request_t
 **/
typedef struct xcb_set_screen_saver_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
    int16_t  timeout; /**<  */
    int16_t  interval; /**<  */
    uint8_t  prefer_blanking; /**<  */
    uint8_t  allow_exposures; /**<  */
} xcb_set_screen_saver_request_t;

/**
 * @brief xcb_get_screen_saver_cookie_t
 **/
typedef struct xcb_get_screen_saver_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_screen_saver_cookie_t;

/** Opcode for xcb_get_screen_saver. */
#define XCB_GET_SCREEN_SAVER 108

/**
 * @brief xcb_get_screen_saver_request_t
 **/
typedef struct xcb_get_screen_saver_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_get_screen_saver_request_t;

/**
 * @brief xcb_get_screen_saver_reply_t
 **/
typedef struct xcb_get_screen_saver_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t timeout; /**<  */
    uint16_t interval; /**<  */
    uint8_t  prefer_blanking; /**<  */
    uint8_t  allow_exposures; /**<  */
    uint8_t  pad1[18]; /**<  */
} xcb_get_screen_saver_reply_t;

typedef enum xcb_host_mode_t {
    XCB_HOST_MODE_INSERT = 0,
    XCB_HOST_MODE_DELETE = 1
} xcb_host_mode_t;

typedef enum xcb_family_t {
    XCB_FAMILY_INTERNET = 0,
    XCB_FAMILY_DECNET = 1,
    XCB_FAMILY_CHAOS = 2,
    XCB_FAMILY_SERVER_INTERPRETED = 5,
    XCB_FAMILY_INTERNET_6 = 6
} xcb_family_t;

/** Opcode for xcb_change_hosts. */
#define XCB_CHANGE_HOSTS 109

/**
 * @brief xcb_change_hosts_request_t
 **/
typedef struct xcb_change_hosts_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  mode; /**<  */
    uint16_t length; /**<  */
    uint8_t  family; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t address_len; /**<  */
} xcb_change_hosts_request_t;

/**
 * @brief xcb_host_t
 **/
typedef struct xcb_host_t {
    uint8_t  family; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t address_len; /**<  */
} xcb_host_t;

/**
 * @brief xcb_host_iterator_t
 **/
typedef struct xcb_host_iterator_t {
    xcb_host_t *data; /**<  */
    int         rem; /**<  */
    int         index; /**<  */
} xcb_host_iterator_t;

/**
 * @brief xcb_list_hosts_cookie_t
 **/
typedef struct xcb_list_hosts_cookie_t {
    unsigned int sequence; /**<  */
} xcb_list_hosts_cookie_t;

/** Opcode for xcb_list_hosts. */
#define XCB_LIST_HOSTS 110

/**
 * @brief xcb_list_hosts_request_t
 **/
typedef struct xcb_list_hosts_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_list_hosts_request_t;

/**
 * @brief xcb_list_hosts_reply_t
 **/
typedef struct xcb_list_hosts_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  mode; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t hosts_len; /**<  */
    uint8_t  pad0[22]; /**<  */
} xcb_list_hosts_reply_t;

typedef enum xcb_access_control_t {
    XCB_ACCESS_CONTROL_DISABLE = 0,
    XCB_ACCESS_CONTROL_ENABLE = 1
} xcb_access_control_t;

/** Opcode for xcb_set_access_control. */
#define XCB_SET_ACCESS_CONTROL 111

/**
 * @brief xcb_set_access_control_request_t
 **/
typedef struct xcb_set_access_control_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  mode; /**<  */
    uint16_t length; /**<  */
} xcb_set_access_control_request_t;

typedef enum xcb_close_down_t {
    XCB_CLOSE_DOWN_DESTROY_ALL = 0,
    XCB_CLOSE_DOWN_RETAIN_PERMANENT = 1,
    XCB_CLOSE_DOWN_RETAIN_TEMPORARY = 2
} xcb_close_down_t;

/** Opcode for xcb_set_close_down_mode. */
#define XCB_SET_CLOSE_DOWN_MODE 112

/**
 * @brief xcb_set_close_down_mode_request_t
 **/
typedef struct xcb_set_close_down_mode_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  mode; /**<  */
    uint16_t length; /**<  */
} xcb_set_close_down_mode_request_t;

typedef enum xcb_kill_t {
    XCB_KILL_ALL_TEMPORARY = 0
} xcb_kill_t;

/** Opcode for xcb_kill_client. */
#define XCB_KILL_CLIENT 113

/**
 * @brief xcb_kill_client_request_t
 **/
typedef struct xcb_kill_client_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
    uint32_t resource; /**<  */
} xcb_kill_client_request_t;

/** Opcode for xcb_rotate_properties. */
#define XCB_ROTATE_PROPERTIES 114

/**
 * @brief xcb_rotate_properties_request_t
 **/
typedef struct xcb_rotate_properties_request_t {
    uint8_t      major_opcode; /**<  */
    uint8_t      pad0; /**<  */
    uint16_t     length; /**<  */
    xcb_window_t window; /**<  */
    uint16_t     atoms_len; /**<  */
    int16_t      delta; /**<  */
} xcb_rotate_properties_request_t;

typedef enum xcb_screen_saver_t {
    XCB_SCREEN_SAVER_RESET = 0,
    XCB_SCREEN_SAVER_ACTIVE = 1
} xcb_screen_saver_t;

/** Opcode for xcb_force_screen_saver. */
#define XCB_FORCE_SCREEN_SAVER 115

/**
 * @brief xcb_force_screen_saver_request_t
 **/
typedef struct xcb_force_screen_saver_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  mode; /**<  */
    uint16_t length; /**<  */
} xcb_force_screen_saver_request_t;

typedef enum xcb_mapping_status_t {
    XCB_MAPPING_STATUS_SUCCESS = 0,
    XCB_MAPPING_STATUS_BUSY = 1,
    XCB_MAPPING_STATUS_FAILURE = 2
} xcb_mapping_status_t;

/**
 * @brief xcb_set_pointer_mapping_cookie_t
 **/
typedef struct xcb_set_pointer_mapping_cookie_t {
    unsigned int sequence; /**<  */
} xcb_set_pointer_mapping_cookie_t;

/** Opcode for xcb_set_pointer_mapping. */
#define XCB_SET_POINTER_MAPPING 116

/**
 * @brief xcb_set_pointer_mapping_request_t
 **/
typedef struct xcb_set_pointer_mapping_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  map_len; /**<  */
    uint16_t length; /**<  */
} xcb_set_pointer_mapping_request_t;

/**
 * @brief xcb_set_pointer_mapping_reply_t
 **/
typedef struct xcb_set_pointer_mapping_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  status; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
} xcb_set_pointer_mapping_reply_t;

/**
 * @brief xcb_get_pointer_mapping_cookie_t
 **/
typedef struct xcb_get_pointer_mapping_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_pointer_mapping_cookie_t;

/** Opcode for xcb_get_pointer_mapping. */
#define XCB_GET_POINTER_MAPPING 117

/**
 * @brief xcb_get_pointer_mapping_request_t
 **/
typedef struct xcb_get_pointer_mapping_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_get_pointer_mapping_request_t;

/**
 * @brief xcb_get_pointer_mapping_reply_t
 **/
typedef struct xcb_get_pointer_mapping_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  map_len; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint8_t  pad0[24]; /**<  */
} xcb_get_pointer_mapping_reply_t;

typedef enum xcb_map_index_t {
    XCB_MAP_INDEX_SHIFT = 0,
    XCB_MAP_INDEX_LOCK = 1,
    XCB_MAP_INDEX_CONTROL = 2,
    XCB_MAP_INDEX_1 = 3,
    XCB_MAP_INDEX_2 = 4,
    XCB_MAP_INDEX_3 = 5,
    XCB_MAP_INDEX_4 = 6,
    XCB_MAP_INDEX_5 = 7
} xcb_map_index_t;

/**
 * @brief xcb_set_modifier_mapping_cookie_t
 **/
typedef struct xcb_set_modifier_mapping_cookie_t {
    unsigned int sequence; /**<  */
} xcb_set_modifier_mapping_cookie_t;

/** Opcode for xcb_set_modifier_mapping. */
#define XCB_SET_MODIFIER_MAPPING 118

/**
 * @brief xcb_set_modifier_mapping_request_t
 **/
typedef struct xcb_set_modifier_mapping_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  keycodes_per_modifier; /**<  */
    uint16_t length; /**<  */
} xcb_set_modifier_mapping_request_t;

/**
 * @brief xcb_set_modifier_mapping_reply_t
 **/
typedef struct xcb_set_modifier_mapping_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  status; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
} xcb_set_modifier_mapping_reply_t;

/**
 * @brief xcb_get_modifier_mapping_cookie_t
 **/
typedef struct xcb_get_modifier_mapping_cookie_t {
    unsigned int sequence; /**<  */
} xcb_get_modifier_mapping_cookie_t;

/** Opcode for xcb_get_modifier_mapping. */
#define XCB_GET_MODIFIER_MAPPING 119

/**
 * @brief xcb_get_modifier_mapping_request_t
 **/
typedef struct xcb_get_modifier_mapping_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_get_modifier_mapping_request_t;

/**
 * @brief xcb_get_modifier_mapping_reply_t
 **/
typedef struct xcb_get_modifier_mapping_reply_t {
    uint8_t  response_type; /**<  */
    uint8_t  keycodes_per_modifier; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint8_t  pad0[24]; /**<  */
} xcb_get_modifier_mapping_reply_t;

/** Opcode for xcb_no_operation. */
#define XCB_NO_OPERATION 127

/**
 * @brief xcb_no_operation_request_t
 **/
typedef struct xcb_no_operation_request_t {
    uint8_t  major_opcode; /**<  */
    uint8_t  pad0; /**<  */
    uint16_t length; /**<  */
} xcb_no_operation_request_t;

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_char2b_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_char2b_t)
 */

/*****************************************************************************
 **
 ** void xcb_char2b_next
 ** 
 ** @param xcb_char2b_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_char2b_next (xcb_char2b_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_char2b_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_char2b_end
 ** 
 ** @param xcb_char2b_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_char2b_end (xcb_char2b_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_window_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_window_t)
 */

/*****************************************************************************
 **
 ** void xcb_window_next
 ** 
 ** @param xcb_window_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_window_next (xcb_window_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_window_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_window_end
 ** 
 ** @param xcb_window_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_window_end (xcb_window_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_pixmap_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_pixmap_t)
 */

/*****************************************************************************
 **
 ** void xcb_pixmap_next
 ** 
 ** @param xcb_pixmap_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_pixmap_next (xcb_pixmap_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_pixmap_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_pixmap_end
 ** 
 ** @param xcb_pixmap_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_pixmap_end (xcb_pixmap_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_cursor_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_cursor_t)
 */

/*****************************************************************************
 **
 ** void xcb_cursor_next
 ** 
 ** @param xcb_cursor_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_cursor_next (xcb_cursor_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_cursor_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_cursor_end
 ** 
 ** @param xcb_cursor_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_cursor_end (xcb_cursor_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_font_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_font_t)
 */

/*****************************************************************************
 **
 ** void xcb_font_next
 ** 
 ** @param xcb_font_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_font_next (xcb_font_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_font_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_font_end
 ** 
 ** @param xcb_font_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_font_end (xcb_font_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_gcontext_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_gcontext_t)
 */

/*****************************************************************************
 **
 ** void xcb_gcontext_next
 ** 
 ** @param xcb_gcontext_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_gcontext_next (xcb_gcontext_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_gcontext_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_gcontext_end
 ** 
 ** @param xcb_gcontext_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_gcontext_end (xcb_gcontext_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_colormap_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_colormap_t)
 */

/*****************************************************************************
 **
 ** void xcb_colormap_next
 ** 
 ** @param xcb_colormap_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_colormap_next (xcb_colormap_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_colormap_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_colormap_end
 ** 
 ** @param xcb_colormap_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_colormap_end (xcb_colormap_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_atom_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_atom_t)
 */

/*****************************************************************************
 **
 ** void xcb_atom_next
 ** 
 ** @param xcb_atom_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_atom_next (xcb_atom_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_atom_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_atom_end
 ** 
 ** @param xcb_atom_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_atom_end (xcb_atom_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_drawable_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_drawable_t)
 */

/*****************************************************************************
 **
 ** void xcb_drawable_next
 ** 
 ** @param xcb_drawable_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_drawable_next (xcb_drawable_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_drawable_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_drawable_end
 ** 
 ** @param xcb_drawable_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_drawable_end (xcb_drawable_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_fontable_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_fontable_t)
 */

/*****************************************************************************
 **
 ** void xcb_fontable_next
 ** 
 ** @param xcb_fontable_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_fontable_next (xcb_fontable_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_fontable_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_fontable_end
 ** 
 ** @param xcb_fontable_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_fontable_end (xcb_fontable_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_visualid_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_visualid_t)
 */

/*****************************************************************************
 **
 ** void xcb_visualid_next
 ** 
 ** @param xcb_visualid_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_visualid_next (xcb_visualid_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_visualid_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_visualid_end
 ** 
 ** @param xcb_visualid_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_visualid_end (xcb_visualid_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_timestamp_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_timestamp_t)
 */

/*****************************************************************************
 **
 ** void xcb_timestamp_next
 ** 
 ** @param xcb_timestamp_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_timestamp_next (xcb_timestamp_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_timestamp_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_timestamp_end
 ** 
 ** @param xcb_timestamp_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_timestamp_end (xcb_timestamp_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_keysym_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_keysym_t)
 */

/*****************************************************************************
 **
 ** void xcb_keysym_next
 ** 
 ** @param xcb_keysym_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_keysym_next (xcb_keysym_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_keysym_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_keysym_end
 ** 
 ** @param xcb_keysym_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_keysym_end (xcb_keysym_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_keycode_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_keycode_t)
 */

/*****************************************************************************
 **
 ** void xcb_keycode_next
 ** 
 ** @param xcb_keycode_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_keycode_next (xcb_keycode_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_keycode_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_keycode_end
 ** 
 ** @param xcb_keycode_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_keycode_end (xcb_keycode_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_button_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_button_t)
 */

/*****************************************************************************
 **
 ** void xcb_button_next
 ** 
 ** @param xcb_button_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_button_next (xcb_button_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_button_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_button_end
 ** 
 ** @param xcb_button_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_button_end (xcb_button_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_point_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_point_t)
 */

/*****************************************************************************
 **
 ** void xcb_point_next
 ** 
 ** @param xcb_point_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_point_next (xcb_point_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_point_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_point_end
 ** 
 ** @param xcb_point_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_point_end (xcb_point_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_rectangle_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_rectangle_t)
 */

/*****************************************************************************
 **
 ** void xcb_rectangle_next
 ** 
 ** @param xcb_rectangle_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_rectangle_next (xcb_rectangle_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_rectangle_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_rectangle_end
 ** 
 ** @param xcb_rectangle_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_rectangle_end (xcb_rectangle_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_arc_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_arc_t)
 */

/*****************************************************************************
 **
 ** void xcb_arc_next
 ** 
 ** @param xcb_arc_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_arc_next (xcb_arc_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_arc_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_arc_end
 ** 
 ** @param xcb_arc_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_arc_end (xcb_arc_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_format_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_format_t)
 */

/*****************************************************************************
 **
 ** void xcb_format_next
 ** 
 ** @param xcb_format_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_format_next (xcb_format_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_format_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_format_end
 ** 
 ** @param xcb_format_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_format_end (xcb_format_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_visualtype_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_visualtype_t)
 */

/*****************************************************************************
 **
 ** void xcb_visualtype_next
 ** 
 ** @param xcb_visualtype_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_visualtype_next (xcb_visualtype_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_visualtype_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_visualtype_end
 ** 
 ** @param xcb_visualtype_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_visualtype_end (xcb_visualtype_iterator_t i  /**< */);


/*****************************************************************************
 **
 ** xcb_visualtype_t * xcb_depth_visuals
 ** 
 ** @param const xcb_depth_t *R
 ** @returns xcb_visualtype_t *
 **
 *****************************************************************************/
 
xcb_visualtype_t *
xcb_depth_visuals (const xcb_depth_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_depth_visuals_length
 ** 
 ** @param const xcb_depth_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_depth_visuals_length (const xcb_depth_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_visualtype_iterator_t xcb_depth_visuals_iterator
 ** 
 ** @param const xcb_depth_t *R
 ** @returns xcb_visualtype_iterator_t
 **
 *****************************************************************************/
 
xcb_visualtype_iterator_t
xcb_depth_visuals_iterator (const xcb_depth_t *R  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_depth_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_depth_t)
 */

/*****************************************************************************
 **
 ** void xcb_depth_next
 ** 
 ** @param xcb_depth_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_depth_next (xcb_depth_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_depth_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_depth_end
 ** 
 ** @param xcb_depth_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_depth_end (xcb_depth_iterator_t i  /**< */);


/*****************************************************************************
 **
 ** int xcb_screen_allowed_depths_length
 ** 
 ** @param const xcb_screen_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_screen_allowed_depths_length (const xcb_screen_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_depth_iterator_t xcb_screen_allowed_depths_iterator
 ** 
 ** @param const xcb_screen_t *R
 ** @returns xcb_depth_iterator_t
 **
 *****************************************************************************/
 
xcb_depth_iterator_t
xcb_screen_allowed_depths_iterator (const xcb_screen_t *R  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_screen_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_screen_t)
 */

/*****************************************************************************
 **
 ** void xcb_screen_next
 ** 
 ** @param xcb_screen_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_screen_next (xcb_screen_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_screen_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_screen_end
 ** 
 ** @param xcb_screen_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_screen_end (xcb_screen_iterator_t i  /**< */);


/*****************************************************************************
 **
 ** char * xcb_setup_request_authorization_protocol_name
 ** 
 ** @param const xcb_setup_request_t *R
 ** @returns char *
 **
 *****************************************************************************/
 
char *
xcb_setup_request_authorization_protocol_name (const xcb_setup_request_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_setup_request_authorization_protocol_name_length
 ** 
 ** @param const xcb_setup_request_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_setup_request_authorization_protocol_name_length (const xcb_setup_request_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_request_authorization_protocol_name_end
 ** 
 ** @param const xcb_setup_request_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_request_authorization_protocol_name_end (const xcb_setup_request_t *R  /**< */);


/*****************************************************************************
 **
 ** char * xcb_setup_request_authorization_protocol_data
 ** 
 ** @param const xcb_setup_request_t *R
 ** @returns char *
 **
 *****************************************************************************/
 
char *
xcb_setup_request_authorization_protocol_data (const xcb_setup_request_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_setup_request_authorization_protocol_data_length
 ** 
 ** @param const xcb_setup_request_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_setup_request_authorization_protocol_data_length (const xcb_setup_request_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_request_authorization_protocol_data_end
 ** 
 ** @param const xcb_setup_request_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_request_authorization_protocol_data_end (const xcb_setup_request_t *R  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_setup_request_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_setup_request_t)
 */

/*****************************************************************************
 **
 ** void xcb_setup_request_next
 ** 
 ** @param xcb_setup_request_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_setup_request_next (xcb_setup_request_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_setup_request_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_request_end
 ** 
 ** @param xcb_setup_request_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_request_end (xcb_setup_request_iterator_t i  /**< */);


/*****************************************************************************
 **
 ** char * xcb_setup_failed_reason
 ** 
 ** @param const xcb_setup_failed_t *R
 ** @returns char *
 **
 *****************************************************************************/
 
char *
xcb_setup_failed_reason (const xcb_setup_failed_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_setup_failed_reason_length
 ** 
 ** @param const xcb_setup_failed_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_setup_failed_reason_length (const xcb_setup_failed_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_failed_reason_end
 ** 
 ** @param const xcb_setup_failed_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_failed_reason_end (const xcb_setup_failed_t *R  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_setup_failed_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_setup_failed_t)
 */

/*****************************************************************************
 **
 ** void xcb_setup_failed_next
 ** 
 ** @param xcb_setup_failed_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_setup_failed_next (xcb_setup_failed_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_setup_failed_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_failed_end
 ** 
 ** @param xcb_setup_failed_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_failed_end (xcb_setup_failed_iterator_t i  /**< */);


/*****************************************************************************
 **
 ** char * xcb_setup_authenticate_reason
 ** 
 ** @param const xcb_setup_authenticate_t *R
 ** @returns char *
 **
 *****************************************************************************/
 
char *
xcb_setup_authenticate_reason (const xcb_setup_authenticate_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_setup_authenticate_reason_length
 ** 
 ** @param const xcb_setup_authenticate_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_setup_authenticate_reason_length (const xcb_setup_authenticate_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_authenticate_reason_end
 ** 
 ** @param const xcb_setup_authenticate_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_authenticate_reason_end (const xcb_setup_authenticate_t *R  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_setup_authenticate_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_setup_authenticate_t)
 */

/*****************************************************************************
 **
 ** void xcb_setup_authenticate_next
 ** 
 ** @param xcb_setup_authenticate_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_setup_authenticate_next (xcb_setup_authenticate_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_setup_authenticate_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_authenticate_end
 ** 
 ** @param xcb_setup_authenticate_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_authenticate_end (xcb_setup_authenticate_iterator_t i  /**< */);


/*****************************************************************************
 **
 ** char * xcb_setup_vendor
 ** 
 ** @param const xcb_setup_t *R
 ** @returns char *
 **
 *****************************************************************************/
 
char *
xcb_setup_vendor (const xcb_setup_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_setup_vendor_length
 ** 
 ** @param const xcb_setup_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_setup_vendor_length (const xcb_setup_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_vendor_end
 ** 
 ** @param const xcb_setup_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_vendor_end (const xcb_setup_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_format_t * xcb_setup_pixmap_formats
 ** 
 ** @param const xcb_setup_t *R
 ** @returns xcb_format_t *
 **
 *****************************************************************************/
 
xcb_format_t *
xcb_setup_pixmap_formats (const xcb_setup_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_setup_pixmap_formats_length
 ** 
 ** @param const xcb_setup_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_setup_pixmap_formats_length (const xcb_setup_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_format_iterator_t xcb_setup_pixmap_formats_iterator
 ** 
 ** @param const xcb_setup_t *R
 ** @returns xcb_format_iterator_t
 **
 *****************************************************************************/
 
xcb_format_iterator_t
xcb_setup_pixmap_formats_iterator (const xcb_setup_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_setup_roots_length
 ** 
 ** @param const xcb_setup_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_setup_roots_length (const xcb_setup_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_screen_iterator_t xcb_setup_roots_iterator
 ** 
 ** @param const xcb_setup_t *R
 ** @returns xcb_screen_iterator_t
 **
 *****************************************************************************/
 
xcb_screen_iterator_t
xcb_setup_roots_iterator (const xcb_setup_t *R  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_setup_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_setup_t)
 */

/*****************************************************************************
 **
 ** void xcb_setup_next
 ** 
 ** @param xcb_setup_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_setup_next (xcb_setup_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_setup_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_setup_end
 ** 
 ** @param xcb_setup_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_setup_end (xcb_setup_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_client_message_data_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_client_message_data_t)
 */

/*****************************************************************************
 **
 ** void xcb_client_message_data_next
 ** 
 ** @param xcb_client_message_data_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_client_message_data_next (xcb_client_message_data_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_client_message_data_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_client_message_data_end
 ** 
 ** @param xcb_client_message_data_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_client_message_data_end (xcb_client_message_data_iterator_t i  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_window_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           depth
 ** @param xcb_window_t      wid
 ** @param xcb_window_t      parent
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @param uint16_t          border_width
 ** @param uint16_t          _class
 ** @param xcb_visualid_t    visual
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_window_checked (xcb_connection_t *c  /**< */,
                           uint8_t           depth  /**< */,
                           xcb_window_t      wid  /**< */,
                           xcb_window_t      parent  /**< */,
                           int16_t           x  /**< */,
                           int16_t           y  /**< */,
                           uint16_t          width  /**< */,
                           uint16_t          height  /**< */,
                           uint16_t          border_width  /**< */,
                           uint16_t          _class  /**< */,
                           xcb_visualid_t    visual  /**< */,
                           uint32_t          value_mask  /**< */,
                           const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_window
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           depth
 ** @param xcb_window_t      wid
 ** @param xcb_window_t      parent
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @param uint16_t          border_width
 ** @param uint16_t          _class
 ** @param xcb_visualid_t    visual
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_window (xcb_connection_t *c  /**< */,
                   uint8_t           depth  /**< */,
                   xcb_window_t      wid  /**< */,
                   xcb_window_t      parent  /**< */,
                   int16_t           x  /**< */,
                   int16_t           y  /**< */,
                   uint16_t          width  /**< */,
                   uint16_t          height  /**< */,
                   uint16_t          border_width  /**< */,
                   uint16_t          _class  /**< */,
                   xcb_visualid_t    visual  /**< */,
                   uint32_t          value_mask  /**< */,
                   const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_window_attributes_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_window_attributes_checked (xcb_connection_t *c  /**< */,
                                      xcb_window_t      window  /**< */,
                                      uint32_t          value_mask  /**< */,
                                      const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_window_attributes
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_window_attributes (xcb_connection_t *c  /**< */,
                              xcb_window_t      window  /**< */,
                              uint32_t          value_mask  /**< */,
                              const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_window_attributes_cookie_t xcb_get_window_attributes
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_get_window_attributes_cookie_t
 **
 *****************************************************************************/
 
xcb_get_window_attributes_cookie_t
xcb_get_window_attributes (xcb_connection_t *c  /**< */,
                           xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_window_attributes_cookie_t xcb_get_window_attributes_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_get_window_attributes_cookie_t
 **
 *****************************************************************************/
 
xcb_get_window_attributes_cookie_t
xcb_get_window_attributes_unchecked (xcb_connection_t *c  /**< */,
                                     xcb_window_t      window  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_window_attributes_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_window_attributes_reply_t * xcb_get_window_attributes_reply
 ** 
 ** @param xcb_connection_t                    *c
 ** @param xcb_get_window_attributes_cookie_t   cookie
 ** @param xcb_generic_error_t                **e
 ** @returns xcb_get_window_attributes_reply_t *
 **
 *****************************************************************************/
 
xcb_get_window_attributes_reply_t *
xcb_get_window_attributes_reply (xcb_connection_t                    *c  /**< */,
                                 xcb_get_window_attributes_cookie_t   cookie  /**< */,
                                 xcb_generic_error_t                **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_destroy_window_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_destroy_window_checked (xcb_connection_t *c  /**< */,
                            xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_destroy_window
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_destroy_window (xcb_connection_t *c  /**< */,
                    xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_destroy_subwindows_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_destroy_subwindows_checked (xcb_connection_t *c  /**< */,
                                xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_destroy_subwindows
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_destroy_subwindows (xcb_connection_t *c  /**< */,
                        xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_save_set_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_save_set_checked (xcb_connection_t *c  /**< */,
                             uint8_t           mode  /**< */,
                             xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_save_set
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_save_set (xcb_connection_t *c  /**< */,
                     uint8_t           mode  /**< */,
                     xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_reparent_window_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param xcb_window_t      parent
 ** @param int16_t           x
 ** @param int16_t           y
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_reparent_window_checked (xcb_connection_t *c  /**< */,
                             xcb_window_t      window  /**< */,
                             xcb_window_t      parent  /**< */,
                             int16_t           x  /**< */,
                             int16_t           y  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_reparent_window
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param xcb_window_t      parent
 ** @param int16_t           x
 ** @param int16_t           y
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_reparent_window (xcb_connection_t *c  /**< */,
                     xcb_window_t      window  /**< */,
                     xcb_window_t      parent  /**< */,
                     int16_t           x  /**< */,
                     int16_t           y  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_map_window_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_map_window_checked (xcb_connection_t *c  /**< */,
                        xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_map_window
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_map_window (xcb_connection_t *c  /**< */,
                xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_map_subwindows_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_map_subwindows_checked (xcb_connection_t *c  /**< */,
                            xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_map_subwindows
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_map_subwindows (xcb_connection_t *c  /**< */,
                    xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_unmap_window_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_unmap_window_checked (xcb_connection_t *c  /**< */,
                          xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_unmap_window
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_unmap_window (xcb_connection_t *c  /**< */,
                  xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_unmap_subwindows_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_unmap_subwindows_checked (xcb_connection_t *c  /**< */,
                              xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_unmap_subwindows
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_unmap_subwindows (xcb_connection_t *c  /**< */,
                      xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_configure_window_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param uint16_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_configure_window_checked (xcb_connection_t *c  /**< */,
                              xcb_window_t      window  /**< */,
                              uint16_t          value_mask  /**< */,
                              const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_configure_window
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param uint16_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_configure_window (xcb_connection_t *c  /**< */,
                      xcb_window_t      window  /**< */,
                      uint16_t          value_mask  /**< */,
                      const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_circulate_window_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           direction
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_circulate_window_checked (xcb_connection_t *c  /**< */,
                              uint8_t           direction  /**< */,
                              xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_circulate_window
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           direction
 ** @param xcb_window_t      window
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_circulate_window (xcb_connection_t *c  /**< */,
                      uint8_t           direction  /**< */,
                      xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_geometry_cookie_t xcb_get_geometry
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @returns xcb_get_geometry_cookie_t
 **
 *****************************************************************************/
 
xcb_get_geometry_cookie_t
xcb_get_geometry (xcb_connection_t *c  /**< */,
                  xcb_drawable_t    drawable  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_geometry_cookie_t xcb_get_geometry_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @returns xcb_get_geometry_cookie_t
 **
 *****************************************************************************/
 
xcb_get_geometry_cookie_t
xcb_get_geometry_unchecked (xcb_connection_t *c  /**< */,
                            xcb_drawable_t    drawable  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_geometry_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_geometry_reply_t * xcb_get_geometry_reply
 ** 
 ** @param xcb_connection_t           *c
 ** @param xcb_get_geometry_cookie_t   cookie
 ** @param xcb_generic_error_t       **e
 ** @returns xcb_get_geometry_reply_t *
 **
 *****************************************************************************/
 
xcb_get_geometry_reply_t *
xcb_get_geometry_reply (xcb_connection_t           *c  /**< */,
                        xcb_get_geometry_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_query_tree_cookie_t xcb_query_tree
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_query_tree_cookie_t
 **
 *****************************************************************************/
 
xcb_query_tree_cookie_t
xcb_query_tree (xcb_connection_t *c  /**< */,
                xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_query_tree_cookie_t xcb_query_tree_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_query_tree_cookie_t
 **
 *****************************************************************************/
 
xcb_query_tree_cookie_t
xcb_query_tree_unchecked (xcb_connection_t *c  /**< */,
                          xcb_window_t      window  /**< */);


/*****************************************************************************
 **
 ** xcb_window_t * xcb_query_tree_children
 ** 
 ** @param const xcb_query_tree_reply_t *R
 ** @returns xcb_window_t *
 **
 *****************************************************************************/
 
xcb_window_t *
xcb_query_tree_children (const xcb_query_tree_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_query_tree_children_length
 ** 
 ** @param const xcb_query_tree_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_query_tree_children_length (const xcb_query_tree_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_query_tree_children_end
 ** 
 ** @param const xcb_query_tree_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_query_tree_children_end (const xcb_query_tree_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_query_tree_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_query_tree_reply_t * xcb_query_tree_reply
 ** 
 ** @param xcb_connection_t         *c
 ** @param xcb_query_tree_cookie_t   cookie
 ** @param xcb_generic_error_t     **e
 ** @returns xcb_query_tree_reply_t *
 **
 *****************************************************************************/
 
xcb_query_tree_reply_t *
xcb_query_tree_reply (xcb_connection_t         *c  /**< */,
                      xcb_query_tree_cookie_t   cookie  /**< */,
                      xcb_generic_error_t     **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_intern_atom_cookie_t xcb_intern_atom
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           only_if_exists
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_intern_atom_cookie_t
 **
 *****************************************************************************/
 
xcb_intern_atom_cookie_t
xcb_intern_atom (xcb_connection_t *c  /**< */,
                 uint8_t           only_if_exists  /**< */,
                 uint16_t          name_len  /**< */,
                 const char       *name  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_intern_atom_cookie_t xcb_intern_atom_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           only_if_exists
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_intern_atom_cookie_t
 **
 *****************************************************************************/
 
xcb_intern_atom_cookie_t
xcb_intern_atom_unchecked (xcb_connection_t *c  /**< */,
                           uint8_t           only_if_exists  /**< */,
                           uint16_t          name_len  /**< */,
                           const char       *name  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_intern_atom_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_intern_atom_reply_t * xcb_intern_atom_reply
 ** 
 ** @param xcb_connection_t          *c
 ** @param xcb_intern_atom_cookie_t   cookie
 ** @param xcb_generic_error_t      **e
 ** @returns xcb_intern_atom_reply_t *
 **
 *****************************************************************************/
 
xcb_intern_atom_reply_t *
xcb_intern_atom_reply (xcb_connection_t          *c  /**< */,
                       xcb_intern_atom_cookie_t   cookie  /**< */,
                       xcb_generic_error_t      **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_atom_name_cookie_t xcb_get_atom_name
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_atom_t        atom
 ** @returns xcb_get_atom_name_cookie_t
 **
 *****************************************************************************/
 
xcb_get_atom_name_cookie_t
xcb_get_atom_name (xcb_connection_t *c  /**< */,
                   xcb_atom_t        atom  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_atom_name_cookie_t xcb_get_atom_name_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_atom_t        atom
 ** @returns xcb_get_atom_name_cookie_t
 **
 *****************************************************************************/
 
xcb_get_atom_name_cookie_t
xcb_get_atom_name_unchecked (xcb_connection_t *c  /**< */,
                             xcb_atom_t        atom  /**< */);


/*****************************************************************************
 **
 ** char * xcb_get_atom_name_name
 ** 
 ** @param const xcb_get_atom_name_reply_t *R
 ** @returns char *
 **
 *****************************************************************************/
 
char *
xcb_get_atom_name_name (const xcb_get_atom_name_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_get_atom_name_name_length
 ** 
 ** @param const xcb_get_atom_name_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_get_atom_name_name_length (const xcb_get_atom_name_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_get_atom_name_name_end
 ** 
 ** @param const xcb_get_atom_name_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_get_atom_name_name_end (const xcb_get_atom_name_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_atom_name_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_atom_name_reply_t * xcb_get_atom_name_reply
 ** 
 ** @param xcb_connection_t            *c
 ** @param xcb_get_atom_name_cookie_t   cookie
 ** @param xcb_generic_error_t        **e
 ** @returns xcb_get_atom_name_reply_t *
 **
 *****************************************************************************/
 
xcb_get_atom_name_reply_t *
xcb_get_atom_name_reply (xcb_connection_t            *c  /**< */,
                         xcb_get_atom_name_cookie_t   cookie  /**< */,
                         xcb_generic_error_t        **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_property_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @param xcb_window_t      window
 ** @param xcb_atom_t        property
 ** @param xcb_atom_t        type
 ** @param uint8_t           format
 ** @param uint32_t          data_len
 ** @param const void       *data
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_property_checked (xcb_connection_t *c  /**< */,
                             uint8_t           mode  /**< */,
                             xcb_window_t      window  /**< */,
                             xcb_atom_t        property  /**< */,
                             xcb_atom_t        type  /**< */,
                             uint8_t           format  /**< */,
                             uint32_t          data_len  /**< */,
                             const void       *data  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_property
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @param xcb_window_t      window
 ** @param xcb_atom_t        property
 ** @param xcb_atom_t        type
 ** @param uint8_t           format
 ** @param uint32_t          data_len
 ** @param const void       *data
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_property (xcb_connection_t *c  /**< */,
                     uint8_t           mode  /**< */,
                     xcb_window_t      window  /**< */,
                     xcb_atom_t        property  /**< */,
                     xcb_atom_t        type  /**< */,
                     uint8_t           format  /**< */,
                     uint32_t          data_len  /**< */,
                     const void       *data  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_delete_property_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param xcb_atom_t        property
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_delete_property_checked (xcb_connection_t *c  /**< */,
                             xcb_window_t      window  /**< */,
                             xcb_atom_t        property  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_delete_property
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param xcb_atom_t        property
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_delete_property (xcb_connection_t *c  /**< */,
                     xcb_window_t      window  /**< */,
                     xcb_atom_t        property  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_property_cookie_t xcb_get_property
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           _delete
 ** @param xcb_window_t      window
 ** @param xcb_atom_t        property
 ** @param xcb_atom_t        type
 ** @param uint32_t          long_offset
 ** @param uint32_t          long_length
 ** @returns xcb_get_property_cookie_t
 **
 *****************************************************************************/
 
xcb_get_property_cookie_t
xcb_get_property (xcb_connection_t *c  /**< */,
                  uint8_t           _delete  /**< */,
                  xcb_window_t      window  /**< */,
                  xcb_atom_t        property  /**< */,
                  xcb_atom_t        type  /**< */,
                  uint32_t          long_offset  /**< */,
                  uint32_t          long_length  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_property_cookie_t xcb_get_property_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           _delete
 ** @param xcb_window_t      window
 ** @param xcb_atom_t        property
 ** @param xcb_atom_t        type
 ** @param uint32_t          long_offset
 ** @param uint32_t          long_length
 ** @returns xcb_get_property_cookie_t
 **
 *****************************************************************************/
 
xcb_get_property_cookie_t
xcb_get_property_unchecked (xcb_connection_t *c  /**< */,
                            uint8_t           _delete  /**< */,
                            xcb_window_t      window  /**< */,
                            xcb_atom_t        property  /**< */,
                            xcb_atom_t        type  /**< */,
                            uint32_t          long_offset  /**< */,
                            uint32_t          long_length  /**< */);


/*****************************************************************************
 **
 ** void * xcb_get_property_value
 ** 
 ** @param const xcb_get_property_reply_t *R
 ** @returns void *
 **
 *****************************************************************************/
 
void *
xcb_get_property_value (const xcb_get_property_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_get_property_value_length
 ** 
 ** @param const xcb_get_property_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_get_property_value_length (const xcb_get_property_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_get_property_value_end
 ** 
 ** @param const xcb_get_property_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_get_property_value_end (const xcb_get_property_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_property_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_property_reply_t * xcb_get_property_reply
 ** 
 ** @param xcb_connection_t           *c
 ** @param xcb_get_property_cookie_t   cookie
 ** @param xcb_generic_error_t       **e
 ** @returns xcb_get_property_reply_t *
 **
 *****************************************************************************/
 
xcb_get_property_reply_t *
xcb_get_property_reply (xcb_connection_t           *c  /**< */,
                        xcb_get_property_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_list_properties_cookie_t xcb_list_properties
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_list_properties_cookie_t
 **
 *****************************************************************************/
 
xcb_list_properties_cookie_t
xcb_list_properties (xcb_connection_t *c  /**< */,
                     xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_list_properties_cookie_t xcb_list_properties_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_list_properties_cookie_t
 **
 *****************************************************************************/
 
xcb_list_properties_cookie_t
xcb_list_properties_unchecked (xcb_connection_t *c  /**< */,
                               xcb_window_t      window  /**< */);


/*****************************************************************************
 **
 ** xcb_atom_t * xcb_list_properties_atoms
 ** 
 ** @param const xcb_list_properties_reply_t *R
 ** @returns xcb_atom_t *
 **
 *****************************************************************************/
 
xcb_atom_t *
xcb_list_properties_atoms (const xcb_list_properties_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_list_properties_atoms_length
 ** 
 ** @param const xcb_list_properties_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_list_properties_atoms_length (const xcb_list_properties_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_list_properties_atoms_end
 ** 
 ** @param const xcb_list_properties_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_list_properties_atoms_end (const xcb_list_properties_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_list_properties_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_list_properties_reply_t * xcb_list_properties_reply
 ** 
 ** @param xcb_connection_t              *c
 ** @param xcb_list_properties_cookie_t   cookie
 ** @param xcb_generic_error_t          **e
 ** @returns xcb_list_properties_reply_t *
 **
 *****************************************************************************/
 
xcb_list_properties_reply_t *
xcb_list_properties_reply (xcb_connection_t              *c  /**< */,
                           xcb_list_properties_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_selection_owner_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      owner
 ** @param xcb_atom_t        selection
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_selection_owner_checked (xcb_connection_t *c  /**< */,
                                 xcb_window_t      owner  /**< */,
                                 xcb_atom_t        selection  /**< */,
                                 xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_selection_owner
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      owner
 ** @param xcb_atom_t        selection
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_selection_owner (xcb_connection_t *c  /**< */,
                         xcb_window_t      owner  /**< */,
                         xcb_atom_t        selection  /**< */,
                         xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_selection_owner_cookie_t xcb_get_selection_owner
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_atom_t        selection
 ** @returns xcb_get_selection_owner_cookie_t
 **
 *****************************************************************************/
 
xcb_get_selection_owner_cookie_t
xcb_get_selection_owner (xcb_connection_t *c  /**< */,
                         xcb_atom_t        selection  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_selection_owner_cookie_t xcb_get_selection_owner_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_atom_t        selection
 ** @returns xcb_get_selection_owner_cookie_t
 **
 *****************************************************************************/
 
xcb_get_selection_owner_cookie_t
xcb_get_selection_owner_unchecked (xcb_connection_t *c  /**< */,
                                   xcb_atom_t        selection  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_selection_owner_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_selection_owner_reply_t * xcb_get_selection_owner_reply
 ** 
 ** @param xcb_connection_t                  *c
 ** @param xcb_get_selection_owner_cookie_t   cookie
 ** @param xcb_generic_error_t              **e
 ** @returns xcb_get_selection_owner_reply_t *
 **
 *****************************************************************************/
 
xcb_get_selection_owner_reply_t *
xcb_get_selection_owner_reply (xcb_connection_t                  *c  /**< */,
                               xcb_get_selection_owner_cookie_t   cookie  /**< */,
                               xcb_generic_error_t              **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_convert_selection_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      requestor
 ** @param xcb_atom_t        selection
 ** @param xcb_atom_t        target
 ** @param xcb_atom_t        property
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_convert_selection_checked (xcb_connection_t *c  /**< */,
                               xcb_window_t      requestor  /**< */,
                               xcb_atom_t        selection  /**< */,
                               xcb_atom_t        target  /**< */,
                               xcb_atom_t        property  /**< */,
                               xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_convert_selection
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      requestor
 ** @param xcb_atom_t        selection
 ** @param xcb_atom_t        target
 ** @param xcb_atom_t        property
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_convert_selection (xcb_connection_t *c  /**< */,
                       xcb_window_t      requestor  /**< */,
                       xcb_atom_t        selection  /**< */,
                       xcb_atom_t        target  /**< */,
                       xcb_atom_t        property  /**< */,
                       xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_send_event_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           propagate
 ** @param xcb_window_t      destination
 ** @param uint32_t          event_mask
 ** @param const char       *event
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_send_event_checked (xcb_connection_t *c  /**< */,
                        uint8_t           propagate  /**< */,
                        xcb_window_t      destination  /**< */,
                        uint32_t          event_mask  /**< */,
                        const char       *event  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_send_event
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           propagate
 ** @param xcb_window_t      destination
 ** @param uint32_t          event_mask
 ** @param const char       *event
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_send_event (xcb_connection_t *c  /**< */,
                uint8_t           propagate  /**< */,
                xcb_window_t      destination  /**< */,
                uint32_t          event_mask  /**< */,
                const char       *event  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_grab_pointer_cookie_t xcb_grab_pointer
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           owner_events
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          event_mask
 ** @param uint8_t           pointer_mode
 ** @param uint8_t           keyboard_mode
 ** @param xcb_window_t      confine_to
 ** @param xcb_cursor_t      cursor
 ** @param xcb_timestamp_t   time
 ** @returns xcb_grab_pointer_cookie_t
 **
 *****************************************************************************/
 
xcb_grab_pointer_cookie_t
xcb_grab_pointer (xcb_connection_t *c  /**< */,
                  uint8_t           owner_events  /**< */,
                  xcb_window_t      grab_window  /**< */,
                  uint16_t          event_mask  /**< */,
                  uint8_t           pointer_mode  /**< */,
                  uint8_t           keyboard_mode  /**< */,
                  xcb_window_t      confine_to  /**< */,
                  xcb_cursor_t      cursor  /**< */,
                  xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_grab_pointer_cookie_t xcb_grab_pointer_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           owner_events
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          event_mask
 ** @param uint8_t           pointer_mode
 ** @param uint8_t           keyboard_mode
 ** @param xcb_window_t      confine_to
 ** @param xcb_cursor_t      cursor
 ** @param xcb_timestamp_t   time
 ** @returns xcb_grab_pointer_cookie_t
 **
 *****************************************************************************/
 
xcb_grab_pointer_cookie_t
xcb_grab_pointer_unchecked (xcb_connection_t *c  /**< */,
                            uint8_t           owner_events  /**< */,
                            xcb_window_t      grab_window  /**< */,
                            uint16_t          event_mask  /**< */,
                            uint8_t           pointer_mode  /**< */,
                            uint8_t           keyboard_mode  /**< */,
                            xcb_window_t      confine_to  /**< */,
                            xcb_cursor_t      cursor  /**< */,
                            xcb_timestamp_t   time  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_grab_pointer_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_grab_pointer_reply_t * xcb_grab_pointer_reply
 ** 
 ** @param xcb_connection_t           *c
 ** @param xcb_grab_pointer_cookie_t   cookie
 ** @param xcb_generic_error_t       **e
 ** @returns xcb_grab_pointer_reply_t *
 **
 *****************************************************************************/
 
xcb_grab_pointer_reply_t *
xcb_grab_pointer_reply (xcb_connection_t           *c  /**< */,
                        xcb_grab_pointer_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_pointer_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_pointer_checked (xcb_connection_t *c  /**< */,
                            xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_pointer
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_pointer (xcb_connection_t *c  /**< */,
                    xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_grab_button_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           owner_events
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          event_mask
 ** @param uint8_t           pointer_mode
 ** @param uint8_t           keyboard_mode
 ** @param xcb_window_t      confine_to
 ** @param xcb_cursor_t      cursor
 ** @param uint8_t           button
 ** @param uint16_t          modifiers
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_grab_button_checked (xcb_connection_t *c  /**< */,
                         uint8_t           owner_events  /**< */,
                         xcb_window_t      grab_window  /**< */,
                         uint16_t          event_mask  /**< */,
                         uint8_t           pointer_mode  /**< */,
                         uint8_t           keyboard_mode  /**< */,
                         xcb_window_t      confine_to  /**< */,
                         xcb_cursor_t      cursor  /**< */,
                         uint8_t           button  /**< */,
                         uint16_t          modifiers  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_grab_button
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           owner_events
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          event_mask
 ** @param uint8_t           pointer_mode
 ** @param uint8_t           keyboard_mode
 ** @param xcb_window_t      confine_to
 ** @param xcb_cursor_t      cursor
 ** @param uint8_t           button
 ** @param uint16_t          modifiers
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_grab_button (xcb_connection_t *c  /**< */,
                 uint8_t           owner_events  /**< */,
                 xcb_window_t      grab_window  /**< */,
                 uint16_t          event_mask  /**< */,
                 uint8_t           pointer_mode  /**< */,
                 uint8_t           keyboard_mode  /**< */,
                 xcb_window_t      confine_to  /**< */,
                 xcb_cursor_t      cursor  /**< */,
                 uint8_t           button  /**< */,
                 uint16_t          modifiers  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_button_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           button
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          modifiers
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_button_checked (xcb_connection_t *c  /**< */,
                           uint8_t           button  /**< */,
                           xcb_window_t      grab_window  /**< */,
                           uint16_t          modifiers  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_button
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           button
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          modifiers
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_button (xcb_connection_t *c  /**< */,
                   uint8_t           button  /**< */,
                   xcb_window_t      grab_window  /**< */,
                   uint16_t          modifiers  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_active_pointer_grab_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cursor
 ** @param xcb_timestamp_t   time
 ** @param uint16_t          event_mask
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_active_pointer_grab_checked (xcb_connection_t *c  /**< */,
                                        xcb_cursor_t      cursor  /**< */,
                                        xcb_timestamp_t   time  /**< */,
                                        uint16_t          event_mask  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_active_pointer_grab
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cursor
 ** @param xcb_timestamp_t   time
 ** @param uint16_t          event_mask
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_active_pointer_grab (xcb_connection_t *c  /**< */,
                                xcb_cursor_t      cursor  /**< */,
                                xcb_timestamp_t   time  /**< */,
                                uint16_t          event_mask  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_grab_keyboard_cookie_t xcb_grab_keyboard
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           owner_events
 ** @param xcb_window_t      grab_window
 ** @param xcb_timestamp_t   time
 ** @param uint8_t           pointer_mode
 ** @param uint8_t           keyboard_mode
 ** @returns xcb_grab_keyboard_cookie_t
 **
 *****************************************************************************/
 
xcb_grab_keyboard_cookie_t
xcb_grab_keyboard (xcb_connection_t *c  /**< */,
                   uint8_t           owner_events  /**< */,
                   xcb_window_t      grab_window  /**< */,
                   xcb_timestamp_t   time  /**< */,
                   uint8_t           pointer_mode  /**< */,
                   uint8_t           keyboard_mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_grab_keyboard_cookie_t xcb_grab_keyboard_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           owner_events
 ** @param xcb_window_t      grab_window
 ** @param xcb_timestamp_t   time
 ** @param uint8_t           pointer_mode
 ** @param uint8_t           keyboard_mode
 ** @returns xcb_grab_keyboard_cookie_t
 **
 *****************************************************************************/
 
xcb_grab_keyboard_cookie_t
xcb_grab_keyboard_unchecked (xcb_connection_t *c  /**< */,
                             uint8_t           owner_events  /**< */,
                             xcb_window_t      grab_window  /**< */,
                             xcb_timestamp_t   time  /**< */,
                             uint8_t           pointer_mode  /**< */,
                             uint8_t           keyboard_mode  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_grab_keyboard_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_grab_keyboard_reply_t * xcb_grab_keyboard_reply
 ** 
 ** @param xcb_connection_t            *c
 ** @param xcb_grab_keyboard_cookie_t   cookie
 ** @param xcb_generic_error_t        **e
 ** @returns xcb_grab_keyboard_reply_t *
 **
 *****************************************************************************/
 
xcb_grab_keyboard_reply_t *
xcb_grab_keyboard_reply (xcb_connection_t            *c  /**< */,
                         xcb_grab_keyboard_cookie_t   cookie  /**< */,
                         xcb_generic_error_t        **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_keyboard_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_keyboard_checked (xcb_connection_t *c  /**< */,
                             xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_keyboard
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_keyboard (xcb_connection_t *c  /**< */,
                     xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_grab_key_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           owner_events
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          modifiers
 ** @param xcb_keycode_t     key
 ** @param uint8_t           pointer_mode
 ** @param uint8_t           keyboard_mode
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_grab_key_checked (xcb_connection_t *c  /**< */,
                      uint8_t           owner_events  /**< */,
                      xcb_window_t      grab_window  /**< */,
                      uint16_t          modifiers  /**< */,
                      xcb_keycode_t     key  /**< */,
                      uint8_t           pointer_mode  /**< */,
                      uint8_t           keyboard_mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_grab_key
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           owner_events
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          modifiers
 ** @param xcb_keycode_t     key
 ** @param uint8_t           pointer_mode
 ** @param uint8_t           keyboard_mode
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_grab_key (xcb_connection_t *c  /**< */,
              uint8_t           owner_events  /**< */,
              xcb_window_t      grab_window  /**< */,
              uint16_t          modifiers  /**< */,
              xcb_keycode_t     key  /**< */,
              uint8_t           pointer_mode  /**< */,
              uint8_t           keyboard_mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_key_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_keycode_t     key
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          modifiers
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_key_checked (xcb_connection_t *c  /**< */,
                        xcb_keycode_t     key  /**< */,
                        xcb_window_t      grab_window  /**< */,
                        uint16_t          modifiers  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_key
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_keycode_t     key
 ** @param xcb_window_t      grab_window
 ** @param uint16_t          modifiers
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_key (xcb_connection_t *c  /**< */,
                xcb_keycode_t     key  /**< */,
                xcb_window_t      grab_window  /**< */,
                uint16_t          modifiers  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_allow_events_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_allow_events_checked (xcb_connection_t *c  /**< */,
                          uint8_t           mode  /**< */,
                          xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_allow_events
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_allow_events (xcb_connection_t *c  /**< */,
                  uint8_t           mode  /**< */,
                  xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_grab_server_checked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_grab_server_checked (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_grab_server
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_grab_server (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_server_checked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_server_checked (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_ungrab_server
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_ungrab_server (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_query_pointer_cookie_t xcb_query_pointer
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_query_pointer_cookie_t
 **
 *****************************************************************************/
 
xcb_query_pointer_cookie_t
xcb_query_pointer (xcb_connection_t *c  /**< */,
                   xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_query_pointer_cookie_t xcb_query_pointer_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_query_pointer_cookie_t
 **
 *****************************************************************************/
 
xcb_query_pointer_cookie_t
xcb_query_pointer_unchecked (xcb_connection_t *c  /**< */,
                             xcb_window_t      window  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_query_pointer_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_query_pointer_reply_t * xcb_query_pointer_reply
 ** 
 ** @param xcb_connection_t            *c
 ** @param xcb_query_pointer_cookie_t   cookie
 ** @param xcb_generic_error_t        **e
 ** @returns xcb_query_pointer_reply_t *
 **
 *****************************************************************************/
 
xcb_query_pointer_reply_t *
xcb_query_pointer_reply (xcb_connection_t            *c  /**< */,
                         xcb_query_pointer_cookie_t   cookie  /**< */,
                         xcb_generic_error_t        **e  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_timecoord_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_timecoord_t)
 */

/*****************************************************************************
 **
 ** void xcb_timecoord_next
 ** 
 ** @param xcb_timecoord_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_timecoord_next (xcb_timecoord_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_timecoord_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_timecoord_end
 ** 
 ** @param xcb_timecoord_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_timecoord_end (xcb_timecoord_iterator_t i  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_motion_events_cookie_t xcb_get_motion_events
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param xcb_timestamp_t   start
 ** @param xcb_timestamp_t   stop
 ** @returns xcb_get_motion_events_cookie_t
 **
 *****************************************************************************/
 
xcb_get_motion_events_cookie_t
xcb_get_motion_events (xcb_connection_t *c  /**< */,
                       xcb_window_t      window  /**< */,
                       xcb_timestamp_t   start  /**< */,
                       xcb_timestamp_t   stop  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_motion_events_cookie_t xcb_get_motion_events_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param xcb_timestamp_t   start
 ** @param xcb_timestamp_t   stop
 ** @returns xcb_get_motion_events_cookie_t
 **
 *****************************************************************************/
 
xcb_get_motion_events_cookie_t
xcb_get_motion_events_unchecked (xcb_connection_t *c  /**< */,
                                 xcb_window_t      window  /**< */,
                                 xcb_timestamp_t   start  /**< */,
                                 xcb_timestamp_t   stop  /**< */);


/*****************************************************************************
 **
 ** xcb_timecoord_t * xcb_get_motion_events_events
 ** 
 ** @param const xcb_get_motion_events_reply_t *R
 ** @returns xcb_timecoord_t *
 **
 *****************************************************************************/
 
xcb_timecoord_t *
xcb_get_motion_events_events (const xcb_get_motion_events_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_get_motion_events_events_length
 ** 
 ** @param const xcb_get_motion_events_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_get_motion_events_events_length (const xcb_get_motion_events_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_timecoord_iterator_t xcb_get_motion_events_events_iterator
 ** 
 ** @param const xcb_get_motion_events_reply_t *R
 ** @returns xcb_timecoord_iterator_t
 **
 *****************************************************************************/
 
xcb_timecoord_iterator_t
xcb_get_motion_events_events_iterator (const xcb_get_motion_events_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_motion_events_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_motion_events_reply_t * xcb_get_motion_events_reply
 ** 
 ** @param xcb_connection_t                *c
 ** @param xcb_get_motion_events_cookie_t   cookie
 ** @param xcb_generic_error_t            **e
 ** @returns xcb_get_motion_events_reply_t *
 **
 *****************************************************************************/
 
xcb_get_motion_events_reply_t *
xcb_get_motion_events_reply (xcb_connection_t                *c  /**< */,
                             xcb_get_motion_events_cookie_t   cookie  /**< */,
                             xcb_generic_error_t            **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_translate_coordinates_cookie_t xcb_translate_coordinates
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      src_window
 ** @param xcb_window_t      dst_window
 ** @param int16_t           src_x
 ** @param int16_t           src_y
 ** @returns xcb_translate_coordinates_cookie_t
 **
 *****************************************************************************/
 
xcb_translate_coordinates_cookie_t
xcb_translate_coordinates (xcb_connection_t *c  /**< */,
                           xcb_window_t      src_window  /**< */,
                           xcb_window_t      dst_window  /**< */,
                           int16_t           src_x  /**< */,
                           int16_t           src_y  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_translate_coordinates_cookie_t xcb_translate_coordinates_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      src_window
 ** @param xcb_window_t      dst_window
 ** @param int16_t           src_x
 ** @param int16_t           src_y
 ** @returns xcb_translate_coordinates_cookie_t
 **
 *****************************************************************************/
 
xcb_translate_coordinates_cookie_t
xcb_translate_coordinates_unchecked (xcb_connection_t *c  /**< */,
                                     xcb_window_t      src_window  /**< */,
                                     xcb_window_t      dst_window  /**< */,
                                     int16_t           src_x  /**< */,
                                     int16_t           src_y  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_translate_coordinates_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_translate_coordinates_reply_t * xcb_translate_coordinates_reply
 ** 
 ** @param xcb_connection_t                    *c
 ** @param xcb_translate_coordinates_cookie_t   cookie
 ** @param xcb_generic_error_t                **e
 ** @returns xcb_translate_coordinates_reply_t *
 **
 *****************************************************************************/
 
xcb_translate_coordinates_reply_t *
xcb_translate_coordinates_reply (xcb_connection_t                    *c  /**< */,
                                 xcb_translate_coordinates_cookie_t   cookie  /**< */,
                                 xcb_generic_error_t                **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_warp_pointer_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      src_window
 ** @param xcb_window_t      dst_window
 ** @param int16_t           src_x
 ** @param int16_t           src_y
 ** @param uint16_t          src_width
 ** @param uint16_t          src_height
 ** @param int16_t           dst_x
 ** @param int16_t           dst_y
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_warp_pointer_checked (xcb_connection_t *c  /**< */,
                          xcb_window_t      src_window  /**< */,
                          xcb_window_t      dst_window  /**< */,
                          int16_t           src_x  /**< */,
                          int16_t           src_y  /**< */,
                          uint16_t          src_width  /**< */,
                          uint16_t          src_height  /**< */,
                          int16_t           dst_x  /**< */,
                          int16_t           dst_y  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_warp_pointer
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      src_window
 ** @param xcb_window_t      dst_window
 ** @param int16_t           src_x
 ** @param int16_t           src_y
 ** @param uint16_t          src_width
 ** @param uint16_t          src_height
 ** @param int16_t           dst_x
 ** @param int16_t           dst_y
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_warp_pointer (xcb_connection_t *c  /**< */,
                  xcb_window_t      src_window  /**< */,
                  xcb_window_t      dst_window  /**< */,
                  int16_t           src_x  /**< */,
                  int16_t           src_y  /**< */,
                  uint16_t          src_width  /**< */,
                  uint16_t          src_height  /**< */,
                  int16_t           dst_x  /**< */,
                  int16_t           dst_y  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_input_focus_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           revert_to
 ** @param xcb_window_t      focus
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_input_focus_checked (xcb_connection_t *c  /**< */,
                             uint8_t           revert_to  /**< */,
                             xcb_window_t      focus  /**< */,
                             xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_input_focus
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           revert_to
 ** @param xcb_window_t      focus
 ** @param xcb_timestamp_t   time
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_input_focus (xcb_connection_t *c  /**< */,
                     uint8_t           revert_to  /**< */,
                     xcb_window_t      focus  /**< */,
                     xcb_timestamp_t   time  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_input_focus_cookie_t xcb_get_input_focus
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_input_focus_cookie_t
 **
 *****************************************************************************/
 
xcb_get_input_focus_cookie_t
xcb_get_input_focus (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_input_focus_cookie_t xcb_get_input_focus_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_input_focus_cookie_t
 **
 *****************************************************************************/
 
xcb_get_input_focus_cookie_t
xcb_get_input_focus_unchecked (xcb_connection_t *c  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_input_focus_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_input_focus_reply_t * xcb_get_input_focus_reply
 ** 
 ** @param xcb_connection_t              *c
 ** @param xcb_get_input_focus_cookie_t   cookie
 ** @param xcb_generic_error_t          **e
 ** @returns xcb_get_input_focus_reply_t *
 **
 *****************************************************************************/
 
xcb_get_input_focus_reply_t *
xcb_get_input_focus_reply (xcb_connection_t              *c  /**< */,
                           xcb_get_input_focus_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_query_keymap_cookie_t xcb_query_keymap
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_query_keymap_cookie_t
 **
 *****************************************************************************/
 
xcb_query_keymap_cookie_t
xcb_query_keymap (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_query_keymap_cookie_t xcb_query_keymap_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_query_keymap_cookie_t
 **
 *****************************************************************************/
 
xcb_query_keymap_cookie_t
xcb_query_keymap_unchecked (xcb_connection_t *c  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_query_keymap_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_query_keymap_reply_t * xcb_query_keymap_reply
 ** 
 ** @param xcb_connection_t           *c
 ** @param xcb_query_keymap_cookie_t   cookie
 ** @param xcb_generic_error_t       **e
 ** @returns xcb_query_keymap_reply_t *
 **
 *****************************************************************************/
 
xcb_query_keymap_reply_t *
xcb_query_keymap_reply (xcb_connection_t           *c  /**< */,
                        xcb_query_keymap_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_open_font_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_font_t        fid
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_open_font_checked (xcb_connection_t *c  /**< */,
                       xcb_font_t        fid  /**< */,
                       uint16_t          name_len  /**< */,
                       const char       *name  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_open_font
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_font_t        fid
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_open_font (xcb_connection_t *c  /**< */,
               xcb_font_t        fid  /**< */,
               uint16_t          name_len  /**< */,
               const char       *name  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_close_font_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_font_t        font
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_close_font_checked (xcb_connection_t *c  /**< */,
                        xcb_font_t        font  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_close_font
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_font_t        font
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_close_font (xcb_connection_t *c  /**< */,
                xcb_font_t        font  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_fontprop_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_fontprop_t)
 */

/*****************************************************************************
 **
 ** void xcb_fontprop_next
 ** 
 ** @param xcb_fontprop_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_fontprop_next (xcb_fontprop_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_fontprop_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_fontprop_end
 ** 
 ** @param xcb_fontprop_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_fontprop_end (xcb_fontprop_iterator_t i  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_charinfo_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_charinfo_t)
 */

/*****************************************************************************
 **
 ** void xcb_charinfo_next
 ** 
 ** @param xcb_charinfo_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_charinfo_next (xcb_charinfo_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_charinfo_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_charinfo_end
 ** 
 ** @param xcb_charinfo_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_charinfo_end (xcb_charinfo_iterator_t i  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_query_font_cookie_t xcb_query_font
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_fontable_t    font
 ** @returns xcb_query_font_cookie_t
 **
 *****************************************************************************/
 
xcb_query_font_cookie_t
xcb_query_font (xcb_connection_t *c  /**< */,
                xcb_fontable_t    font  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_query_font_cookie_t xcb_query_font_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_fontable_t    font
 ** @returns xcb_query_font_cookie_t
 **
 *****************************************************************************/
 
xcb_query_font_cookie_t
xcb_query_font_unchecked (xcb_connection_t *c  /**< */,
                          xcb_fontable_t    font  /**< */);


/*****************************************************************************
 **
 ** xcb_fontprop_t * xcb_query_font_properties
 ** 
 ** @param const xcb_query_font_reply_t *R
 ** @returns xcb_fontprop_t *
 **
 *****************************************************************************/
 
xcb_fontprop_t *
xcb_query_font_properties (const xcb_query_font_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_query_font_properties_length
 ** 
 ** @param const xcb_query_font_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_query_font_properties_length (const xcb_query_font_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_fontprop_iterator_t xcb_query_font_properties_iterator
 ** 
 ** @param const xcb_query_font_reply_t *R
 ** @returns xcb_fontprop_iterator_t
 **
 *****************************************************************************/
 
xcb_fontprop_iterator_t
xcb_query_font_properties_iterator (const xcb_query_font_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_charinfo_t * xcb_query_font_char_infos
 ** 
 ** @param const xcb_query_font_reply_t *R
 ** @returns xcb_charinfo_t *
 **
 *****************************************************************************/
 
xcb_charinfo_t *
xcb_query_font_char_infos (const xcb_query_font_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_query_font_char_infos_length
 ** 
 ** @param const xcb_query_font_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_query_font_char_infos_length (const xcb_query_font_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_charinfo_iterator_t xcb_query_font_char_infos_iterator
 ** 
 ** @param const xcb_query_font_reply_t *R
 ** @returns xcb_charinfo_iterator_t
 **
 *****************************************************************************/
 
xcb_charinfo_iterator_t
xcb_query_font_char_infos_iterator (const xcb_query_font_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_query_font_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_query_font_reply_t * xcb_query_font_reply
 ** 
 ** @param xcb_connection_t         *c
 ** @param xcb_query_font_cookie_t   cookie
 ** @param xcb_generic_error_t     **e
 ** @returns xcb_query_font_reply_t *
 **
 *****************************************************************************/
 
xcb_query_font_reply_t *
xcb_query_font_reply (xcb_connection_t         *c  /**< */,
                      xcb_query_font_cookie_t   cookie  /**< */,
                      xcb_generic_error_t     **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_query_text_extents_cookie_t xcb_query_text_extents
 ** 
 ** @param xcb_connection_t   *c
 ** @param xcb_fontable_t      font
 ** @param uint32_t            string_len
 ** @param const xcb_char2b_t *string
 ** @returns xcb_query_text_extents_cookie_t
 **
 *****************************************************************************/
 
xcb_query_text_extents_cookie_t
xcb_query_text_extents (xcb_connection_t   *c  /**< */,
                        xcb_fontable_t      font  /**< */,
                        uint32_t            string_len  /**< */,
                        const xcb_char2b_t *string  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_query_text_extents_cookie_t xcb_query_text_extents_unchecked
 ** 
 ** @param xcb_connection_t   *c
 ** @param xcb_fontable_t      font
 ** @param uint32_t            string_len
 ** @param const xcb_char2b_t *string
 ** @returns xcb_query_text_extents_cookie_t
 **
 *****************************************************************************/
 
xcb_query_text_extents_cookie_t
xcb_query_text_extents_unchecked (xcb_connection_t   *c  /**< */,
                                  xcb_fontable_t      font  /**< */,
                                  uint32_t            string_len  /**< */,
                                  const xcb_char2b_t *string  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_query_text_extents_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_query_text_extents_reply_t * xcb_query_text_extents_reply
 ** 
 ** @param xcb_connection_t                 *c
 ** @param xcb_query_text_extents_cookie_t   cookie
 ** @param xcb_generic_error_t             **e
 ** @returns xcb_query_text_extents_reply_t *
 **
 *****************************************************************************/
 
xcb_query_text_extents_reply_t *
xcb_query_text_extents_reply (xcb_connection_t                 *c  /**< */,
                              xcb_query_text_extents_cookie_t   cookie  /**< */,
                              xcb_generic_error_t             **e  /**< */);


/*****************************************************************************
 **
 ** char * xcb_str_name
 ** 
 ** @param const xcb_str_t *R
 ** @returns char *
 **
 *****************************************************************************/
 
char *
xcb_str_name (const xcb_str_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_str_name_length
 ** 
 ** @param const xcb_str_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_str_name_length (const xcb_str_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_str_name_end
 ** 
 ** @param const xcb_str_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_str_name_end (const xcb_str_t *R  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_str_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_str_t)
 */

/*****************************************************************************
 **
 ** void xcb_str_next
 ** 
 ** @param xcb_str_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_str_next (xcb_str_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_str_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_str_end
 ** 
 ** @param xcb_str_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_str_end (xcb_str_iterator_t i  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_list_fonts_cookie_t xcb_list_fonts
 ** 
 ** @param xcb_connection_t *c
 ** @param uint16_t          max_names
 ** @param uint16_t          pattern_len
 ** @param const char       *pattern
 ** @returns xcb_list_fonts_cookie_t
 **
 *****************************************************************************/
 
xcb_list_fonts_cookie_t
xcb_list_fonts (xcb_connection_t *c  /**< */,
                uint16_t          max_names  /**< */,
                uint16_t          pattern_len  /**< */,
                const char       *pattern  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_list_fonts_cookie_t xcb_list_fonts_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint16_t          max_names
 ** @param uint16_t          pattern_len
 ** @param const char       *pattern
 ** @returns xcb_list_fonts_cookie_t
 **
 *****************************************************************************/
 
xcb_list_fonts_cookie_t
xcb_list_fonts_unchecked (xcb_connection_t *c  /**< */,
                          uint16_t          max_names  /**< */,
                          uint16_t          pattern_len  /**< */,
                          const char       *pattern  /**< */);


/*****************************************************************************
 **
 ** int xcb_list_fonts_names_length
 ** 
 ** @param const xcb_list_fonts_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_list_fonts_names_length (const xcb_list_fonts_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_str_iterator_t xcb_list_fonts_names_iterator
 ** 
 ** @param const xcb_list_fonts_reply_t *R
 ** @returns xcb_str_iterator_t
 **
 *****************************************************************************/
 
xcb_str_iterator_t
xcb_list_fonts_names_iterator (const xcb_list_fonts_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_list_fonts_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_list_fonts_reply_t * xcb_list_fonts_reply
 ** 
 ** @param xcb_connection_t         *c
 ** @param xcb_list_fonts_cookie_t   cookie
 ** @param xcb_generic_error_t     **e
 ** @returns xcb_list_fonts_reply_t *
 **
 *****************************************************************************/
 
xcb_list_fonts_reply_t *
xcb_list_fonts_reply (xcb_connection_t         *c  /**< */,
                      xcb_list_fonts_cookie_t   cookie  /**< */,
                      xcb_generic_error_t     **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_list_fonts_with_info_cookie_t xcb_list_fonts_with_info
 ** 
 ** @param xcb_connection_t *c
 ** @param uint16_t          max_names
 ** @param uint16_t          pattern_len
 ** @param const char       *pattern
 ** @returns xcb_list_fonts_with_info_cookie_t
 **
 *****************************************************************************/
 
xcb_list_fonts_with_info_cookie_t
xcb_list_fonts_with_info (xcb_connection_t *c  /**< */,
                          uint16_t          max_names  /**< */,
                          uint16_t          pattern_len  /**< */,
                          const char       *pattern  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_list_fonts_with_info_cookie_t xcb_list_fonts_with_info_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint16_t          max_names
 ** @param uint16_t          pattern_len
 ** @param const char       *pattern
 ** @returns xcb_list_fonts_with_info_cookie_t
 **
 *****************************************************************************/
 
xcb_list_fonts_with_info_cookie_t
xcb_list_fonts_with_info_unchecked (xcb_connection_t *c  /**< */,
                                    uint16_t          max_names  /**< */,
                                    uint16_t          pattern_len  /**< */,
                                    const char       *pattern  /**< */);


/*****************************************************************************
 **
 ** xcb_fontprop_t * xcb_list_fonts_with_info_properties
 ** 
 ** @param const xcb_list_fonts_with_info_reply_t *R
 ** @returns xcb_fontprop_t *
 **
 *****************************************************************************/
 
xcb_fontprop_t *
xcb_list_fonts_with_info_properties (const xcb_list_fonts_with_info_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_list_fonts_with_info_properties_length
 ** 
 ** @param const xcb_list_fonts_with_info_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_list_fonts_with_info_properties_length (const xcb_list_fonts_with_info_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_fontprop_iterator_t xcb_list_fonts_with_info_properties_iterator
 ** 
 ** @param const xcb_list_fonts_with_info_reply_t *R
 ** @returns xcb_fontprop_iterator_t
 **
 *****************************************************************************/
 
xcb_fontprop_iterator_t
xcb_list_fonts_with_info_properties_iterator (const xcb_list_fonts_with_info_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** char * xcb_list_fonts_with_info_name
 ** 
 ** @param const xcb_list_fonts_with_info_reply_t *R
 ** @returns char *
 **
 *****************************************************************************/
 
char *
xcb_list_fonts_with_info_name (const xcb_list_fonts_with_info_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_list_fonts_with_info_name_length
 ** 
 ** @param const xcb_list_fonts_with_info_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_list_fonts_with_info_name_length (const xcb_list_fonts_with_info_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_list_fonts_with_info_name_end
 ** 
 ** @param const xcb_list_fonts_with_info_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_list_fonts_with_info_name_end (const xcb_list_fonts_with_info_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_list_fonts_with_info_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_list_fonts_with_info_reply_t * xcb_list_fonts_with_info_reply
 ** 
 ** @param xcb_connection_t                   *c
 ** @param xcb_list_fonts_with_info_cookie_t   cookie
 ** @param xcb_generic_error_t               **e
 ** @returns xcb_list_fonts_with_info_reply_t *
 **
 *****************************************************************************/
 
xcb_list_fonts_with_info_reply_t *
xcb_list_fonts_with_info_reply (xcb_connection_t                   *c  /**< */,
                                xcb_list_fonts_with_info_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_font_path_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint16_t          font_qty
 ** @param uint32_t          path_len
 ** @param const char       *path
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_font_path_checked (xcb_connection_t *c  /**< */,
                           uint16_t          font_qty  /**< */,
                           uint32_t          path_len  /**< */,
                           const char       *path  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_font_path
 ** 
 ** @param xcb_connection_t *c
 ** @param uint16_t          font_qty
 ** @param uint32_t          path_len
 ** @param const char       *path
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_font_path (xcb_connection_t *c  /**< */,
                   uint16_t          font_qty  /**< */,
                   uint32_t          path_len  /**< */,
                   const char       *path  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_font_path_cookie_t xcb_get_font_path
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_font_path_cookie_t
 **
 *****************************************************************************/
 
xcb_get_font_path_cookie_t
xcb_get_font_path (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_font_path_cookie_t xcb_get_font_path_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_font_path_cookie_t
 **
 *****************************************************************************/
 
xcb_get_font_path_cookie_t
xcb_get_font_path_unchecked (xcb_connection_t *c  /**< */);


/*****************************************************************************
 **
 ** int xcb_get_font_path_path_length
 ** 
 ** @param const xcb_get_font_path_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_get_font_path_path_length (const xcb_get_font_path_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_str_iterator_t xcb_get_font_path_path_iterator
 ** 
 ** @param const xcb_get_font_path_reply_t *R
 ** @returns xcb_str_iterator_t
 **
 *****************************************************************************/
 
xcb_str_iterator_t
xcb_get_font_path_path_iterator (const xcb_get_font_path_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_font_path_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_font_path_reply_t * xcb_get_font_path_reply
 ** 
 ** @param xcb_connection_t            *c
 ** @param xcb_get_font_path_cookie_t   cookie
 ** @param xcb_generic_error_t        **e
 ** @returns xcb_get_font_path_reply_t *
 **
 *****************************************************************************/
 
xcb_get_font_path_reply_t *
xcb_get_font_path_reply (xcb_connection_t            *c  /**< */,
                         xcb_get_font_path_cookie_t   cookie  /**< */,
                         xcb_generic_error_t        **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_pixmap_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           depth
 ** @param xcb_pixmap_t      pid
 ** @param xcb_drawable_t    drawable
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_pixmap_checked (xcb_connection_t *c  /**< */,
                           uint8_t           depth  /**< */,
                           xcb_pixmap_t      pid  /**< */,
                           xcb_drawable_t    drawable  /**< */,
                           uint16_t          width  /**< */,
                           uint16_t          height  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_pixmap
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           depth
 ** @param xcb_pixmap_t      pid
 ** @param xcb_drawable_t    drawable
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_pixmap (xcb_connection_t *c  /**< */,
                   uint8_t           depth  /**< */,
                   xcb_pixmap_t      pid  /**< */,
                   xcb_drawable_t    drawable  /**< */,
                   uint16_t          width  /**< */,
                   uint16_t          height  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_pixmap_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_pixmap_t      pixmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_pixmap_checked (xcb_connection_t *c  /**< */,
                         xcb_pixmap_t      pixmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_pixmap
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_pixmap_t      pixmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_pixmap (xcb_connection_t *c  /**< */,
                 xcb_pixmap_t      pixmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_gc_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    cid
 ** @param xcb_drawable_t    drawable
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_gc_checked (xcb_connection_t *c  /**< */,
                       xcb_gcontext_t    cid  /**< */,
                       xcb_drawable_t    drawable  /**< */,
                       uint32_t          value_mask  /**< */,
                       const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_gc
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    cid
 ** @param xcb_drawable_t    drawable
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_gc (xcb_connection_t *c  /**< */,
               xcb_gcontext_t    cid  /**< */,
               xcb_drawable_t    drawable  /**< */,
               uint32_t          value_mask  /**< */,
               const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_gc_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    gc
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_gc_checked (xcb_connection_t *c  /**< */,
                       xcb_gcontext_t    gc  /**< */,
                       uint32_t          value_mask  /**< */,
                       const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_gc
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    gc
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_gc (xcb_connection_t *c  /**< */,
               xcb_gcontext_t    gc  /**< */,
               uint32_t          value_mask  /**< */,
               const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_copy_gc_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    src_gc
 ** @param xcb_gcontext_t    dst_gc
 ** @param uint32_t          value_mask
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_copy_gc_checked (xcb_connection_t *c  /**< */,
                     xcb_gcontext_t    src_gc  /**< */,
                     xcb_gcontext_t    dst_gc  /**< */,
                     uint32_t          value_mask  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_copy_gc
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    src_gc
 ** @param xcb_gcontext_t    dst_gc
 ** @param uint32_t          value_mask
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_copy_gc (xcb_connection_t *c  /**< */,
             xcb_gcontext_t    src_gc  /**< */,
             xcb_gcontext_t    dst_gc  /**< */,
             uint32_t          value_mask  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_dashes_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    gc
 ** @param uint16_t          dash_offset
 ** @param uint16_t          dashes_len
 ** @param const uint8_t    *dashes
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_dashes_checked (xcb_connection_t *c  /**< */,
                        xcb_gcontext_t    gc  /**< */,
                        uint16_t          dash_offset  /**< */,
                        uint16_t          dashes_len  /**< */,
                        const uint8_t    *dashes  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_dashes
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    gc
 ** @param uint16_t          dash_offset
 ** @param uint16_t          dashes_len
 ** @param const uint8_t    *dashes
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_dashes (xcb_connection_t *c  /**< */,
                xcb_gcontext_t    gc  /**< */,
                uint16_t          dash_offset  /**< */,
                uint16_t          dashes_len  /**< */,
                const uint8_t    *dashes  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_clip_rectangles_checked
 ** 
 ** @param xcb_connection_t      *c
 ** @param uint8_t                ordering
 ** @param xcb_gcontext_t         gc
 ** @param int16_t                clip_x_origin
 ** @param int16_t                clip_y_origin
 ** @param uint32_t               rectangles_len
 ** @param const xcb_rectangle_t *rectangles
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_clip_rectangles_checked (xcb_connection_t      *c  /**< */,
                                 uint8_t                ordering  /**< */,
                                 xcb_gcontext_t         gc  /**< */,
                                 int16_t                clip_x_origin  /**< */,
                                 int16_t                clip_y_origin  /**< */,
                                 uint32_t               rectangles_len  /**< */,
                                 const xcb_rectangle_t *rectangles  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_clip_rectangles
 ** 
 ** @param xcb_connection_t      *c
 ** @param uint8_t                ordering
 ** @param xcb_gcontext_t         gc
 ** @param int16_t                clip_x_origin
 ** @param int16_t                clip_y_origin
 ** @param uint32_t               rectangles_len
 ** @param const xcb_rectangle_t *rectangles
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_clip_rectangles (xcb_connection_t      *c  /**< */,
                         uint8_t                ordering  /**< */,
                         xcb_gcontext_t         gc  /**< */,
                         int16_t                clip_x_origin  /**< */,
                         int16_t                clip_y_origin  /**< */,
                         uint32_t               rectangles_len  /**< */,
                         const xcb_rectangle_t *rectangles  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_gc_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    gc
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_gc_checked (xcb_connection_t *c  /**< */,
                     xcb_gcontext_t    gc  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_gc
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_gcontext_t    gc
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_gc (xcb_connection_t *c  /**< */,
             xcb_gcontext_t    gc  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_clear_area_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           exposures
 ** @param xcb_window_t      window
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_clear_area_checked (xcb_connection_t *c  /**< */,
                        uint8_t           exposures  /**< */,
                        xcb_window_t      window  /**< */,
                        int16_t           x  /**< */,
                        int16_t           y  /**< */,
                        uint16_t          width  /**< */,
                        uint16_t          height  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_clear_area
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           exposures
 ** @param xcb_window_t      window
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_clear_area (xcb_connection_t *c  /**< */,
                uint8_t           exposures  /**< */,
                xcb_window_t      window  /**< */,
                int16_t           x  /**< */,
                int16_t           y  /**< */,
                uint16_t          width  /**< */,
                uint16_t          height  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_copy_area_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    src_drawable
 ** @param xcb_drawable_t    dst_drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           src_x
 ** @param int16_t           src_y
 ** @param int16_t           dst_x
 ** @param int16_t           dst_y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_copy_area_checked (xcb_connection_t *c  /**< */,
                       xcb_drawable_t    src_drawable  /**< */,
                       xcb_drawable_t    dst_drawable  /**< */,
                       xcb_gcontext_t    gc  /**< */,
                       int16_t           src_x  /**< */,
                       int16_t           src_y  /**< */,
                       int16_t           dst_x  /**< */,
                       int16_t           dst_y  /**< */,
                       uint16_t          width  /**< */,
                       uint16_t          height  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_copy_area
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    src_drawable
 ** @param xcb_drawable_t    dst_drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           src_x
 ** @param int16_t           src_y
 ** @param int16_t           dst_x
 ** @param int16_t           dst_y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_copy_area (xcb_connection_t *c  /**< */,
               xcb_drawable_t    src_drawable  /**< */,
               xcb_drawable_t    dst_drawable  /**< */,
               xcb_gcontext_t    gc  /**< */,
               int16_t           src_x  /**< */,
               int16_t           src_y  /**< */,
               int16_t           dst_x  /**< */,
               int16_t           dst_y  /**< */,
               uint16_t          width  /**< */,
               uint16_t          height  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_copy_plane_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    src_drawable
 ** @param xcb_drawable_t    dst_drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           src_x
 ** @param int16_t           src_y
 ** @param int16_t           dst_x
 ** @param int16_t           dst_y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @param uint32_t          bit_plane
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_copy_plane_checked (xcb_connection_t *c  /**< */,
                        xcb_drawable_t    src_drawable  /**< */,
                        xcb_drawable_t    dst_drawable  /**< */,
                        xcb_gcontext_t    gc  /**< */,
                        int16_t           src_x  /**< */,
                        int16_t           src_y  /**< */,
                        int16_t           dst_x  /**< */,
                        int16_t           dst_y  /**< */,
                        uint16_t          width  /**< */,
                        uint16_t          height  /**< */,
                        uint32_t          bit_plane  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_copy_plane
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    src_drawable
 ** @param xcb_drawable_t    dst_drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           src_x
 ** @param int16_t           src_y
 ** @param int16_t           dst_x
 ** @param int16_t           dst_y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @param uint32_t          bit_plane
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_copy_plane (xcb_connection_t *c  /**< */,
                xcb_drawable_t    src_drawable  /**< */,
                xcb_drawable_t    dst_drawable  /**< */,
                xcb_gcontext_t    gc  /**< */,
                int16_t           src_x  /**< */,
                int16_t           src_y  /**< */,
                int16_t           dst_x  /**< */,
                int16_t           dst_y  /**< */,
                uint16_t          width  /**< */,
                uint16_t          height  /**< */,
                uint32_t          bit_plane  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_point_checked
 ** 
 ** @param xcb_connection_t  *c
 ** @param uint8_t            coordinate_mode
 ** @param xcb_drawable_t     drawable
 ** @param xcb_gcontext_t     gc
 ** @param uint32_t           points_len
 ** @param const xcb_point_t *points
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_point_checked (xcb_connection_t  *c  /**< */,
                        uint8_t            coordinate_mode  /**< */,
                        xcb_drawable_t     drawable  /**< */,
                        xcb_gcontext_t     gc  /**< */,
                        uint32_t           points_len  /**< */,
                        const xcb_point_t *points  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_point
 ** 
 ** @param xcb_connection_t  *c
 ** @param uint8_t            coordinate_mode
 ** @param xcb_drawable_t     drawable
 ** @param xcb_gcontext_t     gc
 ** @param uint32_t           points_len
 ** @param const xcb_point_t *points
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_point (xcb_connection_t  *c  /**< */,
                uint8_t            coordinate_mode  /**< */,
                xcb_drawable_t     drawable  /**< */,
                xcb_gcontext_t     gc  /**< */,
                uint32_t           points_len  /**< */,
                const xcb_point_t *points  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_line_checked
 ** 
 ** @param xcb_connection_t  *c
 ** @param uint8_t            coordinate_mode
 ** @param xcb_drawable_t     drawable
 ** @param xcb_gcontext_t     gc
 ** @param uint32_t           points_len
 ** @param const xcb_point_t *points
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_line_checked (xcb_connection_t  *c  /**< */,
                       uint8_t            coordinate_mode  /**< */,
                       xcb_drawable_t     drawable  /**< */,
                       xcb_gcontext_t     gc  /**< */,
                       uint32_t           points_len  /**< */,
                       const xcb_point_t *points  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_line
 ** 
 ** @param xcb_connection_t  *c
 ** @param uint8_t            coordinate_mode
 ** @param xcb_drawable_t     drawable
 ** @param xcb_gcontext_t     gc
 ** @param uint32_t           points_len
 ** @param const xcb_point_t *points
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_line (xcb_connection_t  *c  /**< */,
               uint8_t            coordinate_mode  /**< */,
               xcb_drawable_t     drawable  /**< */,
               xcb_gcontext_t     gc  /**< */,
               uint32_t           points_len  /**< */,
               const xcb_point_t *points  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_segment_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_segment_t)
 */

/*****************************************************************************
 **
 ** void xcb_segment_next
 ** 
 ** @param xcb_segment_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_segment_next (xcb_segment_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_segment_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_segment_end
 ** 
 ** @param xcb_segment_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_segment_end (xcb_segment_iterator_t i  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_segment_checked
 ** 
 ** @param xcb_connection_t    *c
 ** @param xcb_drawable_t       drawable
 ** @param xcb_gcontext_t       gc
 ** @param uint32_t             segments_len
 ** @param const xcb_segment_t *segments
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_segment_checked (xcb_connection_t    *c  /**< */,
                          xcb_drawable_t       drawable  /**< */,
                          xcb_gcontext_t       gc  /**< */,
                          uint32_t             segments_len  /**< */,
                          const xcb_segment_t *segments  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_segment
 ** 
 ** @param xcb_connection_t    *c
 ** @param xcb_drawable_t       drawable
 ** @param xcb_gcontext_t       gc
 ** @param uint32_t             segments_len
 ** @param const xcb_segment_t *segments
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_segment (xcb_connection_t    *c  /**< */,
                  xcb_drawable_t       drawable  /**< */,
                  xcb_gcontext_t       gc  /**< */,
                  uint32_t             segments_len  /**< */,
                  const xcb_segment_t *segments  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_rectangle_checked
 ** 
 ** @param xcb_connection_t      *c
 ** @param xcb_drawable_t         drawable
 ** @param xcb_gcontext_t         gc
 ** @param uint32_t               rectangles_len
 ** @param const xcb_rectangle_t *rectangles
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_rectangle_checked (xcb_connection_t      *c  /**< */,
                            xcb_drawable_t         drawable  /**< */,
                            xcb_gcontext_t         gc  /**< */,
                            uint32_t               rectangles_len  /**< */,
                            const xcb_rectangle_t *rectangles  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_rectangle
 ** 
 ** @param xcb_connection_t      *c
 ** @param xcb_drawable_t         drawable
 ** @param xcb_gcontext_t         gc
 ** @param uint32_t               rectangles_len
 ** @param const xcb_rectangle_t *rectangles
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_rectangle (xcb_connection_t      *c  /**< */,
                    xcb_drawable_t         drawable  /**< */,
                    xcb_gcontext_t         gc  /**< */,
                    uint32_t               rectangles_len  /**< */,
                    const xcb_rectangle_t *rectangles  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_arc_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param uint32_t          arcs_len
 ** @param const xcb_arc_t  *arcs
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_arc_checked (xcb_connection_t *c  /**< */,
                      xcb_drawable_t    drawable  /**< */,
                      xcb_gcontext_t    gc  /**< */,
                      uint32_t          arcs_len  /**< */,
                      const xcb_arc_t  *arcs  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_arc
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param uint32_t          arcs_len
 ** @param const xcb_arc_t  *arcs
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_arc (xcb_connection_t *c  /**< */,
              xcb_drawable_t    drawable  /**< */,
              xcb_gcontext_t    gc  /**< */,
              uint32_t          arcs_len  /**< */,
              const xcb_arc_t  *arcs  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_fill_poly_checked
 ** 
 ** @param xcb_connection_t  *c
 ** @param xcb_drawable_t     drawable
 ** @param xcb_gcontext_t     gc
 ** @param uint8_t            shape
 ** @param uint8_t            coordinate_mode
 ** @param uint32_t           points_len
 ** @param const xcb_point_t *points
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_fill_poly_checked (xcb_connection_t  *c  /**< */,
                       xcb_drawable_t     drawable  /**< */,
                       xcb_gcontext_t     gc  /**< */,
                       uint8_t            shape  /**< */,
                       uint8_t            coordinate_mode  /**< */,
                       uint32_t           points_len  /**< */,
                       const xcb_point_t *points  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_fill_poly
 ** 
 ** @param xcb_connection_t  *c
 ** @param xcb_drawable_t     drawable
 ** @param xcb_gcontext_t     gc
 ** @param uint8_t            shape
 ** @param uint8_t            coordinate_mode
 ** @param uint32_t           points_len
 ** @param const xcb_point_t *points
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_fill_poly (xcb_connection_t  *c  /**< */,
               xcb_drawable_t     drawable  /**< */,
               xcb_gcontext_t     gc  /**< */,
               uint8_t            shape  /**< */,
               uint8_t            coordinate_mode  /**< */,
               uint32_t           points_len  /**< */,
               const xcb_point_t *points  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_fill_rectangle_checked
 ** 
 ** @param xcb_connection_t      *c
 ** @param xcb_drawable_t         drawable
 ** @param xcb_gcontext_t         gc
 ** @param uint32_t               rectangles_len
 ** @param const xcb_rectangle_t *rectangles
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_fill_rectangle_checked (xcb_connection_t      *c  /**< */,
                                 xcb_drawable_t         drawable  /**< */,
                                 xcb_gcontext_t         gc  /**< */,
                                 uint32_t               rectangles_len  /**< */,
                                 const xcb_rectangle_t *rectangles  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_fill_rectangle
 ** 
 ** @param xcb_connection_t      *c
 ** @param xcb_drawable_t         drawable
 ** @param xcb_gcontext_t         gc
 ** @param uint32_t               rectangles_len
 ** @param const xcb_rectangle_t *rectangles
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_fill_rectangle (xcb_connection_t      *c  /**< */,
                         xcb_drawable_t         drawable  /**< */,
                         xcb_gcontext_t         gc  /**< */,
                         uint32_t               rectangles_len  /**< */,
                         const xcb_rectangle_t *rectangles  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_fill_arc_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param uint32_t          arcs_len
 ** @param const xcb_arc_t  *arcs
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_fill_arc_checked (xcb_connection_t *c  /**< */,
                           xcb_drawable_t    drawable  /**< */,
                           xcb_gcontext_t    gc  /**< */,
                           uint32_t          arcs_len  /**< */,
                           const xcb_arc_t  *arcs  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_fill_arc
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param uint32_t          arcs_len
 ** @param const xcb_arc_t  *arcs
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_fill_arc (xcb_connection_t *c  /**< */,
                   xcb_drawable_t    drawable  /**< */,
                   xcb_gcontext_t    gc  /**< */,
                   uint32_t          arcs_len  /**< */,
                   const xcb_arc_t  *arcs  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_put_image_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           format
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @param int16_t           dst_x
 ** @param int16_t           dst_y
 ** @param uint8_t           left_pad
 ** @param uint8_t           depth
 ** @param uint32_t          data_len
 ** @param const uint8_t    *data
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_put_image_checked (xcb_connection_t *c  /**< */,
                       uint8_t           format  /**< */,
                       xcb_drawable_t    drawable  /**< */,
                       xcb_gcontext_t    gc  /**< */,
                       uint16_t          width  /**< */,
                       uint16_t          height  /**< */,
                       int16_t           dst_x  /**< */,
                       int16_t           dst_y  /**< */,
                       uint8_t           left_pad  /**< */,
                       uint8_t           depth  /**< */,
                       uint32_t          data_len  /**< */,
                       const uint8_t    *data  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_put_image
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           format
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @param int16_t           dst_x
 ** @param int16_t           dst_y
 ** @param uint8_t           left_pad
 ** @param uint8_t           depth
 ** @param uint32_t          data_len
 ** @param const uint8_t    *data
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_put_image (xcb_connection_t *c  /**< */,
               uint8_t           format  /**< */,
               xcb_drawable_t    drawable  /**< */,
               xcb_gcontext_t    gc  /**< */,
               uint16_t          width  /**< */,
               uint16_t          height  /**< */,
               int16_t           dst_x  /**< */,
               int16_t           dst_y  /**< */,
               uint8_t           left_pad  /**< */,
               uint8_t           depth  /**< */,
               uint32_t          data_len  /**< */,
               const uint8_t    *data  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_image_cookie_t xcb_get_image
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           format
 ** @param xcb_drawable_t    drawable
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @param uint32_t          plane_mask
 ** @returns xcb_get_image_cookie_t
 **
 *****************************************************************************/
 
xcb_get_image_cookie_t
xcb_get_image (xcb_connection_t *c  /**< */,
               uint8_t           format  /**< */,
               xcb_drawable_t    drawable  /**< */,
               int16_t           x  /**< */,
               int16_t           y  /**< */,
               uint16_t          width  /**< */,
               uint16_t          height  /**< */,
               uint32_t          plane_mask  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_image_cookie_t xcb_get_image_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           format
 ** @param xcb_drawable_t    drawable
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @param uint32_t          plane_mask
 ** @returns xcb_get_image_cookie_t
 **
 *****************************************************************************/
 
xcb_get_image_cookie_t
xcb_get_image_unchecked (xcb_connection_t *c  /**< */,
                         uint8_t           format  /**< */,
                         xcb_drawable_t    drawable  /**< */,
                         int16_t           x  /**< */,
                         int16_t           y  /**< */,
                         uint16_t          width  /**< */,
                         uint16_t          height  /**< */,
                         uint32_t          plane_mask  /**< */);


/*****************************************************************************
 **
 ** uint8_t * xcb_get_image_data
 ** 
 ** @param const xcb_get_image_reply_t *R
 ** @returns uint8_t *
 **
 *****************************************************************************/
 
uint8_t *
xcb_get_image_data (const xcb_get_image_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_get_image_data_length
 ** 
 ** @param const xcb_get_image_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_get_image_data_length (const xcb_get_image_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_get_image_data_end
 ** 
 ** @param const xcb_get_image_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_get_image_data_end (const xcb_get_image_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_image_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_image_reply_t * xcb_get_image_reply
 ** 
 ** @param xcb_connection_t        *c
 ** @param xcb_get_image_cookie_t   cookie
 ** @param xcb_generic_error_t    **e
 ** @returns xcb_get_image_reply_t *
 **
 *****************************************************************************/
 
xcb_get_image_reply_t *
xcb_get_image_reply (xcb_connection_t        *c  /**< */,
                     xcb_get_image_cookie_t   cookie  /**< */,
                     xcb_generic_error_t    **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_text_8_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint32_t          items_len
 ** @param const uint8_t    *items
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_text_8_checked (xcb_connection_t *c  /**< */,
                         xcb_drawable_t    drawable  /**< */,
                         xcb_gcontext_t    gc  /**< */,
                         int16_t           x  /**< */,
                         int16_t           y  /**< */,
                         uint32_t          items_len  /**< */,
                         const uint8_t    *items  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_text_8
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint32_t          items_len
 ** @param const uint8_t    *items
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_text_8 (xcb_connection_t *c  /**< */,
                 xcb_drawable_t    drawable  /**< */,
                 xcb_gcontext_t    gc  /**< */,
                 int16_t           x  /**< */,
                 int16_t           y  /**< */,
                 uint32_t          items_len  /**< */,
                 const uint8_t    *items  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_text_16_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint32_t          items_len
 ** @param const uint8_t    *items
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_text_16_checked (xcb_connection_t *c  /**< */,
                          xcb_drawable_t    drawable  /**< */,
                          xcb_gcontext_t    gc  /**< */,
                          int16_t           x  /**< */,
                          int16_t           y  /**< */,
                          uint32_t          items_len  /**< */,
                          const uint8_t    *items  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_poly_text_16
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param uint32_t          items_len
 ** @param const uint8_t    *items
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_poly_text_16 (xcb_connection_t *c  /**< */,
                  xcb_drawable_t    drawable  /**< */,
                  xcb_gcontext_t    gc  /**< */,
                  int16_t           x  /**< */,
                  int16_t           y  /**< */,
                  uint32_t          items_len  /**< */,
                  const uint8_t    *items  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_image_text_8_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           string_len
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param const char       *string
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_image_text_8_checked (xcb_connection_t *c  /**< */,
                          uint8_t           string_len  /**< */,
                          xcb_drawable_t    drawable  /**< */,
                          xcb_gcontext_t    gc  /**< */,
                          int16_t           x  /**< */,
                          int16_t           y  /**< */,
                          const char       *string  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_image_text_8
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           string_len
 ** @param xcb_drawable_t    drawable
 ** @param xcb_gcontext_t    gc
 ** @param int16_t           x
 ** @param int16_t           y
 ** @param const char       *string
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_image_text_8 (xcb_connection_t *c  /**< */,
                  uint8_t           string_len  /**< */,
                  xcb_drawable_t    drawable  /**< */,
                  xcb_gcontext_t    gc  /**< */,
                  int16_t           x  /**< */,
                  int16_t           y  /**< */,
                  const char       *string  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_image_text_16_checked
 ** 
 ** @param xcb_connection_t   *c
 ** @param uint8_t             string_len
 ** @param xcb_drawable_t      drawable
 ** @param xcb_gcontext_t      gc
 ** @param int16_t             x
 ** @param int16_t             y
 ** @param const xcb_char2b_t *string
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_image_text_16_checked (xcb_connection_t   *c  /**< */,
                           uint8_t             string_len  /**< */,
                           xcb_drawable_t      drawable  /**< */,
                           xcb_gcontext_t      gc  /**< */,
                           int16_t             x  /**< */,
                           int16_t             y  /**< */,
                           const xcb_char2b_t *string  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_image_text_16
 ** 
 ** @param xcb_connection_t   *c
 ** @param uint8_t             string_len
 ** @param xcb_drawable_t      drawable
 ** @param xcb_gcontext_t      gc
 ** @param int16_t             x
 ** @param int16_t             y
 ** @param const xcb_char2b_t *string
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_image_text_16 (xcb_connection_t   *c  /**< */,
                   uint8_t             string_len  /**< */,
                   xcb_drawable_t      drawable  /**< */,
                   xcb_gcontext_t      gc  /**< */,
                   int16_t             x  /**< */,
                   int16_t             y  /**< */,
                   const xcb_char2b_t *string  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_colormap_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           alloc
 ** @param xcb_colormap_t    mid
 ** @param xcb_window_t      window
 ** @param xcb_visualid_t    visual
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_colormap_checked (xcb_connection_t *c  /**< */,
                             uint8_t           alloc  /**< */,
                             xcb_colormap_t    mid  /**< */,
                             xcb_window_t      window  /**< */,
                             xcb_visualid_t    visual  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_colormap
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           alloc
 ** @param xcb_colormap_t    mid
 ** @param xcb_window_t      window
 ** @param xcb_visualid_t    visual
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_colormap (xcb_connection_t *c  /**< */,
                     uint8_t           alloc  /**< */,
                     xcb_colormap_t    mid  /**< */,
                     xcb_window_t      window  /**< */,
                     xcb_visualid_t    visual  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_colormap_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_colormap_checked (xcb_connection_t *c  /**< */,
                           xcb_colormap_t    cmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_colormap
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_colormap (xcb_connection_t *c  /**< */,
                   xcb_colormap_t    cmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_copy_colormap_and_free_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    mid
 ** @param xcb_colormap_t    src_cmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_copy_colormap_and_free_checked (xcb_connection_t *c  /**< */,
                                    xcb_colormap_t    mid  /**< */,
                                    xcb_colormap_t    src_cmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_copy_colormap_and_free
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    mid
 ** @param xcb_colormap_t    src_cmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_copy_colormap_and_free (xcb_connection_t *c  /**< */,
                            xcb_colormap_t    mid  /**< */,
                            xcb_colormap_t    src_cmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_install_colormap_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_install_colormap_checked (xcb_connection_t *c  /**< */,
                              xcb_colormap_t    cmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_install_colormap
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_install_colormap (xcb_connection_t *c  /**< */,
                      xcb_colormap_t    cmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_uninstall_colormap_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_uninstall_colormap_checked (xcb_connection_t *c  /**< */,
                                xcb_colormap_t    cmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_uninstall_colormap
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_uninstall_colormap (xcb_connection_t *c  /**< */,
                        xcb_colormap_t    cmap  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_list_installed_colormaps_cookie_t xcb_list_installed_colormaps
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_list_installed_colormaps_cookie_t
 **
 *****************************************************************************/
 
xcb_list_installed_colormaps_cookie_t
xcb_list_installed_colormaps (xcb_connection_t *c  /**< */,
                              xcb_window_t      window  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_list_installed_colormaps_cookie_t xcb_list_installed_colormaps_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @returns xcb_list_installed_colormaps_cookie_t
 **
 *****************************************************************************/
 
xcb_list_installed_colormaps_cookie_t
xcb_list_installed_colormaps_unchecked (xcb_connection_t *c  /**< */,
                                        xcb_window_t      window  /**< */);


/*****************************************************************************
 **
 ** xcb_colormap_t * xcb_list_installed_colormaps_cmaps
 ** 
 ** @param const xcb_list_installed_colormaps_reply_t *R
 ** @returns xcb_colormap_t *
 **
 *****************************************************************************/
 
xcb_colormap_t *
xcb_list_installed_colormaps_cmaps (const xcb_list_installed_colormaps_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_list_installed_colormaps_cmaps_length
 ** 
 ** @param const xcb_list_installed_colormaps_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_list_installed_colormaps_cmaps_length (const xcb_list_installed_colormaps_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_list_installed_colormaps_cmaps_end
 ** 
 ** @param const xcb_list_installed_colormaps_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_list_installed_colormaps_cmaps_end (const xcb_list_installed_colormaps_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_list_installed_colormaps_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_list_installed_colormaps_reply_t * xcb_list_installed_colormaps_reply
 ** 
 ** @param xcb_connection_t                       *c
 ** @param xcb_list_installed_colormaps_cookie_t   cookie
 ** @param xcb_generic_error_t                   **e
 ** @returns xcb_list_installed_colormaps_reply_t *
 **
 *****************************************************************************/
 
xcb_list_installed_colormaps_reply_t *
xcb_list_installed_colormaps_reply (xcb_connection_t                       *c  /**< */,
                                    xcb_list_installed_colormaps_cookie_t   cookie  /**< */,
                                    xcb_generic_error_t                   **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_cookie_t xcb_alloc_color
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          red
 ** @param uint16_t          green
 ** @param uint16_t          blue
 ** @returns xcb_alloc_color_cookie_t
 **
 *****************************************************************************/
 
xcb_alloc_color_cookie_t
xcb_alloc_color (xcb_connection_t *c  /**< */,
                 xcb_colormap_t    cmap  /**< */,
                 uint16_t          red  /**< */,
                 uint16_t          green  /**< */,
                 uint16_t          blue  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_cookie_t xcb_alloc_color_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          red
 ** @param uint16_t          green
 ** @param uint16_t          blue
 ** @returns xcb_alloc_color_cookie_t
 **
 *****************************************************************************/
 
xcb_alloc_color_cookie_t
xcb_alloc_color_unchecked (xcb_connection_t *c  /**< */,
                           xcb_colormap_t    cmap  /**< */,
                           uint16_t          red  /**< */,
                           uint16_t          green  /**< */,
                           uint16_t          blue  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_alloc_color_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_reply_t * xcb_alloc_color_reply
 ** 
 ** @param xcb_connection_t          *c
 ** @param xcb_alloc_color_cookie_t   cookie
 ** @param xcb_generic_error_t      **e
 ** @returns xcb_alloc_color_reply_t *
 **
 *****************************************************************************/
 
xcb_alloc_color_reply_t *
xcb_alloc_color_reply (xcb_connection_t          *c  /**< */,
                       xcb_alloc_color_cookie_t   cookie  /**< */,
                       xcb_generic_error_t      **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_alloc_named_color_cookie_t xcb_alloc_named_color
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_alloc_named_color_cookie_t
 **
 *****************************************************************************/
 
xcb_alloc_named_color_cookie_t
xcb_alloc_named_color (xcb_connection_t *c  /**< */,
                       xcb_colormap_t    cmap  /**< */,
                       uint16_t          name_len  /**< */,
                       const char       *name  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_alloc_named_color_cookie_t xcb_alloc_named_color_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_alloc_named_color_cookie_t
 **
 *****************************************************************************/
 
xcb_alloc_named_color_cookie_t
xcb_alloc_named_color_unchecked (xcb_connection_t *c  /**< */,
                                 xcb_colormap_t    cmap  /**< */,
                                 uint16_t          name_len  /**< */,
                                 const char       *name  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_alloc_named_color_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_alloc_named_color_reply_t * xcb_alloc_named_color_reply
 ** 
 ** @param xcb_connection_t                *c
 ** @param xcb_alloc_named_color_cookie_t   cookie
 ** @param xcb_generic_error_t            **e
 ** @returns xcb_alloc_named_color_reply_t *
 **
 *****************************************************************************/
 
xcb_alloc_named_color_reply_t *
xcb_alloc_named_color_reply (xcb_connection_t                *c  /**< */,
                             xcb_alloc_named_color_cookie_t   cookie  /**< */,
                             xcb_generic_error_t            **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_cells_cookie_t xcb_alloc_color_cells
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           contiguous
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          colors
 ** @param uint16_t          planes
 ** @returns xcb_alloc_color_cells_cookie_t
 **
 *****************************************************************************/
 
xcb_alloc_color_cells_cookie_t
xcb_alloc_color_cells (xcb_connection_t *c  /**< */,
                       uint8_t           contiguous  /**< */,
                       xcb_colormap_t    cmap  /**< */,
                       uint16_t          colors  /**< */,
                       uint16_t          planes  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_cells_cookie_t xcb_alloc_color_cells_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           contiguous
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          colors
 ** @param uint16_t          planes
 ** @returns xcb_alloc_color_cells_cookie_t
 **
 *****************************************************************************/
 
xcb_alloc_color_cells_cookie_t
xcb_alloc_color_cells_unchecked (xcb_connection_t *c  /**< */,
                                 uint8_t           contiguous  /**< */,
                                 xcb_colormap_t    cmap  /**< */,
                                 uint16_t          colors  /**< */,
                                 uint16_t          planes  /**< */);


/*****************************************************************************
 **
 ** uint32_t * xcb_alloc_color_cells_pixels
 ** 
 ** @param const xcb_alloc_color_cells_reply_t *R
 ** @returns uint32_t *
 **
 *****************************************************************************/
 
uint32_t *
xcb_alloc_color_cells_pixels (const xcb_alloc_color_cells_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_alloc_color_cells_pixels_length
 ** 
 ** @param const xcb_alloc_color_cells_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_alloc_color_cells_pixels_length (const xcb_alloc_color_cells_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_alloc_color_cells_pixels_end
 ** 
 ** @param const xcb_alloc_color_cells_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_alloc_color_cells_pixels_end (const xcb_alloc_color_cells_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** uint32_t * xcb_alloc_color_cells_masks
 ** 
 ** @param const xcb_alloc_color_cells_reply_t *R
 ** @returns uint32_t *
 **
 *****************************************************************************/
 
uint32_t *
xcb_alloc_color_cells_masks (const xcb_alloc_color_cells_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_alloc_color_cells_masks_length
 ** 
 ** @param const xcb_alloc_color_cells_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_alloc_color_cells_masks_length (const xcb_alloc_color_cells_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_alloc_color_cells_masks_end
 ** 
 ** @param const xcb_alloc_color_cells_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_alloc_color_cells_masks_end (const xcb_alloc_color_cells_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_alloc_color_cells_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_cells_reply_t * xcb_alloc_color_cells_reply
 ** 
 ** @param xcb_connection_t                *c
 ** @param xcb_alloc_color_cells_cookie_t   cookie
 ** @param xcb_generic_error_t            **e
 ** @returns xcb_alloc_color_cells_reply_t *
 **
 *****************************************************************************/
 
xcb_alloc_color_cells_reply_t *
xcb_alloc_color_cells_reply (xcb_connection_t                *c  /**< */,
                             xcb_alloc_color_cells_cookie_t   cookie  /**< */,
                             xcb_generic_error_t            **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_planes_cookie_t xcb_alloc_color_planes
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           contiguous
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          colors
 ** @param uint16_t          reds
 ** @param uint16_t          greens
 ** @param uint16_t          blues
 ** @returns xcb_alloc_color_planes_cookie_t
 **
 *****************************************************************************/
 
xcb_alloc_color_planes_cookie_t
xcb_alloc_color_planes (xcb_connection_t *c  /**< */,
                        uint8_t           contiguous  /**< */,
                        xcb_colormap_t    cmap  /**< */,
                        uint16_t          colors  /**< */,
                        uint16_t          reds  /**< */,
                        uint16_t          greens  /**< */,
                        uint16_t          blues  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_planes_cookie_t xcb_alloc_color_planes_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           contiguous
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          colors
 ** @param uint16_t          reds
 ** @param uint16_t          greens
 ** @param uint16_t          blues
 ** @returns xcb_alloc_color_planes_cookie_t
 **
 *****************************************************************************/
 
xcb_alloc_color_planes_cookie_t
xcb_alloc_color_planes_unchecked (xcb_connection_t *c  /**< */,
                                  uint8_t           contiguous  /**< */,
                                  xcb_colormap_t    cmap  /**< */,
                                  uint16_t          colors  /**< */,
                                  uint16_t          reds  /**< */,
                                  uint16_t          greens  /**< */,
                                  uint16_t          blues  /**< */);


/*****************************************************************************
 **
 ** uint32_t * xcb_alloc_color_planes_pixels
 ** 
 ** @param const xcb_alloc_color_planes_reply_t *R
 ** @returns uint32_t *
 **
 *****************************************************************************/
 
uint32_t *
xcb_alloc_color_planes_pixels (const xcb_alloc_color_planes_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_alloc_color_planes_pixels_length
 ** 
 ** @param const xcb_alloc_color_planes_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_alloc_color_planes_pixels_length (const xcb_alloc_color_planes_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_alloc_color_planes_pixels_end
 ** 
 ** @param const xcb_alloc_color_planes_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_alloc_color_planes_pixels_end (const xcb_alloc_color_planes_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_alloc_color_planes_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_alloc_color_planes_reply_t * xcb_alloc_color_planes_reply
 ** 
 ** @param xcb_connection_t                 *c
 ** @param xcb_alloc_color_planes_cookie_t   cookie
 ** @param xcb_generic_error_t             **e
 ** @returns xcb_alloc_color_planes_reply_t *
 **
 *****************************************************************************/
 
xcb_alloc_color_planes_reply_t *
xcb_alloc_color_planes_reply (xcb_connection_t                 *c  /**< */,
                              xcb_alloc_color_planes_cookie_t   cookie  /**< */,
                              xcb_generic_error_t             **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_colors_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint32_t          plane_mask
 ** @param uint32_t          pixels_len
 ** @param const uint32_t   *pixels
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_colors_checked (xcb_connection_t *c  /**< */,
                         xcb_colormap_t    cmap  /**< */,
                         uint32_t          plane_mask  /**< */,
                         uint32_t          pixels_len  /**< */,
                         const uint32_t   *pixels  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_colors
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint32_t          plane_mask
 ** @param uint32_t          pixels_len
 ** @param const uint32_t   *pixels
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_colors (xcb_connection_t *c  /**< */,
                 xcb_colormap_t    cmap  /**< */,
                 uint32_t          plane_mask  /**< */,
                 uint32_t          pixels_len  /**< */,
                 const uint32_t   *pixels  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_coloritem_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_coloritem_t)
 */

/*****************************************************************************
 **
 ** void xcb_coloritem_next
 ** 
 ** @param xcb_coloritem_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_coloritem_next (xcb_coloritem_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_coloritem_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_coloritem_end
 ** 
 ** @param xcb_coloritem_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_coloritem_end (xcb_coloritem_iterator_t i  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_store_colors_checked
 ** 
 ** @param xcb_connection_t      *c
 ** @param xcb_colormap_t         cmap
 ** @param uint32_t               items_len
 ** @param const xcb_coloritem_t *items
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_store_colors_checked (xcb_connection_t      *c  /**< */,
                          xcb_colormap_t         cmap  /**< */,
                          uint32_t               items_len  /**< */,
                          const xcb_coloritem_t *items  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_store_colors
 ** 
 ** @param xcb_connection_t      *c
 ** @param xcb_colormap_t         cmap
 ** @param uint32_t               items_len
 ** @param const xcb_coloritem_t *items
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_store_colors (xcb_connection_t      *c  /**< */,
                  xcb_colormap_t         cmap  /**< */,
                  uint32_t               items_len  /**< */,
                  const xcb_coloritem_t *items  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_store_named_color_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           flags
 ** @param xcb_colormap_t    cmap
 ** @param uint32_t          pixel
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_store_named_color_checked (xcb_connection_t *c  /**< */,
                               uint8_t           flags  /**< */,
                               xcb_colormap_t    cmap  /**< */,
                               uint32_t          pixel  /**< */,
                               uint16_t          name_len  /**< */,
                               const char       *name  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_store_named_color
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           flags
 ** @param xcb_colormap_t    cmap
 ** @param uint32_t          pixel
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_store_named_color (xcb_connection_t *c  /**< */,
                       uint8_t           flags  /**< */,
                       xcb_colormap_t    cmap  /**< */,
                       uint32_t          pixel  /**< */,
                       uint16_t          name_len  /**< */,
                       const char       *name  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_rgb_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_rgb_t)
 */

/*****************************************************************************
 **
 ** void xcb_rgb_next
 ** 
 ** @param xcb_rgb_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_rgb_next (xcb_rgb_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_rgb_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_rgb_end
 ** 
 ** @param xcb_rgb_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_rgb_end (xcb_rgb_iterator_t i  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_query_colors_cookie_t xcb_query_colors
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint32_t          pixels_len
 ** @param const uint32_t   *pixels
 ** @returns xcb_query_colors_cookie_t
 **
 *****************************************************************************/
 
xcb_query_colors_cookie_t
xcb_query_colors (xcb_connection_t *c  /**< */,
                  xcb_colormap_t    cmap  /**< */,
                  uint32_t          pixels_len  /**< */,
                  const uint32_t   *pixels  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_query_colors_cookie_t xcb_query_colors_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint32_t          pixels_len
 ** @param const uint32_t   *pixels
 ** @returns xcb_query_colors_cookie_t
 **
 *****************************************************************************/
 
xcb_query_colors_cookie_t
xcb_query_colors_unchecked (xcb_connection_t *c  /**< */,
                            xcb_colormap_t    cmap  /**< */,
                            uint32_t          pixels_len  /**< */,
                            const uint32_t   *pixels  /**< */);


/*****************************************************************************
 **
 ** xcb_rgb_t * xcb_query_colors_colors
 ** 
 ** @param const xcb_query_colors_reply_t *R
 ** @returns xcb_rgb_t *
 **
 *****************************************************************************/
 
xcb_rgb_t *
xcb_query_colors_colors (const xcb_query_colors_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_query_colors_colors_length
 ** 
 ** @param const xcb_query_colors_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_query_colors_colors_length (const xcb_query_colors_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_rgb_iterator_t xcb_query_colors_colors_iterator
 ** 
 ** @param const xcb_query_colors_reply_t *R
 ** @returns xcb_rgb_iterator_t
 **
 *****************************************************************************/
 
xcb_rgb_iterator_t
xcb_query_colors_colors_iterator (const xcb_query_colors_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_query_colors_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_query_colors_reply_t * xcb_query_colors_reply
 ** 
 ** @param xcb_connection_t           *c
 ** @param xcb_query_colors_cookie_t   cookie
 ** @param xcb_generic_error_t       **e
 ** @returns xcb_query_colors_reply_t *
 **
 *****************************************************************************/
 
xcb_query_colors_reply_t *
xcb_query_colors_reply (xcb_connection_t           *c  /**< */,
                        xcb_query_colors_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_lookup_color_cookie_t xcb_lookup_color
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_lookup_color_cookie_t
 **
 *****************************************************************************/
 
xcb_lookup_color_cookie_t
xcb_lookup_color (xcb_connection_t *c  /**< */,
                  xcb_colormap_t    cmap  /**< */,
                  uint16_t          name_len  /**< */,
                  const char       *name  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_lookup_color_cookie_t xcb_lookup_color_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_colormap_t    cmap
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_lookup_color_cookie_t
 **
 *****************************************************************************/
 
xcb_lookup_color_cookie_t
xcb_lookup_color_unchecked (xcb_connection_t *c  /**< */,
                            xcb_colormap_t    cmap  /**< */,
                            uint16_t          name_len  /**< */,
                            const char       *name  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_lookup_color_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_lookup_color_reply_t * xcb_lookup_color_reply
 ** 
 ** @param xcb_connection_t           *c
 ** @param xcb_lookup_color_cookie_t   cookie
 ** @param xcb_generic_error_t       **e
 ** @returns xcb_lookup_color_reply_t *
 **
 *****************************************************************************/
 
xcb_lookup_color_reply_t *
xcb_lookup_color_reply (xcb_connection_t           *c  /**< */,
                        xcb_lookup_color_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_cursor_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cid
 ** @param xcb_pixmap_t      source
 ** @param xcb_pixmap_t      mask
 ** @param uint16_t          fore_red
 ** @param uint16_t          fore_green
 ** @param uint16_t          fore_blue
 ** @param uint16_t          back_red
 ** @param uint16_t          back_green
 ** @param uint16_t          back_blue
 ** @param uint16_t          x
 ** @param uint16_t          y
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_cursor_checked (xcb_connection_t *c  /**< */,
                           xcb_cursor_t      cid  /**< */,
                           xcb_pixmap_t      source  /**< */,
                           xcb_pixmap_t      mask  /**< */,
                           uint16_t          fore_red  /**< */,
                           uint16_t          fore_green  /**< */,
                           uint16_t          fore_blue  /**< */,
                           uint16_t          back_red  /**< */,
                           uint16_t          back_green  /**< */,
                           uint16_t          back_blue  /**< */,
                           uint16_t          x  /**< */,
                           uint16_t          y  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_cursor
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cid
 ** @param xcb_pixmap_t      source
 ** @param xcb_pixmap_t      mask
 ** @param uint16_t          fore_red
 ** @param uint16_t          fore_green
 ** @param uint16_t          fore_blue
 ** @param uint16_t          back_red
 ** @param uint16_t          back_green
 ** @param uint16_t          back_blue
 ** @param uint16_t          x
 ** @param uint16_t          y
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_cursor (xcb_connection_t *c  /**< */,
                   xcb_cursor_t      cid  /**< */,
                   xcb_pixmap_t      source  /**< */,
                   xcb_pixmap_t      mask  /**< */,
                   uint16_t          fore_red  /**< */,
                   uint16_t          fore_green  /**< */,
                   uint16_t          fore_blue  /**< */,
                   uint16_t          back_red  /**< */,
                   uint16_t          back_green  /**< */,
                   uint16_t          back_blue  /**< */,
                   uint16_t          x  /**< */,
                   uint16_t          y  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_glyph_cursor_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cid
 ** @param xcb_font_t        source_font
 ** @param xcb_font_t        mask_font
 ** @param uint16_t          source_char
 ** @param uint16_t          mask_char
 ** @param uint16_t          fore_red
 ** @param uint16_t          fore_green
 ** @param uint16_t          fore_blue
 ** @param uint16_t          back_red
 ** @param uint16_t          back_green
 ** @param uint16_t          back_blue
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_glyph_cursor_checked (xcb_connection_t *c  /**< */,
                                 xcb_cursor_t      cid  /**< */,
                                 xcb_font_t        source_font  /**< */,
                                 xcb_font_t        mask_font  /**< */,
                                 uint16_t          source_char  /**< */,
                                 uint16_t          mask_char  /**< */,
                                 uint16_t          fore_red  /**< */,
                                 uint16_t          fore_green  /**< */,
                                 uint16_t          fore_blue  /**< */,
                                 uint16_t          back_red  /**< */,
                                 uint16_t          back_green  /**< */,
                                 uint16_t          back_blue  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_create_glyph_cursor
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cid
 ** @param xcb_font_t        source_font
 ** @param xcb_font_t        mask_font
 ** @param uint16_t          source_char
 ** @param uint16_t          mask_char
 ** @param uint16_t          fore_red
 ** @param uint16_t          fore_green
 ** @param uint16_t          fore_blue
 ** @param uint16_t          back_red
 ** @param uint16_t          back_green
 ** @param uint16_t          back_blue
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_create_glyph_cursor (xcb_connection_t *c  /**< */,
                         xcb_cursor_t      cid  /**< */,
                         xcb_font_t        source_font  /**< */,
                         xcb_font_t        mask_font  /**< */,
                         uint16_t          source_char  /**< */,
                         uint16_t          mask_char  /**< */,
                         uint16_t          fore_red  /**< */,
                         uint16_t          fore_green  /**< */,
                         uint16_t          fore_blue  /**< */,
                         uint16_t          back_red  /**< */,
                         uint16_t          back_green  /**< */,
                         uint16_t          back_blue  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_cursor_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cursor
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_cursor_checked (xcb_connection_t *c  /**< */,
                         xcb_cursor_t      cursor  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_free_cursor
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cursor
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_free_cursor (xcb_connection_t *c  /**< */,
                 xcb_cursor_t      cursor  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_recolor_cursor_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cursor
 ** @param uint16_t          fore_red
 ** @param uint16_t          fore_green
 ** @param uint16_t          fore_blue
 ** @param uint16_t          back_red
 ** @param uint16_t          back_green
 ** @param uint16_t          back_blue
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_recolor_cursor_checked (xcb_connection_t *c  /**< */,
                            xcb_cursor_t      cursor  /**< */,
                            uint16_t          fore_red  /**< */,
                            uint16_t          fore_green  /**< */,
                            uint16_t          fore_blue  /**< */,
                            uint16_t          back_red  /**< */,
                            uint16_t          back_green  /**< */,
                            uint16_t          back_blue  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_recolor_cursor
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_cursor_t      cursor
 ** @param uint16_t          fore_red
 ** @param uint16_t          fore_green
 ** @param uint16_t          fore_blue
 ** @param uint16_t          back_red
 ** @param uint16_t          back_green
 ** @param uint16_t          back_blue
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_recolor_cursor (xcb_connection_t *c  /**< */,
                    xcb_cursor_t      cursor  /**< */,
                    uint16_t          fore_red  /**< */,
                    uint16_t          fore_green  /**< */,
                    uint16_t          fore_blue  /**< */,
                    uint16_t          back_red  /**< */,
                    uint16_t          back_green  /**< */,
                    uint16_t          back_blue  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_query_best_size_cookie_t xcb_query_best_size
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           _class
 ** @param xcb_drawable_t    drawable
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @returns xcb_query_best_size_cookie_t
 **
 *****************************************************************************/
 
xcb_query_best_size_cookie_t
xcb_query_best_size (xcb_connection_t *c  /**< */,
                     uint8_t           _class  /**< */,
                     xcb_drawable_t    drawable  /**< */,
                     uint16_t          width  /**< */,
                     uint16_t          height  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_query_best_size_cookie_t xcb_query_best_size_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           _class
 ** @param xcb_drawable_t    drawable
 ** @param uint16_t          width
 ** @param uint16_t          height
 ** @returns xcb_query_best_size_cookie_t
 **
 *****************************************************************************/
 
xcb_query_best_size_cookie_t
xcb_query_best_size_unchecked (xcb_connection_t *c  /**< */,
                               uint8_t           _class  /**< */,
                               xcb_drawable_t    drawable  /**< */,
                               uint16_t          width  /**< */,
                               uint16_t          height  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_query_best_size_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_query_best_size_reply_t * xcb_query_best_size_reply
 ** 
 ** @param xcb_connection_t              *c
 ** @param xcb_query_best_size_cookie_t   cookie
 ** @param xcb_generic_error_t          **e
 ** @returns xcb_query_best_size_reply_t *
 **
 *****************************************************************************/
 
xcb_query_best_size_reply_t *
xcb_query_best_size_reply (xcb_connection_t              *c  /**< */,
                           xcb_query_best_size_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_query_extension_cookie_t xcb_query_extension
 ** 
 ** @param xcb_connection_t *c
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_query_extension_cookie_t
 **
 *****************************************************************************/
 
xcb_query_extension_cookie_t
xcb_query_extension (xcb_connection_t *c  /**< */,
                     uint16_t          name_len  /**< */,
                     const char       *name  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_query_extension_cookie_t xcb_query_extension_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint16_t          name_len
 ** @param const char       *name
 ** @returns xcb_query_extension_cookie_t
 **
 *****************************************************************************/
 
xcb_query_extension_cookie_t
xcb_query_extension_unchecked (xcb_connection_t *c  /**< */,
                               uint16_t          name_len  /**< */,
                               const char       *name  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_query_extension_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_query_extension_reply_t * xcb_query_extension_reply
 ** 
 ** @param xcb_connection_t              *c
 ** @param xcb_query_extension_cookie_t   cookie
 ** @param xcb_generic_error_t          **e
 ** @returns xcb_query_extension_reply_t *
 **
 *****************************************************************************/
 
xcb_query_extension_reply_t *
xcb_query_extension_reply (xcb_connection_t              *c  /**< */,
                           xcb_query_extension_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_list_extensions_cookie_t xcb_list_extensions
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_list_extensions_cookie_t
 **
 *****************************************************************************/
 
xcb_list_extensions_cookie_t
xcb_list_extensions (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_list_extensions_cookie_t xcb_list_extensions_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_list_extensions_cookie_t
 **
 *****************************************************************************/
 
xcb_list_extensions_cookie_t
xcb_list_extensions_unchecked (xcb_connection_t *c  /**< */);


/*****************************************************************************
 **
 ** int xcb_list_extensions_names_length
 ** 
 ** @param const xcb_list_extensions_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_list_extensions_names_length (const xcb_list_extensions_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_str_iterator_t xcb_list_extensions_names_iterator
 ** 
 ** @param const xcb_list_extensions_reply_t *R
 ** @returns xcb_str_iterator_t
 **
 *****************************************************************************/
 
xcb_str_iterator_t
xcb_list_extensions_names_iterator (const xcb_list_extensions_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_list_extensions_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_list_extensions_reply_t * xcb_list_extensions_reply
 ** 
 ** @param xcb_connection_t              *c
 ** @param xcb_list_extensions_cookie_t   cookie
 ** @param xcb_generic_error_t          **e
 ** @returns xcb_list_extensions_reply_t *
 **
 *****************************************************************************/
 
xcb_list_extensions_reply_t *
xcb_list_extensions_reply (xcb_connection_t              *c  /**< */,
                           xcb_list_extensions_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_keyboard_mapping_checked
 ** 
 ** @param xcb_connection_t   *c
 ** @param uint8_t             keycode_count
 ** @param xcb_keycode_t       first_keycode
 ** @param uint8_t             keysyms_per_keycode
 ** @param const xcb_keysym_t *keysyms
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_keyboard_mapping_checked (xcb_connection_t   *c  /**< */,
                                     uint8_t             keycode_count  /**< */,
                                     xcb_keycode_t       first_keycode  /**< */,
                                     uint8_t             keysyms_per_keycode  /**< */,
                                     const xcb_keysym_t *keysyms  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_keyboard_mapping
 ** 
 ** @param xcb_connection_t   *c
 ** @param uint8_t             keycode_count
 ** @param xcb_keycode_t       first_keycode
 ** @param uint8_t             keysyms_per_keycode
 ** @param const xcb_keysym_t *keysyms
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_keyboard_mapping (xcb_connection_t   *c  /**< */,
                             uint8_t             keycode_count  /**< */,
                             xcb_keycode_t       first_keycode  /**< */,
                             uint8_t             keysyms_per_keycode  /**< */,
                             const xcb_keysym_t *keysyms  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_keyboard_mapping_cookie_t xcb_get_keyboard_mapping
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_keycode_t     first_keycode
 ** @param uint8_t           count
 ** @returns xcb_get_keyboard_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_get_keyboard_mapping_cookie_t
xcb_get_keyboard_mapping (xcb_connection_t *c  /**< */,
                          xcb_keycode_t     first_keycode  /**< */,
                          uint8_t           count  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_keyboard_mapping_cookie_t xcb_get_keyboard_mapping_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_keycode_t     first_keycode
 ** @param uint8_t           count
 ** @returns xcb_get_keyboard_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_get_keyboard_mapping_cookie_t
xcb_get_keyboard_mapping_unchecked (xcb_connection_t *c  /**< */,
                                    xcb_keycode_t     first_keycode  /**< */,
                                    uint8_t           count  /**< */);


/*****************************************************************************
 **
 ** xcb_keysym_t * xcb_get_keyboard_mapping_keysyms
 ** 
 ** @param const xcb_get_keyboard_mapping_reply_t *R
 ** @returns xcb_keysym_t *
 **
 *****************************************************************************/
 
xcb_keysym_t *
xcb_get_keyboard_mapping_keysyms (const xcb_get_keyboard_mapping_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_get_keyboard_mapping_keysyms_length
 ** 
 ** @param const xcb_get_keyboard_mapping_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_get_keyboard_mapping_keysyms_length (const xcb_get_keyboard_mapping_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_get_keyboard_mapping_keysyms_end
 ** 
 ** @param const xcb_get_keyboard_mapping_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_get_keyboard_mapping_keysyms_end (const xcb_get_keyboard_mapping_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_keyboard_mapping_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_keyboard_mapping_reply_t * xcb_get_keyboard_mapping_reply
 ** 
 ** @param xcb_connection_t                   *c
 ** @param xcb_get_keyboard_mapping_cookie_t   cookie
 ** @param xcb_generic_error_t               **e
 ** @returns xcb_get_keyboard_mapping_reply_t *
 **
 *****************************************************************************/
 
xcb_get_keyboard_mapping_reply_t *
xcb_get_keyboard_mapping_reply (xcb_connection_t                   *c  /**< */,
                                xcb_get_keyboard_mapping_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_keyboard_control_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_keyboard_control_checked (xcb_connection_t *c  /**< */,
                                     uint32_t          value_mask  /**< */,
                                     const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_keyboard_control
 ** 
 ** @param xcb_connection_t *c
 ** @param uint32_t          value_mask
 ** @param const uint32_t   *value_list
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_keyboard_control (xcb_connection_t *c  /**< */,
                             uint32_t          value_mask  /**< */,
                             const uint32_t   *value_list  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_keyboard_control_cookie_t xcb_get_keyboard_control
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_keyboard_control_cookie_t
 **
 *****************************************************************************/
 
xcb_get_keyboard_control_cookie_t
xcb_get_keyboard_control (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_keyboard_control_cookie_t xcb_get_keyboard_control_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_keyboard_control_cookie_t
 **
 *****************************************************************************/
 
xcb_get_keyboard_control_cookie_t
xcb_get_keyboard_control_unchecked (xcb_connection_t *c  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_keyboard_control_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_keyboard_control_reply_t * xcb_get_keyboard_control_reply
 ** 
 ** @param xcb_connection_t                   *c
 ** @param xcb_get_keyboard_control_cookie_t   cookie
 ** @param xcb_generic_error_t               **e
 ** @returns xcb_get_keyboard_control_reply_t *
 **
 *****************************************************************************/
 
xcb_get_keyboard_control_reply_t *
xcb_get_keyboard_control_reply (xcb_connection_t                   *c  /**< */,
                                xcb_get_keyboard_control_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_bell_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param int8_t            percent
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_bell_checked (xcb_connection_t *c  /**< */,
                  int8_t            percent  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_bell
 ** 
 ** @param xcb_connection_t *c
 ** @param int8_t            percent
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_bell (xcb_connection_t *c  /**< */,
          int8_t            percent  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_pointer_control_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param int16_t           acceleration_numerator
 ** @param int16_t           acceleration_denominator
 ** @param int16_t           threshold
 ** @param uint8_t           do_acceleration
 ** @param uint8_t           do_threshold
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_pointer_control_checked (xcb_connection_t *c  /**< */,
                                    int16_t           acceleration_numerator  /**< */,
                                    int16_t           acceleration_denominator  /**< */,
                                    int16_t           threshold  /**< */,
                                    uint8_t           do_acceleration  /**< */,
                                    uint8_t           do_threshold  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_pointer_control
 ** 
 ** @param xcb_connection_t *c
 ** @param int16_t           acceleration_numerator
 ** @param int16_t           acceleration_denominator
 ** @param int16_t           threshold
 ** @param uint8_t           do_acceleration
 ** @param uint8_t           do_threshold
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_pointer_control (xcb_connection_t *c  /**< */,
                            int16_t           acceleration_numerator  /**< */,
                            int16_t           acceleration_denominator  /**< */,
                            int16_t           threshold  /**< */,
                            uint8_t           do_acceleration  /**< */,
                            uint8_t           do_threshold  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_pointer_control_cookie_t xcb_get_pointer_control
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_pointer_control_cookie_t
 **
 *****************************************************************************/
 
xcb_get_pointer_control_cookie_t
xcb_get_pointer_control (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_pointer_control_cookie_t xcb_get_pointer_control_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_pointer_control_cookie_t
 **
 *****************************************************************************/
 
xcb_get_pointer_control_cookie_t
xcb_get_pointer_control_unchecked (xcb_connection_t *c  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_pointer_control_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_pointer_control_reply_t * xcb_get_pointer_control_reply
 ** 
 ** @param xcb_connection_t                  *c
 ** @param xcb_get_pointer_control_cookie_t   cookie
 ** @param xcb_generic_error_t              **e
 ** @returns xcb_get_pointer_control_reply_t *
 **
 *****************************************************************************/
 
xcb_get_pointer_control_reply_t *
xcb_get_pointer_control_reply (xcb_connection_t                  *c  /**< */,
                               xcb_get_pointer_control_cookie_t   cookie  /**< */,
                               xcb_generic_error_t              **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_screen_saver_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param int16_t           timeout
 ** @param int16_t           interval
 ** @param uint8_t           prefer_blanking
 ** @param uint8_t           allow_exposures
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_screen_saver_checked (xcb_connection_t *c  /**< */,
                              int16_t           timeout  /**< */,
                              int16_t           interval  /**< */,
                              uint8_t           prefer_blanking  /**< */,
                              uint8_t           allow_exposures  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_screen_saver
 ** 
 ** @param xcb_connection_t *c
 ** @param int16_t           timeout
 ** @param int16_t           interval
 ** @param uint8_t           prefer_blanking
 ** @param uint8_t           allow_exposures
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_screen_saver (xcb_connection_t *c  /**< */,
                      int16_t           timeout  /**< */,
                      int16_t           interval  /**< */,
                      uint8_t           prefer_blanking  /**< */,
                      uint8_t           allow_exposures  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_screen_saver_cookie_t xcb_get_screen_saver
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_screen_saver_cookie_t
 **
 *****************************************************************************/
 
xcb_get_screen_saver_cookie_t
xcb_get_screen_saver (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_screen_saver_cookie_t xcb_get_screen_saver_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_screen_saver_cookie_t
 **
 *****************************************************************************/
 
xcb_get_screen_saver_cookie_t
xcb_get_screen_saver_unchecked (xcb_connection_t *c  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_screen_saver_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_screen_saver_reply_t * xcb_get_screen_saver_reply
 ** 
 ** @param xcb_connection_t               *c
 ** @param xcb_get_screen_saver_cookie_t   cookie
 ** @param xcb_generic_error_t           **e
 ** @returns xcb_get_screen_saver_reply_t *
 **
 *****************************************************************************/
 
xcb_get_screen_saver_reply_t *
xcb_get_screen_saver_reply (xcb_connection_t               *c  /**< */,
                            xcb_get_screen_saver_cookie_t   cookie  /**< */,
                            xcb_generic_error_t           **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_hosts_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @param uint8_t           family
 ** @param uint16_t          address_len
 ** @param const char       *address
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_hosts_checked (xcb_connection_t *c  /**< */,
                          uint8_t           mode  /**< */,
                          uint8_t           family  /**< */,
                          uint16_t          address_len  /**< */,
                          const char       *address  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_change_hosts
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @param uint8_t           family
 ** @param uint16_t          address_len
 ** @param const char       *address
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_change_hosts (xcb_connection_t *c  /**< */,
                  uint8_t           mode  /**< */,
                  uint8_t           family  /**< */,
                  uint16_t          address_len  /**< */,
                  const char       *address  /**< */);


/*****************************************************************************
 **
 ** uint8_t * xcb_host_address
 ** 
 ** @param const xcb_host_t *R
 ** @returns uint8_t *
 **
 *****************************************************************************/
 
uint8_t *
xcb_host_address (const xcb_host_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_host_address_length
 ** 
 ** @param const xcb_host_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_host_address_length (const xcb_host_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_host_address_end
 ** 
 ** @param const xcb_host_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_host_address_end (const xcb_host_t *R  /**< */);

/**
 * Get the next element of the iterator
 * @param i Pointer to a xcb_host_iterator_t
 *
 * Get the next element in the iterator. The member rem is
 * decreased by one. The member data points to the next
 * element. The member index is increased by sizeof(xcb_host_t)
 */

/*****************************************************************************
 **
 ** void xcb_host_next
 ** 
 ** @param xcb_host_iterator_t *i
 ** @returns void
 **
 *****************************************************************************/
 
void
xcb_host_next (xcb_host_iterator_t *i  /**< */);

/**
 * Return the iterator pointing to the last element
 * @param i An xcb_host_iterator_t
 * @return  The iterator pointing to the last element
 *
 * Set the current element in the iterator to the last element.
 * The member rem is set to 0. The member data points to the
 * last element.
 */

/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_host_end
 ** 
 ** @param xcb_host_iterator_t i
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_host_end (xcb_host_iterator_t i  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_list_hosts_cookie_t xcb_list_hosts
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_list_hosts_cookie_t
 **
 *****************************************************************************/
 
xcb_list_hosts_cookie_t
xcb_list_hosts (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_list_hosts_cookie_t xcb_list_hosts_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_list_hosts_cookie_t
 **
 *****************************************************************************/
 
xcb_list_hosts_cookie_t
xcb_list_hosts_unchecked (xcb_connection_t *c  /**< */);


/*****************************************************************************
 **
 ** int xcb_list_hosts_hosts_length
 ** 
 ** @param const xcb_list_hosts_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_list_hosts_hosts_length (const xcb_list_hosts_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_host_iterator_t xcb_list_hosts_hosts_iterator
 ** 
 ** @param const xcb_list_hosts_reply_t *R
 ** @returns xcb_host_iterator_t
 **
 *****************************************************************************/
 
xcb_host_iterator_t
xcb_list_hosts_hosts_iterator (const xcb_list_hosts_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_list_hosts_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_list_hosts_reply_t * xcb_list_hosts_reply
 ** 
 ** @param xcb_connection_t         *c
 ** @param xcb_list_hosts_cookie_t   cookie
 ** @param xcb_generic_error_t     **e
 ** @returns xcb_list_hosts_reply_t *
 **
 *****************************************************************************/
 
xcb_list_hosts_reply_t *
xcb_list_hosts_reply (xcb_connection_t         *c  /**< */,
                      xcb_list_hosts_cookie_t   cookie  /**< */,
                      xcb_generic_error_t     **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_access_control_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_access_control_checked (xcb_connection_t *c  /**< */,
                                uint8_t           mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_access_control
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_access_control (xcb_connection_t *c  /**< */,
                        uint8_t           mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_close_down_mode_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_close_down_mode_checked (xcb_connection_t *c  /**< */,
                                 uint8_t           mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_set_close_down_mode
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_set_close_down_mode (xcb_connection_t *c  /**< */,
                         uint8_t           mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_kill_client_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint32_t          resource
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_kill_client_checked (xcb_connection_t *c  /**< */,
                         uint32_t          resource  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_kill_client
 ** 
 ** @param xcb_connection_t *c
 ** @param uint32_t          resource
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_kill_client (xcb_connection_t *c  /**< */,
                 uint32_t          resource  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_rotate_properties_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param uint16_t          atoms_len
 ** @param int16_t           delta
 ** @param const xcb_atom_t *atoms
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_rotate_properties_checked (xcb_connection_t *c  /**< */,
                               xcb_window_t      window  /**< */,
                               uint16_t          atoms_len  /**< */,
                               int16_t           delta  /**< */,
                               const xcb_atom_t *atoms  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_rotate_properties
 ** 
 ** @param xcb_connection_t *c
 ** @param xcb_window_t      window
 ** @param uint16_t          atoms_len
 ** @param int16_t           delta
 ** @param const xcb_atom_t *atoms
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_rotate_properties (xcb_connection_t *c  /**< */,
                       xcb_window_t      window  /**< */,
                       uint16_t          atoms_len  /**< */,
                       int16_t           delta  /**< */,
                       const xcb_atom_t *atoms  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_force_screen_saver_checked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_force_screen_saver_checked (xcb_connection_t *c  /**< */,
                                uint8_t           mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_force_screen_saver
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           mode
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_force_screen_saver (xcb_connection_t *c  /**< */,
                        uint8_t           mode  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_set_pointer_mapping_cookie_t xcb_set_pointer_mapping
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           map_len
 ** @param const uint8_t    *map
 ** @returns xcb_set_pointer_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_set_pointer_mapping_cookie_t
xcb_set_pointer_mapping (xcb_connection_t *c  /**< */,
                         uint8_t           map_len  /**< */,
                         const uint8_t    *map  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_set_pointer_mapping_cookie_t xcb_set_pointer_mapping_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @param uint8_t           map_len
 ** @param const uint8_t    *map
 ** @returns xcb_set_pointer_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_set_pointer_mapping_cookie_t
xcb_set_pointer_mapping_unchecked (xcb_connection_t *c  /**< */,
                                   uint8_t           map_len  /**< */,
                                   const uint8_t    *map  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_set_pointer_mapping_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_set_pointer_mapping_reply_t * xcb_set_pointer_mapping_reply
 ** 
 ** @param xcb_connection_t                  *c
 ** @param xcb_set_pointer_mapping_cookie_t   cookie
 ** @param xcb_generic_error_t              **e
 ** @returns xcb_set_pointer_mapping_reply_t *
 **
 *****************************************************************************/
 
xcb_set_pointer_mapping_reply_t *
xcb_set_pointer_mapping_reply (xcb_connection_t                  *c  /**< */,
                               xcb_set_pointer_mapping_cookie_t   cookie  /**< */,
                               xcb_generic_error_t              **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_pointer_mapping_cookie_t xcb_get_pointer_mapping
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_pointer_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_get_pointer_mapping_cookie_t
xcb_get_pointer_mapping (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_pointer_mapping_cookie_t xcb_get_pointer_mapping_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_pointer_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_get_pointer_mapping_cookie_t
xcb_get_pointer_mapping_unchecked (xcb_connection_t *c  /**< */);


/*****************************************************************************
 **
 ** uint8_t * xcb_get_pointer_mapping_map
 ** 
 ** @param const xcb_get_pointer_mapping_reply_t *R
 ** @returns uint8_t *
 **
 *****************************************************************************/
 
uint8_t *
xcb_get_pointer_mapping_map (const xcb_get_pointer_mapping_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_get_pointer_mapping_map_length
 ** 
 ** @param const xcb_get_pointer_mapping_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_get_pointer_mapping_map_length (const xcb_get_pointer_mapping_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_get_pointer_mapping_map_end
 ** 
 ** @param const xcb_get_pointer_mapping_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_get_pointer_mapping_map_end (const xcb_get_pointer_mapping_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_pointer_mapping_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_pointer_mapping_reply_t * xcb_get_pointer_mapping_reply
 ** 
 ** @param xcb_connection_t                  *c
 ** @param xcb_get_pointer_mapping_cookie_t   cookie
 ** @param xcb_generic_error_t              **e
 ** @returns xcb_get_pointer_mapping_reply_t *
 **
 *****************************************************************************/
 
xcb_get_pointer_mapping_reply_t *
xcb_get_pointer_mapping_reply (xcb_connection_t                  *c  /**< */,
                               xcb_get_pointer_mapping_cookie_t   cookie  /**< */,
                               xcb_generic_error_t              **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_set_modifier_mapping_cookie_t xcb_set_modifier_mapping
 ** 
 ** @param xcb_connection_t    *c
 ** @param uint8_t              keycodes_per_modifier
 ** @param const xcb_keycode_t *keycodes
 ** @returns xcb_set_modifier_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_set_modifier_mapping_cookie_t
xcb_set_modifier_mapping (xcb_connection_t    *c  /**< */,
                          uint8_t              keycodes_per_modifier  /**< */,
                          const xcb_keycode_t *keycodes  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_set_modifier_mapping_cookie_t xcb_set_modifier_mapping_unchecked
 ** 
 ** @param xcb_connection_t    *c
 ** @param uint8_t              keycodes_per_modifier
 ** @param const xcb_keycode_t *keycodes
 ** @returns xcb_set_modifier_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_set_modifier_mapping_cookie_t
xcb_set_modifier_mapping_unchecked (xcb_connection_t    *c  /**< */,
                                    uint8_t              keycodes_per_modifier  /**< */,
                                    const xcb_keycode_t *keycodes  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_set_modifier_mapping_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_set_modifier_mapping_reply_t * xcb_set_modifier_mapping_reply
 ** 
 ** @param xcb_connection_t                   *c
 ** @param xcb_set_modifier_mapping_cookie_t   cookie
 ** @param xcb_generic_error_t               **e
 ** @returns xcb_set_modifier_mapping_reply_t *
 **
 *****************************************************************************/
 
xcb_set_modifier_mapping_reply_t *
xcb_set_modifier_mapping_reply (xcb_connection_t                   *c  /**< */,
                                xcb_set_modifier_mapping_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_get_modifier_mapping_cookie_t xcb_get_modifier_mapping
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_modifier_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_get_modifier_mapping_cookie_t
xcb_get_modifier_mapping (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will cause
 * a reply to be generated. Any returned error will be
 * placed in the event queue.
 */

/*****************************************************************************
 **
 ** xcb_get_modifier_mapping_cookie_t xcb_get_modifier_mapping_unchecked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_get_modifier_mapping_cookie_t
 **
 *****************************************************************************/
 
xcb_get_modifier_mapping_cookie_t
xcb_get_modifier_mapping_unchecked (xcb_connection_t *c  /**< */);


/*****************************************************************************
 **
 ** xcb_keycode_t * xcb_get_modifier_mapping_keycodes
 ** 
 ** @param const xcb_get_modifier_mapping_reply_t *R
 ** @returns xcb_keycode_t *
 **
 *****************************************************************************/
 
xcb_keycode_t *
xcb_get_modifier_mapping_keycodes (const xcb_get_modifier_mapping_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** int xcb_get_modifier_mapping_keycodes_length
 ** 
 ** @param const xcb_get_modifier_mapping_reply_t *R
 ** @returns int
 **
 *****************************************************************************/
 
int
xcb_get_modifier_mapping_keycodes_length (const xcb_get_modifier_mapping_reply_t *R  /**< */);


/*****************************************************************************
 **
 ** xcb_generic_iterator_t xcb_get_modifier_mapping_keycodes_end
 ** 
 ** @param const xcb_get_modifier_mapping_reply_t *R
 ** @returns xcb_generic_iterator_t
 **
 *****************************************************************************/
 
xcb_generic_iterator_t
xcb_get_modifier_mapping_keycodes_end (const xcb_get_modifier_mapping_reply_t *R  /**< */);

/**
 * Return the reply
 * @param c      The connection
 * @param cookie The cookie
 * @param e      The xcb_generic_error_t supplied
 *
 * Returns the reply of the request asked by
 * 
 * The parameter @p e supplied to this function must be NULL if
 * xcb_get_modifier_mapping_unchecked(). is used.
 * Otherwise, it stores the error if any.
 *
 * The returned value must be freed by the caller using free().
 */

/*****************************************************************************
 **
 ** xcb_get_modifier_mapping_reply_t * xcb_get_modifier_mapping_reply
 ** 
 ** @param xcb_connection_t                   *c
 ** @param xcb_get_modifier_mapping_cookie_t   cookie
 ** @param xcb_generic_error_t               **e
 ** @returns xcb_get_modifier_mapping_reply_t *
 **
 *****************************************************************************/
 
xcb_get_modifier_mapping_reply_t *
xcb_get_modifier_mapping_reply (xcb_connection_t                   *c  /**< */,
                                xcb_get_modifier_mapping_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 * This form can be used only if the request will not cause
 * a reply to be generated. Any returned error will be
 * saved for handling by xcb_request_check().
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_no_operation_checked
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_no_operation_checked (xcb_connection_t *c  /**< */);

/**
 * Delivers a request to the X server
 * @param c The connection
 * @return A cookie
 *
 * Delivers a request to the X server.
 * 
 */

/*****************************************************************************
 **
 ** xcb_void_cookie_t xcb_no_operation
 ** 
 ** @param xcb_connection_t *c
 ** @returns xcb_void_cookie_t
 **
 *****************************************************************************/
 
xcb_void_cookie_t
xcb_no_operation (xcb_connection_t *c  /**< */);


#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */
