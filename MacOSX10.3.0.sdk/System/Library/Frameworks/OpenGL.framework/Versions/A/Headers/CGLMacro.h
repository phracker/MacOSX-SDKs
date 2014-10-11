/*
	Copyright:	(c) 1999 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _CGLMACRO_H
#define _CGLMACRO_H

#include <OpenGL/CGLContext.h>


/****************** OpenGL 1.1 Macros *****************************/

/* Macro context name */
#define CGL_MACRO_CONTEXT cgl_ctx

#define glAccum(op, value) \
	(*cgl_ctx->disp.accum)(cgl_ctx->rend, op, value)

#define glAlphaFunc(func, ref) \
	(*cgl_ctx->disp.alpha_func)(cgl_ctx->rend, func, ref)

#define glAreTexturesResident(n, textures, residences) \
	(*cgl_ctx->disp.are_textures_resident)(cgl_ctx->rend, n, textures, residences)

#define glArrayElement(i) \
	(*cgl_ctx->disp.array_element)(cgl_ctx->rend, i)

#define glBegin(mode) \
	(*cgl_ctx->disp.begin)(cgl_ctx->rend, mode)

#define glBindTexture(target, texture) \
	(*cgl_ctx->disp.bind_texture)(cgl_ctx->rend, target, texture)

#define glBitmap(width, height, xorig, yorig, xmove, ymove, bmap) \
	(*cgl_ctx->disp.bitmap)(cgl_ctx->rend, width, height, xorig, yorig, xmove, ymove, bmap)

#define glBlendFunc(sfactor, dfactor) \
	(*cgl_ctx->disp.blend_func)(cgl_ctx->rend, sfactor, dfactor)

#define glCallList(list) \
	(*cgl_ctx->disp.call_list)(cgl_ctx->rend, list)

#define glCallLists(n, type, lists) \
	(*cgl_ctx->disp.call_lists)(cgl_ctx->rend, n, type, lists)

#define glClear(mask) \
	(*cgl_ctx->disp.clear)(cgl_ctx->rend, mask)

#define glClearAccum(red, green, blue, alpha) \
	(*cgl_ctx->disp.clear_accum)(cgl_ctx->rend, red, green, blue, alpha)

#define glClearColor(red, green, blue, alpha) \
	(*cgl_ctx->disp.clear_color)(cgl_ctx->rend, red, green, blue, alpha)

#define glClearDepth(depth) \
	(*cgl_ctx->disp.clear_depth)(cgl_ctx->rend, depth)

#define glClearIndex(c) \
	(*cgl_ctx->disp.clear_index)(cgl_ctx->rend, c)

#define glClearStencil(s) \
	(*cgl_ctx->disp.clear_stencil)(cgl_ctx->rend, s)

#define glClipPlane(plane, equation) \
	(*cgl_ctx->disp.clip_plane)(cgl_ctx->rend, plane, equation)

#define glColor3b(red, green, blue) \
	(*cgl_ctx->disp.color3b)(cgl_ctx->rend, red, green, blue)

#define glColor3bv(v) \
	(*cgl_ctx->disp.color3bv)(cgl_ctx->rend, v)

#define glColor3d(red, green, blue) \
	(*cgl_ctx->disp.color3d)(cgl_ctx->rend, red, green, blue)

#define glColor3dv(v) \
	(*cgl_ctx->disp.color3dv)(cgl_ctx->rend, v)

#define glColor3f(red, green, blue) \
	(*cgl_ctx->disp.color3f)(cgl_ctx->rend, red, green, blue)

#define glColor3fv(v) \
	(*cgl_ctx->disp.color3fv)(cgl_ctx->rend, v)

#define glColor3i(red, green, blue) \
	(*cgl_ctx->disp.color3i)(cgl_ctx->rend, red, green, blue)

#define glColor3iv(v) \
	(*cgl_ctx->disp.color3iv)(cgl_ctx->rend, v)

#define glColor3s(red, green, blue) \
	(*cgl_ctx->disp.color3s)(cgl_ctx->rend, red, green, blue)

#define glColor3sv(v) \
	(*cgl_ctx->disp.color3sv)(cgl_ctx->rend, v)

#define glColor3ub(red, green, blue) \
	(*cgl_ctx->disp.color3ub)(cgl_ctx->rend, red, green, blue)

#define glColor3ubv(v) \
	(*cgl_ctx->disp.color3ubv)(cgl_ctx->rend, v)

#define glColor3ui(red, green, blue) \
	(*cgl_ctx->disp.color3ui)(cgl_ctx->rend, red, green, blue)

#define glColor3uiv(v) \
	(*cgl_ctx->disp.color3uiv)(cgl_ctx->rend, v)

#define glColor3us(red, green, blue) \
	(*cgl_ctx->disp.color3us)(cgl_ctx->rend, red, green, blue)

#define glColor3usv(v) \
	(*cgl_ctx->disp.color3usv)(cgl_ctx->rend, v)

#define glColor4b(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4b)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4bv(v) \
	(*cgl_ctx->disp.color4bv)(cgl_ctx->rend, v)

#define glColor4d(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4d)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4dv(v) \
	(*cgl_ctx->disp.color4dv)(cgl_ctx->rend, v)

#define glColor4f(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4f)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4fv(v) \
	(*cgl_ctx->disp.color4fv)(cgl_ctx->rend, v)

#define glColor4i(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4i)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4iv(v) \
	(*cgl_ctx->disp.color4iv)(cgl_ctx->rend, v)

#define glColor4s(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4s)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4sv(v) \
	(*cgl_ctx->disp.color4sv)(cgl_ctx->rend, v)

#define glColor4ub(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4ub)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4ubv(v) \
	(*cgl_ctx->disp.color4ubv)(cgl_ctx->rend, v)

#define glColor4ui(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4ui)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4uiv(v) \
	(*cgl_ctx->disp.color4uiv)(cgl_ctx->rend, v)

#define glColor4us(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4us)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4usv(v) \
	(*cgl_ctx->disp.color4usv)(cgl_ctx->rend, v)

#define glColorMask(red, green, blue, alpha) \
	(*cgl_ctx->disp.color_mask)(cgl_ctx->rend, red, green, blue, alpha)

#define glColorMaterial(face, mode) \
	(*cgl_ctx->disp.color_material)(cgl_ctx->rend, face, mode)

#define glColorPointer(size, type, stride, pointer) \
	(*cgl_ctx->disp.color_pointer)(cgl_ctx->rend, size, type, stride, pointer)

#define glCopyPixels(x, y, width, height, type) \
	(*cgl_ctx->disp.copy_pixels)(cgl_ctx->rend, x, y, width, height, type)

#define glCopyTexImage1D(target, level, internalFormat, x, y, width, border) \
	(*cgl_ctx->disp.copy_tex_image1D)(cgl_ctx->rend, target, level, internalFormat, x, y, width, border)

#define glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border) \
	(*cgl_ctx->disp.copy_tex_image2D)(cgl_ctx->rend, target, level, internalFormat, x, y, width, height, border)

#define glCopyTexSubImage1D(target, level, xoffset, x, y, width) \
	(*cgl_ctx->disp.copy_tex_sub_image1D)(cgl_ctx->rend, target, level, xoffset, x, y, width)

#define glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) \
	(*cgl_ctx->disp.copy_tex_sub_image2D)(cgl_ctx->rend, target, level, xoffset, yoffset, x, y, width, height)

#define glCullFace(mode) \
	(*cgl_ctx->disp.cull_face)(cgl_ctx->rend, mode)

#define glDeleteLists(list, range) \
	(*cgl_ctx->disp.delete_lists)(cgl_ctx->rend, list, range)

#define glDeleteTextures(n, textures) \
	(*cgl_ctx->disp.delete_textures)(cgl_ctx->rend, n, textures)

#define glDepthFunc(func) \
	(*cgl_ctx->disp.depth_func)(cgl_ctx->rend, func)

#define glDepthMask(flag) \
	(*cgl_ctx->disp.depth_mask)(cgl_ctx->rend, flag)

#define glDepthRange(zNear, zFar) \
	(*cgl_ctx->disp.depth_range)(cgl_ctx->rend, zNear, zFar)

#define glDisable(cap) \
	(*cgl_ctx->disp.disable)(cgl_ctx->rend, cap)

#define glDisableClientState(array) \
	(*cgl_ctx->disp.disable_client_state)(cgl_ctx->rend, array)

#define glDrawArrays(mode, first, count) \
	(*cgl_ctx->disp.draw_arrays)(cgl_ctx->rend, mode, first, count)

#define glDrawBuffer(mode) \
	(*cgl_ctx->disp.draw_buffer)(cgl_ctx->rend, mode)

#define glDrawElements(mode, count, type, indices) \
	(*cgl_ctx->disp.draw_elements)(cgl_ctx->rend, mode, count, type, indices)

#define glDrawPixels(width, height, format, type, pixels) \
	(*cgl_ctx->disp.draw_pixels)(cgl_ctx->rend, width, height, format, type, pixels)

#define glEdgeFlag(flag) \
	(*cgl_ctx->disp.edge_flag)(cgl_ctx->rend, flag)

#define glEdgeFlagPointer(stride, pointer) \
	(*cgl_ctx->disp.edge_flag_pointer)(cgl_ctx->rend, stride, pointer)

#define glEdgeFlagv(flag) \
	(*cgl_ctx->disp.edge_flagv)(cgl_ctx->rend, flag)

#define glEnable(cap) \
	(*cgl_ctx->disp.enable)(cgl_ctx->rend, cap)

#define glEnableClientState(array) \
	(*cgl_ctx->disp.enable_client_state)(cgl_ctx->rend, array)

#define glEnd() \
	(*cgl_ctx->disp.end)(cgl_ctx->rend)

#define glEndList() \
	(*cgl_ctx->disp.end_list)(cgl_ctx->rend)

#define glEvalCoord1d(u) \
	(*cgl_ctx->disp.eval_coord1d)(cgl_ctx->rend, u)

#define glEvalCoord1dv(u) \
	(*cgl_ctx->disp.eval_coord1dv)(cgl_ctx->rend, u)

#define glEvalCoord1f(u) \
	(*cgl_ctx->disp.eval_coord1f)(cgl_ctx->rend, u)

#define glEvalCoord1fv(u) \
	(*cgl_ctx->disp.eval_coord1fv)(cgl_ctx->rend, u)

#define glEvalCoord2d(u, v) \
	(*cgl_ctx->disp.eval_coord2d)(cgl_ctx->rend, u, v)

#define glEvalCoord2dv(u) \
	(*cgl_ctx->disp.eval_coord2dv)(cgl_ctx->rend, u)

#define glEvalCoord2f(u, v) \
	(*cgl_ctx->disp.eval_coord2f)(cgl_ctx->rend, u, v)

#define glEvalCoord2fv(u) \
	(*cgl_ctx->disp.eval_coord2fv)(cgl_ctx->rend, u)

#define glEvalMesh1(mode, i1, i2) \
	(*cgl_ctx->disp.eval_mesh1)(cgl_ctx->rend, mode, i1, i2)

#define glEvalMesh2(mode, i1, i2, j1, j2) \
	(*cgl_ctx->disp.eval_mesh2)(cgl_ctx->rend, mode, i1, i2, j1, j2)

