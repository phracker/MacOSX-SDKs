//******************************************************************************
// Copyright:  (c) 2010-2012 by Apple, Inc., All Rights Reserved.
//*****************************************************************************/

#ifndef __GRANDCL_PRIV_H
#define __GRANDCL_PRIV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <OpenCL/opencl.h>

// Internal type used to map blocks to kernels
typedef struct {
  void *block_ptr;  // block pointer
  cl_kernel kernel; // associated kernel
} block_kernel_pair;

typedef struct block_kernel_map {
  cl_program         program;
  const size_t       num_kernels;
  void (*initBlocks)(void);
  block_kernel_pair *map;
} block_kernel_map;

// Table of block_kernel_map
typedef struct block_kernel_map_table {
  block_kernel_map** table;
  size_t             size;
  size_t             capacity;
} block_kernel_map_table;

// Structure to hold setting arguments
typedef struct kargs_struct {
  cl_bitfield *arg_flags;
  size_t *arg_sizes;
  void **arg_values;
} kargs_struct;

// Logging functions for situations that do and do not involve an underlying
// OpenCL error

void gcl_log_warning( const char* fmt, ... );
void gcl_log_error( const char* fmt, ... );
void gcl_log_fatal( const char* fmt, ... ) __attribute__((noreturn));
void gcl_log_cl_error( int err, const char* fmt, ... );
void gcl_log_cl_fatal( int err, const char* fmt, ... );

// Helper function to create and initialize and delete setting arguments
// in a kernel
void gclCreateArgsAPPLE(cl_kernel k, kargs_struct *args);
void gclDeleteArgsAPPLE(cl_kernel k, kargs_struct *args);

// Helper function used to set a by value argument on a kernel.
int gclSetKernelArgAPPLE(cl_kernel k, cl_uint arg_index,
                             size_t arg_size, const void *arg_value,
                             kargs_struct* args);

// Helper function used to set a cl_mem kernel argument.
int gclSetKernelArgMemAPPLE(cl_kernel k, cl_uint arg_index,
                                const void *arg_value,
                                kargs_struct* args);

// Helper function used to set a sampler_t kernel argument
int gclSetKernelArgSamplerAPPLE(cl_kernel k, cl_uint arg_index,
                                const void *arg_value,
                                kargs_struct* args, cl_sampler* sampler);
  
int gclReleaseSampler(cl_sampler sampler);
  
// Helper function to execute the kernel
int gclExecKernelAPPLE(cl_kernel k, const cl_ndrange *ndrange,
                            kargs_struct* args);

// Helper function to build program
int gclBuildProgramAPPLE(char* filename, block_kernel_map *map);

// Helper function to build a kernel using a portable binary where filename
// is the relative path from the app to the file (without the suffix).
int gclBuildProgramBinaryAPPLE(const char* filename, const char* bundle_id,
                               block_kernel_map *map, const char* build_opts);

// Helper function to register a block_kernel_map to the framework
void gclRegisterBlockKernelMap(block_kernel_map* map);

#ifdef __cplusplus
}
#endif

#endif // __GRANDCL_PRIV_H
