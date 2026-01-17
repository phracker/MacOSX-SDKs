/*******************************************************************************
 * Copyright (c) 2008 - 2012 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and/or associated documentation files (the
 * "Materials"), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 ******************************************************************************/

#ifndef __CL_EXT_H
#define __CL_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <OpenCL/cl.h>
#include <AvailabilityMacros.h>

/* enum can be used if cl_khr_fp64 extension is supported by the OpenCL implementation. */
#define CL_DEVICE_DOUBLE_FP_CONFIG                  0x1032

/* enum can be used if cl_khr_fp16 extension is supported by the OpenCL implementation. */
#define CL_DEVICE_HALF_FP_CONFIG                    0x1033
  
/*
 * Apple extensions:
 *  Apple has been allocated a block of identifiers starting at 0x10000000, and error codes in the range 
 *  -1060 ... -1091.
 */
    
/* Memory object destruction
 *
 * Apple extension for use to manage externally allocated buffers used with cl_mem objects with CL_MEM_USE_HOST_PTR
 *
 * Registers a user callback function that will be called when the memory object is deleted and its resources 
 * freed. Each call to clSetMemObjectCallbackFn registers the specified user callback function on a callback 
 * stack associated with memobj. The registered user callback functions are called in the reverse order in 
 * which they were registered. The user callback functions are called and then the memory object is deleted 
 * and its resources freed. This provides a mechanism for the application (and libraries) using memobj to be 
 * notified when the memory referenced by host_ptr, specified when the memory object is created and used as 
 * the storage bits for the memory object, can be reused or freed.
 *
 * The application may not call CL api's with the cl_mem object passed to the pfn_notify.
 *
 * Please check for the "cl_APPLE_SetMemObjectDestructor" extension using clGetDeviceInfo(CL_DEVICE_EXTENSIONS)
 * before using.
 *
 * NOTE:  This feature is a core feature in OpenCL 1.1. Please use clSetMemObjectDestructorCallback instead.
 */

/* *** DEPRECATED! **** Please use the equivalent standard function clSetMemObjectDestructor instead. It was added in OpenCL 1.1. */
cl_int	clSetMemObjectDestructorAPPLE(  cl_mem                  /* memobj */, 
                                        void (CL_CALLBACK *    /*pfn_notify*/)( cl_mem /* memobj */, void* /*user_data*/), 
                                        void *                 /*user_data */ ) CL_EXT_SUFFIX__VERSION_1_0_DEPRECATED;

/* Context Logging Functions
 *
 * The next three convenience functions are intended to be used as the pfn_notify parameter to clCreateContext().
 * Please check for the "cl_APPLE_ContextLoggingFunctions" extension using clGetDeviceInfo(CL_DEVICE_EXTENSIONS)
 * before using.  Note that if you pass NULL to the clCreateContext pfn_notify parameter, you can also use these
 * by setting the CL_LOG_ERRORS environment variable to one of stdout, stderr, or console.  Pass your own do-nothing
 * context logging function to disable the CL_LOG_ERRORS override.
 *
 * clLogMessagesToSystemLog fowards on all log messages to the Apple System Logger 
 */
extern void clLogMessagesToSystemLogAPPLE(  const char * /* errstr */, 
                                            const void * /* private_info */, 
                                            size_t       /* cb */, 
                                            void *       /* user_data */ )  CL_EXT_SUFFIX__VERSION_1_0 CL_DEPRECATED(10.6, 10.14);

/* clLogMessagesToStdout sends all log messages to the file descriptor stdout   */
extern void clLogMessagesToStdoutAPPLE(   const char * /* errstr */, 
                                          const void * /* private_info */, 
                                          size_t       /* cb */, 
                                          void *       /* user_data */ )    CL_EXT_SUFFIX__VERSION_1_0 CL_DEPRECATED(10.6, 10.14);

