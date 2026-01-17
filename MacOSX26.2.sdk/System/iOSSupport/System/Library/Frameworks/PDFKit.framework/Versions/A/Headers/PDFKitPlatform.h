//
//  PDFKitPlatform.h
//  Copyright © 2019 Apple. All rights reserved.
//

#import <TargetConditionals.h>

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


#if (TARGET_OS_MAC && !(TARGET_OS_SIMULATOR || TARGET_OS_IPHONE || TARGET_OS_MACCATALYST))

// OSX Headers
#import <Cocoa/Cocoa.h>
#import <AppKit/NSAccessibilityProtocols.h>

#define PDFKIT_PLATFORM_OSX

// AppKit types
#define PDFKitPlatformView                                      NSView
#define PDFKitPlatformViewController                            NSViewController
#define PDFKitPlatformScrollView                                NSScrollView
#define PDFKitPlatformColor                                     NSColor
#define PDFKitPlatformBezierPath                                NSBezierPath
#define PDFKitPlatformBezierPathElement                         NSBezierPathElement
#define PDFKitPlatformImage                                     NSImage
#define PDFKitPlatformImageView                                 NSImageView
#define PDFKitPlatformEvent                                     NSEvent
#define PDFKitPlatformFont                                      NSFont
#define PDFKitPlatformColor                                     NSColor
#define PDFKitPlatformControl                                   NSControl
#define PDFKitPlatformTextField                                 NSTextField
#define PDFKitPlatformTextView                                  NSTextView
#define PDFKitPlatformTextViewDelegate                          NSTextViewDelegate
#define PDFKitPlatformChoiceWidgetComboBoxView                  NSPopUpButton
#define PDFKitPlatformChoiceWidgetListView                      NSTableView
#define PDFKitPlatformButton                                    NSButton
#define PDFKitPlatformButtonCell                                NSButtonCell
#define PDFKitPlatformAccessibilityElement                      NSAccessibilityElement
#define PDFKitResponder                                         NSResponder
#define PDFKitPlatformTextContentType                           NSTextContentType

// Geometry types
#define PDFPoint                                                NSPoint
#define PDFRect                                                 NSRect
#define PDFSize                                                 NSSize
#define PDFEdgeInsets                                           NSEdgeInsets

// Constants
#define PDFPointZero                                            NSZeroPoint
#define PDFSizeZero                                             NSZeroSize
#define PDFRectZero                                             NSZeroRect
#define PDFEdgeInsetsZero                                       NSEdgeInsetsZero
#define PDFTrackingRunLoopMode                                  NSEventTrackingRunLoopMode

// Font Weights
#define PDFKitPlatformFontWeightRegular                         NSFontWeightRegular

#elif (TARGET_OS_SIMULATOR || TARGET_OS_IPHONE || TARGET_OS_MACCATALYST)

// iOS Headers
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define PDFKIT_PLATFORM_IOS

#if TARGET_OS_MACCATALYST
    #define PDFKIT_PLATFORM_MACCATALYST
#endif

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
#define PDFKitPlatformTextContentType                           UITextContentType

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
#define PDFTrackingRunLoopMode                             UITrackingRunLoopMode

// Font Weights
#define PDFKitPlatformFontWeightRegular                         UIFontWeightRegular

#else

#error "Failure: PDFKit unsupported platform"

#endif

