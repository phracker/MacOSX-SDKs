//
//  EKObject.h
//  EventKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface EKObject : NSObject {
}

// Returns YES if this object or any sub-object (alarm, etc.) has uncommitted changes.
- (BOOL)hasChanges;

// Returns YES if this object has never been saved.
- (BOOL)isNew;

// If this object is not new, this method will unload all loaded properties and clear any dirty state
- (void)reset;

// If this object is not new, this method will unload dirty state only.
- (void)rollback;

// Determines if the object is still valid (i.e. it still exists in the database), and unloads all
// properties that have not been modified. If this ever returns NO, it indicates the record was deleted
// and this instance should be discarded and no longer referenced.
- (BOOL)refresh;

@end
