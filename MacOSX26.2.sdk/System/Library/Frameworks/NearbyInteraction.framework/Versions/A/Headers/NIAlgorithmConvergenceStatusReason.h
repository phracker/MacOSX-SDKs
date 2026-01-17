//
//  NIAlgorithmConvergenceStatusReason.h
//  NearbyInteraction
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>

NS_ASSUME_NONNULL_BEGIN
/**
 Reasons for the convergence state.
 @discussion Multiple reasons may be present simultaenously.
 */
API_AVAILABLE_BEGIN(ios(16.0), watchos(9.0))

typedef NSString * NIAlgorithmConvergenceStatusReason NS_TYPED_ENUM NS_SWIFT_NAME(NIAlgorithmConvergenceStatus.Reason)
API_UNAVAILABLE(macos, tvos);

/** Tell user to sweep device horizontally from side to side. */
NI_EXPORT NIAlgorithmConvergenceStatusReason const NIAlgorithmConvergenceStatusReasonInsufficientHorizontalSweep
API_UNAVAILABLE(macos, tvos);

/** Tell user to sweep device verically up and down. */
NI_EXPORT NIAlgorithmConvergenceStatusReason const NIAlgorithmConvergenceStatusReasonInsufficientVerticalSweep
API_UNAVAILABLE(macos, tvos);

/** Tell user to move around. */
NI_EXPORT NIAlgorithmConvergenceStatusReason const NIAlgorithmConvergenceStatusReasonInsufficientMovement
API_UNAVAILABLE(macos, tvos);

/** Tell user to turn on the light. */
NI_EXPORT NIAlgorithmConvergenceStatusReason const NIAlgorithmConvergenceStatusReasonInsufficientLighting
API_UNAVAILABLE(macos, tvos);

__BEGIN_DECLS
/** Helper methods for getting the localized description of the convergence reason*/
NI_EXPORT
NSString * NIAlgorithmConvergenceStatusReasonDescription(const NIAlgorithmConvergenceStatusReason reason)
NS_SWIFT_UNAVAILABLE("Use NIAlgorithmConvergenceStatus.Reason.localizedDescription")
API_UNAVAILABLE(macos, tvos);
__END_DECLS

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
