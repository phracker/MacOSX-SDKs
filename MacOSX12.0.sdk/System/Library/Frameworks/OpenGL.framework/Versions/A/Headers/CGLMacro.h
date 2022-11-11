/*
	Copyright:	(c) 1999-2012 Apple Inc. All rights reserved.
*/

#ifndef _CGLMACRO_H
#define _CGLMACRO_H

#ifdef __gl3_h_
#  ifndef __has_feature
#    define __has_feature(X) 0
#  endif
#  if !__has_feature(modules)
#    error Can not include both gl3.h and CGLMacro.h simultaneously
#  endif
#endif

#include <OpenGL/CGLTypes.h>
#include <OpenGL/CGLContext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

/* Macro context name (CGLContextObj) */
#if !defined(CGL_MACRO_CONTEXT)
#define CGL_MACRO_CONTEXT cgl_ctx
#endif

/* Macro renderer name (GLIContext) */
#if !defined(CGL_MACRO_RENDERER)
#define CGL_MACRO_RENDERER cgl_rend
#endif

#define CGL_MACRO_DECLARE_CONTEXT()  CGLContextObj CGL_MACRO_CONTEXT = CGLGetCurrentContext();

/* Repeated renderer lookups may be avoided by defining CGL_MACRO_CACHE_RENDERER before including CGLMacro.h.
   Note: If you change the value of CGL_MACRO_CONTEXT partway through a function, you will have to
   keep CGL_MACRO_RENDERER up to date with with it's context. */
#if defined(CGL_MACRO_CACHE_RENDERER)
#define CGL_MACRO_DECLARE_RENDERER()  GLIContext CGL_MACRO_RENDERER = CGL_MACRO_CONTEXT->rend;
#define CGL_MACRO_CONTEXT_RENDERER  CGL_MACRO_RENDERER
#else
#define CGL_MACRO_DECLARE_RENDERER()
#define CGL_MACRO_CONTEXT_RENDERER  CGL_MACRO_CONTEXT->rend
#endif

/* Use the following function macro to declare the local CGLMacro variables */
#define CGL_MACRO_DECLARE_VARIABLES() \
	CGL_MACRO_DECLARE_CONTEXT(); \
	CGL_MACRO_DECLARE_RENDERER();

/* This is for converting old non-arb handle definitions to ARB handle definitions for 64 bit compiles */
#define CGL_HANDLE_ARB(handle)	(GLhandleARB)((unsigned long)handle)

/****************** OpenGL 1.1 Macros *****************************/

#define glAccum(op, value) \
	(*(CGL_MACRO_CONTEXT)->disp.accum)(CGL_MACRO_CONTEXT_RENDERER, op, value)

#define glAlphaFunc(func, ref) \
	(*(CGL_MACRO_CONTEXT)->disp.alpha_func)(CGL_MACRO_CONTEXT_RENDERER, func, ref)

#define glAreTexturesResident(n, textures, residences) \
	(*(CGL_MACRO_CONTEXT)->disp.are_textures_resident)(CGL_MACRO_CONTEXT_RENDERER, n, textures, residences)

#define glArrayElement(i) \
	(*(CGL_MACRO_CONTEXT)->disp.array_element)(CGL_MACRO_CONTEXT_RENDERER, i)

#define glBegin(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.begin)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glBindTexture(target, texture) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_texture)(CGL_MACRO_CONTEXT_RENDERER, target, texture)

#define glBitmap(width, height, xorig, yorig, xmove, ymove, bmap) \
	(*(CGL_MACRO_CONTEXT)->disp.bitmap)(CGL_MACRO_CONTEXT_RENDERER, width, height, xorig, yorig, xmove, ymove, bmap)

#define glBlendFunc(sfactor, dfactor) \
	(*(CGL_MACRO_CONTEXT)->disp.blend_func)(CGL_MACRO_CONTEXT_RENDERER, sfactor, dfactor)

#define glCallList(list) \
	(*(CGL_MACRO_CONTEXT)->disp.call_list)(CGL_MACRO_CONTEXT_RENDERER, list)

#define glCallLists(n, type, lists) \
	(*(CGL_MACRO_CONTEXT)->disp.call_lists)(CGL_MACRO_CONTEXT_RENDERER, n, type, lists)

#define glClear(mask) \
	(*(CGL_MACRO_CONTEXT)->disp.clear)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glClearAccum(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_accum)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glClearColor(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_color)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glClearDepth(depth) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_depth)(CGL_MACRO_CONTEXT_RENDERER, depth)

#define glClearIndex(c) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_index)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glClearStencil(s) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_stencil)(CGL_MACRO_CONTEXT_RENDERER, s)

#define glClipPlane(plane, equation) \
	(*(CGL_MACRO_CONTEXT)->disp.clip_plane)(CGL_MACRO_CONTEXT_RENDERER, plane, equation)

#define glColor3b(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.color3b)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3bv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color3bv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3d(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.color3d)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color3dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3f(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.color3f)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color3fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3i(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.color3i)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color3iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3s(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.color3s)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color3sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3ub(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.color3ub)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3ubv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color3ubv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3ui(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.color3ui)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3uiv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color3uiv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3us(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.color3us)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3usv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color3usv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4b(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color4b)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4bv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color4bv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4d(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color4d)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color4dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4f(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color4f)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color4fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4i(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color4i)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color4iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4s(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color4s)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color4sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4ub(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color4ub)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4ubv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color4ubv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4ui(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color4ui)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4uiv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color4uiv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4us(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color4us)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4usv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.color4usv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glColorMask(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.color_mask)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColorMaterial(face, mode) \
	(*(CGL_MACRO_CONTEXT)->disp.color_material)(CGL_MACRO_CONTEXT_RENDERER, face, mode)

#define glColorPointer(size, type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.color_pointer)(CGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glCopyPixels(x, y, width, height, type) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_pixels)(CGL_MACRO_CONTEXT_RENDERER, x, y, width, height, type)

#define glCopyTexImage1D(target, level, internalFormat, x, y, width, border) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_tex_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalFormat, x, y, width, border)

#define glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_tex_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalFormat, x, y, width, height, border)

#define glCopyTexSubImage1D(target, level, xoffset, x, y, width) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_tex_sub_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, x, y, width)

#define glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_tex_sub_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, x, y, width, height)

#define glCullFace(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.cull_face)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glDeleteLists(list, range) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_lists)(CGL_MACRO_CONTEXT_RENDERER, list, range)

#define glDeleteTextures(n, textures) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_textures)(CGL_MACRO_CONTEXT_RENDERER, n, textures)

#define glDepthFunc(func) \
	(*(CGL_MACRO_CONTEXT)->disp.depth_func)(CGL_MACRO_CONTEXT_RENDERER, func)

#define glDepthMask(flag) \
	(*(CGL_MACRO_CONTEXT)->disp.depth_mask)(CGL_MACRO_CONTEXT_RENDERER, flag)

#define glDepthRange(zNear, zFar) \
	(*(CGL_MACRO_CONTEXT)->disp.depth_range)(CGL_MACRO_CONTEXT_RENDERER, zNear, zFar)

#define glDisable(cap) \
	(*(CGL_MACRO_CONTEXT)->disp.disable)(CGL_MACRO_CONTEXT_RENDERER, cap)

#define glDisableClientState(array) \
	(*(CGL_MACRO_CONTEXT)->disp.disable_client_state)(CGL_MACRO_CONTEXT_RENDERER, array)

#define glDrawArrays(mode, first, count) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_arrays)(CGL_MACRO_CONTEXT_RENDERER, mode, first, count)

#define glDrawBuffer(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_buffer)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glDrawElements(mode, count, type, indices) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_elements)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices)

#define glDrawPixels(width, height, format, type, pixels) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_pixels)(CGL_MACRO_CONTEXT_RENDERER, width, height, format, type, pixels)

#define glEdgeFlag(flag) \
	(*(CGL_MACRO_CONTEXT)->disp.edge_flag)(CGL_MACRO_CONTEXT_RENDERER, flag)

#define glEdgeFlagPointer(stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.edge_flag_pointer)(CGL_MACRO_CONTEXT_RENDERER, stride, pointer)

#define glEdgeFlagv(flag) \
	(*(CGL_MACRO_CONTEXT)->disp.edge_flagv)(CGL_MACRO_CONTEXT_RENDERER, flag)

#define glEnable(cap) \
	(*(CGL_MACRO_CONTEXT)->disp.enable)(CGL_MACRO_CONTEXT_RENDERER, cap)

#define glEnableClientState(array) \
	(*(CGL_MACRO_CONTEXT)->disp.enable_client_state)(CGL_MACRO_CONTEXT_RENDERER, array)

#define glEnd() \
	(*(CGL_MACRO_CONTEXT)->disp.end)(CGL_MACRO_CONTEXT_RENDERER)

#define glEndList() \
	(*(CGL_MACRO_CONTEXT)->disp.end_list)(CGL_MACRO_CONTEXT_RENDERER)

#define glEvalCoord1d(u) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_coord1d)(CGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord1dv(u) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_coord1dv)(CGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord1f(u) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_coord1f)(CGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord1fv(u) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_coord1fv)(CGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord2d(u, v) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_coord2d)(CGL_MACRO_CONTEXT_RENDERER, u, v)

#define glEvalCoord2dv(u) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_coord2dv)(CGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord2f(u, v) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_coord2f)(CGL_MACRO_CONTEXT_RENDERER, u, v)

#define glEvalCoord2fv(u) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_coord2fv)(CGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalMesh1(mode, i1, i2) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_mesh1)(CGL_MACRO_CONTEXT_RENDERER, mode, i1, i2)

#define glEvalMesh2(mode, i1, i2, j1, j2) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_mesh2)(CGL_MACRO_CONTEXT_RENDERER, mode, i1, i2, j1, j2)

#define glEvalPoint1(i) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_point1)(CGL_MACRO_CONTEXT_RENDERER, i)

#define glEvalPoint2(i, j) \
	(*(CGL_MACRO_CONTEXT)->disp.eval_point2)(CGL_MACRO_CONTEXT_RENDERER, i, j)

#define glFeedbackBuffer(size, type, buffer) \
	(*(CGL_MACRO_CONTEXT)->disp.feedback_buffer)(CGL_MACRO_CONTEXT_RENDERER, size, type, buffer)

#define glFinish() \
	(*(CGL_MACRO_CONTEXT)->disp.finish)(CGL_MACRO_CONTEXT_RENDERER)

#define glFlush() \
	(*(CGL_MACRO_CONTEXT)->disp.flush)(CGL_MACRO_CONTEXT_RENDERER)

#define glFogf(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.fogf)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glFogfv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.fogfv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glFogi(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.fogi)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glFogiv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.fogiv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glFrontFace(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.front_face)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glFrustum(left, right, bottom, top, zNear, zFar) \
	(*(CGL_MACRO_CONTEXT)->disp.frustum)(CGL_MACRO_CONTEXT_RENDERER, left, right, bottom, top, zNear, zFar)

#define glGenLists(range) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_lists)(CGL_MACRO_CONTEXT_RENDERER, range)

#define glGenTextures(n, textures) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_textures)(CGL_MACRO_CONTEXT_RENDERER, n, textures)

#define glGetBooleanv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_booleanv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetClipPlane(plane, equation) \
	(*(CGL_MACRO_CONTEXT)->disp.get_clip_plane)(CGL_MACRO_CONTEXT_RENDERER, plane, equation)

#define glGetDoublev(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_doublev)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetError() \
	(*(CGL_MACRO_CONTEXT)->disp.get_error)(CGL_MACRO_CONTEXT_RENDERER)