#define glEvalPoint1(i) \
	(*cgl_ctx->disp.eval_point1)(cgl_ctx->rend, i)

#define glEvalPoint2(i, j) \
	(*cgl_ctx->disp.eval_point2)(cgl_ctx->rend, i, j)

#define glFeedbackBuffer(size, type, buffer) \
	(*cgl_ctx->disp.feedback_buffer)(cgl_ctx->rend, size, type, buffer)

#define glFinish() \
	(*cgl_ctx->disp.finish)(cgl_ctx->rend)

#define glFlush() \
	(*cgl_ctx->disp.flush)(cgl_ctx->rend)

#define glFogf(pname, param) \
	(*cgl_ctx->disp.fogf)(cgl_ctx->rend, pname, param)

#define glFogfv(pname, params) \
	(*cgl_ctx->disp.fogfv)(cgl_ctx->rend, pname, params)

#define glFogi(pname, param) \
	(*cgl_ctx->disp.fogi)(cgl_ctx->rend, pname, param)

#define glFogiv(pname, params) \
	(*cgl_ctx->disp.fogiv)(cgl_ctx->rend, pname, params)

#define glFrontFace(mode) \
	(*cgl_ctx->disp.front_face)(cgl_ctx->rend, mode)

#define glFrustum(left, right, bottom, top, zNear, zFar) \
	(*cgl_ctx->disp.frustum)(cgl_ctx->rend, left, right, bottom, top, zNear, zFar)

#define glGenLists(range) \
	(*cgl_ctx->disp.gen_lists)(cgl_ctx->rend, range)

#define glGenTextures(n, textures) \
	(*cgl_ctx->disp.gen_textures)(cgl_ctx->rend, n, textures)

#define glGetBooleanv(pname, params) \
	(*cgl_ctx->disp.get_booleanv)(cgl_ctx->rend, pname, params)

#define glGetClipPlane(plane, equation) \
	(*cgl_ctx->disp.get_clip_plane)(cgl_ctx->rend, plane, equation)

#define glGetDoublev(pname, params) \
	(*cgl_ctx->disp.get_doublev)(cgl_ctx->rend, pname, params)

#define glGetError() \
	(*cgl_ctx->disp.get_error)(cgl_ctx->rend)

#define glGetFloatv(pname, params) \
	(*cgl_ctx->disp.get_floatv)(cgl_ctx->rend, pname, params)

#define glGetIntegerv(pname, params) \
	(*cgl_ctx->disp.get_integerv)(cgl_ctx->rend, pname, params)

#define glGetLightfv(light, pname, params) \
	(*cgl_ctx->disp.get_lightfv)(cgl_ctx->rend, light, pname, params)

#define glGetLightiv(light, pname, params) \
	(*cgl_ctx->disp.get_lightiv)(cgl_ctx->rend, light, pname, params)

#define glGetMapdv(target, query, v) \
	(*cgl_ctx->disp.get_mapdv)(cgl_ctx->rend, target, query, v)

#define glGetMapfv(target, query, v) \
	(*cgl_ctx->disp.get_mapfv)(cgl_ctx->rend, target, query, v)

#define glGetMapiv(target, query, v) \
	(*cgl_ctx->disp.get_mapiv)(cgl_ctx->rend, target, query, v)

#define glGetMaterialfv(face, pname, params) \
	(*cgl_ctx->disp.get_materialfv)(cgl_ctx->rend, face, pname, params)

#define glGetMaterialiv(face, pname, params) \
	(*cgl_ctx->disp.get_materialiv)(cgl_ctx->rend, face, pname, params)

#define glGetPixelMapfv(map, values) \
	(*cgl_ctx->disp.get_pixel_mapfv)(cgl_ctx->rend, map, values)

#define glGetPixelMapuiv(map, values) \
	(*cgl_ctx->disp.get_pixel_mapuiv)(cgl_ctx->rend, map, values)

#define glGetPixelMapusv(map, values) \
	(*cgl_ctx->disp.get_pixel_mapusv)(cgl_ctx->rend, map, values)

#define glGetPointerv(pname, params) \
	(*cgl_ctx->disp.get_pointerv)(cgl_ctx->rend, pname, params)

#define glGetPolygonStipple(mask) \
	(*cgl_ctx->disp.get_polygon_stipple)(cgl_ctx->rend, mask)

#define glGetString(name) \
	(*cgl_ctx->disp.get_string)(cgl_ctx->rend, name)

#define glGetTexEnvfv(target, pname, params) \
	(*cgl_ctx->disp.get_tex_envfv)(cgl_ctx->rend, target, pname, params)

#define glGetTexEnviv(target, pname, params) \
	(*cgl_ctx->disp.get_tex_enviv)(cgl_ctx->rend, target, pname, params)

#define glGetTexGendv(coord, pname, params) \
	(*cgl_ctx->disp.get_tex_gendv)(cgl_ctx->rend, coord, pname, params)

#define glGetTexGenfv(coord, pname, params) \
	(*cgl_ctx->disp.get_tex_genfv)(cgl_ctx->rend, coord, pname, params)

#define glGetTexGeniv(coord, pname, params) \
	(*cgl_ctx->disp.get_tex_geniv)(cgl_ctx->rend, coord, pname, params)

#define glGetTexImage(target, level, format, type, pixels) \
	(*cgl_ctx->disp.get_tex_image)(cgl_ctx->rend, target, level, format, type, pixels)

#define glGetTexLevelParameterfv(target, level, pname, params) \
	(*cgl_ctx->disp.get_tex_level_parameterfv)(cgl_ctx->rend, target, level, pname, params)

#define glGetTexLevelParameteriv(target, level, pname, params) \
	(*cgl_ctx->disp.get_tex_level_parameteriv)(cgl_ctx->rend, target, level, pname, params)

#define glGetTexParameterfv(target, pname, params) \
	(*cgl_ctx->disp.get_tex_parameterfv)(cgl_ctx->rend, target, pname, params)

#define glGetTexParameteriv(target, pname, params) \
	(*cgl_ctx->disp.get_tex_parameteriv)(cgl_ctx->rend, target, pname, params)

#define glHint(target, mode) \
	(*cgl_ctx->disp.hint)(cgl_ctx->rend, target, mode)

#define glIndexMask(mask) \
	(*cgl_ctx->disp.index_mask)(cgl_ctx->rend, mask)

#define glIndexPointer(type, stride, pointer) \
	(*cgl_ctx->disp.index_pointer)(cgl_ctx->rend, type, stride, pointer)

#define glIndexd(c) \
	(*cgl_ctx->disp.indexd)(cgl_ctx->rend, c)

#define glIndexdv(c) \
	(*cgl_ctx->disp.indexdv)(cgl_ctx->rend, c)

#define glIndexf(c) \
	(*cgl_ctx->disp.indexf)(cgl_ctx->rend, c)

#define glIndexfv(c) \
	(*cgl_ctx->disp.indexfv)(cgl_ctx->rend, c)

#define glIndexi(c) \
	(*cgl_ctx->disp.indexi)(cgl_ctx->rend, c)

#define glIndexiv(c) \
	(*cgl_ctx->disp.indexiv)(cgl_ctx->rend, c)

#define glIndexs(c) \
	(*cgl_ctx->disp.indexs)(cgl_ctx->rend, c)

#define glIndexsv(c) \
	(*cgl_ctx->disp.indexsv)(cgl_ctx->rend, c)

#define glIndexub(c) \
	(*cgl_ctx->disp.indexub)(cgl_ctx->rend, c)

#define glIndexubv(c) \
	(*cgl_ctx->disp.indexubv)(cgl_ctx->rend, c)

#define glInitNames() \
	(*cgl_ctx->disp.init_names)(cgl_ctx->rend)

#define glInterleavedArrays(format, stride, pointer) \
	(*cgl_ctx->disp.interleaved_arrays)(cgl_ctx->rend, format, stride, pointer)

#define glIsEnabled(cap) \
	(*cgl_ctx->disp.is_enabled)(cgl_ctx->rend, cap)

#define glIsList(list) \
	(*cgl_ctx->disp.is_list)(cgl_ctx->rend, list)

#define glIsTexture(texture) \
	(*cgl_ctx->disp.is_texture)(cgl_ctx->rend, texture)

#define glLightModelf(pname, param) \
	(*cgl_ctx->disp.light_modelf)(cgl_ctx->rend, pname, param)

#define glLightModelfv(pname, params) \
	(*cgl_ctx->disp.light_modelfv)(cgl_ctx->rend, pname, params)

#define glLightModeli(pname, param) \
	(*cgl_ctx->disp.light_modeli)(cgl_ctx->rend, pname, param)

#define glLightModeliv(pname, params) \
	(*cgl_ctx->disp.light_modeliv)(cgl_ctx->rend, pname, params)

#define glLightf(light, pname, param) \
	(*cgl_ctx->disp.lightf)(cgl_ctx->rend, light, pname, param)

#define glLightfv(light, pname, params) \
	(*cgl_ctx->disp.lightfv)(cgl_ctx->rend, light, pname, params)

#define glLighti(light, pname, param) \
	(*cgl_ctx->disp.lighti)(cgl_ctx->rend, light, pname, param)

#define glLightiv(light, pname, params) \
	(*cgl_ctx->disp.lightiv)(cgl_ctx->rend, light, pname, params)

#define glLineStipple(factor, pattern) \
	(*cgl_ctx->disp.line_stipple)(cgl_ctx->rend, factor, pattern)

#define glLineWidth(width) \
	(*cgl_ctx->disp.line_width)(cgl_ctx->rend, width)

#define glListBase(base) \
	(*cgl_ctx->disp.list_base)(cgl_ctx->rend, base)

#define glLoadIdentity() \
	(*cgl_ctx->disp.load_identity)(cgl_ctx->rend)

#define glLoadMatrixd(m) \
	(*cgl_ctx->disp.load_matrixd)(cgl_ctx->rend, m)

#define glLoadMatrixf(m) \
	(*cgl_ctx->disp.load_matrixf)(cgl_ctx->rend, m)

#define glLoadName(name) \
	(*cgl_ctx->disp.load_name)(cgl_ctx->rend, name)

#define glLogicOp(opcode) \
	(*cgl_ctx->disp.logic_op)(cgl_ctx->rend, opcode)

#define glMap1d(target, u1, u2, stride, order, points) \
	(*cgl_ctx->disp.map1d)(cgl_ctx->rend, target, u1, u2, stride, order, points)

#define glMap1f(target, u1, u2, stride, order, points) \
	(*cgl_ctx->disp.map1f)(cgl_ctx->rend, target, u1, u2, stride, order, points)

#define glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*cgl_ctx->disp.map2d)(cgl_ctx->rend, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*cgl_ctx->disp.map2f)(cgl_ctx->rend, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMapGrid1d(un, u1, u2) \
	(*cgl_ctx->disp.map_grid1d)(cgl_ctx->rend, un, u1, u2)

#define glMapGrid1f(un, u1, u2) \
	(*cgl_ctx->disp.map_grid1f)(cgl_ctx->rend, un, u1, u2)

#define glMapGrid2d(un, u1, u2, vn, v1, v2) \
	(*cgl_ctx->disp.map_grid2d)(cgl_ctx->rend, un, u1, u2, vn, v1, v2)

