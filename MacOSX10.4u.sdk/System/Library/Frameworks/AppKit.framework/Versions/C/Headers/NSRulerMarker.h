/*
        NSRulerMarker.h
        Application Kit
        Copyright (c) 1994-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

@class NSEvent, NSImage, NSRulerView;

@interface NSRulerMarker : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    NSRulerView *_ruler;
    float _location;
    NSImage *_image;
    NSPoint _imageOrigin;

    struct __rFlags {
        unsigned int movable:1;
        unsigned int removable:1;
        unsigned int dragging:1;
        unsigned int pinned:1;
        unsigned int _reserved:28;
    } _rFlags;

    id _representedObject;
}

/**************************** Initialization ****************************/

- (id)initWithRulerView:(NSRulerView *)ruler markerLocation:(float)location image:(NSImage *)image imageOrigin:(NSPoint)imageOrigin;
    // Designated initializer.  Location is expressed in the client view's bounds coordinates.  Location is the x position if the ruler is horizontal or the y position if the ruler is vertical.  The image will not be scaled or rotated.  The image origin indicates the point in the image that will be placed on the ruler's baseline at the given location and is expressed in the image's coordinate system.  NSRulerMarkers are movable but not removable by default.  A removable object should have its dimmed image set.

/*********************** Query/Set basic attributes ***********************/

- (NSRulerView *)ruler;
    // Returns the ruler.


- (void)setMarkerLocation:(float)location;
- (float)markerLocation;
    // The location is set by the -init... method and the -setLocation: method.  Location is an x position for horizontal rulers or a y position for vertical rulers.  It is expressed in the client view's coordinate system.

- (void)setImage:(NSImage *)image;
- (NSImage *)image;
    // The image is what's drawn in the ruler.

- (void)setImageOrigin:(NSPoint)imageOrigin;
- (NSPoint)imageOrigin;
    // The image is drawn such that the image origin is on the baseline of the ruler at the object's location.

- (void)setMovable:(BOOL)flag;
- (void)setRemovable:(BOOL)flag;
- (BOOL)isMovable;
- (BOOL)isRemovable;
    // Objects are movable, but not removable by default.  Movable means the ruler object can be dragged by the user.  Removable means it can be deleted by the user.

- (BOOL)isDragging;
    // Returns YES if the ruler object is currently being dragged.

- (void)setRepresentedObject:(id <NSCopying>)representedObject;
- (id <NSCopying>)representedObject;
    // The representedObject of an NSRulerMarker is purely for the client's use.  It must be able to copy itself.  A represented object should be some small object.  The text object uses NSStrings for most ruler objects or NSTextTab objects for tab stops.

/************************** Ruler facilities **************************/

- (NSRect)imageRectInRuler;
    // Returns the rect that would be occupied by the object's image in the ruler's bounds coordinates.  This takes the flippedness of the ruler into account.

- (float)thicknessRequiredInRuler;
    // Returns the height or width (depending on the ruler's orientation) required in the ruler to display the object.

- (void)drawRect:(NSRect)rect;
    // Draws the object at it's current location.  Only rect needs to be drawn.

- (BOOL)trackMouse:(NSEvent *)mouseDownEvent adding:(BOOL)isAdding;
    // Handles the given mmouseDown event.  Performs a modal tracking loop until mouseUp allowing the object to be moved, if movable or removed, if removable.

@end
