/*
    NSTextList.h
    Copyright (c) 2004-2018, Apple Inc.
    All rights reserved.

    Class to represent text lists.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * NSTextListMarkerFormat NS_TYPED_EXTENSIBLE_ENUM;
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerBox NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerCheck NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerCircle NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDiamond NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDisc NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerHyphen NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerSquare NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseHexadecimal NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseHexadecimal NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerOctal NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseAlpha NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseAlpha NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseLatin NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseLatin NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseRoman NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseRoman NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDecimal NS_AVAILABLE_MAC(10_13);

typedef NS_OPTIONS(NSUInteger, NSTextListOptions) {
    NSTextListPrependEnclosingMarker = (1 << 0)
};

@interface NSTextList : NSObject <NSCoding, NSCopying> {
    /*All instance variables are private*/
    NSString *_markerFormat APPKIT_IVAR;
    NSUInteger _listFlags APPKIT_IVAR;
    NSInteger _startIndex APPKIT_IVAR;
    void *_listSecondary APPKIT_IVAR;
}

- (instancetype)initWithMarkerFormat:(NSTextListMarkerFormat)format options:(NSUInteger)mask;
@property (readonly, copy) NSTextListMarkerFormat markerFormat;
@property (readonly) NSTextListOptions listOptions;
- (NSString *)markerForItemNumber:(NSInteger)itemNum;
@property NSInteger startingItemNumber NS_AVAILABLE_MAC(10_6);

@end

NS_ASSUME_NONNULL_END