/* clLogMessagesToStderr sends all log messages to the file descriptor stderr   */
extern void clLogMessagesToStderrAPPLE(   const char * /* errstr */, 
                                          const void * /* private_info */, 
                                          size_t       /* cb */, 
                                          void *       /* user_data */ )    CL_EXT_SUFFIX__VERSION_1_0 CL_DEPRECATED(10.6, 10.14);
    
/* Extension: cl_APPLE_clut 
 * New APIs that allow apps to reduce the number of CL API calls they need to make
 * to setup CL before a kernel can be enqueued for execution.   
 */
extern CL_API_ENTRY cl_int CL_API_CALL clCreateContextAndCommandQueueAPPLE(
                                                  const cl_context_properties * /* properties */,
                                                  cl_uint                       /* num_devices */,
                                                  const cl_device_id *          /* devices */,
                                                  void ( CL_CALLBACK *          /*pfn_notify*/)(const char * /* errinfo */, const void * /* private_info */, size_t /* cb */, void * /* user_data */),
                                                  void *                        /* user_data */,
                                                  cl_command_queue_properties   /* queue_properties */,
                                                  cl_context *                  /* context */,
                                                  cl_command_queue *            /* queues */)   CL_EXT_SUFFIX__VERSION_1_1 CL_DEPRECATED(10.7, 10.14);

extern CL_API_ENTRY cl_int CL_API_CALL clCreateProgramAndKernelsWithSourceAPPLE(
                                                       cl_context           /* context */,
                                                       cl_uint              /* count */,
                                                       const char **        /* program_source_strings */,
                                                       const size_t *       /* program_source_lengths */,
                                                       cl_uint              /* num_devices */,
                                                       const cl_device_id * /* device_list */,
                                                       const char *         /* options */,
                                                       cl_uint              /* num_kernels */,
                                                       const char **        /* kernel_name_strings */,
                                                       cl_program *         /* program */,
                                                       cl_kernel *          /* kernels */)   CL_EXT_SUFFIX__VERSION_1_1 CL_DEPRECATED(10.7, 10.14);

extern CL_API_ENTRY cl_int CL_API_CALL clSetKernelArgsListAPPLE(cl_kernel /* kernel */, 
                                                                cl_uint   /* num_args */, 
                                                                ... )   CL_EXT_SUFFIX__VERSION_1_1 CL_DEPRECATED(10.7, 10.14);

extern CL_API_ENTRY cl_int CL_API_CALL clSetKernelArgsVaListAPPLE(cl_kernel /* kernel */, 
                                                                  cl_uint   /* num_args */, 
                                                                  va_list   /* argp */)   CL_EXT_SUFFIX__VERSION_1_1 CL_DEPRECATED(10.7, 10.14);

#define CL_INVALID_ARG_NAME_APPLE   -1060
extern CL_API_ENTRY cl_int CL_API_CALL clSetKernelArgByNameAPPLE(cl_kernel    /* kernel */,                                         
                                                                 const char * /* arg_name */,
                                                                 size_t       /* arg_size */,
                                                                 const void * /* arg_value */) CL_EXT_SUFFIX__VERSION_1_1 CL_DEPRECATED(10.7, 10.14);

/* Extension: cl_APPLE_query_kernel_names
 * 
 * These selectors may be passed to clGetProgramInfo to obtain information about the kernel functions in a cl_program.
 * The cl_program must be successfully built with clBuildProgram for at least one device to succeed. Otherwise CL_INVALID_PROGRAM_EXECUTABLE is returned.
 */
#define CL_PROGRAM_NUM_KERNELS_APPLE                      0x10000004    /* Introduced in MacOS X.7.  Returns a cl_uint for number of kernels in program. */
#define CL_PROGRAM_KERNEL_NAMES_APPLE                     0x10000005    /* Introduced in MacOS X.7.  Returns a ';' delimited char[] containing the names of kernels in program */