#define glMapGrid2f(un, u1, u2, vn, v1, v2) \
	(*cgl_ctx->disp.map_grid2f)(cgl_ctx->rend, un, u1, u2, vn, v1, v2)

#define glMaterialf(face, pname, param) \
	(*cgl_ctx->disp.materialf)(cgl_ctx->rend, face, pname, param)

#define glMaterialfv(face, pname, params) \
	(*cgl_ctx->disp.materialfv)(cgl_ctx->rend, face, pname, params)

#define glMateriali(face, pname, param) \
	(*cgl_ctx->disp.materiali)(cgl_ctx->rend, face, pname, param)

#define glMaterialiv(face, pname, params) \
	(*cgl_ctx->disp.materialiv)(cgl_ctx->rend, face, pname, params)

#define glMatrixMode(mode) \
	(*cgl_ctx->disp.matrix_mode)(cgl_ctx->rend, mode)

#define glMultMatrixd(m) \
	(*cgl_ctx->disp.mult_matrixd)(cgl_ctx->rend, m)

#define glMultMatrixf(m) \
	(*cgl_ctx->disp.mult_matrixf)(cgl_ctx->rend, m)

#define glNewList(list, mode) \
	(*cgl_ctx->disp.new_list)(cgl_ctx->rend, list, mode)

#define glNormal3b(nx, ny, nz) \
	(*cgl_ctx->disp.normal3b)(cgl_ctx->rend, nx, ny, nz)

#define glNormal3bv(v) \
	(*cgl_ctx->disp.normal3bv)(cgl_ctx->rend, v)

#define glNormal3d(nx, ny, nz) \
	(*cgl_ctx->disp.normal3d)(cgl_ctx->rend, nx, ny, nz)

#define glNormal3dv(v) \
	(*cgl_ctx->disp.normal3dv)(cgl_ctx->rend, v)

#define glNormal3f(nx, ny, nz) \
	(*cgl_ctx->disp.normal3f)(cgl_ctx->rend, nx, ny, nz)

#define glNormal3fv(v) \
	(*cgl_ctx->disp.normal3fv)(cgl_ctx->rend, v)

#define glNormal3i(nx, ny, nz) \
	(*cgl_ctx->disp.normal3i)(cgl_ctx->rend, nx, ny, nz)

#define glNormal3iv(v) \
	(*cgl_ctx->disp.normal3iv)(cgl_ctx->rend, v)

#define glNormal3s(nx, ny, nz) \
	(*cgl_ctx->disp.normal3s)(cgl_ctx->rend, nx, ny, nz)

#define glNormal3sv(v) \
	(*cgl_ctx->disp.normal3sv)(cgl_ctx->rend, v)

#define glNormalPointer(type, stride, pointer) \
	(*cgl_ctx->disp.normal_pointer)(cgl_ctx->rend, type, stride, pointer)

#define glOrtho(left, right, bottom, top, zNear, zFar) \
	(*cgl_ctx->disp.ortho)(cgl_ctx->rend, left, right, bottom, top, zNear, zFar)

#define glPassThrough(token) \
	(*cgl_ctx->disp.pass_through)(cgl_ctx->rend, token)

#define glPixelMapfv(map, mapsize, values) \
	(*cgl_ctx->disp.pixel_mapfv)(cgl_ctx->rend, map, mapsize, values)

#define glPixelMapuiv(map, mapsize, values) \
	(*cgl_ctx->disp.pixel_mapuiv)(cgl_ctx->rend, map, mapsize, values)

#define glPixelMapusv(map, mapsize, values) \
	(*cgl_ctx->disp.pixel_mapusv)(cgl_ctx->rend, map, mapsize, values)

#define glPixelStoref(pname, param) \
	(*cgl_ctx->disp.pixel_storef)(cgl_ctx->rend, pname, param)

#define glPixelStorei(pname, param) \
	(*cgl_ctx->disp.pixel_storei)(cgl_ctx->rend, pname, param)

#define glPixelTransferf(pname, param) \
	(*cgl_ctx->disp.pixel_transferf)(cgl_ctx->rend, pname, param)

#define glPixelTransferi(pname, param) \
	(*cgl_ctx->disp.pixel_transferi)(cgl_ctx->rend, pname, param)

#define glPixelZoom(xfactor, yfactor) \
	(*cgl_ctx->disp.pixel_zoom)(cgl_ctx->rend, xfactor, yfactor)

#define glPointSize(size) \
	(*cgl_ctx->disp.point_size)(cgl_ctx->rend, size)

#define glPolygonMode(face, mode) \
	(*cgl_ctx->disp.polygon_mode)(cgl_ctx->rend, face, mode)

#define glPolygonOffset(factor, units) \
	(*cgl_ctx->disp.polygon_offset)(cgl_ctx->rend, factor, units)

#define glPolygonStipple(mask) \
	(*cgl_ctx->disp.polygon_stipple)(cgl_ctx->rend, mask)

#define glPopAttrib() \
	(*cgl_ctx->disp.pop_attrib)(cgl_ctx->rend)

#define glPopClientAttrib() \
	(*cgl_ctx->disp.pop_client_attrib)(cgl_ctx->rend)

#define glPopMatrix() \
	(*cgl_ctx->disp.pop_matrix)(cgl_ctx->rend)

#define glPopName() \
	(*cgl_ctx->disp.pop_name)(cgl_ctx->rend)

#define glPrioritizeTextures(n, textures, priorities) \
	(*cgl_ctx->disp.prioritize_textures)(cgl_ctx->rend, n, textures, priorities)

#define glPushAttrib(mask) \
	(*cgl_ctx->disp.push_attrib)(cgl_ctx->rend, mask)

#define glPushClientAttrib(mask) \
	(*cgl_ctx->disp.push_client_attrib)(cgl_ctx->rend, mask)

#define glPushMatrix() \
	(*cgl_ctx->disp.push_matrix)(cgl_ctx->rend)

#define glPushName(name) \
	(*cgl_ctx->disp.push_name)(cgl_ctx->rend, name)

#define glRasterPos2d(x, y) \
	(*cgl_ctx->disp.raster_pos2d)(cgl_ctx->rend, x, y)

#define glRasterPos2dv(v) \
	(*cgl_ctx->disp.raster_pos2dv)(cgl_ctx->rend, v)

#define glRasterPos2f(x, y) \
	(*cgl_ctx->disp.raster_pos2f)(cgl_ctx->rend, x, y)

#define glRasterPos2fv(v) \
	(*cgl_ctx->disp.raster_pos2fv)(cgl_ctx->rend, v)

#define glRasterPos2i(x, y) \
	(*cgl_ctx->disp.raster_pos2i)(cgl_ctx->rend, x, y)

#define glRasterPos2iv(v) \
	(*cgl_ctx->disp.raster_pos2iv)(cgl_ctx->rend, v)

#define glRasterPos2s(x, y) \
	(*cgl_ctx->disp.raster_pos2s)(cgl_ctx->rend, x, y)

#define glRasterPos2sv(v) \
	(*cgl_ctx->disp.raster_pos2sv)(cgl_ctx->rend, v)

#define glRasterPos3d(x, y, z) \
	(*cgl_ctx->disp.raster_pos3d)(cgl_ctx->rend, x, y, z)

#define glRasterPos3dv(v) \
	(*cgl_ctx->disp.raster_pos3dv)(cgl_ctx->rend, v)

#define glRasterPos3f(x, y, z) \
	(*cgl_ctx->disp.raster_pos3f)(cgl_ctx->rend, x, y, z)

#define glRasterPos3fv(v) \
	(*cgl_ctx->disp.raster_pos3fv)(cgl_ctx->rend, v)

#define glRasterPos3i(x, y, z) \
	(*cgl_ctx->disp.raster_pos3i)(cgl_ctx->rend, x, y, z)

#define glRasterPos3iv(v) \
	(*cgl_ctx->disp.raster_pos3iv)(cgl_ctx->rend, v)

#define glRasterPos3s(x, y, z) \
	(*cgl_ctx->disp.raster_pos3s)(cgl_ctx->rend, x, y, z)

#define glRasterPos3sv(v) \
	(*cgl_ctx->disp.raster_pos3sv)(cgl_ctx->rend, v)

#define glRasterPos4d(x, y, z, w) \
	(*cgl_ctx->disp.raster_pos4d)(cgl_ctx->rend, x, y, z, w)

#define glRasterPos4dv(v) \
	(*cgl_ctx->disp.raster_pos4dv)(cgl_ctx->rend, v)

#define glRasterPos4f(x, y, z, w) \
	(*cgl_ctx->disp.raster_pos4f)(cgl_ctx->rend, x, y, z, w)

#define glRasterPos4fv(v) \
	(*cgl_ctx->disp.raster_pos4fv)(cgl_ctx->rend, v)

#define glRasterPos4i(x, y, z, w) \
	(*cgl_ctx->disp.raster_pos4i)(cgl_ctx->rend, x, y, z, w)

#define glRasterPos4iv(v) \
	(*cgl_ctx->disp.raster_pos4iv)(cgl_ctx->rend, v)

#define glRasterPos4s(x, y, z, w) \
	(*cgl_ctx->disp.raster_pos4s)(cgl_ctx->rend, x, y, z, w)

#define glRasterPos4sv(v) \
	(*cgl_ctx->disp.raster_pos4sv)(cgl_ctx->rend, v)

#define glReadBuffer(mode) \
	(*cgl_ctx->disp.read_buffer)(cgl_ctx->rend, mode)

#define glReadPixels(x, y, width, height, format, type, pixels) \
	(*cgl_ctx->disp.read_pixels)(cgl_ctx->rend, x, y, width, height, format, type, pixels)

#define glRectd(x1, y1, x2, y2) \
	(*cgl_ctx->disp.rectd)(cgl_ctx->rend, x1, y1, x2, y2)

#define glRectdv(v1, v2) \
	(*cgl_ctx->disp.rectdv)(cgl_ctx->rend, v1, v2)

#define glRectf(x1, y1, x2, y2) \
	(*cgl_ctx->disp.rectf)(cgl_ctx->rend, x1, y1, x2, y2)

#define glRectfv(v1, v2) \
	(*cgl_ctx->disp.rectfv)(cgl_ctx->rend, v1, v2)

#define glRecti(x1, y1, x2, y2) \
	(*cgl_ctx->disp.recti)(cgl_ctx->rend, x1, y1, x2, y2)

#define glRectiv(v1, v2) \
	(*cgl_ctx->disp.rectiv)(cgl_ctx->rend, v1, v2)

#define glRects(x1, y1, x2, y2) \
	(*cgl_ctx->disp.rects)(cgl_ctx->rend, x1, y1, x2, y2)

#define glRectsv(v1, v2) \
	(*cgl_ctx->disp.rectsv)(cgl_ctx->rend, v1, v2)

#define glRenderMode(mode) \
	(*cgl_ctx->disp.render_mode)(cgl_ctx->rend, mode)

#define glRotated(angle, x, y, z) \
	(*cgl_ctx->disp.rotated)(cgl_ctx->rend, angle, x, y, z)

#define glRotatef(angle, x, y, z) \
	(*cgl_ctx->disp.rotatef)(cgl_ctx->rend, angle, x, y, z)

