//
//  bnns_graph.h
//  BasicNeuralNetworkSubroutines
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#ifndef __BNNS_GRAPH_HEADER__
#define __BNNS_GRAPH_HEADER__

#if __has_include(<TargetConditionals.h>)
# include <TargetConditionals.h>
#endif // __has_include(<TargetConditionals.h>)

#if __has_include( <Availability.h> )
#include <Availability.h>
#else
#define __API_AVAILABLE(...)
#define __API_DEPRECATED_WITH_REPLACEMENT(...)
#endif

#if __has_feature(objc_fixed_enum) || __has_extension(cxx_strong_enums)
#  define BNNS_ENUM(_name, _type, ...) \
typedef enum : _type { __VA_ARGS__ } _name
#else // __has_feature(objc_fixed_enum) || __has_extension(cxx_strong_enums)
#  define BNNS_ENUM(_name, _type, ...) \
enum { __VA_ARGS__ }; typedef _type _name
#endif// __has_feature(objc_fixed_enum) || __has_extension(cxx_strong_enums)

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull begin")
#else
#define _Null_unspecified
#define _Nullable
#define _Nonnull
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Data types

/// The compiled version of a graph that can be executed by BNNS.
/// This object may be written to a file and mmap'd into read-only memory at a future time for execution through a call to
/// `BNNSGraphExecute()` or `BNNSGraphContextExecute()`.
/// @seealso `BNNSGraphCompileFromFile`
typedef struct {
  void *_Nullable data;   ///< Pointer to opaque object
  size_t size;            ///< size in bytes of object pointed to by data
} bnns_graph_t
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Wrapper around a `bnns_graph_t` object that adds mutable data storage.
/// Mutable data is required to support dynamic shapes and certain other execution options.
/// The underlying `graph_t` object must remain valid throughout the lifetime of this object.
/// @seealso `BNNSGraphContextMake`, `BNNSGraphContextDestroy`
typedef struct {
  void *_Nullable data;   ///< Pointer to opaque object
  size_t size;            ///< size in bytes of object pointed to by data
} bnns_graph_context_t
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Compilation options used to compile source model to a `bnns_graph_t` object.
/// Create an initial object by calling `BNNSGraphCompileOptionsMakeDefault()` and
/// set or query individual options by calling the `BNNSGraphCompileOptions*` family of functions.
/// @seealso `BNNSGraphCompileOptionsMakeDefault`, `BNNSGraphCompileOptionsDestroy`
typedef struct {
  void *_Nullable data;   ///< Pointer to opaque object
  size_t size;            ///< size in bytes of object pointed to by data
} bnns_graph_compile_options_t
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Specifies the shape of an argument
///
/// Members:
/// - `rank`: Rank of the tensor and number of elements in array shape. A rank of 0 may be used to indicate to
///          `BNNSGraphContextSetDynamicShapes()` that the constant or default shape from the
///          source should be used.
/// - `shape`: Array of length `rank` containing sizes of each dimension
///           May only be NULL if `rank==0`.
///           For inputs, `shape[d] = 0` is used to indicate that the constant or default shape from the source
///           should be used for dimension `d`.
///           For outputs, `shape[d] = 0` is set by `BNNSGraphContextSetDynamicShapes()` to indicate that
///           the size in that dimension could not be deduced from the input shape alone, but will depend on the values
///           of the input data. Note that in some cases the returned shape will only be an upper bound on the size in that
///           dimension.
typedef struct {
  size_t rank;
  uint64_t *_Nullable shape;
} bnns_graph_shape_t
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Type for user-provided memory allocation function
///
/// The function may be called for either an initial allocation, or to resize an existing allocation.
/// Typically on the first execution of a graph all calls will be for allocation, and on subsequent executions with the same context it will
/// be for reallocation. An optimized implementation will normally track sizes and avoid reallocating if size is the same or smaller.
///
/// Arguments:
/// `user_memory_context`: pointer that stores allocator mechanism state, passed unaltered from the function that specifies an argument of this type
/// `user_memory_context_size`: size in bytes of `user_memory_context`.
/// `memptr`: pointer to be allocated or reallocated. If `*memptr` is NULL, data item is being allocated for the first time, if it is not NULL, the item is being reallocated
/// `alignment`: Minimum required alignment for the object, in bytes.
/// `size`: Minimum size of object to be returned in `memptr`, in bytes.
///
/// Returns:
/// 0 on success, non-zero on failure
///
/// @seealso `BNNSGraphContextSetWorkspaceAllocationCallback`, `BNNSGraphContextSetOutputAllocationCallback`
typedef int (*bnns_graph_realloc_fn_t)(void *_Nullable user_memory_context,
                                       size_t user_memory_context_size,
                                       void *_Nullable *_Nonnull memptr,
                                       size_t alignment,
                                       size_t size)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Type for user-provided memory free function
