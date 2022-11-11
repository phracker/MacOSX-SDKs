#ifndef REALITYKIT_GEOMETRYMODIFIER_H_
#define REALITYKIT_GEOMETRYMODIFIER_H_

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
struct geometry_parameters;

namespace geometry_modifier
{
struct geometry_data_t;

namespace api
{
// Uniforms

RK_API float time(thread geometry_data_t &data);

RK_API metal::float2 uv0_offset(thread geometry_data_t &data);
RK_API metal::float2x2 uv0_transform(thread geometry_data_t &data);

RK_API metal::float2 uv1_offset(thread geometry_data_t &data);
RK_API metal::float2x2 uv1_transform(thread geometry_data_t &data);

RK_API float4 custom_parameter(thread geometry_data_t &data);

RK_API thread texture::texture_data_t &textures(thread geometry_data_t &data);
RK_API thread material::material_constants_t &material_constants(thread geometry_data_t &data);

// Transforms

RK_API metal::float4x4 model_to_world(thread geometry_data_t &data);
RK_API metal::float4x4 world_to_model(thread geometry_data_t &data);

RK_API metal::float3x3 normal_to_world(thread geometry_data_t &data);

RK_API metal::float4x4 model_to_view(thread geometry_data_t &data);

RK_API metal::float4x4 view_to_projection(thread geometry_data_t &data);
RK_API metal::float4x4 projection_to_view(thread geometry_data_t &data);

// Geometry

RK_API uint vertex_id(thread geometry_data_t &data);
RK_API float3 position(thread geometry_data_t &data);

RK_API float3 model_position_offset(thread geometry_data_t &data);
RK_API void set_model_position_offset(float3 value, thread geometry_data_t &data);

RK_API float4 color(thread geometry_data_t &data);
RK_API void set_color(float4 value, thread geometry_data_t &data);

RK_API float3 normal(thread geometry_data_t &data);
RK_API void set_normal(float3 value, thread geometry_data_t &data);

RK_API float3 bitangent(thread geometry_data_t &data);
RK_API void set_bitangent(float3 value, thread geometry_data_t &data);

RK_API float2 uv0(thread geometry_data_t &data);
RK_API void set_uv0(float2 value, thread geometry_data_t &data);

RK_API float2 uv1(thread geometry_data_t &data);
RK_API void set_uv1(float2 value, thread geometry_data_t &data);

RK_API float4 custom_attribute(thread geometry_data_t &data);
RK_API void set_custom_attribute(float4 value, thread geometry_data_t &data);
}

// MARK: - Uniforms

/// Uniforms are read-only values that are constant for all vertices from the same model.
/// You can retrieve this object by calling `geometry_parameters.uniforms()`
struct uniforms
{
    RK_INLINE uniforms(thread geometry_data_t &_data)
        : data(_data)
    {
    }

    /// Returns the current simulation time, which you can use to animate other values,
    /// such as color or position over time.
    ///
    /// Time is expressed as seconds since RealityKit began rendering.
    RK_INLINE float time() const thread
    {
        return geometry_modifier::api::time(data);
    }

    /// Returns a matrix you can use to transform from model-space into world-space.
    RK_INLINE metal::float4x4 model_to_world() const thread
    {
        return geometry_modifier::api::model_to_world(data);
    }

    /// Returns a matrix you can use to transform from world-space into model-space.
    RK_INLINE metal::float4x4 world_to_model() const thread
    {
        return geometry_modifier::api::world_to_model(data);
    }

    /// Returns a 3x3 matrix useful for transforming normal vectors from model-space
    /// into world space.
    RK_INLINE metal::float3x3 normal_to_world() const thread
    {
        return geometry_modifier::api::normal_to_world(data);
    }

    /// Returns a matrix you can use to transform from model-space into view-space.
    RK_INLINE metal::float4x4 model_to_view() const thread
    {
        return geometry_modifier::api::model_to_view(data);
    }

    /// Returns a matrix you can use to transform from view-space into projection-space.
    RK_INLINE metal::float4x4 view_to_projection() const thread
    {
        return geometry_modifier::api::view_to_projection(data);
    }

    /// Returns a matrix you can use to transform from projection-space into view-space.
    RK_INLINE metal::float4x4 projection_to_view() const thread
    {
        return geometry_modifier::api::projection_to_view(data);
    }

    /// Returns a float4 value, which you set on a model's `CustomMaterial`.
    ///
    /// You can use this for any purpose, as its value has no pre-existing meaning within RealityKit.
    RK_INLINE float4 custom_parameter() const thread
    {
        return geometry_modifier::api::custom_parameter(data);
    }

    /// Returns the value of a model's UV0 offset.
    ///
    /// While the built-in PhysicallyBasedMaterial shaders use this to control uv0, Geometry
    /// Modifiers give you control to use this in any way you see fit.
    ///
    /// @see uv0_transform()
    RK_INLINE float2 uv0_offset() const thread
    {
        return geometry_modifier::api::uv0_offset(data);
    }

