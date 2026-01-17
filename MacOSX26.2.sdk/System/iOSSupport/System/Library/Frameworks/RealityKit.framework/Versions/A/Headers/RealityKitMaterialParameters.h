#ifndef REALITYKIT_MATERIAL_PARAMETERS_H
#define REALITYKIT_MATERIAL_PARAMETERS_H

//
//  Copyright © 2021 Apple Inc. All rights reserved.
//
#if defined(__METAL_VERSION__)

#ifndef __REALITYKIT_INDIRECT
#error "Please include <RealityKit/RealityKit.h> instead of individual files directly"
#endif

#include <RealityKit/RealityKitTypes.h>

namespace realitykit
{
struct surface_parameters;
struct geometry_parameters;

namespace material
{
struct material_constants_t;

namespace api
{
// Material Constants

RK_API float3 base_color_tint(thread material_constants_t &data);
RK_API float opacity_scale(thread material_constants_t &data);
RK_API float opacity_threshold(thread material_constants_t &data);
RK_API float roughness_scale(thread material_constants_t &data);
RK_API float metallic_scale(thread material_constants_t &data);
RK_API float specular_scale(thread material_constants_t &data);
RK_API float3 emissive_color(thread material_constants_t &data);
RK_API float clearcoat_scale(thread material_constants_t &data);
RK_API float clearcoat_roughness_scale(thread material_constants_t &data);
} // namespace api

// MARK: - Material Parameters

/// Material parameters that are constant across one instance of a model. These values
/// are set on the `Material` and available for use in your calculations.
///
/// When providing a surface shader, you are responsible for using these values
/// as desired for your final look.
struct material_parameters
{
    RK_INLINE material_parameters(thread material::material_constants_t &_data)
        : data(_data)
    {
    }

    /// Returns the value of baseColor.tint set on the model's material.
    RK_INLINE float3 base_color_tint() const thread
    {
        return material::api::base_color_tint(data);
    }

    /// Returns the value of (baseColor.tint.alpha * opacityScale) set on the model's material.
    RK_INLINE float opacity_scale() const thread
    {
        return material::api::opacity_scale(data);
    }

    /// Returns the value of opacityThreshold set on the model's material.
    ///
    /// Defaults to 0.
    RK_INLINE float opacity_threshold() const thread
    {
        return material::api::opacity_threshold(data);
    }

    /// Returns the value of roughness.scale set on the model's material.
    RK_INLINE float roughness_scale() const thread
    {
        return material::api::roughness_scale(data);
    }

    /// Returns the value of metallic.scale set on the model's material.
    RK_INLINE float metallic_scale() const thread
    {
        return material::api::metallic_scale(data);
    }

    /// Returns the value of specular.scale set on the model's material.
    RK_INLINE float specular_scale() const thread
    {
        return material::api::specular_scale(data);
    }

    /// Returns the value of emissiveColor set on the model's material.
    RK_INLINE float3 emissive_color() const thread
    {
        return material::api::emissive_color(data);
    }

    /// Returns the value of clearcoat.scale set on the model's material.
    RK_INLINE float clearcoat_scale() const thread
    {
        return material::api::clearcoat_scale(data);
    }

    /// Returns the value of clearcoatRoughness.scale set on the model's material.
    RK_INLINE float clearcoat_roughness_scale() const thread
    {
        return material::api::clearcoat_roughness_scale(data);
    }

private:
    thread material::material_constants_t &data;
};

} // namespace material
} // namespace realitykit

#endif // __METAL_VERSION__
#endif /* REALITYKIT_MATERIAL_PARAMETERS_H */