///
/// This is called upon destruction of a context to free *all* memory associated to the `user_memory_context`.
/// If user has supplied both workspace and output memory management functions and the `user_memory_context` pointers are equal,
/// BNNS will only call this function once during `BNNSGraphContextDestroy`.
///
/// @seealso `BNNSGraphContextSetWorkspaceAllocationCallback`, `BNNSGraphContextSetOutputAllocationCallback`
typedef void (*bnns_graph_free_all_fn_t)(void *_Nullable user_memory_context, size_t user_memory_context_size)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Message Level Enum
///
/// Indicates the logging type for a specified message for message-logging callbacks to
/// surface messages taking into account the message type
BNNS_ENUM(BNNSGraphMessageLevel, uint32_t,
  BNNSGraphMessageLevelInfo
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 1,
  BNNSGraphMessageLevelUnsupported
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 2,
  BNNSGraphMessageLevelWarning
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 4,
  BNNSGraphMessageLevelError
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 8,
);

/// Additional user-defined logging argument for user to pass into the message logging callbacks
typedef struct {

  /// size of the additional logging data
  size_t size;

  /// pointer to the additional logging data
  void *_Nullable data;

} bnns_user_message_data_t
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Graph execute message callback function
///
/// Surfaces messages (i.e. warnings, errors, logs) according to the `BNNSGraphMessageLevel` message level specifier
/// User may specify customized actionables and logging styles. Default definition of this callback reports messages onto `os_log`
typedef void (*bnns_graph_execute_message_fn_t)(BNNSGraphMessageLevel msg_level,
                                                char const *_Nonnull error_msg,
                                                char const *_Nullable op_info,
                                                bnns_user_message_data_t * _Nullable additional_logging_arguments)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Graph compile message callback function
///
/// Surfaces messages (i.e. warnings, errors, logs) according to the `BNNSGraphMessageLevel` message level specifier
/// User may specify customized actionables and logging styles. Default definition of this callback reports messages onto `os_log`
typedef void (*bnns_graph_compile_message_fn_t)(BNNSGraphMessageLevel msg_level,
                                                char const *_Nonnull error_msg,
                                                char const *_Nullable source_location,
                                                bnns_user_message_data_t * _Nullable additional_logging_arguments)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));


#pragma mark - Compile options

/// Allocates and returns a new `bnns_graph_compile_options_t` object initialized to default values.
/// The user is responsible for calling `BNNSGraphCompileOptionsDestroy` on this object once it is no longer required.
bnns_graph_compile_options_t BNNSGraphCompileOptionsMakeDefault(void)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Destroys the given options object
void BNNSGraphCompileOptionsDestroy(bnns_graph_compile_options_t options)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Sets option for compiled graph to execute on only one thread.
/// Default behavior is to execute on multiple threads.
void BNNSGraphCompileOptionsSetTargetSingleThread(bnns_graph_compile_options_t options, 
                                                  bool value)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns true if execution is set to use a single thread, false otherwise.
bool BNNSGraphCompileOptionsGetTargetSingleThread(const bnns_graph_compile_options_t options)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Sets whether the generated `bnns_graph_t` object includes debug info.
/// Default behavior is *not* to include debug info.
void BNNSGraphCompileOptionsSetGenerateDebugInfo(bnns_graph_compile_options_t options, 
                                                 bool value)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns true if the generated `bnns_graph_t` will contain the debug info, false otherwise.
bool BNNSGraphCompileOptionsGetGenerateDebugInfo(const bnns_graph_compile_options_t options)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// BNNS Graph Compilation Optimization Preferences
/// - `BNNSGraphOptimizationPreferencePerformance`: Optimize for best execute performance
///   In this mode additional work may be moved to the compile phase, even if it increases the footprint of the IR.
/// - `BNNSGraphOptimizationPreferenceIRSize`: Optimize for smallest size of IR on disk
///   In this mode, data will be left in smallest possible form, but may decrease execute performance due
///   to cost of performing transformations
BNNS_ENUM(BNNSGraphOptimizationPreference, uint32_t,
  BNNSGraphOptimizationPreferencePerformance __API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 0,
  BNNSGraphOptimizationPreferenceIRSize      __API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 1,
);

/// Specifies the optimization preference to compile with
/// Default is `BNNSGraphOptimizationPreferencePerformance`.
void BNNSGraphCompileOptionsSetOptimizationPreference(bnns_graph_compile_options_t options,
                                                      BNNSGraphOptimizationPreference preference)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns the current optimization preference.
BNNSGraphOptimizationPreference BNNSGraphCompileOptionsGetOptimizationPreference(bnns_graph_compile_options_t options)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Graph Compile-time Message Callback Setter
///
/// Specifies customized callback function for compile time message reporting.
/// When unspecified, default callback functions log messages onto `os_log`.
///
/// - `options`: graph compile options
/// - `log_callback`: routine that customizes the graph compile time message logging callback of type
///                                       `bnns_graph_compile_message_fn_t`
/// - `additional_logging_arguments`: additional user-set data for the message logging functions to pass onto the callback functions unaltered
void BNNSGraphCompileOptionsSetMessageLogCallback(bnns_graph_compile_options_t options,
                                                  bnns_graph_compile_message_fn_t log_callback,
                                                  bnns_user_message_data_t * _Nullable additional_logging_arguments)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Sets mask for log messages that are logged (either via `os_log` or the user specified callback)