    /// Returns the value of a model's UV0 transform.
    ///
    /// While the built-in PhysicallyBasedMaterial shaders use this to control uv0, Geometry
    /// Modifiers give you control to use this in any way you see fit.
    ///
    /// If you want to apply this to uv0, you can use code like the following.
    ///
    /// @code
    /// #include <RealityKit/RealityKit.h>
    ///
    /// [[visible]]
    /// void geometryModifier(realitykit::geometry_parameters params)
    /// {
    ///   params.geometry().set_uv0(params.uniforms().uv0_transform() * params.geometry().uv0() + params.uniforms().uv0_offset());
    /// }
    /// @endcode
    RK_INLINE metal::float2x2 uv0_transform() const thread
    {
        return geometry_modifier::api::uv0_transform(data);
    }

    /// Returns the value of a model's UV1 offset.
    ///
    /// While the built-in PhysicallyBasedMaterial shaders use this to control uv1, Geometry
    /// Modifiers give you control to use this in any way you see fit.
    ///
    /// @see uv1_transform()
    RK_INLINE float2 uv1_offset() const thread
    {
        return geometry_modifier::api::uv1_offset(data);
    }

    /// Returns the value of a model's UV1 transform.
    ///
    /// While the built-in PhysicallyBasedMaterial shaders use this to control uv1, Geometry
    /// Modifiers give you control to use this in any way you see fit.
    ///
    /// If you want to apply this to uv1, you can use code like the following.
    ///
    /// @code
    /// #include <RealityKit/RealityKit.h>
    ///
    /// [[visible]]
    /// void geometryModifier(realitykit::geometry_parameters params)
    /// {
    ///   params.geometry().set_uv1(params.uniforms().uv1_transform() * params.geometry().uv1() + params.uniforms().uv1_offset());
    /// }
    /// @endcode
    RK_INLINE metal::float2x2 uv1_transform() const thread
    {
        return geometry_modifier::api::uv1_transform(data);
    }

private:
    thread geometry_data_t &data;
};

// MARK: - Geometry

/// Geometry gives you access to values contained on each vertex within a model,
/// such as position and color. You can also modify most of the properties, which
/// you can access later from the surface shader.
struct geometry
{
    RK_INLINE geometry(thread geometry_data_t &_data)
        : data(_data)
    {
    }

    /// Returns per-vertex identifier, as specified by Metal.
    ///
    /// See `vertex_id` in Metal Shading Language Section 5.2.3.1.
    RK_INLINE uint vertex_id() const thread
    {
        return geometry_modifier::api::vertex_id(data);
    }

    /// Position of this vertex in model-space. This will be the value originally
    /// set when the model was created. You can provide an offset to this value using
    /// set_model_position_offset().
    ///
    /// @see set_model_position_offset()
    RK_INLINE float3 model_position() const thread
    {
        return geometry_modifier::api::position(data);
    }

    /// Position of this vertex in world-space. This value is computed based on the model_position()
    /// and the object's position in the virtual world.
    RK_INLINE float3 world_position() const thread
    {
        return (api::model_to_world(data) * float4(model_position(), 1)).xyz;
    }

    /// Returns any offset for the current vertex, in model-space. Defaults to
    /// (0,0,0) unless previously set by `set_model_position_offset()`.
    RK_INLINE float3 model_position_offset() const thread
    {
        return geometry_modifier::api::model_position_offset(data);
    }

    /// Offsets the current vertex by the given value in model-space. The value you provide
    /// will be added to `model_position()` to determine its final position.
    RK_INLINE void set_model_position_offset(float3 value) thread
    {
        geometry_modifier::api::set_model_position_offset(value, data);
    }

    /// Returns any offset for the current vertex, by transforming model_position_offset()
    /// into world-space.
    RK_INLINE float3 world_position_offset() const thread
    {
        return geometry_modifier::api::normal_to_world(data) * model_position_offset();
    }

    /// Offsets the current vertex by the given value in world-space. The value will be
    /// transformed into model-space before storing.
    RK_INLINE void set_world_position_offset(float3 value) thread
    {
        float4 model_offset = geometry_modifier::api::world_to_model(data) * float4(value, 0.0);

        set_model_position_offset(model_offset.xyz);
    }

    /// Returns color for the current vertex. This value is initially any color specified
    /// on the current vertex, and can be changed with set_color().
    RK_INLINE float4 color() const thread
    {
        return geometry_modifier::api::color(data);
    }

    /// Sets the current vertex's color.
    RK_INLINE void set_color(float4 value) thread
    {
        geometry_modifier::api::set_color(value, data);
    }

