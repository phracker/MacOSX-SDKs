/*
    File:	AGL/aglMacro.h

    Contains:	Macros that replace OpenGL function calls when you use the internal renderer interface.

    Version:	Technology:	Mac OS X
                Release:	GM
 
     Copyright: (c) 2000-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _AGLMACRO_H
#define _AGLMACRO_H

#include "aglContext.h"

/****************** OpenGL 1.1 Macros *****************************/

/* Macro context name */
#define AGL_MACRO_CONTEXT agl_ctx

#define glAccum(op, value) \
	(*agl_ctx->disp.accum)(agl_ctx->rend, op, value)

#define glAlphaFunc(func, ref) \
	(*agl_ctx->disp.alpha_func)(agl_ctx->rend, func, ref)

#define glAreTexturesResident(n, textures, residences) \
	(*agl_ctx->disp.are_textures_resident)(agl_ctx->rend, n, textures, residences)

#define glArrayElement(i) \
	(*agl_ctx->disp.array_element)(agl_ctx->rend, i)

#define glBegin(mode) \
	(*agl_ctx->disp.begin)(agl_ctx->rend, mode)

#define glBindTexture(target, texture) \
	(*agl_ctx->disp.bind_texture)(agl_ctx->rend, target, texture)

#define glBitmap(width, height, xorig, yorig, xmove, ymove, bmap) \
	(*agl_ctx->disp.bitmap)(agl_ctx->rend, width, height, xorig, yorig, xmove, ymove, bmap)

#define glBlendFunc(sfactor, dfactor) \
	(*agl_ctx->disp.blend_func)(agl_ctx->rend, sfactor, dfactor)

#define glCallList(list) \
	(*agl_ctx->disp.call_list)(agl_ctx->rend, list)

#define glCallLists(n, type, lists) \
	(*agl_ctx->disp.call_lists)(agl_ctx->rend, n, type, lists)

#define glClear(mask) \
	(*agl_ctx->disp.clear)(agl_ctx->rend, mask)

#define glClearAccum(red, green, blue, alpha) \
	(*agl_ctx->disp.clear_accum)(agl_ctx->rend, red, green, blue, alpha)

#define glClearColor(red, green, blue, alpha) \
	(*agl_ctx->disp.clear_color)(agl_ctx->rend, red, green, blue, alpha)

#define glClearDepth(depth) \
	(*agl_ctx->disp.clear_depth)(agl_ctx->rend, depth)

#define glClearIndex(c) \
	(*agl_ctx->disp.clear_index)(agl_ctx->rend, c)

#define glClearStencil(s) \
	(*agl_ctx->disp.clear_stencil)(agl_ctx->rend, s)

#define glClipPlane(plane, equation) \
	(*agl_ctx->disp.clip_plane)(agl_ctx->rend, plane, equation)

#define glColor3b(red, green, blue) \
	(*agl_ctx->disp.color3b)(agl_ctx->rend, red, green, blue)

#define glColor3bv(v) \
	(*agl_ctx->disp.color3bv)(agl_ctx->rend, v)

#define glColor3d(red, green, blue) \
	(*agl_ctx->disp.color3d)(agl_ctx->rend, red, green, blue)

#define glColor3dv(v) \
	(*agl_ctx->disp.color3dv)(agl_ctx->rend, v)

#define glColor3f(red, green, blue) \
	(*agl_ctx->disp.color3f)(agl_ctx->rend, red, green, blue)

#define glColor3fv(v) \
	(*agl_ctx->disp.color3fv)(agl_ctx->rend, v)

#define glColor3i(red, green, blue) \
	(*agl_ctx->disp.color3i)(agl_ctx->rend, red, green, blue)

#define glColor3iv(v) \
	(*agl_ctx->disp.color3iv)(agl_ctx->rend, v)

#define glColor3s(red, green, blue) \
	(*agl_ctx->disp.color3s)(agl_ctx->rend, red, green, blue)

#define glColor3sv(v) \
	(*agl_ctx->disp.color3sv)(agl_ctx->rend, v)

#define glColor3ub(red, green, blue) \
	(*agl_ctx->disp.color3ub)(agl_ctx->rend, red, green, blue)

#define glColor3ubv(v) \
	(*agl_ctx->disp.color3ubv)(agl_ctx->rend, v)

#define glColor3ui(red, green, blue) \
	(*agl_ctx->disp.color3ui)(agl_ctx->rend, red, green, blue)

#define glColor3uiv(v) \
	(*agl_ctx->disp.color3uiv)(agl_ctx->rend, v)

#define glColor3us(red, green, blue) \
	(*agl_ctx->disp.color3us)(agl_ctx->rend, red, green, blue)

#define glColor3usv(v) \
	(*agl_ctx->disp.color3usv)(agl_ctx->rend, v)

#define glColor4b(red, green, blue, alpha) \
	(*agl_ctx->disp.color4b)(agl_ctx->rend, red, green, blue, alpha)

#define glColor4bv(v) \
	(*agl_ctx->disp.color4bv)(agl_ctx->rend, v)

#define glColor4d(red, green, blue, alpha) \
	(*agl_ctx->disp.color4d)(agl_ctx->rend, red, green, blue, alpha)

#define glColor4dv(v) \
	(*agl_ctx->disp.color4dv)(agl_ctx->rend, v)

#define glColor4f(red, green, blue, alpha) \
	(*agl_ctx->disp.color4f)(agl_ctx->rend, red, green, blue, alpha)

#define glColor4fv(v) \
	(*agl_ctx->disp.color4fv)(agl_ctx->rend, v)

#define glColor4i(red, green, blue, alpha) \
	(*agl_ctx->disp.color4i)(agl_ctx->rend, red, green, blue, alpha)

#define glColor4iv(v) \
	(*agl_ctx->disp.color4iv)(agl_ctx->rend, v)

#define glColor4s(red, green, blue, alpha) \
	(*agl_ctx->disp.color4s)(agl_ctx->rend, red, green, blue, alpha)

#define glColor4sv(v) \
	(*agl_ctx->disp.color4sv)(agl_ctx->rend, v)

#define glColor4ub(red, green, blue, alpha) \
	(*agl_ctx->disp.color4ub)(agl_ctx->rend, red, green, blue, alpha)

#define glColor4ubv(v) \
	(*agl_ctx->disp.color4ubv)(agl_ctx->rend, v)

#define glColor4ui(red, green, blue, alpha) \
	(*agl_ctx->disp.color4ui)(agl_ctx->rend, red, green, blue, alpha)

#define glColor4uiv(v) \
	(*agl_ctx->disp.color4uiv)(agl_ctx->rend, v)

#define glColor4us(red, green, blue, alpha) \
	(*agl_ctx->disp.color4us)(agl_ctx->rend, red, green, blue, alpha)

#define glColor4usv(v) \
	(*agl_ctx->disp.color4usv)(agl_ctx->rend, v)

#define glColorMask(red, green, blue, alpha) \
	(*agl_ctx->disp.color_mask)(agl_ctx->rend, red, green, blue, alpha)

#define glColorMaterial(face, mode) \
	(*agl_ctx->disp.color_material)(agl_ctx->rend, face, mode)

#define glColorPointer(size, type, stride, pointer) \
	(*agl_ctx->disp.color_pointer)(agl_ctx->rend, size, type, stride, pointer)

#define glCopyPixels(x, y, width, height, type) \
	(*agl_ctx->disp.copy_pixels)(agl_ctx->rend, x, y, width, height, type)

#define glCopyTexImage1D(target, level, internalFormat, x, y, width, border) \
	(*agl_ctx->disp.copy_tex_image1D)(agl_ctx->rend, target, level, internalFormat, x, y, width, border)

#define glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border) \
	(*agl_ctx->disp.copy_tex_image2D)(agl_ctx->rend, target, level, internalFormat, x, y, width, height, border)

#define glCopyTexSubImage1D(target, level, xoffset, x, y, width) \
	(*agl_ctx->disp.copy_tex_sub_image1D)(agl_ctx->rend, target, level, xoffset, x, y, width)

#define glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) \
	(*agl_ctx->disp.copy_tex_sub_image2D)(agl_ctx->rend, target, level, xoffset, yoffset, x, y, width, height)

#define glCullFace(mode) \
	(*agl_ctx->disp.cull_face)(agl_ctx->rend, mode)

#define glDeleteLists(list, range) \
	(*agl_ctx->disp.delete_lists)(agl_ctx->rend, list, range)

#define glDeleteTextures(n, textures) \
	(*agl_ctx->disp.delete_textures)(agl_ctx->rend, n, textures)

#define glDepthFunc(func) \
	(*agl_ctx->disp.depth_func)(agl_ctx->rend, func)

#define glDepthMask(flag) \
	(*agl_ctx->disp.depth_mask)(agl_ctx->rend, flag)

#define glDepthRange(zNear, zFar) \
	(*agl_ctx->disp.depth_range)(agl_ctx->rend, zNear, zFar)

#define glDisable(cap) \
	(*agl_ctx->disp.disable)(agl_ctx->rend, cap)

#define glDisableClientState(array) \
	(*agl_ctx->disp.disable_client_state)(agl_ctx->rend, array)

#define glDrawArrays(mode, first, count) \
	(*agl_ctx->disp.draw_arrays)(agl_ctx->rend, mode, first, count)

#define glDrawBuffer(mode) \
	(*agl_ctx->disp.draw_buffer)(agl_ctx->rend, mode)

#define glDrawElements(mode, count, type, indices) \
	(*agl_ctx->disp.draw_elements)(agl_ctx->rend, mode, count, type, indices)

#define glDrawPixels(width, height, format, type, pixels) \
	(*agl_ctx->disp.draw_pixels)(agl_ctx->rend, width, height, format, type, pixels)

#define glEdgeFlag(flag) \
	(*agl_ctx->disp.edge_flag)(agl_ctx->rend, flag)

#define glEdgeFlagPointer(stride, pointer) \
	(*agl_ctx->disp.edge_flag_pointer)(agl_ctx->rend, stride, pointer)

#define glEdgeFlagv(flag) \
	(*agl_ctx->disp.edge_flagv)(agl_ctx->rend, flag)

#define glEnable(cap) \
	(*agl_ctx->disp.enable)(agl_ctx->rend, cap)

#define glEnableClientState(array) \
	(*agl_ctx->disp.enable_client_state)(agl_ctx->rend, array)

