
// -*- Metal -*-
//===-- MetalTensorOpsBase ------------------------------------------------------===//
// Copyright (c) 2025 Apple Inc. All rights reserved
//===----------------------------------------------------------------------===//

#ifndef __MetalTensorOpsBase__
#define __MetalTensorOpsBase__

#if defined(__METAL_VERSION__) && defined(__HAVE_TENSOR__)

namespace mpp
{
namespace tensor_ops
{

namespace __tensor_ops_detail
{
class op
{
};
} // namespace __tensor_ops_detail

} // namespace tensor_ops
} // namespace mpp

#endif
#endif