#define glScaled(x, y, z) \
	(*cgl_ctx->disp.scaled)(cgl_ctx->rend, x, y, z)

#define glScalef(x, y, z) \
	(*cgl_ctx->disp.scalef)(cgl_ctx->rend, x, y, z)

#define glScissor(x, y, width, height) \
	(*cgl_ctx->disp.scissor)(cgl_ctx->rend, x, y, width, height)

#define glSelectBuffer(size, buffer) \
	(*cgl_ctx->disp.select_buffer)(cgl_ctx->rend, size, buffer)

#define glShadeModel(mode) \
	(*cgl_ctx->disp.shade_model)(cgl_ctx->rend, mode)

#define glStencilFunc(func, ref, mask) \
	(*cgl_ctx->disp.stencil_func)(cgl_ctx->rend, func, ref, mask)

#define glStencilMask(mask) \
	(*cgl_ctx->disp.stencil_mask)(cgl_ctx->rend, mask)

#define glStencilOp(fail, zfail, zpass) \
	(*cgl_ctx->disp.stencil_op)(cgl_ctx->rend, fail, zfail, zpass)

#define glTexCoord1d(s) \
	(*cgl_ctx->disp.tex_coord1d)(cgl_ctx->rend, s)

#define glTexCoord1dv(v) \
	(*cgl_ctx->disp.tex_coord1dv)(cgl_ctx->rend, v)

#define glTexCoord1f(s) \
	(*cgl_ctx->disp.tex_coord1f)(cgl_ctx->rend, s)

#define glTexCoord1fv(v) \
	(*cgl_ctx->disp.tex_coord1fv)(cgl_ctx->rend, v)

#define glTexCoord1i(s) \
	(*cgl_ctx->disp.tex_coord1i)(cgl_ctx->rend, s)

#define glTexCoord1iv(v) \
	(*cgl_ctx->disp.tex_coord1iv)(cgl_ctx->rend, v)

#define glTexCoord1s(s) \
	(*cgl_ctx->disp.tex_coord1s)(cgl_ctx->rend, s)

#define glTexCoord1sv(v) \
	(*cgl_ctx->disp.tex_coord1sv)(cgl_ctx->rend, v)

#define glTexCoord2d(s, t) \
	(*cgl_ctx->disp.tex_coord2d)(cgl_ctx->rend, s, t)

#define glTexCoord2dv(v) \
	(*cgl_ctx->disp.tex_coord2dv)(cgl_ctx->rend, v)

#define glTexCoord2f(s, t) \
	(*cgl_ctx->disp.tex_coord2f)(cgl_ctx->rend, s, t)

#define glTexCoord2fv(v) \
	(*cgl_ctx->disp.tex_coord2fv)(cgl_ctx->rend, v)

#define glTexCoord2i(s, t) \
	(*cgl_ctx->disp.tex_coord2i)(cgl_ctx->rend, s, t)

#define glTexCoord2iv(v) \
	(*cgl_ctx->disp.tex_coord2iv)(cgl_ctx->rend, v)

#define glTexCoord2s(s, t) \
	(*cgl_ctx->disp.tex_coord2s)(cgl_ctx->rend, s, t)

#define glTexCoord2sv(v) \
	(*cgl_ctx->disp.tex_coord2sv)(cgl_ctx->rend, v)

#define glTexCoord3d(s, t, r) \
	(*cgl_ctx->disp.tex_coord3d)(cgl_ctx->rend, s, t, r)

#define glTexCoord3dv(v) \
	(*cgl_ctx->disp.tex_coord3dv)(cgl_ctx->rend, v)

#define glTexCoord3f(s, t, r) \
	(*cgl_ctx->disp.tex_coord3f)(cgl_ctx->rend, s, t, r)

#define glTexCoord3fv(v) \
	(*cgl_ctx->disp.tex_coord3fv)(cgl_ctx->rend, v)

#define glTexCoord3i(s, t, r) \
	(*cgl_ctx->disp.tex_coord3i)(cgl_ctx->rend, s, t, r)

#define glTexCoord3iv(v) \
	(*cgl_ctx->disp.tex_coord3iv)(cgl_ctx->rend, v)

#define glTexCoord3s(s, t, r) \
	(*cgl_ctx->disp.tex_coord3s)(cgl_ctx->rend, s, t, r)

#define glTexCoord3sv(v) \
	(*cgl_ctx->disp.tex_coord3sv)(cgl_ctx->rend, v)

#define glTexCoord4d(s, t, r, q) \
	(*cgl_ctx->disp.tex_coord4d)(cgl_ctx->rend, s, t, r, q)

#define glTexCoord4dv(v) \
	(*cgl_ctx->disp.tex_coord4dv)(cgl_ctx->rend, v)

#define glTexCoord4f(s, t, r, q) \
	(*cgl_ctx->disp.tex_coord4f)(cgl_ctx->rend, s, t, r, q)

#define glTexCoord4fv(v) \
	(*cgl_ctx->disp.tex_coord4fv)(cgl_ctx->rend, v)

#define glTexCoord4i(s, t, r, q) \
	(*cgl_ctx->disp.tex_coord4i)(cgl_ctx->rend, s, t, r, q)

#define glTexCoord4iv(v) \
	(*cgl_ctx->disp.tex_coord4iv)(cgl_ctx->rend, v)

#define glTexCoord4s(s, t, r, q) \
	(*cgl_ctx->disp.tex_coord4s)(cgl_ctx->rend, s, t, r, q)

#define glTexCoord4sv(v) \
	(*cgl_ctx->disp.tex_coord4sv)(cgl_ctx->rend, v)

#define glTexCoordPointer(size, type, stride, pointer) \
	(*cgl_ctx->disp.tex_coord_pointer)(cgl_ctx->rend, size, type, stride, pointer)

#define glTexEnvf(target, pname, param) \
	(*cgl_ctx->disp.tex_envf)(cgl_ctx->rend, target, pname, param)

#define glTexEnvfv(target, pname, params) \
	(*cgl_ctx->disp.tex_envfv)(cgl_ctx->rend, target, pname, params)

#define glTexEnvi(target, pname, param) \
	(*cgl_ctx->disp.tex_envi)(cgl_ctx->rend, target, pname, param)

#define glTexEnviv(target, pname, params) \
	(*cgl_ctx->disp.tex_enviv)(cgl_ctx->rend, target, pname, params)

#define glTexGend(coord, pname, param) \
	(*cgl_ctx->disp.tex_gend)(cgl_ctx->rend, coord, pname, param)

#define glTexGendv(coord, pname, params) \
	(*cgl_ctx->disp.tex_gendv)(cgl_ctx->rend, coord, pname, params)

#define glTexGenf(coord, pname, param) \
	(*cgl_ctx->disp.tex_genf)(cgl_ctx->rend, coord, pname, param)

#define glTexGenfv(coord, pname, params) \
	(*cgl_ctx->disp.tex_genfv)(cgl_ctx->rend, coord, pname, params)

#define glTexGeni(coord, pname, param) \
	(*cgl_ctx->disp.tex_geni)(cgl_ctx->rend, coord, pname, param)

#define glTexGeniv(coord, pname, params) \
	(*cgl_ctx->disp.tex_geniv)(cgl_ctx->rend, coord, pname, params)

#define glTexImage1D(target, level, internalformat, width, border, format, type, pixels) \
	(*cgl_ctx->disp.tex_image1D)(cgl_ctx->rend, target, level, internalformat, width, border, format, type, pixels)

#define glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels) \
	(*cgl_ctx->disp.tex_image2D)(cgl_ctx->rend, target, level, internalformat, width, height, border, format, type, pixels)

#define glTexParameterf(target, pname, param) \
	(*cgl_ctx->disp.tex_parameterf)(cgl_ctx->rend, target, pname, param)

#define glTexParameterfv(target, pname, params) \
	(*cgl_ctx->disp.tex_parameterfv)(cgl_ctx->rend, target, pname, params)

#define glTexParameteri(target, pname, param) \
	(*cgl_ctx->disp.tex_parameteri)(cgl_ctx->rend, target, pname, param)

#define glTexParameteriv(target, pname, params) \
	(*cgl_ctx->disp.tex_parameteriv)(cgl_ctx->rend, target, pname, params)

#define glTexSubImage1D(target, level, xoffset, width, format, type, pixels) \
	(*cgl_ctx->disp.tex_sub_image1D)(cgl_ctx->rend, target, level, xoffset, width, format, type, pixels)

#define glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels) \
	(*cgl_ctx->disp.tex_sub_image2D)(cgl_ctx->rend, target, level, xoffset, yoffset, width, height, format, type, pixels)

#define glTranslated(x, y, z) \
	(*cgl_ctx->disp.translated)(cgl_ctx->rend, x, y, z)

#define glTranslatef(x, y, z) \
	(*cgl_ctx->disp.translatef)(cgl_ctx->rend, x, y, z)

#define glVertex2d(x, y) \
	(*cgl_ctx->disp.vertex2d)(cgl_ctx->rend, x, y)

#define glVertex2dv(v) \
	(*cgl_ctx->disp.vertex2dv)(cgl_ctx->rend, v)

#define glVertex2f(x, y) \
	(*cgl_ctx->disp.vertex2f)(cgl_ctx->rend, x, y)

#define glVertex2fv(v) \
	(*cgl_ctx->disp.vertex2fv)(cgl_ctx->rend, v)

#define glVertex2i(x, y) \
	(*cgl_ctx->disp.vertex2i)(cgl_ctx->rend, x, y)

#define glVertex2iv(v) \
	(*cgl_ctx->disp.vertex2iv)(cgl_ctx->rend, v)

#define glVertex2s(x, y) \
	(*cgl_ctx->disp.vertex2s)(cgl_ctx->rend, x, y)

#define glVertex2sv(v) \
	(*cgl_ctx->disp.vertex2sv)(cgl_ctx->rend, v)

#define glVertex3d(x, y, z) \
	(*cgl_ctx->disp.vertex3d)(cgl_ctx->rend, x, y, z)

#define glVertex3dv(v) \
	(*cgl_ctx->disp.vertex3dv)(cgl_ctx->rend, v)

#define glVertex3f(x, y, z) \
	(*cgl_ctx->disp.vertex3f)(cgl_ctx->rend, x, y, z)

#define glVertex3fv(v) \
	(*cgl_ctx->disp.vertex3fv)(cgl_ctx->rend, v)

#define glVertex3i(x, y, z) \
	(*cgl_ctx->disp.vertex3i)(cgl_ctx->rend, x, y, z)

#define glVertex3iv(v) \
	(*cgl_ctx->disp.vertex3iv)(cgl_ctx->rend, v)

#define glVertex3s(x, y, z) \
	(*cgl_ctx->disp.vertex3s)(cgl_ctx->rend, x, y, z)

#define glVertex3sv(v) \
	(*cgl_ctx->disp.vertex3sv)(cgl_ctx->rend, v)

#define glVertex4d(x, y, z, w) \
	(*cgl_ctx->disp.vertex4d)(cgl_ctx->rend, x, y, z, w)

#define glVertex4dv(v) \
	(*cgl_ctx->disp.vertex4dv)(cgl_ctx->rend, v)

