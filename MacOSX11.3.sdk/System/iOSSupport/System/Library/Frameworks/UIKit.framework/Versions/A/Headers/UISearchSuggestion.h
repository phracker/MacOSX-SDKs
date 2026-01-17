#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISearchSuggestion.h>)
//
//  UISearchSuggestion.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;

UIKIT_CLASS_AVAILABLE_TVOS_ONLY(14.0)
@protocol UISearchSuggestion <NSObject>

/// The localized suggestion that will be displayed as the search string
@property (nonatomic, readonly, nullable) NSString *localizedSuggestion;

@optional
/// The localized description used as accessibility string
@property (nonatomic, readonly, nullable) NSString *localizedDescription;

/// Icon that represents this search suggestion item
@property (nonatomic, readonly, nullable) UIImage *iconImage;

@end

/// A concrete container for search suggestion string and optional image and associated information for providing shortcuts in search experience on tvOS.
UIKIT_CLASS_AVAILABLE_TVOS_ONLY(14.0)
@interface UISearchSuggestionItem : NSObject <UISearchSuggestion>

/// Returns a new search suggestion object with a specified suggestion string.
+ (instancetype)suggestionWithLocalizedSuggestion:(NSString *)suggestion NS_SWIFT_UNAVAILABLE("Use init(string suggestionString: String) instead.");

/// Returns a new search suggestion object with a specified suggestion string and a description string.
+ (instancetype)suggestionWithLocalizedSuggestion:(NSString *)suggestion descriptionString:(nullable NSString *)description NS_SWIFT_UNAVAILABLE("Use init(string suggestionString: String, descriptionString: String?) instead.");

/// Returns a new search suggestion object with a specified suggestion string, description string, and a search icon image.
+ (instancetype)suggestionWithLocalizedSuggestion:(NSString *)suggestion descriptionString:(nullable NSString *)description iconImage:(nullable UIImage *)iconImage NS_SWIFT_UNAVAILABLE("Use init(string suggestionString: String, descriptionString: String?, iconImage: UIImage?) instead.");

/// Initializes a search suggestion object with a specified search suggestion string.
- (instancetype)initWithLocalizedSuggestion:(NSString *)suggestion;

/// Initializes a search suggestion object with a specified search suggestion string and a description string.
- (instancetype)initWithLocalizedSuggestion:(NSString *)suggestion localizedDescription:(nullable NSString *)description;

/// Initializes a search suggestion object with a specified search suggestion string, a description string, and a search icon image.
- (instancetype)initWithLocalizedSuggestion:(NSString *)suggestion localizedDescription:(nullable NSString *)description iconImage:(nullable UIImage *)iconImage;

/// The localized suggestion that will be displayed as the search string
@property (nonatomic, readonly, nullable) NSString *localizedSuggestion;

/// The localized description used as accessibility string
@property (nonatomic, readonly, nullable) NSString *localizedDescription;

/// Icon that represents this search suggestion item
@property (nonatomic, readonly, nullable) UIImage *iconImage;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISearchSuggestion.h>
#endif
