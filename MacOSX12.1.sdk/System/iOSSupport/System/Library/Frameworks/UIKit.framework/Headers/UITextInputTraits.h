#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextInputTraits.h>)
//
//  UITextInputTraits.h
//  UIKit
//
//  Copyright (c) 2006-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

//
// UITextAutocapitalizationType
//
// Controls autocapitalization behavior for a text widget.
// Note: Capitalization does not apply in all script systems. In such
// cases, these values are ignored by the keyboard/input method implementation.
//
typedef NS_ENUM(NSInteger, UITextAutocapitalizationType) {
    UITextAutocapitalizationTypeNone,
    UITextAutocapitalizationTypeWords,
    UITextAutocapitalizationTypeSentences,
    UITextAutocapitalizationTypeAllCharacters,
};

//
// UITextAutocorrectionType
//
// Controls keyboard autocorrection behavior for a text widget.
// Note: Some input methods do not support inline autocorrection, and 
// instead use a conversion and/or candidate selection methodology. In such
// cases, these values are ignored by the keyboard/input method implementation.
//
typedef NS_ENUM(NSInteger, UITextAutocorrectionType) {
    UITextAutocorrectionTypeDefault,
    UITextAutocorrectionTypeNo,
    UITextAutocorrectionTypeYes,
};

//
// UITextSpellCheckingType
//
// Controls the annotation of misspelled words for a text widget.
// Note: Some input methods do not support spell checking.
typedef NS_ENUM(NSInteger, UITextSpellCheckingType) {
    UITextSpellCheckingTypeDefault,
    UITextSpellCheckingTypeNo,
    UITextSpellCheckingTypeYes,
} API_AVAILABLE(ios(5.0));

//
// UITextSmartQuotesType
//
// Controls the automatic conversion of typographic quote characters for a text widget.
typedef NS_ENUM(NSInteger, UITextSmartQuotesType) {
    UITextSmartQuotesTypeDefault,
    UITextSmartQuotesTypeNo,
    UITextSmartQuotesTypeYes,
} API_AVAILABLE(ios(11.0));

//
// UITextSmartDashesType
//
// Controls the automatic conversion of hyphens into en/em-dashes for a text widget.
typedef NS_ENUM(NSInteger, UITextSmartDashesType) {
    UITextSmartDashesTypeDefault,
    UITextSmartDashesTypeNo,
    UITextSmartDashesTypeYes,
} API_AVAILABLE(ios(11.0));

//
// UITextSmartInsertDeleteType
//
// Controls the automatic insertion/removal of spaces for a text widget.
typedef NS_ENUM(NSInteger, UITextSmartInsertDeleteType) {
    UITextSmartInsertDeleteTypeDefault,
    UITextSmartInsertDeleteTypeNo,
    UITextSmartInsertDeleteTypeYes,
} API_AVAILABLE(ios(11.0));

//
// UIKeyboardType
//
// Requests that a particular keyboard type be displayed when a text widget
// becomes first responder. 
// Note: Some keyboard/input methods types may not support every variant. 
// In such cases, the input method will make a best effort to find a close 
// match to the requested type (e.g. displaying UIKeyboardTypeNumbersAndPunctuation 
// type if UIKeyboardTypeNumberPad is not supported).
//
typedef NS_ENUM(NSInteger, UIKeyboardType) {
    UIKeyboardTypeDefault,                // Default type for the current input method.
    UIKeyboardTypeASCIICapable,           // Displays a keyboard which can enter ASCII characters
    UIKeyboardTypeNumbersAndPunctuation,  // Numbers and assorted punctuation.
    UIKeyboardTypeURL,                    // A type optimized for URL entry (shows . / .com prominently).
    UIKeyboardTypeNumberPad,              // A number pad with locale-appropriate digits (0-9, ۰-۹, ०-९, etc.). Suitable for PIN entry.
    UIKeyboardTypePhonePad,               // A phone pad (1-9, *, 0, #, with letters under the numbers).
    UIKeyboardTypeNamePhonePad,           // A type optimized for entering a person's name or phone number.
    UIKeyboardTypeEmailAddress,           // A type optimized for multiple email address entry (shows space @ . prominently).
    UIKeyboardTypeDecimalPad API_AVAILABLE(ios(4.1)),   // A number pad with a decimal point.
    UIKeyboardTypeTwitter API_AVAILABLE(ios(5.0)),      // A type optimized for twitter text entry (easy access to @ #)
    UIKeyboardTypeWebSearch API_AVAILABLE(ios(7.0)),    // A default keyboard type with URL-oriented addition (shows space . prominently).
    UIKeyboardTypeASCIICapableNumberPad API_AVAILABLE(ios(10.0)), // A number pad (0-9) that will always be ASCII digits.

    UIKeyboardTypeAlphabet = UIKeyboardTypeASCIICapable, // Deprecated

};

//
// UIKeyboardAppearance
//
// Requests a keyboard appearance be used when a text widget
// becomes first responder.. 
// Note: Some keyboard/input methods types may not support every variant. 
// In such cases, the input method will make a best effort to find a close 
// match to the requested type.
//
typedef NS_ENUM(NSInteger, UIKeyboardAppearance) {
    UIKeyboardAppearanceDefault,          // Default appearance for the current input method.
    UIKeyboardAppearanceDark API_AVAILABLE(ios(7.0)),
    UIKeyboardAppearanceLight API_AVAILABLE(ios(7.0)),
    UIKeyboardAppearanceAlert = UIKeyboardAppearanceDark,  // Deprecated
};

