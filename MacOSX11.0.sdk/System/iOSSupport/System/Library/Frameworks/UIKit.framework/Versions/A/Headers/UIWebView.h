#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWebView.h>)
//
//  UIWebView.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UIScrollView.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIWebViewNavigationType) {
    UIWebViewNavigationTypeLinkClicked,
    UIWebViewNavigationTypeFormSubmitted,
    UIWebViewNavigationTypeBackForward,
    UIWebViewNavigationTypeReload,
    UIWebViewNavigationTypeFormResubmitted,
    UIWebViewNavigationTypeOther
} API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, UIWebPaginationMode) {
    UIWebPaginationModeUnpaginated,
    UIWebPaginationModeLeftToRight,
    UIWebPaginationModeTopToBottom,
    UIWebPaginationModeBottomToTop,
    UIWebPaginationModeRightToLeft
} API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, UIWebPaginationBreakingMode) {
    UIWebPaginationBreakingModePage,
    UIWebPaginationBreakingModeColumn
} API_UNAVAILABLE(tvos);

@class UIWebViewInternal;
@protocol UIWebViewDelegate;

UIKIT_EXTERN API_DEPRECATED("No longer supported; please adopt WKWebView.", ios(2.0, 12.0)) API_UNAVAILABLE(tvos, macos, macCatalyst) @interface UIWebView : UIView <NSCoding, UIScrollViewDelegate>

@property (nullable, nonatomic, assign) id <UIWebViewDelegate> delegate;

@property (nonatomic, readonly, strong) UIScrollView *scrollView API_AVAILABLE(ios(5.0));

- (void)loadRequest:(NSURLRequest *)request;
- (void)loadHTMLString:(NSString *)string baseURL:(nullable NSURL *)baseURL;
- (void)loadData:(NSData *)data MIMEType:(NSString *)MIMEType textEncodingName:(NSString *)textEncodingName baseURL:(NSURL *)baseURL;

@property (nullable, nonatomic, readonly, strong) NSURLRequest *request;

- (void)reload;
- (void)stopLoading;

- (void)goBack;
- (void)goForward;

@property (nonatomic, readonly, getter=canGoBack) BOOL canGoBack;
@property (nonatomic, readonly, getter=canGoForward) BOOL canGoForward;
@property (nonatomic, readonly, getter=isLoading) BOOL loading;

- (nullable NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script;

@property (nonatomic) BOOL scalesPageToFit;

@property (nonatomic) BOOL detectsPhoneNumbers API_DEPRECATED("", ios(2.0, 3.0));
@property (nonatomic) UIDataDetectorTypes dataDetectorTypes API_AVAILABLE(ios(3.0));

@property (nonatomic) BOOL allowsInlineMediaPlayback API_AVAILABLE(ios(4.0)); // iPhone Safari defaults to NO. iPad Safari defaults to YES
@property (nonatomic) BOOL mediaPlaybackRequiresUserAction API_AVAILABLE(ios(4.0)); // iPhone and iPad Safari both default to YES

@property (nonatomic) BOOL mediaPlaybackAllowsAirPlay API_AVAILABLE(ios(5.0)); // iPhone and iPad Safari both default to YES

@property (nonatomic) BOOL suppressesIncrementalRendering API_AVAILABLE(ios(6.0)); // iPhone and iPad Safari both default to NO

@property (nonatomic) BOOL keyboardDisplayRequiresUserAction API_AVAILABLE(ios(6.0)); // default is YES

@property (nonatomic) UIWebPaginationMode paginationMode API_AVAILABLE(ios(7.0));
@property (nonatomic) UIWebPaginationBreakingMode paginationBreakingMode API_AVAILABLE(ios(7.0));
@property (nonatomic) CGFloat pageLength API_AVAILABLE(ios(7.0));
@property (nonatomic) CGFloat gapBetweenPages API_AVAILABLE(ios(7.0));
@property (nonatomic, readonly) NSUInteger pageCount API_AVAILABLE(ios(7.0));

@property (nonatomic) BOOL allowsPictureInPictureMediaPlayback API_AVAILABLE(ios(9.0));

@property (nonatomic) BOOL allowsLinkPreview API_AVAILABLE(ios(9.0)); // default is NO
@end

API_UNAVAILABLE(tvos, macos, macCatalyst) @protocol UIWebViewDelegate <NSObject>

@optional
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType API_DEPRECATED("No longer supported.", ios(2.0, 12.0));
- (void)webViewDidStartLoad:(UIWebView *)webView API_DEPRECATED("No longer supported.", ios(2.0, 12.0));
- (void)webViewDidFinishLoad:(UIWebView *)webView API_DEPRECATED("No longer supported.", ios(2.0, 12.0));
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error API_DEPRECATED("No longer supported.", ios(2.0, 12.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIWebView.h>
#endif
