
// -*- Metal -*-
//===-- MetalTensorOpsMatMul2d
//------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//
// This API performs generalized matrix multiplication operation
//             C = A*B + C;
// A and B can be tensor_handle, tensor_offset, and tensor_inline.
// C can be tensor_handle, tensor_offset, tensor_inline or cooperative_tensor.
// Data type combinations supported by this operation are as follows:
//
//  A          B         C
//  ---------------------------
//  half       half      half
//  half       int8_t    half
//  int8_t     half      half
//  half       half      float
//  half       float     float
//  half       int8_t    float
//  float      half      float
//  float      float     float
//  float      int8_t    float
//  int8_t     half      float
//  int8_t     float     float
//  int8_t     int8_t    int32_t
//  bfloat     bfloat    bfloat
//  bfloat     bfloat    float
//  bfloat     float     float
//  bfloat     int8_t    bfloat
//  bfloat     int8_t    float
//  float      bfloat    float
//  int8_t     bfloat    bfloat
//  int8_t     bfloat    float
//  bfloat     half      bfloat
//  bfloat     half      half
//  bfloat     half      float
//  half       bfloat    bfloat
//  half       bfloat    half
//  half       bfloat    float
//
// Basic usage is in the following example which takes M x K matrix A of type
// half, K x N matrix B of type half, both in device memory and produces M x N
// matrix C of type float in device memory. It tiles this matrix multiplication
// in thread groups, where each thread group computes a 64 x 32 tile of output
// but multiplying 64 x K tile of A with K x 32 tile of B. This compute kernel
// will be launched with dispatch grid of
//
//        MTLSize threadgroups = MTLSizeMake((M + 63)/64, (N + 31)/32, 1);
//
// It uses 4 SIMD-Groups per threadgroup
// The way to dispatch this compute kernel is
//
//    id<MTLComputePipelineState> state = [device newComputePipelineState:...];
//    NSUInteger simdgroupWidth = [state threadExecutionWidth];
//    ...
//    [encoder dispatchThreadgroups:threadgroups
//    threadPerThreadgroups:MTLSizeMake(simdgroupWidth*4, 1, 1)];
//
// kernel void simpleMatMul(tensor<device half,  dextents<int32_t, 2>> A,
//                          tensor<device half,  dextents<int32_t, 2>> B,
//                          tensor<device float, dextents<int32_t, 2>> C,
//                          constant uint& M, constant uint& N, constant uint& K,
//                          uint2 tgid [[threadgroup_position_in_grid]])
// {
//     // descriptor to create matmul operation that does 64x32 times 32x32
//     // producing 64x32
//     constexpr auto matmulDescriptor =
//         matmul2d_descriptor(64, // m outer dim of local tile
//                             32, // n outer dim of local tile
//                             static_cast<int>(dynamic_extent), // k inner dimension. dynamic_extent means operation will read K from input tensor
//                                                               // K = A.extents().extent(0) or B.extents().extent(1) for NN
//                                                               // K = A.extents().extent(0) or B.extents().extent(0) for NT
//                                                               // and so on..
//                             false,  // transpse_left = false for NN and NT and true for TN and TT
//                             false,  // transpse_right = false for NN and TN and true for NT and TT
//                             false); // relaxed_precision = false, set it to true to allow implementation
//                                     // to sacrifice accurancy for performance.
//
//    // create matmul op from above descriptor with 4 SIMD-Groups. All 4
//    // SIMD-Groups in this threadgroup will execute this
//    // matmul cooperatively. More on this scope below.
//    matmul2d<matmulDescriptor, execution_simdgroups<4>> matmulOp;
//
//    // Following three lines of code create appropriate slice for this thread
//    // group to work on. E.g. A.slice below creates a
//    // tensor<device half, dextents<int32_t, 2>, tensor_offset>
//    // which has same extents as original tensor A but origin shifted to
//    // (0,tgid.y*64) i.e. mA[x,y] == A[x,tgid.y*64+y]
//
//    auto mA = A.slice(0, tgid.y*64);
//    auto mB = B.slice(tgid.x*32, 0);
//    auto mC = C.slice(tgid.x*32, tgid.y*64);
//
//    // execute the operation. Assumes C is is initialized to zero.
//    op.run(mA, mB, mC);
// }
//
// Above matrix multiplication implementation will do edge checking for all
// thread groups against extents of original tensor although for large enough
// matrices most of thread groups will be working on "inside" tiles, requiring no
// bounds check. In high performance code we can avoid edge checking for inside
// thread groups and get better performance
//
// kernel void matMul(tensor<device half,  dextents<int32_t, 2>> A,
//                    tensor<device half,  dextents<int32_t, 2>> B,
//                    tensor<device float, dextents<int32_t, 2>> C,
//                    constant uint& M, constant uint& N,
//                    constant uint& K, uint2 tgid [[threadgroup_position_in_grid]])
// {
//     // descriptor to create matmul operation that does 64x32 times 32x32
//     // producing 64x32
//     constexpr auto matmulDescriptor = matmul2d_descriptor(64,
//                                                           32,
//                                                           static_cast<int>(dynamic_extent));
//
//     matmul2d<matmulDescriptor, execution_simdgroups<4>> matmulOp;
//
//    // Inside thredgroup in both outer dimensions M and N.
//    if ( tgid.x*64 + 63 < M && tgid.y*32 + 31 < N)
//    {
//      auto tA = A.static_slice<dynamic_extent, 64>(0,tgid.y*64);
//      auto tB = B.static_slice<32, dynamic_extent>(tgid.x*32, 0);
//      auto tC = C.static_slice<32, 64>(tgid.x*32, tgid.y*64);
//
//      op.run(tA, tB, tC);
//    }
//    else
//    {
//      auto tA = A.slice(0, tgid.y*64);
//      auto tB = B.slice(tgid.x*32, 0);
//      auto tC = C.slice(tgid.x*32, tgid.y*64);
//
//      op.run(tA, tB, tC);
//    }
// }
//
// User can also take ownership of looping over reduction or k-dimension by
// choosing appropriate chunk size in k (called k-tile or tilek) For following
// example, we choose 16.
// kernel void matMulKLoop(tensor<device half, dextents<int32_t, 2>> A,
//                         tensor<device half, dextents<int32_t, 2>> B,
//                         tensor<device float, dextents<int32_t, 2>> C,
//                         constant uint& M, constant uint& N, constant uint& K,
//                         uint2 tgid [[threadgroup_position_in_grid]])
// {
//     // descriptor to create matmul operation that does 64x32 times 32x32
//     // producing 64x32
//     constexpr auto matmulDescriptor = matmul2d_descriptor(64,
//                                                           32,
//                                                           16); // tilek = 16, we loop over K in chunks of 16 rather than
//                                                                // letting matmul op run method looping over K
//                                                                // internally choose tileK
//
//     matmul2d<matmulDescriptor, execution_simdgroups<4>> matmulOp;
//
//     constexpr int tilek = 16;
//
//    // Inside thredgroup in both outer dimensions M and N.
//    if ( tgid.x*64 + 63 < M && tgid.y*32 + 31 < N)
//    {
//      auto tC = C.static_slice<32, 64>(tgid.x*32, tgid.y*64);
//      int k = 0;
//      for (; k + tilek - 1 < K; k += tilek)
//      {
//        auto tA = A.static_slice<tilek, 64>(k,tgid.y*64);
//        auto tB = B.static_slice<32, tilek>(tgid.x*32, k);
//
//        op.run(tA, tB, tC);
//      }
//
//      auto tA = A.static_slice<dynamic_extent, 64>(k, tgid.y*64);
//      auto tB = B.static_slice<32, dynamic_extent>(tgid.x*32, k);
//      op.run(tA, tB, tC);
//    }
//    else
//    {
//      auto tA = A.slice(0, tgid.y*64);
//      auto tB = B.slice(tgid.x*32, 0);
//      auto tC = C.slice(tgid.x*32, tgid.y*64);
//
//      op.run(tA, tB, tC);
//    }
// }
//
// Often times, we need to do some post processing on computed results before
// storing to device or threadgroup memory. For example, in machine learning we
// need to apply activation function on compute value. One can do GEMM as above
// which writes the result to device memory, read the value back, call post
// processing function and write again. This results in wasted bandwidth,
// performance and power. User can apply post processing in-register where GEMM
// output is computed using cooperative_tensor. Unlike tensor_handle,
// tensor_offset and tensor_inline which are non-owning meaning these are
// wrappers around resource in device, threadgroup or thread address space,
// cooperative_tensor owns thread private data and divides the data for entire
// tensor among threads (participating in the scope of operation) in implementation
// defined manner. This thread private memory is allocated at construction of
// cooperative_tensor and deallocated when this cooperative_tensor goes out of
// scope. The layout of cooperative_tensor depends on operation, data type,
// number of threads in opscope with which op was created. Note that
// cooperative_tensor created from an op is only valid for threads that are part
// of execution scope on which op was created. Though the layout of cooperative_tensor
// is implementation defined, we provide accessor functions as shown in the
// example below
//
// kernel void simpleMatMulCooperative(tensor<device half, dextents<int32_t, 2>> A,
//                                     tensor<device half, dextents<int32_t, 2>> B,
//                                     tensor<device float, dextents<int32_t, 2>> C,
//                                     tensor<device half, dextents<int32_t, 2>> bias,
//                                     constant uint& M, constant uint& N, constant uint& K,
//                                     uint2 tgid [[threadgroup_position_in_grid]])
// {
//     constexpr auto matmulDescriptor = matmul2d_descriptor(64,
//                                                           32,
//                                                           static_cast<int>(dynamic_extent));
//
//     matmul2d<matmulDescriptor, execution_simdgroups<4>> matmulOp;
//
//    auto mA = A.slice(0, tgid.y*64);
//    auto mB = B.slice(tgid.x*32, 0);
//    auto mC = C.slice(tgid.x*32, tgid.y*64);
//
//    // This creates cooperative destination tensor of float element type.
//    // Since matmul op above descriptor is created with 4 SIMD-Groups,
//    // cooperative tensor will divide data among the threads in these
//    // 4 SIMD-Groups. The layout of data among lanes is implementation defined
//    // and not all threads and even all elements within a thread need
//    // be valid. Use the valid element check shown below to guard
//    // access to elements of cooperative_tensor
//
//    auto cT = matmulOp.get_destination_cooperative_tensor<decltype(mA), decltype(mB), float>();
//
//    // Loop over all the elements of cooperative_tensor thread elements owned
//    // by "this" thread and initialize to zero.
//    // It is imperative for performance to include "unroll pragma" so compiler
//    // fully unrolls the loop.
//
//    #pragma unroll full
//    for (uint16_t i = 0, i < cT.get_capacity(); ++i) {
//      if(cT.get_mask(i))
//        cT[i] = 0;
//    }
//
//    // execute the operation. All threads compute the matmul cooperatively
//    // and results are written to cooperative_tensor.
//    op.run(mA, mB, cT);
//
//    // create cooperative bias tensor with same layout as destination
//    // cooperative_tensor of matmul
//    auto biasT = matmulOp.get_destination_cooperative_tensor<decltype(mA), decltype(mB), float>();
//
//    // load data from bias tensor_handle into biasT cooperative_tensor using
//    // layout and distribution of element among threads of scope on which matmul was created.
//    biasT.load(bias);
//
//    #pragma unroll full
//    for (uint16_t i = 0, i < cT.get_capacity(); ++i) {
//
//      if(cT.get_mask(i)) {
//        //add bias
//        cT[i] += biasT[i];
//
//        // get the 2-dimensional local coordinate of this thread's i-th
//        // element in destination local coordinate system (in this example
//        // 32 x 64 tile).
//        auto ids = cT.get_multidimensional_index(i);
//        cT[i] = foo(cT[i], idx); // do some operation based on coordinate values
//      }
//    }
//
//   // store to tensor handle
//   cT.store(mC);
// }
//
// Note on scope of operation
// ==========================
// A tensor operation may be executed on a single thread entirely or
// cooperatively among a set of SIMD groups. The set of threads is called the
// "execution scope" of the tensor operation. A tensor op must be created with
// an execution scope provided as template argument. All the threads in this
// execution scope must enter the run method i.e. call to run methods must be
// "execution scope" uniform. Use the following types to configure the execution
// modes of each operation:
//     metal::execution_thread: The operation will be run on a single thread.
//                              Fragment shaders only support this execution scope.
//     metal::execution_simdgroup: The operation will be run cooperatively by all
//                                 threads in the SIMD group. May be used for finer
//                                 control over tiling by slicing tensors with SIMD IDs.
//     metal::execution_simdgroups<N>: The operation will be executed cooperatively by N
//                                     SIMD groups. Must be used when all threads in a
//                                     threadgroup are cooperatively performing the operation.
//
// It is undefined behavior if the number of SIMD groups dispatched does not
// match the number of SIMD groups that the operation was configured with.
//
// Even though each thread in the execution scope can potentially independently
// enter and exit run method, the threads in the execution scope are working
// do not necessarily operate completely independently. For example, the tensor
// operation may need for (for correctness or performance) to synchronize
// among the threads in execution scope it was created with.
//
//
//===----------------------------------------------------------------------===//
#ifndef __MetalTensorOpsMatMul2d__
#define __MetalTensorOpsMatMul2d__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