    /// Returns the normal for the current vertex.
    RK_INLINE float3 normal() const thread
    {
        return geometry_modifier::api::normal(data);
    }

    /// Sets the current vertex's normal.
    RK_INLINE void set_normal(float3 value) thread
    {
        geometry_modifier::api::set_normal(value, data);
    }

    /// Returns the bitangent for the current vertex.
    RK_INLINE float3 bitangent() const thread
    {
        return geometry_modifier::api::bitangent(data);
    }

    /// Sets the current vertex's bitangent.
    RK_INLINE void set_bitangent(float3 value) thread
    {
        geometry_modifier::api::set_bitangent(value, data);
    }

    /// Returns uv0 for the current vertex. This is the raw value, and may need to be flipped to sample into USD textures.
    ///
    /// Most often, you will use this as a primary texture coordinate.
    RK_INLINE float2 uv0() const thread
    {
        return geometry_modifier::api::uv0(data);
    }

    /// Sets uv0 for the current vertex.
    RK_INLINE void set_uv0(float2 value) thread
    {
        geometry_modifier::api::set_uv0(value, data);
    }

    /// Returns uv1 for the current vertex. This is the raw value, and may need to be flipped to sample into USD textures.
    ///
    /// You can use this as secondary texture coordinate or for any other
    /// purposes.
    RK_INLINE float2 uv1() const thread
    {
        return geometry_modifier::api::uv1(data);
    }

    /// Sets uv1 for the current vertex.
    RK_INLINE void set_uv1(float2 value) thread
    {
        geometry_modifier::api::set_uv1(value, data);
    }

    /// Returns any user-specified attribute on the current vertex.
    ///
    /// Defaults to `(0,0,0,0)` unless previously set via set_custom_attribute.
    RK_INLINE float4 custom_attribute() const thread
    {
        return geometry_modifier::api::custom_attribute(data);
    }

    /// Stores an attribute on the vertex which will later be available in the surface shader.
    RK_INLINE void set_custom_attribute(float4 value) thread
    {
        geometry_modifier::api::set_custom_attribute(value, data);
    }

private:
    thread geometry_data_t &data;
};
}

// MARK: - Geometry Parameters

/// Parameter passed to geometry modifier functions, providing access to input and
/// output values.
///
/// Geometry modifier functions allow you to modify vertices and their related properties
/// before rasterization. For example, you can add an offset which simulates the effect of
/// wind on long grass.
///
/// Values are grouped into sub-objects of related values. For example, you can use `textures()`
/// to access textures bound by your application.
///
/// @code
/// #include <RealityKit/RealityKit.h>
///
/// [[visible]]
/// void myGeometryModifier(realitykit::geometry_parameters params)
/// {
/// }
/// @endcode
///
/// Below is a geometry modifier that emulates PhysicallyBasedMaterial's behavior.
///
/// @code
/// #include <RealityKit/RealityKit.h>
///
/// [[visible]]
/// void myGeometryModifier(realitykit::geometry_parameters params)
/// {
///     auto geo = params.geometry();
///     auto uniforms = params.uniforms();
///
///     geo.set_uv0(uniforms.uv0_transform() * geo.uv0() + uniforms.uv0_offset());
///     geo.set_uv1(uniforms.uv1_transform() * geo.uv1() + uniforms.uv1_offset());
/// }
/// @endcode
struct geometry_parameters
{
    RK_INLINE geometry_parameters(thread geometry_modifier::geometry_data_t &_data)
        : data(_data)
    {
    }

    RK_INLINE geometry_parameters(const thread geometry_parameters &p) = default;

    /// Returns the uniforms associated with this model.
    ///
    /// Uniforms are read-only values that are constant for all vertices and fragments
    /// from the same model.
    RK_INLINE geometry_modifier::uniforms uniforms() const thread
    {
        return geometry_modifier::uniforms(data);
    }

    /// Returns the geometry associated with the current vertex, allowing you to access
    /// and customize aspects of the model, such as the color or uvs, or to add offsets
    /// to the position.
    RK_INLINE geometry_modifier::geometry geometry() thread
    {
        return geometry_modifier::geometry(data);
    }

    /// Returns the textures associated with this model, allowing you to retrieve
    /// and sample textures set on the model.
    RK_INLINE texture::textures textures() const thread
    {
        return texture::textures(geometry_modifier::api::textures(data));
    }

    /// Returns the material constants associated with this model. These values
    /// are constant across a given model, and allow access to parameters set on
    /// the `CustomMaterial`, such as `base_color_tint` or `roughness`.
    RK_INLINE material::material_parameters material_constants() const thread
    {
        return material::material_parameters(geometry_modifier::api::material_constants(data));
    }

private:
    thread geometry_modifier::geometry_data_t &data;
};
}

#endif // __METAL_VERSION__
#endif // REALITYKIT_GEOMETRYMODIFIER_H_
