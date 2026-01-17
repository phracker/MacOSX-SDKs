#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPasteboard.h>)
//
//  UIPasteboard.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * UIPasteboardName NS_TYPED_EXTENSIBLE_ENUM;

UIKIT_EXTERN UIPasteboardName const UIPasteboardNameGeneral API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
UIKIT_EXTERN NSString *const UIPasteboardNameFind API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) API_DEPRECATED("The Find pasteboard is no longer available.", ios(3.0, 10.0));

typedef NSString * UIPasteboardDetectionPattern NS_TYPED_ENUM API_AVAILABLE(ios(14.0));

/// NSString value, suitable for implementing "Paste and Go"
UIKIT_EXTERN UIPasteboardDetectionPattern const UIPasteboardDetectionPatternProbableWebURL API_AVAILABLE(ios(14.0));

/// NSString value, suitable for implementing "Paste and Search"
UIKIT_EXTERN UIPasteboardDetectionPattern const UIPasteboardDetectionPatternProbableWebSearch API_AVAILABLE(ios(14.0));

/// NSNumber value
UIKIT_EXTERN UIPasteboardDetectionPattern const UIPasteboardDetectionPatternNumber API_AVAILABLE(ios(14.0));

@class UIColor, UIImage;

UIKIT_EXTERN API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) @interface UIPasteboard : NSObject

@property(class, nonatomic, readonly) UIPasteboard *generalPasteboard;

+ (nullable UIPasteboard *)pasteboardWithName:(UIPasteboardName)pasteboardName create:(BOOL)create;
+ (UIPasteboard *)pasteboardWithUniqueName;

@property(readonly,nonatomic) UIPasteboardName name;

+ (void)removePasteboardWithName:(UIPasteboardName)pasteboardName;

@property(readonly,getter=isPersistent,nonatomic) BOOL persistent;
- (void)setPersistent:(BOOL)persistent API_DEPRECATED("Do not set persistence on pasteboards. This property is set automatically.", ios(3.0, 10.0));
@property(readonly,nonatomic) NSInteger changeCount;

// Item provider interface

@property (nonatomic, copy) NSArray<__kindof NSItemProvider *> *itemProviders API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

- (void)setItemProviders:(NSArray<NSItemProvider *> *)itemProviders localOnly:(BOOL)localOnly expirationDate:(NSDate * _Nullable)expirationDate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// Automatically creates item providers wrapping the objects passed in.
- (void)setObjects:(NSArray<id<NSItemProviderWriting>> *)objects API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);
- (void)setObjects:(NSArray<id<NSItemProviderWriting>> *)objects localOnly:(BOOL)localOnly expirationDate:(NSDate * _Nullable)expirationDate API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// First item

@property(nonatomic, readonly) NSArray<NSString *> * pasteboardTypes;
- (BOOL)containsPasteboardTypes:(NSArray<NSString *> *)pasteboardTypes;
- (nullable NSData *)dataForPasteboardType:(NSString *)pasteboardType;

- (nullable id)valueForPasteboardType:(NSString *)pasteboardType;

- (void)setValue:(id)value forPasteboardType:(NSString *)pasteboardType;
- (void)setData:(NSData *)data forPasteboardType:(NSString *)pasteboardType;

// Multiple items

@property(readonly,nonatomic) NSInteger numberOfItems;
- (nullable NSArray<NSArray<NSString *> *> *)pasteboardTypesForItemSet:(nullable NSIndexSet*)itemSet;

- (BOOL)containsPasteboardTypes:(NSArray<NSString *> *)pasteboardTypes inItemSet:(nullable NSIndexSet *)itemSet;
- (nullable NSIndexSet *)itemSetWithPasteboardTypes:(NSArray<NSString *> *)pasteboardTypes;
- (nullable NSArray *)valuesForPasteboardType:(NSString *)pasteboardType inItemSet:(nullable NSIndexSet *)itemSet;
- (nullable NSArray<NSData *> *)dataForPasteboardType:(NSString *)pasteboardType inItemSet:(nullable NSIndexSet *)itemSet;

// Direct access

@property(nonatomic,copy) NSArray<NSDictionary<NSString *, id> *> *items;
- (void)addItems:(NSArray<NSDictionary<NSString *, id> *> *)items;

typedef NSString * UIPasteboardOption NS_TYPED_ENUM API_AVAILABLE(ios(10.0));

UIKIT_EXTERN UIPasteboardOption const UIPasteboardOptionExpirationDate API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) API_AVAILABLE(ios(10.0)) NS_SWIFT_NAME(UIPasteboardOption.expirationDate); // Value: NSDate.
UIKIT_EXTERN UIPasteboardOption const UIPasteboardOptionLocalOnly API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) API_AVAILABLE(ios(10.0)) NS_SWIFT_NAME(UIPasteboardOption.localOnly); // Value: NSNumber, boolean.