#include "__impl/MPPTensorOpsBase.h"
#include "__impl/MPPTensorOpsTypes.h"
#include "__impl/MPPTensorOpsUtility.h"
#include <metal_numeric>

#pragma METAL internals : enable

namespace mpp
{
namespace tensor_ops
{

enum class reduction_operation
{
  sum,
  max,
  min,
};

struct matmul2d_descriptor
{
  enum class mode
  {
    multiply,
    multiply_accumulate,
  };

  int m, n, k;
  bool transpose_left, transpose_right;
  bool relaxed_precision;
  mode matmul_mode;

public:
  constexpr matmul2d_descriptor(int __m, int __n, int __k = static_cast<int>(metal::dynamic_extent),
                                bool __transpose_left = false,
                                bool __transpose_right = false,
                                bool __relaxed_precision = false,
                                mode __matmul_mode = mode::multiply) thread
      : m(__m),
        n(__n),
        k(__k),
        transpose_left(__transpose_left),
        transpose_right(__transpose_right),
        relaxed_precision(__relaxed_precision),
        matmul_mode(__matmul_mode)
  {
  }
};

template <typename ElementType>
struct reduction_operation_identity
{
  static const constant ElementType sum_identity = (ElementType)0;
  static const constant ElementType max_identity =
      metal::numeric_limits<ElementType>::lowest();
  static const constant ElementType min_identity =
      metal::numeric_limits<ElementType>::max();
};

#include "__impl/MPPTensorOpsMatMul2dImpl.h"

template <matmul2d_descriptor Descriptor, typename Scope, class... Args>
class matmul2d : __tensor_ops_detail::op
{
  static_assert(__tensor_ops_detail::__is_tensorops_execution_scope_v<Scope>,
                "Scope template argument should be of op_scope type");

public:
    
