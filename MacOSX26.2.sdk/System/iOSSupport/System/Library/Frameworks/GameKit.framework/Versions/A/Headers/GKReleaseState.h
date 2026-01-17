// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

/// Describes the release state of an App Store Connect resource, such as an Achievement or Leaderboard.
typedef NS_OPTIONS(NSUInteger, GKReleaseState) {
    /// The system can't determine the release state of the resource.
    GKReleaseStateUnknown,
    
    /// The resource is associated with a release in App Store Connect. This has no relationship with the "archived" state of a resource (i.e., A resource can be release _and_ archived).
    GKReleaseStateReleased,
    
    /// The resource has been created in App Store Connect but isn't yet associated with a released version of an App.
    GKReleaseStatePrereleased
} API_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4), visionos(2.4));

