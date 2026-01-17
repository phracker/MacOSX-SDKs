/*
    File:	AGL/aglMacro.h

    Contains:	Macros that replace OpenGL function calls when you use the internal renderer interface.

    Version:	Technology:	Mac OS X
                Release:	GM
 
     Copyright: (c) 2000-2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _AGLMACRO_H
#define _AGLMACRO_H

#include "aglContext.h"

/* Macro context name (AGLContext) */
#if !defined(AGL_MACRO_CONTEXT)
#define AGL_MACRO_CONTEXT agl_ctx
#endif

/* Macro renderer name (GLIContext) */
#if !defined(AGL_MACRO_RENDERER)
#define AGL_MACRO_RENDERER agl_rend
#endif

#define AGL_MACRO_DECLARE_CONTEXT()  AGLContext AGL_MACRO_CONTEXT = aglGetCurrentContext();

/* Repeated renderer lookups may be avoided by defining AGL_MACRO_CACHE_RENDERER before including aglMacro.h.
   Note: If you change the value of AGL_MACRO_CONTEXT partway through a function, you will have to
   keep AGL_MACRO_RENDERER up to date with with it's context. */
#if defined(AGL_MACRO_CACHE_RENDERER)
#define AGL_MACRO_DECLARE_RENDERER()  GLIContext AGL_MACRO_RENDERER = AGL_MACRO_CONTEXT->rend;
#define AGL_MACRO_CONTEXT_RENDERER  AGL_MACRO_RENDERER
#else
#define AGL_MACRO_DECLARE_RENDERER()
#define AGL_MACRO_CONTEXT_RENDERER  AGL_MACRO_CONTEXT->rend
#endif

/* Use the following function macro to declare the local aglMacro variables */
#define AGL_MACRO_DECLARE_VARIABLES() \
    AGL_MACRO_DECLARE_CONTEXT(); \
    AGL_MACRO_DECLARE_RENDERER();

/****************** OpenGL 1.1 Macros *****************************/

#define glAccum(op, value) \
	(*(AGL_MACRO_CONTEXT)->disp.accum)(AGL_MACRO_CONTEXT_RENDERER, op, value)

#define glAlphaFunc(func, ref) \
	(*(AGL_MACRO_CONTEXT)->disp.alpha_func)(AGL_MACRO_CONTEXT_RENDERER, func, ref)

#define glAreTexturesResident(n, textures, residences) \
	(*(AGL_MACRO_CONTEXT)->disp.are_textures_resident)(AGL_MACRO_CONTEXT_RENDERER, n, textures, residences)

#define glArrayElement(i) \
	(*(AGL_MACRO_CONTEXT)->disp.array_element)(AGL_MACRO_CONTEXT_RENDERER, i)

#define glBegin(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.begin)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glBindTexture(target, texture) \
	(*(AGL_MACRO_CONTEXT)->disp.bind_texture)(AGL_MACRO_CONTEXT_RENDERER, target, texture)

#define glBitmap(width, height, xorig, yorig, xmove, ymove, bmap) \
	(*(AGL_MACRO_CONTEXT)->disp.bitmap)(AGL_MACRO_CONTEXT_RENDERER, width, height, xorig, yorig, xmove, ymove, bmap)

#define glBlendFunc(sfactor, dfactor) \
	(*(AGL_MACRO_CONTEXT)->disp.blend_func)(AGL_MACRO_CONTEXT_RENDERER, sfactor, dfactor)

#define glCallList(list) \
	(*(AGL_MACRO_CONTEXT)->disp.call_list)(AGL_MACRO_CONTEXT_RENDERER, list)

#define glCallLists(n, type, lists) \
	(*(AGL_MACRO_CONTEXT)->disp.call_lists)(AGL_MACRO_CONTEXT_RENDERER, n, type, lists)

#define glClear(mask) \
	(*(AGL_MACRO_CONTEXT)->disp.clear)(AGL_MACRO_CONTEXT_RENDERER, mask)

#define glClearAccum(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.clear_accum)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glClearColor(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.clear_color)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glClearDepth(depth) \
	(*(AGL_MACRO_CONTEXT)->disp.clear_depth)(AGL_MACRO_CONTEXT_RENDERER, depth)

#define glClearIndex(c) \
	(*(AGL_MACRO_CONTEXT)->disp.clear_index)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glClearStencil(s) \
	(*(AGL_MACRO_CONTEXT)->disp.clear_stencil)(AGL_MACRO_CONTEXT_RENDERER, s)

#define glClipPlane(plane, equation) \
	(*(AGL_MACRO_CONTEXT)->disp.clip_plane)(AGL_MACRO_CONTEXT_RENDERER, plane, equation)

#define glColor3b(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.color3b)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3bv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color3bv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3d(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.color3d)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color3dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3f(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.color3f)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color3fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3i(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.color3i)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color3iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3s(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.color3s)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color3sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3ub(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.color3ub)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3ubv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color3ubv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3ui(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.color3ui)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3uiv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color3uiv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor3us(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.color3us)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glColor3usv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color3usv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4b(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color4b)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4bv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color4bv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4d(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color4d)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color4dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4f(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color4f)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color4fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4i(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color4i)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color4iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4s(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color4s)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color4sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4ub(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color4ub)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4ubv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color4ubv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4ui(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color4ui)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4uiv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color4uiv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColor4us(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color4us)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColor4usv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.color4usv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glColorMask(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.color_mask)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glColorMaterial(face, mode) \
	(*(AGL_MACRO_CONTEXT)->disp.color_material)(AGL_MACRO_CONTEXT_RENDERER, face, mode)

#define glColorPointer(size, type, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.color_pointer)(AGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glCopyPixels(x, y, width, height, type) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_pixels)(AGL_MACRO_CONTEXT_RENDERER, x, y, width, height, type)

#define glCopyTexImage1D(target, level, internalFormat, x, y, width, border) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_tex_image1D)(AGL_MACRO_CONTEXT_RENDERER, target, level, internalFormat, x, y, width, border)

#define glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_tex_image2D)(AGL_MACRO_CONTEXT_RENDERER, target, level, internalFormat, x, y, width, height, border)

#define glCopyTexSubImage1D(target, level, xoffset, x, y, width) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_tex_sub_image1D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, x, y, width)

#define glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_tex_sub_image2D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, x, y, width, height)

#define glCullFace(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.cull_face)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glDeleteLists(list, range) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_lists)(AGL_MACRO_CONTEXT_RENDERER, list, range)

#define glDeleteTextures(n, textures) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_textures)(AGL_MACRO_CONTEXT_RENDERER, n, textures)

#define glDepthFunc(func) \
	(*(AGL_MACRO_CONTEXT)->disp.depth_func)(AGL_MACRO_CONTEXT_RENDERER, func)

#define glDepthMask(flag) \
	(*(AGL_MACRO_CONTEXT)->disp.depth_mask)(AGL_MACRO_CONTEXT_RENDERER, flag)

#define glDepthRange(zNear, zFar) \
	(*(AGL_MACRO_CONTEXT)->disp.depth_range)(AGL_MACRO_CONTEXT_RENDERER, zNear, zFar)

#define glDisable(cap) \
	(*(AGL_MACRO_CONTEXT)->disp.disable)(AGL_MACRO_CONTEXT_RENDERER, cap)

#define glDisableClientState(array) \
	(*(AGL_MACRO_CONTEXT)->disp.disable_client_state)(AGL_MACRO_CONTEXT_RENDERER, array)

#define glDrawArrays(mode, first, count) \
	(*(AGL_MACRO_CONTEXT)->disp.draw_arrays)(AGL_MACRO_CONTEXT_RENDERER, mode, first, count)

#define glDrawBuffer(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.draw_buffer)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glDrawElements(mode, count, type, indices) \
	(*(AGL_MACRO_CONTEXT)->disp.draw_elements)(AGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices)

#define glDrawPixels(width, height, format, type, pixels) \
	(*(AGL_MACRO_CONTEXT)->disp.draw_pixels)(AGL_MACRO_CONTEXT_RENDERER, width, height, format, type, pixels)

#define glEdgeFlag(flag) \
	(*(AGL_MACRO_CONTEXT)->disp.edge_flag)(AGL_MACRO_CONTEXT_RENDERER, flag)

#define glEdgeFlagPointer(stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.edge_flag_pointer)(AGL_MACRO_CONTEXT_RENDERER, stride, pointer)

#define glEdgeFlagv(flag) \
	(*(AGL_MACRO_CONTEXT)->disp.edge_flagv)(AGL_MACRO_CONTEXT_RENDERER, flag)

#define glEnable(cap) \
	(*(AGL_MACRO_CONTEXT)->disp.enable)(AGL_MACRO_CONTEXT_RENDERER, cap)

#define glEnableClientState(array) \
	(*(AGL_MACRO_CONTEXT)->disp.enable_client_state)(AGL_MACRO_CONTEXT_RENDERER, array)

#define glEnd() \
	(*(AGL_MACRO_CONTEXT)->disp.end)(AGL_MACRO_CONTEXT_RENDERER)

#define glEndList() \
	(*(AGL_MACRO_CONTEXT)->disp.end_list)(AGL_MACRO_CONTEXT_RENDERER)

#define glEvalCoord1d(u) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_coord1d)(AGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord1dv(u) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_coord1dv)(AGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord1f(u) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_coord1f)(AGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord1fv(u) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_coord1fv)(AGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord2d(u, v) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_coord2d)(AGL_MACRO_CONTEXT_RENDERER, u, v)

#define glEvalCoord2dv(u) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_coord2dv)(AGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalCoord2f(u, v) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_coord2f)(AGL_MACRO_CONTEXT_RENDERER, u, v)

#define glEvalCoord2fv(u) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_coord2fv)(AGL_MACRO_CONTEXT_RENDERER, u)

#define glEvalMesh1(mode, i1, i2) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_mesh1)(AGL_MACRO_CONTEXT_RENDERER, mode, i1, i2)

#define glEvalMesh2(mode, i1, i2, j1, j2) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_mesh2)(AGL_MACRO_CONTEXT_RENDERER, mode, i1, i2, j1, j2)

#define glEvalPoint1(i) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_point1)(AGL_MACRO_CONTEXT_RENDERER, i)

#define glEvalPoint2(i, j) \
	(*(AGL_MACRO_CONTEXT)->disp.eval_point2)(AGL_MACRO_CONTEXT_RENDERER, i, j)

