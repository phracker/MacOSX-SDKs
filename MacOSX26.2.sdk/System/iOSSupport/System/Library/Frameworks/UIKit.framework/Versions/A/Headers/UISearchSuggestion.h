#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISearchSuggestion.h>)
//
//  UISearchSuggestion.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage;

UIKIT_CLASS_AVAILABLE_IOS_TVOS(16.0, 14.0) NS_SWIFT_UI_ACTOR
@protocol UISearchSuggestion <NSObject>

/// The localized suggestion that will be displayed as the search string
@property (nonatomic, readonly, nullable) NSString *localizedSuggestion;

@optional
/// The localized description used as accessibility string
@property (nonatomic, readonly, nullable) NSString *localizedDescription;

/// Icon that represents this search suggestion item
@property (nonatomic, readonly, nullable) UIImage *iconImage;

@required

/// If non-null, will be displayed as the search string instead of localizedSuggestion
@property (nonatomic, readonly, nullable) NSAttributedString *localizedAttributedSuggestion API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/// User information
@property (strong, nullable, nonatomic) id representedObject API_AVAILABLE(ios(16.0), tvos(16.0));
@end

/// A concrete container for search suggestion string and optional image and associated information for providing shortcuts in search experience on tvOS.
UIKIT_CLASS_AVAILABLE_IOS_TVOS(16.0, 14.0) NS_SWIFT_UI_ACTOR
@interface UISearchSuggestionItem : NSObject <UISearchSuggestion>

/// Returns a new search suggestion object with a specified suggestion string.
+ (instancetype)suggestionWithLocalizedSuggestion:(NSString *)suggestion NS_SWIFT_UNAVAILABLE("Use init(string suggestionString: String) instead.");

/// Returns a new search suggestion object with a specified suggestion string and a description string.
+ (instancetype)suggestionWithLocalizedSuggestion:(NSString *)suggestion descriptionString:(nullable NSString *)description NS_SWIFT_UNAVAILABLE("Use init(string suggestionString: String, descriptionString: String?) instead.");

/// Returns a new search suggestion object with a specified suggestion string, description string, and a search icon image.
+ (instancetype)suggestionWithLocalizedSuggestion:(NSString *)suggestion descriptionString:(nullable NSString *)description iconImage:(nullable UIImage *)iconImage NS_SWIFT_UNAVAILABLE("Use init(string suggestionString: String, descriptionString: String?, iconImage: UIImage?) instead.");

/// Factory methods taking NSAttributedString instead of NSString for the suggestion
+ (instancetype)suggestionWithLocalizedAttributedSuggestion:(NSAttributedString *)suggestion NS_SWIFT_UNAVAILABLE("Use init(localizedAttributedSuggestion: NSAttributedString) instead.") API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);
+ (instancetype)suggestionWithLocalizedAttributedSuggestion:(NSAttributedString *)suggestion descriptionString:(nullable NSString *)description NS_SWIFT_UNAVAILABLE("Use init(localizedAttributedSuggestion: NSAttributedString, localizedDescription: String?) instead.") API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);
+ (instancetype)suggestionWithLocalizedAttributedSuggestion:(NSAttributedString *)suggestion descriptionString:(nullable NSString *)description iconImage:(nullable UIImage *)iconImage NS_SWIFT_UNAVAILABLE("Use init(localizedAttributedSuggestion: NSAttributedString, localizedDescription: String?, iconImage: UIImage?) instead.") API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/// Initializes a search suggestion object with a specified search suggestion string.
- (instancetype)initWithLocalizedSuggestion:(NSString *)suggestion;

/// Initializes a search suggestion object with a specified search suggestion string and a description string.
- (instancetype)initWithLocalizedSuggestion:(NSString *)suggestion localizedDescription:(nullable NSString *)description;

/// Initializes a search suggestion object with a specified search suggestion string, a description string, and a search icon image.
- (instancetype)initWithLocalizedSuggestion:(NSString *)suggestion localizedDescription:(nullable NSString *)description iconImage:(nullable UIImage *)iconImage;

/// Initializers taking NSAttributedString instead of NSString for the suggestion
- (instancetype)initWithLocalizedAttributedSuggestion:(NSAttributedString *)suggestion API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);
- (instancetype)initWithLocalizedAttributedSuggestion:(NSAttributedString *)suggestion localizedDescription:(nullable NSString *)description API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);
- (instancetype)initWithLocalizedAttributedSuggestion:(NSAttributedString *)suggestion localizedDescription:(nullable NSString *)description iconImage:(nullable UIImage *)iconImage API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/// If non-null, will be displayed as the search string instead of localizedSuggestion
@property (nonatomic, readonly, nullable) NSAttributedString *localizedAttributedSuggestion API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/// The localized suggestion that will be displayed as the search string
@property (nonatomic, readonly, nullable) NSString *localizedSuggestion;

/// The localized description used as accessibility string
@property (nonatomic, readonly, nullable) NSString *localizedDescription;

/// Icon that represents this search suggestion item
@property (nonatomic, readonly, nullable) UIImage *iconImage;

/// User information
@property (strong, nullable, nonatomic) id representedObject API_AVAILABLE(ios(16.0), tvos(16.0));
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISearchSuggestion.h>
#endif