#define glGetFloatv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_floatv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetIntegerv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_integerv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetLightfv(light, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_lightfv)(CGL_MACRO_CONTEXT_RENDERER, light, pname, params)

#define glGetLightiv(light, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_lightiv)(CGL_MACRO_CONTEXT_RENDERER, light, pname, params)

#define glGetMapdv(target, query, v) \
	(*(CGL_MACRO_CONTEXT)->disp.get_mapdv)(CGL_MACRO_CONTEXT_RENDERER, target, query, v)

#define glGetMapfv(target, query, v) \
	(*(CGL_MACRO_CONTEXT)->disp.get_mapfv)(CGL_MACRO_CONTEXT_RENDERER, target, query, v)

#define glGetMapiv(target, query, v) \
	(*(CGL_MACRO_CONTEXT)->disp.get_mapiv)(CGL_MACRO_CONTEXT_RENDERER, target, query, v)

#define glGetMaterialfv(face, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_materialfv)(CGL_MACRO_CONTEXT_RENDERER, face, pname, params)

#define glGetMaterialiv(face, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_materialiv)(CGL_MACRO_CONTEXT_RENDERER, face, pname, params)

#define glGetPixelMapfv(map, values) \
	(*(CGL_MACRO_CONTEXT)->disp.get_pixel_mapfv)(CGL_MACRO_CONTEXT_RENDERER, map, values)

#define glGetPixelMapuiv(map, values) \
	(*(CGL_MACRO_CONTEXT)->disp.get_pixel_mapuiv)(CGL_MACRO_CONTEXT_RENDERER, map, values)

#define glGetPixelMapusv(map, values) \
	(*(CGL_MACRO_CONTEXT)->disp.get_pixel_mapusv)(CGL_MACRO_CONTEXT_RENDERER, map, values)

#define glGetPointerv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_pointerv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetPolygonStipple(mask) \
	(*(CGL_MACRO_CONTEXT)->disp.get_polygon_stipple)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glGetString(name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_string)(CGL_MACRO_CONTEXT_RENDERER, name)

#define glGetTexEnvfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_envfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexEnviv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_enviv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexGendv(coord, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_gendv)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glGetTexGenfv(coord, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_genfv)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glGetTexGeniv(coord, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_geniv)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glGetTexImage(target, level, format, type, pixels) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_image)(CGL_MACRO_CONTEXT_RENDERER, target, level, format, type, pixels)

#define glGetTexLevelParameterfv(target, level, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_level_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, level, pname, params)

#define glGetTexLevelParameteriv(target, level, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_level_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, level, pname, params)

#define glGetTexParameterfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glHint(target, mode) \
	(*(CGL_MACRO_CONTEXT)->disp.hint)(CGL_MACRO_CONTEXT_RENDERER, target, mode)

#define glIndexMask(mask) \
	(*(CGL_MACRO_CONTEXT)->disp.index_mask)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glIndexPointer(type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.index_pointer)(CGL_MACRO_CONTEXT_RENDERER, type, stride, pointer)

#define glIndexd(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexd)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexdv(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexdv)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexf(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexf)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexfv(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexfv)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexi(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexi)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexiv(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexiv)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexs(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexs)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexsv(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexsv)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexub(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexub)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexubv(c) \
	(*(CGL_MACRO_CONTEXT)->disp.indexubv)(CGL_MACRO_CONTEXT_RENDERER, c)

#define glInitNames() \
	(*(CGL_MACRO_CONTEXT)->disp.init_names)(CGL_MACRO_CONTEXT_RENDERER)

#define glInterleavedArrays(format, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.interleaved_arrays)(CGL_MACRO_CONTEXT_RENDERER, format, stride, pointer)

#define glIsEnabled(cap) \
	(*(CGL_MACRO_CONTEXT)->disp.is_enabled)(CGL_MACRO_CONTEXT_RENDERER, cap)

#define glIsList(list) \
	(*(CGL_MACRO_CONTEXT)->disp.is_list)(CGL_MACRO_CONTEXT_RENDERER, list)

#define glIsTexture(texture) \
	(*(CGL_MACRO_CONTEXT)->disp.is_texture)(CGL_MACRO_CONTEXT_RENDERER, texture)

#define glLightModelf(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.light_modelf)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glLightModelfv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.light_modelfv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glLightModeli(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.light_modeli)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glLightModeliv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.light_modeliv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glLightf(light, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.lightf)(CGL_MACRO_CONTEXT_RENDERER, light, pname, param)

#define glLightfv(light, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.lightfv)(CGL_MACRO_CONTEXT_RENDERER, light, pname, params)

#define glLighti(light, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.lighti)(CGL_MACRO_CONTEXT_RENDERER, light, pname, param)

#define glLightiv(light, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.lightiv)(CGL_MACRO_CONTEXT_RENDERER, light, pname, params)

#define glLineStipple(factor, pattern) \
	(*(CGL_MACRO_CONTEXT)->disp.line_stipple)(CGL_MACRO_CONTEXT_RENDERER, factor, pattern)

#define glLineWidth(width) \
	(*(CGL_MACRO_CONTEXT)->disp.line_width)(CGL_MACRO_CONTEXT_RENDERER, width)

#define glListBase(base) \
	(*(CGL_MACRO_CONTEXT)->disp.list_base)(CGL_MACRO_CONTEXT_RENDERER, base)

#define glLoadIdentity() \
	(*(CGL_MACRO_CONTEXT)->disp.load_identity)(CGL_MACRO_CONTEXT_RENDERER)

#define glLoadMatrixd(m) \
	(*(CGL_MACRO_CONTEXT)->disp.load_matrixd)(CGL_MACRO_CONTEXT_RENDERER, m)

#define glLoadMatrixf(m) \
	(*(CGL_MACRO_CONTEXT)->disp.load_matrixf)(CGL_MACRO_CONTEXT_RENDERER, m)

#define glLoadName(name) \
	(*(CGL_MACRO_CONTEXT)->disp.load_name)(CGL_MACRO_CONTEXT_RENDERER, name)

#define glLogicOp(opcode) \
	(*(CGL_MACRO_CONTEXT)->disp.logic_op)(CGL_MACRO_CONTEXT_RENDERER, opcode)

#define glMap1d(target, u1, u2, stride, order, points) \
	(*(CGL_MACRO_CONTEXT)->disp.map1d)(CGL_MACRO_CONTEXT_RENDERER, target, u1, u2, stride, order, points)

#define glMap1f(target, u1, u2, stride, order, points) \
	(*(CGL_MACRO_CONTEXT)->disp.map1f)(CGL_MACRO_CONTEXT_RENDERER, target, u1, u2, stride, order, points)

#define glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*(CGL_MACRO_CONTEXT)->disp.map2d)(CGL_MACRO_CONTEXT_RENDERER, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*(CGL_MACRO_CONTEXT)->disp.map2f)(CGL_MACRO_CONTEXT_RENDERER, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMapGrid1d(un, u1, u2) \
	(*(CGL_MACRO_CONTEXT)->disp.map_grid1d)(CGL_MACRO_CONTEXT_RENDERER, un, u1, u2)

#define glMapGrid1f(un, u1, u2) \
	(*(CGL_MACRO_CONTEXT)->disp.map_grid1f)(CGL_MACRO_CONTEXT_RENDERER, un, u1, u2)

#define glMapGrid2d(un, u1, u2, vn, v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.map_grid2d)(CGL_MACRO_CONTEXT_RENDERER, un, u1, u2, vn, v1, v2)

#define glMapGrid2f(un, u1, u2, vn, v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.map_grid2f)(CGL_MACRO_CONTEXT_RENDERER, un, u1, u2, vn, v1, v2)

#define glMaterialf(face, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.materialf)(CGL_MACRO_CONTEXT_RENDERER, face, pname, param)

#define glMaterialfv(face, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.materialfv)(CGL_MACRO_CONTEXT_RENDERER, face, pname, params)

#define glMateriali(face, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.materiali)(CGL_MACRO_CONTEXT_RENDERER, face, pname, param)

#define glMaterialiv(face, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.materialiv)(CGL_MACRO_CONTEXT_RENDERER, face, pname, params)

#define glMatrixMode(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.matrix_mode)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glMultMatrixd(m) \
	(*(CGL_MACRO_CONTEXT)->disp.mult_matrixd)(CGL_MACRO_CONTEXT_RENDERER, m)

#define glMultMatrixf(m) \
	(*(CGL_MACRO_CONTEXT)->disp.mult_matrixf)(CGL_MACRO_CONTEXT_RENDERER, m)

#define glNewList(list, mode) \
	(*(CGL_MACRO_CONTEXT)->disp.new_list)(CGL_MACRO_CONTEXT_RENDERER, list, mode)

#define glNormal3b(nx, ny, nz) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3b)(CGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3bv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3bv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glNormal3d(nx, ny, nz) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3d)(CGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glNormal3f(nx, ny, nz) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3f)(CGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glNormal3i(nx, ny, nz) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3i)(CGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glNormal3s(nx, ny, nz) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3s)(CGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.normal3sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glNormalPointer(type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.normal_pointer)(CGL_MACRO_CONTEXT_RENDERER, type, stride, pointer)

#define glOrtho(left, right, bottom, top, zNear, zFar) \
	(*(CGL_MACRO_CONTEXT)->disp.ortho)(CGL_MACRO_CONTEXT_RENDERER, left, right, bottom, top, zNear, zFar)

#define glPassThrough(token) \
	(*(CGL_MACRO_CONTEXT)->disp.pass_through)(CGL_MACRO_CONTEXT_RENDERER, token)

#define glPixelMapfv(map, mapsize, values) \
	(*(CGL_MACRO_CONTEXT)->disp.pixel_mapfv)(CGL_MACRO_CONTEXT_RENDERER, map, mapsize, values)

#define glPixelMapuiv(map, mapsize, values) \
	(*(CGL_MACRO_CONTEXT)->disp.pixel_mapuiv)(CGL_MACRO_CONTEXT_RENDERER, map, mapsize, values)

#define glPixelMapusv(map, mapsize, values) \
	(*(CGL_MACRO_CONTEXT)->disp.pixel_mapusv)(CGL_MACRO_CONTEXT_RENDERER, map, mapsize, values)

#define glPixelStoref(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.pixel_storef)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelStorei(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.pixel_storei)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelTransferf(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.pixel_transferf)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelTransferi(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.pixel_transferi)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelZoom(xfactor, yfactor) \
	(*(CGL_MACRO_CONTEXT)->disp.pixel_zoom)(CGL_MACRO_CONTEXT_RENDERER, xfactor, yfactor)

#define glPointSize(size) \
	(*(CGL_MACRO_CONTEXT)->disp.point_size)(CGL_MACRO_CONTEXT_RENDERER, size)

#define glPolygonMode(face, mode) \
	(*(CGL_MACRO_CONTEXT)->disp.polygon_mode)(CGL_MACRO_CONTEXT_RENDERER, face, mode)

#define glPolygonOffset(factor, units) \
	(*(CGL_MACRO_CONTEXT)->disp.polygon_offset)(CGL_MACRO_CONTEXT_RENDERER, factor, units)

#define glPolygonStipple(mask) \
	(*(CGL_MACRO_CONTEXT)->disp.polygon_stipple)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glPopAttrib() \
	(*(CGL_MACRO_CONTEXT)->disp.pop_attrib)(CGL_MACRO_CONTEXT_RENDERER)

#define glPopClientAttrib() \
	(*(CGL_MACRO_CONTEXT)->disp.pop_client_attrib)(CGL_MACRO_CONTEXT_RENDERER)

#define glPopMatrix() \
	(*(CGL_MACRO_CONTEXT)->disp.pop_matrix)(CGL_MACRO_CONTEXT_RENDERER)