#define glVertex4f(x, y, z, w) \
	(*cgl_ctx->disp.vertex4f)(cgl_ctx->rend, x, y, z, w)

#define glVertex4fv(v) \
	(*cgl_ctx->disp.vertex4fv)(cgl_ctx->rend, v)

#define glVertex4i(x, y, z, w) \
	(*cgl_ctx->disp.vertex4i)(cgl_ctx->rend, x, y, z, w)

#define glVertex4iv(v) \
	(*cgl_ctx->disp.vertex4iv)(cgl_ctx->rend, v)

#define glVertex4s(x, y, z, w) \
	(*cgl_ctx->disp.vertex4s)(cgl_ctx->rend, x, y, z, w)

#define glVertex4sv(v) \
	(*cgl_ctx->disp.vertex4sv)(cgl_ctx->rend, v)

#define glVertexPointer(size, type, stride, pointer) \
	(*cgl_ctx->disp.vertex_pointer)(cgl_ctx->rend, size, type, stride, pointer)

#define glViewport(x, y, width, height) \
	(*cgl_ctx->disp.viewport)(cgl_ctx->rend, x, y, width, height)

/****************** OpenGL 1.2 ************************************/

#define glBlendColor(red, green, blue, alpha) \
	(*cgl_ctx->disp.blend_color)(cgl_ctx->rend, red, green, blue, alpha)

#define glBlendEquation(mode) \
	(*cgl_ctx->disp.blend_equation)(cgl_ctx->rend, mode)

#define glDrawRangeElements(mode, start, end, count, type, indices) \
	(*cgl_ctx->disp.draw_range_elements)(cgl_ctx->rend, mode, start, end, count, type, indices)

#define glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, data) \
	(*cgl_ctx->disp.tex_image3D)(cgl_ctx->rend, target, level, internalformat, width, height, depth, border, format, type, data)

#define glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) \
	(*cgl_ctx->disp.tex_sub_image3D)(cgl_ctx->rend, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels)

#define glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height) \
	(*cgl_ctx->disp.copy_tex_sub_image3D)(cgl_ctx->rend, target, level, xoffset, yoffset, zoffset, x, y, width, height)

/****************** OpenGL 1.2 Imaging Subset *********************/

#define glColorTable(target, internalformat, width, format, type, table) \
	(*cgl_ctx->disp.color_table)(cgl_ctx->rend, target, internalformat, width, format, type, table)

#define glColorTableParameterfv(target, pname, params) \
	(*cgl_ctx->disp.color_table_parameterfv)(cgl_ctx->rend, target, pname, params)

#define glColorTableParameteriv(target, pname, params) \
	(*cgl_ctx->disp.color_table_parameteriv)(cgl_ctx->rend, target, pname, params)

#define glCopyColorTable(target, internalformat, x, y, width) \
	(*cgl_ctx->disp.copy_color_table)(cgl_ctx->rend, target, internalformat, x, y, width)

#define glGetColorTable(target, format, type, table) \
	(*cgl_ctx->disp.get_color_table)(cgl_ctx->rend, target, format, type, table)

#define glGetColorTableParameterfv(target, pname, params) \
	(*cgl_ctx->disp.get_color_table_parameterfv)(cgl_ctx->rend, target, pname, params)

#define glGetColorTableParameteriv(target, pname, params) \
	(*cgl_ctx->disp.get_color_table_parameteriv)(cgl_ctx->rend, target, pname, params)

#define glColorSubTable(target, start, count, format, type, data) \
	(*cgl_ctx->disp.color_sub_table)(cgl_ctx->rend, target, start, count, format, type, data)

#define glCopyColorSubTable(target, start, x, y, width) \
	(*cgl_ctx->disp.copy_color_sub_table)(cgl_ctx->rend, target, start, x, y, width)

#define glConvolutionFilter1D(target, internalformat, width, format, type, image) \
	(*cgl_ctx->disp.convolution_filter1D)(cgl_ctx->rend, target, internalformat, width, format, type, image)

#define glConvolutionFilter2D(target, internalformat, width, height, format, type, image) \
	(*cgl_ctx->disp.convolution_filter2D)(cgl_ctx->rend, target, internalformat, width, height, format, type, image)

#define glConvolutionParameterf(target, pname, param) \
	(*cgl_ctx->disp.convolution_parameterf)(cgl_ctx->rend, target, pname, param)

#define glConvolutionParameterfv(target, pname, params) \
	(*cgl_ctx->disp.convolution_parameterfv)(cgl_ctx->rend, target, pname, params)

#define glConvolutionParameteri(target, pname, param) \
	(*cgl_ctx->disp.convolution_parameteri)(cgl_ctx->rend, target, pname, param)

#define glConvolutionParameteriv(target, pname, params) \
	(*cgl_ctx->disp.convolution_parameteriv)(cgl_ctx->rend, target, pname, params)

#define glCopyConvolutionFilter1D(target, internalformat, x, y, width) \
	(*cgl_ctx->disp.copy_convolution_filter1D)(cgl_ctx->rend, target, internalformat, x, y, width)

#define glCopyConvolutionFilter2D(target, internalformat, x, y, width, height) \
	(*cgl_ctx->disp.copy_convolution_filter2D)(cgl_ctx->rend, target, internalformat, x, y, width, height)

#define glGetConvolutionFilter(target, format, type, image) \
	(*cgl_ctx->disp.get_convolution_filter)(cgl_ctx->rend, target, format, type, image)

#define glGetConvolutionParameterfv(target, pname, params) \
	(*cgl_ctx->disp.get_convolution_parameterfv)(cgl_ctx->rend, target, pname, params)

#define glGetConvolutionParameteriv(target, pname, params) \
	(*cgl_ctx->disp.get_convolution_parameteriv)(cgl_ctx->rend, target, pname, params)

#define glGetSeparableFilter(target, format, type, row, column, span) \
	(*cgl_ctx->disp.get_separable_filter)(cgl_ctx->rend, target, format, type, row, column, span)

#define glSeparableFilter2D(target, internalformat, width, height, format, type, row, column) \
	(*cgl_ctx->disp.separable_filter2D)(cgl_ctx->rend, target, internalformat, width, height, format, type, row, column)

#define glGetHistogram(target, reset, format, type, values) \
	(*cgl_ctx->disp.get_histogram)(cgl_ctx->rend, target, reset, format, type, values)

#define glGetHistogramParameterfv(target, pname, params) \
	(*cgl_ctx->disp.get_histogram_parameterfv)(cgl_ctx->rend, target, pname, params)

#define glGetHistogramParameteriv(target, pname, params) \
	(*cgl_ctx->disp.get_histogram_parameteriv)(cgl_ctx->rend, target, pname, params)

#define glGetMinmax(target, reset, format, type, values) \
	(*cgl_ctx->disp.get_minmax)(cgl_ctx->rend, target, reset, format, type, values)

#define glGetMinmaxParameterfv(target, pname, params) \
	(*cgl_ctx->disp.get_minmax_parameterfv)(cgl_ctx->rend, target, pname, params)

#define glGetMinmaxParameteriv(target, pname, params) \
	(*cgl_ctx->disp.get_minmax_parameteriv)(cgl_ctx->rend, target, pname, params)

#define glHistogram(target, width, internalformat, sink) \
	(*cgl_ctx->disp.histogram)(cgl_ctx->rend, target, width, internalformat, sink)

#define glMinmax(target, internalformat, sink) \
	(*cgl_ctx->disp.minmax)(cgl_ctx->rend, target, internalformat, sink)

#define glResetHistogram(target) \
	(*cgl_ctx->disp.reset_histogram)(cgl_ctx->rend, target)

#define glResetMinmax(target) \
	(*cgl_ctx->disp.reset_minmax)(cgl_ctx->rend, target)

/****************** OpenGL 1.3 ************************************/

#define glClientActiveTexture(target) \
	(*cgl_ctx->disp.client_active_texture)(cgl_ctx->rend, target)

#define glActiveTexture(target) \
	(*cgl_ctx->disp.active_texture)(cgl_ctx->rend, target)

#define glMultiTexCoord1d(target, s) \
	(*cgl_ctx->disp.multi_tex_coord1d)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1dv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord1dv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1f(target, s) \
	(*cgl_ctx->disp.multi_tex_coord1f)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1fv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord1fv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1i(target, s) \
	(*cgl_ctx->disp.multi_tex_coord1i)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1iv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord1iv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1s(target, s) \
	(*cgl_ctx->disp.multi_tex_coord1s)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1sv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord1sv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2d(target, s, t) \
	(*cgl_ctx->disp.multi_tex_coord2d)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2dv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord2dv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2f(target, s, t) \
	(*cgl_ctx->disp.multi_tex_coord2f)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2fv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord2fv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2i(target, s, t) \
	(*cgl_ctx->disp.multi_tex_coord2i)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2iv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord2iv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2s(target, s, t) \
	(*cgl_ctx->disp.multi_tex_coord2s)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2sv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord2sv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3d(target, s, t, r) \
	(*cgl_ctx->disp.multi_tex_coord3d)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3dv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord3dv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3f(target, s, t, r) \
	(*cgl_ctx->disp.multi_tex_coord3f)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3fv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord3fv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3i(target, s, t, r) \
	(*cgl_ctx->disp.multi_tex_coord3i)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3iv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord3iv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3s(target, s, t, r) \
	(*cgl_ctx->disp.multi_tex_coord3s)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3sv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord3sv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4d(target, s, t, r, q) \
	(*cgl_ctx->disp.multi_tex_coord4d)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4dv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord4dv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4f(target, s, t, r, q) \
	(*cgl_ctx->disp.multi_tex_coord4f)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4fv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord4fv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4i(target, s, t, r, q) \
	(*cgl_ctx->disp.multi_tex_coord4i)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4iv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord4iv)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4s(target, s, t, r, q) \
	(*cgl_ctx->disp.multi_tex_coord4s)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4sv(target, v) \
	(*cgl_ctx->disp.multi_tex_coord4sv)(cgl_ctx->rend, target, v)

#define glSampleCoverage(v, i) \
	(*cgl_ctx->disp.sample_coverage)(cgl_ctx->rend, v, i)

#define glSamplePass(mode) \
	(*cgl_ctx->disp.sample_pass)(cgl_ctx->rend, mode)

#define glLoadTransposeMatrixf(v) \
	(*cgl_ctx->disp.load_transpose_matrixf)(cgl_ctx->rend, v)

#define glLoadTransposeMatrixd(v) \
	(*cgl_ctx->disp.load_transpose_matrixd)(cgl_ctx->rend, v)

#define glMultTransposeMatrixf(v) \
	(*cgl_ctx->disp.mult_transpose_matrixf)(cgl_ctx->rend, v)

#define glMultTransposeMatrixd(v) \
	(*cgl_ctx->disp.mult_transpose_matrixd)(cgl_ctx->rend, v)

