//
//  MKMarkerAnnotationView.h
//  MapKit
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <MapKit/MKAnnotationView.h>
#import <MapKit/MKTypes.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(11_0) __TVOS_AVAILABLE(11_0) API_UNAVAILABLE(watchos)
@interface MKMarkerAnnotationView : MKAnnotationView

@property (nonatomic) MKFeatureVisibility titleVisibility;
@property (nonatomic) MKFeatureVisibility subtitleVisibility;

@property (nonatomic, copy, nullable) UIColor *markerTintColor UI_APPEARANCE_SELECTOR;

@property (nonatomic, copy, nullable) UIColor *glyphTintColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, copy, nullable) NSString *glyphText UI_APPEARANCE_SELECTOR;
@property (nonatomic, copy, nullable) UIImage *glyphImage UI_APPEARANCE_SELECTOR;
@property (nonatomic, copy, nullable) UIImage *selectedGlyphImage UI_APPEARANCE_SELECTOR;

@property (nonatomic) BOOL animatesWhenAdded;

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
