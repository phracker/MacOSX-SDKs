
#ifndef SPAngleFloat_h
#define SPAngleFloat_h

#include <Spatial/StructuresFloat.h>
#include <math.h>

// MARK: - SINGLE-PRECISION Public API

/*!
 @abstract Returns an angle with the value specified in degrees.
 
 @param degrees The angle in degrees.
 @returns A new angle structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatMakeWithDegrees(float degrees)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns an angle with the value specified in radians.
 
 @param radians The angle in radians.
 @returns A new angle structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatMakeWithRadians(float radians)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/*!
 @abstract Returns the angle in degrees.
 
 @param angle The source angle.
 @returns The angle in degrees.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPAngleFloatGetDegrees(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Returns @p true if both rotation angles are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAngleFloatEqualToAngle(SPAngleFloat angle1, SPAngleFloat angle2)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

// MARK: - Header inline implementations

SPATIAL_REFINED_FOR_SWIFT // SPATIAL_SWIFT_NAME(Angle2DFloat.init(degrees:))
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatMakeWithDegrees(float degrees) {
  return (SPAngleFloat){ .radians = degrees / 180 * (float)M_PI };
}

SPATIAL_SWIFT_NAME(Angle2DFloat.init(radians:))
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatMakeWithRadians(float radians) {
  return (SPAngleFloat){ .radians = radians };
}

SPATIAL_REFINED_FOR_SWIFT // SPATIAL_SWIFT_NAME(getter:Angle2DFloat.degrees(self:))
SPATIAL_OVERLOADABLE
float SPAngleFloatGetDegrees(SPAngleFloat angle) {
  return (float)(angle.radians * 180 / M_PI);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPAngleFloatEqualToAngle(SPAngleFloat angle1, SPAngleFloat angle2) {
    return angle1.radians == angle2.radians;
}

// MARK: - Trigonometric Functions

/*!
 @abstract Returns the inverse cosine of the specified value.
 
 @param x The source value.
 @returns The inverse cosine of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAcos(float x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAcos(float x) {
#ifdef __cplusplus
    return SPAngleFloatMakeWithRadians(::__tg_acos(x));
#else
    return SPAngleFloatMakeWithRadians(acos(x));
#endif
}

/*!
 @abstract Returns the inverse sine of the specified value.
 
 @param x The source value.
 @returns The inverse sine of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAsin(float x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAsin(float x) {
    return SPAngleFloatMakeWithRadians(_sp_simd_asin(x));
}

/*!
 @abstract Returns the inverse tangent of the specified value.
 
 @param x The source value.
 @returns The inverse tangent of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAtan(float x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAtan(float x) {
#ifdef __cplusplus
    return SPAngleFloatMakeWithRadians(::__tg_atan(x));
#else
    return SPAngleFloatMakeWithRadians(atan(x));
#endif
}

/*!
 @abstract Returns the inverse hyperbolic cosine of the specified value.
 
 @param x The source value.
 @returns The inverse hyperbolic cosine of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAcosh(float x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAcosh(float x) {
#ifdef __cplusplus
    return SPAngleFloatMakeWithRadians(::__tg_acosh(x));
#else
    return SPAngleFloatMakeWithRadians(acosh(x));
#endif
}

/*!
 @abstract Returns the inverse hyperbolic sine of the specified value.
 
 @param x The source value.
 @returns The inverse hyperbolic sine of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAsinh(float x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAsinh(float x) {
#ifdef __cplusplus
    return SPAngleFloatMakeWithRadians(::__tg_asinh(x));
#else
    return SPAngleFloatMakeWithRadians(asinh(x));
#endif
}

/*!
 @abstract Returns the inverse hyperbolic tangent of the specified value.
 
 @param x The source value.
 @returns The inverse hyperbolic tangent of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAtanh(float x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAtanh(float x) {
#ifdef __cplusplus
    return SPAngleFloatMakeWithRadians(::__tg_atanh(x));
#else
    return SPAngleFloatMakeWithRadians(atanh(x));
#endif
}

/*!
 @abstract Returns the 2-argument arctangent of the specified values.
 
 @param y The @p y source value.
 @param x The @p x source value.
 @returns The inverse hyperbolic tangent of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAtan2(float y, float x)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatAtan2(float y, float x) {
    return SPAngleFloatMakeWithRadians(_sp_simd_atan2(y, x));
}

/*!
 @abstract Returns the cosine of the specified angle.
 
 @param angle The source angle.
 @returns The cosine of the specified angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPAngleFloatCos(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPAngleFloatCos(SPAngleFloat angle) {
#ifdef __cplusplus
    return ::__tg_cos(angle.radians);
#else
    return cos(angle.radians);
#endif
}

/*!
 @abstract Returns the sine of the specified angle.
 
 @param angle The source angle.
 @returns The sine of the specified angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPAngleFloatSin(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPAngleFloatSin(SPAngleFloat angle) {
#ifdef __cplusplus
    return ::__tg_sin(angle.radians);
#else
    return sin(angle.radians);
#endif
}

/*!
 @abstract Returns the tangent of the specified angle.
 
 @param angle The source angle.
 @returns The tangent of the specified angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPAngleFloatTan(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPAngleFloatTan(SPAngleFloat angle) {
#ifdef __cplusplus
    return ::__tg_tan(angle.radians);
#else
    return tan(angle.radians);
#endif
}

/*!
 @abstract Returns the hyperbolic cosine of the specified angle.
 
 @param angle The source angle.
 @returns The hyperbolic cosine of the specified angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPAngleFloatCosh(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPAngleFloatCosh(SPAngleFloat angle) {
#ifdef __cplusplus
    return ::__tg_cosh(angle.radians);
#else
    return cosh(angle.radians);
#endif
}

/*!
 @abstract Returns the hyperbolic sine of the specified angle.
 
 @param angle The source angle.
 @returns The hyperbolic sine of the specified angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPAngleFloatSinh(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPAngleFloatSinh(SPAngleFloat angle) {
#ifdef __cplusplus
    return ::__tg_sinh(angle.radians);
#else
    return sinh(angle.radians);
#endif
}

/*!
 @abstract Returns the hyperbolic tangent of the specified angle.
 
 @param angle The source angle.
 @returns The hyperbolic tangent of the specified angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
float SPAngleFloatTanh(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
float SPAngleFloatTanh(SPAngleFloat angle) {
#ifdef __cplusplus
    return ::__tg_tanh(angle.radians);
#else
    return tanh(angle.radians);
#endif
}

// MARK: - Normalization

/*!
 @abstract Returns the specified angle normalized to `(-π, π]` radians (`(-180°, 180.0°]`).
 
 @param angle The source angle.
 @returns  The normalized angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatNormalize(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatNormalize(SPAngleFloat angle) {

        float radians = fmod(angle.radians, M_PI * 2);

        if (radians <= -M_PI) {
            radians += M_PI * 2;
        }
        else if (radians > M_PI) {
            radians -= M_PI * 2;
        }

    return SPAngleFloatMakeWithRadians(radians);
}

// MARK: - Negation

/*!
 @abstract Returns the additive inverse of the specified angle.
 
 @param angle The source angle.
 @returns  The normalized angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatNegate(SPAngleFloat angle)
__API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngleFloat SPAngleFloatNegate(SPAngleFloat angle) {
    return SPAngleFloatMakeWithRadians(-angle.radians);
}

#endif /* SPAngleFloat_h */
