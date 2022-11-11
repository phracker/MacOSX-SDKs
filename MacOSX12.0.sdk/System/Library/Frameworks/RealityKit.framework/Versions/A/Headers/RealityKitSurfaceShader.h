#ifndef REALITYKIT_SURFACESHADER_H_
#define REALITYKIT_SURFACESHADER_H_

//
//  Copyright © 2021 Apple Inc. All rights reserved.
//
#if defined(__METAL_VERSION__)

#ifndef __REALITYKIT_INDIRECT
#error "Please include <RealityKit/RealityKit.h> instead of individual files directly"
#endif

#include <RealityKit/RealityKitMaterialParameters.h>
#include <RealityKit/RealityKitTextures.h>
#include <RealityKit/RealityKitTypes.h>

#include <metal_stdlib>
#include <metal_types>

namespace realitykit
{
struct surface_parameters;

namespace surface
{
struct surface_data_t;

namespace api
{
// Uniforms

RK_API float time(thread surface_data_t &data);

RK_API thread texture::texture_data_t &textures(thread surface_data_t &data);
RK_API thread material::material_constants_t &material_constants(thread surface_data_t &data);
RK_API float4 custom_parameter(thread surface_data_t &data);

// Transforms
RK_API metal::float4x4 model_to_world(thread surface_data_t &data);
RK_API metal::float4x4 model_to_view(thread surface_data_t &data);

RK_API metal::float4x4 world_to_view(thread surface_data_t &data);

RK_API metal::float4x4 view_to_projection(thread surface_data_t &data);
RK_API metal::float4x4 projection_to_view(thread surface_data_t &data);

// Geometry

RK_API float3 model_position(thread surface_data_t &data);
RK_API float4 screen_position(thread surface_data_t &data);
RK_API float3 world_position(thread surface_data_t &data);
RK_API float3 view_direction(thread surface_data_t &data);

RK_API float4 color(thread surface_data_t &data);

RK_API float3 geometry_normal(thread surface_data_t &data);
RK_API float3 geometry_tangent(thread surface_data_t &data);
RK_API float3 geometry_bitangent(thread surface_data_t &data);

RK_API float2 uv0(thread surface_data_t &data);
RK_API float2 uv1(thread surface_data_t &data);

RK_API float4 custom_attribute(thread surface_data_t &data);

// Surface

RK_API half3 base_color(thread surface_data_t &data);
RK_API void set_base_color(half3 value, thread surface_data_t &data);

RK_API float3 tangent_space_normal(thread surface_data_t &data);
RK_API void set_tangent_space_normal(float3 value, thread surface_data_t &data);

RK_API half3 emissive_color(thread surface_data_t &data);
RK_API void set_emissive_color(half3 value, thread surface_data_t &data);

RK_API half roughness(thread surface_data_t &data);
RK_API void set_roughness(half value, thread surface_data_t &data);

RK_API half metallic(thread surface_data_t &data);
RK_API void set_metallic(half value, thread surface_data_t &data);

RK_API half ambient_occlusion(thread surface_data_t &data);
RK_API void set_ambient_occlusion(half value, thread surface_data_t &data);

RK_API half specular(thread surface_data_t &data);
RK_API void set_specular(half value, thread surface_data_t &data);

RK_API half opacity(thread surface_data_t &data);
RK_API void set_opacity(half value, thread surface_data_t &data);

RK_API half clearcoat(thread surface_data_t &data);
RK_API void set_clearcoat(half value, thread surface_data_t &data);

RK_API half clearcoat_roughness(thread surface_data_t &data);
RK_API void set_clearcoat_roughness(half value, thread surface_data_t &data);

} // namespace api

// MARK: - Uniforms

/// Uniforms are read-only values that are constant for all vertices and fragments
/// from the same model.
struct uniforms
{
    RK_INLINE uniforms(thread surface::surface_data_t &_data)
        : data(_data)
    {
    }

    /// Returns the current simulation time, which you can use to animate other values,
    /// such as color or position over time.
    ///
    /// Time is expressed as seconds since RealityKit began rendering.
    RK_INLINE float time() const thread
    {
        return surface::api::time(data);
    }

    /// Returns a matrix you can use to transform from model-space into world-space.
    RK_INLINE metal::float4x4 model_to_world() const thread
    {
        return surface::api::model_to_world(data);
    }

