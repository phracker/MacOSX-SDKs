/*
	Copyright:	(c) 1999-2013 Apple Inc. All rights reserved.
*/

#ifndef _GLIDISPATCH_H
#define _GLIDISPATCH_H

#include <OpenGL/gltypes.h>
#include <OpenGL/gliContext.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
** GL function dispatch table type
*/
typedef struct __GLIFunctionDispatchRec
{
	void (*accum)(GLIContext ctx, GLenum op, GLfloat value);
	void (*alpha_func)(GLIContext ctx, GLenum func, GLclampf ref);
	GLboolean (*are_textures_resident)(GLIContext ctx, GLsizei n, const GLuint *textures, GLboolean *residences);
	void (*array_element)(GLIContext ctx, GLint i);
	void (*begin)(GLIContext ctx, GLenum mode);
	void (*bind_texture)(GLIContext ctx, GLenum target, GLuint texture);
	void (*bitmap)(GLIContext ctx, GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
	void (*blend_func)(GLIContext ctx, GLenum sfactor, GLenum dfactor);
	void (*call_list)(GLIContext ctx, GLuint list);
	void (*call_lists)(GLIContext ctx, GLsizei n, GLenum type, const GLvoid *lists);
	void (*clear)(GLIContext ctx, GLbitfield mask);
	void (*clear_accum)(GLIContext ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void (*clear_color)(GLIContext ctx, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	void (*clear_depth)(GLIContext ctx, GLclampd depth);
	void (*clear_index)(GLIContext ctx, GLfloat c);
	void (*clear_stencil)(GLIContext ctx, GLint s);
	void (*clip_plane)(GLIContext ctx, GLenum plane, const GLdouble *equation);
	void (*color3b)(GLIContext ctx, GLbyte red, GLbyte green, GLbyte blue);
	void (*color3bv)(GLIContext ctx, const GLbyte *v);
	void (*color3d)(GLIContext ctx, GLdouble red, GLdouble green, GLdouble blue);
	void (*color3dv)(GLIContext ctx, const GLdouble *v);
	void (*color3f)(GLIContext ctx, GLfloat red, GLfloat green, GLfloat blue);
	void (*color3fv)(GLIContext ctx, const GLfloat *v);
	void (*color3i)(GLIContext ctx, GLint red, GLint green, GLint blue);
	void (*color3iv)(GLIContext ctx, const GLint *v);
	void (*color3s)(GLIContext ctx, GLshort red, GLshort green, GLshort blue);
	void (*color3sv)(GLIContext ctx, const GLshort *v);
	void (*color3ub)(GLIContext ctx, GLubyte red, GLubyte green, GLubyte blue);
	void (*color3ubv)(GLIContext ctx, const GLubyte *v);
	void (*color3ui)(GLIContext ctx, GLuint red, GLuint green, GLuint blue);
	void (*color3uiv)(GLIContext ctx, const GLuint *v);
	void (*color3us)(GLIContext ctx, GLushort red, GLushort green, GLushort blue);
	void (*color3usv)(GLIContext ctx, const GLushort *v);
	void (*color4b)(GLIContext ctx, GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
	void (*color4bv)(GLIContext ctx, const GLbyte *v);
	void (*color4d)(GLIContext ctx, GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
	void (*color4dv)(GLIContext ctx, const GLdouble *v);
	void (*color4f)(GLIContext ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void (*color4fv)(GLIContext ctx, const GLfloat *v);
	void (*color4i)(GLIContext ctx, GLint red, GLint green, GLint blue, GLint alpha);
	void (*color4iv)(GLIContext ctx, const GLint *v);
	void (*color4s)(GLIContext ctx, GLshort red, GLshort green, GLshort blue, GLshort alpha);
	void (*color4sv)(GLIContext ctx, const GLshort *v);
	void (*color4ub)(GLIContext ctx, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
	void (*color4ubv)(GLIContext ctx, const GLubyte *v);
	void (*color4ui)(GLIContext ctx, GLuint red, GLuint green, GLuint blue, GLuint alpha);
	void (*color4uiv)(GLIContext ctx, const GLuint *v);
	void (*color4us)(GLIContext ctx, GLushort red, GLushort green, GLushort blue, GLushort alpha);
	void (*color4usv)(GLIContext ctx, const GLushort *v);
	void (*color_mask)(GLIContext ctx, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void (*color_material)(GLIContext ctx, GLenum face, GLenum mode);
	void (*color_pointer)(GLIContext ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*copy_pixels)(GLIContext ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
	void (*copy_tex_image1D)(GLIContext ctx, GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
	void (*copy_tex_image2D)(GLIContext ctx, GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	void (*copy_tex_sub_image1D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
	void (*copy_tex_sub_image2D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	void (*cull_face)(GLIContext ctx, GLenum mode);
	void (*delete_lists)(GLIContext ctx, GLuint list, GLsizei range);
	void (*delete_textures)(GLIContext ctx, GLsizei n, const GLuint *textures);
	void (*depth_func)(GLIContext ctx, GLenum func);
	void (*depth_mask)(GLIContext ctx, GLboolean flag);
	void (*depth_range)(GLIContext ctx, GLclampd zNear, GLclampd zFar);
	void (*disable)(GLIContext ctx, GLenum cap);
	void (*disable_client_state)(GLIContext ctx, GLenum array);
	void (*draw_arrays)(GLIContext ctx, GLenum mode, GLint first, GLsizei count);
	void (*draw_buffer)(GLIContext ctx, GLenum mode);
	void (*draw_elements)(GLIContext ctx, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
	void (*draw_pixels)(GLIContext ctx, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	void (*edge_flag)(GLIContext ctx, GLboolean flag);
	void (*edge_flag_pointer)(GLIContext ctx, GLsizei stride, const GLvoid *pointer);
	void (*edge_flagv)(GLIContext ctx, const GLboolean *flag);
	void (*enable)(GLIContext ctx, GLenum cap);
	void (*enable_client_state)(GLIContext ctx, GLenum array);
	void (*end)(GLIContext ctx);
	void (*end_list)(GLIContext ctx);
	void (*eval_coord1d)(GLIContext ctx, GLdouble u);
	void (*eval_coord1dv)(GLIContext ctx, const GLdouble *u);
	void (*eval_coord1f)(GLIContext ctx, GLfloat u);
	void (*eval_coord1fv)(GLIContext ctx, const GLfloat *u);
	void (*eval_coord2d)(GLIContext ctx, GLdouble u, GLdouble v);
	void (*eval_coord2dv)(GLIContext ctx, const GLdouble *u);
	void (*eval_coord2f)(GLIContext ctx, GLfloat u, GLfloat v);
	void (*eval_coord2fv)(GLIContext ctx, const GLfloat *u);
	void (*eval_mesh1)(GLIContext ctx, GLenum mode, GLint i1, GLint i2);
	void (*eval_mesh2)(GLIContext ctx, GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
	void (*eval_point1)(GLIContext ctx, GLint i);
	void (*eval_point2)(GLIContext ctx, GLint i, GLint j);
	void (*feedback_buffer)(GLIContext ctx, GLsizei size, GLenum type, GLfloat *buffer);
	void (*finish)(GLIContext ctx);
	void (*flush)(GLIContext ctx);
	void (*fogf)(GLIContext ctx, GLenum pname, GLfloat param);
	void (*fogfv)(GLIContext ctx, GLenum pname, const GLfloat *params);
	void (*fogi)(GLIContext ctx, GLenum pname, GLint param);
	void (*fogiv)(GLIContext ctx, GLenum pname, const GLint *params);
	void (*front_face)(GLIContext ctx, GLenum mode);
	void (*frustum)(GLIContext ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	GLuint (*gen_lists)(GLIContext ctx, GLsizei range);
	void (*gen_textures)(GLIContext ctx, GLsizei n, GLuint *textures);
	void (*get_booleanv)(GLIContext ctx, GLenum pname, GLboolean *params);
	void (*get_clip_plane)(GLIContext ctx, GLenum plane, GLdouble *equation);
	void (*get_doublev)(GLIContext ctx, GLenum pname, GLdouble *params);
	GLenum (*get_error)(GLIContext ctx);
	void (*get_floatv)(GLIContext ctx, GLenum pname, GLfloat *params);
	void (*get_integerv)(GLIContext ctx, GLenum pname, GLint *params);
	void (*get_lightfv)(GLIContext ctx, GLenum light, GLenum pname, GLfloat *params);
	void (*get_lightiv)(GLIContext ctx, GLenum light, GLenum pname, GLint *params);
	void (*get_mapdv)(GLIContext ctx, GLenum target, GLenum query, GLdouble *v);
	void (*get_mapfv)(GLIContext ctx, GLenum target, GLenum query, GLfloat *v);
	void (*get_mapiv)(GLIContext ctx, GLenum target, GLenum query, GLint *v);
	void (*get_materialfv)(GLIContext ctx, GLenum face, GLenum pname, GLfloat *params);
	void (*get_materialiv)(GLIContext ctx, GLenum face, GLenum pname, GLint *params);
	void (*get_pixel_mapfv)(GLIContext ctx, GLenum map, GLfloat *values);
	void (*get_pixel_mapuiv)(GLIContext ctx, GLenum map, GLuint *values);
	void (*get_pixel_mapusv)(GLIContext ctx, GLenum map, GLushort *values);
	void (*get_pointerv)(GLIContext ctx, GLenum pname, GLvoid **params);
	void (*get_polygon_stipple)(GLIContext ctx, GLubyte *mask);
	const GLubyte* (*get_string)(GLIContext ctx, GLenum name);
	void (*get_tex_envfv)(GLIContext ctx, GLenum target, GLenum pname, GLfloat *params);
	void (*get_tex_enviv)(GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*get_tex_gendv)(GLIContext ctx, GLenum coord, GLenum pname, GLdouble *params);
	void (*get_tex_genfv)(GLIContext ctx, GLenum coord, GLenum pname, GLfloat *params);
	void (*get_tex_geniv)(GLIContext ctx, GLenum coord, GLenum pname, GLint *params);
	void (*get_tex_image)(GLIContext ctx, GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
	void (*get_tex_level_parameterfv)(GLIContext ctx, GLenum target, GLint level, GLenum pname, GLfloat *params);
	void (*get_tex_level_parameteriv)(GLIContext ctx, GLenum target, GLint level, GLenum pname, GLint *params);
	void (*get_tex_parameterfv)(GLIContext ctx, GLenum target, GLenum pname, GLfloat *params);
	void (*get_tex_parameteriv)(GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*hint)(GLIContext ctx, GLenum target, GLenum mode);
	void (*index_mask)(GLIContext ctx, GLuint mask);
	void (*index_pointer)(GLIContext ctx, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*indexd)(GLIContext ctx, GLdouble c);
	void (*indexdv)(GLIContext ctx, const GLdouble *c);
	void (*indexf)(GLIContext ctx, GLfloat c);
	void (*indexfv)(GLIContext ctx, const GLfloat *c);
	void (*indexi)(GLIContext ctx, GLint c);
	void (*indexiv)(GLIContext ctx, const GLint *c);
	void (*indexs)(GLIContext ctx, GLshort c);
	void (*indexsv)(GLIContext ctx, const GLshort *c);
	void (*indexub)(GLIContext ctx, GLubyte c);
	void (*indexubv)(GLIContext ctx, const GLubyte *c);
	void (*init_names)(GLIContext ctx);
	void (*interleaved_arrays)(GLIContext ctx, GLenum format, GLsizei stride, const GLvoid *pointer);
	GLboolean (*is_enabled)(GLIContext ctx, GLenum cap);
	GLboolean (*is_list)(GLIContext ctx, GLuint list);
	GLboolean (*is_texture)(GLIContext ctx, GLuint texture);
	void (*light_modelf)(GLIContext ctx, GLenum pname, GLfloat param);
	void (*light_modelfv)(GLIContext ctx, GLenum pname, const GLfloat *params);
	void (*light_modeli)(GLIContext ctx, GLenum pname, GLint param);
	void (*light_modeliv)(GLIContext ctx, GLenum pname, const GLint *params);
	void (*lightf)(GLIContext ctx, GLenum light, GLenum pname, GLfloat param);
	void (*lightfv)(GLIContext ctx, GLenum light, GLenum pname, const GLfloat *params);
	void (*lighti)(GLIContext ctx, GLenum light, GLenum pname, GLint param);
	void (*lightiv)(GLIContext ctx, GLenum light, GLenum pname, const GLint *params);
	void (*line_stipple)(GLIContext ctx, GLint factor, GLushort pattern);
	void (*line_width)(GLIContext ctx, GLfloat width);
	void (*list_base)(GLIContext ctx, GLuint base);
	void (*load_identity)(GLIContext ctx);
	void (*load_matrixd)(GLIContext ctx, const GLdouble *m);
	void (*load_matrixf)(GLIContext ctx, const GLfloat *m);
	void (*load_name)(GLIContext ctx, GLuint name);
	void (*logic_op)(GLIContext ctx, GLenum opcode);
	void (*map1d)(GLIContext ctx, GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
	void (*map1f)(GLIContext ctx, GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
	void (*map2d)(GLIContext ctx, GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
	void (*map2f)(GLIContext ctx, GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
	void (*map_grid1d)(GLIContext ctx, GLint un, GLdouble u1, GLdouble u2);
	void (*map_grid1f)(GLIContext ctx, GLint un, GLfloat u1, GLfloat u2);
	void (*map_grid2d)(GLIContext ctx, GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
	void (*map_grid2f)(GLIContext ctx, GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
	void (*materialf)(GLIContext ctx, GLenum face, GLenum pname, GLfloat param);
	void (*materialfv)(GLIContext ctx, GLenum face, GLenum pname, const GLfloat *params);
	void (*materiali)(GLIContext ctx, GLenum face, GLenum pname, GLint param);
	void (*materialiv)(GLIContext ctx, GLenum face, GLenum pname, const GLint *params);
	void (*matrix_mode)(GLIContext ctx, GLenum mode);
	void (*mult_matrixd)(GLIContext ctx, const GLdouble *m);
	void (*mult_matrixf)(GLIContext ctx, const GLfloat *m);
	void (*new_list)(GLIContext ctx, GLuint list, GLenum mode);
	void (*normal3b)(GLIContext ctx, GLbyte nx, GLbyte ny, GLbyte nz);
	void (*normal3bv)(GLIContext ctx, const GLbyte *v);
	void (*normal3d)(GLIContext ctx, GLdouble nx, GLdouble ny, GLdouble nz);
	void (*normal3dv)(GLIContext ctx, const GLdouble *v);
	void (*normal3f)(GLIContext ctx, GLfloat nx, GLfloat ny, GLfloat nz);
	void (*normal3fv)(GLIContext ctx, const GLfloat *v);
	void (*normal3i)(GLIContext ctx, GLint nx, GLint ny, GLint nz);
	void (*normal3iv)(GLIContext ctx, const GLint *v);
	void (*normal3s)(GLIContext ctx, GLshort nx, GLshort ny, GLshort nz);
	void (*normal3sv)(GLIContext ctx, const GLshort *v);
	void (*normal_pointer)(GLIContext ctx, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*ortho)(GLIContext ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void (*pass_through)(GLIContext ctx, GLfloat token);
	void (*pixel_mapfv)(GLIContext ctx, GLenum map, GLsizei mapsize, const GLfloat *values);
	void (*pixel_mapuiv)(GLIContext ctx, GLenum map, GLsizei mapsize, const GLuint *values);
	void (*pixel_mapusv)(GLIContext ctx, GLenum map, GLsizei mapsize, const GLushort *values);
	void (*pixel_storef)(GLIContext ctx, GLenum pname, GLfloat param);
	void (*pixel_storei)(GLIContext ctx, GLenum pname, GLint param);
	void (*pixel_transferf)(GLIContext ctx, GLenum pname, GLfloat param);
	void (*pixel_transferi)(GLIContext ctx, GLenum pname, GLint param);
	void (*pixel_zoom)(GLIContext ctx, GLfloat xfactor, GLfloat yfactor);
	void (*point_size)(GLIContext ctx, GLfloat size);
	void (*polygon_mode)(GLIContext ctx, GLenum face, GLenum mode);
	void (*polygon_offset)(GLIContext ctx, GLfloat factor, GLfloat units);
	void (*polygon_stipple)(GLIContext ctx, const GLubyte *mask);
	void (*pop_attrib)(GLIContext ctx);
	void (*pop_client_attrib)(GLIContext ctx);
	void (*pop_matrix)(GLIContext ctx);
	void (*pop_name)(GLIContext ctx);
	void (*prioritize_textures)(GLIContext ctx, GLsizei n, const GLuint *textures, const GLclampf *priorities);
	void (*push_attrib)(GLIContext ctx, GLbitfield mask);
	void (*push_client_attrib)(GLIContext ctx, GLbitfield mask);
	void (*push_matrix)(GLIContext ctx);
	void (*push_name)(GLIContext ctx, GLuint name);
	void (*raster_pos2d)(GLIContext ctx, GLdouble x, GLdouble y);
	void (*raster_pos2dv)(GLIContext ctx, const GLdouble *v);
	void (*raster_pos2f)(GLIContext ctx, GLfloat x, GLfloat y);
	void (*raster_pos2fv)(GLIContext ctx, const GLfloat *v);
	void (*raster_pos2i)(GLIContext ctx, GLint x, GLint y);
	void (*raster_pos2iv)(GLIContext ctx, const GLint *v);
	void (*raster_pos2s)(GLIContext ctx, GLshort x, GLshort y);
	void (*raster_pos2sv)(GLIContext ctx, const GLshort *v);
	void (*raster_pos3d)(GLIContext ctx, GLdouble x, GLdouble y, GLdouble z);
	void (*raster_pos3dv)(GLIContext ctx, const GLdouble *v);
	void (*raster_pos3f)(GLIContext ctx, GLfloat x, GLfloat y, GLfloat z);
	void (*raster_pos3fv)(GLIContext ctx, const GLfloat *v);
	void (*raster_pos3i)(GLIContext ctx, GLint x, GLint y, GLint z);
	void (*raster_pos3iv)(GLIContext ctx, const GLint *v);
	void (*raster_pos3s)(GLIContext ctx, GLshort x, GLshort y, GLshort z);
	void (*raster_pos3sv)(GLIContext ctx, const GLshort *v);
	void (*raster_pos4d)(GLIContext ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void (*raster_pos4dv)(GLIContext ctx, const GLdouble *v);
	void (*raster_pos4f)(GLIContext ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void (*raster_pos4fv)(GLIContext ctx, const GLfloat *v);
	void (*raster_pos4i)(GLIContext ctx, GLint x, GLint y, GLint z, GLint w);
	void (*raster_pos4iv)(GLIContext ctx, const GLint *v);
	void (*raster_pos4s)(GLIContext ctx, GLshort x, GLshort y, GLshort z, GLshort w);
	void (*raster_pos4sv)(GLIContext ctx, const GLshort *v);
	void (*read_buffer)(GLIContext ctx, GLenum mode);
	void (*read_pixels)(GLIContext ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
	void (*rectd)(GLIContext ctx, GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	void (*rectdv)(GLIContext ctx, const GLdouble *v1, const GLdouble *v2);
	void (*rectf)(GLIContext ctx, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void (*rectfv)(GLIContext ctx, const GLfloat *v1, const GLfloat *v2);
	void (*recti)(GLIContext ctx, GLint x1, GLint y1, GLint x2, GLint y2);
	void (*rectiv)(GLIContext ctx, const GLint *v1, const GLint *v2);
	void (*rects)(GLIContext ctx, GLshort x1, GLshort y1, GLshort x2, GLshort y2);
	void (*rectsv)(GLIContext ctx, const GLshort *v1, const GLshort *v2);
	GLint (*render_mode)(GLIContext ctx, GLenum mode);
	void (*rotated)(GLIContext ctx, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
	void (*rotatef)(GLIContext ctx, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void (*scaled)(GLIContext ctx, GLdouble x, GLdouble y, GLdouble z);
	void (*scalef)(GLIContext ctx, GLfloat x, GLfloat y, GLfloat z);
	void (*scissor)(GLIContext ctx, GLint x, GLint y, GLsizei width, GLsizei height);
	void (*select_buffer)(GLIContext ctx, GLsizei size, GLuint *buffer);
	void (*shade_model)(GLIContext ctx, GLenum mode);
	void (*stencil_func)(GLIContext ctx, GLenum func, GLint ref, GLuint mask);
	void (*stencil_mask)(GLIContext ctx, GLuint mask);
	void (*stencil_op)(GLIContext ctx, GLenum fail, GLenum zfail, GLenum zpass);
	void (*tex_coord1d)(GLIContext ctx, GLdouble s);
	void (*tex_coord1dv)(GLIContext ctx, const GLdouble *v);
	void (*tex_coord1f)(GLIContext ctx, GLfloat s);
	void (*tex_coord1fv)(GLIContext ctx, const GLfloat *v);
	void (*tex_coord1i)(GLIContext ctx, GLint s);
	void (*tex_coord1iv)(GLIContext ctx, const GLint *v);
	void (*tex_coord1s)(GLIContext ctx, GLshort s);
	void (*tex_coord1sv)(GLIContext ctx, const GLshort *v);
	void (*tex_coord2d)(GLIContext ctx, GLdouble s, GLdouble t);
	void (*tex_coord2dv)(GLIContext ctx, const GLdouble *v);
	void (*tex_coord2f)(GLIContext ctx, GLfloat s, GLfloat t);
	void (*tex_coord2fv)(GLIContext ctx, const GLfloat *v);
	void (*tex_coord2i)(GLIContext ctx, GLint s, GLint t);
	void (*tex_coord2iv)(GLIContext ctx, const GLint *v);
	void (*tex_coord2s)(GLIContext ctx, GLshort s, GLshort t);
	void (*tex_coord2sv)(GLIContext ctx, const GLshort *v);
	void (*tex_coord3d)(GLIContext ctx, GLdouble s, GLdouble t, GLdouble r);
	void (*tex_coord3dv)(GLIContext ctx, const GLdouble *v);
	void (*tex_coord3f)(GLIContext ctx, GLfloat s, GLfloat t, GLfloat r);
	void (*tex_coord3fv)(GLIContext ctx, const GLfloat *v);
	void (*tex_coord3i)(GLIContext ctx, GLint s, GLint t, GLint r);
	void (*tex_coord3iv)(GLIContext ctx, const GLint *v);
	void (*tex_coord3s)(GLIContext ctx, GLshort s, GLshort t, GLshort r);
	void (*tex_coord3sv)(GLIContext ctx, const GLshort *v);
	void (*tex_coord4d)(GLIContext ctx, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
	void (*tex_coord4dv)(GLIContext ctx, const GLdouble *v);
	void (*tex_coord4f)(GLIContext ctx, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	void (*tex_coord4fv)(GLIContext ctx, const GLfloat *v);
	void (*tex_coord4i)(GLIContext ctx, GLint s, GLint t, GLint r, GLint q);
	void (*tex_coord4iv)(GLIContext ctx, const GLint *v);
	void (*tex_coord4s)(GLIContext ctx, GLshort s, GLshort t, GLshort r, GLshort q);
	void (*tex_coord4sv)(GLIContext ctx, const GLshort *v);
	void (*tex_coord_pointer)(GLIContext ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*tex_envf)(GLIContext ctx, GLenum target, GLenum pname, GLfloat param);
	void (*tex_envfv)(GLIContext ctx, GLenum target, GLenum pname, const GLfloat *params);
	void (*tex_envi)(GLIContext ctx, GLenum target, GLenum pname, GLint param);
	void (*tex_enviv)(GLIContext ctx, GLenum target, GLenum pname, const GLint *params);
	void (*tex_gend)(GLIContext ctx, GLenum coord, GLenum pname, GLdouble param);
	void (*tex_gendv)(GLIContext ctx, GLenum coord, GLenum pname, const GLdouble *params);
	void (*tex_genf)(GLIContext ctx, GLenum coord, GLenum pname, GLfloat param);
	void (*tex_genfv)(GLIContext ctx, GLenum coord, GLenum pname, const GLfloat *params);
	void (*tex_geni)(GLIContext ctx, GLenum coord, GLenum pname, GLint param);
	void (*tex_geniv)(GLIContext ctx, GLenum coord, GLenum pname, const GLint *params);
	void (*tex_image1D)(GLIContext ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	void (*tex_image2D)(GLIContext ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	void (*tex_parameterf)(GLIContext ctx, GLenum target, GLenum pname, GLfloat param);
	void (*tex_parameterfv)(GLIContext ctx, GLenum target, GLenum pname, const GLfloat *params);
	void (*tex_parameteri)(GLIContext ctx, GLenum target, GLenum pname, GLint param);
	void (*tex_parameteriv)(GLIContext ctx, GLenum target, GLenum pname, const GLint *params);
	void (*tex_sub_image1D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
	void (*tex_sub_image2D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	void (*translated)(GLIContext ctx, GLdouble x, GLdouble y, GLdouble z);
	void (*translatef)(GLIContext ctx, GLfloat x, GLfloat y, GLfloat z);
	void (*vertex2d)(GLIContext ctx, GLdouble x, GLdouble y);
	void (*vertex2dv)(GLIContext ctx, const GLdouble *v);
	void (*vertex2f)(GLIContext ctx, GLfloat x, GLfloat y);
	void (*vertex2fv)(GLIContext ctx, const GLfloat *v);
	void (*vertex2i)(GLIContext ctx, GLint x, GLint y);
	void (*vertex2iv)(GLIContext ctx, const GLint *v);
	void (*vertex2s)(GLIContext ctx, GLshort x, GLshort y);
	void (*vertex2sv)(GLIContext ctx, const GLshort *v);
	void (*vertex3d)(GLIContext ctx, GLdouble x, GLdouble y, GLdouble z);
	void (*vertex3dv)(GLIContext ctx, const GLdouble *v);
	void (*vertex3f)(GLIContext ctx, GLfloat x, GLfloat y, GLfloat z);
	void (*vertex3fv)(GLIContext ctx, const GLfloat *v);
	void (*vertex3i)(GLIContext ctx, GLint x, GLint y, GLint z);
	void (*vertex3iv)(GLIContext ctx, const GLint *v);
	void (*vertex3s)(GLIContext ctx, GLshort x, GLshort y, GLshort z);
	void (*vertex3sv)(GLIContext ctx, const GLshort *v);
	void (*vertex4d)(GLIContext ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void (*vertex4dv)(GLIContext ctx, const GLdouble *v);
	void (*vertex4f)(GLIContext ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void (*vertex4fv)(GLIContext ctx, const GLfloat *v);
	void (*vertex4i)(GLIContext ctx, GLint x, GLint y, GLint z, GLint w);
	void (*vertex4iv)(GLIContext ctx, const GLint *v);
	void (*vertex4s)(GLIContext ctx, GLshort x, GLshort y, GLshort z, GLshort w);
	void (*vertex4sv)(GLIContext ctx, const GLshort *v);
	void (*vertex_pointer)(GLIContext ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*viewport)(GLIContext ctx, GLint x, GLint y, GLsizei width, GLsizei height);
	void (*blend_func_separate)(GLIContext ctx, GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
	void (*blend_color)(GLIContext ctx, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	void (*blend_equation)(GLIContext ctx, GLenum mode);
	void (*lock_arrays_EXT)(GLIContext ctx, GLint first, GLsizei count);
	void (*unlock_arrays_EXT)(GLIContext ctx);
	void (*client_active_texture)(GLIContext ctx, GLenum target);
	void (*active_texture)(GLIContext ctx, GLenum target);
	void (*multi_tex_coord1d)(GLIContext ctx, GLenum target, GLdouble s);
	void (*multi_tex_coord1dv)(GLIContext ctx, GLenum target, const GLdouble *v);
	void (*multi_tex_coord1f)(GLIContext ctx, GLenum target, GLfloat s);
	void (*multi_tex_coord1fv)(GLIContext ctx, GLenum target, const GLfloat *v);
	void (*multi_tex_coord1i)(GLIContext ctx, GLenum target, GLint s);
	void (*multi_tex_coord1iv)(GLIContext ctx, GLenum target, const GLint *v);
	void (*multi_tex_coord1s)(GLIContext ctx, GLenum target, GLshort s);
	void (*multi_tex_coord1sv)(GLIContext ctx, GLenum target, const GLshort *v);
	void (*multi_tex_coord2d)(GLIContext ctx, GLenum target, GLdouble s, GLdouble t);
	void (*multi_tex_coord2dv)(GLIContext ctx, GLenum target, const GLdouble *v);
	void (*multi_tex_coord2f)(GLIContext ctx, GLenum target, GLfloat s, GLfloat t);
	void (*multi_tex_coord2fv)(GLIContext ctx, GLenum target, const GLfloat *v);
	void (*multi_tex_coord2i)(GLIContext ctx, GLenum target, GLint s, GLint t);
	void (*multi_tex_coord2iv)(GLIContext ctx, GLenum target, const GLint *v);
	void (*multi_tex_coord2s)(GLIContext ctx, GLenum target, GLshort s, GLshort t);
	void (*multi_tex_coord2sv)(GLIContext ctx, GLenum target, const GLshort *v);
	void (*multi_tex_coord3d)(GLIContext ctx, GLenum target, GLdouble s, GLdouble t, GLdouble r);
	void (*multi_tex_coord3dv)(GLIContext ctx, GLenum target, const GLdouble *v);
	void (*multi_tex_coord3f)(GLIContext ctx, GLenum target, GLfloat s, GLfloat t, GLfloat r);
	void (*multi_tex_coord3fv)(GLIContext ctx, GLenum target, const GLfloat *v);
	void (*multi_tex_coord3i)(GLIContext ctx, GLenum target, GLint s, GLint t, GLint r);
	void (*multi_tex_coord3iv)(GLIContext ctx, GLenum target, const GLint *v);
	void (*multi_tex_coord3s)(GLIContext ctx, GLenum target, GLshort s, GLshort t, GLshort r);
	void (*multi_tex_coord3sv)(GLIContext ctx, GLenum target, const GLshort *v);
	void (*multi_tex_coord4d)(GLIContext ctx, GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
	void (*multi_tex_coord4dv)(GLIContext ctx, GLenum target, const GLdouble *v);
	void (*multi_tex_coord4f)(GLIContext ctx, GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	void (*multi_tex_coord4fv)(GLIContext ctx, GLenum target, const GLfloat *v);
	void (*multi_tex_coord4i)(GLIContext ctx, GLenum target, GLint s, GLint t, GLint r, GLint q);
	void (*multi_tex_coord4iv)(GLIContext ctx, GLenum target, const GLint *v);
	void (*multi_tex_coord4s)(GLIContext ctx, GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
	void (*multi_tex_coord4sv)(GLIContext ctx, GLenum target, const GLshort *v);
	void (*load_transpose_matrixd)(GLIContext ctx, const GLdouble *m);
	void (*load_transpose_matrixf)(GLIContext ctx, const GLfloat *m);
	void (*mult_transpose_matrixd)(GLIContext ctx, const GLdouble *m);
	void (*mult_transpose_matrixf)(GLIContext ctx, const GLfloat *m);
	void (*compressed_tex_image3D)(GLIContext ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
	void (*compressed_tex_image2D)(GLIContext ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
	void (*compressed_tex_image1D)(GLIContext ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
	void (*compressed_tex_sub_image3D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
	void (*compressed_tex_sub_image2D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
	void (*compressed_tex_sub_image1D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
	void (*get_compressed_tex_image)(GLIContext ctx, GLenum target, GLint level, GLvoid *img);
	void (*secondary_color3b)(GLIContext ctx, GLbyte red, GLbyte green, GLbyte blue);
	void (*secondary_color3bv)(GLIContext ctx, const GLbyte *v);
	void (*secondary_color3d)(GLIContext ctx, GLdouble red, GLdouble green, GLdouble blue);
	void (*secondary_color3dv)(GLIContext ctx, const GLdouble *v);
	void (*secondary_color3f)(GLIContext ctx, GLfloat red, GLfloat green, GLfloat blue);
	void (*secondary_color3fv)(GLIContext ctx, const GLfloat *v);
	void (*secondary_color3i)(GLIContext ctx, GLint red, GLint green, GLint blue);
	void (*secondary_color3iv)(GLIContext ctx, const GLint *v);
	void (*secondary_color3s)(GLIContext ctx, GLshort red, GLshort green, GLshort blue);
	void (*secondary_color3sv)(GLIContext ctx, const GLshort *v);
	void (*secondary_color3ub)(GLIContext ctx, GLubyte red, GLubyte green, GLubyte blue);
	void (*secondary_color3ubv)(GLIContext ctx, const GLubyte *v);
	void (*secondary_color3ui)(GLIContext ctx, GLuint red, GLuint green, GLuint blue);
	void (*secondary_color3uiv)(GLIContext ctx, const GLuint *v);
	void (*secondary_color3us)(GLIContext ctx, GLushort red, GLushort green, GLushort blue);
	void (*secondary_color3usv)(GLIContext ctx, const GLushort *v);
	void (*secondary_color_pointer)(GLIContext ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*vertex_array_range_EXT)(GLIContext ctx, GLsizei count, const GLvoid *pointer);
	void (*flush_vertex_array_range_EXT)(GLIContext ctx, GLsizei count, const GLvoid *pointer);
	void (*draw_range_elements)(GLIContext ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
	void (*color_table)(GLIContext ctx, GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
	void (*color_table_parameterfv)(GLIContext ctx, GLenum target, GLenum pname, const GLfloat *params);
	void (*color_table_parameteriv)(GLIContext ctx, GLenum target, GLenum pname, const GLint *params);
	void (*copy_color_table)(GLIContext ctx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
	void (*get_color_table)(GLIContext ctx, GLenum target, GLenum format, GLenum type, GLvoid *table);
	void (*get_color_table_parameterfv)(GLIContext ctx, GLenum target, GLenum pname, GLfloat *params);
	void (*get_color_table_parameteriv)(GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*color_sub_table)(GLIContext ctx, GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
	void (*copy_color_sub_table)(GLIContext ctx, GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
	void (*convolution_filter1D)(GLIContext ctx, GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
	void (*convolution_filter2D)(GLIContext ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
	void (*convolution_parameterf)(GLIContext ctx, GLenum target, GLenum pname, GLfloat params);
	void (*convolution_parameterfv)(GLIContext ctx, GLenum target, GLenum pname, const GLfloat *params);
	void (*convolution_parameteri)(GLIContext ctx, GLenum target, GLenum pname, GLint params);
	void (*convolution_parameteriv)(GLIContext ctx, GLenum target, GLenum pname, const GLint *params);
	void (*copy_convolution_filter1D)(GLIContext ctx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
	void (*copy_convolution_filter2D)(GLIContext ctx, GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
	void (*get_convolution_filter)(GLIContext ctx, GLenum target, GLenum format, GLenum type, GLvoid *image);
	void (*get_convolution_parameterfv)(GLIContext ctx, GLenum target, GLenum pname, GLfloat *params);
	void (*get_convolution_parameteriv)(GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*get_separable_filter)(GLIContext ctx, GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
	void (*separable_filter2D)(GLIContext ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
	void (*get_histogram)(GLIContext ctx, GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
	void (*get_histogram_parameterfv)(GLIContext ctx, GLenum target, GLenum pname, GLfloat *params);
	void (*get_histogram_parameteriv)(GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*get_minmax)(GLIContext ctx, GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
	void (*get_minmax_parameterfv)(GLIContext ctx, GLenum target, GLenum pname, GLfloat *params);
	void (*get_minmax_parameteriv)(GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*histogram)(GLIContext ctx, GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
	void (*minmax)(GLIContext ctx, GLenum target, GLenum internalformat, GLboolean sink);
	void (*reset_histogram)(GLIContext ctx, GLenum target);
	void (*reset_minmax)(GLIContext ctx, GLenum target);
	void (*tex_image3D)(GLIContext ctx, GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	void (*tex_sub_image3D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
	void (*copy_tex_sub_image3D)(GLIContext ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	void (*get_uniform_indices) (GLIContext ctx, GLuint program, GLsizei uniformCount, const GLchar* const *uniformNames, GLuint* uniformIndices);
	void (*get_active_uniformsiv) (GLIContext ctx, GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params);
	void (*get_active_uniform_name) (GLIContext ctx, GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName);
	GLuint (*get_uniform_block_index) (GLIContext ctx, GLuint program, const GLchar* uniformBlockName);
	void (*get_active_uniform_blockiv) (GLIContext ctx, GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params);
	void (*get_active_uniform_block_name) (GLIContext ctx, GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName);
	void (*uniform_block_binding) (GLIContext ctx, GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
	void (*get_combiner_input_parameterfv_NV)(GLIContext ctx, GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
	void (*get_combiner_input_parameteriv_NV)(GLIContext ctx, GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
	void (*get_combiner_output_parameterfv_NV)(GLIContext ctx, GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
	void (*get_combiner_output_parameteriv_NV)(GLIContext ctx, GLenum stage, GLenum portion, GLenum pname, GLint *params);
	void (*get_final_combiner_input_parameterfv_NV)(GLIContext ctx, GLenum variable, GLenum pname, GLfloat *params);
	void (*get_final_combiner_input_parameteriv_NV)(GLIContext ctx, GLenum variable, GLenum pname, GLint *params);
	void (*combiner_stage_parameterfv_NV)(GLIContext ctx, GLenum stage, GLenum pname, const GLfloat *params);
	void (*get_combiner_stage_parameterfv_NV)(GLIContext ctx, GLenum stage, GLenum pname, GLfloat *params);
	void (*texture_range_APPLE)(GLIContext ctx, GLenum target, GLsizei length, const GLvoid *pointer);
	void (*get_tex_parameter_pointerv_APPLE)(GLIContext ctx, GLenum target, GLenum pname, GLvoid **params);
	void (*blend_equation_separate_EXT)(GLIContext ctx, GLenum equationRGB, GLenum equationAlpha);
	void (*sample_coverage)(GLIContext ctx, GLclampf value, GLboolean invert);
	void (*sample_pass)(GLIContext ctx, GLenum mode);
	void (*pn_trianglesi_ATI)(GLIContext ctx, GLenum pname, GLint param);
	void (*pn_trianglesf_ATI)(GLIContext ctx, GLenum pname, GLfloat param);
	void (*gen_fences_APPLE)(GLIContext ctx, GLsizei n, GLuint *fences);
	void (*delete_fences_APPLE)(GLIContext ctx, GLsizei n, const GLuint *fences);
	void (*set_fence_APPLE)(GLIContext ctx, GLuint fence);
	GLboolean (*is_fence_APPLE)(GLIContext ctx, GLuint fence);
	GLboolean (*test_fence_APPLE)(GLIContext ctx, GLuint fence);
	void (*finish_fence_APPLE)(GLIContext ctx, GLuint fence);
	GLboolean (*test_object_APPLE)(GLIContext ctx, GLenum object, GLuint name);
	void (*finish_object_APPLE)(GLIContext ctx, GLenum object, GLuint name);
	void (*bind_program_ARB)(GLIContext ctx, GLenum target, GLuint program);
	void (*delete_programs_ARB)(GLIContext ctx, GLsizei n, const GLuint *programs);
	void (*gen_programs_ARB)(GLIContext ctx, GLsizei n, GLuint *programs);
	GLboolean (*is_program_ARB)(GLIContext ctx, GLuint program);
	void (*vertex_attrib1s_ARB)(GLIContext ctx, GLuint index, GLshort x);
	void (*vertex_attrib1f_ARB)(GLIContext ctx, GLuint index, GLfloat x);
	void (*vertex_attrib1d_ARB)(GLIContext ctx, GLuint index, GLdouble x);
	void (*vertex_attrib2s_ARB)(GLIContext ctx, GLuint index, GLshort x, GLshort y);
	void (*vertex_attrib2f_ARB)(GLIContext ctx, GLuint index, GLfloat x, GLfloat y);
	void (*vertex_attrib2d_ARB)(GLIContext ctx, GLuint index, GLdouble x, GLdouble y);
	void (*vertex_attrib3s_ARB)(GLIContext ctx, GLuint index, GLshort x, GLshort y, GLshort z);
	void (*vertex_attrib3f_ARB)(GLIContext ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z);
	void (*vertex_attrib3d_ARB)(GLIContext ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z);
	void (*vertex_attrib4s_ARB)(GLIContext ctx, GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
	void (*vertex_attrib4f_ARB)(GLIContext ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void (*vertex_attrib4d_ARB)(GLIContext ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void (*vertex_attrib4Nub_ARB)(GLIContext ctx, GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
	void (*vertex_attrib1sv_ARB)(GLIContext ctx, GLuint index, const GLshort *v);
	void (*vertex_attrib1fv_ARB)(GLIContext ctx, GLuint index, const GLfloat *v);
	void (*vertex_attrib1dv_ARB)(GLIContext ctx, GLuint index, const GLdouble *v);
	void (*vertex_attrib2sv_ARB)(GLIContext ctx, GLuint index, const GLshort *v);
	void (*vertex_attrib2fv_ARB)(GLIContext ctx, GLuint index, const GLfloat *v);
	void (*vertex_attrib2dv_ARB)(GLIContext ctx, GLuint index, const GLdouble *v);
	void (*vertex_attrib3sv_ARB)(GLIContext ctx, GLuint index, const GLshort *v);
	void (*vertex_attrib3fv_ARB)(GLIContext ctx, GLuint index, const GLfloat *v);
	void (*vertex_attrib3dv_ARB)(GLIContext ctx, GLuint index, const GLdouble *v);
	void (*vertex_attrib4bv_ARB)(GLIContext ctx, GLuint index, const GLbyte *v);
	void (*vertex_attrib4sv_ARB)(GLIContext ctx, GLuint index, const GLshort *v);
	void (*vertex_attrib4iv_ARB)(GLIContext ctx, GLuint index, const GLint *v);
	void (*vertex_attrib4ubv_ARB)(GLIContext ctx, GLuint index, const GLubyte *v);
	void (*vertex_attrib4usv_ARB)(GLIContext ctx, GLuint index, const GLushort *v);
	void (*vertex_attrib4uiv_ARB)(GLIContext ctx, GLuint index, const GLuint *v);
	void (*vertex_attrib4fv_ARB)(GLIContext ctx, GLuint index, const GLfloat *v);
	void (*vertex_attrib4dv_ARB)(GLIContext ctx, GLuint index, const GLdouble *v);
	void (*vertex_attrib4Nbv_ARB)(GLIContext ctx, GLuint index, const GLbyte *v);
	void (*vertex_attrib4Nsv_ARB)(GLIContext ctx, GLuint index, const GLshort *v);
	void (*vertex_attrib4Niv_ARB)(GLIContext ctx, GLuint index, const GLint *v);
	void (*vertex_attrib4Nubv_ARB)(GLIContext ctx, GLuint index, const GLubyte *v);
	void (*vertex_attrib4Nusv_ARB)(GLIContext ctx, GLuint index, const GLushort *v);
	void (*vertex_attrib4Nuiv_ARB)(GLIContext ctx, GLuint index, const GLuint *v);
	void (*vertex_attrib_pointer_ARB)(GLIContext ctx, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
	void (*enable_vertex_attrib_array_ARB)(GLIContext ctx, GLuint index);
	void (*disable_vertex_attrib_array_ARB)(GLIContext ctx, GLuint index);
	void (*get_vertex_attribdv_ARB)(GLIContext ctx, GLuint index, GLenum pname, GLdouble *params);
	void (*get_vertex_attribfv_ARB)(GLIContext ctx, GLuint index, GLenum pname, GLfloat *params);
	void (*get_vertex_attribiv_ARB)(GLIContext ctx, GLuint index, GLenum pname, GLint *params);
	void (*get_vertex_attrib_pointerv_ARB)(GLIContext ctx, GLuint index, GLenum pname, GLvoid **pointer);
	void (*program_env_parameter4d_ARB)(GLIContext ctx, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void (*program_env_parameter4dv_ARB)(GLIContext ctx, GLenum target, GLuint index, const GLdouble *params);
	void (*program_env_parameter4f_ARB)(GLIContext ctx, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void (*program_env_parameter4fv_ARB)(GLIContext ctx, GLenum target, GLuint index, const GLfloat *params);
	void (*program_local_parameter4d_ARB)(GLIContext ctx, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void (*program_local_parameter4dv_ARB)(GLIContext ctx, GLenum target, GLuint index, const GLdouble *params);
	void (*program_local_parameter4f_ARB)(GLIContext ctx, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void (*program_local_parameter4fv_ARB)(GLIContext ctx, GLenum target, GLuint index, const GLfloat *params);
	void (*get_program_env_parameterdv_ARB)(GLIContext ctx, GLenum target, GLuint index, GLdouble *params);
	void (*get_program_env_parameterfv_ARB)(GLIContext ctx, GLenum target, GLuint index, GLfloat *params);
	void (*get_program_local_parameterdv_ARB)(GLIContext ctx, GLenum target, GLuint index, GLdouble *params);
	void (*get_program_local_parameterfv_ARB)(GLIContext ctx, GLenum target, GLuint index, GLfloat *params);
	void (*program_string_ARB)(GLIContext ctx, GLenum target, GLenum format, GLsizei len, const GLvoid* string);
	void (*get_program_string_ARB)(GLIContext ctx, GLenum target, GLenum pname, GLvoid *string);
	void (*get_programiv_ARB)(GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*enable_vertex_attrib_ARB)(GLIContext ctx, GLuint index, GLenum pname);
	void (*disable_vertex_attrib_ARB)(GLIContext ctx, GLuint index, GLenum pname);
	GLboolean (*is_vertex_attrib_enabled_ARB)(GLIContext ctx, GLuint index, GLenum pname);
	void (*map_vertex_attrib1d_ARB)(GLIContext ctx, GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
	void (*map_vertex_attrib1f_ARB)(GLIContext ctx, GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
	void (*map_vertex_attrib2d_ARB)(GLIContext ctx, GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
	void (*map_vertex_attrib2f_ARB)(GLIContext ctx, GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
	void (*point_parameterf)(GLIContext ctx, GLenum pname, GLfloat param);
	void (*point_parameterfv)(GLIContext ctx, GLenum pname, const GLfloat *params);
	void (*point_parameteri)(GLIContext ctx, GLenum pname, GLint param);
	void (*point_parameteriv)(GLIContext ctx, GLenum pname, const GLint *params);
	void (*fog_coordf)(GLIContext ctx, GLfloat coord);
	void (*fog_coordfv)(GLIContext ctx, const GLfloat *coord);
	void (*fog_coordd)(GLIContext ctx, GLdouble coord);
	void (*fog_coorddv)(GLIContext ctx, const GLdouble *coord);
	void (*fog_coord_pointer)(GLIContext ctx, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*vertex_array_parameteri_EXT)(GLIContext ctx, GLenum pname, GLint param);
	void (*bind_vertex_array_EXT)(GLIContext ctx, GLuint id);
	void (*delete_vertex_arrays_EXT)(GLIContext ctx, GLsizei n, const GLuint *ids);
	void (*gen_vertex_arrays_EXT)(GLIContext ctx, GLsizei n, GLuint *ids);
	GLboolean (*is_vertex_array_EXT)(GLIContext ctx, GLuint id);
	void (*element_pointer_APPLE)(GLIContext ctx, GLenum type, const GLvoid *pointer);
	void (*draw_element_array_APPLE)(GLIContext ctx, GLenum mode, GLint first, GLsizei count);
	void (*draw_range_element_array_APPLE)(GLIContext ctx, GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count);
	void (*weightbv_ARB)(GLIContext ctx, GLint size, const GLbyte *weights);
	void (*weightsv_ARB)(GLIContext ctx, GLint size, const GLshort *weights);
	void (*weightiv_ARB)(GLIContext ctx, GLint size, const GLint *weights);
	void (*weightfv_ARB)(GLIContext ctx, GLint size, const GLfloat *weights);
	void (*weightdv_ARB)(GLIContext ctx, GLint size, const GLdouble *weights);
	void (*weightubv_ARB)(GLIContext ctx, GLint size, const GLubyte *weights);
	void (*weightusv_ARB)(GLIContext ctx, GLint size, const GLushort *weights);
	void (*weightuiv_ARB)(GLIContext ctx, GLint size, const GLuint *weights);
	void (*weight_pointer_ARB)(GLIContext ctx, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*vertex_blend_ARB)(GLIContext ctx, GLint count);
	void (*multi_draw_arrays)(GLIContext ctx, GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
	void (*multi_draw_elements)(GLIContext ctx, GLenum mode, const GLsizei *count, GLenum type, const GLvoid* const *indices, GLsizei drawcount);
	void (*window_pos2d) (GLIContext ctx, GLdouble x, GLdouble y);
	void (*window_pos2dv) (GLIContext ctx, const GLdouble *v);
	void (*window_pos2f) (GLIContext ctx, GLfloat x, GLfloat y);
	void (*window_pos2fv) (GLIContext ctx, const GLfloat *v);
	void (*window_pos2i) (GLIContext ctx, GLint x, GLint y);
	void (*window_pos2iv) (GLIContext ctx, const GLint *v);
	void (*window_pos2s) (GLIContext ctx, GLshort x, GLshort y);
	void (*window_pos2sv) (GLIContext ctx, const GLshort *v);
	void (*window_pos3d) (GLIContext ctx, GLdouble x, GLdouble y, GLdouble z);
	void (*window_pos3dv) (GLIContext ctx, const GLdouble *v);
	void (*window_pos3f) (GLIContext ctx, GLfloat x, GLfloat y, GLfloat z);
	void (*window_pos3fv) (GLIContext ctx, const GLfloat *v);
	void (*window_pos3i) (GLIContext ctx, GLint x, GLint y, GLint z);
	void (*window_pos3iv) (GLIContext ctx, const GLint *v);
	void (*window_pos3s) (GLIContext ctx, GLshort x, GLshort y, GLshort z);
	void (*window_pos3sv) (GLIContext ctx, const GLshort *v);
	void (*active_stencil_face_EXT) (GLIContext ctx, GLenum face);
	void (*stencil_op_separate_ATI) (GLIContext ctx, GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
	void (*stencil_func_separate_ATI) (GLIContext ctx, GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask);
	void (*flush_render_APPLE) (GLIContext ctx);
	void (*finish_render_APPLE) (GLIContext ctx);
	void (*swap_APPLE)(GLIContext ctx);
	void (*delete_object_ARB) (GLIContext ctx, GLhandleARB obj);
	GLhandleARB (*get_handle_ARB) (GLIContext ctx, GLenum pname);
	void (*detach_object_ARB) (GLIContext ctx, GLhandleARB containerObj, GLhandleARB attachedObj);
	GLhandleARB (*create_shader_object_ARB) (GLIContext ctx, GLenum shaderType);
	void (*shader_source_ARB) (GLIContext ctx, GLhandleARB shaderObj, GLsizei count, const GLcharARB* const *string, const GLint *length);
	void (*compile_shader_ARB) (GLIContext ctx, GLhandleARB shaderObj);
	GLhandleARB (*create_program_object_ARB) (GLIContext ctx);
	void (*attach_object_ARB) (GLIContext ctx, GLhandleARB containerObj, GLhandleARB obj);
	void (*link_program_ARB) (GLIContext ctx, GLhandleARB programObj);
	void (*use_program_object_ARB) (GLIContext ctx, GLhandleARB programObj);
	void (*validate_program_ARB) (GLIContext ctx, GLhandleARB programObj);
	void (*uniform1f_ARB) (GLIContext ctx, GLint location, GLfloat v0);
	void (*uniform2f_ARB) (GLIContext ctx, GLint location, GLfloat v0, GLfloat v1);
	void (*uniform3f_ARB) (GLIContext ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	void (*uniform4f_ARB) (GLIContext ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void (*uniform1i_ARB) (GLIContext ctx, GLint location, GLint v0);
	void (*uniform2i_ARB) (GLIContext ctx, GLint location, GLint v0, GLint v1);
	void (*uniform3i_ARB) (GLIContext ctx, GLint location, GLint v0, GLint v1, GLint v2);
	void (*uniform4i_ARB) (GLIContext ctx, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	void (*uniform1fv_ARB) (GLIContext ctx, GLint location, GLsizei count, const GLfloat *value);
	void (*uniform2fv_ARB) (GLIContext ctx, GLint location, GLsizei count, const GLfloat *value);
	void (*uniform3fv_ARB) (GLIContext ctx, GLint location, GLsizei count, const GLfloat *value);
	void (*uniform4fv_ARB) (GLIContext ctx, GLint location, GLsizei count, const GLfloat *value);
	void (*uniform1iv_ARB) (GLIContext ctx, GLint location, GLsizei count, const GLint *value);
	void (*uniform2iv_ARB) (GLIContext ctx, GLint location, GLsizei count, const GLint *value);
	void (*uniform3iv_ARB) (GLIContext ctx, GLint location, GLsizei count, const GLint *value);
	void (*uniform4iv_ARB) (GLIContext ctx, GLint location, GLsizei count, const GLint *value);
	void (*uniform_matrix2fv_ARB) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*uniform_matrix3fv_ARB) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*uniform_matrix4fv_ARB) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*get_object_parameterfv_ARB) (GLIContext ctx, GLhandleARB obj, GLenum pname, GLfloat *params);
	void (*get_object_parameteriv_ARB) (GLIContext ctx, GLhandleARB obj, GLenum pname, GLint *params);
	void (*get_info_log_ARB) (GLIContext ctx, GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
	void (*get_attached_objects_ARB) (GLIContext ctx, GLhandleARB containerObj, GLsizei maxCount, GLsizei *count, GLhandleARB *obj);
	GLint (*get_uniform_location_ARB) (GLIContext ctx, GLhandleARB programObj, const GLcharARB *name);
	void (*get_active_uniform_ARB) (GLIContext ctx, GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
	void (*get_uniformfv_ARB) (GLIContext ctx, GLhandleARB programObj, GLint location, GLfloat *params);
	void (*get_uniformiv_ARB) (GLIContext ctx, GLhandleARB programObj, GLint location, GLint *params);
	void (*get_shader_source_ARB) (GLIContext ctx, GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *source);
	void (*bind_attrib_location_ARB) (GLIContext ctx, GLhandleARB programObj, GLuint index, const GLcharARB *name);
	void (*get_active_attrib_ARB) (GLIContext ctx, GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
	GLint (*get_attrib_location_ARB) (GLIContext ctx, GLhandleARB programObj, const GLcharARB *name);
	void (*clamp_color_ARB) (GLIContext ctx, GLenum target, GLenum clamp);
	void (*gen_queries) (GLIContext ctx, GLsizei n, GLuint *ids);
	void (*delete_queries) (GLIContext ctx, GLsizei n, const GLuint *ids);
	GLboolean (*is_query) (GLIContext ctx, GLuint id);
	void (*begin_query) (GLIContext ctx, GLenum target, GLuint id);
	void (*end_query) (GLIContext ctx, GLenum target);
	void (*get_queryiv) (GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*get_query_objectiv) (GLIContext ctx, GLuint id, GLenum pname, GLint *params);
	void (*get_query_objectuiv) (GLIContext ctx, GLuint id, GLenum pname, GLuint *params);
	void (*bind_buffer) (GLIContext ctx, GLenum target, GLuint buffer);
	void (*delete_buffers) (GLIContext ctx, GLsizei n, const GLuint *buffers);
	void (*gen_buffers) (GLIContext ctx, GLsizei n, GLuint *buffers);
	GLboolean (*is_buffer) (GLIContext ctx, GLuint buffer);
	void (*buffer_data) (GLIContext ctx, GLenum target, GLsizeiptrARB size, const GLvoid *data, GLenum usage);
	void (*buffer_sub_data) (GLIContext ctx, GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid *data);
	void (*get_buffer_sub_data) (GLIContext ctx, GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid *data);
	GLvoid *(*map_buffer) (GLIContext ctx, GLenum target, GLenum access);
	GLboolean (*unmap_buffer) (GLIContext ctx, GLenum target);
	void (*get_buffer_parameteriv) (GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*get_buffer_pointerv) (GLIContext ctx, GLenum target, GLenum pname, GLvoid **params);
	void (*depth_bounds_EXT) (GLIContext ctx, GLclampd zmin, GLclampd zmax);
	void (*draw_buffers_ARB) (GLIContext ctx, GLsizei n, const GLenum *bufs);
	
	GLboolean (*is_shader) (GLIContext ctx, GLuint shader);
	GLboolean (*is_program) (GLIContext ctx, GLuint program);
	void (*get_shaderiv) (GLIContext ctx, GLuint shader, GLenum pname, GLint *params);
	void (*get_programiv) (GLIContext ctx, GLuint program, GLenum pname, GLint *params);
	void (*get_shader_info_log) (GLIContext ctx, GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
	void (*get_program_info_log) (GLIContext ctx, GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

	void (*stencil_func_separate) (GLIContext ctx, GLenum face, GLenum func, GLint ref, GLuint mask);
	void (*stencil_mask_separate) (GLIContext ctx, GLenum face, GLuint mask);
	
	void (*multi_draw_element_array_APPLE)(GLIContext ctx, GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
	void (*multi_draw_range_element_array_APPLE)(GLIContext ctx, GLenum mode, GLuint start, GLuint end, const GLint *first, const GLsizei *count, GLsizei primcount);

	/* EXT_framebuffer_object */
	GLboolean (*is_renderbuffer_EXT) (GLIContext ctx, GLuint renderbuffer);
	void (*bind_renderbuffer_EXT) (GLIContext ctx, GLenum target, GLuint renderbuffer);
	void (*delete_renderbuffers_EXT) (GLIContext ctx, GLsizei n, const GLuint *renderbuffers);
	void (*gen_renderbuffers_EXT) (GLIContext ctx, GLsizei n, GLuint *renderbuffers);
	void (*renderbuffer_storage_EXT) (GLIContext ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
	void (*get_renderbuffer_parameteriv_EXT) (GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	GLboolean (*is_framebuffer_EXT) (GLIContext ctx, GLuint framebuffer);
	void (*bind_framebuffer_EXT) (GLIContext ctx, GLenum target, GLuint framebuffer);
	void (*delete_framebuffers_EXT) (GLIContext ctx, GLsizei n, const GLuint *framebuffers);
	void (*gen_framebuffers_EXT) (GLIContext ctx, GLsizei n, GLuint *framebuffers);
	GLenum (*check_framebuffer_status_EXT) (GLIContext ctx, GLenum target);
	void (*framebuffer_texture1D_EXT) (GLIContext ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	void (*framebuffer_texture2D_EXT) (GLIContext ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	void (*framebuffer_texture3D_EXT) (GLIContext ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
	void (*framebuffer_renderbuffer_EXT) (GLIContext ctx, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
	void (*get_framebuffer_attachment_parameteriv_EXT) (GLIContext ctx, GLenum target, GLenum attachment, GLenum pname, GLint *params);
	void (*generate_mipmap_EXT) (GLIContext ctx, GLenum target);

	void (*buffer_parameteri_APPLE) (GLIContext ctx, GLenum target, GLenum pname, GLint param);
	void (*flush_mapped_buffer_range_APPLE) (GLIContext ctx, GLenum target, GLintptr offset, GLsizeiptr size);

	void (*program_env_parameters4fv_EXT)(GLIContext ctx, GLenum target, GLuint index, GLsizei count, const GLfloat *params);
	void (*program_local_parameters4fv_EXT)(GLIContext ctx, GLenum target, GLuint index, GLsizei count, const GLfloat *params);

	GLenum (*object_purgeable_APPLE)(GLIContext ctx, GLenum objectType, GLuint name, GLenum option);
	GLenum (*object_unpurgeable_APPLE)(GLIContext ctx, GLenum objectType, GLuint name, GLenum option);
	void   (*get_object_parameteriv_APPLE) (GLIContext ctx, GLenum objectType, GLuint name, GLenum pname, GLint* params);

	/* EXT_geometry_shader4 */
	void (*program_parameteri_EXT)(GLIContext ctx, GLuint program_name, GLenum pname, GLint value);
	void (*framebuffer_texture_EXT)(GLIContext ctx, GLenum target, GLenum attachment, GLuint texture, GLint level);
	void (*framebuffer_texture_layer_EXT)(GLIContext ctx, GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
	void (*framebuffer_texture_face_EXT)(GLIContext ctx, GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);
	
	/* EXT_transform_feedback */
	void (*bind_buffer_range_EXT)(GLIContext ctx, GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
	void (*bind_buffer_offset_EXT)(GLIContext ctx, GLenum target, GLuint index, GLuint buffer, GLintptr offset);
	void (*bind_buffer_base_EXT)(GLIContext ctx, GLenum target, GLuint index, GLuint buffer);
	void (*begin_transform_feedback_EXT)(GLIContext ctx, GLenum primitiveMode);
	void (*end_transform_feedback_EXT)(GLIContext ctx);
	void (*transform_feedback_varyings_EXT)(GLIContext ctx, GLuint program, GLsizei count, const GLchar* const *varyings, GLenum bufferMode);
	void (*get_transform_feedback_varying_EXT)(GLIContext ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
	void (*get_integer_indexedv_EXT)(GLIContext ctx, GLenum param, GLuint index, GLint *values); 
	void (*get_boolean_indexedv_EXT)(GLIContext ctx, GLenum param, GLuint index, GLboolean *values);

	/* EXT_bindable_uniform */
	void (*uniform_buffer_EXT)(GLIContext ctx, GLuint program, GLint location, GLuint buffer);
	GLint (*get_uniform_buffer_size_EXT)(GLIContext ctx, GLuint program, GLint location);
	GLintptr (*get_uniform_buffer_offset_EXT)(GLIContext ctx, GLuint program, GLint location);

	/* EXT_texture_integer */
	void (*clear_colorIi_EXT) (GLIContext ctx, GLint r, GLint g, GLint b, GLint a );
	void (*clear_colorIui_EXT) (GLIContext ctx, GLuint r, GLuint g, GLuint b, GLuint a );
	void (*tex_parameterIiv_EXT)(GLIContext ctx, GLenum target, GLenum pname, GLint *params );
	void (*tex_parameterIuiv_EXT)(GLIContext ctx, GLenum target, GLenum pname, GLuint *params );
	void (*get_tex_parameterIiv_EXT) (GLIContext ctx, GLenum target, GLenum pname, GLint *params);
	void (*get_tex_parameterIuiv_EXT) (GLIContext ctx, GLenum target, GLenum pname, GLuint *params);

	/* EXT_gpu_shader4 */
	void (*vertex_attribI1i_EXT)(GLIContext ctx, GLuint index, GLint x);
	void (*vertex_attribI2i_EXT)(GLIContext ctx, GLuint index, GLint x, GLint y);
	void (*vertex_attribI3i_EXT)(GLIContext ctx, GLuint index, GLint x, GLint y, GLint z);
	void (*vertex_attribI4i_EXT)(GLIContext ctx, GLuint index, GLint x, GLint y, GLint z, GLint w);
	void (*vertex_attribI1ui_EXT)(GLIContext ctx, GLuint index, GLuint x);
	void (*vertex_attribI2ui_EXT)(GLIContext ctx, GLuint index, GLuint x, GLuint y);
	void (*vertex_attribI3ui_EXT)(GLIContext ctx, GLuint index, GLuint x, GLuint y, GLuint z);
	void (*vertex_attribI4ui_EXT)(GLIContext ctx, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
	void (*vertex_attribI1iv_EXT)(GLIContext ctx, GLuint index, const GLint *v);
	void (*vertex_attribI2iv_EXT)(GLIContext ctx, GLuint index, const GLint *v);
	void (*vertex_attribI3iv_EXT)(GLIContext ctx, GLuint index, const GLint *v);
	void (*vertex_attribI4iv_EXT)(GLIContext ctx, GLuint index, const GLint *v);
	void (*vertex_attribI1uiv_EXT)(GLIContext ctx, GLuint index, const GLuint *v);
	void (*vertex_attribI2uiv_EXT)(GLIContext ctx, GLuint index, const GLuint *v);
	void (*vertex_attribI3uiv_EXT)(GLIContext ctx, GLuint index, const GLuint *v);
	void (*vertex_attribI4uiv_EXT)(GLIContext ctx, GLuint index, const GLuint *v);
	void (*vertex_attribI4bv_EXT)(GLIContext ctx, GLuint index, const GLbyte *v);
	void (*vertex_attribI4sv_EXT)(GLIContext ctx, GLuint index, const GLshort *v);
	void (*vertex_attribI4ubv_EXT)(GLIContext ctx, GLuint index, const GLubyte *v);
	void (*vertex_attribI4usv_EXT)(GLIContext ctx, GLuint index, const GLushort *v);
	void (*vertex_attribI_pointer_EXT)(GLIContext ctx, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*get_vertex_attribIiv_EXT)(GLIContext ctx, GLuint index, GLenum pname, GLint *params);
	void (*get_vertex_attribIuiv_EXT)(GLIContext ctx, GLuint index, GLenum pname, GLuint *params);
	void (*uniform1ui_EXT)(GLIContext ctx, GLint location, GLuint v0);
	void (*uniform2ui_EXT)(GLIContext ctx, GLint location, GLuint v0, GLuint v1);
	void (*uniform3ui_EXT)(GLIContext ctx, GLint location, GLuint v0, GLuint v1, GLuint v2);
	void (*uniform4ui_EXT)(GLIContext ctx, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	void (*uniform1uiv_EXT)(GLIContext ctx, GLint location, GLsizei count, const GLuint *value);
	void (*uniform2uiv_EXT)(GLIContext ctx, GLint location, GLsizei count, const GLuint *value);
	void (*uniform3uiv_EXT)(GLIContext ctx, GLint location, GLsizei count, const GLuint *value);
	void (*uniform4uiv_EXT)(GLIContext ctx, GLint location, GLsizei count, const GLuint *value);
	void (*get_uniformuiv_EXT)(GLIContext ctx, GLuint program, GLint location, GLuint *params);
	void (*bind_frag_data_location_EXT)(GLIContext ctx, GLuint program, GLuint colorNumber, const GLchar *name);
	GLint (*get_frag_data_location_EXT)(GLIContext ctx, GLuint program, const GLchar *name);

	/* EXT_draw_buffers2 */
	void (*color_mask_indexed_EXT) (GLIContext ctx, GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
	void (*enable_indexed_EXT) (GLIContext ctx, GLenum target, GLuint index);
	void (*disable_indexed_EXT) (GLIContext ctx, GLenum target, GLuint index);
	GLboolean (*is_enabled_indexed_EXT) (GLIContext ctx, GLenum target, GLuint index);

	/* OpenGL 2.1 */
	void (*uniform_matrix2x3fv) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*uniform_matrix3x2fv) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*uniform_matrix2x4fv) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*uniform_matrix4x2fv) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*uniform_matrix3x4fv) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*uniform_matrix4x3fv) (GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

	/* EXT_framebuffer_blit and EXT_framebuffer_multisample */
	void (*blit_framebuffer_EXT) (GLIContext ctx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
	void (*renderbuffer_storage_multisample_EXT) (GLIContext ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);

	/* NV_conditional_render */
	void (*begin_conditional_render_NV)(GLIContext ctx, GLuint id, GLenum mode);
	void (*end_conditional_render_NV)(GLIContext ctx);

	void (*get_attached_shaders) (GLIContext ctx, GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
	
	/* EXT_provoking_vertex */
	void (*provoking_vertex_EXT) (GLIContext ctx, GLenum mode);
	
	/* ARB_instanced_arrays */
	void (*vertex_attrib_divisor) (GLIContext ctx, GLuint index, GLuint divisor);
	/* ARB_instanced_arrays and ARB_draw_instanced */
	void (*draw_arrays_instanced)(GLIContext ctx, GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
	void (*draw_elements_instanced)(GLIContext ctx, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei instancecount);

	/* ARB_draw_elements_base_vertex */
	void (*draw_elements_base_vertex)(GLIContext ctx, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint base_vertex);
	void (*draw_range_elements_base_vertex)(GLIContext ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices, GLint base_vertex);
	void (*draw_elements_instanced_base_vertex)(GLIContext ctx, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei instancecount, GLint base_vertex);
	void (*multi_draw_elements_base_vertex)(GLIContext ctx, GLenum mode, const GLsizei *count, GLenum type, const GLvoid* const *indices, GLsizei drawcount, const GLint *base_vertex);

	/* ARB_vertex_array_object / OES_vertex_array_object */
	void (*bind_vertex_array_ARB)(GLIContext ctx, GLuint array);
	void (*delete_vertex_arrays_ARB)(GLIContext ctx, GLsizei n, const GLuint *arrays);
	void (*gen_vertex_arrays_ARB)(GLIContext ctx, GLsizei n, GLuint *arrays);
	GLboolean (*is_vertex_array_ARB)(GLIContext ctx, GLuint array);

	/* APPLE_vertex_point_size */
	void (*point_size_pointer) (GLIContext ctx, GLenum type, GLsizei stride, const GLvoid *pointer);
	void (*vertex_point_sizef_APPLE) (GLIContext ctx, GLfloat size);

	/* OpenGL 3.0 */
	void (*clear_bufferiv)(GLIContext ctx, GLenum buffer, GLint drawbuffer, const GLint *value);
	void (*clear_bufferuiv)(GLIContext ctx, GLenum buffer, GLint drawbuffer, const GLuint *value);
	void (*clear_bufferfv)(GLIContext ctx, GLenum buffer, GLint drawbuffer, const GLfloat *value);
	void (*clear_bufferfi)(GLIContext ctx, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
	const GLubyte* (*get_stringi)(GLIContext ctx, GLenum name, GLuint index);
	
	/* ARB_sync */
	GLsync (*fence_sync) (GLIContext ctx, GLenum condition, GLbitfield flags);
	GLboolean (*is_sync) (GLIContext ctx, GLsync sync);
	void (*delete_sync) (GLIContext ctx, GLsync sync);
	GLenum (*client_wait_sync) (GLIContext ctx, GLsync sync, GLbitfield flags, GLuint64 timeout);
	void (*wait_sync) (GLIContext ctx, GLsync sync, GLbitfield flags, GLuint64 timeout);
	void (*get_integer64v_sync) (GLIContext ctx, GLenum pname, GLint64 *params);
	void (*get_synciv) (GLIContext ctx, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);

	/* ARB_texture_multisample */
	void (*tex_image2D_multisample)(GLIContext ctx, GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	void (*tex_image3D_multisample)(GLIContext ctx, GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
	void (*get_multisamplefv)(GLIContext ctx, GLenum pname, GLuint index, GLfloat *val);
	void (*sample_maski)(GLIContext ctx, GLuint index, GLbitfield mask);

	/* ARB_texture_buffer_object */
	void (*tex_buffer)(GLIContext ctx, GLenum target, GLenum internalformat, GLuint buffer);

	/* ARB_copy_buffer */
	void (*copy_buffer_sub_data)(GLIContext ctx, GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size);

	/* NV_primitive_restart */
	void (*primitive_restart_index)(GLIContext ctx, GLuint index);

	/* EXT_timer_query */
	void (*get_query_objecti64v) (GLIContext ctx, GLuint id, GLenum pname, GLint64EXT *params);
	void (*get_query_objectui64v) (GLIContext ctx, GLuint id, GLenum pname, GLuint64EXT *params);

	/* ARB_map_buffer_range */
	GLvoid *(*map_buffer_range) (GLIContext ctx, GLenum target, GLintptr offset, GLsizeiptr length, GLenum access);
	void (*flush_mapped_buffer_range) (GLIContext ctx, GLenum target, GLintptr offset, GLsizeiptr length);

	/* ARB_timer_query */
	void (*query_counter) (GLIContext ctx, GLuint id, GLenum target);
	void (*get_integer64i_v) (GLIContext ctx, GLenum target, GLuint index, GLint64 *data);
	void (*get_buffer_parameteri64v)(GLIContext ctx, GLenum target, GLenum pname, GLint64 *params);

	/* ARB_sampler_object */
	void (*gen_samplers) (GLIContext ctx, GLsizei count, GLuint *samplers);
	void (*delete_samplers) (GLIContext ctx, GLsizei count, const GLuint *samplers);
	GLboolean (*is_sampler) (GLIContext ctx, GLuint sampler);
	void (*bind_sampler) (GLIContext ctx, GLuint unit, GLuint sampler);
	void (*sampler_parameteri) (GLIContext ctx, GLuint sampler, GLenum pname, GLint param);
	void (*sampler_parameteriv) (GLIContext ctx, GLuint sampler, GLenum pname, const GLint *param);
	void (*sampler_parameterf) (GLIContext ctx, GLuint sampler, GLenum pname, GLfloat param);
	void (*sampler_parameterfv) (GLIContext ctx, GLuint sampler, GLenum pname, const GLfloat *param);
	void (*sampler_parameterIiv) (GLIContext ctx, GLuint sampler, GLenum pname, const GLint *param);
	void (*sampler_parameterIuiv) (GLIContext ctx, GLuint sampler, GLenum pname, const GLuint *param);
	void (*get_sampler_parameteriv) (GLIContext ctx, GLuint sampler, GLenum pname, GLint *params);
	void (*get_sampler_parameterfv) (GLIContext ctx, GLuint sampler, GLenum pname, GLfloat *params);
	void (*get_sampler_parameterIiv) (GLIContext ctx, GLuint sampler, GLenum pname, GLint *params);
	void (*get_sampler_parameterIuiv) (GLIContext ctx, GLuint sampler, GLenum pname, GLuint *params);

	/* EXT_debug_label */
	void (*label_object_EXT)(GLIContext ctx, GLenum type, GLuint object, GLsizei length, const GLchar *label);
	void (*get_object_label_EXT)(GLIContext ctx, GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label);

	/* EXT_debug_marker */
	void (*insert_event_marker_EXT)(GLIContext ctx, GLsizei length, const GLchar *marker);
	void (*push_group_marker_EXT)(GLIContext ctx, GLsizei length, const GLchar *marker);
	void (*pop_group_marker_EXT)(GLIContext ctx);

	/* ARB_separate_shader_objects */
	void (*use_program_stages)(GLIContext ctx, GLuint pipeline, GLbitfield stages, GLuint program);
	void (*active_shader_program)(GLIContext ctx, GLuint pipeline, GLuint program);
	GLuint (*create_shader_programv)(GLIContext ctx, GLenum type, GLsizei count, const GLchar* const *strings);
	void (*bind_program_pipeline)(GLIContext ctx, GLuint pipeline);
	void (*delete_program_pipelines)(GLIContext ctx, GLsizei n, const GLuint *pipelines);
	void (*gen_program_pipelines)(GLIContext ctx, GLsizei n, GLuint *pipelines);
	GLboolean (*is_program_pipeline)(GLIContext ctx, GLuint pipeline);
	void (*get_program_pipelineiv)(GLIContext ctx, GLuint pipeline, GLenum pname, GLint *params);
	void (*validate_program_pipeline)(GLIContext ctx, GLuint pipeline);
	void (*get_program_pipeline_info_log)(GLIContext ctx, GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
	void (*program_uniform1i)(GLIContext ctx, GLuint program, GLint location, GLint x);
	void (*program_uniform2i)(GLIContext ctx, GLuint program, GLint location, GLint x, GLint y);
	void (*program_uniform3i)(GLIContext ctx, GLuint program, GLint location, GLint x, GLint y, GLint z);
	void (*program_uniform4i)(GLIContext ctx, GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w);
	void (*program_uniform1f)(GLIContext ctx, GLuint program, GLint location, GLfloat x);
	void (*program_uniform2f)(GLIContext ctx, GLuint program, GLint location, GLfloat x, GLfloat y);
	void (*program_uniform3f)(GLIContext ctx, GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z);
	void (*program_uniform4f)(GLIContext ctx, GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void (*program_uniform1iv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLint *value);
	void (*program_uniform2iv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLint *value);
	void (*program_uniform3iv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLint *value);
	void (*program_uniform4iv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLint *value);
	void (*program_uniform1fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLfloat *value);
	void (*program_uniform2fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLfloat *value);
	void (*program_uniform3fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLfloat *value);
	void (*program_uniform4fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLfloat *value);
	void (*program_uniform_matrix2fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*program_uniform_matrix3fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*program_uniform_matrix4fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*program_uniform1ui)(GLIContext ctx, GLuint program, GLint location, GLuint x);
	void (*program_uniform2ui)(GLIContext ctx, GLuint program, GLint location, GLuint x, GLuint y);
	void (*program_uniform3ui)(GLIContext ctx, GLuint program, GLint location, GLuint x, GLuint y, GLuint z);
	void (*program_uniform4ui)(GLIContext ctx, GLuint program, GLint location, GLuint x, GLuint y, GLuint z, GLuint w);
	void (*program_uniform1uiv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLuint *value);
	void (*program_uniform2uiv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLuint *value);
	void (*program_uniform3uiv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLuint *value);
	void (*program_uniform4uiv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLuint *value);
	void (*program_uniform_matrix2x3fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*program_uniform_matrix3x2fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*program_uniform_matrix2x4fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*program_uniform_matrix4x2fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*program_uniform_matrix3x4fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (*program_uniform_matrix4x3fv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

	/* ARB_blend_func_extended */
	void (*bind_frag_data_location_indexed) (GLIContext ctx, GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
	GLint (*get_frag_data_index) (GLIContext ctx, GLuint program, const GLchar *name);

	/* ARB_draw_buffers_blend */
	void (*blend_func_i) (GLIContext ctx, GLuint buf, GLenum src, GLenum dst);
	void (*blend_func_separate_i) (GLIContext ctx, GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	void (*blend_equation_i) (GLIContext ctx, GLuint buf, GLenum mode);
	void (*blend_equation_separate_i) (GLIContext ctx, GLuint buf, GLenum modeRGB, GLenum modeAlpha);

	/* ARB_shading_language_include */
	void (*named_string_ARB) (GLIContext ctx, GLenum type, GLint namelen, const GLchar *name, GLint stringlen, const GLchar *string);
	void (*delete_named_string_ARB) (GLIContext ctx, GLint namelen, const GLchar *name);
	void (*compile_shader_include_ARB) (GLIContext ctx, GLuint shader, GLsizei count, const GLchar* const *path, const GLint *length);
	GLboolean (*is_named_string_ARB) (GLIContext ctx, GLint namelen, const GLchar *name);
	void (*get_named_string_ARB) (GLIContext ctx, GLint namelen, const GLchar *name, GLsizei bufSize, GLint *stringlen, GLchar *string);
	void (*get_named_string_iv_ARB) (GLIContext ctx, GLint namelen, const GLchar *name, GLenum pname, GLint *params);

	/* ARB_ES2_compatibility */
	void (*release_shader_compiler)(GLIContext ctx);
	void (*shader_binary)(GLIContext ctx, GLint n, GLuint *shaders, GLenum binaryformat, const GLvoid *binary, GLint length);
	void (*get_shader_precision_format)(GLIContext ctx, GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
	void (*depth_rangef) (GLIContext ctx, GLclampf zNear, GLclampf zFar);
	void (*clear_depthf) (GLIContext ctx, GLclampf depth);

	/* ARB_vertex_type_2_10_10_10_rev */
	void (*vertex_attribP1ui) (GLIContext ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value);
	void (*vertex_attribP2ui) (GLIContext ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value);
	void (*vertex_attribP3ui) (GLIContext ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value);
	void (*vertex_attribP4ui) (GLIContext ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value);
	void (*vertex_attribP1uiv) (GLIContext ctx, GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
	void (*vertex_attribP2uiv) (GLIContext ctx, GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
	void (*vertex_attribP3uiv) (GLIContext ctx, GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
	void (*vertex_attribP4uiv) (GLIContext ctx, GLuint index, GLenum type, GLboolean normalized, const GLuint *value);

	/* ARB_get_program_binary */
	void (*get_program_binary) (GLIContext ctx, GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, GLvoid *binary);
	void (*program_binary) (GLIContext ctx, GLuint program, GLenum binaryFormat, const GLvoid *binary, GLsizei length);
	
	/* ARB_sample_shading */
	void (*min_sample_shading) (GLIContext ctx, GLclampf value);

	/* ARB_viewport_array */
	void (*viewport_arrayv) (GLIContext ctx, GLuint first, GLsizei count, const GLfloat * v);
	void (*viewport_indexedf) (GLIContext ctx, GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	void (*viewport_indexedfv) (GLIContext ctx, GLuint index, const GLfloat * v);
	void (*scissor_arrayv) (GLIContext ctx, GLuint first, GLsizei count, const GLint * v);
	void (*scissor_indexed) (GLIContext ctx, GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
	void (*scissor_indexedv) (GLIContext ctx, GLuint index, const GLint * v);
	void (*depth_range_arrayv) (GLIContext ctx, GLuint first, GLsizei count, const GLclampd * v);
	void (*depth_range_indexed) (GLIContext ctx, GLuint index, GLclampd n, GLclampd f);
	void (*get_floati_v) (GLIContext ctx, GLenum target, GLuint index, GLfloat *data);
	void (*get_doublei_v) (GLIContext ctx, GLenum target, GLuint index, GLdouble *data);

	/* ARB_draw_indirect */
	void (*draw_arrays_indirect) (GLIContext ctx, GLenum mode, const GLvoid *indirect);
	void (*draw_elements_indirect) (GLIContext ctx, GLenum mode, GLenum type, const GLvoid *indirect);

	/* ARB_tessellation_shader */
	void (*patch_parameteri) (GLIContext ctx, GLenum pname, GLint value);
	void (*patch_parameterfv) (GLIContext ctx, GLenum pname, const GLfloat* values);

	/* ARB_transform_feedback2 */
	void (*bind_transform_feedback) (GLIContext ctx, GLenum target, GLuint name);
	void (*gen_transform_feedbacks) (GLIContext ctx, GLsizei n, GLuint* ids);
	void (*delete_transform_feedbacks) (GLIContext ctx, GLsizei n, const GLuint* ids);
	void (*pause_transform_feedback) (GLIContext ctx);
	void (*resume_transform_feedback) (GLIContext ctx);
	GLboolean (*is_transform_feedback) (GLIContext ctx, GLuint name);
	void (*draw_transform_feedback) (GLIContext ctx, GLenum mode, GLuint name);

	/* ARB_transform_feedback3 */
	void (*begin_query_indexed) (GLIContext ctx, GLenum target, GLuint index, GLuint id);
	void (*end_query_indexed) (GLIContext ctx, GLenum target, GLuint index);
	void (*get_query_indexediv) (GLIContext ctx, GLenum target, GLuint index, GLenum pname, GLint *params);
	void (*draw_transform_feedback_stream) (GLIContext ctx, GLenum mode, GLuint name, GLuint stream);

	/* ARB_separate_shader_objects && ARB_gpu_shader_fp64 */
	void (*program_uniform1d)(GLIContext ctx, GLuint program, GLint location, GLdouble x);
	void (*program_uniform2d)(GLIContext ctx, GLuint program, GLint location, GLdouble x, GLdouble y);
	void (*program_uniform3d)(GLIContext ctx, GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z);
	void (*program_uniform4d)(GLIContext ctx, GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void (*program_uniform1dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLdouble *value);
	void (*program_uniform2dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLdouble *value);
	void (*program_uniform3dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLdouble *value);
	void (*program_uniform4dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, const GLdouble *value);
	void (*program_uniform_matrix2dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*program_uniform_matrix3dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*program_uniform_matrix4dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*program_uniform_matrix2x3dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*program_uniform_matrix3x2dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*program_uniform_matrix2x4dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*program_uniform_matrix4x2dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*program_uniform_matrix3x4dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*program_uniform_matrix4x3dv)(GLIContext ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);

	/* ARB_gpu_shader_fp64 */
	void (*uniform1d)(GLIContext ctx, GLint location, GLdouble x);
	void (*uniform2d)(GLIContext ctx, GLint location, GLdouble x, GLdouble y);
	void (*uniform3d)(GLIContext ctx, GLint location, GLdouble x, GLdouble y, GLdouble z);
	void (*uniform4d)(GLIContext ctx, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void (*uniform1dv)(GLIContext ctx, GLint location, GLsizei count, const GLdouble *value);
	void (*uniform2dv)(GLIContext ctx, GLint location, GLsizei count, const GLdouble *value);
	void (*uniform3dv)(GLIContext ctx, GLint location, GLsizei count, const GLdouble *value);
	void (*uniform4dv)(GLIContext ctx, GLint location, GLsizei count, const GLdouble *value);
	void (*uniform_matrix2dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*uniform_matrix3dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*uniform_matrix4dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*uniform_matrix2x3dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*uniform_matrix3x2dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*uniform_matrix2x4dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*uniform_matrix4x2dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*uniform_matrix3x4dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*uniform_matrix4x3dv)(GLIContext ctx, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
	void (*get_uniformdv)(GLIContext ctx, GLuint program_obj, GLint location, GLdouble *params);
	
	/* ARB_vertex_attrib_64bit */
	void (*vertex_attribl1d)(GLIContext ctx, GLuint index, GLdouble x);
	void (*vertex_attribl2d)(GLIContext ctx, GLuint index, GLdouble x, GLdouble y);
	void (*vertex_attribl3d)(GLIContext ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z);
	void (*vertex_attribl4d)(GLIContext ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void (*vertex_attribl1dv)(GLIContext ctx, GLuint index, const GLdouble *v);
	void (*vertex_attribl2dv)(GLIContext ctx, GLuint index, const GLdouble *v);
	void (*vertex_attribl3dv)(GLIContext ctx, GLuint index, const GLdouble *v);
	void (*vertex_attribl4dv)(GLIContext ctx, GLuint index, const GLdouble *v);
	void (*vertex_attrib_lpointer)(GLIContext ctx, GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
	void (*get_vertex_attrib_ldv)(GLIContext ctx, GLuint index, GLenum pname, GLdouble *params);

	/* ARB_shader_subroutine */
	GLint (*get_subroutine_uniform_location)(GLIContext ctx, GLuint program, GLenum shadertype, const GLchar *name);
	GLuint (*get_subroutine_index)(GLIContext ctx, GLuint program, GLenum shadertype, const GLchar *name);
	void (*get_active_subroutine_uniformiv)(GLIContext ctx, GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
	void (*get_active_subroutine_uniform_name)(GLIContext ctx, GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
	void (*get_active_subroutine_name)(GLIContext ctx, GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
	void (*uniform_subroutinesuiv)(GLIContext ctx, GLenum shadertype, GLsizei count, const GLuint *indices);
	void (*get_uniform_subroutineuiv)(GLIContext ctx, GLenum shadertype, GLint location, GLuint *params);
	void (*get_program_stageiv)(GLIContext ctx, GLuint program, GLenum shadertype, GLenum pname, GLint *values);


	/* ARB_internalformat_query */
	void (*get_internal_formativ) (GLIContext ctx, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params);

	/* ARB_texture_storage */
	void (*tex_storage1D) (GLIContext ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
	void (*tex_storage2D) (GLIContext ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
	void (*tex_storage3D) (GLIContext ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
	
	/* GL_APPLE_label_process */
	void (*label_object_with_responsible_process_APPLE) (GLIContext ctx, GLenum type, GLuint name, GLint pid);

	/* GL_NV_texture_barrier */
	void (*texture_barrier_NV) (GLIContext ctx);

    /* "GL_APPLE_multi_draw_indirect" */
    void (*multi_draw_elements_indirect_APPLE) (GLIContext ctx, GLenum mode, GLenum type, const GLvoid *indirect, GLsizei drawcount, GLsizei stride);
} GLIFunctionDispatch;


#ifdef __cplusplus
}
#endif

#endif /* _GLIDISPATCH_H */