- (void)setItems:(NSArray<NSDictionary<NSString *, id> *> *)items options:(NSDictionary<UIPasteboardOption, id> *)options API_AVAILABLE(ios(10.0));

@property(nullable,nonatomic,copy) NSString *string API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
@property(nullable,nonatomic,copy) NSArray<NSString *> *strings API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@property(nullable,nonatomic,copy) NSURL *URL API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
@property(nullable,nonatomic,copy) NSArray<NSURL *> *URLs API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@property(nullable,nonatomic,copy) UIImage *image API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
@property(nullable,nonatomic,copy) NSArray<UIImage *> *images API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@property(nullable,nonatomic,copy) UIColor *color API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
@property(nullable,nonatomic,copy) NSArray<UIColor *> *colors API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Queries

@property (nonatomic, readonly) BOOL hasStrings API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) API_AVAILABLE(ios(10.0));
@property (nonatomic, readonly) BOOL hasURLs API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) API_AVAILABLE(ios(10.0));
@property (nonatomic, readonly) BOOL hasImages API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) API_AVAILABLE(ios(10.0));
@property (nonatomic, readonly) BOOL hasColors API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) API_AVAILABLE(ios(10.0));

// Detection

/// Detects patterns in the first pasteboard item.
///
/// @param patterns Detect only these patterns.
/// @param completionHandler Receives which patterns were detected, or an error.
- (void)detectPatternsForPatterns:(NSSet<UIPasteboardDetectionPattern> *)patterns
                completionHandler:(void(^)(NSSet<UIPasteboardDetectionPattern> * _Nullable,
                                           NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(14.0));
            
/// Detects patterns in the specified pasteboard items.
///
/// @param patterns Detect only these patterns.
/// @param itemSet Specifies which pasteboard items by their position. Nil means all items.
/// @param completionHandler Receives which patterns were detected per item specified,
///                          or an error.
- (void)detectPatternsForPatterns:(NSSet<UIPasteboardDetectionPattern> *)patterns
                        inItemSet:(NSIndexSet * _Nullable)itemSet
                completionHandler:(void(^)(NSArray<NSSet<UIPasteboardDetectionPattern> *> * _Nullable,
                                           NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(14.0));
                 
/// Detects patterns and corresponding values in the first pasteboard item.
///
/// @param patterns Detect only these patterns.
/// @param completionHandler Receives which patterns and values were detected, or an error.
- (void)detectValuesForPatterns:(NSSet<UIPasteboardDetectionPattern> *)patterns
              completionHandler:(void(^)(NSDictionary<UIPasteboardDetectionPattern, id> * _Nullable,
                                         NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(14.0));
            
/// Detects patterns and corresponding values in the specified pasteboard items.
///
/// @param patterns Detect only these patterns.
/// @param itemSet Specifies which pasteboard items by their position. Nil means all items.
/// @param completionHandler Receives which patterns and values were detected per item specified,
///                          or an error.
- (void)detectValuesForPatterns:(NSSet<UIPasteboardDetectionPattern> *)patterns
                      inItemSet:(NSIndexSet * _Nullable)itemSet
              completionHandler:(void(^)(NSArray<NSDictionary<UIPasteboardDetectionPattern, id> *> * _Nullable,
                                         NSError * _Nullable))completionHandler NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(14.0));

@end

// Notification

UIKIT_EXTERN NSNotificationName const UIPasteboardChangedNotification API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
UIKIT_EXTERN NSString *const UIPasteboardChangedTypesAddedKey API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
UIKIT_EXTERN NSString *const UIPasteboardChangedTypesRemovedKey API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

UIKIT_EXTERN NSNotificationName const UIPasteboardRemovedNotification API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Types

UIKIT_EXTERN NSArray<NSString *> *UIPasteboardTypeListString API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
UIKIT_EXTERN NSArray<NSString *> *UIPasteboardTypeListURL API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
UIKIT_EXTERN NSArray<NSString *> *UIPasteboardTypeListImage API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
UIKIT_EXTERN NSArray<NSString *> *UIPasteboardTypeListColor API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

// Use the following type in setItems: or setItems:options: to automatically insert appropriate UTIs for supported types.
// Supported types are: NSString, NSURL, UIImage, UIColor, NSAttributedString.
UIKIT_EXTERN NSString * const UIPasteboardTypeAutomatic API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) API_AVAILABLE(ios(10.0));

NS_ASSUME_NONNULL_END
    

#else
#import <UIKitCore/UIPasteboard.h>
#endif
