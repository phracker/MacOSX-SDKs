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

API_AVAILABLE(ios(11.0), tvos(11.0), macos(11.0)) API_UNAVAILABLE(watchos)
@interface MKMarkerAnnotationView : MKAnnotationView

@property (nonatomic) MKFeatureVisibility titleVisibility;
@property (nonatomic) MKFeatureVisibility subtitleVisibility;

#if TARGET_OS_IPHONE
@property (nonatomic, copy, nullable) UIColor *markerTintColor UI_APPEARANCE_SELECTOR;

@property (nonatomic, copy, nullable) UIColor *glyphTintColor UI_APPEARANCE_SELECTOR;
@property (nonatomic, copy, nullable) NSString *glyphText UI_APPEARANCE_SELECTOR;
@property (nonatomic, copy, nullable) UIImage *glyphImage UI_APPEARANCE_SELECTOR;
@property (nonatomic, copy, nullable) UIImage *selectedGlyphImage UI_APPEARANCE_SELECTOR;
#else
@property (nonatomic, copy, nullable) NSColor *markerTintColor;

@property (nonatomic, copy, nullable) NSColor *glyphTintColor;
@property (nonatomic, copy, nullable) NSString *glyphText;
@property (nonatomic, copy, nullable) NSImage *glyphImage;
@property (nonatomic, copy, nullable) NSImage *selectedGlyphImage;
#endif

@property (nonatomic) BOOL animatesWhenAdded;

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
