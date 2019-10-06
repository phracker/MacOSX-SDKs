#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPrintInteractionController.h>)
//
//  UIPrintInteractionController.h
//  UIKit
//
//  Copyright 2010-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPrintInteractionController, UIPrintInfo, UIPrintPaper, UIPrintPageRenderer, UIPrintFormatter, UIPrinter;
@class UIView, UIBarButtonItem;

typedef void (^UIPrintInteractionCompletionHandler)(UIPrintInteractionController *printInteractionController, BOOL completed, NSError * __nullable error) API_UNAVAILABLE(tvos);


API_AVAILABLE(ios(9.0)) typedef NS_ENUM(NSInteger, UIPrinterCutterBehavior) {
    UIPrinterCutterBehaviorNoCut,
    UIPrinterCutterBehaviorPrinterDefault,
    UIPrinterCutterBehaviorCutAfterEachPage,
    UIPrinterCutterBehaviorCutAfterEachCopy,
    UIPrinterCutterBehaviorCutAfterEachJob,
} API_UNAVAILABLE(tvos);

@protocol UIPrintInteractionControllerDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(tvos) @interface UIPrintInteractionController : NSObject

@property(class, nonatomic, readonly, getter=isPrintingAvailable) BOOL printingAvailable;                    // return YES if system supports printing. use this to hide HI for unsupported devices.

@property(class, nonatomic, readonly) NSSet<NSString *> *printableUTIs;                       // return set of all document UTI types we can print
+ (BOOL)canPrintURL:(NSURL *)url;
+ (BOOL)canPrintData:(NSData *)data;

@property(class, nonatomic, readonly) UIPrintInteractionController *sharedPrintController;

@property(nullable,nonatomic,strong) UIPrintInfo                             *printInfo;      // changes to printInfo ignored while printing. default is nil
@property(nullable,nonatomic,weak)   id<UIPrintInteractionControllerDelegate> delegate;       // not retained. default is nil
@property(nonatomic)        BOOL                                     showsPageRange API_DEPRECATED("Pages can be removed from the print preview, so page range is always shown.", ios(4.2, 10.0));
@property(nonatomic)        BOOL                                     showsNumberOfCopies API_AVAILABLE(ios(7.0)); // default is YES.
@property(nonatomic)        BOOL                                     showsPaperSelectionForLoadedPapers API_AVAILABLE(ios(8.0)); // default is NO.  Paper selection for loaded papers is always shown for UIPrintInfoOutputPhoto and UIPrintInfoOutputPhotoGrayscale

@property(nullable, nonatomic,readonly) UIPrintPaper *printPaper;  // set after printer selection

@property(nullable,nonatomic,strong) UIPrintPageRenderer *printPageRenderer;  // calls class to render each page
@property(nullable,nonatomic,strong) UIPrintFormatter    *printFormatter;     // uses a single formatter to fill the pages
@property(nullable,nonatomic,copy)   id                   printingItem;       // single NSData, NSURL, UIImage, ALAsset
@property(nullable,nonatomic,copy)   NSArray             *printingItems;      // array of NSData, NSURL, UIImage, ALAsset. does not support page range

- (BOOL)presentAnimated:(BOOL)animated completionHandler:(nullable UIPrintInteractionCompletionHandler)completion;                                                // iPhone
- (BOOL)presentFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated completionHandler:(nullable UIPrintInteractionCompletionHandler)completion;    // iPad
- (BOOL)presentFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated completionHandler:(nullable UIPrintInteractionCompletionHandler)completion;      // iPad

/*!
 * @discussion	Use to print without showing the standard print panel. Use with a
 *		UIPrinter found using the UIPrinterPickerController.
 *              The value for the duplex property on printInfo will be ignored.
 */
- (BOOL)printToPrinter:(UIPrinter *)printer completionHandler:(nullable UIPrintInteractionCompletionHandler)completion;

- (void)dismissAnimated:(BOOL)animated;

@end

API_UNAVAILABLE(tvos) @protocol UIPrintInteractionControllerDelegate <NSObject>
@optional

- ( UIViewController * _Nullable )printInteractionControllerParentViewController:(UIPrintInteractionController *)printInteractionController;

- (UIPrintPaper *)printInteractionController:(UIPrintInteractionController *)printInteractionController choosePaper:(NSArray<UIPrintPaper *> *)paperList;

- (void)printInteractionControllerWillPresentPrinterOptions:(UIPrintInteractionController *)printInteractionController;
- (void)printInteractionControllerDidPresentPrinterOptions:(UIPrintInteractionController *)printInteractionController;
- (void)printInteractionControllerWillDismissPrinterOptions:(UIPrintInteractionController *)printInteractionController;
- (void)printInteractionControllerDidDismissPrinterOptions:(UIPrintInteractionController *)printInteractionController;

- (void)printInteractionControllerWillStartJob:(UIPrintInteractionController *)printInteractionController;
- (void)printInteractionControllerDidFinishJob:(UIPrintInteractionController *)printInteractionController;

- (CGFloat)printInteractionController:(UIPrintInteractionController *)printInteractionController cutLengthForPaper:(UIPrintPaper *)paper API_AVAILABLE(ios(7.0));
- (UIPrinterCutterBehavior) printInteractionController:(UIPrintInteractionController *)printInteractionController chooseCutterBehavior:(NSArray *)availableBehaviors API_AVAILABLE(ios(9.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPrintInteractionController.h>
#endif