///
/// - `options`: graph compile options
/// - `log_level_mask`: bitmask of levels to log for
///                    (Default is BNNSGraphMessageLevelUnsupported | BNNSGraphMessageLevelWarning | BNNSGraphMessageLevelError)
void BNNSGraphCompileOptionsSetMessageLogMask(bnns_graph_compile_options_t options,
                                              uint32_t log_level_mask)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

#if !0
/// Specifies that the `bnns_graph_t` object should be generated directly to the given file
/// This is intended to reduce memory required for compilation, as the full set of graph weights need not be memory resident all at once
/// This option will be ignored if a file descriptor is supplied by calling `BNNSGraphCompileOptionsSetOutputFD`.
/// If this option is used, the `bnns_graph_t` returned BNNSCompileFromFile() will be a read-only mmap'd version of the result.
/// Passing NULL will reset to the default behavior of generating strictly in memory.
/// The file will be created with 0600 permissions (read/write by user only).
/// @seealso BNNSGraphCompileOptionsSetOutputFD
void BNNSGraphCompileOptionsSetOutputPath(bnns_graph_compile_options_t options, char const *_Nullable path)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns the path used if the `bnns_graph_t` object is generated directly to a file, or NULL if this option is not enabled
char const* _Nullable BNNSGraphCompileOptionsGetOutputPath(bnns_graph_compile_options_t options)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Specifies that the `bnns_graph_t` object should be generated directly to the given file descriptor
/// This is intended to reduce memory required for compilation, as the full set of graph weights need not be memory resident all at once
/// This option will override any previously set output path option.
/// The file indicated by the desriptor must be open for writing, and will be truncated and completely overwritten.
/// If this option is used, the `bnns_graph_t` returned BNNSCompileFromFile() will be a read-only mmap'd version of the result.
/// Passing -1 will reset to the default behavior of generating strictly in memory (or the file specified via
/// `BNNSGraphCompileOptionsSetOutputPath`).
void BNNSGraphCompileOptionsSetOutputFD(bnns_graph_compile_options_t options, int fd)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

// Return the file descriptor to be used for output, or -1 it none has been set.
int BNNSGraphCompileOptionsGetOutputFD(bnns_graph_compile_options_t options)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));
#endif 

#pragma mark - Compilation

#if !0

/// Compiles the given mlmodelc to a `bnns_graph_t` object.
/// The resulting object may be written to disk and then mmap'd in and executed in a new process at a later time or consumed
/// immediately.
///
/// The user is responsible for calling `free` (by default) or `munmap` (if a file was specified via one of the
/// `BNNSGraphCompileOptionsSetOutputPath*` calls) once they are ready to release the object.
///
/// Arguments:
/// - `filename`: specifies the path to the mlmodelc.
/// - `function`: specifies the name of a specific function to be compiled. If all functions in the source file are to be compiled,
///   `NULL` or the empty string may be passed.
/// - `options`: specifies compilation options. If the user passes `NULL`, options are the default set of options.
///
/// Returns:
/// - Compiled graph on success, or `(bnns_graph_t) { .data = NULL, .size = 0 }` on failure.
bnns_graph_t BNNSGraphCompileFromFile(const char *_Nonnull filename,
                                      const char *_Nullable function,
                                      bnns_graph_compile_options_t options)
