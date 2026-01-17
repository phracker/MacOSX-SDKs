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
	(*cgl_ctx->disp.color3bv)(cgl_ctx->rend, v)

#define glColor4d(red, green, blue, alpha) \
	(*cgl_ctx->disp.color4d)(cgl_ctx->rend, red, green, blue, alpha)

#define glColor4dv(v) \
	(*cgl_ctx->disp.color3dv)(cgl_ctx->rend, v)

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
	(*cgl_ctx->exts.blend_color)(cgl_ctx->rend, red, green, blue, alpha)

#define glBlendEquation(mode) \
	(*cgl_ctx->exts.blend_equation)(cgl_ctx->rend, mode)

#define glDrawRangeElements(mode, start, end, count, type, indices) \
	(*cgl_ctx->exts.draw_range_elements)(cgl_ctx->rend, mode, start, end, count, type, indices)

/****************** OpenGL 1.3 ************************************/

#define glClientActiveTexture(target) \
	(*cgl_ctx->exts.client_active_texture_ARB)(cgl_ctx->rend, target)

#define glActiveTexture(target) \
	(*cgl_ctx->exts.active_texture_ARB)(cgl_ctx->rend, target)

#define glMultiTexCoord1d(target, s) \
	(*cgl_ctx->exts.multi_tex_coord1d_ARB)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1dv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord1dv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1f(target, s) \
	(*cgl_ctx->exts.multi_tex_coord1f_ARB)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1fv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord1fv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1i(target, s) \
	(*cgl_ctx->exts.multi_tex_coord1i_ARB)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1iv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord1iv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1s(target, s) \
	(*cgl_ctx->exts.multi_tex_coord1s_ARB)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1sv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord1sv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2d(target, s, t) \
	(*cgl_ctx->exts.multi_tex_coord2d_ARB)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2dv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord2dv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2f(target, s, t) \
	(*cgl_ctx->exts.multi_tex_coord2f_ARB)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2fv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord2fv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2i(target, s, t) \
	(*cgl_ctx->exts.multi_tex_coord2i_ARB)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2iv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord2iv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2s(target, s, t) \
	(*cgl_ctx->exts.multi_tex_coord2s_ARB)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2sv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord2sv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3d(target, s, t, r) \
	(*cgl_ctx->exts.multi_tex_coord3d_ARB)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3dv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord3dv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3f(target, s, t, r) \
	(*cgl_ctx->exts.multi_tex_coord3f_ARB)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3fv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord3fv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3i(target, s, t, r) \
	(*cgl_ctx->exts.multi_tex_coord3i_ARB)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3iv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord3iv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3s(target, s, t, r) \
	(*cgl_ctx->exts.multi_tex_coord3s_ARB)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3sv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord3sv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4d(target, s, t, r, q) \
	(*cgl_ctx->exts.multi_tex_coord4d_ARB)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4dv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord4dv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4f(target, s, t, r, q) \
	(*cgl_ctx->exts.multi_tex_coord4f_ARB)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4fv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord4fv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4i(target, s, t, r, q) \
	(*cgl_ctx->exts.multi_tex_coord4i_ARB)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4iv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord4iv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4s(target, s, t, r, q) \
	(*cgl_ctx->exts.multi_tex_coord4s_ARB)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4sv(target, v) \
	(*cgl_ctx->exts.multi_tex_coord4sv_ARB)(cgl_ctx->rend, target, v)

#define glSampleCoverage(v, i) \
	(*cgl_ctx->exts.sample_coverage_ARB)(cgl_ctx->rend, v, i)

#define glSamplePass(mode) \
	(*cgl_ctx->exts.sample_pass_ARB)(cgl_ctx->rend, mode)

#define glLoadTransposeMatrixf(v) \
	(*cgl_ctx->exts.load_transpose_matrixf_ARB)(cgl_ctx->rend, v)

#define glLoadTransposeMatrixd(v) \
	(*cgl_ctx->exts.load_transpose_matrixd_ARB)(cgl_ctx->rend, v)

#define glMultTransposeMatrixf(v) \
	(*cgl_ctx->exts.mult_transpose_matrixf_ARB)(cgl_ctx->rend, v)

#define glMultTransposeMatrixd(v) \
	(*cgl_ctx->exts.mult_transpose_matrixd_ARB)(cgl_ctx->rend, v)

#define glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_image3D_ARB)(cgl_ctx->rend, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_image2D_ARB)(cgl_ctx->rend, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_image1D_ARB)(cgl_ctx->rend, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_sub_image3D_ARB)(cgl_ctx->rend, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_sub_image2D_ARB)(cgl_ctx->rend, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_sub_image1D_ARB)(cgl_ctx->rend, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImage(target, level, img) \
	(*cgl_ctx->exts.get_compressed_tex_image_ARB)(cgl_ctx->rend, target, level, img)
	
/****************** Supported OpenGL Extension Macros *************/

#define glBlendColorEXT(red, green, blue, alpha) \
	(*cgl_ctx->exts.blend_color_EXT)(cgl_ctx->rend, red, green, blue, alpha)