  static constexpr constant matmul2d_descriptor descriptor = Descriptor;
  using scope = Scope;
    
  matmul2d() thread = default;

  template <
      typename LeftOperandType, typename RightOperandType,
      typename DestinationOperandType,
      typename V = __tensor_ops_detail::__enable_if_t<
          ((__tensor_ops_detail::__is_tensor_type_v<LeftOperandType> || __tensor_ops_detail::__is_cooperative_tensor_type_v<LeftOperandType>) &&
           (__tensor_ops_detail::__is_tensor_type_v<RightOperandType> || __tensor_ops_detail::__is_cooperative_tensor_type_v<RightOperandType>) &&
           (__tensor_ops_detail::__is_tensor_type_v<DestinationOperandType> || __tensor_ops_detail::__is_cooperative_tensor_type_v<DestinationOperandType>))>,
      typename... RunArgs>
  INLINE void run(thread LeftOperandType &left, thread RightOperandType &right,
                  thread DestinationOperandType &destination) thread const
  {
    __mutmul2d_detail::__run<Descriptor, Scope, LeftOperandType,
                             RightOperandType, DestinationOperandType,
                             RunArgs...>(left, right, destination);
  }

  template <typename LeftElementType, typename RightElementType, typename ElementType, typename CoordType = int, typename... CoopArgs>
  using cooperative_tensor_left_input_t =
      __mutmul2d_detail::__cooperative_tensor_left_input_t<
          Descriptor, Scope, LeftElementType, RightElementType, ElementType, CoordType, CoopArgs...>;