#define glFeedbackBuffer(size, type, buffer) \
	(*(AGL_MACRO_CONTEXT)->disp.feedback_buffer)(AGL_MACRO_CONTEXT_RENDERER, size, type, buffer)

#define glFinish() \
	(*(AGL_MACRO_CONTEXT)->disp.finish)(AGL_MACRO_CONTEXT_RENDERER)

#define glFlush() \
	(*(AGL_MACRO_CONTEXT)->disp.flush)(AGL_MACRO_CONTEXT_RENDERER)

#define glFogf(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.fogf)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glFogfv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.fogfv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glFogi(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.fogi)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glFogiv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.fogiv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glFrontFace(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.front_face)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glFrustum(left, right, bottom, top, zNear, zFar) \
	(*(AGL_MACRO_CONTEXT)->disp.frustum)(AGL_MACRO_CONTEXT_RENDERER, left, right, bottom, top, zNear, zFar)

#define glGenLists(range) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_lists)(AGL_MACRO_CONTEXT_RENDERER, range)

#define glGenTextures(n, textures) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_textures)(AGL_MACRO_CONTEXT_RENDERER, n, textures)

#define glGetBooleanv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_booleanv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetClipPlane(plane, equation) \
	(*(AGL_MACRO_CONTEXT)->disp.get_clip_plane)(AGL_MACRO_CONTEXT_RENDERER, plane, equation)

#define glGetDoublev(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_doublev)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetError() \
	(*(AGL_MACRO_CONTEXT)->disp.get_error)(AGL_MACRO_CONTEXT_RENDERER)

#define glGetFloatv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_floatv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetIntegerv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_integerv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetLightfv(light, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_lightfv)(AGL_MACRO_CONTEXT_RENDERER, light, pname, params)

#define glGetLightiv(light, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_lightiv)(AGL_MACRO_CONTEXT_RENDERER, light, pname, params)

#define glGetMapdv(target, query, v) \
	(*(AGL_MACRO_CONTEXT)->disp.get_mapdv)(AGL_MACRO_CONTEXT_RENDERER, target, query, v)

#define glGetMapfv(target, query, v) \
	(*(AGL_MACRO_CONTEXT)->disp.get_mapfv)(AGL_MACRO_CONTEXT_RENDERER, target, query, v)

#define glGetMapiv(target, query, v) \
	(*(AGL_MACRO_CONTEXT)->disp.get_mapiv)(AGL_MACRO_CONTEXT_RENDERER, target, query, v)

#define glGetMaterialfv(face, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_materialfv)(AGL_MACRO_CONTEXT_RENDERER, face, pname, params)

#define glGetMaterialiv(face, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_materialiv)(AGL_MACRO_CONTEXT_RENDERER, face, pname, params)

#define glGetPixelMapfv(map, values) \
	(*(AGL_MACRO_CONTEXT)->disp.get_pixel_mapfv)(AGL_MACRO_CONTEXT_RENDERER, map, values)

#define glGetPixelMapuiv(map, values) \
	(*(AGL_MACRO_CONTEXT)->disp.get_pixel_mapuiv)(AGL_MACRO_CONTEXT_RENDERER, map, values)

#define glGetPixelMapusv(map, values) \
	(*(AGL_MACRO_CONTEXT)->disp.get_pixel_mapusv)(AGL_MACRO_CONTEXT_RENDERER, map, values)

#define glGetPointerv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_pointerv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glGetPolygonStipple(mask) \
	(*(AGL_MACRO_CONTEXT)->disp.get_polygon_stipple)(AGL_MACRO_CONTEXT_RENDERER, mask)

#define glGetString(name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_string)(AGL_MACRO_CONTEXT_RENDERER, name)

#define glGetTexEnvfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_envfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexEnviv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_enviv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexGendv(coord, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_gendv)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glGetTexGenfv(coord, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_genfv)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glGetTexGeniv(coord, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_geniv)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glGetTexImage(target, level, format, type, pixels) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_image)(AGL_MACRO_CONTEXT_RENDERER, target, level, format, type, pixels)

#define glGetTexLevelParameterfv(target, level, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_level_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, level, pname, params)

#define glGetTexLevelParameteriv(target, level, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_level_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, level, pname, params)

#define glGetTexParameterfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetTexParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glHint(target, mode) \
	(*(AGL_MACRO_CONTEXT)->disp.hint)(AGL_MACRO_CONTEXT_RENDERER, target, mode)

#define glIndexMask(mask) \
	(*(AGL_MACRO_CONTEXT)->disp.index_mask)(AGL_MACRO_CONTEXT_RENDERER, mask)

#define glIndexPointer(type, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.index_pointer)(AGL_MACRO_CONTEXT_RENDERER, type, stride, pointer)

#define glIndexd(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexd)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexdv(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexdv)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexf(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexf)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexfv(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexfv)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexi(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexi)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexiv(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexiv)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexs(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexs)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexsv(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexsv)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexub(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexub)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glIndexubv(c) \
	(*(AGL_MACRO_CONTEXT)->disp.indexubv)(AGL_MACRO_CONTEXT_RENDERER, c)

#define glInitNames() \
	(*(AGL_MACRO_CONTEXT)->disp.init_names)(AGL_MACRO_CONTEXT_RENDERER)

#define glInterleavedArrays(format, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.interleaved_arrays)(AGL_MACRO_CONTEXT_RENDERER, format, stride, pointer)

#define glIsEnabled(cap) \
	(*(AGL_MACRO_CONTEXT)->disp.is_enabled)(AGL_MACRO_CONTEXT_RENDERER, cap)

#define glIsList(list) \
	(*(AGL_MACRO_CONTEXT)->disp.is_list)(AGL_MACRO_CONTEXT_RENDERER, list)

#define glIsTexture(texture) \
	(*(AGL_MACRO_CONTEXT)->disp.is_texture)(AGL_MACRO_CONTEXT_RENDERER, texture)

#define glLightModelf(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.light_modelf)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glLightModelfv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.light_modelfv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glLightModeli(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.light_modeli)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glLightModeliv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.light_modeliv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glLightf(light, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.lightf)(AGL_MACRO_CONTEXT_RENDERER, light, pname, param)

#define glLightfv(light, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.lightfv)(AGL_MACRO_CONTEXT_RENDERER, light, pname, params)

#define glLighti(light, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.lighti)(AGL_MACRO_CONTEXT_RENDERER, light, pname, param)

#define glLightiv(light, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.lightiv)(AGL_MACRO_CONTEXT_RENDERER, light, pname, params)

#define glLineStipple(factor, pattern) \
	(*(AGL_MACRO_CONTEXT)->disp.line_stipple)(AGL_MACRO_CONTEXT_RENDERER, factor, pattern)

#define glLineWidth(width) \
	(*(AGL_MACRO_CONTEXT)->disp.line_width)(AGL_MACRO_CONTEXT_RENDERER, width)

#define glListBase(base) \
	(*(AGL_MACRO_CONTEXT)->disp.list_base)(AGL_MACRO_CONTEXT_RENDERER, base)

#define glLoadIdentity() \
	(*(AGL_MACRO_CONTEXT)->disp.load_identity)(AGL_MACRO_CONTEXT_RENDERER)

#define glLoadMatrixd(m) \
	(*(AGL_MACRO_CONTEXT)->disp.load_matrixd)(AGL_MACRO_CONTEXT_RENDERER, m)

#define glLoadMatrixf(m) \
	(*(AGL_MACRO_CONTEXT)->disp.load_matrixf)(AGL_MACRO_CONTEXT_RENDERER, m)

#define glLoadName(name) \
	(*(AGL_MACRO_CONTEXT)->disp.load_name)(AGL_MACRO_CONTEXT_RENDERER, name)

#define glLogicOp(opcode) \
	(*(AGL_MACRO_CONTEXT)->disp.logic_op)(AGL_MACRO_CONTEXT_RENDERER, opcode)

#define glMap1d(target, u1, u2, stride, order, points) \
	(*(AGL_MACRO_CONTEXT)->disp.map1d)(AGL_MACRO_CONTEXT_RENDERER, target, u1, u2, stride, order, points)

#define glMap1f(target, u1, u2, stride, order, points) \
	(*(AGL_MACRO_CONTEXT)->disp.map1f)(AGL_MACRO_CONTEXT_RENDERER, target, u1, u2, stride, order, points)

#define glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*(AGL_MACRO_CONTEXT)->disp.map2d)(AGL_MACRO_CONTEXT_RENDERER, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*(AGL_MACRO_CONTEXT)->disp.map2f)(AGL_MACRO_CONTEXT_RENDERER, target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMapGrid1d(un, u1, u2) \
	(*(AGL_MACRO_CONTEXT)->disp.map_grid1d)(AGL_MACRO_CONTEXT_RENDERER, un, u1, u2)

#define glMapGrid1f(un, u1, u2) \
	(*(AGL_MACRO_CONTEXT)->disp.map_grid1f)(AGL_MACRO_CONTEXT_RENDERER, un, u1, u2)

#define glMapGrid2d(un, u1, u2, vn, v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.map_grid2d)(AGL_MACRO_CONTEXT_RENDERER, un, u1, u2, vn, v1, v2)

#define glMapGrid2f(un, u1, u2, vn, v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.map_grid2f)(AGL_MACRO_CONTEXT_RENDERER, un, u1, u2, vn, v1, v2)

#define glMaterialf(face, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.materialf)(AGL_MACRO_CONTEXT_RENDERER, face, pname, param)

#define glMaterialfv(face, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.materialfv)(AGL_MACRO_CONTEXT_RENDERER, face, pname, params)

#define glMateriali(face, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.materiali)(AGL_MACRO_CONTEXT_RENDERER, face, pname, param)

#define glMaterialiv(face, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.materialiv)(AGL_MACRO_CONTEXT_RENDERER, face, pname, params)

#define glMatrixMode(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.matrix_mode)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glMultMatrixd(m) \
	(*(AGL_MACRO_CONTEXT)->disp.mult_matrixd)(AGL_MACRO_CONTEXT_RENDERER, m)

#define glMultMatrixf(m) \
	(*(AGL_MACRO_CONTEXT)->disp.mult_matrixf)(AGL_MACRO_CONTEXT_RENDERER, m)

