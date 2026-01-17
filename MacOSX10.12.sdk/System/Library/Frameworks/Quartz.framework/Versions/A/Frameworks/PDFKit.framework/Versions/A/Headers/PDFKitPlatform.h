//
//  PDFKitPlatform.h
//  PDFKit
//

#import <TargetConditionals.h>

#define PDFKIT_PLATFORM_OSX




// OSX Headers
#import <Cocoa/Cocoa.h>
#import <AppKit/NSAccessibilityProtocols.h>

// AppKit types
#define PDFKitPlatformView                              NSView
#define PDFKitPlatformViewController                    NSViewController
#define PDFKitPlatformScrollView                        NSScrollView
#define PDFKitPlatformColor                             NSColor
#define PDFKitPlatformBezierPath                        NSBezierPath
#define PDFKitPlatformBezierPathElement                 NSBezierPathElement
#define PDFKitPlatformImage                             NSImage
#define PDFKitPlatformImageView                         NSImageView
#define PDFKitPlatformEvent                             NSEvent
#define PDFKitPlatformFont                              NSFont
#define PDFKitPlatformColor                             NSColor
#define PDFKitPlatformControl                           NSControl
#define PDFKitPlatformTextField                         NSTextField
#define PDFKitPlatformTextFieldDidBeginEditing          NSControlTextDidBeginEditingNotification
#define PDFKitPlatformTextFieldDidChangeText            NSControlTextDidChangeNotification
#define PDFKitPlatformTextFieldDidEndEditing            NSControlTextDidEndEditingNotification
#define PDFKitPlatformTextView                          NSTextView
#define PDFKitPlatformTextViewDidChangeSelection        NSTextViewDidChangeSelectionNotification
#define PDFKitPlatformChoiceWidgetView                  NSPopUpButton
#define PDFKitPlatformButton                            NSButton
#define PDFKitPlatformButtonCell                        NSButtonCell

// Geometry types
#define PDFPoint                                        NSPoint
#define PDFRect                                         NSRect
#define PDFSize                                         NSSize
#define PDFEdgeInsets                                   NSEdgeInsets

// Constants
#define PDFPointZero                                    NSZeroPoint
#define PDFSizeZero                                     NSZeroSize
#define PDFRectZero                                     NSZeroRect

// Availability / deprecation
#define PDFKIT_AVAILABLE(_osx)                          NS_AVAILABLE_MAC(_osx)
#define PDFKIT_DEPRECATED(_macIntro, _macDep)           NS_DEPRECATED_MAC(_macIntro, _macDep)



