#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/skeleton_joint.h>)
//
//  skeleton_joint.h
//  ARKit
//
//  Created by Nathaniel Pohl on 8/18/22.
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef skeleton_joint_h
#define skeleton_joint_h

#import <ARKit/object.h>

#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL(ar_skeleton_joint)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

/**
 Returns a bool value that indicates whether the two skeleton joints are equal.

 @param skeleton_joint A skeleton joint to be compared.
 @param other_skeleton_joint The other skeleton joint to be compared to.

 @return YES if the skeleton joints are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_skeleton_joint_is_equal_to_skeleton_joint(ar_skeleton_joint_t _Nullable skeleton_joint,
                                                            ar_skeleton_joint_t _Nullable other_skeleton_joint) AR_REFINED_FOR_SWIFT;

/**
 Get a joint's index.

 @param joint The joint.

 @return The index of the joint.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN uint64_t ar_skeleton_joint_get_index(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

/**
 Get a joint's parent joint.

 @param joint the joint.

 @return Parent joint. This function will return null for the root node.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_skeleton_joint_t _Nullable ar_skeleton_joint_get_parent(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from the joint to its parent joint's coordinate system.

 @param joint The joint.

 @note For a hand skeleton, the root of all these transforms starts at the wrist, then the next joint out (metacarpals and forearm) are relative to
 the wrist, then all knuckles are relative to the metacarpals and so on until the finger tips.

 @return The transform from the joint to its parent joint's coordinate system. This function will return an identity matrix when called for the root
 joint.
 */

API_AVAILABLE(visionos(1.0))
AR_EXTERN simd_float4x4 ar_skeleton_joint_get_parent_from_joint_transform(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from the joint to the anchor's coordinate system.

 @param joint The joint.

 @return The transform from the joint to the anchor's coordinate system.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN simd_float4x4 ar_skeleton_joint_get_anchor_from_joint_transform(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

/**
 Determine whether a joint is tracked.

 @param joint The joint.

 @return `true` if the joint is tracked, `false` otherwise.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN bool ar_skeleton_joint_is_tracked(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler for enumerating skeleton joints.

 @param joint The joint.

 @return `true` to continue enumerating to the next joint name, `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (^ar_skeleton_joint_enumerator_t)(ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating skeleton joints.

 @param context The application-defined context.
 @param joint The joint.
 @return `true` to continue enumerating to the next joint, `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (*ar_skeleton_joint_enumerator_function_t)(void *_Nullable context, ar_skeleton_joint_t joint) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // skeleton_joint_h
#else
#import <ARKitCore/skeleton_joint.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/skeleton_joint.h>)