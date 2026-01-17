/*
	NSDraggingItem.h
	Application Kit
	Copyright (c) 2010-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString;
@protocol NSPasteboardWriting;


APPKIT_EXTERN NSString * const NSDraggingImageComponentIconKey NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSDraggingImageComponentLabelKey NS_AVAILABLE_MAC(10_7);

NS_CLASS_AVAILABLE(10_7, NA)
@interface NSDraggingImageComponent : NSObject {
@private
    NSString *_key;
    id	_contents;
    NSRect _frame;
}

+ (NSDraggingImageComponent *)draggingImageComponentWithKey:(NSString *)key;

/* Designated initializer */
- (instancetype)initWithKey:(NSString *)key;

/* key must be unique for each component in an NSDraggingItem. You can create your own named components, but the following names have special meaning. NSDraggingImageComponentIconKey is an image of the item being dragged. NSDraggingImageComponentLabelKey represents a textual label associate with the item, for example, a file name.
*/
@property (copy) NSString *key;

/* An object providing the image contents of the component, typically you set an NSImage, but may be anything CALayer accepts.
*/
@property (nullable, strong) id contents;

/* The coordinate space is the bounds of the parent NSDraggingItem. That is, {{0,0}, {draggingFrame.size.width, draggingFrame.size.height}} Note: NSDraggingItem does not clip its components.
*/
@property NSRect frame;

@end

NS_CLASS_AVAILABLE(10_7, NA)
@interface NSDraggingItem : NSObject {
@private
    id _item;
    NSRect _frame;
    NSArray *_components;
    NSArray *(^_componentsProvider)(void);
#if !__LP64__
    NSInteger _reserved1;
    NSInteger _reserved2;
#endif
}

/* The designated initializer. When creating an NSDraggingItem the pasteboardWriter must implement the NSPasteboardWriting protocol.
*/
- (instancetype)initWithPasteboardWriter:(id <NSPasteboardWriting>) pasteboardWriter;

/* When you create an NSDraggingItem, item is the pasteboardWriter passed to initWithPasteboardWriter. However, when enumerating dragging items in an NSDraggingSession or NSDraggingInfo object, item is not the original pasteboardWriter. It is an instance of one of the classes provided to the enumeration method.
*/
@property (readonly, strong) id item;

/* The dragging frame that provides the spatial relationship between NSDraggingItems in the NSDraggingFormationNone. Note: The exact coordinate space of this rect depends on where it is used. See NSDraggingSession and NSDraggingInfo. 
*/
@property NSRect draggingFrame;

/* The dragging image is the composite of an array of NSDraggingImageComponents. The dragging image components may not be set directly. Instead, provide a block to generate the components and the block will be called if necessary. The block may be set to nil, meaning that this drag item has no image. Generally, only dragging destinations do this, and only if there is at least one valid item in the drop, and this is not it. The components are composited in painting order. That is, each component in the array is painted on top of the previous components in the array.
*/
@property (nullable, copy) NSArray<NSDraggingImageComponent *> * __nonnull (^imageComponentsProvider)(void);

/* Alternate single image component setter. This method simplifies modifiying the components of an NSDraggingItem when there is only one component. This method will set the draggingFrame and imageComponentsProvider properties. frame is in the same coordinate space that the draggingFrame property is.
*/
- (void)setDraggingFrame:(NSRect)frame contents:(id)contents;

/* An array of NSDraggingImageComponents that are used to create the drag image. Note: the array contains copies of the components. Changes made to these copies are not reflected in the drag. If needed, the imageComponentsProvider block is called to generate the image components.
*/
@property (nullable, readonly, copy) NSArray<NSDraggingImageComponent *> *imageComponents;

@end

NS_ASSUME_NONNULL_END
