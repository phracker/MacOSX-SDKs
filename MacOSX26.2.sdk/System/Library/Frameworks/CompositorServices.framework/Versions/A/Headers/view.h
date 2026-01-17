//
//  view.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_view_h
#define cp_view_h

CP_NONNULL_EXTERN_C_BEGIN

/*!
 * MARK: View Texture Map
 */

/// An opaque type that describes the relationship between a
/// view and the underlying texture.
///
/// A texture map helps you locate the content for a specific view within
/// a texture. Texture maps are especially important when a layer uses a
/// single texture to manage multiple views. For example, a head-mounted
/// display might store the images for both the left and right eyes in a
/// single texture. Pass this type to other functions to get specific details
/// about the current texture, such as its view bounds or its index into
/// a texture array.
CP_STRUCT_REF(cp_view_texture_map, cp_view_t.TextureMap, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Returns the index of the view’s textures in the drawable.
///
/// - Parameters:
///    - view_texture_map: The texture map for your view.
/// - Returns: The index of the color or depth texture in the drawable.
///
/// Pass the returned index to the ``cp_drawable_get_color_texture``
/// or ``cp_drawable_get_depth_texture`` function.
size_t
cp_view_texture_map_get_texture_index(cp_view_texture_map_t view_texture_map)
CF_SWIFT_NAME(getter:cp_view_texture_map_t.textureIndex(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the index of the view’s texture in an array-based texture type.
///
/// - Parameters:
///    - view_texture_map: The texture map for your view.
/// - Returns: The index of the view’s texture in an array-based texture type.
///
/// Use the returned index to retrieve the view’s texture when the texture
/// type is <doc://com.apple.documentation/documentation/metal/mtltexturetype/type2darray>.
/// When configuring your render pass descriptor, specify the index in the
/// <doc://com.apple.documentation/documentation/metal/mtlrenderpassattachmentdescriptor/1437914-slice>
/// property of the descriptor’s color and depth attachments.
///
/// To request an array-based texture from your layer, configure your layer
/// with the ``cp_layer_renderer_layout/cp_layer_renderer_layout_dedicated`` layout option.
size_t
cp_view_texture_map_get_slice_index(cp_view_texture_map_t view_texture_map)
CF_SWIFT_NAME(getter:cp_view_texture_map_t.sliceIndex(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

#ifdef __OBJC__

/// Returns the portion of the texture that the view uses to draw its content.
///
/// - Parameters:
///   - view_texture_map: The texture map for your view.
/// - Returns: A Metal viewport that specifies the view’s size and location
/// in the texture.
///
/// Call this function to get the size of the view and its location within
/// the texture. If the layer dedicates a separate texture to each view,
/// the texture bounds and view bounds match. However, if the layer uses a
/// shared or layered texture, the view’s location or other slice index
/// might differ.
MTLViewport
cp_view_texture_map_get_viewport(cp_view_texture_map_t view_texture_map)
CF_SWIFT_NAME(getter:cp_view_texture_map_t.viewport(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));
#endif

/*!
 * MARK: View
 */

/// An opaque type that manages the information for how to render
/// content into the current frame.
///
/// Compositor provides a view for each distinct render viewpoint.
/// For example, a head-mounted display typically contains two views:
/// one for each eye. Use the information in the views to set up your
/// render pass descriptor. For example, use it to determine which
/// part of a texture to fill with content.
CP_STRUCT_REF(cp_view, cp_drawable_t.View, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Returns the texture map for this view.
///
/// - Parameters:
///    - view: The view with the texture map.
/// - Returns: The texture map for the layer assigned to this view.
///
/// Use the texture map to fetch additional information you need to
/// draw your content. For example, use it to fetch the rectangle to
/// use for drawing in the associated texture.
cp_view_texture_map_t
cp_view_get_view_texture_map(cp_view_t view)
CF_SWIFT_NAME(getter:cp_view_t.textureMap(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the transformation matrix to convert between the device
/// coordinate space to the position of the view in that space.
///
/// - Parameters:
///    - view: The view to query.
/// - Returns: A transform matrix to the device coordinate space
/// from the view coordinate space.
///
/// When you generate a frame, you specify a pose matrix that indicates
/// the device’s position and orientation in the world coordinate space.
/// When the device is a head-mounted display, the view for each eye
/// has an additional matrix to specify the position of that eye relative
/// to the device’s pose. Multiply the device’s pose matrix by the
/// returned matrix to obtain the view’s location in the world coordinate space.
simd_float4x4
cp_view_get_transform(cp_view_t view)
CF_SWIFT_NAME(getter:cp_view_t.transform(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the tangent values for the angles you use to determine
/// the planes of the viewing frustum.
///
/// - Parameters:
///    - view: The view to query.
/// - Returns: A vector that contains the left, right, top, and bottom
/// tangent values in that order. In other words, the value at index 0
/// contains the left tangent, the value at index 1 contains the right
/// tangent, and so on. The angles and tangent values are always positive.
///
/// In a 3D scene, the viewing frustum is the volume between the near and
/// far clipping planes that contains the scene’s visible content. When
/// you render this content into a view, you generate a two-dimensional
/// version of your content suitable for display onscreen. To ensure
/// your content still looks three-dimensional, apply a perspective
/// projection matrix to your content. This matrix scales your content
/// appropriately based on its distance from the viewing point.
///
/// This function returns the tangent values you use to build the perspective
/// projection matrix for your content. You can also use the values to
/// determine the apparent size of the view at any distance from the viewing
/// point. When you multiply a tangent value by a distance, you obtain
/// the horizontal or vertical distance from the view’s center point to
/// the corresponding rectangle edge at that distance. For a perspective
/// projection matrix, multiply these values by the distance to the near
/// clipping plane and combine them to create the matrix rows you need.
simd_float4
cp_view_get_tangents(cp_view_t view)
API_DEPRECATED("Use cp_drawable_compute_projection instead", visionos(1.0, 2.0))
API_UNAVAILABLE(macosx, ios)
CF_SWIFT_NAME(getter:cp_view_t.tangents(self:));

CP_NONNULL_EXTERN_C_END

#endif /* cp_view_h */
