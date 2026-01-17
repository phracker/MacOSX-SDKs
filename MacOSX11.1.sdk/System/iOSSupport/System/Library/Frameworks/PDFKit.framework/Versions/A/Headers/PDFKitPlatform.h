//
//  PDFKitPlatform.h
//  Copyright © 2019 Apple. All rights reserved.
//

#import <TargetConditionals.h>

    #define PDFKIT_PLATFORM_IOS

#ifndef PDFKIT_EXTERN
    #ifdef __cplusplus
        #define PDFKIT_EXTERN extern "C" __attribute__((visibility ("default")))
    #else
        #define PDFKIT_EXTERN extern __attribute__((visibility ("default")))
    #endif
#endif

// Deprecation &  macros

#define PDFKIT_AVAILABLE(_macIntro, _iosIntro) \
    NS_AVAILABLE(_macIntro, _iosIntro)

#define PDFKIT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
    NS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)

#define PDFKIT_CLASS_AVAILABLE(_macIntro, _iosIntro) \
    NS_CLASS_AVAILABLE(_macIntro, _iosIntro)

#define PDFKIT_CLASS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
    NS_CLASS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)

#define PDFKIT_ENUM_AVAILABLE(_macIntro, _iosIntro) \
    NS_ENUM_AVAILABLE(_macIntro, _iosIntro)

#define PDFKIT_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
    NS_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)



// iOS Headers
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// UIKit types
#define PDFKitPlatformView                                      UIView
#define PDFKitPlatformViewController                            UIViewController
#define PDFKitPlatformScrollView                                UIScrollView
#define PDFKitPlatformColor                                     UIColor
#define PDFKitPlatformBezierPath                                UIBezierPath
#define PDFKitPlatformBezierPathElement                         UIBezierPathElement
#define PDFKitPlatformImage                                     UIImage
#define PDFKitPlatformImageView                                 UIImageView
#define PDFKitPlatformEvent                                     UIEvent
#define PDFKitPlatformFont                                      UIFont
#define PDFKitPlatformColor                                     UIColor
#define PDFKitPlatformControl                                   UIControl
#define PDFKitPlatformTextField                                 UITextField
#define PDFKitPlatformTextView                                  UITextView
#define PDFKitPlatformTextViewDelegate                          UITextViewDelegate
#define PDFKitPlatformChoiceWidgetComboBoxView                  UIPickerView
#define PDFKitPlatformChoiceWidgetListView                      UITableView
#define PDFKitPlatformButton                                    UIButton
#define PDFKitPlatformButtonCell                                UICollectionViewCell
#define PDFKitPlatformAccessibilityElement                      UIAccessibilityElement
#define PDFKitResponder                                         UIResponder

// Geometry types
#define PDFPoint                                                CGPoint
#define PDFRect                                                 CGRect
#define PDFSize                                                 CGSize
#define PDFEdgeInsets                                           UIEdgeInsets

// Constants
#define PDFPointZero                                            CGPointZero
#define PDFSizeZero                                             CGSizeZero
#define PDFRectZero                                             CGRectZero
#define PDFEdgeInsetsZero                                       UIEdgeInsetsZero


