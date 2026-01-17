//
//  CLKComplicationWidgetMigrator.h
//  ClockKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLKComplicationDescriptor;
@class CLKComplicationWidgetMigrationConfiguration;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(watchos(9.0)) API_UNAVAILABLE(ios)
@protocol CLKComplicationWidgetMigrator <NSObject>

/// Provide a mapping from an existing configured `CLKComplicationDescriptor` to a Widget.
@optional
- (void)getWidgetConfigurationFrom:(CLKComplicationDescriptor *)complicationDescriptor
                 completionHandler:(void (^)(CLKComplicationWidgetMigrationConfiguration * _Nullable))completionHandler NS_SWIFT_ASYNC(2);

@end

NS_ASSUME_NONNULL_END