/* Extension: cl_APPLE_fixed_alpha_channel_orders
 *
 * These selectors may be passed to clCreateImage2D() in the cl_image_format.image_channel_order field.
 * They are like CL_BGRA and CL_ARGB except that the alpha channel to be ignored.  On calls to read_imagef, 
 * the alpha will be 0xff (1.0f) if the sample falls in the image and 0 if it does not fall in the image. 
 * On calls to write_imagef, the alpha value is ignored and 0xff (1.0f) is written. These formats are 
 * currently only available for the CL_UNORM_INT8 cl_channel_type. They are intended to support legacy
 * image formats. 
 */
#define CL_1RGB_APPLE                                     0x10000006      /* Introduced in MacOS X.7. */
#define CL_BGR1_APPLE                                     0x10000007      /* Introduced in MacOS X.7. */

/* Extension: cl_APPLE_biased_fixed_point_image_formats
 *
 * This selector may be passed to clCreateImage2D() in the cl_image_format.image_channel_data_type field.
 * It defines a biased signed 1.14 fixed point storage format, with range [-1, 3). The conversion from
 * float to this fixed point format is defined as follows:
 *
 *      ushort float_to_sfixed14( float x ){
 *          int i = convert_int_sat_rte( x * 0x1.0p14f );         // scale [-1, 3.0) to [-16384, 3*16384), round to nearest integer
 *          i = add_sat( i, 0x4000 );                             // apply bias, to convert to [0, 65535) range
 *          return convert_ushort_sat(i);                         // clamp to destination size
 *      }
 *
 * The inverse conversion is the reverse process. The formats are currently only available on the CPU with
 * the CL_RGBA channel layout.
 */
#define CL_SFIXED14_APPLE                                 0x10000008      /* Introduced in MacOS X.7. */ 
#define CL_BIASED_HALF_APPLE                              0x10000009      /* Introduced in MacOS X.7. */ 


  
/* Extension: YUV image support 
 * 
 * These formats can only be used when creating images from YUV 4:2:2 IOSurface, using the
 * clCreateImageFromIOSurface2DAPPLE() API. These formats are only available for the CL_UNORM_INT8, 
 * CL_UNSIGNED_INT8, and CL_SIGNED_INT8 cl_channel_type.
 */
#define CL_YCbYCr_APPLE                                   0x10000010      /* Introduced in MacOS X.7. */
#define CL_CbYCrY_APPLE                                   0x10000011      /* Introduced in MacOS X.7. */
  
/* Extension: ABGR and xBGR formats for CoreImage CL-GPU support */
#define CL_ABGR_APPLE                                     0x10000012

    
/* Extension: cl_APPLE_fp64_ops
 *
 * This extension if enabled supports double-precision basic arithmetic operations (add, sub, mul, divide and sqrt)
 * This is a subset of the cl_khr_fp64 extension defined in the OpenCL 1.1 and 1.2 specifications.
 * The precision values for these basic operations are the same as defined by the cl_khr_fp64 extension
 */
 
  
/* Extension: clCreateDAGAPPLE
 *
 * Create a DAG object which owns the individual program fragments (DAG nodes)
 * used to create the final kernel. If the context is invalid, returns
 * NULL for the dag.
 */
typedef struct _cl_dag * cl_dag;
typedef int              cl_dag_node;
  
cl_dag clCreateDAGAPPLE(cl_context c) CL_EXT_SUFFIX__VERSION_1_2 CL_DEPRECATED(10.8, 10.14);

/* Extension: clReleaseDAGAPPLE
 * Release a DAG object used to create the final kernel
 */
void clReleaseDAGAPPLE(cl_dag dag) CL_EXT_SUFFIX__VERSION_1_2 CL_DEPRECATED(10.8, 10.14);

/* Extension: clGetDAGNodeAPPLE
 * For a given function 'f' created with clCreateDAGAPPLE(), set 0 or more
 * arguments from args at their corresponding index in 'arg_indices'.  For 
 * functions:
 *
 * void foo(float4, float4);
 * float4 bar(float4);
 *
 * You can set either the 1st, 2nd, or both inputs to foo() with the output of
 * bar() by passing the bar() cl_dag_node one or more times in args().  
 * Argument indices which are unset by this function are required to be 
 * set by a clSetKernelArg() call on 'f' for each unset argument prior to 
 * clEnqueueNDRangeKernel() on the output of clCreateKernelFromDAGAPPLE().
 */
