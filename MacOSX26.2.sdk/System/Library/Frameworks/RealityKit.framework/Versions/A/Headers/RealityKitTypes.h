#ifndef REALITYKIT_TYPES_H_
#define REALITYKIT_TYPES_H_

//
//  Copyright © 2021 Apple Inc. All rights reserved.
//
#if defined(__METAL_VERSION__)

#include <RealityKit/RealityKitConfig.h>

#include <metal_config>

#if __METAL_VERSION__ < 230
#warning "Metal version 2.3 is required for surface shaders"
#endif

#define RK_API [[visible]]

#define RK_INLINE inline __attribute__((__always_inline__))

#ifndef RK_INTERNAL_STRIP_OUT_AVAILABILITY

#define RK_AVAILABILITY_IOS_18 __attribute__((availability(ios, introduced=18.0, strict)))
#define RK_AVAILABILITY_MACOS_15  __attribute__((availability(macos, introduced=15.0, strict)))
#define RK_AVAILABILITY_IOS_19 __attribute__((availability(ios, introduced=19.0, strict)))
#define RK_AVAILABILITY_MACOS_16  __attribute__((availability(macos, introduced=16.0, strict)))

#else

#define RK_AVAILABILITY_IOS_18
#define RK_AVAILABILITY_MACOS_15
#define RK_AVAILABILITY_IOS_19
#define RK_AVAILABILITY_MACOS_16

#endif
namespace realitykit
{

struct hover_state_t;

namespace geometry_modifier
{
struct geometry_data_t;
}

namespace texture
{
struct texture_data_t;
}

namespace material
{
struct material_constants_t;
}

namespace surface
{
struct surface_data_t;
}

} // namespace realitykit

#endif // __METAL_VERSION__
#endif // REALITYKIT_TYPES_H_
