//
//  LCCDefines.h
//  LockedCameraCapture
//
//  Created by Can Aran on 4/29/24.
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/// A type to use when opening your app from the capture extension.
///
/// Use this `NSUserActivityType` with <doc:LockedCameraCapture/LockedCameraCaptureSession/openApplication(for:)>
/// to check if someone is launching your app from a locked camera capture extension.
extern NSString * const NSUserActivityTypeLockedCameraCapture;