#define glPopName() \
	(*(CGL_MACRO_CONTEXT)->disp.pop_name)(CGL_MACRO_CONTEXT_RENDERER)

#define glPrioritizeTextures(n, textures, priorities) \
	(*(CGL_MACRO_CONTEXT)->disp.prioritize_textures)(CGL_MACRO_CONTEXT_RENDERER, n, textures, priorities)

#define glPushAttrib(mask) \
	(*(CGL_MACRO_CONTEXT)->disp.push_attrib)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glPushClientAttrib(mask) \
	(*(CGL_MACRO_CONTEXT)->disp.push_client_attrib)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glPushMatrix() \
	(*(CGL_MACRO_CONTEXT)->disp.push_matrix)(CGL_MACRO_CONTEXT_RENDERER)

#define glPushName(name) \
	(*(CGL_MACRO_CONTEXT)->disp.push_name)(CGL_MACRO_CONTEXT_RENDERER, name)

#define glRasterPos2d(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos2d)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glRasterPos2dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos2dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos2f(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos2f)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glRasterPos2fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos2fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos2i(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos2i)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glRasterPos2iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos2iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos2s(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos2s)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glRasterPos2sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos2sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos3d(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos3d)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glRasterPos3dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos3dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos3f(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos3f)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glRasterPos3fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos3fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos3i(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos3i)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glRasterPos3iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos3iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos3s(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos3s)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glRasterPos3sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos3sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos4d(x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos4d)(CGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glRasterPos4dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos4dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos4f(x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos4f)(CGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glRasterPos4fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos4fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos4i(x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos4i)(CGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glRasterPos4iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos4iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos4s(x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos4s)(CGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glRasterPos4sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.raster_pos4sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glReadBuffer(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.read_buffer)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glReadPixels(x, y, width, height, format, type, pixels) \
	(*(CGL_MACRO_CONTEXT)->disp.read_pixels)(CGL_MACRO_CONTEXT_RENDERER, x, y, width, height, format, type, pixels)

#define glRectd(x1, y1, x2, y2) \
	(*(CGL_MACRO_CONTEXT)->disp.rectd)(CGL_MACRO_CONTEXT_RENDERER, x1, y1, x2, y2)

#define glRectdv(v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.rectdv)(CGL_MACRO_CONTEXT_RENDERER, v1, v2)

#define glRectf(x1, y1, x2, y2) \
	(*(CGL_MACRO_CONTEXT)->disp.rectf)(CGL_MACRO_CONTEXT_RENDERER, x1, y1, x2, y2)

#define glRectfv(v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.rectfv)(CGL_MACRO_CONTEXT_RENDERER, v1, v2)

#define glRecti(x1, y1, x2, y2) \
	(*(CGL_MACRO_CONTEXT)->disp.recti)(CGL_MACRO_CONTEXT_RENDERER, x1, y1, x2, y2)

#define glRectiv(v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.rectiv)(CGL_MACRO_CONTEXT_RENDERER, v1, v2)

#define glRects(x1, y1, x2, y2) \
	(*(CGL_MACRO_CONTEXT)->disp.rects)(CGL_MACRO_CONTEXT_RENDERER, x1, y1, x2, y2)

#define glRectsv(v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.rectsv)(CGL_MACRO_CONTEXT_RENDERER, v1, v2)

#define glRenderMode(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.render_mode)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glRotated(angle, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.rotated)(CGL_MACRO_CONTEXT_RENDERER, angle, x, y, z)

#define glRotatef(angle, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.rotatef)(CGL_MACRO_CONTEXT_RENDERER, angle, x, y, z)

#define glScaled(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.scaled)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glScalef(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.scalef)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glScissor(x, y, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.scissor)(CGL_MACRO_CONTEXT_RENDERER, x, y, width, height)

#define glSelectBuffer(size, buffer) \
	(*(CGL_MACRO_CONTEXT)->disp.select_buffer)(CGL_MACRO_CONTEXT_RENDERER, size, buffer)

#define glShadeModel(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.shade_model)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glStencilFunc(func, ref, mask) \
	(*(CGL_MACRO_CONTEXT)->disp.stencil_func)(CGL_MACRO_CONTEXT_RENDERER, func, ref, mask)

#define glStencilMask(mask) \
	(*(CGL_MACRO_CONTEXT)->disp.stencil_mask)(CGL_MACRO_CONTEXT_RENDERER, mask)

#define glStencilOp(fail, zfail, zpass) \
	(*(CGL_MACRO_CONTEXT)->disp.stencil_op)(CGL_MACRO_CONTEXT_RENDERER, fail, zfail, zpass)

#define glTexCoord1d(s) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord1d)(CGL_MACRO_CONTEXT_RENDERER, s)

#define glTexCoord1dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord1dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord1f(s) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord1f)(CGL_MACRO_CONTEXT_RENDERER, s)

#define glTexCoord1fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord1fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord1i(s) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord1i)(CGL_MACRO_CONTEXT_RENDERER, s)

#define glTexCoord1iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord1iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord1s(s) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord1s)(CGL_MACRO_CONTEXT_RENDERER, s)

#define glTexCoord1sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord1sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord2d(s, t) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord2d)(CGL_MACRO_CONTEXT_RENDERER, s, t)

#define glTexCoord2dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord2dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord2f(s, t) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord2f)(CGL_MACRO_CONTEXT_RENDERER, s, t)

#define glTexCoord2fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord2fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord2i(s, t) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord2i)(CGL_MACRO_CONTEXT_RENDERER, s, t)

#define glTexCoord2iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord2iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord2s(s, t) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord2s)(CGL_MACRO_CONTEXT_RENDERER, s, t)

#define glTexCoord2sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord2sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord3d(s, t, r) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord3d)(CGL_MACRO_CONTEXT_RENDERER, s, t, r)

#define glTexCoord3dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord3dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord3f(s, t, r) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord3f)(CGL_MACRO_CONTEXT_RENDERER, s, t, r)

#define glTexCoord3fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord3fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord3i(s, t, r) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord3i)(CGL_MACRO_CONTEXT_RENDERER, s, t, r)

#define glTexCoord3iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord3iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord3s(s, t, r) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord3s)(CGL_MACRO_CONTEXT_RENDERER, s, t, r)

#define glTexCoord3sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord3sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord4d(s, t, r, q) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord4d)(CGL_MACRO_CONTEXT_RENDERER, s, t, r, q)

#define glTexCoord4dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord4dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord4f(s, t, r, q) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord4f)(CGL_MACRO_CONTEXT_RENDERER, s, t, r, q)

#define glTexCoord4fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord4fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord4i(s, t, r, q) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord4i)(CGL_MACRO_CONTEXT_RENDERER, s, t, r, q)

#define glTexCoord4iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord4iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord4s(s, t, r, q) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord4s)(CGL_MACRO_CONTEXT_RENDERER, s, t, r, q)

#define glTexCoord4sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord4sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoordPointer(size, type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_coord_pointer)(CGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glTexEnvf(target, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_envf)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexEnvfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_envfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexEnvi(target, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_envi)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexEnviv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_enviv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexGend(coord, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_gend)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, param)

#define glTexGendv(coord, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_gendv)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glTexGenf(coord, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_genf)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, param)

#define glTexGenfv(coord, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_genfv)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glTexGeni(coord, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_geni)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, param)

#define glTexGeniv(coord, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_geniv)(CGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glTexImage1D(target, level, internalformat, width, border, format, type, pixels) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, border, format, type, pixels)

#define glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, border, format, type, pixels)

#define glTexParameterf(target, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_parameterf)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexParameterfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexParameteri(target, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_parameteri)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexSubImage1D(target, level, xoffset, width, format, type, pixels) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_sub_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, width, format, type, pixels)

#define glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_sub_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, width, height, format, type, pixels)

#define glTranslated(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.translated)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glTranslatef(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.translatef)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex2d(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex2d)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glVertex2dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex2dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex2f(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex2f)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glVertex2fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex2fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex2i(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex2i)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glVertex2iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex2iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex2s(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex2s)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glVertex2sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex2sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex3d(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex3d)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex3dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex3dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex3f(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex3f)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex3fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex3fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex3i(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex3i)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex3iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex3iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex3s(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex3s)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex3sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex3sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex4d(x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex4d)(CGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glVertex4dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex4dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex4f(x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex4f)(CGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glVertex4fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex4fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex4i(x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex4i)(CGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glVertex4iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex4iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex4s(x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex4s)(CGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glVertex4sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex4sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glVertexPointer(size, type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_pointer)(CGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glViewport(x, y, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.viewport)(CGL_MACRO_CONTEXT_RENDERER, x, y, width, height)

/****************** OpenGL 1.2 ************************************/

#define glBlendColor(red, green, blue, alpha) \
	(*(CGL_MACRO_CONTEXT)->disp.blend_color)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glBlendEquation(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.blend_equation)(CGL_MACRO_CONTEXT_RENDERER, mode)

#define glDrawRangeElements(mode, start, end, count, type, indices) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_range_elements)(CGL_MACRO_CONTEXT_RENDERER, mode, start, end, count, type, indices)

#define glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, data) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, depth, border, format, type, data)

#define glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_sub_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels)

#define glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_tex_sub_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, x, y, width, height)

/****************** OpenGL 1.2 Imaging Subset *********************/

#define glColorTable(target, internalformat, width, format, type, table) \
	(*(CGL_MACRO_CONTEXT)->disp.color_table)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, format, type, table)

#define glColorTableParameterfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.color_table_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glColorTableParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.color_table_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glCopyColorTable(target, internalformat, x, y, width) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_color_table)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, x, y, width)

#define glGetColorTable(target, format, type, table) \
	(*(CGL_MACRO_CONTEXT)->disp.get_color_table)(CGL_MACRO_CONTEXT_RENDERER, target, format, type, table)

#define glGetColorTableParameterfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_color_table_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetColorTableParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_color_table_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glColorSubTable(target, start, count, format, type, data) \
	(*(CGL_MACRO_CONTEXT)->disp.color_sub_table)(CGL_MACRO_CONTEXT_RENDERER, target, start, count, format, type, data)

#define glCopyColorSubTable(target, start, x, y, width) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_color_sub_table)(CGL_MACRO_CONTEXT_RENDERER, target, start, x, y, width)

#define glConvolutionFilter1D(target, internalformat, width, format, type, image) \
	(*(CGL_MACRO_CONTEXT)->disp.convolution_filter1D)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, format, type, image)

#define glConvolutionFilter2D(target, internalformat, width, height, format, type, image) \
	(*(CGL_MACRO_CONTEXT)->disp.convolution_filter2D)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, height, format, type, image)

#define glConvolutionParameterf(target, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.convolution_parameterf)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glConvolutionParameterfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.convolution_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glConvolutionParameteri(target, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.convolution_parameteri)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glConvolutionParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.convolution_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glCopyConvolutionFilter1D(target, internalformat, x, y, width) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_convolution_filter1D)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, x, y, width)

#define glCopyConvolutionFilter2D(target, internalformat, x, y, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.copy_convolution_filter2D)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, x, y, width, height)

#define glGetConvolutionFilter(target, format, type, image) \
	(*(CGL_MACRO_CONTEXT)->disp.get_convolution_filter)(CGL_MACRO_CONTEXT_RENDERER, target, format, type, image)

