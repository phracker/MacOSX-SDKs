/*
        NSPDFInfo.h
        Application Kit
        Copyright (c) 2013-2018, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSPrintInfo.h>

NS_ASSUME_NONNULL_BEGIN

@class NSURL;

NS_CLASS_AVAILABLE_MAC(10_9)
@interface NSPDFInfo : NSObject <NSCopying, NSCoding> {
    NSURL *_URL APPKIT_IVAR;
    NSArray *_tagNames APPKIT_IVAR;
    NSPaperOrientation _orientation APPKIT_IVAR;
    NSSize _paperSize APPKIT_IVAR;
    NSMutableDictionary *_attributes APPKIT_IVAR;
    BOOL _fileExtensionHidden APPKIT_IVAR;
};

@property (copy, nullable) NSURL *URL;
@property (getter=isFileExtensionHidden) BOOL fileExtensionHidden;
@property (copy) NSArray<NSString *> *tagNames;
@property NSPaperOrientation orientation;
@property NSSize paperSize;
@property (readonly) NSMutableDictionary<NSPrintInfoAttributeKey, id> *attributes;

@end

NS_ASSUME_NONNULL_END
