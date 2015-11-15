/*
        NSTextAttachment.h
        Copyright (c) 1994-2015, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSCell.h>

NS_ASSUME_NONNULL_BEGIN

enum {
    NSAttachmentCharacter NS_ENUM_AVAILABLE(10_0, 7_0) = 0xFFFC // Replacement character is used for attachments
};

@class NSTextContainer;
@class NSLayoutManager;
@class NSImage;
@class NSTextAttachmentCell;
@protocol NSTextAttachmentCell;


// This protocol defines the interface to attachment objects from NSLayoutManager
@protocol NSTextAttachmentContainer <NSObject>
#if __OBJC2__
// This protocol is available only for Objective-C 2 or later architecture

// Returns the image object rendered by NSLayoutManager at imageBounds inside textContainer.  It should return an image appropriate for the target rendering context derived by arguments to this method.  The NSTextAttachment implementation returns -image when non-nil.  If -image==nil, it returns an image based on -contents and -fileType properties.
- (nullable NSImage *)imageForBounds:(NSRect)imageBounds textContainer:(nullable NSTextContainer *)textContainer characterIndex:(NSUInteger)charIndex  NS_AVAILABLE(10_11, 7_0);


// Returns the layout bounds to the layout manager.  The bounds origin is interpreted to match position inside lineFrag.  The NSTextAttachment implementation returns -bounds if not CGRectZero; otherwise, it derives the bounds value from -[image size].  Conforming objects can implement more sophisticated logic for negotiating the frame size based on the available container space and proposed line fragment rect.
- (NSRect)attachmentBoundsForTextContainer:(nullable NSTextContainer *)textContainer proposedLineFragment:(NSRect)lineFrag glyphPosition:(CGPoint)position characterIndex:(NSUInteger)charIndex NS_AVAILABLE(10_11, 7_0);

#endif
@end

NS_CLASS_AVAILABLE(10_0, 7_0) @interface NSTextAttachment : NSObject <NSTextAttachmentContainer, NSCoding>
{
    /*All instance variables are private*/
    NSFileWrapper *_fileWrapper;
    id <NSTextAttachmentCell>_cell;
    struct {
        unsigned int cellWasExplicitlySet:1;
        unsigned int ignoresOrientation:1;
        unsigned int allowsEditingContents:1;
        unsigned int :29;
    } _flags;
}

/**************************** Initialization ****************************/

// Designated initializer.  Both arguments can be nil.  When contentData==nil || uti==nil, the receiver is consider to be an attachment without document contents.  In this case, the NSAttributedString methods writing external file format tries to save the return value of -[NSTextAttachment image] instead.
- (instancetype)initWithData:(nullable NSData *)contentData ofType:(nullable NSString *)uti NS_DESIGNATED_INITIALIZER NS_AVAILABLE(10_11, 7_0);

// Previous designated initializer on OS X. This method invokes -initWithData:ofType: with nil arguments, then, fills -fileWrapper property.
- (instancetype)initWithFileWrapper:(nullable NSFileWrapper *)fileWrapper;


#if __OBJC2__
/**************************** Content properties ****************************/

// These two properties define the contents for the text attachment.  Modifying these properties have a side effect of invalidating -image and -fileWrapper properties. -fileType is an UTI describing the format for -contents.
@property(nullable, copy) NSData *contents NS_AVAILABLE(10_11, 7_0);
@property(nullable, copy) NSString *fileType NS_AVAILABLE(10_11, 7_0);

/**************************** Rendering/layout properties ****************************/

// Image representing the text attachment contents. Modifying this property invalidates -contents, -fileType, and -FileWrapper properties.
@property(nullable, strong) NSImage *image NS_AVAILABLE(10_11, 7_0);

// Defines the layout bounds of the receiver's graphical representation in the text coordinate system.  The origin is at the glyph location on the text baseline.  The default value is CGRectZero.
@property NSRect bounds NS_AVAILABLE(10_11, 7_0);
#endif

/**************************** Non-image contents properties ****************************/

// Optionally, NSTextAttachment can be associated with a file wrapper. Modifying this property has a side effect of invalidating -image, -contents, and fileType properties.
@property(nullable, strong) NSFileWrapper *fileWrapper;

// The cell which handles user interaction. By default an instance of NSTextAttachmentCell is used.
@property (nullable, strong) id <NSTextAttachmentCell> attachmentCell;

@end

@interface NSAttributedString (NSAttributedStringAttachmentConveniences)
// A convenience method for creating an attributed string containing attachment using NSAttachmentCharacter as the base character.
+ (NSAttributedString *)attributedStringWithAttachment:(NSTextAttachment *)attachment NS_AVAILABLE(10_0, 7_0);
@end

@interface NSMutableAttributedString (NSMutableAttributedStringAttachmentConveniences)

- (void)updateAttachmentsFromPath:(NSString *)path;

@end

// These are the only methods required of cells in text attachments... The default NSCell class implements most of these; the NSTextAttachmentCell class is a subclass which implements all and provides some additional functionality.
@protocol NSTextAttachmentCell <NSObject>
- (void)drawWithFrame:(NSRect)cellFrame inView:(nullable NSView *)controlView;
- (BOOL)wantsToTrackMouse;
- (void)highlight:(BOOL)flag withFrame:(NSRect)cellFrame inView:(nullable NSView *)controlView;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(nullable NSView *)controlView untilMouseUp:(BOOL)flag;
- (NSSize)cellSize;
- (NSPoint)cellBaselineOffset;
@property(nullable, assign) NSTextAttachment *attachment;

// Sophisticated cells should implement these in addition to the simpler methods, above.  The class NSTextAttachmentCell implements them to simply call the simpler methods; more complex conformers should implement the simpler methods to call these.
- (void)drawWithFrame:(NSRect)cellFrame inView:(nullable NSView *)controlView characterIndex:(NSUInteger)charIndex;
- (void)drawWithFrame:(NSRect)cellFrame inView:(nullable NSView *)controlView characterIndex:(NSUInteger)charIndex layoutManager:(NSLayoutManager *)layoutManager;
- (BOOL)wantsToTrackMouseForEvent:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(nullable NSView *)controlView atCharacterIndex:(NSUInteger)charIndex;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(nullable NSView *)controlView atCharacterIndex:(NSUInteger)charIndex untilMouseUp:(BOOL)flag;
- (NSRect)cellFrameForTextContainer:(NSTextContainer *)textContainer proposedLineFragment:(NSRect)lineFrag glyphPosition:(NSPoint)position characterIndex:(NSUInteger)charIndex;
@end


// Simple class to provide basic attachment cell functionality. By default this class causes NSTextView to send out delegate messages when the attachment is clicked on or dragged.
@interface NSTextAttachmentCell : NSCell <NSTextAttachmentCell> {
    /*All instance variables are private*/
    NSTextAttachment *_attachment;
}
@end

NS_ASSUME_NONNULL_END
