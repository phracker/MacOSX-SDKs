//
//  PKContentVersion.h
//  PencilKit
//
//  Copyright © 2023 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>


/// A version specifying which PencilKit features are used/allowed.
API_AVAILABLE(ios(17.0), macos(14.0))
NS_SWIFT_SENDABLE
typedef NS_ENUM(NSInteger, PKContentVersion) {
    /// Version for inks introduced in iOS 14.0.
    ///
    /// Inks included are Pen, Pencil, and Marker.
    PKContentVersion1 NS_SWIFT_NAME(version1) = 1,
    /// Version for inks introduced in iOS 17.0.
    ///
    /// Inks included are Pen, Pencil, Marker, Monoline, Fountain Pen, Watercolor, and Crayon.
    PKContentVersion2 NS_SWIFT_NAME(version2),
    
    /// New Fountain Pen
    PKContentVersion3 NS_SWIFT_NAME(version3) API_AVAILABLE(ios(17.5), macos(14.5)),
    
    /// New Reed Pen
    PKContentVersion4 NS_SWIFT_NAME(version4) API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)),

    /// The latest version including all features.
    PKContentVersionLatest = 4
};
