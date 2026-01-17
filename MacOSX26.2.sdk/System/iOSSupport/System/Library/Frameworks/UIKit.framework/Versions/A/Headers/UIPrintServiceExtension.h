#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<PrintKitUI/UIPrintServiceExtension.h>)
//
//  UIPrintServiceExtension.h
//  UIKit
//
//  Copyright 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPrintInfo;

UIKIT_EXTERN API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIPrinterDestination : NSObject <NSSecureCoding>

-(instancetype)initWithURL:(NSURL *)url;

@property (readwrite, copy)           NSURL    *URL;
@property (readwrite, copy, nullable) NSString *displayName;
@property (readwrite, copy, nullable) NSData   *txtRecord;

@end

UIKIT_EXTERN API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIPrintServiceExtension : NSObject

-(NSArray<UIPrinterDestination *> *)printerDestinationsForPrintInfo:(UIPrintInfo *)printInfo;

@end

NS_ASSUME_NONNULL_END

#else
#import <PrintKitUI/UIPrintServiceExtension.h>
#endif
