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

+ (id) servicePlugInMessageWithContent:(NSAttributedString*)content date:(NSDate *)date;
- (id) initWithContent:(NSAttributedString*)content date:(NSDate *)date;

@property (readonly) NSString *guid;
@property (nonatomic, copy) NSAttributedString *content;
@property (nonatomic, copy) NSDate *date;

@end