#define glEnd() \
	(*agl_ctx->disp.end)(agl_ctx->rend)

#define glEndList() \
	(*agl_ctx->disp.end_list)(agl_ctx->rend)

#define glEvalCoord1d(u) \
	(*agl_ctx->disp.eval_coord1d)(agl_ctx->rend, u)

#define glEvalCoord1dv(u) \
	(*agl_ctx->disp.eval_coord1dv)(agl_ctx->rend, u)

#define glEvalCoord1f(u) \
	(*agl_ctx->disp.eval_coord1f)(agl_ctx->rend, u)

#define glEvalCoord1fv(u) \
	(*agl_ctx->disp.eval_coord1fv)(agl_ctx->rend, u)

#define glEvalCoord2d(u, v) \
	(*agl_ctx->disp.eval_coord2d)(agl_ctx->rend, u, v)

#define glEvalCoord2dv(u) \
	(*agl_ctx->disp.eval_coord2dv)(agl_ctx->rend, u)

#define glEvalCoord2f(u, v) \
	(*agl_ctx->disp.eval_coord2f)(agl_ctx->rend, u, v)

#define glEvalCoord2fv(u) \
	(*agl_ctx->disp.eval_coord2fv)(agl_ctx->rend, u)

#define glEvalMesh1(mode, i1, i2) \
	(*agl_ctx->disp.eval_mesh1)(agl_ctx->rend, mode, i1, i2)

#define glEvalMesh2(mode, i1, i2, j1, j2) \
	(*agl_ctx->disp.eval_mesh2)(agl_ctx->rend, mode, i1, i2, j1, j2)

#define glEvalPoint1(i) \
	(*agl_ctx->disp.eval_point1)(agl_ctx->rend, i)

#define glEvalPoint2(i, j) \
	(*agl_ctx->disp.eval_point2)(agl_ctx->rend, i, j)

#define glFeedbackBuffer(size, type, buffer) \
	(*agl_ctx->disp.feedback_buffer)(agl_ctx->rend, size, type, buffer)

#define glFinish() \
	(*agl_ctx->disp.finish)(agl_ctx->rend)

#define glFlush() \
	(*agl_ctx->disp.flush)(agl_ctx->rend)

#define glFogf(pname, param) \
	(*agl_ctx->disp.fogf)(agl_ctx->rend, pname, param)

#define glFogfv(pname, params) \
	(*agl_ctx->disp.fogfv)(agl_ctx->rend, pname, params)

#define glFogi(pname, param) \
	(*agl_ctx->disp.fogi)(agl_ctx->rend, pname, param)

#define glFogiv(pname, params) \
	(*agl_ctx->disp.fogiv)(agl_ctx->rend, pname, params)

#define glFrontFace(mode) \
	(*agl_ctx->disp.front_face)(agl_ctx->rend, mode)

#define glFrustum(left, right, bottom, top, zNear, zFar) \
	(*agl_ctx->disp.frustum)(agl_ctx->rend, left, right, bottom, top, zNear, zFar)

#define glGenLists(range) \
	(*agl_ctx->disp.gen_lists)(agl_ctx->rend, range)

#define glGenTextures(n, textures) \
	(*agl_ctx->disp.gen_textures)(agl_ctx->rend, n, textures)

#define glGetBooleanv(pname, params) \
	(*agl_ctx->disp.get_booleanv)(agl_ctx->rend, pname, params)

#define glGetClipPlane(plane, equation) \
	(*agl_ctx->disp.get_clip_plane)(agl_ctx->rend, plane, equation)

#define glGetDoublev(pname, params) \
	(*agl_ctx->disp.get_doublev)(agl_ctx->rend, pname, params)

#define glGetError() \
	(*agl_ctx->disp.get_error)(agl_ctx->rend)

#define glGetFloatv(pname, params) \
	(*agl_ctx->disp.get_floatv)(agl_ctx->rend, pname, params)

#define glGetIntegerv(pname, params) \
	(*agl_ctx->disp.get_integerv)(agl_ctx->rend, pname, params)

#define glGetLightfv(light, pname, params) \
	(*agl_ctx->disp.get_lightfv)(agl_ctx->rend, light, pname, params)

#define glGetLightiv(light, pname, params) \
	(*agl_ctx->disp.get_lightiv)(agl_ctx->rend, light, pname, params)

#define glGetMapdv(target, query, v) \
	(*agl_ctx->disp.get_mapdv)(agl_ctx->rend, target, query, v)

#define glGetMapfv(target, query, v) \
	(*agl_ctx->disp.get_mapfv)(agl_ctx->rend, target, query, v)

#define glGetMapiv(target, query, v) \
	(*agl_ctx->disp.get_mapiv)(agl_ctx->rend, target, query, v)

#define glGetMaterialfv(face, pname, params) \
	(*agl_ctx->disp.get_materialfv)(agl_ctx->rend, face, pname, params)

#define glGetMaterialiv(face, pname, params) \
	(*agl_ctx->disp.get_materialiv)(agl_ctx->rend, face, pname, params)

#define glGetPixelMapfv(map, values) \
	(*agl_ctx->disp.get_pixel_mapfv)(agl_ctx->rend, map, values)

#define glGetPixelMapuiv(map, values) \
	(*agl_ctx->disp.get_pixel_mapuiv)(agl_ctx->rend, map, values)

#define glGetPixelMapusv(map, values) \
	(*agl_ctx->disp.get_pixel_mapusv)(agl_ctx->rend, map, values)

#define glGetPointerv(pname, params) \
	(*agl_ctx->disp.get_pointerv)(agl_ctx->rend, pname, params)

#define glGetPolygonStipple(mask) \
	(*agl_ctx->disp.get_polygon_stipple)(agl_ctx->rend, mask)

#define glGetString(name) \
	(*agl_ctx->disp.get_string)(agl_ctx->rend, name)

#define glGetTexEnvfv(target, pname, params) \
	(*agl_ctx->disp.get_tex_envfv)(agl_ctx->rend, target, pname, params)

#define glGetTexEnviv(target, pname, params) \
	(*agl_ctx->disp.get_tex_enviv)(agl_ctx->rend, target, pname, params)

#define glGetTexGendv(coord, pname, params) \
	(*agl_ctx->disp.get_tex_gendv)(agl_ctx->rend, coord, pname, params)

#define glGetTexGenfv(coord, pname, params) \
	(*agl_ctx->disp.get_tex_genfv)(agl_ctx->rend, coord, pname, params)

#define glGetTexGeniv(coord, pname, params) \
	(*agl_ctx->disp.get_tex_geniv)(agl_ctx->rend, coord, pname, params)

#define glGetTexImage(target, level, format, type, pixels) \
	(*agl_ctx->disp.get_tex_image)(agl_ctx->rend, target, level, format, type, pixels)

#define glGetTexLevelParameterfv(target, level, pname, params) \
	(*agl_ctx->disp.get_tex_level_parameterfv)(agl_ctx->rend, target, level, pname, params)

#define glGetTexLevelParameteriv(target, level, pname, params) \
	(*agl_ctx->disp.get_tex_level_parameteriv)(agl_ctx->rend, target, level, pname, params)

#define glGetTexParameterfv(target, pname, params) \
	(*agl_ctx->disp.get_tex_parameterfv)(agl_ctx->rend, target, pname, params)

#define glGetTexParameteriv(target, pname, params) \
	(*agl_ctx->disp.get_tex_parameteriv)(agl_ctx->rend, target, pname, params)

#define glHint(target, mode) \
	(*agl_ctx->disp.hint)(agl_ctx->rend, target, mode)

#define glIndexMask(mask) \
	(*agl_ctx->disp.index_mask)(agl_ctx->rend, mask)

#define glIndexPointer(type, stride, pointer) \
	(*agl_ctx->disp.index_pointer)(agl_ctx->rend, type, stride, pointer)

#define glIndexd(c) \
	(*agl_ctx->disp.indexd)(agl_ctx->rend, c)

#define glIndexdv(c) \
	(*agl_ctx->disp.indexdv)(agl_ctx->rend, c)

#define glIndexf(c) \
	(*agl_ctx->disp.indexf)(agl_ctx->rend, c)

#define glIndexfv(c) \
	(*agl_ctx->disp.indexfv)(agl_ctx->rend, c)

#define glIndexi(c) \
	(*agl_ctx->disp.indexi)(agl_ctx->rend, c)

#define glIndexiv(c) \
	(*agl_ctx->disp.indexiv)(agl_ctx->rend, c)

#define glIndexs(c) \
	(*agl_ctx->disp.indexs)(agl_ctx->rend, c)

#define glIndexsv(c) \
	(*agl_ctx->disp.indexsv)(agl_ctx->rend, c)

#define glIndexub(c) \
	(*agl_ctx->disp.indexub)(agl_ctx->rend, c)

#define glIndexubv(c) \
	(*agl_ctx->disp.indexubv)(agl_ctx->rend, c)

#define glInitNames() \
	(*agl_ctx->disp.init_names)(agl_ctx->rend)

#define glInterleavedArrays(format, stride, pointer) \
	(*agl_ctx->disp.interleaved_arrays)(agl_ctx->rend, format, stride, pointer)

#define glIsEnabled(cap) \
	(*agl_ctx->disp.is_enabled)(agl_ctx->rend, cap)

#define glIsList(list) \
	(*agl_ctx->disp.is_list)(agl_ctx->rend, list)

#define glIsTexture(texture) \
	(*agl_ctx->disp.is_texture)(agl_ctx->rend, texture)

#define glLightModelf(pname, param) \
	(*agl_ctx->disp.light_modelf)(agl_ctx->rend, pname, param)

#define glLightModelfv(pname, params) \
	(*agl_ctx->disp.light_modelfv)(agl_ctx->rend, pname, params)

#define glLightModeli(pname, param) \
	(*agl_ctx->disp.light_modeli)(agl_ctx->rend, pname, param)

#define glLightModeliv(pname, params) \
	(*agl_ctx->disp.light_modeliv)(agl_ctx->rend, pname, params)

#define glLightf(light, pname, param) \
	(*agl_ctx->disp.lightf)(agl_ctx->rend, light, pname, param)

#define glLightfv(light, pname, params) \
	(*agl_ctx->disp.lightfv)(agl_ctx->rend, light, pname, params)

#define glLighti(light, pname, param) \
	(*agl_ctx->disp.lighti)(agl_ctx->rend, light, pname, param)

