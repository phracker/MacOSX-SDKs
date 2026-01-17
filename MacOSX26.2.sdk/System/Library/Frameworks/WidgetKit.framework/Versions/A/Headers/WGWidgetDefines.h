//
//  WKWidgetDefines.h
//  WidgetKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/// A key you use to access the widget's kind. The value matches the `kind` property specified in the widget’s configuration.
extern NSString * const WGWidgetUserInfoKeyKind NS_REFINED_FOR_SWIFT;

/// A key you use to access the widget's family.
extern NSString * const WGWidgetUserInfoKeyFamily NS_REFINED_FOR_SWIFT;

///A key you use to access the activity ID if the widget represents a Live Activity.
extern NSString * const WGWidgetUserInfoKeyActivityID NS_REFINED_FOR_SWIFT;

/// A string that the system passes to the app on launch from a Live Activity that doesn't provide
/// a URL.
///
/// In many cases, you use  <doc://com.apple.documentation/documentation/swiftui/view/widgeturl(_:)>
/// to allow users to tap a Live Activity and open a screen in the app with functionality that best fits the
/// Live Activity. If you don't use the `widgetURL(_:)` modifier to provide a URL, the system launches
/// your app and passes `NSUserActivityTypeLiveActivity` as the <doc://com.apple.documentation/documentation/foundation/nsuseractivity/1409611-activitytype>
/// of <doc://com.apple.documentation/documentation/foundation/nsuseractivity>
/// upon launch. Check for this value on launch to open a screen in your app that fits the context of the
/// active Live Activity.
extern NSString * const NSUserActivityTypeLiveActivity;
