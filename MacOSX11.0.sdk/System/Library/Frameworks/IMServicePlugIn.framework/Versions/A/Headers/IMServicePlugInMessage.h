/*
    IMServicePlugInMessage.h
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>


typedef struct _IMServicePlugInMessageInternal IMServicePlugInMessageInternal;

NS_CLASS_DEPRECATED_MAC(10_7, 10_13)
@interface IMServicePlugInMessage : NSObject <NSCoding, NSCopying> {
    IMServicePlugInMessageInternal *_internal;
}

+ (id) servicePlugInMessageWithContent:(NSAttributedString*)content NS_DEPRECATED_MAC(10_7, 10_13);
- (id) initWithContent:(NSAttributedString*)content NS_DEPRECATED_MAC(10_7, 10_13);

+ (id) servicePlugInMessageWithContent:(NSAttributedString*)content date:(NSDate *)date NS_DEPRECATED_MAC(10_7, 10_13);
- (id) initWithContent:(NSAttributedString*)content date:(NSDate *)date NS_DEPRECATED_MAC(10_7, 10_13);

@property (readonly) NSString *guid NS_DEPRECATED_MAC(10_7, 10_13);
@property (nonatomic, copy) NSAttributedString *content NS_DEPRECATED_MAC(10_7, 10_13);
@property (nonatomic, copy) NSDate *date NS_DEPRECATED_MAC(10_7, 10_13);

@end