#define glNewList(list, mode) \
	(*(AGL_MACRO_CONTEXT)->disp.new_list)(AGL_MACRO_CONTEXT_RENDERER, list, mode)

#define glNormal3b(nx, ny, nz) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3b)(AGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3bv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3bv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glNormal3d(nx, ny, nz) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3d)(AGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glNormal3f(nx, ny, nz) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3f)(AGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glNormal3i(nx, ny, nz) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3i)(AGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glNormal3s(nx, ny, nz) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3s)(AGL_MACRO_CONTEXT_RENDERER, nx, ny, nz)

#define glNormal3sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.normal3sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glNormalPointer(type, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.normal_pointer)(AGL_MACRO_CONTEXT_RENDERER, type, stride, pointer)

#define glOrtho(left, right, bottom, top, zNear, zFar) \
	(*(AGL_MACRO_CONTEXT)->disp.ortho)(AGL_MACRO_CONTEXT_RENDERER, left, right, bottom, top, zNear, zFar)

#define glPassThrough(token) \
	(*(AGL_MACRO_CONTEXT)->disp.pass_through)(AGL_MACRO_CONTEXT_RENDERER, token)

#define glPixelMapfv(map, mapsize, values) \
	(*(AGL_MACRO_CONTEXT)->disp.pixel_mapfv)(AGL_MACRO_CONTEXT_RENDERER, map, mapsize, values)

#define glPixelMapuiv(map, mapsize, values) \
	(*(AGL_MACRO_CONTEXT)->disp.pixel_mapuiv)(AGL_MACRO_CONTEXT_RENDERER, map, mapsize, values)

#define glPixelMapusv(map, mapsize, values) \
	(*(AGL_MACRO_CONTEXT)->disp.pixel_mapusv)(AGL_MACRO_CONTEXT_RENDERER, map, mapsize, values)

#define glPixelStoref(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.pixel_storef)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelStorei(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.pixel_storei)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelTransferf(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.pixel_transferf)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelTransferi(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.pixel_transferi)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPixelZoom(xfactor, yfactor) \
	(*(AGL_MACRO_CONTEXT)->disp.pixel_zoom)(AGL_MACRO_CONTEXT_RENDERER, xfactor, yfactor)

#define glPointSize(size) \
	(*(AGL_MACRO_CONTEXT)->disp.point_size)(AGL_MACRO_CONTEXT_RENDERER, size)

#define glPolygonMode(face, mode) \
	(*(AGL_MACRO_CONTEXT)->disp.polygon_mode)(AGL_MACRO_CONTEXT_RENDERER, face, mode)

#define glPolygonOffset(factor, units) \
	(*(AGL_MACRO_CONTEXT)->disp.polygon_offset)(AGL_MACRO_CONTEXT_RENDERER, factor, units)

#define glPolygonStipple(mask) \
	(*(AGL_MACRO_CONTEXT)->disp.polygon_stipple)(AGL_MACRO_CONTEXT_RENDERER, mask)

#define glPopAttrib() \
	(*(AGL_MACRO_CONTEXT)->disp.pop_attrib)(AGL_MACRO_CONTEXT_RENDERER)

#define glPopClientAttrib() \
	(*(AGL_MACRO_CONTEXT)->disp.pop_client_attrib)(AGL_MACRO_CONTEXT_RENDERER)

#define glPopMatrix() \
	(*(AGL_MACRO_CONTEXT)->disp.pop_matrix)(AGL_MACRO_CONTEXT_RENDERER)

#define glPopName() \
	(*(AGL_MACRO_CONTEXT)->disp.pop_name)(AGL_MACRO_CONTEXT_RENDERER)

#define glPrioritizeTextures(n, textures, priorities) \
	(*(AGL_MACRO_CONTEXT)->disp.prioritize_textures)(AGL_MACRO_CONTEXT_RENDERER, n, textures, priorities)

#define glPushAttrib(mask) \
	(*(AGL_MACRO_CONTEXT)->disp.push_attrib)(AGL_MACRO_CONTEXT_RENDERER, mask)

#define glPushClientAttrib(mask) \
	(*(AGL_MACRO_CONTEXT)->disp.push_client_attrib)(AGL_MACRO_CONTEXT_RENDERER, mask)

#define glPushMatrix() \
	(*(AGL_MACRO_CONTEXT)->disp.push_matrix)(AGL_MACRO_CONTEXT_RENDERER)

#define glPushName(name) \
	(*(AGL_MACRO_CONTEXT)->disp.push_name)(AGL_MACRO_CONTEXT_RENDERER, name)

#define glRasterPos2d(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos2d)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glRasterPos2dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos2dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos2f(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos2f)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glRasterPos2fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos2fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos2i(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos2i)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glRasterPos2iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos2iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos2s(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos2s)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glRasterPos2sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos2sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos3d(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos3d)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glRasterPos3dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos3dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos3f(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos3f)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glRasterPos3fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos3fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos3i(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos3i)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glRasterPos3iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos3iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos3s(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos3s)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glRasterPos3sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos3sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos4d(x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos4d)(AGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glRasterPos4dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos4dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos4f(x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos4f)(AGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glRasterPos4fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos4fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos4i(x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos4i)(AGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glRasterPos4iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos4iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glRasterPos4s(x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos4s)(AGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glRasterPos4sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.raster_pos4sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glReadBuffer(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.read_buffer)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glReadPixels(x, y, width, height, format, type, pixels) \
	(*(AGL_MACRO_CONTEXT)->disp.read_pixels)(AGL_MACRO_CONTEXT_RENDERER, x, y, width, height, format, type, pixels)

#define glRectd(x1, y1, x2, y2) \
	(*(AGL_MACRO_CONTEXT)->disp.rectd)(AGL_MACRO_CONTEXT_RENDERER, x1, y1, x2, y2)

#define glRectdv(v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.rectdv)(AGL_MACRO_CONTEXT_RENDERER, v1, v2)

#define glRectf(x1, y1, x2, y2) \
	(*(AGL_MACRO_CONTEXT)->disp.rectf)(AGL_MACRO_CONTEXT_RENDERER, x1, y1, x2, y2)

#define glRectfv(v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.rectfv)(AGL_MACRO_CONTEXT_RENDERER, v1, v2)

#define glRecti(x1, y1, x2, y2) \
	(*(AGL_MACRO_CONTEXT)->disp.recti)(AGL_MACRO_CONTEXT_RENDERER, x1, y1, x2, y2)

#define glRectiv(v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.rectiv)(AGL_MACRO_CONTEXT_RENDERER, v1, v2)

#define glRects(x1, y1, x2, y2) \
	(*(AGL_MACRO_CONTEXT)->disp.rects)(AGL_MACRO_CONTEXT_RENDERER, x1, y1, x2, y2)

#define glRectsv(v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.rectsv)(AGL_MACRO_CONTEXT_RENDERER, v1, v2)

#define glRenderMode(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.render_mode)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glRotated(angle, x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.rotated)(AGL_MACRO_CONTEXT_RENDERER, angle, x, y, z)

#define glRotatef(angle, x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.rotatef)(AGL_MACRO_CONTEXT_RENDERER, angle, x, y, z)

#define glScaled(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.scaled)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glScalef(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.scalef)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glScissor(x, y, width, height) \
	(*(AGL_MACRO_CONTEXT)->disp.scissor)(AGL_MACRO_CONTEXT_RENDERER, x, y, width, height)

#define glSelectBuffer(size, buffer) \
	(*(AGL_MACRO_CONTEXT)->disp.select_buffer)(AGL_MACRO_CONTEXT_RENDERER, size, buffer)

#define glShadeModel(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.shade_model)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glStencilFunc(func, ref, mask) \
	(*(AGL_MACRO_CONTEXT)->disp.stencil_func)(AGL_MACRO_CONTEXT_RENDERER, func, ref, mask)

#define glStencilMask(mask) \
	(*(AGL_MACRO_CONTEXT)->disp.stencil_mask)(AGL_MACRO_CONTEXT_RENDERER, mask)

#define glStencilOp(fail, zfail, zpass) \
	(*(AGL_MACRO_CONTEXT)->disp.stencil_op)(AGL_MACRO_CONTEXT_RENDERER, fail, zfail, zpass)

#define glTexCoord1d(s) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord1d)(AGL_MACRO_CONTEXT_RENDERER, s)

#define glTexCoord1dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord1dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord1f(s) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord1f)(AGL_MACRO_CONTEXT_RENDERER, s)

#define glTexCoord1fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord1fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord1i(s) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord1i)(AGL_MACRO_CONTEXT_RENDERER, s)

#define glTexCoord1iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord1iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord1s(s) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord1s)(AGL_MACRO_CONTEXT_RENDERER, s)

#define glTexCoord1sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord1sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord2d(s, t) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord2d)(AGL_MACRO_CONTEXT_RENDERER, s, t)

#define glTexCoord2dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord2dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord2f(s, t) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord2f)(AGL_MACRO_CONTEXT_RENDERER, s, t)

#define glTexCoord2fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord2fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord2i(s, t) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord2i)(AGL_MACRO_CONTEXT_RENDERER, s, t)

#define glTexCoord2iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord2iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord2s(s, t) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord2s)(AGL_MACRO_CONTEXT_RENDERER, s, t)

#define glTexCoord2sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord2sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord3d(s, t, r) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord3d)(AGL_MACRO_CONTEXT_RENDERER, s, t, r)

#define glTexCoord3dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord3dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord3f(s, t, r) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord3f)(AGL_MACRO_CONTEXT_RENDERER, s, t, r)

#define glTexCoord3fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord3fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord3i(s, t, r) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord3i)(AGL_MACRO_CONTEXT_RENDERER, s, t, r)

#define glTexCoord3iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord3iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord3s(s, t, r) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord3s)(AGL_MACRO_CONTEXT_RENDERER, s, t, r)

#define glTexCoord3sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord3sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord4d(s, t, r, q) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord4d)(AGL_MACRO_CONTEXT_RENDERER, s, t, r, q)

#define glTexCoord4dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord4dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord4f(s, t, r, q) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord4f)(AGL_MACRO_CONTEXT_RENDERER, s, t, r, q)

#define glTexCoord4fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord4fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord4i(s, t, r, q) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord4i)(AGL_MACRO_CONTEXT_RENDERER, s, t, r, q)