#define glLightiv(light, pname, params) \
	(*agl_ctx->disp.lightiv)(agl_ctx->rend, light, pname, params)

#define glLineStipple(factor, pattern) \
	(*agl_ctx->disp.line_stipple)(agl_ctx->rend, factor, pattern)

#define glLineWidth(width) \
	(*agl_ctx->disp.line_width)(agl_ctx->rend, width)

#define glListBase(base) \
	(*agl_ctx->disp.list_base)(agl_ctx->rend, base)

#define glLoadIdentity() \
	(*agl_ctx->disp.load_identity)(agl_ctx->rend)

#define glLoadMatrixd(m) \
	(*agl_ctx->disp.load_matrixd)(agl_ctx->rend, m)

#define glLoadMatrixf(m) \
	(*agl_ctx->disp.load_matrixf)(agl_ctx->rend, m)

#define glLoadName(name) \
	(*agl_ctx->disp.load_name)(agl_ctx->rend, name)

#define glLogicOp(opcode) \
	(*agl_ctx->disp.logic_op)(agl_ctx->rend, opcode)

#define glMap1d(target, u1, u2, stride, order, points) \
	(*agl_ctx->disp.map1d)(agl_ctx->rend, target, u1, u2, stride, order, points)

#define glMap1f(target, u1, u2, stride, order, points) \
	(*agl_ctx->disp.map1f)(agl_ctx->rend, target, u1, u2, stride, order, points)

#define glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*agl_ctx->disp.map2d)(agl_ctx->rend, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*agl_ctx->disp.map2f)(agl_ctx->rend, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMapGrid1d(un, u1, u2) \
	(*agl_ctx->disp.map_grid1d)(agl_ctx->rend, un, u1, u2)

#define glMapGrid1f(un, u1, u2) \
	(*agl_ctx->disp.map_grid1f)(agl_ctx->rend, un, u1, u2)

#define glMapGrid2d(un, u1, u2, vn, v1, v2) \
	(*agl_ctx->disp.map_grid2d)(agl_ctx->rend, un, u1, u2, vn, v1, v2)

#define glMapGrid2f(un, u1, u2, vn, v1, v2) \
	(*agl_ctx->disp.map_grid2f)(agl_ctx->rend, un, u1, u2, vn, v1, v2)

#define glMaterialf(face, pname, param) \
	(*agl_ctx->disp.materialf)(agl_ctx->rend, face, pname, param)

#define glMaterialfv(face, pname, params) \
	(*agl_ctx->disp.materialfv)(agl_ctx->rend, face, pname, params)

#define glMateriali(face, pname, param) \
	(*agl_ctx->disp.materiali)(agl_ctx->rend, face, pname, param)

#define glMaterialiv(face, pname, params) \
	(*agl_ctx->disp.materialiv)(agl_ctx->rend, face, pname, params)

#define glMatrixMode(mode) \
	(*agl_ctx->disp.matrix_mode)(agl_ctx->rend, mode)

#define glMultMatrixd(m) \
	(*agl_ctx->disp.mult_matrixd)(agl_ctx->rend, m)

#define glMultMatrixf(m) \
	(*agl_ctx->disp.mult_matrixf)(agl_ctx->rend, m)

#define glNewList(list, mode) \
	(*agl_ctx->disp.new_list)(agl_ctx->rend, list, mode)

#define glNormal3b(nx, ny, nz) \
	(*agl_ctx->disp.normal3b)(agl_ctx->rend, nx, ny, nz)

#define glNormal3bv(v) \
	(*agl_ctx->disp.normal3bv)(agl_ctx->rend, v)

#define glNormal3d(nx, ny, nz) \
	(*agl_ctx->disp.normal3d)(agl_ctx->rend, nx, ny, nz)

#define glNormal3dv(v) \
	(*agl_ctx->disp.normal3dv)(agl_ctx->rend, v)

#define glNormal3f(nx, ny, nz) \
	(*agl_ctx->disp.normal3f)(agl_ctx->rend, nx, ny, nz)

#define glNormal3fv(v) \
	(*agl_ctx->disp.normal3fv)(agl_ctx->rend, v)

#define glNormal3i(nx, ny, nz) \
	(*agl_ctx->disp.normal3i)(agl_ctx->rend, nx, ny, nz)

#define glNormal3iv(v) \
	(*agl_ctx->disp.normal3iv)(agl_ctx->rend, v)

#define glNormal3s(nx, ny, nz) \
	(*agl_ctx->disp.normal3s)(agl_ctx->rend, nx, ny, nz)

#define glNormal3sv(v) \
	(*agl_ctx->disp.normal3sv)(agl_ctx->rend, v)

#define glNormalPointer(type, stride, pointer) \
	(*agl_ctx->disp.normal_pointer)(agl_ctx->rend, type, stride, pointer)

#define glOrtho(left, right, bottom, top, zNear, zFar) \
	(*agl_ctx->disp.ortho)(agl_ctx->rend, left, right, bottom, top, zNear, zFar)

#define glPassThrough(token) \
	(*agl_ctx->disp.pass_through)(agl_ctx->rend, token)

#define glPixelMapfv(map, mapsize, values) \
	(*agl_ctx->disp.pixel_mapfv)(agl_ctx->rend, map, mapsize, values)

#define glPixelMapuiv(map, mapsize, values) \
	(*agl_ctx->disp.pixel_mapuiv)(agl_ctx->rend, map, mapsize, values)

#define glPixelMapusv(map, mapsize, values) \
	(*agl_ctx->disp.pixel_mapusv)(agl_ctx->rend, map, mapsize, values)

#define glPixelStoref(pname, param) \
	(*agl_ctx->disp.pixel_storef)(agl_ctx->rend, pname, param)

#define glPixelStorei(pname, param) \
	(*agl_ctx->disp.pixel_storei)(agl_ctx->rend, pname, param)

#define glPixelTransferf(pname, param) \
	(*agl_ctx->disp.pixel_transferf)(agl_ctx->rend, pname, param)

#define glPixelTransferi(pname, param) \
	(*agl_ctx->disp.pixel_transferi)(agl_ctx->rend, pname, param)

#define glPixelZoom(xfactor, yfactor) \
	(*agl_ctx->disp.pixel_zoom)(agl_ctx->rend, xfactor, yfactor)

#define glPointSize(size) \
	(*agl_ctx->disp.point_size)(agl_ctx->rend, size)

#define glPolygonMode(face, mode) \
	(*agl_ctx->disp.polygon_mode)(agl_ctx->rend, face, mode)

#define glPolygonOffset(factor, units) \
	(*agl_ctx->disp.polygon_offset)(agl_ctx->rend, factor, units)

#define glPolygonStipple(mask) \
	(*agl_ctx->disp.polygon_stipple)(agl_ctx->rend, mask)

#define glPopAttrib() \
	(*agl_ctx->disp.pop_attrib)(agl_ctx->rend)

#define glPopClientAttrib() \
	(*agl_ctx->disp.pop_client_attrib)(agl_ctx->rend)

#define glPopMatrix() \
	(*agl_ctx->disp.pop_matrix)(agl_ctx->rend)

#define glPopName() \
	(*agl_ctx->disp.pop_name)(agl_ctx->rend)

#define glPrioritizeTextures(n, textures, priorities) \
	(*agl_ctx->disp.prioritize_textures)(agl_ctx->rend, n, textures, priorities)

#define glPushAttrib(mask) \
	(*agl_ctx->disp.push_attrib)(agl_ctx->rend, mask)

#define glPushClientAttrib(mask) \
	(*agl_ctx->disp.push_client_attrib)(agl_ctx->rend, mask)

#define glPushMatrix() \
	(*agl_ctx->disp.push_matrix)(agl_ctx->rend)

#define glPushName(name) \
	(*agl_ctx->disp.push_name)(agl_ctx->rend, name)

#define glRasterPos2d(x, y) \
	(*agl_ctx->disp.raster_pos2d)(agl_ctx->rend, x, y)

#define glRasterPos2dv(v) \
	(*agl_ctx->disp.raster_pos2dv)(agl_ctx->rend, v)

#define glRasterPos2f(x, y) \
	(*agl_ctx->disp.raster_pos2f)(agl_ctx->rend, x, y)

#define glRasterPos2fv(v) \
	(*agl_ctx->disp.raster_pos2fv)(agl_ctx->rend, v)

#define glRasterPos2i(x, y) \
	(*agl_ctx->disp.raster_pos2i)(agl_ctx->rend, x, y)

#define glRasterPos2iv(v) \
	(*agl_ctx->disp.raster_pos2iv)(agl_ctx->rend, v)

#define glRasterPos2s(x, y) \
	(*agl_ctx->disp.raster_pos2s)(agl_ctx->rend, x, y)

#define glRasterPos2sv(v) \
	(*agl_ctx->disp.raster_pos2sv)(agl_ctx->rend, v)

#define glRasterPos3d(x, y, z) \
	(*agl_ctx->disp.raster_pos3d)(agl_ctx->rend, x, y, z)

#define glRasterPos3dv(v) \
	(*agl_ctx->disp.raster_pos3dv)(agl_ctx->rend, v)

#define glRasterPos3f(x, y, z) \
	(*agl_ctx->disp.raster_pos3f)(agl_ctx->rend, x, y, z)

#define glRasterPos3fv(v) \
	(*agl_ctx->disp.raster_pos3fv)(agl_ctx->rend, v)

#define glRasterPos3i(x, y, z) \
	(*agl_ctx->disp.raster_pos3i)(agl_ctx->rend, x, y, z)

#define glRasterPos3iv(v) \
	(*agl_ctx->disp.raster_pos3iv)(agl_ctx->rend, v)

#define glRasterPos3s(x, y, z) \
	(*agl_ctx->disp.raster_pos3s)(agl_ctx->rend, x, y, z)

#define glRasterPos3sv(v) \
	(*agl_ctx->disp.raster_pos3sv)(agl_ctx->rend, v)

#define glRasterPos4d(x, y, z, w) \
	(*agl_ctx->disp.raster_pos4d)(agl_ctx->rend, x, y, z, w)

#define glRasterPos4dv(v) \
	(*agl_ctx->disp.raster_pos4dv)(agl_ctx->rend, v)

#define glRasterPos4f(x, y, z, w) \
	(*agl_ctx->disp.raster_pos4f)(agl_ctx->rend, x, y, z, w)

#define glRasterPos4fv(v) \
	(*agl_ctx->disp.raster_pos4fv)(agl_ctx->rend, v)

