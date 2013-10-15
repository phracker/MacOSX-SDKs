//
//  MKPinAnnotationView.h
//  MapKit
//
//  Copyright (c) 2009-2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotationView.h>

typedef NS_ENUM(NSUInteger, MKPinAnnotationColor) {
    MKPinAnnotationColorRed = 0,
    MKPinAnnotationColorGreen,
    MKPinAnnotationColorPurple
} NS_ENUM_AVAILABLE(10_9, 3_0);

MK_CLASS_AVAILABLE(10_9, 3_0)
@interface MKPinAnnotationView : MKAnnotationView

@property (nonatomic) MKPinAnnotationColor pinColor;

@property (nonatomic) BOOL animatesDrop;

@end