__asm__("_BNNSGraphCompileFromFile_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

#endif 

#pragma mark - Graph query


/// Returns number of input arguments from a graph function.
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
///
/// Returns:
/// The number of input arguments on success, or `SIZE_T_MAX` on failure.
size_t BNNSGraphGetInputCount(bnns_graph_t graph,
                              const char *_Nullable function)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns number of output arguments from a graph function.
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
///
/// Returns:
/// The number of output arguments on success, or `SIZE_T_MAX` on failure.
size_t BNNSGraphGetOutputCount(bnns_graph_t graph,
                               const char *_Nullable function)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns total number of arguments for a graph function.
///
/// This will be the sum of values returned by `BNNSGraphGetInputCount` and `BNNSGraphGetOutputCount`.
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
///
/// Returns:
/// The number of output arguments on success, or `SIZE_T_MAX` on failure.
size_t BNNSGraphGetArgumentCount(bnns_graph_t graph,
                                 const char *_Nullable function)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns number of callable functions in this graph.
///
/// Arguments:
/// - `graph`: object to query.
///
/// Returns:
/// The number of callable functions on success, or `SIZE_T_MAX` on failure.
size_t BNNSGraphGetFunctionCount(bnns_graph_t graph)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Extracts argument names of inputs to a graph function
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
/// - `input_names_count`: number of elements in `input_names`.
/// - `input_names`: array of string pointers to populate.
///   On exit `input_names[i]` will be set to a read-only pointer to a string containing
///   the i-th argument name, for i in [0, min(num_inputs, input_names_count)).
///
/// Returns:
/// 0 on success, nonzero on failure.
/// Failure may be caused by either invalid values of `graph` or `function`.
int BNNSGraphGetInputNames(bnns_graph_t graph,
                           const char *_Nullable function,
                           size_t input_names_count,
                           char const *_Nullable *_Nonnull input_names)
__asm__("_BNNSGraphGetInputNames_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Extracts argument names of outputs to a graph function
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
/// - `output_names_count`: number of elements in `output_names`.
/// - `output_names`: array of string pointers to populate.
///   On exit `output_names[i]` will be set to a read-only pointer to a string containing
///   the i-th argument name, for i in [0, min(num_outputs, output_names_count)).
///
/// Returns:
/// 0 on success, nonzero on failure.
/// Failure may be caused by either invalid values of `graph` or `function`.
int BNNSGraphGetOutputNames(bnns_graph_t graph,
                            const char *_Nullable function,
                            size_t output_names_count,
                            char const *_Nullable *_Nonnull output_names)
__asm__("_BNNSGraphGetOutputNames_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Extracts names of argument to a graph function
///
/// This will be the concatenation of the results from `BNNSGraphGetOutputNames` and `BNNSGraphGetInputNames`
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
/// - `argument_names_count`: number of elements in `argument_names`.
/// - `argument_names`: array of string pointers to populate.
///   On exit `argument_names[i]` will be set to a read-only pointer to a string containing
///   the i-th argument name, for i in [0, min(num_argument, argument_names_count)).
///
/// Returns:
/// 0 on success, nonzero on failure.
/// Failure may be caused by either invalid values of `graph` or `function`.
int BNNSGraphGetArgumentNames(bnns_graph_t graph,
                              const char *_Nullable function,
                              size_t argument_names_count,
                              char const *_Nullable *_Nonnull argument_names)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Extracts names of callable functions in the graph
///
/// Arguments:
/// - `graph`: object to query.
/// - `function_name_count`: number of elements in `function_names`
/// - `function_names`: array of string pointers to populate.
///   On exit `function_names[i]` will be set to a read-only pointer to a string containing
///   the i-th function name, for i in [0, min(num_functions, function_name_length)).
///
/// Returns:
/// 0 on success, nonzero on failure.
/// Failure may be caused by either invalid values of `graph`.
int BNNSGraphGetFunctionNames(bnns_graph_t graph,
                              size_t function_name_count,
                              char const *_Nullable *_Nonnull function_names)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Describes the intent of an argument
///
/// - `BNNSGraphArgumentIntentIn` - argument provides an input tensor
/// - `BNNSGraphArgumentIntentOut` - argument provide an output tensor
/// - `BNNSGraphArgumentIntentInOut` - argument is an input and then updated in-place to provide an output as well
BNNS_ENUM( BNNSGraphArgumentIntent, uint32_t,
  BNNSGraphArgumentIntentIn     __API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 1,
  BNNSGraphArgumentIntentOut    __API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 2,
  BNNSGraphArgumentIntentInOut  __API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = BNNSGraphArgumentIntentIn | BNNSGraphArgumentIntentOut,
);

/// Returns intents of arguments
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
/// - `argument_intents_count`: number of elements in `argument_intents`.
/// - `argument_intents`: array of intents to populate.
///   On exit `argument_intents[i]` will be set to a value indicating the intent of
///   the i-th argument name, for i in [0, min(num_argument, argument_intents_count)).
///
/// Returns:
/// 0 on success, nonzero on failure.
/// Failure may be caused by either invalid values of `graph` or `function`.
int BNNSGraphGetArgumentIntents(bnns_graph_t graph,
                                const char *_Nullable function,
                                size_t argument_intents_count,
                                BNNSGraphArgumentIntent *_Nonnull argument_intents)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns index into arguments[] array for given function argument.
///
/// Returns the position in the arguments[] array for a call to `BNNSGraphExecute` or `BNNSGraphContextExecute` for the given argument.
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
/// - `argument`: name of input/output argument to query
///
/// Returns:
/// Index of argument on success, or `SIZE_T_MAX` on failure.
size_t BNNSGraphGetArgumentPosition(const bnns_graph_t graph,
                                    const char *_Nullable function,
                                    const char *_Nonnull argument)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns the interleave factors for arguments, if present
///
/// If any arguments to the function are specified with an interleave factor (e.g. using
/// the `interleave` option to `tensor_buffer` in MIL), this function can be
/// used to retrieve the interleave factor array.
///
/// Arguments:
/// - `graph`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
/// - `argument_count`: number of elements in `argument_interleave` and in `argument_interleave_counts`.
/// - `argument_interleave`: array of pointers to interleave factors to populate.
///   On exit `argument_interleave[i]` will be set to either:
///   - `NULL` if argument `i` has no interleave factor; or
///   - a pointer into the graph object containing the interleave factors that contains `argument_interleave_counts[i]` elements.
///   Only the first [0, min(argument_count, argument_interleave)) entries are set.
/// - `argument_interleave_counts`: gives the size of the array pointed to by `argument_interleave[i]`, or is set to 0
///   if `argument_interleave[i]` is set to `NULL`.
///
/// Returns:
/// 0 on success, nonzero on failure.
/// Failure may be caused by either invalid values of `graph` or `function`.
int BNNSGraphGetArgumentInterleaveFactors(bnns_graph_t graph,
                                          const char *_Nullable function,
                                          size_t argument_count,
                                          const uint16_t *_Nullable *_Nonnull argument_interleave,
                                          size_t *_Nonnull argument_interleave_counts)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

#pragma mark - Execution - without context

/// Used to specify the interpretation of the `arguments` argument to `BNNSGraphContextExecute()`.
/// `BNNSGraphArgumentTypePointer`: arguments[i] is a pointer to the raw data for the tensor
/// `BNNSGraphArgumentTypeTensor`: arguments[i] is a pointer to a BNNSTensor
///                               The layout and sizes of inputs must either be zero, or must match the source model.
///                               The layout and sizes of the output will be set by `BNNSGraphContextExecute()`.
BNNS_ENUM(BNNSGraphArgumentType, uint32_t,
  BNNSGraphArgumentTypePointer __API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 0,
  BNNSGraphArgumentTypeTensor  __API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = 2,
);

/// Describes data associated with an input or output argument
///
/// Exactly one of descriptor or data_ptr should be set based on the configuration specified with `BNNSGraphContextSetArgumentType()`
typedef struct {
  union {
    BNNSTensor *_Nullable tensor;                 ///< Pointer to BNNSTensor
    BNNSNDArrayDescriptor *_Nullable descriptor;  ///< Pointer to BNNSNDArrayDescriptor (deprecated, use BNNSTensor instead)
    void *_Nullable data_ptr;                     ///< Direct pointer to numerical data
  };
  size_t data_ptr_size;                           ///< size in bytes of `data_ptr`, if set
} bnns_graph_argument_t;

#pragma mark - Graph Context

/// Allocates and initializes a `bnns_graph_context_t`
///
/// Arguments:
/// - `graph`: object to be wrapped into the context. Must remain valid for the lifetime of returned context.
///
/// Returns:
/// - New context on success, or `(bnns_graph_context_t) { .data = NULL, .size = 0 }` on failure.
///   The object must be destroyed through a call to `BNNSGraphContextDestroy`.
///
/// @seealso `BNNSGraphContextDestroy`
bnns_graph_context_t BNNSGraphContextMake(const bnns_graph_t graph)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Make a new graph context with streaming support for the given function
///
/// Use this function in place of `BNNSGraphContextMake` to create a context for use with a model
/// compiled with the `BNNSOption` attribute `StateMode=Streaming` enabled. In addition to the
/// regular work performed by `BNNSGraphContextMake`, this call will also allocate ring-buffer
/// backed memory for all inout (i.e. CoreML `state`) arguments of the given function. Calls to
/// `BNNSGraphContextExecute()` with this function will ignore any user-provided pointers for
/// inout arguments and will use the internal ring-buffer instead. Upon return from the call, any
/// user-provided `bnns_argument_t` will be set to point to the ring-buffer memory.
/// The internal ring buffer will then be advanced by the distance determined by analysis of the compiled
/// program ready for use in the next frame.
///
/// If the function was not compiled with the BNNSOption parameter StateMode=Streaming, this call will fail.
///
/// If a state does not appear in the `initial_states` list, it will be initialized to all zeros.
///
/// Arguments:
/// - `graph`: object to be wrapped into the context. Must remain valid for the lifetime of returned context.
/// - `function`: function to initialize state for. It may be `NULL` if there is only one function.
/// - `initial_states_count`: Number of initial states contained in the array `inital_states`. May be 0.
/// - `initial_states`: Array of BNNSTensors describing data to be used to initialize each state.
///                    `initial_state[i]` is used to intialize the state with name
///                    `initial_state[i]->name`.
///
/// Returns:
/// - New context on success, or `(bnns_graph_context_t) { .data = NULL, .size = 0 }` on failure.
///   The object must be destroyed through a call to `BNNSGraphContextDestroy`.
bnns_graph_context_t BNNSGraphContextMakeStreaming(bnns_graph_t graph,
                                                   const char *_Nullable function,
                                                   size_t initial_states_count,
                                                   BNNSTensor const *_Nullable initial_states)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Destroys a graph context created through a call to `BNNSGraphContextCreate`
///
/// Arguments:
/// `context`: object to be destroyed
void BNNSGraphContextDestroy(bnns_graph_context_t context)
__asm__("_BNNSGraphContextDestroy_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Specifies the dynamic shapes for a graph and infers (if possible) output shapes
///
/// Notes:
/// - It is an error to call this function before all existing calls to `BNNSGraphContextExecute()` using the same context complete.
/// - Required workspace size for `BNNSGraphContextExecute()` may change as a result of this call.
/// - This function does not set dynamic strides as required by some arguments.
///  Arguments with dynamic strides must be provided as `BNNSTensor`s.
///  Use `BNNSGraphContextSetArgumentType` to set the argument type to `BNNSGraphArgumentTypeTensor`, and provide
///  `BNNSTensor` pointers in `bnns_graph_argument_t`.
///
/// Arguments:
/// - `context`: context for which to set dynamic shapes
/// - `function`: specific function to be set shapes for. It may be `NULL` if there is only one function.
/// - `shapes_count`: number of elements in array shapes
/// - `shapes`: array of shapes for outputs and inputs, in the same order as will be passed for `BNNSGraphContextExecute()`
///   On entry, input shapes are read from this array, unless indicated otherwise by setting `shapes[idx].rank = 0`, in which
///   case the constant or default value from the source model will be used. If a non-zero value is specified that does not match a constant
///   size in the source model, an error is generated. Output shapes are not read.
///   On exit, output shapes that have `shapes[idx].rank != 0` will be set to an upper bound on the  expected output shape.
///   If the output shape cannot be deduced as it depends on input data values, the value of `shapes[idx].size[d]` will be set
///   to zero for that dimension.
///
/// Returns:
/// - `0` on success if all tensor shapes were exactly determined (workspace size is exact)
/// - `1` on success if one or more tensor shapes are merely bounds, but no tensor is unbounded (workspace size is bounded)
/// - `2` on success if one or more tensor shapes are unbounded (BNNS will need to allocate during execution)
/// - `< 0` on failure.
int BNNSGraphContextSetDynamicShapes(bnns_graph_context_t context,
                                     char const *_Nullable function,
                                     size_t shapes_count,
                                     bnns_graph_shape_t *_Nonnull shapes)
__asm__("_BNNSGraphContextSetDynamicShapes_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Sets the batch size for a graph
///
/// This is a special case of `BNNSGraphContextSetDynamicShapes()` where the only dynamic sizes that occur are the first index
/// of their tensor (i.e. the batch dimension) and are all equal. This allows just passing a single `batch_size` constant.
///
/// Notes:
/// - It is an error to call this function before all existing calls to `BNNSGraphContextExecute()` complete.
/// - Required workspace size for `BNNSGraphContextExecute()` may change as a result of this call.
/// - If the graph has dynamic sizes other than batch size, then `BNNSGraphContextSetDynamicShapes()` must be used instead
/// - This function does not set dynamic strides as required by some arguments.
///  Arguments with dynamic strides must be provided as `BNNSTensor`s.
///  Use `BNNSGraphContextSetArgumentType` to set the argument type to `BNNSGraphArgumentTypeTensor`, and provide
///  `BNNSTensor` pointers in `bnns_graph_argument_t`.
///
/// Arguments:
/// - `context`: context for which to set dynamic shapes
/// - `function`: specific function to be set shapes for. It may be `NULL` if there is only one function.
/// - `batch_size`: the batch size to set
///
/// Returns:
/// - 0 on success, non-zero on failure
int BNNSGraphContextSetBatchSize(bnns_graph_context_t context,
                                 char const *_Nullable function,
                                 uint64_t batch_size)
__asm__("_BNNSGraphContextSetBatchSize_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Sets the type used to interpret the `arguments` argument to `BNNSGraphContextExecute()`.
///
/// Notes:
/// - Some arguments require dynamic strides. These must be provided as `BNNSTensor`s.
///  Use `BNNSGraphContextSetArgumentType` to set the argument type to `BNNSGraphArgumentTypeTensor`, and provide
///  `BNNSTensor` pointers in `bnns_graph_argument_t`.
///
/// Arguments:
/// - `context`: for which to enable signposts
/// - `argument_type`: argument type to set, default is `BNNSGraphArgumentTypePointer`
///
/// Returns:
/// - 0 on success, non-zero on failure
int BNNSGraphContextSetArgumentType(bnns_graph_context_t context, 
                                    BNNSGraphArgumentType argument_type)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Enables debug mode, checks intermediate tensors for nans and infs.
/// Not for use in production code.
void BNNSGraphContextEnableNanAndInfChecks(bnns_graph_context_t context,
                                           bool enable_check_for_nans_inf)
__asm__("_BNNSGraphContextEnableNanAndInfChecks")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Sets streaming advancement amount for cases with dynamically shaped inputs.
///
/// For models compiled with the `BNNSOption` attribute `StateMode=Streaming` enabled, where
/// `slice_update` ops use an update parameter of dynamic shape, BNNS cannot unambigiously
/// determine the streaming advancement size. Instead the user must use this function *prior* to calling
/// `BNNSGraphContextExecute()` to set the advancement size for each frame. 
///
/// The internal state pointer will then be advanced by `advance_count` elements in the streaming
/// dimension prior to returning from `BNNSGraphContextExecute()`. The BNNS streaming APIs
/// do not support models that require different advancement amounts for different states.
int BNNSGraphContextSetStreamingAdvanceCount(const bnns_graph_context_t context,
                                             size_t advance_count)
__API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4));

#pragma mark - Execution - with Graph Context

/// Executes the specified function with the provided context
///
/// The same context must only be used by a single thread at a time.
///
/// If the underlying model contains dynamic shaped inputs or outputs, these must be set prior to calling this routine through a call
/// to either `BNNSGraphContextSetDynamicShapes` or `BNNSGraphContextSetBatchSize`. The shapes should not
/// be modified again until this routine has returned.
///
/// This routine performs no memory allocation if the following conditions are met:
/// - workspace is not `NULL`.
/// - the graph does not contain tensors whose shape BNNS could not bound prior to this call.
/// - no new shape information is supplied via `arguments`.
/// - all output storage is provided explicitly by the user.
/// If any of these points is not the case, the user may control allocation by registering suitable callbacks via the functions
/// `BNNSGraphContextSetWorkspaceAllocationCallback` and `BNNSGraphContextSetOutputAllocationCallback`.
///
/// If the output allocation policy has been set to `bnns_managed=true`, the context must not be used in another call to
/// `BNNSGraphContextExecute` until the outputs are no longer needed (as they may be reused or deallocated).
///
/// Arguments:
/// - `context`: is the context to be executed.
/// - `function`: specific function to be executed. It may be `NULL` if there is only one function.
/// - `argument_count`: number of elements in `arguments`.
/// - `arguments`: array of `bnns_graph_argument_t` objects supply input data and memory allocated to hold the output.
///    Arguments are ordered such that outputs precede inputs, in the same order as they appear the source function's output and input
///    blocks. The position of an argument can be looked up by its source name using the BNNSGraphGetArgumentPosition() function.
///    If `.data_ptr=NULL` or `.tensor.data=NULL` for an output, one will be allocated for the user.
/// - `workspace_size`: size in bytes of `workspace`, or zero if `workspace==NULL`.
/// - `workspace`: scratch memory to be used during execution. MUST be page-aligned.
///               May be freed or reused by the user upon return.
///               If `NULL` is passed, the routine will allocate its own workspace.
///
/// Returns:
/// - 0 on success, non-zero on failure
///
/// @seealso `BNNSGraphContextMake`, `BNNSGraphContextGetWorkspaceSize`,
///          `BNNSGraphContextSetArgumentType`, `BNNSGraphContextSetDynamicShapes`
int BNNSGraphContextExecute(bnns_graph_context_t context,
                            const char *_Nullable function,
                            size_t argument_count,
                            bnns_graph_argument_t *_Nonnull arguments,
                            size_t workspace_size,
                            char* _Nullable workspace)
__asm__("_BNNSGraphContextExecute_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Returns the minimum size in bytes of the workspace argument that should be passed to `BNNSGraphContextExecute()`.
///
/// If `BNNSGraphContextSetBatchSize` or `BNNSGraphContextSetDynamicShapes` is called, then this function
/// should be call afterwards to obtain a new workspace size.
/// Due to memory layout algorithms being heuristic in nature, there is no guarantee that workspace size is monotonic
/// with any dynamic size. That is to say that the case with the maximum dynamic size may not be an upper bound on workspace
/// required for smaller sizes.
///
/// Arguments:
/// - `graph`: is the graph to be executed
/// - `function`: specific function to be executed. It may be `NULL` if there is only one function.
///
/// Returns:
/// - size in bytes of required workspace, or `SIZE_T_MAX` on failure (invalid graph, invalid function, or function contains dynamic shapes).
size_t BNNSGraphContextGetWorkspaceSize(bnns_graph_context_t context,
                                        const char *_Nullable function)
__asm__("_BNNSGraphContextGetWorkspaceSize_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

#pragma mark - Graph Context Query

/// Fills tensor descriptor for a given function argument.
///
/// If the shape has been modified for this context, such as by calling `BNNSGraphContextSetDynamicShapes()`,
/// then this routine will return that modified shape.
///
/// Arguments:
/// - `context`: object to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
/// - `argument`: name of input/output argument to query
/// - `fill_known_dynamic_shapes`: if `true`, any dynamic shapes are replaced with shapes that will be used on next
///    execution of `context`, either drawn from default shapes in the source model or supplied by a preceding call to
///    `BNNSGraphContextSetDynamicShapes()` or `BNNSGraphContextSetBatchSize()`.
///    Otherwise dynamically-sized dimensions are indicated by a value of -1 in shape/stride as appropriate.
/// - `tensor`: pointer to `BNNSTensor` to be filled by this routine.
///   On return all fields except `.data` and `.data_size_in_bytes` will have been populated.
///
/// Returns:
/// 0 on success and a non-zero on failure.
int BNNSGraphContextGetTensor(bnns_graph_context_t context,
                              const char *_Nullable function,
                              const char *_Nonnull argument,
                              bool fill_known_dynamic_shapes,
                              BNNSTensor *_Nonnull tensor)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Fills the strides member of a BNNSTensor for compatibility with a given model input or output based on its current shape
///
/// All sizes must be fully specified (i.e. not `< 0`). If the input or output is a tensor, contiguous strides will be filled in.
/// If the input or output is a tensor buffer, the strides will be filled in according to the specification in the model that was
/// compiled to the given graph.
///
/// Arguments:
/// - `graph`: ir to query.
/// - `function`: function to query. It may be `NULL` if there is only one function.
/// - `argument`: name of input/output argument to query
/// - `tensor`: pointer to `BNNSTensor` to be filled by this routine.
///   On return the first `tensor.rank` elements will have been overwritten with the strides BNNS expects.
///
/// Returns:
/// 0 on success and a non-zero on failure.
int BNNSGraphTensorFillStrides(bnns_graph_t graph,
                               const char *_Nullable function,
                               const char *_Nonnull argument,
                               BNNSTensor *_Nonnull tensor)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

#pragma mark - Graph Context Memory Management

/// Sets allocation/free callbacks for internal workspace
///
/// In the case that the required workspace cannot be bounded prior to execution (for example if tensor sizes depend on the
/// input data), BNNS will need to allocate workspace during execution. If the user wishes to override BNNS's default memory
/// allocation mechanism, they may provide allocation and free routines here.
///
/// Note that the `free` function will typically only be called when the context is destroyed, however workspace is only
/// required during the actual execution. As such users may wish to make memory in this allocation purgable or free it
/// between calls to `BNNSGraphContextExecute()`.
///
/// If the same value of `user_memory_context` is supplied to both `BNNSGraphContextSetWorkspaceAllocationCallback`
/// and to `BNNSGraphContextSetOutputAllocationCallback`, the `free` function will only be called once rather than twice.
///
/// Arguments:
/// - `context`: context to set callbacks for
/// - `realloc`: routine for (re)allocation of workspace. If `NULL` is passed then `free` must also be `NULL`, and routine will
///             reset context to the default BNNS allocation mechanism.
/// - `free`: routine to free all previous allocated data. Must match nullity of `realloc`. If `NULL` is passed then `realloc`
///          must also be `NULL`, and routine will reset context to the default BNNS allocation mechanism.
/// - `user_memory_context_size`: size in bytes of `user_memory_context`
/// - `user_memory_context`: pointer that will be passed unmodified by BNNS in all calls to `realloc` and `free`
///
/// Returns:
/// - 0 on success, non-zero on failure
int BNNSGraphContextSetWorkspaceAllocationCallback(bnns_graph_context_t context,
                                                   bnns_graph_realloc_fn_t _Nullable realloc,
                                                   bnns_graph_free_all_fn_t _Nullable free,
                                                   size_t user_memory_context_size,
                                                   void *_Nullable user_memory_context)
__asm__("_BNNSGraphContextSetWorkspaceAllocationCallback_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Sets allocation/free callbacks for function outputs
///
/// In the case that the output shape cannot be bounded prior to execution, the user may pass a NULL data pointer, and BNNS
/// will allocation the memory within the given context. If the user wishes to override BNNS's default memory
/// allocation mechanism for outputs, they may provide allocation and free routines here.
///
/// If the same value of `user_memory_context` is supplied to both `BNNSGraphContextSetWorkspaceAllocationCallback`
/// and to `BNNSGraphContextSetOutputAllocationCallback`, the `free` function will only be called once rather than twice.
///
/// Arguments:
/// - `context`: context to set callbacks for
/// - `realloc`: routine for (re)allocation of outputs. If `NULL` is passed then `free` must also be `NULL`, and routine will
///             reset context to the default BNNS allocation mechanism.
/// - `free`: routine to free all previous allocated data. Must match nullity of `realloc`. If `NULL` is passed then `realloc`
///          must also be `NULL`, and routine will reset context to the default BNNS allocation mechanism.
/// - `user_memory_context_size`: size in bytes of `user_memory_context`
/// - `user_memory_context`: pointer that will be passed unmodified by BNNS in all calls to `realloc` and `free`
///
/// Returns:
/// - 0 on success, non-zero on failure
int BNNSGraphContextSetOutputAllocationCallback(bnns_graph_context_t context,
                                                bnns_graph_realloc_fn_t _Nullable realloc,
                                                bnns_graph_free_all_fn_t _Nullable free,
                                                size_t user_memory_context_size,
                                                void *_Nullable user_memory_context)
__asm__("_BNNSGraphContextSetOutputAllocationCallback_v2")
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Execution time message logging callback setter
///
/// Specifies customized callback function for execution-time message reporting.
/// When unspecified, default callback functions log messages onto `os_log`.
///
/// - `context`: context to set callbacks for
/// - `log_callback_fn`:  routine that customizes the message reporting for all execution-time routines
/// - `additional_logging_arguments`: additional user-set data for the message logging functions to pass onto the callback functions unaltered
int BNNSGraphContextSetMessageLogCallback(bnns_graph_context_t context,
                                          bnns_graph_execute_message_fn_t _Nonnull log_callback_fn,
                                          bnns_user_message_data_t * _Nullable additional_logging_arguments)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// Sets mask for log messages that are logged (either via `os_log` or the user specified callback)
///
/// - `context`: context to set callbacks for
/// - `log_level_mask`: bitmask of levels to log for
///                    (Default is BNNSGraphMessageLevelUnsupported | BNNSGraphMessageLevelWarning | BNNSGraphMessageLevelError)
int BNNSGraphContextSetMessageLogMask(bnns_graph_context_t context, 
                                      uint32_t log_level_mask)
__API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

#ifdef __cplusplus
} // extern "C"
#endif

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull end")
#else
#undef _Nullable
#undef _Null_unspecified
#undef _Nonnull
#endif

#undef BNNS_ENUM

#if !__has_include( <Availability.h> )
#undef __API_AVAILABLE
#undef __API_DEPRECATED_WITH_REPLACEMENT
#endif

#endif /* __BNNS_GRAPH_HEADER__ */
