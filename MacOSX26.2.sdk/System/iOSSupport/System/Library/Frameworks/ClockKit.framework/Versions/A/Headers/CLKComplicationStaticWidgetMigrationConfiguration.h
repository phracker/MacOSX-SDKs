//
//  CLKComplicationStaticWidgetMigrationConfiguration.h
//  ClockKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <ClockKit/CLKComplicationWidgetMigrationConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/// Holds data that maps to a Widget specified by a `StaticConfiguration` in a specific extension.
API_AVAILABLE(watchos(9.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationStaticWidgetMigrationConfiguration : CLKComplicationWidgetMigrationConfiguration

// The kind specified in the `WidgetConfiguration`
@property(nonatomic, readonly, copy) NSString *kind;

// The extension that the `WidgetConfiguration` is specified in
@property(nonatomic, readonly, copy) NSString *extensionBundleIdentifier;

- (instancetype)initWithKind:(NSString *)kind
   extensionBundleIdentifier:(NSString *)extensionBundleIdentifier;
+ (instancetype)staticWidgetMigrationConfigurationWithKind:(NSString *)kind
                                 extensionBundleIdentifier:(NSString *)extensionBundleIdentifier;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
