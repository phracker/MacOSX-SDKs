//  
//  GCGearShifterElement.h
//  GameController
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <GameController/GCPhysicalInputElement.h>
#import <GameController/GCSwitchPositionInput.h>
#import <GameController/GCRelativeInput.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A \c GCGearShifterElement object represents an attached gear shifter.  Both
 pattern and sequential gear shifters are supported.
 */
API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos)
@interface GCGearShifterElement : NSObject <GCPhysicalInputElement>

/**
 Get the input reporting the position of the pattern gear shifter.  If this
 property is \c nil, the gear shifter is not a pattern gear shifter.
 
 In the returned input, a position of \c -1 corresponds to the "reverse gear".
 A position of \c 0 corresponds to the neutral gear.
 */
@property (readonly, nullable) id<GCSwitchPositionInput> patternInput;

/**
 Get the input reporting changes to the sequential gear shifter.  If this
 property is \c nil, the gear shifter is not a sequential gear shifter.
 */
@property (readonly, nullable) id<GCRelativeInput> sequentialInput;

@end

NS_ASSUME_NONNULL_END
