#ifndef REALITYKIT_TEXTURES_H
#define REALITYKIT_TEXTURES_H

//
//  Copyright © 2021 Apple Inc. All rights reserved.
//
#if defined(__METAL_VERSION__)

#ifndef __REALITYKIT_INDIRECT
#error "Please include <RealityKit/RealityKit.h> instead of individual files directly"
#endif

#include <RealityKit/RealityKitTypes.h>

#include <metal_common>
#include <metal_geometric>
#include <metal_texture>

namespace realitykit
{
struct surface_parameters;
struct geometry_parameters;

/// Unpack a tangent-space normal from a two-component texture representation.
///
/// @discussion The Z component will be computed from the xy components, and the result
/// will be normalized.
///
/// Call this overload if your texture encodes only the x/y components of the normal,
/// or your data may not already be normalized. If you don't need re-normalization, call
/// unpack_normal with three components
///
/// @see unpack_normal(half3)
RK_INLINE half3 unpack_normal(half2 packed_normal)
{
    using namespace metal;

    half3 normal;
    normal.xy = (packed_normal.xy * 2.0h - 1.0h);
    normal.z = sqrt(1.0h - saturate(dot(normal.xy,normal.xy)));
    return normal;
}

/// Unpack a tangent-space normal from a three-component packed texture representation.
///
/// @discussion This overload maps a packed normal in the range (0, 1) into (-1, 1). The resulting
/// normal will not be normalized. To re-normalize the value, call unpack_normal with the xy components.
///
/// @see unpack_normal(half2)
///
/// @param packed_normal A packed normal where each component is in the range (0, 1).
///
RK_INLINE half3 unpack_normal(half3 packed_normal)
{
    return packed_normal * 2.0h - 1.0h;
}

/// Unpack a tangent-space normal from a three component texture representation, and increases
/// or decreases its intensity.
///
/// @discussion The intensity of the normal will be modulated by scaling the x/y components by intensity.
/// The Z component will then be computed from the xy components, resulting in a normalized value.
///
/// @param intensity Values greater than one will increase the intensity, where values smaller
/// than 1 will reduce the intensity.
RK_INLINE half3 unpack_normal(half3 packed_normal, half intensity)
{
    using namespace metal;

    half3 normal;
    normal.xy = (packed_normal.xy * 2.0h - 1.0h) * intensity;
    normal.z = sqrt(1.0h - saturate(dot(normal.xy,normal.xy)));
    return normal;
}

namespace texture
{
struct texture_data_t;

namespace api
{
RK_API metal::texture2d<half> base_color(thread texture_data_t &data);
RK_API metal::texture2d<half> opacity(thread texture_data_t &data);
RK_API metal::texture2d<half> normal(thread texture_data_t &data);
RK_API metal::texture2d<half> emissive_color(thread texture_data_t &data);
RK_API metal::texture2d<half> roughness(thread texture_data_t &data);
RK_API metal::texture2d<half> metallic(thread texture_data_t &data);
RK_API metal::texture2d<half> ambient_occlusion(thread texture_data_t &data);
RK_API metal::texture2d<half> specular(thread texture_data_t &data);
RK_API metal::texture2d<half> clearcoat(thread texture_data_t &data);
RK_API metal::texture2d<half> clearcoat_roughness(thread texture_data_t &data);
RK_API metal::texture2d<half> custom(thread texture_data_t &data);
} // namespace api

// MARK: - Textures

/// Provides access to textures that are applied to a model.
///
/// @discussion When textures are loaded from a USD, their origin will be in the bottom
/// left corner, rather than the top left which Metal samples in. To account for this,
/// flip your UVs vertically before sampling.
///
/// @code
/// constexpr sampler samplerBilinear(coord::normalized,
///                                   address::repeat,
///                                   filter::linear,
///                                   mip_filter::nearest);
///
/// float2 uv = params.geometry().uv0();
///
/// // Flip uvs vertically.
/// uv.y = 1.0 - uv.y;
///
/// float4 color = params.textures().base_color().sample(samplerBilinear, uv);
/// @endcode
///
/// This is available in both geometry modifier and surface shader functions.
struct textures
{
    RK_INLINE textures(thread texture::texture_data_t &_data)
        : data(_data)
    {
    }

    /// Returns any base color texture assigned to the model.
    ///
    /// If no texture is assigned, returns a texture containing (1,1,1,1).
    RK_INLINE metal::texture2d<half> base_color() const thread
    {
        return texture::api::base_color(data);
    }

    /// Returns any opacity texture assigned to the model.
    ///
    /// If no texture is assigned, returns a texture containing (1,1,1,1).
    RK_INLINE metal::texture2d<half> opacity() const thread
    {
        return texture::api::opacity(data);
    }

    /// Returns any normal map texture assigned to the model
    ///
    /// If no texture is assigned, returns a texture containing a light blue color,
    /// representing a default normal.
    RK_INLINE metal::texture2d<half> normal() const thread
    {
        return texture::api::normal(data);
    }

    /// Returns any emissive color texture assigned to the model
    ///
    /// If no texture is assigned, returns a texture containing (0,0,0,1).
    RK_INLINE metal::texture2d<half> emissive_color() const thread
    {
        return texture::api::emissive_color(data);
    }

    /// Returns any roughness texture assigned to the model
    ///
    /// If no texture is assigned, returns a texture containing (1,1,1,1).
    RK_INLINE metal::texture2d<half> roughness() const thread
    {
        return texture::api::roughness(data);
    }

    /// Returns any metallic texture assigned to the model
    ///
    /// If no texture is assigned, returns a texture containing (1,1,1,1).
    RK_INLINE metal::texture2d<half> metallic() const thread
    {
        return texture::api::metallic(data);
    }

    /// Returns any ambient occlusion texture assigned to the model
    ///
    /// If no texture is assigned, returns a texture containing (1,1,1,1).
    RK_INLINE metal::texture2d<half> ambient_occlusion() const thread
    {
        return texture::api::ambient_occlusion(data);
    }

    /// Returns any specular texture assigned to the model
    ///
    /// If no texture is assigned, returns a texture containing (1,1,1,1).
    RK_INLINE metal::texture2d<half> specular() const thread
    {
        return texture::api::specular(data);
    }

    /// Returns any clearcoat texture assigned to the model.
    ///
    /// If no texture is assigned, returns a texture containing (1,1,1,1).
    RK_INLINE metal::texture2d<half> clearcoat() const thread
    {
        return texture::api::clearcoat(data);
    }

    /// Returns any clearcoat roughness texture assigned to the model.
    ///
    /// If no texture is assigned, returns a texture containing (1,1,1,1).
    RK_INLINE metal::texture2d<half> clearcoat_roughness() const thread
    {
        return texture::api::clearcoat_roughness(data);
    }

    /// Returns a custom texture you have previously set on the CustomMaterial. You can use
    /// it to store and access any texture data you'd like. It is not otherwise used within RealityKit.
    ///
    /// If no texture is assigned, returns a texture containing (0,0,0,1).
    RK_INLINE metal::texture2d<half> custom() const thread
    {
        return texture::api::custom(data);
    }

private:
    thread texture::texture_data_t &data;
};

} // namespace texture
} // namespace realitykit

#endif // __METAL_VERSION__
#endif /* REALITYKIT_TEXTURES_H */