  template <typename LeftElementType, typename RightElementType,
            typename ElementType, typename CoordType = int,
            typename U = __tensor_ops_detail::__enable_if_t<
                __tensor_ops_detail::__is_thread_addrspace_v<LeftElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<RightElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<ElementType> &&
                __tensor_ops_detail::__is_integral_v<CoordType>>,
            typename... CoopArgs>
  INLINE cooperative_tensor_left_input_t<LeftElementType, RightElementType, ElementType, CoordType, CoopArgs...>
  get_left_input_cooperative_tensor() thread const
  {
    return __mutmul2d_detail::__get_left_input_cooperative_tensor<
        Descriptor, Scope, LeftElementType, RightElementType, ElementType, CoordType, CoopArgs...>();
  }
  
  template <typename LeftElementType, typename RightElementType,
            typename ElementType, typename CoordType = int,
            typename SrcElemType, typename SrcExtents, typename SrcLayout,
            typename U = __tensor_ops_detail::__enable_if_t<
                __tensor_ops_detail::__is_thread_addrspace_v<LeftElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<RightElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<ElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<SrcElemType> &&
                __tensor_ops_detail::__is_integral_v<CoordType>>,
            typename... CoopArgs>
  INLINE cooperative_tensor_left_input_t<LeftElementType, RightElementType, ElementType, CoordType, CoopArgs...>
  get_left_input_cooperative_tensor(const thread metal::cooperative_tensor<SrcElemType, SrcExtents, SrcLayout> & src) thread const
  {
    return __mutmul2d_detail::__get_left_input_cooperative_tensor<
        SrcElemType, SrcExtents, SrcLayout, Descriptor, Scope, LeftElementType, RightElementType,
        ElementType, CoordType, CoopArgs...>(src);
  }

