//
//  CLKComplication.h
//  ClockKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClockKit/CLKDefines.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKComplication : NSObject <NSCopying>

/// The family of this complication.
@property (nonatomic, readonly) CLKComplicationFamily family;

/// The identifier of this complication.
@property (nonatomic, readonly) NSString *identifier API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

/// An optional dictionary, defined in this complication's CLKComplicationDescriptor.
@property (nonatomic, readonly, nullable) NSDictionary *userInfo API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

/// An optional user activity, defined in this complication's CLKComplicationDescriptor.
@property (nonatomic, readonly, nullable) NSUserActivity *userActivity API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);
@end

NS_ASSUME_NONNULL_END
