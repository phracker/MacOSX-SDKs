//
//  CLKComplicationWidgetMigrationConfiguration.h
//  ClockKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Common class for different kinds of mappings to Widget configurations.
API_AVAILABLE(watchos(9.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationWidgetMigrationConfiguration : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
