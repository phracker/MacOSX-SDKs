//
//  SRKeyboardMetrics.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRKeyboardMetrics : NSObject

/// The duration over which these metrics were calculated
@property (readonly) NSTimeInterval duration;

/// The identifier of the keyboard in the keyboard list
@property (readonly, copy) NSString *keyboardIdentifier;

/// The version of keyboard metrics
@property (readonly, copy) NSString *version;

/// The width of the keyboard in mm in the session
@property (readonly) NSMeasurement<NSUnitLength*> *width;

/// The height of the keyboard in mm in the session
@property (readonly) NSMeasurement<NSUnitLength*> *height;

@end

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRKeyboardMetrics (ScalarMetrics)

/// The total number of words typed during the session
@property (readonly) NSInteger totalWords;

/// The total number of altered words during the session
@property (readonly) NSInteger totalAlteredWords;

/// The total number of taps during the session
@property (readonly) NSInteger totalTaps;

/// The total number of drags during the session
@property (readonly) NSInteger totalDrags;

/// The total number of deletes during the session
@property (readonly) NSInteger totalDeletes;

/// The total number of emojis used during the session
@property (readonly) NSInteger totalEmojis;

/// The total number of paths used during the sesion
@property (readonly) NSInteger totalPaths;

/// The total time taken to complete paths in the session
@property (readonly) NSTimeInterval totalPathTime;

/// The total length of paths completed in the session
@property (readonly) NSMeasurement<NSUnitLength *> *totalPathLength;

/// The total number of autocorrections in the session
@property (readonly) NSInteger totalAutoCorrections;

/// The total number of space corrections in the session
@property (readonly) NSInteger totalSpaceCorrections;

/// The total number of retro corrections in the session
@property (readonly) NSInteger totalRetroCorrections;

/// The total number of transposition corrections in the session
@property (readonly) NSInteger totalTranspositionCorrections;

/// The total number of insert key corrections in the session
@property (readonly) NSInteger totalInsertKeyCorrections;

/// The total number of skip touch corrections in the session
@property (readonly) NSInteger totalSkipTouchCorrections;

/// The total number of near key corrections in the session
@property (readonly) NSInteger totalNearKeyCorrections;

/// The total number of substitution corrections in the session
@property (readonly) NSInteger totalSubstitutionCorrections;

/// The total number of hit test corrections in the session
@property (readonly) NSInteger totalHitTestCorrections;

/// The total amount of time typing during the session
@property (readonly) NSTimeInterval totalTypingDuration;

@end

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRKeyboardProbabilityMetric <UnitType : __kindof NSUnit *> : NSObject

/// Sample values from probability distribution
@property (readonly, copy) NSArray<NSMeasurement<UnitType> *> *distributionSampleValues;

@end

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRKeyboardMetrics (ProbabilityMetrics)

/// The distance from the touch up to the center of any key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitLength *> *upErrorDistance;

/// The distance from the touch down to the center of any key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitLength *> *downErrorDistance;

/// The distance from the touch up to the right centroid of the space key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitLength *> *spaceUpErrorDistance;

/// The distance from the touch down to the right centroid of the space key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitLength *> *spaceDownErrorDistance;

/// The distance from the touch up to the center of the delete key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitLength *> *deleteUpErrorDistance;

/// The distance from the touch down to the center of the delete key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitLength *> *deleteDownErrorDistance;

/// The distance from the touch up to the center of the intended key of a character in a short word
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitLength *> *shortWordCharKeyUpErrorDistance;

/// The distance from the touch down to the center of the intended key of a character in a short word
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitLength *> *shortWordCharKeyDownErrorDistance;

/// The duration between touch down to touchup for any key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *touchDownUp;

/// The duration between touch down and touchup of all space key events in the session.
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *spaceTouchDownUp;

/// The duration between touch down and touchup of all delete key events in the session.
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *deleteTouchDownUp;

/// The duration between touch down and touchup of all character keys in short words in the session.
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *shortWordCharKeyTouchDownUp;

/// The duration between touch down to touch down for any key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *touchDownDown;