#define glTexCoord4iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord4iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoord4s(s, t, r, q) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord4s)(AGL_MACRO_CONTEXT_RENDERER, s, t, r, q)

#define glTexCoord4sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord4sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glTexCoordPointer(size, type, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_coord_pointer)(AGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glTexEnvf(target, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_envf)(AGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexEnvfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_envfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexEnvi(target, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_envi)(AGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexEnviv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_enviv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexGend(coord, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_gend)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, param)

#define glTexGendv(coord, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_gendv)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glTexGenf(coord, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_genf)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, param)

#define glTexGenfv(coord, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_genfv)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glTexGeni(coord, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_geni)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, param)

#define glTexGeniv(coord, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_geniv)(AGL_MACRO_CONTEXT_RENDERER, coord, pname, params)

#define glTexImage1D(target, level, internalformat, width, border, format, type, pixels) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_image1D)(AGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, border, format, type, pixels)

#define glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_image2D)(AGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, border, format, type, pixels)

#define glTexParameterf(target, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_parameterf)(AGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexParameterfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexParameteri(target, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_parameteri)(AGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glTexParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glTexSubImage1D(target, level, xoffset, width, format, type, pixels) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_sub_image1D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, width, format, type, pixels)

#define glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_sub_image2D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, width, height, format, type, pixels)

#define glTranslated(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.translated)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glTranslatef(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.translatef)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex2d(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex2d)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glVertex2dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex2dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex2f(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex2f)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glVertex2fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex2fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex2i(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex2i)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glVertex2iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex2iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex2s(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex2s)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glVertex2sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex2sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex3d(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex3d)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex3dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex3dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex3f(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex3f)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex3fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex3fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex3i(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex3i)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex3iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex3iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex3s(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex3s)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glVertex3sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex3sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex4d(x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex4d)(AGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glVertex4dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex4dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex4f(x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex4f)(AGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glVertex4fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex4fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex4i(x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex4i)(AGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glVertex4iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex4iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertex4s(x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex4s)(AGL_MACRO_CONTEXT_RENDERER, x, y, z, w)

#define glVertex4sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex4sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glVertexPointer(size, type, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_pointer)(AGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glViewport(x, y, width, height) \
	(*(AGL_MACRO_CONTEXT)->disp.viewport)(AGL_MACRO_CONTEXT_RENDERER, x, y, width, height)

/****************** OpenGL 1.2 ************************************/

#define glBlendColor(red, green, blue, alpha) \
	(*(AGL_MACRO_CONTEXT)->disp.blend_color)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue, alpha)

#define glBlendEquation(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.blend_equation)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glDrawRangeElements(mode, start, end, count, type, indices) \
	(*(AGL_MACRO_CONTEXT)->disp.draw_range_elements)(AGL_MACRO_CONTEXT_RENDERER, mode, start, end, count, type, indices)

#define glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, data) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_image3D)(AGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, depth, border, format, type, data)

#define glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels) \
	(*(AGL_MACRO_CONTEXT)->disp.tex_sub_image3D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels)

#define glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_tex_sub_image3D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, x, y, width, height)

/****************** OpenGL 1.2 Imaging Subset *********************/

#define glColorTable(target, internalformat, width, format, type, table) \
	(*(AGL_MACRO_CONTEXT)->disp.color_table)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, format, type, table)

#define glColorTableParameterfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.color_table_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glColorTableParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.color_table_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glCopyColorTable(target, internalformat, x, y, width) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_color_table)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, x, y, width)

#define glGetColorTable(target, format, type, table) \
	(*(AGL_MACRO_CONTEXT)->disp.get_color_table)(AGL_MACRO_CONTEXT_RENDERER, target, format, type, table)

#define glGetColorTableParameterfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_color_table_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetColorTableParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_color_table_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glColorSubTable(target, start, count, format, type, data) \
	(*(AGL_MACRO_CONTEXT)->disp.color_sub_table)(AGL_MACRO_CONTEXT_RENDERER, target, start, count, format, type, data)

#define glCopyColorSubTable(target, start, x, y, width) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_color_sub_table)(AGL_MACRO_CONTEXT_RENDERER, target, start, x, y, width)

#define glConvolutionFilter1D(target, internalformat, width, format, type, image) \
	(*(AGL_MACRO_CONTEXT)->disp.convolution_filter1D)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, format, type, image)

#define glConvolutionFilter2D(target, internalformat, width, height, format, type, image) \
	(*(AGL_MACRO_CONTEXT)->disp.convolution_filter2D)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, height, format, type, image)

#define glConvolutionParameterf(target, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.convolution_parameterf)(AGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glConvolutionParameterfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.convolution_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glConvolutionParameteri(target, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.convolution_parameteri)(AGL_MACRO_CONTEXT_RENDERER, target, pname, param)

#define glConvolutionParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.convolution_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glCopyConvolutionFilter1D(target, internalformat, x, y, width) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_convolution_filter1D)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, x, y, width)

#define glCopyConvolutionFilter2D(target, internalformat, x, y, width, height) \
	(*(AGL_MACRO_CONTEXT)->disp.copy_convolution_filter2D)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, x, y, width, height)

#define glGetConvolutionFilter(target, format, type, image) \
	(*(AGL_MACRO_CONTEXT)->disp.get_convolution_filter)(AGL_MACRO_CONTEXT_RENDERER, target, format, type, image)

#define glGetConvolutionParameterfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_convolution_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetConvolutionParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_convolution_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetSeparableFilter(target, format, type, row, column, span) \
	(*(AGL_MACRO_CONTEXT)->disp.get_separable_filter)(AGL_MACRO_CONTEXT_RENDERER, target, format, type, row, column, span)

#define glSeparableFilter2D(target, internalformat, width, height, format, type, row, column) \
	(*(AGL_MACRO_CONTEXT)->disp.separable_filter2D)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, height, format, type, row, column)

#define glGetHistogram(target, reset, format, type, values) \
	(*(AGL_MACRO_CONTEXT)->disp.get_histogram)(AGL_MACRO_CONTEXT_RENDERER, target, reset, format, type, values)

#define glGetHistogramParameterfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_histogram_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetHistogramParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_histogram_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetMinmax(target, reset, format, type, values) \
	(*(AGL_MACRO_CONTEXT)->disp.get_minmax)(AGL_MACRO_CONTEXT_RENDERER, target, reset, format, type, values)

#define glGetMinmaxParameterfv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_minmax_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetMinmaxParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_minmax_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glHistogram(target, width, internalformat, sink) \
	(*(AGL_MACRO_CONTEXT)->disp.histogram)(AGL_MACRO_CONTEXT_RENDERER, target, width, internalformat, sink)

#define glMinmax(target, internalformat, sink) \
	(*(AGL_MACRO_CONTEXT)->disp.minmax)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, sink)

#define glResetHistogram(target) \
	(*(AGL_MACRO_CONTEXT)->disp.reset_histogram)(AGL_MACRO_CONTEXT_RENDERER, target)

#define glResetMinmax(target) \
	(*(AGL_MACRO_CONTEXT)->disp.reset_minmax)(AGL_MACRO_CONTEXT_RENDERER, target)

/****************** OpenGL 1.3 ************************************/

#define glClientActiveTexture(target) \
	(*(AGL_MACRO_CONTEXT)->disp.client_active_texture)(AGL_MACRO_CONTEXT_RENDERER, target)

#define glActiveTexture(target) \
	(*(AGL_MACRO_CONTEXT)->disp.active_texture)(AGL_MACRO_CONTEXT_RENDERER, target)

#define glMultiTexCoord1d(target, s) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord1d)(AGL_MACRO_CONTEXT_RENDERER, target, s)

#define glMultiTexCoord1dv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord1dv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord1f(target, s) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord1f)(AGL_MACRO_CONTEXT_RENDERER, target, s)

#define glMultiTexCoord1fv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord1fv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord1i(target, s) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord1i)(AGL_MACRO_CONTEXT_RENDERER, target, s)

#define glMultiTexCoord1iv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord1iv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord1s(target, s) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord1s)(AGL_MACRO_CONTEXT_RENDERER, target, s)

#define glMultiTexCoord1sv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord1sv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord2d(target, s, t) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord2d)(AGL_MACRO_CONTEXT_RENDERER, target, s, t)

#define glMultiTexCoord2dv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord2dv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord2f(target, s, t) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord2f)(AGL_MACRO_CONTEXT_RENDERER, target, s, t)

#define glMultiTexCoord2fv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord2fv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord2i(target, s, t) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord2i)(AGL_MACRO_CONTEXT_RENDERER, target, s, t)

#define glMultiTexCoord2iv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord2iv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord2s(target, s, t) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord2s)(AGL_MACRO_CONTEXT_RENDERER, target, s, t)

#define glMultiTexCoord2sv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord2sv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord3d(target, s, t, r) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord3d)(AGL_MACRO_CONTEXT_RENDERER, target, s, t, r)

#define glMultiTexCoord3dv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord3dv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord3f(target, s, t, r) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord3f)(AGL_MACRO_CONTEXT_RENDERER, target, s, t, r)

#define glMultiTexCoord3fv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord3fv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord3i(target, s, t, r) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord3i)(AGL_MACRO_CONTEXT_RENDERER, target, s, t, r)

#define glMultiTexCoord3iv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord3iv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord3s(target, s, t, r) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord3s)(AGL_MACRO_CONTEXT_RENDERER, target, s, t, r)

#define glMultiTexCoord3sv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord3sv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord4d(target, s, t, r, q) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord4d)(AGL_MACRO_CONTEXT_RENDERER, target, s, t, r, q)

#define glMultiTexCoord4dv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord4dv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord4f(target, s, t, r, q) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord4f)(AGL_MACRO_CONTEXT_RENDERER, target, s, t, r, q)

#define glMultiTexCoord4fv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord4fv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord4i(target, s, t, r, q) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord4i)(AGL_MACRO_CONTEXT_RENDERER, target, s, t, r, q)

