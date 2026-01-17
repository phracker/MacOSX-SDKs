#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIActivityIndicatorView.h>)
//
//  UIActivityIndicatorView.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIActivityIndicatorViewStyle) {
    UIActivityIndicatorViewStyleMedium  API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) = 100,
    UIActivityIndicatorViewStyleLarge   API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) = 101,
    
    UIActivityIndicatorViewStyleWhiteLarge API_DEPRECATED_WITH_REPLACEMENT("UIActivityIndicatorViewStyleLarge", ios(2.0, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos, watchos) = 0,
    UIActivityIndicatorViewStyleWhite API_DEPRECATED_WITH_REPLACEMENT("UIActivityIndicatorViewStyleMedium", ios(2.0, 13.0), tvos(9.0, 13.0)) API_UNAVAILABLE(visionos, watchos) = 1,
    UIActivityIndicatorViewStyleGray API_DEPRECATED_WITH_REPLACEMENT("UIActivityIndicatorViewStyleMedium", ios(2.0, 13.0)) API_UNAVAILABLE(tvos, visionos, watchos) = 2,
} API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIActivityIndicatorView : UIView <NSCoding>

- (instancetype)initWithActivityIndicatorStyle:(UIActivityIndicatorViewStyle)style NS_DESIGNATED_INITIALIZER; // sizes the view according to the style
- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
   
@property(nonatomic) UIActivityIndicatorViewStyle activityIndicatorViewStyle; // default is UIActivityIndicatorViewStyleMedium
@property(nonatomic) BOOL                         hidesWhenStopped;           // default is YES. calls -setHidden when animating gets set to NO

@property (null_resettable, readwrite, nonatomic, strong) UIColor *color API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

- (void)startAnimating;
- (void)stopAnimating;
@property(nonatomic, readonly, getter=isAnimating) BOOL animating;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIActivityIndicatorView.h>
#endif
