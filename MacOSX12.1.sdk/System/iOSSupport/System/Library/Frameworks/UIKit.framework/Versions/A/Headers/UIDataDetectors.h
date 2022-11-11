#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDataDetectors.h>)
//
//  UIDataDetectors.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_OPTIONS(NSUInteger, UIDataDetectorTypes) {
    UIDataDetectorTypePhoneNumber                                        = 1 << 0, // Phone number detection
    UIDataDetectorTypeLink                                               = 1 << 1, // URL detection
    UIDataDetectorTypeAddress API_AVAILABLE(ios(4.0))                 = 1 << 2, // Street address detection
    UIDataDetectorTypeCalendarEvent API_AVAILABLE(ios(4.0))           = 1 << 3, // Event detection
    UIDataDetectorTypeShipmentTrackingNumber API_AVAILABLE(ios(10.0)) = 1 << 4, // Shipment tracking number detection
    UIDataDetectorTypeFlightNumber API_AVAILABLE(ios(10.0))           = 1 << 5, // Flight number detection
    UIDataDetectorTypeLookupSuggestion API_AVAILABLE(ios(10.0))       = 1 << 6, // Information users may want to look up

    UIDataDetectorTypeNone          = 0,               // Disable detection
    UIDataDetectorTypeAll           = NSUIntegerMax    // Enable all types, including types that may be added later
} API_UNAVAILABLE(tvos);

#else
#import <UIKitCore/UIDataDetectors.h>
#endif