  template <typename LeftElementType, typename RightElementType, typename ElementType,
            typename SrcElemType, typename SrcExtents, typename SrcLayout,
            typename U = __tensor_ops_detail::__enable_if_t<
                __tensor_ops_detail::__is_thread_addrspace_v<LeftElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<RightElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<ElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<SrcElemType>>>
  INLINE bool
  is_compatible_as_left_input(const thread metal::cooperative_tensor<SrcElemType, SrcExtents, SrcLayout> & src) thread const
  {
      return __mutmul2d_detail::__is_compatible_as_left_input<
          LeftElementType, RightElementType, ElementType, Descriptor, Scope,
          SrcElemType, SrcExtents, SrcLayout>(src);
  }

  template <typename LeftElementType, typename RightElementType, typename ElementType, typename CoordType = int, typename... CoopArgs>
  using cooperative_tensor_right_input_t =
      __mutmul2d_detail::__cooperative_tensor_right_input_t<
          Descriptor, Scope, LeftElementType, RightElementType, ElementType, CoordType, CoopArgs...>;

  template <typename LeftElementType, typename RightElementType,
            typename ElementType, typename CoordType = int,
            typename U = __tensor_ops_detail::__enable_if_t<
                __tensor_ops_detail::__is_thread_addrspace_v<LeftElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<RightElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<ElementType> &&
                __tensor_ops_detail::__is_integral_v<CoordType>>,
            typename... CoopArgs>
  INLINE cooperative_tensor_right_input_t<LeftElementType, RightElementType, ElementType, CoordType, CoopArgs...>
  get_right_input_cooperative_tensor() thread const
  {
    return __mutmul2d_detail::__get_right_input_cooperative_tensor<
        Descriptor, Scope, LeftElementType, RightElementType, ElementType, CoordType, CoopArgs...>();
  }