#define glBlendEquationEXT(mode) \
	(*cgl_ctx->exts.blend_equation_EXT)(cgl_ctx->rend, mode)

#define glLockArraysEXT(first, count) \
	(*cgl_ctx->exts.lock_arrays_EXT)(cgl_ctx->rend, first, count)

#define glUnlockArraysEXT() \
	(*cgl_ctx->exts.unlock_arrays_EXT)(cgl_ctx->rend)

#define glClientActiveTextureARB(target) \
	(*cgl_ctx->exts.client_active_texture_ARB)(cgl_ctx->rend, target)

#define glActiveTextureARB(target) \
	(*cgl_ctx->exts.active_texture_ARB)(cgl_ctx->rend, target)


#define glMultiTexCoord1dARB(target, s) \
	(*cgl_ctx->exts.multi_tex_coord1d_ARB)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1dvARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord1dv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1fARB(target, s) \
	(*cgl_ctx->exts.multi_tex_coord1f_ARB)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1fvARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord1fv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1iARB(target, s) \
	(*cgl_ctx->exts.multi_tex_coord1i_ARB)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1ivARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord1iv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord1sARB(target, s) \
	(*cgl_ctx->exts.multi_tex_coord1s_ARB)(cgl_ctx->rend, target, s)

#define glMultiTexCoord1svARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord1sv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2dARB(target, s, t) \
	(*cgl_ctx->exts.multi_tex_coord2d_ARB)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2dvARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord2dv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2fARB(target, s, t) \
	(*cgl_ctx->exts.multi_tex_coord2f_ARB)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2fvARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord2fv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2iARB(target, s, t) \
	(*cgl_ctx->exts.multi_tex_coord2i_ARB)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2ivARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord2iv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord2sARB(target, s, t) \
	(*cgl_ctx->exts.multi_tex_coord2s_ARB)(cgl_ctx->rend, target, s, t)

#define glMultiTexCoord2svARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord2sv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3dARB(target, s, t, r) \
	(*cgl_ctx->exts.multi_tex_coord3d_ARB)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3dvARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord3dv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3fARB(target, s, t, r) \
	(*cgl_ctx->exts.multi_tex_coord3f_ARB)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3fvARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord3fv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3iARB(target, s, t, r) \
	(*cgl_ctx->exts.multi_tex_coord3i_ARB)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3ivARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord3iv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord3sARB(target, s, t, r) \
	(*cgl_ctx->exts.multi_tex_coord3s_ARB)(cgl_ctx->rend, target, s, t, r)

#define glMultiTexCoord3svARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord3sv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4dARB(target, s, t, r, q) \
	(*cgl_ctx->exts.multi_tex_coord4d_ARB)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4dvARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord4dv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4fARB(target, s, t, r, q) \
	(*cgl_ctx->exts.multi_tex_coord4f_ARB)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4fvARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord4fv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4iARB(target, s, t, r, q) \
	(*cgl_ctx->exts.multi_tex_coord4i_ARB)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4ivARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord4iv_ARB)(cgl_ctx->rend, target, v)

#define glMultiTexCoord4sARB(target, s, t, r, q) \
	(*cgl_ctx->exts.multi_tex_coord4s_ARB)(cgl_ctx->rend, target, s, t, r, q)

#define glMultiTexCoord4svARB(target, v) \
	(*cgl_ctx->exts.multi_tex_coord4sv_ARB)(cgl_ctx->rend, target, v)

#define glSampleCoverageARB(v, i) \
	(*cgl_ctx->exts.sample_coverage_ARB)(cgl_ctx->rend, v, i)

#define glSamplePassARB(mode) \
	(*cgl_ctx->exts.sample_pass_ARB)(cgl_ctx->rend, mode)

#define glLoadTransposeMatrixfARB(v) \
	(*cgl_ctx->exts.load_transpose_matrixf_ARB)(cgl_ctx->rend, v)

#define glLoadTransposeMatrixdARB(v) \
	(*cgl_ctx->exts.load_transpose_matrixd_ARB)(cgl_ctx->rend, v)

#define glMultTransposeMatrixfARB(v) \
	(*cgl_ctx->exts.mult_transpose_matrixf_ARB)(cgl_ctx->rend, v)

#define glMultTransposeMatrixdARB(v) \
	(*cgl_ctx->exts.mult_transpose_matrixd_ARB)(cgl_ctx->rend, v)

#define glCompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_image3D_ARB)(cgl_ctx->rend, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_image2D_ARB)(cgl_ctx->rend, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_image1D_ARB)(cgl_ctx->rend, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_sub_image3D_ARB)(cgl_ctx->rend, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_sub_image2D_ARB)(cgl_ctx->rend, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data) \
	(*cgl_ctx->exts.compressed_tex_sub_image1D_ARB)(cgl_ctx->rend, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImageARB(target, level, img) \
	(*cgl_ctx->exts.get_compressed_tex_image_ARB)(cgl_ctx->rend, target, level, img)

#endif /* _CGLMACRO_H */

