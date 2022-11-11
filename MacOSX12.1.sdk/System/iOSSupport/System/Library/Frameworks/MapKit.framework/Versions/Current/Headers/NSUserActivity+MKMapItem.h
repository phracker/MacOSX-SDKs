//
//  NSUserActivity+MKMapItem.h
//  MapKit
//
//  Copyright (c) 2009-2016, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MKMapItem;

@interface NSUserActivity (MKMapItem)

@property (nonatomic, strong) MKMapItem *mapItem NS_AVAILABLE(10_12, 10_0) __TVOS_AVAILABLE(10_0) __WATCHOS_AVAILABLE(3_0);

@end