#define glRasterPos4i(x, y, z, w) \
	(*agl_ctx->disp.raster_pos4i)(agl_ctx->rend, x, y, z, w)

#define glRasterPos4iv(v) \
	(*agl_ctx->disp.raster_pos4iv)(agl_ctx->rend, v)

#define glRasterPos4s(x, y, z, w) \
	(*agl_ctx->disp.raster_pos4s)(agl_ctx->rend, x, y, z, w)

#define glRasterPos4sv(v) \
	(*agl_ctx->disp.raster_pos4sv)(agl_ctx->rend, v)

#define glReadBuffer(mode) \
	(*agl_ctx->disp.read_buffer)(agl_ctx->rend, mode)

#define glReadPixels(x, y, width, height, format, type, pixels) \
	(*agl_ctx->disp.read_pixels)(agl_ctx->rend, x, y, width, height, format, type, pixels)

#define glRectd(x1, y1, x2, y2) \
	(*agl_ctx->disp.rectd)(agl_ctx->rend, x1, y1, x2, y2)

#define glRectdv(v1, v2) \
	(*agl_ctx->disp.rectdv)(agl_ctx->rend, v1, v2)

#define glRectf(x1, y1, x2, y2) \
	(*agl_ctx->disp.rectf)(agl_ctx->rend, x1, y1, x2, y2)

#define glRectfv(v1, v2) \
	(*agl_ctx->disp.rectfv)(agl_ctx->rend, v1, v2)

#define glRecti(x1, y1, x2, y2) \
	(*agl_ctx->disp.recti)(agl_ctx->rend, x1, y1, x2, y2)

#define glRectiv(v1, v2) \
	(*agl_ctx->disp.rectiv)(agl_ctx->rend, v1, v2)

#define glRects(x1, y1, x2, y2) \
	(*agl_ctx->disp.rects)(agl_ctx->rend, x1, y1, x2, y2)

#define glRectsv(v1, v2) \
	(*agl_ctx->disp.rectsv)(agl_ctx->rend, v1, v2)

#define glRenderMode(mode) \
	(*agl_ctx->disp.render_mode)(agl_ctx->rend, mode)

#define glRotated(angle, x, y, z) \
	(*agl_ctx->disp.rotated)(agl_ctx->rend, angle, x, y, z)

#define glRotatef(angle, x, y, z) \
	(*agl_ctx->disp.rotatef)(agl_ctx->rend, angle, x, y, z)

#define glScaled(x, y, z) \
	(*agl_ctx->disp.scaled)(agl_ctx->rend, x, y, z)

#define glScalef(x, y, z) \
	(*agl_ctx->disp.scalef)(agl_ctx->rend, x, y, z)

#define glScissor(x, y, width, height) \
	(*agl_ctx->disp.scissor)(agl_ctx->rend, x, y, width, height)

#define glSelectBuffer(size, buffer) \
	(*agl_ctx->disp.select_buffer)(agl_ctx->rend, size, buffer)

#define glShadeModel(mode) \
	(*agl_ctx->disp.shade_model)(agl_ctx->rend, mode)

#define glStencilFunc(func, ref, mask) \
	(*agl_ctx->disp.stencil_func)(agl_ctx->rend, func, ref, mask)

#define glStencilMask(mask) \
	(*agl_ctx->disp.stencil_mask)(agl_ctx->rend, mask)

#define glStencilOp(fail, zfail, zpass) \
	(*agl_ctx->disp.stencil_op)(agl_ctx->rend, fail, zfail, zpass)

#define glTexCoord1d(s) \
	(*agl_ctx->disp.tex_coord1d)(agl_ctx->rend, s)

#define glTexCoord1dv(v) \
	(*agl_ctx->disp.tex_coord1dv)(agl_ctx->rend, v)

#define glTexCoord1f(s) \
	(*agl_ctx->disp.tex_coord1f)(agl_ctx->rend, s)

#define glTexCoord1fv(v) \
	(*agl_ctx->disp.tex_coord1fv)(agl_ctx->rend, v)

#define glTexCoord1i(s) \
	(*agl_ctx->disp.tex_coord1i)(agl_ctx->rend, s)

#define glTexCoord1iv(v) \
	(*agl_ctx->disp.tex_coord1iv)(agl_ctx->rend, v)

#define glTexCoord1s(s) \
	(*agl_ctx->disp.tex_coord1s)(agl_ctx->rend, s)

#define glTexCoord1sv(v) \
	(*agl_ctx->disp.tex_coord1sv)(agl_ctx->rend, v)

#define glTexCoord2d(s, t) \
	(*agl_ctx->disp.tex_coord2d)(agl_ctx->rend, s, t)

#define glTexCoord2dv(v) \
	(*agl_ctx->disp.tex_coord2dv)(agl_ctx->rend, v)

#define glTexCoord2f(s, t) \
	(*agl_ctx->disp.tex_coord2f)(agl_ctx->rend, s, t)

#define glTexCoord2fv(v) \
	(*agl_ctx->disp.tex_coord2fv)(agl_ctx->rend, v)

#define glTexCoord2i(s, t) \
	(*agl_ctx->disp.tex_coord2i)(agl_ctx->rend, s, t)

#define glTexCoord2iv(v) \
	(*agl_ctx->disp.tex_coord2iv)(agl_ctx->rend, v)

#define glTexCoord2s(s, t) \
	(*agl_ctx->disp.tex_coord2s)(agl_ctx->rend, s, t)

#define glTexCoord2sv(v) \
	(*agl_ctx->disp.tex_coord2sv)(agl_ctx->rend, v)

#define glTexCoord3d(s, t, r) \
	(*agl_ctx->disp.tex_coord3d)(agl_ctx->rend, s, t, r)

#define glTexCoord3dv(v) \
	(*agl_ctx->disp.tex_coord3dv)(agl_ctx->rend, v)

#define glTexCoord3f(s, t, r) \
	(*agl_ctx->disp.tex_coord3f)(agl_ctx->rend, s, t, r)

#define glTexCoord3fv(v) \
	(*agl_ctx->disp.tex_coord3fv)(agl_ctx->rend, v)

#define glTexCoord3i(s, t, r) \
	(*agl_ctx->disp.tex_coord3i)(agl_ctx->rend, s, t, r)

#define glTexCoord3iv(v) \
	(*agl_ctx->disp.tex_coord3iv)(agl_ctx->rend, v)

#define glTexCoord3s(s, t, r) \
	(*agl_ctx->disp.tex_coord3s)(agl_ctx->rend, s, t, r)

#define glTexCoord3sv(v) \
	(*agl_ctx->disp.tex_coord3sv)(agl_ctx->rend, v)

#define glTexCoord4d(s, t, r, q) \
	(*agl_ctx->disp.tex_coord4d)(agl_ctx->rend, s, t, r, q)

#define glTexCoord4dv(v) \
	(*agl_ctx->disp.tex_coord4dv)(agl_ctx->rend, v)

#define glTexCoord4f(s, t, r, q) \
	(*agl_ctx->disp.tex_coord4f)(agl_ctx->rend, s, t, r, q)

#define glTexCoord4fv(v) \
	(*agl_ctx->disp.tex_coord4fv)(agl_ctx->rend, v)

#define glTexCoord4i(s, t, r, q) \
	(*agl_ctx->disp.tex_coord4i)(agl_ctx->rend, s, t, r, q)

#define glTexCoord4iv(v) \
	(*agl_ctx->disp.tex_coord4iv)(agl_ctx->rend, v)

#define glTexCoord4s(s, t, r, q) \
	(*agl_ctx->disp.tex_coord4s)(agl_ctx->rend, s, t, r, q)

#define glTexCoord4sv(v) \
	(*agl_ctx->disp.tex_coord4sv)(agl_ctx->rend, v)

#define glTexCoordPointer(size, type, stride, pointer) \
	(*agl_ctx->disp.tex_coord_pointer)(agl_ctx->rend, size, type, stride, pointer)

#define glTexEnvf(target, pname, param) \
	(*agl_ctx->disp.tex_envf)(agl_ctx->rend, target, pname, param)

#define glTexEnvfv(target, pname, params) \
	(*agl_ctx->disp.tex_envfv)(agl_ctx->rend, target, pname, params)

#define glTexEnvi(target, pname, param) \
	(*agl_ctx->disp.tex_envi)(agl_ctx->rend, target, pname, param)

#define glTexEnviv(target, pname, params) \
	(*agl_ctx->disp.tex_enviv)(agl_ctx->rend, target, pname, params)

#define glTexGend(coord, pname, param) \
	(*agl_ctx->disp.tex_gend)(agl_ctx->rend, coord, pname, param)

#define glTexGendv(coord, pname, params) \
	(*agl_ctx->disp.tex_gendv)(agl_ctx->rend, coord, pname, params)

#define glTexGenf(coord, pname, param) \
	(*agl_ctx->disp.tex_genf)(agl_ctx->rend, coord, pname, param)

#define glTexGenfv(coord, pname, params) \
	(*agl_ctx->disp.tex_genfv)(agl_ctx->rend, coord, pname, params)

#define glTexGeni(coord, pname, param) \
	(*agl_ctx->disp.tex_geni)(agl_ctx->rend, coord, pname, param)

#define glTexGeniv(coord, pname, params) \
	(*agl_ctx->disp.tex_geniv)(agl_ctx->rend, coord, pname, params)

#define glTexImage1D(target, level, internalformat, width, border, format, type, pixels) \
	(*agl_ctx->disp.tex_image1D)(agl_ctx->rend, target, level, internalformat, width, border, format, type, pixels)

#define glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels) \
	(*agl_ctx->disp.tex_image2D)(agl_ctx->rend, target, level, internalformat, width, height, border, format, type, pixels)

#define glTexParameterf(target, pname, param) \
	(*agl_ctx->disp.tex_parameterf)(agl_ctx->rend, target, pname, param)

#define glTexParameterfv(target, pname, params) \
	(*agl_ctx->disp.tex_parameterfv)(agl_ctx->rend, target, pname, params)

#define glTexParameteri(target, pname, param) \
	(*agl_ctx->disp.tex_parameteri)(agl_ctx->rend, target, pname, param)

#define glTexParameteriv(target, pname, params) \
	(*agl_ctx->disp.tex_parameteriv)(agl_ctx->rend, target, pname, params)

