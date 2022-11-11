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

#if RK_BUILD_TIME_LINKING

// Temporary flags during experimentation or development on older OS'es. In this
// mode, the shader is linked at compile-time.
#define RK_API extern
#define RK_INLINE inline __attribute__((__always_inline__))

#else

#if __HAVE_VISIBLE_FUNCTIONS__
#define RK_API [[visible]]
#else
#define RK_API
#endif

#define RK_INLINE inline __attribute__((__always_inline__))

#endif

namespace realitykit
{

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
