/*
        NSTextAttachmentCell.h
        Copyright (c) 2021-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSCell.h>

@class NSTextAttachment;
@class NSLayoutManager;
@class NSTextContainer;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

#if !TARGET_OS_IPHONE
// These are the only methods required of cells in text attachments... The default NSCell class implements most of these; the NSTextAttachmentCell class is a subclass which implements all and provides some additional functionality.
API_UNAVAILABLE(macCatalyst)
@protocol NSTextAttachmentCell <NSObject>
- (void)drawWithFrame:(NSRect)cellFrame inView:(nullable NSView *)controlView NS_SWIFT_UI_ACTOR;
- (BOOL)wantsToTrackMouse NS_SWIFT_UI_ACTOR;
- (void)highlight:(BOOL)flag withFrame:(NSRect)cellFrame inView:(nullable NSView *)controlView NS_SWIFT_UI_ACTOR;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(nullable NSView *)controlView untilMouseUp:(BOOL)flag NS_SWIFT_UI_ACTOR;
- (NSSize)cellSize NS_SWIFT_NONISOLATED;
- (NSPoint)cellBaselineOffset NS_SWIFT_NONISOLATED;
@property (nullable, assign) NSTextAttachment *attachment NS_SWIFT_NONISOLATED;

// Sophisticated cells should implement these in addition to the simpler methods, above.  The class NSTextAttachmentCell implements them to simply call the simpler methods; more complex conformers should implement the simpler methods to call these.
- (void)drawWithFrame:(NSRect)cellFrame inView:(nullable NSView *)controlView characterIndex:(NSUInteger)charIndex NS_SWIFT_UI_ACTOR;
- (void)drawWithFrame:(NSRect)cellFrame inView:(nullable NSView *)controlView characterIndex:(NSUInteger)charIndex layoutManager:(NSLayoutManager *)layoutManager NS_SWIFT_UI_ACTOR;
- (BOOL)wantsToTrackMouseForEvent:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(nullable NSView *)controlView atCharacterIndex:(NSUInteger)charIndex NS_SWIFT_UI_ACTOR;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(nullable NSView *)controlView atCharacterIndex:(NSUInteger)charIndex untilMouseUp:(BOOL)flag NS_SWIFT_UI_ACTOR;
- (NSRect)cellFrameForTextContainer:(NSTextContainer *)textContainer proposedLineFragment:(NSRect)lineFrag glyphPosition:(NSPoint)position characterIndex:(NSUInteger)charIndex NS_SWIFT_NONISOLATED;
@end


// Simple class to provide basic attachment cell functionality. By default this class causes NSTextView to send out delegate messages when the attachment is clicked on or dragged.
@interface NSTextAttachmentCell : NSCell <NSTextAttachmentCell>
@end
#endif // !TARGET_OS_IPHONE

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
