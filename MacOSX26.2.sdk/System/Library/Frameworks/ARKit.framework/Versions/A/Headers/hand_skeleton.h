#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/hand_skeleton.h>)
//
//  hand_skeleton.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef hand_skeleton_h
#define hand_skeleton_h

#import <ARKit/object.h>
#import <ARKit/skeleton_joint.h>

#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL(ar_hand_skeleton)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

#pragma mark - Hand Skeleton Constants

API_AVAILABLE(visionos(1.0))
OS_ENUM(ar_hand_skeleton_joint_name, uint64_t,
    ar_hand_skeleton_joint_name_wrist = 0,
    ar_hand_skeleton_joint_name_thumb_knuckle = 1,
    ar_hand_skeleton_joint_name_thumb_intermediate_base = 2,
    ar_hand_skeleton_joint_name_thumb_intermediate_tip = 3,
    ar_hand_skeleton_joint_name_thumb_tip = 4,
    ar_hand_skeleton_joint_name_index_finger_metacarpal = 5,
    ar_hand_skeleton_joint_name_index_finger_knuckle = 6,
    ar_hand_skeleton_joint_name_index_finger_intermediate_base = 7,
    ar_hand_skeleton_joint_name_index_finger_intermediate_tip = 8,
    ar_hand_skeleton_joint_name_index_finger_tip = 9,
    ar_hand_skeleton_joint_name_middle_finger_metacarpal = 10,
    ar_hand_skeleton_joint_name_middle_finger_knuckle = 11,
    ar_hand_skeleton_joint_name_middle_finger_intermediate_base = 12,
    ar_hand_skeleton_joint_name_middle_finger_intermediate_tip = 13,
    ar_hand_skeleton_joint_name_middle_finger_tip = 14,
    ar_hand_skeleton_joint_name_ring_finger_metacarpal = 15,
    ar_hand_skeleton_joint_name_ring_finger_knuckle = 16,
    ar_hand_skeleton_joint_name_ring_finger_intermediate_base = 17,
    ar_hand_skeleton_joint_name_ring_finger_intermediate_tip = 18,
    ar_hand_skeleton_joint_name_ring_finger_tip = 19,
    ar_hand_skeleton_joint_name_little_finger_metacarpal = 20,
    ar_hand_skeleton_joint_name_little_finger_knuckle = 21,
    ar_hand_skeleton_joint_name_little_finger_intermediate_base = 22,
    ar_hand_skeleton_joint_name_little_finger_intermediate_tip = 23,
    ar_hand_skeleton_joint_name_little_finger_tip = 24,
    ar_hand_skeleton_joint_name_forearm_wrist = 25,
    ar_hand_skeleton_joint_name_forearm_arm = 26
) AR_REFINED_FOR_SWIFT;

#pragma mark - Hand Skeleton Functions

/**
 Create a hand skeleton in a neutral pose that allows access to constants like joint indices, names, counts, etc.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_hand_skeleton_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_hand_skeleton_t ar_hand_skeleton_create(void) AR_REFINED_FOR_SWIFT;

/**
 Returns a bool value that indicates whether the two hand skeletons are equal.

 @param hand_skeleton A hand skeleton to be compared.
 @param other_hand_skeleton The other hand skeleton to be compared to.

 @return YES if the hand skeletons are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_hand_skeleton_is_equal_to_hand_skeleton(ar_hand_skeleton_t _Nullable hand_skeleton,
                                                          ar_hand_skeleton_t _Nullable other_hand_skeleton) AR_REFINED_FOR_SWIFT;

/**
 Get a joint by it's name from the hand skeleton.

 @param hand_skeleton The hand skeleton.
 @param joint_name The joint index.

 @return An instance of `ar_skeleton_joint_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_skeleton_joint_t ar_hand_skeleton_get_joint_named(ar_hand_skeleton_t hand_skeleton,
                                                               ar_hand_skeleton_joint_name_t joint_name) AR_REFINED_FOR_SWIFT;

/**
 Get the total number of joints in the hand skeleton.

 @param hand_skeleton The hand skeleton.

 @return The number of joints.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN uint64_t ar_hand_skeleton_get_joint_count(ar_hand_skeleton_t hand_skeleton) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Enumerate the names of joints in an `ar_hand_skeleton_t` using an enumeration block.

 @param hand_skeleton The hand skeleton.
 @param joint_enumerator The enumerator block.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_hand_skeleton_enumerate_joints(ar_hand_skeleton_t hand_skeleton,
                                                 ar_skeleton_joint_enumerator_t joint_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Enumerate the joints in an `ar_hand_skeleton_t` using a function.

 @param hand_skeleton The hand skeleton.
 @param context The application-defined context parameter to pass to the function.
 @param joint_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_hand_skeleton_enumerate_joints_f(ar_hand_skeleton_t hand_skeleton,
                                                   void *_Nullable context,
                                                   ar_skeleton_joint_enumerator_function_t joint_enumerator_function) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // hand_skeleton_h
#else
#import <ARKitCore/hand_skeleton.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/hand_skeleton.h>)