#define glTexSubImage1D(target, level, xoffset, width, format, type, pixels) \
	(*agl_ctx->disp.tex_sub_image1D)(agl_ctx->rend, target, level, xoffset, width, format, type, pixels)

#define glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels) \
	(*agl_ctx->disp.tex_sub_image2D)(agl_ctx->rend, target, level, xoffset, yoffset, width, height, format, type, pixels)

#define glTranslated(x, y, z) \
	(*agl_ctx->disp.translated)(agl_ctx->rend, x, y, z)

#define glTranslatef(x, y, z) \
	(*agl_ctx->disp.translatef)(agl_ctx->rend, x, y, z)

#define glVertex2d(x, y) \
	(*agl_ctx->disp.vertex2d)(agl_ctx->rend, x, y)

#define glVertex2dv(v) \
	(*agl_ctx->disp.vertex2dv)(agl_ctx->rend, v)

#define glVertex2f(x, y) \
	(*agl_ctx->disp.vertex2f)(agl_ctx->rend, x, y)

#define glVertex2fv(v) \
	(*agl_ctx->disp.vertex2fv)(agl_ctx->rend, v)

#define glVertex2i(x, y) \
	(*agl_ctx->disp.vertex2i)(agl_ctx->rend, x, y)

#define glVertex2iv(v) \
	(*agl_ctx->disp.vertex2iv)(agl_ctx->rend, v)

#define glVertex2s(x, y) \
	(*agl_ctx->disp.vertex2s)(agl_ctx->rend, x, y)

#define glVertex2sv(v) \
	(*agl_ctx->disp.vertex2sv)(agl_ctx->rend, v)

#define glVertex3d(x, y, z) \
	(*agl_ctx->disp.vertex3d)(agl_ctx->rend, x, y, z)

#define glVertex3dv(v) \
	(*agl_ctx->disp.vertex3dv)(agl_ctx->rend, v)

#define glVertex3f(x, y, z) \
	(*agl_ctx->disp.vertex3f)(agl_ctx->rend, x, y, z)

#define glVertex3fv(v) \
	(*agl_ctx->disp.vertex3fv)(agl_ctx->rend, v)

#define glVertex3i(x, y, z) \
	(*agl_ctx->disp.vertex3i)(agl_ctx->rend, x, y, z)

#define glVertex3iv(v) \
	(*agl_ctx->disp.vertex3iv)(agl_ctx->rend, v)

#define glVertex3s(x, y, z) \
	(*agl_ctx->disp.vertex3s)(agl_ctx->rend, x, y, z)

#define glVertex3sv(v) \
	(*agl_ctx->disp.vertex3sv)(agl_ctx->rend, v)

#define glVertex4d(x, y, z, w) \
	(*agl_ctx->disp.vertex4d)(agl_ctx->rend, x, y, z, w)

#define glVertex4dv(v) \
	(*agl_ctx->disp.vertex4dv)(agl_ctx->rend, v)

#define glVertex4f(x, y, z, w) \
	(*agl_ctx->disp.vertex4f)(agl_ctx->rend, x, y, z, w)

#define glVertex4fv(v) \
	(*agl_ctx->disp.vertex4fv)(agl_ctx->rend, v)

#define glVertex4i(x, y, z, w) \
	(*agl_ctx->disp.vertex4i)(agl_ctx->rend, x, y, z, w)

#define glVertex4iv(v) \
	(*agl_ctx->disp.vertex4iv)(agl_ctx->rend, v)

#define glVertex4s(x, y, z, w) \
	(*agl_ctx->disp.vertex4s)(agl_ctx->rend, x, y, z, w)

#define glVertex4sv(v) \
	(*agl_ctx->disp.vertex4sv)(agl_ctx->rend, v)

#define glVertexPointer(size, type, stride, pointer) \
	(*agl_ctx->disp.vertex_pointer)(agl_ctx->rend, size, type, stride, pointer)

#define glViewport(x, y, width, height) \
	(*agl_ctx->disp.viewport)(agl_ctx->rend, x, y, width, height)

/****************** OpenGL 1.2 ************************************/

#define glBlendColor(red, green, blue, alpha) \
	(*agl_ctx->disp.blend_color)(agl_ctx->rend, red, green, blue, alpha)

#define glBlendEquation(mode) \
	(*agl_ctx->disp.blend_equation)(agl_ctx->rend, mode)

#define glDrawRangeElements(mode, start, end, count, type, indices) \
	(*agl_ctx->disp.draw_range_elements)(agl_ctx->rend, mode, start, end, count, type, indices)

#define glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, data) \
	(*agl_ctx->disp.tex_image3D)(agl_ctx->rend, target, level, internalformat, width, height, depth, border, format, type, data)

#define glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) \
	(*agl_ctx->disp.tex_sub_image3D)(agl_ctx->rend, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels)

#define glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height) \
	(*agl_ctx->disp.copy_tex_sub_image3D)(agl_ctx->rend, target, level, xoffset, yoffset, zoffset, x, y, width, height)

/****************** OpenGL 1.2 Imaging Subset *********************/

#define glColorTable(target, internalformat, width, format, type, table) \
	(*agl_ctx->disp.color_table)(agl_ctx->rend, target, internalformat, width, format, type, table)

#define glColorTableParameterfv(target, pname, params) \
	(*agl_ctx->disp.color_table_parameterfv)(agl_ctx->rend, target, pname, params)

#define glColorTableParameteriv(target, pname, params) \
	(*agl_ctx->disp.color_table_parameteriv)(agl_ctx->rend, target, pname, params)

#define glCopyColorTable(target, internalformat, x, y, width) \
	(*agl_ctx->disp.copy_color_table)(agl_ctx->rend, target, internalformat, x, y, width)

#define glGetColorTable(target, format, type, table) \
	(*agl_ctx->disp.get_color_table)(agl_ctx->rend, target, format, type, table)

#define glGetColorTableParameterfv(target, pname, params) \
	(*agl_ctx->disp.get_color_table_parameterfv)(agl_ctx->rend, target, pname, params)

#define glGetColorTableParameteriv(target, pname, params) \
	(*agl_ctx->disp.get_color_table_parameteriv)(agl_ctx->rend, target, pname, params)

#define glColorSubTable(target, start, count, format, type, data) \
	(*agl_ctx->disp.color_sub_table)(agl_ctx->rend, target, start, count, format, type, data)

#define glCopyColorSubTable(target, start, x, y, width) \
	(*agl_ctx->disp.copy_color_sub_table)(agl_ctx->rend, target, start, x, y, width)

#define glConvolutionFilter1D(target, internalformat, width, format, type, image) \
	(*agl_ctx->disp.convolution_filter1D)(agl_ctx->rend, target, internalformat, width, format, type, image)

#define glConvolutionFilter2D(target, internalformat, width, height, format, type, image) \
	(*agl_ctx->disp.convolution_filter2D)(agl_ctx->rend, target, internalformat, width, height, format, type, image)

#define glConvolutionParameterf(target, pname, param) \
	(*agl_ctx->disp.convolution_parameterf)(agl_ctx->rend, target, pname, param)

#define glConvolutionParameterfv(target, pname, params) \
	(*agl_ctx->disp.convolution_parameterfv)(agl_ctx->rend, target, pname, params)

#define glConvolutionParameteri(target, pname, param) \
	(*agl_ctx->disp.convolution_parameteri)(agl_ctx->rend, target, pname, param)

#define glConvolutionParameteriv(target, pname, params) \
	(*agl_ctx->disp.convolution_parameteriv)(agl_ctx->rend, target, pname, params)

#define glCopyConvolutionFilter1D(target, internalformat, x, y, width) \
	(*agl_ctx->disp.copy_convolution_filter1D)(agl_ctx->rend, target, internalformat, x, y, width)

#define glCopyConvolutionFilter2D(target, internalformat, x, y, width, height) \
	(*agl_ctx->disp.copy_convolution_filter2D)(agl_ctx->rend, target, internalformat, x, y, width, height)

#define glGetConvolutionFilter(target, format, type, image) \
	(*agl_ctx->disp.get_convolution_filter)(agl_ctx->rend, target, format, type, image)

#define glGetConvolutionParameterfv(target, pname, params) \
	(*agl_ctx->disp.get_convolution_parameterfv)(agl_ctx->rend, target, pname, params)

#define glGetConvolutionParameteriv(target, pname, params) \
	(*agl_ctx->disp.get_convolution_parameteriv)(agl_ctx->rend, target, pname, params)

#define glGetSeparableFilter(target, format, type, row, column, span) \
	(*agl_ctx->disp.get_separable_filter)(agl_ctx->rend, target, format, type, row, column, span)

#define glSeparableFilter2D(target, internalformat, width, height, format, type, row, column) \
	(*agl_ctx->disp.separable_filter2D)(agl_ctx->rend, target, internalformat, width, height, format, type, row, column)

#define glGetHistogram(target, reset, format, type, values) \
	(*agl_ctx->disp.get_histogram)(agl_ctx->rend, target, reset, format, type, values)

#define glGetHistogramParameterfv(target, pname, params) \
	(*agl_ctx->disp.get_histogram_parameterfv)(agl_ctx->rend, target, pname, params)

#define glGetHistogramParameteriv(target, pname, params) \
	(*agl_ctx->disp.get_histogram_parameteriv)(agl_ctx->rend, target, pname, params)

#define glGetMinmax(target, reset, format, type, values) \
	(*agl_ctx->disp.get_minmax)(agl_ctx->rend, target, reset, format, type, values)

#define glGetMinmaxParameterfv(target, pname, params) \
	(*agl_ctx->disp.get_minmax_parameterfv)(agl_ctx->rend, target, pname, params)

#define glGetMinmaxParameteriv(target, pname, params) \
	(*agl_ctx->disp.get_minmax_parameteriv)(agl_ctx->rend, target, pname, params)

#define glHistogram(target, width, internalformat, sink) \
	(*agl_ctx->disp.histogram)(agl_ctx->rend, target, width, internalformat, sink)

#define glMinmax(target, internalformat, sink) \
	(*agl_ctx->disp.minmax)(agl_ctx->rend, target, internalformat, sink)

#define glResetHistogram(target) \
	(*agl_ctx->disp.reset_histogram)(agl_ctx->rend, target)

#define glResetMinmax(target) \
	(*agl_ctx->disp.reset_minmax)(agl_ctx->rend, target)

/****************** OpenGL 1.3 ************************************/

#define glClientActiveTexture(target) \
	(*agl_ctx->disp.client_active_texture)(agl_ctx->rend, target)