#define glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) \
	(*cgl_ctx->disp.compressed_tex_image3D)(cgl_ctx->rend, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) \
	(*cgl_ctx->disp.compressed_tex_image2D)(cgl_ctx->rend, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) \
	(*cgl_ctx->disp.compressed_tex_image1D)(cgl_ctx->rend, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
	(*cgl_ctx->disp.compressed_tex_sub_image3D)(cgl_ctx->rend, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
	(*cgl_ctx->disp.compressed_tex_sub_image2D)(cgl_ctx->rend, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) \
	(*cgl_ctx->disp.compressed_tex_sub_image1D)(cgl_ctx->rend, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImage(target, level, img) \
	(*cgl_ctx->disp.get_compressed_tex_image)(cgl_ctx->rend, target, level, img)

#define glSampleCoverage(v, i) \
	(*cgl_ctx->disp.sample_coverage)(cgl_ctx->rend, v, i)

#define glSamplePass(mode) \
	(*cgl_ctx->disp.sample_pass)(cgl_ctx->rend, mode)

/****************** OpenGL 1.4 ************************************/

#define glFogCoordf(coord) \
	(*cgl_ctx->disp.fog_coordf)(cgl_ctx->rend, coord)

#define glFogCoordfv(coord) \
	(*cgl_ctx->disp.fog_coordfv)(cgl_ctx->rend, coord)

#define glFogCoordd(coord) \
	(*cgl_ctx->disp.fog_coordd)(cgl_ctx->rend, coord)

#define glFogCoorddv(coord) \
	(*cgl_ctx->disp.fog_coorddv)(cgl_ctx->rend,coord)

#define glFogCoordPointer(type, stride, pointer) \
	(*cgl_ctx->disp.fog_coord_pointer)(cgl_ctx->rend, type, stride, pointer)

#define glSecondaryColor3b(red, green, blue) \
	(*cgl_ctx->disp.secondary_color3b)(cgl_ctx->rend, red, green, blue)

#define glSecondaryColor3bv(components) \
	(*cgl_ctx->disp.secondary_color3bv)(cgl_ctx->rend, components)

#define glSecondaryColor3d(red, green, blue) \
	(*cgl_ctx->disp.secondary_color3d)(cgl_ctx->rend, red, green, blue)

#define glSecondaryColor3dv(components) \
	(*cgl_ctx->disp.secondary_color3dv)(cgl_ctx->rend, components)

#define glSecondaryColor3f(red, green, blue) \
	(*cgl_ctx->disp.secondary_color3f)(cgl_ctx->rend, red, green, blue)

#define glSecondaryColor3fv(components) \
	(*cgl_ctx->disp.secondary_color3fv)(cgl_ctx->rend, components)

#define glSecondaryColor3i(red, green, blue) \
	(*cgl_ctx->disp.secondary_color3i)(cgl_ctx->rend, red, green, blue)

#define glSecondaryColor3iv(components) \
	(*cgl_ctx->disp.secondary_color3iv)(cgl_ctx->rend, components)

#define glSecondaryColor3s(red, green, blue) \
	(*cgl_ctx->disp.secondary_color3s)(cgl_ctx->rend, red, green, blue)

#define glSecondaryColor3sv(components) \
	(*cgl_ctx->disp.secondary_color3sv)(cgl_ctx->rend, components)

#define glSecondaryColor3ub(red, green, blue) \
	(*cgl_ctx->disp.secondary_color3ub)(cgl_ctx->rend, red, green, blue)

#define glSecondaryColor3ubv(components) \
	(*cgl_ctx->disp.secondary_color3ubv)(cgl_ctx->rend, components)

#define glSecondaryColor3ui(red, green, blue) \
	(*cgl_ctx->disp.secondary_color3ui)(cgl_ctx->rend, red, green, blue)

#define glSecondaryColor3uiv(components) \
	(*cgl_ctx->disp.secondary_color3uiv)(cgl_ctx->rend, components)

#define glSecondaryColor3us(red, green, blue) \
	(*cgl_ctx->disp.secondary_color3us)(cgl_ctx->rend, red, green, blue)

#define glSecondaryColor3usv(components) \
	(*cgl_ctx->disp.secondary_color3usv)(cgl_ctx->rend, components)

#define glSecondaryColorPointer(size, type, stride, pointer) \
	(*cgl_ctx->disp.secondary_color_pointer)(cgl_ctx->rend, size, type, stride, pointer)

#define glPointParameterf(pname, param) \
	(*cgl_ctx->disp.point_parameterf)(cgl_ctx->rend, pname, param)

#define glPointParameterfv(pname, params) \
	(*cgl_ctx->disp.point_parameterfv)(cgl_ctx->rend, pname, params)

#define glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha) \
	(*cgl_ctx->disp.blend_func_separate)(cgl_ctx->rend, sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha)

#define glMultiDrawArrays(mode, first, count, primcount) \
	(*cgl_ctx->disp.multi_draw_arrays)(cgl_ctx->rend, mode, first, count, primcount)

#define glMultiDrawElements(mode, count, type, indices, primcount) \
	(*cgl_ctx->disp.multi_draw_elements)(cgl_ctx->rend, mode, count, type, indices, primcount)

#define glWindowPos2d(x, y) \
	(*cgl_ctx->disp.window_pos2d)(cgl_ctx->rend, x, y)

#define glWindowPos2dv(v) \
	(*cgl_ctx->disp.window_pos2dv)(cgl_ctx->rend, v)

#define glWindowPos2f(x, y) \
	(*cgl_ctx->disp.window_pos2f)(cgl_ctx->rend, x, y)

#define glWindowPos2fv(v) \
	(*cgl_ctx->disp.window_pos2fv)(cgl_ctx->rend, v)

#define glWindowPos2i(x, y) \
	(*cgl_ctx->disp.window_pos2i)(cgl_ctx->rend, x, y)

#define glWindowPos2iv(v) \
	(*cgl_ctx->disp.window_pos2iv)(cgl_ctx->rend, v)

#define glWindowPos2s(x, y) \
	(*cgl_ctx->disp.window_pos2s)(cgl_ctx->rend, x, y)

#define glWindowPos2sv(v) \
	(*cgl_ctx->disp.window_pos2sv)(cgl_ctx->rend, v)

#define glWindowPos3d(x, y, z) \
	(*cgl_ctx->disp.window_pos3d)(cgl_ctx->rend, x, y, z)

#define glWindowPos3dv(v) \
	(*cgl_ctx->disp.window_pos3dv)(cgl_ctx->rend, v)

#define glWindowPos3f(x, y, z) \
	(*cgl_ctx->disp.window_pos3f)(cgl_ctx->rend, x, y, z)

#define glWindowPos3fv(v) \
	(*cgl_ctx->disp.window_pos3fv)(cgl_ctx->rend, v)

#define glWindowPos3i(x, y, z) \
	(*cgl_ctx->disp.window_pos3i)(cgl_ctx->rend, x, y, z)

#define glWindowPos3iv(v) \
	(*cgl_ctx->disp.window_pos3iv)(cgl_ctx->rend, v)

#define glWindowPos3s(x, y, z) \
	(*cgl_ctx->disp.window_pos3s)(cgl_ctx->rend, x, y, z)

#define glWindowPos3sv(v) \
	(*cgl_ctx->disp.window_pos3sv)(cgl_ctx->rend, v)

/*********** ARB Extensions *************************************************/

/* GL_ARB_vertex_program */
#define glBindProgramARB(target, id) \
	(*cgl_ctx->disp.bind_program_ARB)(cgl_ctx->rend, target, id)

#define glDeleteProgramsARB(n, programs) \
	(*cgl_ctx->disp.delete_programs_ARB)(cgl_ctx->rend, n, programs)

#define glGenProgramsARB(n, programs) \
	(*cgl_ctx->disp.gen_programs_ARB)(cgl_ctx->rend, n, programs)

#define glIsProgramARB(id) \
	(*cgl_ctx->disp.is_program_ARB)(cgl_ctx->rend, id)

#define glVertexAttrib1sARB(index, x) \
	(*cgl_ctx->disp.vertex_attrib1s_ARB)(cgl_ctx->rend, index, x)

#define glVertexAttrib1fARB(index, x) \
	(*cgl_ctx->disp.vertex_attrib1f_ARB)(cgl_ctx->rend, index, x)

#define glVertexAttrib1dARB(index, x) \
	(*cgl_ctx->disp.vertex_attrib1d_ARB)(cgl_ctx->rend, index, x)

#define glVertexAttrib2sARB(index, x, y) \
	(*cgl_ctx->disp.vertex_attrib2s_ARB)(cgl_ctx->rend, index, x, y)

#define glVertexAttrib2fARB(index, x, y) \
	(*cgl_ctx->disp.vertex_attrib2f_ARB)(cgl_ctx->rend, index, x, y)

#define glVertexAttrib2dARB(index, x, y) \
	(*cgl_ctx->disp.vertex_attrib2d_ARB)(cgl_ctx->rend, index, x, y)

#define glVertexAttrib3sARB(index, x, y, z) \
	(*cgl_ctx->disp.vertex_attrib3s_ARB)(cgl_ctx->rend, index, x, y, z)

#define glVertexAttrib3fARB(index, x, y, z) \
	(*cgl_ctx->disp.vertex_attrib3f_ARB)(cgl_ctx->rend, index, x, y, z)

#define glVertexAttrib3dARB(index, x, y, z) \
	(*cgl_ctx->disp.vertex_attrib3d_ARB)(cgl_ctx->rend, index, x, y, z)

#define glVertexAttrib4sARB(index, x, y, z, w) \
	(*cgl_ctx->disp.vertex_attrib4s_ARB)(cgl_ctx->rend, index, x, y, z, w)

#define glVertexAttrib4fARB(index, x, y, z, w) \
	(*cgl_ctx->disp.vertex_attrib4f_ARB)(cgl_ctx->rend, index, x, y, z, w)

#define glVertexAttrib4dARB(index, x, y, z, w) \
	(*cgl_ctx->disp.vertex_attrib4d_ARB)(cgl_ctx->rend, index, x, y, z, w)

#define glVertexAttrib4NubARB(index, x, y, z, w) \
	(*cgl_ctx->disp.vertex_attrib4Nub_ARB)(cgl_ctx->rend, index, x, y, z, w)

#define glVertexAttrib1svARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib1sv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib1fvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib1fv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib1dvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib1dv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib2svARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib2sv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib2fvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib2fv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib2dvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib2dv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib3svARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib3sv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib3fvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib3fv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib3dvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib3dv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4bvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4bv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4ubvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4ubv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4svARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4sv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4usvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4usv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4ivARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4iv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4uivARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4uiv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4fvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4fv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4dvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4dv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4NbvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4Nbv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4NubvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4Nubv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4NsvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4Nsv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4NusvARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4Nusv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4NivARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4Niv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttrib4NuivARB(index, addr) \
	(*cgl_ctx->disp.vertex_attrib4Nuiv_ARB)(cgl_ctx->rend, index, addr)

#define glVertexAttribPointerARB(index, size, type, normalized, stride, addr) \
	(*cgl_ctx->disp.vertex_attrib_pointer_ARB)(cgl_ctx->rend, index, size, type, normalized, stride, addr)

#define glEnableVertexAttribArrayARB(index) \
	(*cgl_ctx->disp.enable_vertex_attrib_array_ARB)(cgl_ctx->rend, index)

#define glDisableVertexAttribArrayARB(index) \
	(*cgl_ctx->disp.disable_vertex_attrib_array_ARB)(cgl_ctx->rend, index)

#define glGetVertexAttribdvARB(index, pname, params) \
	(*cgl_ctx->disp.get_vertex_attribdv_ARB)(cgl_ctx->rend, index, pname, params)

#define glGetVertexAttribfvARB(index, pname, params) \
	(*cgl_ctx->disp.get_vertex_attribfv_ARB)(cgl_ctx->rend, index, pname, params)

#define glGetVertexAttribivARB(index, pname, params) \
	(*cgl_ctx->disp.get_vertex_attribiv_ARB)(cgl_ctx->rend, index, pname, params)

#define glGetVertexAttribPointervARB(index, pname, pointer) \
	(*cgl_ctx->disp.get_vertex_attrib_pointerv_ARB)(cgl_ctx->rend, index, pname, pointer)

#define glProgramEnvParameter4dARB(target, index, x, y, z, w) \
	(*cgl_ctx->disp.program_env_parameter4d_ARB)(cgl_ctx->rend, target, index, x, y, z, w)

#define glProgramEnvParameter4dvARB(target, index, params) \
	(*cgl_ctx->disp.program_env_parameter4dv_ARB)(cgl_ctx->rend, target, index, params)

#define glProgramEnvParameter4fARB(target, index, x, y, z, w) \
	(*cgl_ctx->disp.program_env_parameter4f_ARB)(cgl_ctx->rend, target, index, x, y, z, w)

#define glProgramEnvParameter4fvARB(target, index, params) \
	(*cgl_ctx->disp.program_env_parameter4fv_ARB)(cgl_ctx->rend, target, index, params)

#define glProgramLocalParameter4dARB(target, index, x, y, z, w) \
	(*cgl_ctx->disp.program_local_parameter4d_ARB)(cgl_ctx->rend, target, index, x, y, z, w)

#define glProgramLocalParameter4dvARB(target, index, params) \
	(*cgl_ctx->disp.program_local_parameter4dv_ARB)(cgl_ctx->rend, target, index, params)

#define glProgramLocalParameter4fARB(target, index, x, y, z, w) \
	(*cgl_ctx->disp.program_local_parameter4f_ARB)(cgl_ctx->rend, target, index, x, y, z, w)

#define glProgramLocalParameter4fvARB(target, index, params) \
	(*cgl_ctx->disp.program_local_parameter4fv_ARB)(cgl_ctx->rend, target, index, params)

#define glGetProgramEnvParameterdvARB(target, index, params) \
	(*cgl_ctx->disp.get_program_env_parameterdv_ARB)(cgl_ctx->rend, target, index, params)

#define glGetProgramEnvParameterfvARB(target, index, params) \
	(*cgl_ctx->disp.get_program_env_parameterfv_ARB)(cgl_ctx->rend, target, index, params)

#define glGetProgramLocalParameterdvARB(target, index, params) \
	(*cgl_ctx->disp.get_program_local_parameterdv_ARB)(cgl_ctx->rend, target, index, params)

#define glGetProgramLocalParameterfvARB(target, index, params) \
	(*cgl_ctx->disp.get_program_local_parameterfv_ARB)(cgl_ctx->rend, target, index, params)

#define glProgramStringARB(target, format, length, string) \
	(*cgl_ctx->disp.program_string_ARB)(cgl_ctx->rend, target, format, length, string)

#define glGetProgramStringARB(target, pname, string) \
	(*cgl_ctx->disp.get_program_string_ARB)(cgl_ctx->rend, target, pname, string)

#define glGetProgramivARB(target, pname, params) \
	(*cgl_ctx->disp.get_programiv_ARB)(cgl_ctx->rend, target, pname, params)

/* GL_ARB_vertex_blend */
#define glWeightbvARB(size, weights) \
	(*cgl_ctx->disp.weightbv_ARB)(cgl_ctx->rend, size, weights)

#define glWeightsvARB(size, weights) \
	(*cgl_ctx->disp.weightsv_ARB)(cgl_ctx->rend, size, weights)

#define glWeightivARB(size, weights) \
	(*cgl_ctx->disp.weightiv_ARB)(cgl_ctx->rend, size, weights)

#define glWeightfvARB(size, weights) \
	(*cgl_ctx->disp.weightfv_ARB)(cgl_ctx->rend, size, weights)

#define glWeightdvARB(size, weights) \
	(*cgl_ctx->disp.weightdv_ARB)(cgl_ctx->rend, size, weights)

#define glWeightubvARB(size, weights) \
	(*cgl_ctx->disp.weightubv_ARB)(cgl_ctx->rend, size, weights)

#define glWeightusvARB(size, weights) \
	(*cgl_ctx->disp.weightusv_ARB)(cgl_ctx->rend, size, weights)

#define glWeightuivARB(size, weights) \
	(*cgl_ctx->disp.weightuiv_ARB)(cgl_ctx->rend, size, weights)

#define glWeightPointerARB(size, type, stride, pointer) \
	(*cgl_ctx->disp.weight_pointer_ARB)(cgl_ctx->rend, size, type, stride, pointer)

#define glVertexBlendARB(count) \
	(*cgl_ctx->disp.vertex_blend_ARB)(cgl_ctx->rend, count)

/* GL_ARB_multitexture */
#define glClientActiveTextureARB glClientActiveTexture
#define glActiveTextureARB       glActiveTexture
#define glMultiTexCoord1dARB  glMultiTexCoord1d
#define glMultiTexCoord1dvARB glMultiTexCoord1dv
#define glMultiTexCoord1fARB  glMultiTexCoord1f
#define glMultiTexCoord1fvARB glMultiTexCoord1fv
#define glMultiTexCoord1iARB  glMultiTexCoord1i
#define glMultiTexCoord1ivARB glMultiTexCoord1iv
#define glMultiTexCoord1sARB  glMultiTexCoord1s
#define glMultiTexCoord1svARB glMultiTexCoord1sv
#define glMultiTexCoord2dARB  glMultiTexCoord2d
#define glMultiTexCoord2dvARB glMultiTexCoord2dv
#define glMultiTexCoord2fARB  glMultiTexCoord2f
#define glMultiTexCoord2fvARB glMultiTexCoord2fv
#define glMultiTexCoord2iARB  glMultiTexCoord2i
#define glMultiTexCoord2ivARB glMultiTexCoord2iv
#define glMultiTexCoord2sARB  glMultiTexCoord2s
#define glMultiTexCoord2svARB glMultiTexCoord2sv
#define glMultiTexCoord3dARB  glMultiTexCoord3d
#define glMultiTexCoord3dvARB glMultiTexCoord3dv
#define glMultiTexCoord3fARB  glMultiTexCoord3f
#define glMultiTexCoord3fvARB glMultiTexCoord3fv
#define glMultiTexCoord3iARB  glMultiTexCoord3i
#define glMultiTexCoord3ivARB glMultiTexCoord3iv
#define glMultiTexCoord3sARB  glMultiTexCoord3s
#define glMultiTexCoord3svARB glMultiTexCoord3sv
#define glMultiTexCoord4dARB  glMultiTexCoord4d
#define glMultiTexCoord4dvARB glMultiTexCoord4dv
#define glMultiTexCoord4fARB  glMultiTexCoord4f
#define glMultiTexCoord4fvARB glMultiTexCoord4fv
#define glMultiTexCoord4iARB  glMultiTexCoord4i
#define glMultiTexCoord4ivARB glMultiTexCoord4iv
#define glMultiTexCoord4sARB  glMultiTexCoord4s
#define glMultiTexCoord4svARB glMultiTexCoord4sv

/* GL_ARB_transpose_matrix */
#define glLoadTransposeMatrixfARB glLoadTransposeMatrixf
#define glLoadTransposeMatrixdARB glLoadTransposeMatrixd
#define glMultTransposeMatrixfARB glMultTransposeMatrixf
#define glMultTransposeMatrixdARB glMultTransposeMatrixd

/* GL_ARB_texture_compression */
#define glCompressedTexImage3DARB    glCompressedTexImage3D
#define glCompressedTexImage2DARB    glCompressedTexImage2D
#define glCompressedTexImage1DARB    glCompressedTexImage1D
#define glCompressedTexSubImage3DARB glCompressedTexSubImage3D
#define glCompressedTexSubImage2DARB glCompressedTexSubImage2D
#define glCompressedTexSubImage1DARB glCompressedTexSubImage1D
#define glGetCompressedTexImageARB   glGetCompressedTexImage

/* GL_ARB_multisample */
#define glSampleCoverageARB glSampleCoverage
#define glSamplePassARB     glSamplePass

/* GL_ARB_point_parameters */
#define glPointParameterfARB  glPointParameterf
#define glPointParameterfvARB glPointParameterfv

/* GL_ARB_window_pos */
#define glWindowPos2dARB  glWindowPos2d
#define glWindowPos2dvARB glWindowPos2dv
#define glWindowPos2fARB  glWindowPos2f
#define glWindowPos2fvARB glWindowPos2fv
#define glWindowPos2iARB  glWindowPos2i
#define glWindowPos2ivARB glWindowPos2iv
#define glWindowPos2sARB  glWindowPos2s
#define glWindowPos2svARB glWindowPos2sv
#define glWindowPos3dARB  glWindowPos3d
#define glWindowPos3dvARB glWindowPos3dv
#define glWindowPos3fARB  glWindowPos3f
#define glWindowPos3fvARB glWindowPos3fv
#define glWindowPos3iARB  glWindowPos3i
#define glWindowPos3ivARB glWindowPos3iv
#define glWindowPos3sARB  glWindowPos3s
#define glWindowPos3svARB glWindowPos3sv

/*********** EXT Extensions *************************************************/

/* GL_EXT_compiled_vertex_array */
#define glLockArraysEXT(first, count) \
	(*cgl_ctx->disp.lock_arrays_EXT)(cgl_ctx->rend, first, count)

#define glUnlockArraysEXT() \
	(*cgl_ctx->disp.unlock_arrays_EXT)(cgl_ctx->rend)

/* GL_EXT_stencil_two_side */
#define glActiveStencilFaceEXT(face) \
	(*cgl_ctx->disp.active_stencil_face_EXT)(cgl_ctx->rend, face)

/* GL_ATI_separate_stencil */
#define glStencilOpSeparateATI(face, sfail, dpfail, dppass) \
	(*cgl_ctx->disp.stencil_op_separate_ATI)(cgl_ctx->rend, face, sfail, dpfail, dppass)

#define glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask) \
	(*cgl_ctx->disp.stencil_func_separate_ATI)(cgl_ctx->rend, frontfunc, backfunc, ref, mask)

/* GL_EXT_paletted_texture */
#define glColorTableEXT glColorTable
#define glColorSubTableEXT glColorSubTable
#define glGetColorTableEXT glGetColorTable
#define glGetColorTableParameterivEXT glGetColorTableParameteriv
#define glGetColorTableParameterfvEXT glGetColorTableParameterfv

/* GL_EXT_secondary_color */
#define glSecondaryColor3bEXT glSecondaryColor3b
#define glSecondaryColor3bvEXT glSecondaryColor3bv
#define glSecondaryColor3dEXT glSecondaryColor3d
#define glSecondaryColor3dvEXT glSecondaryColor3dv
#define glSecondaryColor3fEXT glSecondaryColor3f
#define glSecondaryColor3fvEXT glSecondaryColor3fv
#define glSecondaryColor3iEXT glSecondaryColor3i
#define glSecondaryColor3ivEXT glSecondaryColor3iv
#define glSecondaryColor3sEXT glSecondaryColor3s
#define glSecondaryColor3svEXT glSecondaryColor3sv
#define glSecondaryColor3ubEXT glSecondaryColor3ub
#define glSecondaryColor3ubvEXT glSecondaryColor3ubv
#define glSecondaryColor3uiEXT glSecondaryColor3ui
#define glSecondaryColor3uivEXT glSecondaryColor3uiv
#define glSecondaryColor3usEXT glSecondaryColor3us
#define glSecondaryColor3usvEXT glSecondaryColor3usv
#define glSecondaryColorPointerEXT glSecondaryColorPointer

/* GL_EXT_fog_coord */
#define glFogCoordfEXT glFogCoordf
#define glFogCoordfvEXT glFogCoordfv
#define glFogCoorddEXT glFogCoordd
#define glFogCoorddvEXT glFogCoorddv
#define glFogCoordPointerEXT glFogCoordPointer

/* GL_EXT_draw_range_elements */
#define glDrawRangeElementsEXT glDrawRangeElements

/* GL_EXT_blend_func_separate */
#define glBlendFuncSeparateEXT glBlendFuncSeparate

/* GL_EXT_multi_draw_arrays */
#define glMultiDrawArraysEXT glMultiDrawArrays
#define glMultiDrawElementsEXT glMultiDrawElements

/* GL_EXT_blend_color */
#define glBlendColorEXT glBlendColor

/* GL_EXT_blend_minmax */
#define glBlendEquationEXT glBlendEquation

/*********** APPLE Extensions ***********************************************/

/* GL_APPLE_vertex_program_evaluators */
#define glEnableVertexAttribAPPLE(index, pname) \
	(*cgl_ctx->disp.enable_vertex_attrib_ARB)(cgl_ctx->rend, index, pname)

#define glDisableVertexAttribAPPLE(index, pname) \
	(*cgl_ctx->disp.disable_vertex_attrib_ARB)(cgl_ctx->rend, index, pname)

#define glIsVertexAttribEnabledAPPLE(index, pname) \
	(*cgl_ctx->disp.is_vertex_attrib_enabled_ARB)(cgl_ctx->rend, index, pname)

#define glMapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points) \
	(*cgl_ctx->disp.map_vertex_attrib1d_ARB)(cgl_ctx->rend, index, size, u1, u2, stride, order, points)

#define glMapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points) \
	(*cgl_ctx->disp.map_vertex_attrib1f_ARB)(cgl_ctx->rend, index, size, u1, u2, stride, order, points)

#define glMapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*cgl_ctx->disp.map_vertex_attrib2d_ARB)(cgl_ctx->rend, index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*cgl_ctx->disp.map_vertex_attrib2f_ARB)(cgl_ctx->rend, index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

/* GL_APPLE_texture_range */
#define glTextureRangeAPPLE(target, length, pointer) \
	(*cgl_ctx->disp.texture_range_APPLE)(cgl_ctx->rend, target, length, pointer)

#define glGetTexParameterPointervAPPLE(target, pname, params) \
	(*cgl_ctx->disp.get_tex_parameter_pointerv_APPLE)(cgl_ctx->rend, target, pname, params)

/* GL_APPLE_fence */
#define glGenFencesAPPLE(n, fences) \
	(*cgl_ctx->disp.gen_fences_APPLE)(cgl_ctx->rend, n, fences)

#define glDeleteFencesAPPLE(n, fences) \
	(*cgl_ctx->disp.delete_fences_APPLE)(cgl_ctx->rend, n, fences)

#define glSetFenceAPPLE(fence) \
	(*cgl_ctx->disp.set_fence_APPLE)(cgl_ctx->rend, fence)

#define glIsFenceAPPLE(fence) \
	(*cgl_ctx->disp.is_fence_APPLE)(cgl_ctx->rend, fence)

#define glTestFenceAPPLE(fence) \
	(*cgl_ctx->disp.test_fence_APPLE)(cgl_ctx->rend, fence)

#define glFinishFenceAPPLE(fence) \
	(*cgl_ctx->disp.finish_fence_APPLE)(cgl_ctx->rend, fence)

#define glTestObjectAPPLE(object, name) \
	(*cgl_ctx->disp.test_object_APPLE)(cgl_ctx->rend, object, name)

#define glFinishObjectAPPLE(object, name) \
	(*cgl_ctx->disp.finish_object_APPLE)(cgl_ctx->rend, object, name)

/* GL_APPLE_vertex_array_range */
#define glVertexArrayRangeAPPLE(length, pointer) \
	(*cgl_ctx->disp.vertex_array_range_EXT)(cgl_ctx->rend, length, pointer)

#define glFlushVertexArrayRangeAPPLE(length, pointer) \
	(*cgl_ctx->disp.flush_vertex_array_range_EXT)(cgl_ctx->rend, length, pointer)

#define glVertexArrayParameteriAPPLE(pname, param) \
	(*cgl_ctx->disp.vertex_array_parameteri_EXT)(cgl_ctx->rend, pname, param)

/* GL_APPLE_vertex_array_object */
#define glBindVertexArrayAPPLE(id) \
	(*cgl_ctx->disp.bind_vertex_array_EXT)(cgl_ctx->rend, id)

#define glDeleteVertexArraysAPPLE(n, ids) \
	(*cgl_ctx->disp.delete_vertex_arrays_EXT)(cgl_ctx->rend, n, ids)

#define glGenVertexArraysAPPLE(n, ids) \
	(*cgl_ctx->disp.gen_vertex_arrays_EXT)(cgl_ctx->rend, n, ids)

#define glIsVertexArrayAPPLE(id) \
	(*cgl_ctx->disp.is_vertex_array_EXT)(cgl_ctx->rend, id)

/* GL_APPLE_element_array */
#define glElementPointerAPPLE(type, pointer) \
	(*cgl_ctx->disp.element_pointer_APPLE)(cgl_ctx->rend, type, pointer)

#define glDrawElementArrayAPPLE(mode, first, count) \
	(*cgl_ctx->disp.draw_element_array_APPLE)(cgl_ctx->rend, mode, first, count)

#define glDrawRangeElementArrayAPPLE(mode, start, end, first, count) \
	(*cgl_ctx->disp.draw_range_element_array_APPLE)(cgl_ctx->rend, mode, start, end, first, count)

/* GL_APPLE_flush_render */
#define glFlushRenderAPPLE() \
	(*cgl_ctx->disp.flush_render_APPLE)(cgl_ctx->rend)

#define glFinishRenderAPPLE() \
	(*cgl_ctx->disp.finish_render_APPLE)(cgl_ctx->rend)

#define glSwapAPPLE() \
	(*cgl_ctx->disp.swap_APPLE)(cgl_ctx->rend)


/*********** ATI Extensions *************************************************/

/* GL_ATI_blend_equation_separate */
#define glBlendEquationSeparateATI(equationRGB, equationAlpha) \
	(*cgl_ctx->disp.blend_equation_separate_ATI)(cgl_ctx->rend, equationRGB, equationAlpha)

/* GL_ATI_pn_triangles */
#define glPNTrianglesiATI(pname, param) \
    (*cgl_ctx->disp.pn_trianglesi_ATI)(cgl_ctx->rend, pname, param)

#define glPNTrianglesfATI(pname, param) \
    (*cgl_ctx->disp.pn_trianglesf_ATI)(cgl_ctx->rend, pname, param)

/* GL_ATIX_pn_triangles */
#define glPNTrianglesiATIX glPNTrianglesiATI
#define glPNTrianglesfATIX glPNTrianglesfATI

/*********** NVIDIA Extensions **********************************************/

/* GL_NV_point_sprite */
#define glPointParameteriNV(pname, param) \
	(*cgl_ctx->disp.point_parameteri)(cgl_ctx->rend, pname, param)

#define glPointParameterivNV(pname, params) \
	(*cgl_ctx->disp.point_parameteriv)(cgl_ctx->rend, pname, params)

/* GL_NV_register_combiners */
#define glCombinerParameterfvNV(pname, params) \
	(*cgl_ctx->disp.combiner_parameterfv_NV)(cgl_ctx->rend, pname, params)

#define glCombinerParameterfNV(pname, param) \
	(*cgl_ctx->disp.combiner_parameterf_NV)(cgl_ctx->rend, pname, param)

#define glCombinerParameterivNV(pname, params) \
	(*cgl_ctx->disp.combiner_parameteriv_NV)(cgl_ctx->rend, pname, params)

#define glCombinerParameteriNV(pname, param) \
	(*cgl_ctx->disp.combiner_parameteri_NV)(cgl_ctx->rend, pname, param)

#define glCombinerInputNV(stage, portion, variable, input, mapping ,componentUsage) \
	(*cgl_ctx->disp.combiner_input_NV)(cgl_ctx->rend, stage, portion, variable, input, mapping ,componentUsage)

#define glCombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDoProduct, muxSum) \
	(*cgl_ctx->disp.combiner_output_NV)(cgl_ctx->rend, stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDoProduct, muxSum)

#define glFinalCombinerInputNV(variable, input, mapping, componentUsage) \
	(*cgl_ctx->disp.final_combiner_input_NV)(cgl_ctx->rend, variable, input, mapping, componentUsage)

#define glGetCombinerInputParameterfvNV(stage, portion, variable, pname, params) \
	(*cgl_ctx->disp.get_combiner_input_parameterfv_NV)(cgl_ctx->rend, stage, portion, variable, pname, params)

#define glGetCombinerInputParameterivNV(stage, portion, variable, pname, params) \
	(*cgl_ctx->disp.get_combiner_input_parameteriv_NV)(cgl_ctx->rend, stage, portion, variable, pname, params)

#define glGetCombinerOutputParameterfvNV(stage, portion, pname, params) \
	(*cgl_ctx->disp.get_combiner_output_parameterfv_NV)(cgl_ctx->rend, stage, portion, pname, params)

#define glGetCombinerOutputParameterivNV(stage, portion, pname, params) \
	(*cgl_ctx->disp.get_combiner_output_parameteriv_NV)(cgl_ctx->rend, stage, portion, pname, params)

#define glGetFinalCombinerInputParameterfvNV(variable, pname, params) \
	(*cgl_ctx->disp.get_final_combiner_input_parameterfv_NV)(cgl_ctx->rend, variable, pname, params)

#define glGetFinalCombinerInputParameterfvNV(variable, pname, params) \
	(*cgl_ctx->disp.get_final_combiner_input_parameterfv_NV)(cgl_ctx->rend, variable, pname, params)

/* GL_NV_register_combiners2 */
#define glCombinerStageParameterfvNV(stage, pname, params) \
	(*cgl_ctx->disp.combiner_stage_parameterfv_NV)(cgl_ctx->rend, stage, pname, params)

#define glGetCombinerStageParameterfvNV(stage, pname, param) \
	(*cgl_ctx->disp.get_combiner_stage_parameterfv_NV)(cgl_ctx->rend, stage, pname, param)

#endif /* _CGLMACRO_H */

