/*******************************************************************************
 * Copyright:  (c) 2010-2012 by Apple, Inc., All Rights Reserved.
 ******************************************************************************/

#ifndef __GCL_H
#define __GCL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdint.h>
#include <AvailabilityMacros.h>

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER
#include <IOSurface/IOSurface.h>
#endif

#include <OpenGL/gltypes.h>

#include <OpenCL/opencl.h>
#include <dispatch/dispatch.h>
  
typedef struct _cl_ndrange {
  size_t work_dim;
  size_t global_work_offset[3];
  size_t global_work_size[3];
  size_t local_work_size[3];
} cl_ndrange;
  
typedef cl_mem cl_image;
typedef uint64_t cl_timer;
typedef uintptr_t sampler_t;
typedef cl_bitfield cl_queue_flags;
typedef cl_bitfield cl_malloc_flags;

typedef cl_mem_object_type cl_image_type;
#define CL_IMAGE_2D CL_MEM_OBJECT_IMAGE2D
#define CL_IMAGE_3D CL_MEM_OBJECT_IMAGE3D

#define CL_DISPATCH_QUEUE_PRIORITY_DEFAULT  (cl_ulong)0
#define CL_DISPATCH_QUEUE_PRIORITY_LOW      ((cl_ulong)1 << 63)
#define CL_DISPATCH_QUEUE_PRIORITY_HIGH     ((cl_ulong)1 << 62)  
#define CL_DEVICE_TYPE_USE_ID               ((cl_ulong)1 << 61)
  
typedef enum clk_sampler_type
{
    __CLK_ADDRESS_BASE             = 0,
    CLK_ADDRESS_NONE               = 0 << __CLK_ADDRESS_BASE,
    CLK_ADDRESS_CLAMP              = 1 << __CLK_ADDRESS_BASE,
    CLK_ADDRESS_CLAMP_TO_EDGE      = 2 << __CLK_ADDRESS_BASE,
    CLK_ADDRESS_REPEAT             = 3 << __CLK_ADDRESS_BASE,
    CLK_ADDRESS_MIRRORED_REPEAT    = 4 << __CLK_ADDRESS_BASE,
    __CLK_ADDRESS_MASK             = CLK_ADDRESS_NONE | CLK_ADDRESS_CLAMP | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_ADDRESS_REPEAT | CLK_ADDRESS_MIRRORED_REPEAT,
    __CLK_ADDRESS_BITS             = 3,        // number of bits required to represent address info
    
    __CLK_NORMALIZED_BASE          = __CLK_ADDRESS_BITS,
    CLK_NORMALIZED_COORDS_FALSE    = 0,
    CLK_NORMALIZED_COORDS_TRUE     = 1 << __CLK_NORMALIZED_BASE,
    __CLK_NORMALIZED_MASK          = CLK_NORMALIZED_COORDS_FALSE | CLK_NORMALIZED_COORDS_TRUE,
    __CLK_NORMALIZED_BITS          = 1,        // number of bits required to represent normalization 
    
    __CLK_FILTER_BASE              = __CLK_NORMALIZED_BASE + __CLK_NORMALIZED_BITS,
    CLK_FILTER_NEAREST             = 0 << __CLK_FILTER_BASE,
    CLK_FILTER_LINEAR              = 1 << __CLK_FILTER_BASE,
    __CLK_FILTER_MASK              = CLK_FILTER_NEAREST | CLK_FILTER_LINEAR,
    __CLK_FILTER_BITS              = 2         // number of bits required to represent address info

} clk_sampler_type;
  
  
//************************************************************************************************************************
// create a dispatch queue for an OpenCL device
//
// gcl_queue_flags can be a combination of the following
//      CL_DEVICE_TYPE_GPU, CL_DEVICE_TYPE_CPU or CL_DEVICE_TYPE_USE_DEVICE_ID
//      CL_CONCURRENT_QUEUE (only allowed for the CPU device)
//      CL_QUEUE_PRIORITY_LOW (default), CL_QUEUE_PRIORITY_DEFAULT or CL_QUEUE_PRIORITY_HIGH
//************************************************************************************************************************
#ifdef AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER
DISPATCH_RETURNS_RETAINED
#endif
extern dispatch_queue_t gcl_create_dispatch_queue(cl_queue_flags flags, 
                                                  cl_device_id device_id) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// The following APIs describe how to create OpenCL memory objects
