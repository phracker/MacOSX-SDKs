/*
    IMServicePlugInMessage.h
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>


typedef struct _IMServicePlugInMessageInternal IMServicePlugInMessageInternal;

@interface IMServicePlugInMessage : NSObject <NSCoding, NSCopying> {
    IMServicePlugInMessageInternal *_internal;
}

+ (id) servicePlugInMessageWithContent:(NSAttributedString*)content;
- (id) initWithContent:(NSAttributedString*)content;

@property (readonly) NSString *guid;
@property (nonatomic, copy) NSAttributedString *content;

@end