//
// UIReturnKeyType
//
// Controls the display of the return key. 
//
// Note: This enum is under discussion and may be replaced with a 
// different implementation.
//
typedef NS_ENUM(NSInteger, UIReturnKeyType) {
    UIReturnKeyDefault,
    UIReturnKeyGo,
    UIReturnKeyGoogle,
    UIReturnKeyJoin,
    UIReturnKeyNext,
    UIReturnKeyRoute,
    UIReturnKeySearch,
    UIReturnKeySend,
    UIReturnKeyYahoo,
    UIReturnKeyDone,
    UIReturnKeyEmergencyCall,
    UIReturnKeyContinue API_AVAILABLE(ios(9.0)),
};

typedef NSString * UITextContentType NS_TYPED_ENUM;

UIKIT_EXTERN API_AVAILABLE(ios(12.0)) NS_SWIFT_UI_ACTOR
@interface UITextInputPasswordRules : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic,readonly) NSString *passwordRulesDescriptor;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
+ (instancetype)passwordRulesWithDescriptor:(NSString *)passwordRulesDescriptor;

@end

//
// UITextInputTraits
//
// Controls features of text widgets (or other custom objects that might wish 
// to respond to keyboard input).
//
NS_SWIFT_UI_ACTOR
@protocol UITextInputTraits <NSObject>

@optional

@property(nonatomic) UITextAutocapitalizationType autocapitalizationType; // default is UITextAutocapitalizationTypeSentences
@property(nonatomic) UITextAutocorrectionType autocorrectionType;         // default is UITextAutocorrectionTypeDefault
@property(nonatomic) UITextSpellCheckingType spellCheckingType API_AVAILABLE(ios(5.0)); // default is UITextSpellCheckingTypeDefault;
@property(nonatomic) UITextSmartQuotesType smartQuotesType API_AVAILABLE(ios(11.0)); // default is UITextSmartQuotesTypeDefault;
@property(nonatomic) UITextSmartDashesType smartDashesType API_AVAILABLE(ios(11.0)); // default is UITextSmartDashesTypeDefault;
@property(nonatomic) UITextSmartInsertDeleteType smartInsertDeleteType API_AVAILABLE(ios(11.0)); // default is UITextSmartInsertDeleteTypeDefault;
@property(nonatomic) UIKeyboardType keyboardType;                         // default is UIKeyboardTypeDefault
@property(nonatomic) UIKeyboardAppearance keyboardAppearance;             // default is UIKeyboardAppearanceDefault
@property(nonatomic) UIReturnKeyType returnKeyType;                       // default is UIReturnKeyDefault (See note under UIReturnKeyType enum)
@property(nonatomic) BOOL enablesReturnKeyAutomatically;                  // default is NO (when YES, will automatically disable return key when text widget has zero-length contents, and will automatically enable when text widget has non-zero-length contents)
@property(nonatomic,getter=isSecureTextEntry) BOOL secureTextEntry;       // default is NO

// The textContentType property is to provide the keyboard with extra information about the semantic intent of the text document.
@property(null_unspecified,nonatomic,copy) UITextContentType textContentType API_AVAILABLE(ios(10.0)); // default is nil

// The passwordRules property is used to communicate requirements for passwords for your service
// to ensure iOS can generate compatible passwords for users. It only works when secureTextEntry
// is YES. You do not need to use this property if the passwords that iOS generates are already
// compatible with your service. You can learn more about the purpose of and syntax for these rules
// on the Password Rules documentation guide.
@property(nullable,nonatomic,copy) UITextInputPasswordRules *passwordRules API_AVAILABLE(ios(12.0)); // default is nil

@end


UIKIT_EXTERN UITextContentType const UITextContentTypeName                      API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeNamePrefix                API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeGivenName                 API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeMiddleName                API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeFamilyName                API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeNameSuffix                API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeNickname                  API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeJobTitle                  API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeOrganizationName          API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeLocation                  API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeFullStreetAddress         API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeStreetAddressLine1        API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeStreetAddressLine2        API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeAddressCity               API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeAddressState              API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeAddressCityAndState       API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeSublocality               API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeCountryName               API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypePostalCode                API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeTelephoneNumber           API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeEmailAddress              API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeURL                       API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeCreditCardNumber          API_AVAILABLE(ios(10.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeUsername                  API_AVAILABLE(ios(11.0));
UIKIT_EXTERN UITextContentType const UITextContentTypePassword                  API_AVAILABLE(ios(11.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeNewPassword               API_AVAILABLE(ios(12.0));
UIKIT_EXTERN UITextContentType const UITextContentTypeOneTimeCode               API_AVAILABLE(ios(12.0));

/// Parcel tracking numbers such as "FedEx 8602 9191 3550", "1Z50T0536891664106", and "729445720428778".
UIKIT_EXTERN UITextContentType const UITextContentTypeShipmentTrackingNumber    API_AVAILABLE(ios(15.0));

/// Airline flight numbers such as "CZ # 1234", "AA212", and "SW Flight 573".
UIKIT_EXTERN UITextContentType const UITextContentTypeFlightNumber              API_AVAILABLE(ios(15.0));

/// Dates, times, or durations such as "7-3-2021" or "This Saturday", "12:30", and "10-11am", respectively.
UIKIT_EXTERN UITextContentType const UITextContentTypeDateTime                  API_AVAILABLE(ios(15.0));

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITextInputTraits.h>
#endif