#define glMultiTexCoord4iv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord4iv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glMultiTexCoord4s(target, s, t, r, q) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord4s)(AGL_MACRO_CONTEXT_RENDERER, target, s, t, r, q)

#define glMultiTexCoord4sv(target, v) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_tex_coord4sv)(AGL_MACRO_CONTEXT_RENDERER, target, v)

#define glSampleCoverage(v, i) \
	(*(AGL_MACRO_CONTEXT)->disp.sample_coverage)(AGL_MACRO_CONTEXT_RENDERER, v, i)

#define glSamplePass(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.sample_pass)(AGL_MACRO_CONTEXT_RENDERER, mode)

#define glLoadTransposeMatrixf(v) \
	(*(AGL_MACRO_CONTEXT)->disp.load_transpose_matrixf)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glLoadTransposeMatrixd(v) \
	(*(AGL_MACRO_CONTEXT)->disp.load_transpose_matrixd)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glMultTransposeMatrixf(v) \
	(*(AGL_MACRO_CONTEXT)->disp.mult_transpose_matrixf)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glMultTransposeMatrixd(v) \
	(*(AGL_MACRO_CONTEXT)->disp.mult_transpose_matrixd)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data) \
	(*(AGL_MACRO_CONTEXT)->disp.compressed_tex_image3D)(AGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, depth, border, imageSize, data)

#define glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data) \
	(*(AGL_MACRO_CONTEXT)->disp.compressed_tex_image2D)(AGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, height, border, imageSize, data)

#define glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data) \
	(*(AGL_MACRO_CONTEXT)->disp.compressed_tex_image1D)(AGL_MACRO_CONTEXT_RENDERER, target, level, internalformat, width, border, imageSize, data)

#define glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data) \
	(*(AGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image3D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data)

#define glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data) \
	(*(AGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image2D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, yoffset, width, height, format, imageSize, data)

#define glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data) \
	(*(AGL_MACRO_CONTEXT)->disp.compressed_tex_sub_image1D)(AGL_MACRO_CONTEXT_RENDERER, target, level, xoffset, width, format, imageSize, data)

#define glGetCompressedTexImage(target, level, img) \
	(*(AGL_MACRO_CONTEXT)->disp.get_compressed_tex_image)(AGL_MACRO_CONTEXT_RENDERER, target, level, img)

#define glSampleCoverage(v, i) \
	(*(AGL_MACRO_CONTEXT)->disp.sample_coverage)(AGL_MACRO_CONTEXT_RENDERER, v, i)

#define glSamplePass(mode) \
	(*(AGL_MACRO_CONTEXT)->disp.sample_pass)(AGL_MACRO_CONTEXT_RENDERER, mode)

/****************** OpenGL 1.4 ************************************/

#define glFogCoordf(coord) \
	(*(AGL_MACRO_CONTEXT)->disp.fog_coordf)(AGL_MACRO_CONTEXT_RENDERER, coord)

#define glFogCoordfv(coord) \
	(*(AGL_MACRO_CONTEXT)->disp.fog_coordfv)(AGL_MACRO_CONTEXT_RENDERER, coord)

#define glFogCoordd(coord) \
	(*(AGL_MACRO_CONTEXT)->disp.fog_coordd)(AGL_MACRO_CONTEXT_RENDERER, coord)

#define glFogCoorddv(coord) \
	(*(AGL_MACRO_CONTEXT)->disp.fog_coorddv)(AGL_MACRO_CONTEXT_RENDERER,coord)

#define glFogCoordPointer(type, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.fog_coord_pointer)(AGL_MACRO_CONTEXT_RENDERER, type, stride, pointer)

#define glSecondaryColor3b(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3b)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3bv(components) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3bv)(AGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3d(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3d)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3dv(components) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3dv)(AGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3f(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3f)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3fv(components) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3fv)(AGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3i(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3i)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3iv(components) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3iv)(AGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3s(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3s)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3sv(components) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3sv)(AGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3ub(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3ub)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3ubv(components) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3ubv)(AGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3ui(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3ui)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3uiv(components) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3uiv)(AGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColor3us(red, green, blue) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3us)(AGL_MACRO_CONTEXT_RENDERER, red, green, blue)

#define glSecondaryColor3usv(components) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color3usv)(AGL_MACRO_CONTEXT_RENDERER, components)

#define glSecondaryColorPointer(size, type, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.secondary_color_pointer)(AGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glPointParameterf(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.point_parameterf)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPointParameterfv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.point_parameterfv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glPointParameteri(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.point_parameteri)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPointParameteriv(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.point_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha) \
	(*(AGL_MACRO_CONTEXT)->disp.blend_func_separate)(AGL_MACRO_CONTEXT_RENDERER, sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha)

#define glMultiDrawArrays(mode, first, count, primcount) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_draw_arrays)(AGL_MACRO_CONTEXT_RENDERER, mode, first, count, primcount)

#define glMultiDrawElements(mode, count, type, indices, primcount) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_draw_elements)(AGL_MACRO_CONTEXT_RENDERER, mode, count, type, indices, primcount)

#define glWindowPos2d(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos2d)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glWindowPos2dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos2dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos2f(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos2f)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glWindowPos2fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos2fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos2i(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos2i)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glWindowPos2iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos2iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos2s(x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos2s)(AGL_MACRO_CONTEXT_RENDERER, x, y)

#define glWindowPos2sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos2sv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos3d(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos3d)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glWindowPos3dv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos3dv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos3f(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos3f)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glWindowPos3fv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos3fv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos3i(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos3i)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glWindowPos3iv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos3iv)(AGL_MACRO_CONTEXT_RENDERER, v)

#define glWindowPos3s(x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos3s)(AGL_MACRO_CONTEXT_RENDERER, x, y, z)

#define glWindowPos3sv(v) \
	(*(AGL_MACRO_CONTEXT)->disp.window_pos3sv)(AGL_MACRO_CONTEXT_RENDERER, v)

/****************** OpenGL 1.5 Macros *****************************/

#define glGenQueries(n, ids) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_queries)(AGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glDeleteQueries(n, ids) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_queries)(AGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glIsQuery(id) \
	(*(AGL_MACRO_CONTEXT)->disp.is_query)(AGL_MACRO_CONTEXT_RENDERER, id)

#define glBeginQuery(target, id) \
	(*(AGL_MACRO_CONTEXT)->disp.begin_query)(AGL_MACRO_CONTEXT_RENDERER, target, id)

#define glEndQuery(target) \
	(*(AGL_MACRO_CONTEXT)->disp.end_query)(AGL_MACRO_CONTEXT_RENDERER, target)

#define glGetQueryiv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_queryiv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetQueryObjectiv(id, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_query_objectiv)(AGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glGetQueryObjectuiv(id, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_query_objectuiv)(AGL_MACRO_CONTEXT_RENDERER, id, pname, params)

#define glBindBuffer(target, buffer) \
	(*(AGL_MACRO_CONTEXT)->disp.bind_buffer)(AGL_MACRO_CONTEXT_RENDERER, target, buffer)

#define glDeleteBuffers(n, buffers) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_buffers)(AGL_MACRO_CONTEXT_RENDERER, n, buffers)

#define glGenBuffers(n, buffers) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_buffers)(AGL_MACRO_CONTEXT_RENDERER, n, buffers)

#define glIsBuffer(buffer) \
	(*(AGL_MACRO_CONTEXT)->disp.is_buffer)(AGL_MACRO_CONTEXT_RENDERER, buffer)

#define glBufferData(target, size, data, usage) \
	(*(AGL_MACRO_CONTEXT)->disp.buffer_data)(AGL_MACRO_CONTEXT_RENDERER, target, size, data, usage)

#define glBufferSubData(target, offset, size, data) \
	(*(AGL_MACRO_CONTEXT)->disp.buffer_sub_data)(AGL_MACRO_CONTEXT_RENDERER, target, offset, size, data)

#define glGetBufferSubData(target, offset, size, data) \
	(*(AGL_MACRO_CONTEXT)->disp.get_buffer_sub_data)(AGL_MACRO_CONTEXT_RENDERER, target, offset, size, data)

#define glMapBuffer(target, access) \
	(*(AGL_MACRO_CONTEXT)->disp.map_buffer)(AGL_MACRO_CONTEXT_RENDERER, target, access)

#define glUnmapBuffer(target) \
	(*(AGL_MACRO_CONTEXT)->disp.unmap_buffer)(AGL_MACRO_CONTEXT_RENDERER, target)

#define glGetBufferParameteriv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_buffer_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glGetBufferPointerv(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_buffer_pointerv)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)
	
/****************** OpenGL 2.0 Macros *****************************/

#define glDrawBuffers(n, bufs) \
	(*(AGL_MACRO_CONTEXT)->disp.draw_buffers_ARB)(AGL_MACRO_CONTEXT_RENDERER, n, bufs)

#define glVertexAttrib1d(index, x) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1dv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib1f(index, x) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1fv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib1s(index, x) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1s_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1sv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1sv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2d(index, x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2dv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2f(index, x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2fv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib2s(index, x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2s_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2sv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2sv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3d(index, x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3dv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3f(index, x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3fv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib3s(index, x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3s_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3sv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3sv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nbv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nbv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Niv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Niv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nsv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nsv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nub(index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nub_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, x, w)

#define glVertexAttrib4Nubv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4ubv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nuiv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nuiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4Nusv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nusv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4bv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4bv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4d(index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4dv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4f(index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4fv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4iv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4s(index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4s_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4sv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4sv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4ubv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4ubv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4uiv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4uiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttrib4usv(index, v) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4usv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, v)

#define glVertexAttribPointer(index, size, type, normalized, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib_pointer_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, size, type, normalized, stride, pointer)

#define glEnableVertexAttribArray(index) \
	(*(AGL_MACRO_CONTEXT)->disp.enable_vertex_attrib_array_ARB)(AGL_MACRO_CONTEXT_RENDERER, index)

#define glDisableVertexAttribArray(index) \
	(*(AGL_MACRO_CONTEXT)->disp.disable_vertex_attrib_array_ARB)(AGL_MACRO_CONTEXT_RENDERER, index)

#define glGetVertexAttribdv(index, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_vertex_attribdv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribfv(index, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_vertex_attribfv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribiv(index, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_vertex_attribiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribPointerv(index, pname, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.get_vertex_attrib_pointerv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname, pointer)

#define glDeleteShader(shader) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) shader)

#define glDetachShader(program, shader) \
	(*(AGL_MACRO_CONTEXT)->disp.detach_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, (GLhandleARB) shader)

#define glCreateShader(type) \
	(GLuint) (*(AGL_MACRO_CONTEXT)->disp.create_shader_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, type)

#define glShaderSource(shader, count, string, length) \
	(*(AGL_MACRO_CONTEXT)->disp.shader_source_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) shader, count, string, length)

#define glCompileShader(shader) \
	(*(AGL_MACRO_CONTEXT)->disp.compile_shader_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) shader)