  template <typename LeftElementType, typename RightElementType,
            typename ElementType, typename CoordType = int,
            typename SrcElemType, typename SrcExtents, typename SrcLayout,
            typename U = __tensor_ops_detail::__enable_if_t<
                __tensor_ops_detail::__is_thread_addrspace_v<LeftElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<RightElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<ElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<SrcElemType> &&
                __tensor_ops_detail::__is_integral_v<CoordType>>,
            typename... CoopArgs>
  INLINE cooperative_tensor_right_input_t<LeftElementType, RightElementType, ElementType, CoordType, CoopArgs...>
  get_right_input_cooperative_tensor(const thread metal::cooperative_tensor<SrcElemType, SrcExtents, SrcLayout> & src) thread const
  {
    return __mutmul2d_detail::__get_right_input_cooperative_tensor<
        SrcElemType, SrcExtents, SrcLayout, Descriptor, Scope, LeftElementType, RightElementType,
        ElementType, CoordType, CoopArgs...>(src);
  }

  template <typename LeftElementType, typename RightElementType, typename ElementType,
            typename SrcElemType, typename SrcExtents, typename SrcLayout,
            typename U = __tensor_ops_detail::__enable_if_t<
                __tensor_ops_detail::__is_thread_addrspace_v<LeftElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<RightElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<ElementType> &&
                __tensor_ops_detail::__is_thread_addrspace_v<SrcElemType>>>
  INLINE bool
  is_compatible_as_right_input(const thread metal::cooperative_tensor<SrcElemType, SrcExtents, SrcLayout> & src) thread const
  {
      return __mutmul2d_detail::__is_compatible_as_right_input<
          LeftElementType, RightElementType, ElementType, Descriptor, Scope,
          SrcElemType, SrcExtents, SrcLayout>(src);
  }

  template <typename LeftOperand, typename RightOperand, typename ElementType, typename CoordType = int, typename... CoopArgs>
  using cooperative_tensor_destination_t =
      __mutmul2d_detail::__cooperative_tensor_destination_t<
          Descriptor, Scope, LeftOperand, RightOperand, ElementType, CoordType, CoopArgs...>;

  template <typename LeftOperandType, typename RightOperandType,
            typename ElementType, typename CoordType = int,
            typename U = __tensor_ops_detail::__enable_if_t<
                (__tensor_ops_detail::__is_tensor_type_v<LeftOperandType> || __tensor_ops_detail::__is_cooperative_tensor_type_v<LeftOperandType>) &&
                (__tensor_ops_detail::__is_tensor_type_v<RightOperandType> || __tensor_ops_detail::__is_cooperative_tensor_type_v<RightOperandType>) &&
                __tensor_ops_detail::__is_thread_addrspace_v<ElementType> &&
                __tensor_ops_detail::__is_integral_v<CoordType>>,
            typename... CoopArgs>
  INLINE cooperative_tensor_destination_t<LeftOperandType, RightOperandType, ElementType, CoordType, CoopArgs...>
  get_destination_cooperative_tensor() thread const
  {

    return __mutmul2d_detail::__get_destination_cooperative_tensor<
        Descriptor, Scope, LeftOperandType, RightOperandType, ElementType,
        CoordType, CoopArgs...>();
  }

  template <typename LeftOperandType, typename RightOperandType, typename ElementType,
            typename CoordType = int, typename... CoopArgs>
  using cooperative_tensor_row_reduction_destination_t =
      __mutmul2d_detail::__cooperative_tensor_row_reduction_destination_t<
          Descriptor, Scope, LeftOperandType, RightOperandType, ElementType, CoordType, CoopArgs...>;

