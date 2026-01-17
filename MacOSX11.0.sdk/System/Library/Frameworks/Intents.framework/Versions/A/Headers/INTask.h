//
//  INTask.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INTaskPriority.h>
#import <Intents/INTaskStatus.h>
#import <Intents/INTaskType.h>

@class INSpatialEventTrigger;
@class INSpeakableString;
@class INTemporalEventTrigger;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INTask : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithTitle:(INSpeakableString *)title
                       status:(INTaskStatus)status
                     taskType:(INTaskType)taskType
          spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
         temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger
        createdDateComponents:(nullable NSDateComponents *)createdDateComponents
       modifiedDateComponents:(nullable NSDateComponents *)modifiedDateComponents
                   identifier:(nullable NSString *)identifier
                     priority:(INTaskPriority)priority NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(13.0), watchos(6.0));

- (instancetype)initWithTitle:(INSpeakableString *)title
                       status:(INTaskStatus)status
                     taskType:(INTaskType)taskType
          spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
         temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger
        createdDateComponents:(nullable NSDateComponents *)createdDateComponents
       modifiedDateComponents:(nullable NSDateComponents *)modifiedDateComponents
                   identifier:(nullable NSString *)identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskStatus status;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpatialEventTrigger *spatialEventTrigger;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTemporalEventTrigger *temporalEventTrigger;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *createdDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *modifiedDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskType taskType;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskPriority priority API_AVAILABLE(ios(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END