/// The duration between touchup on a character key and touch down on a word in the prediction bar
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *charKeyToPrediction;

/// The duration between touchup on a character key and touch down on any sequential character key in a short word
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *shortWordCharKeyToCharKey;

/// The duration between touchup on a character key and touch down on the next sequential key (any key)
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *charKeyToAnyTapKey;

/// The duration between touchup of any key and touch down on a sequential character key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *anyTapToCharKey;

/// The duration between touchup of a space key and touch down of a sequential character key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *spaceToCharKey;

/// The duration between touchup of a character key and touch down of a sequential space key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *charKeyToSpaceKey;

/// The duration between touchup of a space key and touch down of a sequential delete key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *spaceToDeleteKey;

/// The duration between touchup of a delete key and touch down of a sequential space key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *deleteToSpaceKey;

/// The duration between touchup of a space key and touch down of a sequential space key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *spaceToSpaceKey;

/// The duration between touchup of a space key and touch down of a sequential Shift key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *spaceToShiftKey;

/// The duration between touchup of a space key and touch down of a sequential plane change key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *spaceToPlaneChangeKey;

/// The duration between touchup on the space key and touch down of a sequential selection from the prediction bar
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *spaceToPredictionKey;

/// The duration between touchup of a delete key and touch down of a sequential character key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *deleteToCharKey;

/// The duration between touchup of a character key and touch down of a sequential delete key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *charKeyToDelete;

/// The duration between touchup of a delete key and touch down of a sequential delete key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *deleteToDelete;

/// The duration between touchup of a delete key and touch down of a sequential Shift key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *deleteToShiftKey;

/// The duration between touchup of a delete key and touch down of a sequential plane change key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *deleteToPlaneChangeKey;

/// The duration between touchup of any key and touch down on a plane change key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *anyTapToPlaneChangeKey;

/// The duration between touchup on a plane change key and touch down on the next sequential key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *planeChangeToAnyTap;

/// The duration between touchup of a character key and touch down of a sequential plane change key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *charKeyToPlaneChangeKey;

/// The duration between touchup of a plane change key and touch down of any key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *planeChangeKeyToCharKey;

/// sample values of the ratio of error distance between intended and actual path
@property (readonly, strong) NSArray<NSNumber *> *pathErrorDistanceRatio;

/// The duration between touchup of a delete key and touch down of a sequential path
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *deleteToPath;

/// The duration between touchup of a delete key and touch down of a sequential path (ie. Continuous Path)
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *pathToDelete;

/// The duration between touchup on the space key and touch down to begin a sequential path
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *spaceToPath;

/// The duration between touchup of a path and touch down of a sequential space key
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *pathToSpace;

/// The duration between touchup of a path and touch down of a sequential path
@property (readonly, strong) SRKeyboardProbabilityMetric<NSUnitDuration *> *pathToPath;

@end

/// Probability metrics for each character in a word in their respective positions (first, second, third, fourth, fifth, and the rest)
SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRKeyboardMetrics (PositionalMetrics)

/// The distance from the touch up to the center of the intended key of the characters of a long word
@property (readonly, strong) NSArray<SRKeyboardProbabilityMetric<NSUnitLength *> *> *longWordUpErrorDistance;

/// The distance from the touch down to the center of the intended key of the characters of a long word
@property (readonly, strong) NSArray<SRKeyboardProbabilityMetric<NSUnitLength *> *> *longWordDownErrorDistance;

/// The duration between touch down and touchup of the character keys of all the long words in the session.
@property (readonly, strong) NSArray<SRKeyboardProbabilityMetric<NSUnitDuration *> *> *longWordTouchDownUp;

/// The duration between touch down and touch down of the character keys of all the long words in the session.
@property (readonly, strong) NSArray<SRKeyboardProbabilityMetric<NSUnitDuration *> *> *longWordTouchDownDown;

/// The duration between touchup of the delete key and touch down of a sequential delete key
@property (readonly, strong) NSArray<SRKeyboardProbabilityMetric<NSUnitDuration *> *> *deleteToDeletes;

@end

NS_ASSUME_NONNULL_END
