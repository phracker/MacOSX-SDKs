//
//  CLLocationButton.h
//  CoreLocationUI
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.
//

/*
 *  CLLocationButtonIcon
 *
 *  Discussion:
 *      Specifies the type of arrow icon on the button. Button must not be CLLocationButtonIconNone if CLLocationButtonLabel is CLLocationButtonLabelNone.
 *
 */

API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(visionos, watchos)
/// Constants that specify styles for the location arrow icon on the button.
typedef NS_ENUM(NSInteger, CLLocationButtonIcon) {
	
	/// A style that doesn't display an icon.
	///
	/// Use a different icon style if ``CLLocationButton/label`` is ``CLLocationButtonLabel/none``.
	CLLocationButtonIconNone = 0,
	
	/// A style that displays a filled arrow icon.
	CLLocationButtonIconArrowFilled,
	
	/// A style that displays an unfilled, outline arrow icon.
	CLLocationButtonIconArrowOutline,
};

/*
 *  CLLocationButtonLabel
 *
 *  Discussion:
 *      Specifies the text of the label on the button. Button must not be CLLocationButtonLabelNone if CLLocationButtonIcon is CLLocationButtonIconNone.
 *
 */

API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(visionos, watchos)
/// Constants that specify the text of the button label.
typedef NS_ENUM(NSInteger, CLLocationButtonLabel) {
	
	/// A style that doesn’t display a text label.
	///
	/// Use a different label style if ``CLLocationButton/icon`` is ``CLLocationButtonIcon/none``.
	CLLocationButtonLabelNone = 0,
	
	/// A button label with the text _Current Location_.
	CLLocationButtonLabelCurrentLocation,
	
	/// A button label with the text _Send Current Location_.
	CLLocationButtonLabelSendCurrentLocation,
	
	/// A button label with the text _Send My Current Location_.
	CLLocationButtonLabelSendMyCurrentLocation,
	
	/// A button label with the text _Share Current Location_.
	CLLocationButtonLabelShareCurrentLocation,
	
	/// A button label with the text _Share My Current Location_.
	CLLocationButtonLabelShareMyCurrentLocation,
};

API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(visionos, watchos)
/// A button that grants one-time location authorization.
///
/// `CLLocationButton` simplifies requesting one-time authorization to access
/// location data. Add this button to your user interface in situations when
/// users may want to grant temporary access to their location data each time
/// they use a particular feature of your app.
///
/// ![Screenshot of the location button with an icon that uses the filled arrow
/// style and a label that shows Current Location.](cllocationbutton-1)
///
/// The first time a user taps this button,
/// <doc://com.apple.documentation/documentation/corelocation> asks the user to
/// confirm that they’re comfortable using this UI element when they want to
/// grant temporary access to their location data. If the user agrees, the app
/// receives temporary
/// <doc://com.apple.documentation/documentation/corelocation/clauthorizationstatus/authorizedwheninuse>
/// authorization, like when the user chooses _Allow Once_ in response to your
/// app’s standard location authorization request. This temporary authorization
/// expires when your app is no longer in use.
///
/// After the user agrees to using `CLLocationButton`, the button becomes
/// approved to request future authorizations without displaying an additional
/// alert to the user. The next time the user taps it, this button simply grants
/// one-time authorization without requiring confirmation.
///
/// After you receive this temporary authorization, fetch the user's location
/// using the <doc://com.apple.documentation/documentation/corelocation> API and
/// perform any app-specific tasks related to that location data. Connect the
/// button to initiate the tasks you want to perform after getting authorization
/// by adding a target and action to the button. Keep in mind that this action
/// activates every time the user taps this button, regardless of whether the
/// app already has location authorization.
///
/// Create a `CLLocationButton` in Interface Builder or in code, like this:
///
/// ```swift
/// let locationButton = CLLocationButton()
/// locationButton.icon = .arrowFilled
/// locationButton.label = .currentLocation
/// locationButton.cornerRadius = 25.0
/// locationButton.addTarget(self, action: #selector(userPressedLocationButton), for: .touchUpInside)
/// ```
///
/// - Important: When a user taps the button, it only provides one-time
/// authorization to fetch location data — not the location data itself. For
/// more details about fetching location data, see
/// <doc://com.apple.documentation/documentation/corelocation/configuring_your_app_to_use_location_services>.
///
/// Configure the button's content by specifying its ``CLLocationButton/icon``
/// and ``CLLocationButton/label`` styles. Customize its appearance using the
/// ``CLLocationButton/cornerRadius`` and ``CLLocationButton/fontSize``
/// properties, or the standard view appearance properties
/// <doc://com.apple.documentation/documentation/uikit/uiview/1622591-backgroundcolor>
/// and
/// <doc://com.apple.documentation/documentation/uikit/uiview/1622467-tintcolor>.
/// For design guidance, see [Human Interface
/// Guidelines](https://developer.apple.com/design/human-interface-guidelines/ios/app-architecture/accessing-user-data/).
@interface CLLocationButton : UIControl <NSSecureCoding>

/// The style of the location arrow icon on the button.
@property (nonatomic, readwrite) CLLocationButtonIcon icon;

/// The text of the button label.
@property (nonatomic, readwrite) CLLocationButtonLabel label;

/// The font size of the text on the button.
@property (nonatomic, readwrite) CGFloat fontSize;

/// The corner radius of the button.
@property (nonatomic, readwrite) CGFloat cornerRadius;
@end
