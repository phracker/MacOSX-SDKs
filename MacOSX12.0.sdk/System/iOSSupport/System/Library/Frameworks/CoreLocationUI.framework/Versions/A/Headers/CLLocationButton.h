//
//  CLLocationButton.h
//  CoreLocationUI
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.
//

#if __has_include(<UIKit/UIControl.h>)

/*
 *  CLLocationButtonIcon
 *
 *  Discussion:
 *      Specifies the type of arrow icon on the button. Button must not be CLLocationButtonIconNone if CLLocationButtonLabel is CLLocationButtonLabelNone.
 *
 */
typedef NS_ENUM(NSInteger, CLLocationButtonIcon) {
	CLLocationButtonIconNone = 0,
	CLLocationButtonIconArrowFilled,
	CLLocationButtonIconArrowOutline,
};

/*
 *  CLLocationButtonLabel
 *
 *  Discussion:
 *      Specifies the text of the label on the button. Button must not be CLLocationButtonLabelNone if CLLocationButtonIcon is CLLocationButtonIconNone.
 *
 */
typedef NS_ENUM(NSInteger, CLLocationButtonLabel) {
	CLLocationButtonLabelNone = 0,
	CLLocationButtonLabelCurrentLocation,
	CLLocationButtonLabelSendCurrentLocation,
	CLLocationButtonLabelSendMyCurrentLocation,
	CLLocationButtonLabelShareCurrentLocation,
	CLLocationButtonLabelShareMyCurrentLocation,
};

/*
 *  CLLocationButton
 *
 *  Discussion:
 *    CLLocationButton is a UIControl that, in addition to functioning much like a UIButton, may grant a one-time authorization of the device's current location when pressed.
 */
API_AVAILABLE(ios(15.0),watchos(8.0))
@interface CLLocationButton : UIControl <NSSecureCoding>
@property (nonatomic, readwrite) CLLocationButtonIcon icon;
@property (nonatomic, readwrite) CLLocationButtonLabel label;
@property (nonatomic, readwrite) CGFloat fontSize;
@property (nonatomic, readwrite) CGFloat cornerRadius;
@end

#endif
