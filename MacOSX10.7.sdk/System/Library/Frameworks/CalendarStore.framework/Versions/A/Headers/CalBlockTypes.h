//
//  CalBlockTypes.h
//  CalendarStore
//
//  Created by Sean Seguin on 1/14/11.
//  Copyright 2011 Apple. All rights reserved.
//
@class NSManagedObject, NSManagedObjectContext;
typedef void (^CalProgressBlock)(NSUInteger currentUnits, NSUInteger totalUnits, BOOL totalIsKnown);
typedef void (^CalCompletionBlock)(void);
typedef void (^CalDeletionBlock)(NSManagedObject *object, NSManagedObjectContext *context);
typedef void (^CalErrorBlock)(NSError *error);
