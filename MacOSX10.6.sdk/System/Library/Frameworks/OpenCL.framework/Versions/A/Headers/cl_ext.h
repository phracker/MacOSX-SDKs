/*******************************************************************************
 * Copyright:  (c) 2007-2009 by Apple, Inc., All Rights Reserved.
 ******************************************************************************/

#ifndef __CL_EXT_H
#define __CL_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <OpenCL/cl.h>
#include <AvailabilityMacros.h>

// Memory object destruction
//
// Apple extension for use to manage externally allocated buffers used with cl_mem objects with CL_MEM_USE_HOST_PTR
//
// Registers a user callback function that will be called when the memory object is deleted and its resources 
// freed. Each call to clSetMemObjectCallbackFn registers the specified user callback function on a callback 
// stack associated with memobj. The registered user callback functions are called in the reverse order in 
// which they were registered. The user callback functions are called and then the memory object is deleted 
// and its resources freed. This provides a mechanism for the application (and libraries) using memobj to be 
// notified when the memory referenced by host_ptr, specified when the memory object is created and used as 
// the storage bits for the memory object, can be reused or freed.
//
// The application may not call CL api's with the cl_mem object passed to the pfn_notify.
//
// Please check for the "cl_APPLE_SetMemObjectDestructor" extension using clGetDeviceInfo(CL_DEVICE_EXTENSIONS)
// before using.
cl_int	clSetMemObjectDestructorAPPLE(  cl_mem /* memobj */, 
                                        void (* /*pfn_notify*/)( cl_mem /* memobj */, void* /*user_data*/), 
                                        void * /*user_data */ )             CL_EXTENSION_WEAK_LINK AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  


// Context Logging Functions
//
// The next three convenience functions are intended to be used as the pfn_notify parameter to clCreateContext().
// Please check for the "cl_APPLE_ContextLoggingFunctions" extension using clGetDeviceInfo(CL_DEVICE_EXTENSIONS)
// before using.
//
// clLogMessagesToSystemLog fowards on all log messages to the Apple System Logger 
extern void clLogMessagesToSystemLogAPPLE(  const char * /* errstr */, 
                                            const void * /* private_info */, 
                                            size_t       /* cb */, 
                                            void *       /* user_data */ )  CL_EXTENSION_WEAK_LINK AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// clLogMessagesToStdout sends all log messages to the file descriptor stdout
extern void clLogMessagesToStdoutAPPLE(   const char * /* errstr */, 
                                          const void * /* private_info */, 
                                          size_t       /* cb */, 
                                          void *       /* user_data */ )    CL_EXTENSION_WEAK_LINK AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

// clLogMessagesToStderr sends all log messages to the file descriptor stderr
extern void clLogMessagesToStderrAPPLE(   const char * /* errstr */, 
                                          const void * /* private_info */, 
                                          size_t       /* cb */, 
                                          void *       /* user_data */ )    CL_EXTENSION_WEAK_LINK AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    

// Symbol for cl_khr_fp64 extension, supported by some devices.
#define CL_DEVICE_DOUBLE_FP_CONFIG          0x1032


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


#ifdef __cplusplus
}
#endif


#endif /* __CL_EXT_H */
