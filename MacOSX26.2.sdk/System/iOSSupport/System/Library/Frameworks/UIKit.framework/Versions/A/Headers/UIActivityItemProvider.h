#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<ShareSheet/UIActivityItemProvider.h>)
//
//  UIActivityItemProvider.h
//  UIKit
//
//  Copyright 2012-2018 Apple Inc. All rights reserved.
//
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIActivity.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIActivityViewController, UIImage, LPLinkMetadata, INPerson;

API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(watchos)
@protocol UIActivityItemSource <NSObject>

@required

- (id)activityViewControllerPlaceholderItem:(UIActivityViewController *)activityViewController;	// called to determine data type. only the class of the return type is consulted. it should match what -itemForActivityType: returns later
- (nullable id)activityViewController:(UIActivityViewController *)activityViewController itemForActivityType:(nullable UIActivityType)activityType;	// called to fetch data after an activity is selected. you can return nil.

@optional

- (NSString *)activityViewController:(UIActivityViewController *)activityViewController subjectForActivityType:(nullable UIActivityType)activityType API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(watchos); // if activity supports a Subject field. iOS 7.0
- (NSString *)activityViewController:(UIActivityViewController *)activityViewController dataTypeIdentifierForActivityType:(nullable UIActivityType)activityType API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(watchos); // UTI for item if it is an NSData. iOS 7.0. will be called with nil activity and then selected activity
- (nullable UIImage *)activityViewController:(UIActivityViewController *)activityViewController thumbnailImageForActivityType:(nullable UIActivityType)activityType suggestedSize:(CGSize)size API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(watchos); // if activity supports preview image. iOS 7.0
- (nullable LPLinkMetadata *)activityViewControllerLinkMetadata:(UIActivityViewController *)activityViewController API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos); // called to fetch LinkPresentation metadata for the activity item. iOS 13.0

/// @abstract Allows the activity item source to provide recipients who will be filled in by default in the compose view if that sharing app supports it.
/// @discussion This might fail to pre-fill correctly if the sharing app chosen by the user can't recognize the provided person. Also, if a people suggestion is chosen, that suggestion will override this provided value.
- (NSArray<INPerson *> *)activityViewControllerShareRecipients:(UIActivityViewController *)activityViewController API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(watchos) __TVOS_PROHIBITED @interface UIActivityItemProvider : NSOperation <UIActivityItemSource>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithPlaceholderItem:(id)placeholderItem NS_DESIGNATED_INITIALIZER;               // placeHolder is the return value for -activityViewControllerPlaceholderItem:

@property(nullable,nonatomic,strong,readonly) id        placeholderItem;
@property(nullable,nonatomic,copy,readonly)   UIActivityType activityType;     // activity type available when -item is called. nil at other times. use this in your -item method to customize the data to return

@property(nonnull, nonatomic, readonly) id item;   // called on secondary thread when user selects an activity. you must subclass and return a non-nil value. The item can use the UIActivityItemSource protocol to return extra information

@end

NS_ASSUME_NONNULL_END

#else
#import <ShareSheet/UIActivityItemProvider.h>
#endif
