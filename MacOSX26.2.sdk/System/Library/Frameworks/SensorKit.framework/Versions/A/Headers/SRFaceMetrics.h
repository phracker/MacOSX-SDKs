//
//  SRFaceMetrics.h
//  SensorKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

#if (TARGET_OS_VISION && __has_include(<ARKitCore/ARKitCore.h>)) || (TARGET_OS_IOS && !TARGET_OS_MACCATALYST && !TARGET_OS_SIMULATOR)
#define SR_ARKIT_SUPPORTED 1
@class ARFaceAnchor;
#endif

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, SRFaceMetricsContext) {
    SRFaceMetricsContextDeviceUnlock = 1 << 0,
    SRFaceMetricsContextMessagingAppUsage = 1 << 1,
} API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRFaceMetricsExpression : NSObject  <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property identifier
 * @brief An opaque identifier for the face expression
 * @discussion More information about what this face expression represents can be found in Apple's developer documentation
 */
@property (nonatomic, copy, readonly) NSString *identifier;

/*!
 * @property value
 * @brief double value indicating the current position of the expression
 */
@property (nonatomic, assign, readonly) double value;
@end

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRFaceMetrics: NSObject  <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @property version
 * @brief Algorithm version
 */
@property(nonatomic, copy, readonly) NSString* version;

/*!
 * @property sessionIdentifier
 * @brief Identifier of a camera session
 */
@property(nonatomic, copy, readonly) NSString* sessionIdentifier;

/*!
 * @property context
 * @brief Indicates system context during a camera session, e.g., if the device was unlocked or (and) a messaging app was used
 */
@property(nonatomic, assign, readonly) SRFaceMetricsContext context;

/*!
 * @property faceAnchor
 * @brief Description of a face detected in front of camera
 */
#if SR_ARKIT_SUPPORTED
@property(nonatomic, copy, readonly) ARFaceAnchor *faceAnchor;
#endif

/*!
 * @property wholeFaceExpressions
 * @brief Detected whole face expressions
 */
@property (nonatomic, copy, readonly) NSArray <SRFaceMetricsExpression *> *wholeFaceExpressions;

/*!
 * @property partialFaceExpressions
 * @brief Detected partial face expressions
 */
@property (nonatomic, copy, readonly) NSArray <SRFaceMetricsExpression *> *partialFaceExpressions;
@end
NS_ASSUME_NONNULL_END
