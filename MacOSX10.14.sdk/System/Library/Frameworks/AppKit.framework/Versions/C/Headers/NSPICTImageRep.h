/*
        NSPICTImageRep.h
        Application Kit
        Copyright (c) 1997-2018, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSPICTImageRep : NSImageRep
{
    /*All instance variables are private*/
    NSPoint      _pictOrigin APPKIT_IVAR;		/* topLeft of picFrame */
    NSData*      _pictData APPKIT_IVAR;
#if __LP64__
    id		 _imageRep APPKIT_IVAR;
    NSUInteger   _pictOffset APPKIT_IVAR;
#endif /* __LP64__ */
#if !__OBJC2__
    unsigned int _reserved1 APPKIT_IVAR;
    unsigned int _reserved2 APPKIT_IVAR;
#endif /* !__OBJC2__ */
}

+ (nullable instancetype)imageRepWithData:(NSData *)pictData;
- (nullable instancetype)initWithData:(NSData *)pictData;

@property (readonly, copy) NSData *PICTRepresentation;
@property (readonly) NSRect boundingBox;

@end

NS_ASSUME_NONNULL_END