#define glGetConvolutionParameterfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_convolution_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetConvolutionParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_convolution_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetSeparableFilter(target, format, type, row, column, span) \
	(*(CGL_MACRO_CONTEXT)->disp.get_separable_filter)(CGL_MACRO_CONTEXT_RENDERER, target, format, type, row, column, span)

#define glSeparableFilter2D(target, internalformat, width, height, format, type, row, column) \
	(*(CGL_MACRO_CONTEXT)->disp.separable_filter2D)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, height, format, type, row, column)

#define glGetHistogram(target, reset, format, type, values) \
	(*(CGL_MACRO_CONTEXT)->disp.get_histogram)(CGL_MACRO_CONTEXT_RENDERER, target, reset, format, type, values)

#define glGetHistogramParameterfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_histogram_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetHistogramParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_histogram_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetMinmax(target, reset, format, type, values) \
	(*(CGL_MACRO_CONTEXT)->disp.get_minmax)(CGL_MACRO_CONTEXT_RENDERER, target, reset, format, type, values)

#define glGetMinmaxParameterfv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_minmax_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetMinmaxParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_minmax_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glHistogram(target, width, internalformat, sink) \
	(*(CGL_MACRO_CONTEXT)->disp.histogram)(CGL_MACRO_CONTEXT_RENDERER, target, width, internalformat, sink)

#define glMinmax(target, internalformat, sink) \
	(*(CGL_MACRO_CONTEXT)->disp.minmax)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, sink)

#define glResetHistogram(target) \
	(*(CGL_MACRO_CONTEXT)->disp.reset_histogram)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glResetMinmax(target) \
	(*(CGL_MACRO_CONTEXT)->disp.reset_minmax)(CGL_MACRO_CONTEXT_RENDERER, target)

/****************** OpenGL 1.3 ************************************/

#define glClientActiveTexture(target) \
	(*(CGL_MACRO_CONTEXT)->disp.client_active_texture)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glActiveTexture(target) \
	(*(CGL_MACRO_CONTEXT)->disp.active_texture)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glMultiTexCoord1d(target, s) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord1d)(CGL_MACRO_CONTEXT_RENDERER, target, s)

#define glMultiTexCoord1dv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord1dv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord1f(target, s) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord1f)(CGL_MACRO_CONTEXT_RENDERER, target, s)

#define glMultiTexCoord1fv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord1fv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord1i(target, s) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord1i)(CGL_MACRO_CONTEXT_RENDERER, target, s)

#define glMultiTexCoord1iv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord1iv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord1s(target, s) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord1s)(CGL_MACRO_CONTEXT_RENDERER, target, s)

#define glMultiTexCoord1sv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord1sv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord2d(target, s, t) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord2d)(CGL_MACRO_CONTEXT_RENDERER, target, s, t)

#define glMultiTexCoord2dv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord2dv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord2f(target, s, t) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord2f)(CGL_MACRO_CONTEXT_RENDERER, target, s, t)

#define glMultiTexCoord2fv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord2fv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord2i(target, s, t) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord2i)(CGL_MACRO_CONTEXT_RENDERER, target, s, t)

#define glMultiTexCoord2iv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord2iv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord2s(target, s, t) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord2s)(CGL_MACRO_CONTEXT_RENDERER, target, s, t)

#define glMultiTexCoord2sv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord2sv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord3d(target, s, t, r) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord3d)(CGL_MACRO_CONTEXT_RENDERER, target, s, t, r)

#define glMultiTexCoord3dv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord3dv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord3f(target, s, t, r) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord3f)(CGL_MACRO_CONTEXT_RENDERER, target, s, t, r)

#define glMultiTexCoord3fv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord3fv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord3i(target, s, t, r) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord3i)(CGL_MACRO_CONTEXT_RENDERER, target, s, t, r)

#define glMultiTexCoord3iv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord3iv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord3s(target, s, t, r) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord3s)(CGL_MACRO_CONTEXT_RENDERER, target, s, t, r)

#define glMultiTexCoord3sv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord3sv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord4d(target, s, t, r, q) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord4d)(CGL_MACRO_CONTEXT_RENDERER, target, s, t, r, q)

#define glMultiTexCoord4dv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord4dv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord4f(target, s, t, r, q) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord4f)(CGL_MACRO_CONTEXT_RENDERER, target, s, t, r, q)

#define glMultiTexCoord4fv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord4fv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord4i(target, s, t, r, q) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord4i)(CGL_MACRO_CONTEXT_RENDERER, target, s, t, r, q)

#define glMultiTexCoord4iv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord4iv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord4s(target, s, t, r, q) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord4s)(CGL_MACRO_CONTEXT_RENDERER, target, s, t, r, q)

#define glMultiTexCoord4sv(target, v) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_tex_coord4sv)(CGL_MACRO_CONTEXT_RENDERER, target, v)

#define glSampleCoverage(value, invert) \
	(*(CGL_MACRO_CONTEXT)->disp.sample_coverage)(CGL_MACRO_CONTEXT_RENDERER, value, invert)

#define glLoadTransposeMatrixf(m) \
	(*(CGL_MACRO_CONTEXT)->disp.load_transpose_matrixf)(CGL_MACRO_CONTEXT_RENDERER, m)

#define glLoadTransposeMatrixd(m) \
	(*(CGL_MACRO_CONTEXT)->disp.load_transpose_matrixd)(CGL_MACRO_CONTEXT_RENDERER, m)

#define glMultTransposeMatrixf(m) \
	(*(CGL_MACRO_CONTEXT)->disp.mult_transpose_matrixf)(CGL_MACRO_CONTEXT_RENDERER, m)

#define glMultTransposeMatrixd(m) \
	(*(CGL_MACRO_CONTEXT)->disp.mult_transpose_matrixd)(CGL_MACRO_CONTEXT_RENDERER, m)