cl_dag_node clGetDAGNodeAPPLE(cl_dag d, cl_kernel f, cl_dag_node *args,
                              unsigned *arg_indices, unsigned nargs) CL_EXT_SUFFIX__VERSION_1_2 CL_DEPRECATED(10.8, 10.14);

/* Extension:  clCreateKernelFromDAGAPPLE
 * Given a DAG, ask CVMS to create a functional kernel from it.
 */
cl_kernel clCreateKernelFromDAGAPPLE(cl_dag d, cl_uint n,
                                     const cl_device_id *list) CL_EXT_SUFFIX__VERSION_1_2 CL_DEPRECATED(10.8, 10.14);
  
/* Extension: clCreateCommandQueueWithPropertiesAPPLE
 * Create a command queue for the specified device. The properties array
 * specifies a list of command queue property names and their corresponding
 * values.  Each property name is immediately followed by the corresponding
 * value.  The list is terminated with 0.
 *
 * List of supported properties are:
 *
 * CL_QUEUE_PROPERTIES                  cl_command_queue_properties bitfield
 *                                      ( CL_QUEUE_PROFILING_ENABLE,
 *                                        CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)
 *
 * CL_COMMAND_QUEUE_PRIORITY_APPLE      cl_queue_properties_APPLE
 *                                      ( CL_COMMAND_QUEUE_PRIORITY_DEFAULT_APPLE,
 *                                        CL_COMMAND_QUEUE_PRIORITY_BACKGROUND_APPLE )
 *
 * These properties may only be used if the cl_APPLE_command_queue_priority is
 * supported by the device.
 *
 * CL_COMMAND_QUEUE_NUM_COMPUTE_UNITS_APPLE int (value can be 1 .. CL_DEVICE_MAX_COMPUTE_UNITS).
 *
 * This property may only be used if the
 * cl_APPLE_command_queue_select_compute_units extension is supported by the
 * device.
 */
#define cl_APPLE_command_queue_priority 1
#define cl_APPLE_command_queue_select_compute_units 1
  
  typedef intptr_t cl_queue_properties_APPLE;
  
  extern CL_API_ENTRY cl_command_queue CL_API_CALL
  clCreateCommandQueueWithPropertiesAPPLE (cl_context                          /* context */,
                                           cl_device_id                        /* device */,
                                           const cl_queue_properties_APPLE *   /* properties */,
                                           cl_int *                            /* errcode_ret */) CL_EXT_SUFFIX__VERSION_1_2 CL_DEPRECATED(10.8, 10.14);
#define CL_QUEUE_PRIORITY_APPLE                           0x10000013
#define CL_QUEUE_NUM_COMPUTE_UNITS_APPLE                  0x10000014
#define CL_QUEUE_PRIORITY_BACKGROUND_APPLE                0x10000015
#define CL_QUEUE_PRIORITY_DEFAULT_APPLE                   0x10000016

/* Application can pass context name in the property list when calling clCreateContext.
 * This will let us do application specific "stuff" in framework. As an example
 * CoreImage passes context name "CoreImage" and use it to perform flush right after
 * clEnqueueNDRangeKernel when CoreImage enqueues a large kernel (in terms of number of global work items)
 * on weak GPU because we know it improves performance to start large work on weak GPU right away
*/
  
#define CL_OBJECT_NAME_APPLE                               0x10000018


/*
 * Enums for CL_YCbCr formats
*/


/* 64-bit (cl_ulong) IOKit registryID for this device. May be zero for pure software devices. */
#define CL_DEVICE_REGISTRY_ID_APPLE               0x10000030
/* cl_bool that reports whether this device is removable or not (eGPU) */
#define CL_DEVICE_REMOVABLE_APPLE                 0x10000031
	
#ifdef __cplusplus
}
#endif


#endif /* __CL_EXT_H */