#define glCreateProgram() \
	(GLuint) (*(AGL_MACRO_CONTEXT)->disp.create_program_object_ARB)(AGL_MACRO_CONTEXT_RENDERER)

#define glAttachShader(program, shader) \
	(*(AGL_MACRO_CONTEXT)->disp.attach_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, (GLhandleARB) shader)

#define glLinkProgram(program) \
	(*(AGL_MACRO_CONTEXT)->disp.link_program_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program)

#define glUseProgram(program) \
	(*(AGL_MACRO_CONTEXT)->disp.use_program_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program)

#define glDeleteProgram(program) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program)

#define glValidateProgram(program) \
	(*(AGL_MACRO_CONTEXT)->disp.validate_program_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program)

#define glUniform1f(location, v0) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform1f_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2f(location, v0, v1) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform2f_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3f(location, v0, v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform3f_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4f(location, v0, v1, v2, v3) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform4f_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1i(location, v0) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform1i_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2i(location, v0, v1) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform2i_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3i(location, v0, v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform3i_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4i(location, v0, v1, v2, v3) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform4i_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1fv(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform1fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2fv(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform2fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3fv(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform3fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4fv(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform4fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform1iv(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform1iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2iv(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform2iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3iv(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform3iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4iv(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform4iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniformMatrix2fv(location, count, transpose, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform_matrix2fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3fv(location, count, transpose, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform_matrix3fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4fv(location, count, transpose, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform_matrix4fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glIsShader(shader) \
	(*(AGL_MACRO_CONTEXT)->disp.is_shader)(AGL_MACRO_CONTEXT_RENDERER, shader)

#define glIsProgram(program) \
	(*(AGL_MACRO_CONTEXT)->disp.is_program)(AGL_MACRO_CONTEXT_RENDERER, program)

#define glGetShaderiv(shader, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_shaderiv)(AGL_MACRO_CONTEXT_RENDERER, shader, pname, params)

#define glGetProgramiv(program, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_programiv)(AGL_MACRO_CONTEXT_RENDERER, program, pname, params)

#define glGetAttachedShaders(program, maxCount, count, shaders) \
	(*(AGL_MACRO_CONTEXT)->disp.get_attached_objects_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, maxCount, count, (GLhandleARB *) shaders)

#define glGetShaderInfoLog(shader, bufSize, length, infoLog) \
	(*(AGL_MACRO_CONTEXT)->disp.get_shader_info_log)(AGL_MACRO_CONTEXT_RENDERER, shader, bufSize, length, infoLog)

#define glGetProgramInfoLog(program, bufSize, length, infoLog) \
	(*(AGL_MACRO_CONTEXT)->disp.get_program_info_log)(AGL_MACRO_CONTEXT_RENDERER, program, bufSize, length, infoLog)

#define glGetUniformLocation(program, name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_uniform_location_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, name)

#define glGetActiveUniform(program, index, bufSize, length, size, type, name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_active_uniform_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, index, bufSize, length, size, type, name)

#define glGetUniformfv(program, location, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_uniformfv_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, location, params)

#define glGetUniformiv(program, location, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_uniformiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, location, params)

#define glGetShaderSource(shader, bufSize, length, source) \
	(*(AGL_MACRO_CONTEXT)->disp.get_shader_source_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) shader, bufSize, length, source)

#define glBindAttribLocation(program, index, name) \
	(*(AGL_MACRO_CONTEXT)->disp.bind_attrib_location_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, index, name)

#define glGetActiveAttrib(program, index, bufSize, length, size, type, name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_active_attrib_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, index, bufSize, length, size, type, name)

#define glGetAttribLocation(program, name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_attrib_location_ARB)(AGL_MACRO_CONTEXT_RENDERER, (GLhandleARB) program, name)

#define glStencilFuncSeparate(face, func, ref, mask) \
	(*(AGL_MACRO_CONTEXT)->disp.stencil_func_separate)(AGL_MACRO_CONTEXT_RENDERER, face, func, ref, mask)

#define glStencilOpSeparate(face, fail, zfail, zpass) \
	(*(AGL_MACRO_CONTEXT)->disp.stencil_op_separate_ATI)(AGL_MACRO_CONTEXT_RENDERER, face, fail, zfail, zpass)

#define glStencilMaskSeparate(face, mask) \
	(*(AGL_MACRO_CONTEXT)->disp.stencil_mask_separate)(AGL_MACRO_CONTEXT_RENDERER, face, mask)



/********** ARB Extensions *************************************************/

/* GL_ARB_vertex_program */
#define glBindProgramARB(target, id) \
	(*(AGL_MACRO_CONTEXT)->disp.bind_program_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, id)

#define glDeleteProgramsARB(n, programs) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_programs_ARB)(AGL_MACRO_CONTEXT_RENDERER, n, programs)

#define glGenProgramsARB(n, programs) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_programs_ARB)(AGL_MACRO_CONTEXT_RENDERER, n, programs)

#define glIsProgramARB(id) \
	(*(AGL_MACRO_CONTEXT)->disp.is_program_ARB)(AGL_MACRO_CONTEXT_RENDERER, id)

#define glVertexAttrib1sARB(index, x) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1s_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1fARB(index, x) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib1dARB(index, x) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x)

#define glVertexAttrib2sARB(index, x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2s_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2fARB(index, x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib2dARB(index, x, y) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y)

#define glVertexAttrib3sARB(index, x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3s_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3fARB(index, x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib3dARB(index, x, y, z) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z)

#define glVertexAttrib4sARB(index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4s_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4fARB(index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4dARB(index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib4NubARB(index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nub_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, x, y, z, w)

#define glVertexAttrib1svARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1sv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib1fvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib1dvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib1dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib2svARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2sv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib2fvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib2dvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib2dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib3svARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3sv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib3fvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib3dvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib3dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4bvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4bv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4ubvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4ubv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4svARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4sv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4usvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4usv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4ivARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4uivARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4uiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4fvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4dvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NbvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nbv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NubvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nubv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NsvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nsv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NusvARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nusv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NivARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Niv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttrib4NuivARB(index, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib4Nuiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, addr)

#define glVertexAttribPointerARB(index, size, type, normalized, stride, addr) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_attrib_pointer_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, size, type, normalized, stride, addr)

#define glEnableVertexAttribArrayARB(index) \
	(*(AGL_MACRO_CONTEXT)->disp.enable_vertex_attrib_array_ARB)(AGL_MACRO_CONTEXT_RENDERER, index)

#define glDisableVertexAttribArrayARB(index) \
	(*(AGL_MACRO_CONTEXT)->disp.disable_vertex_attrib_array_ARB)(AGL_MACRO_CONTEXT_RENDERER, index)

#define glGetVertexAttribdvARB(index, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_vertex_attribdv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribfvARB(index, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_vertex_attribfv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribivARB(index, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_vertex_attribiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname, params)

#define glGetVertexAttribPointervARB(index, pname, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.get_vertex_attrib_pointerv_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname, pointer)

#define glProgramEnvParameter4dARB(target, index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.program_env_parameter4d_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, x, y, z, w)

