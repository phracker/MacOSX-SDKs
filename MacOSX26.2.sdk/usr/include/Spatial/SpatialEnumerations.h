#ifndef SpatialEnumerations_h
#define SpatialEnumerations_h

// MARK: - SPEulerAngleOrder

/*!
 @abstract Constants that specify the Euler angle order.
*/
typedef enum: uint32_t {
    /*!
     @abstract Pitch-Yaw-Roll
     
     @discussion
     The order of components in the vector matches the axes of rotation:
     
     Pitch (the @p x component) is the rotation about the node's x-axis.
     
     Yaw (the @p y component) is the rotation about the node's y-axis.
     
     Roll (the @p z component) is the rotation about the node's z-axis.
     
     Spatial applies these rotations extrinsically in the specified order: rotation around the world space x-axis,
     then rotation around the world space y-axis, then rotation around the world space z-axis.
     */
    SPEulerPitchYawRoll SPATIAL_REFINED_FOR_SWIFT __API_DEPRECATED("This constant is deprecated, use `SPEulerXYZ`.",
                                                                   macos(13.0, 14.0),
                                                                   ios(16.0, 17.0),
                                                                   watchos(9.0, 10.0),
                                                                   tvos(16.0, 17.0)) = 0x0001,
    
    /*!
    @discussion
    The order of components in the vector matches the axes of rotation:
    
    Pitch (the @p x component) is the rotation about the node's x-axis.
    
    Yaw (the @p y component) is the rotation about the node's y-axis.
    
    Roll (the @p z component) is the rotation about the node's z-axis.
    
    Spatial applies these rotations extrinsically in the specified order: rotation around the world space x-axis,
    then rotation around the world space y-axis, then rotation around the world space z-axis.
    */
   SPEulerXYZ SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0)) = 0x0001,
    
    /*!
     @abstract Roll-Pitch-Yaw
     
     @discussion
     The order of components in the vector matches the axes of rotation:
     
     Roll (the @p z component) is the rotation about the node's z-axis.
     
     Pitch (the @p x component) is the rotation about the node's x-axis.
     
     Yaw (the @p y component) is the rotation about the node's y-axis.
     
     Spatial applies these rotations extrinsically in the specified order: rotation around the world space z-axis,
     then rotation around the world space x-axis, then rotation around the world space y-axis.
     */
    SPEulerZXY SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0)) = 0x0002,
} SPEulerAngleOrder
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Shear enumeration

/// Enumerations that describe an axis.
typedef enum : uint32_t {
    
    /// The operation is along the x-axis.
    SPAxisX SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x0001,
    
    /// The operation is along the y-axis.
    SPAxisY SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x0002,
    
    /// The operation is along the z-axis.
    SPAxisZ SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x0004
 
}
SPAxis
SPATIAL_SWIFT_NAME(Axis3D);

#endif /* SpatialEnumerations_h */