#define glActiveTexture(target) \
	(*agl_ctx->disp.active_texture)(agl_ctx->rend, target)

#define glMultiTexCoord1d(target, s) \
	(*agl_ctx->disp.multi_tex_coord1d)(agl_ctx->rend, target, s)

#define glMultiTexCoord1dv(target, v) \
	(*agl_ctx->disp.multi_tex_coord1dv)(agl_ctx->rend, target, v)

#define glMultiTexCoord1f(target, s) \
	(*agl_ctx->disp.multi_tex_coord1f)(agl_ctx->rend, target, s)

#define glMultiTexCoord1fv(target, v) \
	(*agl_ctx->disp.multi_tex_coord1fv)(agl_ctx->rend, target, v)

#define glMultiTexCoord1i(target, s) \
	(*agl_ctx->disp.multi_tex_coord1i)(agl_ctx->rend, target, s)

#define glMultiTexCoord1iv(target, v) \
	(*agl_ctx->disp.multi_tex_coord1iv)(agl_ctx->rend, target, v)

#define glMultiTexCoord1s(target, s) \
	(*agl_ctx->disp.multi_tex_coord1s)(agl_ctx->rend, target, s)

#define glMultiTexCoord1sv(target, v) \
	(*agl_ctx->disp.multi_tex_coord1sv)(agl_ctx->rend, target, v)

#define glMultiTexCoord2d(target, s, t) \
	(*agl_ctx->disp.multi_tex_coord2d)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2dv(target, v) \
	(*agl_ctx->disp.multi_tex_coord2dv)(agl_ctx->rend, target, v)

#define glMultiTexCoord2f(target, s, t) \
	(*agl_ctx->disp.multi_tex_coord2f)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2fv(target, v) \
	(*agl_ctx->disp.multi_tex_coord2fv)(agl_ctx->rend, target, v)

#define glMultiTexCoord2i(target, s, t) \
	(*agl_ctx->disp.multi_tex_coord2i)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2iv(target, v) \
	(*agl_ctx->disp.multi_tex_coord2iv)(agl_ctx->rend, target, v)

#define glMultiTexCoord2s(target, s, t) \
	(*agl_ctx->disp.multi_tex_coord2s)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2sv(target, v) \
	(*agl_ctx->disp.multi_tex_coord2sv)(agl_ctx->rend, target, v)

#define glMultiTexCoord3d(target, s, t, r) \
	(*agl_ctx->disp.multi_tex_coord3d)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3dv(target, v) \
	(*agl_ctx->disp.multi_tex_coord3dv)(agl_ctx->rend, target, v)

#define glMultiTexCoord3f(target, s, t, r) \
	(*agl_ctx->disp.multi_tex_coord3f)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3fv(target, v) \
	(*agl_ctx->disp.multi_tex_coord3fv)(agl_ctx->rend, target, v)

#define glMultiTexCoord3i(target, s, t, r) \
	(*agl_ctx->disp.multi_tex_coord3i)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3iv(target, v) \
	(*agl_ctx->disp.multi_tex_coord3iv)(agl_ctx->rend, target, v)

#define glMultiTexCoord3s(target, s, t, r) \
	(*agl_ctx->disp.multi_tex_coord3s)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3sv(target, v) \
	(*agl_ctx->disp.multi_tex_coord3sv)(agl_ctx->rend, target, v)

#define glMultiTexCoord4d(target, s, t, r, q) \
	(*agl_ctx->disp.multi_tex_coord4d)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4dv(target, v) \
	(*agl_ctx->disp.multi_tex_coord4dv)(agl_ctx->rend, target, v)

#define glMultiTexCoord4f(target, s, t, r, q) \
	(*agl_ctx->disp.multi_tex_coord4f)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4fv(target, v) \
	(*agl_ctx->disp.multi_tex_coord4fv)(agl_ctx->rend, target, v)

#define glMultiTexCoord4i(target, s, t, r, q) \
	(*agl_ctx->disp.multi_tex_coord4i)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4iv(target, v) \
	(*agl_ctx->disp.multi_tex_coord4iv)(agl_ctx->rend, target, v)

#define glMultiTexCoord4s(target, s, t, r, q) \
	(*agl_ctx->disp.multi_tex_coord4s)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4sv(target, v) \
	(*agl_ctx->disp.multi_tex_coord4sv)(agl_ctx->rend, target, v)

#define glSampleCoverage(v, i) \
	(*agl_ctx->disp.sample_coverage)(agl_ctx->rend, v, i)

#define glSamplePass(mode) \
	(*agl_ctx->disp.sample_pass)(agl_ctx->rend, mode)

#define glLoadTransposeMatrixf(v) \
	(*agl_ctx->disp.load_transpose_matrixf)(agl_ctx->rend, v)

#define glLoadTransposeMatrixd(v) \
	(*agl_ctx->disp.load_transpose_matrixd)(agl_ctx->rend, v)

#define glMultTransposeMatrixf(v) \
	(*agl_ctx->disp.mult_transpose_matrixf)(agl_ctx->rend, v)

#define glMultTransposeMatrixd(v) \
	(*agl_ctx->disp.mult_transpose_matrixd)(agl_ctx->rend, v)

