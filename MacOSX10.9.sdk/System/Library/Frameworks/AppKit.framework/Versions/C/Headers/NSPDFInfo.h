/*
        NSPDFInfo.h
        Application Kit
        Copyright (c) 2013, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSPrintInfo.h>

@class NSURL, NSArray, NSMutableDictionary;

NS_CLASS_AVAILABLE_MAC(10_9)
@interface NSPDFInfo : NSObject <NSCopying, NSCoding> {
    NSURL *_URL;
    NSArray *_tagNames;
    NSPaperOrientation _orientation;
    NSSize _paperSize;
    NSMutableDictionary *_attributes;
    BOOL _fileExtensionHidden;
};

@property (copy) NSURL *URL;
@property (getter=isFileExtensionHidden) BOOL fileExtensionHidden;
@property (copy) NSArray *tagNames;
@property NSPaperOrientation orientation;
@property NSSize paperSize;
@property (readonly) NSMutableDictionary *attributes;

@end