    /// Returns a matrix you can use to transform from model-space into view-space.
    RK_INLINE metal::float4x4 model_to_view() const thread
    {
        return surface::api::model_to_view(data);
    }

    /// Returns a matrix you can use to transform from world-space into view-space.
    RK_INLINE metal::float4x4 world_to_view() const thread
    {
        return surface::api::world_to_view(data);
    }

    /// Returns a matrix you can use to transform from view-space into projection-space.
    RK_INLINE metal::float4x4 view_to_projection() const thread
    {
        return surface::api::view_to_projection(data);
    }

    /// Returns a matrix you can use to transform from projection-space into view-space.
    RK_INLINE metal::float4x4 projection_to_view() const thread
    {
        return surface::api::projection_to_view(data);
    }

    /// Returns a float4 value, which you set on a model's `CustomMaterial`.
    ///
    /// You can use this for any purpose, as its value has no pre-existing meaning within RealityKit.
    RK_INLINE float4 custom_parameter() const thread
    {
        return surface::api::custom_parameter(data);
    }

private:
    thread surface::surface_data_t &data;
};

// MARK: - Geometry

/// Geometry properties for a surface shader.
///
/// The geometry object provides access to data about a fragment's input geometry,
/// such as its screen position, normal, and uv's. This data is read-only at the fragment
/// stage. See surface_properties for modifyable values, including tangent-space normal.
struct geometry
{
    RK_INLINE geometry(thread surface::surface_data_t &_data)
        : data(_data)
    {
    }

    /// Returns the fragment's position in screen space.
    ///
    /// Corresponds to the `[[position]]` fragment function input attribute
    RK_INLINE float4 screen_position() const thread
    {
        return surface::api::screen_position(data);
    }

    /// Returns the fragment's position in world space
    RK_INLINE float3 world_position() const thread
    {
        return surface::api::world_position(data);
    }

    /// Returns the fragment's position in model space
    RK_INLINE float3 model_position() const thread
    {
        return surface::api::model_position(data);
    }

    /// Returns the fragment's interpolated vertex color.
    RK_INLINE float4 color() const thread
    {
        return surface::api::color(data);
    }

    /// Returns the normal of the fragment's geometry.
    RK_INLINE float3 normal() const thread
    {
        return surface::api::geometry_normal(data);
    }

    /// Returns the tangent of the fragment's geometry.
    RK_INLINE float3 tangent() const thread
    {
        return surface::api::geometry_tangent(data);
    }

    /// Returns the bitangent of the fragment's geometry.
    RK_INLINE float3 bitangent() const thread
    {
        return surface::api::geometry_bitangent(data);
    }

    /// Returns the interpolated uv0 for the current fragment. This is the raw value, and may need to be flipped to sample into USD textures.
    ///
    /// Most often, you will use this as a primary texture coordinate.
    RK_INLINE float2 uv0() const thread
    {
        return surface::api::uv0(data);
    }

    /// Returns the interpolated uv1 for the current fragment. This is the raw value, and may need to be flipped to sample into USD textures.
    ///
    /// You can use this as secondary texture coordinate or for any other purpose.
    RK_INLINE float2 uv1() const thread
    {
        return surface::api::uv1(data);
    }

    /// Returns a user attribute set by a geometry modifier.
    ///
    /// You set this value in a geometry modifier and the value is interpolated per-fragment,
    /// using Metal's default interpolation mode.
    RK_INLINE float4 custom_attribute() const thread
    {
        return surface::api::custom_attribute(data);
    }

