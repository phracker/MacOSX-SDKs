//
//  BETextAlternatives.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>

NS_ASSUME_NONNULL_BEGIN

@class NSArray;
@class NSString;

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@interface BETextAlternatives : NSObject

/**
 *  Original text for which alternative strings are provided
 */
@property (readonly) NSString *primaryString;

/**
 *  Array of available aternative strings
 */
@property (readonly) NSArray<NSString *> *alternativeStrings;

- (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
