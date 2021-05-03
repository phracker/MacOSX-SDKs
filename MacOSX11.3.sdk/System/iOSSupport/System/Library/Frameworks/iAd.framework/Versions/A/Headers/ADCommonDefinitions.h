//
//  ADCommonDefinitions.h
//  iAd
//

#ifndef ADCommonDefinitions_h
#define ADCommonDefinitions_h

#import <Availability.h>

#pragma warning "ADCommonDefinitions.h is deprecated and will be removed in a future release. Do not include this header."

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST && (__IPHONE_OS_VERSION_MAX_ALLOWED <= __IPHONE_13_0)

#import <UIKit/UIKit.h>

#define IS_IPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#define IS_IPHONE (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
#define IS_RETINA ([[UIScreen mainScreen] scale] >= 2.0)

#define SCREEN_WIDTH ([[UIScreen mainScreen] bounds].size.width)
#define SCREEN_HEIGHT ([[UIScreen mainScreen] bounds].size.height)
#define SCREEN_MAX_LENGTH (MAX(SCREEN_WIDTH, SCREEN_HEIGHT))
#define SCREEN_MIN_LENGTH (MIN(SCREEN_WIDTH, SCREEN_HEIGHT))

#define IS_IPHONE_4 (IS_IPHONE && SCREEN_MAX_LENGTH < 568.0)
#define IS_IPHONE_5_OR_SE (IS_IPHONE && SCREEN_MAX_LENGTH == 568.0)
#define IS_IPHONE_6_OR_7_OR_8 (IS_IPHONE && SCREEN_MAX_LENGTH == 667.0)
#define IS_IPHONE_6P_OR_7P_OR_8P (IS_IPHONE && SCREEN_MAX_LENGTH == 736.0)
#define IS_IPHONE_X (IS_IPHONE && SCREEN_MAX_LENGTH == 812.0)

#endif /* TARGET_OS_IOS ... */

#endif /* ADCommonDefinitions_h */
