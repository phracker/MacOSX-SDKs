#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScreenshotService.h>)
//
//  UIScreenshotService.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIWindowScene.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UIScreenshotServiceDelegate;

/*!
 @abstract This class allows your application to produce a higher fidelity, PDF screenshot to the user. Set the delegate so that when a screenshot is taken, screenshots can show the full document content from the application.
 */
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_UI_ACTOR
@interface UIScreenshotService : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @abstract Assign a delegate in order to send PDF data to accompany the screenshot taken by the user
 */
@property (nonatomic, weak, nullable) id<UIScreenshotServiceDelegate> delegate;

/*!
 @abstract The window scene associated with the screenshot service
 */
@property (nonatomic, weak, readonly, nullable) UIWindowScene *windowScene;

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(visionos) @interface UIWindowScene (UIScreenshotService)
/*!
 @abstract The screenshot object associated with the scene
 @discussion This is non-null if the screenshot service is available for this window scene
 */
@property (nonatomic, readonly, nullable) UIScreenshotService *screenshotService;

@end


API_UNAVAILABLE(visionos, watchos) NS_SWIFT_UI_ACTOR
@protocol UIScreenshotServiceDelegate <NSObject>

@optional
/*!
 @abstract  The delegate method to send the PDF data to screenshots
 @discussion The delegate is required to send the data via the completion handler
 @param screenshotService The screenshot service object associated per scene
 @param completionHandler The block to execute when the PDF data is ready.
 If no PDF data is available, data can be nil. The indexOfCurrentPage is zero-based, and is the index of the current page of the snapshotted PDF. The rectInCurrentPage is the rect in PDF coordinates with respect to the current page. If the receiver cannot provide the visible area, pass CGRectZero for rectInCurrentPage.
 */
- (void)screenshotService:(UIScreenshotService *)screenshotService generatePDFRepresentationWithCompletion:(void (^)(NSData *_Nullable PDFData, NSInteger indexOfCurrentPage, CGRect rectInCurrentPage))completionHandler;

@end


NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIScreenshotService.h>
#endif
