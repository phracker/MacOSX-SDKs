#ifndef __gl3ext_h_
#define __gl3ext_h_

#ifdef __cplusplus
extern "C" {
#endif


#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#if defined(__APPLE__)
#define GL3_PROTOTYPES
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif


#define GL_ARB_instanced_arrays                    1
#define GL_ARB_occlusion_query2                    1
#define GL_ARB_sampler_objects                     1
#define GL_ARB_shader_bit_encoding                 1
#define GL_ARB_texture_rgb10_a2ui                  1
#define GL_ARB_timer_query                         1
#define GL_EXT_depth_bounds_test                   1
#define GL_EXT_framebuffer_multisample_blit_scaled 1
#define GL_EXT_texture_compression_s3tc            1
#define GL_EXT_texture_filter_anisotropic          1
#define GL_EXT_texture_mirror_clamp                1
#define GL_APPLE_client_storage                    1
#define GL_APPLE_container_object_shareable        1
#define GL_APPLE_object_purgeable                  1
#define GL_APPLE_rgb_422                           1
#define GL_APPLE_texture_range                     1

/****** Enums ************************************************/

#if GL_ARB_instanced_arrays
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB  0x88FE
#endif

#if GL_ARB_occlusion_query2
#define GL_ANY_SAMPLES_PASSED               0x8C2F
#endif

#if GL_ARB_sampler_objects
#define GL_SAMPLER_BINDING                  0x8919
#endif

#if GL_ARB_shader_bit_encoding
#endif

#if GL_ARB_texture_rgb10_a2ui
#define GL_RGB10_A2UI                       0x906F
#endif 

#if GL_ARB_timer_query
#define GL_TIME_ELAPSED                     0x88BF
#define GL_TIMESTAMP                        0x8E28
#endif

#if GL_EXT_depth_bounds_test
#define GL_DEPTH_BOUNDS_TEST_EXT            0x8890
#define GL_DEPTH_BOUNDS_EXT                 0x8891
#endif

#if GL_EXT_framebuffer_multisample_blit_scaled
#define GL_SCALED_RESOLVE_FASTEST_EXT       0x90BA
#define GL_SCALED_RESOLVE_NICEST_EXT        0x90BB
#endif

#if GL_EXT_texture_compression_s3tc
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT     0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT    0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT    0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT    0x83F3
#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT       0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#endif

#if GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT       0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT   0x84FF
#endif

#if GL_EXT_texture_mirror_clamp
#define GL_MIRROR_CLAMP_EXT                 0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_EXT         0x8743
#define GL_MIRROR_CLAMP_TO_BORDER_EXT       0x8912
#endif

#if GL_APPLE_client_storage
#define GL_UNPACK_CLIENT_STORAGE_APPLE      0x85B2
#endif

#if GL_APPLE_object_purgeable
#define GL_RELEASED_APPLE                   0x8A19
#define GL_VOLATILE_APPLE                   0x8A1A
#define GL_RETAINED_APPLE                   0x8A1B
#define GL_UNDEFINED_APPLE                  0x8A1C
#define GL_PURGEABLE_APPLE                  0x8A1D
#endif

#if GL_APPLE_rgb_422
#define GL_RGB_422_APPLE                    0x8A1F
#define GL_UNSIGNED_SHORT_8_8_APPLE         0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE     0x85BB
#endif

#if GL_APPLE_texture_range
#define GL_TEXTURE_RANGE_LENGTH_APPLE       0x85B7
#define GL_TEXTURE_RANGE_POINTER_APPLE      0x85B8
#define GL_TEXTURE_STORAGE_HINT_APPLE       0x85BC
#define GL_TEXTURE_MINIMIZE_STORAGE_APPLE   0x85B6
#define GL_STORAGE_PRIVATE_APPLE            0x85BD
#define GL_STORAGE_CACHED_APPLE             0x85BE
#define GL_STORAGE_SHARED_APPLE             0x85BF
#endif

/****** Functions Prototypes *********************************/

#if GL_ARB_instanced_arrays
#ifdef GL3_PROTOTYPES
extern void glVertexAttribDivisorARB(GLuint index, GLuint divisor);
#endif /* GL3_PROTOTYPES */
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORARBPROC) (GLuint index, GLuint divisor);
#endif

#if GL_ARB_sampler_objects
#ifdef GL3_PROTOTYPES
extern void glGenSamplers(GLsizei count, GLuint *samplers);
extern void glDeleteSamplers(GLsizei count, const GLuint *samplers);
extern GLboolean glIsSampler(GLuint sampler);
extern void glBindSampler(GLenum unit, GLuint sampler);
extern void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param);
extern void glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param);
extern void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param);
extern void glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param);
extern void glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint *param);
extern void glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint *param);
extern void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params);
extern void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params);
extern void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint *params);
extern void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint *params);
#endif /* GL3_PROTOTYPES */
typedef void (APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei count, GLuint *samplers);
typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei count, const GLuint *samplers);
typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
typedef void (APIENTRYP PFNGLBINDSAMPLERPROC) (GLenum unit, GLuint sampler);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, const GLfloat *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, const GLuint *param);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
#endif

#if GL_ARB_timer_query
#ifdef GL3_PROTOTYPES
extern void glQueryCounter (GLuint id, GLenum target);
extern void glGetQueryObjecti64v (GLuint id, GLenum pname, GLint64 *params);
extern void glGetQueryObjectui64v (GLuint id, GLenum pname, GLuint64 *params);
#endif /* GL3_PROTOTYPES */
typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC) (GLuint id, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64 *params);
#endif

#if GL_EXT_depth_bounds_test
#ifdef GL3_PROTOTYPES
typedef void (APIENTRYP PFNGLDEPTHBOUNDSEXTPROC) (GLclampd zmin, GLclampd zmax);
#else
extern void glDepthBoundsEXT(GLclampd zmin, GLclampd zmax);
#endif /* GL3_PROTOTYPES */
#endif

#if GL_APPLE_object_purgeable
#ifdef GL3_PROTOTYPES
extern GLenum glObjectPurgeableAPPLE(GLenum objectType, GLuint name, GLenum option);
extern GLenum glObjectUnpurgeableAPPLE(GLenum objectType, GLuint name, GLenum option);
extern void   glGetObjectParameterivAPPLE(GLenum objectType, GLuint name, GLenum pname, GLint *params);
#endif /* GL3_PROTOTYPES */
typedef GLenum (APIENTRYP PFNGLOBJECTPURGEABLEAPPLEPROC) (GLenum objectType, GLuint name, GLenum option);
typedef GLenum (APIENTRYP PFNGLOBJECTUNPURGABLEAPPLEPROC) (GLenum objectType, GLuint name, GLenum option);
typedef void (APIENTRYP PFNGLGETOBJECTPARAMETERIVAPPLEPROC) (GLenum objectType, GLuint name, GLenum pname, GLint *params);
#endif

#if GL_APPLE_texture_range
#ifdef GL3_PROTOTYPES
extern void glTextureRangeAPPLE(GLenum target, GLsizei length, const GLvoid *pointer);
extern void glGetTexParameterPointervAPPLE(GLenum target, GLenum pname, GLvoid **params);
#endif /* GL3_PROTOTYPES */
typedef void (APIENTRYP PFNGLTEXTURERANGLEAPPLEPROC) (GLenum target, GLsizei length, const GLvoid *pointer);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC) (GLenum target, GLenum pname, GLvoid **params);
#endif

#ifdef __cplusplus
}
#endif

#endif
