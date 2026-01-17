//
//  CLKComplicationIntentWidgetMigrationConfiguration.h
//  ClockKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <ClockKit/CLKComplicationWidgetMigrationConfiguration.h>

@class INIntent;

NS_ASSUME_NONNULL_BEGIN

/// Holds data that maps to a Widget specified by an `IntentConfiguration` in a specific extension.
API_AVAILABLE(watchos(9.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationIntentWidgetMigrationConfiguration : CLKComplicationWidgetMigrationConfiguration

// The kind specified in the `WidgetConfiguration`
@property(nonatomic, readonly, copy) NSString *kind;

// The extension that the `WidgetConfiguration` is specified in
@property(nonatomic, readonly, copy) NSString *extensionBundleIdentifier;

// The configured intent that is the same type as specified in the `WidgetConfiguration`
@property(nonatomic, readonly, copy) INIntent *intent;

// The name used for the complication during editing
@property(nonatomic, readonly, copy) NSString *localizedDisplayName;

- (instancetype)initWithKind:(NSString *)kind
   extensionBundleIdentifier:(NSString *)extensionBundleIdentifier
                      intent:(INIntent *)intent
        localizedDisplayName:(NSString *)localizedDisplayName;
+ (instancetype)intentWidgetMigrationConfigurationWithKind:(NSString *)kind
                                 extensionBundleIdentifier:(NSString *)extensionBundleIdentifier
                                                    intent:(INIntent *)intent
                                      localizedDisplayName:(NSString *)localizedDisplayName;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