//************************************************************************************************************************

//************************************************************************************************************************
// gcl_malloc() allocates a buffer object.  The void * value returned is a memory object handle.  The void * value returned 
// cannot be used to directly access the memory region on the host CPU.  To access this memory region for reading and 
// writing on the host CPU, use APIs such as gcl_memcpy that can be passed in a blocks to GCD APIs that queue tasks for 
// dispatch.
//
// flags can be 0, CL_MEM_USE_HOST_PTR, or CL_MEM_COPY_HOST_PTR.
//************************************************************************************************************************
extern void * gcl_malloc(size_t bytes, 
                         void *host_ptr, 
                         cl_malloc_flags flags) GCL_API_SUFFIX__VERSION_1_1;

extern void   gcl_free(void *ptr) GCL_API_SUFFIX__VERSION_1_1;

//**********************************************************************************************************************************
// gcl_create_image() creates a 2D image (depth = 1) or a 3D image (depth > 1).  
// This API can also be used to create an image from an IOSurfaceRef.
// A cl_image is equivalent to the cl_mem object returned by clCreateImage{2D|3D} and can be used by both GCL and OpenCL APIs.
//**********************************************************************************************************************************
extern cl_image gcl_create_image(const cl_image_format *image_format, 
                                 size_t image_width, 
                                 size_t image_height, 
                                 size_t image_depth, 
                                 IOSurfaceRef io_surface) GCL_API_SUFFIX__VERSION_1_1;
                                 
extern void gcl_retain_image(cl_image image) GCL_API_SUFFIX__VERSION_1_1;

extern void gcl_release_image(cl_image image) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// gcl_get_supported_image_formats() queries the image formats supported by the OpenCL device specified by device_id.
// image_type can be CL_MEM_OBJECT_IMAGE2D, or CL_MEM_OBJECT_IMAGE3D.  num_entries describes the number of image_formats
// available in image_formats, and num_image_formats, if not NULL, contains the number of formats returned by OpenCL.
// Note that a post-return num_image_formats == 0 indicates that an error occurred.
//************************************************************************************************************************
extern void gcl_get_supported_image_formats(cl_device_id device_id, 
                                            cl_image_type image_type, 
                                            unsigned int num_entries, 
                                            cl_image_format *image_formats, 
                                            unsigned int *num_image_formats) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// The following APIs are OpenCL commands that can be passed in a block(s) to the GCD APIs that queue tasks for dispatch 
// such as dispatch_async.  These commands are equivalent to the corresponding clEnqueue* API calls except that we can now 
// queue these commands directly to a dispatch queue instead of a CL command-queue. 
//************************************************************************************************************************
extern void gcl_memcpy(void *dst, 
                       const void *src, 
                       size_t size) GCL_API_SUFFIX__VERSION_1_1;

extern void gcl_memcpy_rect(void *dst, 
                            const void *src, 
                            const size_t dst_origin[3], 
                            const size_t src_origin[3], 
                            const size_t region[3],
                            size_t dst_row_pitch, 
                            size_t dst_slice_pitch, 
                            size_t src_row_pitch, 
                            size_t src_slice_pitch) GCL_API_SUFFIX__VERSION_1_1;

extern void gcl_copy_image(cl_image dst_image, 
                           cl_image src_image, 
                           const size_t dst_origin[3], 
                           const size_t src_origin[3], 
                           const size_t region[3]) GCL_API_SUFFIX__VERSION_1_1;

extern void gcl_copy_ptr_to_image(cl_mem dst_image, 
                                  void *src_ptr, 
                                  const size_t dst_origin[3], 
                                  const size_t region[3]) GCL_API_SUFFIX__VERSION_1_1;

extern void gcl_copy_image_to_ptr(void *dst_ptr, 
                                  cl_image src_image, 
                                  const size_t src_origin[3], 
                                  const size_t region[3]) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// The following map functions allow you to map a region of the buffer or image into the host address space
// for reading and/or writing.
//************************************************************************************************************************
  
extern void *gcl_map_ptr(void *ptr, 
                         cl_map_flags map_flags, 
                         size_t cb) GCL_API_SUFFIX__VERSION_1_1;
                         
extern void *gcl_map_image(cl_image image, 
                           cl_map_flags map_flags, 
                           const size_t origin[3], 
                           const size_t region[3]) GCL_API_SUFFIX__VERSION_1_1;
                           
