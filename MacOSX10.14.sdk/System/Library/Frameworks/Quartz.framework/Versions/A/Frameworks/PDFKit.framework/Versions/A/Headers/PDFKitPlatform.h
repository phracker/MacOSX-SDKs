//
//  PDFKitPlatform.h
//  PDFKit
//

#import <TargetConditionals.h>

    #define PDFKIT_PLATFORM_OSX

#if !(TARGET_OS_IPHONE || (TARGET_OS_OSX && TARGET_RT_64_BIT))
    #define PDFKIT_PLATFORM_i386
#endif

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



// OSX Headers
#import <Cocoa/Cocoa.h>
#import <AppKit/NSAccessibilityProtocols.h>

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
#define PDFKitPlatformTextFieldCell                             NSTextFieldCell
#define PDFKitPlatformTextFieldDidBeginEditing                  NSControlTextDidBeginEditingNotification
#define PDFKitPlatformTextFieldDidChangeText                    NSControlTextDidChangeNotification
#define PDFKitPlatformTextFieldDidEndEditing                    NSControlTextDidEndEditingNotification
#define PDFKitPlatformTextView                                  NSTextView
#define PDFKitPlatformTextViewDidChangeSelection                NSTextViewDidChangeSelectionNotification
#define PDFKitPlatformChoiceWidgetComboBoxView                  NSPopUpButton
#define PDFKitPlatformChoiceWidgetListView                      NSTableView
#define PDFKitPlatformButton                                    NSButton
#define PDFKitPlatformButtonCell                                NSButtonCell
#define PDFKitPlatformAccessibilityElement                      NSAccessibilityElement

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