    /// Returns the direction from this fragment to the view, in world-space.
    RK_INLINE float3 view_direction() const thread
    {
        return surface::api::view_direction(data);
    }

private:
    thread surface::surface_data_t &data;
};

// MARK: - Surface Properties

/// Surface properties for a surface shader.
///
/// The surface sub-object allows you to define the surface's properties at this fragment,
/// including color, normal, roughness, etc.
///
/// @code
/// #include <RealityKit/RealityKit.h>
///
/// [[visible]]
/// void mySurfaceShader(realitykit::surface_parameters params)
/// {
///     params.surface().set_base_color(half3(1, 1, 1));
/// }
/// @endcode
///
/// Below is a surface shader for the lit lighting model that emulates 
/// PhysicallyBasedMaterial's behavior.
///
/// @code
/// #include <RealityKit/RealityKit.h>
///
/// [[visible]]
/// void mySurfaceShader(realitykit::surface_parameters params)
/// {
///     constexpr sampler samplerBilinear(coord::normalized,
///                                       address::repeat,
///                                       filter::linear,
///                                       mip_filter::nearest);
///
///     auto tex = params.textures();
///     auto surface = params.surface();
///     float2 uv = params.geometry().uv0();
///     // USD textures require uvs to be flipped.
///     uv.y = 1.0 - uv.y;
///
///     half4 colorSample = tex.base_color().sample(samplerBilinear, uv);
///     half4 emissiveSample = tex.emissive_color().sample(samplerBilinear, uv);
///
///     // Color
///     surface.set_base_color(colorSample.rgb * half3(params.material_constants().base_color_tint()));
///     surface.set_emissive_color(max(emissiveSample.rgb, half3(params.material_constants().emissive_color())));
///
///     // Opacity
///     surface.set_opacity(tex.opacity().sample(samplerBilinear, uv).r
///                         * params.material_constants().opacity_scale()
///                         * colorSample.a);
///
///     // Normal
///     half3 normal = realitykit::unpack_normal(tex.normal().sample(samplerBilinear, uv).rgb);
///     surface.set_normal(float3(normal));
///
///     // Roughness and Metallic
///     surface.set_roughness(tex.roughness().sample(samplerBilinear, uv).r
///                           * params.material_constants().roughness_scale());
///     surface.set_metallic(tex.metallic().sample(samplerBilinear, uv).r
///                          * params.material_constants().metallic_scale());
///
///     // Ambient and Specular
///     surface.set_ambient_occlusion(tex.ambient_occlusion().sample(samplerBilinear, uv).r);
///     surface.set_specular(tex.specular().sample(samplerBilinear, uv).r
///                          * params.material_constants().specular_scale());
/// }
/// @endcode
struct surface_properties
{
    RK_INLINE surface_properties(thread surface::surface_data_t &_data)
        : data(_data)
    {
    }

    /// Returns the base color for the fragment. The default value is (1,1,1)
    ///
    /// For materials using the unlit lighting model, use set_emissive_color() instead.
    RK_INLINE half3 base_color() const thread
    {
        return surface::api::base_color(data);
    }

    /// Set the base color of this fragment. The default value is (1,1,1)
    ///
    /// For materials with the unlit lighting model, use set_emissive_color instead.
    RK_INLINE void set_base_color(half3 value) thread
    {
        surface::api::set_base_color(value, data);
    }

    /// Returns the tangent-space normal of the current fragment.
    ///
    /// Defaults to (0,0,1).
    RK_INLINE float3 normal() thread
    {
        return surface::api::tangent_space_normal(data);
    }

    /// Sets the tangent-space normal of the current fragment.
    ///
    /// You can set this value to influence lighting calculations. The value will
    /// be normalized before storing.
    RK_INLINE void set_normal(float3 value) thread
    {
        return surface::api::set_tangent_space_normal(metal::normalize(value), data);
    }

    /// Returns the emissive color for the fragment's material. The default value is (0,0,0)
    RK_INLINE half3 emissive_color() const thread
    {
        return surface::api::emissive_color(data);
    }

    /// Set the emissive color of this fragment.
    ///
    /// Use this to add light emitted for glowing materials, or as the output color when
    /// using the unlit lighting model.
    RK_INLINE void set_emissive_color(half3 value) thread
    {
        surface::api::set_emissive_color(value, data);
    }

    /// Returns the roughness of the fragment's material. The default value is 0.
    RK_INLINE half roughness() const thread
    {
        return surface::api::roughness(data);
    }

    /// Set the roughness value of this fragment.
    RK_INLINE void set_roughness(half value) thread
    {
        surface::api::set_roughness(value, data);
    }

    /// Returns the metallic of the fragment's material. The default value is 0.
    RK_INLINE half metallic() const thread
    {
        return surface::api::metallic(data);
    }

    /// Set the metallic value of this fragment.
    RK_INLINE void set_metallic(half value) thread
    {
        surface::api::set_metallic(value, data);
    }

    /// Returns the ambient occlusion value of the fragment's material. The default value is 1.
    RK_INLINE half ambient_occlusion() const thread
    {
        return surface::api::ambient_occlusion(data);
    }