extern void gcl_unmap(void *) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// gcl_create_kernel_from_block() is required to query the work-group size to use in cl_ndrange.local_work_size.  
// This is needed to ensure good performance across GPUs as the work-group sizes vary across GPUs.
//************************************************************************************************************************
extern cl_kernel gcl_create_kernel_from_block(void *kernel_block_ptr) GCL_API_SUFFIX__VERSION_1_1;

extern void gcl_get_kernel_block_workgroup_info(void *kernel_block_ptr, 
                                                cl_kernel_work_group_info param_name, 
                                                size_t param_value_size, 
                                                void *param_value, 
                                                size_t *param_value_size_ret) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// gcl_get_device_id_with_dispatch_queue() returns the cl_device_id.  This can then be used to query device information 
// using the clGetDeviceInfo OpenCL API.
//************************************************************************************************************************
extern cl_device_id gcl_get_device_id_with_dispatch_queue(dispatch_queue_t queue) GCL_API_SUFFIX__VERSION_1_1;
  
//************************************************************************************************************************
// gcl_set_finalizer() sets the finalizer function for any objects created by gcl_malloc or gcl_create_***  
// APIs (such as gcl_create_image)
//************************************************************************************************************************
extern void gcl_set_finalizer(void *object, 
                              void (*cl_pfn_finalizer)(void *object, void *user_data), 
                              void *user_data) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// The following APIs allows you to measure the time it takes to execute a set of CL commands in a block
// gcl_start_timer starts the timer.  gcl_stop_timer will return the time elapsed in seconds.
//************************************************************************************************************************
extern cl_timer gcl_start_timer(void) GCL_API_SUFFIX__VERSION_1_1;

extern double gcl_stop_timer(cl_timer t) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// Create a buffer cl_mem object from ptr returned by gcl_malloc. This cl_mem object can be used by CL API calls and enables
// sharing of objects between GCL and the OpenCL API. The cl_mem object references the data store associated with 
// ptr. The cl_mem objects created using gcl_create_buffer_from_ptr must be released before ptr is freed using gcl_free. 
//************************************************************************************************************************
extern cl_mem gcl_create_buffer_from_ptr(void *ptr) GCL_API_SUFFIX__VERSION_1_1;
  
//************************************************************************************************************************
// The following APIs implement sharing of OpenGL vertex buffer, texture and renderbuffer objects with OpenCL.
//
// A cl_image is equivalent to the cl_mem object returned by clCreateFromGLTexture{2D|3D} or clCreateFromGLRenderbuffer 
// and can be used by both GCL and OpenCL APIs.
//************************************************************************************************************************
extern void * gcl_gl_create_ptr_from_buffer(GLuint bufobj) GCL_API_SUFFIX__VERSION_1_1;

extern cl_image gcl_gl_create_image_from_texture(GLenum texture_target, 
                                                 GLint mip_level, 
                                                 GLuint texture) GCL_API_SUFFIX__VERSION_1_1;

extern cl_image gcl_gl_create_image_from_renderbuffer(GLuint render_buffer) GCL_API_SUFFIX__VERSION_1_1;
 
//************************************************************************************************************************
// The following APIs passed in a block(s) to a dispatch queue implement synchronization of commands between OpenGL and OpenCL.
//************************************************************************************************************************

//************************************************************************************************************************
// gcl_set_gl_sharegroup() specifies the GL ShareGroup used to create the GCL context.
// share is a sharegroup. This API must be called first before any other GCL API calls.
// This associates a GL sharegroup that is used to allocate objects (in CL and/or GL) and to enable CL / GL sharing.
//
// The sharegroup can only be specified once.
//************************************************************************************************************************
extern void gcl_gl_set_sharegroup(void* share) GCL_API_SUFFIX__VERSION_1_1;

//************************************************************************************************************************
// The following APIs allow the OpenCL objects underlying the GCL implementation to be obtained for interoperation 
// with legacy applications and libraries
//************************************************************************************************************************

//************************************************************************************************************************
// gcl_get_context() returns the cl_context used by all GCL dispatch queues. The context may not be retained or released.
//************************************************************************************************************************  
extern cl_context gcl_get_context(void) GCL_API_SUFFIX__VERSION_1_1;
  
#ifdef __cplusplus
}
#endif

#endif  /* __GCL_H  */