  template <typename LeftOperandType, typename RightOperandType, typename ElementType,
            typename CoordType = int,
            typename U = __tensor_ops_detail::__enable_if_t<
                __tensor_ops_detail::__is_integral_v<CoordType>>,
            typename... CoopArgs>
  INLINE cooperative_tensor_row_reduction_destination_t<LeftOperandType, RightOperandType,
                                                        ElementType, CoordType, CoopArgs...>
  get_row_reduction_destination_cooperative_tensor() thread const
  {
    return __mutmul2d_detail::__get_row_reduction_destination_cooperative_tensor<
        Descriptor, Scope, LeftOperandType, RightOperandType, ElementType, CoordType, CoopArgs...>();
  }


  template <typename LeftOperandType, typename RightOperandType, typename ElementType,
            typename CoordType = int, typename... CoopArgs>
  using cooperative_tensor_column_reduction_destination_t =
      __mutmul2d_detail::__cooperative_tensor_column_reduction_destination_t<
          Descriptor, Scope, LeftOperandType, RightOperandType, ElementType, CoordType, CoopArgs...>;

  template <typename LeftOperandType, typename RightOperandType, typename ElementType,
            typename CoordType = int, typename U = __tensor_ops_detail::__enable_if_t<
                __tensor_ops_detail::__is_integral_v<CoordType>>,
            typename... CoopArgs>
  INLINE cooperative_tensor_column_reduction_destination_t<LeftOperandType, RightOperandType,
                                                           ElementType, CoordType, CoopArgs...>
  get_column_reduction_destination_cooperative_tensor() thread const
  {
    return __mutmul2d_detail::__get_column_reduction_destination_cooperative_tensor<
        Descriptor, Scope, LeftOperandType, RightOperandType, ElementType, CoordType, CoopArgs...>();
  }
};

template <class ElementType, class SrcExtents, class DstExtents, class SrcLayout, class DstLayout>
inline void reduce_rows(
    thread metal::cooperative_tensor<ElementType, SrcExtents, SrcLayout> &source,
    thread metal::cooperative_tensor<ElementType, DstExtents, DstLayout> &destination,
    reduction_operation op = reduction_operation::sum,
    ElementType identity =
        reduction_operation_identity<ElementType>::sum_identity)
{
  __mutmul2d_detail::__reduce_rows<ElementType, SrcExtents, DstExtents, SrcLayout, DstLayout>(
      source, destination, identity, op);
}

template <class ElementType, class SrcExtents, class DstExtents, class SrcLayout, class DstLayout>
inline void reduce_columns(
    thread metal::cooperative_tensor<ElementType, SrcExtents, SrcLayout> &source,
    thread metal::cooperative_tensor<ElementType, DstExtents, DstLayout> &destination,
    reduction_operation op = reduction_operation::sum,
    ElementType identity =
        reduction_operation_identity<ElementType>::sum_identity)
{
  __mutmul2d_detail::__reduce_columns<ElementType, SrcExtents, DstExtents, SrcLayout, DstLayout>(
      source, destination, identity, op);
}

// Returns whether the iterators are compatible between a source and destination cooperative tensor.
//
// Use this to check whether map_iterator will be return a valid iterator. For example:
//
//     if (is_iterator_compatible(sourceCT, destCT)) {
//         for (auto it = sourceCT.begin(); it != sourceCT.end(); it++) {
//             auto dst_it = destCT.map_iterator(sourceCT)
//
//             *it += *dst_it;
//         }
//     }
//     else {
//          // Fall back to storing sourceCT to threadgroup memory and access via
//          // destCT's multidimensional indices
//     }
template <class SrcElementType, class DstElementType, class SrcExtents, class DstExtents, class SrcLayout, class DstLayout>
inline bool is_iterator_compatible(
    const thread metal::cooperative_tensor<SrcElementType, SrcExtents, SrcLayout> &source,
    const thread metal::cooperative_tensor<DstElementType, DstExtents, DstLayout> &destination)
{
  return __mutmul2d_detail::__is_iterator_compatible<SrcElementType, DstElementType, SrcExtents, DstExtents,
      SrcLayout, DstLayout>(source, destination);
}

} // namespace tensor_ops
} // namespace mpp

#pragma METAL internals : disable

#endif

#endif // __TensorOpsMatMul2D__