    /// Set the ambient occlusion value of this fragment.
    RK_INLINE void set_ambient_occlusion(half value) thread
    {
        surface::api::set_ambient_occlusion(value, data);
    }

    /// Returns the specular value of this fragment. The default value is 0.
    RK_INLINE half specular() const thread
    {
        return surface::api::specular(data);
    }

    /// Set the specular value of this fragment.
    RK_INLINE void set_specular(half value) thread
    {
        surface::api::set_specular(value, data);
    }

    /// Returns any previously set opacity for this fragment. The default value is 1.
    RK_INLINE half opacity() const thread
    {
        return surface::api::opacity(data);
    }

    /// Set the opacity of this fragment. When the material has a transparent
    /// blending mode, this specifies how opaque the fragment is.
    ///
    /// @see CustomMaterial.blending
    RK_INLINE void set_opacity(half value) thread
    {
        surface::api::set_opacity(value, data);
    }

    /// Returns any previously set clearcoat value for this fragment. The default value is 0.
    RK_INLINE half clearcoat() const thread
    {
        return surface::api::clearcoat(data);
    }

    /// Set the clearcoat value for this fragment.
    ///
    /// @discussion This requires that the CustomMaterial's lighting model is clearcoat, otherwise
    /// its value will be ignored.
    RK_INLINE void set_clearcoat(half value) thread
    {
        surface::api::set_clearcoat(value, data);
    }

    /// Returns any previously set clearcoat roughness value for this fragment. The default value is 0.
    RK_INLINE half clearcoat_roughness() const thread
    {
        return surface::api::clearcoat_roughness(data);
    }

    /// Set the clearcoat roughness value for this fragment.
    ///
    /// @discussion This requires that the CustomMaterial's lighting model is clearcoat, otherwise
    /// its value will be ignored.
    RK_INLINE void set_clearcoat_roughness(half value) thread
    {
        surface::api::set_clearcoat_roughness(value, data);
    }

private:
    thread surface::surface_data_t &data;
};
}

// MARK: - Surface Parameters

/// Parameter passed to surface shader functions, which you use to define the surface's properties
/// at this fragment. You control the full appearance of the surface; any values not set by your surface
/// shader use default values.
///
/// Values are grouped into sub-objects of related values. For example, you can use `textures()`
/// to access textures bound by your application and `surface()` to define the surface appearance.
///
/// Example shader which pulses its color over time, on a relatively rough surface.
///
/// @code
/// #include <RealityKit/RealityKit.h>
///
/// [[visible]]
/// void pulsingSurfaceShader(realitykit::surface_parameters params)
/// {
///     float intensity = sin(params.uniforms().time());
///     params.surface().set_base_color(half3(intensity));
///     params.surface().set_roughness(0.75);
/// }
/// @endcode
struct surface_parameters
{
    RK_INLINE surface_parameters(thread surface::surface_data_t &_data)
        : data(_data)
    {
    }

    RK_INLINE surface_parameters(const thread surface_parameters &p) = default;

    /// Returns the uniforms associated with this fragments.
    ///
    /// Uniforms are read-only values that are constant across all vertices and fragments
    /// from the same model.
    RK_INLINE surface::uniforms uniforms() const thread
    {
        return surface::uniforms(data);
    }

    /// Returns the geometric properties of the current fragment
    ///
    /// Geometry is read-only at the fragment stage. See surface() for modifyable values,
    /// including tangent-space normal.
    RK_INLINE surface::geometry geometry() const thread
    {
        return surface::geometry(data);
    }

    /// Returns an object you use to define the surface's properties for this fragment.
    ///
    /// All properties are initialized to default values.
    RK_INLINE surface::surface_properties surface() thread
    {
        return surface::surface_properties(data);
    }

    /// Returns the textures associated with this model, allowing you to retrieve
    /// and sample textures set on the model.
    RK_INLINE texture::textures textures() const thread
    {
        return texture::textures(surface::api::textures(data));
    }

    /// Returns the material constants associated with this model. These values
    /// are constant across a given model, allowing you to access parameters set on
    /// the CustomMaterial, such as base_color_tint or roughness.
    RK_INLINE material::material_parameters material_constants() const thread
    {
        return material::material_parameters(surface::api::material_constants(data));
    }

private:
    thread surface::surface_data_t &data;
};
} // namespace realitykit

#endif // __METAL_VERSION__
#endif // REALITYKIT_SURFACESHADER_H_