#define glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) \
	(*(CGL_MACRO_CONTEXT)->disp.compressed_tex_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) \
	(*(CGL_MACRO_CONTEXT)->disp.compressed_tex_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) \
	(*(CGL_MACRO_CONTEXT)->disp.compressed_tex_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
	(*(CGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image3D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
	(*(CGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image2D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) \
	(*(CGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image1D)(CGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImage(target, level, img) \
	(*(CGL_MACRO_CONTEXT)->disp.get_compressed_tex_image)(CGL_MACRO_CONTEXT_RENDERER, target, level, img)

/****************** OpenGL 1.4 ************************************/

#define glFogCoordf(coord) \
	(*(CGL_MACRO_CONTEXT)->disp.fog_coordf)(CGL_MACRO_CONTEXT_RENDERER, coord)

#define glFogCoordfv(coord) \
	(*(CGL_MACRO_CONTEXT)->disp.fog_coordfv)(CGL_MACRO_CONTEXT_RENDERER, coord)

#define glFogCoordd(coord) \
	(*(CGL_MACRO_CONTEXT)->disp.fog_coordd)(CGL_MACRO_CONTEXT_RENDERER, coord)

#define glFogCoorddv(coord) \
	(*(CGL_MACRO_CONTEXT)->disp.fog_coorddv)(CGL_MACRO_CONTEXT_RENDERER,coord)

#define glFogCoordPointer(type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.fog_coord_pointer)(CGL_MACRO_CONTEXT_RENDERER, type, stride, pointer)

#define glSecondaryColor3b(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3b)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3bv(components) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3bv)(CGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3d(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3d)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3dv(components) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3dv)(CGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3f(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3f)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3fv(components) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3fv)(CGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3i(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3i)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3iv(components) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3iv)(CGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3s(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3s)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3sv(components) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3sv)(CGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3ub(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3ub)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3ubv(components) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3ubv)(CGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3ui(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3ui)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3uiv(components) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3uiv)(CGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3us(red, green, blue) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3us)(CGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3usv(components) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color3usv)(CGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColorPointer(size, type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.secondary_color_pointer)(CGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glPointParameterf(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.point_parameterf)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPointParameterfv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.point_parameterfv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glPointParameteri(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.point_parameteri)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPointParameteriv(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.point_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha) \
	(*(CGL_MACRO_CONTEXT)->disp.blend_func_separate)(CGL_MACRO_CONTEXT_RENDERER, sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha)

#define glMultiDrawArrays(mode, first, count, primcount) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_draw_arrays)(CGL_MACRO_CONTEXT_RENDERER, mode, first, count, primcount)

#define glMultiDrawElements(mode, count, type, indices, primcount) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_draw_elements)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount)

#define glWindowPos2d(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos2d)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glWindowPos2dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos2dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos2f(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos2f)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glWindowPos2fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos2fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos2i(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos2i)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glWindowPos2iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos2iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos2s(x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos2s)(CGL_MACRO_CONTEXT_RENDERER, x, y)

#define glWindowPos2sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos2sv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos3d(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos3d)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glWindowPos3dv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos3dv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos3f(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos3f)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glWindowPos3fv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos3fv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos3i(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos3i)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glWindowPos3iv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos3iv)(CGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos3s(x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos3s)(CGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glWindowPos3sv(v) \
	(*(CGL_MACRO_CONTEXT)->disp.window_pos3sv)(CGL_MACRO_CONTEXT_RENDERER, v)

/****************** OpenGL 1.5 Macros *****************************/

#define glGenQueries(n, ids) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_queries)(CGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glDeleteQueries(n, ids) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_queries)(CGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glIsQuery(id) \
	(*(CGL_MACRO_CONTEXT)->disp.is_query)(CGL_MACRO_CONTEXT_RENDERER, id)

#define glBeginQuery(target, id) \
	(*(CGL_MACRO_CONTEXT)->disp.begin_query)(CGL_MACRO_CONTEXT_RENDERER, target, id)

#define glEndQuery(target) \
	(*(CGL_MACRO_CONTEXT)->disp.end_query)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glGetQueryiv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_queryiv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetQueryObjectiv(id, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_query_objectiv)(CGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glGetQueryObjectuiv(id, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_query_objectuiv)(CGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glBindBuffer(target, buffer) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_buffer)(CGL_MACRO_CONTEXT_RENDERER, target, buffer)

#define glDeleteBuffers(n, buffers) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_buffers)(CGL_MACRO_CONTEXT_RENDERER, n, buffers)

#define glGenBuffers(n, buffers) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_buffers)(CGL_MACRO_CONTEXT_RENDERER, n, buffers)

#define glIsBuffer(buffer) \
	(*(CGL_MACRO_CONTEXT)->disp.is_buffer)(CGL_MACRO_CONTEXT_RENDERER, buffer)

#define glBufferData(target, size, data, usage) \
	(*(CGL_MACRO_CONTEXT)->disp.buffer_data)(CGL_MACRO_CONTEXT_RENDERER, target, size, data, usage)

#define glBufferSubData(target, offset, size, data) \
	(*(CGL_MACRO_CONTEXT)->disp.buffer_sub_data)(CGL_MACRO_CONTEXT_RENDERER, target, offset, size, data)

#define glGetBufferSubData(target, offset, size, data) \
	(*(CGL_MACRO_CONTEXT)->disp.get_buffer_sub_data)(CGL_MACRO_CONTEXT_RENDERER, target, offset, size, data)

#define glMapBuffer(target, access) \
	(*(CGL_MACRO_CONTEXT)->disp.map_buffer)(CGL_MACRO_CONTEXT_RENDERER, target, access)

#define glUnmapBuffer(target) \
	(*(CGL_MACRO_CONTEXT)->disp.unmap_buffer)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glGetBufferParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_buffer_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetBufferPointerv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_buffer_pointerv)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

/****************** OpenGL 2.0 Macros *****************************/

#define glDrawBuffers(n, bufs) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_buffers_ARB)(CGL_MACRO_CONTEXT_RENDERER, n, bufs)

#define glVertexAttrib1d(index, x) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1dv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib1f(index, x) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1fv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib1s(index, x) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1sv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2d(index, x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2dv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2f(index, x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2fv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2s(index, x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2sv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3d(index, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3dv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3f(index, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3fv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3s(index, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3sv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nbv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nbv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Niv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Niv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nsv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nsv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nub(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nub_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, x, w)

#define glVertexAttrib4Nubv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nubv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nuiv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nuiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nusv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nusv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4bv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4bv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4d(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4dv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4f(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4fv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4iv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4s(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4sv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4ubv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4ubv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4uiv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4uiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4usv(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4usv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribPointer(index, size, type, normalized, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib_pointer_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, size, type, normalized, stride, pointer)

#define glEnableVertexAttribArray(index) \
	(*(CGL_MACRO_CONTEXT)->disp.enable_vertex_attrib_array_ARB)(CGL_MACRO_CONTEXT_RENDERER, index)

#define glDisableVertexAttribArray(index) \
	(*(CGL_MACRO_CONTEXT)->disp.disable_vertex_attrib_array_ARB)(CGL_MACRO_CONTEXT_RENDERER, index)

#define glGetVertexAttribdv(index, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribdv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribfv(index, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribiv(index, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribPointerv(index, pname, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attrib_pointerv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, pointer)

#define glDeleteShader(shader) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(shader))

#define glDetachShader(program, shader) \
	(*(CGL_MACRO_CONTEXT)->disp.detach_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), CGL_HANDLE_ARB(shader))

#define glCreateShader(type) \
	(GLuint)((unsigned long)(*(CGL_MACRO_CONTEXT)->disp.create_shader_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, type))

#define glShaderSource(shader, count, string, length) \
	(*(CGL_MACRO_CONTEXT)->disp.shader_source_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(shader), count, string, length)

#define glCompileShader(shader) \
	(*(CGL_MACRO_CONTEXT)->disp.compile_shader_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(shader))

#define glCreateProgram() \
	(GLuint)((unsigned long)(*(CGL_MACRO_CONTEXT)->disp.create_program_object_ARB)(CGL_MACRO_CONTEXT_RENDERER))

#define glAttachShader(program, shader) \
	(*(CGL_MACRO_CONTEXT)->disp.attach_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), CGL_HANDLE_ARB(shader))

#define glLinkProgram(program) \
	(*(CGL_MACRO_CONTEXT)->disp.link_program_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program))

#define glUseProgram(program) \
	(*(CGL_MACRO_CONTEXT)->disp.use_program_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program))

#define glDeleteProgram(program) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program))

#define glValidateProgram(program) \
	(*(CGL_MACRO_CONTEXT)->disp.validate_program_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program))

#define glUniform1f(location, v0) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2f(location, v0, v1) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3f(location, v0, v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4f(location, v0, v1, v2, v3) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1i(location, v0) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2i(location, v0, v1) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3i(location, v0, v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4i(location, v0, v1, v2, v3) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1fv(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2fv(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3fv(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4fv(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform1iv(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2iv(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3iv(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4iv(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniformMatrix2fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glIsShader(shader) \
	(*(CGL_MACRO_CONTEXT)->disp.is_shader)(CGL_MACRO_CONTEXT_RENDERER, shader)

#define glIsProgram(program) \
	(*(CGL_MACRO_CONTEXT)->disp.is_program)(CGL_MACRO_CONTEXT_RENDERER, program)

#define glGetShaderiv(shader, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_shaderiv)(CGL_MACRO_CONTEXT_RENDERER, shader, pname, params)

#define glGetProgramiv(program, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_programiv)(CGL_MACRO_CONTEXT_RENDERER, program, pname, params)

#define glGetAttachedShaders(program, maxCount, count, shaders) \
	(*(CGL_MACRO_CONTEXT)->disp.get_attached_shaders)(CGL_MACRO_CONTEXT_RENDERER, program, maxCount, count, shaders)

#define glGetShaderInfoLog(shader, bufSize, length, infoLog) \
	(*(CGL_MACRO_CONTEXT)->disp.get_shader_info_log)(CGL_MACRO_CONTEXT_RENDERER, shader, bufSize, length, infoLog)

#define glGetProgramInfoLog(program, bufSize, length, infoLog) \
	(*(CGL_MACRO_CONTEXT)->disp.get_program_info_log)(CGL_MACRO_CONTEXT_RENDERER, program, bufSize, length, infoLog)

#define glGetUniformLocation(program, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniform_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), name)

#define glGetActiveUniform(program, index, bufSize, length, size, type, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_active_uniform_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), index, bufSize, length, size, type, name)

#define glGetUniformfv(program, location, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniformfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), location, params)

#define glGetUniformiv(program, location, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniformiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), location, params)

#define glGetShaderSource(shader, bufSize, length, source) \
	(*(CGL_MACRO_CONTEXT)->disp.get_shader_source_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(shader), bufSize, length, source)

#define glBindAttribLocation(program, index, name) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_attrib_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), index, name)

#define glGetActiveAttrib(program, index, bufSize, length, size, type, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_active_attrib_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), index, bufSize, length, size, type, name)

#define glGetAttribLocation(program, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_attrib_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, CGL_HANDLE_ARB(program), name)

#define glStencilFuncSeparate(face, func, ref, mask) \
	(*(CGL_MACRO_CONTEXT)->disp.stencil_func_separate)(CGL_MACRO_CONTEXT_RENDERER, face, func, ref, mask)

#define glStencilOpSeparate(face, fail, zfail, zpass) \
	(*(CGL_MACRO_CONTEXT)->disp.stencil_op_separate_ATI)(CGL_MACRO_CONTEXT_RENDERER, face, fail, zfail, zpass)

#define glStencilMaskSeparate(face, mask) \
	(*(CGL_MACRO_CONTEXT)->disp.stencil_mask_separate)(CGL_MACRO_CONTEXT_RENDERER, face, mask)

#define glBlendEquationSeparate glBlendEquationSeparateEXT

/****************** OpenGL 2.1 Macros *****************************/

#define glUniformMatrix2x3fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix2x3fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3x2fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix3x2fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix2x4fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix2x4fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4x2fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix4x2fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3x4fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix3x4fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4x3fv(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix4x3fv)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

/****************** OpenGL 3.0 Macros *****************************/

#define glColorMaski glColorMaskIndexedEXT
#define glGetBooleani_v glGetBooleanIndexedvEXT
#define glGetIntegeri_v glGetIntegerIndexedvEXT
#define glEnablei glEnableIndexedEXT
#define glDisablei glDisableIndexedEXT
#define glIsEnabledi glIsEnabledIndexedEXT

#define glBeginTransformFeedback glBeginTransformFeedbackEXT
#define glEndTransformFeedback glEndTransformFeedbackEXT
#define glBindBufferRange glBindBufferRangeEXT
#define glBindBufferBase glBindBufferBaseEXT
#define glTransformFeedbackVaryings glTransformFeedbackVaryingsEXT
#define glGetTransformFeedbackVarying glGetTransformFeedbackVaryingEXT

#define glClampColor glClampColorARB

#define glBeginConditionalRender glBeginConditionalRenderNV
#define glEndConditionalRender glEndConditionalRenderNV

#define glVertexAttribIPointer glVertexAttribIPointerEXT
#define glGetVertexAttribIiv glGetVertexAttribIivEXT
#define glGetVertexAttribIuiv glGetVertexAttribIuivEXT
#define glVertexAttribI1i glVertexAttribI1iEXT
#define glVertexAttribI2i glVertexAttribI2iEXT
#define glVertexAttribI3i glVertexAttribI3iEXT
#define glVertexAttribI4i glVertexAttribI4iEXT
#define glVertexAttribI1ui glVertexAttribI1uiEXT
#define glVertexAttribI2ui glVertexAttribI2uiEXT
#define glVertexAttribI3ui glVertexAttribI3uiEXT
#define glVertexAttribI4ui glVertexAttribI4uiEXT
#define glVertexAttribI1iv glVertexAttribI1ivEXT
#define glVertexAttribI2iv glVertexAttribI2ivEXT
#define glVertexAttribI3iv glVertexAttribI3ivEXT
#define glVertexAttribI4iv glVertexAttribI4ivEXT
#define glVertexAttribI1uiv glVertexAttribI1uivEXT
#define glVertexAttribI2uiv glVertexAttribI2uivEXT
#define glVertexAttribI3uiv glVertexAttribI3uivEXT
#define glVertexAttribI4uiv glVertexAttribI4uivEXT
#define glVertexAttribI4bv glVertexAttribI4bvEXT
#define glVertexAttribI4sv glVertexAttribI4svEXT
#define glVertexAttribI4ubv glVertexAttribI4ubvEXT
#define glVertexAttribI4usv glVertexAttribI4usvEXT
#define glGetUniformuiv glGetUniformuivEXT
#define glBindFragDataLocation glBindFragDataLocationEXT
#define glGetFragDataLocation glGetFragDataLocationEXT
#define glUniform1ui glUniform1uiEXT
#define glUniform2ui glUniform2uiEXT
#define glUniform3ui glUniform3uiEXT
#define glUniform4ui glUniform4uiEXT
#define glUniform1uiv glUniform1uivEXT
#define glUniform2uiv glUniform2uivEXT
#define glUniform3uiv glUniform3uivEXT
#define glUniform4uiv glUniform4uivEXT

#define glTexParameterIiv glTexParameterIivEXT
#define glTexParameterIuiv glTexParameterIuivEXT
#define glGetTexParameterIiv glGetTexParameterIivEXT
#define glGetTexParameterIuiv glGetTexParameterIuivEXT

#define glClearBufferiv(buffer, drawbuffer, value) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_bufferiv)(CGL_MACRO_CONTEXT_RENDERER, buffer, drawbuffer, value)

#define glClearBufferuiv(buffer, drawbuffer, value) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_bufferuiv)(CGL_MACRO_CONTEXT_RENDERER, buffer, drawbuffer, value)

#define glClearBufferfv(buffer, drawbuffer, value) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_bufferfv)(CGL_MACRO_CONTEXT_RENDERER, buffer, drawbuffer, value)

#define glClearBufferfi(buffer, drawbuffer, depth, stencil) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_bufferfi)(CGL_MACRO_CONTEXT_RENDERER, buffer, drawbuffer, depth, stencil)

#define glGetStringi(name, index) \
	(*(CGL_MACRO_CONTEXT)->disp.get_stringi)(CGL_MACRO_CONTEXT_RENDERER, name, index)



/********** ARB Extensions *************************************************/

/* GL_ARB_vertex_program */
#define glBindProgramARB(target, id) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_program_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, id)

#define glDeleteProgramsARB(n, programs) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_programs_ARB)(CGL_MACRO_CONTEXT_RENDERER, n, programs)

#define glGenProgramsARB(n, programs) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_programs_ARB)(CGL_MACRO_CONTEXT_RENDERER, n, programs)

#define glIsProgramARB(id) \
	(*(CGL_MACRO_CONTEXT)->disp.is_program_ARB)(CGL_MACRO_CONTEXT_RENDERER, id)

#define glVertexAttrib1sARB(index, x) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1fARB(index, x) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1dARB(index, x) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib2sARB(index, x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2fARB(index, x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2dARB(index, x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib3sARB(index, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3fARB(index, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3dARB(index, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib4sARB(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4s_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4fARB(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4dARB(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4NubARB(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nub_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib1svARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib1fvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib1dvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib1dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib2svARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib2fvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib2dvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib2dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib3svARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib3fvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib3dvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib3dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4bvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4bv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4ubvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4ubv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4svARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4sv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4usvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4usv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4ivARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4uivARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4uiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4fvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4dvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NbvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nbv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NubvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nubv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NsvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nsv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NusvARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nusv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NivARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Niv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NuivARB(index, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib4Nuiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttribPointerARB(index, size, type, normalized, stride, addr) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib_pointer_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, size, type, normalized, stride, addr)

#define glEnableVertexAttribArrayARB(index) \
	(*(CGL_MACRO_CONTEXT)->disp.enable_vertex_attrib_array_ARB)(CGL_MACRO_CONTEXT_RENDERER, index)

#define glDisableVertexAttribArrayARB(index) \
	(*(CGL_MACRO_CONTEXT)->disp.disable_vertex_attrib_array_ARB)(CGL_MACRO_CONTEXT_RENDERER, index)

#define glGetVertexAttribdvARB(index, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribdv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribfvARB(index, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribivARB(index, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribPointervARB(index, pname, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attrib_pointerv_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname, pointer)

#define glProgramEnvParameter4dARB(target, index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.program_env_parameter4d_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, x, y, z, w)

#define glProgramEnvParameter4dvARB(target, index, params) \
	(*(CGL_MACRO_CONTEXT)->disp.program_env_parameter4dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glProgramEnvParameter4fARB(target, index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.program_env_parameter4f_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, x, y, z, w)

#define glProgramEnvParameter4fvARB(target, index, params) \
	(*(CGL_MACRO_CONTEXT)->disp.program_env_parameter4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glProgramLocalParameter4dARB(target, index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.program_local_parameter4d_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, x, y, z, w)

#define glProgramLocalParameter4dvARB(target, index, params) \
	(*(CGL_MACRO_CONTEXT)->disp.program_local_parameter4dv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glProgramLocalParameter4fARB(target, index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.program_local_parameter4f_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, x, y, z, w)

#define glProgramLocalParameter4fvARB(target, index, params) \
	(*(CGL_MACRO_CONTEXT)->disp.program_local_parameter4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glGetProgramEnvParameterdvARB(target, index, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_program_env_parameterdv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glGetProgramEnvParameterfvARB(target, index, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_program_env_parameterfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glGetProgramLocalParameterdvARB(target, index, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_program_local_parameterdv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glGetProgramLocalParameterfvARB(target, index, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_program_local_parameterfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glProgramStringARB(target, format, length, string) \
	(*(CGL_MACRO_CONTEXT)->disp.program_string_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, format, length, string)

#define glGetProgramStringARB(target, pname, string) \
	(*(CGL_MACRO_CONTEXT)->disp.get_program_string_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, pname, string)

#define glGetProgramivARB(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_programiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

/* GL_EXT_gpu_program_parameters */
#define glProgramEnvParameters4fvEXT(target, index, count, params) \
	(*(CGL_MACRO_CONTEXT)->disp.program_env_parameters4fv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, count, params)

#define glProgramLocalParameters4fvEXT(target, index, count, params) \
	(*(CGL_MACRO_CONTEXT)->disp.program_local_parameters4fv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, count, params)

/* GL_ARB_vertex_blend */
#define glWeightbvARB(size, weights) \
	(*(CGL_MACRO_CONTEXT)->disp.weightbv_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightsvARB(size, weights) \
	(*(CGL_MACRO_CONTEXT)->disp.weightsv_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightivARB(size, weights) \
	(*(CGL_MACRO_CONTEXT)->disp.weightiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightfvARB(size, weights) \
	(*(CGL_MACRO_CONTEXT)->disp.weightfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightdvARB(size, weights) \
	(*(CGL_MACRO_CONTEXT)->disp.weightdv_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightubvARB(size, weights) \
	(*(CGL_MACRO_CONTEXT)->disp.weightubv_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightusvARB(size, weights) \
	(*(CGL_MACRO_CONTEXT)->disp.weightusv_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightuivARB(size, weights) \
	(*(CGL_MACRO_CONTEXT)->disp.weightuiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightPointerARB(size, type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.weight_pointer_ARB)(CGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glVertexBlendARB(count) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_blend_ARB)(CGL_MACRO_CONTEXT_RENDERER, count)

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

/* GL_ARB_occlusion_query */
#define glGenQueriesARB        glGenQueries
#define glDeleteQueriesARB     glDeleteQueries
#define glIsQueryARB           glIsQuery
#define glBeginQueryARB        glBeginQuery
#define glEndQueryARB          glEndQuery
#define glGetQueryivARB        glGetQueryiv
#define glGetQueryObjectivARB  glGetQueryObjectiv
#define glGetQueryObjectuivARB glGetQueryObjectuiv

/* GL_ARB_vertex_buffer_object */
#define glBindBufferARB           glBindBuffer
#define glDeleteBuffersARB        glDeleteBuffers
#define glGenBuffersARB           glGenBuffers
#define glIsBufferARB             glIsBuffer
#define glBufferDataARB           glBufferData
#define glBufferSubDataARB        glBufferSubData
#define glGetBufferSubDataARB     glGetBufferSubData
#define glMapBufferARB            glMapBuffer
#define glUnmapBufferARB          glUnmapBuffer
#define glGetBufferParameterivARB glGetBufferParameteriv
#define glGetBufferPointervARB    glGetBufferPointerv

/* GL_ARB_shader_objects */
#define glDeleteObjectARB(obj) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, obj)

#define glGetHandleARB(pname) \
	(*(CGL_MACRO_CONTEXT)->disp.get_handle_ARB)(CGL_MACRO_CONTEXT_RENDERER, pname)

#define glDetachObjectARB(container, attached) \
	(*(CGL_MACRO_CONTEXT)->disp.detach_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, container, attached)

#define glCreateShaderObjectARB(shader) \
	(*(CGL_MACRO_CONTEXT)->disp.create_shader_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, shader)

#define glShaderSourceARB(shader, count, string, length) \
	(*(CGL_MACRO_CONTEXT)->disp.shader_source_ARB)(CGL_MACRO_CONTEXT_RENDERER, shader, count, string, length)

#define glCompileShaderARB(shader) \
	(*(CGL_MACRO_CONTEXT)->disp.compile_shader_ARB)(CGL_MACRO_CONTEXT_RENDERER, shader)

#define glCreateProgramObjectARB() \
	(*(CGL_MACRO_CONTEXT)->disp.create_program_object_ARB)(CGL_MACRO_CONTEXT_RENDERER)

#define glAttachObjectARB(container, object) \
	(*(CGL_MACRO_CONTEXT)->disp.attach_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, container, object)

#define glLinkProgramARB(program) \
	(*(CGL_MACRO_CONTEXT)->disp.link_program_ARB)(CGL_MACRO_CONTEXT_RENDERER, program)

#define glUseProgramObjectARB(program) \
	(*(CGL_MACRO_CONTEXT)->disp.use_program_object_ARB)(CGL_MACRO_CONTEXT_RENDERER, program)

#define glValidateProgramARB(program) \
	(*(CGL_MACRO_CONTEXT)->disp.validate_program_ARB)(CGL_MACRO_CONTEXT_RENDERER, program)

#define glUniform1fARB(location, v0) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2fARB(location, v0, v1) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3fARB(location, v0, v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4fARB(location, v0, v1, v2, v3) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4f_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1iARB(location, v0) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2iARB(location, v0, v1) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3iARB(location, v0, v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4iARB(location, v0, v1, v2, v3) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4i_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1fvARB(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2fvARB(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3fvARB(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4fvARB(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform1ivARB(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2ivARB(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3ivARB(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4ivARB(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4iv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniformMatrix2fvARB(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix2fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3fvARB(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix3fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4fvARB(location, count, transpose, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_matrix4fv_ARB)(CGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glGetObjectParameterfvARB(obj, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_object_parameterfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, obj, pname, params)

#define glGetObjectParameterivARB(obj, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_object_parameteriv_ARB)(CGL_MACRO_CONTEXT_RENDERER, obj, pname, params)

#define glGetInfoLogARB(obj, max, length, info) \
	(*(CGL_MACRO_CONTEXT)->disp.get_info_log_ARB)(CGL_MACRO_CONTEXT_RENDERER, obj, max, length, info)

#define glGetAttachedObjectsARB(container, max, count, obj) \
	(*(CGL_MACRO_CONTEXT)->disp.get_attached_objects_ARB)(CGL_MACRO_CONTEXT_RENDERER, container, max, count, obj)

#define glGetUniformLocationARB(program, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniform_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, program, name)

#define glGetActiveUniformARB(program, index, max, length, size, type, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_active_uniform_ARB)(CGL_MACRO_CONTEXT_RENDERER, program, index, max, length, size, type, name)

#define glGetUniformfvARB(program, location, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniformfv_ARB)(CGL_MACRO_CONTEXT_RENDERER, program, location, params)

#define glGetUniformivARB(program, location, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniformiv_ARB)(CGL_MACRO_CONTEXT_RENDERER, program, location, params)

#define glGetShaderSourceARB(obj, max, length, source) \
	(*(CGL_MACRO_CONTEXT)->disp.get_shader_source_ARB)(CGL_MACRO_CONTEXT_RENDERER, obj, max, length, source)

/* GL_ARB_vertex_shader */
#define glBindAttribLocationARB(program, index, name) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_attrib_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, program, index, name)

#define glGetActiveAttribARB(program, index, max, length, size, type, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_active_attrib_ARB)(CGL_MACRO_CONTEXT_RENDERER, program, index, max, length, size, type, name)

#define glGetAttribLocationARB(program, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_attrib_location_ARB)(CGL_MACRO_CONTEXT_RENDERER, program, name)

#define glDrawBuffersARB(n, bufs)\
	(*(CGL_MACRO_CONTEXT)->disp.draw_buffers_ARB)(CGL_MACRO_CONTEXT_RENDERER, n, bufs)

/* GL_ARB_color_buffer_float */
#define glClampColorARB(target, clamp)\
	(*(CGL_MACRO_CONTEXT)->disp.clamp_color_ARB)(CGL_MACRO_CONTEXT_RENDERER, target, clamp)

/* GL_ARB_framebuffer_object */
#define glIsRenderbuffer(renderbuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.is_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, renderbuffer)

#define glBindRenderbuffer(target, renderbuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, renderbuffer)

#define glDeleteRenderbuffers(n, renderbuffers) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_renderbuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, renderbuffers)

#define glGenRenderbuffers(n, renderbuffers) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_renderbuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, renderbuffers)

#define glRenderbufferStorage(target, internalformat, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.renderbuffer_storage_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, height)

#define glGetRenderbufferParameteriv(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_renderbuffer_parameteriv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glIsFramebuffer(framebuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.is_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, framebuffer)

#define glBindFramebuffer(target, framebuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, framebuffer)

#define glDeleteFramebuffers(n, framebuffers) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_framebuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, framebuffers)

#define glGenFramebuffers(n, framebuffers) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_framebuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, framebuffers)

#define glCheckFramebufferStatus(target) \
	(*(CGL_MACRO_CONTEXT)->disp.check_framebuffer_status_EXT)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glFramebufferTexture1D(target, attachment, textarget, texture, level) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture1D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level)

#define glFramebufferTexture2D(target, attachment, textarget, texture, level) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture2D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level)

#define glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture3D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level, zoffset)

#define glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, renderbuffertarget, renderbuffer)

#define glGetFramebufferAttachmentParameteriv(target, attachment, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_framebuffer_attachment_parameteriv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, pname, params)

#define glGenerateMipmap(target) \
	(*(CGL_MACRO_CONTEXT)->disp.generate_mipmap_EXT)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) \
	(*(CGL_MACRO_CONTEXT)->disp.blit_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter)

#define glRenderbufferStorageMultisample(target, samples, internalformat, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.renderbuffer_storage_multisample_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, samples, internalformat, width, height)

#define glFramebufferTextureLayer(target, attachment, texture, level, layer) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture_layer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, texture, level, layer)

/* GL_ARB_instanced_arrays */
#define glVertexAttribDivisorARB(index,divisor) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attrib_divisor)(CGL_MACRO_CONTEXT_RENDERER, index, divisor)

/* GL_ARB_draw_instanced */
#define glDrawArraysInstancedARB(mode, first, count, primcount) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_arrays_instanced)(CGL_MACRO_CONTEXT_RENDERER, mode, first, count, primcount)

#define glDrawElementsInstancedARB(mode, count, type, indices, primcount) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_elements_instanced)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount)

/* GL_ARB_draw_elements_base_vertex */
#define glDrawElementsBaseVertex(mode, count, type, indices, basev) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_elements_base_vertex)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, basev)

#define glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basev) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_range_elements_base_vertex)(CGL_MACRO_CONTEXT_RENDERER, mode, start, end, count, type, indices, basev)

#define glDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basev) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_elements_instanced_base_vertex)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount, basev)

#define glMultiDrawElementsBaseVertex(mode, count, type, indices, primcount, basev) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_draw_elements_base_vertex)(CGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount, basev)

/* GL_ARB_sync */
#define glFenceSync(condition, flags) \
	(*(CGL_MACRO_CONTEXT)->disp.fence_sync)(CGL_MACRO_CONTEXT_RENDERER, condition, flags)

#define glIsSync(sync) \
	(*(CGL_MACRO_CONTEXT)->disp.is_sync)(CGL_MACRO_CONTEXT_RENDERER, sync)

#define glDeleteSync(sync) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_sync)(CGL_MACRO_CONTEXT_RENDERER, sync)

#define glClientWaitSync(sync, flags, timeout) \
	(*(CGL_MACRO_CONTEXT)->disp.client_wait_sync)(CGL_MACRO_CONTEXT_RENDERER, sync, flags, timeout)

#define glWaitSync(sync, flags, timeout) \
	(*(CGL_MACRO_CONTEXT)->disp.wait_sync)(CGL_MACRO_CONTEXT_RENDERER, sync, flags, timeout)

#define glGetInteger64v(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_integer64v_sync)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetSynciv(sync, pname, bufSize, length, values) \
	(*(CGL_MACRO_CONTEXT)->disp.get_synciv)(CGL_MACRO_CONTEXT_RENDERER, sync, pname, bufSize, length, values)

/*********** EXT Extensions *************************************************/

/* GL_EXT_stencil_two_side */
#define glActiveStencilFaceEXT(face) \
	(*(CGL_MACRO_CONTEXT)->disp.active_stencil_face_EXT)(CGL_MACRO_CONTEXT_RENDERER, face)

/* GL_EXT_depth_bounds_test */
#define glDepthBoundsEXT(zmin, zmax) \
	(*(CGL_MACRO_CONTEXT)->disp.depth_bounds_EXT)(CGL_MACRO_CONTEXT_RENDERER, zmin, zmax)

/* GL_EXT_blend_equation_separate */
#define glBlendEquationSeparateEXT(modeRGB, modeAlpha) \
	(*(CGL_MACRO_CONTEXT)->disp.blend_equation_separate_EXT)(CGL_MACRO_CONTEXT_RENDERER, modeRGB, modeAlpha)

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

/* GL_EXT_framebuffer_object */
#define glIsRenderbufferEXT(renderbuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.is_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, renderbuffer)

#define glBindRenderbufferEXT(target, renderbuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, renderbuffer)

#define glDeleteRenderbuffersEXT(n, renderbuffers) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_renderbuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, renderbuffers)

#define glGenRenderbuffersEXT(n, renderbuffers) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_renderbuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, renderbuffers)

#define glRenderbufferStorageEXT(target, internalformat, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.renderbuffer_storage_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, height)

#define glGetRenderbufferParameterivEXT(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_renderbuffer_parameteriv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glIsFramebufferEXT(framebuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.is_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, framebuffer)

#define glBindFramebufferEXT(target, framebuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, framebuffer)

#define glDeleteFramebuffersEXT(n, framebuffers) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_framebuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, framebuffers)

#define glGenFramebuffersEXT(n, framebuffers) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_framebuffers_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, framebuffers)

#define glCheckFramebufferStatusEXT(target) \
	(*(CGL_MACRO_CONTEXT)->disp.check_framebuffer_status_EXT)(CGL_MACRO_CONTEXT_RENDERER, target)

#define glFramebufferTexture1DEXT(target, attachment, textarget, texture, level) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture1D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level)

#define glFramebufferTexture2DEXT(target, attachment, textarget, texture, level) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture2D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level)

#define glFramebufferTexture3DEXT(target, attachment, textarget, texture, level, zoffset) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture3D_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level, zoffset)

#define glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_renderbuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, renderbuffertarget, renderbuffer)

#define glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_framebuffer_attachment_parameteriv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, pname, params)

#define glGenerateMipmapEXT(target) \
	(*(CGL_MACRO_CONTEXT)->disp.generate_mipmap_EXT)(CGL_MACRO_CONTEXT_RENDERER, target)

/* EXT_framebuffer_blit and EXT_framebuffer_multisample */
#define glBlitFramebufferEXT(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter) \
	(*(CGL_MACRO_CONTEXT)->disp.blit_framebuffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter)

#define glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height) \
	(*(CGL_MACRO_CONTEXT)->disp.renderbuffer_storage_multisample_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, samples, internalformat, width, height)

/* GL_EXT_geometry_shader4 */
#define glProgramParameteriEXT(program, pname, value) \
	(*(CGL_MACRO_CONTEXT)->disp.program_parameteri_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, pname, value)

#define glFramebufferTextureEXT(target, attachment, texture, level) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, texture, level)

#define glFramebufferTextureLayerEXT(target, attachment, texture, level, layer) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture_layer_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, texture, level, layer)

#define glFramebufferTextureFaceEXT(target, attachment, texture, level, face) \
	(*(CGL_MACRO_CONTEXT)->disp.framebuffer_texture_face_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, attachment, texture, level, face)

/* GL_EXT_transform_feedback */
#define glBindBufferRangeEXT(target, index, buffer, offset, size) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_buffer_range_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, buffer, offset, size)
#define glBindBufferOffsetEXT(target, index, buffer, offset) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_buffer_offset_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, buffer, offset)
#define glBindBufferBaseEXT(target, index, buffer) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_buffer_base_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index, buffer)
#define glBeginTransformFeedbackEXT(primitiveMode) \
	(*(CGL_MACRO_CONTEXT)->disp.begin_transform_feedback_EXT)(CGL_MACRO_CONTEXT_RENDERER, primitiveMode)
#define glEndTransformFeedbackEXT() \
	(*(CGL_MACRO_CONTEXT)->disp.end_transform_feedback_EXT)(CGL_MACRO_CONTEXT_RENDERER)
#define glTransformFeedbackVaryingsEXT(program, count, varyings, bufferMode) \
	(*(CGL_MACRO_CONTEXT)->disp.transform_feedback_varyings_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, count, varyings, bufferMode)
#define glGetTransformFeedbackVaryingEXT(program, index, bufSize, length, size, type, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_transform_feedback_varying_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, index, bufSize, length, size, type, name)

/* GL_EXT_transform_feedback || GL_EXT_draw_buffers2 */
#define glGetIntegerIndexedvEXT(param, index, values) \
	(*(CGL_MACRO_CONTEXT)->disp.get_integer_indexedv_EXT)(CGL_MACRO_CONTEXT_RENDERER, param, index, values)
#define glGetBooleanIndexedvEXT(param, index, values) \
	(*(CGL_MACRO_CONTEXT)->disp.get_boolean_indexedv_EXT)(CGL_MACRO_CONTEXT_RENDERER, param, index, values)

/* GL_EXT_bindable_uniform */
#define glUniformBufferEXT(program, location, buffer) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform_buffer_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, location, buffer)
#define glGetUniformBufferSizeEXT(program, location) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniform_buffer_size_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, location)
#define glGetUniformOffsetEXT(program, location) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniform_buffer_offset_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, location)

/* GL_EXT_texture_integer */
#define glClearColorIiEXT(r, g, b, a) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_colorIi_EXT)(CGL_MACRO_CONTEXT_RENDERER, r, g, b, a)
#define glClearColorIuiEXT(r, g, b, a) \
	(*(CGL_MACRO_CONTEXT)->disp.clear_colorIui_EXT)(CGL_MACRO_CONTEXT_RENDERER, r, g, b, a)
#define glTexParameterIivEXT(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_parameterIiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)
#define glTexParameterIuivEXT(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.tex_parameterIuiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)
#define glGetTexParameterIivEXT(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_parameterIiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)
#define glGetTexParameterIuivEXT(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_parameterIuiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

/* GL_EXT_gpu_shader4 */
#define glVertexAttribI1iEXT(index, x) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI1i_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x)
#define glVertexAttribI2iEXT(index, x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI2i_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)
#define glVertexAttribI3iEXT(index, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI3i_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)
#define glVertexAttribI4iEXT(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4i_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)
#define glVertexAttribI1uiEXT(index, x) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI1ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x)
#define glVertexAttribI2uiEXT(index, x, y) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI2ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y)
#define glVertexAttribI3uiEXT(index, x, y, z) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI3ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z)
#define glVertexAttribI4uiEXT(index, x, y, z, w) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)
#define glVertexAttribI1ivEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI1iv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI2ivEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI2iv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI3ivEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI3iv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI4ivEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4iv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI1uivEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI1uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI2uivEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI2uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI3uivEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI3uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI4uivEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI4bvEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4bv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI4svEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4sv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI4ubvEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4ubv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribI4usvEXT(index, v) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI4usv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, v)
#define glVertexAttribIPointerEXT(index, size, type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_attribI_pointer_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, size, type, stride, pointer)
#define glGetVertexAttribIivEXT(index, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribIiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)
#define glGetVertexAttribIuivEXT(index, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_vertex_attribIuiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, pname, params)
#define glUniform1uiEXT(location, v0) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, v0)
#define glUniform2uiEXT(location, v0, v1) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1)
#define glUniform3uiEXT(location, v0, v1, v2) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)
#define glUniform4uiEXT(location, v0, v1, v2, v3) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4ui_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)
#define glUniform1uivEXT(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform1uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)
#define glUniform2uivEXT(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform2uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)
#define glUniform3uivEXT(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform3uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)
#define glUniform4uivEXT(location, count, value) \
	(*(CGL_MACRO_CONTEXT)->disp.uniform4uiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, location, count, value)
#define glGetUniformuivEXT(program, location, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_uniformuiv_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, location, params)
#define glBindFragDataLocationEXT(program, colorNumber, name) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_frag_data_location_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, colorNumber, name)
#define glGetFragDataLocationEXT(program, name) \
	(*(CGL_MACRO_CONTEXT)->disp.get_frag_data_location_EXT)(CGL_MACRO_CONTEXT_RENDERER, program, name)

/* GL_EXT_draw_buffers2 */
#define glColorMaskIndexedEXT(index, r, g, b, a) \
	(*(CGL_MACRO_CONTEXT)->disp.color_mask_indexed_EXT)(CGL_MACRO_CONTEXT_RENDERER, index, r, g, b, a)
#define glEnableIndexedEXT(target, index) \
	(*(CGL_MACRO_CONTEXT)->disp.enable_indexed_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index)
#define glDisableIndexedEXT(target, index) \
	(*(CGL_MACRO_CONTEXT)->disp.disable_indexed_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index)
#define glIsEnabledIndexedEXT(target, index) \
	(*(CGL_MACRO_CONTEXT)->disp.is_enabled_indexed_EXT)(CGL_MACRO_CONTEXT_RENDERER, target, index)

/* GL_ARB_provoking_vertex */
#define glProvokingVertex(mode) \
	(*(CGL_MACRO_CONTEXT)->disp.provoking_vertex_EXT)(CGL_MACRO_CONTEXT_RENDERER, mode)

/* GL_EXT_provoking_vertex */
#define glProvokingVertexEXT glProvokingVertex

/* GL_EXT_timer_query */
#define glGetQueryObjecti64vEXT(id, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_query_objecti64v)(CGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glGetQueryObjectui64vEXT(id, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_query_objectui64v)(CGL_MACRO_CONTEXT_RENDERER, id, pname, params)

/* GL_EXT_debug_label */
#define glLabelObjectEXT(type, object, length, label) \
	(*(CGL_MACRO_CONTEXT)->disp.label_object_EXT)(CGL_MACRO_CONTEXT_RENDERER, type, object, length, label)

#define glGetObjectLabelEXT(type, object, bufSize, length, label) \
	(*(CGL_MACRO_CONTEXT)->disp.get_object_label_EXT)(CGL_MACRO_CONTEXT_RENDERER, type, object, bufSize, length, label)

/* GL_EXT_debug_marker */
#define glInsertEventMarkerEXT(length, marker) \
	(*(CGL_MACRO_CONTEXT)->disp.insert_event_marker_EXT)(CGL_MACRO_CONTEXT_RENDERER, length, marker)

#define glPushGroupMarkerEXT(length, marker) \
	(*(CGL_MACRO_CONTEXT)->disp.push_group_marker_EXT)(CGL_MACRO_CONTEXT_RENDERER, length, marker)

#define glPopGroupMarkerEXT() \
	(*(CGL_MACRO_CONTEXT)->disp.pop_group_marker_EXT)(CGL_MACRO_CONTEXT_RENDERER)

/*********** APPLE Extensions ***********************************************/

/* GL_APPLE_vertex_program_evaluators */
#define glEnableVertexAttribAPPLE(index, pname) \
	(*(CGL_MACRO_CONTEXT)->disp.enable_vertex_attrib_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname)

#define glDisableVertexAttribAPPLE(index, pname) \
	(*(CGL_MACRO_CONTEXT)->disp.disable_vertex_attrib_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname)

#define glIsVertexAttribEnabledAPPLE(index, pname) \
	(*(CGL_MACRO_CONTEXT)->disp.is_vertex_attrib_enabled_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, pname)

#define glMapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points) \
	(*(CGL_MACRO_CONTEXT)->disp.map_vertex_attrib1d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, size, u1, u2, stride, order, points)

#define glMapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points) \
	(*(CGL_MACRO_CONTEXT)->disp.map_vertex_attrib1f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, size, u1, u2, stride, order, points)

#define glMapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*(CGL_MACRO_CONTEXT)->disp.map_vertex_attrib2d_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*(CGL_MACRO_CONTEXT)->disp.map_vertex_attrib2f_ARB)(CGL_MACRO_CONTEXT_RENDERER, index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

/* GL_APPLE_texture_range */
#define glTextureRangeAPPLE(target, length, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.texture_range_APPLE)(CGL_MACRO_CONTEXT_RENDERER, target, length, pointer)

#define glGetTexParameterPointervAPPLE(target, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_tex_parameter_pointerv_APPLE)(CGL_MACRO_CONTEXT_RENDERER, target, pname, params)

/* GL_APPLE_fence */
#define glGenFencesAPPLE(n, fences) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_fences_APPLE)(CGL_MACRO_CONTEXT_RENDERER, n, fences)

#define glDeleteFencesAPPLE(n, fences) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_fences_APPLE)(CGL_MACRO_CONTEXT_RENDERER, n, fences)

#define glSetFenceAPPLE(fence) \
	(*(CGL_MACRO_CONTEXT)->disp.set_fence_APPLE)(CGL_MACRO_CONTEXT_RENDERER, fence)

#define glIsFenceAPPLE(fence) \
	(*(CGL_MACRO_CONTEXT)->disp.is_fence_APPLE)(CGL_MACRO_CONTEXT_RENDERER, fence)

#define glTestFenceAPPLE(fence) \
	(*(CGL_MACRO_CONTEXT)->disp.test_fence_APPLE)(CGL_MACRO_CONTEXT_RENDERER, fence)

#define glFinishFenceAPPLE(fence) \
	(*(CGL_MACRO_CONTEXT)->disp.finish_fence_APPLE)(CGL_MACRO_CONTEXT_RENDERER, fence)

#define glTestObjectAPPLE(object, name) \
	(*(CGL_MACRO_CONTEXT)->disp.test_object_APPLE)(CGL_MACRO_CONTEXT_RENDERER, object, name)

#define glFinishObjectAPPLE(object, name) \
	(*(CGL_MACRO_CONTEXT)->disp.finish_object_APPLE)(CGL_MACRO_CONTEXT_RENDERER, object, name)

/* GL_APPLE_vertex_array_range */
#define glVertexArrayRangeAPPLE(length, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_array_range_EXT)(CGL_MACRO_CONTEXT_RENDERER, length, pointer)

#define glFlushVertexArrayRangeAPPLE(length, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.flush_vertex_array_range_EXT)(CGL_MACRO_CONTEXT_RENDERER, length, pointer)

#define glVertexArrayParameteriAPPLE(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_array_parameteri_EXT)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

/* GL_APPLE_vertex_array_object */
#define glBindVertexArrayAPPLE(id) \
	(*(CGL_MACRO_CONTEXT)->disp.bind_vertex_array_EXT)(CGL_MACRO_CONTEXT_RENDERER, id)

#define glDeleteVertexArraysAPPLE(n, ids) \
	(*(CGL_MACRO_CONTEXT)->disp.delete_vertex_arrays_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glGenVertexArraysAPPLE(n, ids) \
	(*(CGL_MACRO_CONTEXT)->disp.gen_vertex_arrays_EXT)(CGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glIsVertexArrayAPPLE(id) \
	(*(CGL_MACRO_CONTEXT)->disp.is_vertex_array_EXT)(CGL_MACRO_CONTEXT_RENDERER, id)

/* GL_APPLE_element_array */
#define glElementPointerAPPLE(type, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.element_pointer_APPLE)(CGL_MACRO_CONTEXT_RENDERER, type, pointer)

#define glDrawElementArrayAPPLE(mode, first, count) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_element_array_APPLE)(CGL_MACRO_CONTEXT_RENDERER, mode, first, count)

#define glDrawRangeElementArrayAPPLE(mode, start, end, first, count) \
	(*(CGL_MACRO_CONTEXT)->disp.draw_range_element_array_APPLE)(CGL_MACRO_CONTEXT_RENDERER, mode, start, end, first, count)

#define glMultiDrawElementArrayAPPLE(mode, first, count, primcount) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_draw_element_array_APPLE)(CGL_MACRO_CONTEXT_RENDERER, mode, first, count, primcount)

#define glMultiDrawRangeElementArrayAPPLE(mode, start, end, first, count, primcount) \
	(*(CGL_MACRO_CONTEXT)->disp.multi_draw_range_element_array_APPLE)(CGL_MACRO_CONTEXT_RENDERER, mode, start, end, first, count, primcount)

/* GL_APPLE_flush_render */
#define glFlushRenderAPPLE() \
	(*(CGL_MACRO_CONTEXT)->disp.flush_render_APPLE)(CGL_MACRO_CONTEXT_RENDERER)

#define glFinishRenderAPPLE() \
	(*(CGL_MACRO_CONTEXT)->disp.finish_render_APPLE)(CGL_MACRO_CONTEXT_RENDERER)

#define glSwapAPPLE() \
	(*(CGL_MACRO_CONTEXT)->disp.swap_APPLE)(CGL_MACRO_CONTEXT_RENDERER)

/* GL_APPLE_flush_buffer_range */
#define glBufferParameteriAPPLE(target, pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.buffer_parameteri_APPLE)(CGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glFlushMappedBufferRangeAPPLE(target, offset, size) \
	(*(CGL_MACRO_CONTEXT)->disp.flush_mapped_buffer_range_APPLE)(CGL_MACRO_CONTEXT_RENDERER, target, offset, size)

/* GL_APPLE_object_purgeability */
#define glObjectPurgeableAPPLE(objectType, name, option) \
	(*(CGL_MACRO_CONTEXT)->disp.object_purgeable_APPLE)(CGL_MACRO_CONTEXT_RENDERER, objectType, name, option)

#define glObjectUnpurgeableAPPLE(objectType, name, option) \
	(*(CGL_MACRO_CONTEXT)->disp.object_unpurgeable_APPLE)(CGL_MACRO_CONTEXT_RENDERER, objectType, name, option)

#define glGetObjectParameterivAPPLE(objectType, name, pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.get_object_parameteriv_APPLE)(CGL_MACRO_CONTEXT_RENDERER, objectType, name, pname, params)

/* GL_APPLE_vertex_point_size */
#define glPointSizePointerAPPLE(type, stride, pointer) \
	(*(CGL_MACRO_CONTEXT)->disp.point_size_pointer)(CGL_MACRO_CONTEXT_RENDERER, type, stride, pointer)

#define glVertexPointSizefAPPLE(size) \
	(*(CGL_MACRO_CONTEXT)->disp.vertex_point_sizef_APPLE)(CGL_MACRO_CONTEXT_RENDERER, size)

/*********** ATI Extensions *************************************************/

/* GL_ATI_separate_stencil */
#define glStencilOpSeparateATI(face, sfail, dpfail, dppass) \
	(*(CGL_MACRO_CONTEXT)->disp.stencil_op_separate_ATI)(CGL_MACRO_CONTEXT_RENDERER, face, sfail, dpfail, dppass)

#define glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask) \
	(*(CGL_MACRO_CONTEXT)->disp.stencil_func_separate_ATI)(CGL_MACRO_CONTEXT_RENDERER, frontfunc, backfunc, ref, mask)

/* GL_ATI_blend_equation_separate */
#define glBlendEquationSeparateATI glBlendEquationSeparateEXT

/*********** NVIDIA Extensions **********************************************/

/* GL_NV_point_sprite */
#define glPointParameteriNV(pname, param) \
	(*(CGL_MACRO_CONTEXT)->disp.point_parameteri)(CGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPointParameterivNV(pname, params) \
	(*(CGL_MACRO_CONTEXT)->disp.point_parameteriv)(CGL_MACRO_CONTEXT_RENDERER, pname, params)

/* GL_NV_conditional_render */
#define glBeginConditionalRenderNV(id, mode) \
	(*(CGL_MACRO_CONTEXT)->disp.begin_conditional_render_NV)(CGL_MACRO_CONTEXT_RENDERER, id, mode)

#define glEndConditionalRenderNV() \
	(*(CGL_MACRO_CONTEXT)->disp.end_conditional_render_NV)(CGL_MACRO_CONTEXT_RENDERER)

/* GL_NV_texture_barrier */
#define glTextureBarrierNV() \
	(*(CGL_MACRO_CONTEXT)->disp.texture_barrier_NV)(CGL_MACRO_CONTEXT_RENDERER)

#endif /* _CGLMACRO_H */

