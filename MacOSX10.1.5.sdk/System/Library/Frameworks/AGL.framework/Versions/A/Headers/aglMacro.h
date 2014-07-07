/*
    File:	AGL/aglMacro.h

    Contains:	Macros that replace OpenGL function calls when you use the internal renderer interface.

    Version:	Technology:	Mac OS 9
                Release:	GM
 
     Copyright:  (c) 2000 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _AGLMACRO_H
#define _AGLMACRO_H

#include "aglContext.h"

/****************** OpenGL 1.1 Macros *****************************/

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

#define glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap) \
	(*agl_ctx->disp.bitmap)(agl_ctx->rend, width, height, xorig, yorig, xmove, ymove, bitmap)

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

#define glDrawRangeElements(mode, start, end, count, type, indices) \
	(*agl_ctx->exts.draw_range_elements)(agl_ctx->rend, mode, start, end, count, type, indices)

/****************** OpenGL 1.3 ************************************/

#define glClientActiveTexture(target) \
	(*agl_ctx->exts.client_active_texture_ARB)(agl_ctx->rend, target)

#define glActiveTexture(target) \
	(*agl_ctx->exts.active_texture_ARB)(agl_ctx->rend, target)

#define glMultiTexCoord1d(target, s) \
	(*agl_ctx->exts.multi_tex_coord1d_ARB)(agl_ctx->rend, target, s)