#define glProgramEnvParameter4dvARB(target, index, params) \
	(*(AGL_MACRO_CONTEXT)->disp.program_env_parameter4dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glProgramEnvParameter4fARB(target, index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.program_env_parameter4f_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, x, y, z, w)

#define glProgramEnvParameter4fvARB(target, index, params) \
	(*(AGL_MACRO_CONTEXT)->disp.program_env_parameter4fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glProgramLocalParameter4dARB(target, index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.program_local_parameter4d_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, x, y, z, w)

#define glProgramLocalParameter4dvARB(target, index, params) \
	(*(AGL_MACRO_CONTEXT)->disp.program_local_parameter4dv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glProgramLocalParameter4fARB(target, index, x, y, z, w) \
	(*(AGL_MACRO_CONTEXT)->disp.program_local_parameter4f_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, x, y, z, w)

#define glProgramLocalParameter4fvARB(target, index, params) \
	(*(AGL_MACRO_CONTEXT)->disp.program_local_parameter4fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glGetProgramEnvParameterdvARB(target, index, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_program_env_parameterdv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glGetProgramEnvParameterfvARB(target, index, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_program_env_parameterfv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glGetProgramLocalParameterdvARB(target, index, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_program_local_parameterdv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glGetProgramLocalParameterfvARB(target, index, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_program_local_parameterfv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, index, params)

#define glProgramStringARB(target, format, length, string) \
	(*(AGL_MACRO_CONTEXT)->disp.program_string_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, format, length, string)

#define glGetProgramStringARB(target, pname, string) \
	(*(AGL_MACRO_CONTEXT)->disp.get_program_string_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, pname, string)

#define glGetProgramivARB(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_programiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

/* GL_ARB_vertex_blend */
#define glWeightbvARB(size, weights) \
	(*(AGL_MACRO_CONTEXT)->disp.weightbv_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightsvARB(size, weights) \
	(*(AGL_MACRO_CONTEXT)->disp.weightsv_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightivARB(size, weights) \
	(*(AGL_MACRO_CONTEXT)->disp.weightiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightfvARB(size, weights) \
	(*(AGL_MACRO_CONTEXT)->disp.weightfv_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightdvARB(size, weights) \
	(*(AGL_MACRO_CONTEXT)->disp.weightdv_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightubvARB(size, weights) \
	(*(AGL_MACRO_CONTEXT)->disp.weightubv_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightusvARB(size, weights) \
	(*(AGL_MACRO_CONTEXT)->disp.weightusv_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightuivARB(size, weights) \
	(*(AGL_MACRO_CONTEXT)->disp.weightuiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, weights)

#define glWeightPointerARB(size, type, stride, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.weight_pointer_ARB)(AGL_MACRO_CONTEXT_RENDERER, size, type, stride, pointer)

#define glVertexBlendARB(count) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_blend_ARB)(AGL_MACRO_CONTEXT_RENDERER, count)

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
	(*(AGL_MACRO_CONTEXT)->disp.delete_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, obj)

#define glGetHandleARB(pname) \
	(*(AGL_MACRO_CONTEXT)->disp.get_handle_ARB)(AGL_MACRO_CONTEXT_RENDERER, pname)

#define glDetachObjectARB(container, attached) \
	(*(AGL_MACRO_CONTEXT)->disp.detach_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, container, attached)

#define glCreateShaderObjectARB(shader) \
	(*(AGL_MACRO_CONTEXT)->disp.create_shader_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, shader)

#define glShaderSourceARB(shader, count, string, length) \
	(*(AGL_MACRO_CONTEXT)->disp.shader_source_ARB)(AGL_MACRO_CONTEXT_RENDERER, shader, count, string, length)

#define glCompileShaderARB(shader) \
	(*(AGL_MACRO_CONTEXT)->disp.compile_shader_ARB)(AGL_MACRO_CONTEXT_RENDERER, shader)

#define glCreateProgramObjectARB() \
	(*(AGL_MACRO_CONTEXT)->disp.create_program_object_ARB)(AGL_MACRO_CONTEXT_RENDERER)

#define glAttachObjectARB(container, object) \
	(*(AGL_MACRO_CONTEXT)->disp.attach_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, container, object)

#define glLinkProgramARB(program) \
	(*(AGL_MACRO_CONTEXT)->disp.link_program_ARB)(AGL_MACRO_CONTEXT_RENDERER, program)

#define glUseProgramObjectARB(program) \
	(*(AGL_MACRO_CONTEXT)->disp.use_program_object_ARB)(AGL_MACRO_CONTEXT_RENDERER, program)

#define glValidateProgramARB(program) \
	(*(AGL_MACRO_CONTEXT)->disp.validate_program_ARB)(AGL_MACRO_CONTEXT_RENDERER, program)

#define glUniform1fARB(location, v0) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform1f_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2fARB(location, v0, v1) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform2f_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3fARB(location, v0, v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform3f_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4fARB(location, v0, v1, v2, v3) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform4f_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1iARB(location, v0) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform1i_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0)

#define glUniform2iARB(location, v0, v1) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform2i_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1)

#define glUniform3iARB(location, v0, v1, v2) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform3i_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2)

#define glUniform4iARB(location, v0, v1, v2, v3) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform4i_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, v0, v1, v2, v3)

#define glUniform1fvARB(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform1fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2fvARB(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform2fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3fvARB(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform3fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4fvARB(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform4fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform1ivARB(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform1iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform2ivARB(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform2iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform3ivARB(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform3iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniform4ivARB(location, count, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform4iv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, value)

#define glUniformMatrix2fvARB(location, count, transpose, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform_matrix2fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix3fvARB(location, count, transpose, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform_matrix3fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glUniformMatrix4fvARB(location, count, transpose, value) \
	(*(AGL_MACRO_CONTEXT)->disp.uniform_matrix4fv_ARB)(AGL_MACRO_CONTEXT_RENDERER, location, count, transpose, value)

#define glGetObjectParameterfvARB(obj, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_object_parameterfv_ARB)(AGL_MACRO_CONTEXT_RENDERER, obj, pname, params)

#define glGetObjectParameterivARB(obj, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_object_parameteriv_ARB)(AGL_MACRO_CONTEXT_RENDERER, obj, pname, params)

#define glGetInfoLogARB(obj, max, length, info) \
	(*(AGL_MACRO_CONTEXT)->disp.get_info_log_ARB)(AGL_MACRO_CONTEXT_RENDERER, obj, max, length, info)

#define glGetAttachedObjectsARB(container, max, count, obj) \
	(*(AGL_MACRO_CONTEXT)->disp.get_attached_objects_ARB)(AGL_MACRO_CONTEXT_RENDERER, container, max, count, obj)

#define glGetUniformLocationARB(program, name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_uniform_location_ARB)(AGL_MACRO_CONTEXT_RENDERER, program, name)

#define glGetActiveUniformARB(program, index, max, length, size, type, name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_active_uniform_ARB)(AGL_MACRO_CONTEXT_RENDERER, program, index, max, length, size, type, name)

#define glGetUniformfvARB(program, location, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_uniformfv_ARB)(AGL_MACRO_CONTEXT_RENDERER, program, location, params)

#define glGetUniformivARB(program, location, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_uniformiv_ARB)(AGL_MACRO_CONTEXT_RENDERER, program, location, params)

#define glGetShaderSourceARB(obj, max, length, source) \
	(*(AGL_MACRO_CONTEXT)->disp.get_shader_source_ARB)(AGL_MACRO_CONTEXT_RENDERER, obj, max, length, source)

/* GL_ARB_vertex_shader */
#define glBindAttribLocationARB(program, index, name) \
	(*(AGL_MACRO_CONTEXT)->disp.bind_attrib_location_ARB)(AGL_MACRO_CONTEXT_RENDERER, program, index, name)

#define glGetActiveAttribARB(program, index, max, length, size, type, name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_active_attrib_ARB)(AGL_MACRO_CONTEXT_RENDERER, program, index, max, length, size, type, name)

#define glGetAttribLocationARB(program, name) \
	(*(AGL_MACRO_CONTEXT)->disp.get_attrib_location_ARB)(AGL_MACRO_CONTEXT_RENDERER, program, name)
	
#define glDrawBuffersARB(n, bufs)\
	(*(AGL_MACRO_CONTEXT)->disp.draw_buffers_ARB)(AGL_MACRO_CONTEXT_RENDERER, n, bufs)
	
/*********** EXT Extensions *************************************************/

/* GL_EXT_compiled_vertex_array */
#define glLockArraysEXT(first, count) \
	(*(AGL_MACRO_CONTEXT)->disp.lock_arrays_EXT)(AGL_MACRO_CONTEXT_RENDERER, first, count)

#define glUnlockArraysEXT() \
	(*(AGL_MACRO_CONTEXT)->disp.unlock_arrays_EXT)(AGL_MACRO_CONTEXT_RENDERER)

/* GL_EXT_stencil_two_side */
#define glActiveStencilFaceEXT(face) \
	(*(AGL_MACRO_CONTEXT)->disp.active_stencil_face_EXT)(AGL_MACRO_CONTEXT_RENDERER, face)

/* GL_EXT_depth_bounds_test */
#define glDepthBoundsEXT(zmin, zmax) \
	(*(AGL_MACRO_CONTEXT)->disp.depth_bounds_EXT)(AGL_MACRO_CONTEXT_RENDERER, zmin, zmax)

/* GL_EXT_blend_equation_separate */
#define glBlendEquationSeparateEXT(modeRGB, modeAlpha) \
	(*(AGL_MACRO_CONTEXT)->disp.blend_equation_separate_EXT)(AGL_MACRO_CONTEXT_RENDERER, modeRGB, modeAlpha)

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

#if 0

/* GL_EXT_framebuffer_object */
#define glIsRenderbufferEXT(renderbuffer) \
	(*(AGL_MACRO_CONTEXT)->disp.is_renderbuffer_EXT)(AGL_MACRO_CONTEXT_RENDERER, renderbuffer)

#define glBindRenderbufferEXT(target, renderbuffer) \
	(*(AGL_MACRO_CONTEXT)->disp.bind_renderbuffer_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, renderbuffer)

#define glDeleteRenderbuffersEXT(n, renderbuffers) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_renderbuffers_EXT)(AGL_MACRO_CONTEXT_RENDERER, n, renderbuffers)

#define glGenRenderbuffersEXT(n, renderbuffers) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_renderbuffers_EXT)(AGL_MACRO_CONTEXT_RENDERER, n, renderbuffers)

#define glRenderbufferStorageEXT(target, internalformat, width, height) \
	(*(AGL_MACRO_CONTEXT)->disp.renderbuffer_storage_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, internalformat, width, height)

#define glGetRenderbufferParameterivEXT(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_renderbuffer_parameteriv_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

#define glIsFramebufferEXT(framebuffer) \
	(*(AGL_MACRO_CONTEXT)->disp.is_framebuffer_EXT)(AGL_MACRO_CONTEXT_RENDERER, framebuffer)

#define glBindFramebufferEXT(target, framebuffer) \
	(*(AGL_MACRO_CONTEXT)->disp.bind_framebuffer_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, framebuffer)

#define glDeleteFramebuffersEXT(n, framebuffers) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_framebuffers_EXT)(AGL_MACRO_CONTEXT_RENDERER, n, framebuffers)

#define glGenFramebuffersEXT(n, framebuffers) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_framebuffers_EXT)(AGL_MACRO_CONTEXT_RENDERER, n, framebuffers)

#define glCheckFramebufferStatusEXT(target) \
	(*(AGL_MACRO_CONTEXT)->disp.check_framebuffer_status_EXT)(AGL_MACRO_CONTEXT_RENDERER, target)

#define glFramebufferTexture1DEXT(target, attachment, textarget, texture, level) \
	(*(AGL_MACRO_CONTEXT)->disp.framebuffer_texture1D_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level)

#define glFramebufferTexture2DEXT(target, attachment, textarget, texture, level) \
	(*(AGL_MACRO_CONTEXT)->disp.framebuffer_texture2D_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level)

#define glFramebufferTexture3DEXT(target, attachment, textarget, texture, level, zoffset) \
	(*(AGL_MACRO_CONTEXT)->disp.framebuffer_texture3D_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, attachment, textarget, texture, level, zoffset)

#define glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer) \
	(*(AGL_MACRO_CONTEXT)->disp.framebuffer_renderbuffer_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, attachment, renderbuffertarget, renderbuffer)

#define glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_framebuffer_attachment_parameteriv_EXT)(AGL_MACRO_CONTEXT_RENDERER, target, attachment, pname, params)

#define glGenerateMipmapEXT(target) \
	(*(AGL_MACRO_CONTEXT)->disp.generate_mipmap_EXT)(AGL_MACRO_CONTEXT_RENDERER, target)
	
#endif
/*********** APPLE Extensions ***********************************************/

/* GL_APPLE_vertex_program_evaluators */
#define glEnableVertexAttribAPPLE(index, pname) \
	(*(AGL_MACRO_CONTEXT)->disp.enable_vertex_attrib_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname)

#define glDisableVertexAttribAPPLE(index, pname) \
	(*(AGL_MACRO_CONTEXT)->disp.disable_vertex_attrib_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname)

#define glIsVertexAttribEnabledAPPLE(index, pname) \
	(*(AGL_MACRO_CONTEXT)->disp.is_vertex_attrib_enabled_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, pname)

#define glMapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points) \
	(*(AGL_MACRO_CONTEXT)->disp.map_vertex_attrib1d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, size, u1, u2, stride, order, points)

#define glMapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points) \
	(*(AGL_MACRO_CONTEXT)->disp.map_vertex_attrib1f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, size, u1, u2, stride, order, points)

#define glMapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*(AGL_MACRO_CONTEXT)->disp.map_vertex_attrib2d_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

#define glMapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points) \
	(*(AGL_MACRO_CONTEXT)->disp.map_vertex_attrib2f_ARB)(AGL_MACRO_CONTEXT_RENDERER, index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points)

/* GL_APPLE_texture_range */
#define glTextureRangeAPPLE(target, length, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.texture_range_APPLE)(AGL_MACRO_CONTEXT_RENDERER, target, length, pointer)

#define glGetTexParameterPointervAPPLE(target, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_tex_parameter_pointerv_APPLE)(AGL_MACRO_CONTEXT_RENDERER, target, pname, params)

/* GL_APPLE_fence */
#define glGenFencesAPPLE(n, fences) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_fences_APPLE)(AGL_MACRO_CONTEXT_RENDERER, n, fences)

#define glDeleteFencesAPPLE(n, fences) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_fences_APPLE)(AGL_MACRO_CONTEXT_RENDERER, n, fences)

#define glSetFenceAPPLE(fence) \
	(*(AGL_MACRO_CONTEXT)->disp.set_fence_APPLE)(AGL_MACRO_CONTEXT_RENDERER, fence)

#define glIsFenceAPPLE(fence) \
	(*(AGL_MACRO_CONTEXT)->disp.is_fence_APPLE)(AGL_MACRO_CONTEXT_RENDERER, fence)

#define glTestFenceAPPLE(fence) \
	(*(AGL_MACRO_CONTEXT)->disp.test_fence_APPLE)(AGL_MACRO_CONTEXT_RENDERER, fence)

#define glFinishFenceAPPLE(fence) \
	(*(AGL_MACRO_CONTEXT)->disp.finish_fence_APPLE)(AGL_MACRO_CONTEXT_RENDERER, fence)

#define glTestObjectAPPLE(object, name) \
	(*(AGL_MACRO_CONTEXT)->disp.test_object_APPLE)(AGL_MACRO_CONTEXT_RENDERER, object, name)

#define glFinishObjectAPPLE(object, name) \
	(*(AGL_MACRO_CONTEXT)->disp.finish_object_APPLE)(AGL_MACRO_CONTEXT_RENDERER, object, name)

/* GL_APPLE_vertex_array_range */
#define glVertexArrayRangeAPPLE(length, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_array_range_EXT)(AGL_MACRO_CONTEXT_RENDERER, length, pointer)

#define glFlushVertexArrayRangeAPPLE(length, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.flush_vertex_array_range_EXT)(AGL_MACRO_CONTEXT_RENDERER, length, pointer)

#define glVertexArrayParameteriAPPLE(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.vertex_array_parameteri_EXT)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

/* GL_APPLE_vertex_array_object */
#define glBindVertexArrayAPPLE(id) \
	(*(AGL_MACRO_CONTEXT)->disp.bind_vertex_array_EXT)(AGL_MACRO_CONTEXT_RENDERER, id)

#define glDeleteVertexArraysAPPLE(n, ids) \
	(*(AGL_MACRO_CONTEXT)->disp.delete_vertex_arrays_EXT)(AGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glGenVertexArraysAPPLE(n, ids) \
	(*(AGL_MACRO_CONTEXT)->disp.gen_vertex_arrays_EXT)(AGL_MACRO_CONTEXT_RENDERER, n, ids)

#define glIsVertexArrayAPPLE(id) \
	(*(AGL_MACRO_CONTEXT)->disp.is_vertex_array_EXT)(AGL_MACRO_CONTEXT_RENDERER, id)

/* GL_APPLE_element_array */
#define glElementPointerAPPLE(type, pointer) \
	(*(AGL_MACRO_CONTEXT)->disp.element_pointer_APPLE)(AGL_MACRO_CONTEXT_RENDERER, type, pointer)

#define glDrawElementArrayAPPLE(mode, first, count) \
	(*(AGL_MACRO_CONTEXT)->disp.draw_element_array_APPLE)(AGL_MACRO_CONTEXT_RENDERER, mode, first, count)

#define glDrawRangeElementArrayAPPLE(mode, start, end, first, count) \
	(*(AGL_MACRO_CONTEXT)->disp.draw_range_element_array_APPLE)(AGL_MACRO_CONTEXT_RENDERER, mode, start, end, first, count)

#define glMultiDrawElementArrayAPPLE(mode, first, count, primcount) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_draw_element_array_APPLE)(AGL_MACRO_CONTEXT_RENDERER, mode, first, count, primcount)

#define glMultiDrawRangeElementArrayAPPLE(mode, start, end, first, count, primcount) \
	(*(AGL_MACRO_CONTEXT)->disp.multi_draw_range_element_array_APPLE)(AGL_MACRO_CONTEXT_RENDERER, mode, start, end, first, count, primcount)

/* GL_APPLE_flush_render */
#define glFlushRenderAPPLE() \
	(*(AGL_MACRO_CONTEXT)->disp.flush_render_APPLE)(AGL_MACRO_CONTEXT_RENDERER)

#define glFinishRenderAPPLE() \
	(*(AGL_MACRO_CONTEXT)->disp.finish_render_APPLE)(AGL_MACRO_CONTEXT_RENDERER)

#define glSwapAPPLE() \
	(*(AGL_MACRO_CONTEXT)->disp.swap_APPLE)(AGL_MACRO_CONTEXT_RENDERER)


/*********** ATI Extensions *************************************************/

/* GL_ATI_separate_stencil */
#define glStencilOpSeparateATI(face, sfail, dpfail, dppass) \
	(*(AGL_MACRO_CONTEXT)->disp.stencil_op_separate_ATI)(AGL_MACRO_CONTEXT_RENDERER, face, sfail, dpfail, dppass)

#define glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask) \
	(*(AGL_MACRO_CONTEXT)->disp.stencil_func_separate_ATI)(AGL_MACRO_CONTEXT_RENDERER, frontfunc, backfunc, ref, mask)

/* GL_ATI_blend_equation_separate */
#define glBlendEquationSeparateATI glBlendEquationSeparateEXT

/* GL_ATI_pn_triangles */
#define glPNTrianglesiATI(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.pn_trianglesi_ATI)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPNTrianglesfATI(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.pn_trianglesf_ATI)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

/* GL_ATIX_pn_triangles */
#define glPNTrianglesiATIX glPNTrianglesiATI
#define glPNTrianglesfATIX glPNTrianglesfATI

/*********** NVIDIA Extensions **********************************************/

/* GL_NV_point_sprite */
#define glPointParameteriNV(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.point_parameteri)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glPointParameterivNV(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.point_parameteriv)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

/* GL_NV_register_combiners */
#define glCombinerParameterfvNV(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.combiner_parameterfv_NV)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glCombinerParameterfNV(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.combiner_parameterf_NV)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glCombinerParameterivNV(pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.combiner_parameteriv_NV)(AGL_MACRO_CONTEXT_RENDERER, pname, params)

#define glCombinerParameteriNV(pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.combiner_parameteri_NV)(AGL_MACRO_CONTEXT_RENDERER, pname, param)

#define glCombinerInputNV(stage, portion, variable, input, mapping ,componentUsage) \
	(*(AGL_MACRO_CONTEXT)->disp.combiner_input_NV)(AGL_MACRO_CONTEXT_RENDERER, stage, portion, variable, input, mapping ,componentUsage)

#define glCombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDoProduct, muxSum) \
	(*(AGL_MACRO_CONTEXT)->disp.combiner_output_NV)(AGL_MACRO_CONTEXT_RENDERER, stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDoProduct, muxSum)

#define glFinalCombinerInputNV(variable, input, mapping, componentUsage) \
	(*(AGL_MACRO_CONTEXT)->disp.final_combiner_input_NV)(AGL_MACRO_CONTEXT_RENDERER, variable, input, mapping, componentUsage)

#define glGetCombinerInputParameterfvNV(stage, portion, variable, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_combiner_input_parameterfv_NV)(AGL_MACRO_CONTEXT_RENDERER, stage, portion, variable, pname, params)

#define glGetCombinerInputParameterivNV(stage, portion, variable, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_combiner_input_parameteriv_NV)(AGL_MACRO_CONTEXT_RENDERER, stage, portion, variable, pname, params)

#define glGetCombinerOutputParameterfvNV(stage, portion, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_combiner_output_parameterfv_NV)(AGL_MACRO_CONTEXT_RENDERER, stage, portion, pname, params)

#define glGetCombinerOutputParameterivNV(stage, portion, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_combiner_output_parameteriv_NV)(AGL_MACRO_CONTEXT_RENDERER, stage, portion, pname, params)

#define glGetFinalCombinerInputParameterfvNV(variable, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_final_combiner_input_parameterfv_NV)(AGL_MACRO_CONTEXT_RENDERER, variable, pname, params)

#define glGetFinalCombinerInputParameterfvNV(variable, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.get_final_combiner_input_parameterfv_NV)(AGL_MACRO_CONTEXT_RENDERER, variable, pname, params)

/* GL_NV_register_combiners2 */
#define glCombinerStageParameterfvNV(stage, pname, params) \
	(*(AGL_MACRO_CONTEXT)->disp.combiner_stage_parameterfv_NV)(AGL_MACRO_CONTEXT_RENDERER, stage, pname, params)

#define glGetCombinerStageParameterfvNV(stage, pname, param) \
	(*(AGL_MACRO_CONTEXT)->disp.get_combiner_stage_parameterfv_NV)(AGL_MACRO_CONTEXT_RENDERER, stage, pname, param)

#endif /* _AGLMACRO_H */

