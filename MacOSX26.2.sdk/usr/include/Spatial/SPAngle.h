#ifndef Spatial_SPAngle_h
#define Spatial_SPAngle_h

#include <Spatial/Structures.h>
#include <math.h>

// MARK: - Public API

/*!
 @abstract Returns an angle with the value specified in degrees.
 
 @param degrees The angle in degrees.
 @returns A new angle structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleMakeWithDegrees(double degrees)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns an angle with the value specified in radians.
 
 @param radians The angle in radians.
 @returns A new angle structure.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleMakeWithRadians(double radians)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the angle in degrees.
 
 @param angle The source angle.
 @returns The angle in degrees.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPAngleGetDegrees(SPAngle angle)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns @p true if both rotation angles are equal.
///
/// Note that this function compares the raw value of each angle and doesn't
/// normalize the values. For example, 360° does **not** equal 0°.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPAngleEqualToAngle(SPAngle angle1, SPAngle angle2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Header inline implementations

SPATIAL_SWIFT_NAME(Angle2D.init(degrees:))
SPATIAL_OVERLOADABLE
SPAngle SPAngleMakeWithDegrees(double degrees) {
  return (SPAngle){ .radians = degrees / 180 * M_PI };
}

SPATIAL_SWIFT_NAME(Angle2D.init(radians:))
SPATIAL_OVERLOADABLE
SPAngle SPAngleMakeWithRadians(double radians) {
  return (SPAngle){ .radians = radians };
}

SPATIAL_SWIFT_NAME(getter:Angle2D.degrees(self:))
SPATIAL_OVERLOADABLE
double SPAngleGetDegrees(SPAngle angle) {
  return angle.radians * 180 / M_PI;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPAngleEqualToAngle(SPAngle angle1, SPAngle angle2) {
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
SPAngle SPAngleAcos(double x)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleAcos(double x) {
#ifdef __cplusplus
    return SPAngleMakeWithRadians(::__tg_acos(x));
#else
    return SPAngleMakeWithRadians(acos(x));
#endif
}

/*!
 @abstract Returns the inverse sine of the specified value.
 
 @param x The source value.
 @returns The inverse sine of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleAsin(double x)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleAsin(double x) {
    return SPAngleMakeWithRadians(_sp_simd_asin(x));
}

/*!
 @abstract Returns the inverse tangent of the specified value.
 
 @param x The source value.
 @returns The inverse tangent of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleAtan(double x)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleAtan(double x) {
#ifdef __cplusplus
    return SPAngleMakeWithRadians(::__tg_atan(x));
#else
    return SPAngleMakeWithRadians(atan(x));
#endif
}

/*!
 @abstract Returns the inverse hyperbolic cosine of the specified value.
 
 @param x The source value.
 @returns The inverse hyperbolic cosine of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleAcosh(double x)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleAcosh(double x) {
#ifdef __cplusplus
    return SPAngleMakeWithRadians(::__tg_acosh(x));
#else
    return SPAngleMakeWithRadians(acosh(x));
#endif
}

/*!
 @abstract Returns the inverse hyperbolic sine of the specified value.
 
 @param x The source value.
 @returns The inverse hyperbolic sine of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleAsinh(double x)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleAsinh(double x) {
#ifdef __cplusplus
    return SPAngleMakeWithRadians(::__tg_asinh(x));
#else
    return SPAngleMakeWithRadians(asinh(x));
#endif
}

/*!
 @abstract Returns the inverse hyperbolic tangent of the specified value.
 
 @param x The source value.
 @returns The inverse hyperbolic tangent of the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleAtanh(double x)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleAtanh(double x) {
#ifdef __cplusplus
    return SPAngleMakeWithRadians(::__tg_atanh(x));
#else
    return SPAngleMakeWithRadians(atanh(x));
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
SPAngle SPAngleAtan2(double y, double x)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleAtan2(double y, double x) {
    return SPAngleMakeWithRadians(_sp_simd_atan2(y, x));
}

/*!
 @abstract Returns the cosine of the specified angle.
 
 @param angle The source angle.
 @returns The cosine of the specified angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPAngleCos(SPAngle angle)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPAngleCos(SPAngle angle) {
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
double SPAngleSin(SPAngle angle)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPAngleSin(SPAngle angle) {
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
double SPAngleTan(SPAngle angle)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPAngleTan(SPAngle angle) {
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
double SPAngleCosh(SPAngle angle)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPAngleCosh(SPAngle angle) {
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
double SPAngleSinh(SPAngle angle)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPAngleSinh(SPAngle angle) {
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
double SPAngleTanh(SPAngle angle)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPAngleTanh(SPAngle angle) {
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
SPAngle SPAngleNormalize(SPAngle angle)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleNormalize(SPAngle angle) {

        double radians = fmod(angle.radians, M_PI * 2);

        if (radians <= -M_PI) {
            radians += M_PI * 2;
        }
        else if (radians > M_PI) {
            radians -= M_PI * 2;
        }

    return SPAngleMakeWithRadians(radians);
}

// MARK: - Negation

/*!
 @abstract Returns the additive inverse of the specified angle.
 
 @param angle The source angle.
 @returns  The normalized angle.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPAngleNegate(SPAngle angle)
__API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPAngleNegate(SPAngle angle) {
    return SPAngleMakeWithRadians(-angle.radians);
}


#endif /* Spatial_SPAngle_h */