#define glMultiTexCoord1dv(target, v) \
	(*agl_ctx->exts.multi_tex_coord1dv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord1f(target, s) \
	(*agl_ctx->exts.multi_tex_coord1f_ARB)(agl_ctx->rend, target, s)

#define glMultiTexCoord1fv(target, v) \
	(*agl_ctx->exts.multi_tex_coord1fv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord1i(target, s) \
	(*agl_ctx->exts.multi_tex_coord1i_ARB)(agl_ctx->rend, target, s)

#define glMultiTexCoord1iv(target, v) \
	(*agl_ctx->exts.multi_tex_coord1iv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord1s(target, s) \
	(*agl_ctx->exts.multi_tex_coord1s_ARB)(agl_ctx->rend, target, s)

#define glMultiTexCoord1sv(target, v) \
	(*agl_ctx->exts.multi_tex_coord1sv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord2d(target, s, t) \
	(*agl_ctx->exts.multi_tex_coord2d_ARB)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2dv(target, v) \
	(*agl_ctx->exts.multi_tex_coord2dv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord2f(target, s, t) \
	(*agl_ctx->exts.multi_tex_coord2f_ARB)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2fv(target, v) \
	(*agl_ctx->exts.multi_tex_coord2fv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord2i(target, s, t) \
	(*agl_ctx->exts.multi_tex_coord2i_ARB)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2iv(target, v) \
	(*agl_ctx->exts.multi_tex_coord2iv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord2s(target, s, t) \
	(*agl_ctx->exts.multi_tex_coord2s_ARB)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2sv(target, v) \
	(*agl_ctx->exts.multi_tex_coord2sv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord3d(target, s, t, r) \
	(*agl_ctx->exts.multi_tex_coord3d_ARB)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3dv(target, v) \
	(*agl_ctx->exts.multi_tex_coord3dv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord3f(target, s, t, r) \
	(*agl_ctx->exts.multi_tex_coord3f_ARB)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3fv(target, v) \
	(*agl_ctx->exts.multi_tex_coord3fv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord3i(target, s, t, r) \
	(*agl_ctx->exts.multi_tex_coord3i_ARB)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3iv(target, v) \
	(*agl_ctx->exts.multi_tex_coord3iv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord3s(target, s, t, r) \
	(*agl_ctx->exts.multi_tex_coord3s_ARB)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3sv(target, v) \
	(*agl_ctx->exts.multi_tex_coord3sv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord4d(target, s, t, r, q) \
	(*agl_ctx->exts.multi_tex_coord4d_ARB)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4dv(target, v) \
	(*agl_ctx->exts.multi_tex_coord4dv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord4f(target, s, t, r, q) \
	(*agl_ctx->exts.multi_tex_coord4f_ARB)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4fv(target, v) \
	(*agl_ctx->exts.multi_tex_coord4fv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord4i(target, s, t, r, q) \
	(*agl_ctx->exts.multi_tex_coord4i_ARB)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4iv(target, v) \
	(*agl_ctx->exts.multi_tex_coord4iv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord4s(target, s, t, r, q) \
	(*agl_ctx->exts.multi_tex_coord4s_ARB)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4sv(target, v) \
	(*agl_ctx->exts.multi_tex_coord4sv_ARB)(agl_ctx->rend, target, v)

#define glSampleCoverage(v, i) \
	(*agl_ctx->exts.sample_coverage_ARB)(agl_ctx->rend, v, i)

#define glSamplePass(mode) \
	(*agl_ctx->exts.sample_pass_ARB)(agl_ctx->rend, mode)

#define glLoadTransposeMatrixf(v) \
	(*agl_ctx->exts.load_transpose_matrixf_ARB)(agl_ctx->rend, v)

#define glLoadTransposeMatrixd(v) \
	(*agl_ctx->exts.load_transpose_matrixd_ARB)(agl_ctx->rend, v)

#define glMultTransposeMatrixf(v) \
	(*agl_ctx->exts.mult_transpose_matrixf_ARB)(agl_ctx->rend, v)

#define glMultTransposeMatrixd(v) \
	(*agl_ctx->exts.mult_transpose_matrixd_ARB)(agl_ctx->rend, v)

#define glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_image3D_ARB)(agl_ctx->rend, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_image2D_ARB)(agl_ctx->rend, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_image1D_ARB)(agl_ctx->rend, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_sub_image3D_ARB)(agl_ctx->rend, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_sub_image2D_ARB)(agl_ctx->rend, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_sub_image1D_ARB)(agl_ctx->rend, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImage(target, level, img) \
	(*agl_ctx->exts.get_compressed_tex_image_ARB)(agl_ctx->rend, target, level, img)
	
/****************** Supported OpenGL Extension Macros *************/

/* EXT_blend_color */
#define glBlendColorEXT(red, green, blue, alpha) \
	(*agl_ctx->exts.blend_color_EXT)(agl_ctx->rend, red, green, blue, alpha)

/* EXT_blend_minmax */
#define glBlendEquationEXT(mode) \
	(*agl_ctx->exts.blend_equation_EXT)(agl_ctx->rend, mode)

/* EXT_compiled_vertex_array */
#define glLockArraysEXT(first, count) \
	(*agl_ctx->exts.lock_arrays_EXT)(agl_ctx->rend, first, count)

#define glUnlockArraysEXT() \
	(*agl_ctx->exts.unlock_arrays_EXT)(agl_ctx->rend)

/* ARB_multitexture */
#define glActiveTextureARB(target) \
	(*agl_ctx->exts.active_texture_ARB)(agl_ctx->rend, target)

#define glClientActiveTextureARB(target) \
	(*agl_ctx->exts.client_active_texture_ARB)(agl_ctx->rend, target)

#define glMultiTexCoord1dARB(target, s) \
	(*agl_ctx->exts.multi_tex_coord1d_ARB)(agl_ctx->rend, target, s)

#define glMultiTexCoord1dvARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord1dv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord1fARB(target, s) \
	(*agl_ctx->exts.multi_tex_coord1f_ARB)(agl_ctx->rend, target, s)

#define glMultiTexCoord1fvARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord1fv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord1iARB(target, s) \
	(*agl_ctx->exts.multi_tex_coord1i_ARB)(agl_ctx->rend, target, s)

#define glMultiTexCoord1ivARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord1iv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord1sARB(target, s) \
	(*agl_ctx->exts.multi_tex_coord1s_ARB)(agl_ctx->rend, target, s)

#define glMultiTexCoord1svARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord1sv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord2dARB(target, s, t) \
	(*agl_ctx->exts.multi_tex_coord2d_ARB)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2dvARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord2dv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord2fARB(target, s, t) \
	(*agl_ctx->exts.multi_tex_coord2f_ARB)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2fvARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord2fv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord2iARB(target, s, t) \
	(*agl_ctx->exts.multi_tex_coord2i_ARB)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2ivARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord2iv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord2sARB(target, s, t) \
	(*agl_ctx->exts.multi_tex_coord2s_ARB)(agl_ctx->rend, target, s, t)

#define glMultiTexCoord2svARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord2sv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord3dARB(target, s, t, r) \
	(*agl_ctx->exts.multi_tex_coord3d_ARB)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3dvARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord3dv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord3fARB(target, s, t, r) \
	(*agl_ctx->exts.multi_tex_coord3f_ARB)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3fvARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord3fv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord3iARB(target, s, t, r) \
	(*agl_ctx->exts.multi_tex_coord3i_ARB)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3ivARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord3iv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord3sARB(target, s, t, r) \
	(*agl_ctx->exts.multi_tex_coord3s_ARB)(agl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3svARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord3sv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord4dARB(target, s, t, r, q) \
	(*agl_ctx->exts.multi_tex_coord4d_ARB)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4dvARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord4dv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord4fARB(target, s, t, r, q) \
	(*agl_ctx->exts.multi_tex_coord4f_ARB)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4fvARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord4fv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord4iARB(target, s, t, r, q) \
	(*agl_ctx->exts.multi_tex_coord4i_ARB)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4ivARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord4iv_ARB)(agl_ctx->rend, target, v)

#define glMultiTexCoord4sARB(target, s, t, r, q) \
	(*agl_ctx->exts.multi_tex_coord4s_ARB)(agl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4svARB(target, v) \
	(*agl_ctx->exts.multi_tex_coord4sv_ARB)(agl_ctx->rend, target, v)


#define glSampleCoverageARB(v, i) \
	(*agl_ctx->exts.sample_coverage_ARB)(agl_ctx->rend, v, i)

#define glSamplePassARB(mode) \
	(*agl_ctx->exts.sample_pass_ARB)(agl_ctx->rend, mode)

#define glLoadTransposeMatrixfARB(v) \
	(*agl_ctx->exts.load_transpose_matrixf_ARB)(agl_ctx->rend, v)

#define glLoadTransposeMatrixdARB(v) \
	(*agl_ctx->exts.load_transpose_matrixd_ARB)(agl_ctx->rend, v)

#define glMultTransposeMatrixfARB(v) \
	(*agl_ctx->exts.mult_transpose_matrixf_ARB)(agl_ctx->rend, v)

#define glMultTransposeMatrixdARB(v) \
	(*agl_ctx->exts.mult_transpose_matrixd_ARB)(agl_ctx->rend, v)

#define glCompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_image3D_ARB)(agl_ctx->rend, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_image2D_ARB)(agl_ctx->rend, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_image1D_ARB)(agl_ctx->rend, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_sub_image3D_ARB)(agl_ctx->rend, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_sub_image2D_ARB)(agl_ctx->rend, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data) \
	(*agl_ctx->exts.compressed_tex_sub_image1D_ARB)(agl_ctx->rend, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImageARB(target, level, img) \
	(*agl_ctx->exts.get_compressed_tex_image_ARB)(agl_ctx->rend, target, level, img)

#endif /* _AGLMACRO_H */