#define glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) \
	(*agl_ctx->disp.compressed_tex_image3D)(agl_ctx->rend, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) \
	(*agl_ctx->disp.compressed_tex_image2D)(agl_ctx->rend, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) \
	(*agl_ctx->disp.compressed_tex_image1D)(agl_ctx->rend, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
	(*agl_ctx->disp.compressed_tex_sub_image3D)(agl_ctx->rend, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
	(*agl_ctx->disp.compressed_tex_sub_image2D)(agl_ctx->rend, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) \
	(*agl_ctx->disp.compressed_tex_sub_image1D)(agl_ctx->rend, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImage(target, level, img) \
	(*agl_ctx->disp.get_compressed_tex_image)(agl_ctx->rend, target, level, img)

#define glSampleCoverage(v, i) \
	(*agl_ctx->disp.sample_coverage)(agl_ctx->rend, v, i)

#define glSamplePass(mode) \
	(*agl_ctx->disp.sample_pass)(agl_ctx->rend, mode)

/****************** OpenGL 1.4 ************************************/

#define glFogCoordf(coord) \
	(*agl_ctx->disp.fog_coordf)(agl_ctx->rend, coord)

#define glFogCoordfv(coord) \
	(*agl_ctx->disp.fog_coordfv)(agl_ctx->rend, coord)

#define glFogCoordd(coord) \
	(*agl_ctx->disp.fog_coordd)(agl_ctx->rend, coord)

#define glFogCoorddv(coord) \
	(*agl_ctx->disp.fog_coorddv)(agl_ctx->rend,coord)

#define glFogCoordPointer(type, stride, pointer) \
	(*agl_ctx->disp.fog_coord_pointer)(agl_ctx->rend, type, stride, pointer)

#define glSecondaryColor3b(red, green, blue) \
	(*agl_ctx->disp.secondary_color3b)(agl_ctx->rend, red, green, blue)

#define glSecondaryColor3bv(components) \
	(*agl_ctx->disp.secondary_color3bv)(agl_ctx->rend, components)

#define glSecondaryColor3d(red, green, blue) \
	(*agl_ctx->disp.secondary_color3d)(agl_ctx->rend, red, green, blue)

#define glSecondaryColor3dv(components) \
	(*agl_ctx->disp.secondary_color3dv)(agl_ctx->rend, components)

#define glSecondaryColor3f(red, green, blue) \
	(*agl_ctx->disp.secondary_color3f)(agl_ctx->rend, red, green, blue)

#define glSecondaryColor3fv(components) \
	(*agl_ctx->disp.secondary_color3fv)(agl_ctx->rend, components)

#define glSecondaryColor3i(red, green, blue) \
	(*agl_ctx->disp.secondary_color3i)(agl_ctx->rend, red, green, blue)

#define glSecondaryColor3iv(components) \
	(*agl_ctx->disp.secondary_color3iv)(agl_ctx->rend, components)

#define glSecondaryColor3s(red, green, blue) \
	(*agl_ctx->disp.secondary_color3s)(agl_ctx->rend, red, green, blue)

#define glSecondaryColor3sv(components) \
	(*agl_ctx->disp.secondary_color3sv)(agl_ctx->rend, components)

#define glSecondaryColor3ub(red, green, blue) \
	(*agl_ctx->disp.secondary_color3ub)(agl_ctx->rend, red, green, blue)

#define glSecondaryColor3ubv(components) \
	(*agl_ctx->disp.secondary_color3ubv)(agl_ctx->rend, components)

#define glSecondaryColor3ui(red, green, blue) \
	(*agl_ctx->disp.secondary_color3ui)(agl_ctx->rend, red, green, blue)

#define glSecondaryColor3uiv(components) \
	(*agl_ctx->disp.secondary_color3uiv)(agl_ctx->rend, components)

#define glSecondaryColor3us(red, green, blue) \
	(*agl_ctx->disp.secondary_color3us)(agl_ctx->rend, red, green, blue)

#define glSecondaryColor3usv(components) \
	(*agl_ctx->disp.secondary_color3usv)(agl_ctx->rend, components)

#define glSecondaryColorPointer(size, type, stride, pointer) \
	(*agl_ctx->disp.secondary_color_pointer)(agl_ctx->rend, size, type, stride, pointer)

#define glPointParameterf(pname, param) \
	(*agl_ctx->disp.point_parameterf)(agl_ctx->rend, pname, param)

#define glPointParameterfv(pname, params) \
	(*agl_ctx->disp.point_parameterfv)(agl_ctx->rend, pname, params)

#define glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha) \
	(*agl_ctx->disp.blend_func_separate)(agl_ctx->rend, sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha)

#define glMultiDrawArrays(mode, first, count, primcount) \
	(*agl_ctx->disp.multi_draw_arrays)(agl_ctx->rend, mode, first, count, primcount)

#define glMultiDrawElements(mode, count, type, indices, primcount) \
	(*agl_ctx->disp.multi_draw_elements)(agl_ctx->rend, mode, count, type, indices, primcount)

#define glWindowPos2d(x, y) \
	(*agl_ctx->disp.window_pos2d)(agl_ctx->rend, x, y)

#define glWindowPos2dv(v) \
	(*agl_ctx->disp.window_pos2dv)(agl_ctx->rend, v)

#define glWindowPos2f(x, y) \
	(*agl_ctx->disp.window_pos2f)(agl_ctx->rend, x, y)

#define glWindowPos2fv(v) \
	(*agl_ctx->disp.window_pos2fv)(agl_ctx->rend, v)

#define glWindowPos2i(x, y) \
	(*agl_ctx->disp.window_pos2i)(agl_ctx->rend, x, y)

#define glWindowPos2iv(v) \
	(*agl_ctx->disp.window_pos2iv)(agl_ctx->rend, v)

#define glWindowPos2s(x, y) \
	(*agl_ctx->disp.window_pos2s)(agl_ctx->rend, x, y)

#define glWindowPos2sv(v) \
	(*agl_ctx->disp.window_pos2sv)(agl_ctx->rend, v)

#define glWindowPos3d(x, y, z) \
	(*agl_ctx->disp.window_pos3d)(agl_ctx->rend, x, y, z)

#define glWindowPos3dv(v) \
	(*agl_ctx->disp.window_pos3dv)(agl_ctx->rend, v)

#define glWindowPos3f(x, y, z) \
	(*agl_ctx->disp.window_pos3f)(agl_ctx->rend, x, y, z)

#define glWindowPos3fv(v) \
	(*agl_ctx->disp.window_pos3fv)(agl_ctx->rend, v)

#define glWindowPos3i(x, y, z) \
	(*agl_ctx->disp.window_pos3i)(agl_ctx->rend, x, y, z)

#define glWindowPos3iv(v) \
	(*agl_ctx->disp.window_pos3iv)(agl_ctx->rend, v)

#define glWindowPos3s(x, y, z) \
	(*agl_ctx->disp.window_pos3s)(agl_ctx->rend, x, y, z)

#define glWindowPos3sv(v) \
	(*agl_ctx->disp.window_pos3sv)(agl_ctx->rend, v)

/*********** ARB Extensions *************************************************/

/* GL_ARB_vertex_program */
#define glBindProgramARB(target, id) \
	(*agl_ctx->disp.bind_program_ARB)(agl_ctx->rend, target, id)

#define glDeleteProgramsARB(n, programs) \
	(*agl_ctx->disp.delete_programs_ARB)(agl_ctx->rend, n, programs)

#define glGenProgramsARB(n, programs) \
	(*agl_ctx->disp.gen_programs_ARB)(agl_ctx->rend, n, programs)

#define glIsProgramARB(id) \
	(*agl_ctx->disp.is_program_ARB)(agl_ctx->rend, id)

#define glVertexAttrib1sARB(index, x) \
	(*agl_ctx->disp.vertex_attrib1s_ARB)(agl_ctx->rend, index, x)

#define glVertexAttrib1fARB(index, x) \
	(*agl_ctx->disp.vertex_attrib1f_ARB)(agl_ctx->rend, index, x)

#define glVertexAttrib1dARB(index, x) \
	(*agl_ctx->disp.vertex_attrib1d_ARB)(agl_ctx->rend, index, x)

#define glVertexAttrib2sARB(index, x, y) \
	(*agl_ctx->disp.vertex_attrib2s_ARB)(agl_ctx->rend, index, x, y)

#define glVertexAttrib2fARB(index, x, y) \
	(*agl_ctx->disp.vertex_attrib2f_ARB)(agl_ctx->rend, index, x, y)

#define glVertexAttrib2dARB(index, x, y) \
	(*agl_ctx->disp.vertex_attrib2d_ARB)(agl_ctx->rend, index, x, y)

#define glVertexAttrib3sARB(index, x, y, z) \
	(*agl_ctx->disp.vertex_attrib3s_ARB)(agl_ctx->rend, index, x, y, z)

#define glVertexAttrib3fARB(index, x, y, z) \
	(*agl_ctx->disp.vertex_attrib3f_ARB)(agl_ctx->rend, index, x, y, z)

#define glVertexAttrib3dARB(index, x, y, z) \
	(*agl_ctx->disp.vertex_attrib3d_ARB)(agl_ctx->rend, index, x, y, z)

#define glVertexAttrib4sARB(index, x, y, z, w) \
	(*agl_ctx->disp.vertex_attrib4s_ARB)(agl_ctx->rend, index, x, y, z, w)

#define glVertexAttrib4fARB(index, x, y, z, w) \
	(*agl_ctx->disp.vertex_attrib4f_ARB)(agl_ctx->rend, index, x, y, z, w)

#define glVertexAttrib4dARB(index, x, y, z, w) \
	(*agl_ctx->disp.vertex_attrib4d_ARB)(agl_ctx->rend, index, x, y, z, w)

#define glVertexAttrib4NubARB(index, x, y, z, w) \
	(*agl_ctx->disp.vertex_attrib4Nub_ARB)(agl_ctx->rend, index, x, y, z, w)

#define glVertexAttrib1svARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib1sv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib1fvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib1fv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib1dvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib1dv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib2svARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib2sv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib2fvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib2fv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib2dvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib2dv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib3svARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib3sv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib3fvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib3fv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib3dvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib3dv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4bvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4bv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4ubvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4ubv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4svARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4sv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4usvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4usv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4ivARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4iv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4uivARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4uiv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4fvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4fv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4dvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4dv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4NbvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4Nbv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4NubvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4Nubv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4NsvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4Nsv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4NusvARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4Nusv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4NivARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4Niv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttrib4NuivARB(index, addr) \
	(*agl_ctx->disp.vertex_attrib4Nuiv_ARB)(agl_ctx->rend, index, addr)

#define glVertexAttribPointerARB(index, size, type, normalized, stride, addr) \
	(*agl_ctx->disp.vertex_attrib_pointer_ARB)(agl_ctx->rend, index, size, type, normalized, stride, addr)

#define glEnableVertexAttribArrayARB(index) \
	(*agl_ctx->disp.enable_vertex_attrib_array_ARB)(agl_ctx->rend, index)

#define glDisableVertexAttribArrayARB(index) \
	(*agl_ctx->disp.disable_vertex_attrib_array_ARB)(agl_ctx->rend, index)

#define glGetVertexAttribdvARB(index, pname, params) \
	(*agl_ctx->disp.get_vertex_attribdv_ARB)(agl_ctx->rend, index, pname, params)

#define glGetVertexAttribfvARB(index, pname, params) \
	(*agl_ctx->disp.get_vertex_attribfv_ARB)(agl_ctx->rend, index, pname, params)

#define glGetVertexAttribivARB(index, pname, params) \
	(*agl_ctx->disp.get_vertex_attribiv_ARB)(agl_ctx->rend, index, pname, params)

#define glGetVertexAttribPointervARB(index, pname, pointer) \
	(*agl_ctx->disp.get_vertex_attrib_pointerv_ARB)(agl_ctx->rend, index, pname, pointer)

#define glProgramEnvParameter4dARB(target, index, x, y, z, w) \
	(*agl_ctx->disp.program_env_parameter4d_ARB)(agl_ctx->rend, target, index, x, y, z, w)

#define glProgramEnvParameter4dvARB(target, index, params) \
	(*agl_ctx->disp.program_env_parameter4dv_ARB)(agl_ctx->rend, target, index, params)

#define glProgramEnvParameter4fARB(target, index, x, y, z, w) \
	(*agl_ctx->disp.program_env_parameter4f_ARB)(agl_ctx->rend, target, index, x, y, z, w)

#define glProgramEnvParameter4fvARB(target, index, params) \
	(*agl_ctx->disp.program_env_parameter4fv_ARB)(agl_ctx->rend, target, index, params)

#define glProgramLocalParameter4dARB(target, index, x, y, z, w) \
	(*agl_ctx->disp.program_local_parameter4d_ARB)(agl_ctx->rend, target, index, x, y, z, w)

#define glProgramLocalParameter4dvARB(target, index, params) \
	(*agl_ctx->disp.program_local_parameter4dv_ARB)(agl_ctx->rend, target, index, params)

#define glProgramLocalParameter4fARB(target, index, x, y, z, w) \
	(*agl_ctx->disp.program_local_parameter4f_ARB)(agl_ctx->rend, target, index, x, y, z, w)

#define glProgramLocalParameter4fvARB(target, index, params) \
	(*agl_ctx->disp.program_local_parameter4fv_ARB)(agl_ctx->rend, target, index, params)

#define glGetProgramEnvParameterdvARB(target, index, params) \
	(*agl_ctx->disp.get_program_env_parameterdv_ARB)(agl_ctx->rend, target, index, params)

#define glGetProgramEnvParameterfvARB(target, index, params) \
	(*agl_ctx->disp.get_program_env_parameterfv_ARB)(agl_ctx->rend, target, index, params)

#define glGetProgramLocalParameterdvARB(target, index, params) \
	(*agl_ctx->disp.get_program_local_parameterdv_ARB)(agl_ctx->rend, target, index, params)

#define glGetProgramLocalParameterfvARB(target, index, params) \
	(*agl_ctx->disp.get_program_local_parameterfv_ARB)(agl_ctx->rend, target, index, params)

#define glProgramStringARB(target, format, length, string) \
	(*agl_ctx->disp.program_string_ARB)(agl_ctx->rend, target, format, length, string)

#define glGetProgramStringARB(target, pname, string) \
	(*agl_ctx->disp.get_program_string_ARB)(agl_ctx->rend, target, pname, string)

#define glGetProgramivARB(target, pname, params) \
	(*agl_ctx->disp.get_programiv_ARB)(agl_ctx->rend, target, pname, params)

/* GL_ARB_vertex_blend */
#define glWeightbvARB(size, weights) \
	(*agl_ctx->disp.weightbv_ARB)(agl_ctx->rend, size, weights)

#define glWeightsvARB(size, weights) \
	(*agl_ctx->disp.weightsv_ARB)(agl_ctx->rend, size, weights)

#define glWeightivARB(size, weights) \
	(*agl_ctx->disp.weightiv_ARB)(agl_ctx->rend, size, weights)

#define glWeightfvARB(size, weights) \
	(*agl_ctx->disp.weightfv_ARB)(agl_ctx->rend, size, weights)

#define glWeightdvARB(size, weights) \
	(*agl_ctx->disp.weightdv_ARB)(agl_ctx->rend, size, weights)

#define glWeightubvARB(size, weights) \
	(*agl_ctx->disp.weightubv_ARB)(agl_ctx->rend, size, weights)

#define glWeightusvARB(size, weights) \
	(*agl_ctx->disp.weightusv_ARB)(agl_ctx->rend, size, weights)

#define glWeightuivARB(size, weights) \
	(*agl_ctx->disp.weightuiv_ARB)(agl_ctx->rend, size, weights)

#define glWeightPointerARB(size, type, stride, pointer) \
	(*agl_ctx->disp.weight_pointer_ARB)(agl_ctx->rend, size, type, stride, pointer)

#define glVertexBlendARB(count) \
	(*agl_ctx->disp.vertex_blend_ARB)(agl_ctx->rend, count)

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
	(*agl_ctx->disp.lock_arrays_EXT)(agl_ctx->rend, first, count)

#define glUnlockArraysEXT() \
	(*agl_ctx->disp.unlock_arrays_EXT)(agl_ctx->rend)

/* GL_EXT_stencil_two_side */
#define glActiveStencilFaceEXT(face) \
	(*agl_ctx->disp.active_stencil_face_EXT)(agl_ctx->rend, face)

/* GL_ATI_separate_stencil */
#define glStencilOpSeparateATI(face, sfail, dpfail, dppass) \
	(*agl_ctx->disp.stencil_op_separate_ATI)(agl_ctx->rend, face, sfail, dpfail, dppass)

#define glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask) \
	(*agl_ctx->disp.stencil_func_separate_ATI)(agl_ctx->rend, frontfunc, backfunc, ref, mask)

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
	(*agl_ctx->disp.enable_vertex_attrib_ARB)(agl_ctx->rend, index, pname)

#define glDisableVertexAttribAPPLE(index, pname) \
	(*agl_ctx->disp.disable_vertex_attrib_ARB)(agl_ctx->rend, index, pname)

#define glIsVertexAttribEnabledAPPLE(index, pname) \
	(*agl_ctx->disp.is_vertex_attrib_enabled_ARB)(agl_ctx->rend, index, pname)

#define glMapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points) \
	(*agl_ctx->disp.map_vertex_attrib1d_ARB)(agl_ctx->rend, index, size, u1, u2, stride, order, points)

#define glMapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points) \
	(*agl_ctx->disp.map_vertex_attrib1f_ARB)(agl_ctx->rend, index, size, u1, u2, stride, order, points)

#define glMapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*agl_ctx->disp.map_vertex_attrib2d_ARB)(agl_ctx->rend, index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*agl_ctx->disp.map_vertex_attrib2f_ARB)(agl_ctx->rend, index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

/* GL_APPLE_texture_range */
#define glTextureRangeAPPLE(target, length, pointer) \
	(*agl_ctx->disp.texture_range_APPLE)(agl_ctx->rend, target, length, pointer)

#define glGetTexParameterPointervAPPLE(target, pname, params) \
	(*agl_ctx->disp.get_tex_parameter_pointerv_APPLE)(agl_ctx->rend, target, pname, params)

/* GL_APPLE_fence */
#define glGenFencesAPPLE(n, fences) \
	(*agl_ctx->disp.gen_fences_APPLE)(agl_ctx->rend, n, fences)

#define glDeleteFencesAPPLE(n, fences) \
	(*agl_ctx->disp.delete_fences_APPLE)(agl_ctx->rend, n, fences)

#define glSetFenceAPPLE(fence) \
	(*agl_ctx->disp.set_fence_APPLE)(agl_ctx->rend, fence)

#define glIsFenceAPPLE(fence) \
	(*agl_ctx->disp.is_fence_APPLE)(agl_ctx->rend, fence)

#define glTestFenceAPPLE(fence) \
	(*agl_ctx->disp.test_fence_APPLE)(agl_ctx->rend, fence)

#define glFinishFenceAPPLE(fence) \
	(*agl_ctx->disp.finish_fence_APPLE)(agl_ctx->rend, fence)

#define glTestObjectAPPLE(object, name) \
	(*agl_ctx->disp.test_object_APPLE)(agl_ctx->rend, object, name)

#define glFinishObjectAPPLE(object, name) \
	(*agl_ctx->disp.finish_object_APPLE)(agl_ctx->rend, object, name)

/* GL_APPLE_vertex_array_range */
#define glVertexArrayRangeAPPLE(length, pointer) \
	(*agl_ctx->disp.vertex_array_range_EXT)(agl_ctx->rend, length, pointer)

#define glFlushVertexArrayRangeAPPLE(length, pointer) \
	(*agl_ctx->disp.flush_vertex_array_range_EXT)(agl_ctx->rend, length, pointer)

#define glVertexArrayParameteriAPPLE(pname, param) \
	(*agl_ctx->disp.vertex_array_parameteri_EXT)(agl_ctx->rend, pname, param)

/* GL_APPLE_vertex_array_object */
#define glBindVertexArrayAPPLE(id) \
	(*agl_ctx->disp.bind_vertex_array_EXT)(agl_ctx->rend, id)

#define glDeleteVertexArraysAPPLE(n, ids) \
	(*agl_ctx->disp.delete_vertex_arrays_EXT)(agl_ctx->rend, n, ids)

#define glGenVertexArraysAPPLE(n, ids) \
	(*agl_ctx->disp.gen_vertex_arrays_EXT)(agl_ctx->rend, n, ids)

#define glIsVertexArrayAPPLE(id) \
	(*agl_ctx->disp.is_vertex_array_EXT)(agl_ctx->rend, id)

/* GL_APPLE_element_array */
#define glElementPointerAPPLE(type, pointer) \
	(*agl_ctx->disp.element_pointer_APPLE)(agl_ctx->rend, type, pointer)

#define glDrawElementArrayAPPLE(mode, first, count) \
	(*agl_ctx->disp.draw_element_array_APPLE)(agl_ctx->rend, mode, first, count)

#define glDrawRangeElementArrayAPPLE(mode, start, end, first, count) \
	(*agl_ctx->disp.draw_range_element_array_APPLE)(agl_ctx->rend, mode, start, end, first, count)

/* GL_APPLE_flush_render */
#define glFlushRenderAPPLE() \
	(*agl_ctx->disp.flush_render_APPLE)(agl_ctx->rend)

#define glFinishRenderAPPLE() \
	(*agl_ctx->disp.finish_render_APPLE)(agl_ctx->rend)


/*********** ATI Extensions *************************************************/

/* GL_ATI_blend_equation_separate */
#define glBlendEquationSeparateATI(equationRGB, equationAlpha) \
	(*agl_ctx->disp.blend_equation_separate_ATI)(agl_ctx->rend, equationRGB, equationAlpha)

/* GL_ATI_pn_triangles */
#define glPNTrianglesiATI(pname, param) \
    (*agl_ctx->disp.pn_trianglesi_ATI)(agl_ctx->rend, pname, param)

#define glPNTrianglesfATI(pname, param) \
    (*agl_ctx->disp.pn_trianglesf_ATI)(agl_ctx->rend, pname, param)

/* GL_ATIX_pn_triangles */
#define glPNTrianglesiATIX glPNTrianglesiATI
#define glPNTrianglesfATIX glPNTrianglesfATI

/*********** NVIDIA Extensions **********************************************/

/* GL_NV_point_sprite */
#define glPointParameteriNV(pname, param) \
	(*agl_ctx->disp.point_parameteri)(agl_ctx->rend, pname, param)

#define glPointParameterivNV(pname, params) \
	(*agl_ctx->disp.point_parameteriv)(agl_ctx->rend, pname, params)

/* GL_NV_register_combiners */
#define glCombinerParameterfvNV(pname, params) \
	(*agl_ctx->disp.combiner_parameterfv_NV)(agl_ctx->rend, pname, params)

#define glCombinerParameterfNV(pname, param) \
	(*agl_ctx->disp.combiner_parameterf_NV)(agl_ctx->rend, pname, param)

#define glCombinerParameterivNV(pname, params) \
	(*agl_ctx->disp.combiner_parameteriv_NV)(agl_ctx->rend, pname, params)

#define glCombinerParameteriNV(pname, param) \
	(*agl_ctx->disp.combiner_parameteri_NV)(agl_ctx->rend, pname, param)

#define glCombinerInputNV(stage, portion, variable, input, mapping ,componentUsage) \
	(*agl_ctx->disp.combiner_input_NV)(agl_ctx->rend, stage, portion, variable, input, mapping ,componentUsage)

#define glCombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDoProduct, muxSum) \
	(*agl_ctx->disp.combiner_output_NV)(agl_ctx->rend, stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDoProduct, muxSum)

#define glFinalCombinerInputNV(variable, input, mapping, componentUsage) \
	(*agl_ctx->disp.final_combiner_input_NV)(agl_ctx->rend, variable, input, mapping, componentUsage)

#define glGetCombinerInputParameterfvNV(stage, portion, variable, pname, params) \
	(*agl_ctx->disp.get_combiner_input_parameterfv_NV)(agl_ctx->rend, stage, portion, variable, pname, params)

#define glGetCombinerInputParameterivNV(stage, portion, variable, pname, params) \
	(*agl_ctx->disp.get_combiner_input_parameteriv_NV)(agl_ctx->rend, stage, portion, variable, pname, params)

#define glGetCombinerOutputParameterfvNV(stage, portion, pname, params) \
	(*agl_ctx->disp.get_combiner_output_parameterfv_NV)(agl_ctx->rend, stage, portion, pname, params)

#define glGetCombinerOutputParameterivNV(stage, portion, pname, params) \
	(*agl_ctx->disp.get_combiner_output_parameteriv_NV)(agl_ctx->rend, stage, portion, pname, params)

#define glGetFinalCombinerInputParameterfvNV(variable, pname, params) \
	(*agl_ctx->disp.get_final_combiner_input_parameterfv_NV)(agl_ctx->rend, variable, pname, params)

#define glGetFinalCombinerInputParameterfvNV(variable, pname, params) \
	(*agl_ctx->disp.get_final_combiner_input_parameterfv_NV)(agl_ctx->rend, variable, pname, params)

/* GL_NV_register_combiners2 */
#define glCombinerStageParameterfvNV(stage, pname, params) \
	(*agl_ctx->disp.combiner_stage_parameterfv_NV)(agl_ctx->rend, stage, pname, params)

#define glGetCombinerStageParameterfvNV(stage, pname, param) \
	(*agl_ctx->disp.get_combiner_stage_parameterfv_NV)(agl_ctx->rend, stage, pname, param)

#endif /* _AGLMACRO_H */
